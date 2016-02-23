-- ��д�ߣ�hejingxian
-- �汾�ţ�3

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
    ai.RegisterUserAction(2013, 'CustomAction13')

    -- ��ʼ
    state = ai.NewState(2)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 10)

    -- ��¼ԭ��
    action = ai.NewAction(10, AI_ACTION.RECORD_ORIGIN_POSITION)
    action.SetBranch(15)
    g_AIDebugInfo[10] = '[10] RECORD_ORIGIN_POSITION()'

    -- ��������ʱ��
    action = ai.NewAction(15, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(0)
    action.SetBranch(36)
    g_AIDebugInfo[15] = '[15] SET_PRIMARY_TIMER(0)'

    -- ����״̬
    action = ai.NewAction(36, AI_ACTION.SET_STATE)
    action.SetParam(3) -- ���Լ��ӳ����˺�
    g_AIDebugInfo[36] = '[36] SetParam(State3)'

    -- ���Լ��ӳ����˺�
    state = ai.NewState(3)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 13)

    -- ѡ���Լ�
    action = ai.NewAction(13, 2013)
    action.SetBranch(6)
    g_AIDebugInfo[13] = '[13] CustomAction13()'

    -- �ͷż���
    action = ai.NewAction(6, AI_ACTION.CAST_SKILL)
    action.SetParam(1108, 1)
    action.SetBranch(5, 5)
    g_AIDebugInfo[6] = '[6] CAST_SKILL(1108, 1)'

    -- ��������ʱ��
    action = ai.NewAction(5, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(4)
    action.SetBranch(38)
    g_AIDebugInfo[5] = '[5] SET_PRIMARY_TIMER(4)'

    -- ����״̬
    action = ai.NewAction(38, AI_ACTION.SET_STATE)
    action.SetParam(34) -- ����Ѱ·
    g_AIDebugInfo[38] = '[38] SetParam(State34)'

    -- ����Ѱ·
    state = ai.NewState(34)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 22)

    -- ��¼���ص�
    action = ai.NewAction(22, AI_ACTION.RECORD_RETURN_POSITION)
    action.SetBranch(23)
    g_AIDebugInfo[22] = '[22] RECORD_RETURN_POSITION()'

    -- ����Ѳ��·��
    action = ai.NewAction(23, AI_ACTION.ENTER_PATROL_PATH)
    action.SetParam(param['PatrolPathID'], param['PatrolOrderIndex'])
    action.SetBranch(30)
    g_AIDebugInfo[23] = '[23] ENTER_PATROL_PATH(param[PatrolPathID], param[PatrolOrderIndex])'

    -- Ѳ��
    action = ai.NewAction(30, AI_ACTION.DO_PATROL)
    action.SetBranch(32, 32)
    g_AIDebugInfo[30] = '[30] DO_PATROL()'

    -- ��������ʱ��
    action = ai.NewAction(32, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(16)
    action.SetBranch(40)
    g_AIDebugInfo[32] = '[32] SET_PRIMARY_TIMER(16)'

    -- ����״̬
    action = ai.NewAction(40, AI_ACTION.SET_STATE)
    action.SetParam(24) -- ��״̬
    g_AIDebugInfo[40] = '[40] SetParam(State24)'

    -- ��״̬
    state = ai.NewState(24)
    state.HandleEvent(AI_EVENT.ON_PATH_FAILED, 30)
    state.HandleEvent(AI_EVENT.ON_PATH_SUCCESS, 21)
    state.HandleEvent(AI_EVENT.ON_SECONDARY_TIMER, 30)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 32)

    -- ���ø���ʱ��
    action = ai.NewAction(21, AI_ACTION.SET_SECONDARY_TIMER)
    action.SetParam(16)
    action.SetBranch(32)
    g_AIDebugInfo[21] = '[21] SET_SECONDARY_TIMER(16)'

    ai.SetInitState(2)
end

-- ���Է���
function AI:DebugOnCallAction(nActiondId, nAIType)
    print('[AI] Call action: ' .. AI[nAIType][nActiondId])
end

-- ��AIͼ���Զ���ű�
function AI:CustomAction13(pNpc, ai)
    -- �����Զ��嶯��ʵ�ֽű�
	pNpc.SetTarget(3,pNpc.dwId);
    return 1
end

