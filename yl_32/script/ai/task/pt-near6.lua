-- ��д�ߣ�hejingxian
-- �汾�ţ�6

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
    state = ai.NewState(15)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 27)

    -- ��¼ԭ��
    action = ai.NewAction(27, AI_ACTION.RECORD_ORIGIN_POSITION)
    action.SetBranch(7)
    g_AIDebugInfo[27] = '[27] RECORD_ORIGIN_POSITION()'

    -- ����Ѳ��·��
    action = ai.NewAction(7, AI_ACTION.ENTER_PATROL_PATH)
    action.SetParam(param['PatrolPathID'], param['PatrolOrderIndex'])
    action.SetBranch(29)
    g_AIDebugInfo[7] = '[7] ENTER_PATROL_PATH(param[PatrolPathID], param[PatrolOrderIndex])'

    -- Ѳ��
    action = ai.NewAction(29, AI_ACTION.DO_PATROL)
    action.SetBranch(35, 43)
    g_AIDebugInfo[29] = '[29] DO_PATROL()'

    -- ��������ʱ��
    action = ai.NewAction(35, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(48)
    action.SetBranch(107)
    g_AIDebugInfo[35] = '[35] SET_PRIMARY_TIMER(48)'

    -- ����״̬
    action = ai.NewAction(107, AI_ACTION.SET_STATE)
    action.SetParam(33) -- Ѱ·����
    g_AIDebugInfo[107] = '[107] SetParam(State33)'

    -- Ѱ·����
    state = ai.NewState(33)
    state.HandleEvent(AI_EVENT.ON_SECONDARY_TIMER, 79)
    state.HandleEvent(AI_EVENT.ON_PATH_FAILED, 29)
    state.HandleEvent(AI_EVENT.ON_PATH_SUCCESS, 29)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 79)
    state.HandleEvent(AI_EVENT.ON_ATTACKED, 72)

    -- ��������
    action = ai.NewAction(79, AI_ACTION.SEARCH_ENEMY)
    action.SetParam(param['AlertRange'])
    action.SetBranch(25, 35)
    g_AIDebugInfo[79] = '[79] SEARCH_ENEMY(param[AlertRange])'

    -- ��Ŀ����ӵ���в�б�
    action = ai.NewAction(25, AI_ACTION.ADD_TARGET_TO_THREAT_LIST)
    action.SetBranch(71)
    g_AIDebugInfo[25] = '[25] ADD_TARGET_TO_THREAT_LIST()'

    -- ��¼���ص�
    action = ai.NewAction(71, AI_ACTION.RECORD_RETURN_POSITION)
    action.SetBranch(5)
    g_AIDebugInfo[71] = '[71] RECORD_RETURN_POSITION()'

    -- Npc��ʼ������CD
    action = ai.NewAction(5, AI_ACTION.NPC_INIT_SKILL_CD)
    action.SetBranch(44)
    g_AIDebugInfo[5] = '[5] NPC_INIT_SKILL_CD()'

    -- ��������ʱ��
    action = ai.NewAction(44, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(0)
    action.SetBranch(109)
    g_AIDebugInfo[44] = '[44] SET_PRIMARY_TIMER(0)'

    -- ����״̬
    action = ai.NewAction(109, AI_ACTION.SET_STATE)
    action.SetParam(47) -- ս��״̬
    g_AIDebugInfo[109] = '[109] SetParam(State47)'

    -- ս��״̬
    state = ai.NewState(47)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 66)

    -- ѡ���һ��в
    action = ai.NewAction(66, AI_ACTION.SELECT_FIRST_THREAT)
    action.SetBranch(55, 58)
    g_AIDebugInfo[66] = '[66] SELECT_FIRST_THREAT()'

    -- Npc��׼����ѡ��
    action = ai.NewAction(55, AI_ACTION.NPC_STANDARD_SKILL_SELECTOR)
    action.SetBranch(46, 44)
    g_AIDebugInfo[55] = '[55] NPC_STANDARD_SKILL_SELECTOR()'

    -- Npc���ּ����ͷž���
    action = ai.NewAction(46, AI_ACTION.NPC_KEEP_SKILL_CAST_RANGE)
    action.SetBranch(16, 20)
    g_AIDebugInfo[46] = '[46] NPC_KEEP_SKILL_CAST_RANGE()'

    -- Npc�ͷ�ѡ������
    action = ai.NewAction(16, AI_ACTION.NPC_CAST_SELECT_SKILL)
    action.SetBranch(44, 30)
    g_AIDebugInfo[16] = '[16] NPC_CAST_SELECT_SKILL()'

    -- ��鼼��ʧ�ܼ���
    action = ai.NewAction(30, AI_ACTION.CHECK_SKILL_FAILED_COUNTER)
    action.SetParam(5)
    action.SetBranch(66, 58)
    g_AIDebugInfo[30] = '[30] CHECK_SKILL_FAILED_COUNTER(5)'

    -- ����ϵͳ�޵�
    action = ai.NewAction(58, AI_ACTION.SET_SYSTEM_SHEILD)
    action.SetParam(1)
    action.SetBranch(81)
    g_AIDebugInfo[58] = '[58] SET_SYSTEM_SHEILD(1)'

    -- վ��
    action = ai.NewAction(81, AI_ACTION.STAND)
    action.SetBranch(39)
    g_AIDebugInfo[81] = '[81] STAND()'

    -- ��������ʱ��
    action = ai.NewAction(39, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(8)
    action.SetBranch(111)
    g_AIDebugInfo[39] = '[39] SET_PRIMARY_TIMER(8)'

    -- ����״̬
    action = ai.NewAction(111, AI_ACTION.SET_STATE)
    action.SetParam(37) -- �޵з���״̬
    g_AIDebugInfo[111] = '[111] SetParam(State37)'

    -- �޵з���״̬
    state = ai.NewState(37)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 83)

    -- վ��
    action = ai.NewAction(83, AI_ACTION.STAND)
    action.SetBranch(78)
    g_AIDebugInfo[83] = '[83] STAND()'

    -- ��������ʱ��
    action = ai.NewAction(78, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(8)
    action.SetBranch(113)
    g_AIDebugInfo[78] = '[78] SET_PRIMARY_TIMER(8)'

    -- ����״̬
    action = ai.NewAction(113, AI_ACTION.SET_STATE)
    action.SetParam(63) -- ���سɹ�
    g_AIDebugInfo[113] = '[113] SetParam(State63)'

    -- ���سɹ�
    state = ai.NewState(63)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 70)

    -- ���DEBUFF
    action = ai.NewAction(70, AI_ACTION.CLEAN_DEBUFF)
    action.SetBranch(32)
    g_AIDebugInfo[70] = '[70] CLEAN_DEBUFF()'

    -- ����ϵͳ�޵�
    action = ai.NewAction(32, AI_ACTION.SET_SYSTEM_SHEILD)
    action.SetParam(0)
    action.SetBranch(35)
    g_AIDebugInfo[32] = '[32] SET_SYSTEM_SHEILD(0)'

    -- ��������ʱ��
    action = ai.NewAction(20, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(0)
    action.SetBranch(115)
    g_AIDebugInfo[20] = '[20] SET_PRIMARY_TIMER(0)'

    -- ����״̬
    action = ai.NewAction(115, AI_ACTION.SET_STATE)
    action.SetParam(64) -- ׷��״̬
    g_AIDebugInfo[115] = '[115] SetParam(State64)'

    -- ׷��״̬
    state = ai.NewState(64)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 62)
    state.HandleEvent(AI_EVENT.ON_TARGET_KILLED, 58)

    -- �ȽϷ��ص����
    action = ai.NewAction(62, AI_ACTION.RETURN_POSITION_DISTANCE_COMPARE)
    action.SetParam(param['EscapeRange'])
    action.SetBranch(58, 46, 46)
    g_AIDebugInfo[62] = '[62] RETURN_POSITION_DISTANCE_COMPARE(param[EscapeRange])'

    -- ѡ���¼�������
    action = ai.NewAction(72, AI_ACTION.SELECT_EVENT_SRC)
    action.SetBranch(25, 58)
    g_AIDebugInfo[72] = '[72] SELECT_EVENT_SRC()'

    -- ���ø���ʱ��
    action = ai.NewAction(43, AI_ACTION.SET_SECONDARY_TIMER)
    action.SetParam(16)
    action.SetBranch(35)
    g_AIDebugInfo[43] = '[43] SET_SECONDARY_TIMER(16)'

    ai.SetInitState(15)
end

-- ���Է���
function AI:DebugOnCallAction(nActiondId, nAIType)
    print('[AI] Call action: ' .. AI[nAIType][nActiondId])
end
