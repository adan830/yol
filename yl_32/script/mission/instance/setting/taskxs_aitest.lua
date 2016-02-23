Include("script/mission/instance/instance_def.lua")
if not Instance.tbSetting then
	Instance.tbSetting = {}
end

local InstanceSetting = Instance.tbSetting;



InstanceSetting[1000]=
{
	nTaskInstance = 1;
    nMinLevel = 1;
    nMaxLevel = 60;
	nMapId = 1000;
    tbBeginPos = {988,803,104873},
	tbLeavePos = {3,6023,2065,1048576},

    -- �����漰��NPC����
	NPC =
	{
-- 		���  	npcģ��				�ȼ�(-1Ĭ��)	5��(Ĭ��-1)
        [1] = {nTemplate = 10000, nLevel = 1, nSeries = -1},		-- ������
		[2] = {nTemplate = 262, nLevel = 1, nSeries = -1},		-- ������
		[3] = {nTemplate = 10011, nLevel = 1, nSeries = -1},		-- ����
		[4] = {nTemplate = 10012, nLevel = 1, nSeries = -1},		-- ���򹥻�

	},

    LOCK =
    {
       -- 1�������ܲ��Ĭ��1��Ϊ��ʼ��
		[1] = {nTime = 1, nNum = 0,		-- �ܼ�ʱ
			tbPrelock = {},
			tbStartEvent =
			{
			    	{Instance.TIME_INFO, -1, Lang.mission.str229[Lang.Idx]},
			},
			tbUnLockEvent =
			{
			},
		},
		[2] = {nTime = 0, nNum = 30 ,		-- �ܼ�ʱ
			tbPrelock = {1},
			tbStartEvent =
			{
				{Instance.ADD_NPC, 1, 16, 2, "1", "flower"},
				--{Instance.ADD_NPC, 4, 1, 2, "3", "guangqiu"},
				{Instance.CLEAR_BUFF, -1, },
			},
			tbUnLockEvent =
			{
			},
		},
		[3] = {nTime = 1, nNum = 0 ,		-- �ܼ�ʱ
			tbPrelock = {2},
			tbStartEvent =
			{
			},
			tbUnLockEvent =
			{
				{Instance.DO_SCRIPT, "self.bFinishTask = 1"},
				{Instance.TARGET_INFO, -1, Lang.mission.str236[Lang.Idx]},
				{Instance.SHOW_REWARD_PANEL, -1, 0},
			    {Instance.DO_SCRIPT, "self.tbLock[4]:Close()"},
			},
		},
		[4] = {nTime = 0, nNum = 1,		-- �ܼ�ʱ
			tbPrelock = {1},
			tbStartEvent =
			{
			},
			tbUnLockEvent =
			{
             {Instance.REVIVE_INFO, true, true, false},
			},
		},

    }
}
