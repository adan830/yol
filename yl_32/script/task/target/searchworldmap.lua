
local tb	= Task:GetTarget("SearchMapChronicle");
tb.szTargetName	= "SearchMapChronicle";

function tb:Init(nMapId, nNeedCount)
	self.nMapId	= nMapId;
	self.nNeedCount	= nNeedCount;
end;

function tb:Start()
	-- �������ǰ�������ĵ�ͼ־
	self:SetMapNum(0);
	
	-- ע���¼�
	self:Register();
end;

function tb:Save(nGroupId, nStartTaskId)
	return 0;
end;

function tb:Load(nGroupId, nStartTaskId)
	self:Register();
	return 0;
end;

-- Ŀ��ر�ʱע���¼�
function tb:Close(szReason)
	self:UnRegister();
end;

function tb:GetDesc()
	local nMapNum = self.me.pTask.GetTask(LinkTask.TSKG_LINKTASK , LinkTask.TSK_WORLDMAPNUM);
	return string.format(Lang.task.target.str54[Lang.Idx],self.szMapName,nMapNum,self.nNeedCount);
end;


function tb:GetStaticDesc()
	local szMsg	= "";
	local szMapName = "";	
	if (self.nMapId ~= 0) then
		szMapName	= self.szMapName;
	end;
	szMsg = string.format(Lang.task.target.str55[Lang.Idx],szMsg,self.nNeedCount,szMapName);
	return szMsg;
end;


function tb:Register()
	assert(self._tbBase._tbBase)	--û�о��������������ű���д����
	local oldPlayer = me;
	me = self.me;
	if (MODULE_GAMESERVER and not self.nRegisterId) then
		self.nRegisterId	= PlayerEvent:Register("OnPickUp", self.OnPickUp, self);
	end;
	me = oldPlayer;
end;


function tb:UnRegister()
	local oldPlayer = me;
	me = self.me;
	if (MODULE_GAMESERVER and self.nRegisterId) then
		PlayerEvent:UnRegister("OnPickUp", self.nRegisterId);
		self.nRegisterId	= nil;
	end;
	me = oldPlayer;
end;


-- ��Ҽ����κ�һ����Ʒʱ����
function tb:OnPickUp()
	local nNowCount = self:GetMapCount();
	
	-- print("Item Type: "..(it.nGenre).." / "..(it.nDetail).." / "..(it.nParticular));
	
	local tbItem = LinkTask.WorldMapItemGenre;
	
	-- ����ǵ�ͼ־
	if it.nGenre == tbItem[1] and it.nDetail == tbItem[2] and it.nParticular == tbItem[3] then
		nNowCount = nNowCount + 1;
		self:SetMapNum(nNowCount);
		
		-- ����Ŀ���Ѿ��ﵽ
		if nNowCount>=self.nNeedCount then
			self:UnRegister();
			self.tbTask:OnFinishOneTag();
			self.me.SysMsg(string.format(Lang.task.target.str56[Lang.Idx],self.szMapName));			
			return;
		end;
		
		self.me.SysMsg(string.format(Lang.task.target.str57[Lang.Idx],self.szMapName,  nNowCount, self.nNeedCount ));
	end;
end;


-- �ж������Ƿ��Ѿ����
function tb:IsDone()
	local nNowCount = self:GetMapCount();
	return nNowCount>=self.nNeedCount;
end;


function tb:GetMapCount()
	return self.me.pTask.GetTask(LinkTask.TSKG_LINKTASK , LinkTask.TSK_WORLDMAPNUM);
end;

function tb:SetMapNum(nNum)
	self.me.pTask.SetTask(LinkTask.TSKG_LINKTASK , LinkTask.TSK_WORLDMAPNUM, nNum);
end;

