/* -------------------------------------------------------------------------
//	�ļ���		��	kchatprotocolprocess_gc.h
//	������		��	liuchang
//	����ʱ��	��	2010-6-24 11:14:49
//	��������	��	
//
// -----------------------------------------------------------------------*/
#ifndef __KCHATPROTOCOLPROCESS_GC_H__
#define __KCHATPROTOCOLPROCESS_GC_H__

// -------------------------------------------------------------------------

#include "serverbase/kgcmoduleinterface.h"
#include "kchatmodule_gc.h"

// -------------------------------------------------------------------------
// ����GSЭ��Ľ�����
class KChatClientMsgProcessor : public IKProcessServer
{
public:
	virtual BOOL OnConnectClose(INT nConnectId);
	virtual BOOL OnConnected(INT nConnectId);
	virtual BOOL ProcessData(INT nConnectId, LPBYTE pData, UINT uSize);

private:
	BOOL ProcessReceiveMsg(INT nConnectId, LPBYTE pData, UINT uSize);
	BOOL ProcessSendMsgToPlayer(INT nConnectId, LPBYTE pData, UINT uSize);
};
extern KChatClientMsgProcessor g_ChatProcessAcceptor;


// -------------------------------------------------------------------------
// ����GC��Teamģ����Ϣ
class KChatMsgDispatcher_ForTeam : public IKProcessConnector
{
public:
	virtual BOOL OnConnected();
	virtual BOOL OnConnectClose();
	virtual BOOL ProcessData(LPBYTE pData, UINT uSize);
};

// -------------------------------------------------------------------------
// ����GC��Kinģ����Ϣ
class KChatMsgDispatcher_ForKin : public IKProcessConnector
{
public:
	virtual BOOL OnConnected();
	virtual BOOL OnConnectClose();
	virtual BOOL ProcessData(LPBYTE pData, UINT uSize);
};


// -------------------------------------------------------------------------
// ����GC��Groupģ����Ϣ
class KChatMsgDispatcher_ForGroup : public IKProcessConnector
{
public:
	virtual BOOL OnConnected();
	virtual BOOL OnConnectClose();
	virtual BOOL ProcessData(LPBYTE pData, UINT uSize);
};


// -------------------------------------------------------------------------
// Chatģ�������GCģ������ӹ���
class KChatModuleConnectorFactory : public IKModuleConnectorFactory
{
public:
	virtual IKProcessConnector* GetModuleChatProcess(KE_GC_MODULE_ID emModuleId);
};
extern KChatModuleConnectorFactory g_cChatModuleConnectorFactory;

// -------------------------------------------------------------------------

#endif /* __KCHATPROTOCOLPROCESS_GC_H__ */
