#pragma once
#include "onlinegameworld/kcharacterctrlbase.h"
#include "config/kcharacterdef.h"
#include "onlinegameworld/kplayer.h"
#include "onlinegameworld/korpgworld.h"
#include "luaplayervip.h"
#include "vipdef.h"


struct VipBuyCount
{
	INT nId;
	INT nCount;
};

#define VIP_FREE_EXP_LEVEL (2)	// vip����ȼ�2��
#define VIP_FREE_EXP_TIME (20 * 60)		// �������vipʱ�䣬20����

// Vip���鹦�ܽṹ
struct VipFreeExp
{
	DWORD dwFreeTime;	// �������ʱ��
	BYTE byRecVipLevel;		// �������ǰ��vip�ȼ�
};

struct VipSaveData
{
	INT nExp;
	VipFreeExp sFree;
	//INT arrViplevel[MAX_VIP_LEVEL];
	CHAR  szMsg[256];
	std::map<INT, VipBuyCount> mapVipCount;
};

class PlayerVip : public KCharacterCtrlBase
{
public:
	enum 
	{	emKCtrlId = emKCHARACTER_CTRL_VIP	};

	explicit PlayerVip(KCharacter& rcPlayer);
	~PlayerVip();

	virtual BOOL Init();

	virtual BOOL UnInit();

	virtual BOOL OnLogin();

	virtual BOOL OnLogout();

	virtual BOOL Active();

	// ����
	virtual BOOL OnDbLoad(LPCBYTE pData, SIZE_T uSize);

	// ����
	virtual BOOL OnDbSave(LPBYTE pBuffer, SIZE_T uBuffSize, SIZE_T& uUsedSize);

	LuaPlayerVip* GetScriptInterface() CONST;

	BOOL IsOpen(INT nId, BOOL bSendMsg);

	INT GetTotalBuyCount(INT nId);

	INT GetNowBuyCount(INT nId);

	INT GetRate(INT nId);


	BOOL SyncBuyCount();

	//BOOL SyncRecevie();
	BOOL AddExp(INT nCoins);

	INT GetExp();

	BOOL SyncExp();

	BOOL DoSync();

	BOOL DoRecevie(INT nVipLevel);

	BOOL DoBuyCount(INT nId, INT nNum);

	BOOL CanBuyCount(INT nId, INT nNum);

	BOOL DoAddDegree();

	BOOL DoAddDegree(INT nOldVipLevel, INT nNewVipLevel);

	BOOL RefreshSaveData();

	INT GetOverviewCoins(INT nTargetVipLevel);

	BOOL SyncFreeExpTime();

	BOOL GetOrSetMsg(INT nType,CHAR *szMsg);
public:
	BOOL IsFreeExpState(INT nNewVipLevel, INT& nOldVipLevel);

	VOID SetFreeVipState(DWORD dwFreeTime = 0);

	VOID ResetFreeState();

	VOID SetRecFreeVipLevel(INT nVipLevel);

	VOID DoGiveFirstRechargeReward();

private:
	KPlayer&						m_rcPlayer;

	VipSaveData						m_SaveData;

	LuaPlayerVip* m_pLunaObj;
};