if not MODULE_GAMESERVER then
	return
end

Kin.nCurrXianCampSelectCount = 0;
Kin.nCurrFoCampSelectCount = 0;

-- ��ҵ����ó�
function Kin:c2s_Impeach(pPlayer)
	local tbCostGDPL = {18, 1, 266};
	local tbFind = me.pItem.FindItemInBags(unpack(tbCostGDPL));
	local nHaveNum = Item:GetItemAmount(tbFind);

	if (nHaveNum < 1) then
		me.SysMsg(Lang.item.str203[Lang.Idx]);
		return;
	end
	
	KGameBase.CenterExecute({"Kin:Impeach_gc", pPlayer.dwId});
end

-- ����Ƿ�����ƽ��峤
function Kin:DoCheckChangeMaster(pPlayer)
	if KinBattle:IsWinner(pPlayer) == 1 then
		pPlayer.SendBlackMsg(Lang.item.str204[Lang.Idx]);
		return 0;
	end
	
	return 1;
end

function Kin:c2s_SetApplyerState(pPlayer, dwApplyerId, dwTongId, nState)
  KGameBase.CenterExecute({"SetApplyerState", pPlayer.dwId, dwApplyerId, dwTongId, nState});
end

function Kin:c2s_RandomSelectKinCamp(pPlayer)
  if pPlayer.GetKinCamp() ~= 0 --[[or pPlayer.GetLevel() ~= 19--]] then
      return;
  end
  
  -- �ķ���Ӫ�����پ�ѡ�ķ����������
  local nKinCamp = 1;
  if Kin.nCurrXianCampSelectCount > Kin.nCurrFoCampSelectCount then
      nKinCamp = 2
  elseif Kin.nCurrXianCampSelectCount < Kin.nCurrFoCampSelectCount then
      nKinCamp = 1
  else
      nKinCamp = KUnify.MathRandom(1, 2);
  end
  
  pPlayer.SetKinCamp(nKinCamp);
  
  if nKinCamp == 1 then
      Kin.nCurrXianCampSelectCount = Kin.nCurrXianCampSelectCount + 1;
      pPlayer.SendBlackMsg(Lang.item.str205[Lang.Idx])
  end
  if nKinCamp == 2 then
      Kin.nCurrFoCampSelectCount = Kin.nCurrFoCampSelectCount + 1;
      pPlayer.SendBlackMsg(Lang.item.str206[Lang.Idx])
  end
  
  me.pPlayerPurse.AddMoney(Item.EM_MONEY_SILVER, 1000); -- �漴ѡ����1000����
end

function Kin:c2s_SelectKinCamp(pPlayer, nKinCamp)
  if pPlayer.GetKinCamp() ~= 0 or --[[pPlayer.GetLevel() ~= 19 or--]] nKinCamp < 1 or nKinCamp > 2 then
      return;
  end
  pPlayer.SetKinCamp(nKinCamp);
  
  if nKinCamp == 1 then
      Kin.nCurrXianCampSelectCount = Kin.nCurrXianCampSelectCount + 1;
  end
  if nKinCamp == 2 then
      Kin.nCurrFoCampSelectCount = Kin.nCurrFoCampSelectCount + 1;
  end
end

-- ֪ͨ��ҵ���
function Kin:NotifyImpeach_gs(dwPlayerId, success)
    local tbCostGDPL = {18, 1, 266};
	local pPlayer = KGameBase.GetPlayerById(dwPlayerId);
	if(nil == pPlayer) then 
		return;
	end
	if success == 1 then
	    pPlayer.pItem.ConsumeItemInBags(1, unpack(tbCostGDPL));
	    KChat.BroadcastKinNoticeMsg(pPlayer.GetKinId(), pPlayer.szName .. Lang.item.str207[Lang.Idx]);
	else
	    pPlayer.SendBlackMsg(Lang.item.str208[Lang.Idx]);
  end
end

function Kin:NotifyUpgradeSuccess(dwMasterId, KinLevel)
  local pPlayer = KGameBase.GetPlayerById(dwMasterId);
  KChat.BroadcastKinNoticeMsg(pPlayer.GetKinId(), string.format(Lang.item.str209[Lang.Idx],pPlayer.szName,KinLevel));
  --KChat.BroadcastKinNoticeMsg(pPlayer.GetKinId(), "�峤<"..pPlayer.szName..">�Ѽ�������"..KinLevel.."��"..",��л������ڵĸ�����");
end

function Kin:UpdatePlayerKinLevelInfos(nKinId, nKinLevel)
   UpdateAllPlayerKinLevelInfo(nKinId, nKinLevel);
end

function Kin:c2s_CreateTong(pPlayer, name)
	print("..Kin:c2s_CreateTong name=" .. name);
	local nPrice = 200000;
	local dwNow = KGameBase.GetTime();
	local quitTime = pPlayer.GetLastQuitTongTime();
	if Lib:GetLocalDay(dwNow) == Lib:GetLocalDay(quitTime) then
		me.SendBlackMsg(Lang.item.str210[Lang.Idx])
		return -1;
	end
	
	if me.pPlayerPurse.GetMoney(Item.EM_MONEY_SILVER) < nPrice then
		me.SendBlackMsg(string.format(Lang.item.str211[Lang.Idx],nPrice))
		return -1;
	end
	--me.pPlayerPurse.AddMoney(Item.EM_MONEY_SILVER, -nPrice);
	CreateKin(me.dwId, name, 0, pPlayer.GetKinCamp());
end 


function Kin:c2s_BroadcastRecruitMsg(pPlayer, kinName)
  local nPrice = 20000;
	if me.pPlayerPurse.GetMoney(Item.EM_MONEY_SILVER) < nPrice then
		me.SendBlackMsg(Lang.item.str212[Lang.Idx])
		return -1;
	end
	me.pPlayerPurse.AddMoney(Item.EM_MONEY_SILVER, -nPrice);
	
  KChat.BroadcastSysMsg(string.format(Lang.item.str213[Lang.Idx],kinName,kinName));
  --KChat.BroadcastSysMsg("��λ������ע�⣡����<color=red>��"..kinName.."�� <color=235,123,49>���ڻ�����ļ�У����<color=green>\\b\\p"..kinName.."\\p���\\b#<color=235,123,49>����ɣ�");
end

function Kin:c2s_UpgradeKin(pPlayer, name)
	KGameBase.CenterExecute({"Kin:DoKinUpgrade", pPlayer.dwId, pPlayer.GetKinId()});
end 

function Kin:GiveAward(dwPlayerId, nKinLevel, nDailyAttribution)
	local nTotalContributionOneDay = GetKinTotalContributionOneDay();
	local nAwardPercent = (nDailyAttribution / nTotalContributionOneDay) * 50 + 50;	
	if nAwardPercent > 600 then  -- ���6������
	    nAwardPercent = 600;
	end
	
	if nAwardPercent > 0 then
	    local pPlayer = KGameBase.GetPlayerById(dwPlayerId);
	    KAward.AddPlayerAward(pPlayer, "TongSalary", nKinLevel, 1, nAwardPercent);
	    
	    -- ��ռ��幱�׶�
	    local nCurAttribution = pPlayer.pPlayerPurse.GetMoney(Purse.EM_MONEY_CONTRIBUTION)
	    pPlayer.pPlayerPurse.AddMoney(Purse.EM_MONEY_CONTRIBUTION, -nCurAttribution)
	end
end 

function Kin:OnPlayerJoinTong(nPlayerId, nTongId)
    local pPlayer = KGameBase.GetPlayerById(nPlayerId);
    local nLastQuitTongTime = pPlayer.GetLastQuitTongTime();
    local nCurrTime = KGameBase.GetTime();
    local quitDay = Lib:GetLocalDay(nLastQuitTongTime);
    local nowDay = Lib:GetLocalDay(nCurrTime);

    if nowDay > quitDay then   -- �ų�ͬһ�����˳��ּ����������
        self:GiveAward(nPlayerId, 1, 0);
    end
end

function Kin:SendKinErrorMsg(nPlayerId, msg)
   local pPlayer = KGameBase.GetPlayerById(nPlayerId);
   pPlayer.SendBlackMsg(msg);
end