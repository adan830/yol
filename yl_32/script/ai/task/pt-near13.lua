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
    ai.RegisterUserAction(2119, 'CustomAction119')

    -- ��ʼ
    state = ai.NewState(147)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 91)

    -- ��¼ԭ��
    action = ai.NewAction(91, AI_ACTION.RECORD_ORIGIN_POSITION)
    action.SetBranch(113)
    g_AIDebugInfo[91] = '[91] RECORD_ORIGIN_POSITION()'

    -- ��������ʱ��
    action = ai.NewAction(113, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(0)
    action.SetBranch(163)
    g_AIDebugInfo[113] = '[113] SET_PRIMARY_TIMER(0)'

    -- ����״̬
    action = ai.NewAction(163, AI_ACTION.SET_STATE)
    action.SetParam(138) -- ����״̬
    g_AIDebugInfo[163] = '[163] SetParam(State138)'

    -- ����״̬
    state = ai.NewState(138)
    state.HandleEvent(AI_EVENT.ON_ATTACKED, 92)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 95)

    -- ѡ���¼�������
    action = ai.NewAction(92, AI_ACTION.SELECT_EVENT_SRC)
    action.SetBranch(128, 90)
    g_AIDebugInfo[92] = '[92] SELECT_EVENT_SRC()'

    -- ����ϵͳ�޵�
    action = ai.NewAction(90, AI_ACTION.SET_SYSTEM_SHEILD)
    action.SetParam(1)
    action.SetBranch(157)
    g_AIDebugInfo[90] = '[90] SET_SYSTEM_SHEILD(1)'

    -- ����
    action = ai.NewAction(157, AI_ACTION.RETURN)
    action.SetParam(0)
    action.SetBranch(153, 153)
    g_AIDebugInfo[157] = '[157] RETURN(0)'

    -- ��������ʱ��
    action = ai.NewAction(153, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(8)
    action.SetBranch(165)
    g_AIDebugInfo[153] = '[153] SET_PRIMARY_TIMER(8)'

    -- ����״̬
    action = ai.NewAction(165, AI_ACTION.SET_STATE)
    action.SetParam(84) -- �޵з���״̬
    g_AIDebugInfo[165] = '[165] SetParam(State84)'

    -- �޵з���״̬
    state = ai.NewState(84)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 155)
    state.HandleEvent(AI_EVENT.ON_PATH_FAILED, 155)

    -- ����
    action = ai.NewAction(155, AI_ACTION.RETURN)
    action.SetParam(1)
    action.SetBranch(104, 104)
    g_AIDebugInfo[155] = '[155] RETURN(1)'

    -- ��������ʱ��
    action = ai.NewAction(104, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(8)
    action.SetBranch(167)
    g_AIDebugInfo[104] = '[104] SET_PRIMARY_TIMER(8)'

    -- ����״̬
    action = ai.NewAction(167, AI_ACTION.SET_STATE)
    action.SetParam(154) -- ���سɹ�
    g_AIDebugInfo[167] = '[167] SetParam(State154)'

    -- ���سɹ�
    state = ai.NewState(154)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 139)

    -- ���DEBUFF
    action = ai.NewAction(139, AI_ACTION.CLEAN_DEBUFF)
    action.SetBranch(140)
    g_AIDebugInfo[139] = '[139] CLEAN_DEBUFF()'

    -- ����ϵͳ�޵�
    action = ai.NewAction(140, AI_ACTION.SET_SYSTEM_SHEILD)
    action.SetParam(0)
    action.SetBranch(113)
    g_AIDebugInfo[140] = '[140] SET_SYSTEM_SHEILD(0)'

    -- ��Ŀ����ӵ���в�б�
    action = ai.NewAction(128, AI_ACTION.ADD_TARGET_TO_THREAT_LIST)
    action.SetBranch(100)
    g_AIDebugInfo[128] = '[128] ADD_TARGET_TO_THREAT_LIST()'

    -- ��¼���ص�
    action = ai.NewAction(100, AI_ACTION.RECORD_RETURN_POSITION)
    action.SetBranch(82)
    g_AIDebugInfo[100] = '[100] RECORD_RETURN_POSITION()'

    -- Npc��ʼ������CD
    action = ai.NewAction(82, AI_ACTION.NPC_INIT_SKILL_CD)
    action.SetBranch(122)
    g_AIDebugInfo[82] = '[82] NPC_INIT_SKILL_CD()'

    -- ��������ʱ��
    action = ai.NewAction(122, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(1)
    action.SetBranch(169)
    g_AIDebugInfo[122] = '[122] SET_PRIMARY_TIMER(1)'

    -- ����״̬
    action = ai.NewAction(169, AI_ACTION.SET_STATE)
    action.SetParam(93) -- ս��״̬
    g_AIDebugInfo[169] = '[169] SetParam(State93)'

    -- ս��״̬
    state = ai.NewState(93)
    state.HandleEvent(AI_EVENT.ON_TARGET_KILLED, 113)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 108)

    -- ѡ���һ��в
    action = ai.NewAction(108, AI_ACTION.SELECT_FIRST_THREAT)
    action.SetBranch(142, 90)
    g_AIDebugInfo[108] = '[108] SELECT_FIRST_THREAT()'

    -- Npc��׼����ѡ��
    action = ai.NewAction(142, AI_ACTION.NPC_STANDARD_SKILL_SELECTOR)
    action.SetBranch(151, 122)
    g_AIDebugInfo[142] = '[142] NPC_STANDARD_SKILL_SELECTOR()'

    -- ˫ѡ�����
    action = ai.NewAction(151, AI_ACTION.RANDOM_BI_BRANCH)
    action.SetParam(5, 95)
    action.SetBranch(119, 123)
    g_AIDebugInfo[151] = '[151] RANDOM_BI_BRANCH(5, 95)'

    -- NPC����
    action = ai.NewAction(119, 2119)
    action.SetBranch(101)
    g_AIDebugInfo[119] = '[119] CustomAction119()'

    -- ��������ʱ��
    action = ai.NewAction(101, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(0)
    action.SetBranch(171)
    g_AIDebugInfo[101] = '[101] SET_PRIMARY_TIMER(0)'

    -- ����״̬
    action = ai.NewAction(171, AI_ACTION.SET_STATE)
    action.SetParam(109) -- ��������
    g_AIDebugInfo[171] = '[171] SetParam(State109)'

    -- ��������
    state = ai.NewState(109)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 123)

    -- Npc���ּ����ͷž���
    action = ai.NewAction(123, AI_ACTION.NPC_KEEP_SKILL_CAST_RANGE)
    action.SetBranch(105, 126)
    g_AIDebugInfo[123] = '[123] NPC_KEEP_SKILL_CAST_RANGE()'

    -- Npc�ͷ�ѡ������
    action = ai.NewAction(105, AI_ACTION.NPC_CAST_SELECT_SKILL)
    action.SetBranch(122, 159)
    g_AIDebugInfo[105] = '[105] NPC_CAST_SELECT_SKILL()'

    -- ��鼼��ʧ�ܼ���
    action = ai.NewAction(159, AI_ACTION.CHECK_SKILL_FAILED_COUNTER)
    action.SetParam(100)
    action.SetBranch(122, 90)
    g_AIDebugInfo[159] = '[159] CHECK_SKILL_FAILED_COUNTER(100)'

    -- ��������ʱ��
    action = ai.NewAction(126, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(0)
    action.SetBranch(173)
    g_AIDebugInfo[126] = '[126] SET_PRIMARY_TIMER(0)'

    -- ����״̬
    action = ai.NewAction(173, AI_ACTION.SET_STATE)
    action.SetParam(152) -- ׷��״̬
    g_AIDebugInfo[173] = '[173] SetParam(State152)'

    -- ׷��״̬
    state = ai.NewState(152)
    state.HandleEvent(AI_EVENT.ON_CAST_SKILL_FAILED, 113)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 137)
    state.HandleEvent(AI_EVENT.ON_TARGET_KILLED, 113)

    -- �ȽϷ��ص����
    action = ai.NewAction(137, AI_ACTION.RETURN_POSITION_DISTANCE_COMPARE)
    action.SetParam(param['EscapeRange'])
    action.SetBranch(90, 123, 123)
    g_AIDebugInfo[137] = '[137] RETURN_POSITION_DISTANCE_COMPARE(param[EscapeRange])'

    -- ��������
    action = ai.NewAction(95, AI_ACTION.SEARCH_ENEMY)
    action.SetParam(param['AlertRange'])
    action.SetBranch(128, 113)
    g_AIDebugInfo[95] = '[95] SEARCH_ENEMY(param[AlertRange])'

    ai.SetInitState(147)
end

-- ���Է���
function AI:DebugOnCallAction(nActiondId, nAIType)
    print('[AI] Call action: ' .. AI[nAIType][nActiondId])
end

-- ��AIͼ���Զ���ű�
function AI:CustomAction119(pNpc, ai)
    -- �����Զ��嶯��ʵ�ֽű�
	local param = AI.g_AIParam[ai.nAIType]
    Dialog:NpcBubbleToNearBy(pNpc.dwId, param.Shout1)
    return 1
end

