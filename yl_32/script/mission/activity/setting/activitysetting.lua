-- �������ã��ɲ߻���д
Include("script/mission/activity/activitydef.lua")

--[[
local ActivitySetting = Activity.ActivitySetting

ActivitySetting[1] = 
{
	--nRequireLevel = 0,       -- ����ȼ�
	--RequireFaction = -1,     -- ����ְҵ
	StartTime = 0,             -- ��ʼʱ��
    EndTime = 240000,          -- ����ʱ��
    ActivityName = "", -- ����֣������Ϣ��
	STEP = {},
}

-- ���趨��ֿ�д����Ȼ���̫���������
local STEP = ActivitySetting[1].STEP
STEP[1] =
{
	Time = 300,                                              --ʱ��
	AssignType = Activity.ASSIGN_TYPE.DONOT_NEED,   
	GroupType = Activity.GROUP_TYPE.DONNOT_GROUP,
	GroupNum = 2,                                            -- С�����ȵİ��ģʽ
	MaxPlayer = 400,                                          -- ����ܲμӵ������
	Type = Activity.STEP_TYPE.ZHUNBEICHANG,                   -- ��������
	Enemy = {0,0,0,0,0},                                      -- ��������Ͳ����ٷ��飬����ҹ�ϵ�ж��Ƿ����
	Pos = {801,4567,4353,1048576},
	NPC =
	{},
    LOCK = 
    {},
    NextSteps = {},
}
--]]