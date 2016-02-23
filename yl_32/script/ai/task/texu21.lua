-- ��д�ߣ�hejingxian
-- �汾�ţ�2

Include('script/ai/customfunctions.lua')
Include('script/ai/ai_param.lua')
Include('script/ai/argumentstrings.lua')

local g_AIDebugInfo = {}

function AI:Setup(ai)
    local state
    local action
    local param = AI.g_AIParam[ai.nAIType]
    AI[ai.nAIType] = g_AIDebugInfo

    -- ע���Զ��嶯��

    -- ��ʼ
    state = ai.NewState(48)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 31)

    -- ��¼ԭ��
    action = ai.NewAction(31, AI_ACTION.RECORD_ORIGIN_POSITION)
    action.SetBranch(41)
    g_AIDebugInfo[31] = '[31] RECORD_ORIGIN_POSITION()'

    -- ��������ʱ��
    action = ai.NewAction(41, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(1)
    action.SetBranch(79)
    g_AIDebugInfo[41] = '[41] SET_PRIMARY_TIMER(1)'

    -- ����״̬
    action = ai.NewAction(79, AI_ACTION.SET_STATE)
    action.SetParam(22) -- ����״̬
    g_AIDebugInfo[79] = '[79] SetParam(State22)'

    -- ����״̬
    state = ai.NewState(22)
    state.HandleEvent(AI_EVENT.ON_ATTACKED, 78)

    -- ��������
    action = ai.NewAction(78, AI_ACTION.SEARCH_ENEMY)
    action.SetParam(param['AlertRange'])
    action.SetBranch(57, 37)
    g_AIDebugInfo[78] = '[78] SEARCH_ENEMY(param[AlertRange])'

    -- ��Ŀ����ӵ���в�б�
    action = ai.NewAction(57, AI_ACTION.ADD_TARGET_TO_THREAT_LIST)
    action.SetBranch(7)
    g_AIDebugInfo[57] = '[57] ADD_TARGET_TO_THREAT_LIST()'

    -- ��¼���ص�
    action = ai.NewAction(7, AI_ACTION.RECORD_RETURN_POSITION)
    action.SetBranch(5)
    g_AIDebugInfo[7] = '[7] RECORD_RETURN_POSITION()'

    -- Npc��ʼ������CD
    action = ai.NewAction(5, AI_ACTION.NPC_INIT_SKILL_CD)
    action.SetBranch(70)
    g_AIDebugInfo[5] = '[5] NPC_INIT_SKILL_CD()'

    -- ��������ʱ��
    action = ai.NewAction(70, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(1)
    action.SetBranch(81)
    g_AIDebugInfo[70] = '[70] SET_PRIMARY_TIMER(1)'

    -- ����״̬
    action = ai.NewAction(81, AI_ACTION.SET_STATE)
    action.SetParam(19) -- ս��״̬
    g_AIDebugInfo[81] = '[81] SetParam(State19)'

    -- ս��״̬
    state = ai.NewState(19)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 8)

    -- ѡ���һ��в
    action = ai.NewAction(8, AI_ACTION.SELECT_FIRST_THREAT)
    action.SetBranch(49, 37)
    g_AIDebugInfo[8] = '[8] SELECT_FIRST_THREAT()'

    -- ����ϵͳ�޵�
    action = ai.NewAction(37, AI_ACTION.SET_SYSTEM_SHEILD)
    action.SetParam(1)
    action.SetBranch(63)
    g_AIDebugInfo[37] = '[37] SET_SYSTEM_SHEILD(1)'

    -- ����
    action = ai.NewAction(63, AI_ACTION.RETURN)
    action.SetParam(0)
    action.SetBranch(2, 2)
    g_AIDebugInfo[63] = '[63] RETURN(0)'

    -- ��������ʱ��
    action = ai.NewAction(2, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(8)
    action.SetBranch(83)
    g_AIDebugInfo[2] = '[2] SET_PRIMARY_TIMER(8)'

    -- ����״̬
    action = ai.NewAction(83, AI_ACTION.SET_STATE)
    action.SetParam(68) -- �޵з���״̬
    g_AIDebugInfo[83] = '[83] SetParam(State68)'

    -- �޵з���״̬
    state = ai.NewState(68)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 38)
    state.HandleEvent(AI_EVENT.ON_PATH_FAILED, 38)

    -- ����
    action = ai.NewAction(38, AI_ACTION.RETURN)
    action.SetParam(1)
    action.SetBranch(14, 14)
    g_AIDebugInfo[38] = '[38] RETURN(1)'

    -- ��������ʱ��
    action = ai.NewAction(14, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(8)
    action.SetBranch(85)
    g_AIDebugInfo[14] = '[14] SET_PRIMARY_TIMER(8)'

    -- ����״̬
    action = ai.NewAction(85, AI_ACTION.SET_STATE)
    action.SetParam(46) -- ���سɹ�
    g_AIDebugInfo[85] = '[85] SetParam(State46)'

    -- ���سɹ�
    state = ai.NewState(46)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 53)

    -- ���DEBUFF
    action = ai.NewAction(53, AI_ACTION.CLEAN_DEBUFF)
    action.SetBranch(12)
    g_AIDebugInfo[53] = '[53] CLEAN_DEBUFF()'

    -- ����ϵͳ�޵�
    action = ai.NewAction(12, AI_ACTION.SET_SYSTEM_SHEILD)
    action.SetParam(0)
    action.SetBranch(41)
    g_AIDebugInfo[12] = '[12] SET_SYSTEM_SHEILD(0)'

    -- Npc��׼����ѡ��
    action = ai.NewAction(49, AI_ACTION.NPC_STANDARD_SKILL_SELECTOR)
    action.SetBranch(50, 70)
    g_AIDebugInfo[49] = '[49] NPC_STANDARD_SKILL_SELECTOR()'

    -- Npc���ּ����ͷž���
    action = ai.NewAction(50, AI_ACTION.NPC_KEEP_SKILL_CAST_RANGE)
    action.SetBranch(6, 15)
    g_AIDebugInfo[50] = '[50] NPC_KEEP_SKILL_CAST_RANGE()'

    -- ��������ʱ��
    action = ai.NewAction(15, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(0)
    action.SetBranch(87)
    g_AIDebugInfo[15] = '[15] SET_PRIMARY_TIMER(0)'

    -- ����״̬
    action = ai.NewAction(87, AI_ACTION.SET_STATE)
    action.SetParam(47) -- ׷��״̬
    g_AIDebugInfo[87] = '[87] SetParam(State47)'

    -- ׷��״̬
    state = ai.NewState(47)
    state.HandleEvent(AI_EVENT.ON_ATTACKED, 23)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 21)
    state.HandleEvent(AI_EVENT.ON_CAST_SKILL_FAILED, 41)

    -- ѡ���¼�������
    action = ai.NewAction(23, AI_ACTION.SELECT_EVENT_SRC)
    action.SetBranch(21, 21)
    g_AIDebugInfo[23] = '[23] SELECT_EVENT_SRC()'

    -- �ȽϷ��ص����
    action = ai.NewAction(21, AI_ACTION.RETURN_POSITION_DISTANCE_COMPARE)
    action.SetParam(param['EscapeRange'])
    action.SetBranch(37, 50, 50)
    g_AIDebugInfo[21] = '[21] RETURN_POSITION_DISTANCE_COMPARE(param[EscapeRange])'

    -- Npc�ͷ�ѡ������
    action = ai.NewAction(6, AI_ACTION.NPC_CAST_SELECT_SKILL)
    action.SetBranch(70, 67)
    g_AIDebugInfo[6] = '[6] NPC_CAST_SELECT_SKILL()'

    -- ��鼼��ʧ�ܼ���
    action = ai.NewAction(67, AI_ACTION.CHECK_SKILL_FAILED_COUNTER)
    action.SetParam(5)
    action.SetBranch(8, 37)
    g_AIDebugInfo[67] = '[67] CHECK_SKILL_FAILED_COUNTER(5)'

    ai.SetInitState(48)
end

-- ���Է���
function AI:DebugOnCallAction(nActiondId, nAIType)
    print('[AI] Call action: ' .. AI[nAIType][nActiondId])
end
