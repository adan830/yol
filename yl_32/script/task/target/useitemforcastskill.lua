
local tb	= Task:GetTarget("CastSkill");
tb.szTargetName	= "CastSkill";

-- ����Id,����Id
function tb:Init(tbItemId, nSkillId)
	if (tbItemId[1] ~= 20) then
		print("[Task Error]"..self.szTargetName..Lang.task.target.str66[Lang.Idx])
	end
	
	self.tbItemId	= tbItemId;
	self.szItemName	= KItem.GetNameById(unpack(tbItemId));
	self.nSkillId	= nSkillId;
	self.nParticular = tbItemId[3];
end;


--Ŀ�꿪��
function tb:Start()
	self.bDone		= 0;
	self:Register();
	if (MODULE_GAMESERVER) then	-- ����˿���������Ʒ
		if (Task:GetItemCount(self.me, self.tbItemId) <= 0) then
			Task:AddItem(self.me, self.tbItemId);
		end
	end
end;

--Ŀ�걣��
--�������������Id��nGroupId���Լ����ڱ�����ʼId��nStartTaskId�������汾Ŀ�������������
--����ʵ�ʴ���ı�������
function tb:Save(nGroupId, nStartTaskId)
	self.tbSaveTask	= {	-- ���ﱣ���������Ժ���ʱ��������ͬ���ͻ���
		nGroupId		= nGroupId,
		nStartTaskId	= nStartTaskId,
	};
	self.me.pTask.SetTask(nGroupId, nStartTaskId, self.bDone);
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
	if (not self:IsDone()) then	-- ��Ŀ����һ����ɺ󲻻�ʧЧ��
		self:Register();
		if (MODULE_GAMESERVER) then	-- ����˿���������Ʒ
			if (Task:GetItemCount(self.me, self.tbItemId) <= 0) then
				Task:AddItem(self.me, self.tbItemId);
			end
		end
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
	return "ʹ��"..self.szItemName;
end;


--Ŀ��ֹͣ
--	szReason��ֹͣ��ԭ��
--		"logout"	�������
--		"finish"	�������
--		"giveup"	��ҷ�������
--		"failed"	����ʧ��
--		"refresh"	�ͻ���ˢ��
function tb:Close(szReason)
	self:UnRegister();
	if (MODULE_GAMESERVER) then	-- ����˿����ɾ����Ʒ����ɵĻ������˲��ɾ
		if (szReason == "giveup" or szReason == "failed") then
			Task:DelItem(self.me, self.tbItemId, 1);
		end;
	end;
end;

----==== �����Ǳ�Ŀ�������еĺ������壬������ͬ�������ɺ� ====----

function tb:Register()
	self.tbTask:AddItemUse(self.nParticular, self.OnTaskItem, self)
end;


function tb:UnRegister()
	self.tbTask:RemoveItemUse(self.nParticular);
end;


function tb:OnTaskItem()
	if (self:IsDone()) then
		return nil;
	end
	
	self.me.CastSkill(self.nSkillId, 1, -1, self.me.GetNpc().nIndex);

	-- ɾ��Ʒ
	Task:DelItem(self.me, self.tbItemId, 1);
	
	self.bDone = 1;
	local tbSaveTask	= self.tbSaveTask;
	if (MODULE_GAMESERVER and tbSaveTask) then	-- ����ͬ�����ͻ��ˣ�Ҫ��ͻ���ˢ��
		self.me.pTask.SetTask(tbSaveTask.nGroupId, tbSaveTask.nStartTaskId, self.bDone, 1);
		KTask.SendRefresh(self.me, self.tbTask.nTaskId, self.tbTask.nReferId, tbSaveTask.nGroupId);
	end;
	
	
	
	if (not self.szRepeatMsg) then
		self:UnRegister()	-- ��Ŀ����һ����ɺ󲻻�ʧЧ��
	end;
	self.tbTask:OnFinishOneTag();
end;


