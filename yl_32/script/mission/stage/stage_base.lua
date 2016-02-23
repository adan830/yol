
Include("script/mission/mission.lua");
Include("script/mission/baselock.lua")
Include("script/mission/stage/stage_def.lua")
-- ����

Stage.BaseGame = Mission:New();
local BaseGame = Stage.BaseGame;
local tbEventLock = Lib:NewClass(Lock.tbBaseLock);

BaseGame.EVENT_PROC  =
{
    [Stage.DO_SCRIPT]	= "ExcuteScript",
    [Stage.ADD_NPC]		= "AddNpc",
    [Stage.DEL_NPC]		= "DelNpc",
	[Stage.BLACK_MSG]	= "BlackMsg",
	[Stage.NPC_BUBBLE] 	= "NpcBubble",
	[Stage.ME_BUBBLE]	= "MeBubble",
	[Stage.TARGET_INFO]	= "SyncTargetInfo",
	[Stage.TIME_INFO] = "SyncTimeInfo",
	[Stage.REVIVE_INFO] = "ReviveInfo",
	[Stage.CLEAR_BUFF] = "ClearPlayerBuff",
	[Stage.SET_TRAP_INVALID] = "SetTrapInvalid",		-- ����trap��ʧЧ
	[Stage.SHOW_NOTICE_MSG] = "ShowNoticeMsg",	-- ����
};

function tbEventLock:InitEventLock(tbStage, nTime, nMultiNum, tbStartEvent, tbUnLockEvent)
	self:InitLock(nTime, nMultiNum);
	self.tbStage 	= tbStage;
	self.tbUnLockEvent 	= tbUnLockEvent;
	self.tbStartEvent 	= tbStartEvent;
end

function tbEventLock:OnUnLock()
	if self.tbStage and self.tbUnLockEvent then
		for i = 1, #self.tbUnLockEvent do
			self.tbStage:OnEvent(unpack(self.tbUnLockEvent[i]));
		end
	end
	local tbStage = self.tbStage;
	assert(tbStage);
	
	if tbStage.bCanTakeAward and tbStage.bCanTakeAward == 1 then
		-- �����һ�أ��������㽱��
		Stage:SetTeamRushLayer(tbStage.nTeamId, tbStage.nLayer);
		tbStage.bCanTakeAward = 0;
		
		-- ���������йأ���������㽱��
		if tbStage.nLayer >= Stage.MAX_STAGE_LEVEL then
			for _, nPlayerId in ipairs(tbStage.tbGamePlayers) do
				local pPlayer = KGameBase.GetPlayerById(nPlayerId);
				if pPlayer then
					local nDifficulty = KStage.GetRushDifficulty(pPlayer);
					if nDifficulty == 2 then
						Target:DoTarget(pPlayer, 5);
					end
					Stage:GivePlayerAward(pPlayer);
				end
			end
		end
		
	end
	
	if tbStage.bFinishLayer == 1 then
		Stage:GoNextLayer(tbStage.nTeamId);
	elseif tbStage.bFinishStage == 1 then
		Stage:CloseGame(tbStage.nTeamId);
	end
end

function tbEventLock:OnStartLock()
	if self.tbStage and self.tbStartEvent then
		for i = 1, #self.tbStartEvent do
			self.tbStage:OnEvent(unpack(self.tbStartEvent[i]));
		end
	end
end

function BaseGame:UnInitGame()
	for _, tbLockInfo in pairs(self.tbLock) do
		if tbLockInfo.nTimerId > 0 then
			Timer:Close(tbLockInfo.nTimerId);
		end
	end
end

function BaseGame:InitGame(nMapId, nSceneId, nTeamId, tbLayerSetting)
	self.nMapId = nMapId;
    self.nSceneId = nSceneId;
	self.nTeamId = nTeamId;
	self.nLayer = tbLayerSetting.nLayer;
    self.tbLock = {};
    self.tbNpcGroup = {};
    self.tbAddNpcTimer = {};
	self.tbDelRegenerateNpc = {};		-- ɾ��������npc
	self:Open();
	
	self.tbLayerSetting = tbLayerSetting;
	for i, tbLockSetting in pairs(tbLayerSetting.LOCK) do
		self.tbLock[i] = Lib:NewClass(tbEventLock);
		self.tbLock[i].nLockId = i;
		self.tbLock[i]:InitEventLock(self, tbLockSetting.nTime * Env.GAME_FPS, tbLockSetting.nNum, tbLockSetting.tbStartEvent, tbLockSetting.tbUnLockEvent);
	end
	for i, tbLockSetting in ipairs(tbLayerSetting.LOCK) do -- ��֤����˳��
		for _, verPreLock in pairs(tbLockSetting.tbPrelock) do
			if type(verPreLock) == "number" then
				self.tbLock[i]:AddPreLock(self.tbLock[verPreLock]);
			elseif type(verPreLock) == "table" then
				local tbPreLock = {}
				for j = 1, #verPreLock do
					if self.tbLock[verPreLock[j]] then
						table.insert(tbPreLock, self.tbLock[verPreLock[j]]);
					end
				end
				self.tbLock[i]:AddPreLock(tbPreLock);
			else
				return 0;
			end
		end
	end
	self.nMapId = nMapId;
	self.nEndTime = KGameBase.GetTime() + tbLayerSetting.nTimeLimit;
	
	local nEndTimerId = Timer:Register(tbLayerSetting.nTimeLimit * Env.GAME_FPS, self.OnTimeOut, self);
	self.nEndTimerId = nEndTimerId;
end

function BaseGame:OnTimeOut()
	for _, nPlayerId in ipairs(self.tbGamePlayers) do
		local pPlayer = KGameBase.GetPlayerById(nPlayerId);
		Stage:SetFailedFlag(pPlayer);
	end
	self:CloseGame(1);
	return 0;
end

function BaseGame:_JoinPlayer(pPlayer)
	if not self.tbGamePlayers then
		self.tbGamePlayers = {};
	end
	table.insert(self.tbGamePlayers, pPlayer.dwId);
	self:JoinPlayer(pPlayer, 1);
	
	Player:SetTempReviveFunc(pPlayer, {"Stage:OnDeath", pPlayer});
end

function BaseGame:StartGame()
	self.tbLock[1]:StartLock();
	return 0;
end

function BaseGame:DoLeaveGame(pPlayer, bReturn)
	for _, nPlayerId in ipairs(self.tbGamePlayers) do
		if nPlayerId == pPlayer.dwId then
			table.remove(self.tbGamePlayers, _);
			break;
		end
	end
	
	if bReturn and bReturn == 1 then
		pPlayer.ReturnToLastCity();
	end
	
	if #self.tbGamePlayers <= 0 then
		self:CloseGame();
	end
end

function BaseGame:OnLogout(pPlayer)
	self:DoLeaveGame(pPlayer);
end

function BaseGame:OnPlayerDeath(pPlayer)
	local bAlive = 0;
	for _, nPlayerId in ipairs(self.tbGamePlayers) do
		local pMember = KGameBase.GetPlayerById(nPlayerId);
		if pMember.GetMoveState() ~= Character.MOVE_STATE_ON_DEATH then
			bAlive = 1;
		end
	end 
	
	-- ȫ���������˳���ǰ�ؿ�
	if bAlive == 0 then
		Stage:CloseGame(self.nTeamId);
	end
end

function BaseGame:CloseGame(bReturn)
	self:SyncTargetInfo("");
	
	self:UnInitGame();
	
	if self.nEndTimerId then
		Timer:Close(self.nEndTimerId);
	end
	
	for _, nPlayerId in ipairs(self.tbGamePlayers) do
		local pPlayer = KGameBase.GetPlayerById(nPlayerId);
		
		if self.bFinishStage == 1 then
			KStage.SetRushLayer(pPlayer, self.nLayer);
		end
		
		if bReturn and bReturn == 1 then
			--pPlayer.LeaveTeam();
			pPlayer.ReturnToLastCity();
		end
	end
	
	Timer:Register(3 * Env.GAME_FPS, self.ResetMap, self, self.nMapId, self.nSceneId);
	
	Stage.tbGames[self.nTeamId] = nil;
	
	return 0;
end

function BaseGame:ResetMap(nMapId, nSceneId)
	KScene.ResetMap(nMapId, nSceneId);
	return 0;
end

function BaseGame:OnEvent(nEventType, ...)
	if self.EVENT_PROC[nEventType] and self[self.EVENT_PROC[nEventType]] then
		self[self.EVENT_PROC[nEventType]](self, ...);
	else
		print("Undefind EventType ", nEventType, ...);
	end
end

function BaseGame:GroupPlayerExcute(fnExcute)
	for _, nPlayerId in ipairs(self.tbGamePlayers) do
        local pPlayer = KGameBase.GetPlayerById(nPlayerId)
        if pPlayer then
            fnExcute(pPlayer);
        end
    end
end

function BaseGame:ExcuteScript(szCmd)
	Stage.tbExcuteTable = self;
	local fnExc = loadstring("local self = Stage.tbExcuteTable;"..szCmd);
	if fnExc then
		xpcall(fnExc, Lib.ShowStack);
	end
	Stage.tbExcuteTable = nil;
end

-- ͬ��ʣ��ʱ����Ϣ
function BaseGame:SyncTimeInfo(szTimeInfo, ...)
	local varLock;
	local nTimeFrame; -- ʱ��
	
	-- ������ȡ
	if #arg == 0 then varLock = -1;  
	else varLock = unpack(arg); end
	
	if type(varLock) ~= "number" then
		print("[Lua:BaseGame:BroadcastTimeInfo]varLock��Number");
		assert(false);
	end
	
	-- �������������ʱ�䣬û�������ûʱ��
	if (varLock ~= -1 and self.tbLock[varLock]) then
		nTimeFrame = self.tbLayerSetting.LOCK[varLock].nTime * Env.GAME_FPS;
	else
		nTimeFrame = (self.nEndTime - KGameBase.GetTime()) * Env.GAME_FPS;
	end
	
	self.szTimeInfo = szTimeInfo;  -- set self
	local fnExcute = function(pPlayer)
		local nSec = nTimeFrame / Env.GAME_FPS;
		--pPlayer.SysMsg(string.format(szTimeInfo, Lib:TimeDesc(nSec)));
		pPlayer.CallClientScript({"QClientScript.Mission:SetMissionTimeInfo", szTimeInfo, nTimeFrame});
	end
	self:GroupPlayerExcute(fnExcute);
end

function BaseGame:ShowNoticeMsg(szMsg)
	local fnExcute = function(pPlayer)
		pPlayer.SendNoticeMsg(szMsg);
	end
	self:GroupPlayerExcute(fnExcute);
end

-- ͬ����ʱս����Ϣ���������
function BaseGame:SyncTargetInfo(szInfo, ...)
	local varLock; -- ��ȡvarLock�� �ĸ���
	if #arg == 0 then varLock = -1;   -- û�в���
	else varLock = unpack(arg);	end -- ��ȡ��һ��
	
	self.nCurLock = varLock;
	
	self.szTargetInfo = szInfo;  -- ����targetInfo
	if (varLock ~= -1 and self.tbLock[varLock]) then  -- ���ڸ���
		local nCurrentNum = self.tbLock[varLock].nMultiNum; -- ��ǰɱ����
		local nInitNum = self.tbLock[varLock].nInitMultiNum; -- ��ɱ����
		szInfo = string.format("%s %d/%d", self.szTargetInfo, nInitNum - nCurrentNum, nInitNum);
	end
	
	local fnExcute = function (pPlayer)
		--pPlayer.SysMsg(szInfo);
		pPlayer.CallClientScript({"QClientScript.Mission:SetMissionTargetInfo", szInfo});
	end
	self:GroupPlayerExcute(fnExcute);
end

function BaseGame:SetTrapInvalid(nTrapTemplateId, nInvalid)
	
	local fnExcute = function (pPlayer)
		
		if type(nTrapTemplateId) == "table" then
			nTrapTemplateId = nTrapTemplateId[KUnify.MathRandom(1, #nTrapTemplateId)];
		end
		
		if not nInvalid or nInvalid == 1 then
			pPlayer.SetTrapInvalid(nTrapTemplateId);
		else
			pPlayer.RemoveTrapInvalid(nTrapTemplateId);
		end
	end
	
	self:GroupPlayerExcute(fnExcute);
end

function BaseGame:ReviveInfo(bWait, bUseItem, bReturn, nScene, ...)
	local fnExcute = function (pPlayer)
		Player:SetTempRevive(pPlayer, bWait, bUseItem, bReturn, nScene, unpack(arg));
	end
	self:GroupPlayerExcute(fnExcute);	
end

function BaseGame:NpcBubble(szGroup, szMsg, delay)
	local fnExcute = function (pPlayer)
	    local pOldMe = me;
	    me = pPlayer;
		for _, nId in pairs(self.tbNpcGroup[szGroup]) do
			Dialog:NpcBubble(nId, szMsg, delay * Env.GAME_FPS);
		end
	    me = pOldMe;
	end
	
	self:GroupPlayerExcute(fnExcute);
end

function BaseGame:MeBubble(szMsg, delay)
	
	local fnExcute = function (pPlayer)
	    local pOldMe = me;
	    me = pPlayer;
		Dialog:PlayerBubble(szMsg, delay * Env.GAME_FPS);
	    me = pOldMe;
	end
	
	self:GroupPlayerExcute(fnExcute);
end

function BaseGame:ClearPlayerBuff(nBuffId)
	local fnExcute = function (pPlayer)
		pPlayer.pBufferEffect.ClearBuff(nBuffId);
	end
	
	self:GroupPlayerExcute(fnExcute);
end

-- ��NPC�ӵ�����
function BaseGame:AddNpcInLock(pNpc, nLock)
	if not nLock or nLock <= 0 then
		return 0;
	end
	local tbTmp = pNpc.GetTempTable("Stage");
	tbTmp.nLock = nLock;
end

-- ��NPC�ӵ�����
function BaseGame:AddNpcInGroup(pNpc, szGroup)
	if not self.tbNpcGroup[szGroup] then
		self.tbNpcGroup[szGroup] = {};
	end
	if pNpc then
		table.insert(self.tbNpcGroup[szGroup], pNpc.dwId);
	end
end

-- ��npcˢ����ͬλ����
-- nNum: ����
-- tbIndex: npc������
function BaseGame:__AllocNpc(nNum, tbIndex, nLock, szGroup, nPropId, nLevel, szPointName)
	local pNpc;
	local tbNpcId = {};
	local nIndex;
	if #tbIndex == 1 then
		nIndex = tbIndex[1];
	end
	
	local tbNpcInfo;
	if nIndex then
	    tbNpcInfo = self.tbLayerSetting.NPC[nIndex];
	else
	    tbNpcInfo = self.tbLayerSetting.NPC[tbIndex[KUnify.MathRandom(#tbIndex)]];
	end
	
	local tbNpcT = Scene.tbNpcCfg[self.nMapId][tbNpcInfo.nTemplate];
	local tbNpc = {};
	tbNpc.tbPosList = tbNpcT.tbPosList;
	tbNpc.nTemplateId = tbNpcT.nTemplateId;
	tbNpc.nRegenerationTime = tbNpcT.nRegenerationTime;
	tbNpc.nNormalAI = tbNpcT.nNormalAI;
	tbNpc.nCount = nNum;
	
	local tbRetNpcs = Scene:_CallOneNpc(tbNpc, self.nSceneId, self.nMapId, nil, szPointName, self.nTeamId, szGroup);
	for _, pNpc in ipairs(tbRetNpcs) do
	    KCharacter.ResetNpcIntensity(pNpc, nPropId, nLevel);
	    self:AddNpcInLock(pNpc, nLock);
		self:AddNpcInGroup(pNpc, szGroup);
		table.insert(tbNpcId, pNpc.dwId);
		local tbTmp = pNpc.GetTempTable("Stage")
		tbTmp.tbStage = self;
	end
	
	return tbNpcId;
end

function BaseGame:__AddNpc(tbIndex, nNum, nLock, szGroup, szPointName, nTimes, nFrequency, szTimerName, nRemove)
	if not self.tbLayerSetting or not self.tbLayerSetting.NPC then
		return 0;
	end
	
	local tbNpcInfo = self.tbLayerSetting.NPC[tbIndex[1]];
	local nPropId = KCharacter.GetNpcPropId(tbNpcInfo.nTemplate);
	local nLevel = tbNpcInfo.nLevel;
	assert(nLevel);
	
	if not nRemove then
		nRemove = 1;
	end
	
	local tbNpcId = self:__AllocNpc(nNum, tbIndex, nLock, szGroup, nPropId, nLevel, szPointName)

    if nFrequency then
		for _, id in ipairs(self.tbAddNpcTimer[szTimerName].tbNpcId) do -- ɾ����һ�ֵ�npc
			local pNpc = KGameBase.GetNpcById(id);
			if pNpc and nRemove == 1 then
			    KGameBase.RemoveNpc(pNpc.dwId);
			end
		end
		if nTimes == 1 then
			self.tbAddNpcTimer[szTimerName].nTimerId = nil;
			self.tbAddNpcTimer[szTimerName].tbNpcId = tbNpcId;
		else
			self.tbAddNpcTimer[szTimerName].nTimerId = Timer:Register(nFrequency * Env.GAME_FPS, self.__AddNpc, self, tbIndex, nNum, nLock, szGroup, szPointName, nTimes - 1, nFrequency, szTimerName, nRemove);
			self.tbAddNpcTimer[szTimerName].tbNpcId = tbNpcId;
		end
	end
	
	return 0;
end

-- ���NPC
-- varIndex: nTemplateId or {id1,id2,id3...}, ������һ������һ��ģ��id
-- nNum: ˢ����
-- nLock
-- szGroup: ��ˢ������npc�������������
-- szPointName: ʹ����һ���ˢ��
-- nTimes, nFrequency, szTimerName: ѭ��ˢ���ã�����Ϊ�������������ˢһ�Σ�timer����	
function BaseGame:AddNpc(varIndex, nNum, nLock, szGroup, szPointName, nTimes, nFrequency, szTimerName, nRemove)
	if (nTimes or nFrequency or szTimerName) and not (nTimes > 1 and nFrequency > 0 and szTimerName) then
		assert(false);
	end
	
	if type(varIndex) == "number" then
		varIndex = {varIndex};
	end
	for _, id in ipairs(varIndex) do
		local tbNpcInfo = self.tbLayerSetting.NPC[id];
		assert(tbNpcInfo);
	end
	
	if nFrequency and not self.tbAddNpcTimer[szTimerName] then
		self.tbAddNpcTimer[szTimerName] = {};
		self.tbAddNpcTimer[szTimerName].tbNpcId = {};
	end

	self:__AddNpc(varIndex, nNum, nLock, szGroup, szPointName, nTimes, nFrequency, szTimerName, nRemove);
end

-- ɾ���ض����NPC
function BaseGame:DelNpc(szGroup, szTimerName)
	if not self.tbNpcGroup[szGroup] then
		return 0;
	end
	for _, nId in pairs(self.tbNpcGroup[szGroup]) do
		local pNpc = KGameBase.GetNpcById(nId);
		if pNpc and pNpc.IsDead() ~= 1 then
			KGameBase.RemoveNpc(pNpc.dwId);
		end
	end
	self.tbNpcGroup[szGroup] = nil;
	
	if szTimerName and self.tbAddNpcTimer[szTimerName] then
		Timer:Close(self.tbAddNpcTimer[szTimerName].nTimerId);
	end
	
	self.tbDelRegenerateNpc[szGroup] = 1;
end


-- ������Ϣ
function BaseGame:BlackMsg(szMsg, delay)
	if delay and delay > 0 then
		Timer:Register(delay, self.BlackMsg, self, szMsg);
		return;
	end
	
	local fnExcute = function(pPlayer)
		Dialog:SendBlackBoardMsg(pPlayer, szMsg)
	end
	
	self:GroupPlayerExcute(fnExcute);
	
	return 0;
end
