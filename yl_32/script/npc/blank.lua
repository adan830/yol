
-- �հ�Npcģ��

if not (MODULE_GAMECLIENT or MODULE_GAMESERVER) then
	return
end

local tbAnimal	= Npc:GetClass("blank");

function tbAnimal:OnDialog()
    -- if him.dwTemplateId and Npc.tbNpcTemplate[him.dwTemplateId] then
		-- TaskAct:Talk(string.format("<npcpic=%d>%s<end><playername=%s>%s", him.dwTemplateId, Npc.tbNpcTemplate[him.dwTemplateId].dialogMsg, him.szName, "\\b�����Ի�\\b#"));
	-- end
end

function tbAnimal:OnDeath()
end
