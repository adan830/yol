
local tb	= Task:GetTarget("Send2NewWorld");
tb.szTargetName	= "Send2NewWorld";


-- ��ͼId����ͼX���꣬��ͼY���꣬�ɴ��ʹ�����
function tb:Init(nMapId, nPosX, nPosY, nPosZ, nTotalTimes)
	self.nMapId			= nMapId;
	self.nPosX			= nPosX;
	self.nPosY			= nPosY;
	self.nPosZ			= nPosZ;
	self.nTotalTimes	= nTotalTimes;
	self.szMapName		= Task:GetMapName(nMapId);
end;



--Ŀ�꿪��
function tb:Start()
	self.nCount		= 0;
end;

--Ŀ�걣��
function tb:Save(nGroupId, nStartTaskId)
	self.tbSaveTask	= {	-- ���ﱣ���������Ժ���ʱ��������ͬ���ͻ���
		nGroupId		= nGroupId,
		nStartTaskId	= nStartTaskId,
	};
	self.me.pTask.SetTask(nGroupId, nStartTaskId, self.nCount);
	
	return 1;
end;

--Ŀ������
function tb:Load(nGroupId, nStartTaskId)
	self.tbSaveTask	= {	-- ���ﱣ���������Ժ���ʱ��������ͬ���ͻ���
		nGroupId		= nGroupId,
		nStartTaskId	= nStartTaskId,
	};
	self.nCount		= self.me.pTask.GetTask(nGroupId, nStartTaskId);
	
	return 1;
end;

--����Ŀ���Ƿ���
function tb:IsDone()
	return 1;
end;

--����Ŀ������е��������ͻ��ˣ�
function tb:GetDesc()
	return self:GetStaticDesc();
end;


--����Ŀ��ľ�̬�������뵱ǰ��ҽ��е�����޹�
function tb:GetStaticDesc()
	return "";
end;

function tb:Close(szReason)
	
end;


----==== �����Ǳ�Ŀ�������еĺ������壬������ͬ�������ɺ� ====----

-- �����Դ��Ͷ��ٴ�
function tb:GetLeaveTime()
	if (self.nTotalTimes < 0) then
		return 1;
	end
	
	return self.nTotalTimes - self.nCount;
end;

-- ����
function tb:Send2NewWrold()
	if (self:GetLeaveTime() <= 0) then
		self.me.SysMsg(Lang.task.target.str58[Lang.Idx]);
		return 0;
	end

	self.me.TeleportTo(self.nMapId, self.nPosX, self.nPosY, self.nPosZ);
	self.nCount = self.nCount + 1;
	self.me.SysMsg(Lang.task.target.str59[Lang.Idx]..self:GetLeaveTime());
	
	return 1;
end;
