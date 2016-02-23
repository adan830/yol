-- ��д�ߣ�hejingxian
-- �汾�ţ�9

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
    ai.RegisterUserAction(2045, 'CustomAction45')

    -- ��ʼ
    state = ai.NewState(49)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 71)

    -- ����Ѳ��·��
    action = ai.NewAction(71, AI_ACTION.ENTER_PATROL_PATH)
    action.SetParam(param['PatrolPathID'], param['PatrolOrderIndex'])
    action.SetBranch(73)
    g_AIDebugInfo[71] = '[71] ENTER_PATROL_PATH(param[PatrolPathID], param[PatrolOrderIndex])'

    -- Ѳ��
    action = ai.NewAction(73, AI_ACTION.DO_PATROL)
    action.SetBranch(67, 45)
    g_AIDebugInfo[73] = '[73] DO_PATROL()'

    -- ѡ���Լ�
    action = ai.NewAction(45, 2045)
    action.SetBranch(56)
    g_AIDebugInfo[45] = '[45] CustomAction45()'

    -- �ͷż���
    action = ai.NewAction(56, AI_ACTION.CAST_SKILL)
    action.SetParam(429, 1)
    action.SetBranch(76, 45)
    g_AIDebugInfo[56] = '[56] CAST_SKILL(429, 1)'

    -- ����״̬
    action = ai.NewAction(76, AI_ACTION.SET_STATE)
    action.SetParam(75) -- ��ɱ
    g_AIDebugInfo[76] = '[76] SetParam(State75)'

    -- ��ɱ
    state = ai.NewState(75)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 47)

    -- ����״̬
    action = ai.NewAction(47, AI_ACTION.SET_STATE)
    action.SetParam(4)
    g_AIDebugInfo[47] = '[47] SET_STATE(4)'

    -- ��������ʱ��
    action = ai.NewAction(67, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(4)
    action.SetBranch(78)
    g_AIDebugInfo[67] = '[67] SET_PRIMARY_TIMER(4)'

    -- ����״̬
    action = ai.NewAction(78, AI_ACTION.SET_STATE)
    action.SetParam(57) -- ����
    g_AIDebugInfo[78] = '[78] SetParam(State57)'

    -- ����
    state = ai.NewState(57)
    state.HandleEvent(AI_EVENT.ON_PATH_FAILED, 73)
    state.HandleEvent(AI_EVENT.ON_SECONDARY_TIMER, 73)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 64)
    state.HandleEvent(AI_EVENT.ON_PATH_SUCCESS, 55)

    -- ��������
    action = ai.NewAction(64, AI_ACTION.SEARCH_ENEMY)
    action.SetParam(param['AlertRange'])
    action.SetBranch(69, 67)
    g_AIDebugInfo[64] = '[64] SEARCH_ENEMY(param[AlertRange])'

    -- ��������ʱ��
    action = ai.NewAction(69, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(1)
    action.SetBranch(80)
    g_AIDebugInfo[69] = '[69] SET_PRIMARY_TIMER(1)'

    -- ����״̬
    action = ai.NewAction(80, AI_ACTION.SET_STATE)
    action.SetParam(61) -- ���Լ��ż���
    g_AIDebugInfo[80] = '[80] SetParam(State61)'

    -- ���Լ��ż���
    state = ai.NewState(61)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 45)

    -- ���ø���ʱ��
    action = ai.NewAction(55, AI_ACTION.SET_SECONDARY_TIMER)
    action.SetParam(4)
    action.SetBranch(67)
    g_AIDebugInfo[55] = '[55] SET_SECONDARY_TIMER(4)'

    ai.SetInitState(49)
end

-- ���Է���
function AI:DebugOnCallAction(nActiondId, nAIType)
    print('[AI] Call action: ' .. AI[nAIType][nActiondId])
end

-- ��AIͼ���Զ���ű�
function AI:CustomAction45(pNpc, actionData)
    -- �����Զ��嶯��ʵ�ֽű�
	pNpc.SetTarget(3,pNpc.dwId);
    return 1
end

