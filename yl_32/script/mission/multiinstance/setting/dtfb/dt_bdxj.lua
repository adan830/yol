-- 40������ͨ�Ѷȣ����˸��������ļ�

Include("script/mission/multiinstance/multi_def.lua")

if not MultiInstance.tbSetting then
	MultiInstance.tbSetting = {}
end

local tbMultiSetting = MultiInstance.tbSetting;

tbMultiSetting[550]=
{
	nTimeLimit = 1200,  --����ʱ��20����
	nMapId = 550,
    tbBeginPos = {6993, 1290, 1048576},

    -- �����漰��NPC����
	NPC =
	{
	-- 		���  	npcģ��				�ȼ�(-1Ĭ�����npcpro��)	5��(Ĭ��-1)
        [1] = {nTemplate = 2100, nLevel = -1, nSeries = -1},		-- �����
		[2] = {nTemplate = 2101, nLevel = -1, nSeries = -1},		-- ��ܾ�
		[3] = {nTemplate = 2102, nLevel = -1, nSeries = -1},		-- ����
		[4] = {nTemplate = 2103, nLevel = -1, nSeries = -1},		-- �Ӷ���
		[5] = {nTemplate = 2104, nLevel = -1, nSeries = -1},		-- ��֩��
		[6] = {nTemplate = 2105, nLevel = -1, nSeries = -1},		-- �ڹѸ�
		[7] = {nTemplate = 2106, nLevel = -1, nSeries = -1},		-- �ٶ�����
	},

    LOCK =
    {
       -- 1�������ܲ��Ĭ��1��Ϊ��ʼ��
		[1] = {nTime = 1, nNum = 0,		-- �ܼ�ʱ
			tbPrelock = {},
			tbStartEvent =
			{
			    {MultiInstance.TIME_INFO, Lang.mission.str859[Lang.Idx]},
				{MultiInstance.REVIVE_INFO, true, true, false},
				{MultiInstance.SHOW_NOTICE_MSG, Lang.mission.str860[Lang.Idx]},
			},
			tbUnLockEvent =
			{
			},
		},
		[2] = {nTime = 0, nNum = 29 ,		-- ��ͨ����������ʱ�䵹��ʱ��ɱ�ָ�����
			tbPrelock = {1},
			tbStartEvent =
			{
				{MultiInstance.ADD_NPC, 1, 8, 2, "chanchu", "chanchu"},
				{MultiInstance.ADD_NPC, 2, 1, 2, "chanchu1", "chanchu1"},
				{MultiInstance.ADD_NPC, 3, 9, 2, "feichong", "feichong"},
				{MultiInstance.ADD_NPC, 4, 1, 2, "feichong1", "feichong1"},
				{MultiInstance.ADD_NPC, 5, 8, 2, "zhizhu", "zhizhu"},
				{MultiInstance.ADD_NPC, 6, 1, 2, "zhizhu1", "zhizhu1"},
				{MultiInstance.ADD_NPC, 7, 1, 2, "boss", "boss"},
                {MultiInstance.TARGET_INFO, Lang.mission.str861[Lang.Idx], 1},
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
				{MultiInstance.TIME_INFO, Lang.mission.str858[Lang.Idx],1},
			},
			tbUnLockEvent =
			{
				{MultiInstance.DO_SCRIPT, "self.bFinish = 1"},
			},
		}
    }
}
