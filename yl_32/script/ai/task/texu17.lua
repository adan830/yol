-- ��д�ߣ�hejingxian
-- �汾�ţ�2

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
    ai.RegisterUserAction(2033, 'CustomAction33')

    -- ��ʼ
    state = ai.NewState(19)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 22)

    -- ��¼ԭ��
    action = ai.NewAction(22, AI_ACTION.RECORD_ORIGIN_POSITION)
    action.SetBranch(29)
    g_AIDebugInfo[22] = '[22] RECORD_ORIGIN_POSITION()'

    -- ��������ʱ��
    action = ai.NewAction(29, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(0)
    action.SetBranch(51)
    g_AIDebugInfo[29] = '[29] SET_PRIMARY_TIMER(0)'

    -- ����״̬
    action = ai.NewAction(51, AI_ACTION.SET_STATE)
    action.SetParam(34) -- ���Լ��ӳ����˺�
    g_AIDebugInfo[51] = '[51] SetParam(State34)'

    -- ���Լ��ӳ����˺�
    state = ai.NewState(34)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 33)

    -- ѡ���Լ�
    action = ai.NewAction(33, 2033)
    action.SetBranch(11)
    g_AIDebugInfo[33] = '[33] CustomAction33()'

    -- �ͷż���
    action = ai.NewAction(11, AI_ACTION.CAST_SKILL)
    action.SetParam(410, 1)
    action.SetBranch(48, 48)
    g_AIDebugInfo[11] = '[11] CAST_SKILL(410, 1)'

    -- ��������ʱ��
    action = ai.NewAction(48, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(4)
    action.SetBranch(53)
    g_AIDebugInfo[48] = '[48] SET_PRIMARY_TIMER(4)'

    -- ����״̬
    action = ai.NewAction(53, AI_ACTION.SET_STATE)
    action.SetParam(40) -- ��������
    g_AIDebugInfo[53] = '[53] SetParam(State40)'

    -- ��������
    state = ai.NewState(40)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 2)

    -- ��������
    action = ai.NewAction(2, AI_ACTION.SEARCH_ENEMY)
    action.SetParam(param['AlertRange'])
    action.SetBranch(18, 48)
    g_AIDebugInfo[2] = '[2] SEARCH_ENEMY(param[AlertRange])'

    -- ��Ŀ����ӵ���в�б�
    action = ai.NewAction(18, AI_ACTION.ADD_TARGET_TO_THREAT_LIST)
    action.SetBranch(23)
    g_AIDebugInfo[18] = '[18] ADD_TARGET_TO_THREAT_LIST()'

    -- ��¼���ص�
    action = ai.NewAction(23, AI_ACTION.RECORD_RETURN_POSITION)
    action.SetBranch(7)
    g_AIDebugInfo[23] = '[23] RECORD_RETURN_POSITION()'

    -- Npc��ʼ������CD
    action = ai.NewAction(7, AI_ACTION.NPC_INIT_SKILL_CD)
    action.SetBranch(49)
    g_AIDebugInfo[7] = '[7] NPC_INIT_SKILL_CD()'

    -- ��������ʱ��
    action = ai.NewAction(49, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(4)
    action.SetBranch(55)
    g_AIDebugInfo[49] = '[49] SET_PRIMARY_TIMER(4)'

    -- ����״̬
    action = ai.NewAction(55, AI_ACTION.SET_STATE)
    action.SetParam(41) -- ׷�ٵ���
    g_AIDebugInfo[55] = '[55] SetParam(State41)'

    -- ׷�ٵ���
    state = ai.NewState(41)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 14)

    -- ѡ���һ��в
    action = ai.NewAction(14, AI_ACTION.SELECT_FIRST_THREAT)
    action.SetBranch(30, 49)
    g_AIDebugInfo[14] = '[14] SELECT_FIRST_THREAT()'

    -- Npc��׼����ѡ��
    action = ai.NewAction(30, AI_ACTION.NPC_STANDARD_SKILL_SELECTOR)
    action.SetBranch(27, 49)
    g_AIDebugInfo[30] = '[30] NPC_STANDARD_SKILL_SELECTOR()'

    -- Npc���ּ����ͷž���
    action = ai.NewAction(27, AI_ACTION.NPC_KEEP_SKILL_CAST_RANGE)
    action.SetBranch(4, 31)
    g_AIDebugInfo[27] = '[27] NPC_KEEP_SKILL_CAST_RANGE()'

    -- Npc�ͷ�ѡ������
    action = ai.NewAction(4, AI_ACTION.NPC_CAST_SELECT_SKILL)
    action.SetBranch(49, 49)
    g_AIDebugInfo[4] = '[4] NPC_CAST_SELECT_SKILL()'

    -- ��������ʱ��
    action = ai.NewAction(31, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(0)
    action.SetBranch(57)
    g_AIDebugInfo[31] = '[31] SET_PRIMARY_TIMER(0)'

    -- ����״̬
    action = ai.NewAction(57, AI_ACTION.SET_STATE)
    action.SetParam(13) -- ׷��״̬
    g_AIDebugInfo[57] = '[57] SetParam(State13)'

    -- ׷��״̬
    state = ai.NewState(13)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 50)

    -- �ȽϷ��ص����
    action = ai.NewAction(50, AI_ACTION.RETURN_POSITION_DISTANCE_COMPARE)
    action.SetParam(param['EscapeRange'])
    action.SetBranch(48, 27, 27)
    g_AIDebugInfo[50] = '[50] RETURN_POSITION_DISTANCE_COMPARE(param[EscapeRange])'

    ai.SetInitState(19)
end

-- ���Է���
function AI:DebugOnCallAction(nActiondId, nAIType)
    print('[AI] Call action: ' .. AI[nAIType][nActiondId])
end

-- ��AIͼ���Զ���ű�
function AI:CustomAction33(pNpc, actionData)
    -- �����Զ��嶯��ʵ�ֽű�
	pNpc.SetTarget(3,pNpc.dwId);
    return 1
end

