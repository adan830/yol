/* -------------------------------------------------------------------------
//	�ļ���		��	kcrosssvscript_table.hpp
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

	{"ClearDropItems", LuaClearDropItems, "��ռ�¼�������", "?", "nPlayerId/pPlayer:��ɫId���߶���;", ""},
	{"RecordDropItems", LuaRecordDropItems, "��¼�������", "?ddddd", "nPlayerId/pPlayer:��ɫId���߶���;g;d;p;l;amount;", ""},
	
#endif // #ifdef GAME_SERVER
};
