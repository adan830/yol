/* -------------------------------------------------------------------------
//	�ļ���		��	kluaaiaction_table.hpp
//	������		��	LuaScriptTool
//	��������	��	���ļ���VisualStudio�����ɣ��벻Ҫ�ֶ��޸ģ���
//	ʹ�÷���	��	����Ӧ��CPP�ļ�ĩ�ˣ�include���ļ�
//
// -----------------------------------------------------------------------*/

DEFINE_LUA_CLASS_BEGIN(KAIAction)
	REGISTER_LUA_FUNC(SetParam, "���ò���", "", "", "")
	REGISTER_LUA_FUNC(GetParam, "��ȡ��������", "", "", "")
	REGISTER_LUA_FUNC(SetBranch, "����Action�ķ�֧", "d", "��֧��Id��;", "")
DEFINE_LUA_CLASS_END()
