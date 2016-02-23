-- �ؿ���ͨ�Ѷ������ļ�

Include("script/mission/stage/stage_def.lua")

if not Stage.tbSetting then
	Stage.tbSetting = {}
end

local tbStageSetting = Stage.tbSetting;

--���ֶ���
tbStageSetting[1] =
{
	nTimeLimit = 905,  --����ʱ��15����
	nMapId = 500,
	nLayer = 1,
    tbBeginPos = {5100,888, 1048576},

    -- �����漰��NPC����
	NPC =
	{
	-- 		���  	npcģ��				�ȼ�(-1Ĭ�����npcpro��)	5��(Ĭ��-1)
	       [1] = {nTemplate = 1000, nLevel = -1, nSeries = -1},		-- ��ʶ
		   [2] = {nTemplate = 1001, nLevel = 25, nSeries = -1},		-- ʯͷ��1
		   [3] = {nTemplate = 1002, nLevel = 25, nSeries = -1},		-- ʯͷ��2
		   [4] = {nTemplate = 1003, nLevel = 25, nSeries = -1},		-- ʯͷ��1
		   [5] = {nTemplate = 1004, nLevel = 25, nSeries = -1},		-- ʯͷ��2
		   [6] = {nTemplate = 1005, nLevel = 25, nSeries = -1},		-- ʯͷ��1
		   [7] = {nTemplate = 1006, nLevel = 25, nSeries = -1},		-- ʯͷ��2
		   [8] = {nTemplate = 1007, nLevel = 25, nSeries = -1},		-- ��ɱ
		   [9] = {nTemplate = 1008, nLevel = 25, nSeries = -1},		-- ��ʱը��
		   [10] = {nTemplate = 1009, nLevel = 25, nSeries = -1},		-- ʯ��
		   [11] = {nTemplate = 1010, nLevel = -1, nSeries = -1},		-- ǽ
		   [12] = {nTemplate = 1011, nLevel = 25, nSeries = -1},		-- ��
		   [13] = {nTemplate = 1012, nLevel = 25, nSeries = -1},		-- ��
		   [14] = {nTemplate = 1013, nLevel = -1, nSeries = -1},		-- ����
		   [15] = {nTemplate = 1014, nLevel = 25, nSeries = -1},		-- ������ʯ��ɽ�£�
		   [16] = {nTemplate = 1015, nLevel = 25, nSeries = -1},		-- ������ʯ��ɽ�£�
		   [17] = {nTemplate = 1016, nLevel = 25, nSeries = -1},		-- �涫��
		   [18] = {nTemplate = 1019, nLevel = -1, nSeries = -1},		-- ������
		   [19] = {nTemplate = 1020, nLevel = -1, nSeries = -1},		-- ˮ��
		   [20] = {nTemplate = 1021, nLevel = -1, nSeries = -1},		-- ��ʯ�֣����飩
		   [21] = {nTemplate = 1022, nLevel = 25, nSeries = -1},		-- ��ʯ�֣�������
		   [22] = {nTemplate = 1023, nLevel = 25, nSeries = -1},		-- ʯͷ֧ԮBOSS
		   [23] = {nTemplate = 1024, nLevel = 25, nSeries = -1},		-- ʯͷ֧ԮBOSS
		   [24] = {nTemplate = 1025, nLevel = 25, nSeries = -1},		-- ʯͷ֧ԮBOSS
		   [25] = {nTemplate = 1026, nLevel = -1, nSeries = -1},		-- ͸����ɱ
		   [26] = {nTemplate = 1027, nLevel = 25, nSeries = -1},		-- ʯ��
		   [27] = {nTemplate = 1028, nLevel = 25, nSeries = -1},		-- ը����
		   [28] = {nTemplate = 1029, nLevel = 1, nSeries = -1},		-- ͸��Ŀ��
		   [29] = {nTemplate = 1017, nLevel = 25, nSeries = -1},		-- ʯͷ������
		   [30] = {nTemplate = 1018, nLevel = 25, nSeries = -1},		-- ʯͷ������
	},

    LOCK =
    {
       -- 1�������ܲ��Ĭ��1��Ϊ��ʼ��
		[1] = {nTime = 5, nNum = 0,		-- �ܼ�ʱ
			tbPrelock = {},
			tbStartEvent =
			{
			    {Stage.TIME_INFO, Lang.mission.str1083[Lang.Idx],1},
				{Stage.ADD_NPC, 11, 1, 1, "qiang2", "qiang2"},
				{Stage.SET_TRAP_INVALID, 13, 0},
				{Stage.SET_TRAP_INVALID, 14, 0},
				{Stage.SET_TRAP_INVALID, 15, 0},
			},
			tbUnLockEvent =
			{
			},
		},
		[2] = {nTime = 900, nNum = 0 ,		-- ��С����ʱ��
			tbPrelock = {1},
			tbStartEvent =
			{
			    {Stage.TIME_INFO, Lang.mission.str1084[Lang.Idx],2},
				{Stage.SET_TRAP_INVALID, 13, 1},
				{Stage.SET_TRAP_INVALID, 14, 1},
				{Stage.SET_TRAP_INVALID, 15, 1},
				{Stage.DEL_NPC, "qiang2","qiang2"},
			},
			tbUnLockEvent =
			{
			},
		},
		[3] = {nTime = 0, nNum = 1 ,		-- ����ͨ��
			tbPrelock = {1},
			tbStartEvent =
			{
			    {Stage.ADD_NPC, 11, 1, 3, "qiang", "qiang"},
				{Stage.ADD_NPC, 11, 1, 3, "qiang1", "qiang1"},
				{Stage.ADD_NPC, 1, 3, 3, "biaoshi", "biaoshi"},
				{Stage.ADD_NPC, 8, 5, 3, "zisha2", "zisha2"},
				{Stage.ADD_NPC, 28, 1, 3, "mubiao", "mubiao"},
				--{Stage.TARGET_INFO, "<color=green>һ�˽���һ��ͨ��"},
				--{Stage.BLACK_MSG, "һ�˽���һ��ͨ��"},
				{Stage.TARGET_INFO, Lang.mission.str1085[Lang.Idx]},
				{Stage.BLACK_MSG, Lang.mission.str1086[Lang.Idx]},
			},
			tbUnLockEvent =
			{
				{Stage.DEL_NPC,"biaoshi"},
				{Stage.DEL_NPC,"mubiao"},
				{Stage.ADD_NPC, 3, 1, 5, "shitou_m22", "shitou_m22"},
			    {Stage.ADD_NPC, 5, 1, 5, "shitou_l22", "shitou_l22"},
			    {Stage.ADD_NPC, 7, 1, 4, "shitou_r22", "shitou_r22"},
				{Stage.ADD_NPC, 2, 1, 4, "shitou_m1", "shitou_m1", 100, 16, "shitou_timer1",0},                  --ʯͷ
				{Stage.ADD_NPC, 4, 1, 4, "shitou_l1", "shitou_l1", 100, 16, "shitou_timer3",0},
				{Stage.ADD_NPC, 6, 1, 4, "shitou_r1", "shitou_r1", 100, 16, "shitou_timer5",0},
				{Stage.ADD_NPC, 29, 1, 4, "shitou_l11", "shitou_l11", 100, 10, "shitou_l11",0},
			},
		},
		[4] = {nTime = 0, nNum = 11 ,		-- ��һС�ڣ��ɼ�"��"
			tbPrelock = {3},
			tbStartEvent =
			{

			    {Stage.ADD_NPC, 13, 11, 4, "zhen", "zhen"},
				--{Stage.TARGET_INFO, Lang.mission.str1085[Lang.Idx]},
				--{Stage.BLACK_MSG, Lang.mission.str1086[Lang.Idx]},
			},
			tbUnLockEvent =
			{
			{Stage.DEL_NPC,"shitou_m1", "shitou_timer1"},
			{Stage.DEL_NPC,"shitou_m2", "shitou_timer2"},
			{Stage.DEL_NPC,"shitou_l1", "shitou_timer3"},
			{Stage.DEL_NPC,"shitou_l2", "shitou_timer4"},
			{Stage.DEL_NPC,"shitou_r1", "shitou_timer5"},
			{Stage.DEL_NPC,"shitou_r2", "shitou_timer6"},
			{Stage.DEL_NPC,"shitou_m", "shitou_timer7"},
			{Stage.DEL_NPC,"shitou_l", "shitou_timer8"},
			{Stage.DEL_NPC,"shitou_r", "shitou_timer9"},
			{Stage.DEL_NPC,"shitou_r11", "shitou_r11"},
			{Stage.DEL_NPC,"shitou_l11", "shitou_l11"},
			{Stage.DEL_NPC,"shitou_r111", "shitou_r111"},
			{Stage.DEL_NPC,"zhen1"},
			{Stage.DEL_NPC,"ding1"},
			{Stage.DEL_NPC,"ding2"},
			{Stage.DEL_NPC,"ding3"},
			{Stage.DEL_NPC,"ding4"},
			{Stage.DEL_NPC,"ding5"},

			},
		},
		[5] = {nTime = 5, nNum = 0 ,		-- ʯͷ��Ϊ����ʯͷ��ͬʱ����£�
			tbPrelock = {3},
			tbStartEvent =
			{

			},
			tbUnLockEvent =
			{
			  {Stage.ADD_NPC, 3, 1, 5, "shitou_m2", "shitou_m2", 100, 16, "shitou_timer2",0},
			  {Stage.ADD_NPC, 5, 1, 5, "shitou_l2", "shitou_l2", 100, 16, "shitou_timer4",0},
			  {Stage.ADD_NPC, 7, 1, 4, "shitou_r2", "shitou_r2", 100, 16, "shitou_timer6",0},
			 -- {Stage.ADD_NPC, 30, 1, 4, "shitou_r11", "shitou_r11", 100, 10, "shitou_r11",0},
			},
		},
		[6] = {nTime = 0, nNum = 1 ,		-- "��"��������
			tbPrelock = {3},
			tbStartEvent =
			{
				{Stage.ADD_NPC,12, 1, 6, "zhen1", "zhen1"},
			},
			tbUnLockEvent =
			{
			{Stage.BLACK_MSG, Lang.mission.str1087[Lang.Idx]},
			{Stage.ADD_NPC, 14, 1, 6, "ding1", "ding1"},
			},
		},
		[7] = {nTime = 0, nNum = 1 ,		-- "��"��������
			tbPrelock = {3},
			tbStartEvent =
			{
				{Stage.ADD_NPC,12, 1, 7, "zhen1", "zhen1"},
			},
			tbUnLockEvent =
			{
			{Stage.BLACK_MSG, Lang.mission.str1087[Lang.Idx]},
			{Stage.ADD_NPC, 14, 1, 7, "ding2", "ding2"},
			},
		},
		[8] = {nTime = 0, nNum = 1 ,		-- "��"��������
			tbPrelock = {3},
			tbStartEvent =
			{
				{Stage.ADD_NPC,12, 1, 8, "zhen1", "zhen1"},
			},
			tbUnLockEvent =
			{
			{Stage.BLACK_MSG, Lang.mission.str1087[Lang.Idx]},
			{Stage.ADD_NPC, 14, 1, 8, "ding3", "ding3"},
			},
		},
		[9] = {nTime = 0, nNum = 1 ,		-- "��"��������
			tbPrelock = {3},
			tbStartEvent =
			{
				{Stage.ADD_NPC,12, 1, 9, "zhen1", "zhen1"},
			},
			tbUnLockEvent =
			{
			{Stage.BLACK_MSG, Lang.mission.str1087[Lang.Idx]},
			{Stage.ADD_NPC, 14, 1, 9, "ding4", "ding4"},
			},
		},
		[10] = {nTime = 0, nNum = 1 ,		-- "��"��������
			tbPrelock = {3},
			tbStartEvent =
			{
				{Stage.ADD_NPC,12, 1, 10, "zhen1", "zhen1"},
			},
			tbUnLockEvent =
			{
			{Stage.BLACK_MSG, Lang.mission.str1087[Lang.Idx]},
			{Stage.ADD_NPC, 14, 1, 10, "ding5", "ding5"},
			},
		},
		[11] = {nTime = 0, nNum = 18 ,		-- �ڶ�С�ڡ�������š�
			tbPrelock = {13},
			tbStartEvent =
			{
				{Stage.ADD_NPC, 10, 18, 11, "gui", "gui"},
				{Stage.ADD_NPC, 27, 4, 11, "gui2", "gui2"},
				--{Stage.ADD_NPC, 27, 5, 11, "gui2", "gui2", 100, 10,"gui2_timer"},
				{Stage.TARGET_INFO, Lang.mission.str1088[Lang.Idx]},
				{Stage.BLACK_MSG, Lang.mission.str1089[Lang.Idx]},
			},
			tbUnLockEvent =
			{

			 {Stage.DEL_NPC, "gui2"},
			{Stage.ADD_NPC, 1, 1, 12, "biaoshi1", "biaoshi1"},
			--{Stage.DEL_NPC, "gui2","gui2_timer"},
			--{Stage.DEL_NPC, "gui22","gui22_timer"},
			{Stage.DEL_NPC, "gui22"},
			{Stage.DEL_NPC, "zhadan",},
			{Stage.DEL_NPC,"qiang1"},
			{Stage.SET_TRAP_INVALID, 12, 1},
			},
		},
		[12] = {nTime = 0, nNum = 18 ,		-- �ڶ�С�ڡ����Ī��
			tbPrelock = {11},
			tbStartEvent =
			{
				--{Stage.ADD_NPC, 10, 18, 12, "gui", "gui"},
				--{Stage.ADD_NPC, 27, 4, 12, "gui22", "gui2"},
				--{Stage.ADD_NPC, 27, 4, 12, "gui22", "gui2", 100, 10,"gui22_timer"},
				--{Stage.TARGET_INFO, "<color=green>�ڶ��ڵ㣺<color=yellow>�������\\r\\r<color=green>������������ɸ��˺���ǧ��𹥻��򿿽���\\r\\r<color=white>Ŀ��:����ڶ���ʯ��"},
				--{Stage.BLACK_MSG, "�Ͻ�����ڶ���ʯ��"},
			},
			tbUnLockEvent =
			{
				--{Stage.ADD_NPC, 1, 1, 12, "biaoshi1", "biaoshi1"},
			      --{Stage.DEL_NPC, "gui22","gui22_timer"},
				--  {Stage.DEL_NPC, "gui22"},
                --  {Stage.DEL_NPC, "zhadan",},
				--  {Stage.DEL_NPC,"qiang1"},
				  --{Stage.BLACK_MSG, "ɽ����������ʲô����С��"},
				--  {Stage.SET_TRAP_INVALID, 12, 1},
			},
		},
		[13] = {nTime = 0, nNum = 1 ,		-- ��������
			tbPrelock = {4},
			tbStartEvent =
			{
			{Stage.ADD_NPC, 13, 1, 13, "kaimen", "kaimen"},
			  {Stage.TARGET_INFO, Lang.mission.str1090[Lang.Idx]},
			},
			tbUnLockEvent =
			{
				{Stage.DEL_NPC,"qiang"},
				{Stage.SET_TRAP_INVALID, 11, 1},               -- trapʧЧ
			},
		},
		[14] = {nTime = 0, nNum = 1 ,		-- ������
			tbPrelock = {13},
			tbStartEvent =
			{
			},
			tbUnLockEvent =
			{

			},
		},
		[15] = {nTime = 0, nNum = 1 ,		-- ����С�ڣ�б��ʯͷ��ʼ��
			tbPrelock = {17},
			tbStartEvent =
			{
				--{Stage.ADD_NPC, 16, 1, 15, "zhadan2", "zhadan2", 100, 10,"zhadan_timer"},
				--{Stage.ADD_NPC, 16, 1, 15, "zhadan3", "zhadan3", 100, 10,"zhadan_timer1"},
				--{Stage.ADD_NPC, 15, 1, 15, "zhadan2", "zhadan2", 100, 30,"zhadan_timer",0},                    --��ʯ
				--{Stage.ADD_NPC, 16, 1, 15, "zhadan3", "zhadan3", 100, 30,"zhadan_timer1",0},                   --��ʯ
				{Stage.ADD_NPC, 15, 1, 15, "zhadan2", "zhadan2"},                    --��ʯ
				{Stage.ADD_NPC, 16, 1, 15, "zhadan3", "zhadan3"},                   --��ʯ
			},
			tbUnLockEvent =
			{
			},
		},
		[16] = {nTime = 1, nNum = 0 ,		-- ������
			tbPrelock = {11},
			tbStartEvent =
			{
			--{Stage.ADD_NPC, 17, 1, 16, "dongxi1", "dongxi1"},
			--{Stage.TARGET_INFO, "����������"},
			},
			tbUnLockEvent =
			{
			--{Stage.ADD_NPC, 18, 1, 16, "baohu", "baohu"},
			},
		},
		[17] = {nTime = 0, nNum = 1 ,		-- ��������ʼ��ʯͷ
			tbPrelock = {16},
			tbStartEvent =
			{
			{Stage.ADD_NPC, 17, 1, 17, "dongxi", "dongxi"},
			{Stage.TARGET_INFO, Lang.mission.str1091[Lang.Idx]},
			},
			tbUnLockEvent =
			{
			--{Stage.ADD_NPC, 18, 1, 17, "baohu1", "baohu1"},
			{Stage.DEL_NPC,"biaoshi1"},
			{Stage.BLACK_MSG, Lang.mission.str1092[Lang.Idx]},
			},
		},
		[18] = {nTime = 0, nNum = 12 ,		-- ���Ľڣ���ʯ���������ֺܶ��
			tbPrelock = {17},
			tbStartEvent =
			{
			{Stage.ADD_NPC, 10, 12, 18, "gui3", "gui3"},
			--{Stage.ADD_NPC, 17, 1, 18, "dongxi1", "dongxi1"},
			{Stage.TARGET_INFO, Lang.mission.str1091[Lang.Idx]},
			},
			tbUnLockEvent =
			{
			{Stage.DEL_NPC,"zhadan2"},
			{Stage.DEL_NPC,"zhadan3"},
			--{Stage.ADD_NPC, 18, 1, 18, "baohu2", "baohu2"},
			},
		},
		[19] = {nTime = 0, nNum = 1 ,		-- ������
			tbPrelock = {1},
			tbStartEvent =
			{
			--{Stage.ADD_NPC, 17, 1, 19, "dongxi2", "dongxi2"},
			--{Stage.TARGET_INFO, Lang.mission.str1093[Lang.Idx]},
			},
			tbUnLockEvent =
			{

			--{Stage.ADD_NPC, 18, 1, 19, "baohu3", "baohu3"},
			},
		},
		[20] = {nTime = 0, nNum = 1 ,		-- ������
			tbPrelock = {19},
			tbStartEvent =
			{
			--{Stage.ADD_NPC, 16, 1, 15, "zhadan22", "zhadan2"},
			--{Stage.ADD_NPC, 16, 1, 15, "zhadan33", "zhadan3"},
			--{Stage.ADD_NPC, 17, 1, 20, "dongxi3", "dongxi3"},
			{Stage.TARGET_INFO, Lang.mission.str1093[Lang.Idx]},
			},
			tbUnLockEvent =
			{
			--{Stage.DEL_NPC,"zhadan2", "zhadan_timer"},
			--{Stage.DEL_NPC,"zhadan3", "zhadan_timer1"},
			--{Stage.DEL_NPC,"zhadan2"},
			--{Stage.DEL_NPC,"zhadan3"},
			--{Stage.ADD_NPC, 18, 1, 20, "baohu4", "baohu4"},
			},
		},
		[21] = {nTime = 2, nNum = 0 ,		-- ������
			tbPrelock = {20},
			tbStartEvent =
			{
			},
			tbUnLockEvent =
			{
			{Stage.DEL_NPC,"baohu1"},
			{Stage.DEL_NPC,"baohu2"},
			{Stage.DEL_NPC,"baohu3"},
			{Stage.DEL_NPC,"baohu4"},
			},
		},
		[22] = {nTime = 0, nNum = 1 ,		-- ��ͨ����������ʱ�䵹��ʱ��ɱ�ָ�����
			tbPrelock = {18},
			tbStartEvent =
			{
			{Stage.ADD_NPC, 19, 1, 22, "shuijing", "shuijing"},
			{Stage.ADD_NPC, 8, 3, 22, "zisha1", "zisha1"},
			{Stage.BLACK_MSG, Lang.mission.str1094[Lang.Idx]},
			},
			tbUnLockEvent =
			{
			},
		},
		[23] = {nTime = 5, nNum = 0 ,		-- ��ͨ����������ʱ�䵹��ʱ��ɱ�ָ�����
			tbPrelock = {22},
			tbStartEvent =
			{
			{Stage.ADD_NPC, 20, 1, 23, "jushiguai", "jushiguai"},
			{Stage.NPC_BUBBLE, "jushiguai",Lang.mission.str1095[Lang.Idx], 2},
			{Stage.TARGET_INFO, Lang.mission.str1096[Lang.Idx]},
			{Stage.BLACK_MSG, Lang.mission.str1094[Lang.Idx]},
			},
			tbUnLockEvent =
			{
			{Stage.DEL_NPC,"jushiguai"},
			},
		},
		[24] = {nTime = 5, nNum = 0 ,		-- ��ͨ����������ʱ�䵹��ʱ��ɱ�ָ�����
			tbPrelock = {22},
			tbStartEvent =
			{

			},
			tbUnLockEvent =
			{
			{Stage.ADD_NPC, 26, 8, 24, "gui1", "gui1"},
			},
		},
		[25] = {nTime = 0, nNum = 1 ,		-- ���Ľ�BOSS����ʯ��
			tbPrelock = {23},
			tbStartEvent =
			{
                {Stage.ADD_NPC, 21, 1, 25, "jushiguai1", "jushiguai"},                     --BOSS����
				{Stage.TARGET_INFO, Lang.mission.str1097[Lang.Idx]},
				{Stage.BLACK_MSG, Lang.mission.str1098[Lang.Idx]},

			},
			tbUnLockEvent =
			{
			{Stage.DEL_NPC,"gui1"},
			{Stage.DEL_NPC,"gui2","gui_timer"},
			{Stage.DEL_NPC,"shitou","shitou_timer"},
			},
		},
		[26] = {nTime = 0, nNum = 1 ,		-- ��ͨ����������ʱ�䵹��ʱ��ɱ�ָ�����
			tbPrelock = {23},
			tbStartEvent =
			{
                {Stage.ADD_NPC, 25, 3, 26, "beisha", "beisha"},
			},
			tbUnLockEvent =
			{
			{Stage.DEL_NPC,"beisha"},
			{Stage.BLACK_MSG, Lang.mission.str1099[Lang.Idx]},
			},
		},
		[27] = {nTime = 10, nNum = 0 ,		-- ��ͨ����������ʱ�䵹��ʱ��ɱ�ָ�����
			tbPrelock = {26},
			tbStartEvent =
			{
                {Stage.ADD_NPC, 26, 3, 27, "gui2", "gui1", 100, 15, "gui_timer"},
			},
			tbUnLockEvent =
			{
			},
		},
		[28] = {nTime = 0, nNum = 1 ,		-- ��ͨ����������ʱ�䵹��ʱ��ɱ�ָ�����
			tbPrelock = {26},
			tbStartEvent =
			{
                {Stage.ADD_NPC, 25, 3, 28, "beisha1", "beisha"},
			},
			tbUnLockEvent =
			{
			{Stage.DEL_NPC,"beisha1"},
			{Stage.BLACK_MSG, Lang.mission.str1099[Lang.Idx]},
			},
		},
		[29] = {nTime = 10, nNum = 0 ,		-- ��ͨ����������ʱ�䵹��ʱ��ɱ�ָ�����
			tbPrelock = {28},
			tbStartEvent =
			{
			},
			tbUnLockEvent =
			{
			},
		},
		[30] = {nTime = 0, nNum = 1 ,		-- ��ͨ����������ʱ�䵹��ʱ��ɱ�ָ�����
			tbPrelock = {28},
			tbStartEvent =
			{
				{Stage.DEL_NPC,"gui2","gui_timer"},
                {Stage.ADD_NPC, 25, 3, 30, "beisha2", "beisha"},
			},
			tbUnLockEvent =
			{
			{Stage.DEL_NPC,"beisha2"},
			{Stage.BLACK_MSG, Lang.mission.str1100[Lang.Idx]},
			},
		},
		[31] = {nTime = 10, nNum = 0 ,		-- ��ͨ����������ʱ�䵹��ʱ��ɱ�ָ�����
			tbPrelock = {30},
			tbStartEvent =
			{
                {Stage.ADD_NPC, 22, 2, 31, "shitou", "shitou", 100, 10, "shitou_timer"},
			},
			tbUnLockEvent =
			{
			},
		},
		[32] = {nTime = 0, nNum = 1 ,		-- ��ͨ����������ʱ�䵹��ʱ��ɱ�ָ�����
			tbPrelock = {30},
			tbStartEvent =
			{
                {Stage.ADD_NPC, 25, 3, 32, "beisha3", "beisha"},
			},
			tbUnLockEvent =
			{
		        {Stage.DEL_NPC,"beisha3"},
		        {Stage.DEL_NPC,"shitou","shitou_timer"},
				{Stage.BLACK_MSG, Lang.mission.str1101[Lang.Idx]},
			},
		},
		[33] = {nTime = 5, nNum = 0 ,		-- ���ӵ�ǰ�沽�裨��ʯͷ��
			tbPrelock = {5},
			tbStartEvent =
			{

			},
			tbUnLockEvent =
			{
			  {Stage.ADD_NPC, 3, 1, 5, "shitou_m", "shitou_m", 100, 16, "shitou_timer7",0},
			  {Stage.ADD_NPC, 5, 1, 5, "shitou_l", "shitou_l", 100, 16, "shitou_timer8",0},
			  {Stage.ADD_NPC, 7, 1, 4, "shitou_r", "shitou_r", 100, 16, "shitou_timer9",0},
			  {Stage.ADD_NPC, 30, 1, 4, "shitou_r111", "shitou_r11", 100, 10, "shitou_r111",0},
			},
		},
		[34] = {nTime = 0, nNum = 1 ,		-- ������
			tbPrelock = {4},
			tbStartEvent =
			{
              --{Stage.ADD_NPC, 13, 1, 34, "kaimen", "kaimen"},
			 -- {Stage.TARGET_INFO, Lang.mission.str1090[Lang.Idx]},
			},
			tbUnLockEvent =
			{
			--	{Stage.DEL_NPC,"qiang"},
			--	{Stage.SET_TRAP_INVALID, 11, 1},               -- trapʧЧ
			},
		},
		[35] = {nTime = 1, nNum = 0 ,		-- ��ͨ����������ʱ�䵹��ʱ��ɱ�ָ�����
			tbPrelock = {25},
			tbStartEvent =
			{
			{Stage.SET_TRAP_INVALID, 11, 0},      -- trap���ڹؿ�����ǰһ��Ҫ�ָ���Ч
			{Stage.SET_TRAP_INVALID, 12, 0},
			{Stage.SET_TRAP_INVALID, 13, 0},
			{Stage.SET_TRAP_INVALID, 14, 0},
			{Stage.SET_TRAP_INVALID, 15, 0},

			},
			tbUnLockEvent =
			{
				{Stage.DO_SCRIPT, "self.bCanTakeAward = 1"},
			},
		},
		[36] = {nTime = 5, nNum = 0 ,		-- ͨ�������ܼ�ʱ
			tbPrelock = {35},
			tbStartEvent =
			{
				{Stage.TARGET_INFO, Lang.mission.str1067[Lang.Idx]},
				{Stage.TIME_INFO, Lang.mission.str1068[Lang.Idx], 4},
			},
			tbUnLockEvent =
			{
				{Stage.DO_SCRIPT, "self.bFinishLayer = 1"},
			},
		}
    }
}

--��������
tbStageSetting[2]=
{
	nTimeLimit = 905,  --����ʱ��5����
	nMapId = 501,
	nLayer = 2,
    tbBeginPos = {2889, 1096, 1048576},

    -- �����漰��NPC����
	NPC =
	{
	-- 		���  	npcģ��				�ȼ�(-1Ĭ��)	5��(Ĭ��-1)
	       [1] = {nTemplate = 1050, nLevel = -1, nSeries = -1},		-- ˮ��1~2
		   [2] = {nTemplate = 1051, nLevel = -1, nSeries = -1},		-- ˮ��2~3
		   [3] = {nTemplate = 1052, nLevel = -1, nSeries = -1},		-- ˮ��3~4
		   [4] = {nTemplate = 1053, nLevel = -1, nSeries = -1},		-- ˮ��boss
		   [5] = {nTemplate = 1054, nLevel = 1, nSeries = -1},		-- ����ľ��
		   [6] = {nTemplate = 1055, nLevel = 1, nSeries = -1},		-- �ٶ�ľ��
		   [7] = {nTemplate = 1056, nLevel = 1, nSeries = -1},		-- �ָ�ľ��
		   [8] = {nTemplate = 1057, nLevel = -1, nSeries = -1},		-- ����buff
		   [9] = {nTemplate = 1058, nLevel = -1, nSeries = -1},		-- �ٶ�uff
		   [10] = {nTemplate = 1059, nLevel = -1, nSeries = -1},		-- �ָ�buff
		   [11] = {nTemplate = 1060, nLevel = 25, nSeries = -1},		-- ħ��
		   [12] = {nTemplate = 1061, nLevel = 25, nSeries = -1},		-- ħ��������
		   [13] = {nTemplate = 1062, nLevel = 25, nSeries = -1},		-- ħ��
		   [14] = {nTemplate = 1063, nLevel = 25, nSeries = -1},		-- ħ��
		   [15] = {nTemplate = 1064, nLevel = 25, nSeries = -1},		-- Թ��
		   [16] = {nTemplate = 1065, nLevel = -1, nSeries = -1},		-- ʥ��
		   [17] = {nTemplate = 1066, nLevel = 25, nSeries = -1},		-- ����
		    [18] = {nTemplate = 1067, nLevel = -1, nSeries = -1},		-- һ��������ɱ
		   [19] = {nTemplate = 1068, nLevel = 25, nSeries = -1},		-- ��
		   [20] = {nTemplate = 1069, nLevel = 1, nSeries = -1},		-- �˲���ɱ
		   [21] = {nTemplate = 1070, nLevel = 25, nSeries = -1},		-- ���
		   [22] = {nTemplate = 1071, nLevel = 25, nSeries = -1},		-- ���
		   [23] = {nTemplate = 1072, nLevel = 25, nSeries = -1},		-- ���
		   [24] = {nTemplate = 1073, nLevel = 25, nSeries = -1},		-- ���
		    [25] = {nTemplate = 1074, nLevel = 25, nSeries = -1},		-- ���͹��
			[26] = {nTemplate = 1075, nLevel = 25, nSeries = -1},		-- �ٻ����
		   [27] = {nTemplate = 1076, nLevel = 25, nSeries = -1},		-- �ٻ����
		   [28] = {nTemplate = 1077, nLevel = 25, nSeries = -1},		-- �ٻ����
		   [29] = {nTemplate = 1078, nLevel = 25, nSeries = -1},		-- �ٻ����
		   [30] = {nTemplate = 1079, nLevel = -1, nSeries = -1},		-- ͸����ɱ
		    [31] = {nTemplate = 1080, nLevel = -1, nSeries = -1},		-- ��������Ѫ
			[32] = {nTemplate = 1081, nLevel = -1, nSeries = -1},		-- ����׷�˴�
			[33] = {nTemplate = 1082, nLevel = -1, nSeries = -1},		-- ��ͷ
			[34] = {nTemplate = 1083, nLevel = 25, nSeries = -1},		-- �׹�
	},
    LOCK =
    {
       -- 1�������ܲ��Ĭ��1��Ϊ��ʼ��
		[1] = {nTime = 5, nNum = 0,		-- �ܼ�ʱ
			tbPrelock = {},
			tbStartEvent =
			{
			    {Stage.TIME_INFO, Lang.mission.str1102[Lang.Idx],1},
			},
			tbUnLockEvent =
			{
			},
		},
		[2] = {nTime = 900, nNum = 0 ,		-- ʱ�䵹��ʱ��ʱ�䵽�ˣ�ϵͳ���Զ����˳�����
			tbPrelock = {1},
			tbStartEvent =
			{
			    {Stage.TIME_INFO, Lang.mission.str1103[Lang.Idx],2},
				{Stage.BLACK_MSG, Lang.mission.str1104[Lang.Idx]},
			},
			tbUnLockEvent =
			{
			},
		},
	    [3] = {nTime = 0, nNum = 1 ,		-- ��������
			tbPrelock = {1},
			tbStartEvent =
			{
                {Stage.ADD_NPC, 5, 1, 3, "huoyan", "huoyan"},
			},
			tbUnLockEvent =
			{
			    {Stage.ADD_NPC, 8, 1, 3, "huoyan1", "huoyan1"},
				{Stage.ADD_NPC, 1, 1, 3, "shuijing1", "shuijing1"},
			},
		},
		[4] = {nTime = 0, nNum = 1 ,		-- �ٶ�����
			tbPrelock = {1},
			tbStartEvent =
			{
                {Stage.ADD_NPC, 6, 1, 4, "sudu", "sudu"},
			},
			tbUnLockEvent =
			{
			    {Stage.ADD_NPC, 9, 1, 4, "sudu1", "sudu1"},
				{Stage.ADD_NPC, 1, 1, 4, "shuijing11", "shuijing1"},
			},
		},
		[5] = {nTime = 0, nNum = 1 ,		-- �ָ�����
			tbPrelock = {1},
			tbStartEvent =
			{
               {Stage.ADD_NPC, 7, 1, 5, "huixue", "huixue"},
			},
			tbUnLockEvent =
			{
			    {Stage.ADD_NPC, 10, 1, 5, "huixue1", "huixue1"},
				{Stage.ADD_NPC, 1, 1, 5, "shuijing111", "shuijing1"},
			},
		},
		[6] = {nTime = 0, nNum = 1 ,		-- ���ڿ���ˮ��
			tbPrelock = {3},
			tbStartEvent =
			{
               {Stage.ADD_NPC, 20, 1, 9, "kaishi1", "kaishi1"},
			},
			tbUnLockEvent =
			{
			},
		},
		[7] = {nTime = 0, nNum = 1 ,		-- ���ڿ���ˮ��
			tbPrelock = {4},
			tbStartEvent =
			{
               {Stage.ADD_NPC, 20, 1, 9, "kaishi2", "kaishi2"},
			},
			tbUnLockEvent =
			{
			},
		},
		[8] = {nTime = 0, nNum = 1 ,		-- ���ڿ���ˮ��
			tbPrelock = {5},
			tbStartEvent =
			{
               {Stage.ADD_NPC, 20, 1, 9, "kaishi3", "kaishi3"},
			},
			tbUnLockEvent =
			{
			},
		},
		[9] = {nTime = 0, nNum = 1 ,
			tbPrelock = {1},
			tbStartEvent =
			{
			   {Stage.TARGET_INFO, Lang.mission.str1105[Lang.Idx]},
			},
			tbUnLockEvent =
			{
			   {Stage.BLACK_MSG, Lang.mission.str1106[Lang.Idx]},
			},
		},
		[10] = {nTime = 0, nNum = 1 ,
			tbPrelock = {9},
			tbStartEvent =
			{
			   {Stage.ADD_NPC, 20, 1, 10, "zisha1111", "zisha1"},
			   {Stage.TARGET_INFO, Lang.mission.str1105[Lang.Idx]},
			},
			tbUnLockEvent =
			{
			   {Stage.BLACK_MSG, Lang.mission.str1107[Lang.Idx]},
			},
		},
		[11] = {nTime = 0, nNum = 22 ,		-- ��һ�ڵ㣺��������ħ��
			tbPrelock = {10},
			tbStartEvent =
			{
               {Stage.ADD_NPC, 11, 14, 11, "mobing", "mobing"},
			   {Stage.ADD_NPC, 12, 6, 11, "gongjian", "gongjian"},
			   {Stage.ADD_NPC, 13, 1, 11, "mobing1", "mobing1"},
			   {Stage.ADD_NPC, 14, 1, 11, "mobing2", "mobing2"},
			   {Stage.TARGET_INFO, Lang.mission.str1108[Lang.Idx]},
			},
			tbUnLockEvent =
			{
		     	{Stage.ADD_NPC, 2, 1, 11, "shuijing2", "shuijing2"},
				{Stage.BLACK_MSG, Lang.mission.str1106[Lang.Idx]},
			},
		},
		[12] = {nTime = 0, nNum = 1 ,		-- �ڶ�ˮ������
			tbPrelock = {11},
			tbStartEvent =
			{
               {Stage.ADD_NPC, 20, 1, 12, "zisha2", "zisha2"},
			    {Stage.TARGET_INFO, Lang.mission.str1109[Lang.Idx]},
			},
			tbUnLockEvent =
			{
			   {Stage.BLACK_MSG, Lang.mission.str1110[Lang.Idx]},
			},
		},
		[13] = {nTime = 0, nNum = 1 ,		-- �ڶ��ڵ㣺����Թ��
			tbPrelock = {12},
			tbStartEvent =
			{
               {Stage.ADD_NPC, 15, 1, 13, "yuanling", "yuanling"},
			   {Stage.ADD_NPC, 16, 1, 13, "shengguang", "shengguang", 100, 10,"shengguang_timer"},
			   {Stage.TARGET_INFO, Lang.mission.str1111[Lang.Idx]},
			},
			tbUnLockEvent =
			{
			   {Stage.ADD_NPC, 3, 1, 13, "shuijing3", "shuijing3"},
			   {Stage.BLACK_MSG, Lang.mission.str1106[Lang.Idx]},
			   {Stage.DEL_NPC,"shengguang","shengguang_timer"},
			},
		},
		[14] = {nTime = 0, nNum = 1 ,		-- ����ˮ������
			tbPrelock = {13},
			tbStartEvent =
			{
               {Stage.ADD_NPC, 20, 1, 14, "zisha3", "zisha3"},
			    {Stage.TARGET_INFO, Lang.mission.str1112[Lang.Idx]},
			},
			tbUnLockEvent =
			{
			   {Stage.BLACK_MSG, Lang.mission.str1113[Lang.Idx]},
			},
		},
		[15] = {nTime = 0, nNum = 1 ,		-- �����ڵ㣺���𿪹�(��һ��)
			tbPrelock = {14},
			tbStartEvent =
			{
            {Stage.ADD_NPC, 19, 1, 15, "gang3", "gang3"},
			{Stage.ADD_NPC, 33, 1, 15, "jiantou3", "jiantou3"},
			{Stage.ADD_NPC, 21, 1, 15, "gui1", "gui1"},
			{Stage.ADD_NPC, 22, 1, 15, "gui2", "gui2"},
			{Stage.ADD_NPC, 23, 2, 15, "gui3", "gui3"},
			{Stage.ADD_NPC, 24, 2, 15, "gui4", "gui4"},
			{Stage.ADD_NPC, 25, 6, 15, "xionggui1", "xionggui1"},
			{Stage.ADD_NPC, 34, 6, 15, "xionggui2", "xionggui2"},
			{Stage.TARGET_INFO, Lang.mission.str1114[Lang.Idx]},
			},
			tbUnLockEvent =
			{
			{Stage.DEL_NPC,"gui1"},
			{Stage.DEL_NPC,"gui2"},
			{Stage.DEL_NPC,"gui3"},
			{Stage.DEL_NPC,"gui4"},
            {Stage.DEL_NPC,"jiantou3"},
			{Stage.ADD_NPC, 18, 1, 17, "xinzisha", "xinzisha"},
			},
		},
		[16] = {nTime = 0, nNum = 1 ,		-- �����ڵ㣺���𿪹أ��ڶ�����
			tbPrelock = {14},
			tbStartEvent =
			{
			{Stage.ADD_NPC, 19, 1, 16, "gang4", "gang4"},
			{Stage.ADD_NPC, 33, 1, 16, "jiantou4", "jiantou4"},
			{Stage.TARGET_INFO, Lang.mission.str1114[Lang.Idx]},
			},
			tbUnLockEvent =
			{
			{Stage.DEL_NPC,"xionggui1"},
			{Stage.DEL_NPC,"xionggui2"},
			{Stage.DEL_NPC,"jiantou4"},
			{Stage.ADD_NPC, 18, 1, 17, "xinzisha1", "xinzisha1"},
			},
		},
		[17] = {nTime = 0, nNum = 2 ,		-- ����ˮ������
			tbPrelock = {14},
		    tbStartEvent =
			{
			},
			tbUnLockEvent =
		   {
			{Stage.ADD_NPC, 4, 1, 2, "shuijing4", "shuijing4"},

			},
		},
		[18] = {nTime = 0, nNum = 1 ,		-- ����ˮ������
			tbPrelock = {17},
			tbStartEvent =
			{
               {Stage.ADD_NPC, 20, 1, 18, "zisha4", "zisha4"},
			   {Stage.TARGET_INFO, Lang.mission.str1115[Lang.Idx]},
			    {Stage.BLACK_MSG, Lang.mission.str1117[Lang.Idx]},
			},
			tbUnLockEvent =
			{
			{Stage.DEL_NPC,"gui1"},
			{Stage.DEL_NPC,"gui2"},
			{Stage.DEL_NPC,"gui3"},
			{Stage.DEL_NPC,"gui4"},
			{Stage.DEL_NPC,"xionggui1"},
			{Stage.DEL_NPC,"xionggui2"},
			   {Stage.BLACK_MSG, Lang.mission.str1117[Lang.Idx]},
			},
		},
		[19] = {nTime = 0, nNum = 1 ,		-- ���Ľڵ㣺����BOSS����
			tbPrelock = {18},
			tbStartEvent =
			{
               {Stage.ADD_NPC, 17, 1, 19, "yaowang", "yaowang"},
			   {Stage.NPC_BUBBLE, "yaowang",Lang.mission.str1118[Lang.Idx], 2},
			   {Stage.TARGET_INFO, Lang.mission.str1119[Lang.Idx]},
			},
			tbUnLockEvent =
			{
			{Stage.DEL_NPC,"jiaxue","jiaxue_timer"},
			{Stage.DEL_NPC,"dazhao","dazhao_timer"},
			{Stage.DEL_NPC,"huoyan1"},
			{Stage.DEL_NPC,"sudu1"},
			{Stage.DEL_NPC,"huixue1"},
			{Stage.DEL_NPC,"zhaohuan11"},
			{Stage.DEL_NPC,"zhaohuan22"},
			{Stage.DEL_NPC,"zhaohuan33"},
			{Stage.DEL_NPC,"zhaohuan44"},
			{Stage.DEL_NPC,"zhaohuan1"},
			{Stage.DEL_NPC,"zhaohuan2"},
			{Stage.DEL_NPC,"zhaohuan3"},
			{Stage.DEL_NPC,"zhaohuan4"},
			{Stage.CLEAR_BUFF, 1204},
			{Stage.CLEAR_BUFF, 1205},
			{Stage.CLEAR_BUFF, 1207},
			{Stage.CLEAR_BUFF, 1208},
			{Stage.CLEAR_BUFF, 1216},
			{Stage.CLEAR_BUFF, 1217},
			 {Stage.BLACK_MSG, Lang.mission.str1120[Lang.Idx]},
			},
		},
		[20] = {nTime = 0, nNum = 1 ,		-- ��������BOSS����ɱ��
			tbPrelock = {18},
			tbStartEvent =
			{
               {Stage.ADD_NPC, 30, 3, 20, "beisha", "beisha"},
			},
			tbUnLockEvent =
			{
			   {Stage.DEL_NPC,"beisha"},
			},
		},
		[21] = {nTime = 30, nNum = 0 ,		-- ��һ���ٻ�һ��С��
			tbPrelock = {20},
			tbStartEvent =
			{
			  {Stage.ADD_NPC, 26, 2, 21, "zhaohuan1", "zhaohuan1"},
			  {Stage.ADD_NPC, 27, 3, 21, "zhaohuan2", "zhaohuan2"},
			  {Stage.ADD_NPC, 28, 2, 21, "zhaohuan3", "zhaohuan3"},
			  {Stage.ADD_NPC, 29, 3, 21, "zhaohuan4", "zhaohuan4"},
			   {Stage.BLACK_MSG, Lang.mission.str1121[Lang.Idx]},
			},
			tbUnLockEvent =
			{
			},
		},
		[22] = {nTime = 0, nNum = 1 ,		-- ������������ɱ��
			tbPrelock = {20},
			tbStartEvent =
			{
               {Stage.ADD_NPC, 30, 3, 22, "beisha1", "beisha"},
			},
			tbUnLockEvent =
			{
			   {Stage.DEL_NPC,"beisha1"},
			   {Stage.DEL_NPC,"zhaohuan1"},
			   {Stage.DEL_NPC,"zhaohuan2"},
			   {Stage.DEL_NPC,"zhaohuan3"},
			   {Stage.DEL_NPC,"zhaohuan4"},
			},
		},
		[23] = {nTime = 30, nNum = 0 ,		-- �ڶ����ٻ�һ��С��
			tbPrelock = {22},
			tbStartEvent =
			{
			  {Stage.ADD_NPC, 26, 3, 22, "zhaohuan11", "zhaohuan1"},
			  {Stage.ADD_NPC, 27, 2, 22, "zhaohuan22", "zhaohuan2"},
			  {Stage.ADD_NPC, 28, 3, 22, "zhaohuan33", "zhaohuan3"},
			  {Stage.ADD_NPC, 29, 2, 22, "zhaohuan44", "zhaohuan4"},
			   {Stage.BLACK_MSG, Lang.mission.str1121[Lang.Idx]},
			},
			tbUnLockEvent =
			{
			},
		},
		[24] = {nTime = 0, nNum = 1 ,		-- ��������
			tbPrelock = {22},
			tbStartEvent =
			{
               {Stage.ADD_NPC, 30, 3, 24, "beisha2", "beisha"},
			},
			tbUnLockEvent =
			{
			   {Stage.DEL_NPC,"beisha2"},
			},
		},
		[25] = {nTime = 30, nNum = 0 ,		-- �ٻ���ѪС��
			tbPrelock = {24},
			tbStartEvent =
			{
			  {Stage.ADD_NPC, 31, 1, 25, "jiaxue", "jiaxue", 200, 7, "jiaxue_timer"},
			   --{Stage.ADD_NPC, 32, 1, 25, "dazhao", "dazhao", 200, 12, "dazhao_timer"},
			   {Stage.BLACK_MSG, Lang.mission.str1123[Lang.Idx]},
			},
			tbUnLockEvent =
			{
			},
		},
		[26] = {nTime = 1, nNum = 0 ,		-- ɾ������BUFF
			tbPrelock = {19},
			tbStartEvent =
			{

			},
			tbUnLockEvent =
			{
				{Stage.DO_SCRIPT, "self.bCanTakeAward = 1"},
			},
		},
		[27] = {nTime = 5, nNum = 0 ,		-- ͨ�������ܼ�ʱ
			tbPrelock = {26},
			tbStartEvent =
			{
				{Stage.TARGET_INFO, Lang.mission.str1067[Lang.Idx]},
				{Stage.TIME_INFO, Lang.mission.str1068[Lang.Idx], 4},
			},
			tbUnLockEvent =
			{
				{Stage.DO_SCRIPT, "self.bFinishLayer = 1"},
			},
		}
    }
}

--���ѵĽ���
tbStageSetting[3] =
{
	nTimeLimit = 905,  --����ʱ��5����
	nMapId = 504,
	nLayer = 3,
    tbBeginPos = {2727, 400, 1048576},

    -- �����漰��NPC����
	NPC =
	{
	-- 		���  	npcģ��				�ȼ�(-1Ĭ�����npcpro��)	5��(Ĭ��-1)
	  [1] = {nTemplate = 1200, nLevel = 25, nSeries = -1},		-- �󽫾�
	  [2] = {nTemplate = 1201, nLevel = -1, nSeries = -1},		-- ����
	  [3] = {nTemplate = 1202, nLevel = 1, nSeries = -1},		-- ��ɱ
	  [4] = {nTemplate = 1203, nLevel = -1, nSeries = -1},		-- ����
	  [5] = {nTemplate = 1204, nLevel = 25, nSeries = -1},		-- ��ɱ
	  [6] = {nTemplate = 1205, nLevel = 25, nSeries = -1},		-- ��������
	  [7] = {nTemplate = 1206, nLevel = 25, nSeries = -1},		-- �����
	  [8] = {nTemplate = 1207, nLevel = -1, nSeries = -1},		-- ȫ���Ѫ
	  [9] = {nTemplate = 1208, nLevel = -1, nSeries = -1},		-- �󽫾�
	  [10] = {nTemplate = 1209, nLevel = -1, nSeries = -1},		-- ǽ
	  [11] = {nTemplate = 1210, nLevel = -1, nSeries = -1},		-- ͸��Ŀ��
	},
    LOCK =
    {
       -- 1�������ܲ��Ĭ��1��Ϊ��ʼ��
		[1] = {nTime = 5, nNum = 0,		-- �ܼ�ʱ
			tbPrelock = {},
			tbStartEvent =
			{
			    {Stage.TIME_INFO, Lang.mission.str1124[Lang.Idx],1},
				{Stage.SET_TRAP_INVALID, 17, 1},
				{Stage.SET_TRAP_INVALID, 16, 0},
				{Stage.ADD_NPC, 10, 1, 1, "qiang1", "qiang1"},
			},
			tbUnLockEvent =
			{
			{Stage.DEL_NPC,"qiang1","qiang1"},
			},
		},
		[2] = {nTime = 900, nNum = 0 ,		-- ʱ�䵹��ʱ��ʱ�䵽�ˣ�ϵͳ���Զ����˳�����
			tbPrelock = {1},
			tbStartEvent =
			{
                {Stage.SET_TRAP_INVALID, 16, 1},
				{Stage.ADD_NPC, 2, 2, 2, "huoyan", "huoyan"},
			    {Stage.TIME_INFO, Lang.mission.str1125[Lang.Idx],2},
			},
			tbUnLockEvent =
			{
			},
		},
	    [3] = {nTime = 0, nNum = 1 ,		-- �����������ӿ���
			tbPrelock = {1},
			tbStartEvent =
			{
			   {Stage.ADD_NPC, 3, 3, 3, "zisha1", "zisha1"},
			   {Stage.ADD_NPC, 11, 1, 3, "mubiao", "mubiao"},
			   {Stage.BLACK_MSG, Lang.mission.str1126[Lang.Idx]},
			   {Stage.TARGET_INFO, Lang.mission.str1127[Lang.Idx]},
			},
			tbUnLockEvent =
			{
			    {Stage.ADD_NPC, 2, 2, 3, "huoyan1", "huoyan1"},
			},
		},
		 [4] = {nTime = 0, nNum = 1 ,		-- �����������ӿ���
			tbPrelock = {3},
			tbStartEvent =
			{
			   {Stage.ADD_NPC, 3, 3, 4, "zisha2", "zisha2"},
			},
			tbUnLockEvent =
			{
			   {Stage.ADD_NPC, 2, 2, 4, "huoyan2", "huoyan2"},
			},
		},
		 [5] = {nTime = 0, nNum = 1 ,		-- �����������ӿ���
			tbPrelock = {4},
			tbStartEvent =
			{
			   {Stage.ADD_NPC, 3, 3, 5, "zisha3", "zisha3"},
			},
			tbUnLockEvent =
			{
			   {Stage.ADD_NPC, 2, 2, 5, "huoyan3", "huoyan3"},
			},
		},
		 [6] = {nTime = 0, nNum = 1 ,		-- �����������ӿ���
			tbPrelock = {5},
			tbStartEvent =
			{
			   {Stage.ADD_NPC, 3, 3, 6, "zisha4", "zisha4"},
			},
			tbUnLockEvent =
			{
			{Stage.BLACK_MSG, Lang.mission.str1133[Lang.Idx]},
			{Stage.DEL_NPC,"mubiao"},
			},
		},
		 [7] = {nTime = 8, nNum = 0 ,		-- �����������ӿ���
			tbPrelock = {6},
			tbStartEvent =
			{
			{Stage.ADD_NPC, 4, 4, 7, "shandian", "shandian", 20, 2,"shandian_timer"},
			},
			tbUnLockEvent =
			{
			{Stage.DEL_NPC,"shandian","shandian_timer"},
			{Stage.ADD_NPC, 4, 5, 7, "shandian1", "shandian1"},
			},
		},
		[8] = {nTime = 0, nNum = 1 ,		-- ��ͨ����������ʱ�䵹��ʱ��ɱ�ָ�����
			tbPrelock = {15},
			tbStartEvent =
			{
			{Stage.SET_TRAP_INVALID, 17, 0},
			{Stage.ADD_NPC, 8, 1, 8, "jiaxue", "jiaxue", 200, 30, "jiaxue_timer"},
			{Stage.ADD_NPC, 10, 1, 1, "qiang2", "qiang2"},
			{Stage.ADD_NPC, 1, 1, 8, "dajiangjun", "dajiangjun"},
			{Stage.BLACK_MSG, Lang.mission.str1128[Lang.Idx]},
			{Stage.TARGET_INFO, Lang.mission.str1127[Lang.Idx]},
			},
			tbUnLockEvent =
			{
				{Stage.DEL_NPC,"jiaxue","jiaxue_timer"},
				{Stage.DEL_NPC,"fenshen1"},
				{Stage.DEL_NPC,"fenshen"},

			},
		},
		 [9] = {nTime = 0, nNum = 1 ,		-- �����������ӿ���
			tbPrelock = {7},
			tbStartEvent =
			{
			   {Stage.ADD_NPC, 5, 3, 9, "beisha", "beisha"},
			},
			tbUnLockEvent =
			{
			     {Stage.BLACK_MSG, Lang.mission.str1129[Lang.Idx]},
			   {Stage.ADD_NPC, 6, 4, 9, "fenshen", "fenshen"},
			   	{Stage.DEL_NPC,"beisha"},
			},
		},
		[10] = {nTime = 0, nNum = 1 ,		-- �����������ӿ���
			tbPrelock = {9},
			tbStartEvent =
			{
			   {Stage.ADD_NPC, 5, 3, 10, "beisha1", "beisha"},
			},
			tbUnLockEvent =
			{
			   {Stage.BLACK_MSG, Lang.mission.str1129[Lang.Idx]},
			   {Stage.ADD_NPC, 6, 4, 10, "fenshen1", "fenshen"},
			   	{Stage.DEL_NPC,"beisha1"},
				{Stage.DEL_NPC,"fenshen"},
			},
		},
		[11] = {nTime = 0, nNum = 1 ,		-- �����������ӿ���
			tbPrelock = {10},
			tbStartEvent =
			{
			   {Stage.ADD_NPC, 5, 3, 11, "beisha2", "beisha"},
			},
			tbUnLockEvent =
			{
			{Stage.BLACK_MSG, Lang.mission.str1130[Lang.Idx]},
			   {Stage.ADD_NPC, 7, 3, 11, "feng", "feng"},
			   	{Stage.DEL_NPC,"beisha2"},
			},
		},
		[12] = {nTime = 0, nNum = 1 ,		-- �����������ӿ���
			tbPrelock = {11},
			tbStartEvent =
			{
			   {Stage.ADD_NPC, 5, 3, 12, "beisha3", "beisha"},
			},
			tbUnLockEvent =
			{
			{Stage.BLACK_MSG, Lang.mission.str1130[Lang.Idx]},
			   {Stage.ADD_NPC, 7, 3, 12, "feng1", "feng"},
			   	{Stage.DEL_NPC,"beisha3"},
			},
		},
		[13] = {nTime = 10, nNum = 0 ,		-- �����������ӿ���
			tbPrelock = {11},
			tbStartEvent =
			{

			},
			tbUnLockEvent =
			{
			{Stage.DEL_NPC,"feng"},
			},
		},
		[14] = {nTime = 12, nNum = 0 ,		-- �����������ӿ���
			tbPrelock = {12},
			tbStartEvent =
			{

			},
			tbUnLockEvent =
			{
			{Stage.DEL_NPC,"feng1"},
			},
		},
		[15] = {nTime = 8, nNum = 0 ,		-- �����������ӿ���
			tbPrelock = {7},
			tbStartEvent =
			{
			   {Stage.ADD_NPC, 9, 1, 15, "dajiangjun1", "dajiangjun"},
			   {Stage.NPC_BUBBLE, "dajiangjun1",Lang.mission.str937[Lang.Idx], 3},
			--{Stage.TARGET_INFO, Lang.mission.str1096[Lang.Idx]},
			},
			tbUnLockEvent =
			{
				{Stage.DEL_NPC,"dajiangjun1"},
				{Stage.DEL_NPC,"shandian1"},
			},
		},
		[16] = {nTime = 1, nNum = 0 ,		-- ��ͨ����������ʱ�䵹��ʱ��ɱ�ָ�����
			tbPrelock = {8},
			tbStartEvent =
			{
			{Stage.SET_TRAP_INVALID, 16, 0},
			},
			tbUnLockEvent =
			{
				{Stage.DO_SCRIPT, "self.bCanTakeAward = 1"},
			},
		},
		[17] = {nTime = 20, nNum = 0 ,		-- ͨ�������ܼ�ʱ
			tbPrelock = {16},
			tbStartEvent =
			{
				{Stage.TARGET_INFO, Lang.mission.str1131[Lang.Idx]},
				{Stage.TIME_INFO, "Lang.mission.str1132[Lang.Idx]", 4},
			},
			tbUnLockEvent =
			{
				{Stage.DO_SCRIPT, "self.bFinishStage = 1"},
			},
		}
    }
}
