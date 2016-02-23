/* -------------------------------------------------------------------------
//	�ļ���		��	tmpfriendfactory.h
//	������		��	
//	����ʱ��	��	
//	��������	��	��ʱ���ѹ���
//
// -----------------------------------------------------------------------*/
#ifndef __KTMPFRIENDFACTORY_H__
#define __KTMPFRIENDFACTORY_H__


#include "unirelationfactory.h"

class KTmpFriendFactory : public KUniRelationFactory
{
	typedef KUniRelationFactory SUPER_CLASS;
public:
	KTmpFriendFactory();
	virtual ~KTmpFriendFactory();
public:
	/***********************************************************
	 Function		: CanCreateRelation
	 Description	: ����Ƿ���Դ�����ҹ�ϵ
	 Return			: BOOL
	 Param			: pMaster		��λ���
	 Param			: pTarget		��λ���
	 ***********************************************************/
	virtual BOOL CanCreateRelation(
			INT nMaster,
			INT nTarget);
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
};


#endif //__KTMPFRIENDFACTORY_H__
