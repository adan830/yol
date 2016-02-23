-- ��д�ߣ�hejingxian
-- �汾�ţ�20

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
    state = ai.NewState(1)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 20)

    -- ��¼ԭ��
    action = ai.NewAction(20, AI_ACTION.RECORD_ORIGIN_POSITION)
    action.SetBranch(22)
    g_AIDebugInfo[20] = '[20] RECORD_ORIGIN_POSITION()'

    -- ��������ʱ��
    action = ai.NewAction(22, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(4)
    action.SetBranch(36)
    g_AIDebugInfo[22] = '[22] SET_PRIMARY_TIMER(4)'

    -- ����״̬
    action = ai.NewAction(36, AI_ACTION.SET_STATE)
    action.SetParam(16) -- ����
    g_AIDebugInfo[36] = '[36] SetParam(State16)'

    -- ����
    state = ai.NewState(16)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 3)

    -- վ��
    action = ai.NewAction(3, AI_ACTION.STAND)
    action.SetBranch(9)
    g_AIDebugInfo[3] = '[3] STAND()'

    -- ��������
    action = ai.NewAction(9, AI_ACTION.SEARCH_ENEMY)
    action.SetParam(param['AlertRange'])
    action.SetBranch(24, 24)
    g_AIDebugInfo[9] = '[9] SEARCH_ENEMY(param[AlertRange])'

    -- ��Ŀ����ӵ���в�б�
    action = ai.NewAction(24, AI_ACTION.ADD_TARGET_TO_THREAT_LIST)
    action.SetBranch(32)
    g_AIDebugInfo[24] = '[24] ADD_TARGET_TO_THREAT_LIST()'

    -- ��������ʱ��
    action = ai.NewAction(32, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(4)
    action.SetBranch(38)
    g_AIDebugInfo[32] = '[32] SET_PRIMARY_TIMER(4)'

    -- ����״̬
    action = ai.NewAction(38, AI_ACTION.SET_STATE)
    action.SetParam(33) -- ���빥��״̬
    g_AIDebugInfo[38] = '[38] SetParam(State33)'

    -- ���빥��״̬
    state = ai.NewState(33)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 25)

    -- ѡ���һ��в
    action = ai.NewAction(25, AI_ACTION.SELECT_FIRST_THREAT)
    action.SetBranch(13, 13)
    g_AIDebugInfo[25] = '[25] SELECT_FIRST_THREAT()'

    -- Npc��׼����ѡ��
    action = ai.NewAction(13, AI_ACTION.NPC_STANDARD_SKILL_SELECTOR)
    action.SetBranch(18, 18)
    g_AIDebugInfo[13] = '[13] NPC_STANDARD_SKILL_SELECTOR()'

    -- Npc�ͷ�ѡ������
    action = ai.NewAction(18, AI_ACTION.NPC_CAST_SELECT_SKILL)
    action.SetBranch(11, 32)
    g_AIDebugInfo[18] = '[18] NPC_CAST_SELECT_SKILL()'

    -- ��������ʱ��
    action = ai.NewAction(11, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(32)
    action.SetBranch(40)
    g_AIDebugInfo[11] = '[11] SET_PRIMARY_TIMER(32)'

    -- ����״̬
    action = ai.NewAction(40, AI_ACTION.SET_STATE)
    action.SetParam(4) -- �ͷż��ܽ���
    g_AIDebugInfo[40] = '[40] SetParam(State4)'

    -- �ͷż��ܽ���
    state = ai.NewState(4)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 13)

    ai.SetInitState(1)
end

-- ���Է���
function AI:DebugOnCallAction(nActiondId, nAIType)
    print('[AI] Call action: ' .. AI[nAIType][nActiondId])
end
