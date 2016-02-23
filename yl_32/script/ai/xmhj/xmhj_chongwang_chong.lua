-- ��д�ߣ�lidianyi
-- �汾�ţ�42

Include('script/ai/customfunctions.lua')
Include('script/ai/ai_param.lua')
Include('script/ai/argumentstrings.lua')

local g_AIDebugInfo = {}

-- �Զ��帽�ӽű�
local nFirstTime;
local nSecendTime;

local function ToCompare(p1,p2)
	return p2 < p1;
end

function AI:Setup(ai)
    local state
    local action
    local param = AI.g_AIParam[ai.nAIType]

    -- ע���Զ��嶯��
    ai.RegisterUserAction(2082, 'AI:GetFartherPlayer')
    ai.RegisterUserAction(2084, 'AI:ChongGetTime')
    ai.RegisterUserAction(2088, 'AI:ChongColdDown')

    -- ��ʼ
    state = ai.NewState(1)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 62)

    -- ��¼ԭ��
    action = ai.NewAction(62, AI_ACTION.RECORD_ORIGIN_POSITION)
    action.SetBranch(65)
    g_AIDebugInfo[62] = '[62] RECORD_ORIGIN_POSITION()'

    -- ��������ʱ��
    action = ai.NewAction(65, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(8)
    action.SetBranch(172)
    g_AIDebugInfo[65] = '[65] SET_PRIMARY_TIMER(8)'

    -- ����״̬
    action = ai.NewAction(172, AI_ACTION.SET_STATE)
    action.SetParam(63) -- Ѱ��
    g_AIDebugInfo[172] = '[172] SetParam(State63)'

    -- Ѱ��
    state = ai.NewState(63)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 2)
    state.HandleEvent(AI_EVENT.ON_ATTACKED, 69)

    -- ��������
    action = ai.NewAction(2, AI_ACTION.SEARCH_ENEMY)
    action.SetParam(param['SearchPlayerDistance'])
    action.SetBranch(72, 65)
    g_AIDebugInfo[2] = '[2] SEARCH_ENEMY(param[SearchPlayerDistance])'

    -- ��Ŀ����ӵ���в�б�
    action = ai.NewAction(72, AI_ACTION.ADD_TARGET_TO_THREAT_LIST)
    action.SetBranch(11)
    g_AIDebugInfo[72] = '[72] ADD_TARGET_TO_THREAT_LIST()'

    -- ��¼���ص�
    action = ai.NewAction(11, AI_ACTION.RECORD_RETURN_POSITION)
    action.SetBranch(76)
    g_AIDebugInfo[11] = '[11] RECORD_RETURN_POSITION()'

    -- Npc��ʼ������CD
    action = ai.NewAction(76, AI_ACTION.NPC_INIT_SKILL_CD)
    action.SetBranch(84)
    g_AIDebugInfo[76] = '[76] NPC_INIT_SKILL_CD()'

    -- ��ȡ��ǰʱ��
    action = ai.NewAction(84, 2084)
    action.SetBranch(78)
    g_AIDebugInfo[84] = '[84] AI:ChongGetTime()'

    -- ��������ʱ��
    action = ai.NewAction(78, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(4)
    action.SetBranch(174)
    g_AIDebugInfo[78] = '[78] SET_PRIMARY_TIMER(4)'

    -- ����״̬
    action = ai.NewAction(174, AI_ACTION.SET_STATE)
    action.SetParam(80) -- ս��״̬
    g_AIDebugInfo[174] = '[174] SetParam(State80)'

    -- ս��״̬
    state = ai.NewState(80)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 9)

    -- ѡ���һ��в
    action = ai.NewAction(9, AI_ACTION.SELECT_FIRST_THREAT)
    action.SetBranch(88, 127)
    g_AIDebugInfo[9] = '[9] SELECT_FIRST_THREAT()'

    -- ������ȴ
    action = ai.NewAction(88, 2088)
    action.SetBranch(82, 92)
    g_AIDebugInfo[88] = '[88] AI:ChongColdDown()'

    -- GetFartherPlayer&CastSkill
    action = ai.NewAction(82, 2082)
    action.SetBranch(78, 108)
    g_AIDebugInfo[82] = '[82] AI:GetFartherPlayer()'

    -- ��鼼��ʧ�ܼ���
    action = ai.NewAction(108, AI_ACTION.CHECK_SKILL_FAILED_COUNTER)
    action.SetParam(3)
    action.SetBranch(78, 127)
    g_AIDebugInfo[108] = '[108] CHECK_SKILL_FAILED_COUNTER(3)'

    -- ����ϵͳ�޵�
    action = ai.NewAction(127, AI_ACTION.SET_SYSTEM_SHEILD)
    action.SetParam(1)
    action.SetBranch(126)
    g_AIDebugInfo[127] = '[127] SET_SYSTEM_SHEILD(1)'

    -- ����
    action = ai.NewAction(126, AI_ACTION.RETURN)
    action.SetParam(0)
    action.SetBranch(115, 115)
    g_AIDebugInfo[126] = '[126] RETURN(0)'

    -- ��������ʱ��
    action = ai.NewAction(115, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(80)
    action.SetBranch(176)
    g_AIDebugInfo[115] = '[115] SET_PRIMARY_TIMER(80)'

    -- ����״̬
    action = ai.NewAction(176, AI_ACTION.SET_STATE)
    action.SetParam(113) -- �޵з���״̬
    g_AIDebugInfo[176] = '[176] SetParam(State113)'

    -- �޵з���״̬
    state = ai.NewState(113)
    state.HandleEvent(AI_EVENT.ON_PATH_FAILED, 112)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 112)

    -- ����
    action = ai.NewAction(112, AI_ACTION.RETURN)
    action.SetParam(1)
    action.SetBranch(130, 130)
    g_AIDebugInfo[112] = '[112] RETURN(1)'

    -- ��������ʱ��
    action = ai.NewAction(130, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(32)
    action.SetBranch(178)
    g_AIDebugInfo[130] = '[130] SET_PRIMARY_TIMER(32)'

    -- ����״̬
    action = ai.NewAction(178, AI_ACTION.SET_STATE)
    action.SetParam(116) -- ���سɹ�
    g_AIDebugInfo[178] = '[178] SetParam(State116)'

    -- ���سɹ�
    state = ai.NewState(116)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 124)

    -- ���DEBUFF
    action = ai.NewAction(124, AI_ACTION.CLEAN_DEBUFF)
    action.SetBranch(119)
    g_AIDebugInfo[124] = '[124] CLEAN_DEBUFF()'

    -- ����ϵͳ�޵�
    action = ai.NewAction(119, AI_ACTION.SET_SYSTEM_SHEILD)
    action.SetParam(0)
    action.SetBranch(65)
    g_AIDebugInfo[119] = '[119] SET_SYSTEM_SHEILD(0)'

    -- Npc��׼����ѡ��
    action = ai.NewAction(92, AI_ACTION.NPC_STANDARD_SKILL_SELECTOR)
    action.SetBranch(94, 78)
    g_AIDebugInfo[92] = '[92] NPC_STANDARD_SKILL_SELECTOR()'

    -- Npc���ּ����ͷž���
    action = ai.NewAction(94, AI_ACTION.NPC_KEEP_SKILL_CAST_RANGE)
    action.SetBranch(96, 99)
    g_AIDebugInfo[94] = '[94] NPC_KEEP_SKILL_CAST_RANGE()'

    -- Npc�ͷ�ѡ������
    action = ai.NewAction(96, AI_ACTION.NPC_CAST_SELECT_SKILL)
    action.SetBranch(78, 108)
    g_AIDebugInfo[96] = '[96] NPC_CAST_SELECT_SKILL()'

    -- ��������ʱ��
    action = ai.NewAction(99, AI_ACTION.SET_PRIMARY_TIMER)
    action.SetParam(4)
    action.SetBranch(180)
    g_AIDebugInfo[99] = '[99] SET_PRIMARY_TIMER(4)'

    -- ����״̬
    action = ai.NewAction(180, AI_ACTION.SET_STATE)
    action.SetParam(101) -- ׷��״̬
    g_AIDebugInfo[180] = '[180] SetParam(State101)'

    -- ׷��״̬
    state = ai.NewState(101)
    state.HandleEvent(AI_EVENT.ON_PRIMARY_TIMER, 103)

    -- �ȽϷ��ص����
    action = ai.NewAction(103, AI_ACTION.RETURN_POSITION_DISTANCE_COMPARE)
    action.SetParam(param['AttackRange'])
    action.SetBranch(127, 94, 94)
    g_AIDebugInfo[103] = '[103] RETURN_POSITION_DISTANCE_COMPARE(param[AttackRange])'

    -- ѡ���¼�������
    action = ai.NewAction(69, AI_ACTION.SELECT_EVENT_SRC)
    action.SetBranch(72, 127)
    g_AIDebugInfo[69] = '[69] SELECT_EVENT_SRC()'

    ai.SetInitState(1)
end

-- ���Է���
function AI:DebugOnCallAction(action_id)
    Log('[AI] Call action: ' .. g_AIDebugInfo[action_id])
end

-- ��AIͼ���Զ���ű�
function AI:ChongGetTime(pNpc, actionData)
    -- �����Զ��嶯��ʵ�ֽű�
	nFirstTime = KGameBase.GetTime();
    return 1
end

function AI:ChongColdDown(pNpc, actionData)
    -- �����Զ��嶯��ʵ�ֽű�
	nSecendTime = KGameBase.GetTime();
	if nSecendTime - nFirstTime >= 6 then
		nFirstTime = nSecendTime;
    	return 1;
    end
    return 2;
end

function AI:GetFartherPlayer(pNpc, actionData)
    -- �����Զ��嶯��ʵ�ֽű�
	local tbPlayerInBattle = {};
	local tbGetDis = {};--
	local tbPlayerDis = {};--
	local tbGetPlayerId = {};--
	local tbDis = {};
	local tbPlayerToCastSkill = {};--
	local tbNpcPos = pNpc.GetPosition();
	for _, nId in pairs(pNpc.GetThreatList()) do 
    	tbPlayerInBattle[#tbPlayerInBattle + 1] = nId;
    end
    if (not tbPlayerInBattle) or (table.getn(tbPlayerInBattle) < 1) then
    	return 2;
    end
    for _, nId in pairs(tbPlayerInBattle) do
    	local pPlayer = KGameBase.GetPlayerById(nId);
    	local tbPos = pPlayer.GetPosition();
    	local nDis = (tbPos.nX - tbNpcPos.nX)^2 + (tbPos.nY - tbNpcPos.nY)^2 + (tbPos.nZ - tbNpcPos.nZ)^2
    	tbPlayerDis[nDis] = nId;
    	tbDis[#tbDis + 1] = nDis;   		
    end
    --���б��еľ����������
    table.sort(tbDis);
 ------------------------------------------------------------
 ------------------------------------------------------------
 	local nPlayerNum = (#tbDis >= 3) and 3 or #tbDis;
	for i = 1, nPlayerNum do
		local nPlayerId = tbPlayerDis[tbDis[#tbDis + 1 - i]];
		local pPlayerToCastSkill = KGameBase.GetPlayerById(nPlayerId);
		local tbPlayerPos = pPlayerToCastSkill.GetPosition();
 		pNpc.pFightSkill.CastSkill(575,nPlayerId,tbPlayerPos.nX,tbPlayerPos.nY,tbPlayerPos.nZ);
	end
 	return 1;
end
	
	

