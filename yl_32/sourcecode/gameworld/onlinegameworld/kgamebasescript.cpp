/* -------------------------------------------------------------------------
//	�ļ���		��	kgamebasescript.cpp
//	������		��	simon
//	����ʱ��	��	2009/12/30 12:12:28
//	��������	��	
//
// -----------------------------------------------------------------------*/

#include "stdafx.h"
#include "onlinegameworld/korpgworld.h"
#include "onlinegameworld/kcharacter.h"
#include "onlinegameworld/kplayer.h"
#include "onlinegameworld/knpc.h"
#include "onlinegameworld/kdoodad.h"
#include "onlinegameworld/ikscenemgr.h"
#include "onlinegameworld/ikscene.h"
#include "onlinegameworld/kcharactermgr.h"
#include "onlinegameworld/knpcmgr.h"
#include "onlinegameworld/kluanpc.h"
#include "onlinegameworld/kluaplayer.h"
#include "onlinegameworld/kdoodadmgr.h"
#include "onlinegamebase/ksysservice.h"
#include "onlinegameworld/ikgameserver.h"
#include "ksocketinterface.h"
#include "onlinegameworld/synchelper.h"
#include "onlinegamemodule/ai/kaimanager.h"
#include "../nsworld/kcharacterhelper.h"
#include "../onlinegamemodule/instance/kinstancectrl.h"
#include "../onlinegamemodule/bladestate/kbladectrl.h"
#include "../onlinegamemodule/arena/ArenaHelper.h"

#include "onlinegameworld/klogwritter.h"
#include "KRelayClient.h"
#include "../onlinegamemodule/overallteam/koverallrelayclient.h"

#ifdef GAME_SERVER
#include "onlinegameworld/kplayermgr.h"
#else
#include "onlinegameworld/kplayermanager_client.h"
#endif // GAME_SERVER


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// -------------------------------------------------------------------------


extern QLogFile* g_pScriptLogFile;
extern IKSocketClientInterface* g_piSocketClient;
// -------------------------------------------------------------------------

namespace KGameBaseNamespace
{
	// -------------------------------------------------------------------------
	// @ClientSvr(C/S)	: 
	// @ClassName		: --
	// @LuaApiName		: Sleep
	// @Description		: Debug: ʹ���߳�ֹͣһ��ʱ��
	// @ReturnCode		: 
	// @ArgumentFlag	: d
	// @ArgumentComment	: dwMilliSeconds
	// @LuaMarkEnd
	// -------------------------------------------------------------------------
	INT LuaSleep(QLuaScript& sc)
	{
		DWORD dwMilliSeconds = sc.GetInt(1);
		QThread_Sleep(dwMilliSeconds);
		return 1;
	}

	// -------------------------------------------------------------------------
	// @ClientSvr(C/S)	: 
	// @ClassName		: --
	// @LuaApiName		: WriteLog
	// @Description		: д�ű���־
	// @ReturnCode		: 
	// @ArgumentFlag	: ds
	// @ArgumentComment	: ��־��Ҫ�ȼ� LOG_RECORD_REMIND_LEVEL
	// @ArgumentComment	: ����
	// @LuaMarkEnd
	// -------------------------------------------------------------------------
	INT LuaWriteLog(QLuaScript& sc)
	{
		INT nLevel = sc.GetInt(1);
		LPCSTR pszStr = sc.GetStr(2);

		g_pScriptLogFile->LogRecord(
			(LOG_RECORD_REMIND_LEVEL)nLevel,
			pszStr
			);
		return 1;
	}

	// -------------------------------------------------------------------------
	// @ClientSvr(C/S)	: 
	// @ClassName		: --
	// @LuaApiName		: WriteLogServer
	// @Description		: дlogserver��־
	// @ReturnCode		: 
	// @ArgumentFlag	: ds
	// @ArgumentComment	: ��־����
	// @ArgumentComment	: ����
	// @LuaMarkEnd
	// -------------------------------------------------------------------------
	INT LuaWriteLogServer(QLuaScript& sc)
	{
		INT nType = sc.GetInt(1);
		LPCSTR pszStr = sc.GetStr(2);

		KLogWritter::GetInstance()->LogSever_DataAnalysisLog(nType, pszStr);
		return 1;
	}

	// -------------------------------------------------------------------------
	// @ClientSvr(C/S)	: 
	// @ClassName		: --
	// @LuaApiName		: GetPlayerByName
	// @Description		: ͨ����ɫ�����Player
	// @ReturnCode		: o
	// @ArgumentFlag	: s
	// @ArgumentComment	: szName
	// @LuaMarkEnd
	// -------------------------------------------------------------------------
	INT LuaGetPlayerByName(QLuaScript& sc)
	{
		LPCSTR pszName = sc.GetStr(1);

		KPlayer* pPlayer = g_cPlayerMgr.GetByName(pszName);
		KLuaPlayer* pLuaPlayer = NULL;

		if (pPlayer && (pLuaPlayer = (KLuaPlayer*)pPlayer->GetScriptInterface()))
			sc.PushObj((QLunaBase*)pLuaPlayer);
		else
			sc.PushNull();

		return 1;
	}

	// -------------------------------------------------------------------------
	// @ClientSvr(C/S)	: 
	// @ClassName		: --
	// @LuaApiName		: GetPlayerById
	// @Description		: ͨ��Id���Player
	// @ReturnCode		: o
	// @ArgumentFlag	: d
	// @ArgumentComment	: dwId
	// @LuaMarkEnd
	// -------------------------------------------------------------------------
	INT LuaGetPlayerById(QLuaScript& sc)
	{
		DWORD dwId = (DWORD)sc.GetInt(1);

		KPlayer* pPlayer = g_cPlayerMgr.GetById(dwId);
		KLuaPlayer* pLuaPlayer = NULL;

		if (pPlayer && (pLuaPlayer = (KLuaPlayer*)pPlayer->GetScriptInterface()))
			sc.PushObj((QLunaBase*)pLuaPlayer);
		else
			sc.PushNull();

		return 1;
	}

	// -------------------------------------------------------------------------
	// @ClientSvr(C/S)	: 
	// @ClassName		: --
	// @LuaApiName		: SaveAllPlayers
	// @Description		: ���̵�ǰ�������
	// @ReturnCode		: 
	// @ArgumentFlag	: 
	// @LuaMarkEnd
	// -------------------------------------------------------------------------
	INT LuaSaveAllPlayers(QLuaScript& sc)
	{
		std::vector<KPlayer*> vPlayers;

		g_cPlayerMgr.GetAllPlayers(vPlayers);
		for (std::vector<KPlayer*>::iterator it = vPlayers.begin(); it != vPlayers.end(); ++it)
		{
			KPlayer* pPlayer = *it;
			pPlayer->m_cPlayerServer.SavePosition();
			g_RelayClient.SaveRoleData(pPlayer);
			g_RelayClient.DoSaveDelayRoleData(pPlayer);
		}

		return 0;
	}

	// -------------------------------------------------------------------------
	// @ClientSvr(C/S)	: 
	// @ClassName		: --
	// @LuaApiName		: SavePlayerDelayData
	// @Description		: �洢�����������
	// @ReturnCode		: 
	// @ArgumentFlag	: o
	// @ArgumentComment	: player
	// @LuaMarkEnd
	// -------------------------------------------------------------------------
	INT LuaSavePlayerDelayData(QLuaScript& sc)
	{
		KPlayer* pPlayer = NULL;
		KLuaPlayer *pLuaPlayer = dynamic_cast<KLuaPlayer *>(sc.GetObj(1));

		if (pLuaPlayer)
		{
			pPlayer = pLuaPlayer->GetHim();
		}
		LOG_PROCESS_ERROR(pPlayer);

		g_RelayClient.DoSaveDelayRoleData(pPlayer);

	EXIT0:
		return 0;
	}

	// -------------------------------------------------------------------------
	// @ClientSvr(C/S)	: 
	// @ClassName		: --
	// @LuaApiName		: GetNpcById
	// @Description		: ͨ��Id���Npc
	// @ReturnCode		: o
	// @ArgumentFlag	: d
	// @ArgumentComment	: dwId
	// @LuaMarkEnd
	// -------------------------------------------------------------------------
	INT LuaGetNpcById(QLuaScript& sc)
	{
		DWORD dwId = (DWORD)sc.GetInt(1);

		KNpc* pNpc = g_cNpcMgr.GetById(dwId);
		KLuaNpc* pLuaNpc = NULL;

		if (pNpc && (pLuaNpc = (KLuaNpc*)pNpc->GetScriptInterface()))
			sc.PushObj((QLunaBase*)pLuaNpc);
		else
			sc.PushNull();

		return 1;
	}

	// -------------------------------------------------------------------------
	// @ClientSvr(C/S)	: 
	// @ClassName		: --
	// @LuaApiName		: GetNpcByNickName
	// @Description		: ͨ���������Npc
	// @ReturnCode		: o
	// @ArgumentFlag	: ds
	// @ArgumentComment	: dwSceneId
	// @ArgumentComment	: szNickName
	// @LuaMarkEnd
	// -------------------------------------------------------------------------
	INT LuaGetNpcByNickName(QLuaScript& sc)
	{
		DWORD dwSceneId = (DWORD)sc.GetInt(1);

		IKScene* pScene = g_pSceneMgr->GetScene(dwSceneId);
		QCONFIRM_RET_FALSE(pScene);

		KNpc* pNpc = dynamic_cast<KNpc*>(pScene->GetByNickName(sc.GetStr(2)));
		KLuaNpc* pLuaNpc = NULL;

		if (pNpc && (pLuaNpc = (KLuaNpc*)pNpc->GetScriptInterface()))
			sc.PushObj((QLunaBase*)pLuaNpc);
		else
			sc.PushNull();

		return 1;
	}

	// -------------------------------------------------------------------------
	// @ClientSvr(C/S)	: 
	// @ClassName		: --
	// @LuaApiName		: GetDoodadByNickName
	// @Description		: ͨ���������Doodad
	// @ReturnCode		: o
	// @ArgumentFlag	: ds
	// @ArgumentComment	: dwSceneId
	// @ArgumentComment	: szNickName
	// @LuaMarkEnd
	// -------------------------------------------------------------------------
	INT LuaGetDoodadByNickName(QLuaScript& sc)
	{
		DWORD dwSceneId = (DWORD)sc.GetInt(1);

		IKScene* pScene = g_pSceneMgr->GetScene(dwSceneId);
		QCONFIRM_RET_FALSE(pScene);

		KDoodad* pDoodad = dynamic_cast<KDoodad*>(pScene->GetByNickName(sc.GetStr(2)));
		KLuaDoodad* pLuaDoodad = NULL;

		if (pDoodad && (pLuaDoodad = pDoodad->GetScriptInterface()))
			sc.PushObj((QLunaBase*)pLuaDoodad);
		else
			sc.PushNull();

		return 1;
	}

	// -------------------------------------------------------------------------
	// @ClientSvr(C/S)	: 
	// @ClassName		: --
	// @LuaApiName		: GetNameByTemplateId
	// @Description		: ����Npc��ģ��ID������NpcName
	// @ReturnCode		: �ɹ�����npc���ƣ�ʧ�ܷ��ؿ�
	// @ArgumentFlag	: d
	// @ArgumentComment	: nNpcTemplateID:Npc��ģ��ID
	// @LuaMarkEnd
	// -------------------------------------------------------------------------
	INT LuaGetNameByTemplateId(QLuaScript& sc)
	{
		INT nTemplateId	= sc.GetInt(1);
		ASSERT(nTemplateId > 0);
		CONST KNPC_TEMPLATE* pNpcTemp = g_cNpcMgr.GetTemplateInfo(nTemplateId);
		if (!pNpcTemp)
			return 0;

		sc.PushString(pNpcTemp->strDisplayName);

		return 1;
	}

	// -------------------------------------------------------------------------
	// @ClientSvr(C/S)	: 
	// @ClassName		: --
	// @LuaApiName		: GetNpcTitleByTemplateId
	// @Description		: ����Npc��ģ��ID������NpcTitle
	// @ReturnCode		: �ɹ�����npc���ƣ�ʧ�ܷ��ؿ�
	// @ArgumentFlag	: d
	// @ArgumentComment	: Npc��ģ��ID
	// @LuaMarkEnd
	// -------------------------------------------------------------------------
	INT LuaGetNpcTitleByTemplateId(QLuaScript& sc)
	{
		INT nTemplateId	= sc.GetInt(1);
		ASSERT(nTemplateId > 0);
		CONST KNPC_TEMPLATE* pNpcTemp = g_cNpcMgr.GetTemplateInfo(nTemplateId);
		if (!pNpcTemp)
			return 0;

		sc.PushString(pNpcTemp->strTitle);

		return 1;
	}

	// -------------------------------------------------------------------------
	// @ClientSvr(C/S)	: 
	// @ClassName		: --
	// @LuaApiName		: FindNpcWithTemplateId
	// @Description		: ����ģ��ID����Npc
	// @ReturnCode		: �����б�{o}
	// @ArgumentFlag	: ud
	// @ArgumentComment	: dwSceneId ����Id
	// @ArgumentComment	: nNpcTemplateId: Npc��ģ��Id
	// @LuaMarkEnd
	// -------------------------------------------------------------------------
	INT LuaFindNpcWithTemplateId(QLuaScript& sc)
	{
		INT nRet = 0;
		INT nMapId = sc.GetInt(1);
		INT nNpcTemplateId = sc.GetInt(2);

		IKScene* pScene = g_pSceneMgr->GetScene(nMapId);
		QCONFIRM_RET_FALSE(pScene);

		std::vector<KNpc*>::iterator it;
		TKTraverseHelper<KNpc> m_cTraverseHelper;
		pScene->TraverseAllNpcs(m_cTraverseHelper);

		sc.PushTable();
		for (it = m_cTraverseHelper.m_vObjList.begin(); it != m_cTraverseHelper.m_vObjList.end(); ++it)
		{
			KNpc* pNpc = *it;
			sc.PushObj((QLunaBase*)pNpc->GetScriptInterface());
			sc.SetTableField(pNpc->GetName());
		}
		return 1;
	}

	// -------------------------------------------------------------------------
	// @ClientSvr(C/S)	: 
	// @ClassName		: --
	// @LuaApiName		: GetDoodadNameByTemplateId
	// @Description		: ����Doodad��ģ��ID������DoodadName
	// @ReturnCode		: �ɹ�����Doodad���ƣ�ʧ�ܷ��ؿ�
	// @ArgumentFlag	: d
	// @ArgumentComment	: nDoodadTemplateID:Doodad��ģ��ID
	// @LuaMarkEnd
	// -------------------------------------------------------------------------
	INT LuaGetDoodadNameByTemplateId(QLuaScript& sc)
	{
		INT nTemplateId	= sc.GetInt(1);
		ASSERT(nTemplateId > 0);

		const KDOODAD_TEMPLATE* pTemplate = g_cDoodadMgr.GetTemplateInfo(nTemplateId);

		if (pTemplate)
			sc.PushString(pTemplate->strDisplayName);
		else
			sc.PushNull();

		return 1;
	}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: --
// @LuaApiName		: GetCharacterById
// @Description		: ͨ��Id�õ�Character
// @ReturnCode		: o
// @ArgumentFlag	: d
// @ArgumentComment	: CharacterId
// @LuaMarkEnd
// -------------------------------------------------------------------------
	INT LuaGetCharacterById(QLuaScript& sc)
	{
		DWORD dwId = (DWORD)sc.GetInt(1);

		KCharacter* pCharacter = g_cCharacterMgr.GetById(dwId);
		if (!pCharacter)
			return 0;

		sc.PushObj((QLunaBase*)pCharacter->GetScriptInterface());

		return 1;
	}

	// -------------------------------------------------------------------------
	// @ClientSvr(C/S)	: 
	// @ClassName		: --
	// @LuaApiName		: GetDoodadById
	// @Description		: ͨ��Id�õ�Doodad
	// @ReturnCode		: o
	// @ArgumentFlag	: d
	// @ArgumentComment	: DoodadId
	// @LuaMarkEnd
	// -------------------------------------------------------------------------
	INT LuaGetDoodadById(QLuaScript& sc)
	{
		DWORD dwId = (DWORD)sc.GetInt(1);

		KDoodad* pDoodad = g_cDoodadMgr.GetById(dwId);
		if (!pDoodad)
			return 0;

		sc.PushObj((QLunaBase*)pDoodad->GetScriptInterface());

		return 1;
	}

	// -------------------------------------------------------------------------
	// @ClientSvr(C/S)	: 
	// @ClassName		: --
	// @LuaApiName		: IsNpc
	// @Description		: ͨ��Id�ж��Ƿ�Npc
	// @ReturnCode		: y/n
	// @ArgumentFlag	: d
	// @ArgumentComment	: dwId
	// @LuaMarkEnd
	// -------------------------------------------------------------------------
	INT LuaIsNpc(QLuaScript& sc)
	{
		DWORD dwId = (DWORD)sc.GetInt(1);

		BOOL bTruth = IS_NPC(dwId);
		sc.PushNumber(bTruth);

		return 1;
	}

	// -------------------------------------------------------------------------
	// @ClientSvr(C/S)	: 
	// @ClassName		: --
	// @LuaApiName		: IsPlayer
	// @Description		: ͨ��Id�ж��Ƿ�Player
	// @ReturnCode		: y/n
	// @ArgumentFlag	: d
	// @ArgumentComment	: dwId
	// @LuaMarkEnd
	// -------------------------------------------------------------------------
	INT LuaIsPlayer(QLuaScript& sc)
	{
		DWORD dwId = (DWORD)sc.GetInt(1);

		BOOL bTruth = IS_PLAYER(dwId);
		sc.PushNumber(bTruth);

		return 1;
	}

	// -------------------------------------------------------------------------
	// @ClientSvr(C/S)	: 
	// @ClassName		: --
	// @LuaApiName		: GetTime
	// @Description		: ��õ�ǰʱ�䣨������
	// @ReturnCode		: ��1970��1��1��0ʱ�����������UTCʱ��������������ʱ�䣩
	// @ArgumentFlag	: 
	// @LuaMarkEnd
	// -------------------------------------------------------------------------
	INT LuaGetTime(QLuaScript& sc)
	{
		time_t t = KSysService::Time(NULL);
		sc.PushNumber((DWORD)t);
		return 1;
	}

	// -------------------------------------------------------------------------
	// @ClientSvr(C/S)	: 
	// @ClassName		: --
	// @LuaApiName		: EnableWorldDebug
	// @Description		: ����/��ֹ�������ڲ�������Ϣ
	// @ReturnCode		: 
	// @ArgumentFlag	: d
	// @ArgumentComment	: 1 ���� 0 ��ֹ
	// @LuaMarkEnd
	// -------------------------------------------------------------------------
	INT LuaEnableWorldDebug(QLuaScript &sc)
	{
		g_cOrpgWorld.m_bDebugSelf = sc.GetInt(1);
		return 0;
	}

	// -------------------------------------------------------------------------
	// @ClientSvr(C/S)	: 
	// @ClassName		: --
	// @LuaApiName		: GetPlayerCount
	// @Description		: ��������
	// @ReturnCode		: d
	// @ArgumentFlag	: 
	// @ArgumentComment	: 
	// @LuaMarkEnd
	// -------------------------------------------------------------------------
	INT LuaGetPlayerCount(QLuaScript &sc)
	{
		sc.PushNumber(g_cPlayerMgr.GetPlayerCount());
		return 1;
	}

	// -------------------------------------------------------------------------
	// @ClientSvr(C/S)	: 
	// @ClassName		: --
	// @LuaApiName		: GetNpcCount
	// @Description		: ���Npc��
	// @ReturnCode		: d
	// @ArgumentFlag	: 
	// @ArgumentComment	: 
	// @LuaMarkEnd
	// -------------------------------------------------------------------------
	INT LuaGetNpcCount(QLuaScript &sc)
	{
		sc.PushNumber(g_cNpcMgr.GetNpcCount());
		return 1;
	}

	// -------------------------------------------------------------------------
	// @ClientSvr(C/S)	: 
	// @ClassName		: --
	// @LuaApiName		: GetDoodadCount
	// @Description		: ���Doodad��
	// @ReturnCode		: d
	// @ArgumentFlag	: 
	// @ArgumentComment	: 
	// @LuaMarkEnd
	// -------------------------------------------------------------------------
	INT LuaGetDoodadCount(QLuaScript &sc)
	{
		sc.PushNumber(g_cDoodadMgr.GetDoodadCount());
		return 1;
	}

	// -------------------------------------------------------------------------
	// @ClientSvr(C/S)	: 
	// @ClassName		: --
	// @LuaApiName		: GetAllPlayers
	// @Description		: ��ȡ������ҿ��գ���Ҫ�洢pPlayer����Ϊplayer��������ã�
	// @ReturnCode		: *o
	// @ArgumentFlag	: 
	// @ArgumentComment	: 
	// @LuaMarkEnd
	// -------------------------------------------------------------------------
	INT LuaGetAllPlayers(QLuaScript &sc)
	{
		std::vector<KPlayer*> vPlayers;
		INT nRet = g_cPlayerMgr.GetAllPlayers(vPlayers);
		if (nRet)
		{
			sc.PushTable();
			INT nIndex = 1;
			for (std::vector<KPlayer*>::iterator it = vPlayers.begin(); it != vPlayers.end(); ++it)
			{
				sc.PushObj((QLunaBase*)(*it)->GetScriptInterface());
				sc.SetTableIndex(nIndex++);
			}
		}
		return nRet;
	}

	// -------------------------------------------------------------------------
	// @ClientSvr(C/S)	: 
	// @ClassName		: --
	// @LuaApiName		: GetServerId
	// @Description		: ��ȡ��������Id
	// @ReturnCode		: d
	// @ArgumentFlag	: 
	// @ArgumentComment	: 
	// @LuaMarkEnd
	// -------------------------------------------------------------------------
	INT LuaGetServerId(QLuaScript &sc)
	{
		sc.PushNumber(g_cOrpgWorld.m_nServerId);
		return 1;
	}

#ifdef GAME_CLIENT
	// -------------------------------------------------------------------------
	// @ClientSvr(C/S)	: C
	// @ClassName		: --
	// @LuaApiName		: GetPing
	// @Description		: ��ȡping������ʱ��
	// @ReturnCode		: d
	// @ArgumentFlag	: 
	// @ArgumentComment	: 
	// @LuaMarkEnd
	// -------------------------------------------------------------------------
	INT LuaGetPing(QLuaScript& sc)
	{
		sc.PushNumber(g_cOrpgWorld.m_nPing);
		return 1;
	}

	// -------------------------------------------------------------------------
	// @ClientSvr(C/S)	: C
	// @ClassName		: --
	// @LuaApiName		: GetClientPlayerId
	// @Description		: ��ÿͻ����Լ���Id��
	// @ReturnCode		: d
	// @ArgumentFlag	: 
	// @ArgumentComment	: 
	// @LuaMarkEnd
	// -------------------------------------------------------------------------
	INT LuaGetClientPlayerId(QLuaScript& sc)
	{
		DWORD dwId = g_cOrpgWorld.m_dwClientPlayerId;

		sc.PushNumber(dwId);

		return 1;
	}

	// -------------------------------------------------------------------------
	// @ClientSvr(C/S)	: C
	// @ClassName		: --
	// @LuaApiName		: Console
	// @Description		: �򿪿���̨���
	// @ReturnCode		: d
	// @ArgumentFlag	: 
	// @ArgumentComment	: 
	// @LuaMarkEnd
	// -------------------------------------------------------------------------
	INT LuaConsole(QLuaScript& sc)
	{
		sc.PushNumber(QConsoleHelper::CreateConsole());
		return 1;
	}

	// -------------------------------------------------------------------------
	// @ClientSvr(C/S)	: C
	// @ClassName		: --
	// @LuaApiName		: ShutDown
	// @Description		: �رտͻ�������
	// @ReturnCode		: d
	// @ArgumentFlag	: 
	// @ArgumentComment	: 
	// @LuaMarkEnd
	// -------------------------------------------------------------------------
	INT LuaShutDown(QLuaScript& sc)
	{
		sc.PushNumber(g_piSocketClient->ShutDown());
		return 1;
	}

	// -------------------------------------------------------------------------
	// @ClientSvr(C/S)	: C
	// @ClassName		: --
	// @LuaApiName		: GetServerTime
	// @Description		: ��ȡ������ʱ�䣨���������ݵ�¼ʱ������ʱ���������
	// @ReturnCode		: d
	// @ArgumentFlag	: 
	// @ArgumentComment	: 
	// @LuaMarkEnd
	// -------------------------------------------------------------------------
	INT LuaGetServerTime(QLuaScript& sc)
	{
		time_t timeServer = g_cOrpgWorld.GetServerTime();
		sc.PushNumber(timeServer);
		return 1;
	}

#endif // GAME_CLIENT

#ifdef GAME_SERVER

	// -------------------------------------------------------------------------
	// @ClientSvr(C/S)	: S
	// @ClassName		: --
	// @LuaApiName		: CallNpc
	// @Description		: �ٻ�Npc
	// @ReturnCode		: 
	// @ArgumentFlag	: ddddd[d]
	// @ArgumentComment	: dwNpcTemplateId
	// @ArgumentComment	: dwSceneId
	// @ArgumentComment	: nX
	// @ArgumentComment	: nY
	// @ArgumentComment	: nZ
	// @ArgumentComment	: nFaceDirection ���򣨿�ѡ��
	// @LuaMarkEnd
	// -------------------------------------------------------------------------
	INT LuaCallNpc(QLuaScript& sc)
	{
		INT nRet = 0;
		DWORD dwNpcTemplateId = sc.GetInt(1);
		DWORD dwSceneId = sc.GetInt(2);
		INT nX = sc.GetInt(3);
		INT nY = sc.GetInt(4);
		INT nZ = sc.GetInt(5);
		INT nFaceDir = sc.GetTopIndex() >= 6 ? sc.GetInt(6) : 0;

		KNpc* pNpc = NULL;
		IKScene* pScene = g_pSceneMgr->GetScene(dwSceneId);
		if (pScene)
		{
			pNpc = g_cOrpgWorld.AddNpc(dwNpcTemplateId);
			if (pNpc)
			{
				pNpc->m_nFaceDirection = nFaceDir;
				pNpc->m_nDirectionXY = nFaceDir;
				nRet = pScene->AddNpc(pNpc, nX, nY, nZ);

				sc.PushObj((QLunaBase*)pNpc->GetScriptInterface());
			}
		}

		if (! pNpc)
			sc.PushNull();

		return nRet;
	}

	// -------------------------------------------------------------------------
	// @ClientSvr(C/S)	: S
	// @ClassName		: --
	// @LuaApiName		: AddNpc
	// @Description		: �ٻ�Npc
	// @ReturnCode		: 
	// @ArgumentFlag	: odddd[d]
	// @ArgumentComment	: npcĿ��
	// @ArgumentComment	: dwSceneId
	// @ArgumentComment	: nX
	// @ArgumentComment	: nY
	// @ArgumentComment	: nZ
	// @ArgumentComment	: nFaceDirection ���򣨿�ѡ��
	// @LuaMarkEnd
	// -------------------------------------------------------------------------
	INT LuaAddNpc(QLuaScript& sc)
	{
		INT nRet = 0;
		KLuaNpc *pLuaNpc = dynamic_cast<KLuaNpc *>(sc.GetObj(1));
		KNpc* pNpc = NULL;
		DWORD dwSceneId = sc.GetInt(2);
		INT nX = sc.GetInt(3);
		INT nY = sc.GetInt(4);
		INT nZ = sc.GetInt(5);
		INT nFaceDir = sc.GetTopIndex() >= 6 ? sc.GetInt(6) : 0;
		IKScene* pScene = g_pSceneMgr->GetScene(dwSceneId);

		LOG_PROCESS_ERROR(pLuaNpc);
		pNpc = pLuaNpc->GetHim();
		LOG_PROCESS_ERROR(pNpc);

		if (pScene)
		{
			pNpc->m_nFaceDirection = nFaceDir;
			pNpc->m_nDirectionXY = nFaceDir;
			nRet = pScene->AddNpc(pNpc, nX, nY, nZ);
		}

		sc.PushNumber(nRet);

	EXIT0:
		return 1;
	}

	// -------------------------------------------------------------------------
	// @ClientSvr(C/S)	: S
	// @ClassName		: --
	// @LuaApiName		: SetNpcRegenerationInfo
	// @Description		: ����NPC����������
	// @ReturnCode		: 1/0
	// @ArgumentFlag	: dddddddd[ds]
	// @ArgumentComment	: dwNpcId
	// @ArgumentComment	: nX
	// @ArgumentComment	: nY
	// @ArgumentComment	: nZ
	// @ArgumentComment	: nFaceDirection
	// @ArgumentComment	: nRegenerationTime
	// @ArgumentComment	: nNormalAIType
	// @ArgumentComment	: nRelation
	// @ArgumentComment	: dwExValue
	// @ArgumentComment	: szExInfo
	// @LuaMarkEnd
	// -------------------------------------------------------------------------
	INT LuaSetNpcRegenerationInfo(QLuaScript& sc)
	{
		INT nRet = 0;
		DWORD dwNpcId = sc.GetInt(1);
		INT nX = sc.GetInt(2);
		INT nY = sc.GetInt(3);
		INT nZ = sc.GetInt(4);
		INT nFaceDirection = sc.GetInt(5);
		INT nRegenerationTime = sc.GetInt(6);
		INT nNormalAIType = sc.GetInt(7);
		INT nRelation = sc.GetInt(8);
		DWORD dwExValue = 0;
		LPCSTR pszStr = NULL;

		if(sc.IsNumber(9))
		{
			dwExValue = sc.GetInt(9);
		}
		if(sc.IsString(10))
		{
			pszStr = sc.GetStr(10);
		}

		KNpc* pNpc = g_cNpcMgr.GetById(dwNpcId);
		if (pNpc)
		{
			//ע��������Ϣ
			if (nRegenerationTime > 0)
			{
//#ifdef _DEBUG
//				printf("LuaSetNpcRegenerationInfo(dwNpcId=%08X, dwNpcTemplateId=%d, nRegenerationTime=%d)\n",dwNpcId, pNpc->GetTemplateId(), nRegenerationTime);
//#endif
				KREGENERATION_INFO regeneration_info;
				//regeneration_info.dwTemplateId = dwNpcTemplateId;
				regeneration_info.nGenerationTime = nRegenerationTime * GAME_FPS;//�����õ���ת����֡��
				regeneration_info.nX = nX;
				regeneration_info.nY = nY;
				regeneration_info.nZ = nZ;
				regeneration_info.nFaceDirection = nFaceDirection;
				regeneration_info.nNormalAIType = nNormalAIType;
				regeneration_info.nRelation = nRelation;
				regeneration_info.dwExValue = dwExValue;
				strncpy(regeneration_info.szExInfo, pszStr, MAX_NAME_LEN);
				pNpc->SetRegenerationInfo(regeneration_info);
				sc.PushNumber(1);
			}
			return 1;
		} 

		sc.PushNumber(0);
		return 0;
	}

	// -------------------------------------------------------------------------
	// @ClientSvr(C/S)	: S
	// @ClassName		: --
	// @LuaApiName		: RemoveNpc
	// @Description		: ɾ��Npc
	// @ReturnCode		: 
	// @ArgumentFlag	: d[d]
	// @ArgumentComment	: dwNpcId
	// @ArgumentComment	: bRegenerate
	// @LuaMarkEnd
	// -------------------------------------------------------------------------
	INT LuaRemoveNpc(QLuaScript& sc)
	{
		INT nRet = 0;
		DWORD dwNpcId = sc.GetInt(1);
		if (sc.IsNumber(2))
		{
			BOOL bRegenerate = sc.GetInt(2);
			g_cOrpgWorld.RemoveNpc(dwNpcId, bRegenerate);
		}
		else
		{
			g_cOrpgWorld.RemoveNpc(dwNpcId);
		}
		return 0;
	}

	// -------------------------------------------------------------------------
	// @ClientSvr(C/S)	: S
	// @ClassName		: --
	// @LuaApiName		: GetDistance
	// @Description		: �õ�����֮��ľ����ƽ��
	// @ReturnCode		: 
	// @ArgumentFlag	: dddd
	// @ArgumentComment	: X1
	// @ArgumentComment	: Y1
	// @ArgumentComment	: X2
	// @ArgumentComment	: Y2
	// @LuaMarkEnd
	// -------------------------------------------------------------------------
	INT LuaGetDistance(QLuaScript& sc)
	{
		INT nX1 = sc.GetInt(1);
		INT nY1 = sc.GetInt(2);
		INT nX2 = sc.GetInt(3);
		INT nY2 = sc.GetInt(4);
		sc.PushNumber((nX1 - nX2) * (nX1 - nX2) + (nY1 - nY2) * (nY1 - nY2));
		return 1;
	}

	// -------------------------------------------------------------------------
	// @ClientSvr(C/S)	: S
	// @ClassName		: --
	// @LuaApiName		: StartOfflineFight
	// @Description		: 
	// @ReturnCode		: 
	// @ArgumentFlag	: dddddd
	// @ArgumentComment	: dwStartPlayer
	// @ArgumentComment	: dwOfflinePlayer
	// @ArgumentComment	: dwStartRoleMapNpcId
	// @ArgumentComment	: dwStartPetMapNpcId
	// @ArgumentComment	: dwOfflineRoleMapNpcId
	// @ArgumentComment	: dwOfflinePetMapNpcId
	// @LuaMarkEnd
	// -------------------------------------------------------------------------
	INT LuaStartOfflineFight(QLuaScript& sc)
	{
		// INT ArenaHelper::StartOfflineFight(DWORD dwStartPlayer, DWORD dwOfflinePlayer, DWORD dwStartRoleMapNpcId, DWORD dwStartPetMapNpcId, DWORD dwOfflineRoleMapNpcId, DWORD dwOfflinePetMapNpcId)
		DWORD dwStartPlayer = sc.GetInt(1);
		DWORD dwOfflinePlayer = sc.GetInt(2);
		DWORD dwStartRoleMapNpcId = sc.GetInt(3);
		DWORD dwStartPetMapNpcId = sc.GetInt(4);
		DWORD dwOfflineRoleMapNpcId = sc.GetInt(5);
		DWORD dwOfflinePetMapNpcId = sc.GetInt(6);

		g_cArenaHelper.StartOfflineFight(dwStartPlayer, dwOfflinePlayer, dwStartRoleMapNpcId, dwStartPetMapNpcId, dwOfflineRoleMapNpcId, dwOfflinePetMapNpcId);

		return 0;
	}

	// -------------------------------------------------------------------------
	// @ClientSvr(C/S)	: S
	// @ClassName		: --
	// @LuaApiName		: GetPosition
	// @Description		: ���ݷ���;���õ�xyz���Ŀ���
	// @ReturnCode		: 
	// @ArgumentFlag	: ddddd
	// @ArgumentComment	: nX
	// @ArgumentComment	: nY
	// @ArgumentComment	: nZ
	// @ArgumentComment	: nDirection
	// @ArgumentComment	: nDistance
	// @LuaMarkEnd
	// -------------------------------------------------------------------------
	INT LuaGetPosition(QLuaScript& sc)
	{
		INT nDestX = 0;
		INT nDestY = 0;
		INT nDestZ = 0;

		INT nX = sc.GetInt(1);
		INT nY = sc.GetInt(2);
		INT nZ = sc.GetInt(3);
		INT nDirection = sc.GetInt(4);
		INT nDistance = sc.GetInt(5);

		int nDeltaX = nDistance * g_Cos(nDirection) / SIN_COS_NUMBER;
		int nDeltaY = nDistance * g_Sin(nDirection) / SIN_COS_NUMBER;

		nDestX = nX + nDeltaX;
		nDestY = nY + nDeltaY;
		nDestZ = nZ;

		sc.PushNumber(nDestX);
		sc.PushNumber(nDestY);
		sc.PushNumber(nDestZ);

		return 3;
	}

	// -------------------------------------------------------------------------
	// @ClientSvr(C/S)	: S
	// @ClassName		: --
	// @LuaApiName		: GetDirection
	// @Description		: �õ�������ķ���
	// @ReturnCode		: 
	// @ArgumentFlag	: dddd
	// @ArgumentComment	: nX1
	// @ArgumentComment	: nY1
	// @ArgumentComment	: nX2
	// @ArgumentComment	: nY2
	// @LuaMarkEnd
	// -------------------------------------------------------------------------
	INT LuaGetDirection(QLuaScript& sc)
	{

		INT nX1 = sc.GetInt(1);
		INT nY1 = sc.GetInt(2);
		INT nX2 = sc.GetInt(3);
		INT nY2 = sc.GetInt(4);

		INT nDirection = g_GetDirection(nX1, nY1, nX2, nY2);

		sc.PushNumber(nDirection);

		return 1;
	}


	// -------------------------------------------------------------------------
	// @ClientSvr(C/S)	: S
	// @ClassName		: --
	// @LuaApiName		: CallDoodad
	// @Description		: ����Doodad
	// @ReturnCode		: 
	// @ArgumentFlag	: dd???
	// @ArgumentComment	: dwDoodadTemplateId
	// @ArgumentComment	: ���䷢���ߣ�һ����˭���һ����
	// @ArgumentComment	: ӵ�еõ�������ʸ�����б�����ݵ��䷢���ߺ͵���ģʽɸѡ��һ���ɼ��б�
	// @ArgumentComment	: table {dwSceneId = XXX, nX = XX, nY = XX, nZ = XX}
	// @ArgumentComment	: table {nGenre = XXX, nDetail = XX, nParticular = XX, nLevel = XX, nAmount = XX}
	// @LuaMarkEnd
	// -------------------------------------------------------------------------
	INT LuaCallDoodad(QLuaScript& sc)
	{
		BOOL bResult = FALSE;
		INT nRet = 0;
		KDoodad* pDoodad = NULL;
		std::vector<DWORD> vecList;
		KPlayer* pOwner = NULL;

		DWORD dwSceneId = 0;
		INT nX = 0, nY = 0, nZ = 0;

		DWORD dwTemplateId = sc.GetInt(1);
		DWORD dwOwnerId = sc.GetInt(2);

		if (sc.IsTable(3))
		{
			INT nIdx = 0;
			sc.GetTableIndex(3, ++nIdx);
			INT nTopIndex = sc.GetTopIndex();
			while (sc.IsNumber(nTopIndex))
			{
				DWORD dwPlayerId = sc.GetInt(nTopIndex);
				vecList.push_back(dwPlayerId);
				sc.GetTableIndex(3, ++nIdx);
				nTopIndex = sc.GetTopIndex();
			}
		}

		if(sc.IsTable(4))
		{
			sc.GetTableField(4, "dwSceneId");
			dwSceneId = sc.GetInt(sc.GetTopIndex());

			sc.GetTableField(4, "nX");
			nX = sc.GetInt(sc.GetTopIndex());

			sc.GetTableField(4, "nY");
			nY = sc.GetInt(sc.GetTopIndex());

			sc.GetTableField(4, "nZ");
			nZ = sc.GetInt(sc.GetTopIndex());
		}

		PROCESS_ERROR(pDoodad = g_cDoodadMgr.CreateDoodad(dwTemplateId));

		if(sc.IsTable(5))
		{
			sc.GetTableField(5, "nGenre");
			pDoodad->m_nGenre = sc.GetInt(sc.GetTopIndex());

			sc.GetTableField(5, "nDetail");
			pDoodad->m_nDetail = sc.GetInt(sc.GetTopIndex());

			sc.GetTableField(5, "nParticular");
			pDoodad->m_nParticular = sc.GetInt(sc.GetTopIndex());

			pDoodad->m_nLevel = 0;
			sc.GetTableField(5, "nLevel");
			if(sc.IsNumber(sc.GetTopIndex()))
			{
				pDoodad->m_nLevel = sc.GetInt(sc.GetTopIndex());
			}

			pDoodad->m_nAmount = 1;
			sc.GetTableField(5, "nAmount");
			if(sc.IsNumber(sc.GetTopIndex()))
			{
				pDoodad->m_nAmount = sc.GetInt(sc.GetTopIndex());
			}
		}

		pDoodad->SetOwnerId(dwOwnerId);

		// ��Ҫ��Ҫֱ�Ӹ�������
		if(g_cDoodadMgr.CheckAutoPick(pDoodad))
		{
			goto EXIT0;
		}

		if (dwOwnerId > 0 && IS_PLAYER(dwOwnerId))
		{
			pOwner = g_cPlayerMgr.GetById(dwOwnerId);
			LOG_PROCESS_ERROR(pOwner);

			pOwner->AddDropDoodadId(pDoodad->GetId());
		}

		// ��ʼ���ɼ�����б�
		pDoodad->InitVisibleList(vecList);

		PROCESS_ERROR(g_cDoodadMgr.AddToScene(pDoodad, dwSceneId, nX, nY, nZ));

		bResult = TRUE;
EXIT0:
		if ( TRUE == bResult )
		{
			sc.PushObj((QLunaBase*)pDoodad->GetScriptInterface());
			nRet = 1;
		}
		else
		{
			if (pDoodad)
			{
				g_cDoodadMgr.RemoveFromScene(pDoodad->m_dwId);
				g_cDoodadMgr.DestroyDoodad(pDoodad->m_dwId);
				pDoodad = NULL;
			}
			sc.PushNull();
		}
		return nRet;
	}

	// -------------------------------------------------------------------------
	// @ClientSvr(C/S)	: S
	// @ClassName		: --
	// @LuaApiName		: RemoveDoodad
	// @Description		: ɾ��Doodad
	// @ReturnCode		: 
	// @ArgumentFlag	: d
	// @ArgumentComment	: dwDoodadId
	// @LuaMarkEnd
	// -------------------------------------------------------------------------
	INT LuaRemoveDoodad(QLuaScript& sc)
	{
		INT nRet = 0;
		DWORD dwDoodadId = sc.GetInt(1);
		g_cDoodadMgr.NotifyRemoveFromScene(dwDoodadId);
		g_cDoodadMgr.RemoveFromScene(dwDoodadId);
		g_cDoodadMgr.DestroyDoodad(dwDoodadId);
		//g_cOrpgWorld.RemoveFromScene(dwDoodadId);
		return 0;
	}

	// -------------------------------------------------------------------------
	// @ClientSvr(C/S)	: S
	// @ClassName		: --
	// @LuaApiName		: GetNextLevelExp
	// @Description		: 
	// @ReturnCode		: 
	// @ArgumentFlag	: d
	// @ArgumentComment	: nLevel
	// @LuaMarkEnd
	// -------------------------------------------------------------------------
	INT LuaGetNextLevelExp(QLuaScript& sc)
	{
		INT nNextLevel = sc.GetInt(1);

		DWORD dwExp = g_cCharacterHelper.GetNextLvExp(nNextLevel);

		sc.PushNumber(dwExp);

		return 1;
	}

	// -------------------------------------------------------------------------
	// @ClientSvr(C/S)	: S
	// @ClassName		: --
	// @LuaApiName		: LeaveOverallTeam
	// @Description		: 
	// @ReturnCode		: 
	// @ArgumentFlag	: o
	// @ArgumentComment	: pPlayer
	// @LuaMarkEnd
	// -------------------------------------------------------------------------
	INT LuaLeaveOverallTeam(QLuaScript& sc)
	{
		KPlayer* pPlayer = NULL;
		KInstanceCtrl* pInstanceCtrl = NULL;
		KLuaPlayer *pLuaPlayer = dynamic_cast<KLuaPlayer *>(sc.GetObj(1));

		if (pLuaPlayer)
		{
			pPlayer = pLuaPlayer->GetHim();
		}
		LOG_PROCESS_ERROR(pPlayer);

		pInstanceCtrl = pPlayer->GetCtrl<KInstanceCtrl>();
		LOG_PROCESS_ERROR(pInstanceCtrl);

		pInstanceCtrl->DoLeaveOverallTeam();

EXIT0:
		return 0;
	}

	// -------------------------------------------------------------------------
	// @ClientSvr(C/S)	: S
	// @ClassName		: --
	// @LuaApiName		: Shutdown
	// @Description		: �رշ�����
	// @ReturnCode		: 
	// @ArgumentFlag	: 
	// @ArgumentComment	: 
	// @LuaMarkEnd
	// -------------------------------------------------------------------------
	INT LuaShutdown(QLuaScript &sc)
	{
		IKGameServer* pServer = g_GetGameServerInterface();
		QCONFIRM_RET_FALSE(pServer);
		pServer->ShutDown();
		return 0;
	}

	// -------------------------------------------------------------------------
	// @ClientSvr(C/S)	: S
	// @ClassName		: --
	// @LuaApiName		: ReloadGmList
	// @Description		: ���ر�GS��GM������
	// @ReturnCode		: 
	// @ArgumentFlag	: 
	// @ArgumentComment	: 
	// @LuaMarkEnd
	// -------------------------------------------------------------------------
	INT LuaReloadGmList(QLuaScript &sc)
	{
		sc.PushNumber(g_cOrpgWorld.LoadGmList());
		return 0;
	}

	// -------------------------------------------------------------------------
	// @ClientSvr(C/S)	: S
	// @ClassName		: --
	// @LuaApiName		: IsDevMode
	// @Description		: �Ƿ��ڲ����԰�
	// @ReturnCode		: d
	// @ArgumentFlag	: 
	// @ArgumentComment	: 
	// @LuaMarkEnd
	// -------------------------------------------------------------------------
	INT LuaIsDevMode(QLuaScript &sc)
	{
		sc.PushNumber(g_cOrpgWorld.m_bDevMode);
		return 1;
	}

	// -------------------------------------------------------------------------
	// @ClientSvr(C/S)	: S
	// @ClassName		: --
	// @LuaApiName		: CenterExecute
	// @Description		: ��Coordinatorִ�нű�ָ��
	// @ReturnCode		: 
	// @ArgumentFlag	: {s}
	// @ArgumentComment	: szCall��Ҫִ�к�������������
	// @LuaMarkEnd
	// -------------------------------------------------------------------------
	INT LuaCenterExecute(QLuaScript& sc)
	{
		INT nRetCode = 0;
		static BYTE bySyncPackBuffer[60000];

		ZeroStruct(bySyncPackBuffer);

		nRetCode = sc.SaveValue2Buffer(bySyncPackBuffer, sizeof(bySyncPackBuffer), 1);
		QCONFIRM_RET_FALSE(nRetCode > 0);

		g_RelayClient.DoRemoteLuaCall(bySyncPackBuffer, nRetCode);

		sc.PushNumber(nRetCode);
		return 1;
	}

	// -------------------------------------------------------------------------
	// @ClientSvr(C/S)	: S
	// @ClassName		: --
	// @LuaApiName		: GetIsSwimByPlayerId
	// @Description		: �Ƿ�����Ӿ״̬
	// @ReturnCode		: 
	// @ArgumentFlag	: d
	// @ArgumentComment	: ���id
	// @LuaMarkEnd
	// -------------------------------------------------------------------------
	INT LuaGetIsSwimByPlayerId(QLuaScript& sc)
	{
		DWORD dwId = (DWORD)sc.GetInt(1);

		KPlayer* pPlayer = g_cPlayerMgr.GetById(dwId);

		BOOL bSwim = FALSE;
		if (pPlayer != NULL)
		{
			bSwim = pPlayer->IsSwim();
		}

		sc.PushNumber(bSwim);


		return 1;
	}

	// -------------------------------------------------------------------------
	// @ClientSvr(C/S)	: S
	// @ClassName		: --
	// @LuaApiName		: CheckRemoveBladeState
	// @Description		: ȡ������״̬
	// @ReturnCode		: 
	// @ArgumentFlag	: ?
	// @ArgumentComment	: nPlayerId/pPlayer:��ɫId���߶���
	// @LuaMarkEnd
	// -------------------------------------------------------------------------
	INT LuaCheckRemoveBladeState(QLuaScript &sc)
	{
		KPlayer* pPlayer = NULL;
		if (sc.IsNumber(1))
		{
			INT nPlayerId = sc.GetInt(1);
			QCONFIRM_RET_FALSE(IS_PLAYER(nPlayerId));
			pPlayer = (KPlayer*)g_cCharacterMgr.GetById(nPlayerId);
		}
		else
		{
			KLuaPlayer *pLuaPlayer = dynamic_cast<KLuaPlayer *>(sc.GetObj(1));
			if (pLuaPlayer)
				pPlayer = pLuaPlayer->GetHim();
		}
		QCONFIRM_RET_FALSE(pPlayer);

		KBladeCtrl* pBladeCtrl = pPlayer->GetCtrl<KBladeCtrl>();
		QCONFIRM_RET_FALSE(pBladeCtrl);

		pBladeCtrl->CheckRemoveBladeState();

		return 0;
	}

	// -------------------------------------------------------------------------
	// @ClientSvr(C/S)	: S
	// @ClassName		: --
	// @LuaApiName		: GetServerStartTime
	// @Description		: �õ�����ʱ��
	// @ReturnCode		: 
	// @ArgumentFlag	: 
	// @ArgumentComment	: 
	// @LuaMarkEnd
	// -------------------------------------------------------------------------
	INT LuaGetServerStartTime(QLuaScript& sc)
	{
		DWORD dwStartTime = g_cOrpgWorld.m_dwServerStartTime;
		sc.PushNumber(dwStartTime);

		return 1;
	}



	// -------------------------------------------------------------------------
	// @ClientSvr(C/S)	: S
	// @ClassName		: --
	// @LuaApiName		: GetDtaskDetail
	// @Description		: �õ��ճ�����ľ�������
	// @ReturnCode		: 
	// @ArgumentFlag	: 
	// @ArgumentComment	: 
	// @LuaMarkEnd
	// -------------------------------------------------------------------------
//	INT LuaGetDtaskDetail(QLuaScript& sc)
//	{
//		DWORD dwTaskDetail  = (DWORD)sc.GetInt(1);
//		struct DTASK_DETAIL szDtaskDetail = *(struct DTASK_DETAIL*)&dwTaskDetail;
//		sc.PushNumber(szDtaskDetail.byTaskLevel);
//		sc.PushNumber(szDtaskDetail.byTaskStatus);
//		sc.PushNumber(szDtaskDetail.byTaskTimes);
//		sc.PushNumber(szDtaskDetail.byTaskId);
//		return 4;
//	}

	// -------------------------------------------------------------------------
	// @ClientSvr(C/S)	: S
	// @ClassName		: --
	// @LuaApiName		: SetDtaskDetail
	// @Description		: �����ճ�����ľ�������
	// @ReturnCode		: 
	// @ArgumentFlag	: 
	// @ArgumentComment	: 
	// @LuaMarkEnd
	// -------------------------------------------------------------------------
//	INT LuaSetDtaskDetail(QLuaScript& sc)
//	{
//		BYTE byTaskLevel  = (BYTE)sc.GetInt(1);
//		BYTE byTaskStatus  = (BYTE)sc.GetInt(2);
//		BYTE byTaskTimes  = (BYTE)sc.GetInt(3);
//		BYTE byTaskId  = (BYTE)sc.GetInt(4);

		
//		struct DTASK_DETAIL szDtaskDetail;
//		szDtaskDetail.byTaskLevel = byTaskLevel;
//		szDtaskDetail.byTaskStatus = byTaskStatus;
//		szDtaskDetail.byTaskTimes = byTaskTimes;
//		szDtaskDetail.byTaskId = byTaskId;
		
//		DWORD dwTaskDetail = *(DWORD*)&szDtaskDetail;
//		sc.PushNumber(dwTaskDetail);
//		return 1;
//	}



	

#endif // GAME_SERVER

#include "kgamebasescript_table.hpp"
}

BOOL g_RegisterGameBaseScript()
{
	return g_cScriptManager.RegisterTableFuncs("KGameBase", KGameBaseNamespace::arFunction, countof(KGameBaseNamespace::arFunction));
}
