-- ����������
Include("script/mission/activity/setting/activitysetting.lua")
Activity.tbActivities = {}
Activity.tbPlayerProgress = {} -- ��ҵ�ǰ���ȣ����ĸ������
Activity.KIN_ACT_SET_START_INDEX = 1000;          -- ��������������1000��ʼ
Activity.KIN_ACT_MAX_NUM = 6;                     -- ���ɴ����ļ���
Activity.DYNAMIC_KIN_ACT_SET_START_INDEX = 10000; -- ��̬�����ļ�������������10000��ʼ
Activity.nCurrDynamicKinActSetIndex = Activity.DYNAMIC_KIN_ACT_SET_START_INDEX;
Activity.tbKinActivitySettingIndexMap = {}
Activity.tbBonfireInfo = {};	--����״̬
Activity.tbManHuangZhiDiBoss = {
	[353] = {bossCount = 0},
	[354] = {bossCount = 0},
	[355] = {bossCount = 0},
	[356] = {bossCount = 0},
	}; --����֮��boss����
local tbManHuangZhiDiBoss = Activity.tbManHuangZhiDiBoss;
Activity.tbMPJJAwardScore = { 
	[1] = 30,	--�ھ����ֽ���
	[2]	= 25,	--�Ǿ����ֽ���
	[4] = 20,	--��ǿ���ֽ���
	[8] = 15,	--��ǿ���ֽ���
	[16] = 10,	--ʮ��ǿ���ֽ���
}; 
local tbMPJJAwardScore = Activity.tbMPJJAwardScore or {};

-- ս����
function Activity:c2s_JoinZbt(pPlayer)
  Pet:GetDownRide(pPlayer);	-- ����
  Activity:RequestEnterActivity(pPlayer, 2, 2);
  DailyTasks:commitTaskValue(pPlayer,"c2s_JoinZbt",DailyTasks.TYPE_JOIN_ACTIVITY,1);
end
-- ��ħս��
function Activity:c2s_JoinBattle(pPlayer)
  local nCount = Player.tbDegree:GetDegree(pPlayer, "JoinSMZC")
	if nCount == 0 then
		pPlayer.SendBlackMsg(Lang.mission.str2[Lang.Idx]);
		return
	end
	
	Player.tbDegree:ReduceDegree(pPlayer, "JoinSMZC", 1)
	
  Pet:GetDownRide(pPlayer);	-- ����
	--KGameBase.CenterExecute{"Activity:ApplyJoinBattleField_GC", pPlayer.dwId, self.tbBattleFieldMaps};
	self:DoJoinBattleField(pPlayer.dwId, self.tbBattleFieldMaps[1])
	--Activity:RequestEnterActivity(pPlayer, 20, 1);
	--self:JoinActivity(pPlayer.dwId, 20, 3);
  DailyTasks:commitTaskValue(pPlayer,"c2s_JoinBattle",DailyTasks.TYPE_JOIN_ACTIVITY,1);
end

function Activity:c2s_JoinMHZD(pPlayer, nIndex)
	Pet:GetDownRide(pPlayer);	-- ����
	
	local nStartMapId = 353;
	local nTargetMapId = nStartMapId + nIndex - 1;
	if nTargetMapId > 356 then
		pPlayer.SendBlackMsg(Lang.mission.str3[Lang.Idx]);
		return;
	end
	KGameBase.CenterExecute{"Activity:ApplyJoinMHZD_GC", pPlayer.dwId, nTargetMapId};
	
	--ͳ�Ƶ�  ldy
	local szStr = string.format("name=%s","JoinMHZD");
	pPlayer.pPlayerPurse.LogMoney(Item.EM_MONEY_COIN, 0,68,szStr);

	DailyTasks:commitTaskValue(pPlayer,"c2s_JoinMHZD",DailyTasks.TYPE_JOIN_ACTIVITY,1);
	
end

function Activity:c2s_SyncMHZD(pPlayer)
	pPlayer.CallClientScript({"YoulongApp.UI.Controller.QUIClientScript:SetCurrentBossCount", self.tbManHuangZhiDiBoss[353].bossCount, self.tbManHuangZhiDiBoss[354].bossCount, self.tbManHuangZhiDiBoss[355].bossCount, self.tbManHuangZhiDiBoss[356].bossCount});
end

function Activity:DoJoinBattleField(nPlayerId, nMapId)
	local pPlayer = KGameBase.GetPlayerById(nPlayerId);
	
	if not pPlayer then
		return;
	end
	
	local tbStartIdx = self.tbStartSteps[nMapId];
	assert(tbStartIdx);
	
	Activity:RequestEnterActivity(pPlayer, tbStartIdx.nActivityIndex, tbStartIdx.nStepIndex);
	
	
	--ͳ�Ƶ�  ldy
	local szStr = string.format("name=%s","JoinBattleField");
	pPlayer.pPlayerPurse.LogMoney(Item.EM_MONEY_COIN, 0,68,szStr);
	
	
end

function Activity:DoJoinMHZD(nPlayerId, nMapId, isFull)
	local pPlayer = KGameBase.GetPlayerById(nPlayerId);
	
	if not pPlayer then
		return;
	end
	
	if isFull ~= 0 and pPlayer.GetVipLevel() < 3 then
		pPlayer.SendBlackMsg(Lang.mission.str4[Lang.Idx]);
		return;
	end
	
	local tbStartIdx = self.tbStartSteps[nMapId];
	assert(tbStartIdx);
	
	Activity:RequestEnterActivity(pPlayer, tbStartIdx.nActivityIndex, tbStartIdx.nStepIndex);
	
	--ͳ�Ƶ�  ldy
	local szStr = string.format("name=%s","JoinMHZD");
	pPlayer.pPlayerPurse.LogMoney(Item.EM_MONEY_COIN, 0,68,szStr);
	
end

-- ����boss
function Activity:c2s_JoinBoss(pPlayer)
	--pPlayer.SysMsg("�μ�����boss");
	Pet:GetDownRide(pPlayer);	-- ����
	Activity:RequestEnterActivity(pPlayer, 15, 1);
	--self:JoinActivity(pPlayer.dwId, 15, 2);
	
	--ͳ�Ƶ�  ldy
	local szStr = string.format("name=%s","JoinBoss");
	pPlayer.pPlayerPurse.LogMoney(Item.EM_MONEY_COIN, 0,68,szStr);
	DailyTasks:commitTaskValue(pPlayer,"c2s_JoinBoss",DailyTasks.TYPE_JOIN_ACTIVITY,1);
	
end
-- ս����˫(���ɾ���)
function Activity:c2s_Mpjj(pPlayer)
	--pPlayer.SysMsg("�μ����ɾ���");
	local nCount = Player.tbDegree:GetDegree(pPlayer, "JoinZSWS")
	if nCount == 0 then
		pPlayer.SendBlackMsg(Lang.mission.str5[Lang.Idx]);
		return
	end
	
	Player.tbDegree:ReduceDegree(pPlayer, "JoinZSWS", 1)
	
	Pet:GetDownRide(pPlayer);	-- ����
	Activity:RequestEnterActivity(pPlayer, 10, 1);
	--self:JoinActivity(pPlayer.dwId, 10, 1);
	
	--ͳ�Ƶ�  ldy
	local szStr = string.format("name=%s","Mpjj");
	pPlayer.pPlayerPurse.LogMoney(Item.EM_MONEY_COIN, 0,68,szStr);

	DailyTasks:commitTaskValue(pPlayer,"c2s_Mpjj",DailyTasks.TYPE_JOIN_ACTIVITY,1);
	
end

--��������
function Activity:c2s_EnterBonfireActivity(pPlayer, nActivityIndex, nKinId)
	if not nActivityIndex then
		nActivityIndex = 1001;
	end
	
	if not nKinId then
		nKinId = pPlayer.GetKinId();
	end
	
    if (pPlayer.GetKinId() ~= nKinId) then
        return;
    end
	   
    local tbSettingIndexMap = self.tbKinActivitySettingIndexMap[nKinId];
    local nActualActivityIndex = tbSettingIndexMap[nActivityIndex];
		
	if self:IfCanEnterActivity(pPlayer, nActualActivityIndex, nStepIndex) ~= 1 then
		return;
	end
	
	if self.tbBonfireInfo[nKinId] == nil then
		self.tbBonfireInfo[nKinId] = {onGoing = 1, sendTorch = 0, useTorch = 0, mapId = 0, npcId = 0, tbPos = {0, 0, 0}};
	end
	
	local tbBonfire = self.tbBonfireInfo[nKinId];

	--������Ϣ
	local tbPlayerKinInfo = GetPlayerKinInfo(pPlayer.dwId);
	--����������峤
	if tbBonfire.sendTorch == 0 and pPlayer.dwId == tbPlayerKinInfo.dwKinMasterID then
		if pPlayer.pItem.CountFreeBagCell() <= 0 then
			pPlayer.SysMsg(Lang.mission.str6[Lang.Idx]);
		else
			tbBonfire.sendTorch = 1;
			local pItem = KItem.AddPlayerItem(pPlayer, 18, 1, 267);	--GDPL
			pPlayer.pItem.SetItemTimeout(pItem, 24 * 60 - Lib:GetLocalDayTime() / 60, 0);
			KChat.BroadcastKinNoticeMsg(nKinId, string.format(Lang.mission.str7[Lang.Idx],pPlayer.szName));
		end
	end
	
	KGameBase.CenterExecute{"Activity:UpdateBonfireInfo_GC", nKinId, tbBonfire};
	
	--ûʹ��
	if tbBonfire.useTorch == 0 then
		pPlayer.SendBlackMsg(Lang.mission.str8[Lang.Idx]);
		return;
	end
	
	local nMapId = pPlayer.dwSceneTemplateId;
	if KScene.GetSceneTypeName(nMapId) ~= "city" then
		pPlayer.SendBlackMsg(Lang.mission.str9[Lang.Idx]);
		return;
	end
	
	local tbPlayerPos = pPlayer.GetPosition();
	local tbPos = tbBonfire.tbPos;
	local distance = KGameBase.GetDistance(tbPlayerPos.nX, tbPlayerPos.nY, tbPos[1], tbPos[2])
	if distance <= (12 * Scene.CELL_LENGHT) ^ 2 then
		pPlayer.SendBlackMsg(Lang.mission.str10[Lang.Idx]);
		return;
	end
	
	pPlayer.TeleportTo(tbBonfire.mapId, tbPos[1], tbPos[2], tbPos[3]);
	
	--ͳ�Ƶ�  ldy
	local szStr = string.format("name=%s","BonfireActivity");
	pPlayer.pPlayerPurse.LogMoney(Item.EM_MONEY_COIN, 0,68,szStr);
	
	DailyTasks:commitTaskValue(pPlayer,"c2s_EnterBonfireActivity",DailyTasks.TYPE_JOIN_ACTIVITY,1);
end

--?gs KItem.AddPlayerItem(me, 18, 1, 267);

--ͬ��������Ϣ��
function Activity:UpdateBonfireInfo_GS(nKinId, tbBonfireInfo)
	self.tbBonfireInfo[nKinId] = Lib:CopyTBN(tbBonfireInfo);
end

--��ȡ��������״̬(0û�н�������1������)
function Activity:GetBonfireStatus(pPlayer)

	if pPlayer == nil then
		return 0;
	end
	
	--[[local dwNow = KGameBase.GetTime();
	local quitTime = pPlayer.GetLastQuitTongTime();
	if Lib:GetLocalDay(dwNow) == Lib:GetLocalDay(quitTime) then
		return 0;
	end--]]
	
	local nKinId = pPlayer.GetKinId();
	if self.tbBonfireInfo[nKinId] == nil then
		return 0;
	end
	
	local tbBonfire = self.tbBonfireInfo[nKinId];
	local tbPos = pPlayer.GetPosition();
	
	if tbPos.dwSceneId ~= tbBonfire.mapId or tbBonfire.useTorch == 0 then
		return 0;
	end
	
	local tbBonfirePos = tbBonfire.tbPos;
	local distance = KGameBase.GetDistance(tbPos.nX, tbPos.nY, tbBonfirePos[1], tbBonfirePos[2])
	if distance > (12 * Scene.CELL_LENGHT) ^ 2 then
		return 0;
	end
	
	return 1;
end

--
function Activity:UpdateManHuangZhiDi_GS(nScenId, tbManHuangZhiDi)
	self.tbManHuangZhiDiBoss[nScenId] = Lib:CopyTBN(tbManHuangZhiDi);
end

--����ʣ��ʱ��
function Activity:GetKinActivityLeftTime(nKinId, nKinActivityIndex)
	
	if Activity.tbKinActivitySettingIndexMap == nil or Activity.tbKinActivitySettingIndexMap[nKinId] == nil then
		print("��ȡ����ʣ��ʱ��ʧ��");
		return 0;
	end;
	
	local tbKinIdMap = Activity.tbKinActivitySettingIndexMap[nKinId];
	local nActualActivityIndex = tbKinIdMap[nKinActivityIndex];

	local tbActivity    = Activity.ActivitySetting[nActualActivityIndex];
	local nCurCloseTime = Lib:GetSecByTimeTable(tbActivity.tbOpenTimes[1][2]);
	local curDayTime = KGameBase.GetTime();
	local leftTime = nCurCloseTime - curDayTime;

	return leftTime;
end

function Activity:c2s_EnterKinPTSY(pPlayer, nKinId)
	if not nKinId then
		nKinId = pPlayer.GetKinId();
	end
	self:c2s_EnterKinActivity(pPlayer, 1002, nKinId);
	
	--ͳ�Ƶ�  ldy
	local szStr = string.format("name=%s","KinPTSY");
	pPlayer.pPlayerPurse.LogMoney(Item.EM_MONEY_COIN, 0,68,szStr);
	DailyTasks:commitTaskValue(pPlayer,"c2s_EnterKinPTSY",DailyTasks.TYPE_JOIN_ACTIVITY,1);
end

function Activity:c2s_EnterKinActivity(pPlayer, nActivityIndex, nKinId)
    if (pPlayer.GetKinId() ~= nKinId) then
        return;
    end
        
    local tbSettingIndexMap = self.tbKinActivitySettingIndexMap[nKinId];
    local nActualActivityIndex = tbSettingIndexMap[nActivityIndex];
		
	if self:IfCanEnterActivity(pPlayer, nActualActivityIndex, nStepIndex) ~= 1 then
		return;
	end
	
	self:DoEnterActivity(pPlayer, nActualActivityIndex);

	DailyTasks:commitTaskValue(pPlayer,"c2s_EnterKinActivity",DailyTasks.TYPE_JOIN_ACTIVITY,1);
end

function Activity:IsOpenTimeToday(tbOpenTime)
	assert(type(tbOpenTime[1]) == "table" and type(tbOpenTime[2]) == "table")
	local tbStartTime = tbOpenTime[1];
	
	local tNow = KGameBase.GetTime();
	local tbNowTime = Lib:GetTimeTable(tNow);
	
	-- ���ڼ��Բ���
	if tbStartTime.wday and tbStartTime.wday ~= tbNowTime.wday then
		return 0;
	end
	
	-- ���ڶԲ���
	if tbStartTime.year and (tbStartTime.year ~= tbNowTime.year 
		or tbStartTime.month ~= tbNowTime.month or tbStartTime.day ~= tbNowTime.day) then
		return 0;
	end
	
	if not tbStartTime.year and tbStartTime.month and (tbStartTime.month ~= tbNowTime.month 
		or tbStartTime.day ~= tbNowTime.day) then
		return 0;
	end
	
	if not tbStartTime.year and not tbStartTime.month and tbStartTime.day and ( tbStartTime.day ~= tbNowTime.day ) then
		return 0;
	end
	
	return 1;
end

-- �Ƿ��ڻʱ����
function Activity:IsOpenTime(tbOpenTime)
	assert(type(tbOpenTime[1]) == "table" and type(tbOpenTime[2]) == "table")
	local tbStartTime = tbOpenTime[1];
	local tbEndTime = tbOpenTime[2];
	
	local tNow = KGameBase.GetTime();
	
	-- �Ƿ��ڽ����л
	if self:IsOpenTimeToday(tbOpenTime) ~= 1 then
		return 0;
	end
	
	-- ���ʱ��
	local nStartTime = Lib:GetSecByTimeTable(tbStartTime);		-- ���ʼʱ���
	local nEndTime = Lib:GetSecByTimeTable(tbEndTime);			-- �����ʱ���
	
	if tNow >= nStartTime and tNow <= nEndTime then
		return 1;
	end
	
	return 0;
end

function Activity:RequestEnterActivity(pPlayer, nActivityIndex, nStepIndex)   
	local tbActivity = Activity.ActivitySetting[nActivityIndex];  -- �����
	local tbTargetStep = tbActivity.STEP[nStepIndex];
	if tbTargetStep == nil then
		 print("Wrong activiy step index", nStepIndex);
		 return 0;
	end
	
	local tNow = KGameBase.GetTime();
	local nStartTime = nil;
	
	for _, tbOpenTime in pairs(tbActivity.tbOpenTimes) do
		if self:IsOpenTime(tbOpenTime) == 1 then
			nStartTime = Lib:GetSecByTimeTable(tbOpenTime[1]);
			break;
		end
	end

	if nStartTime and tbActivity.nReadyStartTime and tNow < nStartTime + tbActivity.nReadyStartTime then
		pPlayer.SendBlackMsg(Lang.mission.strr11[Lang.Idx]);
		return 0;
	end
	
	if self:IfCanEnterActivity(pPlayer, nActivityIndex, nStepIndex) ~= 1 then
		return;
	end
	
	self:DoEnterActivity(pPlayer, nActivityIndex);
end

function Activity:DoEnterActivity(pPlayer, nActivityIndex)
	local tbActivity = self.ActivitySetting[nActivityIndex];
	local tbEnterPos = tbActivity.tbEnterPos;
	
	-- �����
	pPlayer.LeaveTeam();
	
	-- ���͵������
	local nCopyIndex = 0;
	if tbEnterPos.nCopyIndex ~= nil then
	    nCopyIndex = tbEnterPos.nCopyIndex;
	end
	local nRandomIndex = KUnify.MathRandom(1, #tbEnterPos.tbPos);
	local tbPos = tbEnterPos.tbPos[nRandomIndex];
	pPlayer.TeleportTo(tbEnterPos.nMapId, tbPos[1], tbPos[2], tbPos[3], 0, nCopyIndex);
	
	Activity:OnEnterActivity(pPlayer, nActivityIndex)
end

function Activity:OnEnterActivity(pPlayer, nActivityIndex)
    pPlayer.pTask.SetTask(5000, 1, nActivityIndex);
end

function Activity:IsKinActivity(nActivitySettingIndex)
    if nActivitySettingIndex >= Activity.KIN_ACT_SET_START_INDEX and nActivitySettingIndex < (Activity.KIN_ACT_SET_START_INDEX + Activity.KIN_ACT_MAX_NUM) then
        return 1;
    else
        return 0;
    end
end

function Activity:OnEnterScene(nCharacterId)
	local pPlayer = KGameBase.GetPlayerById(nCharacterId);
	if not pPlayer then
		return;
	end
	
	local nMapId = pPlayer.dwSceneTemplateId;
	
	local szSceneType = KScene.GetSceneTypeName(nMapId);
	
	if szSceneType ~= "activity" and szSceneType ~= "activity_zb" then
		return;
	end
	
	-- ���͵�׼����ʱ�ٲμӻ
	if szSceneType == "activity_zb" then
		local tbStartStep = self.tbStartSteps[nMapId];
		assert(tbStartStep);
		
		if self:IsKinActivity(tbStartStep.nActivityIndex) == 1 then   -- �ض������ڵ�����Ϊ����
		    local nKinId = pPlayer.GetKinId();
		    local tbSettingIndexMap = self.tbKinActivitySettingIndexMap[nKinId];
			local nActualActivityIndex = tbSettingIndexMap[tbStartStep.nActivityIndex];
			Activity:JoinActivity(nCharacterId, nActualActivityIndex, tbStartStep.nStepIndex);
		else
		    Activity:JoinActivity(nCharacterId, tbStartStep.nActivityIndex, tbStartStep.nStepIndex);
		end
	end
	
	local tbCurActivity = self.tbPlayerProgress[nCharacterId];
	if tbCurActivity ~= nil then
		local tbActivity = self.tbActivities[tbCurActivity.nActivityIndex]
		if tbActivity ~= nil and tbActivity.tbSteps[tbCurActivity.nStepIndex] ~= nil then
			tbActivity.tbSteps[tbCurActivity.nStepIndex]:OnEnterActivityScene(nCharacterId)
	    end
    end
end

function Activity:CreateActivity(nActivityIndex)
	if self.ActivitySetting[nActivityIndex] == nil then
		print("Wrong activity index ",  nActivityIndex)
		return;
    end
    if self.tbActivities[nActivityIndex] ~= nil then
    	return;
    end
    
    -- �����µĻ����
    local tbActivity = self.ActivitySetting[nActivityIndex]
	local nStartIndex = tbActivity.nStartStep;
	assert(nStartIndex);
    local tbSteps = {}
    for index, tbStepSetting in pairs(tbActivity.STEP) do
    	local tbNewStep = Activity.ACTSTEP_FACTORY:Create(tbStepSetting.Type)
    	tbNewStep:Init(tbStepSetting, nActivityIndex, index)
    	tbSteps[index] = tbNewStep
    end
    
    -- ���ݻ�����������֯������
    for index, tbStepSetting in pairs(tbActivity.STEP) do
        for i = 1, #tbStepSetting.NextSteps do
        	tbSteps[index].tbNextSteps[#tbSteps[index].tbNextSteps + 1] = tbSteps[tbStepSetting.NextSteps[i]]
        end 
    end
    
    local tbActivityData = {}
    tbActivityData.tbSteps = tbSteps
    tbActivityData.tbStartStep = tbSteps[nStartIndex];
    tbActivityData.szActivityName = tbActivity.ActivityName
    self.tbActivities[nActivityIndex] = tbActivityData
    
    print("..create activity["..self.ActivitySetting[nActivityIndex].ActivityName.."]")
end

function Activity:CreateAllActivities()
	for nActivityIndex, tbActivity in pairs(self.ActivitySetting) do
	    if self:IsKinActivity(nActivityIndex) == 0 then  --������̬����
	        self:CreateActivity(nActivityIndex)
	    end
    end
    return 0
end

function Activity:GetPrepareTime(nActivityIndex)
	local tbActivity = self.ActivitySetting[nActivityIndex];  -- ����
	assert(tbActivity);
	
	return tbActivity.nPrepareTime;
end

function Activity:IfCanEnterActivity(pPlayer, nActivityIndex, nStepIndex)
    if not self.ActivitySetting[nActivityIndex] then
		    return 0;
    end
    
	local tbActivity = self.ActivitySetting[nActivityIndex];  -- ����
	
	if tbActivity.nRequireLevel ~= nil then  -- ���ȼ�����
		if pPlayer.GetLevel() < tbActivity.nRequireLevel then
			pPlayer.SysMsg(string.format(Lang.mission.strr12[Lang.Idx],tbActivity.nRequireLevel,tbActivity.ActivityName));
			return 0;
		end
	end
	
	assert(tbActivity.tbOpenTimes);
	local tNow = KGameBase.GetTime();
	local nStartTime;
	
	for _, tbOpenTime in pairs(tbActivity.tbOpenTimes) do
		if self:IsOpenTime(tbOpenTime) == 1 then
			nStartTime = Lib:GetSecByTimeTable(tbOpenTime[1]);
			break;
		end
	end
	
	if not nStartTime then
		pPlayer.SendBlackMsg(Lang.mission.strr13[Lang.Idx]);
		return 0;
	end

	if tbActivity.nPrepareTime and tNow - nStartTime > tbActivity.nPrepareTime then
		pPlayer.SendBlackMsg(Lang.mission.strr14[Lang.Idx]);
		return 0;
	end

	return 1;
end 

-- �����߼�ID, ���ţ������,�Ƿ��¼λ��
function Activity:JoinActivity(nPlayerId, nActivityIndex, nStepIndex, NeedTransport)
	local nJoin = 0;
	
	if self.tbActivities[nActivityIndex] == nil then
		print("..activity index is not exist["..self.nActivityIndex.."] check avtivity configure");
    	self:CreateActivity(nActivityIndex)
    end

    local pPlayer = KGameBase.GetPlayerById(nPlayerId)
    if self.ActivitySetting[nActivityIndex] == nil or pPlayer == nil then
    	print("..player is not exist!");
		return 0;
    end
	
	--[[
    local nTeamId = pPlayer.GetTeamId()
    if nTeamId > 0 then
    	if pPlayer.IsCaptain() ~= 1 then  -- ֻ�жӳ��ܱ����μӻ
    		pPlayer.SysMsg("ֻ�жӳ��ܱ����μӻ");
    		return
        end
    end
    ]]--
	
    local tbActivity = self.ActivitySetting[nActivityIndex];  -- ����
    local tbActivityData = self.tbActivities[nActivityIndex];  -- �����
	
    assert(tbActivity.tbOpenTimes);
	local nIsOpenTime = 0;
	
	for _, tbOpenTime in pairs(tbActivity.tbOpenTimes) do
		if self:IsOpenTime(tbOpenTime) == 1 then
			nIsOpenTime = 1;
			break;
		end
	end
	
	assert(nIsOpenTime == 1);
	
	if tbActivity.nRequireLevel ~= nil then  -- ���ȼ�����
		if pPlayer.GetLevel() < tbActivity.nRequireLevel then
			pPlayer.SysMsg(string.format(Lang.mission.strr15[Lang.Idx],tbActivity.nRequireLeve,tbActivity.ActivityName));
			return 0;
		end
	end

	local tbTargetStep = tbActivityData.tbSteps[nStepIndex]
	if tbTargetStep == nil then
		print("..Wrong activiy step index", nStepIndex);
		return 0;
	end
	
	if tbTargetStep.IsOpen == 1 then
		if self.tbPlayerProgress[pPlayer.dwId] ~= nil then
			tbTargetStep:KickPlayerAnyWhere(pPlayer.dwId);
		end
		
		nJoin = tbTargetStep:JoinPlayer(pPlayer.dwId, 0, NeedTransport);
	end
	
	if nJoin == 1 then
		self:OnJoinActivity(pPlayer, nActivityIndex, nStepIndex);
	end
	
	return nJoin;
end

function Activity:DestroyKinActivities(nKinId)
    local tbKinIdMap = Activity.tbKinActivitySettingIndexMap[nKinId];
    for _, actIndex in pairs(tbKinIdMap) do
        Activity.ActivitySetting[actIndex] = nil;
        Activity.tbActivities[actIndex] = nil;
    end
    
    Activity.tbKinActivitySettingIndexMap[nKinId] = nil;
end

function Activity:CreateKinActivities(nKinId)
    if Activity.tbKinActivitySettingIndexMap[nKinId] ~= nil then          -- �Ѵ�����
        return;
    end

    local nStartKinActivityIndex = Activity.KIN_ACT_SET_START_INDEX;      -- ����������1000��ʼ
    local nDynamicActivityStartIndex = Activity.nCurrDynamicKinActSetIndex;
    local nMaxKinActNum = Activity.KIN_ACT_MAX_NUM; 
    local tbKinIdMap = {};
    
    for nIndex = nStartKinActivityIndex, nStartKinActivityIndex + nMaxKinActNum - 1 do -- ����������1000��ʼ�����6���
        if Activity.ActivitySetting[nIndex] ~= nil then
            local tbNewActivitySetting = Lib:CopyTBN(Activity.ActivitySetting[nIndex], 10);	--10��table����
            local nDynamicKinIndex = nDynamicActivityStartIndex + nIndex - nStartKinActivityIndex;
            Activity.ActivitySetting[nDynamicKinIndex] = tbNewActivitySetting;
            Activity.ActivitySetting[nDynamicKinIndex].ActivityName = Activity.ActivitySetting[nDynamicKinIndex].ActivityName.."_"..tostring(nKinId);
            local nMapCopyIndex = math.floor((nDynamicKinIndex - Activity.DYNAMIC_KIN_ACT_SET_START_INDEX) / Activity.KIN_ACT_MAX_NUM);
            local nSceneType = KScene.GetSceneType(Activity.ActivitySetting[nDynamicKinIndex].tbEnterPos.nMapId);
            if nSceneType == 2 then -- ս������
                Activity.ActivitySetting[nDynamicKinIndex].tbEnterPos.nCopyIndex = nMapCopyIndex;
            end
            
            self:CreateActivity(nDynamicKinIndex);
            
            local tbActivityData = self.tbActivities[nDynamicKinIndex];
	          for _, tbStep in pairs(tbActivityData.tbSteps) do
	              nSceneType = KScene.GetSceneType(tbStep.tbPos[1]);
	              if nSceneType == 2 then -- ս������
	                  tbStep.nMapCopyIndex = nMapCopyIndex;   --���ø�������
	              end
				  tbStep.nKinId = nKinId;
	          end
            tbKinIdMap[nIndex] = nDynamicKinIndex;
        end
    end
    
    -- �����һ������Ļ���ÿ�ʼ����
    Activity.nCurrDynamicKinActSetIndex = Activity.nCurrDynamicKinActSetIndex + Activity.KIN_ACT_MAX_NUM; 
    Activity.tbKinActivitySettingIndexMap[nKinId] = tbKinIdMap;
    
    KGameBase.CenterExecute({"Kin:OnKinActivitiesCreated", nKinId});
end

function Activity:SetKinActivityOpenTime(nKinId, nKinActivityIndex, nOpenTime)
	print("Activity:SetKinActivityOpenTime", nKinId, nKinActivityIndex);
	
	local tbKinIdMap = Activity.tbKinActivitySettingIndexMap[nKinId];
	local nActualActivityIndex = tbKinIdMap[nKinActivityIndex];

	local tbActivity    = Activity.ActivitySetting[nActualActivityIndex];
	
	local nCurOpenTime  = Lib:GetSecByTimeTable(tbActivity.tbOpenTimes[1][1]);
	local nCurCloseTime = Lib:GetSecByTimeTable(tbActivity.tbOpenTimes[1][2]);
	local nTimeDiff     = nCurCloseTime - nCurOpenTime;
   
	local nHour = math.floor(nOpenTime / 3600);
	local nMin = math.floor(math.mod(nOpenTime, 3600) / 60);
	local nSec = math.mod(nOpenTime, 60);
	
	local tbNewStartTime = {hour=nHour, min=nMin, sec=nSec};
	local nNewStartTime = Lib:GetSecByTimeTable(tbNewStartTime);
	local nNewCloseTime = nNewStartTime + nTimeDiff;
	
	local tbEndTime = Lib:GetTimeTable(nNewCloseTime);
	local tbNewEndTime = {hour = tbEndTime.hour, min = tbEndTime.min, sec = tbEndTime.sec};

	tbActivity.tbOpenTimes[1][1] = tbNewStartTime;
	tbActivity.tbOpenTimes[1][2] = tbNewEndTime;
	
	KGameBase.CenterExecute{"Activity:OnSetKinActivityOpenTime_GC", nKinId};

	--print("SetKinActivityOpenTime", tbActivity.tbOpenTimes[1][1], tbActivity.tbOpenTimes[1][2])
end

function Activity:OnSetKinActivityOpenTime_GS(nPlayerId)
	local pPlayer = KGameBase.GetPlayerById(nPlayerId);
	if not pPlayer then
		return;
	end
	
	-- �����
	Activity:CheckActivityRemind(pPlayer);
end

function Activity:OnJoinActivity(pPlayer, nActivityIndex, nStepIndex)

end

function Activity:GetStepStartTime(nActivityIndex, nStepIndex)
	local tbActivityData = self.tbActivities[nActivityIndex];
	local tbTargetStep = tbActivityData.tbSteps[nStepIndex];
	
	return tbTargetStep.dwStartTime;
end

function Activity:NpcUnLock(pNpc)
	local tbTmp = pNpc.GetTempTable("Activity")
	if not tbTmp then
		return 0;
	end
	if (not tbTmp.tbStep) or (not tbTmp.nLock) then
		return 0;
	end
	if not tbTmp.tbStep.tbLock[tbTmp.nLock] then
		return 0;
	end
	tbTmp.tbStep.CurrentDeadName = pNpc.szName
	tbTmp.tbStep.tbLock[tbTmp.nLock]:UnLockMulti();
end

function Activity:PlayerUnLock(pPlayer)
	local tbTmp = pPlayer.GetTempTable("Activity")
	if not tbTmp then
		return 0;
	end
	if (not tbTmp.tbStep) or (not tbTmp.nLock) then
		return 0;
	end
	if not tbTmp.tbStep.tbLock[tbTmp.nLock] then
		return 0;
	end
	tbTmp.tbStep.CurrentDeadName = pPlayer.szName
	tbTmp.tbStep.tbLock[tbTmp.nLock]:UnLockMulti();
end

function Activity:KickPlayer(nPlayerId, bReturn)
	local tbCurActivity = self.tbPlayerProgress[nPlayerId]
	if tbCurActivity ~= nil then
		local tbActivity = self.tbActivities[tbCurActivity.nActivityIndex]
		if tbActivity ~= nil and tbActivity.tbSteps[tbCurActivity.nStepIndex] ~= nil then
			tbActivity.tbSteps[tbCurActivity.nStepIndex]:KickPlayer(nPlayerId, 1)
	    end
	    self.tbPlayerProgress[nPlayerId] = nil
    end
	
	local pPlayer = KGameBase.GetPlayerById(nPlayerId)
	if pPlayer and bReturn and bReturn == 1 then
		pPlayer.ReturnToLastCity();
	end
end

function Activity:EndActivity(nActivityIndex)
    local tbActivity = self.tbActivities[nActivityIndex]
    tbActivity.tbStartStep.nIsOpen = 0
    
    -- �����л��ڻ������߳�
 	  for _, tbStep in pairs(tbActivity.tbSteps) do
        local tbPlayersCopy = {};
        for _, tbPlayer in pairs(tbStep.tbPlayers) do
        	table.insert(tbPlayersCopy, tbPlayer.nPlayerId);
        end
     
        for _, nPlayerId in pairs(tbPlayersCopy) do   	
        	self:KickPlayer(nPlayerId, 1);
        end
    end
    
    for _, tbStep in pairs(tbActivity.tbSteps) do
        tbStep:Clean();
    end 
	
	-- �������boss���������
	Activity.ActivitySetting[nActivityIndex].tbWorldBossRandSteps = {};
	--��ӡ����
    print("�["..tbActivity.szActivityName.."]����");
end


function Activity:IsActivityOpen(nActivityIndex)
    local tbActivity = self.tbActivities[nActivityIndex]
    if tbActivity ~= nil then
        for _, tbStep in pairs(tbActivity.tbSteps) do
            if tbStep.IsOpen == 1 then
                return 1
            end
        end
    end
    return 0
end

function Activity:LeaveGame(pPlayer)
	local tbCurActivity = self.tbPlayerProgress[pPlayer.dwId]
	if tbCurActivity ~= nil then
		local tbActivity = self.tbActivities[tbCurActivity.nActivityIndex]
		if tbActivity ~= nil and tbActivity.tbSteps[tbCurActivity.nStepIndex] ~= nil then
			tbActivity.tbSteps[tbCurActivity.nStepIndex]:LeaveGame(pPlayer.dwId)
	    end
    end
end


function Activity:OnSceneLoaded(nSceneId, nTemplateId)
	print("Activity:OnSceneLoaded", nSceneId, nTemplateId)
	for _, tbActivity in pairs(self.tbActivities) do
		for _, tbStep in pairs(tbActivity.tbSteps) do
			tbStep:OnSceneLoaded(nSceneId, nTemplateId)
	    end
    end
end

function Activity:SkipStep(nPlayerId)
	local tbCurActivity = self.tbPlayerProgress[nPlayerId]
	if tbCurActivity ~= nil then
		local tbActivity = self.tbActivities[tbCurActivity.nActivityIndex]
		if tbActivity ~= nil and tbActivity.tbSteps[tbCurActivity.nStepIndex] ~= nil then
		    tbActivity.tbSteps[tbCurActivity.nStepIndex]:EndStep()
	    end
    end
end

function Activity:CallActivityStepPlayerInFunction(nPlayerId, szFunName, ...)
	local tbCurActivity = self.tbPlayerProgress[nPlayerId]
	if tbCurActivity ~= nil then
		local tbActivity = self.tbActivities[tbCurActivity.nActivityIndex]
		if tbActivity ~= nil and tbActivity.tbSteps[tbCurActivity.nStepIndex] ~= nil then
		    local tbStep = tbActivity.tbSteps[tbCurActivity.nStepIndex]
		    tbStep[szFuncName](unpack(arg))
	    end
    end
end

function Activity:SetActivityOpenTime(nActivityIndex, tbStartTime, tbEndTime)
	local tbActivity = self.ActivitySetting[nActivityIndex];
	local nStartTime = Lib:GetSecByTimeTable(tbStartTime);
	local nEndTime = Lib:GetSecByTimeTable(tbEndTime);
	
	for _, tbOpenTime in pairs(tbActivity.tbOpenTimes) do
		local startTime = Lib:GetSecByTimeTable(tbOpenTime[1]);
		local endTime = Lib:GetSecByTimeTable(tbOpenTime[2]);		
		--local startTime = Timer:CycleTimeToSeconds(tbActivity.StartTime)
		--local endTime = Timer:CycleTimeToSeconds(tbActivity.EndTime)
		if nStartTime >= startTime and nStartTime <= endTime then
			print("..Active time period has cross, please reset the time");
			assert(false);
		end
	end
	
	table.insert(tbActivity.tbOpenTimes,{tbStartTime, tbEndTime, 1});
end

function Activity:IfCanAddActivityRemind(pPlayer, nActivityIdx)
	local tbActivity = self.ActivitySetting[nActivityIdx]; 
	assert(tbActivity);
	
	local tbActivityData = self.tbActivities[nActivityIdx];
	assert(tbActivityData);
	
	local nBaseActivityIdx = nActivityIdx;
	if tbActivity.nBaseActivityIdx then
		nBaseActivityIdx = tbActivity.nBaseActivityIdx;
	end
			
	-- �����������û�м���
	if nBaseActivityIdx >= 1000 then
		local nKinId = pPlayer.GetKinId();
		if nKinId ~= tbActivityData.tbSteps[1].nKinId then
			return 0;
		end
	end
	
	return 1;
	
end

--���ȫ�����ܿ�ʼ�Ļ����֪ͨǰ��
function Activity:CheckCanStartActivity()
	local tNow = KGameBase.GetTime();
	
	for nActivityIndex, tbActivityData in pairs(self.tbActivities) do
	    local tbActivity = self.ActivitySetting[nActivityIndex];
		assert(tbActivity.tbOpenTimes);
		
		-- ��ʱ������������������
		for _, tbOpenTime in pairs(tbActivity.tbOpenTimes) do
			if Activity:IsOpenTimeToday(tbOpenTime) == 1 then
				local dwStartTime = Lib:GetSecByTimeTable(tbOpenTime[1]);		-- ���ʼʱ���
				local dwEndTime = Lib:GetSecByTimeTable(tbOpenTime[2]);			-- �����ʱ���
				local nRemindIdx = 0;
				local nCountDown = 0;
				
				if dwStartTime - tNow == self.REMIND_TIMES_SPAN then
					nRemindIdx = 1;
					nCountDown = self.REMIND_TIMES_SPAN;
				elseif tNow == dwStartTime then
					nRemindIdx = 2;
					if tbActivity.nPrepareTime then
					    nCountDown = tbActivity.nPrepareTime;
					else
					    nCountDown = 60 * 5;
					end
				--[[
				elseif dwEndTime - tNow == self.REMIND_TIMES_SPAN then		-- �����ʱ����û��Ҫ
					nRemindIdx = 3;
					nCountDown = self.REMIND_TIMES_SPAN;
				--]]
				end
				
				local nBaseActivityIdx = nActivityIndex;
				if tbActivity.nBaseActivityIdx then
					nBaseActivityIdx = tbActivity.nBaseActivityIdx;
				end
				
				if nRemindIdx ~= 0 then
					local nRemindId = self:GetRemindByIdx(nBaseActivityIdx, nRemindIdx);
					if nRemindId then
						local tbPlayers = KGameBase.GetAllPlayers()
						for _, pPlayer in pairs(tbPlayers) do
							local nMapId = pPlayer.dwSceneTemplateId;
							local szSceneType = KScene.GetSceneTypeName(nMapId);
							
							if szSceneType ~= "activity" and szSceneType ~= "activity_zb" then
								if self:IfCanAddActivityRemind(pPlayer, nActivityIndex) == 1 then
									KRemind.AddRemindToPlayer(pPlayer, nRemindId, nCountDown);
								end
								pPlayer.CallClientScript({"QClientScript.UI:RefreshActivityPanel"});	-- ������忪�ž�ˢ��һ��
							end
							
						end
					end
				end
				
			end
		end
		
		local nIsOpenTime = 0;
		for _, tbOpenTime in pairs(tbActivity.tbOpenTimes) do
			if self:IsOpenTime(tbOpenTime) == 1 then
				nIsOpenTime = 1;
				break;
			end
		end
		
		if nIsOpenTime == 1 and tbActivityData.tbStartStep.nIsOpen == 0 then
			print("..activity["..tbActivity.ActivityName.."]begin...");
			--KChat.BroadcastNoticeMsg("["..tbActivity.ActivityName.."]��������");
			tbActivityData.tbStartStep:StartStep();
		elseif nIsOpenTime == 0 and tbActivityData.tbStartStep.nIsOpen == 1 then
			self:EndActivity(nActivityIndex);
		end
		
    end
end

--GMָ����  
function Activity:ChangeActiveTime(--[[playerName,--]]_nActivityIndex,Timer)
	local tNow = KGameBase.GetTime();
	self.ActivitySetting[_nActivityIndex].tbOpenTimes[1][1].hour = math.floor(Timer/100);
	self.ActivitySetting[_nActivityIndex].tbOpenTimes[1][1].min = Timer%100;
	self.ActivitySetting[_nActivityIndex].tbOpenTimes[1][2].hour = math.floor(Timer/100)+math.floor((Timer%100+30)/60);
	self.ActivitySetting[_nActivityIndex].tbOpenTimes[1][2].min = (Timer%100+30)%60;
	if self.ActivitySetting[_nActivityIndex].tbOpenTimes[1][1].wday == nil then
		local tbNowTime = Lib:GetTimeTable(tNow);
		self.ActivitySetting[_nActivityIndex].tbOpenTimes[1][1].wday = tbNowTime.wday;
		self.ActivitySetting[_nActivityIndex].tbOpenTimes[1][2].wday = tbNowTime.wday;
	end			
--[[	KGameBase.GetPlayerByName(playerName).SendBlackMsg(self.ActivitySetting[_nActivityIndex].ActivityName .. 
						"wday" .. self.ActivitySetting[_nActivityIndex].tbOpenTimes[1][1].wday
					.. "starttime  " .. self.ActivitySetting[_nActivityIndex].tbOpenTimes[1][1].hour .. self.ActivitySetting[_nActivityIndex].tbOpenTimes[1][1].min
					.. "    endTime" .. self.ActivitySetting[_nActivityIndex].tbOpenTimes[1][2].hour .. self.ActivitySetting[_nActivityIndex].tbOpenTimes[1][2].min)--]]

	--�����˻ʱ��ֻ��һ������ʱ����շ�ֹʱ���ظ�
	local tbActivity = self.ActivitySetting[_nActivityIndex];
	--assert(tbActivity.tbOpenTimes);
--[[	for i=0, tbOpenTime in pairs(tbActivity.tbOpenTimes) do
		if i ~= 1 then
			tbOpenTime = nil;
		end
	end--]]
	--��ʾ
	KChat.BroadcastNoticeMsg(self.ActivitySetting[_nActivityIndex].ActivityName .. 
						"wday" .. self.ActivitySetting[_nActivityIndex].tbOpenTimes[1][1].wday
						.. "starttime   " .. self.ActivitySetting[_nActivityIndex].tbOpenTimes[1][1].hour .. self.ActivitySetting[_nActivityIndex].tbOpenTimes[1][1].min
						.. "    endTime" .. self.ActivitySetting[_nActivityIndex].tbOpenTimes[1][2].hour .. self.ActivitySetting[_nActivityIndex].tbOpenTimes[1][2].min	)	
--[[	local tbPlayers = KGameBase.GetAllPlayers()
	for _, pPlayer in pairs(tbPlayers) do
		Activity:CheckActivityRemind(pPlayer);
	end	--]]
	Activity:CheckCanStartActivity();
end

-- �����
function Activity:CheckActivityRemind(pPlayer)
	local tNow = KGameBase.GetTime();
	
	for nActivityIndex, _ in pairs(self.tbActivities) do
	    local tbActivity = self.ActivitySetting[nActivityIndex];
		assert(tbActivity.tbOpenTimes);
		
		for _, tbOpenTime in pairs(tbActivity.tbOpenTimes) do
			if Activity:IsOpenTimeToday(tbOpenTime) == 1 then
				local dwStartTime = Lib:GetSecByTimeTable(tbOpenTime[1]);		-- ���ʼʱ���
				local dwEndTime = Lib:GetSecByTimeTable(tbOpenTime[2]);			-- �����ʱ���
				local nRemindIdx = 0;
				local nCountDown = 0;
				
				local nBaseActivityIdx = nActivityIndex;
				if tbActivity.nBaseActivityIdx then
					nBaseActivityIdx = tbActivity.nBaseActivityIdx;
				end
				
				if dwStartTime > tNow and dwStartTime - tNow <= self.REMIND_TIMES_SPAN then
					nRemindIdx = 1;
					nCountDown = dwStartTime - tNow;
					print("..activity begin......", nCountDown)
				elseif tbActivity.nPrepareTime and tNow >= dwStartTime and tNow <= dwStartTime + tbActivity.nPrepareTime then
					nRemindIdx = 2;
					nCountDown = dwStartTime + tbActivity.nPrepareTime - tNow;
				-- �����5����û��Ҫ
				--[[
				elseif tNow < dwEndTime and dwEndTime - tNow <= self.REMIND_TIMES_SPAN then
					nRemindIdx = 3;
					nCountDown = dwEndTime - tNow;
				--]]
				end
				
				if nRemindIdx ~= 0 then
					local nRemindId = self:GetRemindByIdx(nBaseActivityIdx, nRemindIdx);
					if nRemindId and self:IfCanAddActivityRemind(pPlayer, nActivityIndex) == 1 then
						Remind:AddRemindToPlayer(pPlayer, nRemindId, nCountDown);
					end
				end
			end
		end
		
    end
end

function Activity:SyncTodayActivityTime(pPlayer)
	local nBaseActivityIdx = 0;
	
	for nActivityIndex, _ in pairs(self.tbActivities) do
	    local tbActivity = self.ActivitySetting[nActivityIndex];
		assert(tbActivity.tbOpenTimes);
		
		nBaseActivityIdx = nActivityIndex;
		if nActivityIndex > 10000 then
			nBaseActivityIdx = tbActivity.nBaseActivityIdx;
		end
		
		for _, tbOpenTime in pairs(tbActivity.tbOpenTimes) do
			if Activity:IsOpenTimeToday(tbOpenTime) == 1 then
				local dwStartTime = Lib:GetSecByTimeTable(tbOpenTime[1]);		-- ���ʼʱ���
				local dwEndTime = Lib:GetSecByTimeTable(tbOpenTime[2]);			-- �����ʱ���
				KActivity.SyncActivityTime(pPlayer, nActivityIndex, nBaseActivityIdx, dwStartTime, dwEndTime);
			end
		end
    end
end

-- �Ի���в���������ִ��
function Activity:ActivityPlayerExecute(nActivityIndex, fnExcute)
	local tbActivity = self.tbActivities[nActivityIndex]
	if tbActivity ~= nil then
		for _, tbStep in pairs(tbActivity.tbSteps) do
            --if tbStep.IsOpen == 1 then
                tbStep:GroupPlayerExcute(fnExcute, 0)
            --end
        end
    end
end

function Activity:GetPlayerCurrentActivityStep(nPlayerId)
	local tbCurActivity = self.tbPlayerProgress[nPlayerId]
	if tbCurActivity ~= nil then
		return tbCurActivity.nActivityIndex, tbCurActivity.nStepIndex
    end
end

function Activity:OnLogout(nPlayerId)
	local pPlayer = KGameBase.GetPlayerById(nPlayerId);
	if not pPlayer then 
		return;
	end
	
	local nMapId = pPlayer.dwSceneTemplateId;
	if KScene.GetSceneTypeName(nMapId) ~= "activity" and KScene.GetSceneTypeName(nMapId) ~= "activity_zb" then
		return;
	end
	
	pPlayer.LeaveTeam();
	
	local tbLastCity = pPlayer.GetLastSaveCity();
	pPlayer.SetPositionForSaving(tbLastCity.nMapId, tbLastCity.nX, tbLastCity.nY, tbLastCity.nZ);
	
	self:KickPlayer(nPlayerId);
	
    --[[if pPlayer.IsBZonePlayer() == 1 then -- ���ǿ��������ֱ���߳�
    	self:KickPlayer(pPlayer.dwId)
    else
	    local tbCurActivity = self.tbPlayerProgress[nPlayerId]
		if tbCurActivity ~= nil then
			local tbActivity = self.tbActivities[tbCurActivity.nActivityIndex]
			if tbActivity ~= nil and tbActivity.tbSteps[tbCurActivity.nStepIndex] ~= nil then
				tbActivity.tbSteps[tbCurActivity.nStepIndex]:KickPlayer(nPlayerId)
			end
		end
    end --]]
end

function Activity:OnLogin(nPlayerId)
    local tbCurActivity = self.tbPlayerProgress[nPlayerId]
	if tbCurActivity ~= nil then
		local tbActivity = self.tbActivities[tbCurActivity.nActivityIndex]
		if tbActivity ~= nil and tbActivity.tbSteps[tbCurActivity.nStepIndex] ~= nil then
		    tbActivity.tbSteps[tbCurActivity.nStepIndex]:OnPlayerLogin(nPlayerId)
	    end
    end
	
	local pPlayer = KGameBase.GetPlayerById(nPlayerId);
	
	if not pPlayer then
		return;
	end
	
	-- �����
	Activity:CheckActivityRemind(pPlayer);
	
	-- ͬ������Ļʱ��
	Activity:SyncTodayActivityTime(pPlayer);
	
	-- ������ɾ����Ƿ�Ҫ������
	Activity:CheckMpjjAward(pPlayer);
end

function Activity:CheckMpjjAward(pPlayer)
	local dwLastMPJJRank = KActivity.GetLastMPJJRank(pPlayer);
	if dwLastMPJJRank ~= 0 then
		KAward.AddPlayerAward(pPlayer, "MenPaiJingJi", dwLastMPJJRank);
		if tbMPJJAwardScore[dwLastMPJJRank] then
			pPlayer.pPlayerPurse.AddMoney(Purse.EM_MONEY_MPJJ_SCORE, tbMPJJAwardScore[dwLastMPJJRank]);
			KRank.ModifyRankValue(pPlayer.dwId, Rank.MPJJ_RANK, pPlayer.pPlayerPurse.GetMoney(Purse.EM_MONEY_MPJJ_SCORE));
		end
		KActivity.SetLastMPJJRank(pPlayer, 0);
	end
end

--npc��id���󣬵��´�C++����lua��ʱ����������תΪ������
function Activity:OnDamage(pCaster, pInjured, nDamage)
	assert(pCaster and pInjured);
	local nCasterId = pCaster.dwId;
	local nInjuredId = pInjured.dwId;
	local tbCurActivity = self.tbPlayerProgress[nCasterId]
	if tbCurActivity ~= nil then
		local tbActivity = self.tbActivities[tbCurActivity.nActivityIndex]
		if tbActivity ~= nil and tbActivity.tbSteps[tbCurActivity.nStepIndex] ~= nil then
		    tbActivity.tbSteps[tbCurActivity.nStepIndex]:OnPlayerDamage(nCasterId, nInjuredId, nDamage)
	    end
	end
		
    tbCurActivity = self.tbPlayerProgress[nInjuredId]
	if tbCurActivity ~= nil then
		local tbActivity = self.tbActivities[tbCurActivity.nActivityIndex]
		if tbActivity ~= nil and tbActivity.tbSteps[tbCurActivity.nStepIndex] ~= nil then
		    tbActivity.tbSteps[tbCurActivity.nStepIndex]:OnPlayerInjured(nInjuredId, nCasterId, nDamage)
	    end
	end
end

function Activity:GetPlayerGroup(nPlayerId)
	local tbCurActivity = self.tbPlayerProgress[nPlayerId]
	if tbCurActivity ~= nil then
		local tbActivity = self.tbActivities[tbCurActivity.nActivityIndex]
		if tbActivity ~= nil and tbActivity.tbSteps[tbCurActivity.nStepIndex] ~= nil then
		    return tbActivity.tbSteps[tbCurActivity.nStepIndex]:GetPlayerGroup(nPlayerId)
		else
			print(string.format("..can not find player[%d] in step", nPlayerId))
	    end
	else
	    print(string.format("player[%d]is not in activity", nPlayerId))
	end
end

function Activity:GetActivityStepPlayerNum(nActivityIndex, nStepIndex)
	local tbActivity = self.tbActivities[nActivityIndex]
	if tbActivity ~= nil and tbActivity.tbSteps[nStepIndex] ~= nil then
		return #tbActivity.tbSteps[nStepIndex].tbPlayers;
	end
end

function Activity:GetProgressBarDescription(nPlayerId)
	local tbCurActivity = self.tbPlayerProgress[nPlayerId]
	if tbCurActivity ~= nil then
		local tbActivity = self.tbActivities[tbCurActivity.nActivityIndex]
		if tbActivity ~= nil and tbActivity.tbSteps[tbCurActivity.nStepIndex] ~= nil then
		    return tbActivity.tbSteps[tbCurActivity.nStepIndex]:GetProgressBarDescription()
	    end
	end
end

function Activity:GetProgressBarTime(nPlayerId)
	local tbCurActivity = self.tbPlayerProgress[nPlayerId]
	if tbCurActivity ~= nil then
		local tbActivity = self.tbActivities[tbCurActivity.nActivityIndex]
		if tbActivity ~= nil and tbActivity.tbSteps[tbCurActivity.nStepIndex] ~= nil then
		    return tbActivity.tbSteps[tbCurActivity.nStepIndex]:GetProgressBarTime()
	    end
	end
end

function Activity:OnProgressBarFinished(nPlayerId, nNpcId)
	local tbCurActivity = self.tbPlayerProgress[nPlayerId]
	if tbCurActivity ~= nil then
		local tbActivity = self.tbActivities[tbCurActivity.nActivityIndex]
		if tbActivity ~= nil and tbActivity.tbSteps[tbCurActivity.nStepIndex] ~= nil then
		    tbActivity.tbSteps[tbCurActivity.nStepIndex]:OnProgressBarFinished(nPlayerId, nNpcId)
	    end
	end
end

function Activity:OnProgressBarCancel(nPlayerId)
	local tbCurActivity = self.tbPlayerProgress[nPlayerId]
	if tbCurActivity ~= nil then
		local tbActivity = self.tbActivities[tbCurActivity.nActivityIndex]
		if tbActivity ~= nil and tbActivity.tbSteps[tbCurActivity.nStepIndex] ~= nil then
		    tbActivity.tbSteps[tbCurActivity.nStepIndex]:OnProgressBarCancel(nPlayerId)
	    end
	end
end

function Activity:OnPlayerDeath(nDeathCharId, nKillerCharId)
    local tbCurActivity = self.tbPlayerProgress[nDeathCharId]
	if tbCurActivity ~= nil then
		local tbActivity = self.tbActivities[tbCurActivity.nActivityIndex]
		if tbActivity ~= nil and tbActivity.tbSteps[tbCurActivity.nStepIndex] ~= nil then
		    tbActivity.tbSteps[tbCurActivity.nStepIndex]:OnPlayerDeath(nDeathCharId, nKillerCharId)
	    end
	end
		
    tbCurActivity = self.tbPlayerProgress[nKillerCharId]
	if tbCurActivity ~= nil then
		local tbActivity = self.tbActivities[tbCurActivity.nActivityIndex]
		if tbActivity ~= nil and tbActivity.tbSteps[tbCurActivity.nStepIndex] ~= nil then
			local pKiller = KGameBase.GetPlayerById(nKillerCharId)
			tbActivity.tbSteps[tbCurActivity.nStepIndex].CurrentKillerName = pKiller.szName
		    tbActivity.tbSteps[tbCurActivity.nStepIndex]:OnPlayerKill(nKillerCharId, nDeathCharId)
	    end
	end
	
	local pPlayer = KGameBase.GetPlayerById(nDeathCharId)
	if pPlayer ~= nil then 
		Activity:PlayerUnLock(pPlayer)
    end
end

function Activity:OnPlayerRevive(dwCharacterId)
    local tbCurActivity = self.tbPlayerProgress[dwCharacterId]
	if tbCurActivity ~= nil then
		local tbActivity = self.tbActivities[tbCurActivity.nActivityIndex]
		if tbActivity ~= nil and tbActivity.tbSteps[tbCurActivity.nStepIndex] ~= nil then
		    tbActivity.tbSteps[tbCurActivity.nStepIndex]:OnPlayerRevive(dwCharacterId)
	    end
	end
end

function Activity:OnNpcDeath(pKiller, pNpc)
	if pNpc and pNpc.IsNpc() ~= 1 then
		return;
	end
	
	local tbCurActivity = self.tbPlayerProgress[pKiller.dwId];
	if tbCurActivity ~= nil then
		local tbActivity = self.tbActivities[tbCurActivity.nActivityIndex]
		if tbActivity ~= nil and tbActivity.tbSteps[tbCurActivity.nStepIndex] ~= nil then
		    tbActivity.tbSteps[tbCurActivity.nStepIndex]:OnNpcDeath(pKiller, pNpc);
	    end
	end
end

--�ֶ��������ս����ϵ,Ŀǰֻ��������֮�ػ����Ҫ
function Activity:c2s_SetPlayerFightMode(pPlayer, nMode)
	local tbCurActivity = self.tbPlayerProgress[pPlayer.dwId];
	if tbCurActivity ~= nil then
		local tbActivity = self.tbActivities[tbCurActivity.nActivityIndex]
		if tbActivity ~= nil and tbActivity.tbSteps[tbCurActivity.nStepIndex] ~= nil then
			tbActivity.tbSteps[tbCurActivity.nStepIndex]:SetPlayerFightMode(pPlayer, nMode);
		end
	end
end

-- ע���¼�
CallCenter:RegisterGlobalEvent(KOBJEVENT.emKOBJEVENTTYPE_PLAYER_LOGIN, Activity.OnLogin, Activity);
CallCenter:RegisterGlobalEvent(KOBJEVENT.emKOBJEVENTTYPE_PLAYER_LOGOUT, Activity.OnLogout, Activity);
CallCenter:RegisterGlobalEvent(KOBJEVENT.emKOBJEVENTTYPE_SCENE_CREATE, Activity.OnSceneLoaded, Activity);
CallCenter:RegisterGlobalEvent(KOBJEVENT.emKOBJEVENTTYPE_CHARACTER_DEATH, Activity.OnPlayerDeath, Activity);
CallCenter:RegisterGlobalEvent(KOBJEVENT.emKOBJEVENTTYPE_CHARACTER_ENTER_SCENE, Activity.OnEnterScene, Activity);
CallCenter:RegisterGlobalEvent(KOBJEVENT.emKOBJEVENTTYPE_CHARACTER_LEAVE_SCENE, Activity.OnLeaveScene, Activity);
CallCenter:RegisterGlobalEvent(KOBJEVENT.emKOBJEVENTTYPE_CHARACTER_REVIVE,Activity.OnPlayerRevive,Activity);

Timer:Register(Env.GAME_FPS, Activity.CheckCanStartActivity, Activity)
Timer:Register(Env.GAME_FPS, Activity.CreateAllActivities, Activity)
