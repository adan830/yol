-- ����ģʽ��ϣ�����������ϵͳ������ɫ�����...

-- S
-- ����ģʽ�µĻص�����
function BlackSky:GetDarkData()
	local tbPlayerData		= me.GetTempTable("Task");
	local tbPlayerDarkData	= tbPlayerData.tbDarkData;
	if (not tbPlayerDarkData) then
		tbPlayerDarkData	= {};
		tbPlayerData.tbDarkData	= tbPlayerDarkData;
	end;
	
	return tbPlayerDarkData;
end


-- S
-- ֪ͨ�ͻ��ˣ�������������ѻص�����������ʱTable
function BlackSky:SendDarkCommand(pPlayer, tbParam)
	if (not tbParam) then
		assert(false);
		return;	
	end
	
	if (pPlayer.dwId ~= me.dwId) then
		Dbg:WriteLog("Task", "Player ID Error In Dark[2]!", pPlayer.dwId, me.dwId);
	end
	
	local tbPlayerDarkData	= self:GetDarkData();
	local nInDark = tbPlayerDarkData.nInDark or 0;
	if (tbPlayerDarkData.tbParam) then
		assert(false or "��һ�������Ļ�û�����꣬��Ӧ��ͬʱ��˳��ļ�������");
		return;
	end
	tbPlayerDarkData.tbParam = tbParam;
	tbPlayerDarkData.tbGRoleArgs = {player = pPlayer};
	tbPlayerDarkData.nDarkPlayerId = pPlayer.dwId;
	KTask.SetBlackSky(pPlayer, 1);	-- ֪ͨ�ͻ��˿�������ģʽ
	
	-- ����ʱΪ����ģʽ���õ�Э���ˣ�ֱ��ִ�С�
	-- Э�鵽��ʱ����ΪtbPlayerDarkData.tbParamΪ�����Բ���ִ���κβ���
	if (nInDark == 1) then
		self:WhenEvnChange(pPlayer, 1);
		-- self:WhenEvnChange(1);
	end
end

-- S
-- ������Talk�Ի��ص�,����װ�˹رյĹ��̣�û�лص������лص�Ҫ�����ر�
function BlackSky:SimpleTalk(pPlayer, szMsg, ...)
	self:SendDarkCommand(pPlayer, {TaskAct.NormalTalk, TaskAct, pPlayer, szMsg, self.GiveMeBright, self, pPlayer, unpack(arg)});
end

-- S
-- ������Say�Ի��ص�������װ�˹رչ��̣�û�лص������лص�Ҫ�����ر�
function BlackSky:SimpleSay(pPlayer, szMsg, ...)
	if (arg.n <= 0) then
		local tbOpt = { Lang.task.str3[Lang.Idx], self.GiveMeBright, self, pPlayer};
		self:SendDarkCommand(pPlayer, {Dialog.NormalSay, Dialog, szMsg, tbOpt});
	elseif (type(arg[1][1]) == "table") then
		local tbOpt = {};
		for _, item in pairs(arg[1]) do
			if (type(item) == "table") then
				local szDesc = item[1];
				local tbTemp = {};
				for i = 2, #item do
					tbTemp[i-1] = item[i];
				end
				if (type(szDesc) == "string") then
					table.insert(tbOpt, #tbOpt+1, {szDesc, self.GiveMeBright, self, pPlayer, unpack(tbTemp)});	
				end
			end
		end
		self:SendDarkCommand(pPlayer, {Dialog.NormalSay, Dialog, szMsg, tbOpt}); 
	else	-- 3��ÿһ������һ��ѡ�һ��N������
		local tbOpt = {};
		for _, item in pairs(arg) do
			if (type(item) == "table") then
				local szDesc = table.remove (item, 1);
				if (type(szDesc) == "string") then
					table.insert(tbOpt, #tbOpt+1, {szDesc, self.GiveMeBright, self, pPlayer, unpack(item)});
				end
			end
			if (not tbOpt[1]) then
				tbOpt[1] = {Lang.task.str3[Lang.Idx], self.GiveMeBright, self, pPlayer};
			end
			self:SendDarkCommand(pPlayer, {Dialog.NormalSay, Dialog, szMsg, unpack(tbOpt)});
		end 
	end;
end

-- S
-- ������յ�������ɵĲ�����ִ�лص�����,��������������յ���������
function BlackSky:WhenEvnChange(nDark)
	local tbPlayerDarkData = self:GetDarkData();
	
	if (not tbPlayerDarkData or not tbPlayerDarkData.tbGRoleArgs or not tbPlayerDarkData.tbGRoleArgs.player) then
		return;
	end
	
	if (tbPlayerDarkData.tbGRoleArgs.player.dwId ~= me.dwId) then
		Dbg:WriteLog("Task", "Player ID Error In Dark[2]!", pPlayer.dwId, me.dwId);
	end
	
	if (nDark == 1) then
		tbPlayerDarkData.nInDark = 1;
		if (not tbPlayerDarkData or not tbPlayerDarkData.tbParam) then
			return;
		end
		
		if(tbPlayerDarkData.nDarkPlayerId ~= tbPlayerDarkData.tbGRoleArgs.player.dwId) then
			Dbg:WriteLog("Task", "Player ID Error In Dark!", tbPlayerDarkData.nDarkPlayerId, tbPlayerDarkData.tbGRoleArgs.player.dwId);
		end
		tbPlayerDarkData.nDarkPlayerId = nil;
		
		local tbDarkData = tbPlayerDarkData.tbParam;
		local oldme = me;
		me = tbPlayerDarkData.tbGRoleArgs.player;
		if (tbDarkData) then
			Lib:CallBack(tbDarkData);
		end
		
		tbPlayerDarkData.tbParam = nil;
		me = oldme;
	elseif (nDark == 0) then
		tbPlayerDarkData.nInDark = 0;	
	end
end


-- S
-- �����������������
function BlackSky:GiveMeBright(pPlayer, ...)
	KTask.SetBlackSky(pPlayer, 0);
	local oldme = me;
	me = pPlayer;
	if (arg.n > 0) then
		Lib:CallBack(arg);
	end
	me = oldme;
end


-- C
-- �ͻ���ȫ�ڲ��������˷���ָ��Э��
function BlackSky:BeginDark()
	Ui(Ui.UI_GUTMODEL):GutBegin(self, self.CompleteDardCallBack);
end

-- C
-- �ͻ��˽ӵ�ֹͣ������Э��
function BlackSky:EndDark()
	Ui(Ui.UI_GUTMODEL):GutEnd(self, self.InBright);
end


-- C
-- ���ͻ���ȫ�ڵ�ʱ��Ļص�����
function BlackSky:CompleteDardCallBack()
	KTask.SendEnvCallBack(me, 1);
end


-- C
-- ���ͻ��˺���������ʱ��ص�����
function BlackSky:InBright()
	KTask.SendEnvCallBack(me, 0);
end

-- �ͻ��˼��Ϻڰ��⻷
function BlackSky:OnCoverBegin()
	CoreEventNotify(UiNotify.emCOREEVENT_COVER_BEGIN);
end;

-- �ͻ���ȥ���ڰ��⻷
function BlackSky:OnCoverEnd()
	CoreEventNotify(UiNotify.emCOREEVENT_COVER_END);
end;
