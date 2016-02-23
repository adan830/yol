
-- �������

-------------------------------------------------------------------
--File: 	randomitem.lua
--Author: 	
--Date: 	
--Describe:	��ȡ�����Ʒ��ͨ�ýű�
--��һ����չ��������������еĵڼ���
--������չ������ʱ��������

------------------------------------------------------------------------------------------
-- initialize

local tbRandomItem = Item:GetClass("randomitem");

------------------------------------------------------------------------------------------
-- public

local tbRandomFile = Lib:LoadTabFile("/setting/item/magic/randomitem.txt") or {};

--[[
[1]:
[1].Amount	= "������ֻ�е������ã�"
[1].Announce	= "���繫��"
[1].Bind	= "��"
[1].Desc	= "������"
[1].DetailType	= ""
[1].EnhTimes	= "ǿ��"
[1].Exp	= "����"
[1].Genre	= ""
[1].Id	= "����ID"
[1].KinOrTongMsg	= "������ṫ��"
[1].KindId	= "Kind��ID"
[1].Level	= ""
[1].Money	= "����"
[1].Name	= "������Ʒ����"
[1].ParticularType	= ""
[1].Probability	= "���ʣ�����Ϊ10000���ܸ���С��10000ʱ�м��ʲ�������ߣ��������10000�����10000�Ĳ����治����"
[1].RandomCount	= "�������"
[1].TimeLimit	= "��Ч��"
[1].YLEnergy	= "��������"
[2]:
[2].Amount	= ""
[2].Announce	= ""
[2].Bind	= ""
[2].Desc	= ""
[2].DetailType	= "1"
[2].EnhTimes	= ""
[2].Exp	= "100"
[2].Genre	= "1"
[2].Id	= "1"
[2].KinOrTongMsg	= ""
[2].KindId	= "1"
[2].Level	= "1"
[2].Money	= ""
[2].Name	= "100����"
[2].ParticularType	= "1"
[2].Probability	= "2000"
[2].RandomCount	= "3"
[2].TimeLimit	= ""
[2].YLEnergy	= ""
[3]:
[3].Amount	= ""
[3].Announce	= ""
[3].Bind	= ""
[3].Desc	= ""
[3].DetailType	= ""
[3].EnhTimes	= ""
[3].Exp	= "200"
[3].Genre	= ""
[3].Id	= "2"
[3].KinOrTongMsg	= ""
[3].KindId	= "1"
[3].Level	= ""
[3].Money	= ""
[3].Name	= "200����"
[3].ParticularType	= ""
[3].Probability	= "2000"
[3].RandomCount	= "3"
[3].TimeLimit	= ""
[3].YLEnergy	= ""
[4]:
[4].Amount	= ""
[4].Announce	= ""
[4].Bind	= ""
[4].Desc	= ""
[4].DetailType	= ""
[4].EnhTimes	= ""
[4].Exp	= "300"
[4].Genre	= ""
[4].Id	= "3"
[4].KinOrTongMsg	= ""
[4].KindId	= "1"
[4].Level	= ""
[4].Money	= ""
[4].Name	= "300����"
[4].ParticularType	= ""
[4].Probability	= "2000"
[4].RandomCount	= "3"
[4].TimeLimit	= ""
[4].YLEnergy	= ""

--]]

function tbRandomItem:CheckUsable()
	return	1;						-- ����
end




function tbRandomItem:OnUse()
	print("..tbRandomItem:OnUse()");
    --[[
	local nNeedBag = 0;
	local nRandomId = tonumber(it.GetExtParam(1));
	for _,tbRow in pairs(tbRandomFile) do  --����-1�����⴦��
		if tonumber(tbRow.KindId) == nRandomId then
			if tonumber(tbRow.Probability) == -1 then
				if (tonumber(tbRow.Genre) and tonumber(tbRow.Genre) ~= 0) then
					nNeedBag = nNeedBag + 1;
				end
			end
		end
	end
	
	for _,tbRow in pairs(tbRandomFile) do  --
		if tonumber(tbRow.KindId) == nRandomId then
			if tonumber(tbRow.Probability) ~= -1 then
				if (tonumber(tbRow.Genre) and tonumber(tbRow.Genre) ~= 0) then
					nNeedBag = nNeedBag + 1;
					return;
				end
			end
		end
	end
	if me.pItem.CountFreeBagCell() < nNeedBag then
		me.SysMsg(Lang.item.str55[Lang.Idx]);
		return 0;
	end
    --]]
    
    --Lib:ShowTB(tbRandomFile);

    --local nKindId = tonumber(it.GetExtParam(1));
	
	local nMoneyType  = tonumber(it.GetExtParam(9));
	local nMoneyCount = tonumber(it.GetExtParam(10));
	
    
    --local tbRows = {};
    --for i=2,#tbRandomFile do 
    --    if(tonumber(tbRandomFile[i].KindId) == nKindId) then 
    --        tbRows[#tbRows + 1] = tbRandomFile[i];
    --    end
    --end
    
    if(nMoneyType and nMoneyType > 0) then
         local szMoneyUnit = "";
         if(nMoneyType == 1 ) then 
            szMoneyUnit = Lang.item.str59[Lang.Idx];
         elseif(nMoneyType == 2) then
            szMoneyUnit = Lang.item.str60[Lang.Idx];
         elseif(nMoneyType == 3) then
            szMoneyUnit = Lang.item.str61[Lang.Idx];
         elseif(nMoneyType == 4) then
            szMoneyUnit = Lang.item.str62[Lang.Idx];
         end
         local szMsg = string.format(Lang.mission.str1220[Lang.Idx],nMoneyCount,szMoneyUnit);
         Dialog:_AskForSure(me.dwId, szMsg, ({"Item:RandomItemCallback", me,it}), "GetRandomItem", 0);
	else
		Item:RandomItemCallback(me,it);
    end
	--tbRandomItem:SureOnUse();
end

--����
function tbRandomItem:SureOnUse()
	local nRandomId = tonumber(it.GetExtParam(1));
	local nRate = KUnify.MathRandom(1,10000);
	local nId;
	local nLineCount = 0;
	
	for _,tbRow in pairs(tbRandomFile) do  --����-1�����⴦��
		nLineCount = nLineCount + 1;
		if tonumber(tbRow.KindId) == nRandomId then
			if tonumber(tbRow.Probability) == -1 then
				nId = tbRow.Id;
				tbRandomItem:GetItem(nLineCount);
			end
		end
	end
	
	nLineCount = 0;
	for _,tbRow in pairs(tbRandomFile) do  --���������������һ��
		nLineCount = nLineCount + 1;
		if tonumber(tbRow.KindId) == nRandomId then
			if (tonumber(tbRow.Probability) and tonumber(tbRow.Probability) ~= -1) then
				nRate = nRate - tonumber(tbRow.Probability);
				if nRate <= 0 then	--���û�е������ζ����һ�����ʲ����������
					nId = tonumber(tbRow.Id);
					tbRandomItem:GetItem(nLineCount);
					return;
				end
			end
		end	
	end
end

--����
function tbRandomItem:GetItem(nLineCount)
	local nKindId = tonumber(tbRandomFile[nLineCount].KindId);
	local szDesc = tbRandomFile[nLineCount].Desc;
	local nId = tonumber(tbRandomFile[nLineCount].Id);
	local szName = tbRandomFile[nLineCount].Name;
	local nExp = tonumber(tbRandomFile[nLineCount].Exp) or 0;
	local nMoney = tonumber(tbRandomFile[nLineCount].Money) or 0;
	local nYLEnergy = tonumber(tbRandomFile[nLineCount].YLEnergy) or 0;
	local nGenre = tonumber(tbRandomFile[nLineCount].Genre) or 0;
	local nDetailType = tonumber(tbRandomFile[nLineCount].DetailType) or 0;
	local nParticularType = tonumber(tbRandomFile[nLineCount].ParticularType) or 0;
	local nLevel = tonumber(tbRandomFile[nLineCount].Level) or 0;
	local nEnhTimes = tonumber(tbRandomFile[nLineCount].EnhTimes) or 0;
	local nAmount = tonumber(tbRandomFile[nLineCount].Amount) or 1;
	local nBindType = tonumber(tbRandomFile[nLineCount].Bind) or 0;
	local nTimeLimit = tonumber(tbRandomFile[nLineCount].TimeLimit) or 0;
	local nAnnounce = tonumber(tbRandomFile[nLineCount].Announce) or 0;
	local nKinOrTongMsg = tonumber(tbRandomFile[nLineCount].KinOrTongMsg) or 0;
	
	--��ȡ����
	if (nExp and nExp ~= 0 and nAnnounce and nAnnounce ~= 0) then
		me.AddExp(nExp);
		local Msg = string.format(Lang.item.str65[Lang.Idx], me.szName, szName, nExp);
		pPlayer.CallClientScript({"YoulongApp.UI.Controller.QUIClientScript:ShowNoticeMessage", "Msg"});
	elseif (nExp and nExp ~= 0 and nKinOrTongMsg and nKinOrTongMsg ~= 0) then
		me.AddExp(nExp);
		local Msg = string.format(Lang.item.str65[Lang.Idx], me.szName, szName, nExp);
		pPlayer.CallClientScript({"YoulongApp.UI.Controller.QUIClientScript:ShowNoticeMessage", "Msg"});
	elseif (nExp and nExp ~= 0) then
		me.AddExp(nExp);
	end
	
	--��ȡ����
	if (nMoney and nMoney ~= 0 and nAnnounce and nAnnounce ~= 0) then
		me.pPlayerPurse.AddMoney(2, nMoney);
		local Msg = string.format(Lang.item.str66[Lang.Idx], me.szName, szName, nMoney);
		pPlayer.CallClientScript({"YoulongApp.UI.Controller.QUIClientScript:ShowNoticeMessage", "Msg"});
	elseif (nMoney and nMoney ~= 0 and nKinOrTongMsg and nKinOrTongMsg ~= 0) then
		me.pPlayerPurse.AddMoney(2, nMoney);
		local Msg = string.format(Lang.item.str66[Lang.Idx], me.szName, szName, nMoney);
		pPlayer.CallClientScript({"YoulongApp.UI.Controller.QUIClientScript:ShowNoticeMessage", "Msg"});
	elseif (nMoney and nMoney ~= 0) then
		me.pPlayerPurse.AddMoney(2, nMoney);
	end
	
	--��ȡ��������
	if (nYLEnergy and nYLEnergy ~= 0 and nAnnounce and nAnnounce ~= 0) then
		me.pPlayerPurse.AddMoney(6, nYLEnergy);
		local Msg = string.format(Lang.item.str67[Lang.Idx], me.szName, szName, nYLEnergy);
		pPlayer.CallClientScript({"YoulongApp.UI.Controller.QUIClientScript:ShowNoticeMessage", "Msg"});
	elseif (nYLEnergy and nYLEnergy ~= 0 and nKinOrTongMsg and nKinOrTongMsg ~= 0) then
		me.pPlayerPurse.AddMoney(6, nYLEnergy);
		local Msg = string.format(Lang.item.str67[Lang.Idx], me.szName, szName, nYLEnergy);
		pPlayer.CallClientScript({"YoulongApp.UI.Controller.QUIClientScript:ShowNoticeMessage", "Msg"});
	elseif (nYLEnergy and nYLEnergy ~= 0) then
		me.pPlayerPurse.AddMoney(6, nYLEnergy);
	end
	
	--��ȡ����
	if nAmount ~= 0 then  --Amountר��������ӵ���
		local pItem = KItem.AddPlayerItem(me, nGenre, nDetailType, nParticularType, nLevel, nAmount);
		local szItemName = pItem.szName;
		if nBindType and nBindType == 1 then
			pItem.Bind(1);
		end
		if pItem and nAnnounce ~= 0 then
			local Msg = string.format(Lang.item.str68[Lang.Idx], me.szName, szName, nAmount, szItemName);
			pPlayer.CallClientScript({"YoulongApp.UI.Controller.QUIClientScript:ShowNoticeMessage", "Msg"});
		elseif pItem and nKinOrTongMsg ~= 0 then
			local Msg = string.format(Lang.item.str68[Lang.Idx], me.szName, szName, nAmount, szItemName);
			pPlayer.CallClientScript({"YoulongApp.UI.Controller.QUIClientScript:ShowNoticeMessage", "Msg"});
		end
	end
	KItem.DelPlayerItem(me, it);	
	--������ʱ
	--����ǿ������
	--���繫��
	--���幫���

end



