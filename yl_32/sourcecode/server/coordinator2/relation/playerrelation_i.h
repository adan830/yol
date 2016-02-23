/* -------------------------------------------------------------------------
//	�ļ���		��	playerrelation_i.h
//	������		��	
//	����ʱ��	��	
//	��������	��	��ҹ�ϵ�ӿڣ��������ҹ�ϵ��һ��һ�Ĺ�ϵ��������ѡ�ʦͽ�����ޡ����ˡ���ݵȣ�
//
// -----------------------------------------------------------------------*/
#ifndef __PLAYERRELATION_I_H__
#define __PLAYERRELATION_I_H__

#define  KD_RELAYTIONDATA_MAX_SIZE	255	//must less equal KD_TINY_FIELD_MAX_DATA_SIZE
/*
struct IKRelationDatabase
{
	virtual VOID AddIntoDatabase(INT nType, INT nPlayerId1, INT nPlayerId2, LPVOID pData = NULL, INT nLen = 0) = 0;
	virtual VOID DelFromDatabase(INT nType, INT nPlayerId1, INT nPlayerId2) = 0;
	virtual VOID Remove(INT nPlayerId) = 0;
	virtual VOID Update(INT nType, INT nPlayerId1, INT nPlayerId2, LPVOID pData = NULL, INT nLen = 0) = 0;
};
*/
struct IKRelationHelper
{
	virtual BOOL CheckCanLoad(INT nPlayerId) = 0;
	virtual BOOL CheckCanUnload(INT nPlayerId) = 0;
	virtual BOOL Dirty(INT nPlayerId1, INT nPlayerId2) = 0;
};

struct IKRelationSaver 
{
	virtual BOOL SaveBegin(INT nType, INT nDataLen, BOOL bMaster = TRUE) = 0;
	virtual BOOL SaveEnd(INT nType) = 0;
	virtual BOOL AddRecord(INT nPlayerId, LPVOID pData = NULL) = 0;
};

struct IKRelationSender
{
	virtual BOOL SendData(LPVOID pData, INT nSize, INT nConnectID = -1) = 0;
};

/**
 * Interface	: IKRelation
 * Description	: ��ҹ�ϵ����ҹ�ϵ�����ǵ���ģ���ʱ���ѣ���
				  �����ǶԵ�˫��ģ�һ����ѣ���
				  Ҳ�����ǲ��Ե�˫��ģ�ʦͽ����
 */
struct IKRelation
{
	virtual LPVOID GetInfo(INT &nLen) = 0;						// ��ȡ��������
	virtual BOOL SaveInfo(CHAR *pBuf, INT nLen) = 0;			// ���渽�����ݵ�ָ��������������ͬ��������Ϣ��
	virtual BOOL LoadInfo(CHAR *pBuf, INT nLen) = 0;			// ���ظ�������
	virtual BOOL QueryRelation(INT nType, LPVOID *ppv) = 0;		// ��ѯ�ӽӿ�
	virtual INT GetRole(BOOL bAsMaster) = 0;					// ��ȡ��λ/��λ��ң�bAsMasterΪTRUE��ʾ��λ��FALSE��ʾ��λ��
	virtual INT GetType() = 0;									// ��ѯ��ϵ����
	virtual INT GetInfLen() = 0;								// ��ȡ������Ϣ����
	virtual INT GetOtherPlayerId(INT nSelfId) = 0;							// ��ȡ��һ����id
};


/**
 * Interface	: IKEnumRelation
 * Description	: ��ҹ�ϵö����
 */
struct IKEnumRelation
{
	virtual VOID Reset() = 0;
	virtual BOOL Next(IKRelation **ppRelation) = 0;
	virtual INT  GetCount() = 0;
};

// class KGC_ProtocolProcessor;
/**
 * Interface	: IKRelationFactory
 * Description	: ��ҹ�ϵ���������ڴ����͹�����ҹ�ϵ��ÿһ�����ҹ�ϵ�����Լ��Ĺ�����
 */
struct IKRelationFactory
{
	/***********************************************************
	 Function		: QueryFactory
	 Description	: ��ѯ�ӽӿ�
	 Param			: nType			�ӽӿ����ͣ���KEPLAYERRELATION_FACTORY_SUBTYPE
	 Param			: ppFactory		���ؽӿ�ָ��
	 Return			: BOOL
	 ***********************************************************/
	virtual BOOL QueryFactory(INT nType, LPVOID * ppFactory) {return FALSE;}
	/***********************************************************
	 Function		: GetRelationInfoLen
	 Description	: ��ȡ��ǰ������ҹ�ϵ�ĸ�����Ϣ���ȣ�����ĳһ�ֹ�ϵ���ͣ�������Ϣ�����ǹ̶��ģ���
					  �ø������ݿ���������ʾ���ܶ�֮�����Ϣ����ÿ����ҹ�ϵ���н���
	 Return			: INT
	 ***********************************************************/
	virtual INT GetRelationInfoLen() = 0;
	/***********************************************************
	 Function		: CreateRelation
	 Description	: ������ҹ�ϵ
	 Return			: BOOL
	 Param			: pMaster			��λ���
	 Param			: pTarget			��λ���
	 Param			: bIsMasterActive	��λ���Ϊ�������뷽
	 Param			: ppRelation		��������ҹ�ϵ
	 ***********************************************************/
	virtual BOOL CreateRelation(
			INT nMaster,
			INT nTarget,
			BOOL				bIsMasterActive = TRUE,
			IKRelation**		ppRelation = NULL) = 0;
	/***********************************************************
	 Function		: CanCreateRelation
	 Description	: ����Ƿ���Դ�����ҹ�ϵ
	 Return			: BOOL
	 Param			: pMaster		��λ���
	 Param			: pTarget		��λ���
	 Param			: pData			��������
	 Param			: nLen			�������ݳ���
	 ***********************************************************/
	virtual BOOL CanCreateRelation(
			INT nMaster,
			INT nTarget) = 0;
	/***********************************************************
	 Function		: GetAllRelations
	 Description	: ��ȡָ�����ָ����ɫ��������ҹ�ϵ��
	 Return			: BOOL
	 Param			: bAsMaster		�Ƿ���Ϊ��λ���
	 Param			: pGuigd		���
	 Param			: ppEnum		���ص���ҹ�ϵö����
	 ***********************************************************/
	virtual BOOL GetAllRelations(
			BOOL				bAsMaster,
			INT nPlayerId,
			IKEnumRelation**	ppEnum) = 0;
	/***********************************************************
	 Function		: FindRelation
	 Description	: ����ָ������λ��ҵ���ҹ�ϵ��
	 Return			: BOOL
	 Param			: pMaster		��λ���
	 Param			: pTarget		��λ���
	 Param			: ppRelation	���ص���ҹ�ϵ
	 ***********************************************************/
	virtual BOOL FindRelation(
			INT nMaster,
			INT nTarget,
			IKRelation**		ppRelation = NULL) = 0;
	/***********************************************************
	 Function		: DeleteRelation
	 Description	: ɾ��ָ������λ��ҵ���ҹ�ϵ��
	 Return			: BOOL
	 Param			: pMaster		��λ���
	 Param			: pTarget		��λ���
	 ***********************************************************/
	virtual BOOL DeleteRelation(
			INT nMaster,
			INT nTarget) = 0;
	/***********************************************************
	 Function		: Unload
	 Description	: ��ָ����Ҵ��ڴ���ɾ��
	 Return			: BOOL
	 Param			: pGuid		��ҽ�ɫID
	 ***********************************************************/
	virtual BOOL Unload(INT nPlayerId) = 0;
	/***********************************************************
	 Function		: SaveAll
	 Description	: ����
	 Return			: BOOL
	 Param			: nPlayerId		��ҽ�ɫID
	 ***********************************************************/
	virtual BOOL SaveAll(INT nPlayerId, IKRelationSaver* pSaver) = 0;
	/***********************************************************
	 Function		: Load
	 Description	: ������ҹ�ϵ�б�
	 Return			: BOOL
	 Param			: pMaster		��λ��ҽ�ɫID
	 Param			: pMaster		��λ��ҽ�ɫID
	 Param			: pData			��ϵ����
	 Param			: nLen			���ݳ���
	 ***********************************************************/
	virtual BOOL Load(INT nMaster, INT nTarget, LPVOID pData, INT nLen) = 0;
	/***********************************************************
	 Function		: Remove
	 Description	: ɾ��ָ����ҵ����й�ϵ
	 Return			: BOOL
	 Param			: pGuid		��ҽ�ɫID
	 ***********************************************************/
	virtual BOOL Remove(INT nPlayerId) = 0;
};

/**
 * Interface	: IKTrainingFactory
 * Description	: ʦͽ������δ��ʦ��
 */
class KGC_Player;
struct IKTrainingFactory : public IKRelationFactory
{
	// ���ʦ�����ʸ�
	virtual BOOL CheckTeacherQualification(INT nTeacher, LPINT pnTeacherErr = NULL, LPINT pnStudentErr = NULL) = 0;
	// �����ӵ��ʸ�
	virtual BOOL CheckStudentQualification(INT nStudent, LPINT pnTeacherErr = NULL, LPINT pnStudentErr = NULL) = 0;
	// ���ʦ���͵���֮���Ƿ����һ����ϵ
	virtual BOOL CheckRelation(KGC_Player* pTeacher, KGC_Player* pStudent, LPINT pnTeacherErr = NULL, LPINT pnStudentErr = NULL) = 0;
};

/**
*	Interface	: IKCloseFriendRelation
*	Description : ����
*/
struct IKCloseFriendRelation : public IKRelation
{
	/***********************************************************************
	Function		: GetBindCoin
	Description		: ��ȡ������ȡ�İ󶨽����
	Return			: INT �󶨽������
	Param			: bMaster �Ƿ�Ϊ��λ
	**********************************************************************/
	virtual	INT GetBindCoin(BOOL bMaster)	= 0;

	/***********************************************************************
	Function		: AddBindCoin
	Description		: ��ӿ���ȡ�İ󶨽������
	Param			: INT ����ȡ�󶨽������
	Param			: bMaster �Ƿ�Ϊ��λ
	**********************************************************************/	
	virtual	BOOL AddBindCoin(INT nCoin, BOOL bMaster) = 0;

	/***********************************************************************
	Function		: CheckOverTime
	Description		: �Ƿ��Ѿ�����һ����
	Return			: FALSE����û��ʱ�� TRUE���Ѿ���ʱ
	**********************************************************************/
	virtual	BOOL CheckOverTime()	= 0;
	/***********************************************************************
	Function		: GainBindCoin
	Description		: ��ȡ�󶨽�ң�
	Return			: FALSE����ȡʧ�ܣ� TRUE����ȡ�ɹ�
	Param			: bMaster �Ƿ�Ϊ��λ
	**********************************************************************/
	virtual	BOOL GainBindCoin(BOOL bMaster)		= 0;
	
	virtual BOOL IsMaster(INT nSelfId) = 0;						// �ж��Լ��Ƿ�Ϊ��λ��
	//virtual	INT  GetOtherPlayerId(INT nSelfId) = 0;
};

/**
 * Interface	: IKBidFriendRelation
 * Description	: ��ͨ����
 */
struct IKBidFriendRelation : public IKRelation
{
	// �������ܶȵ�;��
	enum KE_FAVOR_METHOD
	{
		emKFAVOR_METHOD_NORMAL,		// ����;��
		emKFAVOR_METHOD_IBITEM,		// ͨ��IB����
		emKFAVOR_METHOD_COUNT
	};
	virtual DWORD GetLastTalkTime() = 0;

	virtual BOOL SetLastTalkTime(DWORD lastTalkTime) = 0;
	/***********************************************************
	 Function		: GetFavor
	 Description	: ��ȡ���ܶȡ�
	 Return			: INT ���ܶ�
	 ***********************************************************/
	virtual INT GetFavor() = 0;
	/***********************************************************
	 Function		: AddFavor
	 Description	: �������ܶȡ�
	 Return			: BOOL
	 Param			: nPoint	���ӵ����ܶ�
	 Param			: nMethod	�������ܶȵ�;������KE_FAVOR_METHOD
	Param			: bByHand	�Ƿ��ֹ���ӣ��ǵĻ������ÿ������
	 ***********************************************************/
	virtual BOOL AddFavor(INT nPoint, INT nMethod, INT& nAward, BOOL bByHand = FALSE) = 0;
	/***********************************************************
	 Function		: PreAddFavor
	 Description	: Ԥ�������ܶȣ�ȷ���´��������ܶȳɹ���
	 Return			: BOOL
	 Param			: nPoint	���ӵ����ܶ�
	 Param			: nMethod	�������ܶȵ�;������KE_FAVOR_METHOD
	 ***********************************************************/
	virtual BOOL PreAddFavor(INT nPoint, INT nMethod) = 0;
	/***********************************************************
	 Function		: ActAddFavor
	 Description	: �������ܶȣ���Ԥ�������ܶȶ�Ӧ��
	 Return			: BOOL
	 Param			: nPoint	���ӵ����ܶ�
	 Param			: nMethod	�������ܶȵ�;������KE_FAVOR_METHOD
	 ***********************************************************/
	virtual BOOL ActAddFavor(INT nPoint, INT nMethod) = 0;
	/***********************************************************
	 Function		: CancelPreAddFavor
	 Description	: ȡ��Ԥ�������ܶ�
	 Return			: BOOL
	 Param			: nPoint	Ҫȡ��Ԥ��������ܶ�
	 Param			: nMethod	;������KE_FAVOR_METHOD
	 ***********************************************************/
	virtual BOOL CancelPreAddFavor(INT nPoint, INT nMethod) = 0;
};

// ��ҹ�ϵ�����ͣ���ӦIKRelationFactory���ӽӿڣ�
enum KEPLAYERRELATION_FACTORY_SUBTYPE
{
	emKPLAERRELATION_FACTORY_SUBTYPE_TRAINING,	// ʦͽ������δ��ʦ������ӦIKTrainingFactory
	emKPLAERRELATION_FACTORY_SUBTYPE_COUNT
};

// ��ҹ�ϵ����
// ע�⣡����������ͨ���ѵ���ҹ�ϵ������/ʦͽ/���ޣ���ö��ֵ�������ͨ�������͵�ö��ֵ�󣡣���
// �����ڴ洢����Ҫ����ı�ö�ٵ�˳��
enum KEPLAYERRELATION_TYPE
{
	emKPLAYERRELATION_TYPE_TMPFRIEND	= 0,	// ��ʱ���ѣ������ϵ��A��B��Ϊ��ʱ����
	emKPLAYERRELATION_TYPE_BLACKLIST	= 1,	// �������������ϵ��A��B���������
	emKPLAYERRELATION_TYPE_BINDFRIEND	= 2,	// ��ͨ����, �Ե�˫���ϵ��A��B��Ϊ����
	emKPLAYERRELATION_TYPE_SIBLING		= 3,	// ��ݣ��ֵܡ����ã����Ե�˫���ϵ��A��B��Ϊ��ݣ��ֵܡ����ã�
	emKPLAYERRELATION_TYPE_ENEMEY		= 4,	// ���ˣ����Ե�˫���ϵ��A������Bɱ��
	emKPLAYERRELATION_TYPE_TRAINING		= 5,	// ʦͽ�����Ե�˫���ϵ��A��B��ʦ����δ��ʦ��
	emKPLAYERRELATION_TYPE_TRAINED		= 6,	// ʦͽ�����Ե�˫���ϵ��A��B��ʦ�����ѳ�ʦ��
	emKPLAYERRELATION_TYPE_COUPLE		= 7,	// ���ޣ����Ե�˫���ϵ��A��B���ɷ�
	emKPLAYERRELATION_TYPE_INTRODUCTION = 8,	// ���ܣ����Ե�˫���ϵ��A��B�Ľ�����
	emKPLAYERRELATION_TYPE_BUDDY		= 9,	// ָ�����ѣ�˫��Եȹ�ϵ��A��B��Ϊ����ͬʱҲ��Ϊ��ͨ����
	emKPLAYERRELATION_TYPE_COUNT
};

#endif //__PLAYERRELATION_I_H__
