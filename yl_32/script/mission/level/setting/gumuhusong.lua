Include("script/mission/level/xoyogame_def.lua");

local tbRoom = XoyoGame.RoomSetting.tbRoom;

tbRoom[17] =    --��Ĺ����
{
	fnPlayerGroup 	= nil,						-- ��ҷ�Ⱥ����,������Ĭ��1֧����1��Ⱥ��
	fnDeath			= nil,						-- ���������ű�; ������Ĭ��
	fnWinRule		= nil,						-- ʤ��������������ķ�����Ҫ�ض��壬����һ�㲻��Ҫ��
	nRoomLevel		= 3,						-- ����ȼ�(1~5)
	nMapIndex		= 21,						-- ��ͼ�������
	tbBeginPoint	= {2958, 1796, 1048576},	-- ��ʼ�㣬��ʽ����fnPlayerGroup���������Ĭ����{nX,nY}
	-- �����漰��NPC����
	NPC = 
	{
-- 		���  	npcģ��		�ȼ�(-1Ĭ��)(ǿ�ȱ�id��)	5��(Ĭ��-1)
-- E.g  [0] = {nTemplate, 			nLevel, 		nSeries }
		[1] = {nTemplate = 8025, nLevel = {8057,8057,8057}, nSeries = -1},		-- С��
		[2] = {nTemplate = 8026, nLevel = {8058,8059,8060}, nSeries = -1},		-- �Ļ�
		[3] = {nTemplate = 8027, nLevel = {8061,8062,8063}, nSeries = -1},		-- ��ʬ
		[4] = {nTemplate = 9073, nLevel = {8056,8056,8056}, nSeries = -1},      --off���
		[5] = {nTemplate = 9074, nLevel = {8056,8056,8056}, nSeries = -1},      --on���
		[6] = {nTemplate = 9075, nLevel = {8056,8056,8056}, nSeries = -1},      --off���
		[7] = {nTemplate = 9076, nLevel = {8056,8056,8056}, nSeries = -1},      --on���
		[8] = {nTemplate = 9120, nLevel = {8058,8059,8060}, nSeries = -1},		-- �Ļ�
		[9] = {nTemplate = 9121, nLevel = {8058,8059,8060}, nSeries = -1},		-- �Ļ�
		[10] = {nTemplate = 9122, nLevel = {8058,8059,8060}, nSeries = -1},		-- �Ļ�
		[11] = {nTemplate = 9123, nLevel = {8058,8059,8060}, nSeries = -1},		-- �Ļ�
		[12] = {nTemplate = 9124, nLevel = {8058,8059,8060}, nSeries = -1},		-- �Ļ�
		[13] = {nTemplate = 9125, nLevel = {8058,8059,8060}, nSeries = -1},		-- �Ļ�
		[14] = {nTemplate = 9126, nLevel = {8058,8059,8060}, nSeries = -1},		-- �Ļ�
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
		[2] = {nTime = 240, nNum = 0,		-- �ܼ�ʱ
			tbPrelock = {1},
			tbStartEvent = 
			{
				{XoyoGame.REVIVE_INFO, false, false, true, 97, 1897,2918, 1048576},
			},
			tbUnLockEvent = 
			{
				{XoyoGame.MOVIE_DIALOG, -1, Lang.mission.str644[Lang.Idx]},
				{XoyoGame.DEL_NPC, "xiaoli"},
				{XoyoGame.DEL_NPC, "boss"},
				{XoyoGame.DEL_NPC, "guaiwu"},
				{XoyoGame.DO_SCRIPT, "self.tbLock[3]:Close()"},
				{XoyoGame.DO_SCRIPT, "self.tbLock[4]:Close()"},
				{XoyoGame.DO_SCRIPT, "self.tbLock[5]:Close()"},
				{XoyoGame.DO_SCRIPT, "self.tbLock[6]:Close()"},
				{XoyoGame.DO_SCRIPT, "self.tbLock[7]:Close()"},
			},
		},
		[3] = {nTime = 0, nNum = 2,
			tbPrelock = {1},
			tbStartEvent = 
			{				
				{XoyoGame.MOVIE_DIALOG, -1, Lang.mission.str645[Lang.Idx]},
				{XoyoGame.TARGET_INFO, -1, Lang.mission.str646[Lang.Idx]},
				{XoyoGame.TIME_INFO, -1, Lang.mission.str601[Lang.Idx], 2},
			},
			tbUnLockEvent = 
			{		
			},
		},
		[4] = {nTime = 0, nNum = 1,		-- ����npc
			tbPrelock = {6,7},
			tbStartEvent = 
			{
				{XoyoGame.ADD_NPC, 1, 1, 0, "xiaoli", "xiaoli8057"},		-- ˢ��
				{XoyoGame.ADD_NPC, 3, 1, 4, "boss", "tieshi8061"},		-- ˢ��
				{XoyoGame.MOVIE_DIALOG, -1, Lang.mission.str647[Lang.Idx]},
				{XoyoGame.TARGET_INFO, -1, Lang.mission.str648[Lang.Idx],4},
				{XoyoGame.TIME_INFO, -1, Lang.mission.str601[Lang.Idx], 2},
			},
			tbUnLockEvent = 
			{
				{XoyoGame.MOVIE_DIALOG, -1, Lang.mission.str649[Lang.Idx]},
				
			},
		},
		[5] = {nTime = 0, nNum = 32,
			tbPrelock = {4},
			tbStartEvent = 
			{				
				{XoyoGame.ADD_NPC, 2, 4, 5, "guaiwu", "youhun8058"},		-- �Ļ�
				{XoyoGame.ADD_NPC, 8, 4, 5, "guaiwu", "youhun9120"},		-- �Ļ�
				{XoyoGame.ADD_NPC, 9, 4, 5, "guaiwu", "youhun9121"},		-- �Ļ�
				{XoyoGame.ADD_NPC, 10, 4, 5, "guaiwu", "youhun9122"},		-- �Ļ�
				{XoyoGame.ADD_NPC, 11, 4, 5, "guaiwu", "youhun9123"},		-- �Ļ�
				{XoyoGame.ADD_NPC, 12, 4, 5, "guaiwu", "youhun9124"},		-- �Ļ�
				{XoyoGame.ADD_NPC, 13, 4, 5, "guaiwu", "youhun9125"},		-- �Ļ�
				{XoyoGame.ADD_NPC, 14, 4, 5, "guaiwu", "youhun9126"},		-- �Ļ�
				{XoyoGame.TARGET_INFO, -1, Lang.mission.str650[Lang.Idx],5},
				{XoyoGame.TIME_INFO, -1, Lang.mission.str601[Lang.Idx], 2},
			},
			tbUnLockEvent = 
			{
				{XoyoGame.DO_SCRIPT, "self.tbTeam[1].bIsWiner = 1"},		-- ����������ñ�־
				{XoyoGame.DO_SCRIPT, "self.tbLock[2]:Close()"},
				{XoyoGame.DO_SCRIPT, "self.tbLock[3]:Close()"},
				{XoyoGame.DEL_NPC, "boss"},
				{XoyoGame.DEL_NPC, "guaiwu"},
				{XoyoGame.DEL_NPC, "xiaoli"},
				{XoyoGame.DEL_NPC, "huoba1off1"},
				{XoyoGame.DEL_NPC, "huoba1on1"},
				{XoyoGame.DEL_NPC, "huoba2off1"},
				{XoyoGame.DEL_NPC, "huoba2on1"},
				{XoyoGame.CLOSE_INFO, -1},
				{XoyoGame.TARGET_INFO, -1, Lang.mission.str602[Lang.Idx]},
			},
		},
		[6] = {nTime = 0, nNum = 1,
			tbPrelock = {1},
			tbStartEvent = 
			{				
				{XoyoGame.ADD_NPC, 4, 1, 6, "huoba1off1", "huoba1off"},	
				{XoyoGame.TIME_INFO, -1, Lang.mission.str601[Lang.Idx], 2},
			},
			tbUnLockEvent = 
			{		
				{XoyoGame.ADD_NPC, 5, 1, 0, "huoba1on1", "huoba1on"},	
			},
		},
		[7] = {nTime = 0, nNum = 1,
			tbPrelock = {1},
			tbStartEvent = 
			{				
				{XoyoGame.ADD_NPC, 6, 1, 7, "huoba2off1", "huoba2off"},	
				{XoyoGame.TIME_INFO, -1, Lang.mission.str601[Lang.Idx], 2},
			},
			tbUnLockEvent = 
			{	
				{XoyoGame.ADD_NPC, 7, 1, 0, "huoba2on1", "huoba2on"},	
			},
		},
		[8] = {nTime = 15, nNum = 0,
			tbPrelock = {2},
			tbStartEvent = 
			{
				{XoyoGame.TIME_INFO, -1, Lang.mission.str651[Lang.Idx], 8},
				{XoyoGame.TARGET_INFO, -1, Lang.mission.str603[Lang.Idx]},
			},
			tbUnLockEvent = 
			{
			},
		},
	}
}