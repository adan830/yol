-- ��д�ߣ�hejingxian
-- �汾�ţ�18

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
    ai.RegisterUserAction(2038, 'AI:CustomAction38')

    -- ��ʼ
    state = ai.NewState(17)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 24)

    -- ����Ѳ��·��
    action = ai.NewAction(24, AI_ACTION.ENTER_PATROL_PATH)
    action.SetParam(param['PatrolPathID'], param['PatrolOrderIndex'])
    action.SetBranch(25)
    g_AIDebugInfo[24] = '[24] ENTER_PATROL_PATH(param[PatrolPathID], param[PatrolOrderIndex])'

    -- Ѳ��
    action = ai.NewAction(25, AI_ACTION.DO_PATROL)
    action.SetBranch(18, 38)
    g_AIDebugInfo[25] = '[25] DO_PATROL()'

    -- ��������ʱ��
    action = ai.NewAction(18, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(4)
    action.SetBranch(59)
    g_AIDebugInfo[18] = '[18] SET_PRIMARY_TIMER(4)'

    -- ����״̬
    action = ai.NewAction(59, AI_ACTION.SET_STATE)
    action.SetParam(1) -- ����
    g_AIDebugInfo[59] = '[59] SetParam(State1)'

    -- ����
    state = ai.NewState(1)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 16)
    state.HandleEvent(AI_EVENT.ON_PATH_SUCCESS, 27)
    state.HandleEvent(AI_EVENT.ON_SECONDARY_TIMER, 25)
    state.HandleEvent(AI_EVENT.ON_PATH_FAILED, 25)

    -- ��������
    action = ai.NewAction(16, AI_ACTION.SEARCH_ENEMY)
    action.SetParam(param['AlertRange'])
    action.SetBranch(42, 18)
    g_AIDebugInfo[16] = '[16] SEARCH_ENEMY(param[AlertRange])'

    -- ��������ʱ��
    action = ai.NewAction(42, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(1)
    action.SetBranch(61)
    g_AIDebugInfo[42] = '[42] SET_PRIMARY_TIMER(1)'

    -- ����״̬
    action = ai.NewAction(61, AI_ACTION.SET_STATE)
    action.SetParam(40) -- ���Լ��ż���
    g_AIDebugInfo[61] = '[61] SetParam(State40)'

    -- ���Լ��ż���
    state = ai.NewState(40)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 38)

    -- ѡ���Լ�
    action = ai.NewAction(38, 2038)
    action.SetBranch(39)
    g_AIDebugInfo[38] = '[38] AI:CustomAction38()'

    -- �ͷż���
    action = ai.NewAction(39, AI_ACTION.CAST_SKILL)
    action.SetParam(369, 1)
    action.SetBranch(57, 38)
    g_AIDebugInfo[39] = '[39] CAST_SKILL(369, 1)'

    -- ��������ʱ��
    action = ai.NewAction(57, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(4)
    action.SetBranch(63)
    g_AIDebugInfo[57] = '[57] SET_PRIMARY_TIMER(4)'

    -- ����״̬
    action = ai.NewAction(63, AI_ACTION.SET_STATE)
    action.SetParam(55) -- ��ɱ
    g_AIDebugInfo[63] = '[63] SetParam(State55)'

    -- ��ɱ
    state = ai.NewState(55)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 54)

    -- ����״̬
    action = ai.NewAction(54, AI_ACTION.SET_STATE)
    action.SetParam(4)
    g_AIDebugInfo[54] = '[54] SET_STATE(4)'

    -- ���ø���ʱ��
    action = ai.NewAction(27, AI_ACTION.SET_SECONDARY_TIMER)
    action.SetParam(4)
    action.SetBranch(18)
    g_AIDebugInfo[27] = '[27] SET_SECONDARY_TIMER(4)'

    ai.SetInitState(17)
end

-- ���Է���
function AI:DebugOnCallAction(nActiondId, nAIType)
    print('[AI] Call action: ' .. AI[nAIType][nActiondId])
end

-- ��AIͼ���Զ���ű�
function AI:CustomAction38(pNpc, actionData)
    -- �����Զ��嶯��ʵ�ֽű�
	pNpc.SetTarget(3,pNpc.dwId);
    return 1
end

