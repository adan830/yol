/* -------------------------------------------------------------------------
//	�ļ���		��	unirelationfactory.h
//	������		��	
//	����ʱ��	��	
//	��������	��	�����ϵ��������ʱ���ѡ��������ȣ�
//
// -----------------------------------------------------------------------*/
#ifndef __KUNIRELATIONFACTORY_H__
#define __KUNIRELATIONFACTORY_H__

#include "playerrelation_i.h"
#include "relationcounter.h"
#include "datarelation_t.h"
#include "relationrulemanager.h"

class KRelation;
class KEnumUniRelation;

class KUniRelationFactory : public KRelationFactoryBaseT<>
{
public:
	typedef std::set<INT>					RELATION_SET;
	typedef std::map<INT, RELATION_SET>		RELATION_MAP;
	typedef KRelationRuleManager::KPOLICY	KPOLICY;
public:
	KUniRelationFactory(KEPLAYERRELATION_TYPE nType);
	virtual ~KUniRelationFactory();
	BOOL SetDatabase(IKRelationHelper *pHelper)
	{
		// KGC_CONFIRM_RET_FALSE(pHelper);
		m_pHelper = pHelper;
		return TRUE;
	}
public:
	/***********************************************************
	 Function		: GetRelationInfoLen
	 Description	: ��ȡ��ǰ������ҹ�ϵ�ĸ�����Ϣ���ȣ�����ĳһ�ֹ�ϵ���ͣ�������Ϣ�����ǹ̶��ģ���
					  �ø������ݿ���������ʾ�øж�֮�����Ϣ����ÿ����ҹ�ϵ���н���
	 Return			: INT
	 ***********************************************************/
	virtual INT GetRelationInfoLen()
	{
		return 0;
	}
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
			IKRelation**	ppRelation = NULL);
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
			IKEnumRelation**	ppEnum);
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
			IKRelation**		ppRelation = NULL);
	/***********************************************************
	 Function		: DeleteRelation
	 Description	: ɾ��ָ������λ��ҵ���ҹ�ϵ��
	 Return			: BOOL
	 Param			: pMaster		��λ���
	 Param			: pTarget		��λ���
	 ***********************************************************/
	virtual BOOL DeleteRelation(
			INT nMaster,
			INT nTarget);
	/***********************************************************
	 Function		: Unload
	 Description	: ��ָ����Ҵ��ڴ���ɾ��
	 Return			: BOOL
	 Param			: pGuid		��ҽ�ɫID
	 ***********************************************************/
	virtual BOOL Unload(INT nPlayerId);
	/***********************************************************
	 Function		: SaveAll
	 Description	: ����
	 Return			: BOOL
	 Param			: nPlayerId		��ҽ�ɫID
	 ***********************************************************/
	virtual BOOL SaveAll(INT nPlayerId, IKRelationSaver* pSaver);
	/***********************************************************
	 Function		: Load
	 Description	: ������ҹ�ϵ�б�
	 Return			: BOOL
	 Param			: pMaster		��λ��ҽ�ɫID
	 Param			: pMaster		��λ��ҽ�ɫID
	 Param			: pData			��ϵ����
	 Param			: nLen			���ݳ���
	 ***********************************************************/
	virtual BOOL Load(INT nMaster, INT nTarget, LPVOID pData, INT nLen);
	/***********************************************************
	 Function		: Remove
	 Description	: ɾ��ָ����ҵ����й�ϵ
	 Return			: BOOL
	 Param			: pGuid		��ҽ�ɫID
	 ***********************************************************/
	virtual BOOL Remove(INT nPlayerId);
private:
	BOOL AddReverseRelation(INT nPlayerId1, INT nPlayerId2);
	BOOL DelReverseRelation(INT nPlayerId1, INT nPlayerId2);
	INT CountRelation(CONST RELATION_MAP *pMap);
	VOID AfterCreateRelation(INT nMasterId, INT nTargetId, INT nType);
private:
	CONST KEPLAYERRELATION_TYPE	m_nType;
	KEnumUniRelation*			m_pEnum;
	KRelation*					m_pRelation;
	RELATION_MAP				m_mapRelationList;			// ��ϵ��
	RELATION_MAP				m_mapReverseRelationList;	// �����ϵ��
};

class KEnumUniRelation : public IKEnumRelation
{
	typedef KUniRelationFactory::RELATION_SET RELATION_SET;
public:
	KEnumUniRelation(KRelation *pRelation);
	BOOL Init(INT nPlayerId, BOOL bAsMaster, RELATION_SET *pSet);
	virtual VOID Reset();
	virtual BOOL Next(IKRelation **ppRelation);
	virtual INT  GetCount();
private:
	RELATION_SET::const_iterator	m_itSet;
	RELATION_SET*					m_pRelationSet;
	KRelation*						m_pRelation;
	INT								m_nPlayerId;
	IKRelationHelper*				m_pHelper;
	BOOL							m_bAsMaster;		// m_sGuid�Ľ�ɫ����λ���ߴ�λ��
};

#endif //__KUNIRELATIONFACTORY_H__
