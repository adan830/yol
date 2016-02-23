/* -------------------------------------------------------------------------
//	�ļ���		��	kstagescript_table.hpp
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
	{"StartMopStage", LuaStartMopStage, "��ʼɨ���ؿ�", "od", "pPlayer;nTotalTime;", ""},
	{"GetRushStartTime", LuaGetRushStartTime, "�õ���ʼ��ս�ؿ�ʱ��", "o", "pPlayer;", ""},
	{"SetRushStartTime", LuaSetRushStartTime, "���ÿ�ʼ��ս�ؿ�ʱ��", "od", "pPlayer;��ʼ��սʱ��;", ""},
	{"GetRushLayer", LuaGetRushLayer, "�õ���ǰ��ս��Ĺؿ���", "o", "pPlayer;", ""},
	{"SetRushLayer", LuaSetRushLayer, "���õ�ǰ��ս��Ĺؿ���", "od", "pPlayer;�ؿ���;", ""},
	{"GetRushDifficulty", LuaGetRushDifficulty, "�õ���ǰ��ս�Ĺؿ��Ѷ�", "o", "pPlayer;", ""},
	{"SetRushDifficulty", LuaSetRushDifficulty, "���õ�ǰ��ս�ؿ��Ѷ�", "od", "pPlayer;�ؿ��Ѷ�;", ""},
	{"SetStageStar", LuaSetStageStar, "������ս�Ǽ�", "odd", "pPlayer;�Ѷ�;�Ǽ�;", ""},
	{"GetStageStar", LuaGetStageStar, "�õ���ս�Ǽ�", "od", "pPlayer;�Ѷ�;", ""},
	{"GetLeftMopTime", LuaGetLeftMopTime, "�õ�ʣ��ɨ��ʱ��", "o", "pPlayer;", ""},
	{"StopMopStage", LuaStopMopStage, "���ֹͣɨ���ؿ�", "?d", "nPlayerId/pPlayer:��ɫId���߶���;�Ƿ���ɨ��һ��;", ""},
	{"FinishMop", LuaFinishMop, "ֱ�����ɨ��", "?", "nPlayerId/pPlayer:��ɫId���߶���;", ""},
	{"GetMopStage", LuaGetMopStage, "�õ���ǰ����ɨ���Ĺؿ��Ѷ�", "o", "pPlayer;", ""},
	{"GetMopState", LuaGetMopState, "�õ���ǰɨ��״̬", "o", "pPlayer;", ""},
	{"SetMopStage", LuaSetMopStage, "���õ�ǰ����ɨ���Ĺؿ��Ѷ�", "od", "pPlayer;�ؿ��Ѷ�;", ""},
	{"GetRushState", LuaGetRushState, "�õ���ǰ����״̬", "o", "pPlayer;", ""},
	{"SetRushState", LuaSetRushState, "", "od", "pPlayer;����;", ""},
	{"SpeedUpMop", LuaSpeedUpMop, "", "?", "pPlayer;", ""},
	{"GetSpeedUp", LuaGetSpeedUp, "", "?", "pPlayer;", ""},
#endif // #ifdef GAME_SERVER
};
