if (not CallCenter.tbGlobalEvent) then
	CallCenter.tbGlobalEvent	= {};
	CallCenter.tbGlobalFun	= {};
end

-- ע��ȫ���¼��ص�
function CallCenter:RegisterGlobalEvent(szEvent, varCallBack, ...)
	local tbEvent	= self.tbGlobalEvent[szEvent];
	if (not tbEvent) then
		tbEvent	= {};
		self.tbGlobalEvent[szEvent]	= tbEvent;
	end;
	local nRegisterId	= #tbEvent + 1;
	tbEvent[nRegisterId]= {varCallBack, arg};
	return nRegisterId;
end;

-- ע��ȫ������¼��ص�
function CallCenter:UnRegisterGlobalEvent(szEvent, nRegisterId)
	local tbEvent	= self.tbGlobalEvent[szEvent];
	if (not tbEvent or not tbEvent[nRegisterId]) then
		return;
	end;
	tbEvent[nRegisterId]	= nil;
	return 1;
end;

-- ע��ȫ������¼��ص�(��ע���callback����Id��ע��)
function CallCenter:UnRegisterGlobalEventEx(szEvent, param)
	if (type(param) == "number") then
		return self:UnRegisterGlobalEvent(szEvent, param)
	end
	if (type(param) == "function") then
		local tbEvent	= self.tbGlobalEvent[szEvent]
		if (tbEvent) then
			for i, v in pairs(tbEvent) do
				if (v[1] == param) then
					tbEvent[i] = nil
					break
				end
			end
		end
	end
end

-- ע��ȫ���¼��ص��������������ֻص��з���ֵ��һ���¼�ֻ��ע��һ��
function CallCenter:RegisterGlobalFun(szFun, varCallBack, ...)
	local tbFun	= self.tbGlobalFun[szFun];
	if (not tbFun) then
		tbFun	= {};
		self.tbGlobalFun[szFun]	= tbFun;
	end;
	local nRegisterId	= #tbFun + 1;
	tbFun[nRegisterId]= {varCallBack, arg};
	return nRegisterId;
end;

-- ע��ȫ������¼��ص�
function CallCenter:UnRegisterGlobalFun(szFun, nRegisterId)
	local tbFun	= self.tbGlobalFun[szFun];
	if (not tbFun or not tbFun[nRegisterId]) then
		return;
	end;
	tbFun[nRegisterId]	= nil;
	return 1;
end;

-- ��ϵͳ���ã�ĳ�¼�����
function CallCenter:OnEvent(szEvent, ...)
	-- �ȼ��ȫ��ע��ص�
	self:_CallBack(true, self.tbGlobalEvent[szEvent], arg);
end
CallCenter.FireEvent = CallCenter.OnEvent

-- ��ϵͳ���ã����ú���
function CallCenter:CallFun(szEvent, ...)
	-- �ȼ��ȫ��ע��ص�
	return self:_CallBack(false, self.tbGlobalFun[szEvent], arg);
end;

CallCenter.nRunTime = 0;
function CallCenter:_CallBack(bIsEvent, tbEvent, tbArg)
--local nTime = KGRLInterface.GetTickCount();	
	if (not tbEvent) then
		return;
	end
	--Ϊ�˷�ֹѭ���г�����ע�ᵼ�³�������Copy��ʽ
	for nRegisterId, tbCallFunc in pairs(Lib:CopyTB1(tbEvent)) do
		if (tbEvent[nRegisterId]) then	-- ����Ƿ�δ��ɾ��
			local varCallBack	= tbCallFunc[1];
			local varParam	= tbCallFunc[2];
			local tbCallBack	= nil;
			if (varParam.n ~= 0) then		-- ����������Զ���Ĳ���
				tbCallBack	= {varCallBack, unpack(varParam)};
				Lib:MergeTable(tbCallBack, tbArg);
			else
				tbCallBack	= {varCallBack, unpack(tbArg)};
			end
			if (bIsEvent) then
				Lib:CallBack(tbCallBack);
			else
				local ret = {Lib:CallBack(tbCallBack)};
--CallCenter.nRunTime = CallCenter.nRunTime + KGRLInterface.GetTickCount() - nTime;
				return unpack(ret);
			end
		end
	end

--CallCenter.nRunTime = CallCenter.nRunTime + KGRLInterface.GetTickCount() - nTime;
end
