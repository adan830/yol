/* -------------------------------------------------------------------------
//	�ļ���		��	kgcglobaldatascript_table.hpp
//	������		��	JXLuaMapTableMaker
//	��������	��	���ļ���VS2005 Macro�Զ����ɣ��벻Ҫ�ֶ��޸ģ���
//	ʹ�÷���	��	����Ӧ��CPP�ļ�ĩ�ˣ�include���ļ�
//
// -----------------------------------------------------------------------*/

CONST SCRIPT_FUNCTION arFunction[]	=  
{
#ifdef GAME_CENTER
	{"SetIntValue", LuaSetIntValue, "����һ��ȫ�����α���", "dd", "Key;Value;", "d"},
	{"AddIntValue", LuaAddIntValue, "�ۼ�һ��ȫ�����α���", "dd", "Key;Value;", "d"},
	{"GetIntValue", LuaGetIntValue, "���һ��ȫ�����α���", "d", "Key;", ""},
	{"SetStrValue", LuaSetStrValue, "", "ds", "Key;Value;", ""},
	{"GetStrValue", LuaGetStrValue, "", "d", "Key;", ""},
	{"DelStrValue", LuaDelStrValue, "", "d", "Key;", ""},
#endif // #ifdef GAME_CENTER
};
