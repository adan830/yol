-- ��д�ߣ�chenkangyin
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

    -- ��ʼ
    state = ai.NewState(1)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 2)

    -- ����״̬
    action = ai.NewAction(2, AI_ACTION.SET_STATE)
    action.SetParam(1)
    g_AIDebugInfo[2] = '[2] SET_STATE(1)'

    ai.SetInitState(1)
end

-- ���Է���
function AI:DebugOnCallAction(nActiondId, nAIType)
    print('[AI] Call action: ' .. AI[nAIType][nActiondId])
end
