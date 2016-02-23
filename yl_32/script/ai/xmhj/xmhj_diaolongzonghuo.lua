-- ��д�ߣ�chenkangyin
-- �汾�ţ�6

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
    ai.RegisterUserAction(2018, 'AI:GetFangHuoren')

    -- ��ʼ
    state = ai.NewState(1)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 2)

    -- ��������ʱ��
    action = ai.NewAction(2, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(4)
    action.SetBranch(20)
    g_AIDebugInfo[2] = '[2] SET_PRIMARY_TIMER(4)'

    -- ����״̬
    action = ai.NewAction(20, AI_ACTION.SET_STATE)
    action.SetParam(4) -- ����
    g_AIDebugInfo[20] = '[20] SetParam(State4)'

    -- ����
    state = ai.NewState(4)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 18)

    -- ѡ���Լ�
    action = ai.NewAction(18, 2018)
    action.SetBranch(14)
    g_AIDebugInfo[18] = '[18] AI:GetFangHuoren()'

    -- �ͷż���
    action = ai.NewAction(14, AI_ACTION.CAST_SKILL)
    action.SetParam(739, 1)
    action.SetBranch(15, 15)
    g_AIDebugInfo[14] = '[14] CAST_SKILL(739, 1)'

    -- ����״̬
    action = ai.NewAction(15, AI_ACTION.SET_STATE)
    action.SetParam(1)
    g_AIDebugInfo[15] = '[15] SET_STATE(1)'

    ai.SetInitState(1)
end

-- ���Է���
function AI:DebugOnCallAction(nActiondId, nAIType)
    print('[AI] Call action: ' .. AI[nAIType][nActiondId])
end

-- ��AIͼ���Զ���ű�
function AI:GetFangHuoren(pNpc, actionData)
    -- �����Զ��嶯��ʵ�ֽű�
	pNpc.SetTarget(3,pNpc.dwId);
    return 1
end

