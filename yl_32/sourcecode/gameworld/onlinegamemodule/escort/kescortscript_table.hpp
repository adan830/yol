/* -------------------------------------------------------------------------
//	�ļ���		��	ktowerscript_table.hpp
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
	{"RefreshEscortPlayers", LuaRefreshEscortPlayers, "", "d", "nPlayerId;", ""},
	{"ClearEscortData", LuaClearEscortData, "", "d", "nPlayerId;", ""},
	{"RemoveEscortWatch", LuaRemoveEscortWatch, "", "d", "nPlayerId;", ""},
	{"SpeedUpEscort", LuaSpeedUpEscort, "", "dd", "nPlayerId;bSpeed;", ""},
	{"SetLastRefreshTime", LuaSetLastRefreshTime, "", "?d", "nPlayerId/pPlayer:��ɫId���߶���;dwTime;", ""},
	{"GetLastRefreshTime", LuaGetLastRefreshTime, "", "?", "nPlayerId/pPlayer:��ɫId���߶���;", ""},
	
#endif // #ifdef GAME_SERVER
};
