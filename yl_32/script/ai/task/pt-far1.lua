-- ��д�ߣ�hejingxian
-- �汾�ţ�24

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
    state = ai.NewState(301)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 252)

    -- ��¼ԭ��
    action = ai.NewAction(252, AI_ACTION.RECORD_ORIGIN_POSITION)
    action.SetBranch(313)
    g_AIDebugInfo[252] = '[252] RECORD_ORIGIN_POSITION()'

    -- ��������ʱ��
    action = ai.NewAction(313, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(8)
    action.SetBranch(404)
    g_AIDebugInfo[313] = '[313] SET_PRIMARY_TIMER(8)'

    -- ����״̬
    action = ai.NewAction(404, AI_ACTION.SET_STATE)
    action.SetParam(260) -- ����״̬
    g_AIDebugInfo[404] = '[404] SetParam(State260)'

    -- ����״̬
    state = ai.NewState(260)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 262)
    state.HandleEvent(AI_EVENT.ON_ATTACKED, 309)

    -- ��������
    action = ai.NewAction(262, AI_ACTION.SEARCH_ENEMY)
    action.SetParam(700)
    action.SetBranch(254, 313)
    g_AIDebugInfo[262] = '[262] SEARCH_ENEMY(700)'

    -- ��Ŀ����ӵ���в�б�
    action = ai.NewAction(254, AI_ACTION.ADD_TARGET_TO_THREAT_LIST)
    action.SetBranch(318)
    g_AIDebugInfo[254] = '[254] ADD_TARGET_TO_THREAT_LIST()'

    -- ��¼���ص�
    action = ai.NewAction(318, AI_ACTION.RECORD_RETURN_POSITION)
    action.SetBranch(256)
    g_AIDebugInfo[318] = '[318] RECORD_RETURN_POSITION()'

    -- Npc��ʼ������CD
    action = ai.NewAction(256, AI_ACTION.NPC_INIT_SKILL_CD)
    action.SetBranch(281)
    g_AIDebugInfo[256] = '[256] NPC_INIT_SKILL_CD()'

    -- ��������ʱ��
    action = ai.NewAction(281, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(8)
    action.SetBranch(406)
    g_AIDebugInfo[281] = '[281] SET_PRIMARY_TIMER(8)'

    -- ����״̬
    action = ai.NewAction(406, AI_ACTION.SET_STATE)
    action.SetParam(288) -- ս��״̬
    g_AIDebugInfo[406] = '[406] SetParam(State288)'

    -- ս��״̬
    state = ai.NewState(288)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 249)

    -- ѡ���һ��в
    action = ai.NewAction(249, AI_ACTION.SELECT_FIRST_THREAT)
    action.SetBranch(269, 295)
    g_AIDebugInfo[249] = '[249] SELECT_FIRST_THREAT()'

    -- ����ϵͳ�޵�
    action = ai.NewAction(295, AI_ACTION.SET_SYSTEM_SHEILD)
    action.SetParam(1)
    action.SetBranch(283)
    g_AIDebugInfo[295] = '[295] SET_SYSTEM_SHEILD(1)'

    -- ����
    action = ai.NewAction(283, AI_ACTION.RETURN)
    action.SetParam(0)
    action.SetBranch(315, 315)
    g_AIDebugInfo[283] = '[283] RETURN(0)'

    -- ��������ʱ��
    action = ai.NewAction(315, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(8)
    action.SetBranch(408)
    g_AIDebugInfo[315] = '[315] SET_PRIMARY_TIMER(8)'

    -- ����״̬
    action = ai.NewAction(408, AI_ACTION.SET_STATE)
    action.SetParam(310) -- �޵з���״̬
    g_AIDebugInfo[408] = '[408] SetParam(State310)'

    -- �޵з���״̬
    state = ai.NewState(310)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 311)
    state.HandleEvent(AI_EVENT.ON_PATH_FAILED, 311)

    -- ����
    action = ai.NewAction(311, AI_ACTION.RETURN)
    action.SetParam(1)
    action.SetBranch(298, 298)
    g_AIDebugInfo[311] = '[311] RETURN(1)'

    -- ��������ʱ��
    action = ai.NewAction(298, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(8)
    action.SetBranch(410)
    g_AIDebugInfo[298] = '[298] SET_PRIMARY_TIMER(8)'

    -- ����״̬
    action = ai.NewAction(410, AI_ACTION.SET_STATE)
    action.SetParam(276) -- ���سɹ�
    g_AIDebugInfo[410] = '[410] SetParam(State276)'

    -- ���سɹ�
    state = ai.NewState(276)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 280)

    -- ���DEBUFF
    action = ai.NewAction(280, AI_ACTION.CLEAN_DEBUFF)
    action.SetBranch(277)
    g_AIDebugInfo[280] = '[280] CLEAN_DEBUFF()'

    -- ����ϵͳ�޵�
    action = ai.NewAction(277, AI_ACTION.SET_SYSTEM_SHEILD)
    action.SetParam(0)
    action.SetBranch(313)
    g_AIDebugInfo[277] = '[277] SET_SYSTEM_SHEILD(0)'

    -- Npc��׼����ѡ��
    action = ai.NewAction(269, AI_ACTION.NPC_STANDARD_SKILL_SELECTOR)
    action.SetBranch(305, 281)
    g_AIDebugInfo[269] = '[269] NPC_STANDARD_SKILL_SELECTOR()'

    -- ���־���
    action = ai.NewAction(305, AI_ACTION.KEEP_RANGE)
    action.SetParam(350, 450)
    action.SetBranch(247, 279)
    g_AIDebugInfo[305] = '[305] KEEP_RANGE(350, 450)'

    -- ��������ʱ��
    action = ai.NewAction(279, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(16)
    action.SetBranch(412)
    g_AIDebugInfo[279] = '[279] SET_PRIMARY_TIMER(16)'

    -- ����״̬
    action = ai.NewAction(412, AI_ACTION.SET_STATE)
    action.SetParam(248) -- ׷��״̬
    g_AIDebugInfo[412] = '[412] SetParam(State248)'

    -- ׷��״̬
    state = ai.NewState(248)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 293)
    state.HandleEvent(AI_EVENT.ON_TARGET_KILLED, 313)

    -- �ȽϷ��ص����
    action = ai.NewAction(293, AI_ACTION.RETURN_POSITION_DISTANCE_COMPARE)
    action.SetParam(10000)
    action.SetBranch(295, 247, 247)
    g_AIDebugInfo[293] = '[293] RETURN_POSITION_DISTANCE_COMPARE(10000)'

    -- Npc�ͷ�ѡ������
    action = ai.NewAction(247, AI_ACTION.NPC_CAST_SELECT_SKILL)
    action.SetBranch(281, 306)
    g_AIDebugInfo[247] = '[247] NPC_CAST_SELECT_SKILL()'

    -- ��鼼��ʧ�ܼ���
    action = ai.NewAction(306, AI_ACTION.CHECK_SKILL_FAILED_COUNTER)
    action.SetParam(100)
    action.SetBranch(249, 295)
    g_AIDebugInfo[306] = '[306] CHECK_SKILL_FAILED_COUNTER(100)'

    -- ѡ���¼�������
    action = ai.NewAction(309, AI_ACTION.SELECT_EVENT_SRC)
    action.SetBranch(254, 295)
    g_AIDebugInfo[309] = '[309] SELECT_EVENT_SRC()'

    ai.SetInitState(301)
end

-- ���Է���
function AI:DebugOnCallAction(nActiondId, nAIType)
    print('[AI] Call action: ' .. AI[nAIType][nActiondId])
end
