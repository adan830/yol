/* -------------------------------------------------------------------------
//	�ļ���		��	serverbase/kgcmoduledef.h
//	������		��	luobaohang
//	����ʱ��	��	2010/6/16 20:29:02
//	��������	��	gcģ�鶨��
//
// -----------------------------------------------------------------------*/
#ifndef __SERVERBASE_KGCMODULEDEF_H__
#define __SERVERBASE_KGCMODULEDEF_H__

// -------------------------------------------------------------------------
// ����ģ�����ͬʱ�޸�g_aszGcModuleNames��g_aszGcModuleFiles����֤˳���Ӧ
enum KE_GC_MODULE_ID
{
	emKGCMODULE_NONE = 0,
	emKGCMODULE_LOGICBASE,	// �����߼�ģ�飨��Dllģ�飩
	emKGCMODULE_EXCHANGE,	//������
	emKGCMODULE_CHAT,		//����
	emKGCMODULE_GROUP,		//Ⱥ
	emKGCMODULE_RELATION,
	emKGCMODULE_SHOP,		//�̳�
	emKGCMODULE_GLOBALDATA,
	emKGCMODULE_LEAGUE,		//����
	emKGCMODULE_SUBSTITUTE,	//����
	emKGCMODULE_KIN,		//����
	emKGCMODULE_MAIL,		//����
	emKGCMODULE_CUP,        //cup
	emKGCMODULE_TEAM,			//���

	emKGCMODULE_COUNT,
	emKGCMODULE_ALL = 127 // ���127
};

extern LPCSTR g_aszGcModuleNames[];
extern LPCSTR g_aszGcModuleFiles[];
// -------------------------------------------------------------------------

#endif /* __SERVERBASE_KGCMODULEDEF_H__ */
