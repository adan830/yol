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
    ai.RegisterUserAction(2060, 'CustomAction60')

    -- ��ʼ
    state = ai.NewState(21)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 33)

    -- ��¼ԭ��
    action = ai.NewAction(33, AI_ACTION.RECORD_ORIGIN_POSITION)
    action.SetBranch(51)
    g_AIDebugInfo[33] = '[33] RECORD_ORIGIN_POSITION()'

    -- ѡ��״̬
    action = ai.NewAction(51, AI_ACTION.SELECT_STATE)
    action.SetParam(1)
    action.SetBranch(65, 23, 65)
    g_AIDebugInfo[51] = '[51] SELECT_STATE(1)'

    -- ��������ʱ��
    action = ai.NewAction(65, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(8)
    action.SetBranch(106)
    g_AIDebugInfo[65] = '[65] SET_PRIMARY_TIMER(8)'

    -- ����״̬
    action = ai.NewAction(106, AI_ACTION.SET_STATE)
    action.SetParam(32) -- ����״̬
    g_AIDebugInfo[106] = '[106] SetParam(State32)'

    -- ����״̬
    state = ai.NewState(32)
    state.HandleEvent(AI_EVENT.ON_SECONDARY_TIMER, 51)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 65)

    -- ˫ѡ�����
    action = ai.NewAction(23, AI_ACTION.RANDOM_BI_BRANCH)
    action.SetParam(5, 95)
    action.SetBranch(60, 34)
    g_AIDebugInfo[23] = '[23] RANDOM_BI_BRANCH(5, 95)'

    -- �й�һ��
    action = ai.NewAction(34, AI_ACTION.WANDER)
    action.SetParam(400, 600)
    action.SetBranch(43)
    g_AIDebugInfo[34] = '[34] WANDER(400, 600)'

    -- ���ø���ʱ��
    action = ai.NewAction(43, AI_ACTION.SET_SECONDARY_TIMER)
    action.SetParam(48)
    action.SetBranch(108)
    g_AIDebugInfo[43] = '[43] SET_SECONDARY_TIMER(48)'

    -- ����״̬
    action = ai.NewAction(108, AI_ACTION.SET_STATE)
    action.SetParam(32) -- ����״̬
    g_AIDebugInfo[108] = '[108] SetParam(State32)'

    -- NPC����
    action = ai.NewAction(60, 2060)
    action.SetBranch(54)
    g_AIDebugInfo[60] = '[60] CustomAction60()'

    -- ��������ʱ��
    action = ai.NewAction(54, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(0)
    action.SetBranch(110)
    g_AIDebugInfo[54] = '[54] SET_PRIMARY_TIMER(0)'

    -- ����״̬
    action = ai.NewAction(110, AI_ACTION.SET_STATE)
    action.SetParam(40) -- ��������
    g_AIDebugInfo[110] = '[110] SetParam(State40)'

    -- ��������
    state = ai.NewState(40)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 34)

    ai.SetInitState(21)
end

-- ���Է���
function AI:DebugOnCallAction(nActiondId, nAIType)
    print('[AI] Call action: ' .. AI[nAIType][nActiondId])
end

-- ��AIͼ���Զ���ű�
function AI:CustomAction60(pNpc, ai)
    -- �����Զ��嶯��ʵ�ֽű�
	local param = AI.g_AIParam[ai.nAIType]
    Dialog:NpcBubbleToNearBy(pNpc.dwId, param.Shout1)
    return 1
end

