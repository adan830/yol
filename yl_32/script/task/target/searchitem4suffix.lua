
local tb	= Task:GetTarget("SearchItemBySuffix");
tb.szTargetName	= "SearchItemBySuffix";
tb.REFRESH_FRAME	= 18;	-- һ����һ��

function tb:Init(szItemName, szSuffix, nNeedCount, bDelete)
	self.szItemName = szItemName;
	self.szSuffix	= szSuffix;
	
	self.nNeedCount = nNeedCount;
	self.bDelete = bDelete;

end;

function tb:Start()
--	self:Register();
end;

function tb:Save(nGroupId, nStartTaskId)
	self.tbSaveTask	= {	-- ���ﱣ���������Ժ���ʱ��������ͬ���ͻ���
		nGroupId		= nGroupId,
		nStartTaskId	= nStartTaskId,
	};

	return 0;
end;

function tb:Load(nGroupId, nStartTaskId)
	self.tbSaveTask	= {	-- ���ﱣ���������Ժ���ʱ��������ͬ���ͻ���
		nGroupId		= nGroupId,
		nStartTaskId	= nStartTaskId,
	};
	
	self:Register();
	
	return 0;
end;

function tb:IsDone()
	return self:GetCount() >= self.nNeedCount;
end;

function tb:GetDesc()
	local szMsg	= string.format(Lang.task.target.str53[Lang.Idx].."%s��%d/%d", self.szItemName.."��"..self.szSuffix, self:GetCount(), self.nNeedCount);
	return szMsg;
end;

function tb:GetStaticDesc()
	local szMsg	= string.format(Lang.task.target.str53[Lang.Idx].."%s��%d", self.szItemName, self.nNeedCount);
	return szMsg;
end;

function tb:Close(szReason)
	self:UnRegister();
	-- ɾ����Ʒ������������ű���
end;

function tb:Register()
	if (not self.nRegisterId) then
		self.nRegisterId	= Timer:Register(self.REFRESH_FRAME, self.OnTimer, self);
	end;
end;

function tb:UnRegister()
	if (self.nRegisterId) then
		Timer:Close(self.nRegisterId);
		self.nRegisterId	= nil;
	end;
end;

-- ����������Ʒ����
function tb:GetCount()
	return 0;
end;

function tb:OnTimer(nTickCount)
	local nCount	= self:GetCount();
	if (not self.nCount or self.nCount ~= nCount) then
		self.nCount	= nCount;
		
		local tbSaveTask	= self.tbSaveTask;
		if (MODULE_GAMESERVER) then	-- ����ͬ�����ͻ��ˣ�Ҫ��ͻ���ˢ��
			KTask.SendRefresh(self.me, self.tbTask.nTaskId, self.tbTask.nReferId, tbSaveTask.nGroupId);
		end;
		
		if (self:IsDone()) then
			self.tbTask:OnFinishOneTag();
		end
	end;
	
	return self.REFRESH_FRAME;
end;
