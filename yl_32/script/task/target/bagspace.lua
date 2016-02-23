
local tb	= Task:GetTarget("BagSpace");
tb.szTargetName	= "BagSpace";
tb.REFRESH_FRAME	= 18;	-- һ����һ��

function tb:Init(nBagType, nNeedSpaceCount)
	self.nBagType			= nBagType;
	self.nNeedSpaceCount	= nNeedSpaceCount;
end;

function tb:Start()
	-- nothing
end;

function tb:Save(nGroupId, nStartTaskId)
	self.nGroupId = nGroupId;
	return 0;
end;

function tb:Load(nGroupId, nStartTaskId)
	self:Register();
	self.nGroupId = nGroupId;
	return 0;
end;

function tb:IsDone()
	return self:GetBagSpaceCount() >= self.nNeedSpaceCount;
end;




function tb:GetDesc()
	local szMsg	= string.format(Lang.task.target.str10[Lang.Idx], Lang.task.target.str12[Lang.Idx], self:GetBagSpaceCount(), self.nNeedSpaceCount);
	return szMsg;
end;

function tb:GetStaticDesc()
	local szMsg	= string.format(Lang.task.target.str11[Lang.Idx], Lang.task.target.str12[Lang.Idx], self.nNeedSpaceCount);
	return szMsg;
end;

function tb:Close(szReason)
	self:UnRegister();
end;

function tb:Register()
	-- �ͻ���ʵʱ�����Ʒ����
	if (MODULE_GAMECLIENT) then
		if (not self.nRegisterId) then
			self.nRegisterId	= Timer:Register(self.REFRESH_FRAME, self.OnTimer, self);
			self.nCount			= self:GetBagSpaceCount();
		end;
	end;
end;

function tb:UnRegister()
	-- �ͻ��˹ر�ʵʱ����
	if (MODULE_GAMECLIENT) then
		if (self.nRegisterId) then
			Timer:Close(self.nRegisterId);
			self.nRegisterId	= nil;
		end;
	end;
end;


function tb:OnTimer(nTickCount)
	if (self:GetBagSpaceCount() ~= self.nCount) then
		self.nCount = self:GetBagSpaceCount();
	else
		return self.REFRESH_FRAME;
	end;
	
	if (MODULE_GAMESERVER) then	-- ����ͬ�����ͻ��ˣ�Ҫ��ͻ���ˢ��
		KTask.SendRefresh(self.me, self.tbTask.nTaskId, self.tbTask.nReferId, self.nGroupId);
	end;
	
	-- UNDONE:�������Զ��������ϳ���
--[[	
	if (self:IsDone()) then
		self.tbTask:OnFinishOneTag();
	end
--]]
	
	return self.REFRESH_FRAME;
end;


function tb:GetBagSpaceCount()
	if (MODULE_GAMESERVER) then	-- �����ÿ�����¼���
		return me.pItem.CalcFreeItemCellCount();
	else	-- �ͻ��˼���Ƶ��ʹ�û���
		return self.nCount;
	end;
end;
