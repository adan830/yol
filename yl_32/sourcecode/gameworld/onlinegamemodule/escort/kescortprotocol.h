
#ifndef	__QESCORTPROTOCOL_H__
#define __QESCORTPROTOCOL_H__

#include "onlinegameworld/kprotocol.h"
#include "onlinegamemodule/kescortdef.h"

#pragma pack(1)
enum KC2S_ESCORT_PROTOCOL
{
	c2s_refresh_escorts_request,		// ˢ�³��������
	c2s_start_escort_request,
	c2s_take_escort_award_request,
	c2s_rob_escort_request,
	c2s_del_rob_escort_request,
	c2s_take_rob_award_request,
	c2s_rob_fight_request,
	c2s_rescue_fight_request,
	c2s_rescue_player_request,
};

enum KS2C_ESCORT_PROTOCOL
{
	s2c_sync_escort_members,
	s2c_sync_add_escort_npc,
	s2c_sync_remove_escort_npc,
	s2c_sync_add_escort_selfnpc,
	s2c_sync_rob_escort_members,
	s2c_update_escort_state,
	s2c_sync_escort_members_end,//ͬ�����
	s2c_sync_rob_escort_members_end,//ͬ��rob���
};

struct KC2S_REFRESH_ESCORTS_REQUEST : KPTC_HEADER<c2s_refresh_escorts_request>
{
	INT nPlayerId;
	BYTE byPage;		// ҳ��
	BYTE byRefresh;
};

struct KC2S_TAKE_ESCORT_AWARD_REQUEST : KPTC_HEADER<c2s_take_escort_award_request>
{
	
};

struct KC2S_TAKE_ROB_AWARD_REQUEST : KPTC_HEADER<c2s_take_rob_award_request>
{
	INT nRobPlayerId;
	BYTE byRobEscortLevel;
};

struct KC2S_START_ESCORT_REQUEST : KPTC_HEADER<c2s_start_escort_request>
{
	INT nProtectRoleId;
};

struct KC2S_ROB_ESCORT_REQUEST : KPTC_HEADER<c2s_rob_escort_request>
{
	INT nRobPlayerId;	// ��������
};

struct KC2S_DEL_ROB_ESCORT_REQUEST : KPTC_HEADER<c2s_del_rob_escort_request>
{
	INT nPlayerId;		// ������
	INT nRobPlayerId;	// ��������
};

struct KC2S_ROB_FIGHT_REQUEST : KPTC_HEADER<c2s_rob_fight_request>
{
	INT nRobPlayerId;	// ��������
};

struct KC2S_RESCUE_FIGHT_REQUEST : KPTC_HEADER<c2s_rescue_fight_request>
{
	INT nRobPlayerId;	// ��������
};

struct KC2S_RESCUE_PLAYER_REQUEST : KPTC_HEADER<c2s_rescue_player_request>
{
	INT nPlayerId;	// ��������
};

struct KS2C_SYNC_ESCORT_MEMBERS : KLENPTC_HEADER<s2c_sync_escort_members>
{
	BYTE byCurEscortPage;
	BYTE byTotalEscortPage;
	INT nMembersNum;
	KPlayerEscort aryEscorts[0];
};

//ͬ�����
struct KS2C_SYNC_ESCORT_MEMBERS_END : KLENPTC_HEADER<s2c_sync_escort_members_end>
{
	INT nTotalNumber;
};
//ͬ�����
struct KS2C_SYNC_ROB_MEMBERS_END : KLENPTC_HEADER<s2c_sync_rob_escort_members_end>
{
	INT nTotalNumber;
};


struct KS2C_SYNC_ROB_MEMBERS : KLENPTC_HEADER<s2c_sync_rob_escort_members>
{
	INT nMembersNum;
	KRobEscort aryRobEscorts[0];
};

struct KS2C_ESCORT_ADD_NPC : KPTC_HEADER<s2c_sync_add_escort_npc>
{
	DWORD dwMappingRoleId;
	DWORD dwNpcId;
	DWORD dwPetNpcId;
	BYTE byPos;
	BYTE byCanFight;
};

struct KS2C_ESCORT_REMOVE_NPC : KPTC_HEADER<s2c_sync_remove_escort_npc>
{
	DWORD dwNpcId;
	BYTE byIsPet;
};

struct KS2C_ESCORT_ADD_SELF_NPC : KPTC_HEADER<s2c_sync_add_escort_selfnpc>
{
	DWORD dwMappingRoleId;
	DWORD dwNpcId;
	DWORD dwPetNpcId;
};

struct KS2C_UPDATE_ESCORT_STATE : KPTC_HEADER<s2c_update_escort_state>
{
	INT nPlayerId;
	BYTE byEscortState;
	INT nLeftTime;
	DWORD dwRoberId;
	DWORD dwRoberFightscore;
	CHAR szRoberName[_NAME_LEN];
};


#pragma pack()

#endif
