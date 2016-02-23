/* -------------------------------------------------------------------------
//	�ļ���		��	gameworld/rpg/onlinegamemodule/trade/kpurseprotocol.h
//	������		��	zhangzhixiong
//	����ʱ��	��	2012-9-29
//	��������	��	
//
// -----------------------------------------------------------------------*/
#ifndef __GAMEWORLD_RPG_ONLINEGAMEMODULE_TRADE_SHOP_H__
#define __GAMEWORLD_RPG_ONLINEGAMEMODULE_TRADE_SHOP_H__

#include "onlinegameworld/kprotocol.h"
#include "onlinegamemodule/trade/kpurseprotocoldef.h"

enum KE_SHOP_C2S_PROTOCOL
{
	emSHOP_PTC_C2S_SYNC_BUYITEM,	// �������
	emSHOP_PTC_C2S_SYNC_SELLITEM,
	emSHOP_PTC_C2S_SYNC_DISCOUNT,
	emSHOP_PTC_C2S_COUNT,
};

enum KE_SHOP_S2C_PROTOCOL
{
	emSHOP_PTC_S2C_SYNC_DISCOUNT,
	emSHOP_PTC_S2C_SYNC_ALL_PURCHASE,
	emSHOP_PTC_S2C_SYNC_MY_PURCHASE,
	emSHOP_PTC_S2C_COUNT,
};


#pragma pack(push, 1)

struct KPLAYER_BUY_ITEM_SYNC : KPTC_HEADER<emSHOP_PTC_C2S_SYNC_BUYITEM>
{
	INT         nShopId;        // �̵�ID
	BYTE		byCategoryId;	// ��ǩID
	BYTE		byBuyIdx;		// ��ڼ�������
	WORD		wCount;			// ���������
};

struct KPLAYER_SELL_ITEM_SYNC : KPTC_HEADER<emSHOP_PTC_C2S_SYNC_SELLITEM>
{
	INT         nShopId;        // �̵�ID
	DWORD		dwId;			// ��ƷID
	WORD		wCount;			// Ҫ����NPC����Ʒ������
};

struct KSHOP_C2S_DISCOUNT_SYNC : KPTC_HEADER<emSHOP_PTC_C2S_SYNC_DISCOUNT>
{
	INT nShopId;
	INT nCategoryId;
};

struct KSHOP_DISCOUNT_INFO
{
	INT nDiscount;
	INT nTime;
};

struct KSHOP_S2C_DISCOUNT_SYNC : KLENPTC_HEADER<emSHOP_PTC_S2C_SYNC_DISCOUNT>
{
	INT nCount;
	KSHOP_DISCOUNT_INFO arrInfo[0];
};

struct KSHOP_PURCHASE_RECORD
{
	INT nShopId;
	INT nCategoryId;
	INT nGoodsId;		
	INT nCount;	//�Լ��Ѿ����������(����)		
	//DWORD dwRoleId;
	DWORD dwLastTime;
	INT nTotal;//�Ѿ���������(ȫ��)
	INT nMaxCount;//�������(ȫ��)
};

struct KSHOP_S2C_ALL_PURCHASE_SYNC : KLENPTC_HEADER<emSHOP_PTC_S2C_SYNC_ALL_PURCHASE>
{
	INT nCount;
	KSHOP_PURCHASE_RECORD arrInfo[0];
};

struct KSHOP_S2C_MY_PURCHASE_SYNC : KLENPTC_HEADER<emSHOP_PTC_S2C_SYNC_MY_PURCHASE>
{
	INT nCount;
	KSHOP_PURCHASE_RECORD arrInfo[0];
};

#pragma pack(pop)

#endif