--�̶�Ԥ�ȼ��صĽű����������нű����صĵ�һ��

-- GSר��
if not MODULE_GAMESERVER then
	return
end

print("Preload gs script files...");

Include("/script/npc/npc.lua");
Include("/script/doodad/doodad.lua");
Include("/script/task/task.lua");

Lib:DelayInherit(_KLuaCharacter, _KLuaPlayer);
Lib:DelayInherit(_KLuaCharacter, _KLuaNpc);
