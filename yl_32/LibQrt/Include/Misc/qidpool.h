
#pragma once
#include "Core/QLinkArray.h"
// -------------------------------------------------------------------------
// �����1��nMaxNum��ID
class QIdPool
{
public:
	QIdPool();
	virtual ~QIdPool();

public:
	// ��ʼ��,nMaxNumΪ���IDֵ
	VOID Init(INT nMaxNum);
	VOID Uninit();
	// ����ʹ��һ������id��ʧ�ܷ���0
	INT New();
	// �ͷ�һ������id��δ������ظ��ͷŷ���FALSE
	BOOL Delete(INT nId);
	// ��ȡ���ID
	INT GetMaxNum() { return m_nMaxNum; }
	// ��ȡ�ѷ����ID��
	INT GetUsedCount() { return m_cUsedArray.GetCount(); }
	// ��ȡ��һ���ѷ���ID��������Ϊ0���ȡ��һ����������һ������0
	INT GetNextUsedId(INT nLastId) { return m_cUsedArray.GetNext(nLastId); }
protected:
	INT* m_pnFreeId; // ����id����
	INT m_nFreeCount;
	INT m_nMaxNum;
	QLinkArray m_cUsedArray; // �ѷ����Id
};
