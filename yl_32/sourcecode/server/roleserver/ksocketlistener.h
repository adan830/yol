/* -------------------------------------------------------------------------
//	�ļ���		��	KSocketListener.h
//	������		��	simon
//	����ʱ��	��	2010/5/22 22:23:56
//	��������	��	
//
// -----------------------------------------------------------------------*/
#ifndef __KSOCKETLISTENER_H__
#define __KSOCKETLISTENER_H__

#include "ksocketinterface.h"

// -------------------------------------------------------------------------

struct KCONNECTION_DATA
{
	KCONNECTION_DATA()/* : SocketPacker(4096)*/
	{
		nConnectId = 0; piSocketStream = NULL;
	}

	INT nConnectId;
	ISocketStream* piSocketStream;
	//KG_Packer SocketPacker;
};

class KSocketListener : public IKSocketInterface
{
public:
	KSocketListener();
	~KSocketListener();
	BOOL Init(IKSocketEventHandler* piEventProcessor);
	// ����������
	BOOL SocketOpen();
	// �ر���������
	BOOL SocketClose();
	BOOL Disconnect(INT nConnectId);
	// �������ݡ��¼�
	BOOL Send(INT nConnectId, IMemBlock* piBuffer);
	// ��Ϣѭ�����������ݡ��¼�������
	BOOL MessageLoop();
	// ��ñ���Actived��ַ
	BOOL GetHostIP(KHOST_ADDRESS& rcAddress);

	BOOL GetLocalIpAddress(DWORD dwInAdapterIdx, DWORD dwOutAdapterIdx, CHAR szInIp[], CHAR szOutIp[]);
protected:
	BOOL CloseConnect(INT nConnectId);
protected:
	QSocketServerAcceptor	m_cSockServer;	// Server Linstener�����ڼ���GameClient
	QSOCKET_EVENT* m_pSockEvents;	// �����¼��Ļ�����ָ��
	INT m_nMaxClients;	// ���������
	QIdPool m_cIdPool;	// ����ID������
	KCONNECTION_DATA* m_pConnData;
	IKSocketEventHandler* m_piEventProcessor;
	UINT m_uLastLoopElapse;
private:
	KHOST_ADDRESS	m_cParam;
};

// -------------------------------------------------------------------------

#endif /* __KSOCKETLISTENER_H__ */
