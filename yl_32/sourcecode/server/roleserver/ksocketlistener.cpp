/* -------------------------------------------------------------------------
//	�ļ���		��	KSocketListener.cpp
//	������		��	luobaohang, simon
//	����ʱ��	��	2010/5/22 22:22:42
//	��������	��	
//
// -----------------------------------------------------------------------*/

#include "stdafx.h"
#include "Core/IpMacAddress.h"
#include "Misc/qidpool.h"
#include "ksocketlistener.h"
#include "roleserver_cfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// -------------------------------------------------------------------------

#define RS_CLIENT_PING_TIMEOUT  100 // client Ĭ��ping��ʱ����
const static INT g_snMaxPacketSize = 640 * 1024;
const static INT g_snMaxEventAccept = 1024;
const static INT g_snDefaultMaxClients = 10; // Ĭ�����10���ͻ���
const static INT g_snDefaultPort = 5004; // Ĭ�϶˿�

KSocketListener _gcSocketServer;
IKSocketInterface* g_piSocketServer = &_gcSocketServer;

// -------------------------------------------------------------------------

KSocketListener::KSocketListener()
{
	m_piEventProcessor = NULL;
	m_pSockEvents = NULL;
	m_pConnData = NULL;
	m_nMaxClients = g_snDefaultMaxClients;
	m_uLastLoopElapse = 0;
}

KSocketListener::~KSocketListener()
{
	SocketClose();
}

BOOL KSocketListener::SocketOpen()
{
	QLogPrintf(LOG_INFO,
		"Prepare To Listen On [%s:%d]...", 
		m_cParam.szInternetIp,
		m_cParam.nListenPort
		);
	BOOL bRet = m_cSockServer.Init(m_cParam.szInternetIp,
		m_cParam.nListenPort,
		g_snMaxEventAccept,
		g_snMaxPacketSize,
		g_snMaxPacketSize,
		ENCODE_DECODE_NONE,
		NULL);
	QCONFIRM_RET_FALSE(bRet);
	QLogPrintf(LOG_INFO, "%s", "SocketListener started");
	return TRUE;
}

BOOL KSocketListener::GetLocalIpAddress(DWORD dwInAdapterIdx, DWORD dwOutAdapterIdx, CHAR szInIp[], CHAR szOutIp[])
{
	CONST INT cnAdapterMaxCount		= 10;

	DWORD adwIPAddressIn[cnAdapterMaxCount];
	DWORD adwIPAddressOut[cnAdapterMaxCount];

	DWORD dwInIPCount				= 0;
	DWORD dwOutIPCount			= 0;

	gGetIPAddressList(NULL, adwIPAddressIn, dwInIPCount, 
		NULL, adwIPAddressOut, dwOutIPCount, cnAdapterMaxCount);

	QCONFIRM_RET_FALSE(dwInIPCount > 0 && dwOutIPCount > 0);

	// IntranetIp
	if (dwInAdapterIdx <= 0 || dwInAdapterIdx > dwInIPCount)
		dwInAdapterIdx = 1;

	LPBYTE pByte = (LPBYTE)&adwIPAddressIn[dwInAdapterIdx - 1];
	snprintf(szInIp, MAX_PATH, "%u.%u.%u.%u", pByte[0], pByte[1], pByte[2], pByte[3]);

	// InternetIp
	if (dwOutAdapterIdx <= 0 || dwOutAdapterIdx > dwOutIPCount)
		dwOutAdapterIdx = 1;

	pByte = (LPBYTE)&adwIPAddressOut[dwOutAdapterIdx - 1];
	snprintf(szOutIp, MAX_PATH, "%u.%u.%u.%u", pByte[0], pByte[1], pByte[2], pByte[3]);

	return TRUE;
}

BOOL KSocketListener::Init( IKSocketEventHandler* piEventProcessor )
{
	QIniFile cIniFile;
	BOOL bRet = cIniFile.Load(ROLESVC_CFG_FILE_NAME);
	QCONFIRM_RET_FALSE(bRet);

	CHAR szInternetIp[KD_IPADDRESS_LEN] = {0}; // ����Ip

	cIniFile.GetString(ROLESVC_CFG_SECTION_NETWORK, "OutIp", "",	m_cParam.szInternetIp, sizeof(m_cParam.szInternetIp));
	cIniFile.GetInteger(ROLESVC_CFG_SECTION_NETWORK, "Port", 5103, &m_cParam.nListenPort);
	cIniFile.GetInteger(ROLESVC_CFG_SECTION_LIMIT, "MaxClients", g_snDefaultMaxClients, &m_nMaxClients);
	cIniFile.GetInteger(ROLESVC_CFG_SECTION_NETWORK, "PingTimeOut", RS_CLIENT_PING_TIMEOUT,
		&g_sRoleSvcCfg.sNetwork.nPingTimeOut);

	m_pSockEvents = new QSOCKET_EVENT[g_snMaxEventAccept];
	memset(m_pSockEvents, 0, sizeof(QSOCKET_EVENT) * g_snMaxEventAccept);
	m_cIdPool.Init(m_nMaxClients);

	m_pConnData = new KCONNECTION_DATA[m_nMaxClients + 1]; // ������1��ʼ���Լ�1��0����
	m_piEventProcessor = piEventProcessor;
	m_piEventProcessor->Init(m_nMaxClients);

	return TRUE;
}

BOOL KSocketListener::Send( INT nConnectId, IMemBlock* piBuffer )
{
	QCONFIRM_RET_FALSE((UINT)nConnectId <= (UINT)m_nMaxClients);
	QCONFIRM_RET_FALSE(piBuffer);
	QCONFIRM_RET_FALSE(m_pConnData[nConnectId].piSocketStream);

	in_addr sIp;
	USHORT uPort = 0;
	m_pConnData[nConnectId].piSocketStream->GetRemoteAddress(&sIp, &uPort);
	uPort = ntohs(uPort);

	// if (bDebugSelf)
	printf("  Sending data to Client[%d][%s:%u]\n", nConnectId, inet_ntoa(sIp), uPort);

	INT nRet = m_pConnData[nConnectId].piSocketStream->Send(piBuffer);
	if (nRet <= 0)
	{
		QLogPrintf(LOG_WARNING, "Disconnect [%d] for send error, RetCode: %d", nConnectId, nRet);
		// ����
		CloseConnect(nConnectId);
	}
	return nRet > 0;
}

BOOL KSocketListener::MessageLoop()
{
	INT nEventCount = 0;
	// ���������¼�
	if (!m_cSockServer.Wait(g_snMaxEventAccept, m_pSockEvents, &nEventCount))
		return FALSE;
	QSOCKET_EVENT* pEvent = NULL;
	ISocketStream* pStream = NULL;
	for (INT i = 0; i < nEventCount; i++)
	{
		pEvent = &m_pSockEvents[i];
		pStream = pEvent->piSocket;
		pStream->AddRef();
		SAFE_RELEASE(pEvent->piSocket);

		// �����ǿͻ�������
		if ((QSOCKET_EVENT_ACCEPT & pEvent->uEventFlag) != 0)
		{
			// ��ȡ�������Ӻ�
			in_addr sIp;
			USHORT uPort = 0;
			INT nConnectId = m_cIdPool.New();
			memset(&sIp, 0, sizeof(sIp));
			pStream->GetRemoteAddress(&sIp, &uPort);
			uPort = ntohs(uPort); // ������GetRemoteAddressӦ������

			// �ﵽ������������ܾ�����
			if (0 == nConnectId)
			{
				QLogPrintf(LOG_ERR, "No ConnIndex to allocate for [%s:%d]", inet_ntoa(sIp), uPort);
				SAFE_RELEASE(pStream);
				continue;
			}

			if (m_pConnData[nConnectId].nConnectId != 0 ||
				m_pConnData[nConnectId].piSocketStream != NULL)
				Q_Error("Pre Connect Release Error ?");

			m_pConnData[nConnectId].nConnectId = nConnectId;
			m_pConnData[nConnectId].piSocketStream = pStream;
			m_pConnData[nConnectId].piSocketStream->AddRef();
			//m_pConnData[nConnectId].SocketPacker.Reset();
			pStream->SetUserData(&m_pConnData[nConnectId].nConnectId);			
			SAFE_RELEASE(pStream);
			// ���ӽ����¼�
			m_piEventProcessor->ProcessEvent(nConnectId, emKSOCKET_EVENT_CREATE,
				inet_ntoa(sIp), uPort);
			continue;
		}

		// ��������յ�������¼�
		if ((QSOCKET_EVENT_IN & pEvent->uEventFlag) == 0)
		{
			SAFE_RELEASE(pStream);
			continue;
		}

		// ע�⣺���������Ӻ���ʱ��pStreamû��SetUerData�����Ի��յ�SOCKET_EVENT_IN�¼���
		VOID* pUserData = pStream->GetUserData();	// pUserDataָ����������
		INT nConnectId = 0;
		if (NULL == pUserData)
		{
			SAFE_RELEASE(pStream);
			continue;
		}

		INT nProcessCount	= 0;

		nConnectId = *(INT*)pUserData;
		// ѭ���в��ϵ�ȥ���Խ�������
		// !!!�п���piSocketStream�ڴ���Ϣѭ���б�����Release������ʹ��m_pConnData[nConnectId].piSocketStream != NULL��Ϊѭ������
		while (m_pConnData[nConnectId].piSocketStream != NULL)
		{
			nProcessCount++;
			if (nProcessCount > 10000)	// ��Ϣ����
			{
				m_piEventProcessor->ProcessEvent(nConnectId, emKSOCKET_EVENT_MASS, NULL, nProcessCount);
				//CloseConnect(nConnectId);
				break;
			}

			IMemBlock *pBuffer = NULL;
			INT nRetCode = pStream->Recv(&pBuffer);
			if (nRetCode <= 0)
			{
				// ����հ������ر�����
				if (nRetCode == -1)
				{
					CloseConnect(nConnectId);
				}
				break;
			}

			LPVOID pData = pBuffer->GetData();
			UINT nLen = pBuffer->GetSize();

			BOOL bProcessed = m_piEventProcessor->ProcessPacket(nConnectId, pBuffer);
			if (!bProcessed)
			{
				QLogPrintf(LOG_ERR, "Unknown protocol [%u] from Conn[%d]", (ULONG)LPCBYTE(pData)[0], nConnectId);
				//CloseConnect(nConnectId);
			}

			SAFE_RELEASE(pBuffer);
		}

		SAFE_RELEASE(pStream);
	}

	m_piEventProcessor->Activate();
	return nEventCount;
}

BOOL KSocketListener::GetHostIP(KHOST_ADDRESS& rcAddress)
{
	rcAddress = m_cParam;
	return TRUE;
}

BOOL KSocketListener::CloseConnect( INT nConnectId )
{
	QCONFIRM_RET_FALSE(nConnectId > 0 && nConnectId <= m_nMaxClients);
	QCONFIRM_RET_FALSE(m_pConnData[nConnectId].piSocketStream);
	QLogPrintf(LOG_INFO, "[KSocketListener] disconnecting [%d]...", nConnectId);
	// �������Ӻ�
	m_cIdPool.Delete(nConnectId);
	// �ͷ���Դ
	m_pConnData[nConnectId].piSocketStream->SetUserData(NULL);
	SAFE_RELEASE(m_pConnData[nConnectId].piSocketStream);
	//m_pConnData[nConnectId].SocketPacker.Reset(); // ������������
	m_pConnData[nConnectId].nConnectId = 0;
	// �׳����ӹر��¼�
	m_piEventProcessor->ProcessEvent(nConnectId, emKSOCKET_EVENT_CLOSE, NULL, 0);
	return TRUE;
}

BOOL KSocketListener::Disconnect( INT nConnectId )
{
	QCONFIRM_RET_FALSE(nConnectId != -1);
	return CloseConnect(nConnectId);
}

BOOL KSocketListener::SocketClose()
{
	for (int i = 1; i <= m_nMaxClients && m_pConnData; ++i)
	{
		if (m_pConnData[i].piSocketStream)
			CloseConnect(i);
	}
	m_cSockServer.UnInit(NULL);
	m_cIdPool.Uninit();
	SAFE_DELETE_ARRAY(m_pSockEvents);
	SAFE_DELETE_ARRAY(m_pConnData);

	m_nMaxClients = 0;
	m_piEventProcessor = NULL;
	m_uLastLoopElapse = 0;
	return TRUE;
}
// -------------------------------------------------------------------------
