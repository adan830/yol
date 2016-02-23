
local tb	= Task:GetTarget("KillNpc");
tb.szTargetName	= "KillNpc";	--��Ŀ������֣���ʱ��û�õ�

--Ŀ���ִ�����̣�
--	1��Init			ϵͳ����LoadSubʱ���ɴ�Ŀ����ĵ�һ�������������ÿһ����������Init
--	2��Start/Load	��Ҫ����һ��Ŀ��ʱ��ϵͳ���ɴ���ĵڶ���������������Start���ս���˲��裩��Load���������ʱ�����Ŀ�꣩
--	3��Close		Ŀ����Ҫ��ֹʱ��ϵͳ�����Close
--	4��ϵͳ���ٴ�Ŀ��ĵڶ�������

--���⣺
--	Save��GetDesc	��Ŀ�걻�����ڼ䣨����2֮�󣬲���3֮ǰ�����������������ڵ���
--	GetStaticDesc	��Ŀ�걻��ʼ��֮�󣨲���1֮�󣩣��������������ڵ���

----==== ����һ��������Ŀ�궼���붨��ļ������� ====----

--Ŀ���ʼ��
--���������������༭�����Զ���
function tb:Init(nNpcTempId, nMapId, nNeedCount, szBeforePop, szLaterPop)
	self.nNpcTempId		= nNpcTempId;
	self.szNpcName		= KGameBase.GetNameByTemplateId(nNpcTempId);
	self.nMapId			= nMapId;
	self.szMapName		= Task:GetMapName(nMapId);
	self.nNeedCount		= nNeedCount;
	self.szBeforePop	= szBeforePop;
	self.szLaterPop		= szLaterPop;
end;

--Ŀ�꿪��
function tb:Start()
	self.nCount		= 0;
end;

--Ŀ�걣��
--�������������Id��nGroupId���Լ����ڱ�����ʼId��nStartTaskId�������汾Ŀ�������������
--����ʵ�ʴ���ı�������
function tb:Save(nGroupId, nStartTaskId)
	self.tbSaveTask	= {	-- ���ﱣ���������Ժ���ʱ��������ͬ���ͻ���
		nGroupId		= nGroupId,
		nStartTaskId	= nStartTaskId,
	};
	self.me.pTask.SetTask(nGroupId, nStartTaskId, self.nCount);
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
	self.nCount		= self.me.pTask.GetTask(nGroupId, nStartTaskId);

	return 1;
end;

--����Ŀ���Ƿ���
function tb:IsDone()
	return self.nCount >= self.nNeedCount;
end;

--����Ŀ������е��������ͻ��ˣ�
function tb:GetDesc()
	local szMsg	= Lang.task.target.str16[Lang.Idx];
	if (self.nMapId ~= 0) then
		szMsg	= szMsg..self.szMapName..Lang.task.target.str17[Lang.Idx];
	end;
	szMsg	= szMsg..string.format("%s��%d/%d", self.szNpcName, self.nCount, self.nNeedCount);
	return szMsg;
end;

--����Ŀ��ľ�̬�������뵱ǰ��ҽ��е�����޹�
function tb:GetStaticDesc()
	local szMsg	=  Lang.task.target.str16[Lang.Idx];
	if (self.nMapId ~= 0) then
		szMsg	= szMsg..self.szMapName.. Lang.task.target.str17[Lang.Idx];
	end;
	szMsg	= szMsg..string.format("%s %d��", self.szNpcName, self.nNeedCount);
	return szMsg;
end;

--Ŀ��ֹͣ
--	szReason��ֹͣ��ԭ��
--		"logout"	�������
--		"finish"	�������
--		"giveup"	��ҷ�������
--		"failed"	����ʧ��
--		"refresh"	�ͻ���ˢ��
function tb:Close(szReason)
	local oldPlayer = me;
	me = self.me;
	me = oldPlayer;
end;

----==== �����Ǳ�Ŀ�������еĺ������壬������ͬ�������ɺ� ====----
function tb:OnKillNpc(pPlayer, pNpc)
	if (self:IsDone()) then
		return;
	end;
	if (self.nNpcTempId ~= pNpc.dwTemplateId) then
		return;
	end;
	if (self.nMapId ~= 0 and self.nMapId ~= self.me.dwSceneTemplateId) then
		return;
	end;
	self.nCount	= self.nCount + 1;
	
	
	local tbSaveTask	= self.tbSaveTask;
	if (MODULE_GAMESERVER and tbSaveTask) then	-- ����ͬ�����ͻ��ˣ�Ҫ��ͻ���ˢ��
		self.me.pTask.SetTask(tbSaveTask.nGroupId, tbSaveTask.nStartTaskId, self.nCount, 1);
		KTask.SendRefresh(self.me, self.tbTask.nTaskId, self.tbTask.nReferId, tbSaveTask.nGroupId);
	end;
	
	if (self:IsDone()) then	-- ��Ŀ����һ����ɺ󲻻�ʧЧ��
		--
		self.tbTask:OnFinishOneTag();
	end;
	
end;
