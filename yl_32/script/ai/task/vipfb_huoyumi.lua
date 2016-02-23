-- ��д�ߣ�hejingxian
-- �汾�ţ�17

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
    ai.RegisterUserAction(2078, 'CustomAction78')

    -- ��ʼ
    state = ai.NewState(65)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 12)

    -- ��¼ԭ��
    action = ai.NewAction(12, AI_ACTION.RECORD_ORIGIN_POSITION)
    action.SetBranch(36)
    g_AIDebugInfo[12] = '[12] RECORD_ORIGIN_POSITION()'

    -- ��������ʱ��
    action = ai.NewAction(36, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(1)
    action.SetBranch(119)
    g_AIDebugInfo[36] = '[36] SET_PRIMARY_TIMER(1)'

    -- ����״̬
    action = ai.NewAction(119, AI_ACTION.SET_STATE)
    action.SetParam(47) -- ����״̬
    g_AIDebugInfo[119] = '[119] SetParam(State47)'

    -- ����״̬
    state = ai.NewState(47)
    state.HandleEvent(AI_EVENT.ON_ATTACKED, 60)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 66)

    -- ѡ���¼�������
    action = ai.NewAction(60, AI_ACTION.SELECT_EVENT_SRC)
    action.SetBranch(29, 39)
    g_AIDebugInfo[60] = '[60] SELECT_EVENT_SRC()'

    -- ��Ŀ����ӵ���в�б�
    action = ai.NewAction(29, AI_ACTION.ADD_TARGET_TO_THREAT_LIST)
    action.SetBranch(50)
    g_AIDebugInfo[29] = '[29] ADD_TARGET_TO_THREAT_LIST()'

    -- ��¼���ص�
    action = ai.NewAction(50, AI_ACTION.RECORD_RETURN_POSITION)
    action.SetBranch(63)
    g_AIDebugInfo[50] = '[50] RECORD_RETURN_POSITION()'

    -- Npc��ʼ������CD
    action = ai.NewAction(63, AI_ACTION.NPC_INIT_SKILL_CD)
    action.SetBranch(20)
    g_AIDebugInfo[63] = '[63] NPC_INIT_SKILL_CD()'

    -- ��������ʱ��
    action = ai.NewAction(20, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(1)
    action.SetBranch(121)
    g_AIDebugInfo[20] = '[20] SET_PRIMARY_TIMER(1)'

    -- ����״̬
    action = ai.NewAction(121, AI_ACTION.SET_STATE)
    action.SetParam(5) -- ս��״̬
    g_AIDebugInfo[121] = '[121] SetParam(State5)'

    -- ս��״̬
    state = ai.NewState(5)
    state.HandleEvent(AI_EVENT.ON_TARGET_KILLED, 39)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 51)

    -- վ��
    action = ai.NewAction(39, AI_ACTION.STAND)
    action.SetBranch(21)
    g_AIDebugInfo[39] = '[39] STAND()'

    -- ��������ʱ��
    action = ai.NewAction(21, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(4)
    action.SetBranch(123)
    g_AIDebugInfo[21] = '[21] SET_PRIMARY_TIMER(4)'

    -- ����״̬
    action = ai.NewAction(123, AI_ACTION.SET_STATE)
    action.SetParam(58) -- ����״̬
    g_AIDebugInfo[123] = '[123] SetParam(State58)'

    -- ����״̬
    state = ai.NewState(58)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 62)

    -- ��������
    action = ai.NewAction(62, AI_ACTION.SEARCH_ENEMY)
    action.SetParam(6000)
    action.SetBranch(22, 106)
    g_AIDebugInfo[62] = '[62] SEARCH_ENEMY(6000)'

    -- ��Ŀ����ӵ���в�б�
    action = ai.NewAction(22, AI_ACTION.ADD_TARGET_TO_THREAT_LIST)
    action.SetBranch(1)
    g_AIDebugInfo[22] = '[22] ADD_TARGET_TO_THREAT_LIST()'

    -- ѡ���һ��в
    action = ai.NewAction(1, AI_ACTION.SELECT_FIRST_THREAT)
    action.SetBranch(30, 39)
    g_AIDebugInfo[1] = '[1] SELECT_FIRST_THREAT()'

    -- Npc��׼����ѡ��
    action = ai.NewAction(30, AI_ACTION.NPC_STANDARD_SKILL_SELECTOR)
    action.SetBranch(53, 20)
    g_AIDebugInfo[30] = '[30] NPC_STANDARD_SKILL_SELECTOR()'

    -- Npc���ּ����ͷž���
    action = ai.NewAction(53, AI_ACTION.NPC_KEEP_SKILL_CAST_RANGE)
    action.SetBranch(68, 13)
    g_AIDebugInfo[53] = '[53] NPC_KEEP_SKILL_CAST_RANGE()'

    -- Npc�ͷ�ѡ������
    action = ai.NewAction(68, AI_ACTION.NPC_CAST_SELECT_SKILL)
    action.SetBranch(20, 15)
    g_AIDebugInfo[68] = '[68] NPC_CAST_SELECT_SKILL()'

    -- ��鼼��ʧ�ܼ���
    action = ai.NewAction(15, AI_ACTION.CHECK_SKILL_FAILED_COUNTER)
    action.SetParam(10)
    action.SetBranch(20, 39)
    g_AIDebugInfo[15] = '[15] CHECK_SKILL_FAILED_COUNTER(10)'

    -- ��������ʱ��
    action = ai.NewAction(13, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(0)
    action.SetBranch(125)
    g_AIDebugInfo[13] = '[13] SET_PRIMARY_TIMER(0)'

    -- ����״̬
    action = ai.NewAction(125, AI_ACTION.SET_STATE)
    action.SetParam(38) -- ׷��״̬
    g_AIDebugInfo[125] = '[125] SetParam(State38)'

    -- ׷��״̬
    state = ai.NewState(38)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 116)
    state.HandleEvent(AI_EVENT.ON_TARGET_KILLED, 39)

    -- Ŀ��֪�����
    action = ai.NewAction(116, AI_ACTION.IS_TARGET_EXIST)
    action.SetBranch(55, 51)
    g_AIDebugInfo[116] = '[116] IS_TARGET_EXIST()'

    -- �ȽϷ��ص����
    action = ai.NewAction(55, AI_ACTION.RETURN_POSITION_DISTANCE_COMPARE)
    action.SetParam(param['EscapeRange'])
    action.SetBranch(39, 53, 53)
    g_AIDebugInfo[55] = '[55] RETURN_POSITION_DISTANCE_COMPARE(param[EscapeRange])'

    -- ѡ���һ��в
    action = ai.NewAction(51, AI_ACTION.SELECT_FIRST_THREAT)
    action.SetBranch(70, 36)
    g_AIDebugInfo[51] = '[51] SELECT_FIRST_THREAT()'

    -- ˫ѡ�����
    action = ai.NewAction(70, AI_ACTION.RANDOM_BI_BRANCH)
    action.SetParam(95, 5)
    action.SetBranch(30, 78)
    g_AIDebugInfo[70] = '[70] RANDOM_BI_BRANCH(95, 5)'

    -- NPC����
    action = ai.NewAction(78, 2078)
    action.SetBranch(77)
    g_AIDebugInfo[78] = '[78] CustomAction78()'

    -- ��������ʱ��
    action = ai.NewAction(77, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(16)
    action.SetBranch(127)
    g_AIDebugInfo[77] = '[77] SET_PRIMARY_TIMER(16)'

    -- ����״̬
    action = ai.NewAction(127, AI_ACTION.SET_STATE)
    action.SetParam(79) -- ��������
    g_AIDebugInfo[127] = '[127] SetParam(State79)'

    -- ��������
    state = ai.NewState(79)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 72)

    -- �ͷż���
    action = ai.NewAction(72, AI_ACTION.CAST_SKILL)
    action.SetParam(1364, 1)
    action.SetBranch(74, 20)
    g_AIDebugInfo[72] = '[72] CAST_SKILL(1364, 1)'

    -- ��������ʱ��
    action = ai.NewAction(74, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(80)
    action.SetBranch(129)
    g_AIDebugInfo[74] = '[74] SET_PRIMARY_TIMER(80)'

    -- ����״̬
    action = ai.NewAction(129, AI_ACTION.SET_STATE)
    action.SetParam(75) -- ��һ���
    g_AIDebugInfo[129] = '[129] SetParam(State75)'

    -- ��һ���
    state = ai.NewState(75)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 20)
    state.HandleEvent(AI_EVENT.ON_TARGET_KILLED, 39)

    -- �ͷż���
    action = ai.NewAction(106, AI_ACTION.CAST_SKILL)
    action.SetParam(311, 1)
    action.SetBranch(109, 109)
    g_AIDebugInfo[106] = '[106] CAST_SKILL(311, 1)'

    -- ��鼼��ʧ�ܼ���
    action = ai.NewAction(109, AI_ACTION.CHECK_SKILL_FAILED_COUNTER)
    action.SetParam(3)
    action.SetBranch(39, 107)
    g_AIDebugInfo[109] = '[109] CHECK_SKILL_FAILED_COUNTER(3)'

    -- ����ϵͳ�޵�
    action = ai.NewAction(107, AI_ACTION.SET_SYSTEM_SHEILD)
    action.SetParam(1)
    action.SetBranch(105)
    g_AIDebugInfo[107] = '[107] SET_SYSTEM_SHEILD(1)'

    -- ����
    action = ai.NewAction(105, AI_ACTION.RETURN)
    action.SetParam(0)
    action.SetBranch(104, 104)
    g_AIDebugInfo[105] = '[105] RETURN(0)'

    -- ��������ʱ��
    action = ai.NewAction(104, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(8)
    action.SetBranch(131)
    g_AIDebugInfo[104] = '[104] SET_PRIMARY_TIMER(8)'

    -- ����״̬
    action = ai.NewAction(131, AI_ACTION.SET_STATE)
    action.SetParam(99) -- �޵з���״̬
    g_AIDebugInfo[131] = '[131] SetParam(State99)'

    -- �޵з���״̬
    state = ai.NewState(99)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 89)
    state.HandleEvent(AI_EVENT.ON_PATH_FAILED, 89)

    -- ����
    action = ai.NewAction(89, AI_ACTION.RETURN)
    action.SetParam(1)
    action.SetBranch(98, 98)
    g_AIDebugInfo[89] = '[89] RETURN(1)'

    -- ��������ʱ��
    action = ai.NewAction(98, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(8)
    action.SetBranch(133)
    g_AIDebugInfo[98] = '[98] SET_PRIMARY_TIMER(8)'

    -- ����״̬
    action = ai.NewAction(133, AI_ACTION.SET_STATE)
    action.SetParam(111) -- ���سɹ�
    g_AIDebugInfo[133] = '[133] SetParam(State111)'

    -- ���سɹ�
    state = ai.NewState(111)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 88)

    -- ���DEBUFF
    action = ai.NewAction(88, AI_ACTION.CLEAN_DEBUFF)
    action.SetBranch(95)
    g_AIDebugInfo[88] = '[88] CLEAN_DEBUFF()'

    -- ����ϵͳ�޵�
    action = ai.NewAction(95, AI_ACTION.SET_SYSTEM_SHEILD)
    action.SetParam(0)
    action.SetBranch(36)
    g_AIDebugInfo[95] = '[95] SET_SYSTEM_SHEILD(0)'

    -- ��������
    action = ai.NewAction(66, AI_ACTION.SEARCH_ENEMY)
    action.SetParam(param['AlertRange'])
    action.SetBranch(29, 36)
    g_AIDebugInfo[66] = '[66] SEARCH_ENEMY(param[AlertRange])'

    ai.SetInitState(65)
end

-- ���Է���
function AI:DebugOnCallAction(nActiondId, nAIType)
    print('[AI] Call action: ' .. AI[nAIType][nActiondId])
end

-- ��AIͼ���Զ���ű�
function AI:CustomAction78(pNpc, ai)
    -- �����Զ��嶯��ʵ�ֽű�
	local param = AI.g_AIParam[ai.nAIType]
    Dialog:NpcBubbleToNearBy(pNpc.dwId, param.Shout1)
    return 1
end

