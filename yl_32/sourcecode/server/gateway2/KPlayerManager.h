#ifndef _KPLAYERMANAGER_H_ 
#define _KPLAYERMANAGER_H_ 

#include <map>
#include "ProtocolBasic.h"
#include "protocol/GatewayClientProtocol.h"

enum KAccountState
{
	easInvalid, 
	easWaitForHandshake,                // �ȴ��ͻ��˴����汾�ŵ�
	easWaitForVerifyInfo,               // �ȴ��ͻ��˴����û���,����,����ʢ��Token����Ϣ
	easQueryAccountState,               // ������Relay��ѯ�ʺ�״̬
	easWaitForSDOAVerify,               // �ȴ�SDOA��֤
	easWaitForPaysysVerify,             // �ȴ�Paysys��֤
	easWaitForMibaoPassword,            // �ȴ��ͻ��˴����ܱ�����
	easWaitForMibaoVerify,              // �ȴ�Paysys�ܱ���֤
	easWaitForRoleList,                 // �ȴ���ɫ�б�
	easWaitForPlayerOperation,          // �ȴ���ҷ���������ɫ/ɾ����ɫ/��½��ɫ������
	easWaitForNewbieMapRespond,         // �ȴ����ִ���Ӧ
	easWaitForCreateRoleRespond,        // �ȴ�������ɫ����Ӧ
	easWaitForDeleteRoleRespond,        // �ȴ�ɾ����ɫ����Ӧ
	easWaitForLoginPermission,          // �ȴ���½��Կ
	easQueueWaiting,                    // ��½�Ŷ�״̬
	easWaitForRenameRespond,            // �ȴ�����ȷ��
	easWaitForDisconnect,               // �ȴ��ͻ�����������
	easTotal
};

enum KE_ACCOUNT_VERIFIER
{
	emACCOUNT_VERIFIER_NONE,
	emACCOUNT_VERIFIER_PAYSYS = 1,
	emACCOUNT_VERIFIER_LDAP = 2,
	emACCOUNT_VERIFIER_WHITE_LIST = 4,
};

typedef std::map<DWORD, IMemBlock*> KROLE_LIST;

struct KPlayerAgency
{
	char                          szAccount[_NAME_LEN];
	char                          szPsw[LOGIN_USER_PASSWORD_MAX_LEN];
	char                          szAct[LOGIN_USER_PASSWORD_MAX_LEN];
	char                          szSndaToken[SNDA_TOKEN_LEN];
	char                          szIDCard[ID_CARD_LEN];

	BYTE                          byMibaoMode;
	char                          szMatrixPosition[9];

	KAccountState                 nState;
	int                           nIndex;
	DWORD                         dwQueueID;
	ISocketStream*                piSocket;
	time_t                        nLastPingTime;
	BOOL                          bAccountInGame;
	int                           nChargeFlag;
	tagExtPointInfo               ExtPointInfo;
	DWORD                         dwEndOfDayTime;             // �¿���ֹʱ��
	DWORD 	                      dwLeftTimeOfPoint;		  // �Ƶ�ʣ�����
	DWORD                         dwLeftTimeOfDay;            // �쿨ʣ������
	DWORD                         dwEndTimeOfFee;             // ����շ��ܽ�ֹʱ��
	DWORD                         dwCoin;                     // �����
	DWORD                         dwLimitPlayTimeFlag;        // �����Ա�־λ
	DWORD                         dwLimitOnlineSecond;        // �������ۼ�����ʱ��
	DWORD                         dwLimitOfflineSecond;       // �������ۼ�����ʱ��

	DWORD                         dwLoginTime;                // ���ε�¼ʱ��
	DWORD                         dwLastLoginTime;
	DWORD                         dwLastLoginIP;

	KROLE_LIST                    RoleList;

	DWORD                         dwVerifyPostTime;           // ��PaysysͶ����֤�����ʱ��,���ڲ�����֤Ч��
	INT nZoneId;
	INT nServerId;
};

class KPaysysAgency;
class KRelayAgency;
class KQueueManager;
class QGateway;
class KSndaAgency;

class KPlayerManager
{
public:
	KPlayerManager();

	BOOL Init(KE_ACCOUNT_VERIFIER eAccountVerifier);
	void UnInit();

	void Activate();

	void AttachModule(KPaysysAgency* pModule) { m_pPaysysAgency = pModule; }
	void AttachModule(KRelayAgency* pModule) { m_pRelayAgency = pModule; }
	void AttachModule(KQueueManager* pModule) { m_pQueueManager = pModule; }
	void AttachModule(QGateway* pModule) { m_pGateway = pModule; }
	void AttachModule(KSndaAgency* pModule) { m_pSndaAgency = pModule; }

	KPlayerAgency* GetPlayer(int nIndex)
	{
		KPlayerTable::iterator it = m_PlayerTable.find(nIndex);
		if (it != m_PlayerTable.end())
		{
			return &it->second;
		}
		return NULL;
	}

	int  GetConnectionCount() { return (int)m_PlayerTable.size(); }
	int  TotalConnectionCount() { return m_nTotalConnections; }

	void UnlockAccount(KPlayerAgency* pPlayer);
	void KickoutAccount(const char* pszAccountName);

	BOOL SmartAccountVerify(KPlayerAgency* pPlayer);
	void SetAccountVerifier(KE_ACCOUNT_VERIFIER val) { m_eAccountVerifier = val; }
	KE_ACCOUNT_VERIFIER AccountVerifier() const { return m_eAccountVerifier; }
private:
	BOOL ProcessNewConnection(ISocketStream* piSocket);
	BOOL ProcessPackage(ISocketStream* piSocket);

	void CheckConnectionTimeout();
	void RecycleConnections();

	void Disconnect(KPlayerAgency* pPlayer);

	BOOL _LoadWhiteList();
public:
	BOOL DoPingRespond(KPlayerAgency* pPlayer, DWORD dwTime);
	BOOL DoHandshakeRespond(KPlayerAgency* pPlayer, int nCode);
	BOOL DoAccountLockedNotify(KPlayerAgency* pPlayer);
	BOOL DoAccountVerifyRespond(KPlayerAgency* pPlayer, int nRespondCode);
	BOOL DoMibaoVerifyRespond(KPlayerAgency* pPlayer, int nRespondCode);
	BOOL DoKickAccountNotify(KPlayerAgency* pPlayer);
	BOOL DoSyncRandomPlayerName(KPlayerAgency* pPlayer, CHAR* szPlayerName, INT nSex);
	BOOL DoSyncRoleList(KPlayerAgency* pPlayer, int nRoleIndex, int nRoleCount, BYTE* pbyRoleData, size_t uRoleDataLen);
	BOOL DoSyncNewbieMaps(KPlayerAgency* pPlayer, DWORD dwMapID, KNEWBIE_MAP_COPY_INFO CopyInfo[], int nCopyCount);
	BOOL DoCreateRoleRespond(KPlayerAgency* pPlayer, BYTE byCode, DWORD dwRoleID, BYTE* pbyData, size_t uDataLen);
	BOOL DoDeleteRoleRespond(KPlayerAgency* pPlayer, BYTE byCode, DWORD dwRoleID, time_t nDeleteTime);
	BOOL DoGameLoginRespond(KPlayerAgency* pPlayer, BYTE byCode, DWORD dwRoleID, DWORD dwIP, int nPort, const GUID& crGuid);
	BOOL DoSyncQueueState(KPlayerAgency* pPlayer, int nPosition);
	BOOL DoGiveupQueueRespond(KPlayerAgency* pPlayer);
	BOOL DoRenameRespond(KPlayerAgency* pPlayer, BYTE byCode, DWORD dwRoleID, BYTE* pbyData, size_t uDataLen);
	BOOL DoSndaVerifyRespond(KPlayerAgency* pPlayer, int nRespondCode);

private:
	void OnPingSignal(KPlayerAgency* pPlayer, BYTE* pbyData, size_t uDataLen);
	void OnHandshakeRequest(KPlayerAgency* pPlayer, BYTE* pbyData, size_t uDataLen);
	void OnAccountVerifyRequest(KPlayerAgency* pPlayer, BYTE* pbyData, size_t uDataLen);
	void OnSndaTokenVerifyRequest(KPlayerAgency* pPlayer, BYTE* pbyData, size_t uDataLen);
	void OnMibaoVerifyRequest(KPlayerAgency* pPlayer, BYTE* pbyData, size_t uDataLen);
	void OnQueryNewbieMaps(KPlayerAgency* pPlayer, BYTE* pbyData, size_t uDataLen);
	void OnCreateRoleRequest(KPlayerAgency* pPlayer, BYTE* pbyData, size_t uDataLen);
	void OnRandomPlayernameRequest(KPlayerAgency* pPlayer, BYTE* pbyData, size_t uDataLen);
	void OnDeleteRoleRequest(KPlayerAgency* pPlayer, BYTE* pbyData, size_t uDataLen);
	void OnGameLoginRequest(KPlayerAgency* pPlayer, BYTE* pbyData, size_t uDataLen);
	void OnGiveupQueueRequest(KPlayerAgency* pPlayer, BYTE* pbyData, size_t uDataLen);
	void OnRenameRequest(KPlayerAgency* pPlayer, BYTE* pbyData, size_t uDataLen);

private:
	typedef void (KPlayerManager::*PC2G_PROTOCOL_FUNC)(KPlayerAgency* pPlayer, BYTE* pbyData, size_t uDataLen);

	PC2G_PROTOCOL_FUNC m_PakProcessor[c2g_protocol_total];
	size_t             m_uPakSize[c2g_protocol_total];

private:
	typedef std::map<int, KPlayerAgency> KPlayerTable;
	KPlayerTable                m_PlayerTable;

	//struct KAccountCompareLess
	//{
	//	bool operator()(const string& crX, const string& crY) const
	//	{
	//		return STR_CASE_CMP(crX.c_str(), crY.c_str()) < 0;
	//	}
	//};

	typedef std::map<std::string, int/*, KAccountCompareLess*/> KLockedAccountTable;
	KLockedAccountTable         m_LockedAccountTable;

	int                         m_nPingCycle;

	KPaysysAgency*              m_pPaysysAgency;
	KRelayAgency*               m_pRelayAgency;
	KQueueManager*              m_pQueueManager;
	QGateway*                	m_pGateway;
	KSndaAgency*                m_pSndaAgency;

private:
	QSocketServerAcceptor*    	m_pSockerServer;
	QSOCKET_EVENT*           	m_pSocketEvents;
	int                         m_nNextPlayerIndex;
	int                         m_nMaxPlayer;
	BOOL                        m_bRecycleConnections;
	time_t                      m_nTimeNow;
	time_t                      m_nNextPingCheck;
	KE_ACCOUNT_VERIFIER m_eAccountVerifier;
	std::map<std::string, std::string> m_mapWhiteList; // �������˻�->����
	int m_nTotalConnections; // ���ܿͻ��������ܴ���
};

#endif
