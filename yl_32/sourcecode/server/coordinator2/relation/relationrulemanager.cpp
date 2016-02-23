/* -------------------------------------------------------------------------
//	�ļ���		��	relationrulemanager.cpp
//	������		��	
//	����ʱ��	��	
//	��������	��	��ϵ����������������ϵ�����ͳ�ͻ��
//
// -----------------------------------------------------------------------*/

#include "stdafx.h"
#include "relationrulemanager.h"
#include "relationfactorylist.h"


KRelationRuleManager KRelationRuleManager::ms_inst;

KRelationRuleManager::KPOLICY KRelationRuleManager::ms_aryPolicy[emKPLAYERRELATION_TYPE_COUNT] =	// �˼ʹ�ϵ����
{
	// SyncToServerAsMaster SyncToServerAsTarget SyncToClientAsMaster SyncToClientAsTarget NotifyOnlineAsMaster NotifyOnlineAsTarget NotifyDeleteAsMaster NotifyDeleteAsTarget NotifyTargetCreation NotifyDeleteToMaster NotifyDeleteToTarget
	{TRUE,	FALSE,	TRUE,	FALSE,	FALSE,	FALSE,	FALSE,	TRUE,	TRUE,	TRUE,	FALSE},	// ��ʱ����
	{TRUE,	FALSE,	TRUE,	FALSE,	FALSE,	FALSE,	FALSE,	TRUE,	FALSE,	TRUE,	FALSE},	// ������
	{TRUE,	TRUE,	TRUE,	TRUE,	TRUE,	FALSE,	TRUE,	TRUE,	TRUE,	TRUE,	TRUE},	// ��ͨ����
 	{TRUE,	TRUE,	TRUE,	FALSE,	TRUE,	FALSE,	TRUE,	TRUE,	TRUE,	TRUE,	TRUE},	// ��ݣ��ֵܡ����ã�
 	{TRUE,	FALSE,	TRUE,	FALSE,	FALSE,	TRUE,	FALSE,	TRUE,	FALSE,	TRUE,	FALSE},	// ����
 	{TRUE,	TRUE,	TRUE,	TRUE,	TRUE,	TRUE,	TRUE,	TRUE,	TRUE,	TRUE,	TRUE},	// ��ǰʦͽ
 	{TRUE,	TRUE,	TRUE,	TRUE,	TRUE,	TRUE,	TRUE,	TRUE,	TRUE,	TRUE,	TRUE},	// ��ʦʦͽ
 	{TRUE,	TRUE,	TRUE,	TRUE,	TRUE,	TRUE,	TRUE,	TRUE,	TRUE,	TRUE,	TRUE},	// ����
 	{TRUE,	TRUE,	TRUE,	FALSE,	FALSE,	TRUE,	FALSE,	TRUE,	TRUE,	TRUE,	TRUE},	// ������
 	{TRUE,	TRUE,	TRUE,	TRUE,	TRUE,	FALSE,	TRUE,	TRUE,	TRUE,	TRUE,	TRUE},	// ָ������
};

KRelationRuleManager::KRelationRuleManager()
{
	for (INT i = 0; i < emKTYPE_COUNT; i++)
	{
		m_aDelPermission[i] = TRUE;
	}
	// ��ʱ����
	m_aryCreateRepRules[emKPLAYERRELATION_TYPE_TMPFRIEND].push_back(KRELATION_RULE(emKPLAYERRELATION_TYPE_BLACKLIST,	emKMASK_POSSIDE));
	m_aryCreateRepRules[emKPLAYERRELATION_TYPE_TMPFRIEND].push_back(KRELATION_RULE(emKPLAYERRELATION_TYPE_BINDFRIEND,	emKMASK_POSSIDE));
	m_aryCreateRepRules[emKPLAYERRELATION_TYPE_TMPFRIEND].push_back(KRELATION_RULE(emKPLAYERRELATION_TYPE_ENEMEY,		emKMASK_POSSIDE));
	// ������
//	m_aryCreateRepRules[emKPLAYERRELATION_TYPE_BLACKLIST].push_back(KRELATION_RULE(emKPLAYERRELATION_TYPE_TMPFRIEND,	emKMASK_POSSIDE));
//	m_aryCreateRepRules[emKPLAYERRELATION_TYPE_BLACKLIST].push_back(KRELATION_RULE(emKPLAYERRELATION_TYPE_BINDFRIEND,	emKMASK_POSSIDE));
//	m_aryCreateRepRules[emKPLAYERRELATION_TYPE_BLACKLIST].push_back(KRELATION_RULE(emKPLAYERRELATION_TYPE_ENEMEY,		emKMASK_POSSIDE));

	// �������ĳ�ͻ��ϵ
	m_aryCreateRepRules[emKPLAYERRELATION_TYPE_BLACKLIST].push_back(KRELATION_RULE(emKPLAYERRELATION_TYPE_SIBLING,		emKMASK_POSSIDE));
	m_aryCreateRepRules[emKPLAYERRELATION_TYPE_BLACKLIST].push_back(KRELATION_RULE(emKPLAYERRELATION_TYPE_TRAINED,		emKMASK_POSSIDE));
	m_aryCreateRepRules[emKPLAYERRELATION_TYPE_BLACKLIST].push_back(KRELATION_RULE(emKPLAYERRELATION_TYPE_TRAINING,		emKMASK_POSSIDE));
	m_aryCreateRepRules[emKPLAYERRELATION_TYPE_BLACKLIST].push_back(KRELATION_RULE(emKPLAYERRELATION_TYPE_COUPLE,		emKMASK_POSSIDE));
	m_aryCreateRepRules[emKPLAYERRELATION_TYPE_BLACKLIST].push_back(KRELATION_RULE(emKPLAYERRELATION_TYPE_INTRODUCTION,	emKMASK_POSSIDE));
	m_aryCreateRepRules[emKPLAYERRELATION_TYPE_BLACKLIST].push_back(KRELATION_RULE(emKPLAYERRELATION_TYPE_BUDDY,		emKMASK_POSSIDE));
	// ��ͨ����
	m_aryDeleteDepRules[emKPLAYERRELATION_TYPE_BINDFRIEND].push_back(KRELATION_RULE(emKPLAYERRELATION_TYPE_SIBLING,		emKMASK_ALLSIDE));
	m_aryDeleteDepRules[emKPLAYERRELATION_TYPE_BINDFRIEND].push_back(KRELATION_RULE(emKPLAYERRELATION_TYPE_TRAINING,	emKMASK_ALLSIDE));
	m_aryDeleteDepRules[emKPLAYERRELATION_TYPE_BINDFRIEND].push_back(KRELATION_RULE(emKPLAYERRELATION_TYPE_TRAINED,		emKMASK_ALLSIDE));
	m_aryDeleteDepRules[emKPLAYERRELATION_TYPE_BINDFRIEND].push_back(KRELATION_RULE(emKPLAYERRELATION_TYPE_COUPLE,		emKMASK_ALLSIDE));
	m_aryDeleteDepRules[emKPLAYERRELATION_TYPE_BINDFRIEND].push_back(KRELATION_RULE(emKPLAYERRELATION_TYPE_INTRODUCTION,emKMASK_ALLSIDE));
	m_aryDeleteDepRules[emKPLAYERRELATION_TYPE_BINDFRIEND].push_back(KRELATION_RULE(emKPLAYERRELATION_TYPE_BUDDY,		emKMASK_ALLSIDE));
	// ���
	m_aryCreateDepRules[emKPLAYERRELATION_TYPE_SIBLING].push_back(KRELATION_RULE(emKPLAYERRELATION_TYPE_BINDFRIEND,		emKMASK_POSSIDE));
	// ����
	m_aryCreateRepRules[emKPLAYERRELATION_TYPE_ENEMEY].push_back(KRELATION_RULE(emKPLAYERRELATION_TYPE_TMPFRIEND,		emKMASK_POSSIDE));
	m_aryCreateRepRules[emKPLAYERRELATION_TYPE_ENEMEY].push_back(KRELATION_RULE(emKPLAYERRELATION_TYPE_BLACKLIST,		emKMASK_POSSIDE));
	m_aryCreateRepRules[emKPLAYERRELATION_TYPE_ENEMEY].push_back(KRELATION_RULE(emKPLAYERRELATION_TYPE_BINDFRIEND,		emKMASK_POSSIDE));
	m_aryCreateRepRules[emKPLAYERRELATION_TYPE_ENEMEY].push_back(KRELATION_RULE(emKPLAYERRELATION_TYPE_ENEMEY,			emKMASK_POSSIDE));
	// ʦͽ
	m_aryCreateDepRules[emKPLAYERRELATION_TYPE_TRAINING].push_back(KRELATION_RULE(emKPLAYERRELATION_TYPE_BINDFRIEND,		emKMASK_POSSIDE));
	m_aryCreateDepRules[emKPLAYERRELATION_TYPE_TRAINED].push_back(KRELATION_RULE(emKPLAYERRELATION_TYPE_BINDFRIEND,		emKMASK_POSSIDE));
	// ����
	m_aryCreateDepRules[emKPLAYERRELATION_TYPE_COUPLE].push_back(KRELATION_RULE(emKPLAYERRELATION_TYPE_BINDFRIEND,		emKMASK_POSSIDE));
}

KRelationRuleManager::~KRelationRuleManager()
{
}

// ���������ϵ������TRUE��ʾ����������ϵ
BOOL KRelationRuleManager::CheckCreateDependency(INT nType, INT nMaster, INT nTarget)
{
	BOOL					bRetCode	= FALSE;
	KRELATION_VEC*			pRuleList	= NULL;
	KRelationFactoryList*	pFactoryList = NULL;
	IKRelationFactory*		pFactory	= NULL;
	const KRELATION_RULE*	pRule		= NULL;

	LOG_PROCESS_ERROR(nType >= 0 && nType < emKTYPE_COUNT);
	LOG_PROCESS_ERROR(nMaster && nTarget);

	pRuleList = &m_aryCreateDepRules[nType];
	pFactoryList = KRelationFactoryList::Instance();
	for (KRELATION_VEC::const_iterator it = pRuleList->begin(); 
		it != pRuleList->end(); it++)
	{
		pRule = &(*it);
		LOG_PROCESS_ERROR(pRule->nMode != 0);

		bRetCode = pFactoryList->CreateFactory(pRule->nType, &pFactory);
		LOG_PROCESS_ERROR(bRetCode);

		if ((pRule->nMode & 0x1) != 0)
		{
			if (pFactory->FindRelation(nMaster, nTarget))
			{
				bRetCode = FALSE;
				goto EXIT0;
			}
		}
		if ((pRule->nMode & 0x2) != 0)
		{
			if (pFactory->FindRelation(nTarget, nMaster))
			{
				bRetCode = FALSE;
				goto EXIT0;
			}
		}
	}

	bRetCode = TRUE;
EXIT0:
	return bRetCode;
}

// ����ͻ��ϵ������TRUE��ʾû�г�ͻ
BOOL KRelationRuleManager::CheckCreateRepugnance(INT nType, INT nMaster, INT nTarget)
{
	BOOL					bRetCode = FALSE;
	KRELATION_VEC*			pRuleList = NULL;
	KRelationFactoryList*	pFactoryList = NULL;
	const KRELATION_RULE*	pRule = NULL;
	IKRelationFactory*		pFactory = NULL;

	LOG_PROCESS_ERROR(nType >= 0 && nType < emKTYPE_COUNT);
	LOG_PROCESS_ERROR(nMaster && nTarget);

	pRuleList = &m_aryCreateRepRules[nType];
	pFactoryList = KRelationFactoryList::Instance();
	for (KRELATION_VEC::const_iterator it = pRuleList->begin(); 
		it != pRuleList->end(); it++)
	{
		pRule = &(*it);

		LOG_PROCESS_ERROR(pRule->nMode != 0);
		
		bRetCode = pFactoryList->CreateFactory(pRule->nType, &pFactory);
		LOG_PROCESS_ERROR(bRetCode);

		if ((pRule->nMode & 0x1) != 0)
		{
			if (pFactory->FindRelation(nMaster, nTarget))
			{
				bRetCode = FALSE;
				goto EXIT0;
			}
		}
		if ((pRule->nMode & 0x2) != 0)
		{
			if (pFactory->FindRelation(nTarget, nMaster))
			{
				bRetCode = FALSE;
				goto EXIT0;
			}
		}
	}

	bRetCode = TRUE;
EXIT0:
	return bRetCode;
}

// ���ɾ����ϵ��������ϵ������TRUE��ʾ����������ϵ
BOOL KRelationRuleManager::CheckDeleteDependency(INT nType, INT nMaster, INT nTarget)
{
	BOOL					bRetCode = FALSE;
	KRELATION_VEC*			pRuleList = NULL;
	KRelationFactoryList*	pFactoryList = NULL;
	IKRelationFactory*		pFactory = NULL;
	const KRELATION_RULE*	pRule = NULL;

	LOG_PROCESS_ERROR(nType >= 0 && nType < emKTYPE_COUNT);
	LOG_PROCESS_ERROR(nMaster && nTarget);
	LOG_PROCESS_ERROR(m_aDelPermission[nType]);

	pRuleList = &m_aryDeleteDepRules[nType];
	pFactoryList = KRelationFactoryList::Instance();
	for (KRELATION_VEC::const_iterator it = pRuleList->begin(); 
		it != pRuleList->end(); it++)
	{
		pRule = &(*it);

		LOG_PROCESS_ERROR(pRule->nMode != 0);

		pFactory = NULL;
		bRetCode = pFactoryList->CreateFactory(pRule->nType, &pFactory);
		LOG_PROCESS_ERROR(bRetCode);

		if ((pRule->nMode & 0x1) != 0)
		{
			if (pFactory->FindRelation(nMaster, nTarget))
			{
				bRetCode = FALSE;
				goto EXIT0;
			}
		}
		if ((pRule->nMode & 0x2) != 0)
		{
			if (pFactory->FindRelation(nTarget, nMaster))
			{
				bRetCode = FALSE;
				goto EXIT0;
			}
		}
	}

	bRetCode = TRUE;
EXIT0:
	return bRetCode;
}

CONST KRelationRuleManager::KPOLICY* KRelationRuleManager::GetPolicy(KEPLAYERRELATION_TYPE emType)
{
	if(emType >= 0 && emType < emKPLAYERRELATION_TYPE_COUNT)
	{
		return &ms_aryPolicy[emType];
	}
	return NULL;
}

BOOL KRelationRuleManager::SetPolicy(KEPLAYERRELATION_TYPE emType, CONST KPOLICY* pPolicy)
{
	if (emType >= 0 && emType < emKPLAYERRELATION_TYPE_COUNT && pPolicy)
	{
		ms_aryPolicy[emType] = *pPolicy;
		return TRUE;
	}
	return FALSE;
}
