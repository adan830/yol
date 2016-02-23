/* -------------------------------------------------------------------------
//	�ļ���		��	KinGcScript.cpp
//	������		��	liyun
//	����ʱ��	��	2012/11/12 09:34:08
//	��������	��	
//
// -----------------------------------------------------------------------*/

#include "stdafx.h"
#include "KinRelayClient.h"
#include "onlinegamebase/kscriptmanager.h"
#include "KinModule.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// -------------------------------------------------------------------------



// -------------------------------------------------------------------------

namespace KinGsScript
{
	// -------------------------------------------------------------------------
	// @ClientSvr(C/S)	: 
	// @ClassName		: --
	// @LuaApiName		: CreateKin
	// @Description		: ��������
	// @ReturnCode		: �����ɹ���1������ʧ�ܣ�0
	// @ArgumentFlag	: dsd
	// @ArgumentComment	: dwPlayerId���峤
	// @ArgumentComment	: szTongName�ַ�������������
	// @ArgumentComment	: nTemplateIndexΪ����ģ������
	// @LuaMarkEnd
	// -------------------------------------------------------------------------
	INT LuaCreateKin(QLuaScript& sc)
	{
		DWORD dwMasterId = sc.GetInt(1);
		LPCSTR cszTongName = sc.GetStr(2);
		INT nTemplateIndex = sc.GetInt(3);

		KinRelayClient::DoApplyCreateTongRequest(dwMasterId, cszTongName, nTemplateIndex);
		return 0;
	}

	// -------------------------------------------------------------------------
	// @ClientSvr(C/S)	: 
	// @ClassName		: --
	// @LuaApiName		: GetKinTotalContributionOneDay
	// @Description		: ��������
	// @ReturnCode		: ����һ������Ĺ��׶�
	// @ArgumentFlag	: 
	// @LuaMarkEnd
	// -------------------------------------------------------------------------
	INT LuaGetKinTotalContributionOneDay(QLuaScript& sc)
	{
		sc.PushNumber(g_KinModule.GetTotalContributionOneDay());
		return 1;
	}

	// -------------------------------------------------------------------------
	// @ClientSvr(C/S)	: 
	// @ClassName		: --
	// @LuaApiName		: GetPlayerKinInfo
	// @Description		: �õ���ҵļ�����Ϣ
	// @ArgumentFlag	: d
	// @ArgumentComment	: ���id
	// @LuaMarkEnd
	// -------------------------------------------------------------------------
	INT LuaGetPlayerKinInfo(QLuaScript& sc)
	{
		INT nPlayerId = sc.GetInt(1);

		CONST QKinModule::PLAYER_KIN_INFO& crInfo = g_KinModule.GetPlayerKinInfo((DWORD)nPlayerId);
		sc.PushTable();
		
		sc.PushNumber(crInfo.dwKinMasterID);
		sc.SetTableField("dwKinMasterID");

		sc.PushNumber(crInfo.dwKinId);
		sc.SetTableField("dwKinId");

		sc.PushNumber(crInfo.nKinLevel);
		sc.SetTableField("nKinLevel");

		sc.PushString(crInfo.szKinName.c_str());
		sc.SetTableField("szKinName");

		return 1;
	}

	// -------------------------------------------------------------------------
	// @ClientSvr(C/S)	: 
	// @ClassName		: --
	// @LuaApiName		: UpdateAllPlayerKinLevelInfo
	// @Description		: ���¼���ȼ���Ϣ
	// @ArgumentFlag	: dd
	// @ArgumentComment	: ����id
	// @ArgumentComment	: ����ȼ�
	// @LuaMarkEnd
	// -------------------------------------------------------------------------
	INT LuaUpdateAllPlayerKinLevelInfo(QLuaScript& sc)
	{
		DWORD dwKinId = sc.GetInt(1);
        INT nKinLevel = sc.GetInt(2);
		
		g_KinModule.UpdateKinLevel(dwKinId, nKinLevel);

		return 1;
	}

#include "KinGcScript_table.hpp"
};

BOOL g_RegisterKinGcScriptFun()
{
	return g_cScriptManager.RegisterTableFuncs("_G",
		KinGsScript::arFunction, countof(KinGsScript::arFunction));
}
