Include("script/mission/level/xoyogame_def.lua");

local tbRoom = XoyoGame.RoomSetting.tbRoom;

tbRoom[9] =    --��Ʀ��å
{
	fnPlayerGroup 	= nil,						-- ��ҷ�Ⱥ����,������Ĭ��1֧����1��Ⱥ��
	fnDeath			= nil,						-- ���������ű�; ������Ĭ��
	fnWinRule		= nil,						-- ʤ��������������ķ�����Ҫ�ض��壬����һ�㲻��Ҫ��
	nRoomLevel		= 2,						-- ����ȼ�(1~5)
	nMapIndex		= 6,						-- ��ͼ�������
	tbBeginPoint	= {1911, 1280, 1049600},	-- ��ʼ�㣬��ʽ����fnPlayerGroup���������Ĭ����{nX,nY}
	-- �����漰��NPC����
	NPC = 
	{
-- 		���  	npcģ��		�ȼ�(-1Ĭ��)(ǿ�ȱ�id��)	5��(Ĭ��-1)
-- E.g  [0] = {nTemplate, 			nLevel, 		nSeries }
		[1] = {nTemplate = 8004, nLevel = {8010,8011,8012}, nSeries = -1},		-- ��å
		[2] = {nTemplate = 8005, nLevel = {8013,8014,8015}, nSeries = -1},		-- ����
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
				{XoyoGame.MOVIE_DIALOG, -1, Lang.mission.str628[Lang.Idx]},
			},
			tbUnLockEvent = 
			{
				{XoyoGame.MOVIE_DIALOG, -1, Lang.mission.str629[Lang.Idx]},
				{XoyoGame.DEL_NPC, "guaiwu"},
				{XoyoGame.DEL_NPC, "guaiwu1"},
				{XoyoGame.DEL_NPC, "boss"},
			},
		},
		[3] = {nTime = 0, nNum = 4,
			tbPrelock = {1},
			tbStartEvent = 
			{
				{XoyoGame.ADD_NPC, 1, 4, 3, "guaiwu", "dipi8004"},		-- ˢ��
				{XoyoGame.TARGET_INFO, -1, Lang.mission.str630[Lang.Idx],3},
				--{XoyoGame.CHANGE_FIGHT, -1, 1, Player.emKPK_STATE_PRACTISE},
				{XoyoGame.TIME_INFO, -1, Lang.mission.str601[Lang.Idx], 2},
				
			},
			tbUnLockEvent = 
			{
				--�ô����ƶ�·�ߣ����ƶ�������å����
			},
		},
		[4] = {nTime = 8, nNum = 0,
			tbPrelock = {3},
			tbStartEvent = 
			{		
				{XoyoGame.MOVIE_DIALOG, -1, Lang.mission.str631[Lang.Idx]},
				{XoyoGame.TARGET_INFO, -1, Lang.mission.str632[Lang.Idx]},
				{XoyoGame.TIME_INFO, -1, Lang.mission.str601[Lang.Idx], 2},
			},
			tbUnLockEvent = 
			{
			},
		},
		[5] = {nTime = 0, nNum = 5,
			tbPrelock = {4},
			tbStartEvent = 
			{
				{XoyoGame.ADD_NPC, 2, 1, 5, "boss", "junjie8005"},		-- ��
				{XoyoGame.ADD_NPC, 1, 4, 5, "guaiwu1", "dipi8004_2"},
				{XoyoGame.MOVIE_DIALOG, -1, Lang.mission.str633[Lang.Idx]},
				{XoyoGame.TARGET_INFO, -1, Lang.mission.str634[Lang.Idx],5},
				{XoyoGame.TIME_INFO, -1, Lang.mission.str601[Lang.Idx], 2},
			},
			tbUnLockEvent = 
			{
				{XoyoGame.DO_SCRIPT, "self.tbTeam[1].bIsWiner = 1"},		-- ����������ñ�־
				{XoyoGame.DEL_NPC, "guaiwu"},
				{XoyoGame.DEL_NPC, "guaiwu1"},
				{XoyoGame.DEL_NPC, "boss"},
				{XoyoGame.DO_SCRIPT, "self.tbLock[2]:Close()"},
				{XoyoGame.CLOSE_INFO, -1},
				{XoyoGame.TARGET_INFO, -1, Lang.mission.str602[Lang.Idx]},
				{XoyoGame.MOVIE_DIALOG, -1,Lang.mission.str635[Lang.Idx]},
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