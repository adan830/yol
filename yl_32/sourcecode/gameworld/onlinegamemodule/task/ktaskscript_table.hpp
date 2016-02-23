/* -------------------------------------------------------------------------
//	�ļ���		��	ktaskscript_table.hpp
//	������		��	LuaScriptTool
//	��������	��	���ļ���VisualStudio�����ɣ��벻Ҫ�ֶ��޸ģ���
//	ʹ�÷���	��	����Ӧ��CPP�ļ�ĩ�ˣ�include���ļ�
//
// -----------------------------------------------------------------------*/

CONST SCRIPT_FUNCTION arFunction[]	=  
{
	{"SendAccept", LuaSendAccept, "������/�ͻ��˷��ͽ�����������", "odd[d]", "pPlayer;nTaskId:������ID;nReferId:����������ID;bAccept:�Ƿ����;", "1���ɹ���nil��ʧ��"},
	{"Dump", LuaDump, "������������Ϣ", "o", "pPlayer;", ""},
	{"SendAward", LuaSendAward, "������/�ͻ��˷�������������", "odd[d]", "pPlayer;nTaskId:������ID;nReferId:����������ID;nSelIdx:��ѡ�������;", "1���ɹ���nil��ʧ��"},

#ifdef GAME_SERVER
	{"SendRefresh", LuaSendRefresh, "��ͻ��˷���ˢ��Ҫ��", "odd[d]", "pPlayer;nTaskId:������ID;nReferId:����������ID;nTaskGroupID:�����񱣴��TaskGroup;", "1���ɹ���nil��ʧ��"},
	{"StartProgressTimer", LuaStartProgressTimer, "����һ����ʱ���������ÿͻ��˵Ľ�����", "ods", "pPlayer;���ʱ��;��������;", "��"},
	{"StepStart", LuaStepStart, "֪ͨ�ͻ���Ŀ�꿪ʼ", "oddd", "��Ҷ���;����Id;������Id;������;", "��"},
	{"SetBlackSky", LuaSetBlackSky, "֪ͨ�ͻ��˿������������ģʽ", "od", "pPlayer;�Ƿ�������ģʽ;", "��"},
#endif // #ifdef GAME_SERVER
};
