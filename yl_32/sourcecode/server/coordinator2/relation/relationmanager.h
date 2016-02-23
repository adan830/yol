/* -------------------------------------------------------------------------
//	�ļ���		��	relationmanagers_gc.h
//	������		��	
//	����ʱ��	��	
//	��������	��	
//
// -----------------------------------------------------------------------*/
#ifndef __KRELATIONMANAGER_GC_H__
#define __KRELATIONMANAGER_GC_H__

#include "playerrelation_i.h"
#include "serverbase/protocol/Relay_GS_Protocol.h"
#include "relationcounter.h"
class KRole;
class KCloseFriendRelation;
struct KRELATION_PROTO_FRIENDINFO;

class KRelationManager_GC
{
	enum
	{
		emKRELATION_MAX_COUNT				= 1000,			// ����ϵ��
		emKRELATION_MINFAVOR_NOTIFYONLINE	= 1,			// ֪ͨ�����ߵ���С���ܶ�
		emKRELATION_SEARCHRES_MAXCOUNT		= 50,			// ÿ�������ɰ�ʦ��ҵ��������Ŀ
		emKRELATION_TRAININGHINT_CYCLE		= 7 * 24 * 3600,// ��ʦ/��ͽ��ʾ���ڣ��룩
		emKRELATION_NEXTSEARCHSCRAP			= 40,			// ����ʦͽʱÿ�μ��ʱ��
		emKRELATION_SHOWPLAYERNUMBER		= 50,			// ��Ҫͬ����ʾ������������
	};
	enum KEADDRELATION_RESULT
	{
		emKEADDRELATION_FAIL	= 0,	// ��ӹ�ϵʧ��
		emKEADDRELATION_SUCCESS = 1,	// ��ӹ�ϵ�ɹ�
		emKEHAVE_RELATION		= 2,	// �Ѿ��й�ϵ��
		emKEPLAYER_NOTONLINE	= 3,	// �Է������ߵ�ʱʱ�������Ϊ����
	};
	typedef BOOL (KRelationManager_GC::*fnTrainingCheck)(KRole* pPlayer, INT nPlayerID, IKRelationFactory* pFactory, LPVOID * ppParam);
	typedef BOOL (KRelationManager_GC::*fnTrainingEvent)(KRole* pPlayer, INT nPlayerID, IKRelationFactory* pFactory, LPVOID pParam);
	struct KTRAINING_EVENT
	{
		fnTrainingCheck pfnCheck;
		fnTrainingEvent pfnEvent;
	};
	struct KTPRELATION
	{
		BYTE	btType;
		INT		nPlayerId;
		INT		nBindCoin;
		CHAR	szTarget[_NAME_LEN];
		BOOL	bMaster;
	};
	struct KTPPLAYERSEX
	{
		BYTE bySex;
		INT nPlayerId;
	};
	// sort by 
	struct _KPlayerSexSort
	{
		bool operator()(CONST KTPPLAYERSEX& nStart, CONST KTPPLAYERSEX& nEnd)
		{
			return nStart.bySex > nEnd.bySex;
		}
	};
	struct KFriendAward
	{
		INT nMaxNum; // �������
		INT nAward;  // ��������
	};
public:
	struct KTIMEINFO
	{
		INT nPlayerId;		// ���Id
		INT nType;			// ��ϵ����
		INT	nRemanentTime;	// ����һ�����޵�ʣ��ʱ��
		BOOL bAsMaster;		// ����λ���Ǵ�λ
	};
	typedef	std::multimap<INT, KTPRELATION> MAPRELATION;
	typedef std::set<INT> SET_PLAYERID;
	typedef std::vector<INT > VECPLAYERID;

	// static KRelationManager_GC *Instance() {return &ms_inst;}
	KRelationManager_GC();
	~KRelationManager_GC();

	// dispose
// 	virtual BOOL SendData(LPVOID pData, INT nSize, INT nConnectID = -1);
	// �ж��˼ʹ�ϵ���Ƿ�������
	BOOL CheckIsLoadEnd(KRole* pPlayerApp, INT nAppId, BOOL bSendMsg = TRUE);
	BOOL CheckIsLoadEnd(INT nAppId);
	// ��鴴����ϵ�ĳ�ͻ������
	BOOL CheckCreateDepRep(INT nType, INT nRole, INT nAppId, INT nDstId);
	// ���ɾ����ϵ�ĳ�ͻ������
	BOOL CheckDelDepRep(INT nType, INT nRole, INT nAppId, INT nDstId);
	// �������ܶȵ����ڣ����������ÿ������
	BOOL ResetLimtWhenCrossDay(INT nAppId, INT nDstId);
	// ͬ����ϵ�б�
	BOOL SyncRelationList(INT nPlayerId );
	// �����к����б���Ϣͬ�����Լ�
	BOOL SyncFriendListToMyself(INT nPlayerId );
	// ���Լ���Ϣͬ�����������ߺ���
	BOOL SyncMyselfToFriendList(INT nPlayerID, KRole* pPlayer);
	// ֪ͨ�����Լ���/����
	BOOL NotifyOnline(INT nPlayer, BOOL bOnline);
	// ����ĳ����ҵĹ�ϵ�б����ڴ���ж��
	BOOL Unload(INT nPlayer);
	// ��ȫɾ��ĳ����ҵĹ�ϵ
	BOOL Remove(INT nPlayer, LPCSTR pszPlayerName);	
	// ֪ͨ��ϵ�б�������
	BOOL NotifyRelationListLoaded(INT nPlayerId);
	// ʹ��IB����ÿ�ջ�õ�������ܶ�
	inline INT GetMaxFavorEveryDayWithIB() CONST
	{
		return m_nMaxFavorEveryDayWithIB;
	}
	// ��IB����;��ÿ�ջ�õ�������ܶ�
	inline INT GetMaxFavorEveryDayWithoutIB() CONST
	{
		return m_nMaxFavorEveryDayWithoutIB;
	}
	// ��С���ܶ�
	inline INT GetMinFavor() CONST
	{
		return m_nMinFavor;
	}
	// ������ܶ�
	inline INT GetMaxFavor() CONST
	{
		return m_nMaxFavor;
	}
	// ÿ����ҵ��˼ʹ�ϵ�������Ŀ
	inline INT GetMaxRelationCount() CONST
	{
		return m_nMaxRelationCount;
	}
	// ��ʦͽ��صļ��
	BOOL TrainingCheck(INT nPlayerId);
	// ���ú�����Ϣ
	static BOOL InitRelationInfo(KRole* pMaster, KRole* pTarget, INT nFavor, DWORD dwLastTalkTime, KRELATION_PROTO_FRIENDINFO* pInfo);
	// 
	BOOL GetFriendListToMyselfInfo(IKEnumRelation *pEnum, INT nPlayerSelf,	INT nMaxCount, 
		KRELATION_PROTO_FRIENDINFO aryInfo[], INT& nCount);
	BOOL SyncMyselfToFriendList(KRole* pPlayer, INT nPlayerID, BOOL bMaster);
	BOOL DelRelationByHand(INT nAppID, INT nType, BOOL bRole, LPCSTR pszRelation);
	BOOL AddRelationByHand(INT nAppId, INT nType, BOOL bRole, LPCSTR pszRelation);
	BOOL CanCreateRelation(INT nType, INT nRole, INT nMasterId, INT nTargetId);
	BOOL CreateRelation(INT nType, INT nMasterId, INT nTargetId, BOOL bIsMaster);
	BOOL CanDelRelation(INT nType, INT nRole, INT nMasterId, LPCSTR pszTargetName);
	BOOL DelRelation(INT nType, INT nMasterId, INT nTargetId, BOOL bIsMaster);
	BOOL DelOverTimeRelation(INT nType, INT nMasterId, INT nTargetId, BOOL bIsMaster);
	BOOL AddFriendFavor(INT nAppId, INT nDstId, INT nFavor, INT nMethod, BOOL bByHand = FALSE);
	BOOL SetFriendTalkTime(INT nAppId, INT nDstId, DWORD dwTime);
	// �������ܶ�֮��ͬ��������Ϣ
	BOOL SyncFriendInfo(INT nAppId, INT nDstId);
	// ��������Ƶ��
	BOOL GetMyChannelFriend(INT nPlayerId,  VECPLAYERID& vecPlayerId);
	// ����������ܶȽ���
	BOOL DoFrindFavorAward(KRole* pPlayerApp, KRole* pPlayerDst, INT nAppId, INT nDstId, INT nAwardLevel);
	// �������ܶȵȼ������ص�
	VOID OnFavorLevelUp(INT nPlayerAppId, INT nPlayerDstId, INT nFavorLevel);
	// ��ȡ������һ�����޵����
	BOOL GetCloseFriendTimeInfo(INT nAppPlayerId, std::vector<KTIMEINFO>& rvctTimeInfo);
	// ��ȡĳ���ָ�����˼ʹ�ϵ������
	INT GetOneRelationCount(INT nPlayerId, INT nType, BOOL bAsMaster = TRUE);
	// �ж����֮���Ƿ����ָ�����˼ʹ�ϵ
	BOOL HasRelation(INT nAppId, INT nDstId, INT nType, BOOL bAsMaster = TRUE);
	// ��ȡָ����ҵ����ܶ�
	INT GetFriendFavor(INT nPlayerId1, INT nPlayerId2);

public:
	BOOL Init();
	BOOL UnInit();
	BOOL Activate();
	BOOL SaveAll();

	BOOL OnLoadPlayerData(INT nPlayerId, BYTE* pbyData, size_t uDataLen);
	BOOL SavePlayerData(INT nPlayerId);
	void OnPlayerLeave(INT nPlayerId);

	void AddDirty(DWORD dwPlayerId);

	// Э��ע�� todo �Ƴ����manager
public:
	static void Process_AddFavor(BYTE* pbyData, size_t uDataLen, int nConnIndex);
	static void Process_SearchTeacher(BYTE* pbyData, size_t uDataLen, int nConnIndex);
	static void Process_SearchStudent(BYTE* pbyData, size_t uDataLen, int nConnIndex);
	static void Process_SetTrainingOption(BYTE* pbyData, size_t uDataLen, int nConnIndex);
	static void Process_GetTrainingOption(BYTE* pbyData, size_t uDataLen, int nConnIndex);
	static void Process_RequestTeacher(BYTE* pbyData, size_t uDataLen, int nConnIndex);
	static void Process_RequestStudent(BYTE* pbyData, size_t uDataLen, int nConnIndex);
	static void Process_TrainingGraduate(BYTE* pbyData, size_t uDataLen, int nConnIndex);
	static void Process_TrainingViewInfo(BYTE* pbyData, size_t uDataLen, int nConnIndex);
	static void Process_TrainingPlayerInfo(BYTE* pbyData, size_t uDataLen, int nConnIndex);
	static void Process_TrainingMakeFriend(BYTE* pbyData, size_t uDataLen, int nConnIndex);
	static void Process_TrainingApply(BYTE* pbyData, size_t uDataLen, int nConnIndex);
	static void Process_AddCloseFriendBindCoin(BYTE* pbyData, size_t uDataLen, int nConnIndex);
	static void Process_ApplyGainIbBackCoin(BYTE* pbyData, size_t uDataLen, int nConnIndex);
	static void Process_GainIbBackCoin(BYTE* pbyData, size_t uDataLen, int nConnIndex);
	static void Process_CancelGainCoin(BYTE* pbyData, size_t uDataLen, int nConnIndex);

private:
	BOOL IbBackMailSend(INT nPlayerId);
	BOOL IbBackOverMailSend(INT nSendId, INT nReceiveId, BOOL bBothSend);
	BOOL AddRelationMap(INT nPlayerId, BYTE btType, KCloseFriendRelation* pRelation, INT nCoin);
	BOOL FeedBackApplyIbCoin(INT nPlayerId, BYTE byFirst = 0);
	KCloseFriendRelation* GetCloseFriendRelation(INT nPlayerId, BYTE btType, INT nPlayerId2);
	// �ռ����ߵĺ���id
	BOOL AddFriendIdToVec(INT nSendPlayerId, IKEnumRelation* pEnum, VECPLAYERID& vecPlayerId);
	BOOL SyncRelationList(
		INT					nPlayerID,
		INT					nRelationType,
		IKRelationFactory*	pFactory,
		BOOL				bAsMaster,
		BOOL				bNotifyClient);
	// ���߿ͻ���Ҫ��ʼͬ����
	BOOL SyncStartRelationList(INT nPlayerID);
	// ֪ͨ��ϵ�������/����
	BOOL NotifyOnline(
		INT					nRelationType,
		BOOL				bAsMaster,
		INT					nPlayerId,
		IKRelationFactory*	pFactory,
		BOOL				bOnline,
		SET_PLAYERID& rsetAlreadyNotify);
//	BOOL FindPlayerGuidByName(LPCSTR pszName, GUID nPlayerId);
	// ֪ͨ�����Լ�ɾ��
	BOOL NotifyDelete(INT nSelfId, LPCSTR pszPlayerName, INT nType, BOOL bAsMaster, IKEnumRelation *pEnum);
	// �������������Ŀɰ�Ϊʦ�������
	BOOL SearchTeacherList(IKTrainingFactory* pFactroy, KRole* pStudent, INT nPlayerID);
	// �������������Ŀ���Ϊ���ӵ����
	BOOL SearchStudentList(IKTrainingFactory* pFactroy, KRole* pTeacher, INT nPlayerID);
	// �����Ӻ�ʦ���ʸ�
	BOOL CheckTeacherAndStudent(
		KRole* pTeacher,
		KRole* pStudent,
		INT	nTeacherID,
		INT nStudentID,
		BOOL bIsTeacherActive);
	BOOL TrainingCheck_Student(KRole* pPlayer, INT nPlayerID, IKRelationFactory* pFactory, LPVOID * ppParam);
	BOOL TrainingCheck_Teacher(KRole* pPlayer, INT nPlayerID, IKRelationFactory* pFactory, LPVOID * ppParam);
	BOOL TrainingCheck_TimeOut(KRole* pPlayer, INT nPlayerID, IKRelationFactory* pFactory, LPVOID * ppParam);
	BOOL TrainingEvent_Student(KRole* pPlayer, INT nPlayerID, IKRelationFactory* pFactory, LPVOID pParam);
	BOOL TrainingEvent_Teacher(KRole* pPlayer, INT nPlayerID, IKRelationFactory* pFactory, LPVOID pParam);
	BOOL TrainingEvent_TimeOut(KRole* pPlayer, INT nPlayerID, IKRelationFactory* pFactory, LPVOID pParam);
	// ������ѡ������ͽ���ʦ��������
	BOOL PreSearchPlayer(IKTrainingFactory*	pFactory, BOOL bStudent);
private:
	BOOL SetBeforeFrindFavor(KRole* pPlayer, INT nLeft, INT nAwardLevel);
	BOOL NeedLogRecord(IKRelationFactory *pFactory, BYTE byRelationType, INT nMasterId, INT nTargetId);
	BOOL RecodeDeleteLog(KRole* pAppPlayer, KRole* pTargetPlayer, BYTE byType);

	// static KRelationManager_GC	ms_inst;
	INT							m_nMaxFavorEveryDayWithIB;		// ÿ��������ӵ����ܶ������ֵ��IB����;����
	INT							m_nMaxFavorEveryDayWithoutIB;	// ÿ��������ӵ����ܶ������ֵ����IB����;����
	INT							m_nMinFavor;					// ��С���ܶ�
	INT							m_nMaxFavor;					// ������ܶ�
	INT							m_nMaxRelationCount;			// ��ҹ�ϵ����
	static KTRAINING_EVENT		ms_aTrainingEvent[];			// ʦͽ���
	MAPRELATION					m_mpCloseFriend;	
	time_t						m_tLastSearchStudent;			// ��һ������ͽ�ܵ�ʱ��
	time_t						m_tLastSearchTeacher;			// ��һ������ʦ����ʱ��
	INT							m_nLastTeacherId;				// �ڻ����е����һ��ʦ����id
	INT							m_nLastStudentId;				// �ڻ����е����һ��ͽ�ܵ�id
	std::vector<KTPPLAYERSEX>	m_vecStudentId;					// ͽ��ID
	std::vector<KTPPLAYERSEX>	m_vecTeacherId;					// ʦ��ID
	std::vector<KFriendAward>	m_vecFriendAwardLevel;			// ��Ӧ�ȼ��ϣ�����콱����

	typedef std::set<DWORD> SET_DIRTY_PLAYER;
	SET_DIRTY_PLAYER m_setDirtyPlayerId;
};

#endif //__KRELATIONMANAGER_GC_H__
