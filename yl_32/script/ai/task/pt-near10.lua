-- ��д�ߣ�hejingxian
-- �汾�ţ�13

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
    ai.RegisterUserAction(2007, 'AI:CustomAction7')
    ai.RegisterUserAction(2119, 'AI:CustomAction119')

    -- ��ʼ
    state = ai.NewState(2)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 36)

    -- ��¼ԭ��
    action = ai.NewAction(36, AI_ACTION.RECORD_ORIGIN_POSITION)
    action.SetBranch(3)
    g_AIDebugInfo[36] = '[36] RECORD_ORIGIN_POSITION()'

    -- ��������ʱ��
    action = ai.NewAction(3, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(4)
    action.SetBranch(127)
    g_AIDebugInfo[3] = '[3] SET_PRIMARY_TIMER(4)'

    -- ����״̬
    action = ai.NewAction(127, AI_ACTION.SET_STATE)
    action.SetParam(5) -- ���Լ��ż���
    g_AIDebugInfo[127] = '[127] SetParam(State5)'

    -- ���Լ��ż���
    state = ai.NewState(5)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 7)

    -- ѡ���Լ�
    action = ai.NewAction(7, 2007)
    action.SetBranch(33)
    g_AIDebugInfo[7] = '[7] AI:CustomAction7()'

    -- �ͷż���
    action = ai.NewAction(33, AI_ACTION.CAST_SKILL)
    action.SetParam(389, 1)
    action.SetBranch(15, 15)
    g_AIDebugInfo[33] = '[33] CAST_SKILL(389, 1)'

    -- ��������ʱ��
    action = ai.NewAction(15, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(4)
    action.SetBranch(129)
    g_AIDebugInfo[15] = '[15] SET_PRIMARY_TIMER(4)'

    -- ����״̬
    action = ai.NewAction(129, AI_ACTION.SET_STATE)
    action.SetParam(14) -- ��������
    g_AIDebugInfo[129] = '[129] SetParam(State14)'

    -- ��������
    state = ai.NewState(14)
    state.HandleEvent(AI_EVENT.ON_ATTACKED, 38)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 40)

    -- ѡ���¼�������
    action = ai.NewAction(38, AI_ACTION.SELECT_EVENT_SRC)
    action.SetBranch(42, 104)
    g_AIDebugInfo[38] = '[38] SELECT_EVENT_SRC()'

    -- ��Ŀ����ӵ���в�б�
    action = ai.NewAction(42, AI_ACTION.ADD_TARGET_TO_THREAT_LIST)
    action.SetBranch(45)
    g_AIDebugInfo[42] = '[42] ADD_TARGET_TO_THREAT_LIST()'

    -- ��¼���ص�
    action = ai.NewAction(45, AI_ACTION.RECORD_RETURN_POSITION)
    action.SetBranch(46)
    g_AIDebugInfo[45] = '[45] RECORD_RETURN_POSITION()'

    -- Npc��ʼ������CD
    action = ai.NewAction(46, AI_ACTION.NPC_INIT_SKILL_CD)
    action.SetBranch(57)
    g_AIDebugInfo[46] = '[46] NPC_INIT_SKILL_CD()'

    -- ��������ʱ��
    action = ai.NewAction(57, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(1)
    action.SetBranch(131)
    g_AIDebugInfo[57] = '[57] SET_PRIMARY_TIMER(1)'

    -- ����״̬
    action = ai.NewAction(131, AI_ACTION.SET_STATE)
    action.SetParam(96) -- ս��״̬
    g_AIDebugInfo[131] = '[131] SetParam(State96)'

    -- ս��״̬
    state = ai.NewState(96)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 72)

    -- ѡ���һ��в
    action = ai.NewAction(72, AI_ACTION.SELECT_FIRST_THREAT)
    action.SetBranch(52, 104)
    g_AIDebugInfo[72] = '[72] SELECT_FIRST_THREAT()'

    -- Npc��׼����ѡ��
    action = ai.NewAction(52, AI_ACTION.NPC_STANDARD_SKILL_SELECTOR)
    action.SetBranch(120, 57)
    g_AIDebugInfo[52] = '[52] NPC_STANDARD_SKILL_SELECTOR()'

    -- ˫ѡ�����
    action = ai.NewAction(120, AI_ACTION.RANDOM_BI_BRANCH)
    action.SetParam(10, 90)
    action.SetBranch(119, 71)
    g_AIDebugInfo[120] = '[120] RANDOM_BI_BRANCH(10, 90)'

    -- NPC����
    action = ai.NewAction(119, 2119)
    action.SetBranch(118)
    g_AIDebugInfo[119] = '[119] AI:CustomAction119()'

    -- ��������ʱ��
    action = ai.NewAction(118, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(0)
    action.SetBranch(133)
    g_AIDebugInfo[118] = '[118] SET_PRIMARY_TIMER(0)'

    -- ����״̬
    action = ai.NewAction(133, AI_ACTION.SET_STATE)
    action.SetParam(117) -- ��������
    g_AIDebugInfo[133] = '[133] SetParam(State117)'

    -- ��������
    state = ai.NewState(117)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 71)

    -- Npc���ּ����ͷž���
    action = ai.NewAction(71, AI_ACTION.NPC_KEEP_SKILL_CAST_RANGE)
    action.SetBranch(108, 75)
    g_AIDebugInfo[71] = '[71] NPC_KEEP_SKILL_CAST_RANGE()'

    -- Npc�ͷ�ѡ������
    action = ai.NewAction(108, AI_ACTION.NPC_CAST_SELECT_SKILL)
    action.SetBranch(57, 95)
    g_AIDebugInfo[108] = '[108] NPC_CAST_SELECT_SKILL()'

    -- ��鼼��ʧ�ܼ���
    action = ai.NewAction(95, AI_ACTION.CHECK_SKILL_FAILED_COUNTER)
    action.SetParam(5)
    action.SetBranch(72, 104)
    g_AIDebugInfo[95] = '[95] CHECK_SKILL_FAILED_COUNTER(5)'

    -- ����ϵͳ�޵�
    action = ai.NewAction(104, AI_ACTION.SET_SYSTEM_SHEILD)
    action.SetParam(1)
    action.SetBranch(61)
    g_AIDebugInfo[104] = '[104] SET_SYSTEM_SHEILD(1)'

    -- ����
    action = ai.NewAction(61, AI_ACTION.RETURN)
    action.SetParam(0)
    action.SetBranch(53, 53)
    g_AIDebugInfo[61] = '[61] RETURN(0)'

    -- ��������ʱ��
    action = ai.NewAction(53, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(8)
    action.SetBranch(135)
    g_AIDebugInfo[53] = '[53] SET_PRIMARY_TIMER(8)'

    -- ����״̬
    action = ai.NewAction(135, AI_ACTION.SET_STATE)
    action.SetParam(82) -- �޵з���״̬
    g_AIDebugInfo[135] = '[135] SetParam(State82)'

    -- �޵з���״̬
    state = ai.NewState(82)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 91)
    state.HandleEvent(AI_EVENT.ON_PATH_FAILED, 91)

    -- ����
    action = ai.NewAction(91, AI_ACTION.RETURN)
    action.SetParam(1)
    action.SetBranch(66, 66)
    g_AIDebugInfo[91] = '[91] RETURN(1)'

    -- ��������ʱ��
    action = ai.NewAction(66, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(8)
    action.SetBranch(137)
    g_AIDebugInfo[66] = '[66] SET_PRIMARY_TIMER(8)'

    -- ����״̬
    action = ai.NewAction(137, AI_ACTION.SET_STATE)
    action.SetParam(98) -- ���سɹ�
    g_AIDebugInfo[137] = '[137] SetParam(State98)'

    -- ���سɹ�
    state = ai.NewState(98)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 94)

    -- ���DEBUFF
    action = ai.NewAction(94, AI_ACTION.CLEAN_DEBUFF)
    action.SetBranch(49)
    g_AIDebugInfo[94] = '[94] CLEAN_DEBUFF()'

    -- ����ϵͳ�޵�
    action = ai.NewAction(49, AI_ACTION.SET_SYSTEM_SHEILD)
    action.SetParam(0)
    action.SetBranch(15)
    g_AIDebugInfo[49] = '[49] SET_SYSTEM_SHEILD(0)'

    -- ��������ʱ��
    action = ai.NewAction(75, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(0)
    action.SetBranch(139)
    g_AIDebugInfo[75] = '[75] SET_PRIMARY_TIMER(0)'

    -- ����״̬
    action = ai.NewAction(139, AI_ACTION.SET_STATE)
    action.SetParam(90) -- ׷��״̬
    g_AIDebugInfo[139] = '[139] SetParam(State90)'

    -- ׷��״̬
    state = ai.NewState(90)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 103)
    state.HandleEvent(AI_EVENT.ON_TARGET_KILLED, 15)

    -- �ȽϷ��ص����
    action = ai.NewAction(103, AI_ACTION.RETURN_POSITION_DISTANCE_COMPARE)
    action.SetParam(param['EscapeRange'])
    action.SetBranch(104, 71, 71)
    g_AIDebugInfo[103] = '[103] RETURN_POSITION_DISTANCE_COMPARE(param[EscapeRange])'

    -- ��������
    action = ai.NewAction(40, AI_ACTION.SEARCH_ENEMY)
    action.SetParam(param['AlertRange'])
    action.SetBranch(42, 15)
    g_AIDebugInfo[40] = '[40] SEARCH_ENEMY(param[AlertRange])'

    ai.SetInitState(2)
end

-- ���Է���
function AI:DebugOnCallAction(nActiondId, nAIType)
    print('[AI] Call action: ' .. AI[nAIType][nActiondId])
end

-- ��AIͼ���Զ���ű�
function AI:CustomAction7(pNpc, actionData)
    -- �����Զ��嶯��ʵ�ֽű�
	pNpc.SetTarget(3,pNpc.dwId);
    return 1
end

function AI:CustomAction119(pNpc, ai)
    -- �����Զ��嶯��ʵ�ֽű�
	local param = AI.g_AIParam[ai.nAIType]
    Dialog:NpcBubbleToNearBy(pNpc.dwId, param.Shout1)
    return 1
end

