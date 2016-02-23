-- ���ڻ����Ӫenum����ʼ����
Activity.START_CAMP = 4;

-- ��һ���������ᣬʣ�µ���ҷ��䵽��һ����ķ�ʽ
Activity.ASSIGN_TYPE = {}
Activity.ASSIGN_TYPE.DONOT_NEED = 1         -- ����Ҫ�Զ���������¸�����
Activity.ASSIGN_TYPE.RANDOMLY_ASSIGNED = 2  -- ����־����䣬���������ҵ�ÿһ���Ӽ̲�����,����дÿ������ֵ������������������ƽ������
Activity.ASSIGN_TYPE.GROUP_ORDER_ASSIGNED = 3 -- ����Ϊ��λ˳����䣬������ļ���˳�����˳����䵽ÿ���Ӽ̲�����
Activity.ASSIGN_TYPE.SPECIFY_ASSIGNED = 4  -- ָ�����䣬���ַ���ģʽ��ֻ����һ���Ӽ̲���


-- �������ͣ�һ����������μ���ҷ���ķ�ʽ
Activity.MAX_GROUP_NUM = 4
Activity.GROUP_TYPE = {}
Activity.GROUP_TYPE.DONNOT_GROUP = 1   -- ������
Activity.GROUP_TYPE.RANDOM_GROUP = 2   -- ��ȫ����ķ���
Activity.GROUP_TYPE.FIGHT_SCORE_GROUP = 3	--ս������

-- �����������¼�����
Activity.EVENT_TYPE = {}
Activity.EVENT_TYPE.MOVIE_DIALOG = 1;
Activity.EVENT_TYPE.DO_SCRIPT	  = 2;		-- ִ�нű�
Activity.EVENT_TYPE.ADD_NPC      = 3;
Activity.EVENT_TYPE.BLACK_MSG	= 4;	-- ������ģ 	
Activity.EVENT_TYPE.TARGET_INFO	= 5;	-- Ŀ����Ϣ 
Activity.EVENT_TYPE.DEL_NPC 	= 6;
Activity.EVENT_TYPE.NPC_BUBBLE = 8;
Activity.EVENT_TYPE.ME_BUBBLE = 9;
Activity.EVENT_TYPE.CHANGE_TRAP = 10;
Activity.EVENT_TYPE.HOOK_TRAP = 11;
Activity.EVENT_TYPE.TIME_INFO = 12;
Activity.EVENT_TYPE.SHOW_REWARD_PANEL = 13;
Activity.EVENT_TYPE.TIMING_FUNCTION = 14;    -- ��ʱִ��һ������ (szFucName, nCurrentExecuteTime, nMaxExecuteTime, {arg...})
Activity.EVENT_TYPE.ADD_EXC_ALL_EVENT = 15;  -- ���һ���������˶���ִ��һ�ε��¼���������Ӻ��н�ɫ����˻���輴ִ��һ��(nEventType, {arg..})
Activity.EVENT_TYPE.REMOVE_EXC_ALL_EVENT = 16;  -- ɾ��һ���������˶���ִ��һ�ε��¼�(nEventType, {arg..})
Activity.EVENT_TYPE.SET_RELATION = 17;  -- ����ս����ϵ(nEventType, {arg..})
Activity.EVENT_TYPE.ADD_PLAYER_IN_LOCK = 18;  -- ���ض�����Ҽ��뵱ǰ����������������������npc���������Ļ���(nEventType, nPlayerGroup)
Activity.EVENT_TYPE.JOIN_STEP = 19;  -- ���ض�����Ҽ���ĳ������(nEventType, nActivityIndex, nStepIndex, IsRemoveWinner, nPlayerGroup) ����IsRemoveWinner: ���ǵ�ǰ����ʤ���ߣ��ڼ���ָ������ʱ�Ƿ�����ڵ�ǰ�����ʤ���߼�¼
Activity.EVENT_TYPE.SHOW_NOTICE_MSG = 20; -- ��ʾ����(nEventType, szMsg)  �ɲ��������{Killer}��ʾɱ�������֣�{Dead}��ʾ��ɱ������
Activity.EVENT_TYPE.REVIVE_INFO = 21;
Activity.EVENT_TYPE.REDUCE_ALL_DEGREE = 22;	--��������Ŀǰֻ��ս�����õ�
Activity.EVENT_TYPE.DEL_ALL_NPC = 23;	--ɾ����ͼ����NPC
Activity.EVENT_TYPE.SET_TRAP_EFFECT = 24;	--	����trap���Ƿ���Ч
Activity.EVENT_TYPE.ADD_NPC_ON_TIME = 25;	--	��ʱ���npc

--�������ֵ
Activity.Type_All = 1;
Activity.Type_Self = 2;
Activity.Type_Npc = 4;
Activity.Type_Team = 8;
Activity.Type_Kin = 16;
Activity.Type_Server = 32;

Activity.Type_All_Enable = 65536;
Activity.Type_Self_Enable = 131072;
Activity.Type_Npc_Enable = 262144;
Activity.Type_Team_Enable = 524288;
Activity.Type_Kin_Enable = 1048576;
Activity.Type_Server_Enable = 2097152;

Activity.Type_Not = 2147483648;--1073741824;--2147483648;

-- �����index����,�е�û��ö��,�޸���ر�����ʱ��ע��
Activity.ACTIVITY_INDEX_ZBT		= 2			-- ս����
Activity.ACTIVITY_INDEX_BOSS	= 15		-- ����boss
Activity.ACTIVITY_INDEX_MPJJ	= 10		-- ս����˫(���ɾ���)
Activity.ACTIVITY_INDEX_KIN_PTSY = 1002		-- ���ʢ��
--------------------------------------

-- ���ʼ���趨��
Activity.tbStartSteps = 
{
	[290] = {nActivityIndex = 15, nStepIndex = 2},		-- ����boss
	[330] = {nActivityIndex = 2, nStepIndex = 2},		-- ս����
	[338] = {nActivityIndex = 10, nStepIndex = 1},		-- ս����˫(���ɾ���)
	[340] = {nActivityIndex = 20, nStepIndex = 1},		-- ս��1
	[345] = {nActivityIndex = 21, nStepIndex = 1},		-- ս��2
	[346] = {nActivityIndex = 22, nStepIndex = 1},		-- ս��3
	[347] = {nActivityIndex = 23, nStepIndex = 1},		-- ս��4
	[348] = {nActivityIndex = 24, nStepIndex = 1},		-- ս��5
	[353] = {nActivityIndex = 30, nStepIndex = 1},		--����֮��1
	[354] = {nActivityIndex = 31, nStepIndex = 1},		--����֮��2
	[355] = {nActivityIndex = 32, nStepIndex = 1},		--����֮��3
	[356] = {nActivityIndex = 33, nStepIndex = 1},		--����֮��4
	[341] = {nActivityIndex = 26, nStepIndex = 1},		-- ��������
	[3] = {nActivityIndex = 1001, nStepIndex = 1},	-- ����
	[1002] = {nActivityIndex = 1002, nStepIndex = 1},	-- ���ʢ��
}

Activity.tbBattleFieldMaps = 
{
	340, 345, 346, 347, 348,
}

-- ����趨��
Activity.STEP_TYPE = {}
Activity.STEP_TYPE.BASE = 1           -- ��������
Activity.STEP_TYPE.ZHUNBEICHANG = 2   -- ׼����
Activity.STEP_TYPE.MENPAIJINGJI_YUXIANSAI = 3   -- ս����˫(���ɾ���)Ԥѡ��
Activity.STEP_TYPE.MENPAIJINGJI_SAICHANG = 4   -- ս����˫(���ɾ���)����

Activity.STEP_TYPE.BATTLE_FIELD = 5   -- ս��
Activity.STEP_TYPE.BATTLE_FIELD_ZHUNBEICHANG_1 = 7  -- ս����׼����, ׼����1�� 
Activity.STEP_TYPE.BATTLE_FIELD_ZHUNBEICHANG_2 = 8  -- ս����׼����, ׼����2�� 

Activity.STEP_TYPE.KUAFUBOSS_ZHUNBEICHANG = 6   -- ���BOSS׼����
Activity.STEP_TYPE.KUAFUBOSS_SAICHANG 	  = 9	-- ���boss����

Activity.STEP_TYPE.ZHANBAOTANG_ZHUNBEICHANG = 10 --ս����׼����
Activity.STEP_TYPE.ZHANBAOTANG_SAICHANG 	= 11 --ս��������

Activity.STEP_TYPE.TONGFIGHT_BATTLEFILED 	= 12 -- ��������

Activity.STEP_TYPE.KIN_PANTAOSHENGYAN		= 13 -- ���ʢ��(����)

Activity.STEP_TYPE.BONFIRE_SAICHANG		= 14 -- ����(����)

Activity.STEP_TYPE.MANHUANGZHIDI		= 15 --����֮��

Activity.ACTSTEP_FACTORY = {}
Activity.ActivitySetting = {}

function Activity.ACTSTEP_FACTORY:Create(stepType)
	return Lib:NewClass(self[stepType])
end

-- �������

-- �����
Activity.REMIND_TIMES_SPAN = (5 * 60)		-- 5����ʱ����

Activity.tbReminds = {};

function Activity:LoadReminds()
	local cfgs = Activity.tbReminds;
	local tbFileData = Lib:LoadTabFile("/setting/activity/activity_remind.txt")
	for _, tbRow in pairs(tbFileData) do
		local nActivityIdx = tonumber(tbRow.ActivityIdx);
		assert(nActivityIdx);
		if not cfgs[nActivityIdx] then
			cfgs[nActivityIdx] = {
			nRemindId1 = tonumber(tbRow.Remind1Id);
			nRemindId2 = tonumber(tbRow.Remind2Id);
			nRemindId3 = tonumber(tbRow.Remind3Id);
			};
		end
	end
end

function Activity:GetRemindByIdx(nActivityIdx, nRemindIdx)
	if not self.tbReminds[nActivityIdx] then
		return;
	end
	
	assert(nRemindIdx >= 1 and nRemindIdx <= 3);
	
	local nRemindId = self.tbReminds[nActivityIdx]["nRemindId"..nRemindIdx];
	assert(nRemindId);
	
	return nRemindId;
end

if #Activity.tbReminds <= 0 then
	Activity:LoadReminds();
end