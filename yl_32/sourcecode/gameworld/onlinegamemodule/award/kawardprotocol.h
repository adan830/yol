/* -------------------------------------------------------------------------
//	�ļ���		��	kawardprotocol.h
//	������		��	zhaoyu
//	����ʱ��	��	2013-08-14
//	��������	��  
// -------------------------------------------------------------------------*/

#pragma once

#include "awarddef.h"
#include "onlinegameworld/kprotocol.h"

#pragma pack(1)

enum KS2C_AWARD_PROTOCOL
{
	s2c_award_begin = 0, 

	s2c_sync_award,
	s2c_take_award_respond,
};

enum KC2S_AWARD_PROTOCOL
{
	c2s_award_begin = 0,

	c2s_take_award,
};

// s2c
struct KS2C_SYNC_AWARD : KLENPTC_HEADER<s2c_sync_award>
{
	DWORD dwId;

	INT nRankIdx;

	CHAR szModuleName[MAX_NAME_LEN];
	INT nLevel;

	INT nSilver;             // ������������
	INT nEnergy;                // ������������
	INT nFightingSpirit;     // ս�꽱������
	INT nPrestige;           // ��������

	INT nItemNum;

	KAwardItem Items[0];
};

struct KS2C_TAKE_AWARD_RESPOND : KPTC_HEADER<s2c_take_award_respond>
{
	DWORD dwId;
	BYTE bSucceed;
};


// c2s
struct KC2S_TAKE_AWARD : KPTC_HEADER<c2s_take_award>
{
	DWORD dwAwardId;
	CHAR  szModuleName[MAX_NAME_LEN];
};

#pragma pack()