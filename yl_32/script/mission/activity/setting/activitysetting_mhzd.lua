-- �������ã��ɲ߻���д  20������֮��
Include("script/mission/activity/activitydef.lua")

local ActivitySetting = Activity.ActivitySetting

ActivitySetting[30] =
{
	nRequireLevel = 20,                -- ����ȼ�
	tbOpenTimes = {{ {hour=0, min=0, sec=0}, {hour=23, min=50, sec=0} }},	--����ʱ��{StartTime, EndTime},�����Σ����ʱ��, ÿ��ʱ�䲻���ص�
	ActivityName = Lang.mission.str1134[Lang.Idx],        -- ����֣������Ϣ��
	nStartStep = 1,			   	          -- ��ʼ���裬��¼����λ��
  tbEnterPos = { nMapId = 353, tbPos = {{6722,6273,1048576},{5085,5300,1048576},{4409,5387,1048576},{3272,5633,1048576},{2138,4211,1048576},{2850,3832,1048576},{5176,1955,1048576},{1945,1734,1048576}}},		-- �����
	nPrepareTime = 86390,						-- �����׶�ʱ��
	nReadyStartTime = 2,					-- ׼�����ڻ��ʼ���ÿ���
	STEP = {},
}

local All = Activity.Type_All;
local Self = Activity.Type_Self;
local Npc = Activity.Type_Npc;
local Team = Activity.Type_Team;
local Kin = Activity.Type_Kin;
local Server = Activity.Type_Server;
local All_Enable = Activity.Type_All_Enable;
local Self_Enable = Activity.Type_Self_Enable;
local Npc_Enable = Activity.Type_Npc_Enable;
local Team_Enable = Activity.Type_Team_Enable;
local Kin_Enable = Activity.Type_Kin_Enable;
local Server_Enable = Activity.Type_Server_Enable;
local Not = Activity.Type_Not;
--���� ��ȫ����			����			npc��			���ѣ�			ͬ�����Ա��	ͬ���������
--����1��All,			Self,			Npc,			Team,			Kin,			Server
--����2��All_Enable,	Self_Enable,	Npc_Enable,		Team_Enable,	Kin_Enable,		Server_Enable

--����3��Not

--type_enable��дʱ������ж���Ч�����򲻶Դ����������ж�
--type_enable��д�˵�����£�����д��Ӧtype������Ϊ�����Ϊ����
--all����self�������д��allһ��Ҫ��selfȥ��
--type_not�ĺ���Ϊ��������д��������ĵ�λΪ����

--��д��ʽΪ��ӵķ�ʽ��Type_All + Type_Self_Enable + Type_Team_Enable + Type_Not
ActivitySetting[30].Enemy1 = Team + Team_Enable + Not;  --�Ƕ��ѵ���ȫ���ǵ���
--ActivitySetting[2].Enemy2 = 0;

-- ���趨��ֿ�д����Ȼ���̫���������
local STEP = ActivitySetting[30].STEP


STEP[1] =
{
	Time = 86390,                                              --ʱ��
	AssignType = Activity.ASSIGN_TYPE.RANDOMLY_ASSIGNED,
	GroupType = Activity.GROUP_TYPE.DONNOT_GROUP,
	GroupNum = 2,                                            -- �����Ӫ����
	MaxPlayer = 2000,                                          -- ����ܲμӵ������
	Type = Activity.STEP_TYPE.MANHUANGZHIDI,                   -- ��������
	--Enemy = {0,0,0,0,0},                                      -- ��������Ͳ����ٷ��飬����ҹ�ϵ�ж��Ƿ����
	Pos = {353,{6722,6273,1048576},{5085,5300,1048576},{4409,5387,1048576},{3272,5633,1048576},{2138,4211,1048576},{2850,3832,1048576},{5176,1955,1048576},{1945,1734,1048576}},                         --���Ĭ�ϴ��͵�λ��
	NPC =
	{
-- 		���  	npcģ��				�ȼ�(-1Ĭ��)	5��(Ĭ��-1)

		[1] = {nTemplate = 2801, nLevel = -1, nSeries = -1},		--��ǹ����
		[2] = {nTemplate = 2807, nLevel = -1, nSeries = -1},		--����
		[3] = {nTemplate = 2808, nLevel = -1, nSeries = -1},		--���
		[4] = {nTemplate = 2809, nLevel = -1, nSeries = -1},		--������
		[5] = {nTemplate = 2810, nLevel = -1, nSeries = -1},		--���
		[6] = {nTemplate = 2811, nLevel = -1, nSeries = -1},		--�����
		[7] = {nTemplate = 2812, nLevel = -1, nSeries = -1},		--��������
		[8] = {nTemplate = 2813, nLevel = -1, nSeries = -1},		--���ħ��
		
		[9] =  {nTemplate = 2820, nLevel = -1, nSeries = -1},		--�ںڴ���
		[10] = {nTemplate = 2821, nLevel = -1, nSeries = -1},		--����Ұ��
		[11] = {nTemplate = 2822, nLevel = -1, nSeries = -1},		--������
		[12] = {nTemplate = 2823, nLevel = -1, nSeries = -1},		--�޻궾��
		[13] = {nTemplate = 2824, nLevel = -1, nSeries = -1},		--��ɽ��
		[14] = {nTemplate = 2825, nLevel = -1, nSeries = -1},		--�ٻ�з
		[15] = {nTemplate = 2826, nLevel = -1, nSeries = -1},		--��۹�
		[16] = {nTemplate = 2827, nLevel = -1, nSeries = -1},		--Թ��
		
		[17] = {nTemplate = 2814, nLevel = -1, nSeries = -1},		--��վ

	},
    LOCK =
    {
       -- 1�������ܲ��Ĭ��1��Ϊ��ʼ��
		[1] = {nTime = 1, nNum = 0,		-- �ܼ�ʱ ׼�����ȴ�2��
			tbPrelock = {},
			tbStartEvent =
			{

			},
			tbUnLockEvent =
			{

			},
		},

		[2] = {nTime = 86389, nNum = 0,
			tbPrelock = {1},
			tbStartEvent =
			{		
				{Activity.EVENT_TYPE.TARGET_INFO,-1, string.format(Lang.mission.str136[Lang.Idx],20), 2},
				{Activity.EVENT_TYPE.ADD_EXC_ALL_EVENT, Activity.EVENT_TYPE.TARGET_INFO, {-1, string.format(Lang.mission.str136[Lang.Idx],20), 2}},

        {Activity.EVENT_TYPE.ADD_NPC, 17, 1, 2,"chuangsong","chuangsong"}, --��վ

				{Activity.EVENT_TYPE.ADD_NPC, 1, 4, 2,"guaiwu1","pos1"},
				{Activity.EVENT_TYPE.ADD_NPC, 1, 4, 2,"guaiwu1","pos2"},
				{Activity.EVENT_TYPE.ADD_NPC, 1, 4, 2,"guaiwu1","pos3"},
				{Activity.EVENT_TYPE.ADD_NPC, 1, 4, 2,"guaiwu1","pos4"},
				{Activity.EVENT_TYPE.ADD_NPC, 9, 4, 2,"guaiwu1","pos5"},
				{Activity.EVENT_TYPE.ADD_NPC, 9, 4, 2,"guaiwu1","pos6"},
				{Activity.EVENT_TYPE.ADD_NPC, 9, 4, 2,"guaiwu1","pos7"},
				{Activity.EVENT_TYPE.ADD_NPC, 9, 4, 2,"guaiwu1","pos8"},
				{Activity.EVENT_TYPE.ADD_NPC, 10, 4, 2,"guaiwu1","pos9"},
				{Activity.EVENT_TYPE.ADD_NPC, 10, 4, 2,"guaiwu1","pos10"},
				{Activity.EVENT_TYPE.ADD_NPC, 10, 4, 2,"guaiwu1","pos11"},
				{Activity.EVENT_TYPE.ADD_NPC, 10, 4, 2,"guaiwu1","pos12"},
				{Activity.EVENT_TYPE.ADD_NPC, 1, 4, 2,"guaiwu1","pos13"},
				{Activity.EVENT_TYPE.ADD_NPC, 1, 4, 2,"guaiwu1","pos14"},
	

				{Activity.EVENT_TYPE.ADD_NPC_ON_TIME,060000, 2, 1, 2,"boss","boss"},  --10��ˢ��boss1
				{Activity.EVENT_TYPE.ADD_NPC_ON_TIME,140000, 3, 1, 2,"boss","boss"},  --16��ˢ��boss4
				{Activity.EVENT_TYPE.ADD_NPC_ON_TIME,200000, 4, 1, 2,"boss","boss"},  --16��ˢ��boss4

				
			},
			tbUnLockEvent =
			{
 
			},
		},
    },
    NextSteps = {},
}
