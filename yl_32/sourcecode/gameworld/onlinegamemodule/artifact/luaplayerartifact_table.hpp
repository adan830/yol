/* -------------------------------------------------------------------------
//	�ļ���		��	luaplayerartifact_table.hpp
//	������		��	LuaScriptTool
//	��������	��	���ļ���VisualStudio�����ɣ��벻Ҫ�ֶ��޸ģ���
//	ʹ�÷���	��	����Ӧ��CPP�ļ�ĩ�ˣ�include���ļ�
//
// -----------------------------------------------------------------------*/

DEFINE_LUA_CLASS_BEGIN(LuaPlayerArtifact)
	REGISTER_LUA_FUNC(AddPiece, "����Ƭ", "dd", "id;����;", "")
	REGISTER_LUA_FUNC(UsePiece, "����Ƭ", "dd", "id;����;", "")
	REGISTER_LUA_FUNC(GetArtifactNumByLevel, "��ȡĳһ�ȼ�������������", "d", "�ȼ�;", "")
DEFINE_LUA_CLASS_END()
