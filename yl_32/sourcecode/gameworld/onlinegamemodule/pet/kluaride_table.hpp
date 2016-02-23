/* -------------------------------------------------------------------------
//	�ļ���		��	kluaride_table.hpp
//	������		��	LuaScriptTool
//	��������	��	���ļ���VisualStudio�����ɣ��벻Ҫ�ֶ��޸ģ���
//	ʹ�÷���	��	����Ӧ��CPP�ļ�ĩ�ˣ�include���ļ�
//
// -----------------------------------------------------------------------*/

DEFINE_LUA_CLASS_BEGIN(KLuaRide)
	REGISTER_LUA_DWORD_READONLY(Id, "����Id")
	REGISTER_LUA_DWORD_READONLY(OwnerId, "��������Id")
	REGISTER_LUA_INTEGER_READONLY(Genre, "����G")
	REGISTER_LUA_INTEGER_READONLY(Detail, "����D")
	REGISTER_LUA_INTEGER_READONLY(Particular, "����P")
	REGISTER_LUA_INTEGER_READONLY(Level, "����Level")
	REGISTER_LUA_INTEGER_READONLY(Hungry, "������")
	REGISTER_LUA_INTEGER_READONLY(State, "����״̬")
	REGISTER_LUA_INTEGER_READONLY(MagicRate, "��ǰ�û�������")
	REGISTER_LUA_STRING_READONLY(Name, "��������")

#ifdef GAME_SERVER
	REGISTER_LUA_FUNC(SetMagicRate, "���õ�ǰ�û�������", "", "", "")
	REGISTER_LUA_FUNC(Sync, "ͬ���������ݵ��ͻ���", "", "", "1�ɹ�")
	REGISTER_LUA_FUNC(AddHungry, "���ӱ�ʳ��", "d", "nHungry	;", "1�ɹ�")
	REGISTER_LUA_FUNC(SetState, "��������״̬", "d", "nState	;", "1�ɹ�")
	REGISTER_LUA_FUNC(Regenerate, "��������һֻ����", "dddd", "nGenre	;nDetail	;nParticular;nLevel;", "�ɹ�����1")
#endif // #ifdef GAME_SERVER
DEFINE_LUA_CLASS_END()
