
-- ʹ�ÿ�ݼ�Ŀ����
local tb	= Task:GetTarget("UseShortcut");
tb.szTargetName	= "UseShortcut";	--��Ŀ������֣���ʱ��û�õ�


--Ŀ���ʼ��
--���������������༭�����Զ���
function tb:Init()
	
end;

--Ŀ�꿪��
function tb:Start()
	self.bDone = 0;
	self:Register();
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
	return self:GetStaticDesc();
end;

--����Ŀ��ľ�̬�������뵱ǰ��ҽ��е�����޹�
function tb:GetStaticDesc()
	local szMsg	= Lang.task.target.str69[Lang.Idx];
	return szMsg;
end;


function tb:Close(szReason)
	self:UnRegister();
end;

----==== �����Ǳ�Ŀ�������еĺ������壬������ͬ�������ɺ� ====----

function tb:Register()
	assert(self._tbBase._tbBase)	--û�о��������������ű���д����
	local oldPlayer = me;
	me = self.me;
	if (MODULE_GAMESERVER and not self.nRegisterId) then
		self.nRegisterId	= PlayerEvent:Register("OnUseShortcut", self.OnUseShortcut, self);
	end;
	me = oldPlayer;
end;

function tb:UnRegister()
	assert(self._tbBase._tbBase)	--û�о��������������ű���д����
	local oldPlayer = me;
	me = self.me;
	if (MODULE_GAMESERVER and self.nRegisterId) then
		PlayerEvent:UnRegister("OnUseShortcut", self.nRegisterId);
		self.nRegisterId	= nil;
	end;
	me = oldPlayer;
end;


function tb:OnUseShortcut()
	if (self:IsDone()) then
		return;
	end;
	
	self.bDone = 1;
	local tbSaveTask	= self.tbSaveTask;
	if (MODULE_GAMESERVER and tbSaveTask) then	-- ����ͬ�����ͻ��ˣ�Ҫ��ͻ���ˢ��
		self.me.pTask.SetTask(tbSaveTask.nGroupId, tbSaveTask.nStartTaskId, self.bDone, 1);
		KTask.SendRefresh(self.me, self.tbTask.nTaskId, self.tbTask.nReferId, tbSaveTask.nGroupId);
	end;
	if (self:IsDone()) then	-- ��Ŀ����һ����ɺ󲻻�ʧЧ��
		
		self:UnRegister();
		self.tbTask:OnFinishOneTag();
	end;
end;
