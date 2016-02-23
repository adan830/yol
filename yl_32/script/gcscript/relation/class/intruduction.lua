--=================================================
-- �ļ�������intruduction.lua
-- �����ߡ���
-- ����ʱ�䣺
-- ���������������˹�ϵ�߼�
--=================================================

Require("\\script\\gcscript\\relation\\relation_logic.lua");
local tbIntroduction = {};

-- if (not MODULE_GC_SERVER and not MODULE_GAMESERVER) then
--	return;
-- end


--=================================================
--============= MODULE_GC_SERVER ==================
--=================================================


if (MODULE_GAMECENTER) then
	

tbIntroduction.INTRODUCED_MAXLEVEL = 11;		-- �������˵���ߵȼ�
tbIntroduction.INTRODUCED_MIN_DIFLEVEL = 6;		-- �������뱻������֮�����С�ȼ���

-- �����˼ʹ�ϵ�������ж�
function tbIntroduction:CanCreateRelation(nRole, nAppId, nDstId)
	if (not nRole or not nAppId or not nDstId) then
		return 0;
	end
	
	if (nRole == 0) then
		nAppId, nDstId = nDstId, nAppId;
	end
	
	local nAppLevel = KRelation.GetOneRelationCount(nAppId, Player.emKPLAYERRELATION_TYPE_INTRODUCTION, 1);
	local nDstLevel = KRelation.GetOneRelationCount(nDstId, Player.emKPLAYERRELATION_TYPE_INTRODUCTION, 0);
	if (nDstLevel > self.INTRODUCED_MAXLEVEL) then
		Relation:SetInfoMsg(string.format(Lang.gcscript.str35[Lang.Idx], self.INTRODUCED_MAXLEVEL));
		return 0;
	end
	if (nAppId - nDstLevel < self.INTRODUCED_MIN_DIFLEVEL) then
		Relation:SetInfoMsg(string.format(Lang.gcscript.str36[Lang.Idx], self.INTRODUCED_MIN_DIFLEVEL));
		return 0;
	end
	
	return 1;
end
	
end














--=================================================
--============= MODULE_GAMESERVER =================
--=================================================


if (MODULE_GAMESERVER) then
	
end

Relation:Register(Relation.emKPLAYERRELATION_TYPE_INTRODUCTION, tbIntroduction)
