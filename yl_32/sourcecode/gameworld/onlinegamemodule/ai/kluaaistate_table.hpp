/* -------------------------------------------------------------------------
//	�ļ���		��	kluaaistate_table.hpp
//	������		��	LuaScriptTool
//	��������	��	���ļ���VisualStudio�����ɣ��벻Ҫ�ֶ��޸ģ���
//	ʹ�÷���	��	����Ӧ��CPP�ļ�ĩ�ˣ�include���ļ�
//
// -----------------------------------------------------------------------*/

DEFINE_LUA_CLASS_BEGIN(KAIState)
	REGISTER_LUA_FUNC(HandleEvent, "�¼���Ӧ", "dd", "�¼�ID;ActionID;", "")
DEFINE_LUA_CLASS_END()
