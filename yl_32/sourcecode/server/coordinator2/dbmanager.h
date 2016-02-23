
#pragma once

#include <queue>
#include "onlinegamebase/mysqldatabase.h"
#include "serverbase/kdbcallback.h"

enum KE_OPER_TYPE
{
	emKOPER_ADD_DATA,	//����һ������
	emKOPER_DEL_DATA,	//ɾ��һ������
	emKOPER_MODIFY_DATA, //�޸�����
	emKOPER_DEL_TABLE,	//ɾ��һ�����߼��������ݿ��
};

// -------------------------------------------------------------------------
class IKDBThreadCallback;
class IKMainThreadCallback;
class KDbManager : public IKGcDatabase
{
	struct KDB_CALLBACK
	{
		IKDBThreadCallback*		pCallBack;
		LPVOID					pParam;
		INT						nParam;
	};
	struct KMAIN_CALLBACK
	{
		IKMainThreadCallback*	pCallBack;
		LPVOID					pParam;
		INT						nParam;
	};
	//��Queue����֤��push���ȴ���
	typedef std::deque<KDB_CALLBACK>	QUE_DBTHREAD_CB;
	typedef std::queue<KMAIN_CALLBACK>	QUE_MAINTHREAD_CB;
public:
	KDbManager();
	static KDbManager* Inst();
	virtual BOOL PushDBAffair(IKDBThreadCallback *pAffair, INT nParam = 0, LPVOID pParam = NULL, BOOL bPriority = FALSE);
	//���ݿ���������߳̽���ص�
	virtual BOOL PushMainThreadCallBack(IKMainThreadCallback *pCallback, INT nParam = 0, LPVOID pParam = NULL);
	virtual KMySqlDatabase& GetDatabase();
	// �߳���������ݿ��߳������߳����ݷ��ʳ�ͻ
	virtual BOOL DBThreadLock();
	virtual BOOL DBThreadUnLock();

	BOOL	InitDBManager();
	BOOL	UnInit();
	//���ݿ��߳�����
	BOOL	StratUp();
	//�������ݿ�����
	BOOL	MainThreadActive();	//���߳�Active
	VOID	ReSetRuningState();
private:
	BOOL	GetRuningState();
	//Called by Thread (_DBRoute)
	VOID	DBRoute();
	//Called by Thread (_DBRoute)
	BOOL	AffairLoop();
	//��ȡ�߳�
	static VOID _DBRoute(LPVOID pvParam);
private:
	INT m_nDbAffairCounter;
	BOOL m_bRuningState;
	BOOL m_bSafeQuit;	//�Ƿ��ܰ�ȫ�˳��������Ѵ�����ϣ�
	BOOL m_bStratup;
	QLock m_cThreadLock;	//���̼߳価����Ҫ�ö�������������׻���
	BOOL m_bInited;
	QThread	m_cDbThread;
	KMySqlDatabase m_cDatabase;
	QUE_MAINTHREAD_CB m_queMainThreadCallback; // ���߳�����ص�����
	QUE_DBTHREAD_CB	m_queDBThreadCallback; // ���ݿ����߳��������
};
// -------------------------------------------------------------------------


