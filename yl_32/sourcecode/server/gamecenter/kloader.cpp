/* -------------------------------------------------------------------------
//	�ļ���		��	kloader.cpp
//	������		��	luobaohang
//	����ʱ��	��	2010/6/12 15:04:09
//	��������	��	
//
// -----------------------------------------------------------------------*/

#include "stdafx.h"
#include "Misc/objectpool.h"
#include "onlinegamebase/ksysservice.h"
#include "serverbase/kgclogicbaseinterface.h"
#include "kloader.h"
#include "kgcquery.h"
#include "kconnectlocal.h"
#include "kconnectpipe.h"
#include "ksocketserver.h"
#include "kgcconfig.h"
#include "kdbmanager.h"
#include "kinterfacemgr.h"
#include "kgclogicprovide.h"
#include "kgcmonitorprocess.h"
#include "kkeysharemem.h"
#include "ksharememorypool.h"
#include "kmempipesys.h"

#include "kdatadef.h"
#include "kconnectmgr.h"
#include "kmodulesetting.h"
#include "serverbase/kgcmoduledef.h"
#include "gclogicbase/kgclogicextinterface.h"
#include "kscriptenv.h"
#ifdef __unix
#include <dlfcn.h>
#endif // __unix


extern BOOL g_UnifyInit();
extern BOOL g_UnifyUnInit();
extern BOOL g_UnifyLoop();

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define GAME_FPS 16
const static UINT g_nElapsePerFrame = 1000 / GAME_FPS;

IKGcLogicRequire* g_pGcLogic = NULL;
// -------------------------------------------------------------------------
KLoader::KLoader(void)
{
	m_nCurElapse = 0;
	m_nLoaderId = -1;
}

KLoader::~KLoader(void)
{
}

KLoader* KLoader::Inst()
{
	static KLoader sLoader;
	return &sLoader;
}

IKInterfaceAcceptor* KLoader::RegisterAcceptor( BYTE byModuleId, IKProcessAcceptor* pIServer )
{	
	if (!m_mpProcessAcceptor.insert(MP_PROCESS_ACCEPTOR::value_type(byModuleId, pIServer)).second)
	{
		Q_Error("�ظ�ע�᣻ͬһ���͵Ľӿ���һ��Loader��ֻ�ܿ���һ����");
		return NULL;
	}

	m_lstAcceptor.push_back(KInterfaceAcceptor(byModuleId));

	return &m_lstAcceptor.back();
}

IKInterfaceConnector* KLoader::RegisterConnector( BYTE byConnectorModuleId, BYTE byAcceptorModuleId,
												 IKProcessConnector* pIClient, BOOL bIsEssencial )
{
	if (!m_mpProcessConnector.insert(MP_PROCESS_CONNECTOR::value_type((byConnectorModuleId << 8) | byAcceptorModuleId,
		pIClient)).second)
	{
		Q_Error("�ظ�ע�᣻һ��ģ���ͬһ��InterfaceType��Conectorֻ��ע��һ�Ρ�");
		return NULL;
	}

	m_lstConnetor.push_back(KInterfaceConnector(byAcceptorModuleId, byConnectorModuleId, bIsEssencial));

	return &m_lstConnetor.back();
}

BOOL KLoader::CreateGcInterfaces()
{
	for (INT i = emKGCMODULE_LOGICBASE; i < emKGCMODULE_ALL; ++i)
	{
		BYTE byLoaderId = KModuleSetting::Inst()->GetLoaderId(i);
		// �Ҳ���ģ���Ӧ��Loader
		if (byLoaderId == 0)
		{
		}
		else if (byLoaderId == (BYTE)m_nLoaderId) // ���Acceptorģ���ڱ�Loader
		{
			// ����һ���������ӣ���Acceptor��
			KConnectLocal* pConnect = KConnnectLocalMgr::Inst()->NewConnect();
			KConnectMgr::Inst()->SetConnect(i, pConnect);
		}
		else	// ����ƥ��ΪPipe����
		{
			// ����һ���������ӣ���Connector��
			KConnectPipe* pConnect = KConnectPipeMgr::Inst()->NewConnect(byLoaderId);
			QCONFIRM_RET_FALSE(pConnect);
			// ��ʱ����ΪValid�����ж�����Loader�Ƿ��Ѽ���
			pConnect->SetValid(TRUE);
			KConnectMgr::Inst()->SetConnect(i, pConnect);
		}
	}
	return TRUE;
}

BOOL KLoader::ProcessInterfaceData( BYTE byConnectId, BYTE byAcceptorModuleId, LPBYTE pbData, UINT uDataSize )
{
	if (byConnectId & 0x80) // Connector���͵ģ���Acceptor����
		return ProcessAcceptorData(byConnectId & 0x7f, byAcceptorModuleId, pbData, uDataSize);
	else
		return ProcessConnectorData(byConnectId, byAcceptorModuleId, pbData, uDataSize);
	return FALSE;
}

BOOL KLoader::ProcessAcceptorData( BYTE byConnectorModuleId, BYTE byAcceptorModuleId, LPBYTE pbData, UINT uDataSize )
{
	MP_PROCESS_ACCEPTOR::iterator it = m_mpProcessAcceptor.find(byAcceptorModuleId);
	QCONFIRM_RET_FALSE(it != m_mpProcessAcceptor.end());
	return it->second->ProcessData(byConnectorModuleId, pbData, uDataSize);
}

BOOL KLoader::ProcessConnectorData( BYTE byConnectorModuleId, BYTE byAcceptorModuleId, LPBYTE pbData, UINT uDataSize )
{
	MP_PROCESS_CONNECTOR::iterator it = m_mpProcessConnector.find((byConnectorModuleId << 8) | byAcceptorModuleId);
	QCONFIRM_RET_FALSE(it != m_mpProcessConnector.end());
	return it->second->ProcessData(pbData, uDataSize);
}

BOOL KLoader::LoadModules()
{
	for (INT i = emKGCMODULE_LOGICBASE; i < emKGCMODULE_ALL; ++i)
	{
		// ����Ƿ�Loader���ص�ģ��
		if(KModuleSetting::Inst()->GetLoaderId(i) != m_nLoaderId)
			continue;
		Q_Printl("______________________________________________");
		//Q_Printl("Loading Module " << i << " " << KModuleSetting::Inst()->GetModuleName(i) <<
		//	"(" << KModuleSetting::Inst()->GetModulePath(i) << ")...");
#ifdef WIN32
		HINSTANCE hDll = LoadLibrary(KModuleSetting::Inst()->GetModulePath(i));
		QCONFIRM_RET_FALSE(hDll);
		LPFN_CREATE_MODULE_INST lpfnCreateModuleInstance = (LPFN_CREATE_MODULE_INST)GetProcAddress(hDll,
			KD_CREATE_MODULE_INSTANCE_FUN);
		if (!lpfnCreateModuleInstance)
		{
			Q_Error("Cannot Find " << KD_CREATE_MODULE_INSTANCE_FUN << "In Dll " <<
				KModuleSetting::Inst()->GetModulePath(i) << " Module " << i);
			FreeLibrary(hDll);
			//continue;
		}
		QCONFIRM_RET_FALSE(lpfnCreateModuleInstance);
#else // WIN32
		// RTLD_DEEPBINDʹdlopen��windows����һ�£���Ӧ�ó���Ͷ�̬���е�ͬ��ȫ�ֱ�����ֱ�ռ�ô洢�ռ䣬
		// ����˱�����������ͬһ��ַ������������-->����....����-->�����������ش���
#ifdef RTLD_DEEPBIND
		void* pLib = dlopen(KModuleSetting::Inst()->GetModulePath(i), RTLD_NOW | RTLD_DEEPBIND);
#else
		void* pLib = dlopen(KModuleSetting::Inst()->GetModulePath(i), RTLD_NOW);
#endif // RTLD_DEEPBIND
		if ( ! pLib)
		{
			Q_Error("dlopen failed for Lib " << KModuleSetting::Inst()->GetModulePath(i)
				<< " Module " << i << " err: " << dlerror());
			//continue;
		}
		QCONFIRM_RET_FALSE(pLib);
		LPFN_CREATE_MODULE_INST lpfnCreateModuleInstance = (LPFN_CREATE_MODULE_INST)dlsym(pLib,
			KD_CREATE_MODULE_INSTANCE_FUN);
		if (!lpfnCreateModuleInstance)
		{
			Q_Error("Cannot Find " << KD_CREATE_MODULE_INSTANCE_FUN << "In Lib " <<
				KModuleSetting::Inst()->GetModulePath(i) << " " << dlerror());
			dlclose(pLib);
			//continue;
		}
		QCONFIRM_RET_FALSE(lpfnCreateModuleInstance);
#endif
		KGcQuery* pGcQuery = FeuNew<KGcQuery>::AddAutoRelease(new KGcQuery(i));
		IKGC_Module* piModule = lpfnCreateModuleInstance(pGcQuery);
		QCONFIRM_RET_FALSE(piModule);
		m_vecModuleList.push_back(piModule);

		QLogPrintf(LOG_INFO, "Module %d %s(%s) Init...",
			i, KModuleSetting::Inst()->GetModuleName(i), KModuleSetting::Inst()->GetModulePath(i));
		// Module��ʼ��
		QCONFIRM_RET_FALSE(piModule->OnInit());
	}
	QCONFIRM_RET_FALSE(m_vecModuleList.size() > 0);
	return TRUE;
}

VOID KLoader::GameLoop()
{
	//while(TRUE)
	//{
		g_UnifyLoop();
		// ��������Э�鴦��
		KConnnectLocalMgr::Inst()->ProcessPackage();
		// PipeЭ�鴦��
		KTPacketProcess<KLoader*, BOOL (KLoader::*) (LPVOID, UINT) > cProcessor(this, &KLoader::ProcessPipeData);
		KMemPipeSys::Inst()->Process(m_nLoaderId, &cProcessor);
		// GsЭ�鴦��
		KSocketServer::Inst()->Breath();

		for (UINT i = 0; i < m_vecModuleList.size(); ++i)
		{
			IKGC_Module* piModule = m_vecModuleList[i];
			piModule->Loop();
			
		}

		static UINT uFrameCounter = 0;
		UINT uElapse = KSysService::GetTickCount();
		if (m_nCurElapse + g_nElapsePerFrame <= uElapse)
		{
			// ��ȳ���2֡�����log
			if (uElapse - m_nCurElapse > g_nElapsePerFrame * 2)
			{
				Q_Printl("Warning: MilliSecond Between Two Frames: " << uElapse - m_nCurElapse);
			}
			++uFrameCounter;
			m_nCurElapse = uElapse;
			g_pGcLogic->Breath();
			for (UINT i = 0; i < m_vecModuleList.size(); ++i)
			{
				IKGC_Module* piModule = m_vecModuleList[i];
				piModule->Breath();
			}			
		}

		KDbManager::Inst()->MainThreadActive();

		// ���͹ܵ�����
		KMemPipeSys::Inst()->Flush();

		QThread_Sleep(1);
	//}
}

BOOL KLoader::ProcessPipeData( LPVOID pvData, UINT uDataSize )
{
	LPBYTE pbData = (LPBYTE)pvData;
	return ProcessInterfaceData(*pbData, *(pbData + 1), pbData + 2, uDataSize - 2);
}

BOOL KLoader::Init(INT nLoaderId )
{
	BOOL bResult = FALSE;
	m_nLoaderId = nLoaderId;

	bResult = KGcConfig::Inst()->LoadConfig();
	LOG_PROCESS_ERROR(bResult && "KGcConfig::Inst()->LoadConfig");

	bResult = KDbManager::Inst()->InitDBManager();
	LOG_PROCESS_ERROR(bResult && "KDbManager::Inst()->InitDBManager");
	bResult = KInterfaceMgr::Inst()->Init();
	LOG_PROCESS_ERROR(bResult && "KInterfaceMgr::Inst()->Init");

	bResult = KSocketServer::Inst()->Init("", KModuleSetting::Inst()->GetGsPort(nLoaderId));
	Q_Printl("[Loader] Socket for GameServer @ localhost:" << KModuleSetting::Inst()->GetGsPort(nLoaderId));
	LOG_PROCESS_ERROR(bResult && "KSocketServer::Inst()->Init");

	g_pGcLogic = g_ResgisterGcLogic(KGcLogicProvide::Inst());
	LOG_PROCESS_ERROR(g_pGcLogic);
	bResult = g_pGcLogic->OnInit(KDbManager::Inst());
	LOG_PROCESS_ERROR(bResult && "g_pGcLogic->OnInit");
	bResult = InitScript();
	LOG_PROCESS_ERROR(bResult && "InitScript");
	bResult = g_UnifyInit();
	LOG_PROCESS_ERROR(bResult && "g_UnifyInit");

	bResult = LoadModules();
	LOG_PROCESS_ERROR(bResult && "failed to load modules");

	bResult = KSocketServer::Inst()->StartUp();
	LOG_PROCESS_ERROR(bResult && "KSocketServer::Inst()->StartUp");
	bResult = CreateGcInterfaces();
	LOG_PROCESS_ERROR(bResult && "CreateGcInterfaces");
	bResult = g_pGcLogic->OnStartUp();
	LOG_PROCESS_ERROR(bResult && "g_pGcLogic->OnStartUp");

	for (UINT i = 0; i < m_vecModuleList.size(); ++i)
	{
		IKGC_Module* piModule = m_vecModuleList[i];
		QLogPrintf(LOG_INFO, "[Loader] Module %s Startup...", piModule->GetModuleName());
		bResult = piModule->OnStartUp();
		LOG_PROCESS_ERROR(bResult && "piModule->OnStartUp");
	}
	Q_Printl("[Loader] DbManager thread starting...");
	bResult = KDbManager::Inst()->StratUp();
	LOG_PROCESS_ERROR(bResult && "KDbManager::Inst()->StratUp");
	Q_Printl("GameCenter Stage 1 Complete!");
EXIT0:
	return bResult;
}

BOOL KLoader::Uninit()
{
	if (g_pGcLogic)
		g_pGcLogic->OnUninit();

	for (UINT i = 0; i < m_vecModuleList.size(); ++i)
	{
		IKGC_Module* piModule = m_vecModuleList[i];
		piModule->OnUninit();

	}
	KDbManager::Inst()->UnInit();
	KSocketServer::Inst()->UnInit();
	g_UnifyUnInit();

	return TRUE;
}

INT KLoader::InitScript()
{
	// refact this
	ScriptSafe cSafeScript = KGcScriptEnv::Inst()->GetScriptManager().GetSafeScript();
	cSafeScript->PushNumber(KModuleSetting::Inst()->m_nDevModeFlag);
	cSafeScript->SetGlobalName("IS_DEV_MODE");
	return TRUE;
}
