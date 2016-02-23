-- File       : characterdef.lua
-- Creator    : simon
-- Date       : 2010-01-21 10:20:10
-- Description: Character��������

if not (MODULE_GAMECLIENT or MODULE_GAMESERVER) then
	return
end

local nId = 0;
local function IdAccumulator(nSegment)
	nId = nSegment or nId + 1;
	return nId;
end

Character.CHARACTER_PROPERTY = 
{
	emNONE                  = 0,      -- ������
	emWIND                  = 1,      -- ��
	emTHUNDER               = 2,      -- ��
	emWATER                 = 3,      -- ˮ
	emFIRE                  = 4,     -- ��
}

Character.tbCharacter_Camp = 
{
	emKCHARACTER_CAMP_BLACK		= 0,
	emKCHARACTER_CAMP_RED		= 1,	--
	emKCHARACTER_CAMP_GREEN		= 2,	-- 
}

-- ����·�߶��壬��factiondef.h������Ӧ
-- ��������·��
Character.FACTION_WUSHANG	= 1;	-- ����
Character.FACTION_TIANYAO	= 2;	-- ����
Character.FACTION_YOUMING	= 3;	-- ��ڤ
Character.FACTION_SENLUO	= 4;	-- ɭ��

-- ��������·��
Character.ROUTE_WUSHANG_TONGYONG	= 0;	-- ͨ��
Character.ROUTE_WUSHANG_JIANSHEN	= 1;	-- ����
Character.ROUTE_WUSHANG_YUHE		= 2;	-- ����

-- ��������·��
Character.ROUTE_TIANYAO_TONGYONG	= 0;	-- ͨ��
Character.ROUTE_TIANYAO_FANGHU		= 1;	-- ����
Character.ROUTE_TIANYAO_SHENSHENG	= 2;	-- ��ʥ

-- ��ڤ����·��
Character.ROUTE_YOUMING_TONGYONG	= 0;	-- ͨ��
Character.ROUTE_YOUMING_WENGU		= 1;	-- �ȹ�
Character.ROUTE_YOUMING_CHONGJI		= 2;	-- ���

-- ɭ������·��
Character.ROUTE_SENLUO_TONGYONG	= 0;	-- ͨ��
Character.ROUTE_SENLUO_SHOULIE	= 1;	-- ����
Character.ROUTE_SENLUO_CISHA	= 2;	-- ��ɱ

-- �ܿ�״̬
Character.MOVE_STATE_ON_STAND = 1;		-- վ��״̬
Character.MOVE_STATE_ON_WALK = 2;		-- ��·״̬
Character.MOVE_STATE_ON_RUN = 3;		-- �ܲ�״̬
Character.MOVE_STATE_ON_JUMP = 4;		-- ��Ծ״̬
Character.MOVE_STATE_ON_SWIMJUMP = 5;		-- ˮ����Ծ
Character.MOVE_STATE_ON_SWIM = 6;		-- ˮ����Ӿ
Character.MOVE_STATE_ON_FLOAT = 7;		-- ˮ������
Character.MOVE_STATE_ON_SIT = 8;		-- ��״̬

-- ���ܿ�״̬
Character.MOVE_STATE_ON_KNOCKED_DOWN = 11;		-- ������״̬
Character.MOVE_STATE_ON_KNOCKED_BACK = 12;		-- ������״̬
Character.MOVE_STATE_ON_KNOCKED_OFF = 13;		-- ������״̬
Character.MOVE_STATE_ON_HALT = 14;		-- ����(ѣ�Ρ�ЦѨ�ȵ�)
Character.MOVE_STATE_ON_FREEZE = 15;		-- ���ܶ�(�̶�����)
Character.MOVE_STATE_ON_ENTRAP = 16;		-- �����ƶ�
Character.MOVE_STATE_ON_AUTO_FLY = 17;		-- �Զ��ƶ�,����������
Character.MOVE_STATE_ON_DEATH = 18;		-- ����״̬
Character.MOVE_STATE_ON_DASH = 19;		-- ���״̬
Character.MOVE_STATE_ON_PULL = 20;		-- ��ץ״̬��������ץס�Լ������Է����
Character.MOVE_STATE_ON_REPULSED = 21;		-- ����״̬��һ������ٵ�״̬
Character.MOVE_STATE_ON_RISE = 22;		-- ����״̬
Character.MOVE_STATE_ON_SKID = 23;		-- ͣ��״̬

--��ʼ�ƶ��ٶ�
Character.KD_BASE_RUN_SPEED = 20;		--ע���C++�е���ֵ����һ��