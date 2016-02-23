-- ��д�ߣ�hejingxian
-- �汾�ţ�14

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
    ai.RegisterUserAction(2003, 'AI:CustomAction3')

    -- ��ʼ
    state = ai.NewState(12)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 6)

    -- ��������ʱ��
    action = ai.NewAction(6, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(4)
    action.SetBranch(42)
    g_AIDebugInfo[6] = '[6] SET_PRIMARY_TIMER(4)'

    -- ����״̬
    action = ai.NewAction(42, AI_ACTION.SET_STATE)
    action.SetParam(2) -- ����
    g_AIDebugInfo[42] = '[42] SetParam(State2)'

    -- ����
    state = ai.NewState(2)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 3)

    -- ѡ���Լ�
    action = ai.NewAction(3, 2003)
    action.SetBranch(26)
    g_AIDebugInfo[3] = '[3] AI:CustomAction3()'

    -- �ͷż���
    action = ai.NewAction(26, AI_ACTION.CAST_SKILL)
    action.SetParam(351, 1)
    action.SetBranch(40, 40)
    g_AIDebugInfo[26] = '[26] CAST_SKILL(351, 1)'

    -- ��������ʱ��
    action = ai.NewAction(40, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(48)
    action.SetBranch(44)
    g_AIDebugInfo[40] = '[40] SET_PRIMARY_TIMER(48)'

    -- ����״̬
    action = ai.NewAction(44, AI_ACTION.SET_STATE)
    action.SetParam(30) -- ״̬
    g_AIDebugInfo[44] = '[44] SetParam(State30)'

    -- ״̬
    state = ai.NewState(30)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 6)

    ai.SetInitState(12)
end

-- ���Է���
function AI:DebugOnCallAction(nActiondId, nAIType)
    print('[AI] Call action: ' .. AI[nAIType][nActiondId])
end

-- ��AIͼ���Զ���ű�
function AI:CustomAction3(pNpc, actionData)
    -- �����Զ��嶯��ʵ�ֽű�
	pNpc.SetTarget(3,pNpc.dwId);
    return 1
end

