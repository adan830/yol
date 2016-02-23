/* -------------------------------------------------------------------------
//	�ļ���		��	relation.cpp
//	������		��	
//	����ʱ��	��	
//	��������	��	�޸������ݵ���ҹ�ϵ����ʱ���ѡ��������ȣ�
//
// -----------------------------------------------------------------------*/
#include "stdafx.h"
#include "relation.h"
#include "unirelationfactory.h"

KRelation::KRelation(KEPLAYERRELATION_TYPE nType, IKRelationFactory *pFactory)
	: m_nType(nType), m_pFactory(pFactory)
{
	ASSERT(pFactory && nType >= 0 && nType < emKPLAYERRELATION_TYPE_COUNT);
	m_nMaster = m_nTarget = 0;
}

KRelation::~KRelation()
{
}

BOOL KRelation::Init(INT nMaster, INT nTarget)
{
	// KGC_CONFIRM_RET_FALSE(nMaster && nTarget);
	ASSERT(nMaster && nTarget);
	m_nMaster = nMaster;
	m_nTarget = nTarget;
	return TRUE;
}

// ��ѯ�ӽӿ�
BOOL KRelation::QueryRelation(INT nType, LPVOID *ppv)
{
	// KGC_CONFIRM_RET_FALSE (nType == m_nType);
	ASSERT(nType == m_nType);
	*ppv = this;
	return TRUE;
}

// ��ѯ��ϵ����
INT	KRelation::GetType()
{
	return m_nType;
}

// ��ȡ������Ϣ����
INT KRelation::GetInfLen()
{
	return 0;
}

// ���渽�����ݵ�ָ��������������ͬ��������Ϣ��
BOOL KRelation::SaveInfo(CHAR *pBuf, INT nLen)
{
	// KGC_Error("");
	ASSERT(0);
	return FALSE;
}

// ��������
BOOL KRelation::LoadInfo(CHAR *pBuf, INT nLen)
{
	// KGC_Error("");
	ASSERT(0);
	return FALSE;
}

// ��ȡ��λ/��λ��ң�bAsMasterΪtrue��ʾ��λ��false��ʾ��λ��
INT KRelation::GetRole(BOOL bAsMaster)
{
	return bAsMaster ? m_nMaster : m_nTarget;
}
