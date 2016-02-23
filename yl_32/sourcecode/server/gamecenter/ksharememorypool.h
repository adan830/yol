/* -------------------------------------------------------------------------
//	�ļ���		��	ksharememorypool.h
//	������		��	luobaohang
//	����ʱ��	��	2010/8/4 9:57:11
//	��������	��	
//
// -----------------------------------------------------------------------*/
#ifndef __KSHAREMEMORYPOOL_H__
#define __KSHAREMEMORYPOOL_H__

#include "ksharememorybuffer.h"
#include "Misc/objectpool.h"
//KSHARE_MEM_BLOCK
// -------------------------------------------------------------------------
class KShareMemPool
{
	struct KSHARE_MEM_BLOCK_LIST
	{
		KSHARE_MEM_LONG_PTR lptrFreeBlockList;	// ���п��
		INT nCursor;	// ��ǰ�α�
		INT nTail; // ĩ�ˣ���������
	};
	enum
	{
		emKPOOL_BASE_SIZE = 1024,
		emKPOOL_INC_SIZE = 1024,
	};
public:
	static KShareMemPool* Inst();
	// Called by Loader
	BOOL Init();
	// ����һ���ڴ�飬���ֶ��ͷ�
	KShareMemBuffer* Alloc(UINT uSize);
	// �ͷ�
	BOOL Free(KShareMemBuffer* pBuffer);
	// �����ڴ�飬����SharePtr
	KSHARE_MEM_PTR Alloc(BYTE byPageType);
	// �ͷ�һ��SharePtr
	BOOL Free(KSHARE_MEM_PTR ptr);
	// ����һ���ڴ�飬����ָ���Զ��ͷ�
	KShareMemBufferAuto AllocAuto(UINT uSize);
protected:
	KShareMemPool();
protected:
	// BlockList��Vector�±�ΪBlockType
	// ʹ��˫�����壬��������ʹ�������ͷŵ�һ��
	KSHARE_MEM_BLOCK_LIST m_aBufLstFirst[countof(s_auShareMemBlock)];
	KSHARE_MEM_BLOCK_LIST m_aBufLstSecond[countof(s_auShareMemBlock)];
	// KShareMemBuffer�������
	KIncObjPool<KShareMemBuffer> m_cSahreMemBufferAlloctor;
};

// -------------------------------------------------------------------------

#endif /* __KSHAREMEMORYPOOL_H__ */
