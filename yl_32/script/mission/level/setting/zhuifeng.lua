Include("script/mission/level/xoyogame_def.lua");

local tbRoom = XoyoGame.RoomSetting.tbRoom;

tbRoom[16] =    --׷��
{
	fnPlayerGroup 	= nil,						-- ��ҷ�Ⱥ����,������Ĭ��1֧����1��Ⱥ��
	fnDeath			= nil,						-- ���������ű�; ������Ĭ��
	fnWinRule		= nil,						-- ʤ��������������ķ�����Ҫ�ض��壬����һ�㲻��Ҫ��
	nRoomLevel		= 3,						-- ����ȼ�(1~5)
	nMapIndex		= 7,						-- ��ͼ�������
	tbBeginPoint	= {2535, 528, 1051136},	-- ��ʼ�㣬��ʽ����fnPlayerGroup���������Ĭ����{nX,nY}
	-- �����漰��NPC����
	NPC = 
	{
-- 		���  	npcģ��		�ȼ�(-1Ĭ��)(ǿ�ȱ�id��)	5��(Ĭ��-1)
-- E.g  [0] = {nTemplate, 			nLevel, 		nSeries }
		[1] = {nTemplate = 8019, nLevel = {8051,8051,8051}, nSeries = -1},		-- ��Ӣ�ˣ��Ի���
		[2] = {nTemplate = 8012, nLevel = {8034,8034,8034}, nSeries = -1},		-- ��Ӣ�ˣ�ս����
		[3] = {nTemplate = 8011, nLevel = {8031,8032,8033}, nSeries = -1},		-- ׷��
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
				--{XoyoGame.ADD_NPC, 1, 1, 0, "butou_duihua", "1_yelang_3"},		-- ˢ��
				{XoyoGame.TARGET_INFO, -1, ""},
			},
			tbUnLockEvent = 
			{
			},
		},
		[2] = {nTime = 240, nNum = 0,		-- �ܼ�ʱ
			tbPrelock = {1},
			tbStartEvent = 
			{
				{XoyoGame.REVIVE_INFO, false, false, true, 97, 1897,2918, 1048576},
				{XoyoGame.MOVIE_DIALOG, -1, Lang.mission.str788[Lang.Idx]},
			},
			tbUnLockEvent = 
			{
				{XoyoGame.MOVIE_DIALOG, -1, Lang.mission.str789[Lang.Idx]},
				{XoyoGame.DEL_NPC, "boss"},
				{XoyoGame.DEL_NPC, "butou_zhandou"},
			},
		},
		[3] = {nTime = 0, nNum = 1,
			tbPrelock = {1},
			tbStartEvent = 
			{
				
				{XoyoGame.ADD_NPC, 3, 1, 3, "boss", "zhuifeng8011"},		-- ˢ��
				{XoyoGame.NPC_BLOOD_PERCENT, 
					"boss",
					{25,XoyoGame.DO_SCRIPT, "self.tbLock[4]:UnLock()"},
				},
				{XoyoGame.TARGET_INFO, -1, Lang.mission.str790[Lang.Idx],3},
				{XoyoGame.TIME_INFO, -1, Lang.mission.str601[Lang.Idx], 2},
				
			},
			tbUnLockEvent = 
			{
				{XoyoGame.DO_SCRIPT, "self.tbTeam[1].bIsWiner = 1"},		-- ����������ñ�־
				{XoyoGame.DO_SCRIPT, "self.tbLock[2]:Close()"},
				{XoyoGame.DEL_NPC, "boss"},
				{XoyoGame.DEL_NPC, "butou_duihua"},
				{XoyoGame.DEL_NPC, "butou_zhandou"},
				{XoyoGame.CLOSE_INFO, -1},
				{XoyoGame.TARGET_INFO, -1, Lang.mission.str602[Lang.Idx]},
				{XoyoGame.MOVIE_DIALOG, -1, Lang.mission.str791[Lang.Idx]},
			},
		},
		[4] = {nTime = 4, nNum = 0,
			tbPrelock = {},
			tbStartEvent = 
			{
			},
			tbUnLockEvent = 
			{
				
				{XoyoGame.ADD_NPC, 2, 1, 0, "butou_zhandou", "geyr8012"},		-- ˢ��
				
			},
		},
		[5] = {nTime = 15, nNum = 0,
			tbPrelock = {2},
			tbStartEvent = 
			{
				{XoyoGame.TIME_INFO, -1, Lang.mission.str616[Lang.Idx], 5},
				{XoyoGame.TARGET_INFO, -1, Lang.mission.str603[Lang.Idx]},
			},
			tbUnLockEvent = 
			{
			},
		},
	}
}