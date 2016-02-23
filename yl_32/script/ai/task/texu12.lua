-- ��д�ߣ�hejingxian
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

    -- ��ʼ
    state = ai.NewState(2)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 13)

    -- ��¼ԭ��
    action = ai.NewAction(13, AI_ACTION.RECORD_ORIGIN_POSITION)
    action.SetBranch(7)
    g_AIDebugInfo[13] = '[13] RECORD_ORIGIN_POSITION()'

    -- ��������ʱ��
    action = ai.NewAction(7, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(4)
    action.SetBranch(33)
    g_AIDebugInfo[7] = '[7] SET_PRIMARY_TIMER(4)'

    -- ����״̬
    action = ai.NewAction(33, AI_ACTION.SET_STATE)
    action.SetParam(8) -- ����
    g_AIDebugInfo[33] = '[33] SetParam(State8)'

    -- ����
    state = ai.NewState(8)
    state.HandleEvent(AI_EVENT.ON_ATTACKED, 4)
    state.HandleEvent(AI_EVENT.ON_SELF_KILLED, 4)

    -- վ��
    action = ai.NewAction(4, AI_ACTION.STAND)
    action.SetBranch(30)
    g_AIDebugInfo[4] = '[4] STAND()'

    -- ��������
    action = ai.NewAction(30, AI_ACTION.SEARCH_ENEMY)
    action.SetParam(param['AlertRange'])
    action.SetBranch(6, 6)
    g_AIDebugInfo[30] = '[30] SEARCH_ENEMY(param[AlertRange])'

    -- Npc��׼����ѡ��
    action = ai.NewAction(6, AI_ACTION.NPC_STANDARD_SKILL_SELECTOR)
    action.SetBranch(15, 7)
    g_AIDebugInfo[6] = '[6] NPC_STANDARD_SKILL_SELECTOR()'

    -- Npc�ͷ�ѡ������
    action = ai.NewAction(15, AI_ACTION.NPC_CAST_SELECT_SKILL)
    action.SetBranch(7, 11)
    g_AIDebugInfo[15] = '[15] NPC_CAST_SELECT_SKILL()'

    -- ��������ʱ��
    action = ai.NewAction(11, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(32)
    action.SetBranch(35)
    g_AIDebugInfo[11] = '[11] SET_PRIMARY_TIMER(32)'

    -- ����״̬
    action = ai.NewAction(35, AI_ACTION.SET_STATE)
    action.SetParam(17) -- �ͷż��ܽ���
    g_AIDebugInfo[35] = '[35] SetParam(State17)'

    -- �ͷż��ܽ���
    state = ai.NewState(17)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 7)

    ai.SetInitState(2)
end

-- ���Է���
function AI:DebugOnCallAction(nActiondId, nAIType)
    print('[AI] Call action: ' .. AI[nAIType][nActiondId])
end
