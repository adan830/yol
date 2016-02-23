
if not MODULE_GAMESERVER then
	return
end

Include("script/misc/progressbar_define.lua")


-- S ��ĳ�����ִ�н�����
-- PARAM tbEvent �� {EVENTID1, EVENTID2, EVENTID3}
function ProgressBar:StartProcessOnPlayer(pPlayer, szTxt, nIntervalTime, tbSucCallBack, tbBreakCallBack, tbEvent)
	assert(nIntervalTime > 0)
	assert(szTxt)
	
	self:OnEvent(self.EVENT_NEW_PROGRESS, pPlayer.dwId)
	
	local tbCallbackData = {}
	tbCallbackData.tbSucCallBack = tbSucCallBack
	tbCallbackData.tbBreakCallBack = tbBreakCallBack
	self:SetPlayerCallbakData(pPlayer, tbCallbackData)
	
	-- ��tbEvent�����ɺ��ʵĸ�ʽ
	local tbEventParsel = {}
	if tbEvent then
		for i = 1, #tbEvent do
			tbEventParsel[tbEvent[i]] = 1
		end
	end
	
	self:SetPlayerEventData(pPlayer, tbEventParsel)
	
	local bStartResult = pPlayer.StartProgressBar(nIntervalTime)
	
	if bStartResult == 1 then
		self:NotifyStartProgressBar(pPlayer, nIntervalTime, szTxt)
	else
		self:ClearProgressBarTable(pPlayer) -- ��������Ұ󶨵ı�����
	end
	
	return bStartResult
end

function ProgressBar:Init()
	self:UnRegisterBreakEvent()
	self:RegisterBreakEvent()
end

function ProgressBar:RegisterBreakEvent()
	self:__RegisterBreakEvent(KOBJEVENT.emKOBJEVENTTYPE_CHARACTER_MOVE, self.EVENT_MOVE)
	self:__RegisterBreakEvent(KOBJEVENT.emKOBJEVENTTYPE_PLAYER_LOGOUT, self.EVENT_LOGOUT)
	self:__RegisterBreakEvent(KOBJEVENT.emKOBJEVENTTYPE_PLAYER_ITEM_OPS, self.EVENT_ITEM_OPS)
	self:__RegisterBreakEvent(KOBJEVENT.emKOBJEVENTTYPE_CAPTAIN_CHANGE, self.EVENT_CAPTAIN_CHANGE)
	self:__RegisterBreakEvent(KOBJEVENT.emKOBJEVENTTYPE_CHARACTER_BEHIT, self.EVENT_BE_HIT)
	self:__RegisterBreakEvent(KOBJEVENT.emKOBJEVENTTYPE_CHARACTER_DEATH, self.EVENT_DEATH)
	self:__RegisterBreakEvent(KOBJEVENT.emKOBJEVENTTYPE_CHARACTER_BEGIN_CAST_SKILL, self.EVENT_CAST_SKILL)
	self:__RegisterBreakEvent(KOBJEVENT.emKOBJEVENTTYPE_CHARACTER_LEAVE_SCENE, self.EVENT_LEAVESCENE)
end

function ProgressBar:__RegisterBreakEvent(eEvent, nEventId)
	local nRegisteredId = CallCenter:RegisterGlobalEvent(eEvent, self.OnEvent, ProgressBar, nEventId)
	local tbEvent =
	{
		["eEvent"] = eEvent,
		["nRegisteredId"] = nRegisteredId,
	}
	table.insert(self.tbRegisteredEvent, tbEvent)
end

function ProgressBar:UnRegisterBreakEvent()
	local tbRegisteredEvent = self.tbRegisteredEvent

	for _, tbEvent in ipairs(tbRegisteredEvent) do
		CallCenter:UnRegisterGlobalEvent(tbEvent.eEvent, tbEvent.nRegisteredId)
	end
	
	self.tbRegisteredEvent = {}
end
--
--function ProgressBar:OnEvent(nEventId, dwPlayerId)
	--local pPlayer = KGameBase.GetPlayerById(dwPlayerId)
	--if not pPlayer then
		--return
	--end
	--
	--local tbTempTable = pPlayer.GetTempTable("ProgressBar")
	--local tbBreakEvent = tbTempTable.tbEvent
--
	--if tbBreakEvent and (self.tbAlwaysBreak[nEventId] or tbBreakEvent[nEventId]) then
		--self:OnBreak(pPlayer)
	--end
--end


function ProgressBar:OnEvent(...)
	local nEventId = arg[1]
	if not nEventId or type(nEventId) ~= "number" then
		return
	end
	local tbPlayer = {}
	local fnEventHandle = self.tbEventHandle[nEventId]
	
	if fnEventHandle then
		tbPlayer = fnEventHandle(self, unpack(arg, 2))
	else
		tbPlayer = ProgressBar:DefaultEventHandle(unpack(arg, 2))
	end
	
	for _, pPlayer in pairs(tbPlayer) do
		local tbTempTable = pPlayer.GetTempTable("ProgressBar")
		local tbBreakEvent = tbTempTable.tbEvent

		if tbBreakEvent and (self.tbAlwaysBreak[nEventId] or tbBreakEvent[nEventId]) then
			self:CancelProgress(pPlayer)
		end
	end
end

--����϶���
function ProgressBar:CancelProgress(pPlayer)
	if not pPlayer then
		return
	end
	
	pPlayer.CancelProgressBar()
	
	local tbCallBackData = self:GetPlayerCallbakData(pPlayer)
	if tbCallBackData and tbCallBackData.tbBreakCallBack then
		Lib:CallBack(tbCallBackData.tbBreakCallBack)
	end
	
	self:NotifyCloseProgressBar(pPlayer, 0)
	self:ClearProgressBarTable(pPlayer)
end


function ProgressBar:GetPlayerCallbakData(pPlayer)
	local tbPlayerData = pPlayer.GetTempTable("ProgressBar")
	return tbPlayerData.tbCallbackData
end

function ProgressBar:SetPlayerCallbakData(pPlayer, tbCallback)
	local tbPlayerData = pPlayer.GetTempTable("ProgressBar")
	tbPlayerData.tbCallbackData = tbCallback	
end

function ProgressBar:SetPlayerEventData(pPlayer, tbEvent)
	local tbPlayerData = pPlayer.GetTempTable("ProgressBar")
	tbPlayerData.tbEvent = tbEvent
end

-- S
function ProgressBar:OnProgressFull(dwPlayerId)
	local pPlayer = KGameBase.GetPlayerById(dwPlayerId)
	if not pPlayer then
		return
	end
	local tbCallBackData = self:GetPlayerCallbakData(pPlayer)
	
	if tbCallBackData and tbCallBackData.tbSucCallBack then
		Lib:CallBack(tbCallBackData.tbSucCallBack)
	end
	
	-- kkע���ͻ��˻�����������Զ��ص�������������ͻ���ʱ�䲻ͬ����bug
	-- self:NotifyCloseProgressBar(pPlayer, 1) 
	self:ClearProgressBarTable(pPlayer)  -- ��ɽ�����ʱҲ��Ҫ��������Ұ󶨵ı�����
end

function ProgressBar:ClearProgressBarTable(pPlayer)
	self:SetPlayerEventData(pPlayer, nil) -- ��Break�¼��б�Ϊ��
	self:SetPlayerCallbakData(pPlayer, nil) -- �ûص��б�Ϊ��
end

function ProgressBar:NotifyStartProgressBar(pPlayer, nInterval, szDesc)
	pPlayer.CallClientScript{"YoulongApp.Represent.QRepresentClientScript:PickUpProgressBar", nInterval, szDesc}
end

function ProgressBar:NotifyCloseProgressBar(pPlayer, bFinished)
	pPlayer.CallClientScript{"YoulongApp.Represent.QRepresentClientScript:DestroyProgressBar"}
end


function ProgressBar:c2s_CancelProgressBar(pPlayer)
	ProgressBar:OnEvent(self.EVENT_CLIENT_CANCEL, pPlayer.dwId)
end

-- Ĭ���¼�����ʽ
function ProgressBar:DefaultEventHandle(dwPlayerId)
	local tbPlayer = {}
	if dwPlayerId then
		local pPlayer = KGameBase.GetPlayerById(dwPlayerId)
		if pPlayer then
			table.insert(tbPlayer, pPlayer)
		end	
	end	
	return tbPlayer
end

-- ��Ҫ���⴦��Ĵ���¼�
function ProgressBar:CaptainChangeEventHandle(nTeamId, dwNewCaptainId, dwOldCaptainId)
	local tbPlayer = {}
	if nTeamId and dwNewCaptainId and dwOldCaptainId then
		local pPlayer = KGameBase.GetPlayerById(dwNewCaptainId)
		if pPlayer then
			table.insert(tbPlayer, pPlayer)
		end	
		
		pPlayer = KGameBase.GetPlayerById(dwOldCaptainId)
		if pPlayer then
			table.insert(tbPlayer, pPlayer)
		end	
	end	
	return tbPlayer
end


-- �¼�����ʽ
ProgressBar.tbEventHandle = {
	[ProgressBar.EVENT_CAPTAIN_CHANGE]				= ProgressBar.CaptainChangeEventHandle,
	-- Ĭ�ϴ���ʽΪProgressBar:DefaultEventHandle,
}

ProgressBar:Init()
