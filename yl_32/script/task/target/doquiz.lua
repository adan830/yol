-- by KK
-- quiz���飬����answerthequestion�ش����⣬��ͬ���ǣ�������ϸ�, ����������ģ�飨����ʹ��
-- ��Ŀѡ��ÿ�ξ������ң��ͻ���û�б���𰸣���������
local tb = Task:GetTarget("DoQuiz")
tb.szTargetName = "DoQuiz"

--
function tb:Init(nNpcTempId, nMapId, szOption, nQuizId, nErrorLimit, szPreMsg, szEndMsg, szDesc)
	-- ��������
	self.nNpcTempId = nNpcTempId
	self.nMapId = nMapId
	self.szOption = szOption
	self.nQuizId = nQuizId
	self.nErrorLimit = nErrorLimit
	self.szEndMsg = szEndMsg
	self.szPreMsg = szPreMsg
	self.szDesc = szDesc
end

function tb:Start()
	self.bDone = 0;
	self:Register()
end
-------------------------------------------����
function tb:Save(nGroupId, nStartTaskId)
	self.tbSaveTask	= {	-- ���ﱣ���������Ժ���ʱ��������ͬ���ͻ���
		nGroupId		= nGroupId,
		nStartTaskId	= nStartTaskId,
	};
	self.me.pTask.SetTask(nGroupId, nStartTaskId, self.bDone);
	return 1;
end

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
end

------------------------npc�Ի��˵�
function tb:Register()
	self.tbTask:AddNpcMenu(self.nNpcTempId, self.nMapId, self.szOption, self.OnTalkNpc, self);
end
function tb:UnRegister()
	self.tbTask:RemoveNpcMenu(self.nNpcTempId);
end

---------------------------------����
function tb:GetDesc()
	print("tb:GetDesc()", self.szDesc)
	return self.szDesc or "";
end;
function tb:GetStaticDesc()
  print("tb:GetStaticDesc()", self.szDesc)
	return self.szDesc or "";
end;
function tb:Close(szReason)
	self:UnRegister();
end;

function tb:OnFinishPreDialog()
    self:StartQuiz()
end

--------------------------------npc�Ի�����
function tb:OnTalkNpc()
	if (self.nMapId ~= 0 and self.nMapId ~= self.me.dwSceneTemplateId) then
		TaskAct:Talk(string.format(Lang.task.target.str5[Lang.Idx],self.szNpcName,self.szMapName))
		return;
	end;
	print("tb:OnTalkNpc", self.bFinishedPreDialog, self.szPreMsg, self.bFinishedEndDialog,self.szEndMsg)
	TaskAct:Talk(self.szPreMsg, self.OnFinishPreDialog, self);
	--[[if (self:IsDone()) then
		if (self.bFinishedEndDialog == 0) then
			TaskAct:Talk(self.szEndMsg);
			self.bFinishedEndDialog = 1;
			return;
		end
	end;--]]
end

-- �����������
function tb:StartQuiz()
	self.nErrorCount = 0  -- ��������������ͳ��
	self.me.pQuiz.CallQuiz(self.nQuizId) -- ����
end

-- �Ƿ����
function tb:IsDone()
	return self.bDone == 1
end

function tb:OnShowEndDialog()
    TaskAct:Talk(self.szEndMsg, self.OnFinishEndDialog, self);
    return 0;
end

function tb:OnFinishEndDialog()
	self:DoRightChoiceHandle()
end

-- C++�������ģ�ѡ����Ŀ����Ӧ
function tb:OnQuizChoice(pPlayer, bRight)
	if (bRight == 1) then
		-- ��Ŀ����, �����������
		self.bDone = 1
		Timer:Register(Env.GAME_FPS * 2, self.OnShowEndDialog, self) -- 3�����ʾ�����Ի�
	else
		-- ��Ŀ����
		--self.me.SysMsg("��Ŀ����")
		self.nErrorCount = self.nErrorCount + 1  -- �������ͳ��+1
	end

	-- ��������Ѿ��ﵽ����������
	if (self.nErrorCount >= self.nErrorLimit) then
		self.me.pQuiz.SendClientResult(0, 1)  -- ���߿ͻ��˴�����󣬲��ر���壡
		self.me.SysMsg(Lang.task.target.str23[Lang.Idx])
	end
end

-- ��Ժ�Ĵ���TODO:�ӳ�2��������
function tb:DoRightChoiceHandle()
	local tbSaveTask	= self.tbSaveTask;
	if (MODULE_GAMESERVER and tbSaveTask) then	-- ����ͬ�����ͻ��ˣ�Ҫ��ͻ���ˢ��
		self.me.pTask.SetTask(tbSaveTask.nGroupId, tbSaveTask.nStartTaskId, self.bDone, 1);
		KTask.SendRefresh(self.me, self.tbTask.nTaskId, self.tbTask.nReferId, tbSaveTask.nGroupId);
	end;
	if (not self.szRepeatMsg) then
		self:UnRegister()	-- ��Ŀ����һ����ɺ󲻻�ʧЧ��
	end;

	self.tbTask:OnFinishOneTag();
end
