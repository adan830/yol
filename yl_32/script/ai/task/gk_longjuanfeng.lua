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
    ai.RegisterUserAction(2016, 'CustomAction16')

    -- ��ʼ
    state = ai.NewState(28)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 1)

    -- ��¼ԭ��
    action = ai.NewAction(1, AI_ACTION.RECORD_ORIGIN_POSITION)
    action.SetBranch(40)
    g_AIDebugInfo[1] = '[1] RECORD_ORIGIN_POSITION()'

    -- ��������ʱ��
    action = ai.NewAction(40, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(0)
    action.SetBranch(51)
    g_AIDebugInfo[40] = '[40] SET_PRIMARY_TIMER(0)'

    -- ����״̬
    action = ai.NewAction(51, AI_ACTION.SET_STATE)
    action.SetParam(8) -- ���Լ��ӳ����˺�
    g_AIDebugInfo[51] = '[51] SetParam(State8)'

    -- ���Լ��ӳ����˺�
    state = ai.NewState(8)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 16)

    -- ѡ���Լ�
    action = ai.NewAction(16, 2016)
    action.SetBranch(5)
    g_AIDebugInfo[16] = '[16] CustomAction16()'

    -- �ͷż���
    action = ai.NewAction(5, AI_ACTION.CAST_SKILL)
    action.SetParam(1161, 1)
    action.SetBranch(47, 47)
    g_AIDebugInfo[5] = '[5] CAST_SKILL(1161, 1)'

    -- ��������ʱ��
    action = ai.NewAction(47, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(4)
    action.SetBranch(53)
    g_AIDebugInfo[47] = '[47] SET_PRIMARY_TIMER(4)'

    -- ����״̬
    action = ai.NewAction(53, AI_ACTION.SET_STATE)
    action.SetParam(26) -- ��������
    g_AIDebugInfo[53] = '[53] SetParam(State26)'

    -- ��������
    state = ai.NewState(26)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 33)

    -- ��������
    action = ai.NewAction(33, AI_ACTION.SEARCH_ENEMY)
    action.SetParam(param['AlertRange'])
    action.SetBranch(19, 47)
    g_AIDebugInfo[33] = '[33] SEARCH_ENEMY(param[AlertRange])'

    -- ��Ŀ����ӵ���в�б�
    action = ai.NewAction(19, AI_ACTION.ADD_TARGET_TO_THREAT_LIST)
    action.SetBranch(7)
    g_AIDebugInfo[19] = '[19] ADD_TARGET_TO_THREAT_LIST()'

    -- ��¼���ص�
    action = ai.NewAction(7, AI_ACTION.RECORD_RETURN_POSITION)
    action.SetBranch(3)
    g_AIDebugInfo[7] = '[7] RECORD_RETURN_POSITION()'

    -- Npc��ʼ������CD
    action = ai.NewAction(3, AI_ACTION.NPC_INIT_SKILL_CD)
    action.SetBranch(22)
    g_AIDebugInfo[3] = '[3] NPC_INIT_SKILL_CD()'

    -- ��������ʱ��
    action = ai.NewAction(22, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(4)
    action.SetBranch(55)
    g_AIDebugInfo[22] = '[22] SET_PRIMARY_TIMER(4)'

    -- ����״̬
    action = ai.NewAction(55, AI_ACTION.SET_STATE)
    action.SetParam(41) -- ׷�ٵ���
    g_AIDebugInfo[55] = '[55] SetParam(State41)'

    -- ׷�ٵ���
    state = ai.NewState(41)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 14)

    -- ѡ���һ��в
    action = ai.NewAction(14, AI_ACTION.SELECT_FIRST_THREAT)
    action.SetBranch(2, 22)
    g_AIDebugInfo[14] = '[14] SELECT_FIRST_THREAT()'

    -- Npc��׼����ѡ��
    action = ai.NewAction(2, AI_ACTION.NPC_STANDARD_SKILL_SELECTOR)
    action.SetBranch(32, 22)
    g_AIDebugInfo[2] = '[2] NPC_STANDARD_SKILL_SELECTOR()'

    -- Npc���ּ����ͷž���
    action = ai.NewAction(32, AI_ACTION.NPC_KEEP_SKILL_CAST_RANGE)
    action.SetBranch(12, 38)
    g_AIDebugInfo[32] = '[32] NPC_KEEP_SKILL_CAST_RANGE()'

    -- ��������ʱ��
    action = ai.NewAction(38, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(0)
    action.SetBranch(57)
    g_AIDebugInfo[38] = '[38] SET_PRIMARY_TIMER(0)'

    -- ����״̬
    action = ai.NewAction(57, AI_ACTION.SET_STATE)
    action.SetParam(9) -- ׷��״̬
    g_AIDebugInfo[57] = '[57] SetParam(State9)'

    -- ׷��״̬
    state = ai.NewState(9)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 37)

    -- �ȽϷ��ص����
    action = ai.NewAction(37, AI_ACTION.RETURN_POSITION_DISTANCE_COMPARE)
    action.SetParam(param['EscapeRange'])
    action.SetBranch(47, 32, 32)
    g_AIDebugInfo[37] = '[37] RETURN_POSITION_DISTANCE_COMPARE(param[EscapeRange])'

    -- Npc�ͷ�ѡ������
    action = ai.NewAction(12, AI_ACTION.NPC_CAST_SELECT_SKILL)
    action.SetBranch(22, 22)
    g_AIDebugInfo[12] = '[12] NPC_CAST_SELECT_SKILL()'

    ai.SetInitState(28)
end

-- ���Է���
function AI:DebugOnCallAction(nActiondId, nAIType)
    print('[AI] Call action: ' .. AI[nAIType][nActiondId])
end

-- ��AIͼ���Զ���ű�
function AI:CustomAction16(pNpc, ai)
    -- �����Զ��嶯��ʵ�ֽű�
	pNpc.SetTarget(3,pNpc.dwId);
    return 1
end

