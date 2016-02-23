Include("script/mission/level/xoyogame_def.lua");

local tbRoom = XoyoGame.RoomSetting.tbRoom;

tbRoom[43] =    --�Ұ�֮Ѫ
{
	fnPlayerGroup 	= nil,						-- ��ҷ�Ⱥ����,������Ĭ��1֧����1��Ⱥ��
	fnDeath			= nil,						-- ���������ű�; ������Ĭ��
	fnWinRule		= nil,						-- ʤ��������������ķ�����Ҫ�ض��壬����һ�㲻��Ҫ��
	nRoomLevel		= 2,						-- ����ȼ�(1~5)
	nMapIndex		= 44,						-- ��ͼ�������
	tbBeginPoint	= {1850, 769, 1052154},	-- ��ʼ�㣬��ʽ����fnPlayerGroup���������Ĭ����{nX,nY}
	-- �����漰��NPC����
	NPC = 
	{
-- 		���  	npcģ��		�ȼ�(-1Ĭ��)(ǿ�ȱ�id��)	5��(Ĭ��-1)
-- E.g  [0] = {nTemplate, 			nLevel, 		nSeries }
		[1] = {nTemplate = 8066, nLevel = {8153,8154,8154}, nSeries = -1},		-- �Ұ�֮Ѫ
	},
	-- ���ṹ
	LOCK = 
	{
		-- 1�������ܲ��Ĭ��1��Ϊ��ʼ��
		[1] = {nTime = 15, nNum = 0,
			tbPrelock = {},
			tbStartEvent = 
			{
				{XoyoGame.TIME_INFO, -1, Lang.mission.str600[Lang.Idx], 1},
				{XoyoGame.TARGET_INFO, -1, ""},
			},
			tbUnLockEvent = 
			{
			},
		},
		[2] = {nTime = 210, nNum = 0,		-- �ܼ�ʱ
			tbPrelock = {1},
			tbStartEvent = 
			{
				{XoyoGame.REVIVE_INFO, false, false, true, 97, 1897,2918, 1048576},
			},
			tbUnLockEvent = 
			{
				{XoyoGame.MOVIE_DIALOG, -1, Lang.mission.str656[Lang.Idx]},
				{XoyoGame.DEL_NPC, "guaiwu"},
				{XoyoGame.DO_SCRIPT, "self.tbLock[3]:Close()"},
				{XoyoGame.DO_SCRIPT, "self.tbLock[4]:Close()"},
				{XoyoGame.DO_SCRIPT, "self.tbLock[5]:Close()"},
			},
		},
		[3] = {nTime = 0, nNum = 4,		-- ˢ��
			tbPrelock = {1},
			tbStartEvent = 
			{
				{XoyoGame.ADD_NPC, 1, 4, 3, "guaiwu", "shuizhu8153"},		-- ˢ��
				{XoyoGame.MOVIE_DIALOG, -1, Lang.mission.str657[Lang.Idx]},
				{XoyoGame.TIME_INFO, -1, Lang.mission.str639[Lang.Idx], 2},
				{XoyoGame.TARGET_INFO, -1, Lang.mission.str659[Lang.Idx],3},
			},
			tbUnLockEvent = 
			{
			},
		},
		[4] = {nTime = 0, nNum = 5,		-- ˢ��
			tbPrelock = {3},
			tbStartEvent = 
			{
				{XoyoGame.ADD_NPC, 1, 5, 4, "guaiwu", "shuizhu8153"},		-- ˢ��
				{XoyoGame.TIME_INFO, -1, Lang.mission.str639[Lang.Idx], 2},
				{XoyoGame.TARGET_INFO, -1, Lang.mission.str660[Lang.Idx],4},
			},
			tbUnLockEvent = 
			{
			},
		},
		[5] = {nTime = 0, nNum = 6,		-- ˢ��
			tbPrelock = {4},
			tbStartEvent = 
			{
				{XoyoGame.ADD_NPC, 1, 6, 5, "guaiwu", "shuizhu8153"},		-- ˢ��
				{XoyoGame.TIME_INFO, -1, "Lang.mission.str639[Lang.Idx]", 2},
				{XoyoGame.TARGET_INFO, -1, Lang.mission.str661[Lang.Idx],5},
			},
			tbUnLockEvent = 
			{
			    {XoyoGame.DO_SCRIPT, "self.tbTeam[1].bIsWiner = 1"},		-- ����������ñ�־
				{XoyoGame.DEL_NPC, "guaiwu"},
				{XoyoGame.DO_SCRIPT, "self.tbLock[2]:Close()"},
				{XoyoGame.CLOSE_INFO, -1},
				{XoyoGame.TARGET_INFO, -1, Lang.mission.str602[Lang.Idx]},
				{XoyoGame.MOVIE_DIALOG, -1, Lang.mission.str662[Lang.Idx]},
			},
		},
		[6] = {nTime = 15, nNum = 0,
			tbPrelock = {2},
			tbStartEvent = 
			{
				{XoyoGame.TIME_INFO, -1, Lang.mission.str616[Lang.Idx], 6},
				{XoyoGame.TARGET_INFO, -1, Lang.mission.str603[Lang.Idx]},
			},
			tbUnLockEvent = 
			{
			},
		},
	}
}