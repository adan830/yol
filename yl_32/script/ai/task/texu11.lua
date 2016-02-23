-- ��д�ߣ�hejingxian
-- �汾�ţ�16

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
    ai.RegisterUserAction(2053, 'CustomAction53')

    -- ��ʼ
    state = ai.NewState(22)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 26)

    -- ��¼ԭ��
    action = ai.NewAction(26, AI_ACTION.RECORD_ORIGIN_POSITION)
    action.SetBranch(25)
    g_AIDebugInfo[26] = '[26] RECORD_ORIGIN_POSITION()'

    -- ��¼���ص�
    action = ai.NewAction(25, AI_ACTION.RECORD_RETURN_POSITION)
    action.SetBranch(58)
    g_AIDebugInfo[25] = '[25] RECORD_RETURN_POSITION()'

    -- ����״̬
    action = ai.NewAction(58, AI_ACTION.SET_STATE)
    action.SetParam(9) -- ���Ŷ���
    g_AIDebugInfo[58] = '[58] SetParam(State9)'

    -- ���Ŷ���
    state = ai.NewState(9)
    state.HandleEvent(AI_EVENT.ON_ATTACKED, 35)

    -- ��������ʱ��
    action = ai.NewAction(35, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(4)
    action.SetBranch(60)
    g_AIDebugInfo[35] = '[35] SET_PRIMARY_TIMER(4)'

    -- ����״̬
    action = ai.NewAction(60, AI_ACTION.SET_STATE)
    action.SetParam(12) -- ����Ѱ·
    g_AIDebugInfo[60] = '[60] SetParam(State12)'

    -- ����Ѱ·
    state = ai.NewState(12)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 31)

    -- ����Ѳ��·��
    action = ai.NewAction(31, AI_ACTION.ENTER_PATROL_PATH)
    action.SetParam(param['PatrolPathID'], param['PatrolOrderIndex'])
    action.SetBranch(20)
    g_AIDebugInfo[31] = '[31] ENTER_PATROL_PATH(param[PatrolPathID], param[PatrolOrderIndex])'

    -- Ѳ��
    action = ai.NewAction(20, AI_ACTION.DO_PATROL)
    action.SetBranch(34, 53)
    g_AIDebugInfo[20] = '[20] DO_PATROL()'

    -- ѡ���Լ�
    action = ai.NewAction(53, 2053)
    action.SetBranch(54)
    g_AIDebugInfo[53] = '[53] CustomAction53()'

    -- �ͷż���
    action = ai.NewAction(54, AI_ACTION.CAST_SKILL)
    action.SetParam(392, 1)
    action.SetBranch(41, 34)
    g_AIDebugInfo[54] = '[54] CAST_SKILL(392, 1)'

    -- ��������ʱ��
    action = ai.NewAction(41, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(32)
    action.SetBranch(62)
    g_AIDebugInfo[41] = '[41] SET_PRIMARY_TIMER(32)'

    -- ����״̬
    action = ai.NewAction(62, AI_ACTION.SET_STATE)
    action.SetParam(40) -- �ͷż��ܽ���
    g_AIDebugInfo[62] = '[62] SetParam(State40)'

    -- �ͷż��ܽ���
    state = ai.NewState(40)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 34)

    -- ��������ʱ��
    action = ai.NewAction(34, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(16)
    action.SetBranch(64)
    g_AIDebugInfo[34] = '[34] SET_PRIMARY_TIMER(16)'

    -- ����״̬
    action = ai.NewAction(64, AI_ACTION.SET_STATE)
    action.SetParam(29) -- ��״̬
    g_AIDebugInfo[64] = '[64] SetParam(State29)'

    -- ��״̬
    state = ai.NewState(29)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 46)
    state.HandleEvent(AI_EVENT.ON_SECONDARY_TIMER, 20)
    state.HandleEvent(AI_EVENT.ON_PATH_FAILED, 20)
    state.HandleEvent(AI_EVENT.ON_PATH_SUCCESS, 32)

    -- ��������
    action = ai.NewAction(46, AI_ACTION.SEARCH_ENEMY)
    action.SetParam(param['AlertRange'])
    action.SetBranch(53, 34)
    g_AIDebugInfo[46] = '[46] SEARCH_ENEMY(param[AlertRange])'

    -- ���ø���ʱ��
    action = ai.NewAction(32, AI_ACTION.SET_SECONDARY_TIMER)
    action.SetParam(16)
    action.SetBranch(34)
    g_AIDebugInfo[32] = '[32] SET_SECONDARY_TIMER(16)'

    ai.SetInitState(22)
end

-- ���Է���
function AI:DebugOnCallAction(nActiondId, nAIType)
    print('[AI] Call action: ' .. AI[nAIType][nActiondId])
end

-- ��AIͼ���Զ���ű�
function AI:CustomAction53(pNpc, actionData)
    -- �����Զ��嶯��ʵ�ֽű�
	pNpc.SetTarget(3,pNpc.dwId);
    return 1
end

