#ifndef	__KBIDFRIENDRELATION_H__
#define __KBIDFRIENDRELATION_H__

#include "playerrelation_i.h"

// ��ͨ���ѽӿ�ʵ��
class KBidFriendRelation : public IKBidFriendRelation
{
public:
	// ���Ӻøжȵ�;��
	enum KE_METHOD
	{
		emKMETHOD_NORMAL,		// ����;��
		emKMETHOD_IBITEM,		// ͨ��IB����
		emKMETHOD_COUNT
	};
#pragma pack(push, 1)
	struct KFRIEND_DBINFO
	{
		INT				nFavor;
		DWORD			dwLastTalkTime;
		WORD			aryDayPoint[emKMETHOD_COUNT];	// �����Ѽӵ����ܶ�
	};
	struct KFRIEND_INFO
	{
		KFRIEND_INFO() { btModify = 0; }
		BOOL IsModify() { return btModify == 1; }
		LPVOID GetData() { return this; }
		KFRIEND_DBINFO	sDBInfo;						// ��������
		INT				aryPrePoint[emKMETHOD_COUNT];	// Ԥ��������ܶ�
		BYTE			btModify;
	};
#pragma pack(pop)
public:
	static KFRIEND_INFO GetDefaultValue();
	static KFRIEND_INFO Load(LPVOID pData, INT nLen);
	KBidFriendRelation(INT nType, IKRelationFactory *pFactory);
	virtual ~KBidFriendRelation();
	VOID Init(INT nMaster, INT nTarget, KFRIEND_INFO *pInfo);
public:
	// ��ѯ�ӽӿ�
	virtual BOOL QueryRelation(INT nType, LPVOID *ppv);
	// ��ѯ��ϵ����
	virtual INT GetType();
	// ��ȡ������Ϣ����
	virtual INT GetInfLen();
	// ���渽�����ݵ�ָ��������������ͬ��������Ϣ��
	virtual BOOL SaveInfo(CHAR *pBuf, INT nLen);
	// ���ظ�������
	virtual BOOL LoadInfo(CHAR *pBuf, INT nLen);
	// ��ȡ��λ/��λ��ң�bAsMasterΪTRUE��ʾ��λ��FALSE��ʾ��λ��
	virtual INT GetRole(BOOL bAsMaster);
	// ��ȡ��ϵ�е���һ�����id
	virtual INT GetOtherPlayerId(INT nSelfId);

	virtual DWORD GetLastTalkTime();
	/***********************************************************
	 Function		: GetFavor
	 Description	: ��ȡ�øжȡ�
	 Return			: INT �øж�
	 ***********************************************************/
	virtual INT GetFavor();
	/***********************************************************
	 Function		: AddFavor
	 Description	: ���Ӻøжȡ�
	 Return			: BOOL
	 Param			: nPoint	���ӵĺøж�
	 Param			: nMethod	���Ӻøжȵ�;������KE_FAVOR_METHOD
	 Param			: bByHand	��ʾ�Ƿ�ͨ���ֹ���ӣ����������ÿ������
	 ***********************************************************/
	virtual BOOL AddFavor(INT nPoint, INT nMethod,  INT& nAward, BOOL bByHand = FALSE);
	/***********************************************************
	 Function		: PreAddFavor
	 Description	: Ԥ���Ӻøжȣ�ȷ���´����Ӻøжȳɹ���
	 Return			: BOOL
	 Param			: nPoint	���ӵĺøж�
	 Param			: nMethod	���Ӻøжȵ�;������KE_FAVOR_METHOD
	 ***********************************************************/
	virtual BOOL PreAddFavor(INT nPoint, INT nMethod);
	/***********************************************************
	 Function		: ActAddFavor
	 Description	: ���Ӻøжȣ���Ԥ���Ӻøжȶ�Ӧ��
	 Return			: BOOL
	 Param			: nPoint	���ӵĺøж�
	 Param			: nMethod	���Ӻøжȵ�;������KE_FAVOR_METHOD
	 ***********************************************************/
	virtual BOOL ActAddFavor(INT nPoint, INT nMethod);
	/***********************************************************
	 Function		: CancelPreAddFavor
	 Description	: ȡ��Ԥ�������ܶ�
	 Return			: BOOL
	 Param			: nPoint	Ҫȡ��Ԥ��������ܶ�
	 Param			: nMethod	;������KE_FAVOR_METHOD
	 ***********************************************************/
	virtual BOOL CancelPreAddFavor(INT nPoint, INT nMethod);
	// ��������Ѽ����ܶ�

	static BOOL ClearFavorLimit(INT nPlayerId);

	BOOL SetLastTalkTime(DWORD dwTime);


	// ��ȡ��������
	virtual LPVOID GetInfo(INT &nLen)
	{
		nLen = sizeof(KFRIEND_DBINFO);
		return &m_pInfo->sDBInfo;
	}
private:	
	BOOL CheckFavor(INT nPoint, INT nMethod, KFRIEND_INFO *pInfo);
	INT  GetFavorLevel(INT nPoint);

private:
	BOOL _ClearFavorLimit();
	INT					m_nType;
	IKRelationFactory*	m_pFactory;
	INT					m_nMaster;
	INT					m_nTarget;
	KFRIEND_INFO*		m_pInfo;
};

#endif //__KBIDFRIENDRELATION_H__
