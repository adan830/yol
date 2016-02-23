-- File       : matchrule.lua
-- Creator    : liyun
-- Date       : 2012-10-22 09:12:01
-- Description: �����Ŷӹ����߼�ʵ��

-- data structure
-- �����ȴ����У������һ�������Ķ��У�ʹ�ø���������key
-----------------------------------------------------------------
if not (MODULE_GAMECENTER) then
	return
end

-- local tbInstanceWaitQueueSample = {
--	[1] = {
--		"Tank" = {{p = player1, time = KGameBase:GetTime(), Accept = 0}, item, item}, 
--		"Help" = {p1, p2}, 
--		"Dps" = {p3, p5}, 
--		"Team" = {team, team}
--	},
--	[2] = {"Tank" = {player1, player2, player3}, "Help" = {p1, p2}, "Dps" = {p3, p5}, "Team" = {team, team}},
--	[5] = {"Tank" = {player1, player2, player3}, "Help" = {p1, p2}, "Dps" = {p3, p5}, "Team" = {team, team}},
--	[10] = {"Tank" = {player1, player2, player3}, "Help" = {p1, p2}, "Dps" = {p3, p5}, "Team" = {team, team}},
--}


-- �����Ѿ�ѡ�����ң����ֻ��ѡ��һ�����
-- local tbSelecteSample = {
--	[1] = {
--		"Tank" = {player, player}, 
--		"help" = {player, plyaer}, 
--		"Dps" = {player, player}, 
--		"Team" = {p1, p2}
--	},
--	[3] = {"Tank" = {player, player}, "help" = {player, plyaer}, "Dps" = {player, player}, "Team" = {p1, p2}},
--	[7] = {"Tank" = {player, player}, "help" = {player, plyaer}, "Dps" = {player, player}, "Team" = {p1, p2}},
--	[10] = {"Tank" = {player, player}, "help" = {player, plyaer}, "Dps" = {player, player}, "Team" = {p1, p2}},
--	[35] = {"Tank" = {player, player}, "help" = {player, plyaer}, "Dps" = {player, player}, "Team" = {p1, p2}},
--}


PVEMatch.MAX_TEAM_NUM = 3;
PVEMatch.MATCH_INTERVAL = 100; -- ƥ��ʱ��������λΪTimer��֡��
PVEMatch.ENTER_TIME_OUT = 30; -- ƥ��ɹ���ѡ�����ܾ������ؿ�������ʱ�䣬����Ϊ��λ

-- �����ȴ�����
PVEMatch.tbInstanceWaitQueue = {};

-- �Ѿ�ƥ����ѡ������
PVEMatch.tbSelected = {};

-- �����Ѿ�������е���ң���ֹ�ظ�����ʹ�����ID������
PVEMatch.tbEnteredPlayers = {};

-- ��¼�Ѿ�ƥ����ɵĸ�������
PVEMatch.tbMatchFinishedInstanceIndex = {};

-- ��¼��ʱ��ID
PVEMatch.tbMatchFinishedTimerID = {};

PVEMatch.tbVeryfyTeamMember = {};

-------------------------------------------------------------------------------
-- ��Ҽ��븱���ȴ��б�tbPlayer���Զ�������ݽṹ����ͻ��˴����pPlayer��ͬ
--[[tbPlayer_Sample = {
	dwId = playid,  -- ���Id
	szType = "Dps",  -- ����ְ�����ͣ���Dps,Help,Tank
	nFaction = 1,  -- ������ɣ�ö��ֵ��1��2��3��4
	nRoute = 1001, -- ��������faction*1000 + route�����������ɺ��츳·�߶���ֵ���㴦���츳ö��ֵ��0,1,2,3
	bAccept = 0,  -- ����Ƿ�ͬ����븱������ͻ�����ͼ�����״̬�Ի�������Ӧ
	time = KGameBase.GetTime(),  -- ��ҽ����Ŷӵ�ʱ�䣬������û�����ֵ��ֻ�ж�������ʱ��
}
]]

function PVEMatch:RequestEnterStage_GC(tbPlayerIds, nDifficulty)
	GlobalExecute({"Stage:DoEnterGame", tbPlayerIds, nDifficulty});
end

function PVEMatch:RequestEnterMultiInstance_GC(tbPlayerIds, nMapId)
	GlobalExecute({"MultiInstance:DoEnterGame", tbPlayerIds, nMapId});
end

-- ���˼���
function PVEMatch:SingleRequestEnterInstance_GC(tbPlayer, tbInstanceIndex)
	if PVEMatch:IsPlayerEntered(tbPlayer) == 1 then
		print("PVEMatch:SingleRequestEnterInstance_GC: player re-entered is not allowed, pPlayer.dwId="..tbPlayer.dwId);
		return; -- ���ظ��������
	end
	
	local tbQueue = self.tbInstanceWaitQueue;
	if type(tbInstanceIndex) ~= "table" or tbInstanceIndex[1] == nil then
		print("PVEMatch:SingleRequestEnterInstance_GC: parm tbInstanceIndex must be non-empty table");
		return;
	end
	
	local szType = tbPlayer.szType;
	local bNotified = 0;
	for _, nInstanceIndex in pairs(tbInstanceIndex) do
		if type(tbQueue[nInstanceIndex]) ~= "table" then
			tbQueue[nInstanceIndex] = {};
		end
		if type(tbQueue[nInstanceIndex][szType]) ~= "table" then
			tbQueue[nInstanceIndex][szType] = {};
		end
		
		print("PVEMatch:SingleRequestEnterInstance_GC: player "..tbPlayer.dwId.." entered queue. InstanceIndex is "..nInstanceIndex);
		table.insert(tbQueue[nInstanceIndex][szType], tbPlayer);
		if (bNotified == 0) then
			bNotified = 1;
			GlobalExecute({"PVEMatch:NotifyPlayerEnterQueue_GS", tbPlayer, nInstanceIndex, 1});
		else
			GlobalExecute({"PVEMatch:NotifyPlayerEnterQueue_GS", tbPlayer, nInstanceIndex, 0});
		end
	end 
	
	self:RecordEnteredPlayer(tbPlayer);
end

PVEMatch.ROOM_XOYO_EASY = "XoyoGameEasy";
PVEMatch.ROOM_XOYO_NORMAL = "XoyoGameNormal";
PVEMatch.ROOM_XOYO_HARD = "XoyoGameHard";
PVEMatch.ROOM_XOYO_VERY_HARD = "XoyoGameVeryHard";

-- ��Ӽ���
-- tbTeam = {tbPlayer, tbPlayer, tbPlayer, ...}
function PVEMatch:TeamRequestEnterInstance_GC(tbTeam, tbInstanceIndex)
	--[[
	if #tbTeam == 1 then
		print("PVEMatch:TeamRequestEnterInstance_GC: team must have 2 or more players");
		return;
	end
	--]]
	
	if self:IsTeamEntered(tbTeam) == 1 then
		print("PVEMatch:TeamRequestEnterInstance_GC: team re-entered is not allowed");
		return;
	end
	
	if type(tbInstanceIndex) ~= "table" or tbInstanceIndex[1] == nil then
		print("PVEMatch:TeamRequestEnterInstance_GC: parm tbInstanceIndex must be non empty table");
		return; 
	end
	
	-- ���ֱ�ӽ������Ŷ���
	if tbInstanceIndex[1] == self.ROOM_XOYO_EASY or
		tbInstanceIndex[1] == self.ROOM_XOYO_NORMAL or
		tbInstanceIndex[1] == self.ROOM_XOYO_HARD or
		tbInstanceIndex[1] == self.ROOM_XOYO_VERY_HARD then
		GlobalExecute({"PVEMatch:DelayEnterStageRequest_GS", tbTeam});
	else
	    GlobalExecute({"PVEMatch:DelayEnterMultiInstanceRequest_GS", tbTeam, tbInstanceIndex[1]});
	end
	
	--[[
	-- ����Ӽ��뵽�����ĵȴ�������
	local tbQueue = self.tbInstanceWaitQueue;
	local bNotified = 0;
	for _, nInstanceIndex in pairs(tbInstanceIndex) do
		if type(tbQueue[nInstanceIndex]) ~= "table" then
			tbQueue[nInstanceIndex] = {};
		end
		if type(tbQueue[nInstanceIndex]["Team"]) ~= "table" then
			tbQueue[nInstanceIndex]["Team"] = {};
		end
		
		print("PVEMatch:TeamRequestEnterInstance_GC: entered queue. InstanceIndex is "..nInstanceIndex);
		table.insert(tbQueue[nInstanceIndex]["Team"], tbTeam);
		if (bNotified == 0) then
			bNotified = 1;
			GlobalExecute({"PVEMatch:NotifyTeamEnterQueue_GS", tbTeam, nInstanceIndex, 1});
		else
			GlobalExecute({"PVEMatch:NotifyTeamEnterQueue_GS", tbTeam, nInstanceIndex, 0});
		end
	end
	
	self:RecordEnteredTeam(tbTeam);
	--]]
end

function PVEMatch:VeryfyTeamMember_GC(tbTeamMem, nCaptainId, nInstanceIndex)
	for _, nPlayerId in pairs(tbTeamMem) do
		local bOnline = IsPlayerOnLine(nPlayerId);
		if (bOnline == 0) then
			GlobalExecute({"PVEMatch:NotifyTeamInfo_GC", nCaptainId, Lang.gcscript.str22[Lang.Idx]});
			return;
		end
	end

	self.tbVeryfyTeamMember[nCaptainId] = {};

	local tbVeryfy = self.tbVeryfyTeamMember[nCaptainId];
	tbVeryfy["InstanceIndex"] = nInstanceIndex;
	tbVeryfy["Team"] = {};
	tbVeryfy["TeamLevel"] = {};
	tbVeryfy["NoDegree"] = {};
	tbVeryfy["InMapCopy"] = {};
	tbVeryfy["StageMoping"] = {};
	tbVeryfy["VeryfyInfo"] = {};

	for _, nPlayerId in pairs(tbTeamMem) do
		tbVeryfy["VeryfyInfo"][nPlayerId] = {
			["Veryfied"] = 0,
			["Name"] = "",
		};
	end

	GlobalExecute({"PVEMatch:VeryfyTeamMember_GS", tbTeamMem, nCaptainId, nInstanceIndex});
end

function PVEMatch:VeryfyTeamMemberResult_GC(nCaptainId, tbVeryfied, tbNoDegree, tbInMapCopy, tbStageMoping, tbTeam, tbTeamLevel)
	if (self.tbVeryfyTeamMember[nCaptainId] == nil) then
		print("PVEMatch:VeryfyTeamMemberResult_GC " .. "nCaptainId nil ");
		return;
	end

	local tbVeryfy = self.tbVeryfyTeamMember[nCaptainId];
	if (tbVeryfy == nil) then
		print("PVEMatch:VeryfyTeamMemberResult_GC nCaptainId error");
		return;
	end

	for nPlayerId, szName in pairs(tbVeryfied) do
		if tbVeryfy["VeryfyInfo"][nPlayerId] == nil then
			print("PVEMatch:VeryfyTeamMemberResult_GC member id error");
			return;
		end

		tbVeryfy["VeryfyInfo"][nPlayerId]["Veryfied"] = 1;
		tbVeryfy["VeryfyInfo"][nPlayerId]["Name"] = szName;
	end

	for _, nPlayerId in pairs(tbNoDegree) do
		table.insert(tbVeryfy["NoDegree"], nPlayerId);
	end

	for _, nPlayerId in pairs(tbInMapCopy) do
		table.insert(tbVeryfy["InMapCopy"], nPlayerId);
	end
	
	for _, nPlayerId in pairs(tbStageMoping) do
		table.insert(tbVeryfy["StageMoping"], nPlayerId);
	end

	for _, tbTeamInfo in pairs(tbTeam) do
		table.insert(tbVeryfy["Team"], tbTeamInfo);
	end

	for nPlayerId, nMemLevel in pairs(tbTeamLevel) do
		tbVeryfy["TeamLevel"][nPlayerId] = nMemLevel;
	end

	local bGetAllResult = 1;
	for _, tbVeryfyInfo in pairs(tbVeryfy["VeryfyInfo"]) do
		if (tbVeryfyInfo["Veryfied"] == 0) then
			bGetAllResult = 0;
		end
	end

	if (bGetAllResult == 1) then
		if (#tbVeryfy["NoDegree"] > 0) then
			local nPlayerId = tbVeryfy["NoDegree"][1];
			--local szName = tbVeryfy[nPlayerId]["Name"];
			local szName = tbVeryfy["VeryfyInfo"][nPlayerId]["Name"];
			if (nPlayerId == nCaptainId) then
				if (tbVeryfy["InstanceIndex"] >= 0) then
					GlobalExecute({"PVEMatch:NotifyTeamInfo_GC", nCaptainId, Lang.gcscript.str23[Lang.Idx]});
				else
					GlobalExecute({"PVEMatch:NotifyTeamInfo_GC", nCaptainId, Lang.gcscript.str24[Lang.Idx]});
				end
			else
				if (tbVeryfy["InstanceIndex"] >= 0) then 
					GlobalExecute({"PVEMatch:NotifyTeamInfo_GC", nCaptainId, string.format(Lang.gcscript.str25[Lang.Idx],szName)})
				else
					GlobalExecute({"PVEMatch:NotifyTeamInfo_GC", nCaptainId, string.format(Lang.gcscript.str26[Lang.Idx],szName)})
				end
			end
			return;
		end

		if (#tbVeryfy["InMapCopy"] > 0) then
			local nPlayerId = tbVeryfy["InMapCopy"][1];
			local szName = tbVeryfy["VeryfyInfo"][nPlayerId]["Name"];
			if (nCaptainId == nPlayerId) then
				GlobalExecute({"PVEMatch:NotifyTeamInfo_GC", nCaptainId, Lang.gcscript.str27[Lang.Idx]});
			else
				GlobalExecute({"PVEMatch:NotifyTeamInfo_GC", nCaptainId,  string.format(Lang.gcscript.str28[Lang.Idx],szName)});
			end
			return;
		end
		
		if (#tbVeryfy["StageMoping"] > 0) then
			local nPlayerId = tbVeryfy["StageMoping"][1];
			local szName = tbVeryfy["VeryfyInfo"][nPlayerId]["Name"];
			if (nCaptainId == nPlayerId) then
				GlobalExecute({"PVEMatch:NotifyTeamInfo_GC", nCaptainId, Lang.gcscript.str29[Lang.Idx]});
			else
				GlobalExecute({"PVEMatch:NotifyTeamInfo_GC", nCaptainId, string.format(Lang.gcscript.str30[Lang.Idx],szName) });
			end
			return;
		end

		GlobalExecute({"PVEMatch:VeryfyTeamLevel_GS", nCaptainId, tbVeryfy["InstanceIndex"], tbVeryfy["TeamLevel"], tbVeryfy["Team"], tbVeryfy["VeryfyInfo"]});
	end
end

-- ͬ����븱��
function PVEMatch:AcceptEnterInstance_GC(nPlayerId)
	assert(nPlayerId > 0);

	local nInstanceIndex = self:GetInstanceIndexByPlayerIdFromSelected(nPlayerId);
	if (nInstanceIndex == nil) then
		assert(0);
		return;
	end

	-- ����ͬ��״̬
	local tbSelected = self.tbSelected[nInstanceIndex];
	local bFind = 0;
	local tbAcceptPlayer = nil;

	for _, tbPlayers in pairs(tbSelected) do
		for _, tbPlayer in pairs(tbPlayers) do
			if tbPlayer.dwId == nPlayerId then
				-- �ظ�����
				if tbPlayer.nAccept == 1 then
					return;
				end
				
				tbPlayer.nAccept = 1;
				bFind = 1;
				tbAcceptPlayer = tbPlayer;
				break;
			end
		end
		if bFind == 1 then
			break;
		end
	end
	
	-- û�ҵ������ң��򲻴���
	if bFind == 0 or tbAcceptPlayer == nil then
		assert(0);
		return;
	end
	
	-- �㲥������Ϣ
	local tbSelPlayer = {};
	for _, tbPlayers in pairs(tbSelected) do
		for _, tbPlayer in pairs(tbPlayers) do
			table.insert(tbSelPlayer, tbPlayer);
		end
	end

	if #tbSelPlayer > 0 then
		GlobalExecute({"PVEMatch:NotifyAcceptEnterInstance_GS", tbSelPlayer, tbAcceptPlayer});
	end
	
	-- �������ȫ��ͬ����븱��
	if self:IsAllAcceptedEnterInstance(nInstanceIndex) == 1 then
		local tbSelected = self.tbSelected[nInstanceIndex];
		self.tbSelected[nInstanceIndex] = nil;
		local tbPlayers = {};

		for _, tbP in pairs(tbSelected) do
			for _, tbPlayer in pairs(tbP) do
				self:ClearEnteredPlayer(tbPlayer);
				table.insert(tbPlayers, tbPlayer);
			end
		end

		-- �����ʱ��
		local nTimerId = self.tbMatchFinishedTimerID[nInstanceIndex];
		self.tbMatchFinishedTimerID[nInstanceIndex] = 0;
		if (nTimerId and nTimerId > 0) then
			Timer:Close(nTimerId);
		end

		-- ����ֱ�ӽ��븱��
		self.tbMatchFinishedInstanceIndex[nInstanceIndex] = 0;
		GlobalExecute({"PVEMatch:NotifyTeamLeaveQueue_GS", tbPlayers, nInstanceIndex, 0});
		self:EnterInstance(tbPlayers, nInstanceIndex);
	end
end

 -- ��ұ�ƥ��ɹ���ܾ����븱��������������Ƴ�ѡ������������Ҫ�����������Ƴ�
function PVEMatch:RejectEnterInstance_GC(nPlayerId)
	local nInstanceIndex = self:GetInstanceIndexByPlayerIdFromSelected(nPlayerId);
	if nInstanceIndex == nil then
		assert(0);
		return;
	end
	
	-- ��ѡ�����Ƴ�������ڶ����У�������������Ƴ�
	local tbNotifyPlayers = {};
	local tbNotifyLeave = {};
	local tbSelected = self.tbSelected[nInstanceIndex];
	local bFind = 0;
	local tbRejectPlayer = nil;

	for szType, tbPlayers in pairs(tbSelected) do
		for k, tbPlayer in pairs(tbPlayers) do
			if tbPlayer.dwId == nPlayerId then
				bFind = 1;
				tbRejectPlayer = tbPlayer;
				if szType == "Team" then
					for _, varP in pairs(tbPlayers) do
						table.insert(tbNotifyPlayers, varP);
						table.insert(tbNotifyLeave, varP);
					end
					self:ClearEnteredTeam(tbPlayers);
					tbSelected["Team"] = nil;
				else
					table.insert(tbNotifyPlayers, tbPlayer);
					table.insert(tbNotifyLeave, tbPlayer);
					self:ClearEnteredPlayer({dwId = nPlayerId});
					table.remove(tbPlayers, k);
				end
				self.tbMatchFinishedInstanceIndex[nInstanceIndex] = 0;
				break;
			end
		end
		if bFind == 1 then 
			break; 
		end;
	end
	
	if bFind == 0 or tbRejectPlayer == nil then
		assert(0);
		return;
	end

	-- �����ʱ��
	local nTimerId = self.tbMatchFinishedTimerID[nInstanceIndex];
	self.tbMatchFinishedTimerID[nInstanceIndex] = 0;
	if (nTimerId and nTimerId > 0) then
		Timer:Close(nTimerId);
	end
	
	-- ֪ͨ������ѡ���������˾ܾ����븱��
	for _, tbPlayers in pairs(tbSelected) do
		for _, tbPlayer in pairs(tbPlayers) do
			tbPlayer.nAccept = 0; -- ���������ͬ��״̬
			table.insert(tbNotifyPlayers, tbPlayer);
		end
	end
	
	if #tbNotifyPlayers > 0 then
		GlobalExecute({"PVEMatch:NotifyRejectEnterInstance_GS", tbNotifyPlayers, tbRejectPlayer});
	end

	if #tbNotifyLeave > 0 then
		GlobalExecute({"PVEMatch:NotifyTeamLeaveQueue_GS", tbNotifyLeave, nInstanceIndex})
	end
end

-- �ӵȴ�������ȡ����ҳ���
function PVEMatch:GetWaitPlayer()
	local nPlayerId = 0;

	for nInstanceIndex, tbWaitQueue in pairs(self.tbInstanceWaitQueue) do
		for szType, tbPlayers in pairs(tbWaitQueue) do
			if (szType ~= "Team") then
				for _, tbPlayer in pairs(tbPlayers) do
					nPlayerId = tbPlayer.dwId;
					break;
				end
			end
			if (nPlayerId > 0) then
				break;
			end
		end
		if (nPlayerId > 0) then
			break;
		end
	end
	
	if (nPlayerId > 0) then
		self:RemovePlayerFromWaitQueue({dwId = nPlayerId}, 0, 1);
	end
	
	return nPlayerId;
end

-- �뿪����
function PVEMatch:PlayerLeaveWaitQueue(nPlayerId)
	self:PlayerLeave(nPlayerId);
end

-- ����뿪���������ߣ����ߣ��ȸ�������뿪����
function PVEMatch:PlayerLeave(nPlayerId)
	-- ����������ڵȴ��б��У���ƥ���ϣ��Ѿ�ƥ�����
	local nInstanceIndex = self:GetInstanceIndexByPlayerIdFromSelected(nPlayerId);
	if nInstanceIndex == nil then -- �ڵȴ������У���û�б�ƥ����
		self:RemovePlayerFromWaitQueue({dwId = nPlayerId}, 1, 1);
	elseif self:IsMatchFinished(nInstanceIndex) == 0 then -- ��ƥ����
		self:RemovePlayerFromSelected({dwId = nPlayerId}, 1, 1);
		self:RemovePlayerFromWaitQueue({dwId = nPlayerId}, 1, 1);
	elseif self:IsAllAcceptedEnterInstance(nInstanceIndex) == 0 then -- �Ѿ�ƥ�����
		self:RejectEnterInstance_GC(nPlayerId);
	else
		print("PVEMatch:PlayerLeave: unknow condition with player leave, please check");
		self:RemovePlayerFromSelected({dwId = nPlayerId}, 1, 1);
		self:RemovePlayerFromWaitQueue({dwId = nPlayerId}, 1, 1);
		self:RejectEnterInstance_GC(nInstanceIndex);
	end
end

-- �����������ȴ��������Ƴ�������ң��������ӣ����Ƴ���������
function PVEMatch:RemovePlayerFromWaitQueue(tbPlayer, bNotify, bClearPlayer)
	bNotify = bNotify or 0;
	bClearPlayer = bClearPlayer or 0;

	local bNotified = 0;
	
	for nInstanceIndex, tbWaitQueue in pairs(self.tbInstanceWaitQueue) do
		bNotified = self:RemovePlayerFRomInstanceWaitQueue(nInstanceIndex, tbPlayer, bNotify, bClearPlayer, bNotified);
	end
end

function PVEMatch:RemovePlayerFRomInstanceWaitQueue(nInstanceIndex, tbPlayer, bNotify, bClearPlayer, bNotified)
	local bFind = 0;
	local tbWaitQueue = self.tbInstanceWaitQueue[nInstanceIndex];

	repeat
		bFind = 0;

		for szType, tbPlayers in pairs(tbWaitQueue) do
			if (szType == "Team") then
				for key, tbTeam in pairs(tbPlayers) do
					for _, tbPlayer2 in pairs(tbTeam) do
						if (tbPlayer2.dwId == tbPlayer.dwId) then
							bFind = 1;
							table.remove(tbPlayers, key);
							if (bNotify == 1) then
								if (bNotified == 0) then
									bNotified = 1;
									GlobalExecute({"PVEMatch:NotifyTeamLeaveQueue_GS", tbTeam, nInstanceIndex, 1});
								else
									GlobalExecute({"PVEMatch:NotifyTeamLeaveQueue_GS", tbTeam, nInstanceIndex, 0});
								end
							end
							if (bClearPlayer == 1) then
								self:ClearEnteredTeam(tbTeam);
							end
						end
					end
				end
			else
				for key, tbPlayer2 in pairs(tbPlayers) do
					if (tbPlayer2.dwId == tbPlayer.dwId) then
						bFind = 1;
						table.remove(tbPlayers, key);
						if (bNotify == 1) then
							if (bNotified == 0) then
								bNotified = 1;
								GlobalExecute({"PVEMatch:NotifyPlayerLeaveQueue_GS", tbPlayer2, nInstanceIndex, 1});
							else
								GlobalExecute({"PVEMatch:NotifyPlayerLeaveQueue_GS", tbPlayer2, nInstanceIndex, 0});
							end
						end
						if (bClearPlayer == 1) then
							self:ClearEnteredPlayer({dwId = tbPlayer2.dwId});
						end
					end
				end
			end
		end
	until bFind == 0;

	return bNotified;
end

-- ��ƥ�����Ƴ���ң�������ֱ���Ƴ���������Ƴ���������
function PVEMatch:RemovePlayerFromSelected(tbPlayer, bNotify, bClearPlayer, nExcludeIndex)
	bClearPlayer = bClearPlayer or 0;
	bNotify = bNotify or 0;
	nExcludeIndex = nExcludeIndex or 0;
	local bNotified = 0;

	for nInstanceIndex, tbWaitQueue in pairs(self.tbSelected) do
		if nInstanceIndex ~= nExcludeIndex then
			bNotified = self:RemovePlayerFromInstanceSelected(nInstanceIndex, tbPlayer, bNotify, bClearPlayer, bNotified);
		end
	end
end

function PVEMatch:RemovePlayerFromInstanceSelected(nInstanceIndex, tbPlayer, bNotify, bClearPlayer, bNotified)
	local bFind = 0;
	local tbWaitQueue = self.tbSelected[nInstanceIndex];

	repeat
		bFind = 0;
		for szType, tbPlayers in pairs(tbWaitQueue) do
			for key, tbPlayer2 in pairs(tbPlayers) do
				if (tbPlayer2.dwId == tbPlayer.dwId) then
					bFind = 1;
					if (szType == "Team") then
						tbWaitQueue["Team"] = nil;
						if (bClearPlayer == 1) then
							self:ClearEnteredTeam(tbPlayers);
						end
						if (bNotify == 1) then
							if (bNotified == 0) then
								bNotified = 1;
								GlobalExecute({"PVEMatch:NotifyTeamLeaveQueue_GS", tbPlayers, nInstanceIndex, 1});
							else
								GlobalExecute({"PVEMatch:NotifyTeamLeaveQueue_GS", tbPlayers, nInstanceIndex, 0});
							end
						end
					else
						table.remove(tbPlayers, key);
						if (bClearPlayer == 1) then
							self:ClearEnteredPlayer({dwId = tbPlayer2.dwId});
						end
						if (bNotify == 1) then
							if (bNotified == 0) then
								bNotified = 1;
								GlobalExecute({"PVEMatch:NotifyPlayerLeaveQueue_GS", tbPlayer2, nInstanceIndex, 1});
							else
								GlobalExecute({"PVEMatch:NotifyPlayerLeaveQueue_GS", tbPlayer2, nInstanceIndex, 0});
							end
						end
					end
				end
			end
		end
	until bFind == 0

	return bNotified;
end

-- �ڵȴ��������Ƴ����
function PVEMatch:RemoveTeamFromWaitQueue(tbTeam)

	for nInstanceIndex, tbWaitQueue in pairs(self.tbInstanceWaitQueue) do

		local bFind = 0;
		repeat
			bFind = 0;
			for key, tbTeam in pairs(tbWaitQueue["Team"]) do
				if (tbTeam == tbTeam) then
					bFind = 1;
					table.remove(tbWaitQueue["Team"], key);
				end
			end
		until bFind == 0;

	end
end

-- �ж�ƥ�������Ƿ�ͬ����븱������Ҫȫ��ͬ��
function PVEMatch:IsAllAcceptedEnterInstance(nInstanceIndex)
	local tbs = self.tbSelected[nInstanceIndex];
	local nNum = 0;
	if type(tbs) == "table" then
		for _, tbPlayers in pairs(tbs) do
			for _, tbPlayer in pairs(tbPlayers) do
				if tbPlayer.nAccept == 1 then
					nNum = nNum + 1;
				end
			end
		end
	end
	
	if nNum >= self.MAX_TEAM_NUM then
		return 1;
	else
		return 0;
	end
end

-- �ж��Ƿ�ƥ����ɣ�ֻҪƥ����5�˾Ϳ���
function PVEMatch:IsMatchFinished(nInstanceIndex)
	local tbs = self.tbSelected[nInstanceIndex];
	local nSelNum = 0;
	if type(tbs) == "table" then
		for _, tbPlayers in pairs(tbs) do
			for _, tbPlayer in pairs(tbPlayers) do
				nSelNum = nSelNum + 1;
			end
		end
	end
	
	if nSelNum >= self.MAX_TEAM_NUM then 
		return 1;
	else
		return 0;
	end
end

-- ��¼����Ƿ���븱��ƥ�����
function PVEMatch:RecordEnteredPlayer(tbPlayer)
	self.tbEnteredPlayers[tbPlayer.dwId] = 1;
end

-- �����Ҽ�¼
function PVEMatch:ClearEnteredPlayer(tbPlayer)
	self.tbEnteredPlayers[tbPlayer.dwId] = nil;
end

function PVEMatch:IsPlayerEntered(tbPlayer)
	if self.tbEnteredPlayers[tbPlayer.dwId] == 1 then
		return 1;
	end
	
	return 0;
end

function PVEMatch:IsTeamEntered(tbTeam)
	for _, tbPlayer in pairs(tbTeam) do
		if self.tbEnteredPlayers[tbPlayer.dwId] ~= nil then
			return 1;
		end
	end
	
	return 0;
end

function PVEMatch:ClearEnteredTeam(tbTeam)
	for _, tbPlayer in pairs(tbTeam) do
		self.tbEnteredPlayers[tbPlayer.dwId] = nil;
	end
end

function PVEMatch:RecordEnteredTeam(tbTeam)
	for _, tbPlayer in pairs(tbTeam) do
		self.tbEnteredPlayers[tbPlayer.dwId] = 1;
	end
end

function PVEMatch:GetInstanceIndexByPlayerIdFromSelected(nPlayerId)
	for nInstanceIndex, tbQueue in pairs(self.tbSelected) do
		for _, tbPlayers in pairs(tbQueue) do
			for _, tbPlayer in pairs(tbPlayers) do
				if tbPlayer.dwId == nPlayerId then
					return nInstanceIndex;
				end
			end
		end
	end
end

function PVEMatch:EnterInstance(tbPlayers, nInstanceIndex)
	-- ���ս��ID
	local tbPlayerIds = {};
	for _, tbPlayer in pairs(tbPlayers) do
		table.insert(tbPlayerIds, tbPlayer.dwId);
	end
	local nSysTeamId = CreateSystemTeam(unpack(tbPlayerIds));
	GlobalExecute({"PVEMatch:DoEnterInstance_GS", tbPlayers, nInstanceIndex});
end

function PVEMatch:TestEnterMission(nMember1, nMember2, nMember3, nInstanceIndex)
	local tbPlayerIds = {};
	
	if nMember1 ~= 0 then
		table.insert(tbPlayerIds, nMember1)
	end
	
	if nMember2 ~= 0 then
		table.insert(tbPlayerIds, nMember2)
	end
	
	if nMember3 ~= 0 then
		table.insert(tbPlayerIds, nMember3)
	end

	local nSysTeamId = CreateSystemTeam(unpack(tbPlayerIds));
	GlobalExecute({"PVEMatch:DoEnterMultiInstance_GS", tbPlayerIds, nInstanceIndex});
end

function PVEMatch:TestEnterMissionRemote(nMember1, nMember2, nMember3, nInstanceIndex)
	GlobalExecute({"PVEMatch:DoEnterMultiInstanceRemote_GS", nMember1, nInstanceIndex});
end

function PVEMatch:BroadcastOverallTeamMsg(nMapId, dwLeaderCombinedIdx, nRequireFightscore, szCreaterName)
	GlobalExecute({"PVEMatch:DoBroadcastOverallTeamMsg_GS", nMapId, dwLeaderCombinedIdx, nRequireFightscore, szCreaterName});
end

-- event
------------------------------------------------------------------
-- ��¼�¼�
function PVEMatch:PlayerLogin_GC(nPlayerId)
	self:PlayerLeave(nPlayerId);
end

-- �˳��¼�
function PVEMatch:PlayerLogout_GC(nPlayerId)
	self:PlayerLeave(nPlayerId);
end

-- ����뿪���е�ͼ������ͼ�¼�
function PVEMatch:PlayerLeaveCity_GC(nPlayerId)
	self:PlayerLeave(nPlayerId);
end

-- ����뿪��ӣ���Ϊ�������鶼�뿪����
function PVEMatch:PlayerLeaveTeam_GC(nPlayerId)
	self:PlayerLeave(nPlayerId);
end

-- ��ҽ������
function PVEMatch:PlayerEnterTeam_GC(nPlayerId)
	self:PlayerLeave(nPlayerId);
end

function PVEMatch:OnMatchFinish(nInstanceIndex)
	if nInstanceIndex ~= nil then
		local tbPlayers = {};
		for _, tbPlayers2 in pairs(self.tbSelected[nInstanceIndex]) do
			for _, tbPlayer in pairs(tbPlayers2) do
				table.insert(tbPlayers, tbPlayer);
			end
		end

		for _, tbPlayer in pairs(tbPlayers) do
			self:RemovePlayerFromSelected(tbPlayer, 0, 0, nInstanceIndex);
			self:RemovePlayerFromWaitQueue(tbPlayer);
		end

		-- ����һ����ʱ�����޶�ʱ����û��ͬ����븱���ؿ�����Ϊ�ܾ����븱���ؿ�
		local ntimerId = Timer:Register(self.ENTER_TIME_OUT * Env.GAME_FPS, self.OnEntertimeOut, self, nInstanceIndex);
		self.tbMatchFinishedTimerID[nInstanceIndex] = ntimerId;
		
		GlobalExecute({"PVEMatch:NotifyMatchFinished_GS", tbPlayers, nInstanceIndex, self.ENTER_TIME_OUT});
	end
end

function PVEMatch:OnEntertimeOut(nInstanceIndex)
	-- ��ʱʱ�䵽�ˣ�û��ѡ��ͬ����븱���ؿ���ҪT������������Ҫ�յ�֪ͨ
	if (self.tbMatchFinishedTimerID[nInstanceIndex] == nil 
		or self.tbMatchFinishedTimerID[nInstanceIndex] == 0)
	then
		return 0;
	end

	self.tbMatchFinishedTimerID[nInstanceIndex] = 0;
	local tbRemovedPlayers = {};
	local tbRemainPlayers = {};
	local tbTimeOutPlayers = {};
	local tbSelected = self.tbSelected[nInstanceIndex];

	local bFind = 0
	repeat
		bFind = 0;

		for szType, tbPlayers in pairs(tbSelected) do
			if (szType == "Team") then
				local bFindInTeam = 0;
				for key, tbPlayer in pairs(tbPlayers) do
					if (tbPlayer.nAccept ~= 1) then
						bFind = 1;
						bFindInTeam = 1;
						table.insert(tbTimeOutPlayers, tbPlayer);
					end
				end
				if (bFindInTeam == 1) then
					for _, tbPlayer in pairs(tbPlayers) do
						table.insert(tbRemovedPlayers, tbPlayer);
					end
					self:ClearEnteredTeam(tbPlayers);
					tbSelected["Team"] = nil;
				end
			else
				for key, tbPlayer in pairs(tbPlayers) do
					if (tbPlayer.nAccept ~= 1) then
						bFind = 1;
						table.insert(tbRemovedPlayers, tbPlayer);
						table.insert(tbTimeOutPlayers, tbPlayer);
						self:ClearEnteredPlayer(tbPlayer);
						table.remove(tbPlayers, key);
					end
				end
			end
		end
	until bFind == 0

	for szType, tbPlayers in pairs(tbSelected) do
		for _, tbPlayer in pairs(tbPlayers) do
			tbPlayer.nAccept = 0;
			table.insert(tbRemainPlayers, tbPlayer);
		end
	end

	self.tbMatchFinishedInstanceIndex[nInstanceIndex] = 0;

	-- ֪ͨ��ҳ�ʱ
	if (#tbRemovedPlayers > 0) then
		GlobalExecute({"PVEMatch:NotifyPlayerEnterTimeOut_GS", tbRemovedPlayers, tbTimeOutPlayers, nInstanceIndex});
		GlobalExecute({"PVEMatch:NotifyTeamLeaveQueue_GS", tbRemovedPlayers, nInstanceIndex, 1});
	end

	if (#tbRemainPlayers > 0) then
		GlobalExecute({"PVEMatch:NotifyPlayerEnterTimeOut_GS", tbRemainPlayers, tbTimeOutPlayers, nInstanceIndex});
	end

	return 0; -- �������ö�ʱ���Զ����
end

function PVEMatch:OnPlayerMatchSuccess(tbPlayer, nInstanceIndex)
	GlobalExecute({"PVEMatch:NotifyPlayerMatchSuccess_GS", tbPlayer, nInstanceIndex});
end

function PVEMatch:OnTeamMatchSuccess(tbTeam, nInstanceIndex)
	GlobalExecute({"PVEMatch:NotifyTeamMatchSuccess_GS", tbTeam, nInstanceIndex});
end

-- main logic
--------------------------------------------------------------------------------
function PVEMatch:StartMatch()
	local tbInstanceIndex = {};
	for nInstanceIndex, tbWaitQueue in pairs(self.tbInstanceWaitQueue) do
		if type(self.tbSelected[nInstanceIndex]) ~= "table" then
			self.tbSelected[nInstanceIndex] = {};
		end
		
		table.insert(tbInstanceIndex, nInstanceIndex);
	end
	
	-- ���������ƥ��˳��
	if #tbInstanceIndex > 1 then
		for i = 1, #tbInstanceIndex - 1 do
			local nRandNum = KUnify.MathRandom(i, #tbInstanceIndex);
			local tmp = tbInstanceIndex[nRandNum];
			tbInstanceIndex[nRandNum] = tbInstanceIndex[i];
			tbInstanceIndex[i] = tmp;
		end
	end
	
	for _, nInstanceIndex in pairs(tbInstanceIndex) do	
		-- �Ƿ�ƥ��ɹ���������ƥ�䵽5��
		if self.tbMatchFinishedInstanceIndex[nInstanceIndex] == 0 or self.tbMatchFinishedInstanceIndex[nInstanceIndex] == nil then
			self:MatchPlayer(nInstanceIndex);
			if self:IsMatchFinished(nInstanceIndex) == 1 then
				if self.tbMatchFinishedInstanceIndex[nInstanceIndex] ~= 1 then
					self.tbMatchFinishedInstanceIndex[nInstanceIndex] = 1;
					self:OnMatchFinish(nInstanceIndex);
				end
			else
				self.tbMatchFinishedInstanceIndex[nInstanceIndex] = 0;
			end
		end
	end
end

-- ����ƥ�䣬ÿ������ѡһ��
-- ������򣺵�һ�ֽ�������ƥ�䣬����ѡ����飬��ʵѡ���ˣ�ѡ����ٲ��ҵ��˽�������ƥ�䡣
-- �ڶ����Ժ�����з�����ƥ�䣬������������ģ����ѡ�����⣬�ȴ��б�Ϊ�գ����ƥ��һ�����������
-- ����ƥ�����1̹��1����3�����Ȼ�������ĸ��ǲ�ͬ���ɣ�����һ����ͬ���ɵ���ְͬҵ
function PVEMatch:MatchPlayer(nInstanceIndex)
	local s = self.tbSelected[nInstanceIndex];
	local q = self.tbInstanceWaitQueue[nInstanceIndex]; 
	
	s["Tank"] = s["Tank"] or {};
	s["Help"] = s["Help"] or {};
	s["Dps"] = s["Dps"] or {};
	s["Team"] = s["Team"] or {};
	q["Tank"] = q["Tank"] or {};
	q["Help"] = q["Help"] or {};
	q["Dps"] = q["Dps"] or {};
	q["Team"] = q["Team"] or {};
	
	-- �Ƴ������
	for k, tbTeam in pairs(q["Team"]) do
		if type(tbTeam) == "table" and #tbTeam == 0 then
			table.remove(q["Team"], k);
		end
	end
	
	-- �ж��Ƿ��ǵ�һ�֣�����ѡ�����
	if #s["Tank"] == 0 and #s["Help"] == 0 and #s["Dps"] == 0 and #s["Team"] == 0 then
		if #q["Team"] > 0 then -- ������ڵȴ���������ѡ�����
			local tbTeam = q["Team"][1];
			s["Team"] = tbTeam;
			table.remove(q["Team"], 1);
			-- �������Ӵ����еȴ��б����Ƴ�
			-- self:RemoveTeamFromWaitQueue(tbTeam);
			-- ֪ͨ��ӳ�Աƥ��ɹ��������Ƿ�ͬ����븱��
			self:OnTeamMatchSuccess(s["Team"], nInstanceIndex);
		end
	end

	if (#s["Team"] == nil) then
		s["Team"] = {};
	end
	
	if #s["Team"] < self.MAX_TEAM_NUM then
		-- ��������ƥ�䣬1T1N3D����ͬ���ɲ�ְͬҵ������һ��ѡ����5����Ҳ����һ��ֻѡ����5������ѡ��ı�����������
		self:PerfectMatch(nInstanceIndex);
		
		-- �ǵ�һ������з�����ƥ��
		-- ������ƥ���������ѡ��һ����������ң����ȼ�˳�򣺶���ְ��TND�����ɣ�ְҵ
		-- �ȳ���ѡְ�𻥳⣬����ѡ���ɻ��⣬������ѡְҵ���⣬�����򰴽���ʱ��ѡ��һ��
		self:LessMatch(nInstanceIndex);
	end
end

-- ֻ��������ƥ��
-- ��T��T�ȴ��б�Ϊ��������ѡ1T����N��N�ȴ��б�Ϊ��������ѡ1N����D��D��������3��D�ȴ��б�Ϊ�գ�������ѡ1D��������D�ĸ�������ѡ3D
function PVEMatch:PerfectMatch(nInstanceIndex)
	local q = self.tbInstanceWaitQueue[nInstanceIndex];
	local s = self.tbSelected[nInstanceIndex];
	local k = nil;

	-- ������ƥ��T����ѡ�������T�Ҹ���T�ȴ��б�Ϊ�գ����T�ȴ��б����ų��Ѿ��е����ɺ�ְҵ��ѡ�������ǰ��һ��	
	if #s["Tank"] + self:GetTeamTypeNum(s["Team"], "Tank") == 0 and #q["Tank"] > 0 then
		k = self:_PerfectMatchSingle(s, q["Tank"]);
		if k > 0 then
			local tbPlayer = q["Tank"][k];
			-- self:RemovePlayerFromWaitQueue(q["Tank"][k]);
			table.remove(q["Tank"], k);
			table.insert(s["Tank"], tbPlayer);
			self:OnPlayerMatchSuccess(tbPlayer, nInstanceIndex);
		end
	end

	-- ������ƥ��N����ѡ�����N�Ҹ���N�ȴ��б�Ϊ�գ����N�ȴ��б����ų����е����ɺ�ְҵ��ѡ�������ǰ��һ��
	if #s["Help"] + self:GetTeamTypeNum(s["Team"], "Help") == 0 and #q["Help"] > 0 then
		k = self:_PerfectMatchSingle(s, q["Help"]);
		if k > 0 then
			local tbPlayer = q["Help"][k];
			-- self:RemovePlayerFromWaitQueue(q["Help"][k]);
			table.remove(q["Help"], k);
			table.insert(s["Help"], tbPlayer);
			self:OnPlayerMatchSuccess(tbPlayer, nInstanceIndex);
		end
	end

	-- �����ƥ��D����ѡ�����D����3���б�Ϊ�գ����D�ȴ��б����ų����е����ɺ�ְҵ��ѡ�������ǰ��һ��
	-- ����Ҫѡ3��D���Գ���ѡ3��
	while #s["Dps"] + self:GetTeamTypeNum(s["Team"], "Dps") < 3 and #q["Dps"] > 0 do
		k = self:_PerfectMatchSingle(s, q["Dps"]);
		if k > 0 then
			local tbPlayer = q["Dps"][k];
			-- self:RemovePlayerFromWaitQueue(q["Dps"][k]);
			table.remove(q["Dps"], k);
			table.insert(s["Dps"], tbPlayer);
			self:OnPlayerMatchSuccess(tbPlayer, nInstanceIndex);
		else
			break; -- ������D�����˳�
		end
	end

	return s;
end

-- ���Դӵ��˵ȴ�������ѡ������ƥ������
-- ���У��򷵻ض��е���������������0��������û���򷵻�-1
function PVEMatch:_PerfectMatchSingle(tbSelected, tbWaitQueue)
	local nSelectedNum = 0;
	local nNewMatchKey = -1;
	-- �ҳ��Ѿ��е�����
	local tbHasFaction = {};
	for _, tbPlayers in pairs(tbSelected) do
		for _, tbPlayer in pairs(tbPlayers) do
			tbHasFaction[tbPlayer.nFaction] = 1;
			nSelectedNum = nSelectedNum + 1;
		end
	end

	if nSelectedNum + 1 <= self.MAX_TEAM_NUM then
		-- �ų���ͬ������
		for i = 1, #tbWaitQueue do
			if tbHasFaction[tbWaitQueue[i].nFaction] == nil then
				nNewMatchKey = i;
				break;
			end
		end
	end
	
	return nNewMatchKey;
end

-- ������ƥ�䣬�ȴ��б�Ϊ��ʱѡ����ֻѡ��һ����ң�����˳��Ϊ������ְ�𻥳�TND�����ɻ��⣬ְҵ���ͻ���
function PVEMatch:LessMatch(nInstanceIndex)
	-- print("LessMatch");
	-- ��T��T�б�������ѡһ��T��������ƥ����������ѡһ��
	local q = self.tbInstanceWaitQueue[nInstanceIndex];
	local s = self.tbSelected[nInstanceIndex];
	local k = -1;
	
	-- ��T��T�б�������ѡһ��T��������ƥ��������ѡһ��
	if k <= 0 then
		if #s["Tank"] + self:GetTeamTypeNum(s["Team"], "Tank") == 0 and #q["Tank"] > 0 then
			k = self:_LessMatchSingle(s, q["Tank"]);
			if k > 0 then
				local tbPlayer = q["Tank"][k];
				-- self:RemovePlayerFromWaitQueue(q["Tank"][k]);
				table.remove(q["Tank"], k);
				table.insert(s["Tank"], tbPlayer);
				self:OnPlayerMatchSuccess(tbPlayer, nInstanceIndex);
			end
		end
	end
	
	-- ���������б�������ѡһ���̣�������ƥ����������ѡһ��
	if k <= 0 then
		if #s["Help"] + self:GetTeamTypeNum(s["Team"], "Help") == 0 and #q["Help"] > 0 then
			k = self:_LessMatchSingle(s, q["Help"]);
			if k > 0 then
				local tbPlayer = q["Help"][k];
				-- self:RemovePlayerFromWaitQueue(q["Help"][k]);
				table.remove(q["Help"], k);
				table.insert(s["Help"], tbPlayer);
				self:OnPlayerMatchSuccess(tbPlayer, nInstanceIndex);
			end
		end
	end
	
	-- Dps��������3�����������ƥ����������ѡһ��
	if k <= 0 then
		if #s["Dps"] + self:GetTeamTypeNum(s["Team"], "Dps") < 3 and #q["Dps"] > 0 then
			k = self:_LessMatchSingle(s, q["Dps"]);
			if k > 0 then
				local tbPlayer = q["Dps"][k];
				-- self:RemovePlayerFromWaitQueue(q["Dps"][k]);
				table.remove(q["Dps"], k);
				table.insert(s["Dps"], tbPlayer);
				self:OnPlayerMatchSuccess(tbPlayer, nInstanceIndex);
			end
		end
	end
	
	-- ���ʵ���Ҳ����ˣ����ҵȴ��б������Ƚ����һ��
	if k <= 0 then
		local f = {};
		if #q["Tank"] > 0 then
			f.p = q["Tank"][1];
			f.t = 1;
		end
		
		if #q["Help"] > 0 then
			if f.p == nil then
				f.p = q["Help"][1];
				f.t = 2;
			elseif f.p.time > q["Help"][1].time then
				f.p = q["Help"][1];
				f.t = 2;
			end
		end
		
		if #q["Dps"] > 0 then
			if f.p == nil then
				f.p = q["Dps"][1];
				f.t = 3;
			elseif f.p.time > q["Dps"][1].time then
				f.p = q["Dps"][1];
				f.t = 3;
			end
		end
		
		if f.p ~= nil then
			if f.t == 1 then
				-- self:RemovePlayerFromWaitQueue(f.p);
				table.remove(q["Tank"], 1);
				table.insert(s["Tank"], f.p);
				self:OnPlayerMatchSuccess(f.p, nInstanceIndex);
			elseif f.t == 2 then
				-- self:RemovePlayerFromWaitQueue(f.p);
				table.remove(q["Help"], 1);
				table.insert(s["Help"], f.p);
				self:OnPlayerMatchSuccess(f.p, nInstanceIndex);
			elseif f.t == 3 then
				-- self:RemovePlayerFromWaitQueue(f.p);
				table.remove(q["Dps"], 1);
				table.insert(s["Dps"], f.p);
				self:OnPlayerMatchSuccess(f.p, nInstanceIndex);
			end
		end
	end
end

-- �ȳ����ڲ�ͬ������ѡ��ѡ���������ԴӲ�ְͬҵ��ѡ����ѡ��������ѡ������ŵ�һ��
-- �����򷵻ش���0��������������û���򷵻�-1�����Ƕ���Ϊ�գ���������ѡһ��
function PVEMatch:_LessMatchSingle(tbSelected, tbWaitQueue)
	-- �����Ҳ�ͬ���ɵ�
	local nNewMatchKey = -1;
	local tbHasFaction = {};
	for _, tbPlayers in pairs(tbSelected) do
		for _, tbPlayer in pairs(tbPlayers) do
			tbHasFaction[tbPlayer.nFaction] = 1;
		end
	end

	for i = 1, #tbWaitQueue do
		if tbHasFaction[tbWaitQueue[i].nFaction] == nil then
			nNewMatchKey = i;
			break;
		end
	end
	
	-- �����Ҳ�ְͬҵ�����ܻ�ͬ����
	if nNewMatchKey < 0 then
		-- �ҳ����е��츳·��
		local tbHasFactionRoute = {};
		for _, tbPlayers in pairs(tbSelected) do
			for _, tbPlayer in pairs(tbPlayers) do
				tbHasFactionRoute[tbPlayer.nFaction] = tbHasFactionRoute[tbPlayer.nFaction] or {};
				tbHasFactionRoute[tbPlayer.nFaction][tbPlayer.nRoute] = 1;
			end
		end

		for i = 1, #tbWaitQueue do
			local nFaction = tbWaitQueue[i].nFaction;
			local nRoute = tbWaitQueue[i].nRoute;
			if tbHasFactionRoute[nFaction] == nil or tbHasFactionRoute[nFaction][nRoute] == nil then
				nNewMatchKey = i;
				break;
			end
		end
	end
	
	-- ʵ���Ҳ������ˣ���ȡ��ŵ�һ��
	if nNewMatchKey < 0 and #tbWaitQueue > 0 then
		nNewMatchKey = 1;
	end
	
	return nNewMatchKey;
end

-- ������ʱ����ÿ��ָ��ʱ�����ƥ��һ��
function PVEMatch:BeginTimer()
	if type(self.nRegisterTimerID) == "nil" then
		self.nRegisterTimerID = Timer:Register(self.MATCH_INTERVAL, self.StartMatch, self);
	end
end

function PVEMatch:EndTimer()
	if type(self.nRegisterTimerID) == "nil" then
		Timer:Close(self.nRegisterTimerID);
		self.nRegisterTimerID = nil;
	end
end

-- ��ȡ"Dps" "Help" "Tank"��Ա����
function PVEMatch:GetTeamTypeNum(tbTeam, szType)
	local num = 0;
	if type(tbTeam) == "table" and #tbTeam > 0 then
		for _, varPlayer in pairs(tbTeam) do
			if varPlayer.szType == szType then
				num = num + 1;
			end
		end
	end
	return num;
end

-- ?gc PVEMatch:SetMaxTeamNum(2);
function PVEMatch:SetMaxTeamNum(nNum)
	self.MAX_TEAM_NUM = tonumber(nNum) or 1;
	print("PVEMatch:SetMaxTeamNum set number : " .. self.MAX_TEAM_NUM);
end

PVEMatch:BeginTimer();

