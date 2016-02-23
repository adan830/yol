-- NPC��Ϊ
if not (MODULE_GAMECLIENT or MODULE_GAMESERVER) then
	return
end

Npc.ACT_FIGHTSTAND		= 0;		-- ս��״̬վ��
Npc.ACT_STAND1			= 1;		-- ��ս��״̬վ��һ
Npc.ACT_STAND2			= 2;		-- ��ս��״̬վ����
Npc.ACT_FIGHTWALK		= 3;		-- ս��״̬����
Npc.ACT_WALK			= 4;		-- ��ս��״̬����
Npc.ACT_FIGHTRUN		= 5;		-- ս��״̬����
Npc.ACT_RUN				= 6;		-- ��ս��״̬����
Npc.ACT_HURT			= 7;		-- ����
Npc.ACT_DEATH			= 8;		-- ����
Npc.ACT_ATTACK1			= 9;		-- ����һ
Npc.ACT_ATTACK2			= 10;		-- ������
Npc.ACT_MAGIC			= 11;		-- ���ܹ���
Npc.ACT_SIT				= 12;		-- ����
Npc.ACT_JUMP			= 13;		-- ��Ծ
Npc.ACT_NONE			= 14;		-- ��

-- NPC״̬
Npc.STATE_BASE			= 1000;		-- ״̬����
Npc.STATE_HURT			= 0;		-- ���˶���״̬
Npc.STATE_WEAK			= 1;		-- ����״̬
Npc.STATE_SLOWALL		= 2;		-- �ٻ�״̬
Npc.STATE_BURN			= 3;		-- ����״̬
Npc.STATE_STUN			= 4;		-- ѣ��״̬
Npc.STATE_FIXED			= 5;		-- ����״̬
Npc.STATE_PALSY			= 6;		-- ���״̬
Npc.STATE_SLOWRUN		= 7;		-- ������״̬
Npc.STATE_FREEZE		= 8;		-- ����״̬
Npc.STATE_CONFUSE		= 9;		-- ����״̬
Npc.STATE_KNOCK			= 10;		-- ����״̬
Npc.STATE_POISON		= 11;		-- �ж�״̬
Npc.STATE_HIDE			= 12;		-- ����״̬
Npc.STATE_SHIELD		= 13;		-- ����״̬
Npc.STATE_SUDDENDEATH	= 14;		-- ���״̬
Npc.STATE_IGNORETRAP	= 15;		-- ����������״̬

Npc.STATE_SLEEP			= 335;		-- ˯��
Npc.STATE_ZHONGDU		= 336;		-- �ж�
Npc.STATE_SHOUSHANG		= 337;		-- ����
Npc.STATE_DEATH			= 338;		-- ����
Npc.STATE_FUHUO			= 339;		-- ����״̬����Ӧ������

-- NPC��Դ��λ
Npc.NPCRES_PART_HELM	= 0;		-- ͷ����Դ
Npc.NPCRES_PART_ARMOR	= 1;		-- ������Դ
Npc.NPCRES_PART_WEAPON	= 2;		-- ������Դ
Npc.NPCRES_PART_HORSE	= 3;		-- ��ƥ��Դ

Npc.NPCRELATION_FRIEND  = 0;        -- ��ϵ�Ѻ�
Npc.NPCRELATION_ENEMY   = 1;		-- ��ϵ�ж�

Npc.PNC_NOTIFY = 
{
	RELATIONCHANGED  = 1,
	BORN			 = 2,
}

-- Npc��������������ԣ�Weight��Ȩ�ؾݴ��������һ����(�����ٸ��ݾ�������Ȩ������������һ��),IndexΪNpc����±꣬�������ظ�
Npc.BubbleProperty = 
{
	Silence		= { Weight = 200 },								-- ��Ĭ
	Task 		= { Weight = 50, nIndex = "Task" },				-- ��ͨ����
	Normal		= { Weight = 50, nIndex = "Normal" },			-- ��������
};

-- NPC�����ϵö�� (������� knpcdef.h �� KE_NPC_VIRTUALRELATIONTYPE ��Ӧ)
Npc.emNPCVRELATIONTYPE_NONE 	= 0;		-- �޹�ϵ
Npc.emNPCVRELATIONTYPE_TONE 	= 1;		-- ����ϵ

-- Npc����Ի�����
Npc.GENERAL_DIALOG_TYPE_NORMAL = 1
Npc.GENERAL_DIALOG_TYPE_STORY = 2
Npc.GENERAL_DIALOG_TYPE_EXPSCENE = 3

-- ����npc 
Npc.ComplementalNpc = {}

-- ս��������character����
Npc.CHARACTERCOUNT = 
{
	emHEALTH_COUNT = 1;      -- ����
	emDAMAGE_COUNT = 3;      -- DPS
}

-- NPC ����
Npc.emNPCGROUPTYPE_GROUPS = 0;
Npc.emNPCGROUPTYPE_ALLYGROUPS = 1;
Npc.emNPCGROUPTYPE_ADDGROUPS = 2;

Npc.emModelType = 
{
	emHUMEN_QUINTESSNECE = 3,                 -- ���;�Ӣ
	emNOTHUMEN_NOTQUINTESSNECE = 0,           -- �����ͷǾ�Ӣ
	emNOTHUMEN_QUINTESSNECE = 1,              -- �����;�Ӣ
	emHUMEN_NOTQUINTESSNECE = 2,              -- ���ͷǾ�Ӣ
}

Npc.nMinLevel = 0                             -- Npc ����С�ȼ�0
Npc.nMaxLevel = 100                           -- Npc �����ȼ�

Npc.EXP_TYPE_AVE = 1							--�����˾���
Npc.EXP_TYPE_ALL = 2							--�����˵õ�Exp�ľ���
Npc.EXP_TYPE_BY_DMG = 3							--���˺�������
Npc.EXP_TYPE_FIRSTBLOOD = 4						--��һ�����ȫ��
Npc.EXP_TYPE_LASTBLOOD = 5						--���һ�����ȫ��
Npc.EXP_TYPE_DMGMAX = 6							--�˺������ȫ��