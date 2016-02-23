-- ��д�ߣ�hejingxian
-- �汾�ţ�12

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
    ai.RegisterUserAction(2058, 'AI:CustomAction58')

    -- ���˸���-��ͷ��
    state = ai.NewState(29)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 34)

    -- ��¼ԭ��
    action = ai.NewAction(34, AI_ACTION.RECORD_ORIGIN_POSITION)
    action.SetBranch(21)
    g_AIDebugInfo[34] = '[34] RECORD_ORIGIN_POSITION()'

    -- ��¼���ص�
    action = ai.NewAction(21, AI_ACTION.RECORD_RETURN_POSITION)
    action.SetBranch(25)
    g_AIDebugInfo[21] = '[21] RECORD_RETURN_POSITION()'

    -- ����Ѳ��·��
    action = ai.NewAction(25, AI_ACTION.ENTER_PATROL_PATH)
    action.SetParam(param['PatrolPathID'], param['PatrolOrderIndex'])
    action.SetBranch(36)
    g_AIDebugInfo[25] = '[25] ENTER_PATROL_PATH(param[PatrolPathID], param[PatrolOrderIndex])'

    -- Ѳ��
    action = ai.NewAction(36, AI_ACTION.DO_PATROL)
    action.SetBranch(20, 51)
    g_AIDebugInfo[36] = '[36] DO_PATROL()'

    -- ��������ʱ��
    action = ai.NewAction(20, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(64)
    action.SetBranch(72)
    g_AIDebugInfo[20] = '[20] SET_PRIMARY_TIMER(64)'

    -- ����״̬
    action = ai.NewAction(72, AI_ACTION.SET_STATE)
    action.SetParam(41) -- ��״̬
    g_AIDebugInfo[72] = '[72] SetParam(State41)'

    -- ��״̬
    state = ai.NewState(41)
    state.HandleEvent(AI_EVENT.ON_SECONDARY_TIMER, 55)
    state.HandleEvent(AI_EVENT.ON_PATH_SUCCESS, 54)

    -- Npc��׼����ѡ��
    action = ai.NewAction(55, AI_ACTION.NPC_STANDARD_SKILL_SELECTOR)
    action.SetBranch(58, 36)
    g_AIDebugInfo[55] = '[55] NPC_STANDARD_SKILL_SELECTOR()'

    -- ѡ���Լ�
    action = ai.NewAction(58, 2058)
    action.SetBranch(56)
    g_AIDebugInfo[58] = '[58] AI:CustomAction58()'

    -- Npc�ͷ�ѡ������
    action = ai.NewAction(56, AI_ACTION.NPC_CAST_SELECT_SKILL)
    action.SetBranch(36, 36)
    g_AIDebugInfo[56] = '[56] NPC_CAST_SELECT_SKILL()'

    -- ���ø���ʱ��
    action = ai.NewAction(54, AI_ACTION.SET_SECONDARY_TIMER)
    action.SetParam(64)
    action.SetBranch(20)
    g_AIDebugInfo[54] = '[54] SET_SECONDARY_TIMER(64)'

    -- ��������ʱ��
    action = ai.NewAction(51, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(4)
    action.SetBranch(74)
    g_AIDebugInfo[51] = '[51] SET_PRIMARY_TIMER(4)'

    -- ����״̬
    action = ai.NewAction(74, AI_ACTION.SET_STATE)
    action.SetParam(44) -- ������Ů
    g_AIDebugInfo[74] = '[74] SetParam(State44)'

    -- ������Ů
    state = ai.NewState(44)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 14)

    -- ��������
    action = ai.NewAction(14, AI_ACTION.SEARCH_ENEMY)
    action.SetParam(param['AlertRange'])
    action.SetBranch(4, 51)
    g_AIDebugInfo[14] = '[14] SEARCH_ENEMY(param[AlertRange])'

    -- ��Ŀ����ӵ���в�б�
    action = ai.NewAction(4, AI_ACTION.ADD_TARGET_TO_THREAT_LIST)
    action.SetBranch(40)
    g_AIDebugInfo[4] = '[4] ADD_TARGET_TO_THREAT_LIST()'

    -- Npc��ʼ������CD
    action = ai.NewAction(40, AI_ACTION.NPC_INIT_SKILL_CD)
    action.SetBranch(8)
    g_AIDebugInfo[40] = '[40] NPC_INIT_SKILL_CD()'

    -- ��������ʱ��
    action = ai.NewAction(8, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(4)
    action.SetBranch(76)
    g_AIDebugInfo[8] = '[8] SET_PRIMARY_TIMER(4)'

    -- ����״̬
    action = ai.NewAction(76, AI_ACTION.SET_STATE)
    action.SetParam(28) -- ��ͨ����
    g_AIDebugInfo[76] = '[76] SetParam(State28)'

    -- ��ͨ����
    state = ai.NewState(28)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 66)

    -- �ͷż���
    action = ai.NewAction(66, AI_ACTION.CAST_SKILL)
    action.SetParam(1606, 1)
    action.SetBranch(67, 51)
    g_AIDebugInfo[66] = '[66] CAST_SKILL(1606, 1)'

    -- ��������ʱ��
    action = ai.NewAction(67, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(32)
    action.SetBranch(78)
    g_AIDebugInfo[67] = '[67] SET_PRIMARY_TIMER(32)'

    -- ����״̬
    action = ai.NewAction(78, AI_ACTION.SET_STATE)
    action.SetParam(70) -- ��ͨ����
    g_AIDebugInfo[78] = '[78] SetParam(State70)'

    -- ��ͨ����
    state = ai.NewState(70)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 9)

    -- ��鼼��ʧ�ܼ���
    action = ai.NewAction(9, AI_ACTION.CHECK_SKILL_FAILED_COUNTER)
    action.SetParam(50)
    action.SetBranch(8, 51)
    g_AIDebugInfo[9] = '[9] CHECK_SKILL_FAILED_COUNTER(50)'

    ai.SetInitState(29)
end

-- ���Է���
function AI:DebugOnCallAction(nActiondId, nAIType)
    print('[AI] Call action: ' .. AI[nAIType][nActiondId])
end

-- ��AIͼ���Զ���ű�
function AI:CustomAction58(pNpc, actionData)
    -- �����Զ��嶯��ʵ�ֽű�
	pNpc.SetTarget(3,pNpc.dwId);
    return 1
end

