/* -------------------------------------------------------------------------
//	�ļ���		��	kenemyfactory.h
//	������		��	
//	����ʱ��	��	
//	��������	��	
//
// -----------------------------------------------------------------------*/
#ifndef __KENEMYFACTORY_H__
#define __KENEMYFACTORY_H__
// -------------------------------------------------------------------------
#include "bidunequalrelationfactory_t.h"
#include "datarelation_t.h"
#include "playerrelation_datadef.h"

// -------------------------------------------------------------------------
class KEnemyFactory : public KBidUnEqualRelationFactory_T<KNULL, KDataRelation_T<KNULL> >
{
	typedef KBidUnEqualRelationFactory_T<KNULL, KDataRelation_T<KNULL> > SUPER_CLASS;
public:
	KEnemyFactory();
	~KEnemyFactory();
	/***********************************************************
	Function		: CreateRelation
	Description		: ������ҹ�ϵ
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
	Description		: ����Ƿ���Դ�����ҹ�ϵ
	Return			: BOOL
	Param			: pMaster		��λ���
	Param			: pTarget		��λ���
	Param			: pData			��������
	Param			: nLen			�������ݳ���
	***********************************************************/
	virtual BOOL CanCreateRelation(
	INT nMaster,
	INT nTarget);

	/***********************************************************
	Function		: SaveAll
	Description	: ����
	Return			: BOOL	
	Param			: nPlayerId		��ҽ�ɫID
	***********************************************************/
	virtual BOOL SaveAll(INT nPlayerId, IKRelationSaver* pSaver);

protected:
private:
};


#endif /* __KENEMYFACTORY_H__ */
