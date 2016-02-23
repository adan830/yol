Include("script/mission/level/xoyogame_def.lua");

local tbRoom = XoyoGame.RoomSetting.tbRoom;

tbRoom[20] =    --������41-45
{
	fnPlayerGroup 	= nil,						-- ��ҷ�Ⱥ����,������Ĭ��1֧����1��Ⱥ��
	fnDeath			= nil,						-- ���������ű�; ������Ĭ��
	fnWinRule		= nil,						-- ʤ��������������ķ�����Ҫ�ض��壬����һ�㲻��Ҫ��
	nRoomLevel		= 9,						-- ����ȼ�(1~5)
	nMapIndex		= 30,					-- ��ͼ�������
	nType           = 1,
	tbBeginPoint	= {1008, 1014, 1049093},	-- ��ʼ�㣬��ʽ����fnPlayerGroup���������Ĭ����{nX,nY}
	-- �����漰��NPC����
	NPC = 
	{
-- 		���  	npcģ��		�ȼ�(-1Ĭ��)(ǿ�ȱ�id��)	5��(Ĭ��-1)
-- E.g  [0] = {nTemplate, 			nLevel, 		nSeries }
		[1] = {nTemplate = 9008, nLevel = {9008}, nSeries = -1},		---�Ļ�
		[2] = {nTemplate = 9027, nLevel = {9027}, nSeries = -1},		-- Թ��
		[3] = {nTemplate = 9046, nLevel = {9027}, nSeries = -1},        --BOSS����
		[4] = {nTemplate = 9057, nLevel = {3}, nSeries = -1 },        --������
	},
	-- ���ṹ
	LOCK = 
	{
	-- 1�������ܲ��Ĭ��1��Ϊ��ʼ��
	[1] = {nTime = 10, nNum = 0,
		tbPrelock = {},
		tbStartEvent = 
		{
			{XoyoGame.TIME_INFO, -1, Lang.mission.str565[Lang.Idx], 1},
			{XoyoGame.TARGET_INFO, -1, ""},
			{XoyoGame.ADD_NPC, 4, 1, 0, "jieyinren", "dengtianjieyin1"},
		},
		tbUnLockEvent = 
		{
		},
	},
	[2] = {nTime = 480, nNum = 0,		-- �ܼ�ʱ
		tbPrelock = {1},
		tbStartEvent = 
		{
		},
		tbUnLockEvent = 
		{
			{XoyoGame.MOVIE_DIALOG, -1, Lang.mission.str566[Lang.Idx]},
			{XoyoGame.DEL_NPC, "guaiwu"},
			{XoyoGame.DEL_NPC, "boss"},
			{XoyoGame.DEL_NPC, "tishen"},
			{XoyoGame.TARGET_INFO, -1, Lang.mission.str567[Lang.Idx]},
			{XoyoGame.DO_SCRIPT, "self.tbTeam[1].bIsWiner = 0"},
		},
	},
	[3] = {nTime = 0, nNum = 3,       --ˢ��һ����
		tbPrelock = {1},
			tbStartEvent = 
			{
				{XoyoGame.ADD_NPC, 1, 3, 3, "guaiwu", "youhun9008"},		-- ˢ��
				{XoyoGame.ADD_NPC, 3, 1, 0, "tishen", "tishen9027"},
				{XoyoGame.TIME_INFO, -1, Lang.mission.str568[Lang.Idx], 2},
				{XoyoGame.TARGET_INFO, -1, Lang.mission.str569[Lang.Idx],1},
				{XoyoGame.DO_SCRIPT, "self.tbTeam[1].nWaveNum = 1"},
				
			},
			tbUnLockEvent = 
			{
			},
		},
	[4] = {nTime = 0, nNum = 3,      --ˢ�ڶ�����
		tbPrelock = {3},
		    tbStartEvent = 
			{
				{XoyoGame.ADD_NPC, 1, 3, 4, "guaiwu", "youhun9008"},		-- ˢ��
				{XoyoGame.TARGET_INFO, -1, Lang.mission.str570[Lang.Idx],1},
				{XoyoGame.DO_SCRIPT, "self.tbTeam[1].nWaveNum = 2"},
				
			},
			tbUnLockEvent = 
			{
			},
		},
	[5] = {nTime = 0, nNum = 4,      --ˢ��������
		tbPrelock = {4},
		    tbStartEvent = 
			{
				{XoyoGame.ADD_NPC, 1, 4,5, "guaiwu", "youhun9008"},		-- ˢ��
				{XoyoGame.TARGET_INFO, -1, Lang.mission.str571[Lang.Idx],5},
				{XoyoGame.DO_SCRIPT, "self.tbTeam[1].nWaveNum = 3"},
				
			},
			tbUnLockEvent = 
			{
			},
		},
	[6] = {nTime = 0, nNum = 4,      --ˢ��������
		tbPrelock = {5},
		    tbStartEvent = 
			{
				{XoyoGame.ADD_NPC, 1, 4, 6, "guaiwu", "youhun9008"},		-- ˢ��
				{XoyoGame.TARGET_INFO, -1, Lang.mission.str572[Lang.Idx],6},
				{XoyoGame.DO_SCRIPT, "self.tbTeam[1].nWaveNum = 4"},
				
			},
			tbUnLockEvent = 
			{
			},
		},
	[7] = {nTime = 0, nNum = 4,      --ˢ��������
		tbPrelock = {6},
		    tbStartEvent = 
			{
				{XoyoGame.ADD_NPC, 1, 4, 7, "guaiwu", "youhun9008"},		-- ˢ��
				{XoyoGame.TARGET_INFO, -1, Lang.mission.str573[Lang.Idx],7},
				{XoyoGame.DO_SCRIPT, "self.tbTeam[1].nWaveNum = 5"},
				
			},
			tbUnLockEvent = 
			{
			},
		},
	[8] = {nTime = 0, nNum = 5,      --ˢ��������
		tbPrelock = {7},
		    tbStartEvent = 
			{
				{XoyoGame.ADD_NPC, 1, 5,8, "guaiwu", "youhun9008"},		-- ˢ��
				{XoyoGame.TARGET_INFO, -1, Lang.mission.str574[Lang.Idx],8},
				{XoyoGame.DO_SCRIPT, "self.tbTeam[1].nWaveNum = 6"},
				
			},
			tbUnLockEvent = 
			{
			},
		},
	[9] = {nTime = 0, nNum = 5,      --ˢ��������
		tbPrelock = {8},
		    tbStartEvent = 
			{
				{XoyoGame.ADD_NPC, 1, 5, 9, "guaiwu", "youhun9008"},		-- ˢ��
				{XoyoGame.TARGET_INFO, -1, Lang.mission.str575[Lang.Idx],9},
				{XoyoGame.DO_SCRIPT, "self.tbTeam[1].nWaveNum = 7"},
				
			},
			tbUnLockEvent = 
			{
			},
		},
	[10] = {nTime = 0, nNum = 6,      --ˢ�ڰ�����
		tbPrelock = {9},
		    tbStartEvent = 
			{
				{XoyoGame.ADD_NPC, 1, 6, 10, "guaiwu", "youhun9008"},		-- ˢ��
				{XoyoGame.TARGET_INFO, -1, Lang.mission.str576[Lang.Idx],10},
				{XoyoGame.DO_SCRIPT, "self.tbTeam[1].nWaveNum = 8"},
				
			},
			tbUnLockEvent = 
			{
			},
		},
	[11] = {nTime = 0, nNum = 6,      --ˢ�ھ�����
		tbPrelock = {10},
		    tbStartEvent = 
			{
				{XoyoGame.ADD_NPC, 1, 6, 11, "guaiwu", "jingying9002"},		-- ˢ��
				{XoyoGame.TARGET_INFO, -1, Lang.mission.str577[Lang.Idx],11},
				{XoyoGame.DO_SCRIPT, "self.tbTeam[1].nWaveNum = 9"},
				
			},
			tbUnLockEvent = 
			{
			},
		},
	[12] = {nTime = 0, nNum = 5,      --ˢBOSS
		tbPrelock = {11},
		    tbStartEvent = 
			{
				{XoyoGame.DEL_NPC, "tishen"},
				{XoyoGame.ADD_NPC, 1, 4, 12, "guaiwu", "youhun9008"},		-- ˢ��
				{XoyoGame.ADD_NPC, 2, 1, 12, "boss", "yuanhun9027"},		-- ˢ��
				{XoyoGame.TARGET_INFO, -1, Lang.mission.str588[Lang.Idx],12},
				{XoyoGame.DO_SCRIPT, "self.tbTeam[1].nWaveNum = 10"},
				
			},
			tbUnLockEvent = 
			{
				{XoyoGame.DO_SCRIPT, "self.tbTeam[1].bIsWiner = 1"},		-- ����������ñ�־
				{XoyoGame.DO_SCRIPT, "self.tbLock[2]:Close()"},
				{XoyoGame.DEL_NPC, "boss"},
				{XoyoGame.DEL_NPC, "guaiwu"},
				{XoyoGame.CLOSE_INFO, -1},
				{XoyoGame.TARGET_INFO, -1, Lang.mission.str579[Lang.Idx]},
			},
		},	
	}
}				