--
-- ��ң�ȹؿ� 
-- 

--Include("script/preload.lua")
local preEnv = _G	--����ɵĻ���
--Lang = preEnv.Lang
--assert(Lang)

--zzf
setfenv(1, XoyoGame)	--���õ�ǰ����ΪKin
local   Lang = preEnv.Lang
Lang.mission.str812= {"��ͨ","","","","",""}
Lang.mission.str813= {"�Ѷ�","","","","",""}
Lang.mission.str814= {"����","","","","",""}
Lang.mission.str815= {"��˵","","","","",""}
Lang.Idx = 1
-- �¼�ID

ADD_NPC 		= 1		-- ���NPC
DEL_NPC			= 2		-- ɾ��NPC
CHANGE_TRAP		= 3		-- ����Trip��
DO_SCRIPT		= 4		-- ִ�нű�
TARGET_INFO		= 5		-- Ŀ����Ϣ
TIME_INFO		= 6		-- ʱ����Ϣ
CLOSE_INFO		= 7		-- �رս���
CHANGE_FIGHT	= 8		-- ����ս��״̬
MOVIE_DIALOG	= 9		-- ��Ӱģʽ
BLACK_MSG		= 10	-- �ڵ���Ļ
CHANGE_NPC_AI	= 11	-- ����NPC��AI
ADD_GOUHUO		= 12	-- ��������
SEND_CHAT		= 13	-- ����NPC����
ADD_TITLE		= 14	-- �ӳƺ�
TRANSFORM_CHILD = 15    -- ��С��
SHOW_NAME_AND_LIFE = 16 -- ��ʾ������Ѫ��
NPC_CAN_TALK	= 17	-- Dialog Npc ��ֹ�Ի�
CHANGE_CAMP		= 18	-- �ı�����
SET_SKILL		= 19	-- �������Ҽ�����
DISABLE_SWITCH_SKILL = 20 -- ��ֹ�л�����
TRANSFORM_CHILD_2	= 21 -- ����ͯ
FINISH_ACHIEVE		= 22 -- �ɾ�
NPC_BLOOD_PERCENT	= 23 -- NPCѪ��ע��ص�
NEW_WORLD_PLAYER = 24 	 -- �������
NPC_CAST_SKILL = 25 	-- NPC�ͷż���
NPC_SET_LIFE = 26		-- ���ٷֱ�����npcѪ��
PLAYER_ADD_EFFECT = 27 	-- ������������Ҽ�һ��״̬
PLAYER_REMOVE_EFFECT = 28  	-- ��������������Ƴ�һ��״̬
NPC_ADD_BUFF_TO_PLAYER = 29 -- npc��Χ��Ҽ�buff
SET_NPC_NICKNAME = 30 -- ����npc nickname
NPC_BUBBLE = 31 --npc����
CLEAR_BUFF = 32	-- ɾ���������buff
SYS_MSG = 33	-- ���������ʾ����
REVIVE_INFO = 34

-- AIģʽ
AI_MOVE			= 1
AI_RECYLE_MOVE	= 2
AI_ATTACK		= 3

MAX_TIMES			= 14 	-- ����ۼƴ���
MIN_TEAM_PLAYERS	= 4		-- ������������
MIN_LEVEL			= 50	-- ��͵ȼ�
MAX_TEAM			= 8		-- ������������
PLAY_ROOM_COUNT		= 5		-- ���ع���
ROOM_MAX_LEVEL		= 7		-- �������ȼ�
GUESS_QUESTIONS 	= 30	-- ���������Ŀ��	
MIN_CORRECT			= 20	-- ����Ҫ��Զ��ٲ��ܽ���
LOCK_MANAGER_TIME	= 20	-- ����������ʱ��
PK_REFIGHT_TIME		= 20	-- PK��Ͷս��ʱ��
MAX_REPUTE_TIMES	= 60	-- ���һ�����
START_TIME1			= 0800	-- ����ʱ��1
END_TIME1			= 2300	-- �ر�ʱ��1
START_TIME2			= 0000	-- ����ʱ��2
END_TIME2			= 0200	-- �ر�ʱ��2

TASK_GROUP			= 2050
TIMES_ID			= 1		-- �μӴ����������
CUR_DATE			= 2		-- �Ѿ�����
REPUTE_TIMES		= 3		-- �һ������������
CUR_REPUTE_DATE		= 4		-- ����һ�����
ADDTIMES_TIME		= 5		-- ���Ӵ�����ʱ��
TASK_DIFFICUTY		= 54	-- ��¼�Ѷ�

DELAY_ENDTIME		= 15	-- �ӳٹر�ʱ�䣬15��

REPUTE_CAMP			= 5
REPUTE_CLASS		= 3
REPUTE_VALUE		= 10	-- �һ�����ֵ

START_GAME_TIME 	= 60	-- ׼����׼��ʱ��

ITEM_BAOXIANG		= {18,1,190,1};

LOG_ATTEND_OPEN     = 1;      --��ң�Ȳ���LOG����

RANK_RECORD = 5;

-- ����ȼ���Ӧ��ʱ���������룩
ROOM_TIME = 
{
	[1] = 210,	-- �� 3��
	[2] = 240,	-- �� 3��30
	[3] = 270,	-- �� 4��
	[4]	= 300,	-- �� 4��30
	[5] = 330,	-- �� 5��
	[6] = 360,	-- �� 5��30
	[7] = 390,	-- �� 6��
}

ROOM_DTT_TIME = 2000 -- ���ʱʱ��

-- ��ͼ�� ÿ���ͼ������ͬһ��������~�������֮�����޷����ԭ�������
MAP_GROUP = 
{         -- 1 , 2 , 3 , 4 , 5 , 6 , 7 , 8 , 9 , 10
	[1] =  {119,501,502,505,504,507,511,510,509,508,
			506,512,513,516,514,518,517,520,519,521,
			515,600,601,602,603,604,605,606,607,608,
			609,610,611,612,613,614,615,616,617,618,
			619,522,523,524,525,526,527,528,529,530,
			531},
}

TB_MAPID_LIST = {	119,501,502,505,504,507,511,510,509,508,
			506,512,513,516,514,518,517,520,519,521,
			515,600,601,602,603,604,605,606,607,608,
			609,610,611,612,613,614,615,616,617,618,
			619,522,523,524,525,526,527,528,529,530,
			531};	

-- ������
MANAGER_GROUP = 
{
	[341] = {23, 24, 25},
	[342] = {26, 27, 28, 29},
}

-- ��������
START_SWITCH = 
{
	[1] = 1,
}

BAOMING_IN_POS = {1625,3180};

GAME_IN_POS	= {
	nMapId = 97, 
	nX = 2339, 
	nY = 2670, 
	nZ = 1053184
};	-- ׼������������

PREPARE_TIME = 60;	-- ��׼����׼��ʱ��Ϊ1����

TARGET_INFO_IDX = 1;


-- �뿪��
LEAVE_POS =
{
	--[1] = {1648, 3185},
	100, 3120, 7152, 1048576
}

-- 4��5��6�˶ӳ����ӵĵ���������ֵ
HONOR = {{[4] = 6,  [5] = 8,  [6] = 10},	-- ��һ��
		 {[4] = 3,  [5] = 4, [6] = 5},	-- �ڶ���
		 {[4] = 3, [5] = 4, [6] = 5},	-- ������
		 {[4] = 3, [5] = 4, [6] = 5},	-- ���Ĺ�
		 {[4] = 3, [5] = 4, [6] = 5},	-- �����
		};

--print("sssssssssssssssssss")
-- { ���أ��������Ǽ��������Ѷ�ϵ�� }
LevelDesp =
{
	[1] = { 1, Lang.mission.str812[Lang.Idx],	"��"};
	[2] = { -1, Lang.mission.str813[Lang.Idx] .. "2",	"���"};
	[3] = { 0, Lang.mission.str814[Lang.Idx],	"����"};
	[4] = { -1, Lang.mission.str813[Lang.Idx] .. "4",	"�����"};
	[5] = { 0, Lang.mission.str815[Lang.Idx],	"������"};
};
NPC_LEVEL_FILE = "\\setting\\level\\npc_level.txt";

preEnv.setfenv(1, preEnv)

XoyoGame.TIMES_PER_DAY		= 100 --EventManager.IVER_nXoyoGameCount		-- ÿ���ܲμ���ң�ȵĴ���

-- ÿ��ֻ����6�Σ�6���Ժ� û�е��߽�������Ǯ������ ֻ��80%
XoyoGame.TIMES_FULL_REWARD = 6;

-- ����ͳ��ÿ����ɴ�����task groupid
XoyoGame.FINISH_TASK_GID = 2060;
XoyoGame.LAST_FINISH_DAY = 1;
XoyoGame.FINISH_TASK_ID = 2;


-----------------------------------------
-- RoomSetting��ʼ��
XoyoGame.RoomSetting = {};
local BaseRoom = XoyoGame.BaseRoom;
local RoomSetting = XoyoGame.RoomSetting;

RoomSetting.tbRoom = {};
