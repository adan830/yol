-- ��д�ߣ�lidianyi
-- �汾�ţ�22

Include('script/ai/customfunctions.lua')
Include('script/ai/ai_param.lua')
Include('script/ai/argumentstrings.lua')

local g_AIDebugInfo = {}

-- �Զ��帽�ӽű�
 

function AI:Setup(ai)
    local state
    local action
    local param = AI.g_AIParam[ai.nAIType]
    AI[ai.nAIType] = g_AIDebugInfo

    -- ע���Զ��嶯��
    ai.RegisterUserAction(2098, 'AI:xmhj_XiaoLiGoToPatrol')

    -- ��ʼ
    state = ai.NewState(1)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 2)

    -- ��������ʱ��
    action = ai.NewAction(2, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(4)
    action.SetBranch(107)
    g_AIDebugInfo[2] = '[2] SET_PRIMARY_TIMER(4)'

    -- ����״̬
    action = ai.NewAction(107, AI_ACTION.SET_STATE)
    action.SetParam(4) -- ��״̬
    g_AIDebugInfo[107] = '[107] SetParam(State4)'

    -- ��״̬
    state = ai.NewState(4)
    state.HandleEvent(AI_EVENT.ON_DIALOG, 6)

    -- ѡ���¼�������
    action = ai.NewAction(6, AI_ACTION.SELECT_EVENT_SRC)
    action.SetBranch(8, 98)
    g_AIDebugInfo[6] = '[6] SELECT_EVENT_SRC()'

    -- ����Ŀ��
    action = ai.NewAction(8, AI_ACTION.FACE_TARGET)
    action.SetParam(0)
    action.SetBranch(98)
    g_AIDebugInfo[8] = '[8] FACE_TARGET(0)'

    -- �Զ��嶯��98
    action = ai.NewAction(98, 2098)
    action.SetBranch(16, 109)
    g_AIDebugInfo[98] = '[98] AI:xmhj_XiaoLiGoToPatrol()'

    -- ����״̬
    action = ai.NewAction(109, AI_ACTION.SET_STATE)
    action.SetParam(4) -- ��״̬
    g_AIDebugInfo[109] = '[109] SetParam(State4)'

    -- ����Ѳ��·��
    action = ai.NewAction(16, AI_ACTION.ENTER_PATROL_PATH)
    action.SetParam(param['PatrolPathID'], 0)
    action.SetBranch(18)
    g_AIDebugInfo[16] = '[16] ENTER_PATROL_PATH(param[PatrolPathID], 0)'

    -- ��������ʱ��
    action = ai.NewAction(18, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(4)
    action.SetBranch(111)
    g_AIDebugInfo[18] = '[18] SET_PRIMARY_TIMER(4)'

    -- ����״̬
    action = ai.NewAction(111, AI_ACTION.SET_STATE)
    action.SetParam(20) -- ��״̬
    g_AIDebugInfo[111] = '[111] SetParam(State20)'

    -- ��״̬
    state = ai.NewState(20)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 22)
    state.HandleEvent(AI_EVENT.ON_SECONDARY_TIMER, 37)
    state.HandleEvent(AI_EVENT.ON_ATTACKED, 44)
    state.HandleEvent(AI_EVENT.ON_DIALOG, 37)

    -- ��������
    action = ai.NewAction(22, AI_ACTION.SEARCH_ENEMY)
    action.SetParam(1)
    action.SetBranch(29, 37)
    g_AIDebugInfo[22] = '[22] SEARCH_ENEMY(1)'

    -- ��Ŀ����ӵ���в�б�
    action = ai.NewAction(29, AI_ACTION.ADD_TARGET_TO_THREAT_LIST)
    action.SetBranch(31)
    g_AIDebugInfo[29] = '[29] ADD_TARGET_TO_THREAT_LIST()'

    -- ��¼���ص�
    action = ai.NewAction(31, AI_ACTION.RECORD_RETURN_POSITION)
    action.SetBranch(33)
    g_AIDebugInfo[31] = '[31] RECORD_RETURN_POSITION()'

    -- Npc��ʼ������CD
    action = ai.NewAction(33, AI_ACTION.NPC_INIT_SKILL_CD)
    action.SetBranch(51)
    g_AIDebugInfo[33] = '[33] NPC_INIT_SKILL_CD()'

    -- ��������ʱ��
    action = ai.NewAction(51, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(4)
    action.SetBranch(113)
    g_AIDebugInfo[51] = '[51] SET_PRIMARY_TIMER(4)'

    -- ����״̬
    action = ai.NewAction(113, AI_ACTION.SET_STATE)
    action.SetParam(53) -- ս��״̬
    g_AIDebugInfo[113] = '[113] SetParam(State53)'

    -- ս��״̬
    state = ai.NewState(53)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 58)
    state.HandleEvent(AI_EVENT.ON_DIALOG, 58)

    -- ѡ���һ��в
    action = ai.NewAction(58, AI_ACTION.SELECT_FIRST_THREAT)
    action.SetBranch(60, 84)
    g_AIDebugInfo[58] = '[58] SELECT_FIRST_THREAT()'

    -- Npc��׼����ѡ��
    action = ai.NewAction(60, AI_ACTION.NPC_STANDARD_SKILL_SELECTOR)
    action.SetBranch(62, 51)
    g_AIDebugInfo[60] = '[60] NPC_STANDARD_SKILL_SELECTOR()'

    -- Npc���ּ����ͷž���
    action = ai.NewAction(62, AI_ACTION.NPC_KEEP_SKILL_CAST_RANGE)
    action.SetBranch(64, 68)
    g_AIDebugInfo[62] = '[62] NPC_KEEP_SKILL_CAST_RANGE()'

    -- Npc�ͷ�ѡ������
    action = ai.NewAction(64, AI_ACTION.NPC_CAST_SELECT_SKILL)
    action.SetBranch(51, 51)
    g_AIDebugInfo[64] = '[64] NPC_CAST_SELECT_SKILL()'

    -- ��������ʱ��
    action = ai.NewAction(68, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(4)
    action.SetBranch(115)
    g_AIDebugInfo[68] = '[68] SET_PRIMARY_TIMER(4)'

    -- ����״̬
    action = ai.NewAction(115, AI_ACTION.SET_STATE)
    action.SetParam(70) -- ׷��
    g_AIDebugInfo[115] = '[115] SetParam(State70)'

    -- ׷��
    state = ai.NewState(70)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 62)
    state.HandleEvent(AI_EVENT.ON_DIALOG, 62)

    -- ����ϵͳ�޵�
    action = ai.NewAction(84, AI_ACTION.SET_SYSTEM_SHEILD)
    action.SetParam(1)
    action.SetBranch(75)
    g_AIDebugInfo[84] = '[84] SET_SYSTEM_SHEILD(1)'

    -- ����
    action = ai.NewAction(75, AI_ACTION.RETURN)
    action.SetParam(0)
    action.SetBranch(74, 74)
    g_AIDebugInfo[75] = '[75] RETURN(0)'

    -- ��������ʱ��
    action = ai.NewAction(74, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(80)
    action.SetBranch(117)
    g_AIDebugInfo[74] = '[74] SET_PRIMARY_TIMER(80)'

    -- ����״̬
    action = ai.NewAction(117, AI_ACTION.SET_STATE)
    action.SetParam(78) -- �޵з���״̬
    g_AIDebugInfo[117] = '[117] SetParam(State78)'

    -- �޵з���״̬
    state = ai.NewState(78)
    state.HandleEvent(AI_EVENT.ON_PATH_FAILED, 88)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 88)
    state.HandleEvent(AI_EVENT.ON_DIALOG, 88)

    -- ����
    action = ai.NewAction(88, AI_ACTION.RETURN)
    action.SetParam(1)
    action.SetBranch(80, 80)
    g_AIDebugInfo[88] = '[88] RETURN(1)'

    -- ��������ʱ��
    action = ai.NewAction(80, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(32)
    action.SetBranch(119)
    g_AIDebugInfo[80] = '[80] SET_PRIMARY_TIMER(32)'

    -- ����״̬
    action = ai.NewAction(119, AI_ACTION.SET_STATE)
    action.SetParam(90) -- ���سɹ�
    g_AIDebugInfo[119] = '[119] SetParam(State90)'

    -- ���سɹ�
    state = ai.NewState(90)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 93)
    state.HandleEvent(AI_EVENT.ON_DIALOG, 93)

    -- ���DEBUFF
    action = ai.NewAction(93, AI_ACTION.CLEAN_DEBUFF)
    action.SetBranch(79)
    g_AIDebugInfo[93] = '[93] CLEAN_DEBUFF()'

    -- ����ϵͳ�޵�
    action = ai.NewAction(79, AI_ACTION.SET_SYSTEM_SHEILD)
    action.SetParam(0)
    action.SetBranch(37)
    g_AIDebugInfo[79] = '[79] SET_SYSTEM_SHEILD(0)'

    -- Ѳ��
    action = ai.NewAction(37, AI_ACTION.DO_PATROL)
    action.SetBranch(121, 123)
    g_AIDebugInfo[37] = '[37] DO_PATROL()'

    -- ����״̬
    action = ai.NewAction(121, AI_ACTION.SET_STATE)
    action.SetParam(20) -- ��״̬
    g_AIDebugInfo[121] = '[121] SetParam(State20)'

    -- ����״̬
    action = ai.NewAction(123, AI_ACTION.SET_STATE)
    action.SetParam(20) -- ��״̬
    g_AIDebugInfo[123] = '[123] SetParam(State20)'

    -- ѡ���¼�������
    action = ai.NewAction(44, AI_ACTION.SELECT_EVENT_SRC)
    action.SetBranch(29, 37)
    g_AIDebugInfo[44] = '[44] SELECT_EVENT_SRC()'

    ai.SetInitState(1)
end

-- ���Է���
function AI:DebugOnCallAction(nActiondId, nAIType)
    print('[AI] Call action: ' .. AI[nAIType][nActiondId])
end

-- ��AIͼ���Զ���ű�
function AI:xmhj_XiaoLiGoToPatrol(pNpc, actionData)
	local tbPos = pNpc.GetPosition();
	local pTarget = KGameBase.GetNpcByNickName(tbPos.dwSceneId,"tieshi");
	if not pTarget then
		return 1
	else
		Dialog:Say(AI.ARGUMENT_STRING_TABLE[16])
		return 2
	end
end

