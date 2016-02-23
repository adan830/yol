-- ��д�ߣ�hejingxian
-- �汾�ţ�7

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
    ai.RegisterUserAction(2072, 'CustomAction72')

    -- ��ʼ
    state = ai.NewState(66)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 17)

    -- ��¼ԭ��
    action = ai.NewAction(17, AI_ACTION.RECORD_ORIGIN_POSITION)
    action.SetBranch(47)
    g_AIDebugInfo[17] = '[17] RECORD_ORIGIN_POSITION()'

    -- ��������ʱ��
    action = ai.NewAction(47, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(8)
    action.SetBranch(90)
    g_AIDebugInfo[47] = '[47] SET_PRIMARY_TIMER(8)'

    -- ����״̬
    action = ai.NewAction(90, AI_ACTION.SET_STATE)
    action.SetParam(48) -- ����״̬
    g_AIDebugInfo[90] = '[90] SetParam(State48)'

    -- ����״̬
    state = ai.NewState(48)
    state.HandleEvent(AI_EVENT.ON_ATTACKED, 4)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 5)

    -- ѡ���¼�������
    action = ai.NewAction(4, AI_ACTION.SELECT_EVENT_SRC)
    action.SetBranch(60, 43)
    g_AIDebugInfo[4] = '[4] SELECT_EVENT_SRC()'

    -- ��Ŀ����ӵ���в�б�
    action = ai.NewAction(60, AI_ACTION.ADD_TARGET_TO_THREAT_LIST)
    action.SetBranch(32)
    g_AIDebugInfo[60] = '[60] ADD_TARGET_TO_THREAT_LIST()'

    -- ��¼���ص�
    action = ai.NewAction(32, AI_ACTION.RECORD_RETURN_POSITION)
    action.SetBranch(7)
    g_AIDebugInfo[32] = '[32] RECORD_RETURN_POSITION()'

    -- Npc��ʼ������CD
    action = ai.NewAction(7, AI_ACTION.NPC_INIT_SKILL_CD)
    action.SetBranch(26)
    g_AIDebugInfo[7] = '[7] NPC_INIT_SKILL_CD()'

    -- ��������ʱ��
    action = ai.NewAction(26, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(8)
    action.SetBranch(92)
    g_AIDebugInfo[26] = '[26] SET_PRIMARY_TIMER(8)'

    -- ����״̬
    action = ai.NewAction(92, AI_ACTION.SET_STATE)
    action.SetParam(59) -- ս��״̬
    g_AIDebugInfo[92] = '[92] SetParam(State59)'

    -- ս��״̬
    state = ai.NewState(59)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 56)

    -- ѡ���һ��в
    action = ai.NewAction(56, AI_ACTION.SELECT_FIRST_THREAT)
    action.SetBranch(69, 43)
    g_AIDebugInfo[56] = '[56] SELECT_FIRST_THREAT()'

    -- ����ϵͳ�޵�
    action = ai.NewAction(43, AI_ACTION.SET_SYSTEM_SHEILD)
    action.SetParam(1)
    action.SetBranch(13)
    g_AIDebugInfo[43] = '[43] SET_SYSTEM_SHEILD(1)'

    -- ����
    action = ai.NewAction(13, AI_ACTION.RETURN)
    action.SetParam(0)
    action.SetBranch(2, 2)
    g_AIDebugInfo[13] = '[13] RETURN(0)'

    -- ��������ʱ��
    action = ai.NewAction(2, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(8)
    action.SetBranch(94)
    g_AIDebugInfo[2] = '[2] SET_PRIMARY_TIMER(8)'

    -- ����״̬
    action = ai.NewAction(94, AI_ACTION.SET_STATE)
    action.SetParam(19) -- �޵з���״̬
    g_AIDebugInfo[94] = '[94] SetParam(State19)'

    -- �޵з���״̬
    state = ai.NewState(19)
    state.HandleEvent(AI_EVENT.ON_PATH_FAILED, 39)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 39)

    -- ����
    action = ai.NewAction(39, AI_ACTION.RETURN)
    action.SetParam(1)
    action.SetBranch(30, 30)
    g_AIDebugInfo[39] = '[39] RETURN(1)'

    -- ��������ʱ��
    action = ai.NewAction(30, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(8)
    action.SetBranch(96)
    g_AIDebugInfo[30] = '[30] SET_PRIMARY_TIMER(8)'

    -- ����״̬
    action = ai.NewAction(96, AI_ACTION.SET_STATE)
    action.SetParam(18) -- ���سɹ�
    g_AIDebugInfo[96] = '[96] SetParam(State18)'

    -- ���سɹ�
    state = ai.NewState(18)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 62)

    -- ���DEBUFF
    action = ai.NewAction(62, AI_ACTION.CLEAN_DEBUFF)
    action.SetBranch(46)
    g_AIDebugInfo[62] = '[62] CLEAN_DEBUFF()'

    -- ����ϵͳ�޵�
    action = ai.NewAction(46, AI_ACTION.SET_SYSTEM_SHEILD)
    action.SetParam(0)
    action.SetBranch(47)
    g_AIDebugInfo[46] = '[46] SET_SYSTEM_SHEILD(0)'

    -- Npc��׼����ѡ��
    action = ai.NewAction(69, AI_ACTION.NPC_STANDARD_SKILL_SELECTOR)
    action.SetBranch(6, 26)
    g_AIDebugInfo[69] = '[69] NPC_STANDARD_SKILL_SELECTOR()'

    -- ���־���
    action = ai.NewAction(6, AI_ACTION.KEEP_RANGE)
    action.SetParam(350, 450)
    action.SetBranch(10, 80)
    g_AIDebugInfo[6] = '[6] KEEP_RANGE(350, 450)'

    -- Npc�ͷ�ѡ������
    action = ai.NewAction(10, AI_ACTION.NPC_CAST_SELECT_SKILL)
    action.SetBranch(70, 50)
    g_AIDebugInfo[10] = '[10] NPC_CAST_SELECT_SKILL()'

    -- ˫ѡ�����
    action = ai.NewAction(70, AI_ACTION.RANDOM_BI_BRANCH)
    action.SetParam(50, 50)
    action.SetBranch(72, 26)
    g_AIDebugInfo[70] = '[70] RANDOM_BI_BRANCH(50, 50)'

    -- NPC����
    action = ai.NewAction(72, 2072)
    action.SetBranch(73)
    g_AIDebugInfo[72] = '[72] CustomAction72()'

    -- ��������ʱ��
    action = ai.NewAction(73, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(0)
    action.SetBranch(98)
    g_AIDebugInfo[73] = '[73] SET_PRIMARY_TIMER(0)'

    -- ����״̬
    action = ai.NewAction(98, AI_ACTION.SET_STATE)
    action.SetParam(74) -- ��������
    g_AIDebugInfo[98] = '[98] SetParam(State74)'

    -- ��������
    state = ai.NewState(74)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 26)

    -- ��鼼��ʧ�ܼ���
    action = ai.NewAction(50, AI_ACTION.CHECK_SKILL_FAILED_COUNTER)
    action.SetParam(5)
    action.SetBranch(56, 43)
    g_AIDebugInfo[50] = '[50] CHECK_SKILL_FAILED_COUNTER(5)'

    -- ��������ʱ��
    action = ai.NewAction(80, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(16)
    action.SetBranch(100)
    g_AIDebugInfo[80] = '[80] SET_PRIMARY_TIMER(16)'

    -- ����״̬
    action = ai.NewAction(100, AI_ACTION.SET_STATE)
    action.SetParam(81) -- ׷��״̬
    g_AIDebugInfo[100] = '[100] SetParam(State81)'

    -- ׷��״̬
    state = ai.NewState(81)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 28)
    state.HandleEvent(AI_EVENT.ON_TARGET_KILLED, 47)

    -- �ȽϷ��ص����
    action = ai.NewAction(28, AI_ACTION.RETURN_POSITION_DISTANCE_COMPARE)
    action.SetParam(10000)
    action.SetBranch(43, 10, 10)
    g_AIDebugInfo[28] = '[28] RETURN_POSITION_DISTANCE_COMPARE(10000)'

    -- ��������
    action = ai.NewAction(5, AI_ACTION.SEARCH_ENEMY)
    action.SetParam(700)
    action.SetBranch(60, 47)
    g_AIDebugInfo[5] = '[5] SEARCH_ENEMY(700)'

    ai.SetInitState(66)
end

-- ���Է���
function AI:DebugOnCallAction(nActiondId, nAIType)
    print('[AI] Call action: ' .. AI[nAIType][nActiondId])
end

-- ��AIͼ���Զ���ű�
function AI:CustomAction72(pNpc, ai)
    -- �����Զ��嶯��ʵ�ֽű�
	local param = AI.g_AIParam[ai.nAIType]
    Dialog:NpcBubbleToNearBy(pNpc.dwId, param.Shout1)
    return 1
end


