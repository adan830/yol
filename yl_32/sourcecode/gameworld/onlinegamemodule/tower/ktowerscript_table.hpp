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
	{"StartMopTower", LuaStartMopTower, "��ʼɨ��", "?d", "nPlayerId/pPlayer:��ɫId���߶���;ɨ����Ҫʱ��;", ""},
	{"StopMopTower", LuaStopMopTower, "���ֹͣɨ��", "?d", "nPlayerId/pPlayer:��ɫId���߶���;�Ƿ���ɨ��һ��;", ""},
	{"GetSpeedUp", LuaGetSpeedUp, "�õ��Ƿ��ڼ���", "?", "nPlayerId/pPlayer:��ɫId���߶���;", ""},
	{"GetLeftMopTime", LuaGetLeftMopTime, "�õ�ɨ��ʣ��ʱ��", "?", "nPlayerId/pPlayer:��ɫId���߶���;", ""},
	{"GetMopStartTime", LuaGetMopStartTime, "�õ�ɨ����ʼʱ��", "?", "nPlayerId/pPlayer:��ɫId���߶���;", ""},
	{"FinishMop", LuaFinishMop, "ֱ�����ɨ��", "?", "nPlayerId/pPlayer:��ɫId���߶���;", ""},
	{"SpeedUpMop", LuaSpeedUpMop, "����ɨ��", "?", "nPlayerId/pPlayer:��ɫId���߶���;", ""},
	{"SyncTowerRank", LuaSyncTowerRank, "ͬ�����а�", "?", "", ""},
#endif // #ifdef GAME_SERVER
};
