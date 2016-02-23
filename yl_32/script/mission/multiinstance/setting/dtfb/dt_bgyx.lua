-- 40������ͨ�Ѷȣ����˸��������ļ�

Include("script/mission/multiinstance/multi_def.lua")

if not MultiInstance.tbSetting then
	MultiInstance.tbSetting = {}
end

local tbMultiSetting = MultiInstance.tbSetting;

tbMultiSetting[551]=
{
	nTimeLimit = 1200,  --����ʱ��20����
	nMapId = 551,
    tbBeginPos = {6993, 1290, 1048576},

    -- �����漰��NPC����
	NPC =
	{
	-- 		���  	npcģ��				�ȼ�(-1Ĭ�����npcpro��)	5��(Ĭ��-1)
        [1] = {nTemplate = 2110, nLevel = -1, nSeries = -1},		-- С��
		[2] = {nTemplate = 2111, nLevel = -1, nSeries = -1},		-- �׹�
		[3] = {nTemplate = 2112, nLevel = -1, nSeries = -1},		-- ����
		[4] = {nTemplate = 2113, nLevel = -1, nSeries = -1},		-- ʬ����
		[5] = {nTemplate = 2114, nLevel = -1, nSeries = -1},		-- ʬ���
		[6] = {nTemplate = 2115, nLevel = -1, nSeries = -1},		-- ʬ����
		[7] = {nTemplate = 2116, nLevel = -1, nSeries = -1},		-- ʬ����
	},

    LOCK =
    {
       -- 1�������ܲ��Ĭ��1��Ϊ��ʼ��
		[1] = {nTime = 1, nNum = 0,		-- �ܼ�ʱ
			tbPrelock = {},
			tbStartEvent =
			{
			    {MultiInstance.TIME_INFO, Lang.mission.str862[Lang.Idx]},
				{MultiInstance.REVIVE_INFO, true, true, false},
				{MultiInstance.SHOW_NOTICE_MSG, Lang.mission.str863[Lang.Idx]},
			},
			tbUnLockEvent =
			{
			},
		},
		[2] = {nTime = 0, nNum = 29 ,		-- ��ͨ����������ʱ�䵹��ʱ��ɱ�ָ�����
			tbPrelock = {1},
			tbStartEvent =
			{
				{MultiInstance.ADD_NPC, 1, 9, 2, "xiaogui", "xiaogui"},
				{MultiInstance.ADD_NPC, 2, 1, 2, "xiaogui1", "xiaogui1"},
				{MultiInstance.ADD_NPC, 3, 8, 2, "gongbing", "gongbing"},
				{MultiInstance.ADD_NPC, 4, 1, 2, "gongbing1", "gongbing1"},
				{MultiInstance.ADD_NPC, 5, 8, 2, "daobing", "daobing"},
				{MultiInstance.ADD_NPC, 6, 1, 2, "daobing1", "daobing1"},
				{MultiInstance.ADD_NPC, 7, 1, 2, "boss", "boss"},
                {MultiInstance.TARGET_INFO, Lang.mission.str864[Lang.Idx], 1},
			},
			tbUnLockEvent =
			{
			},
		},
		[3] = {nTime = 1, nNum = 0 ,		-- ��ͨ����������ʱ�䵹��ʱ��ɱ�ָ�����
			tbPrelock = {2},
			tbStartEvent =
			{
			},
			tbUnLockEvent =
			{
				{MultiInstance.DO_SCRIPT, "self.bCanTakeAward = 1"},
			},
	    },
		[4] = {nTime = 10, nNum = 0 ,		-- �ܼ�ʱ
			tbPrelock = {3},
			tbStartEvent =
			{
				{MultiInstance.TARGET_INFO, Lang.mission.str857[Lang.Idx]},
				{MultiInstance.TIME_INFO, Lang.mission.str858[Lang.Idx], 1},
			},
			tbUnLockEvent =
			{
				{MultiInstance.DO_SCRIPT, "self.bFinish = 1"},
			},
		}
    }
}
