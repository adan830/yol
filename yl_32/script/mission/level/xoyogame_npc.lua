--
-- ��ң�� NPC�߼�

Include("script/lib/gift.lua");

XoyoGame.TASK_GROUP_MEDICINE = 2050;
XoyoGame.TASK_GET_MEDICINE_TIME = 53;

XoyoGame.nLastBroadcast = 0;
XoyoGame.nBroadcastNpcId = 0;
XoyoGame.nBroadcastMapId = 0;

function XoyoGame:CanGetMedicine()
	if SpecialEvent:IsWellfareStarted() ~= 1 then
		return 0, Lang.mission.str818[Lang.Idx];
	end
	
	if me.nLevel < 50 then
		return 0, Lang.mission.str819[Lang.Idx];
	end
	
	local nTime = tonumber(os.date("%Y%m%d", GetTime()));
	local nLastTime = me.GetTask(self.TASK_GROUP_MEDICINE, self.TASK_GET_MEDICINE_TIME);
	if nTime == nLastTime then
		return 0, Lang.mission.str820[Lang.Idx];
	end
	
	if me.CountFreeBagCell() < 1 then
		return 0, Lang.mission.str821[Lang.Idx];
	end
	
	return 1;
end

function XoyoGame:GetMedicine()
	local nRes, szMsg = self:CanGetMedicine();
	if nRes == 0 then
		Dialog:Say(szMsg);
		return;
	end
	
	local tbOpt = {
		{Lang.mission.str822[Lang.Idx], XoyoGame.GetMedicine2, XoyoGame, 1},
		{Lang.mission.str823[Lang.Idx], XoyoGame.GetMedicine2, XoyoGame, 2},
		{Lang.mission.str824[Lang.Idx], XoyoGame.GetMedicine2, XoyoGame, 3},
		{Lang.mission.str825[Lang.Idx]},
		};
	Dialog:Say(Lang.mission.str826[Lang.Idx], tbOpt);
end

XoyoGame.tbFreeMedicine = {
	[50] = {
		[1] = {18,1,352,4},
		[2] = {18,1,353,4},
		[3] = {18,1,354,4},
		},
	[80] = {
		[1] = {18,1,352,1},
		[2] = {18,1,353,1},
		[3] = {18,1,354,1},
		},
	[90] = {
		[1] = {18,1,352,2},
		[2] = {18,1,353,2},
		[3] = {18,1,354,2},
		},
	[120] = {
		[1] = {18,1,352,3},
		[2] = {18,1,353,3},
		[3] = {18,1,354,3},
		},
	};

function XoyoGame:GetMedicine2(nType)
	local nRes, szMsg = self:CanGetMedicine();
	if nRes == 0 then
		Dialog:Say(szMsg);
		return;
	end
	
	local nLevel;
	if me.nLevel >= 120 then
		nLevel = 120;
	elseif me.nLevel >= 90 then
		nLevel = 90;
	elseif me.nLevel >= 80 then
		nLevel = 80
	elseif me.nLevel >= 50 then
		nLevel = 50;
	end
	
	local pItem = me.AddItem(unpack(self.tbFreeMedicine[nLevel][nType]));
	me.SetItemTimeout(pItem, 24*60, 0)
	me.SetTask(self.TASK_GROUP_MEDICINE, self.TASK_GET_MEDICINE_TIME, tonumber(os.date("%Y%m%d", GetTime())));
	Dbg:WriteLog("XoyoGame", string.format(Lang.mission.str827[Lang.Idx], me.szName, pItem.szName));
end

function XoyoGame:JieYinRen()
	Dialog:Say(Lang.mission.str828[Lang.Idx],
		{
			{Lang.mission.str829[Lang.Idx], self.ToBaoMingDian, self, 341},
			{Lang.mission.str830[Lang.Idx], self.ToBaoMingDian, self, 342},
			{Lang.mission.str831[Lang.Idx]},
		})
end

function XoyoGame:BroadcastRank()
	return XoyoGame:__BroadcastRank();
end

function XoyoGame:__BroadcastRank()
	if XoyoGame.nBroadcastNpcId <= 0 then
		local tbNpcList = KNpc.GetMapNpcWithName(341, Lang.mission.str832[Lang.Idx]);
		XoyoGame.nBroadcastMapId = 341;
		if not tbNpcList or #tbNpcList == 0 then
			XoyoGame.nBroadcastMapId = 342;
			tbNpcList = KNpc.GetMapNpcWithName(342, Lang.mission.str832[Lang.Idx]);
		end
		if not tbNpcList or #tbNpcList == 0 then
			XoyoGame.nBroadcastMapId = 0;
			return;
		end
		XoyoGame.nBroadcastNpcId = tbNpcList[1];
	end
	
	local szDesc = self:GetBroadcastRank();
	if not szDesc then
		return;
	end
	local pNpc = KNpc.GetByIndex(XoyoGame.nBroadcastNpcId);
	if not pNpc then
		return;
	end
	pNpc.SendChat(szDesc);
	if (XoyoGame.nBroadcastMapId == 0) then
		print("Error When nBroadcastMapId is 0");
		return;
	end
	local tbPlayList, nCount = KPlayer.GetMapPlayer(XoyoGame.nBroadcastMapId);
	for _, nPlayerId in ipairs(tbPlayList) do
		local pMember = KGameBase.GetPlayerById(nPlayerId);
		pMember.Msg(szDesc, pNpc.szName);
	end;
end

function XoyoGame:GetBroadcastRank()
	local nDifficuty, nRank;
	local nMax = #XoyoGame.LevelDesp * XoyoGame.RANK_RECORD - 1;
	local nRepeat = 0;
	repeat
		nRepeat = nRepeat + 1;
		if nRepeat > nMax then
			return;
		end
		if XoyoGame.nLastBroadcast >= nMax then
			XoyoGame.nLastBroadcast = 0;
		else
			XoyoGame.nLastBroadcast = XoyoGame.nLastBroadcast + 1;
		end
		nDifficuty = math.floor(XoyoGame.nLastBroadcast / #XoyoGame.LevelDesp) + 1;
		nRank = XoyoGame.nLastBroadcast % XoyoGame.RANK_RECORD + 1;
	until XoyoGame.tbXoyoRank[nDifficuty] and XoyoGame.tbXoyoRank[nDifficuty][nRank];
	local tbRank = XoyoGame.tbXoyoRank[nDifficuty][nRank];
	if not tbRank then
		return;
	end
	
	local szDesc = Lang.mission.str833[Lang.Idx]
	local szDate = os.date(Lang.mission.str834[Lang.Idx], tbRank.nDate);
	local szTimeUsed = os.date(Lang.mission.str808[Lang.Idx], tbRank.nTime);
	local szCaptain = tbRank.tbMember[1];
	local szDifficuty = XoyoGame.LevelDesp[nDifficuty][2];
	szDesc = string.format(szDesc, szDifficuty, nRank, szTimeUsed, szCaptain, szDate);
	return szDesc;
end

function XoyoGame:WatchRecord()
	local tbOpt = {};
	for i = 1, #XoyoGame.LevelDesp do
		if XoyoGame.LevelDesp[i][1] == 1 then
			table.insert(tbOpt, {XoyoGame.LevelDesp[i][2] .. ":" .. XoyoGame.LevelDesp[i][3], self.WatchRecordDetails, self, i});
		elseif XoyoGame.LevelDesp[i][1] == 0 then
			table.insert(tbOpt, {"<color=gray>" .. XoyoGame.LevelDesp[i][2] .. ":" .. XoyoGame.LevelDesp[i][3] .. "<color>", self.NotOpenDifficuty, self});
		end
	end
	table.insert(tbOpt, {Lang.task.str3[Lang.Idx]});
	Dialog:Say(Lang.mission.str835[Lang.Idx], tbOpt);
end

function XoyoGame:WatchRecordDetails(nDifficuty)
	if not XoyoGame.tbXoyoRank[nDifficuty] or #XoyoGame.tbXoyoRank[nDifficuty] == 0 then
		Dialog:Say(Lang.mission.str836[Lang.Idx]);
		return;
	end
	local szMsg  = string.format(Lang.mission.str837[Lang.Idx], XoyoGame.LevelDesp[nDifficuty][2]);
	for nRank, tbInfo in ipairs(XoyoGame.tbXoyoRank[nDifficuty]) do
		szMsg = szMsg .. string.format(Lang.mission.str838[Lang.Idx], nRank);
		szMsg = szMsg .. os.date(Lang.mission.str839[Lang.Idx], tbInfo.nDate);
		szMsg = szMsg .. os.date("��ʱ:<color=yellow>".. Lang.mission.str808[Lang.Idx] .."<color>\n", tbInfo.nTime);
		szMsg = szMsg .. "��Ա:";
		for _, szName in ipairs(tbInfo.tbMember) do
			szMsg = szMsg .. szName .. " ";
		end
		szMsg = szMsg .. "\n\n";
	end
	Dialog:Say(szMsg);
	
end

function XoyoGame:ToBaoMingDian(nMapId)
	if me.nLevel < self.MIN_LEVEL then
		Dialog:Say(string.format(Lang.mission.str840[Lang.Idx],self.MIN_LEVEL));
		--Dialog:Say("�㹦����ǳ����ң�ȶ�����˵̫Σ���ˣ��Ȱѵȼ�������"..self.MIN_LEVEL.."���������Ȱɡ�");
		return 0;
	end
	if me.GetCamp() == 0 then
		Dialog:Say(Lang.mission.str841[Lang.Idx]);
		return 0;
	end
	me.NewWorld(nMapId, unpack(self.BAOMING_IN_POS))
end

function XoyoGame:NotOpenDifficuty()
	Dialog:Say(Lang.mission.str842[Lang.Idx]);
end

function XoyoGame:DocumentDifficuty(nTeamId, nDifficuty)
	local tbMemberList, nCount = KTeam.GetTeamMemberList(nTeamId);
	for _, nPlayerId in pairs(tbMemberList) do
		local pPlayer = KGameBase.GetPlayerById(nPlayerId);
		pPlayer.SetTask(XoyoGame.TASK_GROUP, XoyoGame.TASK_DIFFICUTY, nDifficuty);
	end
end

function XoyoGame:GetOnlineTeamMember(nTeamId)
	local tbMemberList, nCount = KTeam.GetTeamMemberList(nTeamId);
	if nCount == 0 then
		return;
	end
	for _, nPlayerId in pairs(tbMemberList) do
		local pPlayer = KGameBase.GetPlayerById(tbMemberList[1]);
		if pPlayer then
			return pPlayer;
		end
	end
end

function XoyoGame:GetDifficuty(nTeamId)
	local pPlayer = self:GetOnlineTeamMember(nTeamId);
	if not pPlayer then
		return 1; -- ��ֹ����
	end
	local nDifficuty = pPlayer.GetLevelDifficuty();
	if nDifficuty == 0 then
		nDifficuty = 1;
	end
	return nDifficuty;
end

-- ���Դ���
local nId = 0;
local function IdAccumulator(nSegment)
	nId = nSegment or nId + 1;
	return nId;
end

--���ͻ��˵��õĽӿڣ����˽��ؿ���
function XoyoGame:c2s_ApplyJoinGame(pPlayer, nDifficuty)
	local nTeamId = pPlayer.GetTeamId();
	if nTeamId > 0 then
		local tbTeamList, nCount = KTeam.GetTeamMemberList(nTeamId);
		if nCount > 1 then
			return;
		end
	end
	XoyoGame:TryEnterGame(({pPlayer.dwId}), nDifficuty);
end

function XoyoGame:CheckPlayer(nPlayerId, nMapId)
	local pPlayer = KGameBase.GetPlayerById(nPlayerId);
	if not pPlayer or pPlayer.nMapId ~= nMapId then
		Dialog:Say(Lang.mission.str843[Lang.Idx]);
		return 0;
	end
	if pPlayer.nLevel < self.MIN_LEVEL then
		Dialog:Say(string.format(Lang.mission.str844[Lang.Idx],self.MIN_LEVEL));
		--Dialog:Say("�������Ƕ���ô���в��������ˣ��Ȱѵȼ�������"..self.MIN_LEVEL.."�������ɡ�");
		return 0;
	end
	if pPlayer.GetCamp() == 0 then
		Dialog:Say(Lang.mission.str845[Lang.Idx]);
		return 0;
	end
	if self:GetPlayerTimes(pPlayer) <= 0 then
		Dialog:Say(string.format(Lang.mission.str846[Lang.Idx], pPlayer.szName));
		return 0;
	end
	return 1;
end

function XoyoGame:GetPlayerTimes(pPlayer)
	return self:AddPlayerTimes(pPlayer)
end

function XoyoGame:AddPlayerTimes(pPlayer)
	if pPlayer.nLevel < self.MIN_LEVEL then
		return 0;
	end
	local nCurTime = GetTime()
	local nCurDay = Lib:GetLocalDay(nCurTime);
	local nTimes = pPlayer.GetTask(self.TASK_GROUP, self.TIMES_ID);
	local nAddDay	= pPlayer.GetTask(self.TASK_GROUP, self.ADDTIMES_TIME);
	if nAddDay == 0 then
		nTimes = self.TIMES_PER_DAY;
		pPlayer.SetTask(self.TASK_GROUP, self.TIMES_ID, nTimes);
		pPlayer.SetTask(self.TASK_GROUP, self.ADDTIMES_TIME, nCurDay);
		return nTimes;
	end
	if nCurDay >= nAddDay then
		nTimes = nTimes + (nCurDay - nAddDay) * self.TIMES_PER_DAY;
		-- TODO: �Ժ�Ҫɾ�� -------------------------------
		local nXiuFuNum = (nCurDay - 14333) * self.TIMES_PER_DAY; -- 14334 ��1970.1.1 �� 2009.3.30 ������
		if nXiuFuNum < nTimes then
			nTimes = nXiuFuNum;
		end
		-- TODO��END --------------------------------------
		if nTimes >= self.MAX_TIMES then
			nTimes = self.MAX_TIMES
		end
		pPlayer.SetTask(self.TASK_GROUP, self.TIMES_ID, nTimes);
		pPlayer.SetTask(self.TASK_GROUP, self.ADDTIMES_TIME, nCurDay);
	end
	return nTimes;
end

function XoyoGame:AddPlayerTimesOnLogin()
	self:AddPlayerTimes(me)
end
--PlayerEvent:RegisterOnLoginEvent(XoyoGame.AddPlayerTimesOnLogin, XoyoGame) --zzx

------------------------------------------------------------------------------------------------------------------
--  �콱�������
XoyoGame.tbGift = Gift:New();

local tbGift = XoyoGame.tbGift;
tbGift.ITEM_CALSS = "xoyoitem"

function tbGift:OnOK(tbParam)
	local pItem = self:First();
	local tbItem = {};
	if not pItem then
		return 0;
	end
	while pItem do
		if pItem.szClass == self.ITEM_CALSS then
			table.insert(tbItem, pItem);
		end
		pItem = self:Next();
	end
	
	local nTimes = me.GetTask(XoyoGame.TASK_GROUP, XoyoGame.REPUTE_TIMES);
	local nDate = me.GetTask(XoyoGame.TASK_GROUP, XoyoGame.CUR_REPUTE_DATE);
	local nCurDate = tonumber(os.date("%Y%m%d",GetTime()));
	if nDate ~= nCurDate then
		nTimes = 0;
		me.SetTask(XoyoGame.TASK_GROUP, XoyoGame.CUR_REPUTE_DATE, nCurDate)
		me.SetTask(XoyoGame.TASK_GROUP, XoyoGame.REPUTE_TIMES, nTimes);
	end
	if nTimes >= XoyoGame.MAX_REPUTE_TIMES then
		Dialog:Say(string.format(Lang.mission.str847[Lang.Idx],XoyoGame.MAX_REPUTE_TIMES))
		--Dialog:Say("������Ѿ�������<color=red>"..XoyoGame.MAX_REPUTE_TIMES.."<color>�������ˣ�����Ҫ����һ����Щ�������������͹����ɣ�")
		return 0;
	end

	local nLevel		= me.GetReputeLevel(XoyoGame.REPUTE_CAMP, XoyoGame.REPUTE_CLASS);
	if (not nLevel) then
		print("AddRepute Repute is error ", me.szName, nClass, nCampId);
		return 0;
	else
		if (1 == me.CheckLevelLimit(XoyoGame.REPUTE_CAMP, XoyoGame.REPUTE_CLASS)) then
			me.Msg(Lang.mission.str848[Lang.Idx]);
			return 0;
		end
	end	
	
	local nRet = 0; 
	for _, pDelItem in ipairs(tbItem) do
		local nCount = pDelItem.nCount;
		if nTimes + nRet + nCount > XoyoGame.MAX_REPUTE_TIMES then	-- ���ɵ��߳�������
			local nRemain = nCount - (XoyoGame.MAX_REPUTE_TIMES - nTimes - nRet)
			if nRemain > 0 and nRemain <= nCount and pDelItem.SetCount(nRemain, Item.emITEM_DATARECORD_REMOVE) == 1 then
				nRet = XoyoGame.MAX_REPUTE_TIMES - nTimes;
			end
		elseif me.DelItem(pDelItem) == 1 then
			nRet = nRet + nCount;
		end
		if nTimes + nRet >= XoyoGame.MAX_REPUTE_TIMES then
			break;
		end
	end
	if nRet == 0 then
		Dialog:Say(Lang.mission.str849[Lang.Idx]);
		return 0;
	end
	
	me.AddRepute(XoyoGame.REPUTE_CAMP, XoyoGame.REPUTE_CLASS, nRet * XoyoGame.REPUTE_VALUE);
	me.SetTask(XoyoGame.TASK_GROUP, XoyoGame.REPUTE_TIMES, nTimes + nRet);
	
	--�ɾ�
	Achievement:FinishAchievement(me, 189);
	
	Dialog:Say(Lang.mission.str850[Lang.Idx]);
end

function tbGift:OnUpdate()
	self._szTitle = "���ɱ���";
	local nTimes = me.GetTask(XoyoGame.TASK_GROUP, XoyoGame.REPUTE_TIMES);
	local nDate = me.GetTask(XoyoGame.TASK_GROUP, XoyoGame.CUR_REPUTE_DATE);
	local nCurDate = tonumber(os.date("%Y%m%d",GetTime()));
	if nDate ~= nCurDate then
		nTimes = 0;
	end
	self._szContent = string.format(Lang.mission.str851[Lang.Idx],XoyoGame.MAX_REPUTE_TIMES,nTimes)
	--self._szContent = "ÿ�������Խ�"..XoyoGame.MAX_REPUTE_TIMES.."����Ʒ\n�����ѽ���<color=green>"..nTimes.."<color>��"
	return 0;
end

-- ?pl DoScript("\\script\\mission\\xoyogame\\xoyogame_npc.lua")
