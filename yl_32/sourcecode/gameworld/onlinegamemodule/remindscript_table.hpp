/* -------------------------------------------------------------------------
//	�ļ���		��	remindscript_table.hpp
//	������		��	LuaScriptTool
//	��������	��	���ļ���VisualStudio�����ɣ��벻Ҫ�ֶ��޸ģ���
//	ʹ�÷���	��	����Ӧ��CPP�ļ�ĩ�ˣ�include���ļ�
//
// -----------------------------------------------------------------------*/

CONST SCRIPT_FUNCTION arFunction[]	=  
{
	// �ͻ���/�����0���Ȳ��ܱ���ͨ�����Ÿ�û�õĽ���
	{"...", NULL, "", "", "", ""},

#ifdef GAME_SERVER
	{"AddRemindToPlayer", LuaAddRemindToPlayer, "", "od", "����;����id;", ""},
	{"RemoveRemindToPlayer", LuaRemoveRemindToPlayer, "", "od", "����;����id;", ""},
#endif // #ifdef GAME_SERVER
};
