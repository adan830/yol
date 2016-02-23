/* -------------------------------------------------------------------------
//	�ļ���		��	fightskillscript_table.hpp
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
	{"GetYlEnery", LuaGetYlEnery, "�����������", "d", "nSkillId;", ""},
	{"GetMeidicineSkillNumber", LuaGetMeidicineSkillNumber, "���ҩ�＼�������ֵ", "dd", "nMedicineType;nSkillLevel;", ""},
	{"GetPassiveSkillNumber", LuaGetPassiveSkillNumber, "��ñ������������ֵ", "dd", "nPassiveType;nSkillLevel;", ""},
	{"GetResistSkillNumber", LuaGetResistSkillNumber, "��ÿ��弼�������ֵ", "dd", "nPassiveType;nSkillLevel;", ""},
	{"GetSkillSlot", LuaGetSkillSlot, "��ü��ܲ�λ��Ϣ", "d", "nSkillId;", ""},
	{"GetSkillRoute", LuaGetSkillRoute, "��ü���·��", "d", "nSkillId;", ""},
	{"GetReqLevel", LuaGetReqLevel, "��ü�������ȼ�", "d", "nSkillId;", ""},
#endif // #ifdef GAME_SERVER
};
