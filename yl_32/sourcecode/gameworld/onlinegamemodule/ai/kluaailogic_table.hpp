/* -------------------------------------------------------------------------
//	�ļ���		��	kluaailogic_table.hpp
//	������		��	LuaScriptTool
//	��������	��	���ļ���VisualStudio�����ɣ��벻Ҫ�ֶ��޸ģ���
//	ʹ�÷���	��	����Ӧ��CPP�ļ�ĩ�ˣ�include���ļ�
//
// -----------------------------------------------------------------------*/

DEFINE_LUA_CLASS_BEGIN(KAILogic)
	REGISTER_LUA_INTEGER_READONLY(AIType, "")
	REGISTER_LUA_FUNC(NewAction, "����һ���µ�Action", "dd", "nActionId;nActionKey;", "")
	REGISTER_LUA_FUNC(NewState, "����һ���µ�״̬���", "d", "nStateId ״̬���Id;", "")
	REGISTER_LUA_FUNC(SetInitState, "���ó�ʼ״̬���", "d", "nInitState ��ʼ��ʱ���״̬���ID;", "")
	REGISTER_LUA_FUNC(RegisterUserAction, "ע���Զ����Action", "ds", "nActionKey;pszFunction ��������;", "")
DEFINE_LUA_CLASS_END()
