/* -------------------------------------------------------------------------
//	�ļ���		��	kkeysharemem.h
//	������		��	luobaohang
//	����ʱ��	��	2010/8/24 11:30:54
//	��������	��	Ϊ����ģ���ṩ�����ڴ�
//
// -----------------------------------------------------------------------*/
#ifndef __KKEYSHAREMEM_H__
#define __KKEYSHAREMEM_H__

#include "ksharememoryprovider.h"

enum KE_KEY_SHARE_MEM
{
	emKSMKEY_MEMPIPESYS,
	emKSMKEY_LOADER_SHAREMEM,
	emKSMKEY_MODULE_SETTING,
};
// -------------------------------------------------------------------------
// key�����ڴ�
class KKeyShareMem
{
public:
	KKeyShareMem(void);
	static KKeyShareMem* Inst();
	// Called by GcGateway
	BOOL Init();
	// һ����GcGateway�ڹ���ģ���ʼ��ʱ���ã�����Ҫ����
	LPVOID CreateMem(BYTE byKey, UINT uSize);
	// ��ȡ�Ѵ����Ĺ����ڴ棬Loader����
	LPVOID GetMem(BYTE byKey);
private:
	LPVOID ShareMemAlloc();
	LPVOID ShareMemGet();
private:
	struct KKeyShareData
	{
		KSHARE_MEM_PTR aShareMemPtr[256];
	};
	LPVOID m_pvBuffer;
};

// -------------------------------------------------------------------------

#endif /* __KKEYSHAREMEM_H__ */
