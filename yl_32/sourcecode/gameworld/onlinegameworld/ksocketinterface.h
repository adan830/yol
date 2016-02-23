
#pragma once

class IKSocketEventProcessor
{
public:
	virtual BOOL Init(INT nMaxConnectId) = 0;
	virtual BOOL ProcessEvent(INT nConnectId, INT nEventId, LPCVOID pData, INT nData) = 0;
	virtual BOOL ProcessPacket(INT nConnectId, LPCBYTE pData, UINT uDataLen) = 0;
	virtual BOOL Activate() PURE;
};

#define KD_IPADDRESS_LEN 16
struct KHOST_ADDRESS
{
	CHAR szIntranetIp[KD_IPADDRESS_LEN]; // ����Ip
	CHAR szInternetIp[KD_IPADDRESS_LEN]; // ����Ip
	INT nListenPort;
};
struct KSOCKET_KINGEYES_INFO
{
	DWORD dwSendPackages;
	DWORD dwRecvPackages;
	UINT64 dwSendBytes;
	UINT64 dwRecvBytes;
	DWORD dwSendBytesPerSecond;
	DWORD dwRecvBytesPerSecond;

	DWORD dwTotalConnection;
	DWORD dwTotalCloseConnection;
	DWORD dwTotalLostConnection;
	DWORD dwProcessedConnection;
	DWORD dwCurrentConnection;

	DWORD dwTxBytesDelta; // �ۼƷ����ֽ��������㷢��������
	DWORD dwRxBytesDelta; // �ۼƽ����ֽ����������հ�������
};

// ����������ⲿ���ݽ�����ͳһ�ӿ�
class IKSocketInterface
{
public:
	virtual BOOL Init(IKSocketEventProcessor* piEventProcessor) = 0;
	// ����������
	virtual BOOL SocketOpen() = 0;
	// �ر���������
	virtual BOOL SocketClose() = 0;
	// �Ͽ�ĳ������
	virtual BOOL Disconnect(INT nConnectId) = 0;
	// �������ݡ��¼�
	virtual BOOL Send(INT nConnectId, INT nEventId, LPCVOID pData, INT nData) = 0;
	// ��Ϣѭ�����������ݡ��¼�������
	virtual BOOL MessageLoop() = 0;
	// ��ñ��������ĵ�ַ(����������)
	virtual BOOL GetHostIP(KHOST_ADDRESS& rcAddress) = 0;
	// ��ÿͻ��˵�ַ
	virtual BOOL GetRemoteAddress(INT nConnectId, DWORD& rdwIp, USHORT& ruPort) = 0;
	// ��ȡ����&Э�������Ϣ
	virtual BOOL GetSocketInfo(KSOCKET_KINGEYES_INFO* pcSocketInfo) = 0;
};

// SOCKET�߼��¼�����
enum KE_SOCKET_CONNECT_EVENT
{
	emKSOCKET_EVENT_BEGIN = 0,
	emKSOCKET_EVENT_CREATE,
	emKSOCKET_EVENT_LOST,
	emKSOCKET_EVENT_CLOSE, // ���������ر�
	emKSOCKET_EVENT_MASS, //  ���ݰ�̫��
};

extern IKSocketInterface* g_piSocketServer; // gameserver��ͻ������ӣ�����

class IKSocketEventProcessor_Client
{
public:
	virtual BOOL ProcessEvent(INT nEventId, LPCVOID pData, INT nData) = 0;
	virtual BOOL ProcessPacket(LPCBYTE pData, UINT uDataLen) = 0;
};

class IKSocketClientInterface
{
public:
	virtual BOOL Init(IKSocketEventProcessor_Client* piEventProcessor) = 0;
	virtual BOOL Activate() PURE;
	virtual BOOL Connect(DWORD dwIpAddress, USHORT uPort, const GUID* pGuid, BOOL bHidden) = 0;
	virtual BOOL Send(LPCVOID pData, UINT uDataLen) = 0;
	virtual BOOL ShutDown() = 0;
};
