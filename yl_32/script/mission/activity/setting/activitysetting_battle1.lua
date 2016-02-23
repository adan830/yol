-- �������ã��ɲ߻���д
Include("script/mission/activity/activitydef.lua")

local ActivitySetting = Activity.ActivitySetting

ActivitySetting[21] =
{
	nRequireLevel = 25,                -- ����ȼ�
	tbOpenTimes = {{{ wday=1,hour=14, min=30, sec=0}, {wday=1,hour=15, min=00, sec=5}},{{ wday=1,hour=19, min=30, sec=0}, {wday=1,hour=20, min=0, sec=5}},{{ wday=2,hour=14, min=30, sec=0}, {wday=2,hour=15, min=0, sec=5}},{{ wday=2,hour=19, min=30, sec=0}, {wday=2,hour=20, min=0, sec=5}},{{ wday=4,hour=14, min=30, sec=0}, {wday=4,hour=15, min=0, sec=5}},{{ wday=4,hour=19, min=30, sec=0}, {wday=4,hour=20, min=0, sec=5}},{{ wday=6,hour=14, min=30, sec=0}, {wday=6,hour=15, min=0, sec=5}},{{ wday=6,hour=19, min=30, sec=0}, {wday=6,hour=20, min=0, sec=5}}},	--����ʱ��{StartTime, EndTime},9���ӣ������Σ����ʱ��, ÿ��ʱ�䲻���ص�
	ActivityName = Lang.mission.str88[Lang.Idx],        -- ����֣������Ϣ��
	nStartStep = 1,			   	          -- ��ʼ���裬��¼����λ��
	tbEnterPos = { nMapId = 345, tbPos = {{1726,2280,1048576}}},		-- ׼���������
	nPrepareTime = 180,						-- �����׶�ʱ��
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
ActivitySetting[21].Enemy1 = Team + Team_Enable + Not;  --�Ƕ��ѵ���ȫ���ǵ���
--ActivitySetting[2].Enemy2 = 0;

-- ���趨��ֿ�д����Ȼ���̫���������
local STEP = ActivitySetting[21].STEP


STEP[1] =
{
	Time = 210,                                              --ʱ��   3.5����
	AssignType = Activity.ASSIGN_TYPE.RANDOMLY_ASSIGNED,
	GroupType = Activity.GROUP_TYPE.DONNOT_GROUP,
	GroupNum = 2,                                            -- С�����ȵİ��ģʽ
	MaxPlayer = 100,                                          -- ����ܲμӵ������
	Type = Activity.STEP_TYPE.ZHUNBEICHANG,                   -- ��������
	--Enemy = {0,0,0,0,0},                                      -- ��������Ͳ����ٷ��飬����ҹ�ϵ�ж��Ƿ����
	Pos = {345,{1155,2074,1048576},{1083,2657,1048576},{1452,2931,1048576},{1946,2686,1048576},{2123,2336,1048576},{1638,1716,1048576},{1500,2352,1048576}},                         --���Ĭ�ϴ��͵�λ��
	NPC =
	{
-- 		���  	npcģ��				�ȼ�(-1Ĭ��)	5��(Ĭ��-1)

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

		[2] = {nTime = 179, nNum = 0,
			tbPrelock = {1},
			tbStartEvent =
			{
				{Activity.EVENT_TYPE.SHOW_NOTICE_MSG, Lang.mission.str89[Lang.Idx]},	--׼����������������
				{Activity.EVENT_TYPE.TIME_INFO, -1, Lang.mission.str90[Lang.Idx], 2},
				{Activity.EVENT_TYPE.ADD_EXC_ALL_EVENT, Activity.EVENT_TYPE.TIME_INFO, {-1, Lang.mission.str91[Lang.Idx]}, 2},
				{Activity.EVENT_TYPE.TARGET_INFO,-1, Lang.mission.str92[Lang.Idx], 2},
				{Activity.EVENT_TYPE.ADD_EXC_ALL_EVENT, Activity.EVENT_TYPE.TARGET_INFO, {-1, Lang.mission.str93[Lang.Idx], 2}},
			},
			tbUnLockEvent =
			{
			},
		},
		[3] = {nTime = 30, nNum = 0,
			tbPrelock = {2},
			tbStartEvent =
			{
				{Activity.EVENT_TYPE.TIME_INFO, -1, Lang.mission.str94[Lang.Idx], 3},
				{Activity.EVENT_TYPE.ADD_EXC_ALL_EVENT, Activity.EVENT_TYPE.TIME_INFO, {-1, Lang.mission.str95[Lang.Idx]}, 3},
				{Activity.EVENT_TYPE.TARGET_INFO,-1, Lang.mission.str96[Lang.Idx], 3},
				{Activity.EVENT_TYPE.ADD_EXC_ALL_EVENT, Activity.EVENT_TYPE.TARGET_INFO, {-1, Lang.mission.str97[Lang.Idx], 3}},

			},
			tbUnLockEvent =
			{
			},
		},
    },
    NextSteps = {2},
}


STEP[2] =                                                        --����boss׼����
{
	Time = 1560,                                              	  --ʱ��  26����
	NeedTransport = 0,									                          -- ׼�����ֶ�����
	AssignType = Activity.ASSIGN_TYPE.RANDOMLY_ASSIGNED,          --�������
	GroupType = Activity.GROUP_TYPE.FIGHT_SCORE_GROUP,			      -- ս������
	GroupNum = 2,
	MaxPlayer = 100,
	Type = Activity.STEP_TYPE.BATTLE_FIELD,
	Pos = {349,{4501,1107,1048576},{4497,7368,1048576}},
	NPC =
	{
		-- 		���  	npcģ��				�ȼ�(-1Ĭ��)	5��(Ĭ��-1)
 		[1] = {nTemplate = 2540, nLevel = -1, nSeries = -1},		--�������
		[2] = {nTemplate = 2541, nLevel = -1, nSeries = -1},		--ħ�����
		[3] = {nTemplate = 2546, nLevel = -1, nSeries = -1},		--����������1
 		[4] = {nTemplate = 2547, nLevel = -1, nSeries = -1},		--����������2
 		[5] = {nTemplate = 2548, nLevel = -1, nSeries = -1},		--����������1
 		[6] = {nTemplate = 2549, nLevel = -1, nSeries = -1},		--����������2
 		[7] = {nTemplate = 2550, nLevel = -1, nSeries = -1},		--����������1
 		[8] = {nTemplate = 2551, nLevel = -1, nSeries = -1},		--����������2
 		[9] = {nTemplate = 2552, nLevel = -1, nSeries = -1},		--ħ��������1
 		[10] = {nTemplate = 2553, nLevel = -1, nSeries = -1},		--ħ��������2
 		[11] = {nTemplate = 2554, nLevel = -1, nSeries = -1},		--ħ��������1
 		[12] = {nTemplate = 2555, nLevel = -1, nSeries = -1},		--ħ��������2
 		[13] = {nTemplate = 2556, nLevel = -1, nSeries = -1},		--ħ��������1
 		[14] = {nTemplate = 2557, nLevel = -1, nSeries = -1},		--ħ��������2
 		[15] = {nTemplate = 2571, nLevel = -1, nSeries = -1},		--����npc ��
 		[16] = {nTemplate = 2576, nLevel = -1, nSeries = -1},		--����npc ������
 		[17] = {nTemplate = 2589, nLevel = -1, nSeries = -1},		--ħ��npc ħ��
 		[18] = {nTemplate = 2594, nLevel = -1, nSeries = -1},		--ħ��npc ������

	},
  LOCK =
    {
	-- 1�������ܲ��Ĭ��1��Ϊ��ʼ��
		[1] = {nTime = 1, nNum = 0,		-- 1�뻺��
			tbPrelock = {},
			tbStartEvent =
			{

			},
			tbUnLockEvent =
			{

			},
		},
		[2] = {nTime = 29, nNum = 0,		-- �ܼ�ʱ ׼�����ȴ�29��
			tbPrelock = {1},
			tbStartEvent =
			{
				{Activity.EVENT_TYPE.SHOW_NOTICE_MSG, Lang.mission.str98[Lang.Idx],1},	--׼����������������
				{Activity.EVENT_TYPE.TIME_INFO, -1, Lang.mission.str99[Lang.Idx], 2},
				{Activity.EVENT_TYPE.ADD_EXC_ALL_EVENT, Activity.EVENT_TYPE.TIME_INFO, {-1, Lang.mission.str99[Lang.Idx]}, 2},
				{Activity.EVENT_TYPE.TARGET_INFO,-1, Lang.mission.str100[Lang.Idx], 2},
				{Activity.EVENT_TYPE.ADD_EXC_ALL_EVENT, Activity.EVENT_TYPE.TARGET_INFO, {-1, Lang.mission.str101[Lang.Idx], 2}},
				
				{Activity.EVENT_TYPE.ADD_NPC, 1, 1, 2, "jidi", "jidi"},  								  --�������
				{Activity.EVENT_TYPE.ADD_NPC, 2, 1, 2, "jidi", "jidi"},  								  --ħ�����
				{Activity.EVENT_TYPE.ADD_NPC, 3, 1, 2, "middletower1", "middletower1"},   --����������1
				{Activity.EVENT_TYPE.ADD_NPC, 4, 1, 2, "middletower2", "middletower2"},   --����������2
				{Activity.EVENT_TYPE.ADD_NPC, 5, 1, 2, "shangtower1", "shangtower1"},  		  --����������1
				{Activity.EVENT_TYPE.ADD_NPC, 6, 1, 2, "shangtower2", "shangtower2"},  		  --����������2
				{Activity.EVENT_TYPE.ADD_NPC, 6, 1, 2, "shangtower3", "shangtower3"},  		  --����������3
				{Activity.EVENT_TYPE.ADD_NPC, 6, 1, 2, "shangtower4", "shangtower4"},  		  --����������4
				{Activity.EVENT_TYPE.ADD_NPC, 7, 1, 2, "xiatower1", "xiatower1"},     --����������1
				{Activity.EVENT_TYPE.ADD_NPC, 8, 1, 2, "xiatower2", "xiatower2"},     --����������2
				{Activity.EVENT_TYPE.ADD_NPC, 8, 1, 2, "xiatower3", "xiatower3"},     --����������3
				{Activity.EVENT_TYPE.ADD_NPC, 8, 1, 2, "xiatower4", "xiatower4"},     --����������4
				
				{Activity.EVENT_TYPE.ADD_NPC, 9, 1, 2, "middletower1", "middletower1"},   --ħ��������1
				{Activity.EVENT_TYPE.ADD_NPC, 10, 1, 2, "middletower2", "middletower2"},  --ħ��������2
				{Activity.EVENT_TYPE.ADD_NPC, 11, 1, 2, "shangtower1", "shangtower1"},  		--ħ��������1
				{Activity.EVENT_TYPE.ADD_NPC, 12, 1, 2, "shangtower2", "shangtower2"},  		--ħ��������2
				{Activity.EVENT_TYPE.ADD_NPC, 12, 1, 2, "shangtower3", "shangtower3"},  		--ħ��������3
				{Activity.EVENT_TYPE.ADD_NPC, 12, 1, 2, "shangtower4", "shangtower4"},  		--ħ��������4
				{Activity.EVENT_TYPE.ADD_NPC, 13, 1, 2, "xiatower1", "xiatower1"},    --ħ��������1
				{Activity.EVENT_TYPE.ADD_NPC, 14, 1, 2, "xiatower2", "xiatower2"},    --ħ��������2
				{Activity.EVENT_TYPE.ADD_NPC, 14, 1, 2, "xiatower3", "xiatower3"},    --ħ��������3
				{Activity.EVENT_TYPE.ADD_NPC, 14, 1, 2, "xiatower4", "xiatower4"},    --ħ��������4


				{Activity.EVENT_TYPE.REVIVE_INFO, 1 ,false, true, true, 0,{4048,970,1048576},{4289,1139,1048576},{4594,1123,1048576},{4851,897,1048576},{4989,990,1048576}}, --���帴���
		    {Activity.EVENT_TYPE.REVIVE_INFO, 2 ,false, true, true, 0,{3929,7641,1048576},{4136,7497,1048576},{4416,7450,1048576},{4695,7455,1048576},{4842,7588,1048576}}, --ħ�帴���
			},
			tbUnLockEvent =
			{

			},
		},
  [3] = {nTime = 15, nNum = 0,		-- 15�뻺��
			tbPrelock = {1},
			tbStartEvent =
			{
        {Activity.EVENT_TYPE.ADD_NPC, 15, 3, 3, "shangnpc1", "shangnpc1",},  						--���� ��1��  5ֻ
        {Activity.EVENT_TYPE.ADD_NPC, 16, 1, 3, "shangnpc1", "shangnpc1",},  						--���� ��1������ 1ֻ
        {Activity.EVENT_TYPE.ADD_NPC, 15, 3, 3, "shangnpc2", "shangnpc2",},  						--���� ��2��  5ֻ
        {Activity.EVENT_TYPE.ADD_NPC, 16, 1, 3, "shangnpc2", "shangnpc2",},  						--���� ��2������ 1ֻ
        {Activity.EVENT_TYPE.ADD_NPC, 15, 3, 3, "shangnpc3", "shangnpc3",},      			  --���� ��3��  5ֻ
        {Activity.EVENT_TYPE.ADD_NPC, 16, 1, 3, "shangnpc3", "shangnpc3",},  						--���� ��3������ 1ֻ

				{Activity.EVENT_TYPE.ADD_NPC, 15, 3, 3, "middlenpc1", "middlenpc1",},  			  	--���� ��1��  5ֻ
				{Activity.EVENT_TYPE.ADD_NPC, 16, 1, 3, "middlenpc1", "middlenpc1",},  			  	--���� ��1������ 1ֻ

				{Activity.EVENT_TYPE.ADD_NPC, 15, 3, 3, "xianpc1", "xianpc1",},  			  	--���� ��1��  5ֻ
				{Activity.EVENT_TYPE.ADD_NPC, 16, 1, 3, "xianpc1", "xianpc1",},  			  	--���� ��1������ 1ֻ
				{Activity.EVENT_TYPE.ADD_NPC, 15, 3, 3, "xianpc2", "xianpc2",},  			  	--���� ��2��  5ֻ
				{Activity.EVENT_TYPE.ADD_NPC, 16, 1, 3, "xianpc2", "xianpc2",},  			  	--���� ��2������ 1ֻ
				{Activity.EVENT_TYPE.ADD_NPC, 15, 3, 3, "xianpc3", "xianpc3",},  			  	--���� ��3��  5ֻ
				{Activity.EVENT_TYPE.ADD_NPC, 16, 1, 3, "xianpc3", "xianpc3",},  			  	--���� ��3������ 1ֻ
				
				
			  {Activity.EVENT_TYPE.ADD_NPC, 17, 3, 3, "shangnpc1", "shangnpc1",},  						--ħ�� ��1ħ��  5ֻ
        {Activity.EVENT_TYPE.ADD_NPC, 18, 1, 3, "shangnpc1", "shangnpc1",},  						--ħ�� ��1������ 1ֻ
			  {Activity.EVENT_TYPE.ADD_NPC, 17, 3, 3, "shangnpc2", "shangnpc2",},  						--ħ�� ��2ħ��  5ֻ
        {Activity.EVENT_TYPE.ADD_NPC, 18, 1, 3, "shangnpc2", "shangnpc2",},  						--ħ�� ��2������ 1ֻ
        {Activity.EVENT_TYPE.ADD_NPC, 17, 3, 3, "shangnpc3", "shangnpc3",},        			--ħ�� ��3ħ��  5ֻ
        {Activity.EVENT_TYPE.ADD_NPC, 18, 1, 3, "shangnpc3", "shangnpc3",},  						--ħ�� ��3������ 1ֻ

				{Activity.EVENT_TYPE.ADD_NPC, 17, 3, 3, "middlenpc1", "middlenpc1",},  			  	--ħ�� ��1ħ��  5ֻ
				{Activity.EVENT_TYPE.ADD_NPC, 18, 1, 3, "middlenpc1", "middlenpc1",},  			  	--ħ�� ��1������ 1ֻ

				{Activity.EVENT_TYPE.ADD_NPC, 17, 3, 3, "xianpc1", "xianpc1",},  			  	--ħ�� ��1ħ��  5ֻ
				{Activity.EVENT_TYPE.ADD_NPC, 18, 1, 3, "xianpc1", "xianpc1",},  			  	--ħ�� ��1������ 1ֻ
				{Activity.EVENT_TYPE.ADD_NPC, 17, 3, 3, "xianpc2", "xianpc2",},  			  	--ħ�� ��2ħ��  5ֻ
				{Activity.EVENT_TYPE.ADD_NPC, 18, 1, 3, "xianpc2", "xianpc2",},  			  	--ħ�� ��2������ 1ֻ
				{Activity.EVENT_TYPE.ADD_NPC, 17, 3, 3, "xianpc3", "xianpc3",},  			  	--ħ�� ��3ħ��  5ֻ
				{Activity.EVENT_TYPE.ADD_NPC, 18, 1, 3, "xianpc3", "xianpc3",},  			  	--ħ�� ��3������ 1ֻ
			},
			tbUnLockEvent =
			{

			},
		},
	[4] = {nTime = 1530, nNum = 0,		--��ħս����ʼ   26����
			tbPrelock = {2},
			tbStartEvent =
			{
				{Activity.EVENT_TYPE.SHOW_NOTICE_MSG, Lang.mission.str102[Lang.Idx],1},
				{Activity.EVENT_TYPE.TIME_INFO, -1, Lang.mission.str103[Lang.Idx], 4},
				{Activity.EVENT_TYPE.ADD_EXC_ALL_EVENT, Activity.EVENT_TYPE.TIME_INFO, {-1, Lang.mission.str103[Lang.Idx]},4},
				{Activity.EVENT_TYPE.TARGET_INFO,-1, Lang.mission.str104[Lang.Idx], 4},
				{Activity.EVENT_TYPE.ADD_EXC_ALL_EVENT, Activity.EVENT_TYPE.TARGET_INFO, {-1, Lang.mission.str104[Lang.Idx], 4}},
			},
			tbUnLockEvent =
			{

			},
		},

    },
    NextSteps = {3},
}

STEP[3] =
{
	Time = 30,                                              	    --ʱ��  0.5����
	AssignType = Activity.ASSIGN_TYPE.DONOT_NEED,          --�������
	GroupType = Activity.GROUP_TYPE.DONNOT_GROUP,
	GroupNum = 2,
	MaxPlayer = 100,
	NeedTransport = 0;
	Type = Activity.STEP_TYPE.ZHUNBEICHANG,                   -- ��������
	Pos = {349,{6650,1688,1048576}},
	NPC =
	{
-- 		���  	npcģ��				�ȼ�(-1Ĭ��)	5��(Ĭ��-1)
	},
    LOCK =
    {
       -- 1�������ܲ��Ĭ��1��Ϊ��ʼ��
		[1] = {nTime =30, nNum = 0,		-- �ܼ�ʱ ׼�����ȴ�2��
			tbPrelock = {},
			tbStartEvent =
			{
				{Activity.EVENT_TYPE.TIME_INFO, -1, Lang.mission.str106[Lang.Idx], 1},
				{Activity.EVENT_TYPE.ADD_EXC_ALL_EVENT, Activity.EVENT_TYPE.TIME_INFO, {-1, Lang.mission.str106[Lang.Idx]}, 1},
			},
			tbUnLockEvent =
			{

			},
		},

    },
    NextSteps = {},
}
