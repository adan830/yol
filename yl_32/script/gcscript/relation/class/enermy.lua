--=================================================
-- �ļ�������enermy.lua
-- �����ߡ���
-- ����ʱ�䣺
-- �������������˹�ϵ�߼�
--=================================================

Require("\\script\\gcscript\\relation\\relation_logic.lua");
local tbEnermy = {};

-- if (not MODULE_GC_SERVER and not MODULE_GAMESERVER) then
--	return;
-- end

if (MODULE_GAMECENTER) then
	
end

if (MODULE_GAMESERVER) then
	
end

Relation:Register(Relation.emKPLAYERRELATION_TYPE_ENEMEY, tbEnermy)
