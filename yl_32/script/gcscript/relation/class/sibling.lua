--=================================================
-- �ļ�������sibling.lua
-- �����ߡ���
-- ����ʱ�䣺
-- ������������ݹ�ϵ�߼���Ŀǰ��û�������ϵ�������Ȱ��������д�ϰɣ�
--=================================================

Require("\\script\\gcscript\\relation\\relation_logic.lua");
local tbSibling = {};

-- if (not MODULE_GC_SERVER and not MODULE_GAMESERVER) then
--	return;
-- end

if (MODULE_GAMECENTER) then
	
end

if (MODULE_GAMESERVER) then
	
end

Relation:Register(Relation.emKPLAYERRELATION_TYPE_SIBLING, tbSibling)
