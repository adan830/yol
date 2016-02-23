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
    ai.RegisterUserAction(2037, 'CustomAction37')
    ai.RegisterUserAction(2145, 'CustomAction145')
    ai.RegisterUserAction(2156, 'CustomAction156')
    ai.RegisterUserAction(2189, 'CustomAction189')
    ai.RegisterUserAction(2219, 'CustomAction219')

    -- ����-������
    state = ai.NewState(131)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 67)

    -- ��¼ԭ��
    action = ai.NewAction(67, AI_ACTION.RECORD_ORIGIN_POSITION)
    action.SetBranch(13)
    g_AIDebugInfo[67] = '[67] RECORD_ORIGIN_POSITION()'

    -- ��������ʱ��
    action = ai.NewAction(13, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(4)
    action.SetBranch(245)
    g_AIDebugInfo[13] = '[13] SET_PRIMARY_TIMER(4)'

    -- ����״̬
    action = ai.NewAction(245, AI_ACTION.SET_STATE)
    action.SetParam(2) -- ����״̬
    g_AIDebugInfo[245] = '[245] SetParam(State2)'

    -- ����״̬
    state = ai.NewState(2)
    state.HandleEvent(AI_EVENT.ON_ATTACKED, 108)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 57)

    -- ѡ���¼�������
    action = ai.NewAction(108, AI_ACTION.SELECT_EVENT_SRC)
    action.SetBranch(114, 13)
    g_AIDebugInfo[108] = '[108] SELECT_EVENT_SRC()'

    -- ��Ŀ����ӵ���в�б�
    action = ai.NewAction(114, AI_ACTION.ADD_TARGET_TO_THREAT_LIST)
    action.SetBranch(33)
    g_AIDebugInfo[114] = '[114] ADD_TARGET_TO_THREAT_LIST()'

    -- ��¼���ص�
    action = ai.NewAction(33, AI_ACTION.RECORD_RETURN_POSITION)
    action.SetBranch(144)
    g_AIDebugInfo[33] = '[33] RECORD_RETURN_POSITION()'

    -- Npc��ʼ������CD
    action = ai.NewAction(144, AI_ACTION.NPC_INIT_SKILL_CD)
    action.SetBranch(32)
    g_AIDebugInfo[144] = '[144] NPC_INIT_SKILL_CD()'

    -- ��������ʱ��
    action = ai.NewAction(32, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(4)
    action.SetBranch(247)
    g_AIDebugInfo[32] = '[32] SET_PRIMARY_TIMER(4)'

    -- ����״̬
    action = ai.NewAction(247, AI_ACTION.SET_STATE)
    action.SetParam(19) -- ս��״̬
    g_AIDebugInfo[247] = '[247] SetParam(State19)'

    -- ս��״̬
    state = ai.NewState(19)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 99)

    -- ѡ���һ��в
    action = ai.NewAction(99, AI_ACTION.SELECT_FIRST_THREAT)
    action.SetBranch(100, 13)
    g_AIDebugInfo[99] = '[99] SELECT_FIRST_THREAT()'

    -- �������
    action = ai.NewAction(100, AI_ACTION.CHECK_LIFE)
    action.SetParam(70)
    action.SetBranch(145, 145, 61)
    g_AIDebugInfo[100] = '[100] CHECK_LIFE(70)'

    -- ��������ʱ��
    action = ai.NewAction(61, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(4)
    action.SetBranch(249)
    g_AIDebugInfo[61] = '[61] SET_PRIMARY_TIMER(4)'

    -- ����״̬
    action = ai.NewAction(249, AI_ACTION.SET_STATE)
    action.SetParam(73) -- ��ͨ����
    g_AIDebugInfo[249] = '[249] SetParam(State73)'

    -- ��ͨ����
    state = ai.NewState(73)
    state.HandleEvent(AI_EVENT.ON_TARGET_KILLED, 143)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 117)

    -- ����ϵͳ�޵�
    action = ai.NewAction(143, AI_ACTION.SET_SYSTEM_SHEILD)
    action.SetParam(1)
    action.SetBranch(141)
    g_AIDebugInfo[143] = '[143] SET_SYSTEM_SHEILD(1)'

    -- ����
    action = ai.NewAction(141, AI_ACTION.RETURN)
    action.SetParam(0)
    action.SetBranch(42, 42)
    g_AIDebugInfo[141] = '[141] RETURN(0)'

    -- ��������ʱ��
    action = ai.NewAction(42, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(8)
    action.SetBranch(251)
    g_AIDebugInfo[42] = '[42] SET_PRIMARY_TIMER(8)'

    -- ����״̬
    action = ai.NewAction(251, AI_ACTION.SET_STATE)
    action.SetParam(62) -- �޵з���״̬
    g_AIDebugInfo[251] = '[251] SetParam(State62)'

    -- �޵з���״̬
    state = ai.NewState(62)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 125)
    state.HandleEvent(AI_EVENT.ON_PATH_FAILED, 125)

    -- ����
    action = ai.NewAction(125, AI_ACTION.RETURN)
    action.SetParam(1)
    action.SetBranch(123, 123)
    g_AIDebugInfo[125] = '[125] RETURN(1)'

    -- ��������ʱ��
    action = ai.NewAction(123, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(8)
    action.SetBranch(253)
    g_AIDebugInfo[123] = '[123] SET_PRIMARY_TIMER(8)'

    -- ����״̬
    action = ai.NewAction(253, AI_ACTION.SET_STATE)
    action.SetParam(55) -- ���سɹ�
    g_AIDebugInfo[253] = '[253] SetParam(State55)'

    -- ���سɹ�
    state = ai.NewState(55)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 46)

    -- ���DEBUFF
    action = ai.NewAction(46, AI_ACTION.CLEAN_DEBUFF)
    action.SetBranch(5)
    g_AIDebugInfo[46] = '[46] CLEAN_DEBUFF()'

    -- ����ϵͳ�޵�
    action = ai.NewAction(5, AI_ACTION.SET_SYSTEM_SHEILD)
    action.SetParam(0)
    action.SetBranch(13)
    g_AIDebugInfo[5] = '[5] SET_SYSTEM_SHEILD(0)'

    -- ˫ѡ�����
    action = ai.NewAction(117, AI_ACTION.RANDOM_BI_BRANCH)
    action.SetParam(10, 90)
    action.SetBranch(37, 79)
    g_AIDebugInfo[117] = '[117] RANDOM_BI_BRANCH(10, 90)'

    -- NPC����
    action = ai.NewAction(37, 2037)
    action.SetBranch(12)
    g_AIDebugInfo[37] = '[37] CustomAction37()'

    -- ��������ʱ��
    action = ai.NewAction(12, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(4)
    action.SetBranch(255)
    g_AIDebugInfo[12] = '[12] SET_PRIMARY_TIMER(4)'

    -- ����״̬
    action = ai.NewAction(255, AI_ACTION.SET_STATE)
    action.SetParam(116) -- ��������
    g_AIDebugInfo[255] = '[255] SetParam(State116)'

    -- ��������
    state = ai.NewState(116)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 79)

    -- Npc��׼����ѡ��
    action = ai.NewAction(79, AI_ACTION.NPC_STANDARD_SKILL_SELECTOR)
    action.SetBranch(58, 32)
    g_AIDebugInfo[79] = '[79] NPC_STANDARD_SKILL_SELECTOR()'

    -- Npc���ּ����ͷž���
    action = ai.NewAction(58, AI_ACTION.NPC_KEEP_SKILL_CAST_RANGE)
    action.SetBranch(127, 27)
    g_AIDebugInfo[58] = '[58] NPC_KEEP_SKILL_CAST_RANGE()'

    -- Npc�ͷ�ѡ������
    action = ai.NewAction(127, AI_ACTION.NPC_CAST_SELECT_SKILL)
    action.SetBranch(100, 96)
    g_AIDebugInfo[127] = '[127] NPC_CAST_SELECT_SKILL()'

    -- ��鼼��ʧ�ܼ���
    action = ai.NewAction(96, AI_ACTION.CHECK_SKILL_FAILED_COUNTER)
    action.SetParam(50)
    action.SetBranch(100, 143)
    g_AIDebugInfo[96] = '[96] CHECK_SKILL_FAILED_COUNTER(50)'

    -- ��������ʱ��
    action = ai.NewAction(27, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(4)
    action.SetBranch(257)
    g_AIDebugInfo[27] = '[27] SET_PRIMARY_TIMER(4)'

    -- ����״̬
    action = ai.NewAction(257, AI_ACTION.SET_STATE)
    action.SetParam(83) -- ׷��״̬
    g_AIDebugInfo[257] = '[257] SetParam(State83)'

    -- ׷��״̬
    state = ai.NewState(83)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 139)

    -- �ȽϷ��ص����
    action = ai.NewAction(139, AI_ACTION.RETURN_POSITION_DISTANCE_COMPARE)
    action.SetParam(param['EscapeRange'])
    action.SetBranch(143, 58, 58)
    g_AIDebugInfo[139] = '[139] RETURN_POSITION_DISTANCE_COMPARE(param[EscapeRange])'

    -- NPC����
    action = ai.NewAction(145, 2145)
    action.SetBranch(48)
    g_AIDebugInfo[145] = '[145] CustomAction145()'

    -- ��������ʱ��
    action = ai.NewAction(48, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(24)
    action.SetBranch(259)
    g_AIDebugInfo[48] = '[48] SET_PRIMARY_TIMER(24)'

    -- ����״̬
    action = ai.NewAction(259, AI_ACTION.SET_STATE)
    action.SetParam(110) -- ��������
    g_AIDebugInfo[259] = '[259] SetParam(State110)'

    -- ��������
    state = ai.NewState(110)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 146)

    -- �ͷż���
    action = ai.NewAction(146, AI_ACTION.CAST_SKILL)
    action.SetParam(385, 1)
    action.SetBranch(71, 71)
    g_AIDebugInfo[146] = '[146] CAST_SKILL(385, 1)'

    -- ��������ʱ��
    action = ai.NewAction(71, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(32)
    action.SetBranch(261)
    g_AIDebugInfo[71] = '[71] SET_PRIMARY_TIMER(32)'

    -- ����״̬
    action = ai.NewAction(261, AI_ACTION.SET_STATE)
    action.SetParam(36) -- ������
    g_AIDebugInfo[261] = '[261] SetParam(State36)'

    -- ������
    state = ai.NewState(36)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 235)

    -- �������
    action = ai.NewAction(235, AI_ACTION.CHECK_LIFE)
    action.SetParam(40)
    action.SetBranch(189, 189, 196)
    g_AIDebugInfo[235] = '[235] CHECK_LIFE(40)'

    -- NPC����
    action = ai.NewAction(189, 2189)
    action.SetBranch(191)
    g_AIDebugInfo[189] = '[189] CustomAction189()'

    -- ��������ʱ��
    action = ai.NewAction(191, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(24)
    action.SetBranch(263)
    g_AIDebugInfo[191] = '[191] SET_PRIMARY_TIMER(24)'

    -- ����״̬
    action = ai.NewAction(263, AI_ACTION.SET_STATE)
    action.SetParam(211) -- ��������
    g_AIDebugInfo[263] = '[263] SetParam(State211)'

    -- ��������
    state = ai.NewState(211)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 203)

    -- �ͷż���
    action = ai.NewAction(203, AI_ACTION.CAST_SKILL)
    action.SetParam(425, 1)
    action.SetBranch(157, 157)
    g_AIDebugInfo[203] = '[203] CAST_SKILL(425, 1)'

    -- ��������ʱ��
    action = ai.NewAction(157, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(32)
    action.SetBranch(265)
    g_AIDebugInfo[157] = '[157] SET_PRIMARY_TIMER(32)'

    -- ����״̬
    action = ai.NewAction(265, AI_ACTION.SET_STATE)
    action.SetParam(227) -- ������
    g_AIDebugInfo[265] = '[265] SetParam(State227)'

    -- ������
    state = ai.NewState(227)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 200)

    -- ��������ʱ��
    action = ai.NewAction(200, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(16)
    action.SetBranch(267)
    g_AIDebugInfo[200] = '[200] SET_PRIMARY_TIMER(16)'

    -- ����״̬
    action = ai.NewAction(267, AI_ACTION.SET_STATE)
    action.SetParam(226) -- ����״̬
    g_AIDebugInfo[267] = '[267] SetParam(State226)'

    -- ����״̬
    state = ai.NewState(226)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 150)
    state.HandleEvent(AI_EVENT.ON_TARGET_KILLED, 143)

    -- ˫ѡ�����
    action = ai.NewAction(150, AI_ACTION.RANDOM_BI_BRANCH)
    action.SetParam(10, 90)
    action.SetBranch(156, 152)
    g_AIDebugInfo[150] = '[150] RANDOM_BI_BRANCH(10, 90)'

    -- NPC����
    action = ai.NewAction(156, 2156)
    action.SetBranch(208)
    g_AIDebugInfo[156] = '[156] CustomAction156()'

    -- ��������ʱ��
    action = ai.NewAction(208, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(4)
    action.SetBranch(269)
    g_AIDebugInfo[208] = '[208] SET_PRIMARY_TIMER(4)'

    -- ����״̬
    action = ai.NewAction(269, AI_ACTION.SET_STATE)
    action.SetParam(230) -- ��������
    g_AIDebugInfo[269] = '[269] SetParam(State230)'

    -- ��������
    state = ai.NewState(230)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 152)

    -- Npc��׼����ѡ��
    action = ai.NewAction(152, AI_ACTION.NPC_STANDARD_SKILL_SELECTOR)
    action.SetBranch(217, 200)
    g_AIDebugInfo[152] = '[152] NPC_STANDARD_SKILL_SELECTOR()'

    -- ˫ѡ�����
    action = ai.NewAction(217, AI_ACTION.RANDOM_BI_BRANCH)
    action.SetParam(80, 20)
    action.SetBranch(231, 169)
    g_AIDebugInfo[217] = '[217] RANDOM_BI_BRANCH(80, 20)'

    -- �ͷż���
    action = ai.NewAction(169, AI_ACTION.CAST_SKILL)
    action.SetParam(425, 1)
    action.SetBranch(190, 223)
    g_AIDebugInfo[169] = '[169] CAST_SKILL(425, 1)'

    -- ��������ʱ��
    action = ai.NewAction(190, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(16)
    action.SetBranch(271)
    g_AIDebugInfo[190] = '[190] SET_PRIMARY_TIMER(16)'

    -- ����״̬
    action = ai.NewAction(271, AI_ACTION.SET_STATE)
    action.SetParam(197) -- ��ת����
    g_AIDebugInfo[271] = '[271] SetParam(State197)'

    -- ��ת����
    state = ai.NewState(197)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 200)

    -- ��鼼��ʧ�ܼ���
    action = ai.NewAction(223, AI_ACTION.CHECK_SKILL_FAILED_COUNTER)
    action.SetParam(50)
    action.SetBranch(200, 143)
    g_AIDebugInfo[223] = '[223] CHECK_SKILL_FAILED_COUNTER(50)'

    -- Npc���ּ����ͷž���
    action = ai.NewAction(231, AI_ACTION.NPC_KEEP_SKILL_CAST_RANGE)
    action.SetBranch(206, 210)
    g_AIDebugInfo[231] = '[231] NPC_KEEP_SKILL_CAST_RANGE()'

    -- ��������ʱ��
    action = ai.NewAction(210, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(4)
    action.SetBranch(273)
    g_AIDebugInfo[210] = '[210] SET_PRIMARY_TIMER(4)'

    -- ����״̬
    action = ai.NewAction(273, AI_ACTION.SET_STATE)
    action.SetParam(202) -- ׷��״̬
    g_AIDebugInfo[273] = '[273] SetParam(State202)'

    -- ׷��״̬
    state = ai.NewState(202)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 153)

    -- �ȽϷ��ص����
    action = ai.NewAction(153, AI_ACTION.RETURN_POSITION_DISTANCE_COMPARE)
    action.SetParam(param['EscapeRange'])
    action.SetBranch(143, 231, 231)
    g_AIDebugInfo[153] = '[153] RETURN_POSITION_DISTANCE_COMPARE(param[EscapeRange])'

    -- Npc�ͷ�ѡ������
    action = ai.NewAction(206, AI_ACTION.NPC_CAST_SELECT_SKILL)
    action.SetBranch(200, 223)
    g_AIDebugInfo[206] = '[206] NPC_CAST_SELECT_SKILL()'

    -- ��������ʱ��
    action = ai.NewAction(196, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(4)
    action.SetBranch(275)
    g_AIDebugInfo[196] = '[196] SET_PRIMARY_TIMER(4)'

    -- ����״̬
    action = ai.NewAction(275, AI_ACTION.SET_STATE)
    action.SetParam(209) -- ��ͨ����
    g_AIDebugInfo[275] = '[275] SetParam(State209)'

    -- ��ͨ����
    state = ai.NewState(209)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 185)
    state.HandleEvent(AI_EVENT.ON_TARGET_KILLED, 143)

    -- ˫ѡ�����
    action = ai.NewAction(185, AI_ACTION.RANDOM_BI_BRANCH)
    action.SetParam(10, 90)
    action.SetBranch(219, 228)
    g_AIDebugInfo[185] = '[185] RANDOM_BI_BRANCH(10, 90)'

    -- NPC����
    action = ai.NewAction(219, 2219)
    action.SetBranch(176)
    g_AIDebugInfo[219] = '[219] CustomAction219()'

    -- ��������ʱ��
    action = ai.NewAction(176, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(4)
    action.SetBranch(277)
    g_AIDebugInfo[176] = '[176] SET_PRIMARY_TIMER(4)'

    -- ����״̬
    action = ai.NewAction(277, AI_ACTION.SET_STATE)
    action.SetParam(159) -- ��������
    g_AIDebugInfo[277] = '[277] SetParam(State159)'

    -- ��������
    state = ai.NewState(159)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 228)

    -- Npc��׼����ѡ��
    action = ai.NewAction(228, AI_ACTION.NPC_STANDARD_SKILL_SELECTOR)
    action.SetBranch(192, 71)
    g_AIDebugInfo[228] = '[228] NPC_STANDARD_SKILL_SELECTOR()'

    -- Npc���ּ����ͷž���
    action = ai.NewAction(192, AI_ACTION.NPC_KEEP_SKILL_CAST_RANGE)
    action.SetBranch(158, 168)
    g_AIDebugInfo[192] = '[192] NPC_KEEP_SKILL_CAST_RANGE()'

    -- Npc�ͷ�ѡ������
    action = ai.NewAction(158, AI_ACTION.NPC_CAST_SELECT_SKILL)
    action.SetBranch(235, 172)
    g_AIDebugInfo[158] = '[158] NPC_CAST_SELECT_SKILL()'

    -- ��鼼��ʧ�ܼ���
    action = ai.NewAction(172, AI_ACTION.CHECK_SKILL_FAILED_COUNTER)
    action.SetParam(50)
    action.SetBranch(235, 143)
    g_AIDebugInfo[172] = '[172] CHECK_SKILL_FAILED_COUNTER(50)'

    -- ��������ʱ��
    action = ai.NewAction(168, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(4)
    action.SetBranch(279)
    g_AIDebugInfo[168] = '[168] SET_PRIMARY_TIMER(4)'

    -- ����״̬
    action = ai.NewAction(279, AI_ACTION.SET_STATE)
    action.SetParam(164) -- ׷��״̬
    g_AIDebugInfo[279] = '[279] SetParam(State164)'

    -- ׷��״̬
    state = ai.NewState(164)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 174)

    -- �ȽϷ��ص����
    action = ai.NewAction(174, AI_ACTION.RETURN_POSITION_DISTANCE_COMPARE)
    action.SetParam(param['EscapeRange'])
    action.SetBranch(143, 192, 192)
    g_AIDebugInfo[174] = '[174] RETURN_POSITION_DISTANCE_COMPARE(param[EscapeRange])'

    -- ��������
    action = ai.NewAction(57, AI_ACTION.SEARCH_ENEMY)
    action.SetParam(param['AlertRange'])
    action.SetBranch(114, 13)
    g_AIDebugInfo[57] = '[57] SEARCH_ENEMY(param[AlertRange])'

    ai.SetInitState(131)
end

-- ���Է���
function AI:DebugOnCallAction(nActiondId, nAIType)
    print('[AI] Call action: ' .. AI[nAIType][nActiondId])
end

-- ��AIͼ���Զ���ű�
function AI:CustomAction37(pNpc, ai)
    -- �����Զ��嶯��ʵ�ֽű�
	local param = AI.g_AIParam[ai.nAIType]
    Dialog:NpcBubbleToNearBy(pNpc.dwId, param.Shout2)
    return 1
end

function AI:CustomAction145(pNpc, ai)
    -- �����Զ��嶯��ʵ�ֽű�
	local param = AI.g_AIParam[ai.nAIType]
    Dialog:NpcBubbleToNearBy(pNpc.dwId, param.Shout1)
    return 1
end

function AI:CustomAction189(pNpc, ai)
    -- �����Զ��嶯��ʵ�ֽű�
	local param = AI.g_AIParam[ai.nAIType]
    Dialog:NpcBubbleToNearBy(pNpc.dwId, param.Shout3)
    return 1
end

function AI:CustomAction156(pNpc, ai)
    -- �����Զ��嶯��ʵ�ֽű�
	local param = AI.g_AIParam[ai.nAIType]
    Dialog:NpcBubbleToNearBy(pNpc.dwId, param.Shout2)
    return 1
end


function AI:CustomAction219(pNpc, ai)
    -- �����Զ��嶯��ʵ�ֽű�
	local param = AI.g_AIParam[ai.nAIType]
    Dialog:NpcBubbleToNearBy(pNpc.dwId, param.Shout2)
    return 1
end


