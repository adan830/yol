
#ifndef __QESCORT_MGR_H__
#define __QESCORT_MGR_H__

#include "onlinegamemodule/kescortdef.h"

class KPlayer;

struct KeyValue
{
	int nKey;
	int nValue;
};

class KEscortManager
{
public:
	KEscortManager();
	~KEscortManager();

public:
	BOOL Init();
	void UnInit();

	void Activate();

public:
	BOOL OnStartEscortRequest(INT nPlayerId, DWORD dwProtectRoleId, INT nEscortLevel);

	INT GetEscortMembersNum() { return m_mapEscorts.size(); }

	INT GetRobEscortsMembersNum(INT nPlayerId);

	BOOL SerializeMemberEscorts(LPBYTE byData);

	BOOL SerializeRobEscorts(INT nPlayerId, LPBYTE byData);

	INT GetPlayerEscortState(INT nPlayerId);

	BOOL GetPlayerEscortInfo(INT nPlayerId, KPlayerEscort& sEscort);

	BOOL DoRefreshEscortPlayers();

	BOOL DoUpdatePlayerEscortState(INT nPlayerId);

	BOOL DoModifyRobState(INT nRobPlayerId, INT nRoberId);

private:
	std::map<DWORD, DWORD> m_mapNpc2Role;	// npcid��roleid��Ӧ��
	std::map<DWORD, DWORD> m_mapRole2Npc;
	std::map<DWORD, DWORD> m_mapNpc2Pets;  // Npc�ĳ���

	std::map<DWORD, KPlayerEscort> m_mapEscorts;

	std::map<DWORD, DWORD> m_mapRobPlayers;		// <���ټ���id, �ټ���id>

private:
	std::map<INT, INT> m_mapWatchTable;		// �����б�<nPlayerId, nWatch>�������б�

public:
	VOID AddPlayerToWatchTable(INT nPlayerId);

	VOID RemovePlayerFromWatchTable(INT nPlayerId);

	BOOL OnTakeEscortAwardRequest(INT nPlayerId);

private:
	typedef std::map<DWORD, KRobEscort> KMAP_ROB_ESCORT;		// <������id�������˽ṹ>

	std::map<DWORD, KMAP_ROB_ESCORT> m_mapRobEscorts;

public:
	BOOL OnRobEscortRequest(INT nPlayerId, INT nRobPlayerId);

	BOOL OnDelRobEscortRequest(INT nPlayerId, INT nRobPlayerId);

	BOOL OnTakeRobAwardRequest(INT nPlayerId, INT nRobPlayerId, BYTE byEscortLevel);

	BOOL OnSpeedUpEscortRequest(INT nPlayerId, BOOL bSpeedUp);
};

extern KEscortManager g_cEscortMgr;

#endif
