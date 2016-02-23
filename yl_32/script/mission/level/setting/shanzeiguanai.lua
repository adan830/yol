Include("script/mission/level/xoyogame_def.lua");

local tbRoom = XoyoGame.RoomSetting.tbRoom;

tbRoom[48] =    --ɽ���ذ�	
{
	fnPlayerGroup 	= nil,						-- ��ҷ�Ⱥ����,������Ĭ��1֧����1��Ⱥ��
	fnDeath			= nil,						-- ���������ű�; ������Ĭ��
	fnWinRule		= nil,						-- ʤ��������������ķ�����Ҫ�ض��壬����һ�㲻��Ҫ��
	nRoomLevel		= 1,						-- ����ȼ�(1~5)
	nMapIndex		= 49,						-- ��ͼ�������
	tbBeginPoint	= {3018,680, 1056133},	-- ��ʼ�㣬��ʽ����fnPlayerGroup���������Ĭ����{nX,nY}
	-- �����漰��NPC����
	NPC = 
	{
-- 		���  	npcģ��		�ȼ�(-1Ĭ��)(ǿ�ȱ�id��)	5��(Ĭ��-1)
-- E.g  [0] = {nTemplate, 			nLevel, 		nSeries }
		[1] = {nTemplate = 9067, nLevel = {9044,9044,9044}, nSeries = -1},	
		[2] = {nTemplate = 9082, nLevel = {9044,9044,9044}, nSeries = -1},	-- 
		[3] = {nTemplate = 9100, nLevel = {9044,9044,9044}, nSeries = -1},
		[4] = {nTemplate = 9101, nLevel = {9044,9044,9044}, nSeries = -1},
		[5] = {nTemplate = 9102, nLevel = {9044,9044,9044}, nSeries = -1},
		[6] = {nTemplate = 9103, nLevel = {9044,9044,9044}, nSeries = -1},
		[7] = {nTemplate = 9104, nLevel = {9044,9044,9044}, nSeries = -1},
		[8] = {nTemplate = 9105, nLevel = {9044,9044,9044}, nSeries = -1},
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
		[2] = {nTime = 180, nNum = 0,		-- �ܼ�ʱ
			tbPrelock = {1},
			tbStartEvent = 
			{
				{XoyoGame.REVIVE_INFO, false, false, true, 97, 1897,2918, 1048576},
				{XoyoGame.MOVIE_DIALOG, -1, Lang.mission.str712[Lang.Idx]},
			},
			tbUnLockEvent = 
			{
				{XoyoGame.MOVIE_DIALOG, -1, Lang.mission.str713[Lang.Idx]},
				{XoyoGame.DEL_NPC, "boss"},
			},
		},
		[3] = {nTime = 0, nNum = 24,
			tbPrelock = {1},
			tbStartEvent = 
			{
				{XoyoGame.ADD_NPC, 2, 1, 0, "guai1", "shanzei9082"},		-- ˢ��
				{XoyoGame.ADD_NPC, 1, 3, 3, "guai", "shanzei9067"},		-- ˢ��
				{XoyoGame.ADD_NPC, 3, 3, 3, "guai", "shanzei9100"},		-- ˢ��
				{XoyoGame.ADD_NPC, 4, 3, 3, "guai", "shanzei9101"},		-- ˢ��
				{XoyoGame.ADD_NPC, 5, 4, 3, "guai", "shanzei9102"},		-- ˢ��
				{XoyoGame.ADD_NPC, 6, 4, 3, "guai", "shanzei9103"},		-- ˢ��
				{XoyoGame.ADD_NPC, 7, 4, 3, "guai", "shanzei9104"},		-- ˢ��
				{XoyoGame.ADD_NPC, 8, 3, 3, "guai", "shanzei9105"},		-- ˢ��
				{XoyoGame.TARGET_INFO, -1, Lang.mission.str715[Lang.Idx],3},
				{XoyoGame.TIME_INFO, -1, Lang.mission.str601[Lang.Idx], 2},
				
			},
			tbUnLockEvent = 
			{
				{XoyoGame.MOVIE_DIALOG, -1, Lang.mission.str714[Lang.Idx]},
				{XoyoGame.DO_SCRIPT, "self.tbTeam[1].bIsWiner = 1"},		-- ����������ñ�־
				{XoyoGame.DO_SCRIPT, "self.tbLock[2]:Close()"},
				{XoyoGame.DEL_NPC, "guai"},
				{XoyoGame.CLOSE_INFO, -1},
				{XoyoGame.TARGET_INFO, -1, Lang.mission.str602[Lang.Idx]},
			},
		},
		[4] = {nTime = 15, nNum = 0,
			tbPrelock = {2},
			tbStartEvent = 
			{
				{XoyoGame.TIME_INFO, -1, Lang.mission.str616[Lang.Idx], 4},
				{XoyoGame.TARGET_INFO, -1, Lang.mission.str603[Lang.Idx]},
			},
			tbUnLockEvent = 
			{
			},
		},
	}
}