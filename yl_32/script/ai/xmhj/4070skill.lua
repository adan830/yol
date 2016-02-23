-- ��д�ߣ�chenkangyin
-- �汾�ţ�1

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
    ai.RegisterUserAction(2008, 'AI:GetSkillAction4070')

    -- ��ʼ
    state = ai.NewState(2)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 11)

    -- ��������ʱ��
    action = ai.NewAction(11, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(4)
    action.SetBranch(15)
    g_AIDebugInfo[11] = '[11] SET_PRIMARY_TIMER(4)'

    -- ����״̬
    action = ai.NewAction(15, AI_ACTION.SET_STATE)
    action.SetParam(5) -- ����
    g_AIDebugInfo[15] = '[15] SetParam(State5)'

    -- ����
    state = ai.NewState(5)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 8)

    -- ѡ���Լ�
    action = ai.NewAction(8, 2008)
    action.SetBranch(9)
    g_AIDebugInfo[8] = '[8] AI:GetSkillAction4070()'

    -- �ͷż���
    action = ai.NewAction(9, AI_ACTION.CAST_SKILL)
    action.SetParam(4070, 1)
    action.SetBranch(19, 17)
    g_AIDebugInfo[9] = '[9] CAST_SKILL(4070, 1)'

    -- ����״̬
    action = ai.NewAction(17, AI_ACTION.SET_STATE)
    action.SetParam(4) -- ״̬
    g_AIDebugInfo[17] = '[17] SetParam(State4)'

    -- ״̬
    state = ai.NewState(4)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 7)

    -- ����״̬
    action = ai.NewAction(7, AI_ACTION.SET_STATE)
    action.SetParam(4)
    g_AIDebugInfo[7] = '[7] SET_STATE(4)'

    -- ����״̬
    action = ai.NewAction(19, AI_ACTION.SET_STATE)
    action.SetParam(4) -- ״̬
    g_AIDebugInfo[19] = '[19] SetParam(State4)'

    ai.SetInitState(2)
end

-- ���Է���
function AI:DebugOnCallAction(nActiondId, nAIType)
    print('[AI] Call action: ' .. AI[nAIType][nActiondId])
end

-- ��AIͼ���Զ���ű�
function AI:GetSkillAction4070(pNpc, actionData)
    -- �����Զ��嶯��ʵ�ֽű�
	pNpc.SetTarget(3,pNpc.dwId);
    return 1
end

