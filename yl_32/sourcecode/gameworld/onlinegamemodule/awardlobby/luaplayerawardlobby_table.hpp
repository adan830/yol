/* -------------------------------------------------------------------------
//	�ļ���		��	luaplayerawardlobby_table.hpp
//	������		��	LuaScriptTool
//	��������	��	���ļ���VisualStudio�����ɣ��벻Ҫ�ֶ��޸ģ���
//	ʹ�÷���	��	����Ӧ��CPP�ļ�ĩ�ˣ�include���ļ�
//
// -----------------------------------------------------------------------*/

DEFINE_LUA_CLASS_BEGIN(LuaPlayerAwardLobby)
	REGISTER_LUA_FUNC(DoFinishActivity, "��ɻ", "dd", "id;awardid;", "")
	REGISTER_LUA_FUNC(DoSignIn, "��ɻ", "d", "��������;", "")
	REGISTER_LUA_FUNC(DoGetBankIncomeTest, "��ɻ", "ds", "id;����;", "")
	REGISTER_LUA_FUNC(DoFinishRankActivity, "��ɳ��", "dd", "id;awardid;", "")
DEFINE_LUA_CLASS_END()
