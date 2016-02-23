-- ��д�ߣ�chenkangyin
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
    ai.RegisterUserAction(2007, 'AI:GetHonghulu')

    -- ��ʼ
    state = ai.NewState(3)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 2)

    -- ��������ʱ��
    action = ai.NewAction(2, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(4)
    action.SetBranch(15)
    g_AIDebugInfo[2] = '[2] SET_PRIMARY_TIMER(4)'

    -- ����״̬
    action = ai.NewAction(15, AI_ACTION.SET_STATE)
    action.SetParam(5) -- ����
    g_AIDebugInfo[15] = '[15] SetParam(State5)'

    -- ����
    state = ai.NewState(5)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 7)

    -- ���«�Լ�
    action = ai.NewAction(7, 2007)
    action.SetBranch(8)
    g_AIDebugInfo[7] = '[7] AI:GetHonghulu()'

    -- �ͷż���
    action = ai.NewAction(8, AI_ACTION.CAST_SKILL)
    action.SetParam(599, 1)
    action.SetBranch(17, 19)
    g_AIDebugInfo[8] = '[8] CAST_SKILL(599, 1)'

    -- ����״̬
    action = ai.NewAction(17, AI_ACTION.SET_STATE)
    action.SetParam(13) -- ״̬
    g_AIDebugInfo[17] = '[17] SetParam(State13)'

    -- ״̬
    state = ai.NewState(13)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 10)

    -- ����״̬
    action = ai.NewAction(10, AI_ACTION.SET_STATE)
    action.SetParam(13)
    g_AIDebugInfo[10] = '[10] SET_STATE(13)'

    -- ����״̬
    action = ai.NewAction(19, AI_ACTION.SET_STATE)
    action.SetParam(13) -- ״̬
    g_AIDebugInfo[19] = '[19] SetParam(State13)'

    ai.SetInitState(3)
end

-- ���Է���
function AI:DebugOnCallAction(nActiondId, nAIType)
    print('[AI] Call action: ' .. AI[nAIType][nActiondId])
end

-- ��AIͼ���Զ���ű�
function AI:GetHonghulu(pNpc, actionData)
    -- �����Զ��嶯��ʵ�ֽű�
	pNpc.SetTarget(3,pNpc.dwId);
    return 1
end


