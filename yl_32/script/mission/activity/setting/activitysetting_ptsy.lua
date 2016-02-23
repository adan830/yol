-- �������ã��ɲ߻���д
Include("script/mission/activity/activitydef.lua")

local ActivitySetting = Activity.ActivitySetting

ActivitySetting[1002] =
{
	nRequireLevel = 20,            -- ����ȼ�
	nStartStep = 1,			   				-- ��ʼ����
	tbEnterPos = { nMapId = 1002, tbPos = {{1137,2686,1048576},{2135,1992,1048576}}, nCopyIndex = 0},		-- �����
	tbOpenTimes = {{{hour=1, min=40, sec=0}, {hour=1, min=45, sec=10}}},	--����ʱ��{StartTime, EndTime},�����Σ����ʱ��, ÿ��ʱ�䲻���ص�  30����
	nPrepareTime = 300,						-- �����׶�ʱ��
	nReadyStartTime = 2,					-- ׼�����ڻ��ʼ���ÿ���
	ActivityName = Lang.mission.str182[Lang.Idx],    -- ����֣������Ϣ��
	nBaseActivityIdx = 1002,
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

ActivitySetting[1002].Enemy1 = Self + Self_Enable + Not;

-- ���趨��ֿ�д����Ȼ���̫���������
local STEP = ActivitySetting[1002].STEP
STEP[1] =
{
	Time = 310,                                              --ʱ��
	AssignType = Activity.ASSIGN_TYPE.RANDOMLY_ASSIGNED,
	GroupType = Activity.GROUP_TYPE.DONNOT_GROUP,
	NeedTransport = 0,
	GroupNum = 2,                                            -- С�����ȵİ��ģʽ
	MaxPlayer = 2000,                                         -- ����ܲμӵ������
	Type = Activity.STEP_TYPE.KIN_PANTAOSHENGYAN,             -- ��������
	Enemy = {0,0,0,0,0},                                      -- ��������Ͳ����ٷ��飬����ҹ�ϵ�ж��Ƿ����
	Pos = {1002,{1726,2280,1048576}},
	NPC =
	{
		-- 		���  	npcģ��				�ȼ�(-1Ĭ��)	5��(Ĭ��-1)
 		[1] = {nTemplate = 2650, nLevel = -1, nSeries = -1},		--���
	},
    LOCK =
    {
       -- 1�������ܲ��Ĭ��1��Ϊ��ʼ��
		[1] = {nTime = 1, nNum = 0,		-- �ܼ�ʱ
			tbPrelock = {},
			tbStartEvent =
			{
			},
			tbUnLockEvent =
			{

			},
		},
		[2] = {nTime = 289 , nNum = 0,		-- �ܼ�ʱ
			tbPrelock = {1},
			tbStartEvent =
			{
				{Activity.EVENT_TYPE.BLACK_MSG, -1, Lang.mission.str183[Lang.Idx]},
				{Activity.EVENT_TYPE.SHOW_NOTICE_MSG, Lang.mission.str183[Lang.Idx]},
				
				{Activity.EVENT_TYPE.TARGET_INFO,-1, Lang.mission.str184[Lang.Idx], 2},
				{Activity.EVENT_TYPE.ADD_EXC_ALL_EVENT, Activity.EVENT_TYPE.TARGET_INFO, {-1, Lang.mission.str184[Lang.Idx], 2}},
			
				{Activity.EVENT_TYPE.TIME_INFO, -1, Lang.mission.str185[Lang.Idx], 2},
				{Activity.EVENT_TYPE.ADD_EXC_ALL_EVENT, Activity.EVENT_TYPE.TIME_INFO, {-1, Lang.mission.str185[Lang.Idx],2}},
			  {Activity.EVENT_TYPE.ADD_NPC, 1, 7, 2,"pantao1","pantao1", 10, 30,"timer1"},   --ˢ���
			  {Activity.EVENT_TYPE.ADD_NPC, 1, 7, 2,"pantao2","pantao2", 10, 30,"timer2"},   --ˢ���
			  {Activity.EVENT_TYPE.ADD_NPC, 1, 7, 2,"pantao3","pantao3", 10, 30,"timer3"},   --ˢ���
			  {Activity.EVENT_TYPE.ADD_NPC, 1, 7, 2,"pantao4","pantao4", 10, 30,"timer4"},   --ˢ���

			},
			tbUnLockEvent =
			{
				{Activity.EVENT_TYPE.DEL_NPC,"pantao1"},   --���
				{Activity.EVENT_TYPE.DEL_NPC,"pantao2"},   --���
				{Activity.EVENT_TYPE.DEL_NPC,"pantao3"},   --���
				{Activity.EVENT_TYPE.DEL_NPC,"pantao4"},   --���
				{Activity.EVENT_TYPE.DEL_NPC,"pantao5"},   --���
			},
		},
       -- 1�������ܲ��Ĭ��1��Ϊ��ʼ��
		[3] = {nTime = 10, nNum = 0,		-- �ܼ�ʱ
			tbPrelock = {2},
			tbStartEvent =
			{
				{Activity.EVENT_TYPE.TARGET_INFO,-1, Lang.mission.str186[Lang.Idx], 3},
				{Activity.EVENT_TYPE.ADD_EXC_ALL_EVENT, Activity.EVENT_TYPE.TARGET_INFO, {-1, Lang.mission.str186[Lang.Idx], 3}},
			
				{Activity.EVENT_TYPE.TIME_INFO, -1, Lang.mission.str187[Lang.Idx], 3},
				{Activity.EVENT_TYPE.ADD_EXC_ALL_EVENT, Activity.EVENT_TYPE.TIME_INFO, {-1, Lang.mission.str187[Lang.Idx],3}},
			},
			tbUnLockEvent =
			{

			},
		},
    },
    NextSteps = {},
}