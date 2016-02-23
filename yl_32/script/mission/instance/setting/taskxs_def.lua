Include("script/mission/instance/instance_def.lua")
if not Instance.tbSetting then
	Instance.tbSetting = {}
end

local InstanceSetting = Instance.tbSetting;


InstanceSetting[100]=
{
	nTaskInstance = 1;
    nMinLevel = 1;
    nMaxLevel = 60;
	nMapId = 100;
	nEnemyNum = 12;
    tbBeginPos = {1027,600,1048576},
	tbLeavePos = {3,6023,2065,1048576},

    -- �����漰��NPC����
	NPC =
	{
-- 		���  	npcģ��				�ȼ�(-1Ĭ��)	5��(Ĭ��-1)
        [1] = {nTemplate = 16, nLevel = 1, nSeries = -1},		-- ���
        [2] = {nTemplate = 15, nLevel = 1, nSeries = -1},		-- ħ��
		[4] = {nTemplate = 17, nLevel = 1, nSeries = -1},		-- ħ��
		[5] = {nTemplate = 18, nLevel = 1, nSeries = -1},		-- ħ��
		[6] = {nTemplate = 19, nLevel = -1, nSeries = -1},		-- ��Ч
		[7] = {nTemplate = 20, nLevel = 1, nSeries = -1},		-- ������
		[8] = {nTemplate = 21, nLevel = 1, nSeries = -1},		-- ���
		[9] = {nTemplate = 22, nLevel = 1, nSeries = -1},		-- ���
		[10] = {nTemplate = 23, nLevel = 1, nSeries = -1},		-- ħ��(����)
		[11] = {nTemplate = 13, nLevel = 1, nSeries = -1},		-- ħ��
		[12] = {nTemplate = 14, nLevel = 1, nSeries = -1},		-- ħ��
		[13] = {nTemplate = 24, nLevel = 1, nSeries = -1},		-- ��ħ����
		[14] = {nTemplate = 11, nLevel = -1, nSeries = -1},		-- ��ʯ

	},

    LOCK =
    {
       -- 1�������ܲ��Ĭ��1��Ϊ��ʼ��
		[1] = {nTime = 1, nNum = 0,		-- �ܼ�ʱ
			tbPrelock = {},
			tbStartEvent =
			{
			    	{Instance.TIME_INFO, -1, Lang.mission.str229[Lang.Idx]},
					--  {Instance.ADD_NPC, 7, 1, 8, "erlangshen", "erlangshen"},
					--{Instance.ADD_NPC, 8, 1, 8, "tianbing2", "tianbing2"},
					{Instance.ADD_NPC, 14, 1, 1, "yunshi", "yunshi"},
			},
			tbUnLockEvent =
			{
				{Instance.NOVICE_GUIDE, -1, 6},
				--{Instance.DEL_NPC, "erlangshen",},
				--{Instance.DEL_NPC, "tianbing2",},
				{Instance.DEL_NPC, "yunshi",},
			},
		},
		[2] = {nTime = 0, nNum = 5 ,		-- ��һ��
			tbPrelock = {1},
			tbStartEvent =
			{
			    {Instance.ADD_NPC, 2, 1, 2, "5", "mobing4"},
				{Instance.NPC_BUBBLE, -1, "5", Lang.mission.str535[Lang.Idx], 1},
				{Instance.ADD_NPC, 2, 2, 2, "mobing", "mobing"},
				{Instance.ADD_NPC, 11, 1, 2, "mobing11", "mobing11"},
				{Instance.ADD_NPC, 12, 1, 2, "mobing22", "mobing22"},
				{Instance.ADD_NPC, 6, 1, 2, "7", "texiao1"},
				{Instance.TARGET_INFO, -1, Lang.mission.str536[Lang.Idx]},
				--{Instance.SHOW_NOTICE_STATE, -1, "���ǵ�֧Ԯ����С�ģ�"},
			},
			tbUnLockEvent =
			{
				{Instance.ADD_NPC, 6, 1, 3, "8", "texiao2"},
				{Instance.ADD_NPC, 6, 1, 3, "9", "texiao3"},
				{Instance.ADD_NPC, 6, 1, 3, "10", "texiao4"},
				{Instance.DEL_NPC, "7",},
				--{Instance.REMOVE_NOTICE_STATE, -1, "���ǵ�֧Ԯ����С�ģ�"},
			},
		},
		[3] = {nTime = 0, nNum = 6 ,		-- �ڶ���
			tbPrelock = {2},
			tbStartEvent =
			{
				{Instance.ADD_NPC, 4, 1, 3, "2", "mobing2"},
				{Instance.ADD_NPC, 5, 1, 3, "3", "mobing3"},
				{Instance.ADD_NPC, 10, 1, 3, "5", "mobing5"},
				{Instance.NPC_BUBBLE, -1, "3", Lang.mission.str407[Lang.Idx], 1},
				{Instance.ADD_NPC, 1, 2, 3, "7", "tianbing"},
				{Instance.ADD_NPC, 1, 1, 3, "tianbing11", "tianbing11"},
				{Instance.ADD_NPC, 2, 3, 3, "7", "mobing1"},
				{Instance.DEL_NPC, "8",},
				{Instance.DEL_NPC, "9",},
				{Instance.DEL_NPC, "10",},
				{Instance.TARGET_INFO, -1, Lang.mission.str536[Lang.Idx]},
			},
			tbUnLockEvent =
			{

			},
		},
		[4] = {nTime = 2, nNum = 0 ,		-- ������
			tbPrelock = {3},
			tbStartEvent =
			{
		        {Instance.NPC_BUBBLE, -1, "tianbing11", Lang.mission.str537[Lang.Idx], 1},
			  -- {Instance.ADD_NPC, 10, 3, 4, "9", "mobing9"},
				--{Instance.ADD_NPC, 10, 1, 4, "13", "mobing10"},
				--{Instance.NPC_BUBBLE, -1, "13", "�������꣡��", 1},
			--	{Instance.ADD_NPC, 6, 1, 4, "10", "texiao5"},
				--{Instance.ADD_NPC, 6, 1, 4, "11", "texiao6"},
				--{Instance.ADD_NPC, 6, 1, 4, "12", "texiao7"},
				--{Instance.DEL_NPC, "7",},
				{Instance.TARGET_INFO, -1, Lang.mission.str232[Lang.Idx]},

			},
			tbUnLockEvent =
			{
			{Instance.ADD_NPC, 14, 1, 1, "yunshi", "yunshi"},
			},
		},
		[5] = {nTime = 1, nNum = 0 ,		-- �ܼ�ʱ
			tbPrelock = {4},
			tbStartEvent =
			{
                --{Instance.DEL_NPC, "10",},
				--{Instance.DEL_NPC, "11",},
				--{Instance.DEL_NPC, "12",},
			},
			tbUnLockEvent =
			{
			},
		},
		[6] = {nTime = 0, nNum = 1 ,		-- ���
			tbPrelock = {5},
			tbStartEvent =
			{
			      {Instance.ADD_NPC, 13, 1, 6, "jingying", "jingying"},
				  {Instance.NPC_BUBBLE, -1, "jingying", Lang.mission.str538[Lang.Idx], 1},
			    --{Instance.ADD_NPC, 7, 1, 6, "1", "tianbing1"},
				--{Instance.ADD_NPC, 8, 1, 6, "2", "tianbing2"},
				--{Instance.ADD_NPC, 9, 1, 6, "3", "tianbing3"},
				--{Instance.NPC_BUBBLE, -1, "2", "������һ������", 1},
				{Instance.TARGET_INFO, -1, Lang.mission.str539[Lang.Idx]},

			},
			tbUnLockEvent =
			{
			},
		},
		[7] = {nTime = 1, nNum = 0 ,		-- ���
			tbPrelock = {4},
			tbStartEvent =
			{
			   -- {Instance.DEL_NPC, "7",},
				--{Instance.DEL_NPC, "tianbing11",},
			    --{Instance.ADD_NPC, 13, 1, 7, "jiangjun", "mobing10"},
				--{Instance.NPC_BUBBLE, -1, "jiangjun", "�����ܵ������ң���", 1},
				--{Instance.NPC_BUBBLE, -1, "tianbing11", "��ȥ~���˸���ģ�", 1},
				--{Instance.NPC_BUBBLE, -1, "3", "��л��λ����������", 1},

			},
			tbUnLockEvent =
			{
				--{Instance.DEL_NPC, "1",},
				--{Instance.DEL_NPC, "2",},
				--{Instance.DEL_NPC, "3",},
				--{Instance.NPC_BUBBLE, -1, "erlangshen", "��~������", 1},
			},
		},
		[8] = {nTime = 1, nNum = 0 ,		-- ���
			tbPrelock = {4},
			tbStartEvent =
			{


			},
			tbUnLockEvent =
			{
				--{Instance.DEL_NPC, "1",},
				--{Instance.DEL_NPC, "2",},
				--{Instance.DEL_NPC, "3",},
				--{Instance.ADD_NPC, 7, 1, 8, "erlangshen", "erlangshen"},
				--{Instance.NPC_BUBBLE, -1, "erlangshen", "����үү�ڴˣ�", 1},
			},
		},
		[9] = {nTime = 1, nNum = 0 ,		-- ���
			tbPrelock = {6},
			tbStartEvent =
			{
            -- {Instance.UNLOCK_GOD, -1, 9, 1},               --��������
			},
			tbUnLockEvent =
			{
				--{Instance.DEL_NPC, "1",},
				--{Instance.DEL_NPC, "2",},
				--{Instance.DEL_NPC, "3",},
				--{Instance.ADD_NPC, 7, 1, 8, "erlangshen", "erlangshen"},
				--{Instance.NPC_BUBBLE, -1, "erlangshen", "����үү�ڴˣ�", 1},
			},
		},
		[10] = {nTime = 1, nNum = 0 ,		-- ��������
			tbPrelock = {9},
			tbStartEvent =
			{

			},
			tbUnLockEvent =
			{
				{Instance.DO_SCRIPT, "self.bFinishTask = 1"},
				{Instance.TARGET_INFO, -1, Lang.mission.str236[Lang.Idx]},
				{Instance.SHOW_REWARD_PANEL, -1, 0},
			    {Instance.DO_SCRIPT, "self.tbLock[11]:Close()"},
			},
		},
		[11] = {nTime = 0, nNum = 1,		-- �ܼ�ʱ
			tbPrelock = {1},
			tbStartEvent =
			{
			},
			tbUnLockEvent =
			{
             {Instance.REVIVE_INFO, true, true, false},
			},
		},

    }
}
InstanceSetting[101]=
{
	nTaskInstance = 1;
    nMinLevel = 1;
    nMaxLevel = 60;
	nMapId = 101;
	nEnemyNum = 11;
    tbBeginPos = {2164,559,1048576},
	tbLeavePos = {3,6023,2065,1048576},

    -- �����漰��NPC����
	NPC =
	{
-- 		���  	npcģ��				�ȼ�(-1Ĭ��)	5��(Ĭ��-1)
        [1] = {nTemplate = 26, nLevel = 3, nSeries = -1},		-- ������
        [2] = {nTemplate = 25, nLevel = 1, nSeries = -1},		-- С��
		[3] = {nTemplate = 28, nLevel = 3, nSeries = -1},		-- ������
		[4] = {nTemplate = 31, nLevel = -1, nSeries = -1},		-- ���
		[5] = {nTemplate = 27, nLevel = 2, nSeries = -1},		-- �й�
		[6] = {nTemplate = 30, nLevel = -1, nSeries = -1},		-- С������)
		[7] = {nTemplate = 29, nLevel = 1, nSeries = -1},		-- С��

	},

    LOCK =
    {
       -- 1�������ܲ��Ĭ��1��Ϊ��ʼ��
		[1] = {nTime = 1, nNum = 0,		-- �ܼ�ʱ
			tbPrelock = {},
			tbStartEvent =
			{
			    	{Instance.TIME_INFO, -1, Lang.mission.str229[Lang.Idx]},
			},
			tbUnLockEvent =
			{
				{Instance.NOVICE_GUIDE, -1, 6},
			},
		},
		[2] = {nTime = 0, nNum = 6 ,		-- С��
			tbPrelock = {1},
			tbStartEvent =
			{
				{Instance.ADD_NPC, 2, 4, 2, "2", "shouwei"},
				{Instance.ADD_NPC, 7, 2, 2, "4", "shouwei4"},
				{Instance.ADD_NPC, 4, 2, 2, "3", "huoguo"},
				{Instance.TARGET_INFO, -1, Lang.mission.str540[Lang.Idx]},
			},
			tbUnLockEvent =
			{
			},
		},
		[3] = {nTime = 9, nNum = 0 ,		-- ����
			tbPrelock = {2},
			tbStartEvent =
			{
				{Instance.ADD_NPC, 6, 1, 3, "5", "shouwei2"},
				{Instance.NPC_BUBBLE, -1, "5", Lang.mission.str542[Lang.Idx], 1},
				{Instance.NPC_BUBBLE, -1, "5", Lang.mission.str541[Lang.Idx], 2},
			},
			tbUnLockEvent =
			{
			{Instance.DEL_NPC, "5",},
			},
		},
		[4] = {nTime = 2, nNum = 0 ,		-- �ܼ�ʱ
			tbPrelock = {2},
			tbStartEvent =
			{
			},
			tbUnLockEvent =
			{
			},
		},
		[5] = {nTime = 0, nNum = 5 ,		-- �й�+�ڰ׹�
			tbPrelock = {4},
			tbStartEvent =
			{
				{Instance.ADD_NPC, 5, 3, 5, "4", "shouwei3"},
				{Instance.ADD_NPC, 1, 1, 5, "7", "quan"},
				{Instance.ADD_NPC, 3, 1, 5, "6", "heigui"},
				{Instance.TARGET_INFO, -1, Lang.mission.str540[Lang.Idx]},
			},
			tbUnLockEvent =
			{
			},
		},
		[6] = {nTime = 1, nNum = 0 ,		-- �ܼ�ʱ
			tbPrelock = {5},
			tbStartEvent =
			{
			},
			tbUnLockEvent =
			{
				{Instance.DO_SCRIPT, "self.bFinishTask = 1"},
				{Instance.TARGET_INFO, -1, Lang.mission.str236[Lang.Idx]},
				{Instance.SHOW_REWARD_PANEL, -1, 0},
			    {Instance.DO_SCRIPT, "self.tbLock[7]:Close()"},
			},
		},
		[7] = {nTime = 0, nNum = 1,		-- �ܼ�ʱ
			tbPrelock = {1},
			tbStartEvent =
			{
			},
			tbUnLockEvent =
			{
             {Instance.REVIVE_INFO, true, true, false},
			},
		},

    }
}
InstanceSetting[102]=
{
	nTaskInstance = 1;
    nMinLevel = 1;
    nMaxLevel = 60;
	nMapId = 102;
	nEnemyNum = 30;
    tbBeginPos = {3841,2963,1048576},
	tbLeavePos = {3,2693,6492,1048576},

    -- �����漰��NPC����
	NPC =
	{
-- 		���  	npcģ��				�ȼ�(-1Ĭ��)	5��(Ĭ��-1)
        [1] = {nTemplate = 36, nLevel = 3, nSeries = -1},		-- ���
        [2] = {nTemplate = 35, nLevel = 3, nSeries = -1},		-- ���
		[3] = {nTemplate = 37, nLevel = -1, nSeries = -1},		-- ������1
		[4] = {nTemplate = 38, nLevel = 4, nSeries = -1},		-- ��֣��У�
		[5] = {nTemplate = 39, nLevel = 4, nSeries = -1},		-- ��֣���
		[6] = {nTemplate = 34, nLevel = -1, nSeries = -1},		-- ������2
		[7] = {nTemplate = 33, nLevel = -1, nSeries = -1},		-- ����
	},

    LOCK =
    {
       -- 1�������ܲ��Ĭ��1��Ϊ��ʼ��
		[1] = {nTime = 1, nNum = 0,		-- �ܼ�ʱ
			tbPrelock = {},
			tbStartEvent =
			{
			    	{Instance.TIME_INFO, -1, Lang.mission.str229[Lang.Idx]},
			},
			tbUnLockEvent =
			{
				{Instance.NOVICE_GUIDE, -1, 6},
			},
		},
		[2] = {nTime = 0, nNum = 8 ,		-- ��һ��
			tbPrelock = {1},
			tbStartEvent =
			{
				{Instance.ADD_NPC, 1, 6, 2, "1", "yuguai"},
				{Instance.ADD_NPC, 1, 1, 2, "3", "yuguai6"},
				{Instance.ADD_NPC, 1, 1, 2, "2", "yuguai1"},
				{Instance.NPC_BUBBLE, -1, "3", Lang.mission.str543[Lang.Idx], 1},
				{Instance.TARGET_INFO, -1, Lang.mission.str544[Lang.Idx]},
			},
			tbUnLockEvent =
			{
			},
		},
		[3] = {nTime = 4, nNum = 0 ,		-- ��һ������
			tbPrelock = {2},
			tbStartEvent =
			{
				{Instance.ADD_NPC, 3, 1, 3, "2", "shenmiren"},
				{Instance.ADD_NPC, 7, 1, 3, "1", "yinxing"},
				{Instance.NPC_BUBBLE, -1, "2", Lang.mission.str545[Lang.Idx], 2},
				--{Instance.SHOW_NOTICE_STATE, -1, Lang.mission.str237[Lang.Idx]},
			},
			tbUnLockEvent =
			{
			 {Instance.DEL_NPC, "2",},
			 {Instance.DEL_NPC, "1",},
			-- {Instance.REMOVE_NOTICE_STATE, -1, Lang.mission.str237[Lang.Idx]},
			},
		},
		[4] = {nTime = 0, nNum = 9 ,		-- �ܼ�ʱ
			tbPrelock = {3},
			tbStartEvent =
			{
				{Instance.ADD_NPC, 2, 9, 4, "1", "yuguai2"},
				{Instance.TARGET_INFO, -1, Lang.mission.str544[Lang.Idx]},
			},
			tbUnLockEvent =
			{
			},
		},
		[5] = {nTime = 1, nNum = 0 ,		-- �ܼ�ʱ
			tbPrelock = {4},
			tbStartEvent =
			{

			},
			tbUnLockEvent =
			{
			},
		},
		[6] = {nTime = 0, nNum = 7 ,		-- �ܼ�ʱ
			tbPrelock = {5},
			tbStartEvent =
			{
				{Instance.ADD_NPC, 4, 6, 6, "1", "yuguai4"},
				{Instance.ADD_NPC, 4, 1, 6, "2", "yuguai7"},
				{Instance.NPC_BUBBLE, -1, "2",Lang.mission.str546[Lang.Idx],1},
				{Instance.TARGET_INFO, -1, Lang.mission.str544[Lang.Idx]},
			},
			tbUnLockEvent =
			{
			},
		},
		[7] = {nTime = 5, nNum = 0 ,		-- �ܼ�ʱ
			tbPrelock = {6},
			tbStartEvent =
			{
				{Instance.ADD_NPC, 6, 1, 7, "1", "shenmiren1"},
				{Instance.NPC_BUBBLE, -1, "1", Lang.mission.str547[Lang.Idx], 1},
				{Instance.NPC_BUBBLE, -1, "1", Lang.mission.str548[Lang.Idx], 3},
				--{Instance.SHOW_NOTICE_STATE, -1, Lang.mission.str237[Lang.Idx]},
			},
			tbUnLockEvent =
			{
			-- {Instance.REMOVE_NOTICE_STATE, -1, Lang.mission.str237[Lang.Idx]},
			{Instance.DEL_NPC,"1",},
			},
		},
		[8] = {nTime = 0, nNum = 6 ,		-- �ܼ�ʱ
			tbPrelock = {7},
			tbStartEvent =
			{
				{Instance.ADD_NPC, 5, 4, 8, "1", "yuguai5"},
				{Instance.ADD_NPC, 5, 1, 8, "2", "yuguai8"},
				{Instance.ADD_NPC, 5, 1, 8, "3", "yuguai10"},
				{Instance.NPC_BUBBLE, -1, "2", Lang.mission.str549[Lang.Idx], 1},
				--{Instance.NPC_BUBBLE, -1, "3", "��Ծ���ţ�", 3},
				{Instance.TARGET_INFO, -1, Lang.mission.str544[Lang.Idx]},
			},
			tbUnLockEvent =
			{
			},
		},
		[9] = {nTime = 0, nNum = 0 ,		-- �ܼ�ʱ
			tbPrelock = {8},
			tbStartEvent =
			{
				--{Instance.ADD_NPC, 5, 2, 9, "1", "yuguai5"},
				--{Instance.ADD_NPC, 5, 1, 9, "2", "yuguai8"},
				--{Instance.ADD_NPC, 5, 1, 9, "3", "yuguai10"},
				--{Instance.NPC_BUBBLE, -1, "2", "�������ӣ�", 1},
				--{Instance.NPC_BUBBLE, -1, "3", "���쿾�㣡", 3},
				--{Instance.TARGET_INFO, -1, Lang.mission.str544[Lang.Idx]},
			},
			tbUnLockEvent =
			{
			},
		},
		[10] = {nTime = 1, nNum = 0 ,		-- �ܼ�ʱ
			tbPrelock = {9},
			tbStartEvent =
			{
			},
			tbUnLockEvent =
			{
				{Instance.DO_SCRIPT, "self.bFinishTask = 1"},
				{Instance.TARGET_INFO, -1, Lang.mission.str236[Lang.Idx]},
				{Instance.SHOW_REWARD_PANEL, -1, 0},
			    {Instance.DO_SCRIPT, "self.tbLock[11]:Close()"},
			},
		},
		[11] = {nTime = 0, nNum = 1,		-- �ܼ�ʱ
			tbPrelock = {1},
			tbStartEvent =
			{
			},
			tbUnLockEvent =
			{
             {Instance.REVIVE_INFO, true, true, false},
			},
		},

    }
}
InstanceSetting[103]=
{
	nTaskInstance = 1;
    nMinLevel = 1;
    nMaxLevel = 60;
	nMapId = 103;
	nEnemyNum = 12;
    tbBeginPos = {3841,2963,1048576},
	tbLeavePos = {3,2693,6492,1048576},

    -- �����漰��NPC����
	NPC =
	{
-- 		���  	npcģ��				�ȼ�(-1Ĭ��)	5��(Ĭ��-1)
        [1] = {nTemplate = 41, nLevel = 5, nSeries = -1},		-- ��̫��
        [2] = {nTemplate = 40, nLevel = 4, nSeries = -1},		-- ���
		[3] = {nTemplate = 36, nLevel = 4, nSeries = -1},		-- ���
		[4] = {nTemplate = 42, nLevel = 5, nSeries = -1},		-- ��
		[5] = {nTemplate = 43, nLevel = 1, nSeries = -1},		-- ��������
		[6] = {nTemplate = 44, nLevel = -1, nSeries = -1},		-- �ڵ�
		[7] = {nTemplate = 45, nLevel = -1, nSeries = -1},		-- ��ӡ
		[8] = {nTemplate = 46, nLevel = -1, nSeries = -1},		-- ��̫�Ӿ���
		[9] = {nTemplate = 47, nLevel = -1, nSeries = -1},		-- �ڵ�����
		[10] = {nTemplate = 48, nLevel = 4, nSeries = -1},		-- ˮ��

	},

    LOCK =
    {
       -- 1�������ܲ��Ĭ��1��Ϊ��ʼ��
		[1] = {nTime = 1, nNum = 0,		-- �ܼ�ʱ
			tbPrelock = {},
			tbStartEvent =
			{
			    	{Instance.TIME_INFO, -1, Lang.mission.str229[Lang.Idx]},
			},
			tbUnLockEvent =
			{
				{Instance.NOVICE_GUIDE, -1, 6},
			},
		},
		[2] = {nTime = 0, nNum = 0 ,		-- �ܼ�ʱ
			tbPrelock = {1},
			tbStartEvent =
			{
				--{Instance.ADD_NPC, 3, 7, 2, "1", "yuguai"},
				--{Instance.ADD_NPC, 3, 1, 2, "2", "yuguai1"},
				--{Instance.NPC_BUBBLE, -1, "2", "��β������������ˣ�", 1},
			--	{Instance.TARGET_INFO, -1, Lang.mission.str544[Lang.Idx]},
			},
			tbUnLockEvent =
			{
			},
		},
		[3] = {nTime = 0, nNum = 4 ,		-- �ܼ�ʱ
			tbPrelock = {2},
			tbStartEvent =
			{
				{Instance.ADD_NPC, 2, 3, 3, "1", "yuguai2"},
				{Instance.ADD_NPC, 2, 1, 3, "2", "yuguai6"},
				{Instance.NPC_BUBBLE, -1, "2", Lang.mission.str550[Lang.Idx], 1},
				{Instance.TARGET_INFO, -1, Lang.mission.str544[Lang.Idx]},
			},
			tbUnLockEvent =
			{
			},
		},
		[4] = {nTime = 0, nNum = 4 ,		-- �ܼ�ʱ
			tbPrelock = {3},
			tbStartEvent =
			{
			{Instance.ADD_NPC, 2, 3, 4, "1", "yuguai3"},
			{Instance.ADD_NPC, 2, 1, 4, "2", "yuguai7"},
			{Instance.NPC_BUBBLE, -1, "2", Lang.mission.str551[Lang.Idx], 1},
			{Instance.TARGET_INFO, -1, Lang.mission.str544[Lang.Idx]},
			},
			tbUnLockEvent =
			{
			},
		},
		[5] = {nTime = 0, nNum = 3 ,		-- �ܼ�ʱ
			tbPrelock = {4},
			tbStartEvent =
			{
			{Instance.ADD_NPC, 2, 2, 5, "1", "yuguai4"},
			{Instance.ADD_NPC, 2, 1, 5, "2", "yuguai8"},
			{Instance.NPC_BUBBLE, -1, "2", Lang.mission.str552[Lang.Idx], 1},
			{Instance.TARGET_INFO, -1, Lang.mission.str544[Lang.Idx]},
			},
			tbUnLockEvent =
			{
			},
		},
		[6] = {nTime = 0, nNum = 0 ,		-- �ܼ�ʱ
			tbPrelock = {5},
			tbStartEvent =
			{
				--{Instance.ADD_NPC, 10, 4, 6, "1", "shuiyao2"},
				--{Instance.ADD_NPC, 10, 1, 6, "2", "shuiyao8"},
				--{Instance.NPC_BUBBLE, -1, "2", "�������������������ס����", 1},
				--{Instance.TARGET_INFO, -1, Lang.mission.str544[Lang.Idx] },
			},
			tbUnLockEvent =
			{
			},
		},
		[7] = {nTime = 0, nNum = 1 ,		-- �ܼ�ʱ
			tbPrelock = {6},
			tbStartEvent =
			{
			    {Instance.ADD_NPC, 6, 1, 7, "2", "shuizhu"},
				{Instance.ADD_NPC, 7, 1, 7, "3", "fengyin"},
				{Instance.ADD_NPC, 1, 1, 7, "1", "taizi"},
				{Instance.TARGET_INFO, -1, Lang.mission.str553[Lang.Idx]},
			},
			tbUnLockEvent =
			{
			{Instance.DEL_NPC, "3",},
			{Instance.DEL_NPC, "2",},
			{Instance.DEL_NPC, "1",},
			},
		},
		[8] = {nTime = 7, nNum = 0 ,		-- �ܼ�ʱ
			tbPrelock = {7},
			tbStartEvent =
			{
			{Instance.ADD_NPC, 9, 1, 8, "5", "shuizhu1"},
			},
			tbUnLockEvent =
			{
			{Instance.DEL_NPC, "5",},
			},
		},
		[9] = {nTime = 8, nNum = 0 ,		-- �ܼ�ʱ
			tbPrelock = {7},
			tbStartEvent =
			{
			{Instance.SHOW_NOTICE_STATE, -1, Lang.mission.str237[Lang.Idx]},
			{Instance.DEL_NPC, "1",},
			{Instance.ADD_NPC, 8, 1, 9, "4", "taizi1"},
			{Instance.NPC_BUBBLE, -1, "4", Lang.mission.str554[Lang.Idx], 2},
			{Instance.NPC_BUBBLE, -1, "4", Lang.mission.str555[Lang.Idx], 5},
			{Instance.TARGET_INFO, -1, Lang.mission.str232[Lang.Idx]},
			},
			tbUnLockEvent =
			{
			{Instance.DEL_NPC, "4",},
			 {Instance.REMOVE_NOTICE_STATE, -1, Lang.mission.str237[Lang.Idx]},
			},
		},
		[10] = {nTime = 0, nNum = 1 ,		-- �ܼ�ʱ
			tbPrelock = {9},
			tbStartEvent =
			{
				{Instance.ADD_NPC, 4, 1, 10, "1", "long"},
				{Instance.NPC_BUBBLE, -1, "1", Lang.mission.str556[Lang.Idx], 1},
				{Instance.TARGET_INFO, -1, Lang.mission.str557[Lang.Idx]},
			},
			tbUnLockEvent =
			{
			{Instance.DEL_NPC, "2","2_timer"},
			},
		},
		[11] = {nTime = 8, nNum = 0 ,		-- �ܼ�ʱ
			tbPrelock = {9},
			tbStartEvent =
			{
			},
			tbUnLockEvent =
			{
			},
		},
		[12] = {nTime = 1800, nNum = 0 ,		-- �ܼ�ʱ
			tbPrelock = {11},
			tbStartEvent =
			{
				{Instance.ADD_NPC, 5, 4, 12, "2", "jineng", 120, 12, "1"},
			},
			tbUnLockEvent =
			{
			},
		},
		[13] = {nTime = 4, nNum = 0 ,		-- ���
			tbPrelock = {10},
			tbStartEvent =
			{

			},
			tbUnLockEvent =
			{
			},
		},
		[14] = {nTime = 0, nNum = 1 ,		-- ���
			tbPrelock = {13},
			tbStartEvent =
			{
              {Instance.UNLOCK_GOD, -1, 14, 1},               --������һ������
			},
			tbUnLockEvent =
			{
			},
		},
		[15] = {nTime = 2, nNum = 0 ,		-- �ܼ�ʱ
			tbPrelock = {14},
			tbStartEvent =
			{
			},
			tbUnLockEvent =
			{
				{Instance.DO_SCRIPT, "self.bFinishTask = 1"},
				{Instance.TARGET_INFO, -1, Lang.mission.str236[Lang.Idx]},
				{Instance.SHOW_REWARD_PANEL, -1, 0},
			    {Instance.DO_SCRIPT, "self.tbLock[16]:Close()"},
			},
		},
		[16] = {nTime = 0, nNum = 1,		-- �ܼ�ʱ
			tbPrelock = {1},
			tbStartEvent =
			{
			},
			tbUnLockEvent =
			{
             {Instance.REVIVE_INFO, true, true, false},
			},
		},

    }
}


