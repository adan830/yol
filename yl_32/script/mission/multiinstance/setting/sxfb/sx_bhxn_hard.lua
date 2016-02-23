-- 20�������ѣ����˸��������ļ�

Include("script/mission/multiinstance/multi_def.lua")

if not MultiInstance.tbSetting then
	MultiInstance.tbSetting = {}
end

local tbMultiSetting = MultiInstance.tbSetting;

tbMultiSetting[522]=
{
	nTimeLimit = 605,  --����ʱ��20����
	nMapId = 522,
    tbBeginPos = {7137, 7404, 1048576},
	nGameType = MultiInstance.GAME_TYPE.LV_20_EASY,
	nMultiLevel = 20,
	nDifficulty = 1,

    -- �����漰��NPC����
	NPC =
	{
	-- 		���  	npcģ��				�ȼ�(-1Ĭ�����npcpro��)	5��(Ĭ��-1)
        [1] = {nTemplate = 1250, nLevel = 50, nSeries = -1},		-- �񱩺���
		[2] = {nTemplate = 1251, nLevel = 50, nSeries = -1},		-- ţ������
		[3] = {nTemplate = 1252, nLevel = 50, nSeries = -1},		-- ţħ��
		[4] = {nTemplate = 1253, nLevel = 50, nSeries = -1},		-- �ײ�����
		[5] = {nTemplate = 1254, nLevel = 50, nSeries = -1},		-- ��ͷ��
		[6] = {nTemplate = 1255, nLevel = 50, nSeries = -1},		-- ��Ѫ���
		[7] = {nTemplate = 1256, nLevel = 50, nSeries = -1},		-- ��ӡ����
		[8] = {nTemplate = 1257, nLevel = 50, nSeries = -1},		-- �����
		[9] = {nTemplate = 1258, nLevel = -1, nSeries = -1},		-- ���ɽ��
		[10] = {nTemplate = 1259, nLevel = -1, nSeries = -1},		-- ���͵�1
		[11] = {nTemplate = 1260, nLevel = -1, nSeries = -1},		-- Ⱥ����̨���͵�
		[12] = {nTemplate = 1261, nLevel = -1, nSeries = -1},		-- ������̨���͵�
		[13] = {nTemplate = 1262, nLevel = -1, nSeries = -1},		-- ������̨
		[14] = {nTemplate = 1263, nLevel = -1, nSeries = -1},		-- Ⱥ����̨
		[15] = {nTemplate = 1264, nLevel = -1, nSeries = -1},		-- ������̨
		[16] = {nTemplate = 1265, nLevel = -1, nSeries = -1},		-- ����ħ����1
		[17] = {nTemplate = 1266, nLevel = -1, nSeries = -1},		-- Ⱥ��ħ����1
		[18] = {nTemplate = 1267, nLevel = -1, nSeries = -1},		-- ����ħ����1
		[19] = {nTemplate = 1268, nLevel = -1, nSeries = -1},		-- �ӹ�buff
		[20] = {nTemplate = 1269, nLevel = -1, nSeries = -1},		-- ȫ�����˺�buff
		[21] = {nTemplate = 1270, nLevel = -1, nSeries = -1},		-- ȫ���ֶ���buff
		[22] = {nTemplate = 1271, nLevel = -1, nSeries = -1},		-- ����͵��
		[23] = {nTemplate = 1272, nLevel = -1, nSeries = -1},		-- ����ħ����2
		[24] = {nTemplate = 1273, nLevel = -1, nSeries = -1},		-- Ⱥ��ħ����2
		[25] = {nTemplate = 1274, nLevel = -1, nSeries = -1},		-- ����ħ����2
		[26] = {nTemplate = 1275, nLevel = -1, nSeries = -1},		-- ����ħ����3
		[27] = {nTemplate = 1276, nLevel = -1, nSeries = -1},		-- Ⱥ��ħ����3
		[28] = {nTemplate = 1277, nLevel = -1, nSeries = -1},		-- ����ħ����3
		[29] = {nTemplate = 1278, nLevel = -1, nSeries = -1},		-- ��ɱ
		[30] = {nTemplate = 1279, nLevel = -1, nSeries = -1},		-- ��ɱ
		[31] = {nTemplate = 1280, nLevel = -1, nSeries = -1},		-- ����Ҽ���������
		[32] = {nTemplate = 1281, nLevel = -1, nSeries = -1},		-- ��㴫��
	},

    LOCK =
    {
       -- 1�������ܲ��Ĭ��1��Ϊ��ʼ��
		[1] = {nTime = 5, nNum = 0,		-- �ܼ�ʱ
			tbPrelock = {},
			tbStartEvent =
			{
			    {MultiInstance.ADD_NPC, 31, 1, 1, "yinxingBUFF", "yinxingBUFF"},          --��������һ������BUFF
				{MultiInstance.TIME_INFO, Lang.mission.str886[Lang.Idx],1},
				{MultiInstance.SHOW_NOTICE_MSG, Lang.mission.str887[Lang.Idx]},
			},
			tbUnLockEvent =
			{
			--{MultiInstance.DEL_NPC, "yinxingBUFF"},             --ɾ������Ҽ�����BUFF��NPC
			},
		},
		[2] = {nTime = 900, nNum = 0 ,
			tbPrelock = {1},
			tbStartEvent =
			{
                {MultiInstance.TIME_INFO, Lang.mission.str888[Lang.Idx]},
				{MultiInstance.REVIVE_INFO, true, true, false},

				{MultiInstance.ADD_NPC, 11, 1, 2, "11", "paotaTransmit2"}, --�ص���㣨���ѣ�

			},
			tbUnLockEvent =
			{
			},
		},
		--��1�� 20ֻ�񱩺���
		[3] = {nTime = 0, nNum = 20 ,
			tbPrelock = {1},
			tbStartEvent =
			{
				{MultiInstance.ADD_NPC, 1, 1, 3, "1", "npcbornplace", 20,2,"1_timer",0},  --�񱩺���  --20
				{MultiInstance.SHOW_NOTICE_MSG, Lang.mission.str889[Lang.Idx]},
				{MultiInstance.TARGET_INFO, Lang.mission.str890[Lang.Idx]},

			},
			tbUnLockEvent =
			{
			{MultiInstance.DEL_NPC, "111","11_timer"},                         --ɾ��ͯŮ
			},
		},
		--��2����ʼ��ʱ��
		[4] = {nTime = 170, nNum = 1 ,
			tbPrelock = {1},
			tbStartEvent =
			{
			},
			tbUnLockEvent =
			{
			},
		},
		--��2�� ʱ�䵽�ˣ���ʼˢ24ֻţ��������1ֻţħ��
		[5] = {nTime = 0, nNum = 21 ,
			tbPrelock = {4},
			tbStartEvent =
			{
				{MultiInstance.ADD_NPC, 2, 1, 5, "2", "npcbornplace",20,2,"2_timer",0},  --ţ������   --25
				{MultiInstance.SHOW_NOTICE_MSG, Lang.mission.str891[Lang.Idx]},
				{MultiInstance.TARGET_INFO,Lang.mission.str892[Lang.Idx]},
			},
			tbUnLockEvent =
			{
			{MultiInstance.DEL_NPC, "222","22_timer"},                              --ɾ��ͯŮ
			},
		},
		--��Ӣˢ����ʱ��
		[6] = {nTime = 25, nNum = 0 ,
			tbPrelock = {4},
			tbStartEvent =
			{
			},
			tbUnLockEvent =
			{
			},
		},
		[7] = {nTime = 0, nNum = 100 ,
			tbPrelock = {6},
			tbStartEvent =
			{
				{MultiInstance.ADD_NPC, 3, 1, 5, "3", "jingying"}, 					 --ţħ��
			},
			tbUnLockEvent =
			{
			},
		},
		--��3��ˢ����ʱ�����̳е�5��
		[8] = {nTime = 180, nNum = 1 ,
			tbPrelock = {4},
			tbStartEvent =
			{
			},
			tbUnLockEvent =
			{
			},
		},

		--��3�� ʱ�䵽�ˣ���ʼˢ30ֻ�ײ����˺�2ֻ��ͷ��
		[9] = {nTime = 0, nNum = 20 ,
			tbPrelock = {8},
			tbStartEvent =
			{
				{MultiInstance.ADD_NPC, 4, 1, 9, "4", "npcbornplace",20,2,"4_timer",0},  --�ײ�����   --30
				{MultiInstance.SHOW_NOTICE_MSG, Lang.mission.str893[Lang.Idx]},
				{MultiInstance.TARGET_INFO, Lang.mission.str894[Lang.Idx]},
			},
			tbUnLockEvent =
			{
			{MultiInstance.DEL_NPC, "333","33_timer"},                              --ɾ��ͯŮ
			},
		},
		--��Ӣ��1��ˢ����ʱ��
		[10] = {nTime = 10, nNum = 0 ,
			tbPrelock = {8},
			tbStartEvent =
			{
			},
			tbUnLockEvent =
			{
			},
		},
		[11] = {nTime = 0, nNum = 100 ,
			tbPrelock = {10},
			tbStartEvent =
			{
				--{MultiInstance.ADD_NPC, 5, 1, 9, "5", "npcbornplace",2,25,"5_timer",0}, 					 --ÿ��10sˢһֻ��ͷ��
			},
			tbUnLockEvent =
			{
			},
		},
		--��4��ˢ����ʱ�����̳е�9��
		[12] = {nTime = 180, nNum = 1 ,
			tbPrelock = {8},
			tbStartEvent =
			{
			},
			tbUnLockEvent =
			{
			},
		},
		--��4�� ʱ�䵽�ˣ���ʼˢ32ֻ��Ѫ����3ֻ��ӡ����
		[13] = {nTime = 0, nNum = 22 ,
			tbPrelock = {12},
			tbStartEvent =
			{
				{MultiInstance.ADD_NPC, 6, 1, 13, "6", "npcbornplace",20,3,"6_timer",0},  --��     --32
				{MultiInstance.SHOW_NOTICE_MSG, Lang.mission.str895[Lang.Idx]},
				{MultiInstance.TARGET_INFO, Lang.mission.str896[Lang.Idx]},
			},
			tbUnLockEvent =
			{
			{MultiInstance.DEL_NPC, "444","44_timer"},                                 --ɾ��ͯŮ
			},
		},
		--��Ӣˢ����ʱ��
		[14] = {nTime = 15, nNum = 0 ,
			tbPrelock = {12},
			tbStartEvent =
			{
			},
			tbUnLockEvent =
			{
			},
		},
		[15] = {nTime = 0, nNum = 100 ,
			tbPrelock = {14},
			tbStartEvent =
			{
				{MultiInstance.ADD_NPC, 7, 1,13, "7", "jingying",2,30,"7_timer",0}, 					 --��ӡ����
			},
			tbUnLockEvent =
			{
			},
		},
		--��5��ˢ����ʱ��
		[16] = {nTime = 200, nNum = 1 ,
			tbPrelock = {12},
			tbStartEvent =
			{
			},
			tbUnLockEvent =
			{
			},
		},
		--��5�� ʱ�䵽�ˣ���ʼˢ��boss
		[17] = {nTime = 0, nNum = 1 ,
			tbPrelock = {16},
			tbStartEvent =
			{
				{MultiInstance.ADD_NPC, 8, 1, 17, "8", "npcbornplace"},  --�����
				{MultiInstance.SHOW_NOTICE_MSG, Lang.mission.str897[Lang.Idx]},
				{MultiInstance.TARGET_INFO,Lang.mission.str898[Lang.Idx]},
			},
			tbUnLockEvent =
			{
			{MultiInstance.DO_SCRIPT, "self.bFinish = 1"},
			{MultiInstance.DEL_NPC, "555","55_timer"},                                           --ɾ��ͯŮ
			},
		},

		--��������ʱˢ�� �Ŵ��� ����ɱ�Ŵ����м��ʴ�������buff
		[18] = {nTime = 15, nNum = 0 ,
			tbPrelock = {1},
			tbStartEvent =
			{
			},
			tbUnLockEvent =
			{
			},
		},
		[19] = {nTime = 30, nNum = 10 ,
			tbPrelock = {16},
			tbStartEvent =
			{

			},
			tbUnLockEvent =
			{
			--{MultiInstance.ADD_NPC, 22, 1, 19, "22", "npcbornplace", 3, 30, "22_timer",0}, --��ʱˢ���Ŵ���
			},
		},
		--������ʱ�䵽�ˣ����ɽ��û�� ��ʤ��                1.��ʱ������ͷ��β�����ڣ������¼�������bFinish=1
		[20] = {nTime = 900, nNum = 0 ,
			tbPrelock = {1},
			tbStartEvent =
			{

			},
			tbUnLockEvent =
			{
				{MultiInstance.DO_SCRIPT, "self.bFinish = 1"},
			},
		},
		--���������ɽ���ڸ���ʱ�������� ��ʧ��                2.������������nNum��Ϊ1�������¼�������bFailFinish=1
		[21] = {nTime = 0, nNum = 1 ,
			tbPrelock = {1},
			tbStartEvent =
			{
				{MultiInstance.ADD_NPC, 9, 1, 21, "9", "shenxianjiejie"}, --���ɽ��
			},
			tbUnLockEvent =
			{
				{MultiInstance.DO_SCRIPT, "self.bFailFinish= 1"},
				{MultiInstance.DEL_NPC, "1"},
				{MultiInstance.DEL_NPC, "2"},
				{MultiInstance.DEL_NPC, "3"},
				{MultiInstance.DEL_NPC, "4"},
				{MultiInstance.DEL_NPC, "6"},
				{MultiInstance.DEL_NPC, "7"},
				{MultiInstance.DEL_NPC, "8"},

			},
		},
		--����������ʱ���ڣ�ɱ�����й�  ��ʤ��               3.�������������������ʱ����bFinish=1
		[22] = {nTime = 0, nNum = 100 ,
			tbPrelock = {1},
			tbStartEvent =
			{
			},
			tbUnLockEvent =
			{
				{MultiInstance.DO_SCRIPT, "self.bFinish = 1"},
			},
		},
		[23] = {nTime = 10, nNum = 0 ,          --{��һ����ɱ��}
			tbPrelock = {3},
			tbStartEvent =
			{
			{MultiInstance.ADD_NPC, 29, 1, 4, "zisha", "zisha"},
			},
			tbUnLockEvent =
			{
			},
		},
		[24] = {nTime = 10, nNum = 0 ,          --{�ڶ�����ɱ��}
			tbPrelock = {5},
			tbStartEvent =
			{
			{MultiInstance.ADD_NPC, 29, 1, 8, "zisha1", "zisha"},
			},
			tbUnLockEvent =
			{
			},
		},
		[25] = {nTime = 10, nNum = 0 ,          --{��������ɱ��}
			tbPrelock = {9},
			tbStartEvent =
			{
			{MultiInstance.ADD_NPC, 29, 1, 12, "zisha2", "zisha"},
			},
			tbUnLockEvent =
			{
			},
		},
		[26] = {nTime = 10, nNum = 0 ,          --{���Ĳ���ɱ��}
			tbPrelock = {13},
			tbStartEvent =
			{
			{MultiInstance.ADD_NPC, 29, 1, 16, "zisha3", "zisha"},
			},
			tbUnLockEvent =
			{
			},
		},
		[27] = {nTime = 30, nNum = 0 ,          --{��һ����ͯŮ}
			tbPrelock = {1},
			tbStartEvent =
			{
			},
			tbUnLockEvent =
			{
			{MultiInstance.ADD_NPC, 22, 1, 19, "111", "hou", 3, 35, "11_timer",0},            --ͯŮ
			},
		},
		[28] = {nTime = 30, nNum = 0 ,          --{�ڶ�����ͯŮ}
			tbPrelock = {4},
			tbStartEvent =
			{
			},
			tbUnLockEvent =
			{
			{MultiInstance.ADD_NPC, 22, 1, 19, "222", "hou", 3, 35, "22_timer",0},            --ͯŮ
			},
		},
		[29] = {nTime = 25, nNum = 0 ,          --{��������ͯŮ}
			tbPrelock = {8},
			tbStartEvent =
			{
			},
			tbUnLockEvent =
			{
			{MultiInstance.ADD_NPC, 22, 1, 19, "333", "hou", 3, 35, "33_timer",0},            --ͯŮ
			},
		},
		[30] = {nTime = 40, nNum = 0 ,          --{���Ĳ���ͯŮ}
			tbPrelock = {12},
			tbStartEvent =
			{
			},
			tbUnLockEvent =
			{
			{MultiInstance.ADD_NPC, 22, 1, 19, "444", "hou", 3, 35, "44_timer",0},           --ͯŮ
			},
		},
		[31] = {nTime = 40, nNum = 0 ,          --{���岨��ͯŮ}
			tbPrelock = {16},
			tbStartEvent =
			{
			},
			tbUnLockEvent =
			{
			{MultiInstance.ADD_NPC, 22, 1, 19, "555", "hou", 2, 40, "55_timer",0},           --ͯŮ
			},
		},
		[32] = {nTime = 0, nNum = 1 ,          --{���岨��ͯŮ}
			tbPrelock = {1},
			tbStartEvent =
			{
			{MultiInstance.ADD_NPC, 30, 3, 32, "beisha", "beisha"},
			},
			tbUnLockEvent =
			{
			{MultiInstance.DEL_NPC, "beisha"},
			{MultiInstance.SHOW_NOTICE_MSG, Lang.mission.str899[Lang.Idx]},
			},
		},
		[33] = {nTime = 0, nNum = 1 ,          --{���岨��ͯŮ}
			tbPrelock = {32},
			tbStartEvent =
			{
			{MultiInstance.ADD_NPC, 30, 3, 33, "beisha1", "beisha"},
			},
			tbUnLockEvent =
			{
			{MultiInstance.DEL_NPC, "beisha1"},
			{MultiInstance.SHOW_NOTICE_MSG, Lang.mission.str900[Lang.Idx]},
			},
		},
		[34] = {nTime = 0, nNum = 1 ,          --{���岨��ͯŮ}
			tbPrelock = {33},
			tbStartEvent =
			{
			{MultiInstance.ADD_NPC, 30, 3, 34, "beisha2", "beisha"},
			},
			tbUnLockEvent =
			{
			{MultiInstance.DEL_NPC, "beisha2"},
			{MultiInstance.SHOW_NOTICE_MSG, Lang.mission.str901[Lang.Idx]},
			},
		},
    }
}
