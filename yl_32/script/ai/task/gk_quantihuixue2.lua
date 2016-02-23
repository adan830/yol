-- ��д�ߣ�hejingxian
-- �汾�ţ�2

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
    ai.RegisterUserAction(2006, 'CustomAction6')
    ai.RegisterUserAction(2007, 'CustomAction7')

    -- ��ʼ
    state = ai.NewState(12)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 27)

    -- ��¼ԭ��
    action = ai.NewAction(27, AI_ACTION.RECORD_ORIGIN_POSITION)
    action.SetBranch(15)
    g_AIDebugInfo[27] = '[27] RECORD_ORIGIN_POSITION()'

    -- ��������ʱ��
    action = ai.NewAction(15, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(4)
    action.SetBranch(40)
    g_AIDebugInfo[15] = '[15] SET_PRIMARY_TIMER(4)'

    -- ����״̬
    action = ai.NewAction(40, AI_ACTION.SET_STATE)
    action.SetParam(10) -- �������
    g_AIDebugInfo[40] = '[40] SetParam(State10)'

    -- �������
    state = ai.NewState(10)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 38)

    -- ������� �����κ�Ч��
    action = ai.NewAction(38, AI_ACTION.SEARCH_PLAYER_WITHOUT_ANY_AFFECT)
    action.SetParam(param['AlertRange'])
    action.SetBranch(6, 15)
    g_AIDebugInfo[38] = '[38] SEARCH_PLAYER_WITHOUT_ANY_AFFECT(param[AlertRange])'

    -- ѡ���Լ�
    action = ai.NewAction(6, 2006)
    action.SetBranch(13)
    g_AIDebugInfo[6] = '[6] CustomAction6()'

    -- Npc��׼����ѡ��
    action = ai.NewAction(13, AI_ACTION.NPC_STANDARD_SKILL_SELECTOR)
    action.SetBranch(25, 25)
    g_AIDebugInfo[13] = '[13] NPC_STANDARD_SKILL_SELECTOR()'

    -- Npc�ͷ�ѡ������
    action = ai.NewAction(25, AI_ACTION.NPC_CAST_SELECT_SKILL)
    action.SetBranch(2, 2)
    g_AIDebugInfo[25] = '[25] NPC_CAST_SELECT_SKILL()'

    -- ��������ʱ��
    action = ai.NewAction(2, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(32)
    action.SetBranch(42)
    g_AIDebugInfo[2] = '[2] SET_PRIMARY_TIMER(32)'

    -- ����״̬
    action = ai.NewAction(42, AI_ACTION.SET_STATE)
    action.SetParam(28) -- �ͷż��ܽ���
    g_AIDebugInfo[42] = '[42] SetParam(State28)'

    -- �ͷż��ܽ���
    state = ai.NewState(28)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 7)

    -- ѡ���Լ�
    action = ai.NewAction(7, 2007)
    action.SetBranch(21)
    g_AIDebugInfo[7] = '[7] CustomAction7()'

    -- �ͷż���
    action = ai.NewAction(21, AI_ACTION.CAST_SKILL)
    action.SetParam(350, 1)
    action.SetBranch(44, 46)
    g_AIDebugInfo[21] = '[21] CAST_SKILL(350, 1)'

    -- ����״̬
    action = ai.NewAction(44, AI_ACTION.SET_STATE)
    action.SetParam(14) -- ��ɱ
    g_AIDebugInfo[44] = '[44] SetParam(State14)'

    -- ��ɱ
    state = ai.NewState(14)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 31)

    -- ����״̬
    action = ai.NewAction(31, AI_ACTION.SET_STATE)
    action.SetParam(4)
    g_AIDebugInfo[31] = '[31] SET_STATE(4)'

    -- ����״̬
    action = ai.NewAction(46, AI_ACTION.SET_STATE)
    action.SetParam(14) -- ��ɱ
    g_AIDebugInfo[46] = '[46] SetParam(State14)'

    ai.SetInitState(12)
end

-- ���Է���
function AI:DebugOnCallAction(nActiondId, nAIType)
    print('[AI] Call action: ' .. AI[nAIType][nActiondId])
end

-- ��AIͼ���Զ���ű�
function AI:CustomAction6(pNpc, ai)
    -- �����Զ��嶯��ʵ�ֽű�
	pNpc.SetTarget(3,pNpc.dwId);
    return 1
end

function AI:CustomAction7(pNpc, ai)
    -- �����Զ��嶯��ʵ�ֽű�
	pNpc.SetTarget(3,pNpc.dwId);
    return 1
end

