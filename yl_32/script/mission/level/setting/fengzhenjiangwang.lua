Include("script/mission/level/xoyogame_def.lua");

local tbRoom = XoyoGame.RoomSetting.tbRoom;

tbRoom[47] =    --������
{
	fnPlayerGroup 	= nil,						-- ��ҷ�Ⱥ����,������Ĭ��1֧����1��Ⱥ��
	fnDeath			= nil,						-- ���������ű�; ������Ĭ��
	fnWinRule		= nil,						-- ʤ��������������ķ�����Ҫ�ض��壬����һ�㲻��Ҫ��
	nRoomLevel		= 4,						-- ����ȼ�(1~5)
	nMapIndex		= 48,						-- ��ͼ�������
	tbBeginPoint	= {831, 1796, 1049093},	-- ��ʼ�㣬��ʽ����fnPlayerGroup���������Ĭ����{nX,nY}
	-- �����漰��NPC����
	NPC = 
	{
-- 		���  	npcģ��		�ȼ�(-1Ĭ��)(ǿ�ȱ�id��)	5��(Ĭ��-1)
-- E.g  [0] = {nTemplate, 			nLevel, 		nSeries }
		[1] = {nTemplate = 8067, nLevel = {8156,8157,8158}, nSeries = -1},		-- ����
		[2] = {nTemplate = 9060, nLevel = {1,1,1}, nSeries = -1},		        -- ���ľ�
		[3] = {nTemplate = 9061, nLevel = {1,1,1}, nSeries = -1},		        -- ���ľ�
		[4] = {nTemplate = 9062, nLevel = {1,1,1}, nSeries = -1},		        -- ���ľ�
		[5] = {nTemplate = 9063, nLevel = {9048,9049,9050}, nSeries = -1},		-- ��������
		[6] = {nTemplate = 9064, nLevel = {9048,9049,9050}, nSeries = -1},		-- ��������
		[7] = {nTemplate = 9065, nLevel = {9048,9049,9050}, nSeries = -1},		-- ��������
		[8] = {nTemplate = 9066, nLevel = {8156,8157,8158}, nSeries = -1},		-- ����
		[9] = {nTemplate = 9059, nLevel = {8125,8125,8125}, nSeries = -1},		-- ����
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
			},
			tbUnLockEvent = 
			{
				{XoyoGame.MOVIE_DIALOG, -1, "<playername>: �⽩���մ���ѹ���������ľ����ǿ�󣬸Ͻ��ߣ�<end>"},
				{XoyoGame.DEL_NPC, "boss"},
				{XoyoGame.DEL_NPC, "tishen"}, 
				{XoyoGame.DEL_NPC, "suoyou"}, 
				{XoyoGame.DEL_NPC, "zhenyou"},
				{XoyoGame.DEL_NPC, "dingyou"},
				{XoyoGame.DEL_NPC, "suonpc"}, 
				{XoyoGame.DEL_NPC, "zhennpc"},
				{XoyoGame.DEL_NPC, "dingnpc"},
				{XoyoGame.DO_SCRIPT, "self.tbLock[3]:Close()"},
				{XoyoGame.DO_SCRIPT, "self.tbLock[4]:Close()"},
				{XoyoGame.DO_SCRIPT, "self.tbLock[5]:Close()"},
				{XoyoGame.DO_SCRIPT, "self.tbLock[6]:Close()"},
				{XoyoGame.DO_SCRIPT, "self.tbLock[7]:Close()"},
				{XoyoGame.DO_SCRIPT, "self.tbLock[8]:Close()"},
				{XoyoGame.DO_SCRIPT, "self.tbLock[9]:Close()"},
				{XoyoGame.DO_SCRIPT, "self.tbLock[10]:Close()"},
				{XoyoGame.DO_SCRIPT, "self.tbLock[11]:Close()"},
				{XoyoGame.DO_SCRIPT, "self.tbLock[12]:Close()"},
				{XoyoGame.DO_SCRIPT, "self.tbLock[13]:Close()"},
				{XoyoGame.DO_SCRIPT, "self.tbLock[14]:Close()"},
				{XoyoGame.DO_SCRIPT, "self.tbLock[15]:Close()"},
				{XoyoGame.DO_SCRIPT, "self.tbLock[16]:Close()"},
				{XoyoGame.DO_SCRIPT, "self.tbLock[17]:Close()"},
				{XoyoGame.DO_SCRIPT, "self.tbLock[18]:Close()"},
				{XoyoGame.DO_SCRIPT, "self.tbLock[19]:Close()"},
				{XoyoGame.DO_SCRIPT, "self.tbLock[20]:Close()"},
				{XoyoGame.DO_SCRIPT, "self.tbLock[21]:Close()"},
				{XoyoGame.DO_SCRIPT, "self.tbLock[22]:Close()"},
				{XoyoGame.DO_SCRIPT, "self.tbLock[23]:Close()"},
				{XoyoGame.DO_SCRIPT, "self.tbLock[24]:Close()"},
				{XoyoGame.DO_SCRIPT, "self.tbLock[26]:Close()"},
				{XoyoGame.DO_SCRIPT, "self.tbLock[27]:Close()"},
				{XoyoGame.DO_SCRIPT, "self.tbLock[28]:Close()"},
			},
		},
		[3] = {nTime = 0, nNum = 3,		
			tbPrelock = {1},
			tbStartEvent = 
			{
				{XoyoGame.MOVIE_DIALOG, -1, Lang.mission.str637[Lang.Idx]},
				{XoyoGame.ADD_NPC, 8, 1, 0, "tishen", "jiangwang9066"},		-- ˢ��
				{XoyoGame.ADD_NPC, 2, 1, 0, "suoyou", "suoyou9060"},		-- ˢ��
				{XoyoGame.ADD_NPC, 3, 1, 0, "zhenyou", "zhenyou9061"},		-- ˢ��
				{XoyoGame.ADD_NPC, 4, 1, 0, "dingyou", "dingyou9062"},		-- ˢ��
				{XoyoGame.ADD_NPC, 5, 1, 3, "suonpc", "suonpc9063"},		-- ˢ��
				{XoyoGame.ADD_NPC, 6, 1, 3, "zhennpc", "zhennpc9064"},		-- ˢ��
				{XoyoGame.ADD_NPC, 7, 1, 3, "dingnpc", "dingnpc9065"},		-- ˢ��
				{XoyoGame.TARGET_INFO, -1, Lang.mission.str638[Lang.Idx],3},
				{XoyoGame.TIME_INFO, -1, Lang.mission.str639[Lang.Idx], 2},
			},
			tbUnLockEvent = 
			{   	
			},
		},	
		[4] = {nTime = 0, nNum = 1,                                           
			tbPrelock = {3},
			tbStartEvent = 
			{	
				{XoyoGame.TARGET_INFO, -1, Lang.mission.str640[Lang.Idx],4},
				{XoyoGame.TIME_INFO, -1, Lang.mission.str639[Lang.Idx], 2},
			},
			tbUnLockEvent = 
			{
				{XoyoGame.DO_SCRIPT, "self.tbTeam[1].bIsWiner = 1"},		-- ����������ñ�־
				{XoyoGame.TARGET_INFO, -1, Lang.mission.str602[Lang.Idx]},
				{XoyoGame.DEL_NPC, "boss"},
				{XoyoGame.DEL_NPC, "tishen"},
				{XoyoGame.DEL_NPC, "suoyou"},
				{XoyoGame.DEL_NPC, "zhenyou"},
				{XoyoGame.DEL_NPC, "dingyou"},
				{XoyoGame.DEL_NPC, "suonpc"},
				{XoyoGame.DEL_NPC, "zhennpc"},
				{XoyoGame.DEL_NPC, "dingnpc"},
				{XoyoGame.DO_SCRIPT, "self.tbLock[2]:Close()"},
				{XoyoGame.DO_SCRIPT, "self.tbLock[8]:Close()"},
				{XoyoGame.DO_SCRIPT, "self.tbLock[9]:Close()"},
				{XoyoGame.DO_SCRIPT, "self.tbLock[10]:Close()"},
				{XoyoGame.DO_SCRIPT, "self.tbLock[11]:Close()"},
				{XoyoGame.DO_SCRIPT, "self.tbLock[12]:Close()"},
				{XoyoGame.DO_SCRIPT, "self.tbLock[13]:Close()"},
				{XoyoGame.DO_SCRIPT, "self.tbLock[14]:Close()"},
				{XoyoGame.DO_SCRIPT, "self.tbLock[15]:Close()"},
				{XoyoGame.DO_SCRIPT, "self.tbLock[16]:Close()"},
				{XoyoGame.DO_SCRIPT, "self.tbLock[17]:Close()"},
				{XoyoGame.DO_SCRIPT, "self.tbLock[18]:Close()"},
				{XoyoGame.DO_SCRIPT, "self.tbLock[19]:Close()"},
				{XoyoGame.DO_SCRIPT, "self.tbLock[20]:Close()"},
				{XoyoGame.DO_SCRIPT, "self.tbLock[21]:Close()"},
				{XoyoGame.DO_SCRIPT, "self.tbLock[22]:Close()"},
				{XoyoGame.DO_SCRIPT, "self.tbLock[23]:Close()"},
				{XoyoGame.DO_SCRIPT, "self.tbLock[24]:Close()"},
				{XoyoGame.DO_SCRIPT, "self.tbLock[26]:Close()"},
				{XoyoGame.DO_SCRIPT, "self.tbLock[27]:Close()"},
				{XoyoGame.DO_SCRIPT, "self.tbLock[28]:Close()"},
				{XoyoGame.CLOSE_INFO, -1},
				{XoyoGame.MOVIE_DIALOG, -1, Lang.mission.str641[Lang.Idx]}, 
			},
		},
		[5] = {nTime = 0, nNum = 0,                                           --ˢBOSS
			tbPrelock = {3},
			tbStartEvent = 
			{
				{XoyoGame.DEL_NPC, "tishen"},
				{XoyoGame.ADD_NPC, 1, 1, 4, "boss", "jiangwang8067"},		-- ˢ��
				{XoyoGame.MOVIE_DIALOG, -1, Lang.mission.str642[Lang.Idx]}, 
			},
			tbUnLockEvent = 
			{
			},
		},
		[6] = {nTime = 8, nNum = 0,                                           
			tbPrelock = {3},
			tbStartEvent = 
			{	
			},
			tbUnLockEvent = 
			{
			},
		},
		[7] = {nTime = 12, nNum = 0,                                           
			tbPrelock = {6},
			tbStartEvent = 
			{	
				{XoyoGame.BLACK_MSG, -1, Lang.mission.str643[Lang.Idx]},
				{XoyoGame.ADD_NPC, 9, 1, 0, "guangzhao", "guangzhao9059"},
			},
			tbUnLockEvent = 
			{
			},
		},
		[8] = {nTime = 8, nNum = 0,                                           
			tbPrelock = {7},
			tbStartEvent = 
			{	
			},
			tbUnLockEvent = 
			{
			},
		},
		[9] = {nTime = 12, nNum = 0,                                           
			tbPrelock = {8},
			tbStartEvent = 
			{	
				{XoyoGame.ADD_NPC, 9, 1, 0, "guangzhao", "guangzhao9059"},
			},
			tbUnLockEvent = 
			{
			},
		},
		[10] = {nTime = 8, nNum = 0,                                           
			tbPrelock = {9},
			tbStartEvent = 
			{	
			},
			tbUnLockEvent = 
			{
			},
		},
		[11] = {nTime = 12, nNum = 0,                                           
			tbPrelock = {10},
			tbStartEvent = 
			{	
				{XoyoGame.ADD_NPC, 9, 1, 0, "guangzhao", "guangzhao9059"},
			},
			tbUnLockEvent = 
			{
			},
		},
		[12] = {nTime = 8, nNum = 0,                                           
			tbPrelock = {11},
			tbStartEvent = 
			{	
			},
			tbUnLockEvent = 
			{
			},
		},
		[13] = {nTime = 12, nNum = 0,                                           
			tbPrelock = {12},
			tbStartEvent = 
			{	
				{XoyoGame.ADD_NPC, 9, 1, 0, "guangzhao", "guangzhao9059"},
			},
			tbUnLockEvent = 
			{
			},
		},
		[14] = {nTime = 8, nNum = 0,                                           
			tbPrelock = {13},
			tbStartEvent = 
			{	
			},
			tbUnLockEvent = 
			{
			},
		},
		[15] = {nTime = 12, nNum = 0,                                           
			tbPrelock = {14},
			tbStartEvent = 
			{	
				{XoyoGame.ADD_NPC, 9, 1, 0, "guangzhao", "guangzhao9059"},
			},
			tbUnLockEvent = 
			{
			},
		},
		[16] = {nTime = 8, nNum = 0,                                           
			tbPrelock = {15},
			tbStartEvent = 
			{	
			},
			tbUnLockEvent = 
			{
			},
		},
		[17] = {nTime = 12, nNum = 0,                                           
			tbPrelock = {16},
			tbStartEvent = 
			{	
				{XoyoGame.ADD_NPC, 9, 1, 0, "guangzhao", "guangzhao9059"},
			},
			tbUnLockEvent = 
			{
			},
		},
		[18] = {nTime = 8, nNum = 0,                                           
			tbPrelock = {17},
			tbStartEvent = 
			{	
			},
			tbUnLockEvent = 
			{
			},
		},
		[19] = {nTime = 12, nNum = 0,                                           
			tbPrelock = {18},
			tbStartEvent = 
			{	
				{XoyoGame.ADD_NPC, 9, 1, 0, "guangzhao", "guangzhao9059"},
			},
			tbUnLockEvent = 
			{
			},
		},
		[20] = {nTime = 8, nNum = 0,                                           
			tbPrelock = {19},
			tbStartEvent = 
			{	
			},
			tbUnLockEvent = 
			{
			},
		},
		[21] = {nTime = 12, nNum = 0,                                           
			tbPrelock = {20},
			tbStartEvent = 
			{	
				{XoyoGame.ADD_NPC, 9, 1, 0, "guangzhao", "guangzhao9059"},
			},
			tbUnLockEvent = 
			{
			},
		},
		[22] = {nTime = 8, nNum = 0,                                           
			tbPrelock = {21},
			tbStartEvent = 
			{	
			},
			tbUnLockEvent = 
			{
			},
		},
		[23] = {nTime = 12, nNum = 0,                                           
			tbPrelock = {22},
			tbStartEvent = 
			{	
				{XoyoGame.ADD_NPC, 9, 1, 0, "guangzhao", "guangzhao9059"},
			},
			tbUnLockEvent = 
			{
			},
		},
		[24] = {nTime = 8, nNum = 0,                                           
			tbPrelock = {23},
			tbStartEvent = 
			{	
			},
			tbUnLockEvent = 
			{
			},
		},
		[25] = {nTime = 15, nNum = 0,
			tbPrelock = {2},
			tbStartEvent = 
			{
				{XoyoGame.TIME_INFO, -1, Lang.mission.str616[Lang.Idx], 25},
				{XoyoGame.TARGET_INFO, -1, Lang.mission.str603[Lang.Idx]},
			},
			tbUnLockEvent = 
			{
				{XoyoGame.DEL_NPC, "guangzhao"},
			},
		},
		[26] = {nTime = 12, nNum = 0,                                           
			tbPrelock = {24},
			tbStartEvent = 
			{	
				{XoyoGame.ADD_NPC, 9, 1, 0, "guangzhao", "guangzhao9059"},
			},
			tbUnLockEvent = 
			{
			},
		},
		[27] = {nTime = 8, nNum = 0,                                           
			tbPrelock = {26},
			tbStartEvent = 
			{	
			},
			tbUnLockEvent = 
			{
			},
		},
		[28] = {nTime = 12, nNum = 0,                                           
			tbPrelock = {27},
			tbStartEvent = 
			{	
				{XoyoGame.ADD_NPC, 9, 1, 0, "guangzhao", "guangzhao9059"},
			},
			tbUnLockEvent = 
			{
			},
		},
	}
}