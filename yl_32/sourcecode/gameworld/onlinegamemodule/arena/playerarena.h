#pragma once

#include "stdafx.h"
#include "onlinegameworld/kplayer.h"
#include "onlinegameworld/kcharacterctrlbase.h"
#include "LuaPlayerArena.h"
#include "arenadef.h"
#include "config/kplayerbasedbdef.h"

class PlayerArena  : public KCharacterCtrlBase
{
public:
	enum 
	{	emKCtrlId = emKCHARACTER_CTRL_PLAYER_ARENA	};


	PlayerArena(KCharacter& rcPlayer);
	~PlayerArena();

	virtual BOOL Init();

	virtual BOOL UnInit();

	virtual BOOL OnLogin();

	virtual BOOL OnLogout();

	virtual BOOL Active();

	// ����
	virtual BOOL OnDbLoad(LPCBYTE pData, SIZE_T uSize);

	// ����
	virtual BOOL OnDbSave(LPBYTE pBuffer, SIZE_T uBuffSize, SIZE_T& uUsedSize);
	
	LuaPlayerArena* GetScriptInterface() CONST { return m_pLunaObj; }

private:
	KPlayer&		 m_rcPlayer;

	LuaPlayerArena* m_pLunaObj;


	INT m_nRankIdx;		// �Լ��ھ�����������

	BOOL m_bFirstLogin;

	BOOL m_bFrontArenaNpcsMode;				// ģʽtrue����ʾǰ������ģʽfalse����ʾ���ǰ5
	std::map<DWORD, INT> m_mapRankPos;		// ��ɫid�;�������λ�ö�Ӧ λ�ô�1��ʼ��   0���������λ��, ����Խ�ߣ�posԽ��,   ʵ�ִ����ң��Ӵ�С
	std::map<DWORD, INT> m_mapRankIdx;		// ��ɫid�������Ķ�Ӧ ������0��ʼ

	std::map<DWORD, DWORD> m_mapNpc2Role;	// npcid��roleid��Ӧ��
	std::map<DWORD, DWORD> m_mapRole2Npc;
	std::map<DWORD, DWORD> m_mapNpc2Pets;  // Npc�ĳ���

	typedef std::map<DWORD, KDelayRoleData> KMAP_DELAY_DATA;
	KMAP_DELAY_DATA m_mapDelayData;

private:
	DWORD GetRoleIdByNpcId(DWORD dwNpcId);

	DWORD GetNpcIdByRoleId(DWORD dwRoleId);

	DWORD GetPetNpcIdByRoleNpcId(DWORD dwRoleNpcId);

	INT GetRankIdxByRoleId(DWORD dwRoleId);

	INT GetSkillIdOfCurrRound(INT nRound, INT nRoute);

	KDelayRoleData* GetDelayDataById(DWORD dwRoleId);

	VOID CalChallengeCDTime(INT nChallengeTime);

	VOID ProcessRankChangedWhenChallenge();

	VOID SetRankPos(DWORD dwRoleId, INT nRankIdx);

public:
	BOOL AddArenaRank();

	BOOL ClearNpcs();

	BOOL ResetData(); 

	BOOL StartArena();  // ���뾺����ʱ����
	
	BOOL RefreshArenaPlayers();

	BOOL DoLoadArenaPlayers();

	BOOL DoLoadFrontArenaPlayers();

	BOOL DoGetPlayerIdxRequest(DWORD dwSrcPlayerId, DWORD dwRoleId);

	BOOL OnGetPlayerIdxRespond(DWORD dwRoleId, INT nRankIdx);

	BOOL OnGetPlayerIdRespond(DWORD dwRholeId, INT nRankIdx);

	BOOL OnLoadDelayRoleDataRespond(DWORD dwSrcId, DWORD dwRoleId, KDelayRoleData* pDelayData);

	BOOL CreateArenaNpc(DWORD dwRoleId, INT nPos, KDelayRoleData* pDelayData);

	BOOL OnSwapRankRespond(BOOL bSucceed);

private:
	DWORD m_dwPlayerRoleId;  // ���ǵ�npc����ID
	DWORD m_dwCurrentFightRoleId;
	BOOL m_bFightResult;
	BOOL m_bCheckedAreaRecordFightResult; // �Ƿ���������ڼ��ս����¼����ʤ��0��
	INT m_nWinCombo;	   // ��ʤ����
    INT m_nFailCombo;      // ���ܴ���
	INT m_nFightNum;       // ս������
	INT m_nCurrChallengeCDTime;  //��ǰCDʱ��

	DWORD m_dwLastTakeAwardTime;		// ��һ����ȡ����������ʱ��
	INT m_nTakeComboAward;		// ������ȡ��ʤ��������ʤ����

	INT m_nCDTime;		// ��սCD

	// ����ս�����̼�¼
	std::list<KATTACK_RECORD> m_RecordList;

public:
	BOOL OnFightRequest(DWORD dwNpcId);

	BOOL DoFightProcess();

	BOOL SyncFightProcess();

	BOOL SyncArenaInfo();

	BOOL SyncAddNpc(DWORD dwRoleId, DWORD dwNpcId, DWORD dwPetNpcId,  INT nPos, BOOL bCanFight);

	INT GetCDTime() { return m_nCDTime; }

	VOID SetCDTime(INT nTime) { m_nCDTime = nTime; }

	VOID SetTakeAwardTime(DWORD dwTime) { m_dwLastTakeAwardTime = dwTime; }

	VOID SetWinCombo(INT nWinCombo){ m_nWinCombo = nWinCombo; }
	INT GetWinCombo() { return m_nWinCombo; }

	INT GetTakeComboAward() { return m_nTakeComboAward; }

	VOID SetTakeComboAward(INT nCombo) { m_nTakeComboAward = nCombo; }

private:
	struct KArenaSaveData
	{
		DWORD dwLastTakeAwardTime;
		WORD wCDTime;
		BYTE byTakeComboAward;
		WORD wCurrentChallengeCDTime;
		WORD wFightNum;
        BYTE byWinCombo;
	};

private:
	// ��Ҿ�����ս����¼
	std::vector<KArenaRecord> m_vecArenaRecord;

public:
	BOOL OnLoadRecordRespond(BYTE* pRecordData, size_t uRecordDataLen);
	BOOL SyncArenaRecord();
};
