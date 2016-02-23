-- Npc�ű���

if not (MODULE_GAMECLIENT or MODULE_GAMESERVER) then
	return
end

Include("/script/npc/define.lua");

local function PreLoadNpcTemplate()
	Npc.tbNpcTemplate = {}
	local NumField = {["TemplateId"]=1,["nMinLevel"]=1,["nMaxLevel"]=1, ["nIntensity"]=1}
	local tbFileData = Lib:LoadTabFile("/setting/npc/npc.txt", NumField)
	local tbNpcTemplate = {}

	if tbFileData then
		for _, tb in pairs(tbFileData) do
			tb.nMinLevel = tb.nMinLevel or Npc.nMinLevel
			tb.nMaxLevel = tb.nMaxLevel or Npc.nMaxLevel
			tb.nIntensity = tonumber(tb.nIntensity) or 0
			tbNpcTemplate[tb.TemplateId] = tb
		end
	end
	Npc.tbNpcTemplate = tbNpcTemplate                      -- npcģ���

    tbFileData = Lib:LoadTabFile("\\setting\\npc\\droplist.txt")
	tbNpcTemplate = {}

	if tbFileData then
		for _, tb in pairs(tbFileData) do
			tbNpcTemplate[tb.BoxID] = tb
		end
	end
	Npc.tbNpcDropListTable = tbNpcTemplate                      -- npc�����
end

PreLoadNpcTemplate();

if (not Npc.tbClassBase) then	-- ��ֹ�ļ�����ʱ�ƻ���������
	-- Npc����ģ�壬��ϸ����default.lua�ж���
	Npc.tbClassBase	= {};

	-- Npcģ���
	Npc.tbClass	= {
		-- Ĭ��ģ�壬�����ṩֱ��ʹ��
		default	= Npc.tbClassBase,
		[""]	= Npc.tbClassBase,
	};
	Npc.tbTidBase = {};
	Npc.tbTid = {
		default = Npc.tbTidBase,
		[0] = Npc.tbTidBase,
	};
end;

-- ȡ���ض�������Npcģ��
function Npc:GetClass(szClassName, bNotCreate)
	local tbClass	= self.tbClass[szClassName];
	-- ���û��bNotCreate�����Ҳ���ָ��ģ��ʱ���Զ�������ģ��
	if (not tbClass and bNotCreate ~= 1) then
		-- ��ģ��ӻ���ģ������
		tbClass	= Lib:NewClass(self.tbClassBase);
		-- ���뵽ģ�������
		self.tbClass[szClassName]	= tbClass;
	end;
	return tbClass;
end;

-- �κ�Npc�Ի���ϵͳ�����������
function Npc:OnDialog(szClassName, pDialogNpc)
	-- ������Լ���һЩͨ�õ�Npc�Ի��¼�
	--��սģʽ������Ի���
	-- TODO:������չ
--	if Looker:IsLooker(me) > 0 then
--		Dialog:Say("˭������������ô��������û�������أ�����");
--		return 0;
--	end
--	--������, ��������κ�npc�Ի�
--	if (me.GetTiredDegree() == 2) then
--		Dialog:Say("B?n ?? online qu�� 5h, kh?ng nh?n ???c b?t c? hi?u qu? n��o.");
--		return 0;
--	end;
	local tbOpt	= {};
	local nEventFlag = 0;
	local nTaskFlag = 0;

	if (Task:AppendNpcMenu(tbOpt) == 1) then
		nTaskFlag = 1;
	end;

	if nEventFlag == 1 or nTaskFlag == 1 then
		local szMsg = "";
		local szMsg2 = "";
		if nEventFlag == 1 and nTaskFlag == 1 then
			szMsg = string.format(Lang.npc.str5[Lang.Idx], him.szName)
			szMsg2 = "Lang.npc.str6[Lang.Idx]";
		elseif nEventFlag == 1 then
			szMsg = string.format(Lang.npc.str7[Lang.Idx], him.szName)
			szMsg2 = Lang.npc.str8[Lang.Idx];
		elseif nTaskFlag == 1 then
			szMsg = string.format(Lang.npc.str9[Lang.Idx], him.szName)
			szMsg2 = Lang.npc.str10[Lang.Idx];
		end
		tbOpt[#tbOpt+1]	= {szMsg2, self.OriginalDialog, self, szClassName, him};
		if nTaskFlag == 1 then
			tbOpt[#tbOpt+1]	= {Lang.npc.str1[Lang.Idx]};
		end
		return Dialog:Say(szMsg, tbOpt);  -- 1 or 0
	end

	-- ���� szClassName �ҵ��ض�ģ��
	local tbClass	= self.tbClass[szClassName];
	Dbg:Output("Npc", "OnDialog", szClassName, tbClass);
	if (tbClass) then
		-- ����ģ��ָ���ĶԻ�����
		if MODULE_GAMECLIENT then
			--if not tbClass.bClientDialog or  tbClass.bClientDialog ~= 1 then
			if (tbClass.bClientDialog and tbClass.bClientDialog == 1) then
				tbClass:OnDialog(pDialogNpc);
				return 1;
			end
			return 0;
		end
		if MODULE_GAMESERVER then
			return tbClass:OnDialog(pDialogNpc);
		end
	end;
	return;
end;

function Npc:DropItems(nNpcId, nOwnerId, mPos, tbPlayerList)
	local npcTemplate = Npc.tbNpcTemplate[nNpcId];
	local pPlayer = KGameBase.GetCharacterById(nOwnerId);
	for i = 1, 4 do
		local nDropListId = npcTemplate["DropListId"..i];
		local nDropTimes = tonumber(npcTemplate["DropTimes"..i]);
		local dropList = Npc.tbNpcDropListTable[nDropListId];

		if not dropList then
			break;
		end

		for nTimes = 1, nDropTimes do
			-- ����Ʒ
			local tbRate = {};
			local nTotalRate = 10000;
			for j = 1, 7 do
				local nDropRate = tonumber(dropList["Item"..j.."DropRate"]);
				if not nDropRate then
					-- ʣ�µĸ���
					tbRate[0] = nTotalRate;
					break;
				end
				tbRate[j] = nDropRate;
				nTotalRate =  nTotalRate - nDropRate;
			end
			assert(nTotalRate >= 0);
			tbRate[0] = nTotalRate;

			local nIdx = Lib:RandProb(tbRate);
			if nIdx and nIdx ~= 0 then
				local nDoodadId = tonumber(dropList["Item"..nIdx.."DoodadId"]);

				local tbItem = {
				nGenre = tonumber(dropList["Item"..nIdx.."Genre"]);
				nDetail = tonumber(dropList["Item"..nIdx.."Detail"]);
				nParticular = tonumber(dropList["Item"..nIdx.."Particular"]);
				nLevel = tonumber(dropList["Item"..nIdx.."Level"]);
				nAmount = tonumber(dropList["Item"..nIdx.."Amount"]);
				};

				local tbPos = {
					dwSceneId = mPos.dwSceneId,
					nX = mPos.nX + KUnify.MathRandom(-200, 200),
					nY = mPos.nY + KUnify.MathRandom(-200, 200),
					nZ = mPos.nZ,
				};

				KGameBase.CallDoodad(nDoodadId, nOwnerId, tbPlayerList, tbPos, tbItem);
			end
		end
	end
end

function Npc:DropTest()
	local tbList = {me.dwId};
	local mPos = me.GetPosition();
	local tbPos = {dwSceneId = me.dwSceneId, nX = 7137 + KUnify.MathRandom(-50, 50), nY = 1763 + KUnify.MathRandom(-50, 50), nZ = mPos.nZ};
	local tbItem = {nGenre = 17, nDetail = 2, nParticular = 2, nLevel = 0, nAmount = 2};
	local pDoodad = KGameBase.CallDoodad(1, me.dwId, tbList, tbPos, tbItem);
end

function Npc:OnBubble(szClassName)
	local tbClass = self.tbClass[szClassName];
	if (tbClass) then
		tbClass:OnTriggerBubble();
	end
end

-- �κ�Npc������ϵͳ�����������
function Npc:OnDeath(nKillerId, nCharacterId, nTemplateId, szClassName)--, szParam, ...)
	local pKiller = KGameBase.GetCharacterById(nKillerId)
	local pDead = KGameBase.GetCharacterById(nCharacterId)

	if pDead == nil then
		return
	end

	if pKiller == nil then
		return
	end



	-- ���� szClassName �ҵ��ض�ģ��
	local tbClass	= self.tbClass[szClassName];
	if (tbClass) then
		-- ����ģ��ָ�����������������������Լ�����dropitems
		tbClass:OnDeath(pKiller, pDead);
	else
		local mPos = pDead.GetPosition();
		Npc:DropItems(nTemplateId, nKillerId, mPos, { nKillerId });
	end;
	--[[
	local tbClass	= self.tbClass[szClassName];
	-- ������Լ���һЩͨ�õ�Npc�����¼�
	local tbOnDeath	= him.GetTempTable("Npc").tbOnDeath;
	Dbg:Output("Npc", "OnDeath", szClassName, tbClass, tbOnDeath);
	if (tbOnDeath) then
		local tbCall	= {unpack(tbOnDeath)};
		Lib:MergeTable(tbCall, arg);
		local bOK, nRet	= Lib:CallBack(tbCall);	-- ���ûص�
		if (not bOK or nRet ~= 1) then
			him.GetTempTable("Npc").tbOnDeath	= nil;
		end
	end

	if (tbClass) then
		-- ����ģ��ָ������������
		tbClass:OnDeath(unpack(arg));
	end;

	--npc�������ⴥ���¼�
	Lib:CallBack({"SpecialEvent.ExtendEvent:DoExecute","Npc_Death", him, arg[1]});

	if (not arg[1]) then
		return;
	end

	local pNpc 		= arg[1];
	local nNpcType 	= him.GetNpcType();
	local pPlayer  	= pNpc.GetPlayer();
	if (not pPlayer) then
		return;
	end
	--]]

	--�ϵͳ����
	--EventManager:NpcDeathApi(szClassName, him, pPlayer, unpack(arg))

	-- ��ʱ
	if pKiller.IsPlayer() == 1 and pDead.IsNpc() == 1 then
		Task:OnKillNpc(pKiller, pDead)
		--daily task
		DailyTasks:commitTaskValue(pKiller,tostring(nTemplateId),DailyTasks.TYPE_KILL_NPC,1);
	end
end;

function Npc:OnArrive(szClassName, pNpc)
	--print ("Npc:OnArrive", szClassName, pNpc);
	local tbOnArrive = pNpc.GetTempTable("Npc").tbOnArrive;
	Setting:SetGlobalObj(me, pNpc, it)
	if (tbOnArrive) then
		Lib:CallBack(tbOnArrive);
	end
	Setting:RestoreGlobalObj()
end

-- ��ȡ�ȼ�����
--	tbParam:{szAIParam, szSkillParam, szPropParam, szScriptParam}
function Npc:GetLevelData(szClassName, szKey, nSeries, nLevel, tbParam)
	-- ���� szClassName �ҵ��ض�ģ��
	local tbClass	= self.tbClass[szClassName];
	if (not tbClass) then
		Dbg:WriteLogEx(Dbg.LOG_ERROR, "Npc", string.format("Npc[%s] not found��", szClassName));
		return 0;
	end;

	-- ����ֱ���ҵ������е����Զ���
	local tbData	= nil;

	if (szClassName == "") then
		tbClass	= {_tbBase=tbClass};
	end

	local tbBaseClasses	= {
		rawget(tbClass, "tbLevelData"),
		self.tbAIBase[tbParam[1]],
		self.tbSkillBase[tbParam[2]],
		self.tbPropBase[tbParam[3]],
		tbClass._tbBase and tbClass._tbBase.tbLevelData,
	};
	for i = 1, 5 do
		local tbBase	= tbBaseClasses[i];
		tbData	= tbBase and tbBase[szKey];
		if (tbData) then
			break;
		end;
	end;
	if (not tbData) then
		Dbg:WriteLogEx(Dbg.LOG_ERROR, "Npc", string.format("Npc[%s]:[%s] not found��", szClassName, szKey));
		return 0;
	end;
	if (type(tbData) == "function") then
		return tbData(nSeries, nLevel, tbParam[4]);
	else
		return Lib.Calc:Link(nLevel, tbData);
	end;
end;

-- ע���ض�Npc�����ص�
function Npc:RegPNpcOnDeath(pNpc, ...)
	local tbPNpcData		= pNpc.GetTempTable("Npc");
	assert(not tbPNpcData.tbOnDeath, "too many OnDeath registrer on npc:"..pNpc.szName);
	tbPNpcData.tbOnDeath	= arg;
end;

-- ȡ���ض�Npc�����ص�
function Npc:UnRegPNpcOnDeath(pNpc)
	pNpc.GetTempTable("Npc").tbOnDeath	= nil;
end;

function Npc:GetNpcIntensity(dwId)
	local nIntensity = 0
	local pNpc = KGameBase.GetNpcById(dwId)
	if not pNpc then
		return
	end

	if Npc.tbNpcTemplate[pNpc.dwTemplateId] then
		nIntensity = Npc.tbNpcTemplate[pNpc.dwTemplateId].nIntensity
	end
	return nIntensity
end
