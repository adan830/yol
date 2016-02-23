Include("script/mission/level/xoyogame_def.lua");
Include("script/mission/level/xmhj1/zengya.lua");

local tbRoom = XoyoGame.RoomSetting.tbRoom;

tbRoom[22] =    --����
{
	fnPlayerGroup 	= nil,						-- ��ҷ�Ⱥ����,������Ĭ��1֧����1��Ⱥ��
	fnDeath			= nil,						-- ���������ű�; ������Ĭ��
	fnWinRule		= nil,						-- ʤ��������������ķ�����Ҫ�ض��壬����һ�㲻��Ҫ��
	nRoomLevel		= 4,						-- ����ȼ�(1~5)
	nMapIndex		= 8,						-- ��ͼ�������
	tbBeginPoint	= {2728, 1745, 1056762},	-- ��ʼ�㣬��ʽ����fnPlayerGroup���������Ĭ����{nX,nY}
	DerivedRoom		= XoyoGame.ZengYa,
	tbClearBuff		= {6101, 6105, 6099},               --��Ҫ�����BUFF
	-- �����漰��NPC����
	NPC = 
	{
-- 		���  	npcģ��		�ȼ�(-1Ĭ��)(ǿ�ȱ�id��)	5��(Ĭ��-1)
-- E.g  [0] = {nTemplate, 			nLevel, 		nSeries }
		[1] = {nTemplate = 8013, nLevel = {8035,8036,8037}, nSeries = -1},		-- ���� ��ʵzya8013
		[2] = {nTemplate = 9139, nLevel = {8035,8036,8037}, nSeries = -1},		-- ���� �ξ�zya9139
		[3] = {nTemplate = 9140, nLevel = {8056,8056,8056}, nSeries = -1},		-- ޒ�κ�«hulu9140
		[4] = {nTemplate = 9141, nLevel = {8056,8056,8056}, nSeries = -1},		-- ���羮jing9141
	},
	-- ���ṹ
	LOCK = 
	{
		-- 1�������ܲ��Ĭ��1��Ϊ��ʼ��
		[1] = {nTime = 15, nNum = 0,
			tbPrelock = {},
			tbStartEvent = 
			{
				{XoyoGame.TIME_INFO, -1, Lang.mission.str600[Lang.Idx], 1},		-- ˢ��
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
				{XoyoGame.MOVIE_DIALOG, -1, Lang.mission.str771[Lang.Idx]},
			},
			tbUnLockEvent = 
			{
				{XoyoGame.MOVIE_DIALOG, -1, Lang.mission.str772[Lang.Idx]},
				{XoyoGame.DEL_NPC, "boss"},
				{XoyoGame.DEL_NPC, "boss1"},
                {XoyoGame.DEL_NPC, "rumeng"},
                {XoyoGame.DEL_NPC, "chumeng"}, 
                {XoyoGame.DO_SCRIPT, "self.tbLock[3]:Close()"}, 
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
			},
		},
		[3] = {nTime = 0, nNum = 1,
			tbPrelock = {1},
			tbStartEvent = 
			{
				{XoyoGame.BLACK_MSG, -1, Lang.mission.str773[Lang.Idx]},
				{XoyoGame.ADD_NPC, 1, 1, 16, "boss", "zya8013"},		-- ˢ��
				{XoyoGame.ADD_NPC, 3, 1, 3, "rumeng", "hulu9140"},		-- ˢ��
				{XoyoGame.TARGET_INFO, -1, Lang.mission.str774[Lang.Idx]},
				{XoyoGame.TIME_INFO, -1, Lang.mission.str601[Lang.Idx], 2},
			},
			tbUnLockEvent = 
			{
				{XoyoGame.DO_SCRIPT, "self:RecordBlood([[boss]])"},
			},
		},
		[4] = {nTime = 15, nNum = 0,
			tbPrelock = {2},
			tbStartEvent = 
			{
				{XoyoGame.CLEAR_BUFF, -1},
				{XoyoGame.TIME_INFO, -1, Lang.mission.str616[Lang.Idx], 4},
				{XoyoGame.TARGET_INFO, -1, Lang.mission.str603[Lang.Idx]},
			},
			tbUnLockEvent = 
			{
			},
		},
		[5] = {nTime = 0, nNum = 1,
			tbPrelock = {3},
			tbStartEvent = 
			{
				{XoyoGame.BLACK_MSG, -1, Lang.mission.str775[Lang.Idx]},
				{XoyoGame.CLEAR_BUFF, -1},
				{XoyoGame.ADD_NPC, 2, 1, 12, "boss1", "zya9139"},		-- ˢ��
				{XoyoGame.ADD_NPC, 4, 1, 5, "chumeng", "jing9141"},		-- ˢ��
			},
			tbUnLockEvent = 
			{
				{XoyoGame.DO_SCRIPT, "self:RecordBlood([[boss1]])"},
			},
		},
		[6] = {nTime = 0, nNum = 1,
			tbPrelock = {5},
			tbStartEvent = 
			{
				{XoyoGame.CLEAR_BUFF, -1},
				{XoyoGame.ADD_NPC, 1, 1, 14, "boss", "zya8013"},		-- ˢ��
				{XoyoGame.DO_SCRIPT, "self:SetNpcBlood([[boss]])"},
				{XoyoGame.ADD_NPC, 3, 1, 6, "rumeng", "hulu9140"},		-- ˢ��
			},
			tbUnLockEvent = 
			{
				{XoyoGame.DO_SCRIPT, "self:RecordBlood([[boss]])"},
			},
		},
		[7] = {nTime = 0, nNum = 1,
			tbPrelock = {6},
			tbStartEvent = 
			{
				{XoyoGame.CLEAR_BUFF, -1},
				{XoyoGame.ADD_NPC, 2, 1, 12, "boss1", "zya9139"},		-- ˢ��
				{XoyoGame.DO_SCRIPT, "self:SetNpcBlood([[boss1]])"},
				{XoyoGame.ADD_NPC, 4, 1, 7, "chumeng", "jing9141"},		-- ˢ��
			},
			tbUnLockEvent = 
			{
				{XoyoGame.DO_SCRIPT, "self:RecordBlood([[boss1]])"},
			},
		},
		[8] = {nTime = 0, nNum = 1,
			tbPrelock = {7},
			tbStartEvent = 
			{
				{XoyoGame.CLEAR_BUFF, -1},
				{XoyoGame.ADD_NPC, 1, 1, 14, "boss", "zya8013"},		-- ˢ��
				{XoyoGame.DO_SCRIPT, "self:SetNpcBlood([[boss]])"},
				{XoyoGame.ADD_NPC, 3, 1, 8, "rumeng", "hulu9140"},		-- ˢ��
			},
			tbUnLockEvent = 
			{
				{XoyoGame.DO_SCRIPT, "self:RecordBlood([[boss]])"},
			},
		},
		[9] = {nTime = 0, nNum = 1,
			tbPrelock = {8},
			tbStartEvent = 
			{
				{XoyoGame.CLEAR_BUFF, -1},
				{XoyoGame.ADD_NPC, 2, 1, 12, "boss1", "zya9139"},		-- ˢ��
				{XoyoGame.DO_SCRIPT, "self:SetNpcBlood([[boss1]])"},
				{XoyoGame.ADD_NPC, 4, 1, 9, "chumeng", "jing9141"},		-- ˢ��
			},
			tbUnLockEvent = 
			{
				{XoyoGame.DO_SCRIPT, "self:RecordBlood([[boss1]])"},
			},
		},
		[10] = {nTime = 0, nNum = 1,
			tbPrelock = {9},
			tbStartEvent = 
			{
				{XoyoGame.BLACK_MSG, -1, Lang.mission.str776[Lang.Idx]},
				{XoyoGame.CLEAR_BUFF, -1},
				{XoyoGame.ADD_NPC, 1, 1, 10, "boss", "zya8013"},		-- ˢ��
				{XoyoGame.DO_SCRIPT, "self:SetNpcBlood([[boss]])"},
			},
			tbUnLockEvent = 
			{
			},
		},
		[11] = {nTime = 0, nNum = 1,
			tbPrelock = {10},
			tbStartEvent = 
			{
				{XoyoGame.CLEAR_BUFF, -1},
				{XoyoGame.ADD_NPC, 2, 1, 11, "boss1", "zya9139"},		-- ˢ��
				{XoyoGame.DO_SCRIPT, "self:SetNpcBlood([[boss1]])"},
			},
			tbUnLockEvent = 
			{      
				{XoyoGame.DO_SCRIPT, "self.tbTeam[1].bIsWiner = 1"},		-- ����������ñ�־              
                {XoyoGame.DO_SCRIPT, "self.tbLock[2]:Close()"},                                            
                {XoyoGame.DEL_NPC, "boss"}, 
                {XoyoGame.DEL_NPC, "boss1"},
                {XoyoGame.DEL_NPC, "rumeng"},
                {XoyoGame.DEL_NPC, "chumeng"},                                                                 
                {XoyoGame.CLOSE_INFO, -1},                                                                 
                {XoyoGame.CLEAR_BUFF, -1},                                                                 
                {XoyoGame.TARGET_INFO, -1, Lang.mission.str602[Lang.Idx]},                                                    
                {XoyoGame.MOVIE_DIALOG, -1, Lang.mission.str777[Lang.Idx]},  
			},
		},
		[12] = {nTime = 0, nNum = 1,
			tbPrelock = {1},
			tbStartEvent = 
			{
			},
			tbUnLockEvent = 
			{
			},
		},
		[13] = {nTime = 0, nNum = 1,
			tbPrelock = {12},
			tbStartEvent = 
			{
				{XoyoGame.DEL_NPC, "rumeng"},
                {XoyoGame.DEL_NPC, "chumeng"}, 
				{XoyoGame.CLEAR_BUFF, -1},
				{XoyoGame.ADD_NPC, 1, 1, 13, "boss", "zya8013"},		-- ˢ��
				{XoyoGame.DO_SCRIPT, "self:SetNpcBlood([[boss]])"},
			},
			tbUnLockEvent = 
			{
				{XoyoGame.DO_SCRIPT, "self.tbTeam[1].bIsWiner = 1"},		-- ����������ñ�־              
                {XoyoGame.DO_SCRIPT, "self.tbLock[2]:Close()"},                                            
                {XoyoGame.DEL_NPC, "boss"}, 
                {XoyoGame.DEL_NPC, "boss1"},
                {XoyoGame.DEL_NPC, "rumeng"},
                {XoyoGame.DEL_NPC, "chumeng"},                                                                 
                {XoyoGame.CLOSE_INFO, -1},                                                                 
                {XoyoGame.CLEAR_BUFF, -1},                                                                 
                {XoyoGame.TARGET_INFO, -1, Lang.mission.str602[Lang.Idx]},                                                    
                {XoyoGame.MOVIE_DIALOG, -1, Lang.mission.str777[Lang.Idx]},  
			},
		},
		[14] = {nTime = 0, nNum = 1,
			tbPrelock = {1},
			tbStartEvent = 
			{
			},
			tbUnLockEvent = 
			{
			},
		},
		[15] = {nTime = 0, nNum = 1,
			tbPrelock = {14},
			tbStartEvent = 
			{
				{XoyoGame.DEL_NPC, "rumeng"},
                {XoyoGame.DEL_NPC, "chumeng"}, 
				{XoyoGame.CLEAR_BUFF, -1},
				{XoyoGame.ADD_NPC, 2, 1, 15, "boss1", "zya9139"},		-- ˢ��
				{XoyoGame.DO_SCRIPT, "self:SetNpcBlood([[boss]])"},
			},
			tbUnLockEvent = 
			{
				{XoyoGame.DO_SCRIPT, "self.tbTeam[1].bIsWiner = 1"},		-- ����������ñ�־              
                {XoyoGame.DO_SCRIPT, "self.tbLock[2]:Close()"},                                            
                {XoyoGame.DEL_NPC, "boss"}, 
                {XoyoGame.DEL_NPC, "boss1"},
                {XoyoGame.DEL_NPC, "rumeng"},
                {XoyoGame.DEL_NPC, "chumeng"},                                                               
                {XoyoGame.CLOSE_INFO, -1},                                                                 
                {XoyoGame.CLEAR_BUFF, -1},                                                                 
                {XoyoGame.TARGET_INFO, -1, Lang.mission.str602[Lang.Idx]},                                                    
                {XoyoGame.MOVIE_DIALOG, -1, Lang.mission.str777[Lang.Idx]},  
			},
		},
		[16] = {nTime = 0, nNum = 1,
			tbPrelock = {1},
			tbStartEvent = 
			{
			},
			tbUnLockEvent = 
			{
			},
		},
		[17] = {nTime = 0, nNum = 1,
			tbPrelock = {16},
			tbStartEvent = 
			{
				{XoyoGame.DEL_NPC, "rumeng"},
                {XoyoGame.DEL_NPC, "chumeng"}, 
				{XoyoGame.CLEAR_BUFF, -1},
				{XoyoGame.ADD_NPC, 2, 1, 17, "boss1", "zya9139"},		-- ˢ��
			},
			tbUnLockEvent = 
			{
				{XoyoGame.DO_SCRIPT, "self.tbTeam[1].bIsWiner = 1"},		-- ����������ñ�־              
                {XoyoGame.DO_SCRIPT, "self.tbLock[2]:Close()"},                                            
                {XoyoGame.DEL_NPC, "boss"}, 
                {XoyoGame.DEL_NPC, "boss1"},
                {XoyoGame.DEL_NPC, "rumeng"},
                {XoyoGame.DEL_NPC, "chumeng"},                                                               
                {XoyoGame.CLOSE_INFO, -1},                                                                 
                {XoyoGame.CLEAR_BUFF, -1},                                                                 
                {XoyoGame.TARGET_INFO, -1, Lang.mission.str602[Lang.Idx]},                                                    
                {XoyoGame.MOVIE_DIALOG, -1, Lang.mission.str777[Lang.Idx]},  
			},
		},
		[18] = {nTime = 1, nNum = 0,
			tbPrelock = {3},
			tbStartEvent = 
			{
			},
			tbUnLockEvent = 
			{
				{XoyoGame.DEL_NPC, "boss"},
			},
		},
		[19] = {nTime = 1, nNum = 0,
			tbPrelock = {5},
			tbStartEvent = 
			{
			},
			tbUnLockEvent = 
			{
				{XoyoGame.DEL_NPC, "boss1"},
			},
		},
		[20] = {nTime = 1, nNum = 0,
			tbPrelock = {6},
			tbStartEvent = 
			{
			},
			tbUnLockEvent = 
			{
				{XoyoGame.DEL_NPC, "boss"},
			},
		},
		[21] = {nTime = 1, nNum = 0,
			tbPrelock = {7},
			tbStartEvent = 
			{
			},
			tbUnLockEvent = 
			{
				{XoyoGame.DEL_NPC, "boss1"},
			},
		},
		[22] = {nTime = 1, nNum = 0,
			tbPrelock = {8},
			tbStartEvent = 
			{
			},
			tbUnLockEvent = 
			{
				{XoyoGame.DEL_NPC, "boss"},
			},
		},
		[23] = {nTime = 1, nNum = 0,
			tbPrelock = {9},
			tbStartEvent = 
			{
			},
			tbUnLockEvent = 
			{
				{XoyoGame.DEL_NPC, "boss1"},
			},
		},
	}
}