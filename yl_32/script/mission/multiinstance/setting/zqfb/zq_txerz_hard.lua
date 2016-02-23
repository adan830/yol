-- 40������ͨ�Ѷȣ����˸��������ļ�

Include("script/mission/multiinstance/multi_def.lua")

if not MultiInstance.tbSetting then
	MultiInstance.tbSetting = {}
end

local tbMultiSetting = MultiInstance.tbSetting;

tbMultiSetting[317]=
{
	nTimeLimit = 600,  --����ʱ��20����
	nMapId = 317,
    tbBeginPos = {6010, 960, 1048576},

    -- �����漰��NPC����
	NPC =
	{
	-- 		���  	npcģ��				�ȼ�(-1Ĭ�����npcpro��)	5��(Ĭ��-1)
        [1] = {nTemplate = 1380, nLevel = -1, nSeries = -1},		-- ����
		[2] = {nTemplate = 1381, nLevel = 50, nSeries = -1},		-- ��1-Ѳ��
		[3] = {nTemplate = 1382, nLevel = 50, nSeries = -1},		-- ����-Ѳ�ߣ�����
		[4] = {nTemplate = 1383, nLevel = 50, nSeries = -1},		-- ֧Ԯ(ͨ��)
		[5] = {nTemplate = 1384, nLevel = -1, nSeries = -1},		-- ��ɱ��ͨ�ã�
		[6] = {nTemplate = 1385, nLevel = 50, nSeries = -1},		-- ��2-Ѳ��
		[7] = {nTemplate = 1386, nLevel = 50, nSeries = -1},		-- ��3-Ѳ��
		[8] = {nTemplate = 1387, nLevel = 50, nSeries = -1},		-- ����1-Ѳ��
		[9] = {nTemplate = 1388, nLevel = 50, nSeries = -1},		-- ����2-Ѳ��
		[10] = {nTemplate = 1389, nLevel = 50, nSeries = -1},		-- ����1-Ѳ��
		[11] = {nTemplate = 1390, nLevel = 50, nSeries = -1},		-- ����2-Ѳ��
		[12] = {nTemplate = 1391, nLevel = 50, nSeries = -1},		-- կ��boss
		[13] = {nTemplate = 1392, nLevel = -1, nSeries = -1},		-- ͸����ɱ
	},

    LOCK =
    {
       -- 1�������ܲ��Ĭ��1��Ϊ��ʼ��
		[1] = {nTime = 1, nNum = 0,		-- �ܼ�ʱ
			tbPrelock = {},
			tbStartEvent =
			{
			    {MultiInstance.TIME_INFO, Lang.mission.str972[Lang.Idx]},
				{MultiInstance.REVIVE_INFO, true, true, false},
				{MultiInstance.SHOW_NOTICE_MSG, Lang.mission.str973[Lang.Idx]},
			},
			tbUnLockEvent =
			{
			},
		},
		[2] = {nTime = 0, nNum = 6 ,		-- ��ͨ����������ʱ�䵹��ʱ��ɱ�ָ�����
			tbPrelock = {1},
			tbStartEvent =
			{
				{MultiInstance.ADD_NPC, 1, 5, 2, "renzhi", "renzhi"},
				{MultiInstance.ADD_NPC, 1, 1, 2, "renzhi1", "renzhi1"},
				{MultiInstance.ADD_NPC, 2, 1, 2, "shouwei1", "shouwei1"},
				{MultiInstance.ADD_NPC, 3, 1, 2, "shouwei8", "shouwei8"},
				{MultiInstance.ADD_NPC, 6, 1, 2, "shouwei2", "shouwei2"},
				{MultiInstance.ADD_NPC, 7, 1, 2, "shouwei3", "shouwei3"},
				{MultiInstance.ADD_NPC, 8, 1, 2, "shouwei4", "shouwei4"},
				{MultiInstance.ADD_NPC, 9, 1, 2, "shouwei5", "shouwei5"},
				{MultiInstance.ADD_NPC, 10, 1, 2, "shouwei6", "shouwei6"},
				{MultiInstance.ADD_NPC, 11, 1, 2, "shouwei7", "shouwei7"},
				{MultiInstance.ADD_NPC, 13, 3, 9, "zisha", "zisha"},
				{MultiInstance.ADD_NPC, 5, 2, 3, "beisha1", "beisha1"},
                {MultiInstance.TARGET_INFO, Lang.mission.str974[Lang.Idx], 1},
			},
			tbUnLockEvent =
			{
			},
		},
        [3] = {nTime = 0, nNum = 1 ,		-- ��ͨ����������ʱ�䵹��ʱ��ɱ�ָ�����
			tbPrelock = {1},
			tbStartEvent =
			{

			},
			tbUnLockEvent =
			{
			{MultiInstance.SHOW_NOTICE_MSG, Lang.mission.str975[Lang.Idx]},
			},
		},
		[4] = {nTime = 2, nNum = 0 ,		-- ��ͨ����������ʱ�䵹��ʱ��ɱ�ָ�����
			tbPrelock = {3},
			tbStartEvent =
			{

			},
			tbUnLockEvent =
			{
				{MultiInstance.ADD_NPC, 4, 7, 4, "shibing1", "shibing1"},
			},
		},
		[5] = {nTime = 0, nNum = 1 ,		-- ��ͨ����������ʱ�䵹��ʱ��ɱ�ָ�����
			tbPrelock = {3},
			tbStartEvent =
			{
                {MultiInstance.ADD_NPC, 5, 2, 5, "beisha2", "beisha"},
			},
			tbUnLockEvent =
			{
			{MultiInstance.SHOW_NOTICE_MSG, Lang.mission.str975[Lang.Idx]},
			},
		},
		[6] = {nTime = 2, nNum = 0 ,		-- ��ͨ����������ʱ�䵹��ʱ��ɱ�ָ�����
			tbPrelock = {5},
			tbStartEvent =
			{

			},
			tbUnLockEvent =
			{
				{MultiInstance.ADD_NPC, 4, 7, 6, "shibing2", "shibing2"},
			},
		},
		[7] = {nTime = 0, nNum = 1 ,		-- ��ͨ����������ʱ�䵹��ʱ��ɱ�ָ�����
			tbPrelock = {5},
			tbStartEvent =
			{
				{MultiInstance.ADD_NPC, 5, 2, 7, "beisha3", "beisha"},
			},
			tbUnLockEvent =
			{
			{MultiInstance.SHOW_NOTICE_MSG, Lang.mission.str975[Lang.Idx]},
			},
		},
		[8] = {nTime = 2, nNum = 0 ,		-- ��ͨ����������ʱ�䵹��ʱ��ɱ�ָ�����
			tbPrelock = {7},
			tbStartEvent =
			{

			},
			tbUnLockEvent =
			{
				{MultiInstance.ADD_NPC, 4, 7, 8, "shibing3", "shibing3"},
			},
		},
		[9] = {nTime = 0, nNum = 1 ,		-- ��ͨ����������ʱ�䵹��ʱ��ɱ�ָ�����
			tbPrelock = {1},
			tbStartEvent =
			{

			},
			tbUnLockEvent =
			{
			{MultiInstance.SHOW_NOTICE_MSG, Lang.mission.str976[Lang.Idx]},
			{MultiInstance.DEL_NPC, "renzhi1"},
			},
		},
		[10] = {nTime = 2, nNum = 0 ,		-- ��ͨ����������ʱ�䵹��ʱ��ɱ�ָ�����
			tbPrelock = {9},
			tbStartEvent =
			{

			},
			tbUnLockEvent =
			{
				{MultiInstance.ADD_NPC, 12, 1, 11, "boss", "boss"},
			},
		},
		[11] = {nTime = 0, nNum = 1 ,		-- ��ͨ����������ʱ�䵹��ʱ��ɱ�ָ�����
			tbPrelock = {10},
			tbStartEvent =
			{

			},
			tbUnLockEvent =
			{
			{MultiInstance.ADD_NPC, 1, 1, 2, "renzhi1", "renzhi1"},
			},
		},
		[12] = {nTime = 4, nNum = 0 ,		-- ��ͨ����������ʱ�䵹��ʱ��ɱ�ָ�����
			tbPrelock = {2},
			tbStartEvent =
			{
			{MultiInstance.SHOW_NOTICE_MSG, Lang.mission.str977[Lang.Idx]},
			},
			tbUnLockEvent =
			{
				{MultiInstance.DO_SCRIPT, "self.bCanTakeAward = 1"},
			},
	    },
		[13] = {nTime = 10, nNum = 0 ,		-- �ܼ�ʱ
			tbPrelock = {12},
			tbStartEvent =
			{
				{MultiInstance.TARGET_INFO, Lang.mission.str857[Lang.Idx]},
				{MultiInstance.TIME_INFO, Lang.mission.str858[Lang.Idx], 3},
			},
			tbUnLockEvent =
			{
				{MultiInstance.DO_SCRIPT, "self.bFinish = 1"},
			},
		},
		[14] = {nTime = 0, nNum = 1 ,		-- Ϊ���Ѹ������
			tbPrelock = {7},
			tbStartEvent =
			{
				{MultiInstance.ADD_NPC, 5, 2, 14, "beisha4", "beisha"},
			},
			tbUnLockEvent =
			{
			{MultiInstance.SHOW_NOTICE_MSG, Lang.mission.str1161[Lang.Idx]},
			},
		},
		[15] = {nTime = 2, nNum = 0 ,		-- Ϊ���Ѹ������
			tbPrelock = {14},
			tbStartEvent =
			{

			},
			tbUnLockEvent =
			{
				{MultiInstance.ADD_NPC, 4, 7, 8, "shibing4", "shibing3"},
			},
		}
    }
}
