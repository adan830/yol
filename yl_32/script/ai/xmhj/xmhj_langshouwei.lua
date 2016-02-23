-- ��д�ߣ�lidianyi
-- �汾�ţ�6

Include('script/ai/customfunctions.lua')
Include('script/ai/ai_param.lua')
Include('script/ai/argumentstrings.lua')

local g_AIDebugInfo = {}

function AI:Setup(ai)
    local state
    local action
    local param = AI.g_AIParam[ai.nAIType]

    -- ע���Զ��嶯��
    ai.RegisterUserAction(2011, 'AI:GetSelf')

    -- ��ʼ
    state = ai.NewState(1)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 2)

    -- ��������ʱ��
    action = ai.NewAction(2, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(32)
    action.SetBranch(88)
    g_AIDebugInfo[2] = '[2] SET_PRIMARY_TIMER(32)'

    -- ����״̬
    action = ai.NewAction(88, AI_ACTION.SET_STATE)
    action.SetParam(15) -- ��ʼ����
    g_AIDebugInfo[88] = '[88] SetParam(State15)'

    -- ��ʼ����
    state = ai.NewState(15)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 10)

    -- ��¼ԭ��
    action = ai.NewAction(10, AI_ACTION.RECORD_ORIGIN_POSITION)
    action.SetBranch(11)
    g_AIDebugInfo[10] = '[10] RECORD_ORIGIN_POSITION()'

    -- ѡ���Լ�
    action = ai.NewAction(11, 2011)
    action.SetBranch(13)
    g_AIDebugInfo[11] = '[11] AI:GetSelf()'

    -- �ͷż���
    action = ai.NewAction(13, AI_ACTION.CAST_SKILL)
    action.SetParam(564, 1)
    action.SetBranch(17, 17)
    g_AIDebugInfo[13] = '[13] CAST_SKILL(564, 1)'

    -- �ͷż���
    action = ai.NewAction(17, AI_ACTION.CAST_SKILL)
    action.SetParam(565, 1)
    action.SetBranch(85, 85)
    g_AIDebugInfo[17] = '[17] CAST_SKILL(565, 1)'

    -- ��������ʱ��
    action = ai.NewAction(85, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(4)
    action.SetBranch(90)
    g_AIDebugInfo[85] = '[85] SET_PRIMARY_TIMER(4)'

    -- ����״̬
    action = ai.NewAction(90, AI_ACTION.SET_STATE)
    action.SetParam(4) -- ����״̬
    g_AIDebugInfo[90] = '[90] SetParam(State4)'

    -- ����״̬
    state = ai.NewState(4)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 6)
    state.HandleEvent(AI_EVENT.ON_ATTACKED, 23)

    -- ��������
    action = ai.NewAction(6, AI_ACTION.SEARCH_ENEMY)
    action.SetParam(param['SearchPlayerDistance'])
    action.SetBranch(25, 8)
    g_AIDebugInfo[6] = '[6] SEARCH_ENEMY(param[SearchPlayerDistance])'

    -- ��������ʱ��
    action = ai.NewAction(8, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(4)
    action.SetBranch(92)
    g_AIDebugInfo[8] = '[8] SET_PRIMARY_TIMER(4)'

    -- ����״̬
    action = ai.NewAction(92, AI_ACTION.SET_STATE)
    action.SetParam(4) -- ����״̬
    g_AIDebugInfo[92] = '[92] SetParam(State4)'

    -- ��Ŀ����ӵ���в�б�
    action = ai.NewAction(25, AI_ACTION.ADD_TARGET_TO_THREAT_LIST)
    action.SetBranch(32)
    g_AIDebugInfo[25] = '[25] ADD_TARGET_TO_THREAT_LIST()'

    -- Npc��ʼ������CD
    action = ai.NewAction(32, AI_ACTION.NPC_INIT_SKILL_CD)
    action.SetBranch(30)
    g_AIDebugInfo[32] = '[32] NPC_INIT_SKILL_CD()'

    -- ��¼���ص�
    action = ai.NewAction(30, AI_ACTION.RECORD_RETURN_POSITION)
    action.SetBranch(35)
    g_AIDebugInfo[30] = '[30] RECORD_RETURN_POSITION()'

    -- ��������ʱ��
    action = ai.NewAction(35, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(16)
    action.SetBranch(94)
    g_AIDebugInfo[35] = '[35] SET_PRIMARY_TIMER(16)'

    -- ����״̬
    action = ai.NewAction(94, AI_ACTION.SET_STATE)
    action.SetParam(33) -- ս��״̬
    g_AIDebugInfo[94] = '[94] SetParam(State33)'

    -- ս��״̬
    state = ai.NewState(33)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 28)

    -- ѡ���һ��в
    action = ai.NewAction(28, AI_ACTION.SELECT_FIRST_THREAT)
    action.SetBranch(38, 69)
    g_AIDebugInfo[28] = '[28] SELECT_FIRST_THREAT()'

    -- Npc��׼����ѡ��
    action = ai.NewAction(38, AI_ACTION.NPC_STANDARD_SKILL_SELECTOR)
    action.SetBranch(40, 35)
    g_AIDebugInfo[38] = '[38] NPC_STANDARD_SKILL_SELECTOR()'

    -- Npc���ּ����ͷž���
    action = ai.NewAction(40, AI_ACTION.NPC_KEEP_SKILL_CAST_RANGE)
    action.SetBranch(42, 49)
    g_AIDebugInfo[40] = '[40] NPC_KEEP_SKILL_CAST_RANGE()'

    -- Npc�ͷ�ѡ������
    action = ai.NewAction(42, AI_ACTION.NPC_CAST_SELECT_SKILL)
    action.SetBranch(44, 57)
    g_AIDebugInfo[42] = '[42] NPC_CAST_SELECT_SKILL()'

    -- ��������ʱ��
    action = ai.NewAction(44, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(24)
    action.SetBranch(96)
    g_AIDebugInfo[44] = '[44] SET_PRIMARY_TIMER(24)'

    -- ����״̬
    action = ai.NewAction(96, AI_ACTION.SET_STATE)
    action.SetParam(46) -- ������ȴ״̬
    g_AIDebugInfo[96] = '[96] SetParam(State46)'

    -- ������ȴ״̬
    state = ai.NewState(46)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 35)

    -- ��鼼��ʧ�ܼ���
    action = ai.NewAction(57, AI_ACTION.CHECK_SKILL_FAILED_COUNTER)
    action.SetParam(3)
    action.SetBranch(35, 69)
    g_AIDebugInfo[57] = '[57] CHECK_SKILL_FAILED_COUNTER(3)'

    -- ����ϵͳ�޵�
    action = ai.NewAction(69, AI_ACTION.SET_SYSTEM_SHEILD)
    action.SetParam(1)
    action.SetBranch(67)
    g_AIDebugInfo[69] = '[69] SET_SYSTEM_SHEILD(1)'

    -- ����
    action = ai.NewAction(67, AI_ACTION.RETURN)
    action.SetParam(0)
    action.SetBranch(74, 74)
    g_AIDebugInfo[67] = '[67] RETURN(0)'

    -- ��������ʱ��
    action = ai.NewAction(74, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(80)
    action.SetBranch(98)
    g_AIDebugInfo[74] = '[74] SET_PRIMARY_TIMER(80)'

    -- ����״̬
    action = ai.NewAction(98, AI_ACTION.SET_STATE)
    action.SetParam(60) -- �޵з���״̬
    g_AIDebugInfo[98] = '[98] SetParam(State60)'

    -- �޵з���״̬
    state = ai.NewState(60)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 71)
    state.HandleEvent(AI_EVENT.ON_PATH_FAILED, 71)

    -- ����
    action = ai.NewAction(71, AI_ACTION.RETURN)
    action.SetParam(1)
    action.SetBranch(72, 72)
    g_AIDebugInfo[71] = '[71] RETURN(1)'

    -- ��������ʱ��
    action = ai.NewAction(72, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(32)
    action.SetBranch(100)
    g_AIDebugInfo[72] = '[72] SET_PRIMARY_TIMER(32)'

    -- ����״̬
    action = ai.NewAction(100, AI_ACTION.SET_STATE)
    action.SetParam(61) -- ���سɹ�
    g_AIDebugInfo[100] = '[100] SetParam(State61)'

    -- ���سɹ�
    state = ai.NewState(61)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 75)

    -- ���DEBUFF
    action = ai.NewAction(75, AI_ACTION.CLEAN_DEBUFF)
    action.SetBranch(63)
    g_AIDebugInfo[75] = '[75] CLEAN_DEBUFF()'

    -- ����ϵͳ�޵�
    action = ai.NewAction(63, AI_ACTION.SET_SYSTEM_SHEILD)
    action.SetParam(0)
    action.SetBranch(85)
    g_AIDebugInfo[63] = '[63] SET_SYSTEM_SHEILD(0)'

    -- ��������ʱ��
    action = ai.NewAction(49, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(6)
    action.SetBranch(102)
    g_AIDebugInfo[49] = '[49] SET_PRIMARY_TIMER(6)'

    -- ����״̬
    action = ai.NewAction(102, AI_ACTION.SET_STATE)
    action.SetParam(51) -- ׷��״̬
    g_AIDebugInfo[102] = '[102] SetParam(State51)'

    -- ׷��״̬
    state = ai.NewState(51)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 53)

    -- �ȽϷ��ص����
    action = ai.NewAction(53, AI_ACTION.RETURN_POSITION_DISTANCE_COMPARE)
    action.SetParam(param['AttackRange'])
    action.SetBranch(69, 40, 40)
    g_AIDebugInfo[53] = '[53] RETURN_POSITION_DISTANCE_COMPARE(param[AttackRange])'

    -- ѡ���¼�������
    action = ai.NewAction(23, AI_ACTION.SELECT_EVENT_SRC)
    action.SetBranch(25, 69)
    g_AIDebugInfo[23] = '[23] SELECT_EVENT_SRC()'

    ai.SetInitState(1)
end

-- ���Է���
function AI:DebugOnCallAction(action_id)
    Log('[AI] Call action: ' .. g_AIDebugInfo[action_id])
end

-- ��AIͼ���Զ���ű�
function AI:GetSelf(pNpc, actionData)
    -- �����Զ��嶯��ʵ�ֽű�
	pNpc.SetTarget(3,pNpc.dwId);
    return 1
end

