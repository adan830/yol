
-- �������Ը����������

-- ���������װgdpl
KinBattle.tbWinnerSuit = {1, 11, 1, 0};

KinBattle.BUFF_ATTACK = 1164;		-- ����ͷ��buff����Ч����
KinBattle.BUFF_DEF = 1165;			-- �ط�ͷ��buff

-- ������ʵ���
function KinBattle:OnLoadWinnerComplete(pNpc)
	KGameBase.AddNpc(pNpc, 65541, 3989, 4171, 1048576, 30);
	
	local nWinnerId = KActivity.GetKinBattleWinnerId();
	
	-- ����
	local tbKinInfo = GetPlayerKinInfo(nWinnerId);
	KChat.BroadcastNoticeMsg(string.format(Lang.mission.str29[Lang.Idx], tbKinInfo.szKinName));
	
	local pWinner = KGameBase.GetPlayerById(nWinnerId);
	if not pWinner then
		return;
	end
	
	Timer:Register(3 * Env.GAME_FPS, self.BroadcastWinnerMsg, self, tbKinInfo.szKinName, pWinner.szName);
	
	-- �������װ
	KinBattle:CheckWinnerSuit(pWinner);
	
	-- ������Ȩ��
	self:CheckChatDisableAuth(pWinner);
	
	local tbPlayers = KGameBase.GetAllPlayers()
	for _, pPlayer in pairs(tbPlayers) do
		if pPlayer.GetKinMasterId() == nWinnerId then
			-- ���ƺ�
			KinBattle:CheckTitle(pPlayer);
		end
	end
end

function KinBattle:BroadcastWinnerMsg(szKinName, szWinnerName)
	KChat.BroadcastNoticeMsg(string.format(Lang.mission.str30[Lang.Idx], szKinName, szWinnerName));
	return 0;
end

-- ����Ĭ��npc
function KinBattle:LoadDefaultWinner()
	local pNpc = KGameBase.CallNpc(2602, 65541, 4023, 4162, 1048576, 30);
	if pNpc then
		KActivity.SetKinBattleWinNpcId(pNpc.dwId);
	end
end

function KinBattle:ReloadKinBattleInfo()
	KGameBase.CenterExecute{"KinBattle:ReloadKinBattleInfo_GC"};
	return 0;
end

function KinBattle:DoReloadKinBattleInfo()
	KActivity.ReloadKinBattleInfo();
end

-- �Ƿ��������
function KinBattle:IsWinner(pPlayer)
	local nWinnerId = KActivity.GetKinBattleWinnerId();
	if pPlayer.dwId == nWinnerId then
		return 1;
	end
	return 0;
end

-- �Ƿ���������ͬһ����
-- Ŀǰ�˺��������ڵ�½ʱ��ʹ��
function KinBattle:IsWinnerMember(pPlayer)
	if pPlayer.GetKinId() <= 0 then
		return 0;
	end
	
	local nWinnerId = KActivity.GetKinBattleWinnerId();
	
	if pPlayer.GetKinMasterId() == nWinnerId and pPlayer.dwId ~= pPlayer.GetKinMasterId() then
		return 1;
	end
	
	return 0;
end

-- ������������װ���������ɾ��
function KinBattle:CheckWinnerSuit(pPlayer)
	if self:IsWinner(pPlayer) ~= 1 then
		Item:DelPlayerItem(pPlayer, unpack(KinBattle.tbWinnerSuit));
		return;
	end
	
	if Item:IfHasItem(pPlayer, unpack(KinBattle.tbWinnerSuit)) == 1 then
		return;
	end
	
	-- ����װ
	KItem.AddPlayerItem(pPlayer, unpack(KinBattle.tbWinnerSuit));

end

-- ������Ȩ��
function KinBattle:CheckChatDisableAuth(pPlayer)
	if self:IsWinner(pPlayer) ~= 1 then
		KChat.SetChatDisableAuth(pPlayer, 0);
		return;
	end
	
	KChat.SetChatDisableAuth(pPlayer, 1);
end

function KinBattle:OnLogin(nPlayerId)
	local pPlayer = KGameBase.GetPlayerById(nPlayerId);
	if not pPlayer then
		return;
	end
	
	self:CheckWinnerSuit(pPlayer);
	self:CheckTitle(pPlayer);
	self:CheckChatDisableAuth(pPlayer);
	
	if self:IsWinner(pPlayer) == 1 and KActivity.GetKinBattleWinTimes(pPlayer) < 2 then
		KActivity.SetKinBattleWinTimes(pPlayer, 2);
	end

	if self:IsWinner(pPlayer) == 1 then 
		KChat.BroadcastNoticeMsg(string.format(Lang.mission.str1216[Lang.Idx],pPlayer.szName));
	end
	
end

-- ���ƺ�
function KinBattle:CheckTitle(pPlayer)
	if self:IsWinner(pPlayer) == 1 then
		Title:AddTitleToCharacter(pPlayer, Title.KIN_BATTLE_WINNER, 1, 0);
	else
		Title:RemoveTitleToCharacter(pPlayer, Title.KIN_BATTLE_WINNER, 1, 0);
	end
	
	if self:IsWinnerMember(pPlayer) == 1 then
		Title:AddTitleToCharacter(pPlayer, Title.KIN_BATTLE_WINNER, 2, 0);
	else
		Title:RemoveTitleToCharacter(pPlayer, Title.KIN_BATTLE_WINNER, 2, 0);
	end
	
	-- ɾ��ͷ��������Чbuff
	pPlayer.pBufferEffect.ClearBuff(KinBattle.BUFF_ATTACK);
	pPlayer.pBufferEffect.ClearBuff(KinBattle.BUFF_DEF);
end

-- ?gs Title:AddTitleToCharacter(me, Title.KIN_BATTLE_WINNER, 2, 0);

function KinBattle:DoCheckOldWinnerAward_GS(nOldWinnerId, nWinKinId)
	local pOldWinner = KGameBase.GetPlayerById(nOldWinnerId);
	if not pOldWinner or pOldWinner.GetKinId() == nWinKinId then
		return;
	end
	
	-- ɾ���������װ
	Item:DelPlayerItem(pOldWinner, unpack(KinBattle.tbWinnerSuit));
	
	-- ɾ�ƺ�
	Title:RemoveTitleToCharacter(pOldWinner, Title.KIN_BATTLE_WINNER, 1, 0);
	
	-- ɾ����Ȩ��
	KChat.SetChatDisableAuth(pOldWinner, 0);
	
	KActivity.SetKinBattleWinTimes(pOldWinner, 0);
end

-- ɾ��ԭ��������ʳ�Ա�ƺ�
function KinBattle:DoCheckOldWinnerMemberAward(nWinKinId)
	local tbPlayers = KGameBase.GetAllPlayers()
	for _, pPlayer in pairs(tbPlayers) do
		if pPlayer and pPlayer.GetKinId() ~= nWinKinId then
			Title:RemoveTitleToCharacter(pPlayer, Title.KIN_BATTLE_WINNER, 1, 0);
			KActivity.SetKinBattleWinTimes(pPlayer, 0);
		end
	end
end

CallCenter:RegisterGlobalEvent(KOBJEVENT.emKOBJEVENTTYPE_PLAYER_LOGIN, KinBattle.OnLogin, KinBattle);
