/* -------------------------------------------------------------------------
//	�ļ���		��	kscenescript_table.hpp
//	������		��	LuaScriptTool
//	��������	��	���ļ���VisualStudio�����ɣ��벻Ҫ�ֶ��޸ģ���
//	ʹ�÷���	��	����Ӧ��CPP�ļ�ĩ�ˣ�include���ļ�
//
// -----------------------------------------------------------------------*/

CONST SCRIPT_FUNCTION arFunction[]	=  
{
	{"GetNameById", LuaGetNameById, "ͨ������Id(ģ��)�������", "d", "����Id;", ""},
	{"GetMapOwnerId", LuaGetMapOwnerId, "ͨ������nSceneId��ó���OwnerId", "d", "����Id;", ""},
	{"GetMapCopyIndex", LuaGetMapCopyIndex, "ͨ������nSceneId��ó���CopyIndex", "d", "����Id;", ""},
	{"Dump", LuaDump, "�������������Ϣ�����Ե�ϵͳ��Ϣ����ָ�����", "[ou]", "pLuaPlayer �����ҷ���sysmsg;dwSceneId ֻ����˳�����Ϣ;", ""},
	{"GetPlayerNum", LuaGetPlayerNum, "��ȡ�������������", "d[d]", "dwSceneId ����ID;nCopyIndex �������;", ""},
	{"ResetMap", LuaResetMap, "���ó���", "dd", "nMapID;nSceneId;", ""},
	{"DeleteAllNpc", LuaDeleteAllNpc, "ɾ����������npc", "dd", "nMapID;nSceneId;", ""},
	{"GetNameByTemplateId", LuaGetNameByTemplateId, "ͨ��������TemplateId�������", "d", "����TemplateId;", ""},
	{"GetFilePathByTemplateId", LuaGetFilePathByTemplateId, "ͨ��������TemplateId��ó����ļ��Ĵ��·��", "d", "����TemplateId;", ""},

#ifdef GAME_SERVER
	{"UnloadScene", LuaUnloadScene, "ж�ص�ͼ(С�ģ����Ǳ�Ҫ����ʹ��,�ᵼ�����е�����˳���������������Ϸ����)", "d", "dwSceneId;", ""},
	{"UnloadBattleScene", LuaUnloadBattleScene, "ж��ս����ͼ", "d", "dwSceneId;", ""},
	{"LoadScene", LuaLoadScene, "�����ͼ debug��", "dd[d]", "nSceneId;nMapOwnerId;nUserParam1 �û�������������ɷ���;", "����0������ʧ�ܣ�����1������ɹ�"},
	{"GetSceneType", LuaGetSceneType, "�õ���ͼType", "d", "nMapId;", ""},
	{"GetSceneTypeName", LuaGetSceneTypeName, "�õ���ͼSceneTypeName", "d", "nMapId;", ""},
	{"GetSceneFightState", LuaGetSceneFightState, "�ж�һ����ͼ�Ƿ��ǿ�ս����ͼ", "d", "nMapId;", ""},
	{"GetSceneSetFightMode", LuaGetSceneSetFightMode, "�ж�һ����ͼ�Ƿ��ǿ�ս����ͼ", "d", "nMapId;", ""},
	{"IsDynamicScene", LuaIsDynamicScene, "�ж�һ�������Ƿ��Ƕ�̬����", "d", "nSceneId;", "1 �Ƕ�̬���� 0 ����"},
	{"GetBattleSceneIdByTemplateId", LuaGetBattleSceneIdByTemplateId, "ͨ��������TemplateId��øó���Ĭ��ʹ�õ�ս������Id", "d", "����TemplateId;", ""},
	{"IsDynamicSceneLoad", LuaIsDynamicSceneLoad, "ͨ��ģ��id��ѯ��̬�����Ƿ��Ѽ��ع�", "d", "����TemplateId;", "�����"},
	{"GetDynamicSceneIdByTemplateId", LuaGetDynamicSceneIdByTemplateId, "ͨ��ģ��id�õ���ͨ��̬������id", "d", "����TemplateId;", ""},
#endif // #ifdef GAME_SERVER
};
