/* -------------------------------------------------------------------------
//	�ļ���		��	kgcinterface.h
//	������		��	luobaohang
//	����ʱ��	��	2010/6/9 15:02:12
//	��������	��	
//
// -----------------------------------------------------------------------*/
#ifndef __KGCINTERFACE_H__
#define __KGCINTERFACE_H__

#include "serverbase/kgcmoduleinterface.h"
#include "kgcinterfacedef.h"

// -------------------------------------------------------------------------
class KInterfaceAcceptor : public IKInterfaceAcceptor
{
public:
	KInterfaceAcceptor();
	KInterfaceAcceptor(BYTE byOwnerModuleId);

	virtual BOOL Send(BYTE byConnectorModuleId, LPVOID pvData, UINT uDataSize);
	virtual BOOL IsConnectValid(BYTE byConnectorModuleId);

	BYTE GetOwnerModuleId();
protected:
	BYTE m_byOwnerModuleId;			// Accept ���ڵ�ģ��
};

class KInterfaceConnector : public IKInterfaceConnector
{
public:
	KInterfaceConnector();
	KInterfaceConnector(BYTE byAcceptorModuleId, BYTE byOwnerModuleId, BOOL bEssencial);
	// �����ӷ�������
	virtual BOOL Send(LPVOID pvData, UINT uDataSize);
	// ��������Ƿ���Ч
	virtual BOOL IsConnectValid(); 

	BYTE GetAcceptorModuleId();
	BYTE GetOwnerModuleId();

	BOOL IsEssencial();
protected:
	BYTE m_byAcceptorModuleId;		// Acceptorģ��Id
	BYTE m_byOwnerModuleId;			// Connector ���ڵ�ģ��
	BOOL m_bEssencial;
};

// -------------------------------------------------------------------------

#endif /* __KINTERFACE_H__ */
