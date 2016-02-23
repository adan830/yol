-- ��д�ߣ�hejingxian
-- �汾�ţ�8

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
    state = ai.NewState(22)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 2)

    -- ��¼ԭ��
    action = ai.NewAction(2, AI_ACTION.RECORD_ORIGIN_POSITION)
    action.SetBranch(65)
    g_AIDebugInfo[2] = '[2] RECORD_ORIGIN_POSITION()'

    -- ��������ʱ��
    action = ai.NewAction(65, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(8)
    action.SetBranch(90)
    g_AIDebugInfo[65] = '[65] SET_PRIMARY_TIMER(8)'

    -- ����״̬
    action = ai.NewAction(90, AI_ACTION.SET_STATE)
    action.SetParam(28) -- ����״̬
    g_AIDebugInfo[90] = '[90] SetParam(State28)'

    -- ����״̬
    state = ai.NewState(28)
    state.HandleEvent(AI_EVENT.ON_ATTACKED, 73)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 39)

    -- ѡ���¼�������
    action = ai.NewAction(73, AI_ACTION.SELECT_EVENT_SRC)
    action.SetBranch(81, 9)
    g_AIDebugInfo[73] = '[73] SELECT_EVENT_SRC()'

    -- ��Ŀ����ӵ���в�б�
    action = ai.NewAction(81, AI_ACTION.ADD_TARGET_TO_THREAT_LIST)
    action.SetBranch(76)
    g_AIDebugInfo[81] = '[81] ADD_TARGET_TO_THREAT_LIST()'

    -- ��¼���ص�
    action = ai.NewAction(76, AI_ACTION.RECORD_RETURN_POSITION)
    action.SetBranch(36)
    g_AIDebugInfo[76] = '[76] RECORD_RETURN_POSITION()'

    -- Npc��ʼ������CD
    action = ai.NewAction(36, AI_ACTION.NPC_INIT_SKILL_CD)
    action.SetBranch(5)
    g_AIDebugInfo[36] = '[36] NPC_INIT_SKILL_CD()'

    -- ��������ʱ��
    action = ai.NewAction(5, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(8)
    action.SetBranch(92)
    g_AIDebugInfo[5] = '[5] SET_PRIMARY_TIMER(8)'

    -- ����״̬
    action = ai.NewAction(92, AI_ACTION.SET_STATE)
    action.SetParam(37) -- ս��״̬
    g_AIDebugInfo[92] = '[92] SetParam(State37)'

    -- ս��״̬
    state = ai.NewState(37)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 33)

    -- ѡ���һ��в
    action = ai.NewAction(33, AI_ACTION.SELECT_FIRST_THREAT)
    action.SetBranch(49, 9)
    g_AIDebugInfo[33] = '[33] SELECT_FIRST_THREAT()'

    -- Npc��׼����ѡ��
    action = ai.NewAction(49, AI_ACTION.NPC_STANDARD_SKILL_SELECTOR)
    action.SetBranch(18, 5)
    g_AIDebugInfo[49] = '[49] NPC_STANDARD_SKILL_SELECTOR()'

    -- Npc�ͷ�ѡ������
    action = ai.NewAction(18, AI_ACTION.NPC_CAST_SELECT_SKILL)
    action.SetBranch(65, 89)
    g_AIDebugInfo[18] = '[18] NPC_CAST_SELECT_SKILL()'

    -- ��鼼��ʧ�ܼ���
    action = ai.NewAction(89, AI_ACTION.CHECK_SKILL_FAILED_COUNTER)
    action.SetParam(10000)
    action.SetBranch(5, 9)
    g_AIDebugInfo[89] = '[89] CHECK_SKILL_FAILED_COUNTER(10000)'

    -- ����ϵͳ�޵�
    action = ai.NewAction(9, AI_ACTION.SET_SYSTEM_SHEILD)
    action.SetParam(1)
    action.SetBranch(88)
    g_AIDebugInfo[9] = '[9] SET_SYSTEM_SHEILD(1)'

    -- ����
    action = ai.NewAction(88, AI_ACTION.RETURN)
    action.SetParam(0)
    action.SetBranch(16, 16)
    g_AIDebugInfo[88] = '[88] RETURN(0)'

    -- ��������ʱ��
    action = ai.NewAction(16, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(8)
    action.SetBranch(94)
    g_AIDebugInfo[16] = '[16] SET_PRIMARY_TIMER(8)'

    -- ����״̬
    action = ai.NewAction(94, AI_ACTION.SET_STATE)
    action.SetParam(50) -- �޵з���״̬
    g_AIDebugInfo[94] = '[94] SetParam(State50)'

    -- �޵з���״̬
    state = ai.NewState(50)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 29)
    state.HandleEvent(AI_EVENT.ON_PATH_FAILED, 29)

    -- ����
    action = ai.NewAction(29, AI_ACTION.RETURN)
    action.SetParam(1)
    action.SetBranch(64, 64)
    g_AIDebugInfo[29] = '[29] RETURN(1)'

    -- ��������ʱ��
    action = ai.NewAction(64, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(8)
    action.SetBranch(96)
    g_AIDebugInfo[64] = '[64] SET_PRIMARY_TIMER(8)'

    -- ����״̬
    action = ai.NewAction(96, AI_ACTION.SET_STATE)
    action.SetParam(25) -- ���سɹ�
    g_AIDebugInfo[96] = '[96] SetParam(State25)'

    -- ���سɹ�
    state = ai.NewState(25)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 6)

    -- ���DEBUFF
    action = ai.NewAction(6, AI_ACTION.CLEAN_DEBUFF)
    action.SetBranch(86)
    g_AIDebugInfo[6] = '[6] CLEAN_DEBUFF()'

    -- ����ϵͳ�޵�
    action = ai.NewAction(86, AI_ACTION.SET_SYSTEM_SHEILD)
    action.SetParam(0)
    action.SetBranch(65)
    g_AIDebugInfo[86] = '[86] SET_SYSTEM_SHEILD(0)'

    -- ��������
    action = ai.NewAction(39, AI_ACTION.SEARCH_ENEMY)
    action.SetParam(700)
    action.SetBranch(81, 65)
    g_AIDebugInfo[39] = '[39] SEARCH_ENEMY(700)'

    ai.SetInitState(22)
end

-- ���Է���
function AI:DebugOnCallAction(nActiondId, nAIType)
    print('[AI] Call action: ' .. AI[nAIType][nActiondId])
end
