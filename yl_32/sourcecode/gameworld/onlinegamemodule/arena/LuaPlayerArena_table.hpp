/* -------------------------------------------------------------------------
//	�ļ���		��	LuaPlayerArena_table.hpp
//	������		��	LuaScriptTool
//	��������	��	���ļ���VisualStudio�����ɣ��벻Ҫ�ֶ��޸ģ���
//	ʹ�÷���	��	����Ӧ��CPP�ļ�ĩ�ˣ�include���ļ�
//
// -----------------------------------------------------------------------*/

DEFINE_LUA_CLASS_BEGIN(LuaPlayerArena)
	REGISTER_LUA_FUNC(StartArena, "�ս��뾺����", "", "", "")
	REGISTER_LUA_FUNC(LoadArenaPlayers, "����npc", "", "", "")
	REGISTER_LUA_FUNC(LoadFrontArenaPlayers, "����ǰ5��npc", "", "", "")
	REGISTER_LUA_FUNC(Challenge, "��ս", "", "", "")
	REGISTER_LUA_FUNC(GetCDTime, "�õ���սCDʱ��", "", "", "")
	REGISTER_LUA_FUNC(SetCDTime, "������սCDʱ��", "", "", "")
	REGISTER_LUA_FUNC(SetTakeAwardTime, "������ȡ��������ʱ��", "", "", "")
	REGISTER_LUA_FUNC(GetWinCombo, "�õ���ʤ����", "", "", "")
	REGISTER_LUA_FUNC(SetWinCombo, "������ʤ����", "", "", "")
	REGISTER_LUA_FUNC(GetTakeComboAward, "�õ���ȡ��ʤ��������", "", "", "")
	REGISTER_LUA_FUNC(SetTakeComboAward, "������ȡ��ʤ��������", "", "", "")
	REGISTER_LUA_FUNC(SyncArenaInfo, "���;�������Ϣ", "", "", "")
	REGISTER_LUA_FUNC(ClearData, "�������������", "", "", "")
	REGISTER_LUA_FUNC(ResetData, "0�����þ�����", "", "", "")
DEFINE_LUA_CLASS_END()
