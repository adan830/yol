Include("script/mission/level/xoyogame_def.lua");

local tbRoom = XoyoGame.RoomSetting.tbRoom;

tbRoom[1] =    --ľ��
{
	fnPlayerGroup 	= nil,						-- ��ҷ�Ⱥ����,������Ĭ��1֧����1��Ⱥ��
	fnDeath			= nil,						-- ���������ű�; ������Ĭ��
	fnWinRule		= nil,						-- ʤ��������������ķ�����Ҫ�ض��壬����һ�㲻��Ҫ��
	nRoomLevel		= 1,						-- ����ȼ�(1~5)
	nMapIndex		= 3,						-- ��ͼ�������
	tbBeginPoint	= {420, 1935, 1050618},	-- ��ʼ�㣬��ʽ����fnPlayerGroup���������Ĭ����{nX,nY}
	-- �����漰��NPC����
	NPC = 
	{
-- 		���  	npcģ��		�ȼ�(-1Ĭ��)(ǿ�ȱ�id��)	5��(Ĭ��-1)
-- E.g  [0] = {nTemplate, 			nLevel, 		nSeries }
		[1] = {nTemplate = 8003, nLevel = {8007,8008,8009}, nSeries = -1},		-- ľ��
		[2] = {nTemplate = 9083, nLevel = {8007,8008,8009}, nSeries = -1},      --muren9083
		[3] = {nTemplate = 9084, nLevel = {8007,8008,8009}, nSeries = -1},     --muren9084
		[4] = {nTemplate = 9085, nLevel = {8064,8065,8066}, nSeries = -1},
		[5] = {nTemplate = 9086, nLevel = {8064,8065,8066}, nSeries = -1},
		[6] = {nTemplate = 9087, nLevel = {8064,8065,8066}, nSeries = -1},
		[7] = {nTemplate = 9088, nLevel = {8064,8065,8066}, nSeries = -1},
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
				{XoyoGame.MOVIE_DIALOG, -1, Lang.mission.str697[Lang.Idx]},
			},
			tbUnLockEvent = 
			{
				{XoyoGame.MOVIE_DIALOG, -1, Lang.mission.str698[Lang.Idx]},
				{XoyoGame.DEL_NPC, "guaiwu"},
				
			},
		},
		[3] = {nTime = 0, nNum = 28,
			tbPrelock = {1},
			tbStartEvent = 
			{
				{XoyoGame.ADD_NPC, 1,4, 3, "guaiwu", "muren8003"},		-- ˢ��
				{XoyoGame.ADD_NPC, 2,4, 3, "guaiwu", "muren9083"},		-- ˢ��
				{XoyoGame.ADD_NPC, 3,4, 3, "guaiwu", "muren9084"},		-- ˢ��
				{XoyoGame.ADD_NPC, 4,4, 3, "guaiwu", "muren9085"},		-- ˢ��
				{XoyoGame.ADD_NPC, 5,4, 3, "guaiwu", "muren9086"},		-- ˢ��
				{XoyoGame.ADD_NPC, 6,4, 3, "guaiwu", "muren9087"},		-- ˢ��
				{XoyoGame.ADD_NPC, 7,4, 3, "guaiwu", "muren9088"},		-- ˢ��
				{XoyoGame.TARGET_INFO, -1, Lang.mission.str699[Lang.Idx],3},
				{XoyoGame.TIME_INFO, -1, Lang.mission.str601[Lang.Idx], 2},
				
			},
			tbUnLockEvent = 
			{
				{XoyoGame.DO_SCRIPT, "self.tbTeam[1].bIsWiner = 1"},		-- ����������ñ�־
				{XoyoGame.DO_SCRIPT, "self.tbLock[2]:Close()"},
				{XoyoGame.CLOSE_INFO, -1},
				{XoyoGame.TARGET_INFO, -1, Lang.mission.str602[Lang.Idx]},
				{XoyoGame.MOVIE_DIALOG, -1, Lang.mission.str700[Lang.Idx]},
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