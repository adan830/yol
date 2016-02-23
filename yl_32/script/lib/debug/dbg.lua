-- �ļ�������dbg.lua
-- �����ߡ���FanZai
-- ����ʱ�䣺2007-10-08 22:08:17
-- �ļ�˵����ͳһ�ĵ���ģ�飬����print��debug.traceback��

Dbg.tbDbgMode	= {	-- ������Ҫ���Ե�ģ�顣���ͣ�0�������ԣ�1���򵥵��ԣ�2��ȫ�����
	["Timer"]		= 0,
	["PlayerTimer"]	= 0,
	["Mission"]		= 0,
	["Task"]		= 1,
	["ClientEvent"]	= 0,
	["JbExchange"]  = 1,
	["Represent"]  = 1,
	["Ui"]  = 1,
	["Coroutine"]   = 1,
	["SandMap"]	= 0,
	["Shop"] = 1,
	["Mail"] = 1,
	["Compose"] = 1,
};

-- ���Եȼ�
Dbg.LOG_INFO		= 1;
Dbg.LOG_ATTENTION	= 2;
Dbg.LOG_WARNING		= 4;
Dbg.LOG_ERROR		= 8;


Dbg.tbModeLevel = {[0] = "������", [1] ="�򵥵���", [2] = "ȫ�����"}
function Dbg:ChangeModeLevel(szMode, nLevel)
	if Dbg.tbDbgMode[szMode] then
		if not nLevel then
			return;
		end
		if nLevel < 0 then
			nLevel = 0;
		elseif nLevel > 2 then
			nLevel = 2;
		end
		print(szMode,"����Ϊ", Dbg.tbModeLevel[nLevel]);
		Dbg.tbDbgMode[szMode] = nLevel;
	end
end


function Dbg:OnFunDeprecate(szNewFun)
	local szMsg	= string.format("deprecate function!!! please use '%s' instead.", szNewFun);
	print(debug.traceback(szMsg, 2));
end

-- ���������Ϣ
function Dbg:Output(szMode, ...)
	local nType	= self.tbDbgMode[szMode];
	if (not nType or nType == 0) then
		return;
	end
	
	if (nType >= 1) then
		--print("-DbgOut["..szMode.."]:", unpack(arg));
		print(string.format("[%s %s]:%s", szMode, Lib:TimeDescEn(os.clock()), tostring(arg[1])), unpack(arg, 2));
	end
	if (nType >= 2) then
		self:WriteLogEx(self.LOG_INFO, szMode, unpack(arg));
	end
end

-- �������ջ�ĵ�����Ϣ
function Dbg:PrintEvent(szMode, ...)
	local nType	= self.tbDbgMode[szMode];
	if (not nType or nType == 0) then
		return;
	end
	
	if (nType == 1) then
		print("-DbgEvent["..szMode.."]:", unpack(arg));
	elseif (nType >= 2) then
		print("-DbgEvent["..szMode.."]:", unpack(arg));
		local szTrace	= debug.traceback("DbgInfo", 3);
		print(szTrace);
		self:WriteLogEx(self.LOG_INFO, szMode, unpack(arg), Lib:ReplaceStr(szTrace, "\n", "\t"));
	end
end

-- д����־�ļ���Ĭ��ATTENTION����
function Dbg:WriteLog(szMode, ...)
	self:WriteLogEx(self.LOG_ATTENTION, szMode, unpack(arg));
end

-- д����־�ļ������ȼ���Ϣ
function Dbg:WriteLogEx(nLevel, szMode, ...)
	local nType	= self.tbDbgMode[szMode];
	if (nType and nType > 0) then
		print("-DbgLog["..szMode.."]:", unpack(arg));
	end

	local szMsg	= "["..szMode.."]\t"..table.concat(arg, "\t");
	--local szMsg	= "["..szMode.."]\t";
	--if (KGameBase.WriteLog) then
	--	KGameBase.WriteLog(nLevel, szMsg);
	--else
	--	print("[LOG]", nLevel, szMsg)
	--end
	print("[LOG]", nLevel, szMsg)
end

