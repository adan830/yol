-------------------------------------------------------
-- �ļ�������completetask.lua
-- �ļ���������Ҫ���ָ������ [����ֻ����������ٻ�����]
-- �����ߡ���ZhangDeheng
-- ����ʱ�䣺2009-03-06 09:28:22
-------------------------------------------------------
local tb	= Task:GetTarget("CompleteTask");

tb.szTargetName	= "CompleteTask";
tb.REFRESH_FRAME	= 18;	-- һ����һ��

function tb:Init(nTaskGroupId, nTaskId, nNeedCount, szStaticDesc, szDynamicDesc)
	self.nTaskGroupId			= nTaskGroupId;
	self.nTaskId				= nTaskId;
	self.nNeedCount				= nNeedCount;
	self.szStaticDesc			= szStaticDesc or szDynamicDesc;
	self.szDynamicDesc			= szDynamicDesc;
end;

--Ŀ�꿪��
function tb:Start()
	self.bDone		= 0;
	self:Register();
end;

function tb:Save(nGroupId, nStartTaskId)
	self.tbSaveTask	= {	-- ���ﱣ���������Ժ���ʱ��������ͬ���ͻ���
		nGroupId		= nGroupId,
		nStartTaskId	= nStartTaskId,
	};
	self.me.pTask.SetTask(nGroupId, nStartTaskId, self.bDone, 1);
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

function tb:IsDone()
	return self.bDone == 1;
end;



function tb:GetDesc()
	local szMsg = "";
	if (not self:IsDone()) then
		local nCount = self.me.pTask.GetTask(self.nTaskGroupId, self.nTaskId);
		szMsg	= string.format("%s��%d/%d", self.szDynamicDesc, nCount, self.nNeedCount);
	else
		szMsg 	= self.szDynamicDesc .. Lang.task.target.str22[Lang.Idx];
	end;
	return szMsg;
end;

function tb:GetStaticDesc()
	return self.szStaticDesc;
end;

function tb:Close(szReason)
	self:UnRegister();
end;

function tb:Register()
	if (MODULE_GAMESERVER and not self.nRegisterId) then
		self.nRegisterId	= Timer:Register(self.REFRESH_FRAME, self.OnTimer, self);
	end;
end;

function tb:UnRegister()
	if (MODULE_GAMESERVER and self.nRegisterId) then
		Timer:Close(self.nRegisterId);
		self.nRegisterId	= nil;
	end;
end;

function tb:OnTimer()
	local tbSaveTask	= self.tbSaveTask;
	if (MODULE_GAMESERVER and tbSaveTask) then	-- Ҫ��ͻ���ˢ��
		KTask.SendRefresh(self.me, self.tbTask.nTaskId, self.tbTask.nReferId, tbSaveTask.nGroupId);
	end;
	
	if (self.me.pTask.GetTask(self.nTaskGroupId, self.nTaskId) >= self.nNeedCount) then
		self.bDone = 1;
		
		local tbSaveTask	= self.tbSaveTask;
		if (MODULE_GAMESERVER and tbSaveTask) then	-- ����ͬ�����ͻ��ˣ�Ҫ��ͻ���ˢ��
			self.me.pTask.SetTask(tbSaveTask.nGroupId, tbSaveTask.nStartTaskId, self.bDone, 1);
			KTask.SendRefresh(self.me, self.tbTask.nTaskId, self.tbTask.nReferId, tbSaveTask.nGroupId);
		end;
	
		self:UnRegister()	-- ��Ŀ����һ����ɺ󲻻�ʧЧ��
	
		self.tbTask:OnFinishOneTag();
	end
end
