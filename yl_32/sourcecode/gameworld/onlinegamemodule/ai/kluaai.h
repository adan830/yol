
//	��������	��	AI���ݽű��ӿ�

#pragma once


#include "onlinegamebase/kscriptmanager.h"

// -------------------------------------------------------------------------
class KAICtrl;
class KAIVM;
class KCharacter;

class KLuaAI : public QLunaBase
{
public:
	explicit  KLuaAI(KCharacter& rCharacter, KAICtrl* pAICtrl, KAIVM* pAIVM) :
	m_rCharacter(rCharacter), m_pAICtrl(pAICtrl), m_rAIVM(*pAIVM)	{}

	~KLuaAI() {}	

	static INT Register2Character(QLuaScript& sc, QLunaBase* pLunaObj);

	// �ű��ӿڶ���
	DECLARE_LUA_CLASS(KLuaAI);

	// AI ���
	INT		LuaSetAIType(QLuaScript& sc);
	INT		LuaGetAIType(QLuaScript& sc);

	INT		LuaFireAIEvent(QLuaScript& sc);

	INT		LuaGetAIOriginPos(QLuaScript& sc);
	INT		LuaSetAIOriginPos(QLuaScript& sc);

	INT		LuaGetAISelectSkill(QLuaScript& sc);

	INT		LuaGetAIEventSrcId(QLuaScript& sc);

	INT		LuaEnableDebug(QLuaScript &sc);
	INT		LuaSetPatrolPath(QLuaScript &sc);

	INT		LuaSetBattleZone(QLuaScript &sc);
private:
	KAICtrl*	m_pAICtrl;
	KAIVM&		m_rAIVM;
	KCharacter& m_rCharacter;
};
