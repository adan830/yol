/* -------------------------------------------------------------------------
//	�ļ���		��	kactivityscript_table.hpp
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
	{"SyncActivityTime", LuaSyncActivityTime, "ͬ���ʱ��", "odddd", "pPlayer;nActivityIdx;nBaseActivityIdx;dwOpenTime;dwCloseTime;", ""},
	{"SetLastEnterZBTTime", LuaSetLastEnterZBTTime, "�õ��ϴν���ս���õ�ʱ��", "od", "pPlayer;time;", ""},
	{"GetLastEnterZBTTime", LuaGetLastEnterZBTTime, "�õ��ϴν���ս���õ�ʱ��", "o", "pPlayer;", ""},
	{"GetLastMPJJRank", LuaGetLastMPJJRank, "�������ɾ�������", "o", "pPlayer;", ""},
	{"SetLastMPJJRank", LuaSetLastMPJJRank, "����������ɾ�������", "od", "pPlayer;rank;", ""},
	{"GetKinBattleWinTimes", LuaGetKinBattleWinTimes, "�õ�����������ʤ����", "o", "pPlayer;", ""},
	{"SetKinBattleWinTimes", LuaSetKinBattleWinTimes, "��������������ʤ����", "od", "pPlayer;times;", ""},
	{"AddKinBattleRecord", LuaAddKinBattleRecord, "����һ��������ʼ�¼", "d", "dwRoleId;", ""},
	{"SetKinBattleWinnerId", LuaSetKinBattleWinnerId, "�����������id", "d", "dwWinnerId;", ""},
	{"SetLastWinKinInfo", LuaSetLastWinKinInfo, "�������һ��Ӯ���������Լ�����Ϣ", "d", "dwWinnerId;", ""},
	{"SetKinBattleWinNpcId", LuaSetKinBattleWinNpcId, "��������������������ʵ�npcid", "d", "dwNpcId;", ""},
	{"SyncKinBattleJoinNum", LuaSyncKinBattleJoinNum, "���͵�ǰ�������Բ�������", "ddd", "dwRoleId;nJoinNum;nHasJoined;", ""},
	{"ReloadKinBattleInfo", LuaReloadKinBattleInfo, "���¼�������������Ϣ", "", "", ""},
	{"GetKinBattleWinnerId", LuaGetKinBattleWinnerId, "�õ������������id", "", "", ""},
#endif // #ifdef GAME_SERVER
};
