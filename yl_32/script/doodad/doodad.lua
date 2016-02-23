-- File       : doodad.lua
-- Creator    : simon
-- Date       : 2010-03-17 15:18:19
-- Description:

if not MODULE_GAMESERVER then
	return
end

Doodad.tbGatherDoodadTemplates = {}

if (not Doodad.tbClassBase) then	-- ��ֹ�ļ�����ʱ�ƻ���������
	Doodad.tbClassBase	= {}

	-- ģ���
	Doodad.tbClass	= {
		-- Ĭ��ģ�壬�����ṩֱ��ʹ��
		default	= Doodad.tbClassBase,
		[""]	= Doodad.tbClassBase,
	}
	--Doodad.tbDropList = Lib:LoadTabFile(Doodad.szDropList)
	--Doodad.tbDropListDetail = Lib:LoadTabFile(Doodad.szDropListDetail)
end

function Doodad:OnEnterScene(pDoodad, szClassName)

end

function Doodad:OnLeaveScene(pDoodad, szClassName)

end

function Doodad:DropItem(nDoodadTemplateId, nOwnerId, tbPlayerList, tbPos, tbItem)
	Timer:Register(3, self.DoDropItem, self, nDoodadTemplateId, nOwnerId, tbPlayerList, tbPos, tbItem);
end

function Doodad:DoDropItem(nDoodadTemplateId, nOwnerId, tbPlayerList, tbPos, tbItem)
	local pDoodad = KGameBase.CallDoodad(nDoodadTemplateId, nOwnerId, tbPlayerList, tbPos, tbItem);
	assert(pDoodad);
	
	return 0;
end

-- ȡ���ض�������Npcģ��
function Doodad:GetClass(szClassName, bNoCreate)
	local tbClass	= self.tbClass[szClassName]
	-- ���û��bNotCreate�����Ҳ���ָ��ģ��ʱ���Զ�������ģ��
	if (not tbClass and bNoCreate ~= 1) then
		-- ��ģ��ӻ���ģ������
		tbClass	= Lib:NewClass(self.tbClassBase)
--		-- ���뵽ģ�������
--		tbClass.tbDropList = self:GetDropList(szClassName)
--		tbClass.tbDropList.gold = tonumber(tbClass.tbDropList["Gold"])
--		tbClass.tbDropList.normalexp = tbClass.tbDropList.gold + tonumber(tbClass.tbDropList["NormalExp"])
--		tbClass.tbDropList.careerexp = tbClass.tbDropList.normalexp + tonumber(tbClass.tbDropList["CareerExp"])
--		tbClass.tbDropList.items = tbClass.tbDropList.careerexp + tonumber(tbClass.tbDropList["Items"])
		self.tbClass[szClassName]	= tbClass
	end
	return tbClass
end

function Doodad:Init()
	local szPath = "/setting/doodad/gatherdoodadtemplate.txt"
	self:LoadGatherDoodadTemplate(szPath)
end

function Doodad:LoadGatherDoodadTemplate(szPath)
	assert(szPath)
	local tbTemplateFile = Lib:LoadTabFile(szPath)
	if tbTemplateFile then
		for _, tbRow in pairs(tbTemplateFile) do
			self.tbGatherDoodadTemplates[tonumber(tbRow.TemplateId_Ext)] =
			{
				dwTemplateId = tonumber(tbRow.TemplateId_Ext),
				dwGatherCount = tonumber(tbRow.GatherCount_Ext),
				dwGatherTime = tonumber(tbRow.GatherTime_Ext),
				dwMinActionTime = tonumber(tbRow.MinActionTime_Ext),
				dwMaxActionTime = tonumber(tbRow.MaxActionTime_Ext),
				tbSuccessActions = Lib:Str2Val(tbRow.SuccessActions_Ext),
				tbFailedActions = Lib:Str2Val(tbRow.FailedActions_Ext),
			}
		end
	else
		local szError = string.format("Doodad:LoadGatherDoodadTemplate Failed to Load %s", szPath)
		print(szError)
		Dbg:WriteLogEx(Dbg.LOG_ERROR, "Doodad", szError)
	end
end

function Doodad:GetGatherDoodadTemplate(dwTemplateId)
	return self.tbGatherDoodadTemplates[dwTemplateId]
end

-- ��C++�е�������Doodad�Ƿ���Ե��
function Doodad:CanDialog(pPlayer, pDoodad)
	-- �жϸ�������
	local tbProcess = ExpScene:GetProgressByPlayer(pPlayer)
	if tbProcess then
		return Doodad:IsValidProgress(pDoodad, tbProcess.nProgressId)
	else
		--�ж���ҵ�ǰ�Ĺ��½����Ƿ��в���doodad������
		return Story:CanOpenDoodad(pPlayer, pDoodad)
	end
end

function Doodad:OnDialog(pPlayer, pDoodad, nAwardId)
	if (not pPlayer) or (not pDoodad) then
		print("[Doodad�������] Doodad:OnDialog�յ���Ч��Player��Doodadָ��", pPlayer, pDoodad)
		return
	end

	--���pPlayer�Ƕӳ�������£��������д��ڸ���״̬�Ķ�Աȫ��Ҳ��һ��ͬ���Ľ���
	local tbPlayers = {pPlayer}
	if 1 == pPlayer.IsCaptain() then
		local nTeamLeaderId = pPlayer.dwId
		local nTeamId = pPlayer.GetTeamId()
		local tbTeamMember = KTeam.GetTeamMemberList(nTeamId) or {}
		for _, nPlayerId in pairs(tbTeamMember) do
			if nTeamLeaderId ~= nPlayerId then
				local pTeamPlayer = KGameBase.GetPlayerById(nPlayerId)
				if pTeamPlayer and KTeam.IsPlayerFollowLeader(nPlayerId) == 1 then
					table.insert(tbPlayers, pTeamPlayer)
				end
			end
		end
	end

	for _, pAwardPlayer in pairs(tbPlayers) do
		local tbAwardId = {nAwardId}

		local nBaseMulti = 1
		local nRet, tbAwardData = Award:GiveAward(pAwardPlayer, nBaseMulti, tbAwardId)

		local tbTaskDrop = Task:OnDropTaskItem(pAwardPlayer, nil, pDoodad.dwTemplateId)
		if tbTaskDrop then
			for _, tb in pairs(tbTaskDrop) do
				-- ����׼�����ı��ʽ������table
				tbAwardData[Award.AWARD_ITEM] = tbAwardData[Award.AWARD_ITEM] or {}
				local tbAwardItem = tbAwardData[Award.AWARD_ITEM]
				tbAwardItem[tb[1]] = (tbAwardItem[tb[1]] or 0) + #tb
			end
		end

		local tbExpSceneDrop = ExpScene:OnDropItem(pAwardPlayer, nil, pDoodad.dwTemplateId)
		if tbExpSceneDrop then
			for _, tb in pairs(tbExpSceneDrop) do
				-- ����׼�����ı��ʽ������table
				tbAwardData[Award.AWARD_ITEM] = tbAwardData[Award.AWARD_ITEM] or {}
				local tbAwardItem = tbAwardData[Award.AWARD_ITEM]
				tbAwardItem[tb[1]] = (tbAwardItem[tb[1]] or 0) + #tb
			end
		end

		local tbStoryDrop = Story:OnDropItem(pAwardPlayer, nil, pDoodad.dwTemplateId)
		if tbStoryDrop then
			for _, tb in pairs(tbStoryDrop) do
				-- ����׼�����ı��ʽ������table
				tbAwardData[Award.AWARD_ITEM] = tbAwardData[Award.AWARD_ITEM] or {}
				local tbAwardItem = tbAwardData[Award.AWARD_ITEM]
				tbAwardItem[tb[1]] = (tbAwardItem[tb[1]] or 0) + #tb
			end
		end
		Award:SyncAwardContent(pAwardPlayer, tbAwardData)
	end
	
	return
end

function Doodad:OnProcess(pDoodad, pPlayer, dwProcessTime)
    print(dwProcessTime)
    local tbFinish = {"Doodad:OnProcessFinish", pDoodad.dwId, pPlayer.dwId}
    local tbBreak= {"Doodad:OnProcessBreak", pDoodad.dwId, pPlayer.dwId}
    local tbBreakEvent =
    {
        ProgressBar.EVENT_MOVE,
        ProgressBar.EVENT_COMBAT_START,
        ProgressBar.EVENT_PLOT_PLAY_START,
        ProgressBar.EVENT_CLIENT_CANCEL,
        ProgressBar.EVENT_CAPTAIN_CHANGE,
    }
    ProgressBar:StartProcessOnPlayer(pPlayer, Lang.doodad.str6[Lang.Idx], dwProcessTime, tbFinish, tbBreak, tbBreakEvent)
    return 1
end

function Doodad:OnProcessFinish(dwDoodadId, dwPlayerId)
    local pDoodad = KGameBase.GetDoodadById(dwDoodadId)
    if not pDoodad then
        return
    end

    pDoodad.ProcessFinish(dwPlayerId)
end

function Doodad:OnProcessBreak(dwDoodadId, dwPlayerId)
    local pDoodad = KGameBase.GetDoodadById(dwDoodadId)
    if not pDoodad then
        return
    end

    pDoodad.ProcessBreak(dwPlayerId)
end

--[[
--Doodad.szDropList = "/setting/doodad/drop/droplist.txt"
--Doodad.szDropListDetail = "/setting/doodad/drop/droplistdetail.txt"

--��ȡ������Ʒ�ĸ���
function Doodad:GetDropItemNum(szName, nLevel)
	return tonumber(self.tbDropListDetail[nLevel][szName])
end

--�����ȡ������Ʒ����
function Doodad:GetDropItemName(tbDropList)

	local odds = KUnify.MathRandom(100)
	local szRet

	if(odds <= tbDropList.gold) then
		szRet = "Gold"
	elseif(odds <= tbDropList.normalexp) then
		szRet = "NormalExp"
	elseif(odds <= tbDropList.careerexp) then
		szRet = "CareerExp"
	elseif(odds <= tbDropList.items) then
		szRet = "Items"
	end

	return szRet
end
-- ȡ���ض������ĵ����
function Doodad:GetDropList(szClassName)
	for nRow, tbDataRow in ipairs(self.tbDropList) do
		if( tbDataRow["Class"] == szClassName ) then
			return tbDataRow
		end
	end
	return nil
end

]]--


Doodad:Init()
