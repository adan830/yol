/* -------------------------------------------------------------------------
//	�ļ���		��	luaplayertitle_table.hpp
//	������		��	LuaScriptTool
//	��������	��	���ļ���VisualStudio�����ɣ��벻Ҫ�ֶ��޸ģ���
//	ʹ�÷���	��	����Ӧ��CPP�ļ�ĩ�ˣ�include���ļ�
//
// -----------------------------------------------------------------------*/

DEFINE_LUA_CLASS_BEGIN(LuaPlayerTitle)
	REGISTER_LUA_FUNC(AddTitleToCharacter, "��ӳƺ�", "dddd", "��ȡ;��;��ֵ;����;�Ѿ����˶��;", "")
	REGISTER_LUA_FUNC(RemoveTitleToCharacter, "ɾ���ƺ�", "ddd", "��ȡ;��;��ֵ;����;", "")
	REGISTER_LUA_FUNC(SnycTitle, "ͬ���ƺ�", "", "", "")
	REGISTER_LUA_FUNC(ClearTitle, "����ƺ�", "", "", "")
DEFINE_LUA_CLASS_END()
