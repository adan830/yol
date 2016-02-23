

#include "stdafx.h"
#include "onlinegamebase/kscriptmanager.h"
#include "kcharacterhelper.h"
#include "onlinegameworld/kluacharacter.h"
#include "onlinegameworld/kluanpc.h"
#include "knpchelper.h"
#include "onlinegameworld/kcharactermgr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// -------------------------------------------------------------------------
namespace KCharacterScriptNameSpace
{
// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: --
// @LuaApiName		: ChangeCurrentMana
// @Description		: 
// @ReturnCode		: �ı�Character������
// @ArgumentFlag	: odd
// @ArgumentComment	: ���ı��Character����
// @ArgumentComment	: ���ӵľ���ֵ
// @ArgumentComment	: ���ӵ�ǧ�ֱ�
// @LuaMarkEnd
// -------------------------------------------------------------------------
	INT LuaChangeCurrentMana(QLuaScript& sc)
	{
		KLuaCharacter* pLuaCharacter = (KLuaCharacter*)sc.GetObj(1);
		KCharacter* pCharacter = pLuaCharacter->GetHim();
		g_cCharacterHelper.ChangeCurrentMana(*pCharacter, sc.GetInt(2), sc.GetInt(3));

		return 0;
	}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: --
// @LuaApiName		: SetCombatCamp
// @Description		: ����Character�Ļ�����Ӫ
// @ReturnCode		: 
// @ArgumentFlag	: od
// @ArgumentComment	: ���ı��Character����
// @ArgumentComment	: ��Ӫ����
// @LuaMarkEnd
// -------------------------------------------------------------------------
	INT LuaSetCombatCamp(QLuaScript& sc)
	{
		KLuaCharacter* pLuaCharacter = (KLuaCharacter*)sc.GetObj(1);
		KCharacter* pCharacter = pLuaCharacter->GetHim();
		g_cCharacterHelper.SetCombatCamp(*pCharacter, sc.GetInt(2));

		return 0;
	}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: --
// @LuaApiName		: IsAlliedCamp
// @Description		: �ж�2��Character����Ӫ�Ƿ��г
// @ReturnCode		: 
// @ArgumentFlag	: oo
// @ArgumentComment	: CharacterA
// @ArgumentComment	: CharacterB
// @LuaMarkEnd
// -------------------------------------------------------------------------
	INT LuaIsAlliedCamp(QLuaScript& sc)
	{
		KLuaCharacter* pLuaCharacterA = (KLuaCharacter*)sc.GetObj(1);
		KLuaCharacter* pLuaCharacterB = (KLuaCharacter*)sc.GetObj(2);

		//BYTE nCampA = pLuaCharacterA->GetHim()->GetCombatCamp(); by zzx
		//BYTE nCampB = pLuaCharacterB->GetHim()->GetCombatCamp();

		INT nAllied = 0;//nCampA > 0 && nCampB > 0 && abs(nCampA-nCampB) == (nCampA^nCampB); zzx
		sc.PushNumber(nAllied);

		return 1;
	}


	// -------------------------------------------------------------------------
	// @ClientSvr(C/S)	: 
	// @ClassName		: --
	// @LuaApiName		: Revive
	// @Description		: ����ָ����Character
	// @ReturnCode		: 
	// @ArgumentFlag	: odd
	// @ArgumentComment	: ��Ҫ����� Character Id
	// @ArgumentComment	: ������Ѫ
	// @ArgumentComment	: ��������
	// @LuaMarkEnd
	// -------------------------------------------------------------------------
	INT LuaRevive(QLuaScript& sc)
	{
		KLuaCharacter* pLuaCharacter = (KLuaCharacter*)sc.GetObj(1);
		ASSERT(pLuaCharacter && sc.GetInt(2) >= 0 && sc.GetInt(3) >= 0);

		g_cCharacterHelper.Revive(*pLuaCharacter->GetHim(), sc.GetInt(2), sc.GetInt(3), FALSE);
		return 0;
	}

	// -------------------------------------------------------------------------
	// @ClientSvr(C/S)	: 
	// @ClassName		: --
	// @LuaApiName		: ReduceLife
	// @Description		: �˺�����
	// @ReturnCode		: 
	// @ArgumentFlag	: ddd
	// @ArgumentComment	: Ŀ��id
	// @ArgumentComment	: �ͷ���id
	// @ArgumentComment	: �˺�ֵ
	// @LuaMarkEnd
	// -------------------------------------------------------------------------
	INT LuaReduceLife(QLuaScript& sc)
	{
		INT nCurrentLife = 0;
		KCharacter* pTarget = NULL;
		KCharacter* pCaster = NULL;
		INT nDamage = 0;

		pCaster =  g_cCharacterMgr.GetById(sc.GetInt(1));
		LOG_PROCESS_ERROR(pCaster);
		pTarget = g_cCharacterMgr.GetById(sc.GetInt(2));
		PROCESS_ERROR(pTarget);
		nDamage = sc.GetInt(3);
		LOG_PROCESS_ERROR(nDamage > 0);

		g_cCharacterHelper.OnHurt(*pTarget, *pCaster, nDamage);

		nCurrentLife = pTarget->GetCurrentLife();
		nCurrentLife = nCurrentLife - nDamage;
		if(nCurrentLife <= 0)
		{
			pTarget->SetCurrentLife(0);
			g_cCharacterHelper.OnDeath(*pTarget, *pCaster);
		}
		else
		{
			pTarget->SetCurrentLife(nCurrentLife);
		}
EXIT0:
		return 0;
	}

	// -------------------------------------------------------------------------
	// @ClientSvr(C/S)	: 
	// @ClassName		: --
	// @LuaApiName		: AddLife
	// @Description		: ��Ѫ����
	// @ReturnCode		: 
	// @ArgumentFlag	: ddd
	// @ArgumentComment	: Ŀ��id
	// @ArgumentComment	: �ͷ���id
	// @ArgumentComment	: ����ֵ
	// @LuaMarkEnd
	// -------------------------------------------------------------------------
	INT LuaAddLife(QLuaScript& sc)
	{
		INT nCurrentLife = 0;
		KCharacter* pTarget = NULL;
		KCharacter* pCaster = NULL;
		INT nRecover = 0;

		pCaster =  g_cCharacterMgr.GetById(sc.GetInt(1));
		LOG_PROCESS_ERROR(pCaster);
		pTarget = g_cCharacterMgr.GetById(sc.GetInt(2));
		LOG_PROCESS_ERROR(pTarget);
		nRecover = sc.GetInt(3);
		LOG_PROCESS_ERROR(nRecover > 0);

		nCurrentLife = pTarget->GetCurrentLife();
		LOG_PROCESS_ERROR(nCurrentLife > 0);

		nCurrentLife += nRecover;
		if(nCurrentLife > pTarget->GetMaxLife())
		{
			nCurrentLife = pTarget->GetMaxLife();
		}

		pTarget->SetCurrentLife(nCurrentLife);

		//g_cCharacterHelper.OnRecoverLife(*pTarget, *pCaster, nRecover);

EXIT0:
		return 0;
	}

	// -------------------------------------------------------------------------
	// @ClientSvr(C/S)	: 
	// @ClassName		: --
	// @LuaApiName		: OnRecoverLife
	// @Description		: ��Ѫ����
	// @ReturnCode		: 
	// @ArgumentFlag	: ddd
	// @ArgumentComment	: Ŀ��id
	// @ArgumentComment	: �ͷ���id
	// @ArgumentComment	: ����ֵ
	// @LuaMarkEnd
	// -------------------------------------------------------------------------
	INT LuaOnRecoverLife(QLuaScript& sc)
	{
		KCharacter* pTarget = NULL;
		KCharacter* pCaster = NULL;
		INT nRecover = 0;

		pCaster =  g_cCharacterMgr.GetById(sc.GetInt(1));
		LOG_PROCESS_ERROR(pCaster);
		pTarget = g_cCharacterMgr.GetById(sc.GetInt(2));
		LOG_PROCESS_ERROR(pTarget);
		nRecover = sc.GetInt(3);
		LOG_PROCESS_ERROR(nRecover > 0);

		g_cCharacterHelper.OnRecoverLife(*pTarget, *pCaster, nRecover);

EXIT0:
		return 0;
	}

	// -------------------------------------------------------------------------
	// @ClientSvr(C/S)	: 
	// @ClassName		: --
	// @LuaApiName		: ResetNpcIntensity
	// @Description		: ����NPCǿ��
	// @ReturnCode		: 
	// @ArgumentFlag	: od[d]
	// @ArgumentComment	: ��Ҫ����� npc Id
	// @ArgumentComment	: npcǿ��id
	// @ArgumentComment	: npc�ȼ�
	// @LuaMarkEnd
	// -------------------------------------------------------------------------
	INT LuaResetNpcIntensity(QLuaScript& sc)
	{
		INT nLevel = 0;
		INT nPropId = 0;

		KLuaNpc* pLuaNpc = (KLuaNpc*)sc.GetObj(1);
		ASSERT(pLuaNpc && sc.GetInt(2) >= 0);

		nPropId = sc.GetInt(2);
		ASSERT(nPropId > 0);

		if(sc.IsNumber(3))
			nLevel = sc.GetInt(3);
		g_cNpcHelper.ResetNpcIntensity((*pLuaNpc->GetHim()), nPropId, nLevel);
		return 0;
	}

	// -------------------------------------------------------------------------
	// @ClientSvr(C/S)	: 
	// @ClassName		: --
	// @LuaApiName		: GetNpcPropId
	// @Description		: ����NpcId���NpcPropId
	// @ReturnCode		: 
	// @ArgumentFlag	: d
	// @ArgumentComment	: NpcId
	// @LuaMarkEnd
	// -------------------------------------------------------------------------
	INT LuaGetNpcPropId(QLuaScript& sc)
	{
		INT nPropId = 0;

		nPropId = g_cNpcHelper.GetNpcPropId(sc.GetInt(1));
		ASSERT(nPropId > 0);

		sc.PushNumber(nPropId);
		return 1;
	}

	// -------------------------------------------------------------------------
	// @ClientSvr(C/S)	: 
	// @ClassName		: KLuaNpc
	// @LuaApiName		: GetNpcMatchLevel
	// @Description		: �õ���ָ��level��ƥ��ı���NPC�ĵȼ�
	// @ReturnCode		: 
	// @ArgumentFlag	: dd
	// @ArgumentComment	: Npc PropId
	// @ArgumentComment	: level
	// @LuaMarkEnd
	// -------------------------------------------------------------------------
	INT	LuaGetNpcMatchLevel(QLuaScript& sc)
	{
		INT nPropId = sc.GetInt(1);
		INT nLevel = sc.GetInt(2);
		sc.PushNumber(g_cNpcHelper.GetMatchLevel(nPropId, nLevel));
		return 1;
	}

	// -------------------------------------------------------------------------
	// @ClientSvr(C/S)	: 
	// @ClassName		: KLuaNpc
	// @LuaApiName		: GetNpcExp
	// @Description		: �õ�NPC���飨npc_prop���
	// @ReturnCode		: d
	// @ArgumentFlag	: dd
	// @ArgumentComment	: Npc PropId
	// @ArgumentComment	: level
	// @LuaMarkEnd
	// -------------------------------------------------------------------------
	INT	LuaGetNpcExp(QLuaScript& sc)
	{
		INT nPropId = sc.GetInt(1);
		INT nLevel = sc.GetInt(2);
		sc.PushNumber(g_cNpcHelper.GetNpcExp(nPropId, nLevel));
		return 1;
	}

	// -------------------------------------------------------------------------
	// @ClientSvr(C/S)	: 
	// @ClassName		: KLuaNpc
	// @LuaApiName		: GetNpcExpType
	// @Description		: �õ�NPC������䷽ʽ��npc_prop���
	// @ReturnCode		: d
	// @ArgumentFlag	: dd
	// @ArgumentComment	: Npc PropId
	// @ArgumentComment	: level
	// @LuaMarkEnd
	// -------------------------------------------------------------------------
	INT	LuaGetNpcExpType(QLuaScript& sc)
	{
		INT nPropId = sc.GetInt(1);
		INT nLevel = sc.GetInt(2);
		sc.PushNumber(g_cNpcHelper.GetNpcExpType(nPropId, nLevel));
		return 1;
	}

#include "kcharacterscript_table.hpp"
}

BOOL g_RegisterKCharacterScriptFun()
{
	return g_cScriptManager.RegisterTableFuncs("KCharacter", KCharacterScriptNameSpace::arFunction, countof(KCharacterScriptNameSpace::arFunction));
}


// -------------------------------------------------------------------------
