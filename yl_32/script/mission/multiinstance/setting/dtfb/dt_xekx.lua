-- 40������ͨ�Ѷȣ����˸��������ļ�

Include("script/mission/multiinstance/multi_def.lua")

if not MultiInstance.tbSetting then
	MultiInstance.tbSetting = {}
end

local tbMultiSetting = MultiInstance.tbSetting;

tbMultiSetting[555]=
{
	nTimeLimit = 1200,  --����ʱ��20����
	nMapId = 555,
    tbBeginPos = {5581, 1086, 1048576},

    -- �����漰��NPC����
	NPC =
	{
	-- 		���  	npcģ��				�ȼ�(-1Ĭ�����npcpro��)	5��(Ĭ��-1)
        [1] = {nTemplate = 2150, nLevel = -1, nSeries = -1},		-- �������
		[2] = {nTemplate = 2151, nLevel = -1, nSeries = -1},		-- ��������
		[3] = {nTemplate = 2152, nLevel = -1, nSeries = -1},		-- �������
		[4] = {nTemplate = 2153, nLevel = -1, nSeries = -1},		-- ��������
		[5] = {nTemplate = 2154, nLevel = -1, nSeries = -1},		-- �������
		[6] = {nTemplate = 2155, nLevel = -1, nSeries = -1},		-- ��������
		[7] = {nTemplate = 2156, nLevel = -1, nSeries = -1},		-- �������
		[8] = {nTemplate = 2157, nLevel = -1, nSeries = -1},		-- ��������
	    [9] = {nTemplate = 2158, nLevel = -1, nSeries = -1},		-- ��н�
	},

    LOCK =
    {
       -- 1�������ܲ��Ĭ��1��Ϊ��ʼ��
		[1] = {nTime = 1, nNum = 0,		-- �ܼ�ʱ
			tbPrelock = {},
			tbStartEvent =
			{
			    {MultiInstance.TIME_INFO, Lang.mission.str875[Lang.Idx]},
				{MultiInstance.REVIVE_INFO, true, true, false},
				{MultiInstance.SHOW_NOTICE_MSG, Lang.mission.str884[Lang.Idx]},
			},
			tbUnLockEvent =
			{
			},
		},
		[2] = {nTime = 0, nNum = 33 ,		-- ��ͨ����������ʱ�䵹��ʱ��ɱ�ָ�����
			tbPrelock = {1},
			tbStartEvent =
			{
				{MultiInstance.ADD_NPC, 1, 7, 2, "dizi1", "dizi"},
				{MultiInstance.ADD_NPC, 2, 1, 2, "jingying1", "jingying"},
				{MultiInstance.ADD_NPC, 3, 7, 2, "dizi2", "dizi"},
				{MultiInstance.ADD_NPC, 4, 1, 2, "jingying2", "jingying"},
				{MultiInstance.ADD_NPC, 5, 7, 2, "dizi3", "dizi"},
				{MultiInstance.ADD_NPC, 6, 1, 2, "jingying3", "jingying"},
				{MultiInstance.ADD_NPC, 7, 7, 2, "dizi4", "dizi"},
				{MultiInstance.ADD_NPC, 8, 1, 2, "jingying4", "jingying"},
				{MultiInstance.ADD_NPC, 9, 1, 2, "boss", "boss"},
				{MultiInstance.TARGET_INFO, Lang.mission.str883[Lang.Idx], 1}
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
