
local tb	= Task:GetTarget("JoinFaction");
tb.szTargetName	= "JoinFaction";

function tb:Init(nFactionId, szDynamicDesc, szStaticDesc)
	self.nFactionId 		= nFactionId;
	self.szDynamicDesc		= szDynamicDesc;
	self.szStaticDesc		= szStaticDesc;	
end;



function tb:Start()
	self.bDone		= 0;
	
	if (self.nFactionId == 0) then
		if (self.me.nFaction > 0) then
			self.bDone = 1;
		end
	else
		if (self.me.nFaction == self.nFactionId) then
			self.bDone = 1;
		end
	end
	if (self.bDone == 1) then
		local tbSaveTask	= self.tbSaveTask;
		if (MODULE_GAMESERVER and tbSaveTask) then	-- ����ͬ�����ͻ��ˣ�Ҫ��ͻ���ˢ��
			self.me.pTask.SetTask(tbSaveTask.nGroupId, tbSaveTask.nStartTaskId, self.bDone, 1);
			KTask.SendRefresh(self.me, self.tbTask.nTaskId, self.tbTask.nReferId, tbSaveTask.nGroupId);
		end;
		self.tbTask:OnFinishOneTag();
	else
		self:Register();	
	end	 
	
end;


function tb:Save(nGroupId, nStartTaskId)
	self.tbSaveTask	= {	-- ���ﱣ���������Ժ���ʱ��������ͬ���ͻ���
		nGroupId		= nGroupId,
		nStartTaskId	= nStartTaskId,
	};
	self.me.pTask.SetTask(nGroupId, nStartTaskId, self.bDone);
	return 1;
end;


function tb:Load(nGroupId, nStartTaskId)
	self.tbSaveTask	= {	-- ���ﱣ���������Ժ���ʱ��������ͬ���ͻ���
		nGroupId		= nGroupId,
		nStartTaskId	= nStartTaskId,
	};
	self.bDone		= self.me.pTask.GetTask(nGroupId, nStartTaskId);
	if (not self:IsDone()) then	-- ��Ŀ����һ����ɺ󲻻�ʧЧ��
		self:Register();
	end;
	return 1;
end;

--����Ŀ���Ƿ���
function tb:IsDone()
	return self.bDone == 1;
end;

--����Ŀ������е��������ͻ��ˣ�
function tb:GetDesc()
	return self.szDynamicDesc or "";
end;


--����Ŀ��ľ�̬�������뵱ǰ��ҽ��е�����޹�
function tb:GetStaticDesc()
	return self.szStaticDesc or "";
end;



function tb:Close(szReason)
	self:UnRegister();
end;


function tb:Register()
	assert(self._tbBase._tbBase)	--û�о��������������ű���д����
	local oldPlayer = me;
	me = self.me;
	if (MODULE_GAMESERVER and not self.nRegisterId) then
		self.nRegisterId	= PlayerEvent:Register("OnFactionChange", self.OnFactionChange, self);
	end;
	me = oldPlayer;
end;


function tb:UnRegister()
	assert(self._tbBase._tbBase)	--û�о��������������ű���д����
	local oldPlayer = me;
	me = self.me;
	if (MODULE_GAMESERVER and self.nRegisterId) then
		PlayerEvent:UnRegister("OnFactionChange", self.nRegisterId);
		self.nRegisterId	= nil;
	end;
	me = oldPlayer;
end;

function tb:OnFactionChange(nFactionId)
	if (self:IsDone()) then
		return;
	end
	
	if (self.nFactionId == 0) then
		if (self.me.nFaction > 0) then
			self.bDone = 1;
		end
	else
		if (self.me.nFaction == self.nFactionId) then
			self.bDone = 1;
		end
	end
	
	local tbSaveTask	= self.tbSaveTask;
	if (MODULE_GAMESERVER and tbSaveTask) then	-- ����ͬ�����ͻ��ˣ�Ҫ��ͻ���ˢ��
		self.me.pTask.SetTask(tbSaveTask.nGroupId, tbSaveTask.nStartTaskId, self.bDone, 1);
		KTask.SendRefresh(self.me, self.tbTask.nTaskId, self.tbTask.nReferId, tbSaveTask.nGroupId);
	end;
	
	self:UnRegister();
	self.tbTask:OnFinishOneTag();
end
