-- ��ָ����Npc�Ի�����������talknpcĿ��һ���������ָ����NpcҪ����һ��ָ��ս��Npc���ܳ�����
-- ָ���Ի�Npc����һ��ʱ��ᱻɾ����Ȼ�����ʱ��ս��Npc�ᱻ���

local tb	= Task:GetTarget("Fight2Dialog");
tb.szTargetName	= "Fight2Dialog";


-- ��ͼId,ս��Npcģ��,�Ի�Npcģ��,�Ի�ѡ��,�Ի�����,�ظ��Ի����Ի�Npc����ʱ��,Ŀ�����ǰ���ݣ�Ŀ����ɺ�����
function tb:Init(nMapId, nMapPosX, nMapPosY, nMapPosZ, nFightNpcTempId, nFightNpcLevel, nDialogNpcTempId, szOption, szMsg, szRepeatMsg, nDialogDuration, szBeforePop, szLaterPop)
	self.nMapId				= nMapId;
	self.szMapName			= Task:GetMapName(nMapId);
	self.nMapPosX			= nMapPosX;
	self.nMapPosY			= nMapPosY;
	self.nMapPosZ			= nMapPosZ;
	self.nFightNpcTempId	= nFightNpcTempId;
	self.szFightNpcName		= KGameBase.GetNameByTemplateId(nFightNpcTempId);
	self.nFightNpcLevel		= nFightNpcLevel;
	self.nDialogNpcTempId	= nDialogNpcTempId;
	self.szDialogNpcName	= KGameBase.GetNameByTemplateId(nDialogNpcTempId);
	self.szOption			= szOption;
	self.szMsg				= szMsg;
	self.szRepeatMsg		= szRepeatMsg;
	self.nDialogDuration	= nDialogDuration;
	self.szBeforePop		= szBeforePop;
	self.szLaterPop			= szLaterPop;
	self:IniTarget();
end;


---------------------------------------------------------------------
function tb:IniTarget()
	if (MODULE_GAMESERVER) then
		if (not self.bAddFight or self.bAddFight == 0) then
			local pFightNpc	= KGameBase.CallNpc(self.nFightNpcTempId, self.nMapId, self.nMapPosX, self.nMapPosY, self.nMapPosZ);
			if (not pFightNpc) then
				return;
			end
			pFightNpc.SetLevel(self.nFightNpcLevel); -- todo simon
			self.nFightNpcId = pFightNpc.dwId;
			Npc:RegPNpcOnDeath(pFightNpc, self.OnDeath, self);
			Timer:Register(Env.GAME_FPS * 60, self.OnCheckNpcExist, self);
			self.bAddFight = 1; -- ȷ��ֻ���һ��
		end
	end
end;

-- ���ڷ�ֹ�������Npc��ʧ
function tb:OnCheckNpcExist()
	if (Task:IsNpcExist(self.nDialogNpcId, self) == 1) then
		return;
	end
	
	if (Task:IsNpcExist(self.nFightNpcId, self) == 1) then
		return;
	end
	if (self.nReviveDurationTimeId) then
		return;
	end
	
	print("TaskNpcMiss", self.nDialogNpcId, self.nFightNpcId, self.nReviveDurationTimeId);
	self.nDialogNpcId = nil;
	self.nFightNpcId  = nil;
	
	self:AddFightNpc();
end


-- ��һ���������Ŀ�����һ�ע��һ��ս��Npc��֮�����������ֻ�
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
	
	if (not self:IsDone() or self.szRepeatMsg) then	-- ��Ŀ����һ����ɺ󲻻�ʧЧ��
		self:Register();
		assert(self._tbBase._tbBase)
	end;
	return 1;
end;

function tb:IsDone()
	return self.bDone == 1;
end;

function tb:GetDesc()
	return self:GetStaticDesc();
end;

function tb:GetStaticDesc()
	local szMsg = Lang.task.target.str16[Lang.Idx];
	szMsg = szMsg..self.szFightNpcName..Lang.task.target.str24[Lang.Idx];
	
	szMsg = szMsg..Lang.task.target.str25[Lang.Idx];
	if (self.nMapId ~= 0) then
		szMsg	= szMsg..self.szMapName..Lang.task.target.str17[Lang.Idx];
	end;
	szMsg	= szMsg..string.format(Lang.task.target.str26[Lang.Idx], self.szDialogNpcName);
	return szMsg;
end;

function tb:Close(szReason)
	self:UnRegister();
end;


function tb:Register()
	assert(self._tbBase._tbBase)
	
	self.tbTask:AddNpcMenu(self.nDialogNpcTempId, self.nMapId, self.szOption, self.OnTalkNpc, self);
end;

function tb:UnRegister()
	assert(self._tbBase._tbBase)
	
	self.tbTask:RemoveNpcMenu(self.nDialogNpcTempId);
end;


function tb:OnTalkNpc()
	if (not him) then
		return;
	end;
	
	assert(self._tbBase._tbBase)

	if (self.nMapId ~= 0 and self.nMapId ~= self.me.GetMapId()) then
		TaskAct:Talk(string.format(Lang.task.target.str5[Lang.Idx],self.szDialogNpcName,self.szMapName))
		return;
	end
		
	if (self:IsDone()) then
		if (self.szRepeatMsg) then
			TaskAct:Talk(self.szRepeatMsg);
		end
		
		return;
	end
	
	TaskAct:Talk(self.szMsg, self.OnTalkFinish, self);
end



function tb:OnTalkFinish()
	assert(self._tbBase._tbBase)
	self.bDone	= 1;
	local tbSaveTask	= self.tbSaveTask;
	if (MODULE_GAMESERVER and tbSaveTask) then	-- ����ͬ�����ͻ��ˣ�Ҫ��ͻ���ˢ��
		self.me.pTask.SetTask(tbSaveTask.nGroupId, tbSaveTask.nStartTaskId, self.bDone, 1);
		KTask.SendRefresh(self.me, self.tbTask.nTaskId, self.tbTask.nReferId, tbSaveTask.nGroupId);
	end;
	
	self.tbTask:OnFinishOneTag();
	
	if (not self.szRepeatMsg) then
		self:UnRegister()	-- ��Ŀ����һ����ɺ󲻻�ʧЧ��
	end;
end;


function tb:RiseDialogNpc(pFightNpc)
	assert(self._tbBase)
	assert(self._tbBase._tbBase == nil)
	
	-- ��ս��Npc��λ����ӶԻ�Npc
	local nCurMapId, nCurPosX, nCurPosY, nCurPosZ = pFightNpc.GetWorldPos();
	local pDialogNpc = KGameBase.CallNpc(self.nDialogNpcTempId, nCurMapId, nCurPosX, nCurPosY, nCurPosZ);
	assert(pDialogNpc);
	self.nDialogNpcId = pDialogNpc.dwId;
	Task.tbToBeDelNpc[self.nDialogNpcId] = 1;
	-- ָ��ʱ���ɾ���Ի�Npc�������ս��Npc
	if (MODULE_GAMESERVER) then
		self.nReviveDurationTimeId = Timer:Register(Env.GAME_FPS * self.nDialogDuration, self.Dialog2Fight, self);
	end;
end;


-- �Ի�תս��
function tb:Dialog2Fight()
	assert(not self.nFightNpcId);
	assert(self._tbBase)
	assert(self._tbBase._tbBase == nil)
	assert(MODULE_GAMESERVER);
	-- ��������assert����ظ�����
	if (not self.nReviveDurationTimeId) then
		return 0;
	end
	
	self.nReviveDurationTimeId = nil;
	
	-- ɾ������Ի�Npc
	if (self.nDialogNpcId) then
		local pDialogNpc = KGameBase.GetNpcById(self.nDialogNpcId);
		assert(pDialogNpc);
		Task.tbToBeDelNpc[self.nDialogNpcId] = 0;
		KGameBase.RemoveNpc(self.nDialogNpcId);
		self.nDialogNpcId = nil;
	else
		assert(false);
	end
	
	self:AddFightNpc();
	return 0;
end;

-- ���һ��ս��Npc
function tb:AddFightNpc()
	assert(not self.nDialogNpcId);
	assert(not self.nFightNpcId);
	assert(not self._tbBase._tbBase);
	assert(self._tbBase);
	
	local pFightNpc	= KGameBase.CallNpc(self.nFightNpcTempId, self.nMapId, self.nMapPosX, self.nMapPosY, self.nMapPosZ);
	assert(pFightNpc);
	pFightNpc.SetLevel(self.nFightNpcLevel); -- todo simon
	self.nFightNpcId = pFightNpc.dwId; 
	Npc:RegPNpcOnDeath(pFightNpc, self.OnDeath, self);
end


-- OnDeath����tb._tbBase����
function tb:OnDeath()
	assert(self._tbBase)
	assert(not self._tbBase._tbBase)
	
	if (self.nFightNpcId and him.dwId == self.nFightNpcId) then
		self.nFightNpcId = nil;
		self:RiseDialogNpc(him);
	else
		assert(false);
	end
end;
