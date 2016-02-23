-- ��д�ߣ�hejingxian
-- �汾�ţ�61

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
    ai.RegisterUserAction(2202, 'CustomAction202')

    -- ��ʼ
    state = ai.NewState(164)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 132)

    -- ��¼ԭ��
    action = ai.NewAction(132, AI_ACTION.RECORD_ORIGIN_POSITION)
    action.SetBranch(141)
    g_AIDebugInfo[132] = '[132] RECORD_ORIGIN_POSITION()'

    -- ��������ʱ��
    action = ai.NewAction(141, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(1)
    action.SetBranch(210)
    g_AIDebugInfo[141] = '[141] SET_PRIMARY_TIMER(1)'

    -- ����״̬
    action = ai.NewAction(210, AI_ACTION.SET_STATE)
    action.SetParam(119) -- ����״̬
    g_AIDebugInfo[210] = '[210] SetParam(State119)'

    -- ����״̬
    state = ai.NewState(119)
    state.HandleEvent(AI_EVENT.ON_ATTACKED, 153)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 181)

    -- ѡ���¼�������
    action = ai.NewAction(153, AI_ACTION.SELECT_EVENT_SRC)
    action.SetBranch(163, 158)
    g_AIDebugInfo[153] = '[153] SELECT_EVENT_SRC()'

    -- ��Ŀ����ӵ���в�б�
    action = ai.NewAction(163, AI_ACTION.ADD_TARGET_TO_THREAT_LIST)
    action.SetBranch(161)
    g_AIDebugInfo[163] = '[163] ADD_TARGET_TO_THREAT_LIST()'

    -- ��¼���ص�
    action = ai.NewAction(161, AI_ACTION.RECORD_RETURN_POSITION)
    action.SetBranch(188)
    g_AIDebugInfo[161] = '[161] RECORD_RETURN_POSITION()'

    -- Npc��ʼ������CD
    action = ai.NewAction(188, AI_ACTION.NPC_INIT_SKILL_CD)
    action.SetBranch(173)
    g_AIDebugInfo[188] = '[188] NPC_INIT_SKILL_CD()'

    -- ��������ʱ��
    action = ai.NewAction(173, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(1)
    action.SetBranch(212)
    g_AIDebugInfo[173] = '[173] SET_PRIMARY_TIMER(1)'

    -- ����״̬
    action = ai.NewAction(212, AI_ACTION.SET_STATE)
    action.SetParam(167) -- ս��״̬
    g_AIDebugInfo[212] = '[212] SetParam(State167)'

    -- ս��״̬
    state = ai.NewState(167)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 172)

    -- ѡ���һ��в
    action = ai.NewAction(172, AI_ACTION.SELECT_FIRST_THREAT)
    action.SetBranch(192, 158)
    g_AIDebugInfo[172] = '[172] SELECT_FIRST_THREAT()'

    -- ����ϵͳ�޵�
    action = ai.NewAction(158, AI_ACTION.SET_SYSTEM_SHEILD)
    action.SetParam(1)
    action.SetBranch(135)
    g_AIDebugInfo[158] = '[158] SET_SYSTEM_SHEILD(1)'

    -- ����
    action = ai.NewAction(135, AI_ACTION.RETURN)
    action.SetParam(0)
    action.SetBranch(186, 186)
    g_AIDebugInfo[135] = '[135] RETURN(0)'

    -- ��������ʱ��
    action = ai.NewAction(186, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(8)
    action.SetBranch(214)
    g_AIDebugInfo[186] = '[186] SET_PRIMARY_TIMER(8)'

    -- ����״̬
    action = ai.NewAction(214, AI_ACTION.SET_STATE)
    action.SetParam(178) -- �޵з���״̬
    g_AIDebugInfo[214] = '[214] SetParam(State178)'

    -- �޵з���״̬
    state = ai.NewState(178)
    state.HandleEvent(AI_EVENT.ON_PATH_FAILED, 124)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 124)

    -- ����
    action = ai.NewAction(124, AI_ACTION.RETURN)
    action.SetParam(1)
    action.SetBranch(193, 193)
    g_AIDebugInfo[124] = '[124] RETURN(1)'

    -- ��������ʱ��
    action = ai.NewAction(193, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(8)
    action.SetBranch(216)
    g_AIDebugInfo[193] = '[193] SET_PRIMARY_TIMER(8)'

    -- ����״̬
    action = ai.NewAction(216, AI_ACTION.SET_STATE)
    action.SetParam(197) -- ���سɹ�
    g_AIDebugInfo[216] = '[216] SetParam(State197)'

    -- ���سɹ�
    state = ai.NewState(197)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 128)

    -- ���DEBUFF
    action = ai.NewAction(128, AI_ACTION.CLEAN_DEBUFF)
    action.SetBranch(175)
    g_AIDebugInfo[128] = '[128] CLEAN_DEBUFF()'

    -- ����ϵͳ�޵�
    action = ai.NewAction(175, AI_ACTION.SET_SYSTEM_SHEILD)
    action.SetParam(0)
    action.SetBranch(141)
    g_AIDebugInfo[175] = '[175] SET_SYSTEM_SHEILD(0)'

    -- Npc��׼����ѡ��
    action = ai.NewAction(192, AI_ACTION.NPC_STANDARD_SKILL_SELECTOR)
    action.SetBranch(151, 173)
    g_AIDebugInfo[192] = '[192] NPC_STANDARD_SKILL_SELECTOR()'

    -- Npc���ּ����ͷž���
    action = ai.NewAction(151, AI_ACTION.NPC_KEEP_SKILL_CAST_RANGE)
    action.SetBranch(165, 165)
    g_AIDebugInfo[151] = '[151] NPC_KEEP_SKILL_CAST_RANGE()'

    -- ��������ʱ��
    action = ai.NewAction(165, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(1)
    action.SetBranch(218)
    g_AIDebugInfo[165] = '[165] SET_PRIMARY_TIMER(1)'

    -- ����״̬
    action = ai.NewAction(218, AI_ACTION.SET_STATE)
    action.SetParam(174) -- ս��״̬
    g_AIDebugInfo[218] = '[218] SetParam(State174)'

    -- ս��״̬
    state = ai.NewState(174)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 199)

    -- ѡ���һ��в
    action = ai.NewAction(199, AI_ACTION.SELECT_FIRST_THREAT)
    action.SetBranch(127, 158)
    g_AIDebugInfo[199] = '[199] SELECT_FIRST_THREAT()'

    -- Npc��׼����ѡ��
    action = ai.NewAction(127, AI_ACTION.NPC_STANDARD_SKILL_SELECTOR)
    action.SetBranch(157, 165)
    g_AIDebugInfo[127] = '[127] NPC_STANDARD_SKILL_SELECTOR()'

    -- Npc���ּ����ͷž���
    action = ai.NewAction(157, AI_ACTION.NPC_KEEP_SKILL_CAST_RANGE)
    action.SetBranch(122, 190)
    g_AIDebugInfo[157] = '[157] NPC_KEEP_SKILL_CAST_RANGE()'

    -- ��������ʱ��
    action = ai.NewAction(190, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(0)
    action.SetBranch(220)
    g_AIDebugInfo[190] = '[190] SET_PRIMARY_TIMER(0)'

    -- ����״̬
    action = ai.NewAction(220, AI_ACTION.SET_STATE)
    action.SetParam(120) -- ׷��״̬
    g_AIDebugInfo[220] = '[220] SetParam(State120)'

    -- ׷��״̬
    state = ai.NewState(120)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 184)
    state.HandleEvent(AI_EVENT.ON_TARGET_KILLED, 141)

    -- �ȽϷ��ص����
    action = ai.NewAction(184, AI_ACTION.RETURN_POSITION_DISTANCE_COMPARE)
    action.SetParam(param['EscapeRange'])
    action.SetBranch(158, 157, 157)
    g_AIDebugInfo[184] = '[184] RETURN_POSITION_DISTANCE_COMPARE(param[EscapeRange])'

    -- Npc�ͷ�ѡ������
    action = ai.NewAction(122, AI_ACTION.NPC_CAST_SELECT_SKILL)
    action.SetBranch(165, 133)
    g_AIDebugInfo[122] = '[122] NPC_CAST_SELECT_SKILL()'

    -- ��鼼��ʧ�ܼ���
    action = ai.NewAction(133, AI_ACTION.CHECK_SKILL_FAILED_COUNTER)
    action.SetParam(5)
    action.SetBranch(199, 158)
    g_AIDebugInfo[133] = '[133] CHECK_SKILL_FAILED_COUNTER(5)'

    -- ��������
    action = ai.NewAction(181, AI_ACTION.SEARCH_ENEMY)
    action.SetParam(param['AlertRange'])
    action.SetBranch(163, 202)
    g_AIDebugInfo[181] = '[181] SEARCH_ENEMY(param[AlertRange])'

    -- NPC����
    action = ai.NewAction(202, 2202)
    action.SetBranch(203)
    g_AIDebugInfo[202] = '[202] CustomAction202()'

    -- ��������ʱ��
    action = ai.NewAction(203, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(32)
    action.SetBranch(222)
    g_AIDebugInfo[203] = '[203] SET_PRIMARY_TIMER(32)'

    -- ����״̬
    action = ai.NewAction(222, AI_ACTION.SET_STATE)
    action.SetParam(201) -- ��������
    g_AIDebugInfo[222] = '[222] SetParam(State201)'

    -- ��������
    state = ai.NewState(201)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 141)

    ai.SetInitState(164)
end

-- ���Է���
function AI:DebugOnCallAction(nActiondId, nAIType)
    print('[AI] Call action: ' .. AI[nAIType][nActiondId])
end

-- ��AIͼ���Զ���ű�
function AI:CustomAction202(pNpc, ai)
    -- �����Զ��嶯��ʵ�ֽű�
	local param = AI.g_AIParam[ai.nAIType]
    Dialog:NpcBubbleToNearBy(pNpc.dwId, param.Shout1)
    return 1
end

