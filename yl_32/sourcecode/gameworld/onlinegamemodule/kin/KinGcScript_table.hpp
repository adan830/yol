/* -------------------------------------------------------------------------
//	�ļ���		��	KinGcScript_table.hpp
//	������		��	LuaScriptTool
//	��������	��	���ļ���VisualStudio�����ɣ��벻Ҫ�ֶ��޸ģ���
//	ʹ�÷���	��	����Ӧ��CPP�ļ�ĩ�ˣ�include���ļ�
//
// -----------------------------------------------------------------------*/

CONST SCRIPT_FUNCTION arFunction[]	=  
{
	{"CreateKin", LuaCreateKin, "��������", "dsd", "dwPlayerId���峤;szTongName�ַ�������������;nTemplateIndexΪ����ģ������;", "�����ɹ���1������ʧ�ܣ�0"},
	{"GetKinTotalContributionOneDay", LuaGetKinTotalContributionOneDay, "��������", "", "", "����һ������Ĺ��׶�"},
	{"GetPlayerKinInfo", LuaGetPlayerKinInfo, "�õ���ҵļ�����Ϣ", "d", "���id", ""},
	{"UpdateAllPlayerKinLevelInfo", LuaUpdateAllPlayerKinLevelInfo, "���¼���ȼ���Ϣ", "dd", "����id;����ȼ�", ""},
};
