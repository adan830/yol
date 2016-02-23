
--һ��������������ϣ������ʽ
local tbClassBase	= {};
Task._tbClassBase	= tbClassBase;

function tbClassBase:GetName()
	return self.tbReferData.szName;
end;

-- �õ���ǰ���� 
function tbClassBase:GetCurStep()
	return self.tbSubData.tbSteps[self.nCurStep];
end;

-- �����Npc������û�жԻ�(tbNpcMenu)����еĻ������ѡ����򷵻�nil (��������Ի�)
function tbClassBase:AppendNpcMenu(nNpcTempId, tbOption, pNpc)
	local tbNpcMenuData	= self.tbNpcMenus[nNpcTempId];
	if (not tbNpcMenuData) then
		return nil;
	end
	
	if (pNpc.dwSceneTemplateId ~= tbNpcMenuData.dwSceneTemplateId and tbNpcMenuData.dwSceneTemplateId ~= 0) then
		return nil;
	end
	
	local tbNpcMenu = tbNpcMenuData.tbCallBack;
	
	assert(type(tbNpcMenu[1]) == "string" );
	
	if (tbOption) then
		tbOption[#tbOption + 1]	= tbNpcMenu;
	end;
	
	return 1;
end;


function tbClassBase:CheckTaskOnNpc()
	if (self.tbNpcMenus[him.nTemplateId] and ((him.dwSceneTemplateId == self.tbNpcMenus[him.nTemplateId].dwSceneTemplateId) or self.tbNpcMenus[him.nTemplateId].dwSceneTemplateId == 0)) then
		return 1;
	end
	
	return nil;
end


function tbClassBase:OnExclusiveDialogNpc(nNpcTempId)
	local tbDialogTrigger = self.tbNpcExclusiveDialogs[nNpcTempId];
	if (not tbDialogTrigger) then
		return nil;
	end
	Lib:CallBack(tbDialogTrigger);
end

-- ��Ʒ����
function tbClassBase:OnTaskItem(nParticular)
	local tbItemUse	= self.tbItemUse[nParticular];
	if (not tbItemUse) then
		return nil;
	end;
	Lib:CallBack(tbItemUse);
	return 1;
end;

-- ���һ��Ŀ���ʱ��ִ�У����ж��Ƿ��¼�Ϊ�Զ�������������ִ����һ���衣
function tbClassBase:OnFinishOneTag()
	local tbStep	= self:GetCurStep();
	if (not tbStep) then
		return "No Cur Step!";
	end;

	if (tbStep.tbEvent.nType == 3) then
		assert(self.nCurStep > 0);
		for _, tbCurTag in ipairs(self.tbCurTags) do
			if (not tbCurTag:IsDone()) then
				return;
			end;
		end;

		self:GoNextStep();
	end
end;


function tbClassBase:Active()
	for _, tbCurTag in ipairs(self.tbCurTags) do
		if (not tbCurTag:IsDone()) then
			return;
		end
	end
	local bOK, szMsg	= self:IsCurStepDone();
	if (not bOK) then
		Dialog:SendInfoBoardMsg(self.me, szMsg);
		return nil;
	end;

	self:GoNextStep()
	
	return 1;
end;

function tbClassBase:IsCurStepDone()
	local tbStep	= self:GetCurStep();
	if (not tbStep) then
		return nil;
	end;
	if (not tbStep.tbJudge) then
		return 1;
	end;
	return Lib:DoTestFuncs(tbStep.tbJudge);
end;

function tbClassBase:GoNextStep()
	assert(self.nCurStep > 0);
	for _, tbCurTag in ipairs(self.tbCurTags) do
		if (not tbCurTag:IsDone()) then
			Dialog:SendInfoBoardMsg(self.me, string.format(Lang.task.str4[Lang.Idx],tbCurTag:GetStaticDesc()));
			return;
		end;
	end;
	local tbStep	= self:GetCurStep();
	local tbStepEvent = tbStep.tbEvent;
	if (tbStepEvent.nType == 2) then
		local tbItemId = {20,1,tbStepEvent.nValue,1};
		if (not Task:DelItem(self.me, tbItemId, 1)) then
			self.me.SysMsg(string.format(Lang.task.str5[Lang.Idx]))
			return nil;
		end
	end
	
	if (tbStep.tbExecute) then
		local oldPlayer = me;
		me = self.me;
		
		Lib:DoExecFuncs(tbStep.tbExecute, self.nTaskId);
		me = oldPlayer;
	end;
	self:CloseCurStep("finish");
	--self.me.SysMsg("������ɡ�");
	
	--self.me.CastSkill(Task.nFinishStepSkillId,1,-1, self.me.GetNpc().nIndex);

	self:SetCurStep(self.nCurStep + 1);
	return 1;
end;

-- ���õ�ǰ���裬������ǰĿ�� (����������������������)
function tbClassBase:SetCurStep(nStep, bLoading)
	local oldPlayer = me;
	me = self.me;
	local tbCurTags	= {};
	self.tbCurTags	= tbCurTags;
	self.tbNpcMenus	= {}; --�±�ΪNpcģ��Id
	self.tbNpcExclusiveDialogs = {};
	self.tbItemUse	= {};
	self.tbCollectList = {};
	self.nCurStep		= nStep;
	local tbStep		= self:GetCurStep();
	if (tbStep) then --���в��裬˵����û�����������
		local tbStepDesc	= self.tbReferData.tbStepsDesc;
		local szStepDesc		= nil;
		if (tbStepDesc and tbStepDesc[nStep]) then
			szStepDesc = tbStepDesc[nStep];
			--me.SysMsg(string.format("Step %d: %s", nStep, tbStepDesc[nStep])) modify by NN
		end

		local tbEvent	= tbStep.tbEvent;
		if (tbEvent.nType == 1) then --�������Ϊnpc
			self:AddNpcMenu(tbEvent.nValue, 0, self:GetName(),
				TaskAct.Talk, TaskAct, {self.GetNpcDialog, self},
				Task.Active, Task, self.nTaskId, self.nReferId, nStep);
		elseif (tbEvent.nType == 2) then --�������ΪItem
			self:AddItemUse(tbEvent.nValue,
				Task.Active, Task, self.nTaskId, self.nReferId, nStep);
		end;
		local nSaveLen	= Task.emSAVEID_TARGET_BEGIN; --����ĳ��ȴ�5��ʼ��֮ǰ4��Ϊ����Id,����������Id,��ǰ���裬������ʱ��

		for i, tbTarget in ipairs(tbStep.tbTargets) do
			local tbCurTag	= Lib:NewClass(tbTarget); -- Ŀ��ĵ�2����������һ�μ�loadfile.lua
			tbCurTags[i]	= tbCurTag;
			tbCurTag.tbTask	= self;
			tbCurTag.me		= self.me;
			if (bLoading) then
				nSaveLen	= nSaveLen + tbCurTag:Load(self.nSaveGroup, nSaveLen); -- һ�������е�����Ŀ���ǹ̶��ģ�����nSaveLen���Ӧ��ָ��Ŀ��
			else
				tbCurTag:Start();
			end;
		end;
		
	else -- �����Ѿ�ȫ�����
		self.nCurStep	= -1;
		
		if (MODULE_GAMESERVER and not bLoading) then
			--local tbAwards	= self.tbReferData.tbAwards;
			local tbAwards = Task:GetAwards(self.nReferId); -- ���û�н�����ֱ�����������
			if (not (tbAwards.tbOpt[1] or tbAwards.tbRand[1] or tbAwards.tbFix[1])) then
				Task:SetFinishedRefer(self.nTaskId, self.nReferId);
				Task:CloseTask(self.nTaskId, "finish");
				me = oldPlayer;
				return;
			end;
		end;
		local szMsg = "";
		if (self.tbSubData.tbAttribute.tbDialog.Prize.szMsg) then -- δ�ֲ���
			szMsg = self.tbSubData.tbAttribute.tbDialog.Prize.szMsg;
		else
			szMsg = self.tbSubData.tbAttribute.tbDialog.Prize.tbSetpMsg[1];
		end
				
		local tbAwardCall	= {
			TaskAct.TalkInDark, TaskAct,
			szMsg,
			KTask.SendAward, self.me, self.nTaskId, self.nReferId,
		};
		if (MODULE_GAMESERVER and not bLoading) then
			if (TaskCond:HaveBagSpace(self.tbReferData.nBagSpaceCount)) then
				Lib:CallBack(tbAwardCall);
			else
				Dialog:SendInfoBoardMsg(self.me, string.format(Lang.task.str6[Lang.Idx],self.tbReferData.nBagSpaceCount));
			end
		end;
		
		if (not self.tbReferData.nReplyNpcId or self.tbReferData.nReplyNpcId <= 0) then
			local tbEvent	= self.tbSubData.tbSteps[#self.tbSubData.tbSteps].tbEvent;
			if (tbEvent.nType == 1) then
				self:AddNpcMenu(tbEvent.nValue, 0, string.format(Lang.task.str7[Lang.Idx],self:GetName()), unpack(tbAwardCall));
			else
				assert(false or "û�ط��콱��!");
			end
		else
			self:AddNpcMenu(self.tbReferData.nReplyNpcId, 0, string.format(Lang.task.str7[Lang.Idx],self:GetName()), unpack(tbAwardCall));
		end

	end;

	if (MODULE_GAMESERVER) then
		if (not bLoading) then
			self:SaveData();
		end;
		self.me.pTask.SyncTaskGroup(self.nSaveGroup);
		KTask.SendRefresh(self.me, self.nTaskId, self.nReferId, self.nSaveGroup);
		if (not bLoading and self.nCurStep > 0) then
			self:OnFinishOneTag();
		end
	end;
	
	
	me = oldPlayer;
end;

function tbClassBase:CloseCurStep(szReason)
	for i, tbCurTag in ipairs(self.tbCurTags) do
		tbCurTag:Close(szReason);
	end;
	
	self.tbCurTags	= {};
	self.tbNpcMenus	= {};
	self.tbItemUse	= {};
	self.tbCollectList = {};
	self.tbNpcExclusiveDialogs = {};
end;


function tbClassBase:SaveData()
	self.me.pTask.SetTask(self.nSaveGroup, Task.emSAVEID_TASKID, self.nTaskId);
	self.me.pTask.SetTask(self.nSaveGroup, Task.emSAVEID_REFID, self.nReferId);
	self.me.pTask.SetTask(self.nSaveGroup, Task.emSAVEID_CURSTEP, self.nCurStep);
	self.me.pTask.SetTask(self.nSaveGroup, Task.emSAVEID_ACCEPTDATA, self.nAcceptDate);
	-- self.me.pTask.SetTask(self.nSaveGroup, Task.emSAVEID_NEWFLAG, self.nAcceptDate);
	local nSaveLen	= Task.emSAVEID_TARGET_BEGIN; --����ĳ��ȴ�5��ʼ��֮ǰ4��Ϊ����Id,����������Id,��ǰ���裬������ʱ��
	for _, tbCurTag in ipairs(self.tbCurTags) do
		nSaveLen	= nSaveLen + tbCurTag:Save(self.nSaveGroup, nSaveLen);
	end;
end;


-- �������ָ�������������
function tbClassBase:LoadData(nSaveGroup)
	--Merchant:LoadDate(self.nTaskId)
	self.nSaveGroup		= nSaveGroup;
	self.nAcceptDate	= self.me.pTask.GetTask(nSaveGroup, Task.emSAVEID_ACCEPTDATA);
	self:SetCurStep(self.me.pTask.GetTask(nSaveGroup,Task.emSAVEID_CURSTEP), 1); -- 1��ʶΪLoad
	
	-- ���������������Ŀ��
	if (MODULE_GAMESERVER) then
		for i, tbCurTag in ipairs(self.tbCurTags) do
			if (tbCurTag:IsDone()) then
				self:OnFinishOneTag();
				break;
			end
		end;
	end

end;


function tbClassBase:AddNpcMenu(nNpcTempId, nMapId, szOption, ...)
	if (not nMapId) then
		nMapId = 0;
	end
	Task:DbgOut("AddNpcMenu", nNpcTempId, nMapId, szOption)
	assert(not self.tbNpcMenus[nNpcTempId], "too many Target on npc:"..nNpcTempId);--��һ��������˵��Ӧ�ò�����ڶ��ѡ����ͬһ��Npc����
	-- �滻�������ؼ���
	szOption = string.gsub(szOption, "<taskname>", self.tbTaskData.szName);
	szOption = string.gsub(szOption, "<subtaskname>", self.tbReferData.szName);
	local szTypeIDName = Task:GetTaskIDName(self.tbTaskData.nId);  -- ������������
	self.tbNpcMenus[nNpcTempId]	= {tbCallBack = {szTypeIDName .. "<color=green>"..szOption, unpack(arg)}, dwSceneTemplateId = nMapId};
end;

function tbClassBase:AddExclusiveDialog(nNpcTempId ,...)
	Task:DbgOut("AddNpcExclusiveDialog", nNpcTempId)
	assert(not self.tbNpcExclusiveDialogs[nNpcTempId], "too many ExclusiveDialog on npc:"..nNpcTempId);
	self.tbNpcExclusiveDialogs[nNpcTempId] = {unpack(arg)};
end

-- ֻ����������Ʒ
function tbClassBase:AddItemUse(nTaskItemId, ...)
	assert(not self.tbItemUse[nTaskItemId], "too many Target on item:"..nTaskItemId);
	self.tbItemUse[nTaskItemId]	= {unpack(arg)};
end;

function tbClassBase:RemoveNpcMenu(nNpcTempId)
	self.tbNpcMenus[nNpcTempId]	= nil;
end;
	
function tbClassBase:RemoveNpcExclusiveDialog(nNpcTempId)
	self.tbNpcExclusiveDialogs[nNpcTempId] = nil;
end

function tbClassBase:RemoveItemUse(nParticular)
	self.tbItemUse[nParticular] = nil;
end;


-- ȥһ���������Npc����ĶԻ�
function tbClassBase:GetNpcDialog()
	local tbStep = self:GetCurStep();
	if (not tbStep) then
		Dbg:WriteLog("[UNKNOWBUG]", "TaskClassBase", "GetNpcDialog", "Can't Find CurStep", self.nCurStep or "UnKnowSetp");
		return nil;
	end

	local szMsg = nil;
	
	-- 1.Ŀ��û��ɣ����̶԰�
	for _, tbCurTag in ipairs(self.tbCurTags) do
		if (not tbCurTag:IsDone()) then
			if (self.tbSubData.tbAttribute.tbDialog.Procedure.szMsg) then -- δ�ֲ���
				szMsg = self.tbSubData.tbAttribute.tbDialog.Procedure.szMsg;
			else -- ���˲���
				szMsg = self.tbSubData.tbAttribute.tbDialog.Procedure.tbSetpMsg[self.nCurStep];
			end
			
			return szMsg;
		end;
	end;
	

	-- 2.Ŀ���ɣ�����û��ɣ�����԰�
	local bOK, _  = self:IsCurStepDone();
	if (not bOK) then
		if (self.tbSubData.tbAttribute.tbDialog.Error.szMsg) then -- δ�ֲ���
			szMsg = self.tbSubData.tbAttribute.tbDialog.Error.szMsg;
		else -- ���˲���
			szMsg = self.tbSubData.tbAttribute.tbDialog.Error.tbSetpMsg[self.nCurStep];
		end
		return szMsg
	end


	-- 3.Ŀ�����������ɣ������԰�
	if (self.tbSubData.tbAttribute.tbDialog.End.szMsg) then -- δ�ֲ���
		szMsg = self.tbSubData.tbAttribute.tbDialog.End.szMsg;
	else -- ���˲���
		szMsg = self.tbSubData.tbAttribute.tbDialog.End.tbSetpMsg[self.nCurStep];
	end
			
	return szMsg;	
end


-------------------------------------------------------------------------
-- һ�����ɱ��Npc�ж��ַ������

function tbClassBase:OnKillNpcForCount(pPlayer, pNpc)
	for _, tbCurTag in ipairs(self.tbCurTags) do
		if (tbCurTag.OnKillNpc) then
			tbCurTag:OnKillNpc(pPlayer, pNpc);
		end
	end;
end


function tbClassBase:OnKillNpcForItem(pPlayer, pNpc)
	local bDrop = 0;
	for _, tbCurTag in ipairs(self.tbCurTags) do
		if (tbCurTag.OnKillNpcDropItem) then
			if (tbCurTag:OnKillNpcDropItem(pPlayer, pNpc) == 1) then
				bDrop = 1;
			end
		end
	end
	
	return bDrop;
end

function tbClassBase:OnKillBossForItem(pPlayer, pNpc)
	for _, tbCurTag in ipairs(self.tbCurTags) do
		if (tbCurTag.OnShareBossItem) then
			tbCurTag:OnShareBossItem(pPlayer, pNpc);
		end
	end;
end

function tbClassBase:AddInCollectList(tbItem)
	self.tbCollectList[#self.tbCollectList + 1] =  tbItem;
end

function tbClassBase:RemoveInCollectList(tbItem)
	local nRemoveIndex = -1;
	for i=1, #self.tbCollectList do
		if (Task:IsSameItem(tbItem, self.tbCollectList[i]) == 1) then
			nRemoveIndex = i;
			break;
		end
	end
	
	if (nRemoveIndex > 0) then
		table.remove(self.tbCollectList, nRemoveIndex);
	else
		assert(false);
	end
end

function tbClassBase:IsItemToBeCollect(tbItem)
	for _, item in ipairs(self.tbCollectList) do
		if (tbItem[1] == item[1] and
			tbItem[2] == item[2] and
			tbItem[3] == item[3] and
			tbItem[4] == item[4]) then
				return 1;
			end
	end
	
	return 0;
end
