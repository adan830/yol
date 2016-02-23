/* -------------------------------------------------------------------------
//	�ļ���		��	kgclogicbasescript.cpp
//	������		��	simon
//	����ʱ��	��	2010/12/31 11:25:28
//	��������	��	
//
// -----------------------------------------------------------------------*/

#include "stdafx.h"
#include "onlinegamebase/kscriptmanager.h"
#include "GameCenter.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// -------------------------------------------------------------------------



// -------------------------------------------------------------------------

namespace KGcLogicBaseScriptNameSpace
{
// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: --
// @LuaApiName		: GlobalExecute
// @Description		: Զ��������GameServer���ýű�ָ��
// @ReturnCode		: ���ͳɹ���1������ʧ�ܣ�0
// @ArgumentFlag	: {s}[d]
// @ArgumentComment	: arg:Ҫ���õĺ����������ŵ��ò�����Table���
// @ArgumentComment	: [��ѡ] ָ��gs
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT LuaGlobalExecute(QLuaScript& sc)
{
	INT nRetCode = 0;
	INT nServerConnIdx = -1;
	static BYTE byBuff[60000];

	ZeroStruct(byBuff);

	if (sc.GetTopIndex() >= 2)
		nServerConnIdx = sc.GetInt(2);

	nRetCode = sc.SaveValue2Buffer(byBuff, sizeof(byBuff), 1);
	LOG_PROCESS_ERROR(nRetCode > 0);

	if (nServerConnIdx == 0)
	{
		sc.OutPutErrMsgF("params error!!!nServerConnIdx\n");
	}

	nRetCode = g_pGameCenter->m_GameServer.DoRemoteLuaCall(nServerConnIdx, byBuff, nRetCode);
	LOG_PROCESS_ERROR(nRetCode);

EXIT0:
	sc.PushNumber(nRetCode);
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: --
// @LuaApiName		: CreateSystemTeam
// @Description		: ����ϵͳ���鲢����ָ����ɫ
// @ReturnCode		: SystemTeamId
// @ArgumentFlag	: d[dddd]
// @ArgumentComment	: һ����������Id ��Ϊ��Ա
// @ArgumentComment	: ͬ��
// @ArgumentComment	: ͬ��
// @ArgumentComment	: ͬ��
// @ArgumentComment	: ͬ��
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT LuaCreateSystemTeam(QLuaScript& sc)
{
	INT nPlayerCount = sc.GetTopIndex();
	DWORD dwTeamId = 0;
	KTeam* pTeam = NULL;

	dwTeamId = g_pGameCenter->m_TeamCenter.CreateTeam(TRUE);
	LOG_PROCESS_ERROR(dwTeamId);
 
	pTeam = g_pGameCenter->m_TeamCenter.GetTeam(dwTeamId);
	LOG_PROCESS_ERROR(pTeam);

	for (INT i = 1; i <= nPlayerCount; ++i)
	{
		DWORD dwPlayerId = sc.GetInt(i);
		KRole*  pRole   = NULL;

		pRole = g_pGameCenter->m_RoleManager.GetRole(dwPlayerId);
		QCONFIRM_CONTINUE(pRole);

		if (pRole->m_dwSystemTeamID != KD_BAD_ID)
		{
			g_pGameCenter->m_TeamCenter.DelMember(pRole->m_dwSystemTeamID, pRole->m_dwPlayerID);
		}

		if (pRole->GetTeamId() != KD_BAD_ID)
		{
			g_pGameCenter->m_TeamCenter.DelMember(pRole->GetTeamId(), pRole->m_dwPlayerID);
		}

		g_pGameCenter->m_TeamCenter.AddMember(dwTeamId, dwPlayerId, 1);
		g_pGameCenter->m_TeamCenter.ProcessTeam(dwTeamId, pTeam);
	}

EXIT0:
	sc.PushNumber(dwTeamId);
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: --
// @LuaApiName		: GetMapPlayerCount
// @Description		: �õ���ͼ����Ҹ���
// @ReturnCode		: 
// @ArgumentFlag	: d
// @ArgumentComment	: ��ͼid
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT LuaGetMapPlayerCount(QLuaScript& sc)
{
	INT nPlayerCount = 0;
	INT nMapId = sc.GetInt(1);
	KMapInfo* pMapInfo = g_pGameCenter->m_MapManager.GetMapInfo(nMapId);
	LOG_PROCESS_ERROR(pMapInfo);

	nPlayerCount = pMapInfo->m_nPlayerCount;

EXIT0:
	sc.PushNumber(nPlayerCount);
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: --
// @LuaApiName		: GetPlayerIdByName
// @Description		: ͨ�����ֻ�ȡ���ID
// @ReturnCode		: playerId
// @ArgumentFlag	: s
// @ArgumentComment	: �������
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT LuaGetPlayerIdByName(QLuaScript& sc)
{
	LPCSTR	pcszName = sc.GetStr(1);
	DWORD	dwPlayerId = 0;
	KRole*	pRole = g_pGameCenter->m_RoleManager.GetRole(pcszName);
	if (pRole)
	{
		dwPlayerId = pRole->m_dwPlayerID;
	}

	sc.PushNumber(dwPlayerId);
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: --
// @LuaApiName		: GetRoleInfoById
// @Description		: ͨ��id��ȡ�����Ϣ
// @ReturnCode		: 
// @ArgumentFlag	: d
// @ArgumentComment	: ���id
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT LuaGetRoleInfoById(QLuaScript& sc)
{
	INT     nPlayerId = sc.GetInt(1);
	DWORD	dwPlayerId = 0;
	KRole*	pRole = g_pGameCenter->m_RoleManager.GetRole(nPlayerId);
	if (pRole)
	{
		sc.PushTable();

		sc.PushString(pRole->getAccount());
		sc.SetTableField("szAccount");

		sc.PushNumber(pRole->getLevel());
		sc.SetTableField("nLevel");

		sc.PushString(pRole->getName());
		sc.SetTableField("szName");

		sc.PushNumber(pRole->m_nFightScore);
		sc.SetTableField("nFightScore");

		return 1;
	}
	
	return 0;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: --
// @LuaApiName		: GetRankIdByIdx
// @Description		: �õ�ĳ�����а����еڼ���id
// @ReturnCode		: 
// @ArgumentFlag	: dd
// @ArgumentComment	: ���а�����
// @ArgumentComment	: �ڼ���(start from 0)
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT LuaGetRankIdByIdx(QLuaScript& sc)
{
	INT nRankId = sc.GetInt(1);
	INT nRankIdx = sc.GetInt(2);
	DWORD dwId = 0;

	KRankPool* pRankPool = g_pGameCenter->m_RankManager.GetRankPool(nRankId);
	LOG_PROCESS_ERROR(pRankPool);

	dwId = pRankPool->GetIdByIdx(nRankIdx);

	sc.PushNumber(dwId);
EXIT0:
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: --
// @LuaApiName		: IsPlayerOnLine
// @Description		: ��֤����Ƿ�����
// @ReturnCode		: ����1������0
// @ArgumentFlag	: d
// @ArgumentComment	: ���ID
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT LuaIsPlayerOnLine(QLuaScript& sc)
{
	INT bOnLine = 0;
	DWORD dwPlayerID = sc.GetInt(1);
	KRole* pRole = g_pGameCenter->m_RoleManager.GetRole(dwPlayerID);
	if (pRole && pRole->IsOnline())
		bOnLine = 1;

	sc.PushNumber(bOnLine);
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: --
// @LuaApiName		: Quit
// @Description		: �����������˳�
// @ReturnCode		: ��
// @ArgumentFlag	: 
// @ArgumentComment	: 
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT LuaQuit(QLuaScript& sc)
{
	g_pGameCenter->Quit();
	return 0;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: --
// @LuaApiName		: SaveAll
// @Description		: CR����
// @ReturnCode		: ��
// @ArgumentFlag	: 
// @ArgumentComment	: 
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT LuaSaveAll(QLuaScript& sc)
{
	g_pGameCenter->OnRegularSaveProcess();
	return 0;
}


#include "gclogicbasescript_table.hpp"
};

BOOL g_RegisterGcLogicBaseScriptFun()
{
	return g_cScriptManager.RegisterTableFuncs("_G",
		KGcLogicBaseScriptNameSpace::arFunction, countof(KGcLogicBaseScriptNameSpace::arFunction));
}
