-- 30������ͨ�Ѷȣ����˸��������ļ�

Include("script/mission/multiinstance/multi_def.lua")

if not MultiInstance.tbSetting then
	MultiInstance.tbSetting = {}
end

local tbMultiSetting = MultiInstance.tbSetting;

tbMultiSetting[316]=
{
	nTimeLimit = 600,  --����ʱ��20����
	nMapId = 316,
    tbBeginPos = {1405, 6749, 1048576},
	nGameType = MultiInstance.GAME_TYPE.LV_30_EASY,
	nMultiLevel = 30,
	nDifficulty = 1,

    -- �����漰��NPC����
	NPC =
	{
	-- 		���  	npcģ��				�ȼ�(-1Ĭ�����npcpro��)	5��(Ĭ��-1)
        [1] = {nTemplate = 1348, nLevel = -1, nSeries = -1},		-- ��1�㣨��1��             ��һ��
		[2] = {nTemplate = 1349, nLevel = -1, nSeries = -1},		-- ��1�㣨��2��
		[3] = {nTemplate = 1350, nLevel = -1, nSeries = -1},		-- ��1�㣨��3��
		[4] = {nTemplate = 1351, nLevel = -1, nSeries = -1},		-- ��1�㣨��4��
		[5] = {nTemplate = 1304, nLevel = -1, nSeries = -1},		-- ��1�㣨�汦�䣩
		[6] = {nTemplate = 1305, nLevel = -1, nSeries = -1},		-- ��1�㣨�ٱ��䣩
		[7] = {nTemplate = 1306, nLevel = -1, nSeries = -1},		-- ��1�㣨�ٱ��䣩
		[8] = {nTemplate = 1307, nLevel = -1, nSeries = -1},		-- ��1�㣨�ٱ��䣩
		[9] = {nTemplate = 1352, nLevel = -1, nSeries = -1},		-- ��1�㣨����ˮ�������
		[10] = {nTemplate = 1353, nLevel = -1, nSeries = -1},		-- ��1�㣨����ˮ����
		[11] = {nTemplate = 1310, nLevel = -1, nSeries = -1},		-- ��1�㣨����
		[12] = {nTemplate = 1354, nLevel = -1, nSeries = -1},		-- ��1�㣨������һ�㣩
		[13] = {nTemplate = 1312, nLevel = -1, nSeries = -1},		-- ��1�㣨�ٱ�����Ч��
		[14] = {nTemplate = 1313, nLevel = -1, nSeries = -1},		-- ��1�㣨�ٱ�����Ч��
		[15] = {nTemplate = 1314, nLevel = -1, nSeries = -1},		-- ��1�㣨�ٱ�����Ч?
		[16] = {nTemplate = 1355, nLevel = -1, nSeries = -1},		-- ��2�㣨��1��            �ڶ���
		[17] = {nTemplate = 1356, nLevel = -1, nSeries = -1},		-- ��2�㣨��2��
		[18] = {nTemplate = 1357, nLevel = -1, nSeries = -1},		-- ��2�㣨��3��
		[19] = {nTemplate = 1358, nLevel = -1, nSeries = -1},		-- ��2�㣨��4��
		[20] = {nTemplate = 1319, nLevel = -1, nSeries = -1},		-- ��2�㣨�汦�䣩
		[21] = {nTemplate = 1320, nLevel = -1, nSeries = -1},		-- ��2�㣨�ٱ��䣩
	    [22] = {nTemplate = 1321, nLevel = -1, nSeries = -1},		-- ��2�㣨�ٱ��䣩
	    [23] = {nTemplate = 1322, nLevel = -1, nSeries = -1},		-- ��2�㣨�ٱ��䣩
		[24] = {nTemplate = 1359, nLevel = -1, nSeries = -1},		-- ��2�㣨����ˮ�������
		[25] = {nTemplate = 1360, nLevel = -1, nSeries = -1},		-- ��2�㣨����ˮ����
		[26] = {nTemplate = 1325, nLevel = -1, nSeries = -1},		-- ��2�㣨����
		[27] = {nTemplate = 1361, nLevel = -1, nSeries = -1},		-- ��2�㣨������һ�㣩
		[28] = {nTemplate = 1327, nLevel = -1, nSeries = -1},		-- ��2�㣨�ٱ�����Ч��
		[29] = {nTemplate = 1328, nLevel = -1, nSeries = -1},		-- ��2�㣨�ٱ�����Ч��
		[30] = {nTemplate = 1329, nLevel = -1, nSeries = -1},		-- ��2�㣨�ٱ�����Ч?
		[31] = {nTemplate = 1362, nLevel = -1, nSeries = -1},		-- ��3�㣨��1��            ������
		[32] = {nTemplate = 1363, nLevel = -1, nSeries = -1},		-- ��3�㣨��2��
		[33] = {nTemplate = 1364, nLevel = -1, nSeries = -1},		-- ��3�㣨��3��
		[34] = {nTemplate = 1365, nLevel = -1, nSeries = -1},		-- ��3�㣨��4��
		[35] = {nTemplate = 1334, nLevel = -1, nSeries = -1},		-- ��3�㣨�汦�䣩
		[36] = {nTemplate = 1335, nLevel = -1, nSeries = -1},		-- ��3�㣨�ٱ��䣩
	    [37] = {nTemplate = 1336, nLevel = -1, nSeries = -1},		-- ��3�㣨�ٱ��䣩
	    [38] = {nTemplate = 1337, nLevel = -1, nSeries = -1},		-- ��3�㣨�ٱ��䣩
		[39] = {nTemplate = 1366, nLevel = -1, nSeries = -1},		-- ��3�㣨����ˮ�������
		[40] = {nTemplate = 1367, nLevel = -1, nSeries = -1},		-- ��3�㣨����ˮ����
		[41] = {nTemplate = 1340, nLevel = -1, nSeries = -1},		-- ��3�㣨����
		[42] = {nTemplate = 1368, nLevel = -1, nSeries = -1},		-- ��3�㣨������һ�㣩
		[43] = {nTemplate = 1342, nLevel = -1, nSeries = -1},		-- ��3�㣨�ٱ�����Ч��
		[44] = {nTemplate = 1343, nLevel = -1, nSeries = -1},		-- ��3�㣨�ٱ�����Ч��
		[45] = {nTemplate = 1344, nLevel = -1, nSeries = -1},		-- ��3�㣨�ٱ�����Ч?
		[46] = {nTemplate = 1345, nLevel = -1, nSeries = -1},		-- ��ˮ������Ч
		[47] = {nTemplate = 1346, nLevel = 40, nSeries = -1},		-- ����������
	},

    LOCK =
    {
       -- 1�������ܲ��Ĭ��1��Ϊ��ʼ��
		[1] = {nTime = 1, nNum = 0,		-- �ܼ�ʱ
			tbPrelock = {},
			tbStartEvent =
			{
			    {MultiInstance.TIME_INFO, Lang.mission.str964[Lang.Idx]},
				{MultiInstance.REVIVE_INFO, true, true, false},
				{MultiInstance.SHOW_NOTICE_MSG, Lang.mission.str965[Lang.Idx]},
				{MultiInstance.TARGET_INFO, Lang.mission.str966[Lang.Idx], 1},
			},
			tbUnLockEvent =
			{
			},
		},
		[2] = {nTime = 0, nNum = 1 ,		-- ��ͨ����������ʱ�䵹��ʱ��ɱ�ָ�����
			tbPrelock = {1},
			tbStartEvent =
			{
				{MultiInstance.ADD_NPC, 1, 1, 2, "shui1", "shuijing1"},        --
				{MultiInstance.ADD_NPC, 2, 1, 2, "shui11", "shuijing11"},      --
				{MultiInstance.ADD_NPC, 3, 1, 2, "shui111", "shuijing111"},     --
				{MultiInstance.ADD_NPC, 4, 1, 2, "shui1111", "shuijing1111"},    --
				{MultiInstance.ADD_NPC, 5, 1, 2, "zhen1", "zhen1"},
				{MultiInstance.ADD_NPC, 6, 1, 4, "jia1", "jia1"},
				{MultiInstance.ADD_NPC, 7, 1, 5, "jia11", "jia11"},
				{MultiInstance.ADD_NPC, 8, 1, 6, "jia111", "jia111"},
				{MultiInstance.ADD_NPC, 9, 1, 2, "fanhui1", "fanhui1"},
				{MultiInstance.ADD_NPC, 10, 3, 2, "fanhui", "fanhui"},
				--{MultiInstance.TIME_INFO, "<color=yellow>         ���ޱ���\\r\\r<color=green>����ʣ��ʱ�䣺%s"},
				--{MultiInstance.TARGET_INFO, "<color=yellow>�����淨��<color=white>\\r���<color=green>���ޱ���<color=white>�������ҿ�����\\r\\r�汦��Ὺ����<color=green>��ʱ�����<color=white>\\r\\r����ﱻ��ܿ�����һ��\\r\\r<color=yellow>Ŀ�꣺������Ĳ���������������\\r", 1},
			},
			tbUnLockEvent =
			{
			{MultiInstance.DEL_NPC, "zhen1"},
			{MultiInstance.DEL_NPC, "fanhui1"},
			{MultiInstance.ADD_NPC, 46, 1, 2, "texiao", "texiao"},
			},
		},
		[3] = {nTime = 20, nNum = 1 ,		--
			tbPrelock = {2},
			tbStartEvent =
			{   --
				{MultiInstance.ADD_NPC, 11, 1, 3, "houzi", "houzi"},
				{MultiInstance.SHOW_NOTICE_MSG, Lang.mission.str967[Lang.Idx]},
			},
			tbUnLockEvent =
			{
			   {MultiInstance.DEL_NPC, "houzi"},

			},
		},
		[4] = {nTime = 0, nNum = 1 ,		--
			tbPrelock = {1},
			tbStartEvent =
			{   --
			},
			tbUnLockEvent =
			{
			   {MultiInstance.ADD_NPC, 13, 1, 4, "kong1", "jia1"},
			},
		},
		[5] = {nTime = 0, nNum = 1 ,		--
			tbPrelock = {1},
			tbStartEvent =
			{   --

			},
			tbUnLockEvent =
			{
			   {MultiInstance.ADD_NPC, 14, 1, 5, "kong11", "jia11"},
			},
		},
		[6] = {nTime = 0, nNum = 1 ,		--
			tbPrelock = {1},
			tbStartEvent =
			{   --

			},
			tbUnLockEvent =
			{
			   {MultiInstance.ADD_NPC, 15, 1, 6, "kong111", "jia111"},
			},
		},
		[7] = {nTime = 2, nNum = 0 ,		--
			tbPrelock = {3},
			tbStartEvent =
			{   --
				{MultiInstance.ADD_NPC, 12, 1, 7, "next", "next"},
				--{MultiInstance.TARGET_INFO, "Ŀ�꣺���������ı���", 2}, --
			    {MultiInstance.SHOW_NOTICE_MSG, Lang.mission.str968[Lang.Idx]},
			},
			tbUnLockEvent =
			{
			},
		},
		[8] = {nTime = 0, nNum = 1 ,		-- ��ͨ����������ʱ�䵹��ʱ��ɱ�ָ�����
			tbPrelock = {7},
			tbStartEvent =
			{
				{MultiInstance.ADD_NPC, 16, 1, 8, "shui2", "shuijing2"},        --
				{MultiInstance.ADD_NPC, 17, 1, 8, "shui22", "shuijing22"},      --
				{MultiInstance.ADD_NPC, 18, 1, 8, "shui222", "shuijing222"},     --
				{MultiInstance.ADD_NPC, 19, 1, 8, "shui2222", "shuijing2222"},    --
				{MultiInstance.ADD_NPC, 20, 1, 8, "zhen2", "zhen2"},
				{MultiInstance.ADD_NPC, 21, 1, 10, "jia2", "jia2"},
				{MultiInstance.ADD_NPC, 22, 1, 11, "jia22", "jia22"},
				{MultiInstance.ADD_NPC, 23, 1, 12, "jia222", "jia222"},
				{MultiInstance.ADD_NPC, 24, 1, 8, "fanhui22", "fanhui22"},
				{MultiInstance.ADD_NPC, 25, 3, 8, "fanhui2", "fanhui2"},			--
				--{MultiInstance.TARGET_INFO, "Ŀ�꣺���������ı���", 5}, --
			},
			tbUnLockEvent =
			{
			{MultiInstance.DEL_NPC, "zhen2"},
			{MultiInstance.DEL_NPC, "fanhui22"},
			{MultiInstance.ADD_NPC, 46, 1, 8, "texiao2", "texiao2"},
			},
		},
		[9] = {nTime = 25, nNum = 1 ,		--
			tbPrelock = {8},
			tbStartEvent =
			{   --
				{MultiInstance.ADD_NPC, 26, 1, 9, "houzi2", "houzi2"},
				{MultiInstance.SHOW_NOTICE_MSG, Lang.mission.str969[Lang.Idx]},
			},
			tbUnLockEvent =
			{
			   {MultiInstance.DEL_NPC, "houzi2"},

			},
		},
		[10] = {nTime = 0, nNum = 1 ,		--
			tbPrelock = {7},
			tbStartEvent =
			{   --
			},
			tbUnLockEvent =
			{
			   {MultiInstance.ADD_NPC, 28, 1, 10, "kong2", "jia2"},
			},
		},
		[11] = {nTime = 0, nNum = 1 ,		--
			tbPrelock = {7},
			tbStartEvent =
			{   --

			},
			tbUnLockEvent =
			{
			   {MultiInstance.ADD_NPC, 29, 1, 11, "kong22", "jia22"},
			},
		},
		[12] = {nTime = 0, nNum = 1 ,		--
			tbPrelock = {7},
			tbStartEvent =
			{   --

			},
			tbUnLockEvent =
			{
			   {MultiInstance.ADD_NPC, 30, 1, 12, "kong222", "jia222"},
			},
		},
		[13] = {nTime = 2, nNum = 0 ,		--
			tbPrelock = {9},
			tbStartEvent =
			{   --
				{MultiInstance.ADD_NPC, 27, 1, 13, "next2", "next2"},
				--{MultiInstance.TARGET_INFO, "Ŀ�꣺���������ı���", 2}, --
			    {MultiInstance.SHOW_NOTICE_MSG, Lang.mission.str968[Lang.Idx]},
			},
			tbUnLockEvent =
			{
			},
		},
		[14] = {nTime = 0, nNum = 1 ,		-- ��ͨ����������ʱ�䵹��ʱ��ɱ�ָ�����
			tbPrelock = {13},
			tbStartEvent =
			{
				{MultiInstance.ADD_NPC, 31, 1, 14, "shui3", "shuijing3"},        --
				{MultiInstance.ADD_NPC, 32, 1, 14, "shui33", "shuijing33"},      --
				{MultiInstance.ADD_NPC, 33, 1, 14, "shui333", "shuijing333"},     --
				{MultiInstance.ADD_NPC, 34, 1, 14, "shui3333", "shuijing3333"},    --
				{MultiInstance.ADD_NPC, 35, 1, 14, "zhen3", "zhen3"},
				{MultiInstance.ADD_NPC, 36, 1, 16, "jia3", "jia3"},
				{MultiInstance.ADD_NPC, 37, 1, 17, "jia33", "jia33"},
				{MultiInstance.ADD_NPC, 38, 1, 18, "jia333", "jia333"},
				{MultiInstance.ADD_NPC, 39, 1, 14, "fanhui33", "fanhui33"},
				{MultiInstance.ADD_NPC, 40, 3, 14, "fanhui3", "fanhui3"},			--
				--{MultiInstance.TARGET_INFO, "Ŀ�꣺���������ı���", 5}, --
			},
			tbUnLockEvent =
			{
			{MultiInstance.DEL_NPC, "zhen3"},
			{MultiInstance.DEL_NPC, "fanhui33"},
			{MultiInstance.ADD_NPC, 46, 1, 14, "texiao3", "texiao3"},
			},
		},
		[15] = {nTime = 30, nNum = 1 ,		--
			tbPrelock = {14},
			tbStartEvent =
			{   --
				{MultiInstance.ADD_NPC, 41, 1, 15, "houzi3", "houzi3"},
				{MultiInstance.SHOW_NOTICE_MSG, Lang.mission.str970[Lang.Idx]},
			},
			tbUnLockEvent =
			{
			   {MultiInstance.DEL_NPC, "houzi3"},

			},
		},
		[16] = {nTime = 0, nNum = 1 ,		--
			tbPrelock = {13},
			tbStartEvent =
			{   --
			},
			tbUnLockEvent =
			{
			   {MultiInstance.ADD_NPC, 43, 1, 16, "kong3", "jia3"},
			},
		},
		[17] = {nTime = 0, nNum = 1 ,		--
			tbPrelock = {13},
			tbStartEvent =
			{   --

			},
			tbUnLockEvent =
			{
			   {MultiInstance.ADD_NPC, 44, 1, 17, "kong33", "jia33"},
			},
		},
		[18] = {nTime = 0, nNum = 1 ,		--
			tbPrelock = {13},
			tbStartEvent =
			{   --

			},
			tbUnLockEvent =
			{
			   {MultiInstance.ADD_NPC, 45, 1, 18, "kong333", "jia333"},
			},
		},
		[19] = {nTime = 2, nNum = 0 ,		--
			tbPrelock = {15},
			tbStartEvent =
			{   --
				{MultiInstance.ADD_NPC, 42, 1, 19, "next3", "next3"},
			    {MultiInstance.SHOW_NOTICE_MSG, Lang.mission.str968[Lang.Idx]},
			},
			tbUnLockEvent =
			{
			},
		},
		[20] = {nTime = 0, nNum = 1 ,		--
			tbPrelock = {19},
			tbStartEvent =
			{   --
				{MultiInstance.ADD_NPC, 47, 1, 20, "boss", "boss"},
			    {MultiInstance.SHOW_NOTICE_MSG, Lang.mission.str971[Lang.Idx]},
				{MultiInstance.TARGET_INFO, Lang.mission.str966[Lang.Idx], 1},
			},
			tbUnLockEvent =
			{
				{MultiInstance.DO_SCRIPT, "self.bCanTakeAward = 1"},
			},
		},
		[21] = {nTime = 10, nNum = 0 ,		-- �ܼ�ʱ
			tbPrelock = {20},
			tbStartEvent =
			{
				{MultiInstance.TARGET_INFO, Lang.mission.str857[Lang.Idx]},
				{MultiInstance.TIME_INFO, Lang.mission.str858[Lang.Idx]},
			},
			tbUnLockEvent =
			{
				{MultiInstance.DO_SCRIPT, "self.bFinish = 1"},
			},
		}
    }
}
