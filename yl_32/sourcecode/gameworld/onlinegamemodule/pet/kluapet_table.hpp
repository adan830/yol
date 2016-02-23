/* -------------------------------------------------------------------------
//	�ļ���		��	kluapet_table.hpp
//	������		��	LuaScriptTool
//	��������	��	���ļ���VisualStudio�����ɣ��벻Ҫ�ֶ��޸ģ���
//	ʹ�÷���	��	����Ӧ��CPP�ļ�ĩ�ˣ�include���ļ�
//
// -----------------------------------------------------------------------*/

DEFINE_LUA_CLASS_BEGIN(KLuaPet)
	REGISTER_LUA_STRING_READONLY(Name, "��������")
	REGISTER_LUA_DWORD_READONLY(Id, "����Id")
	REGISTER_LUA_DWORD_READONLY(RandSeed, "�����������")
	REGISTER_LUA_DWORD_READONLY(OwnerId, "��������Id")
	REGISTER_LUA_INTEGER_READONLY(Type, "��������")
	REGISTER_LUA_INTEGER_READONLY(Quality, "����Ʒ��")
	REGISTER_LUA_INTEGER_READONLY(Character, "�����Ը�")
	REGISTER_LUA_INTEGER_READONLY(Hungry, "���ﱥʳ��")
	REGISTER_LUA_INTEGER_READONLY(Level, "����ȼ�")
	REGISTER_LUA_INTEGER_READONLY(RankLevel, "����׼�")
	REGISTER_LUA_INTEGER_READONLY(State, "����״̬")
	REGISTER_LUA_FUNC(AddExp, "���Ӿ���", "d", "���Ӿ���ֵ;", "")
	REGISTER_LUA_FUNC(GetTotalExp, "�õ�������ܾ���", "", "", "")
	REGISTER_LUA_FUNC(GetBaseAttr, "�õ������������", "", "", "")
	REGISTER_LUA_FUNC(AddHungry, "���ӱ�ʳ��", "d", "��ʳ��;", "")

#ifdef GAME_SERVER
	REGISTER_LUA_FUNC(Regenerate, "��������һֻ����", "dddddu", "nType		;nQuality	;nCharacter;nLevel;nRankLevel;uRandSeed;", "�ɹ�����1")
	REGISTER_LUA_FUNC(Sync, "ͬ���������ݵ��ͻ���", "", "", "1�ɹ�")
	REGISTER_LUA_FUNC(UnlockEquipPos, "����װ������", "d", "װ����λ��;", "1�ɹ�")
	REGISTER_LUA_FUNC(GetSkillLevel, "�õ����ܵȼ�", "d", "����id;", "1�ɹ�")
	REGISTER_LUA_FUNC(GetBaseAttrScore, "�õ���������ս����", "", "", "")
	REGISTER_LUA_FUNC(SetFightScore, "���ó���ս����", "d", "nScore;", "")
	REGISTER_LUA_FUNC(DoRest, "���õ�ǰ��ս������Ϣ", "", "", "")
#endif // #ifdef GAME_SERVER
DEFINE_LUA_CLASS_END()
