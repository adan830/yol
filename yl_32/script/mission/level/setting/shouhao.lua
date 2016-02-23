Include("script/mission/level/xoyogame_def.lua");

local tbRoom = XoyoGame.RoomSetting.tbRoom;

tbRoom[23] =    --�޺�
{
	fnPlayerGroup 	= nil,						-- ��ҷ�Ⱥ����,������Ĭ��1֧����1��Ⱥ��
	fnDeath			= nil,						-- ���������ű�; ������Ĭ��
	fnWinRule		= nil,						-- ʤ��������������ķ�����Ҫ�ض��壬����һ�㲻��Ҫ��
	nRoomLevel		= 4,						-- ����ȼ�(1~5)
	nMapIndex		= 9,						-- ��ͼ�������
	tbBeginPoint	= {2011, 2693, 1053184},	-- ��ʼ�㣬��ʽ����fnPlayerGroup���������Ĭ����{nX,nY}
	-- �����漰��NPC����
	NPC = 
	{
-- 		���  	npcģ��		�ȼ�(-1Ĭ��)(ǿ�ȱ�id��)	5��(Ĭ��-1)
-- E.g  [0] = {nTemplate, 			nLevel, 		nSeries }
		[1] = {nTemplate = 8014, nLevel = {8038,8039,8040}, nSeries = -1},		-- �޺�
		[2] = {nTemplate = 8020, nLevel = {8052,8052,8052}, nSeries = -1},		-- ����
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
		[2] = {nTime = 270, nNum = 0,		-- �ܼ�ʱ
			tbPrelock = {1},
			tbStartEvent = 
			{
				{XoyoGame.REVIVE_INFO, false, false, true, 97, 1897,2918, 1048576},
				{XoyoGame.MOVIE_DIALOG, -1, Lang.mission.str721[Lang.Idx]},
			},
			tbUnLockEvent = 
			{
				{XoyoGame.MOVIE_DIALOG, -1, Lang.mission.str722[Lang.Idx]},
				{XoyoGame.DO_SCRIPT, "self.tbLock[3]:Close()"},
				{XoyoGame.DEL_NPC, "boss"},
				{XoyoGame.DEL_NPC, "yinxingzhuzi"},
				{XoyoGame.TARGET_INFO, -1, Lang.mission.str603[Lang.Idx]},
			},
		},
		[3] = {nTime = 0, nNum = 1,
			tbPrelock = {1},
			tbStartEvent = 
			{
				{XoyoGame.ADD_NPC, 1, 1, 3, "boss", "shouhao8014"},		-- ˢ��
				{XoyoGame.SET_NPC_NICKNAME,"boss", "shouhao"},		-- ˢ��
				--{XoyoGame.ADD_NPC, 2, 1, 4, "zhuzi", "shouzhu8020"},		-- ˢ��
				{XoyoGame.TARGET_INFO, -1, Lang.mission.str723[Lang.Idx],3},
				--{XoyoGame.CHANGE_FIGHT, -1, 1, Player.emKPK_STATE_PRACTISE},
				{XoyoGame.TIME_INFO, -1, Lang.mission.str601[Lang.Idx], 2},
				
			},
			tbUnLockEvent = 
			{
				{XoyoGame.DO_SCRIPT, "self.tbTeam[1].bIsWiner = 1"},		-- ����������ñ�־
				{XoyoGame.DO_SCRIPT, "self.tbLock[2]:Close()"},
				{XoyoGame.DEL_NPC, "boss"},
				{XoyoGame.CLOSE_INFO, -1},
				{XoyoGame.TARGET_INFO, -1, Lang.mission.str602[Lang.Idx]},
				{XoyoGame.MOVIE_DIALOG, -1, Lang.mission.str724[Lang.Idx]},
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
		[5] = {nTime = 4, nNum = 0,
			tbPrelock = {1},
			tbStartEvent = 
			{	
			},
			tbUnLockEvent = 
			{
				{XoyoGame.BLACK_MSG, -1, Lang.mission.str725[Lang.Idx]},
			},
		},
	}
}
