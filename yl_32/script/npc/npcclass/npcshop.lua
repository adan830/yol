local tbNpc = Npc:GetClass("npcshop")

tbNpc.tbMsg = {
	[1] = Lang.npc.str80[Lang.Idx],
	[2] = Lang.npc.str81[Lang.Idx],	
	[3] = Lang.npc.str82[Lang.Idx],
}

function tbNpc:OnDialog()
	-- local tbOpt =
	-- {
		-- {"�ӻ��̵�",self.OpenNpcShop,self,2},
		-- {"�����̵�",self.OpenNpcShop,self,3},
		-- {"�����̵�",self.OpenNpcShop,self,4},
		-- {"�ſ����",self.OpenNpcShop,self,5},
	-- };
	--Dialog:Say("�����������챦����ӭ������!",tbOpt);
	--if him.dwTemplateId and tbNpc.tbMsg[him.dwTemplateId] then
		--TaskAct:Talk(string.format("<npcpic=%d>%s<end><playername=%s>%s", him.dwTemplateId, tbNpc.tbMsg[him.dwTemplateId], him.szName, " "));
	--end
	
	if him.dwTemplateId and Npc.tbNpcTemplate[him.dwTemplateId] then
		TaskAct:Talk(string.format("<npcpic=%d>%s<end><playername=%s>%s", him.dwTemplateId, Npc.tbNpcTemplate[him.dwTemplateId].dialogMsg, him.szName, " "));
	end
end

function tbNpc:OpenNpcShop(shopId)
	me.CallClientScript({"QClientScript.NpcShop:OpenNpcShopPanel", shopId});
end
