--=======================================================================
-- �ļ�������npcmgr_s.lua
-- �����ߡ���yulei(yulei1@kingsoft.com)
-- �޸��б�
-- ����ʱ�䣺2011-07-12 16:17:27
-- ����������
--=======================================================================

if not MODULE_GAMESERVER then
	return
end

Include("/script/npc/define.lua");

if (not Npc.NpcMgr) then
	Npc.NpcMgr = {};
end

local NpcMgr = Npc.NpcMgr;