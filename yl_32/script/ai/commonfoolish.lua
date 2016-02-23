
Include("script/ai/ai_param.lua")

--����״̬����
local STATE_STANDBY = 1

function AI:Setup(ai)
    local state
    local action
    local param = AI.g_AIParam[ai.nAIType]

    --ע���Զ��嶯��

    --����״̬
    state = ai.NewState(STATE_STANDBY)
    state.HandleEvent(AI_EVENT.ON_DIALOG, 2)

	--ѡ��ʱ�䷢����
    action = ai.NewAction(2, AI_ACTION.SELECT_EVENT_SRC)
    action.SetBranch(3, 5)

    --��NPC�Ի�����
    action = ai.NewAction(3, AI_ACTION.NPC_OPEN_DIALOG_WINDOW)
    action.SetBranch(5, 5)

    --����״̬
    action = ai.NewAction(5, AI_ACTION.SET_STATE)
    action.SetParam(STATE_STANDBY)

    ai.SetInitState(STATE_STANDBY)
end