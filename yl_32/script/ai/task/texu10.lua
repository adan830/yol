-- ��д�ߣ�hejingxian
-- �汾�ţ�10

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
    ai.RegisterUserAction(2025, 'AI:CustomAction25')

    -- ��ʼ
    state = ai.NewState(12)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 10)

    -- ��¼ԭ��
    action = ai.NewAction(10, AI_ACTION.RECORD_ORIGIN_POSITION)
    action.SetBranch(15)
    g_AIDebugInfo[10] = '[10] RECORD_ORIGIN_POSITION()'

    -- ��¼���ص�
    action = ai.NewAction(15, AI_ACTION.RECORD_RETURN_POSITION)
    action.SetBranch(21)
    g_AIDebugInfo[15] = '[15] RECORD_RETURN_POSITION()'

    -- ��������ʱ��
    action = ai.NewAction(21, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(64)
    action.SetBranch(40)
    g_AIDebugInfo[21] = '[21] SET_PRIMARY_TIMER(64)'

    -- ����״̬
    action = ai.NewAction(40, AI_ACTION.SET_STATE)
    action.SetParam(36) -- ���Ŷ���
    g_AIDebugInfo[40] = '[40] SetParam(State36)'

    -- ���Ŷ���
    state = ai.NewState(36)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 25)

    -- ѡ���Լ�
    action = ai.NewAction(25, 2025)
    action.SetBranch(27)
    g_AIDebugInfo[25] = '[25] AI:CustomAction25()'

    -- Npc��׼����ѡ��
    action = ai.NewAction(27, AI_ACTION.NPC_STANDARD_SKILL_SELECTOR)
    action.SetBranch(24, 24)
    g_AIDebugInfo[27] = '[27] NPC_STANDARD_SKILL_SELECTOR()'

    -- Npc�ͷ�ѡ������
    action = ai.NewAction(24, AI_ACTION.NPC_CAST_SELECT_SKILL)
    action.SetBranch(38, 38)
    g_AIDebugInfo[24] = '[24] NPC_CAST_SELECT_SKILL()'

    -- ��������ʱ��
    action = ai.NewAction(38, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(4)
    action.SetBranch(42)
    g_AIDebugInfo[38] = '[38] SET_PRIMARY_TIMER(4)'

    -- ����״̬
    action = ai.NewAction(42, AI_ACTION.SET_STATE)
    action.SetParam(31) -- ����Ѱ·
    g_AIDebugInfo[42] = '[42] SetParam(State31)'

    -- ����Ѱ·
    state = ai.NewState(31)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 20)

    -- ����Ѳ��·��
    action = ai.NewAction(20, AI_ACTION.ENTER_PATROL_PATH)
    action.SetParam(param['PatrolPathID'], param['PatrolOrderIndex'])
    action.SetBranch(18)
    g_AIDebugInfo[20] = '[20] ENTER_PATROL_PATH(param[PatrolPathID], param[PatrolOrderIndex])'

    -- Ѳ��
    action = ai.NewAction(18, AI_ACTION.DO_PATROL)
    action.SetBranch(19, 19)
    g_AIDebugInfo[18] = '[18] DO_PATROL()'

    -- ��������ʱ��
    action = ai.NewAction(19, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(16)
    action.SetBranch(44)
    g_AIDebugInfo[19] = '[19] SET_PRIMARY_TIMER(16)'

    -- ����״̬
    action = ai.NewAction(44, AI_ACTION.SET_STATE)
    action.SetParam(5) -- ��״̬
    g_AIDebugInfo[44] = '[44] SetParam(State5)'

    -- ��״̬
    state = ai.NewState(5)
    state.HandleEvent(AI_EVENT.ON_SECONDARY_TIMER, 18)
    state.HandleEvent(AI_EVENT.ON_PATH_FAILED, 18)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 19)
    state.HandleEvent(AI_EVENT.ON_PATH_SUCCESS, 7)

    -- ���ø���ʱ��
    action = ai.NewAction(7, AI_ACTION.SET_SECONDARY_TIMER)
    action.SetParam(16)
    action.SetBranch(19)
    g_AIDebugInfo[7] = '[7] SET_SECONDARY_TIMER(16)'

    ai.SetInitState(12)
end

-- ���Է���
function AI:DebugOnCallAction(nActiondId, nAIType)
    print('[AI] Call action: ' .. AI[nAIType][nActiondId])
end

-- ��AIͼ���Զ���ű�
function AI:CustomAction25(pNpc, actionData)
    -- �����Զ��嶯��ʵ�ֽű�
	pNpc.SetTarget(3,pNpc.dwId);
    return 1
end

