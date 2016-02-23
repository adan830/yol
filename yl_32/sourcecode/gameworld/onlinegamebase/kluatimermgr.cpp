

#include "stdafx.h"
#include "onlinegamebase/ktimermgr.h"
#include "onlinegamebase/kscriptmanager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// -------------------------------------------------------------------------

extern KTimerMgr g_cTimerMgr;


// -------------------------------------------------------------------------

namespace KTimerMgrNamespace
{
	// -------------------------------------------------------------------------
	// @ClientSvr(C/S)	: 
	// @ClassName		: --
	// @LuaApiName		: GetFrame
	// @Description		: ��õ�ǰ��Ϸ����
	// @ReturnCode		: ��ǰ��Ϸ����
	// @ArgumentFlag	: 
	// @LuaMarkEnd
	// -------------------------------------------------------------------------
	INT LuaGetFrame(QLuaScript& sc)
	{	
		sc.PushNumber(g_cTimerMgr.GetCurTime());
		return 1;
	}

	// -------------------------------------------------------------------------
	// @ClientSvr(C/S)	: 
	// @ClassName		: --
	// @LuaApiName		: RegisterTimerPoint
	// @Description		: ע�ᶨʱ��ʱ��㣬Timer�����
	// @ReturnCode		: ִ��ʱ���
	// @ArgumentFlag	: d
	// @ArgumentComment	: ����֡��ִ��
	// @LuaMarkEnd
	// -------------------------------------------------------------------------
	INT LuaRegisterTimerPoint(QLuaScript& sc)
	{	
		UINT uFrame			= sc.GetInt(1);
		UINT uActiveFrame	= g_cTimerMgr.AddScriptTimePoint(uFrame);
		sc.PushNumber(uActiveFrame);
		return 1;
	}

#include "kluatimermgr_table.hpp"
}

BOOL g_RegisterTimerMgrScriptFun()
{
	return g_cScriptManager.RegisterTableFuncs("KTimer", KTimerMgrNamespace::arFunction, countof(KTimerMgrNamespace::arFunction));
}
