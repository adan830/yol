
local tbNpc = Npc:GetClass("battledelivery_whj_in")

local tbDeliveryPoint = {1214,6995,1063961};--����

function tbNpc:OnDialog()
	local nPlayerId = me.dwId;
	local nGroupId = Activity:GetPlayerGroup(nPlayerId);
	if nGroupId == 2 then
		tbNpc:GetDelivery();
	else
		local pPlayer = KGameBase.GetPlayerById(nPlayerId);
		pPlayer.SysMsg(Lang.npc.str11[Lang.Idx]);
		return;
	end
end

function tbNpc:GetDelivery()
	local dwSceneId = me.GetPosition().dwSceneId;
	me.TeleportTo(dwSceneId,tbDeliveryPoint[1],tbDeliveryPoint[2],tbDeliveryPoint[3]);
end
