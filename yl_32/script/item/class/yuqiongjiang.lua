
-- �����

------------------------------------------------------------------------------------------
-- initialize

local tbYuQiongJiang = Item:GetClass("yuqiongjiang");

------------------------------------------------------------------------------------------

function tbYuQiongJiang:OnUse()
	local pItem = it;
	local nPercent = (tonumber(pItem.GetExtParam(1)) or 0) / 100;
	local nExp = nPercent * KGameBase.GetNextLevelExp(me.GetLevel()+1);
	
	--������Ϣ
	local tbPlayerKinInfo = GetPlayerKinInfo(me.dwId);
	local tbBonfire = Activity.tbBonfireInfo[me.GetKinId()];

	if tbPlayerKinInfo == nil or tbBonfire == nil then
		me.SendBlackMsg("������ʼ����ʹ������");
		return;
	end
	
	local nMapId = me.dwSceneTemplateId;
	if KScene.GetSceneTypeName(nMapId) ~= "city" then
		me.SendBlackMsg("����ֻ��������ʹ��");
		return;
	elseif KGameBase.GetIsSwimByPlayerId(me.dwId) == 1 then
		me.SendBlackMsg("����������ˮ����ʹ��");
		return;
	elseif tbBonfire.onGoing == 0 then
		me.SendBlackMsg("������ʼ����ʹ������");
		return;
	end

	-- local tbPos = me.GetPosition();
	-- local npc = KGameBase.CallNpc(2655, tbPos.dwSceneId, tbPos.nX, tbPos.nY, tbPos.nZ);

	-- ��ȡ���鲢���ĵ���	
	me.pItem.ConsumeItemInBags(1, pItem.nGenre, pItem.nDetail, pItem.nParticular, pItem.nLevel);
	me.AddExp(nExp);
	
	-- Activity.tbBonfireInfo[me.GetKinId()] = {onGoing = 1, sendTorch = 1, useTorch = 1, mapId = tbPos.dwSceneId, npcId = npc.dwId, tbPos = {tbPos.nX, tbPos.nY, tbPos.nZ}};
	-- KChat.BroadcastKinNoticeMsg(me.GetKinId(), "����������Ѿ�����ȼ������ͯЬ�ǿ��򿪼������μӰɣ�");
	-- KGameBase.CenterExecute{"Activity:UpdateBonfireInfo_GC", me.GetKinId(), Activity.tbBonfireInfo[me.GetKinId()]};
end





