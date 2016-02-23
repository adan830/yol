
#include "stdafx.h"
#include "mysql.h"
#include "Misc/utilities.h"
#include "serverbase/kdbcallback.h"
#include "dbmanager.h"
#include "GameCenter.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static CHAR THIS_FILE[] = __FILE__;
#endif

#define  KD_MAX_QUERY_FIELD	10
// -------------------------------------------------------------------------
KDbManager::KDbManager()
{
	m_bRuningState = m_bInited = m_bStratup = FALSE; 
	m_bSafeQuit = TRUE;
	m_nDbAffairCounter = 0;
}

BOOL KDbManager::InitDBManager()
{
	QCONFIRM_RET_FALSE(!m_bInited);
	m_bInited = TRUE;
	m_bRuningState = TRUE;
	m_bSafeQuit = TRUE;

	QLogPrintf(LOG_INFO, "[DataBase]Connecting to DataBase Server(Ip=%s, Port=%d,UserName=%s)...",
		g_pGameCenter->m_Settings.m_szDBIP,
		g_pGameCenter->m_Settings.m_nDBPort,
		g_pGameCenter->m_Settings.m_szDBAcc);

	// ----------------- connect to database  ----------------- 
	INT nRetCode = m_cDatabase.DBConnect(
		g_pGameCenter->m_Settings.m_szDBIP,
		g_pGameCenter->m_Settings.m_nDBPort,
		g_pGameCenter->m_Settings.m_szDBAcc,
		g_pGameCenter->m_Settings.m_szDBPsw,
		NULL);
	QCONFIRM_RET_FALSE(nRetCode);
	LPCSTR szCurDatabase = g_pGameCenter->m_Settings.m_szDBName;

	QLogPrintf(LOG_INFO, "[DataBase]Creating(if not exists) DataBase(Name=%s)...", szCurDatabase);

	nRetCode = m_cDatabase.CreateDatabase(g_pGameCenter->m_Settings.m_szDBName, emKDBCREATE_IF_NOT_EXIST);
	QCONFIRM_RET_FALSE(nRetCode);
	QCONFIRM_RET_FALSE(szCurDatabase);
	nRetCode = m_cDatabase.SetCurrentDatabase(szCurDatabase);
	QCONFIRM_RET_FALSE(nRetCode);
#if defined _DEBUG && defined WIN32
	//Q_Printl("WAINING______________________ Now Drop DBShare Table");
	////���ڵ���ʱ�����ݣ�����ʱע����
	//sqlStream.AddRemoveTable(KD_DBTBL_SHARE);
	//m_cDatabase.DoQuery(sqlStream);
	//sqlStream.Reset();
#endif

	QLogPrintf(LOG_INFO, "[DataBase]DbManager init OK!");

	return TRUE;
}

BOOL KDbManager::UnInit()
{
	if (!m_bInited)
		return TRUE;
	ReSetRuningState();

	// Ҫ�ȴ��߳��˳�
	while (!m_bSafeQuit)
	{
		if (!MainThreadActive())
			QThread_Sleep(5);
	}
	m_cThreadLock.Lock();
	// ���callback����
	while (!m_queMainThreadCallback.empty())
	{
		KMAIN_CALLBACK sCallBack = m_queMainThreadCallback.front();
		m_queMainThreadCallback.pop();
		m_cThreadLock.Unlock();
		IKMainThreadCallback *piCallback = sCallBack.pCallBack;
		piCallback->MainThreadCallback(sCallBack.nParam, sCallBack.pParam);
		piCallback->Release();
		m_cThreadLock.Lock();
	}
	m_cThreadLock.Unlock();
	m_bInited = FALSE;
	//	m_Database.ShutDown(); UnInit�����п��ܴ���
	Q_Printl("Save Thread Exit...!");
	return TRUE;
}

BOOL KDbManager::StratUp()
{
	m_bStratup = TRUE;
	m_bSafeQuit = FALSE;
	m_cDbThread.Create(_DBRoute, this);
	return TRUE;
}

BOOL KDbManager::PushDBAffair( IKDBThreadCallback *pAffair, INT nParam /*= 0*/, LPVOID pParam /*= NULL*/, BOOL bPriority /*= FALSE*/ )
{
	++m_nDbAffairCounter;
	if (m_bSafeQuit || !m_bStratup)	// ������ݿ��߳����˳�
	{
		pAffair->DBThreadCallback(nParam, pParam);
		pAffair->Release();
		return TRUE;
	}
	KDB_CALLBACK sCallBack;
	sCallBack.pCallBack = pAffair;
	sCallBack.nParam = nParam;
	sCallBack.pParam = pParam;
	m_cThreadLock.Lock();
	if (bPriority)
		m_queDBThreadCallback.push_front(sCallBack);
	else
		m_queDBThreadCallback.push_back(sCallBack);
	m_cThreadLock.Unlock();
	return TRUE;
}

BOOL KDbManager::PushMainThreadCallBack( IKMainThreadCallback *pCallback, INT nParam /*= 0*/, LPVOID pParam /*= NULL*/ )
{
	// ��UnInit�ѵ��ã�ֱ�ӵ�
	if (!m_bInited)
	{
		pCallback->MainThreadCallback(nParam, pParam);
		pCallback->Release();
		return TRUE;
	}
	m_cThreadLock.Lock();
	KMAIN_CALLBACK sCallBack;
	sCallBack.pCallBack = pCallback;
	sCallBack.nParam = nParam;
	sCallBack.pParam = pParam;
	m_queMainThreadCallback.push(sCallBack);
	m_cThreadLock.Unlock();
	return TRUE;
}

BOOL KDbManager::MainThreadActive()
{
	m_cThreadLock.Lock();
	//ע��returnǰҪUnlock
	if (!m_queMainThreadCallback.empty())
	{
		KMAIN_CALLBACK sCallBack = m_queMainThreadCallback.front();
		m_queMainThreadCallback.pop();
		m_cThreadLock.Unlock();
		IKMainThreadCallback *piCallback = sCallBack.pCallBack;
		piCallback->MainThreadCallback(sCallBack.nParam, sCallBack.pParam);
		piCallback->Release();
		return TRUE;
	}
	m_cThreadLock.Unlock();
	return FALSE;
}

VOID KDbManager::DBRoute()
{
	while (GetRuningState())
	{
		if (!AffairLoop())
			QThread_Sleep(1);
	}
	//�߳̽�����������ɴ�ȡ����
	while (AffairLoop())
	{
		continue;
	}
	//��ȫ�˳�
	do 
	{
		m_bSafeQuit = TRUE;
	} while(!m_bSafeQuit);
}

VOID KDbManager::_DBRoute( LPVOID pvParam )
{
	reinterpret_cast<KDbManager *>(pvParam)->DBRoute();
}

BOOL KDbManager::AffairLoop()
{
	m_cThreadLock.Lock();
	//ע��returnǰҪUnlock
	if (!m_queDBThreadCallback.empty())
	{
		//ÿ128������Ľ�����������Ϣ
		if ((m_queDBThreadCallback.size() & 127) == 0)
			Q_Printl("DB Affair Count: " << m_queDBThreadCallback.size());
		KDB_CALLBACK sCallBack = m_queDBThreadCallback.front();
		IKDBThreadCallback *pCallback = sCallBack.pCallBack;
		m_queDBThreadCallback.pop_front();
		m_cThreadLock.Unlock();	//��Unlock��ִ��Callback�ǿ϶���
		pCallback->DBThreadCallback(sCallBack.nParam, sCallBack.pParam);
		pCallback->Release();
		return TRUE;
	}
	m_cThreadLock.Unlock();
	return FALSE;
}

BOOL KDbManager::DBThreadLock()
{
	return m_cThreadLock.Lock();
}

BOOL KDbManager::DBThreadUnLock()
{
	return m_cThreadLock.Unlock();
}

KMySqlDatabase& KDbManager::GetDatabase()
{
	return m_cDatabase;
}

BOOL KDbManager::GetRuningState()
{
	return m_bRuningState;
}

VOID KDbManager::ReSetRuningState()
{
	while (m_bRuningState)
		m_bRuningState = FALSE;
}

KDbManager* KDbManager::Inst()
{
	static KDbManager s_Manager;
	return &s_Manager;
}
