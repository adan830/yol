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
    ai.RegisterUserAction(2092, 'CustomAction92')

    -- ��ʼ
    state = ai.NewState(19)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 105)

    -- ��¼ԭ��
    action = ai.NewAction(105, AI_ACTION.RECORD_ORIGIN_POSITION)
    action.SetBranch(83)
    g_AIDebugInfo[105] = '[105] RECORD_ORIGIN_POSITION()'

    -- ��������ʱ��
    action = ai.NewAction(83, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(1)
    action.SetBranch(109)
    g_AIDebugInfo[83] = '[83] SET_PRIMARY_TIMER(1)'

    -- ����״̬
    action = ai.NewAction(109, AI_ACTION.SET_STATE)
    action.SetParam(57) -- ����״̬
    g_AIDebugInfo[109] = '[109] SetParam(State57)'

    -- ����״̬
    state = ai.NewState(57)
    state.HandleEvent(AI_EVENT.ON_ATTACKED, 32)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 41)

    -- ѡ���¼�������
    action = ai.NewAction(32, AI_ACTION.SELECT_EVENT_SRC)
    action.SetBranch(97, 47)
    g_AIDebugInfo[32] = '[32] SELECT_EVENT_SRC()'

    -- ��Ŀ����ӵ���в�б�
    action = ai.NewAction(97, AI_ACTION.ADD_TARGET_TO_THREAT_LIST)
    action.SetBranch(14)
    g_AIDebugInfo[97] = '[97] ADD_TARGET_TO_THREAT_LIST()'

    -- ��¼���ص�
    action = ai.NewAction(14, AI_ACTION.RECORD_RETURN_POSITION)
    action.SetBranch(85)
    g_AIDebugInfo[14] = '[14] RECORD_RETURN_POSITION()'

    -- Npc��ʼ������CD
    action = ai.NewAction(85, AI_ACTION.NPC_INIT_SKILL_CD)
    action.SetBranch(16)
    g_AIDebugInfo[85] = '[85] NPC_INIT_SKILL_CD()'

    -- ��������ʱ��
    action = ai.NewAction(16, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(1)
    action.SetBranch(111)
    g_AIDebugInfo[16] = '[16] SET_PRIMARY_TIMER(1)'

    -- ����״̬
    action = ai.NewAction(111, AI_ACTION.SET_STATE)
    action.SetParam(2) -- ս��״̬
    g_AIDebugInfo[111] = '[111] SetParam(State2)'

    -- ս��״̬
    state = ai.NewState(2)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 24)
    state.HandleEvent(AI_EVENT.ON_TARGET_KILLED, 47)

    -- ѡ���һ��в
    action = ai.NewAction(24, AI_ACTION.SELECT_FIRST_THREAT)
    action.SetBranch(15, 83)
    g_AIDebugInfo[24] = '[24] SELECT_FIRST_THREAT()'

    -- ˫ѡ�����
    action = ai.NewAction(15, AI_ACTION.RANDOM_BI_BRANCH)
    action.SetParam(95, 5)
    action.SetBranch(44, 92)
    g_AIDebugInfo[15] = '[15] RANDOM_BI_BRANCH(95, 5)'

    -- NPC����
    action = ai.NewAction(92, 2092)
    action.SetBranch(7)
    g_AIDebugInfo[92] = '[92] CustomAction92()'

    -- ��������ʱ��
    action = ai.NewAction(7, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(16)
    action.SetBranch(113)
    g_AIDebugInfo[7] = '[7] SET_PRIMARY_TIMER(16)'

    -- ����״̬
    action = ai.NewAction(113, AI_ACTION.SET_STATE)
    action.SetParam(86) -- ��������
    g_AIDebugInfo[113] = '[113] SetParam(State86)'

    -- ��������
    state = ai.NewState(86)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 54)

    -- �ͷż���
    action = ai.NewAction(54, AI_ACTION.CAST_SKILL)
    action.SetParam(1362, 1)
    action.SetBranch(33, 16)
    g_AIDebugInfo[54] = '[54] CAST_SKILL(1362, 1)'

    -- ��������ʱ��
    action = ai.NewAction(33, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(80)
    action.SetBranch(115)
    g_AIDebugInfo[33] = '[33] SET_PRIMARY_TIMER(80)'

    -- ����״̬
    action = ai.NewAction(115, AI_ACTION.SET_STATE)
    action.SetParam(5) -- ��һ���
    g_AIDebugInfo[115] = '[115] SetParam(State5)'

    -- ��һ���
    state = ai.NewState(5)
    state.HandleEvent(AI_EVENT.ON_TARGET_KILLED, 47)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 16)

    -- վ��
    action = ai.NewAction(47, AI_ACTION.STAND)
    action.SetBranch(55)
    g_AIDebugInfo[47] = '[47] STAND()'

    -- ��������ʱ��
    action = ai.NewAction(55, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(4)
    action.SetBranch(117)
    g_AIDebugInfo[55] = '[55] SET_PRIMARY_TIMER(4)'

    -- ����״̬
    action = ai.NewAction(117, AI_ACTION.SET_STATE)
    action.SetParam(45) -- ����״̬
    g_AIDebugInfo[117] = '[117] SetParam(State45)'

    -- ����״̬
    state = ai.NewState(45)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 48)

    -- ��������
    action = ai.NewAction(48, AI_ACTION.SEARCH_ENEMY)
    action.SetParam(6000)
    action.SetBranch(103, 38)
    g_AIDebugInfo[48] = '[48] SEARCH_ENEMY(6000)'

    -- ��Ŀ����ӵ���в�б�
    action = ai.NewAction(103, AI_ACTION.ADD_TARGET_TO_THREAT_LIST)
    action.SetBranch(52)
    g_AIDebugInfo[103] = '[103] ADD_TARGET_TO_THREAT_LIST()'

    -- ѡ���һ��в
    action = ai.NewAction(52, AI_ACTION.SELECT_FIRST_THREAT)
    action.SetBranch(44, 47)
    g_AIDebugInfo[52] = '[52] SELECT_FIRST_THREAT()'

    -- Npc��׼����ѡ��
    action = ai.NewAction(44, AI_ACTION.NPC_STANDARD_SKILL_SELECTOR)
    action.SetBranch(60, 16)
    g_AIDebugInfo[44] = '[44] NPC_STANDARD_SKILL_SELECTOR()'

    -- Npc���ּ����ͷž���
    action = ai.NewAction(60, AI_ACTION.NPC_KEEP_SKILL_CAST_RANGE)
    action.SetBranch(9, 25)
    g_AIDebugInfo[60] = '[60] NPC_KEEP_SKILL_CAST_RANGE()'

    -- ��������ʱ��
    action = ai.NewAction(25, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(0)
    action.SetBranch(119)
    g_AIDebugInfo[25] = '[25] SET_PRIMARY_TIMER(0)'

    -- ����״̬
    action = ai.NewAction(119, AI_ACTION.SET_STATE)
    action.SetParam(70) -- ׷��״̬
    g_AIDebugInfo[119] = '[119] SetParam(State70)'

    -- ׷��״̬
    state = ai.NewState(70)
    state.HandleEvent(AI_EVENT.ON_TARGET_KILLED, 47)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 20)

    -- �ȽϷ��ص����
    action = ai.NewAction(20, AI_ACTION.RETURN_POSITION_DISTANCE_COMPARE)
    action.SetParam(param['EscapeRange'])
    action.SetBranch(47, 60, 60)
    g_AIDebugInfo[20] = '[20] RETURN_POSITION_DISTANCE_COMPARE(param[EscapeRange])'

    -- Npc�ͷ�ѡ������
    action = ai.NewAction(9, AI_ACTION.NPC_CAST_SELECT_SKILL)
    action.SetBranch(16, 36)
    g_AIDebugInfo[9] = '[9] NPC_CAST_SELECT_SKILL()'

    -- ��鼼��ʧ�ܼ���
    action = ai.NewAction(36, AI_ACTION.CHECK_SKILL_FAILED_COUNTER)
    action.SetParam(10)
    action.SetBranch(16, 47)
    g_AIDebugInfo[36] = '[36] CHECK_SKILL_FAILED_COUNTER(10)'

    -- �ͷż���
    action = ai.NewAction(38, AI_ACTION.CAST_SKILL)
    action.SetParam(311, 1)
    action.SetBranch(73, 73)
    g_AIDebugInfo[38] = '[38] CAST_SKILL(311, 1)'

    -- ��鼼��ʧ�ܼ���
    action = ai.NewAction(73, AI_ACTION.CHECK_SKILL_FAILED_COUNTER)
    action.SetParam(3)
    action.SetBranch(47, 42)
    g_AIDebugInfo[73] = '[73] CHECK_SKILL_FAILED_COUNTER(3)'

    -- ����ϵͳ�޵�
    action = ai.NewAction(42, AI_ACTION.SET_SYSTEM_SHEILD)
    action.SetParam(1)
    action.SetBranch(65)
    g_AIDebugInfo[42] = '[42] SET_SYSTEM_SHEILD(1)'

    -- ����
    action = ai.NewAction(65, AI_ACTION.RETURN)
    action.SetParam(0)
    action.SetBranch(40, 40)
    g_AIDebugInfo[65] = '[65] RETURN(0)'

    -- ��������ʱ��
    action = ai.NewAction(40, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(8)
    action.SetBranch(121)
    g_AIDebugInfo[40] = '[40] SET_PRIMARY_TIMER(8)'

    -- ����״̬
    action = ai.NewAction(121, AI_ACTION.SET_STATE)
    action.SetParam(82) -- �޵з���״̬
    g_AIDebugInfo[121] = '[121] SetParam(State82)'

    -- �޵з���״̬
    state = ai.NewState(82)
    state.HandleEvent(AI_EVENT.ON_PATH_FAILED, 17)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 17)

    -- ����
    action = ai.NewAction(17, AI_ACTION.RETURN)
    action.SetParam(1)
    action.SetBranch(76, 76)
    g_AIDebugInfo[17] = '[17] RETURN(1)'

    -- ��������ʱ��
    action = ai.NewAction(76, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(8)
    action.SetBranch(123)
    g_AIDebugInfo[76] = '[76] SET_PRIMARY_TIMER(8)'

    -- ����״̬
    action = ai.NewAction(123, AI_ACTION.SET_STATE)
    action.SetParam(13) -- ���سɹ�
    g_AIDebugInfo[123] = '[123] SetParam(State13)'

    -- ���سɹ�
    state = ai.NewState(13)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 31)

    -- ���DEBUFF
    action = ai.NewAction(31, AI_ACTION.CLEAN_DEBUFF)
    action.SetBranch(29)
    g_AIDebugInfo[31] = '[31] CLEAN_DEBUFF()'

    -- ����ϵͳ�޵�
    action = ai.NewAction(29, AI_ACTION.SET_SYSTEM_SHEILD)
    action.SetParam(0)
    action.SetBranch(83)
    g_AIDebugInfo[29] = '[29] SET_SYSTEM_SHEILD(0)'

    -- ��������
    action = ai.NewAction(41, AI_ACTION.SEARCH_ENEMY)
    action.SetParam(param['AlertRange'])
    action.SetBranch(97, 83)
    g_AIDebugInfo[41] = '[41] SEARCH_ENEMY(param[AlertRange])'

    ai.SetInitState(19)
end

-- ���Է���
function AI:DebugOnCallAction(nActiondId, nAIType)
    print('[AI] Call action: ' .. AI[nAIType][nActiondId])
end

-- ��AIͼ���Զ���ű�
function AI:CustomAction92(pNpc, ai)
    -- �����Զ��嶯��ʵ�ֽű�
	local param = AI.g_AIParam[ai.nAIType]
    Dialog:NpcBubbleToNearBy(pNpc.dwId, param.Shout1)
    return 1
end

