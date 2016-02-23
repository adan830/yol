-- 40������ͨ�Ѷȣ����˸��������ļ�

Include("script/mission/multiinstance/multi_def.lua")

if not MultiInstance.tbSetting then
	MultiInstance.tbSetting = {}
end

local tbMultiSetting = MultiInstance.tbSetting;

tbMultiSetting[557]=
{
	nTimeLimit = 1200,  --����ʱ��20����
	nMapId = 557,
    tbBeginPos = {6552, 1321, 1048576},

    -- �����漰��NPC����
	NPC =
	{
	-- 		���  	npcģ��				�ȼ�(-1Ĭ�����npcpro��)	5��(Ĭ��-1)
        [1] = {nTemplate = 2170, nLevel = -1, nSeries = -1},		-- �������
		[2] = {nTemplate = 2171, nLevel = -1, nSeries = -1},		-- �����ҽ���
		[3] = {nTemplate = 2172, nLevel = -1, nSeries = -1},		-- ��������
		[4] = {nTemplate = 2173, nLevel = -1, nSeries = -1},		-- ��������
},
    LOCK =
    {
       -- 1�������ܲ��Ĭ��1��Ϊ��ʼ��
		[1] = {nTime = 1, nNum = 0,		-- �ܼ�ʱ
			tbPrelock = {},
			tbStartEvent =
			{
			    {MultiInstance.TIME_INFO, Lang.mission.str865[Lang.Idx]},
				{MultiInstance.REVIVE_INFO, true, true, false},
				{MultiInstance.SHOW_NOTICE_MSG, Lang.mission.str866[Lang.Idx]},
			},
			tbUnLockEvent =
			{
			},
		},
		[2] = {nTime = 0, nNum = 4 ,		-- ��ͨ����������ʱ�䵹��ʱ��ɱ�ָ�����
			tbPrelock = {1},
			tbStartEvent =
			{
				{MultiInstance.ADD_NPC, 1, 1, 2, "1", "1"},
				{MultiInstance.ADD_NPC, 2, 1, 2, "2", "2"},
				{MultiInstance.ADD_NPC, 3, 1, 2, "3", "3"},
				{MultiInstance.ADD_NPC, 4, 1, 2, "4", "4"},
				{MultiInstance.TARGET_INFO, Lang.mission.str866[Lang.Idx], 1}
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
				{MultiInstance.TIME_INFO, Lang.mission.str858[Lang.Idx], 3},
			},
			tbUnLockEvent =
			{
				{MultiInstance.DO_SCRIPT, "self.bFinish = 1"},
			},
		}
    }
}
