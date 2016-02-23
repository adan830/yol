-- ��д�ߣ�hejingxian
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
    ai.RegisterUserAction(2001, 'CustomAction1')
    ai.RegisterUserAction(2002, 'CustomAction2')

    -- ��ʼ
    state = ai.NewState(21)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 8)

    -- ��������ʱ��
    action = ai.NewAction(8, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(0)
    action.SetBranch(27)
    g_AIDebugInfo[8] = '[8] SET_PRIMARY_TIMER(0)'

    -- ����״̬
    action = ai.NewAction(27, AI_ACTION.SET_STATE)
    action.SetParam(11) -- ����
    g_AIDebugInfo[27] = '[27] SetParam(State11)'

    -- ����
    state = ai.NewState(11)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 1)

    -- ѡ���Լ�
    action = ai.NewAction(1, 2001)
    action.SetBranch(17)
    g_AIDebugInfo[1] = '[1] CustomAction1()'

    -- Npc��׼����ѡ��
    action = ai.NewAction(17, AI_ACTION.NPC_STANDARD_SKILL_SELECTOR)
    action.SetBranch(4, 4)
    g_AIDebugInfo[17] = '[17] NPC_STANDARD_SKILL_SELECTOR()'

    -- Npc�ͷ�ѡ������
    action = ai.NewAction(4, AI_ACTION.NPC_CAST_SELECT_SKILL)
    action.SetBranch(29, 33)
    g_AIDebugInfo[4] = '[4] NPC_CAST_SELECT_SKILL()'

    -- ����״̬
    action = ai.NewAction(29, AI_ACTION.SET_STATE)
    action.SetParam(9) -- ����
    g_AIDebugInfo[29] = '[29] SetParam(State9)'

    -- ����
    state = ai.NewState(9)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 10)

    -- ��������ʱ��
    action = ai.NewAction(10, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(64)
    action.SetBranch(2)
    g_AIDebugInfo[10] = '[10] SET_PRIMARY_TIMER(64)'

    -- ѡ���Լ�
    action = ai.NewAction(2, 2002)
    action.SetBranch(22)
    g_AIDebugInfo[2] = '[2] CustomAction2()'

    -- �ͷż���
    action = ai.NewAction(22, AI_ACTION.CAST_SKILL)
    action.SetParam(1116, 1)
    action.SetBranch(31, 10)
    g_AIDebugInfo[22] = '[22] CAST_SKILL(1116, 1)'

    -- ����״̬
    action = ai.NewAction(31, AI_ACTION.SET_STATE)
    action.SetParam(14) -- ����
    g_AIDebugInfo[31] = '[31] SetParam(State14)'

    -- ����
    state = ai.NewState(14)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 20)

    -- ����״̬
    action = ai.NewAction(20, AI_ACTION.SET_STATE)
    action.SetParam(4)
    g_AIDebugInfo[20] = '[20] SET_STATE(4)'

    -- ����״̬
    action = ai.NewAction(33, AI_ACTION.SET_STATE)
    action.SetParam(9) -- ����
    g_AIDebugInfo[33] = '[33] SetParam(State9)'

    ai.SetInitState(21)
end

-- ���Է���
function AI:DebugOnCallAction(nActiondId, nAIType)
    print('[AI] Call action: ' .. AI[nAIType][nActiondId])
end

-- ��AIͼ���Զ���ű�
function AI:CustomAction1(pNpc, actionData)
    -- �����Զ��嶯��ʵ�ֽű�
	pNpc.SetTarget(3,pNpc.dwId);
    return 1
end

function AI:CustomAction2(pNpc, actionData)
    -- �����Զ��嶯��ʵ�ֽű�
	pNpc.SetTarget(3,pNpc.dwId);
    return 1
end

