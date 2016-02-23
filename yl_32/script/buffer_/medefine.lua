
BufferMagicEffect.DEBUG_MODE = 0;
BufferCondition.DEBUG_MODE = 0;

function BufferMagicEffect:DebugPrint(szMsg, ...)
	if self.DEBUG_MODE == 1 then
		print(szMsg, ...);
	end
end

function BufferCondition:DebugPrint(szMsg, ...)
	if self.DEBUG_MODE == 1 then
		print(szMsg, ...);
	end
end

local newCounter = function()
	local i = -1;
	return function ()
		i = i + 1;
		return i;
	end
end

local ById = newCounter();

-- Buff���޸���������
BufferMagicEffect.BuffDataType =
{
	DATATYPE_STUN							= ById(),	-- ѣ��
	DATATYPE_FIX							= ById(),	-- ����
	DATATYPE_FEAR							= ById(),	-- �־�
	DATATYPE_SILENCE						= ById(),	-- ��Ĭ
	DATATYPE_CRAZY							= ById(),	-- ���
	DATATYPE_SPEED_PERCENT					= ById(),	-- �ٶȰٷֱ�
	DATATYPE_ARMOR							= ById(),	-- ����
	DATATYPE_PHYSICATTACK_MAX				= ById(),	-- ��������˺�
	DATATYPE_PHYSICATTACK_MIN				= ById(),	-- ��С�����˺�
	DATATYPE_MAGICATTACK_MAX				= ById(),	-- ������˺�
	DATATYPE_MAGICATTACK_MIN				= ById(),	-- ��С�����˺�
	DATATYPE_MAXLIFE						= ById(),	-- �������ֵ
	DATATYPE_MAXMANA						= ById(),	-- �����ֵ
	DATATYPE_MAXPOWER						= ById(),	-- �����ֵ
	DATATYPE_ATTACK							= ById(),	-- ����
	DATATYPE_RESIST							= ById(),	-- ����
	DATATYPE_HITCOEFFICIENT					= ById(),	-- ����ϵ��
	DATATYPE_CRITICALVALUE					= ById(),	-- ����ֵ
	DATATYPE_CRITICALATTACK					= ById(),	-- �����˺�
	DATATYPE_DODGEPHYSIC					= ById(),	-- ��������
	DATATYPE_DODGEMAGIC						= ById(),	-- ��������
	DATATYPE_DODGEALL						= ById(),	-- ȫ������
	DATATYPE_HIDETO_NPC						= ById(),	-- ��NPC����
	DATATYPE_HIDETO_PLAYER					= ById(),	-- ��Player����
	DATATYPE_REBOUND_P						= ById(),	-- �����ٷֱ�
	DATATYPE_REBOUND_V						= ById(),	-- ����ֵ
	DATATYPE_TRANSTOLIFE_P					= ById(),	-- �˺�ת����
	DATATYPE_TRANSTOMANA_P					= ById(),	-- �˺�תħ��
	DATATYPE_VISIONTO_NPC					= ById(),	-- ��NPC�ɼ�
	DATATYPE_VISIONTO_PLAYER				= ById(),	-- ��PLAYER�ɼ�
	DATATYPE_FORCEATTACK_ID					= ById(),	-- ǿ�ƹ���Ŀ��ID(��Ŀ��Ϊ0)
	DATATYPE_IGNORE_DMG						= ById(),	-- �����˺�
	DATATYPE_IGNORE_CRISTAL					= ById(),	-- ���߻���һ��
	DATATYPE_IGNORE_DEBUFF					= ById(),	-- ��������debuff
	DATATYPE_CURING_LIFE_BASE				= ById(),	-- ��������
	DATATYPE_CURING_MANA_BASE				= ById(),	-- ��������
	DATATYPE_SKILL_COST						= ById(),	-- ��������
	DATATYPE_TRANSPARAM_TYPE				= ById(),	-- ת���Ĳ�������
	DATATYPE_TRANSPARAM_VALUE				= ById(),	-- ת���Ĳ���ֵ
	DATATYPE_SKILL_CHANNELTIME				= ById(),	-- ���ܵ�����ʱ��
	DATATYPE_SKILL_CATETYPE					= ById(),	-- ���ܵ�CateType
	DATATYPE_SKILL_CATEID					= ById(),	-- ���ܵ�CateID
	DATATYPE_SKILL_CRITICAL					= ById(),	-- ���ܵĻ��İٷֱ�
	DATATYPE_SKILL_BUFF						= ById(),	-- ����+-Buff
	DATATYPE_IGNOREBUFF_ID					= ById(),	-- ����Buff id
	DATATYPE_IGNOREBUFF_GROUP				= ById(),	-- ����Buff group
	DATATYPE_IGNOREBUFF_CATETYPE			= ById(),	-- ����Buff catetype
	DATATYPE_IGNOREBUFF_CATEID				= ById(),	-- ����Buff cateid
	DATATYPE_WITHSTAND_BUFF_PLAYER			= ById(),	-- �ֵ��˺��Ľ�ɫ
	DATATYPE_WITHSTAND_BUFF_PERCENT			= ById(),	-- �ֵ��˺�����
	DATATYPE_WITHSTAND_BUFF_LIFEPERCENT		= ById(),	-- �ֵ��˺�����
	DATATYPE_WITHSTAND_MAGIC				= ById(),	-- ��������
	DATATYPE_ENLARGE_ATTACK_P				= ById(),	-- �˺��Ŵ�ٷֱ�
	DATATYPE_REDUCE_ATTACK_P				= ById(),	-- �˺���С�ٷֱ�
	DATATYPE_MODIFYDMG_P					= ById(),	-- �˺�����ٷֱ�
	DATATYPE_BUFF_TOTAL_DMG					= ById(),	-- Buff���˺���
	DATATYPE_CURING_LIFE_PERCENT			= ById(),	-- �������ưٷֱ�
	DATATYPE_CURING_MANA_PERCENT			= ById(),	-- �������ưٷֱ�
	DATATYPE_CHANGE_CHANNEL_CATETYPE		= ById(),	-- ���ü����ͷ�����catetype
	DATATYPE_CHANGE_CHANNEL_CATEID			= ById(),	-- ���ü����ͷ�����cateid
	DATATYPE_CALL_NPC						= ById(),	-- �ٻ�NPC
	DATATYPE_MODIFYTHREAT_P					= ById(),	-- ����˺�������ްٷֱ�
	DATATYPE_SPEED							= ById(),	-- �ٶ�
	DATATYPE_YONGZHEWUDI					= ById(),	-- �����޵�
	DATATYPE_SKILLCOST_CATEID 				= ById(),	-- �������ĵļ���cateid
	DATATYPE_MAGICCRITICALVALUE				= ById(),	-- ħ������ֵ
	DATATYPE_MEDICINE_EFFECT				= ById(),	-- ҩЧ

	DATATYPE_MAX							= 256	--
};

BufferMagicEffect.KE_CHARACTER_DOING =
{
	emKDOING_STAND					= 1, -- վ��״̬
	emKDOING_WALK					= 2, -- ��·״̬
	emKDOING_RUN					= 3, -- �ܲ�״̬
	emKDOING_JUMP					= 4, -- ��Ծ״̬
	emKDOING_FLY					= 5, -- ������
	emKDOING_SIT					= 6, -- ����״̬
};

BufferMagicEffect.TransParamIdx = 
{
	["MaxLife"] 			= 6,
	["MaxMana"] 			= 7,
	["HitCoefficient"] 		= 10,
	["PhysicDodge"] 			= 12,
	["MagicDodge"] 			= 13,
	["CriticalValue"] 		= 14,
	["CuringLife"] 			= 15,
}

-- ͷ��ð�����Ͷ���
BufferMagicEffect.CHARACTER_HEAD_TEXT_TYPE =
{
	emHeadTextBlood = 0, -- ��Ѫ
	emHeadTextAddBlood = 1, -- ��Ѫ
	emHeadTextCriticalHit = 2, -- ����
	emHeadTextDodge = 3, -- ����
	emHeadTextImmune = 4, -- ����
	emHeadTextExp = 5,  -- ���� 
	emHeadTextYlEnergy = 6, -- ��������
	emHeadTextMoney = 7,  -- ����
	emHeadTextFightScore = 8, -- ս����
	emHeadTextSpirit = 9, -- ս��
	emHeadTextEnemyBlood = 10,  -- �Է���Ѫ����ɫ
	emHeadTextEnemyCriticalHit = 11,  -- npc�۱�������ɫ
	emHeadTextGold = 12,   -- Ԫ��
	emHeadTextTime = 13,   
	emHeadTextIgnoreControl = 14, -- ���
	emHeadTextFightScoreTitle = 15, -- ս��������
  emHeadTextEnemyBloodByGod = 16,
  emHeadTextBloodByGod =17,
  emHeadTextAddBloodByGod = 18,
  emHeadTextAddPrestige = 19,        -- ��������
  emHeadTextAddMaxLife = 20,         -- ����ֵ����
  emHeadTextAddMaxAbility = 21,      -- ����ֵ����
  emHeadTextAddAttack = 22,          -- ����ֵ����
  emHeadTextAddDefence = 23,         -- ����ֵ����
  emHeadTextAddHit = 24,             -- ����ֵ����
  emHeadTextAddDodge = 25,           -- ����ֵ����
  emHeadTextAddCriticalHit = 26,     -- ����ֵ����
  emHeadTextAddResist = 27,          -- ����ֵ����
	
	emHeadtextPure = 99,  -- ������
};
