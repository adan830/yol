
local tb	= Task:GetTarget("OpenBoxGetItem");
tb.szTargetName	= "OpenBoxGetItem";

-- ���ӵ�ģ��Id����ͼId, ���ӵĶԻ�����, �ظ���Ϣ�������Ӻ�õ��ĵ��ߣ���ʼ���ݣ���������
function tb:Init(nNpcTempId, nMapId, szOption, szMsg, szRepeatMsg, tbItem, szBeforePop, szLaterPop)
	self.nNpcTempId	= nNpcTempId;
	self.szNpcName	= KGameBase.GetNameByTemplateId(nNpcTempId);
	self.nMapId		= nMapId;
	self.szMapName	= Task:GetMapName(nMapId);
	self.szOption	= szOption;
	self.szMsg		= szMsg;
	if (szRepeatMsg ~= "") then
		self.szRepeatMsg	= szRepeatMsg;
	end;
	
	self.ItemList	= self:ParseItem(tbItem);
	self.szBeforePop	= szBeforePop;
	self.szLaterPop		= szLaterPop;
end;

function tb:Start()
	self.bDone		= 0;
	self:Register();
end;

function tb:ParseItem(szItemSet)
	local tbRet = {};
	local tbItem = Lib:SplitStr(szItemSet, "\n")
	for i=1, #tbItem do
		if (tbItem[i] and tbItem[i] ~= "") then
			-- ÿ�е���Ʒ��ʽ��{��Ʒ��, nGenre, nDetail, nParticular, nLevel, nSeries, nItemNum}
			local tbTemp = loadstring(string.gsub(tbItem[i],"{.+,(.+),(.+),(.+),(.+),(.+),(.+)}", "return {tonumber(%1),tonumber(%2),tonumber(%3),tonumber(%4),tonumber(%5),tonumber(%6)}"))()
			for i = 1, tbTemp[6] do
				table.insert(tbRet, {tbTemp[1],tbTemp[2],tbTemp[3],tbTemp[4],tbTemp[5]});
			end
		end
	end
	
	return tbRet;
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
	local szMsg	= Lang.task.target.str41[Lang.Idx]
	if (self.nMapId ~= 0) then
		szMsg	= szMsg..self.szMapName..Lang.task.target.str17[Lang.Idx]
	end;
	szMsg	= szMsg..string.format("%s ", self.szNpcName);
	return szMsg;
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
		self.me.SysMsg(Lang.task.target.str36[Lang.Idx])
		return;
	end;
	
	if (self:IsDone()) then
		if (self.szRepeatMsg) then
			TaskAct:Talk(self.szRepeatMsg);
		end;
		return;
	end;
	
	local tbOpt =
	{
        { Lang.task.target.str41[Lang.Idx], 			self.SelectOpenBox,	self },
        { Lang.task.target.str42[Lang.Idx]},
    };

    Dialog:Say(Lang.task.target.str43[Lang.Idx], tbOpt);
end;

-- ���ѡ�������[S]
-- 1.��ͻ��˷���Э���ÿͻ������ý�����?
function tb:SelectOpenBox()
	self.bDone	= 1;
	local tbSaveTask	= self.tbSaveTask;
	if (MODULE_GAMESERVER and tbSaveTask) then	-- ����ͬ�����ͻ��ˣ�Ҫ��ͻ���ˢ��
		self.me.pTask.SetTask(tbSaveTask.nGroupId, tbSaveTask.nStartTaskId, self.bDone, 1);
		KTask.SendRefresh(self.me, self.tbTask.nTaskId, self.tbTask.nReferId, tbSaveTask.nGroupId);
	end;
	
	
	for _, tbItem in ipairs(self.ItemList) do
		Task:AddItem(self.me, tbItem);
	end
	
	if (not self.szRepeatMsg) then
		self:UnRegister()	-- ��Ŀ����һ����ɺ󲻻�ʧЧ��
	end;
	
	self.tbTask:OnFinishOneTag();
end;

--[[
-- 2.�ͻ������ý�����������������ɻص�
function tb:SetProgressBar()
end;

-- �ͻ��˽�������ɻص���֪ͨ����˸�����
function tb:OnProgressFull()
end;

-- 3.�����Ϊ��������Ʒ��Ŀ�����
function tb:OnGiveItem()
	
end;
--]]
