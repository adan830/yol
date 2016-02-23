-- �ļ�������relation_gc.lua
-- �����ߡ���
-- ����ʱ�䣺
-- ����������gamecenter���˼ʹ�ϵ�߼�

if not (MODULE_GAMECENTER) then
	return
end

-- �ж��Ƿ������ӹ�ϵ
function Relation:CheckCanAddRelation(nAppId, nDstId, nType, nRole)
	-- �Է�������
	--[[
	local nDstOnline = KGCPlayer.OptGetTask(nDstId, KGCPlayer.TSK_ONLINESERVER);
	if (nDstOnline <= 0) then
		self:SetInfoMsg("�Է���Ҳ����ߡ�");
		return self.emKEPLAYER_NOTONLINE;
	end ]]
	
	-- ����û�м�����
	local nAppIsLoadEnd = CheckIsLoadEnd(nAppId);
	local nDstIsLoadEnd = CheckIsLoadEnd(nDstId);
	if (nAppIsLoadEnd == 0 or nDstIsLoadEnd == 0) then
		--self:SetInfoMsg("�������û�м�����ɡ�");
		self:NotifyPlayerOffline_GC(nAppId, nDstId);
		return self.emKEADDRELATION_FAIL;
	end
	
	-- ����ͻ��������ϵ
	local nCheckDepRep = CheckCreateDepRep(nType, nRole, nAppId, nDstId);
	if (0 == nCheckDepRep) then
		return self.emKEADDRELATION_FAIL;
	end	
	
	-- �Ƿ������ӹ�ϵ
	local nCanAddRelation = CanCreateRelation(nType, nRole, nAppId, nDstId);
	if (nCanAddRelation == 0) then
		return self.emKEADDRELATION_FAIL;
	end
	
	return self.emKEADDRELATION_SUCCESS;
end

function Relation:SetLastTalkTime_GC(nAppId, szDstName, dwTime)
	if (not nAppId or not szDstName or nAppId <= 0) then
		return;
	end

	local nDstId = GetPlayerIdByName(szDstName);
	if (not nDstId or nDstId == 0 or nDstId == nAppId) then
		return;
	end
	
	SetFriendTalkTime(nAppId, nDstId, dwTime);
end

-- ֪ͨ�Է������߻��߲�����
function Relation:NotifyPlayerOffline_GC(nAppId, nDstId)
	if (not nAppId or nAppId <= 0) then
		return;
	end
	if (not nDstId or nDstId <= 0) then
		return;
	end
	
	local szDstName = GetRoleName(nDstId);
	if szDstName then
		GlobalExecute{"Relation:NotifyPlayerOffline_GS", nAppId, szDstName};
	end
end

-- ֪ͨ�ѱ����������
function Relation:NotifyAddedBlack_GC(nAppId, szDstName)
	if (not nAppId or not szDstName or nAppId <= 0) then
		return;
	end
	GlobalExecute{"Relation:NotifyAddedBlack_GS", nAppId, szDstName};
end

-- ֪ͨ�Ѵ�����ֵ
function Relation:NotifyReachMaxCount_GC(nAppId, nType)
	if (not nAppId or nAppId <= 0) then
		return;
	end
	GlobalExecute{"Relation:NotifyReachMaxCount_GS", nAppId, nType};
end

-- ͬ����ϵ�б�
function Relation:SyncRelation_GC(nAppId)
	if (not nAppId or nAppId <= 0) then
		return;
	end
	SyncRelation(nAppId);
end
-- ��ӹ�ϵ
function Relation:AddRelation_GC(nAppId, szDstName, nType, nRole)
	if (not nAppId or not szDstName or nAppId <= 0) then
		return;
	end

	self:ClearInfoMsg();
	
	local nDstId = GetPlayerIdByName(szDstName);
	if (not nDstId or nDstId == 0) then
		return;
	elseif nDstId == nAppId then
		self:SetInfoMsg(Lang.gcscript.str49[Lang.Idx]);
		return;
	end
	
	local nResult = self:CheckCanAddRelation(nAppId, nDstId, nType, nRole);
	if (nResult == self.emKEADDRELATION_SUCCESS) then
		nResult = CreateRelation(nType, nAppId, nDstId, nRole);
		if (nResult == 1) then
			Relation:ProcessAfterAddRelation_GC(nType, nRole, nAppId, nDstId);
			
			-- ����˼ʳɹ������ʾ��Ϣ
			local szType = self.tbRelationName[nType] or "";

			-- local szMsg = "���Ѿ��ɹ��� "..szDstName .. "��ӵ�"..szType.."�б��С�"; print(szMsg);
			-- self:SetInfoMsg(szMsg);
		end
	end
	
	self:TellPlayerMsg_GC(nAppId);
end

function Relation:AfterAddRelation_GC(nAppId, nDstId, nType)
	if (not nAppId or not nDstId or not nType or
		nAppId <= 0 or nDstId <= 0) then
		return;
	end
	
	GlobalExecute{"Relation:AfterAddRelation_GS", nAppId, nDstId, nType};
end

-- �ж��Ƿ����ɾ����ϵ
function Relation:CheckCanDelRelation(nAppId, nDstId, nType, nRole)
	-- �����Ƿ�������
	local nAppIsLoadEnd = CheckIsLoadEnd(nAppId);
	if (nAppIsLoadEnd == 0) then
		return 0;
	end
	
	-- ����ͻ��������ϵ
	local nCheckDepRep = CheckDelDepRep(nType, nRole, nAppId, nDstId);
	if (0 == nCheckDepRep) then
		return 0;
	end
	
	return 1;
end

-- ɾ����ϵ
function Relation:DelRelation_GC(nAppId, szDstName, nType, nRole)
	local nDstPlayerId = GetPlayerIdByName(szDstName);
	if (nDstPlayerId == 0) then
		return;
	end
	self:ClearInfoMsg();
	
	local nCanDelRelation = self:CheckCanDelRelation(nAppId, nDstPlayerId, nType, nRole);
	if (1 == nCanDelRelation) then
		if (1 == DelRelation(nType, nAppId, nDstPlayerId, nRole)) then
			Relation:ProcessAfterDelRelation_GC(nType, nRole, nAppId, nDstPlayerId);
		end
	end
	
	self:TellPlayerMsg_GC(nAppId);
end

-- ����Ƿ�����������ܶ�
function Relation:CheckCanAddFavor(nAppId, nDstId, nFavor, nMethod)
	-- ĳһ��������
	local nDstOnline = KGCPlayer.OptGetTask(nDstId, KGCPlayer.TSK_ONLINESERVER);
	local nAppOnline = KGCPlayer.OptGetTask(nAppId, KGCPlayer.TSK_ONLINESERVER);
	if (nDstOnline <= 0 or nAppOnline <= 0) then
		return 0;
	end
	
	-- ����û�м�����
	local nAppIsLoadEnd = KRelation.CheckIsLoadEnd(nAppId);
	local nDstIsLoadEnd = KRelation.CheckIsLoadEnd(nDstId);
	if (nAppIsLoadEnd == 0 or nDstIsLoadEnd == 0) then
		return 0;
	end
	
	return 1;
end

-- �������ܶ�
function Relation:AddFriendFavor_GC(szAppName, szDstName, nFavor, nMethod)
	if (not szAppName or not szDstName or szAppName == szDstName or nFavor <= 0) then
		return;
	end
	
	self:ClearInfoMsg();
	
	local nAppId = KGCPlayer.GetPlayerIdByName(szAppName);
	local nDstId = KGCPlayer.GetPlayerIdByName(szDstName);
	
	local nCanAddFavor = self:CheckCanAddFavor(nAppId, nDstId, nFavor, nMethod);
	if (1 == nCanAddFavor) then
		KRelation.ResetLimtWhenCrossDay(nAppId, nDstId);
		KRelation.AddFriendFavor(nAppId, nDstId, nFavor, nMethod);
		KRelation.SyncFriendInfo(nAppId, nDstId);
	end
	
	self:TellPlayerMsg_GC(nAppId);
end

-- ����ҷ�����ʾ��Ϣ
function Relation:TellPlayerMsg_GC(nPlayerId)
	-- todo
	do
		return;
	end
	if (not nPlayerId or nPlayerId <= 0) then
		return;
	end
	
	-- û����Ϣ�Ļ�������
	if (self:CheckInfoMsg() == 0) then
		return;
	end
	local szMsg = self:GetInfoMsg();
	local nOnline = KGCPlayer.OptGetTask(nPlayerId, KGCPlayer.TSK_ONLINESERVER);
	if (nOnline > 0) then
		GSExcute(nOnline, {"Relation:TellPlayerMsg_GS", nPlayerId, szMsg});
	end
end

-- ��������ߵ�ʱ���ȡ���ѹ�ϵ����һ�굽�ڵ���Ϣ�����Ҹ��������ʾ
function Relation:GetCloseFriendTimeInfo_GC(nPlayerId)
	if (nPlayerId <= 0) then
		return;
	end
	
	local tbTimeInfo = KRelation.GetCloseFriendTimeInfo(nPlayerId);
	if (not tbTimeInfo or Lib:CountTB(tbTimeInfo) == 0) then
		return;
	end
	
	local tbInfo = {};
	for i, v in pairs(tbTimeInfo) do
		-- ���ʣ��ʱ����0���ͱ�ʾ�ù�ϵ��Ҫɾ��
		if (v.nTime == 0) then
			KRelation.DelOverTimeRelation(v.nType, nPlayerId, v.nPlayerId, v.bAsMaster);
		end
		
		-- ��ʣ��ʱ�����Ϣ֪ͨ���
		local szPlayerName = KGCPlayer.GetPlayerName(v.nPlayerId);
		if (szPlayerName) then
			local tbTemp = {};
			tbTemp.szPlayerName = szPlayerName;
			tbTemp.nTime = v.nTime;
			tbTemp.nType = v.nType;
			table.insert(tbInfo, tbTemp);
		end
	end
	
	GlobalExecute{"Relation:GetCloseFriendTimeInfo_GS2", nPlayerId, tbInfo};
end

--===================================================

-- ���ܶȵȼ�����֮��Ļص�
function Relation:OnFavorLevelUp(nPlayerAppId, nPlayerDstId, nFavorLevel)
	if (not nPlayerAppId or not nPlayerDstId or not nFavorLevel or
		nPlayerAppId <= 0 or nPlayerDstId <= 0 or nFavorLevel <= 0) then
		return;
	end
	GlobalExecute{"Relation:OnFavorLevelUp_GS", nPlayerAppId, nPlayerDstId, nFavorLevel};
end

-- �����˼ʹ�ϵ֮���ͨ�ûص�
function Relation:ProcessAfterAddRelation_GC(nType, nRole, nAppId, nDstId)
	if (not nType) then
		return;
	end
	
	GlobalExecute{"Relation:ProcessAfterAddRelation_GS", nType, nRole, nAppId, nDstId};
	
	if (not self.tbClass[nType]) then
		return;
	end
	if (not self.tbClass[nType]["ProcessAfterAddRelation_GC"]) then
		return;
	end
	self.tbClass[nType]:ProcessAfterAddRelation_GC(nRole, nAppId, nDstId);
end

-- ɾ���˼ʹ�ϵ֮���ͨ�ûص�
function Relation:ProcessAfterDelRelation_GC(nType, nRole, nAppId, nDstId)
	if (not nType) then
		return;
	end
	
	GlobalExecute{"Relation:ProcessAfterDelRelation_GS", nType, nRole, nAppId, nDstId};
	
	if (not self.tbClass[nType]) then
		return;
	end
	if (not self.tbClass[nType]["ProcessAfterDelRelation_GC"]) then
		return;
	end
	self.tbClass[nType]:ProcessAfterDelRelation_GC(nRole, nAppId, nDstId);
end

--=============================================

-- ͨ�õ��˼�gc����gs��һ���ӿ�
-- ��Ҫ�Ǹ�class����ĸ��־�����˼ʹ�ϵ����
function Relation:CallServerScript_Relation(nType, szFunName, tbParam)
	if (not nType or not szFunName or type(szFunName) ~= "string") then
		return;
	end
	
	GlobalExecute{"Relation:ServerScript_Relation", nType, szFunName, tbParam};
end

-- �˼ʲ��֣�ͨ�õĴ�gs���õ�gc����
function Relation:GCScript_Relation(nType, szFunName, tbParam)
	if (not nType or not szFunName or type(szFunName) ~= "string") then
		return;
	end
	
	if (not self.tbClass[nType]) then
		return;
	end
	if (not self.tbClass[nType][szFunName]) then
		return;
	end
	
	self.tbClass[nType][szFunName](self.tbClass[nType], tbParam);
end
