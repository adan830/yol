
local tb	= Task:GetTarget("SayWithNpc");
tb.szTargetName	= "SayWithNpc";

function tb:Init(nNpcTempId, nMapId, szOption, szMsg,  szStaticDesc, szDynamicDesc, szBeforePop, szLaterPop)
	self.nNpcTempId	= nNpcTempId;
	self.szNpcName	= KGameBase.GetNameByTemplateId(nNpcTempId);
	self.nMapId		= nMapId;
	self.szMapName	= Task:GetMapName(nMapId);
	self.szOption	= szOption;
	self.tbSayContent = self:ParseSayContent(szMsg);
	
	self.szStaticDesc	= szStaticDesc;
	self.szDynamicDesc	= szDynamicDesc;
	self.szBeforePop	= szBeforePop;
	self.szLaterPop		= szLaterPop;
end;

function tb:ParseSayContent(szAllMsg)
	local tbMsg	= Lib:SplitStr(szAllMsg or "", "<end>");
	table.remove(tbMsg, #tbMsg); -- ���һ���Ϊ""
	return tbMsg;
end;


function tb:Start()
	self.bDone		= 0;
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
	
	if (self.bDone ~= 1) then
		self:Register();
	end
	
	return 1;
end;

function tb:IsDone()
	return self.bDone == 1;
end;

function tb:GetDesc()
	return self.szDynamicDesc or "";
end;

function tb:GetStaticDesc()
	return self.szStaticDesc or "";
end;


function tb:Close(szReason)
	self:UnRegister();
end;


function tb:Register()
	self.tbTask:AddNpcMenu(self.nNpcTempId, self.nMapId, self.szOption, self.OnTalkNpc, self);
end;

function tb:UnRegister()
	self.tbTask:RemoveNpcMenu(self.nNpcTempId);
end;

function tb:OnTalkNpc()
	if (self.nMapId ~= 0 and self.nMapId ~= self.me.GetMapId()) then
		TaskAct:Talk(string.format(Lang.task.target.str49[Lang.Idx],self.szNpcName,self.szMapName))
		return;
	end;
	if (self:IsDone()) then
		return;
	end;
	
	self:StartSay();
end;


function tb:StartSay()
	self:ShowMessage(1);
end;

function tb:ShowMessage(nIdx)
	local szMsg = self.tbSayContent[nIdx];
	szMsg = Lib:ParseExpression(szMsg);
	szMsg = Task:ParseTag(szMsg);
	if (nIdx < #self.tbSayContent) then -- ������
		Dialog:Say(szMsg,
			{
				{Lang.task.target.str51[Lang.Idx], tb.OnSelect, self, nIdx},
			});
	else
		Dialog:Say(szMsg,
			{
				{Lang.task.target.str52[Lang.Idx], tb.OnSelect, self, nIdx},
			});
	end
end;

		

function tb:OnSelect(nIdx)
	if (nIdx < #self.tbSayContent) then
		self:ShowMessage(nIdx + 1);
		return;
	end
	
	self.bDone	= 1;
	local tbSaveTask	= self.tbSaveTask;
	if (MODULE_GAMESERVER and tbSaveTask) then	-- ����ͬ�����ͻ��ˣ�Ҫ��ͻ���ˢ��
		self.me.pTask.SetTask(tbSaveTask.nGroupId, tbSaveTask.nStartTaskId, self.bDone, 1);
		KTask.SendRefresh(self.me, self.tbTask.nTaskId, self.tbTask.nReferId, tbSaveTask.nGroupId);
	end;
	
	
	
	if (not self.szRepeatMsg) then
		self:UnRegister()	-- ��Ŀ����һ����ɺ󲻻�ʧЧ��
	end;

	self.tbTask:OnFinishOneTag();
	
	return;
end;




