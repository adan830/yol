
#pragma once

// -------------------------------------------------------------------------

#include "kmagicattrib.h"
//#include "knpcattribgroup.h"
//#include "knpc.h"
//#include "kmath.h"

class KNpc;

////	���Ժ����� - �ṩ����ĺ�������
//class KMagicAttribGroup
//{
//public:
//	static VOID DebugMsgReceiveMagic(KNpc& npc, CONST KMagicAttrib& magic, INT nSkillId);
//};


enum DAMAGE_TYPE
{
	damage_physics = 0,		// �����˺�
	damage_fire,			// �����˺�
	damage_cold,			// �����˺�
	damage_light,			// �����˺�
	damage_poison,			// �����˺�
	damage_magic,			// �������˺�
	damage_return,			// �����˺�
	damage_num,				// �˺�������Ŀ
};

// TODO:liuchang 0��ò��ã���KFightSkill::CoverAppendStateMagicType2State
enum KE_STATE
{
	emSTATE_INVALID = -1,
	emSTATE_BEGIN = 0,
	emSTATE_SERISE_BEGIN = emSTATE_BEGIN,
	emSTATE_HURT = emSTATE_SERISE_BEGIN,	// ���˶���״̬(��)
	emSTATE_WEAK,		// ����״̬(ľ)
	emSTATE_SLOWALL,	// �ٻ�״̬(ˮ)
	emSTATE_BURN,		// ����״̬(��)
	emSTATE_STUN,		// ѣ��״̬(��)
	emSTATE_SERISE_END = emSTATE_STUN,

	// ����״̬
	emSTATE_SPECIAL_BEGIN,
	emSTATE_FIXED = emSTATE_SPECIAL_BEGIN,	// ����״̬
	emSTATE_PALSY,		// ���״̬
	emSTATE_SLOWRUN,	// ������״̬
	emSTATE_FREEZE,		// ����״̬
	emSTATE_CONFUSE,	// ����״̬
	emSTATE_KNOCK,		// ����״̬
	emSTATE_DRAG,		// ����״̬
	emSTATE_SILENCE,	// ��Ĭ״̬
	emSTATE_ZHICAN,		//�²�״̬
	emSTATE_FLOAT,		//����״̬
	emSTATE_SPECIAL_END = emSTATE_FLOAT,

	emSTATE_NUM,		// count

	// ʣ�µ�״̬���������Դ����������������ʡ��ӳ�֮��
	emSTATE_POISON	= emSTATE_NUM,	// �ж�״̬
	emSTATE_HIDE,					// ����״̬
	emSTATE_SHIELD,					// ����״̬
	emSTATE_SUDDENDEATH,			// ���״̬
	emSTATE_IGNORETRAP,				// ����������״̬

	emSTATE_ALLNUM,		// all count
};

// ħ�������� - �˺�
template <DAMAGE_TYPE emDamageTypeT>
class KMagicAttribGroup_Damage
{
public:
	//static VOID ModEnhanceDamage(KNpcSkillData& rcNpcSkillData, CONST KMagicAttrib& magic, INT nSkillId)
	//{
	//	rcNpcSkillData.GetDamage(emDamageTypeT).AddEnhanceDamage(magic.nValue[0]);	// ����׷���⹦�˺�ֵ
	//	KMagicAttribGroup::DebugMsgReceiveMagic(rcNpcSkillData.GetNpc(), magic, nSkillId);
	//}
	//static VOID ModEnhanceMagic(KNpcSkillData& rcNpcSkillData, CONST KMagicAttrib& magic, INT nSkillId)
	//{
	//	rcNpcSkillData.GetDamage(emDamageTypeT).AddEnhanceMagic(magic.nValue[0]);	// ����׷���ڹ��˺�ֵ
	//	KMagicAttribGroup::DebugMsgReceiveMagic(rcNpcSkillData.GetNpc(), magic, nSkillId);
	//}
	//static VOID ModResist(KNpcSkillData& rcNpcSkillData, CONST KMagicAttrib& magic, INT nSkillId)
	//{
	//	rcNpcSkillData.GetDamage(emDamageTypeT).AddCurResist(magic.nValue[0]);			// ���ӻ�������ֵ
	//	KMagicAttribGroup::DebugMsgReceiveMagic(rcNpcSkillData.GetNpc(), magic, nSkillId);
	//}
	//static VOID ModReceivePercent(KNpcSkillData& rcNpcSkillData, CONST KMagicAttrib& magic, INT nSkillId)
	//{
	//	rcNpcSkillData.GetDamage(emDamageTypeT).AddReceivePercent(magic.nValue[0]);	// �����ܵ��˺��ٷֱ�
	//	KMagicAttribGroup::DebugMsgReceiveMagic(rcNpcSkillData.GetNpc(), magic, nSkillId);
	//}
};


// ħ�������� - ״̬
// nAttribIdBeginT Ϊ״̬��ĵ�һ��ħ������Id��ʼ
// enNpcStateTΪ״̬ö��
template <KE_STATE emNpcStateT, CONST INT nAttribIdBeginT>
class KMagicAttribGroup_State
{
public:
	enum KE_MAGIC_ATTRIB
	{
		emMAGIC_ATTRIB_ATTACK,
		emMAGIC_ATTRIB_RESISTTIME,
		emMAGIC_ATTRIB_RESISTRATE,
		emMAGIC_ATTRIB_ATTACKTIME,
		emMAGIC_ATTRIB_ATTACKRATE,
		emMAGIC_ATTRIB_RESISTTIMERATE,
		emMAGIC_ATTRIB_ATTACKTIMERATE,
		emMAGIC_ATTRIB_CLEAR,
		emMAGIC_ATTRIB_IGNORE,
		emMAGIC_ATTRIB_NUM,
	};
public:
	// ��ȡħ��������ʼID
	static INT GetAttribIdBegin()
	{ return nAttribIdBeginT; }

	// ������������������
	static BOOL AddDesc(LPCSTR apszSetting[], LPCSTR pszBaseName)
	{
		if (!pszBaseName || !pszBaseName[0])
			return FALSE;

		static CHAR szNameBuf[emMAGIC_ATTRIB_NUM][128];
		INT nBaseNameLen	= QStrLen(pszBaseName);
		if (nBaseNameLen + 20 >= countof(szNameBuf[0]))	// Ԥ������20�ַ��Ӻ�׺
			return FALSE;

		LPCSTR apszSuffix[emMAGIC_ATTRIB_NUM]	=
		{
			"_attack",
			"_resisttime",
			"_resistrate",
			"_attacktime",
			"_attackrate",
			"_resisttimerate",
			"_attacktimerate",
			"_clear",
			"_ignore",
		};

		for (INT i = 0; i < emMAGIC_ATTRIB_NUM; i++)
		{
			QStrCpy(szNameBuf[i], pszBaseName);
			QStrCpy(szNameBuf[i] + nBaseNameLen, apszSuffix[i]);
			apszSetting[nAttribIdBeginT + i]	= szNameBuf[i];
		}

		return TRUE;
	}

	//// �����Դ�������������
	//static VOID AddModifyFunc(KF_NPC_ATTRIBMODIFY afnProcessFunc[])
	//{
	//	afnProcessFunc[nAttribIdBeginT + emMAGIC_ATTRIB_RESISTTIME]		= &_ModifyFuncT<ReceiveMagic_ResistTime>;
	//	afnProcessFunc[nAttribIdBeginT + emMAGIC_ATTRIB_RESISTRATE]		= &_ModifyFuncT<ReceiveMagic_ResistRate>;
	//	afnProcessFunc[nAttribIdBeginT + emMAGIC_ATTRIB_ATTACKTIME]		= &_ModifyFuncT<ReceiveMagic_AttackTime>;
	//	afnProcessFunc[nAttribIdBeginT + emMAGIC_ATTRIB_ATTACKRATE]		= &_ModifyFuncT<ReceiveMagic_AttackRate>;
	//	afnProcessFunc[nAttribIdBeginT + emMAGIC_ATTRIB_RESISTTIMERATE]	= &_ModifyFuncT<ReceiveMagic_ResistTimeRate>;
	//	afnProcessFunc[nAttribIdBeginT + emMAGIC_ATTRIB_ATTACKTIMERATE]	= &_ModifyFuncT<ReceiveMagic_AttackTimeRate>;
	//	afnProcessFunc[nAttribIdBeginT + emMAGIC_ATTRIB_CLEAR]			= &_ModifyFuncT<ReceiveMagic_Clear>;
	//	afnProcessFunc[nAttribIdBeginT + emMAGIC_ATTRIB_IGNORE]			= &_ModifyFuncT<ReceiveMagic_Ignore>;
	//}

protected:
	//template <VOID (*fnModifyT)(KNpcSkillData&, KNpcAttribGroup_State&, CONST KMagicAttrib&, INT nSkillId, INT nState)>
	//static VOID _ModifyFuncT(KNpcSkillData& rcNpcSkillData, CONST KMagicAttrib& magic, INT nSkillId)
	//{
	//	(*fnModifyT)(rcNpcSkillData, rcNpcSkillData.GetSpecialState(emNpcStateT), magic, nSkillId, emNpcStateT);
	//	KMagicAttribGroup::DebugMsgReceiveMagic(rcNpcSkillData.GetNpc(), magic, nSkillId);
	//}

	//static VOID ReceiveMagic_ResistTime(KNpcSkillData &rcNpcSkillData, KNpcAttribGroup_State& attrgrp, CONST KMagicAttrib& magic, INT nSkillId, INT nState)
	//{ attrgrp.AddResistTime(magic.nValue[0]); }
	//static VOID ReceiveMagic_ResistRate(KNpcSkillData &rcNpcSkillData, KNpcAttribGroup_State& attrgrp, CONST KMagicAttrib& magic, INT nSkillId, INT nState)
	//{ attrgrp.AddResistRate(magic.nValue[0]); }
	//static VOID ReceiveMagic_AttackTime(KNpcSkillData &rcNpcSkillData, KNpcAttribGroup_State& attrgrp, CONST KMagicAttrib& magic, INT nSkillId, INT nState)
	//{ attrgrp.AddAttackTime(magic.nValue[0]); }
	//static VOID ReceiveMagic_AttackRate(KNpcSkillData &rcNpcSkillData, KNpcAttribGroup_State& attrgrp, CONST KMagicAttrib& magic, INT nSkillId, INT nState)
	//{ attrgrp.AddAttackRate(magic.nValue[0]); }
	//static VOID ReceiveMagic_ResistTimeRate(KNpcSkillData &rcNpcSkillData, KNpcAttribGroup_State& attrgrp, CONST KMagicAttrib& magic, INT nSkillId, INT nState)
	//{
	//	attrgrp.AddResistTime(magic.nValue[0]);
	//	attrgrp.AddResistRate(magic.nValue[2]);
	//}
	//static VOID ReceiveMagic_AttackTimeRate(KNpcSkillData &rcNpcSkillData, KNpcAttribGroup_State& attrgrp, CONST KMagicAttrib& magic, INT nSkillId, INT nState)
	//{
	//	attrgrp.AddAttackTime(magic.nValue[0]);
	//	attrgrp.AddAttackRate(magic.nValue[2]);
	//}
	//static VOID ReceiveMagic_Clear(KNpcSkillData &rcNpcSkillData, KNpcAttribGroup_State& attrgrp, CONST KMagicAttrib& magic, INT nSkillId, INT nState)
	//{
	//	if (!attrgrp.GetRestFrame())
	//		return;
	//	if (!g_RandPercent(magic.nValue[0]))
	//		return;
	//	attrgrp.SetRestFrame(1);
	//}
	//static VOID ReceiveMagic_Ignore(KNpcSkillData &rcNpcSkillData, KNpcAttribGroup_State& attrgrp, CONST KMagicAttrib& magic, INT nSkillId, INT nState)
	//{
	//	attrgrp.AddIgnore(magic.nValue[0]); 
	//	if (magic.nValue[0] > 0)
	//	{
	//		rcNpcSkillData.RemoveSpecialState((KE_STATE)nState);
	//	}
	//}
};

// NPC״̬
//typedef KMagicAttribGroup_State<emSTATE_HURT, magic_state_hurt>		KMagicAttribStateHurt;
//typedef KMagicAttribGroup_State<emSTATE_WEAK, magic_state_weak>		KMagicAttribStateWeak;
//typedef KMagicAttribGroup_State<emSTATE_SLOWALL, magic_state_slowall>	KMagicAttribStateSlowAll;
//typedef KMagicAttribGroup_State<emSTATE_BURN, magic_state_burn>		KMagicAttribStateBurn;
//typedef KMagicAttribGroup_State<emSTATE_STUN, magic_state_stun>		KMagicAttribStateStun;
//typedef KMagicAttribGroup_State<emSTATE_FIXED, magic_state_fixed>		KMagicAttribStateFixed;
//typedef KMagicAttribGroup_State<emSTATE_PALSY, magic_state_palsy>		KMagicAttribStatePalsy;
//typedef KMagicAttribGroup_State<emSTATE_SLOWRUN, magic_state_slowrun>	KMagicAttribStateSlowRun;
//typedef KMagicAttribGroup_State<emSTATE_FREEZE, magic_state_freeze>	KMagicAttribStateFreeze;
//typedef KMagicAttribGroup_State<emSTATE_CONFUSE, magic_state_confuse>	KMagicAttribStateConfuse;
//typedef KMagicAttribGroup_State<emSTATE_KNOCK, magic_state_knock>		KMagicAttribStateKnock;
//typedef KMagicAttribGroup_State<emSTATE_SILENCE, magic_state_silence>	KMagicAttribStateSilence;
//typedef KMagicAttribGroup_State<emSTATE_DRAG, magic_state_drag>		KMagicAttribStateDrag;
//typedef KMagicAttribGroup_State<emSTATE_ZHICAN, magic_state_zhican>		KMagicAttribStateZhiCan;
//typedef KMagicAttribGroup_State<emSTATE_FLOAT, magic_state_float>		KMagicAttribStateFloat;

// NPC�˺�
typedef KMagicAttribGroup_Damage<damage_physics>	KMagicAttribDamagePhysics;
typedef KMagicAttribGroup_Damage<damage_fire>		KMagicAttribDamageFire;
typedef KMagicAttribGroup_Damage<damage_cold>		KMagicAttribDamageCold;
typedef KMagicAttribGroup_Damage<damage_light>		KMagicAttribDamageLight;
typedef KMagicAttribGroup_Damage<damage_poison>		KMagicAttribDamagePoison;
typedef KMagicAttribGroup_Damage<damage_magic>		KMagicAttribDamageMagic;
typedef KMagicAttribGroup_Damage<damage_return>		KMagicAttribDamageReturn;

// -------------------------------------------------------------------------
