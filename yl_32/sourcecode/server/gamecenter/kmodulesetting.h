/* -------------------------------------------------------------------------
//	�ļ���		��	kmodulesetting.h
//	������		��	luobaohang
//	����ʱ��	��	2010/9/6 17:55:02
//	��������	��	ģ�����ã���GcMonitorͬ��������GcGateway���ã�Loaderֻ��
//
// -----------------------------------------------------------------------*/
#ifndef __KMODULESETTING_H__
#define __KMODULESETTING_H__

#include "serverbase/protocol/GatewayRelayProtocol.h"
// -------------------------------------------------------------------------
#define KD_MODULE_NAME_SIZE 64
//struct KGCMODULE_INFO
//{
//	BYTE byModuleId;
//	BYTE byLoaderId;
//	CHAR szModuleName[KD_MODULE_NAME_SIZE];
//	CHAR szModulePath[MAX_PATH];
//};

class KModuleSetting
{
public:
	KModuleSetting();
	static KModuleSetting* Inst();

	INT Init();
	BOOL SetModuleInfo(INT nModuleNum, KGC_MODULE_INFO aModuleInfo[]);

	INT GetModuleNum();
	INT GetGsPort(BYTE byLoaderId);
	BYTE GetLoaderId(BYTE byModuleId);
	LPCSTR GetModuleName(BYTE byModuleId);
	LPCSTR GetModulePath(BYTE byModuleId);

	INT m_nDevModeFlag; // ����ģʽ���
private:
	//struct KSHARE_MEM_DATA
	//{
	//	INT nModuleNum;
	//	KGCMODULE_INFO aModuleInfo[256];
	//};
	//KSHARE_MEM_DATA m_pShareMemData[1];
	//std::vector<KGC_MODULE_INFO> m_vModuleInfo;
	INT m_nModuleCount;
	KGC_MODULE_INFO m_aModuleInfo[UCHAR_MAX];
};

// -------------------------------------------------------------------------

#endif /* __KMODULESETTING_H__ */
