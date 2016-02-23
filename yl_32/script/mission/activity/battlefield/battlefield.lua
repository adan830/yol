Include("script/mission/activity/activitystep.lua")
Include("script/mission/activity/activitydef.lua")

Activity.BattleField = Lib:NewClass(Activity.ActivityStep);

Activity.ACTSTEP_FACTORY[Activity.STEP_TYPE.BATTLE_FIELD] = Activity.BattleField -- ע�ᵽ�����

local BattleField = Activity.BattleField

BattleField.ONE_NPC_SCORE 		= 5;	--��ɱһ��npc��û�����
BattleField.ONE_PLAYER_SCORE 	= 10;	--��ɱһ����һ�û�����
BattleField.ONE_TOWER_SCORE 	= 15;	--��ɱһ��������û�����
BattleField.ONE_BASE_SCORE 		= 30;	--��ɱһ�����ػ�û�����
BattleField.NPC_START_TEMPLATE_ID 	= 2571;	--ս��npc��ʼID
BattleField.NPC_END_TEMPLATE_ID 	= 2710;	--ս��npc����ID
BattleField.TOWER_START_TEMPLATE_ID = 2546; --ս��������ʼID
BattleField.TOWER_END_TEMPLATE_ID 	= 2570;	--ս����������ID
BattleField.BASE_START_TEMPLATE_ID 	= 2540;	--ս��������ʼID
BattleField.BASE_END_TEMPLATE_ID 	= 2545;	--ս�����ؽ���ID

function BattleField:OnInit()	
	self.tbPlayerNpcScores = {};	--��һ�ɱnpc�÷�
	self.tbPlayerPlayerScores = {};	--��һ�ɱ��ҵ÷�
	self.tbPlayerTowerScores = {};	--��һ�ɱ�����÷�
	self.tbPlayerBaseScores = {};	--��һ�ɱ���ص÷�
	self.tbPlayerRanks = {};			--��һ������а�
	self.tbPlayerScore = {};		--����ܻ��ֱ�
	self.nProtossCampScores = 0;	--�����ܻ���
	self.nEvilCampScores = 0;		--ħ���ܻ���
	self.dwProtossCampScoresUpdateTime = 0;	--�����ܻ��ָ���ʱ��
	self.dwEvilCampScoresUpdateTime = 0;	--ħ���ܻ��ָ���ʱ��
	self.dwProtossBaseKilledTime = 0; --������ر���ɱʱ�� 
	self.dwEvilBaseKilledTime = 0;	--ħ����ر���ɱʱ��
	self.nProtossCampCount = 0;		-- ��������
	self.nEvilCampCount = 0;		-- ħ������
end

-- ����ս����������Ϣ, ��ʼ��
function BattleField:OnEnterActivityScene(nPlayerId)
	print("!!!!!!!!!!!BattleField JoinPlayer. Group: ", nGroup);
	self.tbPlayerNpcScores[nPlayerId] = 0;
	self.tbPlayerPlayerScores[nPlayerId] = 0;
	self.tbPlayerTowerScores[nPlayerId] = 0;
	self.tbPlayerBaseScores[nPlayerId] = 0;
	self.tbPlayerScore[nPlayerId] = {nScore = 0, dwUpateTime = 0};
	
	-- ս��������0
	local pPlayer = KGameBase.GetPlayerById(nPlayerId)
	pPlayer.SetGlobalBattleScore(0);
end

function BattleField:OnStartStep()
	self:BroadcastCampCount();
	-- ȫ���Ѿ����룬����ˢ��
	self:RefreshAllPlayerRanks() 
	-- ���Ϳ�ʼ��Ϣ���������ͻ���
	for nPlayerId, tbScore in pairs(self.tbPlayerScore) do
		--self:SendPlayerRankRecord(nPlayerId);����ˢ��ʱ�Ѿ����͹�
		--self:SendPlayerMeInfo(nPlayerId);
		self:SendPlayerMeRecord(nPlayerId, 0);
		self:SendPlayerCampRecord(nPlayerId);
		self:SendCampCount(nPlayerId);
	end
  
  for _, tbPlayer in pairs(self.tbPlayers) do
		-- ������ħbuff��Ч
		local pPlayer = KGameBase.GetPlayerById(tbPlayer.nPlayerId);
	
		if pPlayer then
	    if pPlayer.GetCurrentCamp() == 4 then
	      self:SetPlayerActivityInfo(tbPlayer.nPlayerId, nil, Lang.mission.str11[Lang.Idx]);	
	      BufferApi.AddBufferToCharacter(pPlayer.dwId, 0, pPlayer.dwId, 1170, 1)
	    elseif pPlayer.GetCurrentCamp() == 5 then
	      self:SetPlayerActivityInfo(tbPlayer.nPlayerId, nil, Lang.mission.str12[Lang.Idx]);	
	      BufferApi.AddBufferToCharacter(pPlayer.dwId, 0, pPlayer.dwId, 1171, 1)
	    end
	    
		end
	end
	
	--����ʼ��Ч
	--self:ShowStartEffect();
end

function BattleField:OnPlayerKill(nKillerCharId, nDeathCharId)
	local pKiller = KGameBase.GetPlayerById(nKillerCharId);
	local pDeath = KGameBase.GetPlayerById(nDeathCharId);
	
	if pKiller and pDeath then
		self:AddPlayerBattleScore(pKiller.dwId, 1);
	end
end

function BattleField:AddPlayerBattleScore(nPlayerId, nScoreType)
	local pPlayer = KGameBase.GetPlayerById(nPlayerId);
	if not pPlayer or self.IsOpen == 0 then
		return;
	end
	
	local nScore = 0;
	if nScoreType == 1 then	--�з����
		nScore = self.ONE_PLAYER_SCORE;
		self.tbPlayerPlayerScores[nPlayerId] = self.tbPlayerPlayerScores[nPlayerId] + nScore;
	elseif nScoreType == 2 then --�з�npc
		nScore = self.ONE_NPC_SCORE;
		self.tbPlayerNpcScores[nPlayerId] = self.tbPlayerNpcScores[nPlayerId] + nScore;
	elseif nScoreType == 3 then	--�з�����
		nScore = self.ONE_TOWER_SCORE;
		self.tbPlayerTowerScores[nPlayerId] = self.tbPlayerTowerScores[nPlayerId] + nScore;
	elseif nScoreType == 4 then --�з�����
		nScore = self.ONE_BASE_SCORE;
		self.tbPlayerBaseScores[nPlayerId] = self.tbPlayerBaseScores[nPlayerId] + nScore;
	end
	
	if pPlayer.GetCurrentCamp() == 4 then	--������Ӫ�ܻ��ּ���
		self.nProtossCampScores = self.nProtossCampScores + nScore;
		self.dwProtossCampScoresUpdateTime = KGameBase.GetTime();
	elseif pPlayer.GetCurrentCamp() == 5 then -- ħ����Ӫ�ܻ��ּ���
		self.nEvilCampScores = self.nEvilCampScores + nScore;
		self.dwEvilCampScoresUpdateTime = KGameBase.GetTime();	
	end
	self.tbPlayerScore[nPlayerId].nScore = self.tbPlayerScore[nPlayerId].nScore + nScore;
	self.tbPlayerScore[nPlayerId].dwUpateTime = KGameBase.GetTime();
	--�ɵĽӿڣ�pPlayer.SetGlobalBattleScore(nCurrScore)
	
	--������ն��
	local nKillPlayerCount = self.tbPlayerPlayerScores[nPlayerId] / self.ONE_PLAYER_SCORE;
	local nKillNpcCount = self.tbPlayerNpcScores[nPlayerId] / self.ONE_NPC_SCORE;
	local nKillTowerCount = self.tbPlayerTowerScores[nPlayerId] / self.ONE_TOWER_SCORE;
	local nKillBaseCount = self.tbPlayerBaseScores[nPlayerId] / self.ONE_BASE_SCORE;
	local nKillCount = nKillPlayerCount + nKillTowerCount + nKillBaseCount;
	if nScoreType ~= 2 then
		if nKillCount == 5 then
			KChat.BroadcastNoticeMsg(string.format(Lang.mission.str13[Lang.Idx],pPlayer.szName,nKillCount));
		elseif nKillCount == 10 then
			KChat.BroadcastNoticeMsg(string.format(Lang.mission.str14[Lang.Idx],pPlayer.szName,nKillCount));
		elseif nKillCount == 15 then
			KChat.BroadcastNoticeMsg(string.format(Lang.mission.str15[Lang.Idx],pPlayer.szName,nKillCount));
		elseif nKillCount == 20 then
			KChat.BroadcastNoticeMsg(string.format(Lang.mission.str16[Lang.Idx],pPlayer.szName,nKillCount));
		end
	end
	--ˢ�µ�ǰ���а�
	self:RefreshAllPlayerRanks();
	self:SendPlayerMeRecord(nPlayerId, nScoreType);
	self:BroadcastCampRecord();
	
	pPlayer.pPlayerPurse.AddMoney(Purse.EM_MONEY_SHENMO_SCORE, nScore)
	KRank.ModifyRankValue(pPlayer.dwId, Rank.SMZC_RANK, pPlayer.pPlayerPurse.GetMoney(Purse.EM_MONEY_SHENMO_SCORE));
end

function BattleField:OnJoinPlayer(nPlayerId, nGroup)
	local pPlayer = KGameBase.GetPlayerById(nPlayerId)
	if pPlayer ~= nil then
	   pPlayer.SetCurrentLife(pPlayer.GetMaxLife()) -- ����ս��ʱ�ָ���Ѫ	 
	end
end


-- ������߻���ʱ
function BattleField:OnKickPlayer(nPlayerId)
	if self.IsOpen ~= 1 then
		return;
	end
	
	-- �ָ������Ӫ
	local pPlayer = KGameBase.GetPlayerById(nPlayerId);
	if pPlayer then
		if pPlayer.GetCurrentCamp() == 4 and self.nProtossCampCount > 0 then
			self.nProtossCampCount = self.nProtossCampCount - 1;
		elseif pPlayer.GetCurrentCamp() == 5 and self.nEvilCampCount > 0 then
			self.nEvilCampCount = self.nEvilCampCount - 1;
		end
		
		--pPlayer.SysMsg("�˴���ħս��������"..self:GetPlayerRank(nPlayerId))
		
		-- ���ͷ����־
		if pPlayer.GetCurrentCamp() == 4 then
	      pPlayer.pBufferEffect.ClearBuff(1170)
	  elseif pPlayer.GetCurrentCamp() == 5 then
	      pPlayer.pBufferEffect.ClearBuff(1171)
	  end
	    
		pPlayer.SetCurrentCamp(1);		
		--�Ƴ����������
		self.tbPlayerNpcScores[nPlayerId] = nil;
		self.tbPlayerPlayerScores[nPlayerId] = nil;
		self.tbPlayerTowerScores[nPlayerId] = nil;
		self.tbPlayerBaseScores[nPlayerId] = nil;
		self.tbPlayerScore[nPlayerId] = nil;
		--�Ƴ�������Ƴ������������ܻ��ֲ��Ƴ�
		self:RefreshAllPlayerRanks();
		self:BroadcastCampCount();
	end
end

-- ͳ��������ҵ�����״̬ (����ָܷı�ʱִ��)
function BattleField:RefreshAllPlayerRanks()
	self.tbPlayerRanks = {} -- array
	for PlayerId, tbScore in pairs(self.tbPlayerScore) do
		-- �������һ��ֲ�������
		table.insert(self.tbPlayerRanks, {nPlayerId = PlayerId, nPlayerScore = tbScore.nScore, dwUpdateTime = tbScore.dwUpateTime})
	end
	
	-- �������������
	local sortFunc = function(a, b) if b.nPlayerScore ~= a.nPlayerScore then  return a.nPlayerScore > b.nPlayerScore  else return  a.dwUpdateTime < b.dwUpdateTime end end
	table.sort(self.tbPlayerRanks, sortFunc);
	
	-- ���������������ͻ���
	for nPlayerId, tbScore in pairs(self.tbPlayerScore) do
		self:SendPlayerRankRecord(nPlayerId);
		self:SendPlayerMeInfo(nPlayerId);
	end
end
-- ��ȡ������
function BattleField:GetPlayerRank(nPlayerId)
	for rankId, tbPlayerRank in pairs(self.tbPlayerRanks) do
		if (tbPlayerRank.nPlayerId == nPlayerId) then
			return rankId
		end
	end
	return -1; -- û����������ô���ܣ�
end

-- ������Ҹ��˻�����Ϣ:  ���˻��֡�����
function BattleField:SendPlayerMeInfo(nPlayerId)
	local pPlayer = KGameBase.GetPlayerById(nPlayerId);
	local nPlayerScore = self.tbPlayerScore[nPlayerId].nScore;	--	��һ���	
	local nPlayerRank = self:GetPlayerRank(nPlayerId); -- �������
	--pPlayer.SysMsg(string.format("���ø�����Ϣ����%d�֣��ŵ�%d��", nPlayerScore, nPlayerRank));
	pPlayer.CallClientScript({"QClientScript.Activity:SetBFMeInfo", nPlayerScore, nPlayerRank});	--���˻��ֺ�����
	local szCampName = "";
	if pPlayer.GetCurrentCamp() == 4 then
		szCampName = szCampName.."����";
	elseif pPlayer.GetCurrentCamp() == 5 then
		szCampName = szCampName.."ħ��";
	end
	self:SetPlayerActivityInfo(nPlayerId, nil, string.format(Lang.mission.str17[Lang.Idx],
	 szCampName, nPlayerRank, nPlayerScore, self.nProtossCampScores, self.nEvilCampScores));	
end

-- ���������Ӫս��, ����Ӫ�����ܼ�
function BattleField:SendPlayerCampRecord(nPlayerId)
	local pPlayer = KGameBase.GetPlayerById(nPlayerId);
	--pPlayer.SysMsg(string.format("������Ӫ����:%d, ħ����Ӫ����:%d", self.nProtossCampScores, self.nEvilCampScores));
	pPlayer.CallClientScript({"QClientScript.Activity:SetBFCampRecord", self.nProtossCampScores, self.nEvilCampScores});
end

-- ����˫����Ӫ��ǰ����
function BattleField:SendCampCount(nPlayerId)
	local pReceivePlayer = KGameBase.GetPlayerById(nPlayerId)  -- �ű����������
	if self.nProtossCampCount == 0 and self.nEvilCampCount == 0 then
		for nGroup, tbPlayerGroup in pairs(self.tbPlayerGroups) do
			if nGroup > 0 then
				for _, nPlayerId in pairs(tbPlayerGroup) do
					local pPlayer = KGameBase.GetPlayerById(nPlayerId)
					if pPlayer then
						if pPlayer.GetCurrentCamp() == 4 then
							self.nProtossCampCount = self.nProtossCampCount + 1;
						elseif pPlayer.GetCurrentCamp() == 5 then
							self.nEvilCampCount = self.nEvilCampCount + 1;
						end
					end
				end
			end
		end
	end
	
	--pReceivePlayer.SysMsg(string.format("����:%d��, ħ��:%d��", self.nProtossCampCount, self.nEvilCampCount));
	pReceivePlayer.CallClientScript({"QClientScript.Activity:SetBFCampCount", self.nProtossCampCount, self.nEvilCampCount});
end

--�㲥ս������
function BattleField:BroadcastCampCount()
	for _, tbPlayer in pairs(self.tbPlayers) do
		self:SendCampCount(tbPlayer.nPlayerId);
	end
end

--�㲥ս������
function BattleField:BroadcastCampRecord()
	for _, tbPlayer in pairs(self.tbPlayers) do
		self:SendPlayerCampRecord(tbPlayer.nPlayerId);
	end
end

-- �����������״��, ����������������·��������������˵���ҡ����콱�������콱���������ܻ���
function BattleField:SendPlayerRankRecord(nPlayerId)
	local pReceivePlayer = KGameBase.GetPlayerById(nPlayerId)  -- �ű����������
	local nRank = 1;
	for _, tbPlayerRank in pairs(self.tbPlayerRanks) do
		if nRank <= 10 then
			-- ��ȡ���а���ҵ���Ϣ
			local pPlayer = KGameBase.GetPlayerById(tbPlayerRank.nPlayerId)
			local nCamp = pPlayer.GetCurrentCamp();
			local szCampName = "";
			if nCamp == 4 then
				szCampName = szCampName..Lang.mission.str18[Lang.Idx];
			elseif nCamp == 5 then
				szCampName = szCampName..Lang.mission.str19[Lang.Idx];
			end
			local szPlayerName = pPlayer.szName;
			local nKillPlayerCount = self.tbPlayerPlayerScores[tbPlayerRank.nPlayerId] / self.ONE_PLAYER_SCORE;
			local nKillNpcCount = self.tbPlayerNpcScores[tbPlayerRank.nPlayerId] / self.ONE_NPC_SCORE;
			local nKillTowerCount = self.tbPlayerTowerScores[tbPlayerRank.nPlayerId] / self.ONE_TOWER_SCORE;
			local nKillBaseCount = self.tbPlayerBaseScores[tbPlayerRank.nPlayerId] / self.ONE_BASE_SCORE;
			local nPlayerScore = self.tbPlayerScore[tbPlayerRank.nPlayerId].nScore 	-- �����ܻ���
			
			-- ǰ10������������
			--pReceivePlayer.SysMsg(string.format("�յ�������Ϣ, ����%d, ���%s", nRank, szPlayerName));
			pReceivePlayer.CallClientScript({"QClientScript.Activity:SetBFRankRecord", nRank, szCampName, szPlayerName, nKillPlayerCount, nKillNpcCount, nKillTowerCount, nKillBaseCount, nPlayerScore});
		end
		nRank = nRank + 1;
	end
	
	--��������10λ
	while nRank <= 10 do
		pReceivePlayer.CallClientScript({"QClientScript.Activity:SetBFRankRecord", nRank,"", "", 0, 0, 0, 0, 0});
		nRank = nRank + 1;
	end
end

-- 1��ʾ��ɱ��� 2��ʾ��ɱnpc 3��ʾ�ݻ����� 4��ʾ�ݻٻ���
function BattleField:SendPlayerMeRecord(nPlayerId, nType)
	local pPlayer = KGameBase.GetPlayerById(nPlayerId);
	if pPlayer then
		local nCount = 0;
		local nScore = 0;
		if nType == 1 then	--�з����
			nScore = self.tbPlayerPlayerScores[nPlayerId];
			nCount = nScore / self.ONE_PLAYER_SCORE;
			pPlayer.CallClientScript({"QClientScript.Activity:SetBFMeRecord", nType, nCount, nScore});
		elseif nType == 2 then --�з�npc
			nScore = self.tbPlayerNpcScores[nPlayerId];
			nCount = nScore / self.ONE_NPC_SCORE;
			pPlayer.CallClientScript({"QClientScript.Activity:SetBFMeRecord", nType, nCount, nScore});			
		elseif nType == 3 then --�з�����
			nScore = self.tbPlayerTowerScores[nPlayerId];
			nCount = nScore / self.ONE_TOWER_SCORE;
			pPlayer.CallClientScript({"QClientScript.Activity:SetBFMeRecord", nType, nCount, nScore});			
		elseif nType == 4 then	--�з�����
			nScore = self.tbPlayerBaseScores[nPlayerId];	
			nCount = nScore / self.ONE_BASE_SCORE; 
			pPlayer.CallClientScript({"QClientScript.Activity:SetBFMeRecord", nType, nCount, nScore});
		elseif nType == 0 then  --����ȫ��
			nScore = self.tbPlayerPlayerScores[nPlayerId];
			nCount = nScore / self.ONE_PLAYER_SCORE;
			pPlayer.CallClientScript({"QClientScript.Activity:SetBFMeRecord", 1, nCount, nScore});
			nScore = self.tbPlayerNpcScores[nPlayerId];
			nCount = nScore / self.ONE_NPC_SCORE;
			pPlayer.CallClientScript({"QClientScript.Activity:SetBFMeRecord", 2, nCount, nScore});
			nScore = self.tbPlayerTowerScores[nPlayerId];
			nCount = nScore / self.ONE_TOWER_SCORE;
			pPlayer.CallClientScript({"QClientScript.Activity:SetBFMeRecord", 3, nCount, nScore});
			nScore = self.tbPlayerBaseScores[nPlayerId];	
			nCount = nScore / self.ONE_BASE_SCORE; 
			pPlayer.CallClientScript({"QClientScript.Activity:SetBFMeRecord", 4, nCount, nScore});			
		end
	end
end

function BattleField:OnNpcDeath(pKiller, pNpc)
	assert(pKiller and pNpc);
	if pNpc.IsNpc() ~= 1 then
		return;
	end
	
	if pKiller.GetCurrentCamp() == pNpc.GetCurrentCamp() then
		return;
	end
	
	if pNpc.dwTemplateId >= self.BASE_START_TEMPLATE_ID and pNpc.dwTemplateId <= self.BASE_END_TEMPLATE_ID then
		if pNpc.GetCurrentCamp() == 4 then	--������ر���ɱ
			self.dwProtossBaseKilledTime = KGameBase.GetTime();
		elseif pNpc.GetCurrentCamp() == 5 then --ħ����ر���ɱ
			self.dwEvilBaseKilledTime = KGameBase.GetTime();
		end
		self:AddPlayerBattleScore(pKiller.dwId, 4);
		self:EndStep();
	elseif pNpc.dwTemplateId >= self.TOWER_START_TEMPLATE_ID and pNpc.dwTemplateId <= self.TOWER_END_TEMPLATE_ID then
		self:AddPlayerBattleScore(pKiller.dwId, 3);
	elseif pNpc.dwTemplateId >= self.NPC_START_TEMPLATE_ID and pNpc.dwTemplateId <= self.NPC_END_TEMPLATE_ID then
		self:AddPlayerBattleScore(pKiller.dwId, 2);
	end
end

function BattleField:OnPlayerDamage(nCasterId, nInjuredId, nDamage)
    local pInjuredChar = KGameBase.GetCharacterById(nInjuredId)
    if pInjuredChar.IsNpc() == 1 then
      local pBaseNpc = KGameBase.GetNpcById(nInjuredId)
	    if pBaseNpc.dwTemplateId >= self.BASE_START_TEMPLATE_ID and pBaseNpc.dwTemplateId <= self.BASE_END_TEMPLATE_ID then
	        local nCurrentLife = pBaseNpc.GetCurrentLife();
	        local nMaxLife = pBaseNpc.GetMaxLife();
	        local fScale = nCurrentLife / nMaxLife;
	        local fLastScale = (nCurrentLife + nDamage) / nMaxLife;
	        local nTargetGroup = 2;
	        
	        local pPlayer = KGameBase.GetPlayerById(nCasterId)
	        if pPlayer.GetCurrentCamp() == 5 then
	           nTargetGroup = 1;
	        end
	        
	        if (fScale < 0.8 and fLastScale >= 0.8) then
	           self:BroadcastActivityNotice(Lang.mission.str20[Lang.Idx], nTargetGroup)
	        elseif (fScale < 0.6  and fLastScale >= 0.6) then
	           self:BroadcastActivityNotice(Lang.mission.str20[Lang.Idx], nTargetGroup)
	        elseif (fScale < 0.4 and fLastScale >= 0.4) then
	           self:BroadcastActivityNotice(Lang.mission.str20[Lang.Idx], nTargetGroup)
	        elseif (fScale < 0.2 and fLastScale >= 0.2) then
	           self:BroadcastActivityNotice(Lang.mission.str20[Lang.Idx], nTargetGroup)
	        end
	    end
	  end
end

function BattleField:ShowStartEffect()
	for _, tbPlayer in pairs(self.tbPlayers) do
		local pPlayer = KGameBase.GetPlayerById(tbPlayer.nPlayerId);
		if pPlayer then
			self:ShowEffect(pPlayer, 1);	--��ʼ��Ч
		end
	end
end

function BattleField:OnEndStep()
	--ʤ�����ж�
	local nWinnerCamp = 0;
	if self.dwProtossBaseKilledTime ~= 0 then
		if self.dwEvilBaseKilledTime ~= 0 then
			if self.dwEvilBaseKilledTime > self.dwProtossBaseKilledTime then
				nWinnerCamp = 4;	--����ʤ��
			else
				nWinnerCamp = 5;	--ħ��ʤ��
			end
		else
			nWinnerCamp = 5;	--ħ��ʤ��
		end
	else 
		if self.dwEvilBaseKilledTime ~= 0 then
			nWinnerCamp = 4;	--����ʤ��
		else
			if self.nProtossCampScores > self.nEvilCampScores then
				nWinnerCamp = 4;
			elseif  self.nProtossCampScores < self.nEvilCampScores then
				nWinnerCamp = 5;
			else	--�������
				if self.nProtossCampScores == 0 and self.nEvilCampScores == 0 then	--���ͣ������
					nWinnerCamp = KUnify.MathRandom(4, 5);
				else
					if self.dwProtossCampScoresUpdateTime > self.dwEvilCampScoresUpdateTime then	--ʱ���Ⱥ��ж�
						nWinnerCamp = 5;
					else
						nWinnerCamp = 4;
					end
				end
			end
		end
	end
	
	--self.nWinnerCamp = nWinnerCamp;
	
	--����Ӫ����
	if nWinnerCamp ~= 0 then
		for _, tbPlayer in pairs(self.tbPlayers) do
			local pPlayer = KGameBase.GetPlayerById(tbPlayer.nPlayerId);
			if pPlayer then
				--[[if pPlayer.GetCurrentCamp() == nWinnerCamp then
					--self:ShowEffect(pPlayer,4);	--�ɹ���Ч
					KAward.AddPlayerAward(pPlayer, "BattleFieldCamp", 1);
				else
					--self:ShowEffect(pPlayer,3);	--ʧ����Ч
				end--]]
				-- ���ͷ����־
				if pPlayer.GetCurrentCamp() == 4 then
			      pPlayer.pBufferEffect.ClearBuff(1170)
			  elseif pPlayer.GetCurrentCamp() == 5 then
			      pPlayer.pBufferEffect.ClearBuff(1171)
			  end
			  
			  if self:GetPlayerRank(tbPlayer.nPlayerId) == -1 then
			  	pPlayer.SysMsg(Lang.mission.str21[Lang.Idx]..self.tbPlayerScore[tbPlayer.nPlayerId].nScore)
			  else
			  	pPlayer.SysMsg(Lang.mission.str21[Lang.Idx]..self.tbPlayerScore[tbPlayer.nPlayerId].nScore..Lang.mission.str22[Lang.Idx]..self:GetPlayerRank(tbPlayer.nPlayerId))
			  end
	  
			  if pPlayer.IsDead() == 1 then  -- �����ɫ�������Զ�����		  
			  	KCharacter.Revive(pPlayer, 1000, 1000);
				else   --������̨�����Զ���Ѫ
				  pPlayer.SetCurrentLife(pPlayer.GetMaxLife());
			  end
				--pPlayer.SetCurrentCamp(1);	--�ָ������Ӫ
				--��ʤ����Ӫ
				pPlayer.CallClientScript({"QClientScript.Activity:SetBFWinCamp", nWinnerCamp - 3});
				--������ս��
				pPlayer.CallClientScript({"QClientScript.Activity:OpenBFPanel"});		
			end
		end
		
		local szWinnerCamp = Lang.mission.str18[Lang.Idx];
		if nWinnerCamp ~= 4 then
			szWinnerCamp = Lang.mission.str19[Lang.Idx];
		end
		KChat.BroadcastNoticeMsg(string.format(Lang.mission.str23[Lang.Idx],szWinnerCamp));
			
		if #self.tbPlayerRanks >= 1 then
			local pFirstPlayer = KGameBase.GetPlayerById(self.tbPlayerRanks[1].nPlayerId);
			KChat.BroadcastNoticeMsg(string.format(Lang.mission.str24[Lang.Idx],pFirstPlayer.szName));
		end
	end
	
	local tbPlayersCopy = Lib:CopyTBN(self.tbPlayers)
	local tbPlayerRanksCopy = Lib:CopyTBN(self.tbPlayerRanks)
	Timer:Register(3 * Env.GAME_FPS, self.SendAward, self, tbPlayersCopy, tbPlayerRanksCopy, nWinnerCamp) -- �ӳټ��뷢�������������һ�����
	
	self:ResetData();
	self:DeleteAllNpc();	--ɾ������npc ������
end

function BattleField:SendAward(tbPlayers, tbPlayerRanks, nWinnerCamp)			
  --�����н���
	for nRank, tbPlayerRank in pairs(tbPlayerRanks) do
		if nRank <= 10 then
			local pPlayer = KGameBase.GetPlayerById(tbPlayerRank.nPlayerId);
			if pPlayer then
				KAward.AddPlayerAward(pPlayer, "BattleFieldRank", nRank);
				
				Title:AddTitleToCharacter(pPlayer, 12, nRank, 0) -- ���ƺŽ���
			end
		end	
	end  
	
	if nWinnerCamp ~= 0 then
		for _, tbPlayer in pairs(tbPlayers) do
			local pPlayer = KGameBase.GetPlayerById(tbPlayer.nPlayerId);
			if pPlayer then
				if pPlayer.GetCurrentCamp() == nWinnerCamp then					
					KAward.AddPlayerAward(pPlayer, "BattleFieldCamp", 1);
				end
				
				pPlayer.SetCurrentCamp(1);	--�ָ������Ӫ
			end
		end
	end
	
	return 0
end

function BattleField:ResetData()
	--��������
	self.tbPlayerNpcScores = {};
	self.tbPlayerPlayerScores = {};
	self.tbPlayerTowerScores = {};
	self.tbPlayerBaseScores = {};
	self.tbPlayerScore = {};
	self.nProtossCampScores = 0;	
	self.nEvilCampScores = 0;
	self.dwProtossCampScoresUpdateTime = 0;
	self.dwEvilCampScoresUpdateTime = 0;		
	self.dwProtossBaseKilledTime = 0;  
	self.dwEvilBaseKilledTime = 0;	
	self.nProtossCampCount = 0;	
	self.nEvilCampCount = 0;		
end
