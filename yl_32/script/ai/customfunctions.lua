-- �Զ���Action
Include('script/ai/argumentstrings.lua')


function AI:SELECT_SKILL_BY_ID(character, actionData)
        local p1, p2, p3, p4, p5 = actionData.GetParam();
        return AI:_SELECT_SKILL_BY_ID(character, p1, p2, p3, p4, p5, actionData);
end
--�Զ��庯����ѡ��ָ������
function AI:_SELECT_SKILL_BY_ID(pNpc, nSkillId, p2, p3, p4, p5,actionData)
	pNpc.pAI.SetAISkillId(0);
	local nLancherId = pNpc.dwId;
	local tbBattleInfo = AI.Brain[nLancherId].tbBattleInfo
	local nTargetId = pNpc.pAI.GetAITarget();

	local nResult = AI.Lib.SelectSkillById(nSkillId, tbBattleInfo, nLancherId, nTargetId)
	if nResult and (nResult == 1) then
		pNpc.pAI.SetAISkillId(nSkillId);
		AI.DebugOutput(string.format("�ɹ���ѡ��ָ������--(%d)%s",nSkillId,FightSkill:GetSkillName(nSkillId)));
		return 1;
	end
	return 2;
end

--=========================================================================

function AI:SELECT_TARGET_BY_TEMPLATE_ID(character, actionData)
        local p1, p2, p3, p4, p5 = actionData.GetParam();
        return AI:_SELECT_TARGET_BY_TEMPLATE_ID(character, p1, p2, p3, p4, p5, actionData);
end
--�Զ��庯����ѡ��ָ��Ŀ��
function AI:_SELECT_TARGET_BY_TEMPLATE_ID(pNpc, nTemplateId, p2, p3, p4, p5,actionData)
	pNpc.pAI.SetAITarget(0);
	local dwNpcId = pNpc.dwId;
	local tbBattleInfo = AI.Brain[dwNpcId].tbBattleInfo
	local nTargetId = AI.Lib.FindTargetByTemplateId(tbBattleInfo, nTemplateId);
	
	if not nTargetId then
	  return 2;
	end
	
	pNpc.pAI.SetAITarget(nTargetId);
	if(AI.bDebug == 1) then
		local szTarget;
		if(pNpc.dwId == nTargetId) then
			szTarget = "�Լ�"
		else
			local pRetTarget = KGameBase.GetCharacterById(nTargetId);
			szTarget = string.format("[%s]",pRetTarget.szName);
		end
		print(string.format("�ɹ���ѡ���� %s ��ΪĿ��", szTarget));
	end
	
	return 1
end

--=========================================================================

function AI:SAY_IN_CHANNEL(character, actionData)
        local p1, p2, p3, p4, p5 = actionData.GetParam();
        p2 = AI.ARGUMENT_STRING_TABLE[p2];
        return AI:_SAY_IN_CHANNEL(character, p1, p2, p3, p4, p5, actionData);
end
--�Զ��庯����Ƶ��˵��
function AI:_SAY_IN_CHANNEL(npc, nChannelId, szMsg, bTarget, p4, p5, actionData)
	local nTargetId = npc.pAI.GetAITarget();
	if bTarget and bTarget == 1 then
		if nTargetId <= 0 then
			AI.DebugOutput(string.format("Ƶ��˵����NPCû��Ŀ��"));
			return 1
		end
		
		local pCharacter = KGameBase.GetCharacterById(nTargetId)
		if not pCharacter then
			AI.DebugOutput(string.format("Ƶ��˵�����Ҳ���Ŀ��"));
			return 1
		end
		
		local szNewMsg = string.format(szMsg, pCharacter.szName)
		KChat.SendMsg(nChannelId, npc.dwId, nTargetId, npc.szName, szNewMsg);
	else
		KChat.SendMsg(nChannelId, npc.dwId, nTargetId, npc.szName, szMsg);
	end
	return 1
end

--=========================================================================

function AI:IS_HAVE_SPEC_BUFF(character, actionData)
        local p1, p2, p3, p4, p5 = actionData.GetParam();
        return AI:_IS_HAVE_SPEC_BUFF(character, p1, p2, p3, p4, p5, actionData);
end
--�Զ��庯�����ж���������Ƿ���ָ��BUFF
function AI:_IS_HAVE_SPEC_BUFF(pNpc, nBuffId, p2, p3, p4, p5)
	local nTargetId = pNpc.pAI.GetAITarget();
	local nRet = AI.Lib.IsHaveBuff(nTargetId, nBuffId)
	if nRet == 1 then
		return 1
	else
		return 2
	end
end

--=========================================================================

function AI:IS_SELF_HAVE_SPEC_BUFF(character, actionData)
        local p1, p2, p3, p4, p5 = actionData.GetParam();
        return AI:_IS_SELF_HAVE_SPEC_BUFF(character, p1, p2, p3, p4, p5, actionData);
end
--�Զ��庯�����ж��Լ������Ƿ���ָ��buff
function AI:_IS_SELF_HAVE_SPEC_BUFF(pNpc, nBuffId, p2, p3, p4, p5)
	local nRet = AI.Lib.IsHaveBuff(pNpc.dwId, nBuffId)
	if nRet == 1 then
		return 1
	else
		return 2
	end
end

--=========================================================================

function AI:GET_CUSTOM_BOOLEAN(character, actionData)
	local scene = character.GetScene();
	local p1, p2, p3, p4, p5 = actionData.GetParam();
	return  _GET_CUSTOM_BOOLEAN(character, p1, p2, p3, p4, p5);
end
--�Զ��庯������ȡNPC�Ĳ����Զ������
function AI:_GET_CUSTOM_BOOLEAN(char, p1, p2, p3, p4, p5)
	if p1 < 0 or p1 > 63 then
		print("NPC�Զ�������INDEXԽ�硣")
		return 2
	end
	
	local customValue = char.GetCustomBoolean(p1)
	if customValue then
		return 1
	else
		return 2
	end
end

--=========================================================================

function AI:SET_CUSTOM_BOOLEAN(character, actionData)
	local scene = character.GetScene();
	local p1, p2, p3, p4, p5 = actionData.GetParam();
	return  _SET_CUSTOM_BOOLEAN(character, p1, p2, p3, p4, p5);
end
--�Զ��庯��������NPC�Ĳ����Զ������
function AI:_SET_CUSTOM_BOOLEAN(char, p1, p2, p3, p4, p5)
	if p1 < 0 or p1 > 63 then
		print("NPC�Զ�������INDEXԽ�硣")
		return 1
	end
	
	if p2 == 0 then	
		char.SetCustomBoolean(p1, false)
	else
		char.SetCustomBoolean(p1, true)	
	end
	
	return 1
end

--=========================================================================

function AI:NPC_SELECT_ITSELF(character, actionData)
	local scene = character.GetScene();
	local p1, p2, p3, p4, p5 = actionData.GetParam();
	return  _NPC_SELECT_ITSELF(character, p1, p2, p3, p4, p5);
end
--�Զ��庯����NPCѡ���Լ�
function AI:_NPC_SELECT_ITSELF(char, p1, p2, p3, p4, p5)
	char.SetTarget(TARGET.NPC, char.dwID)
	return 1
end

--=========================================================================

function AI:SayToSelf(character, actionData)
	local scene = character.GetScene();
	local p1, p2, p3, p4, p5 = actionData.GetParam();
	p1 = ARGUMENT_STRING_TABLE[p1];
	return  _SayToSelf(character, p1, p2, p3, p4, p5);
end
--�Զ��庯������������
function AI:_SayToSelf(Char, p1, p2, p3, p4, p5)
	Char.Say(p1, 2048)
	return 1
end

--=========================================================================

function AI:IS_PLAYER_HAS_ITEM(character, actionData)
	local scene = character.GetScene();
	local p1, p2, p3, p4, p5 = actionData.GetParam();
	return  _IS_PLAYER_HAS_ITEM(character, p1, p2, p3, p4, p5);
end
--�Զ��庯�����ж�NPCѡ������Ƿ��иõ���
function AI:IS_PLAYER_HAS_ITEM(Character, ActionData)
	local nType, nIndex, nBookID, nWear = ActionData.GetParam()
	print("a ~~~~~")
	if not Character then
		return 2
	end
	if not (nType and nIndex) then
		return 2
	end
	print("b~~~~~~")
	local eTargetType, dwTargetID = Character.GetTarget()
	if dwTargetID then
		if IsPlayer(dwTargetID) then
			local player = GetPlayer(dwTargetID)
			if nBookID and nWear then
				if player.GetItemAmount(nType, nIndex, nBookID, nWear) >= 1 then
					return 1
				elseif player.GetItemAmount(nType, nIndex) >= 1 then
					return 1
				end
			end
			return 2
		else
			return 2
		end
	else
		return 2
	end
end

--=========================================================================

--�Զ��庯�����ж�װ���ĵ����Ƿ�Ϊָ������
function AI:IS_PLAYER_EQUIP(Character, ActionData)
	local eEquipmentType = {EQUIPMENT_INVENTORY.MELEE_WEAPON,
							EQUIPMENT_INVENTORY.RANGE_WEAPON,
							EQUIPMENT_INVENTORY.CHEST,
							EQUIPMENT_INVENTORY.HELM,
							EQUIPMENT_INVENTORY.AMULET,
							EQUIPMENT_INVENTORY.LEET_RING,
							EQUIPMENT_INVENTORY.RIGHT_RING,
							EQUIPMENT_INVENTORY.WAIST,
							EQUIPMENT_INVENTORY.PENDANT,
							EQUIPMENT_INVENTORY.PANTS,
							EQUIPMENT_INVENTORY.BOOTS,
							EQUIPMENT_INVENTORY.BANGLE,
							EQUIPMENT_INVENTORY.WAIST_EXTENG}
	local eTargetType, dwTargetID = Character.GetTarget()
	local player = GetPlyaer(dwTargetID)
	if not player then
		return 2
	end
	local nIndex, dwType, dwIndex = ActionData.GetParam()
	local item = player.GetEquipItem(eEquipmentType[nIndex])
	if not item then
		return 2
	end
	if item.dwType == dwType and item.dwIndex == dwIndex then
		return 1
	end
end

--=========================================================================

function AI:CLEAR_ALL_THREAT(character, actionData)
	local scene = character.GetScene();
	local p1, p2, p3, p4, p5 = actionData.GetParam();
	return  _CLEAR_ALL_THREAT(character, p1, p2, p3, p4, p5);
end
--�Զ��庯��������
function AI:_CLEAR_ALL_THREAT(char, p1, p2, p3, p4, p5)
	char.ClearAllThreat()
	return 1
end

--=========================================================================

function AI:RUN_TO_TARGET(character, actionData)
	local scene = character.GetScene();
	local p1, p2, p3, p4, p5 = actionData.GetParam();
	return  _RUN_TO_TARGET(character, p1, p2, p3, p4, p5);
end
--�Զ��庯��������Ŀ��
function AI:_RUN_TO_TARGET(char, p1, p2, p3, p4, p5)
	local dwTargetType, dwID = char.GetTarget()
	local etarget
	if IsPlayer(char.dwID) then
		etarget = GetPlayer(dwID)
		local nX, nY = etarget.nX, etarget.nY
		char.RunTo(nX, nY)
		return 1
	else
		etarget = GetNpc(dwID)
		local nX, nY = etarget.nX, etarget.nY
		char.RunTo(nX, nY)
		return 1
	end
end

--=========================================================================

function AI:SayString(character, actionData)
	local scene = character.GetScene();
	local p1, p2, p3, p4, p5 = actionData.GetParam();
	p1 = ARGUMENT_STRING_TABLE[p1];
	return  _SayString(character, p1, p2, p3, p4, p5);
end
--�Զ��庯�������������ַ�����
function AI:_SayString(npc, szTalkString, nRange, p3, p4, p5)
	if nRange <= 0 then
		npc.Say(szTalkString)
	else
		npc.Say(szTalkString, nRange)
	end
	
	return 1
end

--=========================================================================

function AI:FIRE_AI_EVENT(character, actionData)
	local scene = character.GetScene();
	local p1, p2, p3, p4, p5 = actionData.GetParam();
	p2 = ARGUMENT_STRING_TABLE[p2];
	return  _FIRE_AI_EVENT(character, p1, p2, p3, p4, p5);
end
--�Զ��庯������ָ��NPC�����¼�
function AI:_FIRE_AI_EVENT(char, nAIEventID, szNicknames, p3, p4, p5)
	local scene = char.GetScene()
	local Split = function(szString, szSpliter)
		local tSplited = {}
		local nCount = 0								-- ��¼�ҵ����зַ�����
		local nStartLoc = 0								-- ��¼�������з��ַ����Ŀ�ʼ��
		local nEndLoc = 0								-- ��¼�������з��ַ����Ľ�����
		local bFoundSpliter = false						-- ��¼�Ƿ��ҵ��зַ�
		
		if not szSpliter then							-- ���û�д���ָ�����зַ�, ��Ĭ��Ϊ�Ʊ��tab
			szSpliter = "\t"
		end
		local szFormated = szString .. szSpliter		-- ��ʽ��ԭ�ַ���
		
		repeat
			nCount = nCount + 1
			bFoundSpliter, nEndLoc = szFormated:find(szSpliter, nStartLoc)
			if bFoundSpliter then
				tSplited[nCount] = szFormated:sub(nStartLoc, nEndLoc - #szSpliter)
				if not tSplited[nCount] then
					tSplited[nCount] = ""
				end
				nStartLoc = nEndLoc + 1
			end
		until not bFoundSpliter
		return tSplited
	end
	
	local tNames = Split(szNicknames, ",")
	for i, v in pairs(tNames) do
		local npc = scene.GetNpcByNickName(v)
		if npc then
			npc.FireAIEvent(nAIEventID, char.dwID, 0)
		end
	end

	return 1			
end

--=========================================================================

function AI:SET_TARGET_OF_NICKNAME(character, actionData)
	local scene = character.GetScene();
	local p1, p2, p3, p4, p5 = actionData.GetParam();
	p1 = ARGUMENT_STRING_TABLE[p1];
	return  _SET_TARGET_OF_NICKNAME(character, p1, p2, p3, p4, p5);
end
--�Զ��庯����ѡ��ָ��NPC
function AI:_SET_TARGET_OF_NICKNAME(char, szNickName, p2, p3, p4, p5)
	local scene = char.GetScene()
	local npc = scene.GetNpcByNickName(szNickName)

	if npc then
		char.SetTarget(TARGET.NPC, npc.dwID)
		return 1
	end

	return 2
end

--=========================================================================

function AI:GetCustomTarget(character, actionData)
	local scene = character.GetScene();
	local p1, p2, p3, p4, p5 = actionData.GetParam();
	p1 = ARGUMENT_STRING_TABLE[p1];
	return  _GetCustomTarget(character, p1, p2, p3, p4, p5);
end
--�Զ��庯����ΪNPC��ȡĿ��
function AI:_GetCustomTarget(char, p1, p2, p3, p4, p5)	
	local szNickName = p1;
	if not szNickName then
		return 2;
	end
	
	local target = scene.GetNpcByNickName(szNickName);
	if not target then
		return 2;
	end
	
	character.SetTarget(TARGET.NPC, target.dwID);
	return 1;
end

--=========================================================================

function AI:SET_NPC_DISAPPEAR(character, actionData)
	local scene = character.GetScene();
	local p1, p2, p3, p4, p5 = actionData.GetParam();
	return  _SET_NPC_DISAPPEAR(character, p1, p2, p3, p4, p5);
end
--�Զ��庯��������NPC��ʧ
function AI:_SET_NPC_DISAPPEAR(char, p1, p2, p3, p4, p5)
	char.SetDisappearFrames(p1, p2)
	return 1
end

--=========================================================================

function AI:COMPARE_CUSTOM_INTEGER(character, actionData)
	local scene = character.GetScene();
	local p1, p2, p3, p4, p5 = actionData.GetParam();
	return  _COMPARE_CUSTOM_INTEGER(character, p1, p2, p3, p4, p5);
end
--�Զ��庯�����Ƚ�NPC���Զ������ֱ���
function AI:_COMPARE_CUSTOM_INTEGER(char, p1, p2, p3, p4, p5)
	local customValue = char.GetCustomInteger4(p1)
	if customValue > p2 then	
		return 1
	elseif customValue == p2 then
		return 2
	elseif customValue < p2 then
		return 3
	end
end

--=========================================================================

function AI:SET_CUSTOM_INTEGER(character, actionData)
	local scene = character.GetScene();
	local p1, p2, p3, p4, p5 = actionData.GetParam();
	return  _SET_CUSTOM_INTEGER(character, p1, p2, p3, p4, p5);
end
--�Զ��庯��������NPC�������Զ������
function AI:_SET_CUSTOM_INTEGER(char, nIndex, nValue, nMode, p4, p5)
	if nIndex < 0 or nIndex > 63 then
		print("NPC�Զ�������INDEXԽ�硣")
		return 1
	end
		
	if nMode == 0 then
		char.SetCustomInteger1(nIndex, nValue)
	elseif nMode == 1 then
		char.SetCustomInteger2(nIndex, nValue)
	elseif nMode == 2 then
		char.SetCustomInteger4(nIndex, nValue)
	end
	
	return 1
end

--=========================================================================

function AI:MOVE_TO_POINT(character, actionData)
	local scene = character.GetScene();
	local p1, p2, p3, p4, p5 = actionData.GetParam();
	return  _MOVE_TO_POINT(character, p1, p2, p3, p4, p5);
end
-- �Զ�����Ϊ: �ƶ���ĳ��

-- ����˵��:
--   �ƶ�ģʽ:  0: Teleport
--				1: Walk
--				2: Run
--   ����X:		Ŀ�������X
--   ����Y:		Ŀ�������Y

-- pansong 08.10.29 

function AI:_MOVE_TO_POINT(character, nMode, nX , nY, nZ)

	if nMode == 1 then --�ƶ�
		pNpc.GoTo(nX, nY, nZ)
	elseif nMode == 2 then --˲��		
		pNpc.TeleportTo(0, nX, nY, nZ)
		return 1
	end
	return 2
end

function AI:ADD_BUFF(character, actionData)
	local scene = character.GetScene();
	local p1, p2, p3, p4, p5 = actionData.GetParam();
	return  _ADD_BUFF(character, p1, p2, p3, p4, p5);
end
function AI:_ADD_BUFF(character, dwBuffID, nBuffLevel, nCount, nLeftFrame)
	if nLeftFrame == 0 and nCount ~= 0 then
		character.AddBuff(character.dwID, character.nLevel, dwBuffID, nBuffLevel, nCount)
	elseif nCount == 0 then
		character.AddBuff(character.dwID, character.nLevel, dwBuffID, nBuffLevel)
	else
		character.AddBuff(character.dwID, character.nLevel, dwBuffID, nBuffLevel, nCount, nLeftFrame)
	end

	return 1
end

function AI:CLEAR_SELECTION(character, actionData)
	local scene = character.GetScene();
	local p1, p2, p3, p4, p5 = actionData.GetParam();
	return  _CLEAR_SELECTION(character, p1, p2, p3, p4, p5);
end
--�Զ��庯����NPC���ѡ��
function AI:_CLEAR_SELECTION(char, p1, p2, p3, p4, p5)
	char.SetTarget(TARGET.NO_TARGET, 0)
	return 1
end

--=========================================================================

function AI:ADD_THREAT(character, actionData)
	local scene = character.GetScene();
	local p1, p2, p3, p4, p5 = actionData.GetParam();
	return  _ADD_THREAT(character, p1, p2, p3, p4, p5);
end
--�Զ��庯����NPC��ѡ��Ŀ��ӳ��
function AI:_ADD_THREAT(char, p1, p2, p3, p4, p5)
	local targetType, targetID = char.GetTarget()	
	
	if targetType == 1 and targetID == 0 then
		return 2
	else
		char.ModifyThreat(targetID, p1)
	end
	
	return 1
end

--=========================================================================

function AI:CHARACTER_SAY(character, actionData)
	local scene = character.GetScene();
	local p1, p2, p3, p4, p5 = actionData.GetParam();
	p1 = ARGUMENT_STRING_TABLE[p1];
	p4 = ARGUMENT_STRING_TABLE[p4];
	return  _CHARACTER_SAY(character, p1, p2, p3, p4, p5);
end
-- ��ָ���ǳƵĽ�ɫ˵��
-- ˵����ʽ: 0:Whisper ; 1:Say ; 2:Yell ; 3:SayTo ; 4:YellTo

function AI:_CHARACTER_SAY(character, szNickName, nMode, dwTargetID, szTalk)
	local scene = character.GetScene()
	local npc = scene.GetNpcByNickName(szNickName)
	if npc then
		if nMode == 0 then
			npc.Whisper(dwTargetID, szTalk)
		elseif nMode == 1 then
			npc.Say(szTalk, 2048)
		elseif nMode == 2 then
			npc.Yell(szTalk)
		elseif nMode == 3 then
			npc.SayTo(dwTargetID, szTalk)
		elseif nMode == 4 then
			npc.YellTo(dwTargetID, szTalk)
		end
	end
	
	return 1
end
