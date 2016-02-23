
Include("script/mission/mission.lua");
Include("script/mission/baselock.lua")
Include("script/mission/tower/tower_def.lua")
-- ����

Tower.BaseGame = Mission:New();
local BaseGame = Tower.BaseGame;
local tbEventLock = Lib:NewClass(Lock.tbBaseLock);

BaseGame.EVENT_PROC  =
{
    [Tower.DO_SCRIPT]	= "ExcuteScript",
    [Tower.ADD_NPC]		= "AddNpc",
    [Tower.DEL_NPC]		= "DelNpc",
	[Tower.BLACK_MSG]	= "BlackMsg",
	[Tower.NPC_BUBBLE] 	= "NpcBubble",
	[Tower.TARGET_INFO]	= "SyncTargetInfo",
	[Tower.TIME_INFO] = "SyncTimeInfo"
};

function tbEventLock:InitEventLock(tbTower, nTime, nMultiNum, tbStartEvent, tbUnLockEvent)
	self:InitLock(nTime, nMultiNum);
	self.tbTower 	= tbTower;
	self.tbUnLockEvent 	= tbUnLockEvent;
	self.tbStartEvent 	= tbStartEvent;
end

function tbEventLock:OnUnLock()
	if self.tbTower and self.tbUnLockEvent then
		for i = 1, #self.tbUnLockEvent do
			self.tbTower:OnEvent(unpack(self.tbUnLockEvent[i]));
		end
	end
	local tbTower = self.tbTower;
	
	if tbTower and tbTower.bFinishLayer == 1 then
		if tbTower.bAllFinish and tbTower.bAllFinish == 1 then
			-- ȫ������
			Tower:OnAllFinish(tbTower.nOwnerId);
		else
			Tower:GoNextLayer(tbTower.nOwnerId);
		end
	end
end

function tbEventLock:OnStartLock()
	if self.tbTower and self.tbStartEvent then
		for i = 1, #self.tbStartEvent do
			self.tbTower:OnEvent(unpack(self.tbStartEvent[i]));
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

function BaseGame:InitGame(nMapId, nSceneId, nOwnerId, tbTowerSetting)
	self.nMapId = nMapId;
    self.nSceneId = nSceneId;
	self.nOwnerId = nOwnerId;
	self.nEnemyNum = tbTowerSetting.nEnemyNum;
    self.bOver = 0; -- ������־
    self.tbLock = {};
    self.tbNpcGroup = {};
    self.tbAddNpcTimer = {};
	self:Open();
	
	self.tbTowerSetting = tbTowerSetting;
	for i, tbLockSetting in pairs(tbTowerSetting.LOCK) do
		self.tbLock[i] = Lib:NewClass(tbEventLock);
		self.tbLock[i].nLockId = i;
		self.tbLock[i]:InitEventLock(self, tbLockSetting.nTime * Env.GAME_FPS, tbLockSetting.nNum, tbLockSetting.tbStartEvent, tbLockSetting.tbUnLockEvent);
	end
	for i, tbLockSetting in ipairs(tbTowerSetting.LOCK) do -- ��֤����˳��
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
	self.nEndTime = KGameBase.GetTime() + tbTowerSetting.nTimeLimit;
	
	local nEndTimerId = Timer:Register(tbTowerSetting.nTimeLimit * Env.GAME_FPS, self.OnTimeOut, self);
	self.nEndTimerId = nEndTimerId;
end

function BaseGame:OnTimeOut()
	local pPlayer = KGameBase.GetPlayerById(self.nOwnerId);
	Tower:SetFailedFlag(pPlayer);
	self:CloseGame(1);
	return 0;
end

function BaseGame:StartGame()
	self.tbLock[1]:StartLock();
	return 0;
end

function BaseGame:CloseGame(bReturn)
	self:SyncTargetInfo("");
	
	self:UnInitGame();
	
	if self.nEndTimerId then
		Timer:Close(self.nEndTimerId);
	end
	
	local pPlayer = KGameBase.GetPlayerById(self.nOwnerId);
	
	Tower:SetRewardInfo(pPlayer);
	
	Tower.tbGames[pPlayer.dwId] = nil;
	
	if bReturn and bReturn == 1 then
		local nMapId = pPlayer.dwSceneTemplateId;
		local nSceneId = pPlayer.dwSceneId;
		pPlayer.CallClientScript({"QClientScript.Mission:SetMissionExInfo", ""});
		pPlayer.ReturnToLastCity();
		Timer:Register(3 * Env.GAME_FPS, self.ResetMap, self, nMapId, nSceneId);
		
		Tower.tbFirstEnter[pPlayer.dwId] = nil;
		Tower.tbTotalExp[pPlayer.dwId] = nil;
	end
	
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

function BaseGame:PlayerExcute(fnExcute)
	local pPlayer = KGameBase.GetPlayerById(self.nOwnerId)
	if pPlayer then
		fnExcute(pPlayer);
	end
end

function BaseGame:ExcuteScript(szCmd)
	Tower.tbExcuteTable = self;
	local fnExc = loadstring("local self = Tower.tbExcuteTable;"..szCmd);
	if fnExc then
		xpcall(fnExc, Lib.ShowStack);
	end
	Tower.tbExcuteTable = nil;
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
		nTimeFrame = self.tbTowerSetting.LOCK[varLock].nTime * Env.GAME_FPS;
	else
		nTimeFrame = (self.nEndTime - KGameBase.GetTime()) * Env.GAME_FPS;
	end
	
	self.szTimeInfo = szTimeInfo;  -- set self
	local fnExcute = function(pPlayer)
		local nSec = nTimeFrame / Env.GAME_FPS;
		--pPlayer.SysMsg(string.format(szTimeInfo, Lib:TimeDesc(nSec)));
		pPlayer.CallClientScript({"QClientScript.Mission:SetMissionTimeInfo", szTimeInfo, nTimeFrame});
	end
	self:PlayerExcute(fnExcute);
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
	self:PlayerExcute(fnExcute);
end

function BaseGame:OnLogin(pPlayer)
end

function BaseGame:OnLogout(pPlayer)
end

function BaseGame:CloseTimeInfo(pPlayer)
	pPlayer.CallClientScript({"YoulongApp.UI.Controller.QUIClientScript:BroadcastMissionComplete", "UI_TASKTIPS", "Begin", "�����ر�"});
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
	self:PlayerExcute(fnExcute);
end

-- ��NPC�ӵ�����
function BaseGame:AddNpcInLock(pNpc, nLock)
	if not nLock or nLock <= 0 then
		return 0;
	end
	local tbTmp = pNpc.GetTempTable("Tower");
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
	    tbNpcInfo = self.tbTowerSetting.NPC[nIndex];
	else
	    tbNpcInfo = self.tbTowerSetting.NPC[tbIndex[KUnify.MathRandom(#tbIndex)]];
	end
	
	local tbNpcT = Scene.tbNpcCfg[self.nMapId][tbNpcInfo.nTemplate];
	print("..tbNpcT",self.nMapId,tbNpcInfo.nTemplate);
	local tbNpc = {};
	tbNpc.tbPosList = tbNpcT.tbPosList;
	tbNpc.nTemplateId = tbNpcT.nTemplateId;
	tbNpc.nRegenerationTime = tbNpcT.nRegenerationTime;
	tbNpc.nNormalAI = tbNpcT.nNormalAI;
	tbNpc.nCount = nNum;
	
	local tbRetNpcs = Scene:_CallOneNpc(tbNpc, self.nSceneId, self.nMapId, nil, szPointName);
	for _, pNpc in ipairs(tbRetNpcs) do
	    KCharacter.ResetNpcIntensity(pNpc, nPropId, nLevel);
	    self:AddNpcInLock(pNpc, nLock);
		self:AddNpcInGroup(pNpc, szGroup);
		table.insert(tbNpcId, pNpc.dwId);
		local tbTmp = pNpc.GetTempTable("Tower")
		tbTmp.tbTower = self;
	end
	
	return tbNpcId;
end

function BaseGame:__AddNpc(tbIndex, nNum, nLock, szGroup, szPointName, nTimes, nFrequency, szTimerName, nRemove)
	if not self.tbTowerSetting or not self.tbTowerSetting.NPC then
		return 0;
	end
	
	local tbNpcInfo = self.tbTowerSetting.NPC[tbIndex[1]];
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
		local tbNpcInfo = self.tbTowerSetting.NPC[id];
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
	self:PlayerExcute(fnExcute);
	
	return 0;
end