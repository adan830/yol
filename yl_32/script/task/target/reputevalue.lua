
local tb	= Task:GetTarget("ReputeValue");
tb.szTargetName	= "ReputeValue";
tb.REFRESH_FRAME	= 18;	-- һ����һ��

function tb:Init(nCampId, nClassId, nValue, szStaticDesc, szDynamicDesc, nLevel)
	self.nCampId			= nCampId;
	self.nClassId			= nClassId;
	self.nValue				= nValue;
	self.nLevel				= tonumber(nLevel) or 1;
	if self.nLevel == 0 then
		self.nLevel = 1;
	end
	self.szStaticDesc		= szStaticDesc;
	self.szDynamicDesc		= szDynamicDesc;
end;


--Ŀ�꿪��
function tb:Start()
		self.bDone		= 0;
		self:Register();
end;

--Ŀ�걣��
--�������������Id��nGroupId���Լ����ڱ�����ʼId��nStartTaskId�������汾Ŀ�������������
--����ʵ�ʴ���ı�������
function tb:Save(nGroupId, nStartTaskId)
	self.tbSaveTask	= {	-- ���ﱣ���������Ժ���ʱ��������ͬ���ͻ���
		nGroupId		= nGroupId,
		nStartTaskId	= nStartTaskId,
	};
	self.me.pTask.SetTask(nGroupId, nStartTaskId, self.bDone, 1);
	
	return 1;
end;

--Ŀ������
--�������������Id��nGroupId���Լ����ڱ�����ʼId��nStartTaskId�������뱾Ŀ�������������
--����ʵ������ı�������
function tb:Load(nGroupId, nStartTaskId)	
	self.tbSaveTask	= {	-- ���ﱣ���������Ժ���ʱ��������ͬ���ͻ���
		nGroupId		= nGroupId,
		nStartTaskId	= nStartTaskId,
	};
	self.bDone		= self.me.pTask.GetTask(nGroupId, nStartTaskId);
	
	if (self.bDone ~= 1) then
		self:Register();
	end
	
	return 1;
end;

--����Ŀ���Ƿ���
function tb:IsDone()
	return self.bDone == 1;
end;

--����Ŀ������е��������ͻ��ˣ�
function tb:GetDesc()
	return self.szDynamicDesc;
end;


--����Ŀ��ľ�̬�������뵱ǰ��ҽ��е�����޹�
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
	if (
			(self.me.GetReputeLevel(self.nCampId, self.nClassId) > self.nLevel) or 
	   		((self.me.GetReputeLevel(self.nCampId, self.nClassId) == self.nLevel) and (self.me.GetReputeValue(self.nCampId, self.nClassId) >= self.nValue))
	   	)then
		
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

