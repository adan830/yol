/* -------------------------------------------------------------------------
//	�ļ���		��	mail.cpp
//	������		��	xiewenzhe
//	����ʱ��	��	2011/5/17 14:59:59
//	��������	��	
//
// -----------------------------------------------------------------------*/

#include "stdafx.h"
#include "kgc_mailmodule.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// -------------------------------------------------------------------------

extern "C" GCMODULE_API IKGC_Module* CreateModuleInstance(IN IKGcQuery* piGcQuery)
{
	QCONFIRM_RET_NULL(piGcQuery);
	QCONFIRM_RET_NULL(KGC_MailModule::Instance());

	KGC_MailModule* pModule = KGC_MailModule::Instance();
	pModule->Init(piGcQuery);
	return pModule;
}

// -------------------------------------------------------------------------
