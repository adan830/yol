/* -------------------------------------------------------------------------
//	�ļ���		��	kgc_mailmodule.h
//	������		��	xiewenzhe
//	����ʱ��	��	2011/5/17 14:39:41
//	��������	��	�ʼ�ϵͳģ��
//
// -----------------------------------------------------------------------*/
#ifndef __KGC_MAILMODULE_H__
#define __KGC_MAILMODULE_H__

// -------------------------------------------------------------------------
#include "serverbase/kgcmoduleinterface.h"
interface IKOnlinedPlayerMgr;

class KGC_MailModule : public IKGC_Module, public IKProcessServer
{
public:
	KGC_MailModule(): m_pIKGcQuery(NULL), 
					  m_pIKGcServer(NULL),
					  m_pIKOnlinePlayerMgr(NULL)
	{}
	~KGC_MailModule(){}
	
	VOID Init(IKGcQuery* piGcQuery) { m_pIKGcQuery = piGcQuery; }
	static KGC_MailModule* Instance() {return &ms_inst;}

public:
	//IKGC_Module
	// ��ȡģ������
	LPCSTR GetModuleName();
	// ÿѭ������
	BOOL Loop();
	// ÿ֡����
	BOOL Breath();
	//  ��ʼ������
	BOOL OnInit();
	// ��ʼ����Ͻ�������״̬ʱ����
	BOOL OnStartUp();
	//����ʼ������ǰ����, �ر�
	BOOL OnShutDown();
	// ����ʼ������
	BOOL OnUninit();

	//IKProcessServer
	BOOL OnConnectClose(INT nConnectId) { return TRUE; }
	BOOL OnConnected(INT nConnectId) { return TRUE; }
	BOOL ProcessData(INT nConnectId, LPBYTE pData, UINT uSize);

	IKGcQuery* GetIKGcQuery() { return m_pIKGcQuery; }
	IKGcServer* GetIKGcServer() { return m_pIKGcServer; }
	IKOnlinedPlayerMgr* GetOnlinePlayerMgr() { return m_pIKOnlinePlayerMgr; }

private:
	static KGC_MailModule ms_inst;

private:
	IKGcQuery*  m_pIKGcQuery;
	IKGcServer* m_pIKGcServer;
	IKOnlinedPlayerMgr*  m_pIKOnlinePlayerMgr;
};

// -------------------------------------------------------------------------

#endif /* __KGC_MAILMODULE_H__ */
