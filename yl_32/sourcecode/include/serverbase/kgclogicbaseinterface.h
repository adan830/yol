/* -------------------------------------------------------------------------
//	�ļ���		��	serverbase/kgclogicbaseinterface.h
//	������		��	luobaohang
//	����ʱ��	��	2010/7/13 15:49:02
//	��������	��	gc��Ϸ�߼���ӿڶ���
//
// �߼���Ϊ��Loader�����ӵ�һ����Ϸ�߼���ص�lib��Ϊ����gcģ���ṩ������Ϸ�߼���gcģ��
//	Ҫ�����߼��㹦��ʱ��ͬ������Query�ӿڵķ�ʽ
// -----------------------------------------------------------------------*/
#ifndef __SERVERBASE_KGCLOGICBASEINTERFACE_H__
#define __SERVERBASE_KGCLOGICBASEINTERFACE_H__

#include "serverbase/kgcbaseinterface.h"

// -------------------------------------------------------------------------
// Loader�ṩ���߼���Ľӿ�
struct IKGcLogicProvide
{
	// ע���߼�����չ�ӿڣ��ṩ��gcģ��Query���ã�
	virtual BOOL RegisterExtInterface(REFIID rrid, LPVOID pvObject) PURE;
	virtual BOOL RegisterGsProcessor(IKProcessServer* pIServer) PURE;
	// nConnectId��Gameserver���Ӻţ�-1��ʾ���͸�����
	virtual BOOL Send(INT nConnectId, LPVOID pvData, UINT uDataSize) PURE;
	virtual BOOL Send2OtherGc(INT nModuleId, LPVOID pData, UINT uDataSize) PURE;
};

// Loader���߼��������ӿ�
struct IKGcLogicRequire
{
	// ÿ֡����
	virtual BOOL Breath() PURE;
	//  ��ʼ�����ã��õ��û���Loader����ģ��֮ǰ
	virtual BOOL OnInit(void* pGcDataBase) PURE;
	// ��ʼ����Ͻ�������״̬ʱ����
	virtual BOOL OnStartUp() PURE;
	// ����ʼ������
	virtual BOOL OnUninit() PURE;
};

// �ú������߼���ʵ�֣���Loader���ã�Loader���߼���以���ṩ�ӿڷ���
extern IKGcLogicRequire* g_ResgisterGcLogic(IKGcLogicProvide* piGcLogicRequire);
// -------------------------------------------------------------------------

#endif /* __SERVERBASE_KGCLOGICBASEINTERFACE_H__ */
