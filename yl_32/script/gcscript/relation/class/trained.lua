--=================================================
-- �ļ�������trained.lua
-- �����ߡ���
-- ����ʱ�䣺
-- ����������ʦͽ��ϵ�߼�����ʦ��ʦͽ��ϵ��Ҳ����ʦͽ���ѣ�
--=================================================

Require("\\script\\gcscript\\relation\\relation_logic.lua");
local tbTrained = {};

-- if (not MODULE_GC_SERVER and not MODULE_GAMESERVER) then
--	return;
-- end

if (MODULE_GAMECENTER) then
	
end

if (MODULE_GAMESERVER) then
	
end

Relation:Register(Relation.emKPLAYERRELATION_TYPE_TRAINED, tbTrained)
