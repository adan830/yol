#include "stdafx.h"
#include "onlinegameworld/kluacharacter.h"
#include "onlinegameworld/kcharacter.h"
#include "onlinegameworld/kluaplayer.h"
#include "luaplayervip.h"
#include "playervip.h"
#include "vipmanager.h"
#include "onlinegamemodule/trade/kplayerpurse_i.h"
#include "onlinegamemodule/trade/kplayerpurse.h"

INT LuaPlayerVip::Register2Player(QLuaScript& sc, QLunaBase* pLunaObj)
{
	KLuaPlayer* pLunaPlayer = dynamic_cast<KLuaPlayer*>(pLunaObj);
	QCONFIRM_RET_FALSE(pLunaPlayer);
	KPlayer* pPlayer = pLunaPlayer->GetHim();
	QCONFIRM_RET_FALSE(pPlayer);

	PlayerVip* pPlayerVip= pPlayer->GetCtrl<PlayerVip>();
	QCONFIRM_RET_FALSE(pPlayerVip);
	sc.PushObj(pPlayerVip->GetScriptInterface());
	return 1;
}

// ------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: LuaPlayerVip
// @LuaApiName		: RefreshBuyCount
// @Description		: ˢ�¹������
// @ReturnCode		: 
// @ArgumentFlag	: d
// @ArgumentComment	: id
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT LuaPlayerVip::LuaRefreshBuyCount(QLuaScript& sc)
{
	INT nId = sc.GetInt(1);
	BOOL bOk = g_cVipManager.RefreshBuyCount((DWORD)nId);
	sc.PushNumber(bOk);

EXIT0:
	return 1;
}


// ------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: LuaPlayerVip
// @LuaApiName		: DoBuyCount
// @Description		: �������
// @ReturnCode		: 
// @ArgumentFlag	: dd
// @ArgumentComment	: id
// @ArgumentComment	: ����
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT LuaPlayerVip::LuaDoBuyCount(QLuaScript& sc)
{
	INT nId = sc.GetInt(1);
	INT nNum = sc.GetInt(2);

	PlayerVip* pPlayerVipt = m_rcCharacter.GetCtrl<PlayerVip>();
	BOOL bOk = FALSE;
	if (pPlayerVipt != NULL)
		bOk = pPlayerVipt->DoBuyCount(nId, nNum);
	sc.PushNumber(bOk);

EXIT0:
	return 1;
}

// ------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: LuaPlayerVip
// @LuaApiName		: CanBuyCount
// @Description		: �������
// @ReturnCode		: 
// @ArgumentFlag	: dd
// @ArgumentComment	: id
// @ArgumentComment	: ����
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT LuaPlayerVip::LuaCanBuyCount(QLuaScript& sc)
{
	INT nId = sc.GetInt(1);
	INT nNum = sc.GetInt(2);

	PlayerVip* pPlayerVipt = m_rcCharacter.GetCtrl<PlayerVip>();
	BOOL bOk = FALSE;
	if (pPlayerVipt != NULL)
		bOk = pPlayerVipt->CanBuyCount(nId, nNum);
	sc.PushNumber(bOk);

EXIT0:
	return 1;
}

// ------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: LuaPlayerVip
// @LuaApiName		: IsOpen
// @Description		: �Ƿ񿪷�
// @ReturnCode		: 
// @ArgumentFlag	: ddd
// @ArgumentComment	: playerid
// @ArgumentComment	: id
// @ArgumentComment	: nMsg
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT LuaPlayerVip::LuaIsOpen(QLuaScript& sc)
{
	INT nPlayerId = sc.GetInt(1);
	INT nId = sc.GetInt(2);
	INT nMsg = sc.GetInt(3);
	BOOL bOk = g_cVipManager.IsOpen((DWORD)nPlayerId, nId, (BOOL)nMsg);
	sc.PushNumber(bOk);

EXIT0:
	return 1;
}

// ------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: LuaPlayerVip
// @LuaApiName		: GetRate
// @Description		: �Ƿ񿪷�
// @ReturnCode		: 
// @ArgumentFlag	: dd
// @ArgumentComment	: playerid
// @ArgumentComment	: id
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT LuaPlayerVip::LuaGetRate(QLuaScript& sc)
{
	INT nPlayerId = sc.GetInt(1);
	INT nId = sc.GetInt(2);
	INT bOk = g_cVipManager.GetRate((DWORD)nPlayerId, nId);
	sc.PushNumber(bOk);

EXIT0:
	return 1;
}

// ------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: LuaPlayerVip
// @LuaApiName		: SetFreeState
// @Description		: ����vip����״̬
// @ReturnCode		: 
// @ArgumentFlag	: [d]
// @ArgumentComment	: nFreeTime
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT LuaPlayerVip::LuaSetFreeState(QLuaScript& sc)
{
	INT nFreeTime;
	PlayerVip* pPlayerVip = m_rcCharacter.GetCtrl<PlayerVip>();
	LOG_PROCESS_ERROR(pPlayerVip);

	if(sc.IsNumber(1))
	{
		nFreeTime = sc.GetInt(1);
	}

	pPlayerVip->SetFreeVipState(nFreeTime);

EXIT0:
	return 0;
}

// ------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: LuaPlayerVip
// @LuaApiName		: GetNowBuyCount
// @Description		: ��õ�ǰʹ�ô���
// @ReturnCode		: 
// @ArgumentFlag	: [d]
// @ArgumentComment	: ��ǰʹ�ô���
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT LuaPlayerVip::LuaGetNowBuyCount( QLuaScript& sc )
{
	INT playerID = sc.GetNum(1);
	INT nNum = sc.GetInt(2);
	INT NowBuyCount = g_cVipManager.GetNowBuyCount(playerID,nNum);
	sc.PushNumber(NowBuyCount);
EXIT0:
	return 1;
}


// ------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: LuaPlayerVip
// @LuaApiName		: AddVipExpAndMoney
// @Description		: ����vip����
// @ReturnCode		: 
// @ArgumentFlag	: [d]
// @ArgumentComment	: nFreeTime
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT LuaPlayerVip::LuaAddVipExpAndMoney(QLuaScript& sc)
{
	QLogPrintf(LOG_INFO,"..LuaPlayerVip::LuaAddVipExpAndMoney");
	INT AddMoneyNum = 0;
	KE_PURSE_RESULT nResult = emKPURSE_S_SUCCESS;
	PlayerVip* pPlayerVip = m_rcCharacter.GetCtrl<PlayerVip>();
	KPlayerPurse *pPlayerPurse = m_rcCharacter.GetCtrl<KPlayerPurse>();

	ScriptSafe cSafeScript = g_cScriptManager.GetSafeScript();
	
	LOG_PROCESS_ERROR(pPlayerVip);

	AddMoneyNum = sc.GetInt(1);
	if(0 == pPlayerVip->GetExp()) ////���״γ�ֵ����
	{
		pPlayerVip->DoGiveFirstRechargeReward();
	}
	pPlayerVip->AddExp(AddMoneyNum);
	pPlayerPurse->AddMoney(1,AddMoneyNum,&nResult);
	pPlayerPurse->LogMoney(1, AddMoneyNum,1000, &nResult);//��¼���ĵ�Ǯ
	
	
	cSafeScript->CallTableFunction( "DailyTasks", "commitTaskValue", 0, "osdd",m_rcCharacter.GetScriptInterface(),"",12,1);
	
	//if ()
	//{
	//	QLogPrintf(LOG_ERR, "Can not add Money %d to %d\n", __FUNCTION__,AddMoneyNum, m_rcCharacter.GetId());
	//}

EXIT0:
	return 0;
}
#include "luaplayervip_table.hpp"