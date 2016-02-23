Include("script/mission/activity/activitystep.lua")
Include("script/mission/activity/activitydef.lua")

Activity.MENPAIJINGJI_SAICHANG = Lib:NewClass(Activity.ActivityStep);

Activity.ACTSTEP_FACTORY[Activity.STEP_TYPE.MENPAIJINGJI_SAICHANG] = Activity.MENPAIJINGJI_SAICHANG -- ע�ᵽ�����

local MENPAIJINGJI_SAICHANG = Activity.MENPAIJINGJI_SAICHANG
local tbMPJJAwardScore = Activity.tbMPJJAwardScore or {};

function MENPAIJINGJI_SAICHANG:OnInit()
	self.tbPlayerDamage = {};
	self.tbPlayerName = {};
	self.nWinnerId = -1;
	self.bAward = 0;	--�Ƿ��ѷ�����
end

function MENPAIJINGJI_SAICHANG:OnJoinPlayer(nPlayerId, nGroup)
	local pPlayer = KGameBase.GetPlayerById(nPlayerId)
	Player:SetTempReviveFunc(pPlayer, {"Activity.MENPAIJINGJI_SAICHANG:OnDeath", pPlayer});
    if pPlayer.IsDead() == 1 then  -- �����ɫ�������Զ�����		  
		  KCharacter.Revive(pPlayer, 1000, 1000);
		else   --������̨�����Զ���Ѫ
		  pPlayer.SetCurrentLife(pPlayer.GetMaxLife());
	  end
	self.tbPlayerDamage[nPlayerId] = 0;
	--self:SetPlayerActivityInfo(nPlayerId, nil, string.format("�㵱ǰ�˺�: %d", self.tbPlayerDamage[nPlayerId]))
end

function MENPAIJINGJI_SAICHANG:OnEnterActivityScene(nPlayerId)
	local pPlayer = KGameBase.GetPlayerById(nPlayerId)
	if not pPlayer then
		return;
	end
	
	Player:SetTempReviveFunc(pPlayer, {"Activity.MENPAIJINGJI_SAICHANG:OnDeath", pPlayer});
	KCharacter.Revive(pPlayer, 1000, 1000);
	self.tbPlayerDamage[nPlayerId] = 0;
end

function MENPAIJINGJI_SAICHANG:SetGameProgress(nGameProgress, nPanelIndex)
	self.nGameProgress = nGameProgress
	self.nPanelIndex = nPanelIndex
	for index, tbPlayer in pairs(self.tbPlayers) do
		local pPlayer = KGameBase.GetPlayerById(tbPlayer.nPlayerId);
		self.tbPlayerName[pPlayer.dwId] = pPlayer.szName;
		pPlayer.SetFactionBattleRank(nGameProgress)
    end
	
	local numPlayers = #self.tbPlayers;
    if numPlayers == 1 then
		self:OnlyOnePlayer();
	elseif numPlayers == 2 then
		local szName1 = "";
		local szName2 = "";
		for index, tbPlayer in pairs(self.tbPlayers) do
			local pPlayer = KGameBase.GetPlayerById(tbPlayer.nPlayerId)
			self:ShowEffect(pPlayer, 1);	--��ʼ��Ч
			if index == 1 then
				szName1 = szName1..pPlayer.szName;
			else
				szName2 = szName2..pPlayer.szName;
			end
		end
		
			if nGameProgress == 2 then
			    self:ShowNoticeMsg(string.format(Lang.mission.str68[Lang.Idx], szName1, szName2));
			end
    end
    
    self:SetKnockoutMatchPanel();
end

--һ��Ϊ�յĴ���
function MENPAIJINGJI_SAICHANG:OnlyOnePlayer()
	if  self.IsOpen ~= 0 and #self.tbPlayers == 1 then
		for _,tbPlayer in pairs(self.tbPlayers) do
			local pPlayer = KGameBase.GetPlayerById(tbPlayer.nPlayerId);
			if self.nGameProgress == 2 then
				self:ShowEffect(pPlayer, 4);	--�ɹ���Ч
			else
				self:ShowEffect(pPlayer, 2);	--������Ч
			end
			KActivity.SetLastMPJJRank(pPlayer, self.nGameProgress / 2);
			self.nWinnerId = tbPlayer.nPlayerId;
			--����16ǿ�������
			--[[local szName = pPlayer.szName..",";
			for nPlayerId, strName in pairs(self.tbPlayerName) do
				if nPlayerId ~= self.nWinnerId then
					szName = szName..strName;
					break;
				end
			end--]]
			self:SetKnockoutMatchPanel(self.nWinnerId);
			
			if self.nGameProgress == 2 then
			   self:JoinStep(10,18,0,0,0); -- ���������˲�˲��
			else
			   self:JoinStep(10,18,0,0);
			end
			--������
			self:SendAward();
		end
	end
end

function MENPAIJINGJI_SAICHANG:OnPlayerDamage(nCasterId, nInjuredId, nDamage)
    self.tbPlayerDamage[nCasterId] = self.tbPlayerDamage[nCasterId] + nDamage;
    --self:SetPlayerActivityInfo(nCasterId, nil, string.format("�㵱ǰ�˺�: %d", self.tbPlayerDamage[nCasterId]), "")
end

function MENPAIJINGJI_SAICHANG:OnKickPlayer(nPlayerId)
	self:SetPlayerActivityInfo(nPlayerId, "", "");
	self.tbPlayerDamage[nPlayerId] = nil;
	
	local pPlayer = KGameBase.GetPlayerById(nPlayerId)
  if pPlayer.IsDead() == 1 then  -- �����ɫ�������Զ�����		  
	  KCharacter.Revive(pPlayer, 1000, 1000);
	else   --������̨�����Զ���Ѫ
	  pPlayer.SetCurrentLife(pPlayer.GetMaxLife());
  end
end

function MENPAIJINGJI_SAICHANG:OnLeaveGame(nCharacterId)
	--[[local pPlayer = KGameBase.GetPlayerById(nCharacterId);
	if pPlayer then
		pPlayer.CallClientScript({"QClientScript.Activity:HideKnockoutMatchPanel"});	--�ر�ս����˫16ǿ���
	end--]]
	self:OnlyOnePlayer();
end

function MENPAIJINGJI_SAICHANG:OnPlayerKill(nKillerCharId, nDeathCharId)
    local pKillerPlayer = KGameBase.GetPlayerById(nKillerCharId);
	local pDeathPlayer = KGameBase.GetPlayerById(nDeathCharId);
    self.nWinnerId = nKillerCharId;
	KActivity.SetLastMPJJRank(pDeathPlayer, self.nGameProgress);
	KActivity.SetLastMPJJRank(pKillerPlayer, self.nGameProgress / 2);
	self:SendAward();
	if self.nGameProgress == 2 then
		self:ShowEffect(pKillerPlayer, 4);	--�ɹ���Ч
	else
		self:ShowEffect(pKillerPlayer, 2);	--������Ч
	end
	self:ShowEffect(pDeathPlayer, 3);	--ʧ����Ч
	--����16ǿ�������
	--local szName = pKillerPlayer.szName..","..pDeathPlayer.szName;
	self:SetKnockoutMatchPanel(self.nWinnerId);
	
  if self.nGameProgress == 2 then
		self:JoinStep(10,18,0,0,0); -- ���������˲�˲��
  end
end

function MENPAIJINGJI_SAICHANG:OnEndStep()
	if self.nWinnerId == -1 then 
		if #self.tbPlayers == 2 then 
			local nPlayer1Id = self.tbPlayers[1].nPlayerId 
			local nPlayer2Id = self.tbPlayers[2].nPlayerId 
			if self.tbPlayerDamage[nPlayer2Id] == 0 and self.tbPlayerDamage[nPlayer1Id] == 0 then
				-- ������������ͣ����һ��ʤ����
				local nIndex = KUnify.MathRandom(1, 2)
				self.nWinnerId = self.tbPlayers[nIndex].nPlayerId
			else 	
				--�˺�ֵ�ߵ�Ϊʤ����
				if self.tbPlayerDamage[nPlayer2Id] > self.tbPlayerDamage[nPlayer1Id] then
					self.nWinnerId = nPlayer2Id
				else
					self.nWinnerId = nPlayer1Id
				end
			end
		elseif #self.tbPlayers == 1 then
			self.nWinnerId = self.tbPlayers[1].nPlayerId
		end
    end
	
    --δ��ǰ������
	if self.bAward ~= 1 then
		for _, tbPlayer in pairs(self.tbPlayers) do
			local pPlayer = KGameBase.GetPlayerById(tbPlayer.nPlayerId)
			if tbPlayer.nPlayerId == self.nWinnerId then
				if self.nGameProgress == 2 then
					self:ShowEffect(pPlayer, 4);	--�ɹ���Ч
				else
					self:ShowEffect(pPlayer, 2);	--������Ч
				end
			else
				self:ShowEffect(pPlayer, 3);	--ʧ����Ч
			end
			
		end
	end
	
    if self.nWinnerId ~= -1 and self.bAward ~= 1 then
		if Activity.tbPlayerProgress[self.nWinnerId] and Activity.tbPlayerProgress[self.nWinnerId].nActivityIndex == self.nActivityIndex then
			self:AddWinner(self.nWinnerId, 0);
		end
        local pPlayer = KGameBase.GetPlayerById(self.nWinnerId);
		if pPlayer then
			KActivity.SetLastMPJJRank(pPlayer, self.nGameProgress / 2);
			--����16ǿ�������
			--[[local szName = pPlayer.szName..",";
			for nPlayerId, strName in pairs(self.tbPlayerName) do
				if nPlayerId ~= self.nWinnerId then
					szName = szName..strName;
					break;
				end
			end--]]
			self:SetKnockoutMatchPanel(self.nWinnerId);
		end
		self:SendAward();
	end
	
	if self.nGameProgress == 2 then
		self:JoinStep(10,18,0,0,0); -- ���������˲�˲��
  end
  
	--��������
	self.tbPlayerDamage = {};
	self.tbPlayerName = {};
	self.nWinnerId = -1;
	self.bAward = 0;
end

function MENPAIJINGJI_SAICHANG:OnDeath(pPlayer)
	
end

--������
function MENPAIJINGJI_SAICHANG:SendAward()
	if self.IsOpen ~= 0 and self.nGameProgress == 2 and self.bAward ~= 1 then
		local pKillerPlayer = KGameBase.GetPlayerById(self.nWinnerId)
		if pKillerPlayer then
			self:ShowNoticeMsg(string.format(Lang.mission.str69[Lang.Idx], pKillerPlayer.szName));
			Activity.dwMPJJChampionId = pKillerPlayer.dwId;
		end

		local tbPlayers = KGameBase.GetAllPlayers();
		for _, pPlayer in pairs(tbPlayers) do
			local dwLastMPJJRank = KActivity.GetLastMPJJRank(pPlayer);
			if dwLastMPJJRank ~= 0 then
				KAward.AddPlayerAward(pPlayer, "MenPaiJingJi", dwLastMPJJRank);
				self:GivePlayerTitle(pPlayer, dwLastMPJJRank); --������������ƺ�
				if dwLastMPJJRank == 1 then
					pPlayer.SysMsg(Lang.mission.str70[Lang.Idx]);
				elseif dwLastMPJJRank == 2 then
				  pPlayer.SysMsg(Lang.mission.str71[Lang.Idx]);
				elseif dwLastMPJJRank == 4 then
				  pPlayer.SysMsg(Lang.mission.str72[Lang.Idx]);
				elseif dwLastMPJJRank == 8 then
				  pPlayer.SysMsg(Lang.mission.str73[Lang.Idx]);
				elseif dwLastMPJJRank == 16 then
				  pPlayer.SysMsg(Lang.mission.str74[Lang.Idx]);
				else
				  pPlayer.SysMsg(Lang.mission.str75[Lang.Idx]);
				end
				if tbMPJJAwardScore[dwLastMPJJRank] then
					pPlayer.pPlayerPurse.AddMoney(Purse.EM_MONEY_MPJJ_SCORE, tbMPJJAwardScore[dwLastMPJJRank]);
					KRank.ModifyRankValue(pPlayer.dwId, Rank.MPJJ_RANK, pPlayer.pPlayerPurse.GetMoney(Purse.EM_MONEY_MPJJ_SCORE));
				end
				KActivity.SetLastMPJJRank(pPlayer, 0);
			end
		end
		self.bAward = 1;
	end
end

function MENPAIJINGJI_SAICHANG:GivePlayerTitle(pPlayer, nRank)
    if nRank == 1 then
       Title:AddTitleToCharacter(pPlayer, 17, 1, 1)
    elseif nRank == 2 then
       Title:AddTitleToCharacter(pPlayer, 17, 2, 1)
    elseif nRank == 4 then
       Title:AddTitleToCharacter(pPlayer, 17, 3, 1)
    elseif nRank == 16 then
       Title:AddTitleToCharacter(pPlayer, 17, 5, 1)
    end
    
end

--����16ǿ����
function MENPAIJINGJI_SAICHANG:SetKnockoutMatchPanel(nWinnerId)
	if self.IsOpen == 0 then
		return;
	end
	
	local szNames = "";
	local nWinnerIndex = 0;
	if self.tbPlayers[1] ~= nil then
	  local pPlayer = KGameBase.GetPlayerById(self.tbPlayers[1].nPlayerId);
	  szNames = pPlayer.szName..",";
	  
	  if self.tbPlayers[1].nPlayerId == nWinnerId then
	    nWinnerIndex = 1
	  end
	end
  if self.tbPlayers[2] ~= nil then
    local pPlayer = KGameBase.GetPlayerById(self.tbPlayers[2].nPlayerId);
	  szNames = szNames..pPlayer.szName;
	  
	  if self.tbPlayers[2].nPlayerId == nWinnerId then
	    nWinnerIndex = 2
	  end
	end
  local fnExecute = function(pPlayer)
	if self.nPanelIndex and self.nGameProgress then
		pPlayer.CallClientScript({"QClientScript.Activity:SetKnockoutMatchPanel", self.nGameProgress / 2, self.nPanelIndex, szNames, nWinnerIndex});
	end
  end
  Activity:ActivityPlayerExecute(self.nActivityIndex, fnExecute);
	
end