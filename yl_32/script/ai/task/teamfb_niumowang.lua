-- ��д�ߣ�hejingxian
-- �汾�ţ�35

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
    ai.RegisterUserAction(2078, 'AI:CustomAction78')

    -- ���˸���-ţħ��
    state = ai.NewState(19)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 5)

    -- ��¼ԭ��
    action = ai.NewAction(5, AI_ACTION.RECORD_ORIGIN_POSITION)
    action.SetBranch(40)
    g_AIDebugInfo[5] = '[5] RECORD_ORIGIN_POSITION()'

    -- ��¼���ص�
    action = ai.NewAction(40, AI_ACTION.RECORD_RETURN_POSITION)
    action.SetBranch(3)
    g_AIDebugInfo[40] = '[40] RECORD_RETURN_POSITION()'

    -- ����Ѳ��·��
    action = ai.NewAction(3, AI_ACTION.ENTER_PATROL_PATH)
    action.SetParam(param['PatrolPathID'], param['PatrolOrderIndex'])
    action.SetBranch(33)
    g_AIDebugInfo[3] = '[3] ENTER_PATROL_PATH(param[PatrolPathID], param[PatrolOrderIndex])'

    -- Ѳ��
    action = ai.NewAction(33, AI_ACTION.DO_PATROL)
    action.SetBranch(39, 2)
    g_AIDebugInfo[33] = '[33] DO_PATROL()'

    -- ��������ʱ��
    action = ai.NewAction(2, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(4)
    action.SetBranch(89)
    g_AIDebugInfo[2] = '[2] SET_PRIMARY_TIMER(4)'

    -- ����״̬
    action = ai.NewAction(89, AI_ACTION.SET_STATE)
    action.SetParam(47) -- ������Ů
    g_AIDebugInfo[89] = '[89] SetParam(State47)'

    -- ������Ů
    state = ai.NewState(47)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 35)

    -- ��������
    action = ai.NewAction(35, AI_ACTION.SEARCH_ENEMY)
    action.SetParam(param['AlertRange'])
    action.SetBranch(7, 2)
    g_AIDebugInfo[35] = '[35] SEARCH_ENEMY(param[AlertRange])'

    -- ��Ŀ����ӵ���в�б�
    action = ai.NewAction(7, AI_ACTION.ADD_TARGET_TO_THREAT_LIST)
    action.SetBranch(34)
    g_AIDebugInfo[7] = '[7] ADD_TARGET_TO_THREAT_LIST()'

    -- Npc��ʼ������CD
    action = ai.NewAction(34, AI_ACTION.NPC_INIT_SKILL_CD)
    action.SetBranch(44)
    g_AIDebugInfo[34] = '[34] NPC_INIT_SKILL_CD()'

    -- ��������ʱ��
    action = ai.NewAction(44, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(4)
    action.SetBranch(91)
    g_AIDebugInfo[44] = '[44] SET_PRIMARY_TIMER(4)'

    -- ����״̬
    action = ai.NewAction(91, AI_ACTION.SET_STATE)
    action.SetParam(11) -- ��ͨ����
    g_AIDebugInfo[91] = '[91] SetParam(State11)'

    -- ��ͨ����
    state = ai.NewState(11)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 84)

    -- �ͷż���
    action = ai.NewAction(84, AI_ACTION.CAST_SKILL)
    action.SetParam(1603, 1)
    action.SetBranch(86, 2)
    g_AIDebugInfo[84] = '[84] CAST_SKILL(1603, 1)'

    -- ��������ʱ��
    action = ai.NewAction(86, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(32)
    action.SetBranch(93)
    g_AIDebugInfo[86] = '[86] SET_PRIMARY_TIMER(32)'

    -- ����״̬
    action = ai.NewAction(93, AI_ACTION.SET_STATE)
    action.SetParam(87) -- ��ͨ����
    g_AIDebugInfo[93] = '[93] SetParam(State87)'

    -- ��ͨ����
    state = ai.NewState(87)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 9)

    -- ��鼼��ʧ�ܼ���
    action = ai.NewAction(9, AI_ACTION.CHECK_SKILL_FAILED_COUNTER)
    action.SetParam(50)
    action.SetBranch(44, 2)
    g_AIDebugInfo[9] = '[9] CHECK_SKILL_FAILED_COUNTER(50)'

    -- ��������ʱ��
    action = ai.NewAction(39, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(64)
    action.SetBranch(95)
    g_AIDebugInfo[39] = '[39] SET_PRIMARY_TIMER(64)'

    -- ����״̬
    action = ai.NewAction(95, AI_ACTION.SET_STATE)
    action.SetParam(23) -- ��״̬
    g_AIDebugInfo[95] = '[95] SetParam(State23)'

    -- ��״̬
    state = ai.NewState(23)
    state.HandleEvent(AI_EVENT.ON_PATH_SUCCESS, 25)
    state.HandleEvent(AI_EVENT.ON_SECONDARY_TIMER, 81)

    -- ���ø���ʱ��
    action = ai.NewAction(25, AI_ACTION.SET_SECONDARY_TIMER)
    action.SetParam(64)
    action.SetBranch(39)
    g_AIDebugInfo[25] = '[25] SET_SECONDARY_TIMER(64)'

    -- Npc��׼����ѡ��
    action = ai.NewAction(81, AI_ACTION.NPC_STANDARD_SKILL_SELECTOR)
    action.SetBranch(78, 33)
    g_AIDebugInfo[81] = '[81] NPC_STANDARD_SKILL_SELECTOR()'

    -- ѡ���Լ�
    action = ai.NewAction(78, 2078)
    action.SetBranch(80)
    g_AIDebugInfo[78] = '[78] AI:CustomAction78()'

    -- Npc�ͷ�ѡ������
    action = ai.NewAction(80, AI_ACTION.NPC_CAST_SELECT_SKILL)
    action.SetBranch(33, 33)
    g_AIDebugInfo[80] = '[80] NPC_CAST_SELECT_SKILL()'

    ai.SetInitState(19)
end

-- ���Է���
function AI:DebugOnCallAction(nActiondId, nAIType)
    print('[AI] Call action: ' .. AI[nAIType][nActiondId])
end

-- ��AIͼ���Զ���ű�
function AI:CustomAction78(pNpc, actionData)
    -- �����Զ��嶯��ʵ�ֽű�
	pNpc.SetTarget(3,pNpc.dwId);
    return 1
end

