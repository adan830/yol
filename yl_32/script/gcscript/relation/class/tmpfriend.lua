--=================================================
-- �ļ�������tmpfriend.lua
-- �����ߡ���
-- ����ʱ�䣺
-- ������������ʱ�����߼�
--=================================================

Require("\\script\\gcscript\\relation\\relation_logic.lua");
local tbTmpFriend = {};

-- if (not MODULE_GC_SERVER and not MODULE_GAMESERVER) then
--	return;
-- end

if (MODULE_GAMECENTER) then
	
end

if (MODULE_GAMESERVER) then
	
end

Relation:Register(Relation.emKPLAYERRELATION_TYPE_TMPFRIEND, tbTmpFriend)
