/* -------------------------------------------------------------------------
//	�ļ���		��	kintroductionfactory.h
//	������		��	
//	����ʱ��	��	
//	��������	��	�����˺��ѹ���
//
// -----------------------------------------------------------------------*/
#ifndef __KINTRODUCTIONFACTORY_H__
#define __KINTRODUCTIONFACTORY_H__

#include "bidunequalrelationfactory_t.h"
#include "datarelation_t.h"
#include "playerrelation_datadef.h"
#include "closefriendrelation.h"

class KRole;
class KIntroductionFactory : public KBidUnEqualRelationFactory_T<KCloseFriendRelation::KCLOSEFRIEND_INFO,
	KCloseFriendRelation, sizeof(KCloseFriendRelation::KCLOSEFRIEND_DBINFO) >
{
	typedef KBidUnEqualRelationFactory_T<KCloseFriendRelation::KCLOSEFRIEND_INFO, 
		KCloseFriendRelation, sizeof(KCloseFriendRelation::KCLOSEFRIEND_DBINFO) > SUPER_CLASS;
	enum
	{
		emKINTRODUCED_MAXLEVEL = 11,		// �������˵���󼶱�
		emKINTRODUCER_DIFLEVEL = 6,			// �����˱���ȱ����������ٴ�˼�����Ŀ
	};
	enum KEPLAYERRELATION_MSG_TYPE
	{
		emADDINTRODUCTION_SUCCESS	= 1,	// �����˽����ɹ�
		emINTRODUCTION_OVERMAX_NUMBER,		// ���������������
	};
public:
	KIntroductionFactory();
	~KIntroductionFactory();
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
			BOOL			bIsMasterActive,
			IKRelation**	ppRelation);
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
			INT nTarget);
private:
	BOOL CheckCreation(INT nMasterID, INT nTargetID, KRole* pMaster, KRole* pTarget);

	BOOL MsgToShow(INT nMasterId, INT nTargetId, KRole* pMasterPlayer, KRole* pTargetPlayer, BYTE btMsgType);
};

#endif //__KINTRODUCTIONFACTORY_H__

