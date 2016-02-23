Include("script/mission/stage/stage_base.lua")

Stage.tbGames = {};

Stage.tbLayers = {};

function Stage:GetCurLayer(pPlayer)
	local nDifficulty = KStage.GetRushDifficulty(pPlayer);
	local nTeamId = pPlayer.GetTeamId();
	assert(nTeamId > 0);

	if not self.tbLayers[nTeamId] then
		self.tbLayers[nTeamId] = self.MAX_STAGE_LEVEL * (nDifficulty - 1) + 1;
	end

	return self.tbLayers[nTeamId];
end

function Stage:c2s_DoEnterGameSingle(pPlayer)
	local nDifficulty = KStage.GetRushDifficulty(pPlayer);
	assert(pPlayer.GetTeamId() == 0);
	KTeam.CreateTeam(pPlayer.dwId);
	Timer:Register(1 * Env.GAME_FPS, self.DoEnterGame, self, {pPlayer.dwId}, nDifficulty);
end

function Stage:DoEnterGame(tbPlayerIds, nDifficulty)

	assert( type(tbPlayerIds) == "table" );

	if #tbPlayerIds <= 0 then
		return;
	end

	for _, nPlayerId in ipairs(tbPlayerIds) do
		local pPlayer = KGameBase.GetPlayerById(nPlayerId);
		if pPlayer and pPlayer.GetTeamId() > 0 then

			if Player.tbDegree:GetDegree(pPlayer, "RushStage") <= 0 then
				assert(false);
			end

			KStage.SetRushDifficulty(pPlayer, nDifficulty);
			KStage.SetRushState(pPlayer, 1);
			KStage.SetRushLayer(pPlayer, 0);

			-- ���ÿ�ʼʱ��
			local nTime = KGameBase.GetTime();
			KStage.SetRushStartTime(pPlayer, nTime);

			local nLayer = self:GetCurLayer(pPlayer);
			self:DoEnterLayer(pPlayer, nLayer);
		end
	end

	return 0;
end

function Stage:TestEnterLayer(pPlayer, nLayer)
	local nTeamId = pPlayer.GetTeamId();
	self.tbLayers[nTeamId] = nLayer;
	self:DoEnterLayer(pPlayer, nLayer);
end

-- ?gs Stage:TestEnterLayer(me, 3)

function Stage:DoEnterLayer(pPlayer, nLayer)
	local tbPos = self.tbSetting[nLayer].tbBeginPos;
	local nMapId = self.tbSetting[nLayer].nMapId;

	if type(tbPos[1]) == "table" then
		-- ���������һ����
		tbPos = tbPos[KUnify.MathRandom(1, #tbPos)];
	end

	Pet:GetDownRide(pPlayer);	-- ����

	pPlayer.TeleportTo(nMapId, tbPos[1], tbPos[2], tbPos[3], 1);
end

function Stage:SetFailedFlag(pPlayer)
	local tbTempTable = pPlayer.GetCharacterTempTable();
	if not tbTempTable.tbStageInfo then
		tbTempTable.tbStageInfo = {};
	end

	local tbStageInfo = tbTempTable.tbStageInfo;
	if not tbStageInfo.nFailed then
		tbStageInfo.nFailed = 1;
	end
end

function Stage:GetFailedFlag(pPlayer)
	local nFailed = 0;
	local tbTempTable = pPlayer.GetCharacterTempTable();
	local tbStageInfo = tbTempTable.tbStageInfo;

	if tbStageInfo then
	    nFailed = tbStageInfo.nFailed;
	    tbStageInfo.nFailed = nil;
	end

	return nFailed;
end

-- �����������������������
function Stage:GivePlayerAward(pPlayer, nDelayShow)
	local nLayer = KStage.GetRushLayer(pPlayer);
	if nLayer < 1 then
		return;
	end

	local nStar, nLastTime = self:CalcRushStar(pPlayer);
	local nDifficulty = KStage.GetRushDifficulty(pPlayer);
	
	Stage:BroadcastNoticeMsg(pPlayer, nStar);

	local szCallFunc = "YoulongApp.UI.Controller.QUIClientScript:ShowTaskAwardPanel";
	if nDelayShow and nDelayShow == 1 then
		szCallFunc = "YoulongApp.UI.Controller.QUIClientScript:DelayShowTaskAwardPanel";
	end

	pPlayer.CallClientScript({szCallFunc, self.AWARD_MODULE_NAME, nDifficulty * 10 + nStar, nLastTime, nStar, Reward.emTASK_AWARD_STAGE});
end

-- ?gs me.CallClientScript({"YoulongApp.UI.Controller.QUIClientScript:ShowTaskAwardPanel", Stage.AWARD_MODULE_NAME, 14, 120, 5, Reward.emTASK_AWARD_STAGE});

-- �����ȡ����
function Stage:c2s_GetAward(pPlayer)
	local nLayer = KStage.GetRushLayer(pPlayer);
	if nLayer < 1 then
		return;
	end
	
	local nStar = self:CalcRushStar(pPlayer);
	local nDifficulty = KStage.GetRushDifficulty(pPlayer);

	KAward.AddPlayerAward(pPlayer, self.AWARD_MODULE_NAME, nDifficulty * 10 + nStar);
	KStage.SetRushLayer(pPlayer, 0);
	
	-- �콱��۴���
	if nStar > 1 then
		if Player.tbDegree:GetDegree(pPlayer, "RushStage") <= 0 then
			assert(false);
		end
		Player.tbDegree:ReduceDegree(pPlayer, "RushStage");
	end

	Stage:LeaveGame(pPlayer);
end

function Stage:OnEnterScene(dwCharacterId)
	local pPlayer = KGameBase.GetCharacterById(dwCharacterId);

	if pPlayer.IsNpc() == 1 then
		return;
	end

	local nMapId = pPlayer.dwSceneTemplateId;
	if KScene.GetSceneTypeName(nMapId) ~= "stage" then
		-- ���ز��� < 3�㣬�����浯�������
		if KStage.GetRushState(pPlayer) == 1 then
			pPlayer.LeaveTeam();
			KStage.SetRushState(pPlayer, 0);
			-- �����������
			--self:GivePlayerAward(pPlayer, 1);
			--pPlayer.CallClientScript({"YoulongApp.Represent.QRepresentClientScript:ShowRushStarPanel", nDifficulty, nStar});
		end
		return;
	end

	local nTeamId = pPlayer.GetTeamId();
	if nTeamId <= 0 then
		-- TODO:Ӧ����Ҫ���˳��ж�
		return;
	end

	local nLayer = self:GetCurLayer(pPlayer);

	local pGame = self.tbGames[nTeamId];

	-- ��һ�����͵��ؿ����˿����ؿ�
	if pGame then
	    pGame:_JoinPlayer(pPlayer, 1);
		return;
	end

	pGame = Lib:NewClass(self.BaseGame);
	pGame:InitGame(nMapId, pPlayer.dwSceneId, nTeamId, self.tbSetting[nLayer]);
	pGame:_JoinPlayer(pPlayer, 1);

	self.tbGames[nTeamId] = pGame;
end

function Stage:GoNextLayer(nTeamId)
	local pGame = self.tbGames[nTeamId];
	pGame:CloseGame();

	self.tbLayers[nTeamId] = self.tbLayers[nTeamId] + 1;
	local nLayer = self.tbLayers[nTeamId];

	for _, nPlayerId in ipairs(pGame.tbGamePlayers) do
		local pPlayer = KGameBase.GetPlayerById(nPlayerId);
		Player:FullHealth(pPlayer);	-- ����Ѫ
		Stage:DoEnterLayer(pPlayer, nLayer);
	end
end

function Stage:SetTeamRushLayer(nTeamId, nLayer)
	local pGame = self.tbGames[nTeamId];
	assert(pGame);
	for _, nPlayerId in ipairs(pGame.tbGamePlayers) do
		local pPlayer = KGameBase.GetPlayerById(nPlayerId);
		if pPlayer then
			KStage.SetRushLayer(pPlayer, nLayer);	-- �����Ѿ���ս�Ĳ���
		end
	end
end

-- �رչؿ�
function Stage:CloseGame(nTeamId)
	local pGame = self.tbGames[nTeamId];
	pGame:CloseGame(1);

	self.tbLayers[nTeamId] = nil;
	self.tbGames[nTeamId] = nil;
end

function Stage:DoStartGame(pPlayer)
	local nTeamId = pPlayer.GetTeamId();
	if nTeamId <= 0 then
		return;
	end
	local pGame = self.tbGames[nTeamId];
	if pGame then
		pGame:StartGame();
	end
end

function Stage:c2s_StartGame(pPlayer)
	self:DoStartGame(pPlayer);
end

function Stage:LeaveGame(pPlayer)
	local nTeamId = pPlayer.GetTeamId();
	if nTeamId <= 0 then
		return;
	end

	local pGame = self.tbGames[nTeamId];
	if pGame then
		--pPlayer.LeaveTeam();
		pGame:DoLeaveGame(pPlayer, 1);
	end
end

function Stage:OnDeath(pPlayer)
	local nTeamId = pPlayer.GetTeamId();
	assert(nTeamId > 0);
	local pGame = self.tbGames[nTeamId];
	if pGame then
		pGame:OnPlayerDeath(pPlayer);
	end
end

function Stage:NpcUnLock(pNpc)
	local tbTmp = pNpc.GetTempTable("Stage")
	if not tbTmp then
		return 0;
	end
	if (not tbTmp.tbStage) or (not tbTmp.nLock) then
		return 0;
	end
	if not tbTmp.tbStage.tbLock[tbTmp.nLock] then
		return 0;
	end

	tbTmp.tbStage.tbLock[tbTmp.nLock]:UnLockMulti();

	-- KK:���ݸ����Instance,��¼ɱ�����ı�
	-- �ж�����ɱ����Ҫ���Ƿ����0, ������TargetInfo
	if (tbTmp.tbStage.tbLock[tbTmp.nLock]:IsClose() ~= 1) then
		if (tbTmp.tbStage.tbLock[tbTmp.nLock].nInitMultiNum > 0) then
			-- ����targetInfo����ʾɱ������
			tbTmp.tbStage:SyncTargetInfo(tbTmp.tbStage.szTargetInfo, tbTmp.nLock);
		end
	end
end

function Stage:OnLogout(dwCharacterId)
	local pPlayer = KGameBase.GetPlayerById(dwCharacterId);
	if not pPlayer then
		return;
	end

	local nMapId = pPlayer.dwSceneTemplateId;
	if(0 == nMapId) then 
		return;
	end
	if KScene.GetSceneTypeName(nMapId) ~= "stage" then
		return;
	end

	local nTeamId = pPlayer.GetTeamId();
	local pGame = self.tbGames[nTeamId];

	-- �˳����� �����������˳����飬��Ϊ��ҿ����ǿ�gs����OnLogout
	--pPlayer.LeaveTeam();

	local tbLastCity = pPlayer.GetLastSaveCity();
	pPlayer.SetPositionForSaving(tbLastCity.nMapId, tbLastCity.nX, tbLastCity.nY, tbLastCity.nZ);

	if pGame then
		pGame:OnLogout(pPlayer);
	end
end

-- ���б��δ����Ǽ�
function Stage:CalcRushStar(pPlayer)
	local nLastTime = KGameBase.GetTime() - KStage.GetRushStartTime(pPlayer);
	local nStar = 1;
	local nTeamId = pPlayer.GetTeamId();
	if nTeamId <= 0 then
		return 1, nLastTime;
	end

	local pGame = self.tbGames[nTeamId];
	if not pGame then
		return 1, nLastTime;
	end

	local nBloodPercent = 0;
	local nNum = 0;
	for _, nPlayerId in ipairs(pGame.tbGamePlayers) do
		local pPlayer = KGameBase.GetPlayerById(nPlayerId);
		if pPlayer then
			nNum = nNum + 1;
			nBloodPercent = nBloodPercent + math.floor(pPlayer.GetCurrentLife() * 100 / pPlayer.GetMaxLife());
		end
	end

	if nNum > 0 then
		nBloodPercent = nBloodPercent / nNum;
	end

	-- ���2��
	local nBloodStar = 2;
	local nTimeStar = 2;

	-- ����ʣ��Ѫ��
	if nBloodPercent >= 70 then
		nBloodStar = 5;
	elseif nBloodPercent >= 50 then
		nBloodStar = 4;
	elseif nBloodPercent >= 30 then
		nBloodStar = 3;
	else
		nBloodStar = 2;
	end

	if nLastTime <= 5 * 60 then
		nTimeStar = 5;
	elseif nLastTime <= 10 * 60 then
		nTimeStar = 4;
	elseif nLastTime <= 15 * 60 then
		nTimeStar = 3;
	else
		nTimeStar = 2;
	end

	-- ȡС��
	if nBloodStar < nTimeStar then
		nStar = nBloodStar;
	else
		nStar = nTimeStar;
	end

	local nLayer = KStage.GetRushLayer(pPlayer);
	local nDifficulty = KStage.GetRushDifficulty(pPlayer);
	KStage.SetStageStar(pPlayer, nDifficulty, nStar);

	return nStar, nLastTime;
end

function Stage:OnRegenerateNpc(dwSceneId, tbRetNpc, dwExValue, szGroup)
	local pGame = self.tbGames[dwExValue];
	if not pGame or pGame.nSceneId ~= dwSceneId then
		return;
	end

	-- �����ɵ�npc���¼��뵽group����
	for _, pNpc in ipairs(tbRetNpc) do
		pGame:AddNpcInGroup(pNpc, szGroup);
	end
	
	if pGame.tbDelRegenerateNpc[szGroup] then
		pGame:DelNpc(szGroup);
	end
end

function Stage:BroadcastNoticeMsg(pPlayer, nStar)
	local nTeamId = pPlayer.GetTeamId();
	local nTeamLeader = KTeam.GetTeamLeader(nTeamId);
	if nTeamLeader ~= pPlayer.dwId then
		return;
	end
	--local pGame = self.tbGames[nTeamId];
	local nDifficulty = KStage.GetRushDifficulty(pPlayer);
	if nDifficulty == 1 and nStar == 5 then
		KChat.BroadcastNoticeMsg(string.format(Lang.mission.str1077[Lang.Idx], pPlayer.szName));
	elseif nDifficulty == 2 and nStar == 5 then
		KChat.BroadcastNoticeMsg(string.format(Lang.mission.str1078[Lang.Idx], pPlayer.szName));
	elseif nDifficulty == 3 and nStar > 1 and nStar < 5 then
		KChat.BroadcastNoticeMsg(string.format(Lang.mission.str1079[Lang.Idx], pPlayer.szName));
	elseif nDifficulty == 3 and nStar == 5 then
		KChat.BroadcastNoticeMsg(string.format(Lang.mission.str1080[Lang.Idx], pPlayer.szName));
	elseif nDifficulty == 4 and nStar > 1 and nStar < 5 then
		KChat.BroadcastNoticeMsg(string.format(Lang.mission.str1081[Lang.Idx], pPlayer.szName));
	elseif nDifficulty == 4 and nStar == 5 then
		KChat.BroadcastNoticeMsg(string.format(Lang.mission.str1082[Lang.Idx], pPlayer.szName));
	end
end

CallCenter:RegisterGlobalEvent(KOBJEVENT.emKOBJEVENTTYPE_PLAYER_LOGOUT, Stage.OnLogout, Stage);
CallCenter:RegisterGlobalEvent(KOBJEVENT.emKOBJEVENTTYPE_CHARACTER_ENTER_SCENE, Stage.OnEnterScene, Stage);
