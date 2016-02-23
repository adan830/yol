-- ��д�ߣ�lidianyi
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

    -- ��ʼ
    state = ai.NewState(4)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 6)

    -- ��¼ԭ��
    action = ai.NewAction(6, AI_ACTION.RECORD_ORIGIN_POSITION)
    action.SetBranch(8)
    g_AIDebugInfo[6] = '[6] RECORD_ORIGIN_POSITION()'

    -- ��¼���ص�
    action = ai.NewAction(8, AI_ACTION.RECORD_RETURN_POSITION)
    action.SetBranch(10)
    g_AIDebugInfo[8] = '[8] RECORD_RETURN_POSITION()'

    -- ����Ѳ��·��
    action = ai.NewAction(10, AI_ACTION.ENTER_PATROL_PATH)
    action.SetParam(param['PatrolPathID'], param['PatrolOrderIndex'])
    action.SetBranch(21)
    g_AIDebugInfo[10] = '[10] ENTER_PATROL_PATH(param[PatrolPathID], param[PatrolOrderIndex])'

    -- Ѳ��
    action = ai.NewAction(21, AI_ACTION.DO_PATROL)
    action.SetBranch(23, 23)
    g_AIDebugInfo[21] = '[21] DO_PATROL()'

    -- ��������ʱ��
    action = ai.NewAction(23, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(16)
    action.SetBranch(36)
    g_AIDebugInfo[23] = '[23] SET_PRIMARY_TIMER(16)'

    -- ����״̬
    action = ai.NewAction(36, AI_ACTION.SET_STATE)
    action.SetParam(26) -- ��״̬
    g_AIDebugInfo[36] = '[36] SetParam(State26)'

    -- ��״̬
    state = ai.NewState(26)
    state.HandleEvent(AI_EVENT.ON_SECONDARY_TIMER, 21)
    state.HandleEvent(AI_EVENT.ON_PATH_SUCCESS, 31)
    state.HandleEvent(AI_EVENT.ON_PATH_FAILED, 21)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 23)

    -- ���ø���ʱ��
    action = ai.NewAction(31, AI_ACTION.SET_SECONDARY_TIMER)
    action.SetParam(16)
    action.SetBranch(23)
    g_AIDebugInfo[31] = '[31] SET_SECONDARY_TIMER(16)'

    ai.SetInitState(4)
end

-- ���Է���
function AI:DebugOnCallAction(nActiondId, nAIType)
    print('[AI] Call action: ' .. AI[nAIType][nActiondId])
end
