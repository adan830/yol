/* -------------------------------------------------------------------------
//	�ļ���		��	kgc_mailmodule.cpp
//	������		��	xiewenzhe
//	����ʱ��	��	2011/5/17 15:05:23
//	��������	��	�ʼ�ϵͳģ��
//
// -----------------------------------------------------------------------*/

#include "stdafx.h"
#include "kgc_mailmodule.h"
#include "kmailcenter.h"
#include "gclogicbase/kgclogicextinterface.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// -------------------------------------------------------------------------

KGC_MailModule KGC_MailModule::ms_inst;


LPCTSTR KGC_MailModule::GetModuleName()
{
	return "mail";
}

BOOL KGC_MailModule::Loop()
{
	return TRUE;
}

BOOL KGC_MailModule::Breath()
{
	return KMailCenter::Instance()->Breath();
}

BOOL KGC_MailModule::OnInit()
{
	BOOL bResult = FALSE;

	QCONFIRM_RET_FALSE(NULL != m_pIKGcQuery);

	bResult = m_pIKGcQuery->QueryInterface(IID_IKG_GCServer, (void**)&m_pIKGcServer);
	QCONFIRM_RET_FALSE(bResult && NULL != m_pIKGcServer);

	bResult = m_pIKGcServer->RegisterGsProcessor((IKProcessServer*)this);
	QCONFIRM_RET_FALSE(bResult);

	return KMailCenter::Instance()->Init();
}

// ��ʼ����Ͻ�������״̬�ǵ���
BOOL KGC_MailModule::OnStartUp()
{
	return TRUE;
}

BOOL KGC_MailModule::OnShutDown()
{
	return KMailCenter::Instance()->OnShutDown();
}

BOOL KGC_MailModule::OnUninit()
{
	return KMailCenter::Instance()->UnInit();
}

BOOL KGC_MailModule::ProcessData(INT nConnectId, LPBYTE pData, UINT uSize)
{
	return KMailCenter::Instance()->ProcessData(nConnectId, pData, uSize);
}

// -------------------------------------------------------------------------
