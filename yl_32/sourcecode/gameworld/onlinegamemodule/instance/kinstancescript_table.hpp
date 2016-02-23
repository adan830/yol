/* -------------------------------------------------------------------------
//	�ļ���		��	kinstancescript_table.hpp
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
	{"GetMultiStartTime", LuaGetMultiStartTime, "�õ���ʼ���˸���ʱ��", "o", "pPlayer;", ""},
	{"SetMultiStartTime", LuaSetMultiStartTime, "���ÿ�ʼ���˸���ʱ��", "od", "pPlayer;��ʼ��սʱ��;", ""},
	{"GetMultiState", LuaGetMultiState, "�õ���ǰ���˸���״̬", "o", "pPlayer;", ""},
	{"SetMultiState", LuaSetMultiState, "", "od", "pPlayer;����;", ""},
	{"GetMultiRushStar", LuaGetMultiRushStar, "�õ����˸�������", "o", "pPlayer;", ""},
	{"SetMultiRushStar", LuaSetMultiRushStar, "", "od", "pPlayer;����;", ""},
	{"GetMultiRushMapId", LuaGetMultiRushMapId, "�õ����˸�����ͼid", "o", "pPlayer;", ""},
	{"SetMultiRushMapId", LuaSetMultiRushMapId, "", "od", "pPlayer;����;", ""},
	{"IsMultiMapPassed", LuaIsMultiMapPassed, "�Ƿ�ͨ����mapId�Ķ��˸���", "od", "pPlayer;mapId;", ""},
	{"SetMultiMapPassed", LuaSetMultiMapPassed, "����mapId�Ķ��˸�����ͨ��״̬", "od", "pPlayer;mapId;", ""},
#endif // #ifdef GAME_SERVER
};
