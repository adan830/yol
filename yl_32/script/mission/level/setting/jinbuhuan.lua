Include("script/mission/level/xoyogame_def.lua");

local tbRoom = XoyoGame.RoomSetting.tbRoom;

tbRoom[29] =    --�𲻻�
{
	fnPlayerGroup 	= nil,						-- ��ҷ�Ⱥ����,������Ĭ��1֧����1��Ⱥ��
	fnDeath			= nil,						-- ���������ű�; ������Ĭ��
	fnWinRule		= nil,						-- ʤ��������������ķ�����Ҫ�ض��壬����һ�㲻��Ҫ��
	nRoomLevel		= 5,						-- ����ȼ�(1~5)
	nMapIndex		= 10,						-- ��ͼ�������
	tbBeginPoint	= {6583, 5696, 1055237},	-- ��ʼ�㣬��ʽ����fnPlayerGroup���������Ĭ����{nX,nY}
	-- �����漰��NPC����
	NPC = 
	{
-- 		���  	npcģ��		�ȼ�(-1Ĭ��)(ǿ�ȱ�id��)	5��(Ĭ��-1)
-- E.g  [0] = {nTemplate, 			nLevel, 		nSeries }
		[1] = {nTemplate = 8016, nLevel = {8044,8045,8046}, nSeries = -1},		-- �𲻻�
		[2] = {nTemplate = 9142, nLevel = {8056,8056,8056}, nSeries = -1},		-- �𲻻�
	},
	-- ���ṹ
	LOCK = 
	{
		-- 1�������ܲ��Ĭ��1��Ϊ��ʼ��
		[1] = {nTime = 15, nNum = 0,
			tbPrelock = {},
			tbStartEvent = 
			{
				{XoyoGame.ADD_NPC, 2, 11, 0, "lanlu", "shici9142"},		-- ˢ��	
				{XoyoGame.TIME_INFO, -1, Lang.mission.str600[Lang.Idx], 1},
				{XoyoGame.TARGET_INFO, -1, ""},
			},
			tbUnLockEvent = 
			{
			},
		},
		[2] = {nTime = 300, nNum = 0,		-- �ܼ�ʱ
			tbPrelock = {1},
			tbStartEvent = 
			{
				{XoyoGame.REVIVE_INFO, false, false, true, 97, 1897,2918, 1048576},
				{XoyoGame.MOVIE_DIALOG, -1, Lang.mission.str666[Lang.Idx]},
			},
			tbUnLockEvent = 
			{
				{XoyoGame.DO_SCRIPT, "self.tbLock[3]:Close()"},
				{XoyoGame.MOVIE_DIALOG, -1, Lang.mission.str667[Lang.Idx]},
				{XoyoGame.DEL_NPC, "boss"},
			},
		},
		[3] = {nTime = 0, nNum = 1,
			tbPrelock = {1},
			tbStartEvent = 
			{
				{XoyoGame.ADD_NPC, 1, 1, 3, "boss", "jinbh8016"},		-- ˢ��				
				--{XoyoGame.NPC_BLOOD_PERCENT, 
				--	"boss",
				--	{10,XoyoGame.DO_SCRIPT, "for i=4,6 do self.tbLock[2]:Close() end"},
				--	{10,XoyoGame.DO_SCRIPT, "self.tbLock[7]:UnLock()"},
				--},
				{XoyoGame.TARGET_INFO, -1, Lang.mission.str668[Lang.Idx],3},
				--{XoyoGame.CHANGE_FIGHT, -1, 1, Player.emKPK_STATE_PRACTISE},
				{XoyoGame.TIME_INFO, -1, Lang.mission.str601[Lang.Idx], 2},
				
			},
			tbUnLockEvent = 
			{
				{XoyoGame.DO_SCRIPT, "self.tbTeam[1].bIsWiner = 1"},		-- ����������ñ�־
				{XoyoGame.DO_SCRIPT, "self.tbLock[2]:Close()"},
				--{XoyoGame.DO_SCRIPT, "for i =4,7 do self.tbLock[i]:Close() end"},
				{XoyoGame.DEL_NPC, "boss"},
				{XoyoGame.CLOSE_INFO, -1},
				{XoyoGame.TARGET_INFO, -1, Lang.mission.str602[Lang.Idx]},
				{XoyoGame.MOVIE_DIALOG, -1, Lang.mission.str669[Lang.Idx]},
			},
		},
		[4] = {nTime = 15, nNum = 0,
			tbPrelock = {2},
			tbStartEvent = 
			{
				{XoyoGame.TIME_INFO, -1, Lang.mission.str616[Lang.Idx], 4},
				{XoyoGame.TARGET_INFO, -1, Lang.mission.str603[Lang.Idx],4},
			},
			tbUnLockEvent = 
			{
			},
		},
	}
}