-- ���ﵺ, ���������ĳ��ﻺ��
-- PetIsland.IslandPetsCache = {}
-- PetIsland.tbConfigFile = {} -- ��ȡ�������ļ�
PetIsland.nPetIslandMapId = 233	-- ���ﵺ��ͼ���
-- PetIsland.tbPlayerLeavePos = {}  -- ��ҽ���ǰλ��
PetIsland.tbPlayers = {}  -- �����Ϣ����
PetIsland.tbPlayerNpcs = {}  -- ����dwId�߼�id����, ��ӦtbPlayerPetDefs��ĳ��Ｏ
PetIsland.tbPlayerPetDefs = {}  -- �����������ļ�ֻ�����templateid : {npc��ţ�����id��Ʒ��}
PetIsland.tbPlayerPetQuality = {} -- �������ѡ������ĸ�Ʒ�ʵĳ���
PetIsland.PETCARD_ITEMID_BEGIN   = 10         -- ���ɿ����ߵ���ʼID(Particular)
PetIsland.PETCARD_ITEMID_END     = 177        -- ���ɿ����ߵĽ���ID(Particular)
PetIsland.PETCARD_NUM_ONEQUALITY = 28         -- ����Ʒ�ʵ����ɿ�����

-- �����NPC��Χ
PetIsland.nPetMinNpcId = 500  -- ������С����
PetIsland.nPetMaxNpcId = 158

PetIsland.tbPetCardsRefreshed = {} -- ˢ���������ɿ�
PetIsland.tbPetCardsGet = {}       -- ��ȡ�������ɿ�

PetIsland.tbPetDefs = {}   -- ���еľ�̬�����ս������ӳ��, �����ȥ  :  [Ʒ��] =>{����ȼ�=1, ���ﶨ��={��̬npc��ս��npc������id��Ʒ��}}
PetIsland.tbGDPL_JuLingQiu = { 24, 3, 1 }; -- ������
PetIsland.tbPetNumOfNextLevel =            -- ����ֵ��Ӧ�ĸ�Ʒ���������������ﵽĳ������ֵ��ˢ����10������λ���м������ܻ�ˢ����Ʒ����
{
   [0]  = 1,           -- ������ֵ�ﵽһ��ǰ��ֻ���ܳ���һ����Ʒ����
   [50] = 2,
   [60] = 3,
   [65] = 4,
   [70] = 5,
   [75] = 6,
   [80] = 7,
   [85] = 8,
   [90] = 9,
   [95] = 10
}

PetIsland.tbLastRefreshTime = {} 
PetIsland.tbGetPetCardCost = {}      -- ��ͬƷ�ʳ�������Ԫ��
PetIsland.tbRefreshPetCardCost = {}  -- ��ͬƷ�ʷ�������Ԫ��

-- ��ȡ���ﵺˢ�³ɹ���Ĭ��ֵ, C++��ȡ
function PetIsland:GetDefaultRefreshRates()
	return {100, 70, 50, 30, 20 ,5}
end

-- ���ﵺ��ʼ��, ��C++����, ����
function PetIsland:OnInit()
	local tbFile = Lib:LoadTabFile("setting/pet/pet_island.txt");

	if not tbFile then
		return;
	end

	-- self.tbConfigFile = tbFile -- �����ļ���������

	for i=2, #tbFile do
		local nQuality = tonumber(tbFile[i].Quality)
		local tbPetDefItem = {}
		if (self.tbPetDefs[nQuality] == nil) then
			self.tbPetDefs[nQuality] = tbPetDefItem  -- ��ʼ��Ʒ�ʱ�
			tbPetDefItem.RequireLevel = tonumber(tbFile[i].RequireLevel) -- �ȼ�����
			tbPetDefItem.nMaxLuckyValue = tonumber(tbFile[i].MaxLuckyValue) -- �˽׶ε��������ֵ
			tbPetDefItem.nLuckyValueAdd = tonumber(tbFile[i].LuckyValueAdd) -- �˽׶�ˢ��һ�����ӵ�����ֵ
			tbPetDefItem.UpRateCostItem = tonumber(tbFile[i].UpRateCostItem) -- ����ˢ���ʾ���������
			tbPetDefItem.PetDefs = {} -- ��ʼ����������
		else
			tbPetDefItem = self.tbPetDefs[nQuality]  -- ���Ʒ���Ѿ��г�ʼ���ˣ�ֱ����
		end

		-- �����ȡ
		local tbPets = Lib:SplitStr(tbFile[i].Pets, ",")
		for index, szPetId in pairs(tbPets) do
		  szPetId = string.gsub(szPetId, '"', '')
			local nPetType = tonumber(szPetId)
			--local nPetNpcId = KPet.GetPetNpcIdByType(nPetType) -- ͨ��Pet���ȡ��ӦNpc
			tbPetDefItem.PetDefs[index] = nPetType;
			-- �����ȡ 
			--[[table.insert(tbPetDefItem.PetDefs, {
		 		nPetNpcId, -- ��̬����
		 		nPetType, -- ����ģ��ID
			})--]]
		end

    local tbGetPetCostStr = Lib:SplitStr(tbFile[i].GetPetCardCost, ",")
    local tbGetPetCost = {}
    for index, szPetCost in pairs(tbGetPetCostStr) do
      szPetCost = string.gsub(szPetCost, '"', '')
    	tbGetPetCost[index] = tonumber(szPetCost)
    end
    
    self.tbGetPetCardCost[nQuality] = tbGetPetCost
    self.tbRefreshPetCardCost[nQuality] = tonumber(tbFile[i].RefreshPetCardCost);
	end
	
	-- ��ȡ���ɶ�Ӧ�ĵ���id
	--[[tbFile = Lib:LoadTabFile("setting/pet/petitems.txt");

	if not tbFile then
		return;
	end
	
	self.tbPetItemsMap = {}
  for i=2, #tbFile do
		local nPetID = tonumber(tbFile[i].PetID)
		local tbPets = self.tbPetItemsMap[nPetId]
		if tbPets == nil then
		    tbPets = {}
		    self.tbPetItemsMap[nPetId] = tbPets
		end
		
		local nPetNature = tonumber(tbFile[i].PetNature)
		tbFile[i].PetItem = string.gsub(tbFile[i].PetItem, '"', '')
    local tbPetItemIdStr = Lib:SplitStr(tbFile[i].PetItem, ",")
		local tbPetItemId = {}
		tbPetItemId.nGenre = tonumber(tbPetItemIdStr[1])
		tbPetItemId.nDetail = tonumber(tbPetItemIdStr[2])
		tbPetItemId.nParticular = tonumber(tbPetItemIdStr[3])
		tbPetItemId.nLevel = tonumber(tbPetItemIdStr[4])
		
		tbPets[nPetNature] = tbPetItemId
	end	--]]
	
	-- ��ȡ���ɿ��ƺϳɵ��߱�
	tbFile = Lib:LoadTabFile("setting/pet/petcard_compose.txt");

	if not tbFile then
		return;
	end
	
	-- ��ȡ���ɿ��ƺϳɱ�
	self.tbPetCardComposeMap = {}
  for i=2, #tbFile do
    local tbComposeItem = {}
  
  	local tbItem1 = {}
  	tbFile[i].Item1ID = string.gsub(tbFile[i].Item1ID, '"', '')
  	local tbPetItemIdStr = Lib:SplitStr(tbFile[i].Item1ID, ",")
		tbItem1.nItem1ID  = {}
  	tbItem1.nItem1ID.nGenre = tonumber(tbPetItemIdStr[1])
  	tbItem1.nItem1ID.nDetail = tonumber(tbPetItemIdStr[2])
  	tbItem1.nItem1ID.nParticular = tonumber(tbPetItemIdStr[3])
  	tbItem1.nItem1Rate = tonumber(tbFile[i].Item1Rate)
  	tbItem1.nItem1MaxNum = tonumber(tbFile[i].Item1MaxNum)
  	tbComposeItem[1] = tbItem1
  	
  	local tbItem2 = {}
  	tbFile[i].Item2ID = string.gsub(tbFile[i].Item2ID, '"', '')
  	tbPetItemIdStr = Lib:SplitStr(tbFile[i].Item2ID, ",")
  	tbItem2.nItem2ID = {}
  	tbItem2.nItem2ID.nGenre = tonumber(tbPetItemIdStr[1])
  	tbItem2.nItem2ID.nDetail = tonumber(tbPetItemIdStr[2])
  	tbItem2.nItem2ID.nParticular = tonumber(tbPetItemIdStr[3])
  	tbItem2.nItem2Rate = tonumber(tbFile[i].Item2Rate)
  	tbItem2.nItem2MaxNum = tonumber(tbFile[i].Item2MaxNum)
  	tbComposeItem[2] = tbItem2
  	
  	local tbItem3 = {}
  	tbFile[i].Item3ID = string.gsub(tbFile[i].Item3ID, '"', '')
  	tbPetItemIdStr = Lib:SplitStr(tbFile[i].Item3ID, ",")
  	tbItem3.nItem3ID = {}
  	tbItem3.nItem3ID.nGenre = tonumber(tbPetItemIdStr[1])
  	tbItem3.nItem3ID.nDetail = tonumber(tbPetItemIdStr[2])
  	tbItem3.nItem3ID.nParticular = tonumber(tbPetItemIdStr[3])
  	tbItem3.nItem3Rate = tonumber(tbFile[i].Item3Rate)
  	tbItem3.nItem3MaxNum = tonumber(tbFile[i].Item3MaxNum)
  	tbComposeItem[3] = tbItem3
  	
  	local nQuality = tonumber(tbFile[i].Quality)
  	self.tbPetCardComposeMap[nQuality] = tbComposeItem
	end	
end
-- ====================================================

function PetIsland:ComposePetCard(pPlayer, tbPetIds)
	 local nItem1Num = 0
	 local nItem2Num = 0
	 local tbComposeItem = {}
	 for _, nPetId in pairs(tbPetIds) do	    
	    if (nPetId > 0) then
		    local pPet = KPet.GetPetById(nPetId);
				if pPet == nil then
				    return 
				end
				
				--KPet.FreePet(nPetId)
				
		    local nQuality = pPet.nQuality
		     
		    tbComposeItem = self.tbPetCardComposeMap[nQuality]
		    local tbItem1 = tbComposeItem[1]
		    nItem1Num = nItem1Num + tbItem1.nItem1Rate
		     
		    local tbItem2 = tbComposeItem[2]
		    nItem2Num = nItem2Num + tbItem2.nItem2Rate    
	    end
	 end
	 
	 nItem1Num = math.floor(nItem1Num / 1000)
	 nItem2Num = math.floor(nItem2Num / 1000)
	 
	 -- ��鱳���ռ�
	 local nNeedCellNum = 0;
	 if nItem1Num > 0 then
	     nNeedCellNum = nNeedCellNum + 1
	 end
	 if nItem2Num > 0 then
	     nNeedCellNum = nNeedCellNum + 1
	 end
	 if pPlayer.pItem.CountFreeBagCell() < nNeedCellNum then
			pPlayer.SendBlackMsg(Lang.pet.str36[Lang.Idx]);
			return
	 end
	 
	 if nItem1Num > 0 then
	    KItem.AddPlayerItem(pPlayer, tbComposeItem[1].nItem1ID.nGenre, tbComposeItem[1].nItem1ID.nDetail, tbComposeItem[1].nItem1ID.nParticular, 0, nItem1Num) 
	 end
	 if nItem2Num > 0 then
	    KItem.AddPlayerItem(pPlayer, tbComposeItem[2].nItem2ID.nGenre, tbComposeItem[2].nItem2ID.nDetail, tbComposeItem[2].nItem2ID.nParticular, 0, nItem2Num) 
	 end
	 
	 local nComposeCount = pPlayer.pTask.GetTask(5002, 1)
	 pPlayer.pTask.SetTask(5001, 2, nComposeCount + 1);

   -- �ͷźϳɵ�����	 
 	 for _, nPetId in pairs(tbPetIds) do	    
    if (nPetId > 0) then
	    local pPet = KPet.GetPetById(nPetId);
			if pPet == nil then
			    return 
			end
			
			KPet.FreePet(nPetId)
		end
   end
   
   pPlayer.CallClientScript({"YoulongApp.UI.Controller.QUIClientScript:PlayerComposeItemAnim", nItem1Num, nItem2Num});
end

-- ������ﵺ, ����NPC
function PetIsland:OnInstanceInit(dwCharacterId)
	local pPlayer = KGameBase.GetCharacterById(dwCharacterId);
	if pPlayer.IsNpc() == 1 then
		return
	end

	-- ���������ҽ��뵽���ﵺ������Ϊ
	local nMapId = pPlayer.dwSceneTemplateId;
	-- KScene.GetSceneType(nMapId) ~= 1 or
	if nMapId ~= self.nPetIslandMapId then--self.tbSetting[nMapId] == nil then
		return;
	end

	-- ��¼���
	self.tbPlayers[pPlayer.dwId] = {
		dwSceneId = pPlayer.dwSceneId,  -- ������¼
		bWin = 0,  -- �Ƿ���սʤ����
		bFighting = 0, -- �Ƿ����ڸ�������
		nKillCount = 0  -- ɱ��������ٴΣ���Ҫ4��
	}

	-- ��ұ��˽�����ﵺ����ʼˢ��npc
	self:RefreshLastPet(pPlayer); -- �����û�ϴ�ˢ��������
end

-- ���ﵺ����ʼ��
function PetIsland:OnInstanceUnInit(dwCharacterId)
	local pPlayer = KGameBase.GetCharacterById(dwCharacterId);
	if (pPlayer ~= nil) and (pPlayer.IsNpc() == 1) then
		return
	end

	-- ���������ҽ��뵽���ﵺ������Ϊ
	local nMapId = pPlayer.dwSceneTemplateId;
	-- KScene.GetSceneType(nMapId) ~= 1 or
	if nMapId ~= self.nPetIslandMapId then--self.tbSetting[nMapId] == nil then
		return;
	end

	self.tbPlayers[pPlayer.dwId] = nil;
	self.tbPlayerPetDefs[pPlayer.dwId] = nil
	self.tbPlayerNpcs[pPlayer.dwId] = nil
	self.tbPlayerPetQuality[pPlayer.dwId] = nil
end

-- ������ﵺ
function PetIsland:EnterPetIsland(pPlayer)
	--pPlayer.TeleportTo(self.nPetIslandMapId, 2042,260,1048576)
	Instance:TryEnterInstance({pPlayer.dwId}, self.nPetIslandMapId);
	self:__ClientShowIslandPanel(pPlayer) -- ���ﵺUI���
end

-- ����ˢ�ɳ���ɹ���
function PetIsland:UpRefreshRate(pPlayer, nQuality)
	local nNowRate = KPet.GetPetIslandRefreshRate(pPlayer, nQuality)
	if nNowRate < 100 then  -- ���ʴ��ڵ���100������
		-- TODO: ��Ǯ
		local tbCostGDPL = self.tbGDPL_JuLingQiu -- ������
		local nCostNum = tonumber(self.tbPetDefs[nQuality].UpRateCostItem);  -- ��Ҫ���Ķ��ٸ�������
		local tbFind = me.pItem.FindItem(Item.ROOM_PET, unpack(tbCostGDPL));
		if (Pet:GetTotalCount(tbFind) < nCostNum) then
			local szErrMsg = string.format(Lang.pet.str37[Lang.Idx] , nCostNum);
			me.SysMsg(szErrMsg);
			return;
		end
		me.pItem.ConsumeItemInBags(nCostNum, unpack(tbCostGDPL));

		KPet.SetPetIslandRefreshRate(pPlayer, nQuality, nNowRate+1)
	else
		pPlayer.SysMsg(Lang.pet.str38[Lang.Idx])
	end
end

function PetIsland:RefreshLastPet(pPlayer)
	local tbLastPetInfo = KPet.GetPetIslandLastInfo(pPlayer);
	if tbLastPetInfo.nLastIndex ~= 0  then
		local nQuality = tbLastPetInfo.nLastQuality;
		local nNature = tbLastPetInfo.nLastNature;
		
		-- ��ȡ������λ����Ϣ~ ȡ����һ��npc��PosFile  # = 4
		print("PetIsland:RefreshLastPet", pPlayer.dwSceneTemplateId, self.nPetMinNpcId, Scene.tbNpcCfg[pPlayer.dwSceneTemplateId][self.nPetMinNpcId])
		local tbPosList = Scene.tbNpcCfg[pPlayer.dwSceneTemplateId][self.nPetMinNpcId].tbPosList["nantianmen"];
	
		-- ˢ�¾�̬����
		local dwSceneId = pPlayer.dwSceneId;
		local tbPetDefs = self.tbPetDefs[nQuality].PetDefs  -- ��ȡָ��Ʒ��4�����ó���
		
		local tbPetDef2 = tbPetDefs[tbLastPetInfo.nLastIndex]-- ���ȡ1��
		tbPetDef2[4] = nNature
	
		self.tbPlayerPetDefs[pPlayer.dwId] = tbPetDef2  -- ������ҵ��������
		self.tbPlayerPetQuality[pPlayer.dwId] = nQuality -- ���ѡ��ĳ���Ʒ��
	
		-- ��ʼ��������
		local tbPos = tbPosList[1]--[nIdx]  -- ��ȡλ��, ���ﶨλ
		local nNpcTemplateId = tbPetDef2[1]  -- ����NPC
		local nPetTemplateId = tbPetDef2[2] -- ����ģ��id
		local nPetNature = tbPetDef2[4] -- �����Ը�
		self:__AddPet(pPlayer, nNpcTemplateId, nQuality, nPetNature, tbPos)  -- ѭ����ӳ���
		
		-- ����ˢ���ĳ������Ϣ
		if tbLastPetInfo.nLastFightState == 0 then
	      self:__ClientPetInfo(pPlayer, nPetTemplateId, nQuality, nPetNature)
	    else 
	    	self:StartFight(pPlayer);
	    end
    end
end

-- ˢ�³��� (��̬���ﱣ��������ս�������ñ����ս��ģ��ID��������)
function PetIsland:c2s_RefreshPets(pPlayer, Decuple)
	-- ��һ���ɹ�����
 	--[[local tbRefreshData = KAward.GetNumericalAwardData("PetIsland", 1, nQuality); --KPet.GetPetIslandRefreshRate(pPlayer, nQuality);
 	local nHavePrestige = pPlayer.pPlayerPurse.GetMoney(Purse.EM_MONEY_PRESTIGE);
	if nHavePrestige < tbRefreshData.nCost then
		-- ��������
		pPlayer.SendBlackMsg("��������");
		return
	end
  
  -- �۳�����
  pPlayer.pPlayerPurse.AddMoney(Purse.EM_MONEY_PRESTIGE, -tbRefreshData.nCost);--]]

	local nNowTime = KGameBase.GetTime();	
	if self.tbLastRefreshTime[pPlayer.dwId] ~= nil then
	    local nLastTime = self.tbLastRefreshTime[pPlayer.dwId];
	    if nNowTime - nLastTime < 1 then   -- ���С��1�����������ͣ����������
	        pPlayer.SendBlackMsg(Lang.pet.str39[Lang.Idx] );
	        return;
	    end
	else
	    self.tbLastRefreshTime[pPlayer.dwId] = nNowTime;
	end
	
  local tbPetIslandInfo = KPet.GetPetIslandLastInfo(pPlayer);    
  local nQuality = tbPetIslandInfo.nCurrentQuality;
  
  local nTimes = Player.tbDegree:GetDegree(pPlayer, "RefreshPetCardTimes")
  if nTimes <= 0 then -- ��������ʱ����Ԫ��
     local nCost = self.tbRefreshPetCardCost[nQuality]
     if Decuple == 1 then
         nCost = nCost * 10;
     end
     local nCurCoin = pPlayer.pPlayerPurse.GetMoney(Purse.EM_MONEY_COIN)
     if nCurCoin < nCost then
         pPlayer.SendBlackMsg(Lang.pet.str40[Lang.Idx] )
         return
     end
     
     pPlayer.pPlayerPurse.AddMoney(Purse.EM_MONEY_COIN, -nCost);
	pPlayer.pPlayerPurse.LogMoney(Item.EM_MONEY_COIN, -nCost,103);
  else
     Player.tbDegree:ReduceDegree(pPlayer, "RefreshPetCardTimes")
  end
  
  local nRefreshCount = pPlayer.pTask.GetTask(5001, 1)
	pPlayer.pTask.SetTask(5001, 1, nRefreshCount + 1);
	 
  local nCurrentLuckyValue = tbPetIslandInfo.nCurrentLuckyValue;
  
  if nQuality < 6 then
    local nAddValue = self.tbPetDefs[nQuality].nLuckyValueAdd;
    if Decuple == 1 then  -- 10������ֵ
        nAddValue = nAddValue * 10
    end
    
	  nCurrentLuckyValue = nCurrentLuckyValue + nAddValue;
	  if nCurrentLuckyValue > self.tbPetDefs[nQuality].nMaxLuckyValue then
	      nCurrentLuckyValue = 0
	      nQuality = nQuality + 1
	  end
  end
  
  local nKeyLuckyValue = 0
  local nLuckyProgress = (tbPetIslandInfo.nCurrentLuckyValue / self.tbPetDefs[nQuality].nMaxLuckyValue) * 100;
  for lv, num in pairs(self.tbPetNumOfNextLevel) do
      if nLuckyProgress > lv then
          nKeyLuckyValue = lv;
      end
  end
  
  local tbRefreshedPets = {}
  local tbPetCardPoses = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}
  
  -- С���ʱ���2Ʒ����
  local isHit = KUnify.MathRandom(1, 100) --���������
  if (nRefreshCount == 2 or isHit == 1) and nQuality < 5 then
  --if (nRefreshCount == 2 or isHit > 50) and nQuality < 5 then
      local tbPetDef2 = {}
      
      local tbPetDefs = self.tbPetDefs[nQuality + 2].PetDefs  -- ��ȡָ��Ʒ��4�����ó���
	    local nRand = KUnify.MathRandom(#tbPetDefs) --���������
			tbPetDef2[1] = tbPetDefs[nRand]-- ���ȡ1��
			tbPetDef2[2] = KUnify.MathRandom(1,7)  -- ����Ը�, ����
			
			local index = KUnify.MathRandom(#tbPetCardPoses)
			tbRefreshedPets[tbPetCardPoses[index] * 2 - 1] = tbPetDef2[1]
			tbRefreshedPets[tbPetCardPoses[index] * 2] = tbPetDef2[2]
			
			self.higherQualityPet = tbPetDef2[1]
			
			table.remove(tbPetCardPoses, index)
  end

  -- ��ˢ�¸�Ʒ������
  local nNextLevelPetNum = self.tbPetNumOfNextLevel[nKeyLuckyValue]

  for i = 1, nNextLevelPetNum do    
    local nRand = KUnify.MathRandom(self.tbPetDefs[nQuality].nMaxLuckyValue)
    if nRand < nCurrentLuckyValue then
      local tbPetDef2 = {}
      
	    local tbPetDefs = self.tbPetDefs[nQuality + 1].PetDefs  -- ��ȡָ��Ʒ��4�����ó���
	    nRand = KUnify.MathRandom(#tbPetDefs) --���������
			tbPetDef2[1] = tbPetDefs[nRand]-- ���ȡ1��
			tbPetDef2[2] = KUnify.MathRandom(1,7)  -- ����Ը�, ����
			
			local index = KUnify.MathRandom(#tbPetCardPoses)
			tbRefreshedPets[tbPetCardPoses[index] * 2 - 1] = tbPetDef2[1]
			tbRefreshedPets[tbPetCardPoses[index] * 2] = tbPetDef2[2]
			
			table.remove(tbPetCardPoses, index)
		end
  end
  for _, key in pairs(tbPetCardPoses) do
    local tbPetDefs = self.tbPetDefs[nQuality].PetDefs  -- ��ȡָ��Ʒ��4�����ó���
    local nRand = KUnify.MathRandom(#tbPetDefs) --���������
		local tbPetDef2 = {}
		tbPetDef2[1] = tbPetDefs[nRand]-- ���ȡ1��
		tbPetDef2[2] = KUnify.MathRandom(1,7)  -- ����Ը�, ����
		--tbPetDef2[3] = nQuality
		
		tbRefreshedPets[key * 2 - 1] = tbPetDef2[1]
		tbRefreshedPets[key * 2]     = tbPetDef2[2]
  end
  
  self.tbPetCardsRefreshed[pPlayer.dwId] = tbRefreshedPets;
  
  -- ��ˢ���Ŀ���ͬ�����ͻ���
  KPet.SendRefreshPetInfo(pPlayer, tbRefreshedPets);
	KPet.RecordPetIslandCurrentInfo(pPlayer, nCurrentLuckyValue, nQuality, 0, 0)
	-- ���ó��ƴ���
	Player.tbDegree:SetDegree(pPlayer, "GetPetCardTimes", 3, 1);
	
	--[[self:__RemoveAllPets(pPlayer.dwId)  -- �Ƴ���ǰ�������г���

	-- ����ս��״̬
	self.tbPlayers[pPlayer.dwId].bFighting = 0
	self.tbPlayers[pPlayer.dwId].bWin = 0
	self.tbPlayers[pPlayer.dwId].nKillCount = 0

	-- ��ȡ������λ����Ϣ~ ȡ����һ��npc��PosFile  # = 4
	local tbPosList = Scene.tbNpcCfg[pPlayer.dwSceneTemplateId][self.nPetMinNpcId].tbPosList["nantianmen"];

	-- ˢ�¾�̬����
	local dwSceneId = pPlayer.dwSceneId;
	local tbPetDefs = self.tbPetDefs[nQuality].PetDefs  -- ��ȡָ��Ʒ��4�����ó���

	local nRand = KUnify.MathRandom(#tbPetDefs) --���������
	local tbPetDef2 = tbPetDefs[nRand]-- ���ȡ1��
	tbPetDef2[4] = KUnify.MathRandom(1,7)  -- ����Ը�, ����
	tbPetDef2[5] = nQuality

	self.tbPlayerPetDefs[pPlayer.dwId] = tbPetDef2  -- ������ҵ��������
	self.tbPlayerPetQuality[pPlayer.dwId] = nQuality -- ���ѡ��ĳ���Ʒ��

	-- ��ʼ��������
	local tbPos = tbPosList[1]--[nIdx]  -- ��ȡλ��, ���ﶨλ
	local nNpcTemplateId = tbPetDef2[1]  -- ����NPC
	local nPetTemplateId = tbPetDef2[2] -- ����ģ��id
	local nPetNature = tbPetDef2[4] -- �����Ը�
	
	self:__AddPet(pPlayer, nNpcTemplateId, nQuality, nPetNature, tbPos)  -- ѭ����ӳ���

	-- ����ˢ���ĳ������Ϣ
	self:__ClientPetInfo(pPlayer, nPetTemplateId, nQuality, nPetNature)

    KPet.RecordPetIslandCurrentInfo(pPlayer, nRand, nQuality, nPetNature, 0); -- ����˴���Ϣ--]]
end
-- �鿨
function PetIsland:c2s_GetCard(pPlayer)
   print("..PetIsland:c2s_GetCard",pPlayer.dwId);
   local nTimes = Player.tbDegree:GetDegree(pPlayer, "GetPetCardTimes")
   local tbPetIslandInfo = KPet.GetPetIslandLastInfo(pPlayer);    
   local nQuality = tbPetIslandInfo.nCurrentQuality;
   local tbCards = self.tbPetCardsRefreshed[pPlayer.dwId]
   
   local tbPets = KPet.GetPlayerPetList(pPlayer);
	 local nPetCapacity = pPlayer.GetPetCapacity();
	 if #tbPets == nPetCapacity then
		 pPlayer.SendBlackMsg(Lang.pet.str41[Lang.Idx] );
		 return 0;
	 end
	
   if nTimes <= 0 then
     local tbCost = self.tbGetPetCardCost[nQuality]
     local nCost = tbCost[8 - #tbCards / 2]
       
     local nCurCoin = pPlayer.pPlayerPurse.GetMoney(Purse.EM_MONEY_COIN)
     if nCurCoin < nCost then
         pPlayer.SendBlackMsg(Lang.pet.str42[Lang.Idx] )
         return
     end
     
     pPlayer.pPlayerPurse.AddMoney(Purse.EM_MONEY_COIN, -nCost);
	 pPlayer.pPlayerPurse.LogMoney(Item.EM_MONEY_COIN, -nCost,102);
   else
     Player.tbDegree:ReduceDegree(pPlayer, "GetPetCardTimes", 1)  
   end

   local nRandIndex = KUnify.MathRandom(#tbCards / 2)
   local nRefreshCount = pPlayer.pTask.GetTask(5001, 1)
   if nRefreshCount == 3 and (#tbCards / 2) > 2 then
       while (tbCards[nRandIndex * 2 - 1] == self.higherQualityPet) do
           nRandIndex = KUnify.MathRandom(#tbCards / 2)
       end
   end
   Lib:ShowTB(tbCards);
   print("..nRandIndex <= (#tbCards / 2) ",(nRandIndex <= (#tbCards / 2) ),nRandIndex,#tbCards,tbCards[nRandIndex * 2 - 1],self.higherQualityPet)
   if nRandIndex <= (#tbCards / 2) then
      self.tbPetCardsGet[#self.tbPetCardsGet] = tbCards[nRandIndex * 2 - 1]
      if(tbCards[nRandIndex * 2 - 1] == self.higherQualityPet) then
      		local tbFile = Lib:LoadTabFile("setting/pet/pet.txt");
      		local szMsg = Lang.mission.str1223[Lang.Idx];
      		local szQuality = "";
      		local szName = "";
      		for i=2,#tbFile do 
				if(tonumber(tbFile[i].PetId) == tbCards[nRandIndex * 2 - 1]) then 
					szQuality = Pet.QUALITY_TIPS[tonumber(tbFile[i].Quality)];
					szName = tbFile[i].Name;
					break;
				end
      		end
      		local szFormatMsg = string.format(szMsg,pPlayer.szName,szQuality,szName);
			KChat.BroadcastNoticeMsg(szFormatMsg);
			pPlayer.SysMsg(szFormatMsg);
      end
      self.tbPetCardsGet[#self.tbPetCardsGet + 1] = tbCards[nRandIndex * 2]
      table.remove(tbCards, nRandIndex * 2)
      table.remove(tbCards, nRandIndex * 2 - 1)
      print("PetIsland:c2s_GetCar2", #tbCards, #tbCards / 2, self.tbPetCardsGet[#self.tbPetCardsGet - 1], self.tbPetCardsGet[#self.tbPetCardsGet])
      
      Pet:AddPet(pPlayer, self.tbPetCardsGet[#self.tbPetCardsGet - 1], self.tbPetCardsGet[#self.tbPetCardsGet])
   end
   
   --DailyTasks:commitTaskValue(pPlayer,table.concat({self.tbPetCardsGet[#self.tbPetCardsGet - 1],self.tbPetCardsGet[#self.tbPetCardsGet]},"#"),DailyTasks.TYPE_TAKE_OUT_PET,1);
	DailyTasks:commitTaskValue(pPlayer,"",DailyTasks.TYPE_TAKE_OUT_PET,1);
   pPlayer.CallClientScript({"QClientScript.PetIsland:GetOnePetCard", nRandIndex});
end

-- ��ʼ������ս���� ˢ��ս������
function PetIsland:StartFight(pPlayer)
	if self.tbPlayers[pPlayer.dwId].bFighting == 1 then -- ����ս��
		return
	end

	-- ��ǰnpc����Ӫ�任��3����ս��
	if self.tbPlayerPetDefs[pPlayer.dwId] ~= nil then -- ˢ�¹�
		if self.tbPlayerNpcs[pPlayer.dwId] ~= nil then -- ˢ�³���npc
			for _, nId in pairs(self.tbPlayerNpcs[pPlayer.dwId]) do
				local pNpc = KGameBase.GetNpcById(nId);
				if pNpc and pNpc.IsDead() ~= 1 then
					--KGameBase.RemoveNpc(pNpc.dwId);
					pNpc.SetCurrentCamp(3)
				end
			end

			-- ����������ս��
			self.tbPlayers[pPlayer.dwId].bWin = 0
			self.tbPlayers[pPlayer.dwId].bFighting = 1
			pPlayer.SendBlackMsg(Lang.pet.str43[Lang.Idx] )

			-- ����������ս��
			self.tbPlayers[pPlayer.dwId].bWin = 0
			self.tbPlayers[pPlayer.dwId].bFighting = 1
		end
	else
		pPlayer.SysMsg(Lang.pet.str44[Lang.Idx] )
		return
	end

    KPet.RecordPetIslandCurrentInfo(pPlayer, -1, -1, -1, 1); -- ����ս��״̬��Ϣ, -1��ʾ����ԭ����ֵ
end
-- ���ﵺ������Ϣ��� s2c
function PetIsland:__ClientPetInfo(pPlayer, nNpcTemplateId, nQuality, nPetNature)
	pPlayer.CallClientScript({"QClientScript.PetIsland:ShowPetInfo", nNpcTemplateId, nQuality, nPetNature});
end
-- ���ﵺui��� s2c
function PetIsland:__ClientShowIslandPanel(pPlayer)
	pPlayer.CallClientScript({"QClientScript.PetIsland:OpenIslandPanel"});
end

-- �ͻ�����ʾ����ѡ����� s2c
function PetIsland:__ClientShowChoosePetPanel(pPlayer, nPetTemplateId, nNature)
	-- ����4������id
	pPlayer.CallClientScript({"QClientScript.PetIsland:OpenChoosePetPanel", nPetTemplateId, nNature});
end

-- �ͻ���npc�Ը�ƫɫ
function PetIsland:__ClientSetPetNpcPartialColor(pPlayer, pNpc, nNature)
	pPlayer.CallClientScript({"QClientScript.PetIsland:SetPetNpcPartialColor", pNpc.dwId, nNature});
end

-- �����߼�����������ģ�壬npcģ��id
function PetIsland:__AddPet(pPlayer, nNpcTemplateId, nQuality, nNature, tbPos)
	local dwPlayerId = pPlayer.dwId
	local dwSceneId = pPlayer.dwSceneId
	local dwSceneTemplateId = pPlayer.dwSceneTemplateId

	-- npc�ĳ���ģ�壬λ����Ϣ
	local tbNpcT = Scene.tbNpcCfg[dwSceneTemplateId][self.nPetMinNpcId];
	local tbNpc = {}
	--tbNpc.tbPosList = tbNpcT.tbPosList
	tbNpc.nTemplateId = nNpcTemplateId; --tbNpcT.nTemplateId
	tbNpc.nRegenerationTime = tbNpcT.nRegenerationTime;
	tbNpc.nNormalAI = tbNpcT.nNormalAI;
	tbNpc.nCount = 1; -- һ��

	local tbRetNpcs = Scene:_CallOneNpc(tbNpc, dwSceneId, dwSceneTemplateId, tbPos)

	-- ������ӳɹ��󱣴�����
	for _, pNpc in ipairs(tbRetNpcs) do
	    -- KCharacter.ResetNpcIntensity(pNpc, nPropId, nLevel);
	    -- self:AddNpcInLock(pNpc, nLock);
		-- self:AddNpcInGroup(pNpc);
		-- table.insert(tbNpcId, pNpc.dwId);
		-- local tbTmp = pNpc.GetTempTable("Instance")
		-- tbTmp.tbInstance = self;
		if self.tbPlayerNpcs[pPlayer.dwId] == nil then
			self.tbPlayerNpcs[pPlayer.dwId] = {}
		end
		table.insert(self.tbPlayerNpcs[pPlayer.dwId], pNpc.dwId);
		self:__ClientSetPetNpcPartialColor(pPlayer, pNpc, nNature)
	end
end

-- �Ƴ�ָ����ҳ��ﵺ�����г���
function PetIsland:__RemoveAllPets(dwPlayerId)
	-- ɾ��ԭ���ĳ���
	if self.tbPlayerNpcs[dwPlayerId] ~= nil then
		for _, nId in pairs(self.tbPlayerNpcs[dwPlayerId]) do
			local pNpc = KGameBase.GetNpcById(nId);
			if pNpc and pNpc.IsDead() ~= 1 then
				KGameBase.RemoveNpc(pNpc.dwId);
			end
		end
	end
end

-- ���ﱻɱ,  me��Dead, him��killer
function PetIsland:OnDeath(pKiller, pDead)
	if pKiller.IsPlayer() then  -- ���ɱ������
		if self.tbPlayers[pKiller.dwId] ~= nil then
			-- �ж�����Ƿ���ս��, �ǵĻ���������
			if self.tbPlayers[pKiller.dwId].bFighting == 1 then
				-- ɱ��ͳ��
				self.tbPlayers[pKiller.dwId].nKillCount = self.tbPlayers[pKiller.dwId].nKillCount + 1
				if self.tbPlayers[pKiller.dwId].nKillCount >= 1 then -- ���г���ɱ�⣬

					-- ���սʤ
					self.tbPlayers[pKiller.dwId].bWin = 1
					self.tbPlayers[pKiller.dwId].bFighting = 0
					self.tbPlayers[pKiller.dwId].nKillCount = 0  -- ����

					-- �ͻ��˳�ѡ��������, �����ݳ���id
					local tbPetDef2 = self.tbPlayerPetDefs[pKiller.dwId]
					self:__ClientShowChoosePetPanel(pKiller, tbPetDef2[2], tbPetDef2[4])  -- ����ID�� �Ը�
					
					local nQuality = tbPetDef2[5]  
					if nQuality ==  3 then -- ����Ʒ��ʼ����
					   KChat.BroadcastNoticeMsg("<"..pKiller.szName..Lang.pet.str45[Lang.Idx]..pDead.szName..">")
					elseif nQuality == 4 then
					   KChat.BroadcastNoticeMsg("<"..pKiller.szName..Lang.pet.str46[Lang.Idx]..pDead.szName..">")
					elseif nQuality == 5 then
					  KChat.BroadcastNoticeMsg("<"..pKiller.szName..Lang.pet.str47[Lang.Idx]..pDead.szName..">")
					elseif nQuality == 6 then
					  KChat.BroadcastNoticeMsg("<"..pKiller.szName..Lang.pet.str48[Lang.Idx]..pDead.szName..">")
					end
				end

			end
		end
	end

	if pDead.IsPlayer() then -- ��ұ�����ɱ��
		if self.tbPlayers[pDead.dwId] ~= nil then
			self.tbPlayers[pDead.dwId].bWin = 0
			self.tbPlayers[pDead.dwId].bFighting = 0
			self.tbPlayers[pDead.dwId].nKillCount = 0  -- ����
			pDead.SendBlackMsg(Lang.pet.str49[Lang.Idx])
			

			self.__RemoveAllPets(pDead.dwId) -- ɾ������npc
		end
	end
end

-- ��ҵǳ�ʱ�Ƴ�����
function PetIsland:OnLogout(dwCharacterId)
	local pPlayer = KGameBase.GetCharacterById(dwCharacterId);
	if (pPlayer ~= nil) and (pPlayer.IsNpc() == 1) then
		return
	end

	-- ���������ҽ��뵽���ﵺ������Ϊ
	local nMapId = pPlayer.dwSceneTemplateId;
	-- KScene.GetSceneType(nMapId) ~= 1 or
	if nMapId ~= self.nPetIslandMapId then--self.tbSetting[nMapId] == nil then
		return;
	end

	Instance:LeaveMyInstance(pPlayer)
end

-- ==================================================== C2S
-- ���������ﵺ, ����233
function PetIsland:c2s_EnterPetIsland(pPlayer)
	Instance:LeaveMyInstance(pPlayer)  -- ��ȷ��û�и���
	self:EnterPetIsland(pPlayer)
end

-- ˢ��npc, ����2����
--[[function PetIsland:c2s_RefreshPets(pPlayer, nQuality)
	-- �Ƿ�����ȼ���ˢ�¸�Ʒ�ʳ���
	local nRequireLevel = tonumber(self.tbPetDefs[nQuality].RequireLevel)
	if pPlayer.GetLevel() < nRequireLevel then
		pPlayer.SendBlackMsg(string.format("��Ҫ�ﵽ%d�������ٻ���Ʒ�ʵĴ���", nRequireLevel))
		return
	end

	self:RefreshPets(pPlayer, nQuality);
end--]]

-- ��ʼ������ս��
function PetIsland:c2s_StartFight(pPlayer)
	return self:StartFight(pPlayer)
end

-- ����ˢ�³���ɹ���
function PetIsland:c2s_UpRefreshRate(pPlayer, nQuality)
	return self:UpRefreshRate(pPlayer,nQuality)
end

function PetIsland:c2s_RefreshNature(pPlayer)
	-- ��Ԫ��
	local nCurCoin = me.pPlayerPurse.GetMoney(Purse.EM_MONEY_COIN);
	local nNeedCoin = 10 -- ����10��
	if (nCurCoin < nNeedCoin) then
		me.CallClientScript({"YoulongApp.UI.Controller.QUIClientScript:ShowCoinNotEnoughPanel", "", 10});
		return 0;
	end
	
	me.pPlayerPurse.AddMoney(Purse.EM_MONEY_COIN, -10);
	local tbPetDef2 = self.tbPlayerPetDefs[pPlayer.dwId]
	tbPetDef2[4] = KUnify.MathRandom(1,7)  -- ����Ը�, ����
	
	-- ˢ�¿ͻ���
	self:__ClientPetInfo(pPlayer, tbPetDef2[2], self.tbPlayerPetQuality[pPlayer.dwId], tbPetDef2[4])
end

-- սʤ�����ѡ�����(nIndex : 1-4)
function PetIsland:c2s_ChoosePet(pPlayer)
	if (self.tbPlayers[pPlayer.dwId].bWin == 1) then
		-- AddPlayerPet
		local tbPetDef2 = self.tbPlayerPetDefs[pPlayer.dwId]
		local nPetTempId = tbPetDef2[2]
		local nNature = tbPetDef2[4]
		-- �ж��Ƿ����㹻�ռ�ų���
		local bOk = Pet:AddPet(pPlayer, nPetTempId, nNature)

		if bOk == 1 then
		    --Instance:LeaveMyInstance(pPlayer)
		else
		    -- ���ﴴ��ʧ��
		    --pPlayer.SendBlackMsg("�޷���ȡ��������������Ƿ�����")
		    -- ��ӳ��ﵰ
		    local tbPetItemGDPL = tbPetDef2[3]
		    KItem.AddPlayerItem(pPlayer, tbPetItemGDPL[1], tbPetItemGDPL[2], tbPetItemGDPL[3], tbPetItemGDPL[4], 1)
		    -- TODO: ���ﵰ

		    --pPlayer.SysMsg("��ȡ�����ﵰ...")
		end
		self:__ClientShowIslandPanel(pPlayer)  -- ���³���ˢ�����
		KPet.RecordPetIslandCurrentInfo(pPlayer, 0, 0, 0, 0); -- ����ϴ��ٻ���Ϣ
	end
end
