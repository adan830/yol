-- ��д�ߣ�hejingxian
-- �汾�ţ�3

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
    ai.RegisterUserAction(2171, 'CustomAction171')

    -- ��ʼ
    state = ai.NewState(172)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 177)

    -- ��������ʱ��
    action = ai.NewAction(177, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(60)
    action.SetBranch(178)
    g_AIDebugInfo[177] = '[177] SET_PRIMARY_TIMER(60)'

    -- ����״̬
    action = ai.NewAction(178, AI_ACTION.SET_STATE)
    action.SetParam(168) -- ����
    g_AIDebugInfo[178] = '[178] SetParam(State168)'

    -- ����
    state = ai.NewState(168)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 171)

    -- NPC���
    action = ai.NewAction(171, 2171)
    action.SetBranch(180)
    g_AIDebugInfo[171] = '[171] CustomAction171()'

    -- ����״̬
    action = ai.NewAction(180, AI_ACTION.SET_STATE)
    action.SetParam(169) -- ״̬
    g_AIDebugInfo[180] = '[180] SetParam(State169)'

    -- ״̬
    state = ai.NewState(169)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 173)

    -- ����״̬
    action = ai.NewAction(173, AI_ACTION.SET_STATE)
    action.SetParam(4)
    g_AIDebugInfo[173] = '[173] SET_STATE(4)'

    ai.SetInitState(172)
end

-- ���Է���
function AI:DebugOnCallAction(nActiondId, nAIType)
    print('[AI] Call action: ' .. AI[nAIType][nActiondId])
end

-- ��AIͼ���Զ���ű�
function AI:CustomAction171(pNpc, ai)
    -- �����Զ��嶯��ʵ�ֽű�
    Dialog:StartScaleAnimationToNearBy(pNpc.dwId,170)
    return 1
end

