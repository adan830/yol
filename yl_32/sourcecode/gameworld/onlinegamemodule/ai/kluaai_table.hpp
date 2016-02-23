/* -------------------------------------------------------------------------
//	�ļ���		��	kluaai_table.hpp
//	������		��	LuaScriptTool
//	��������	��	���ļ���VisualStudio�����ɣ��벻Ҫ�ֶ��޸ģ���
//	ʹ�÷���	��	����Ӧ��CPP�ļ�ĩ�ˣ�include���ļ�
//
// -----------------------------------------------------------------------*/

DEFINE_LUA_CLASS_BEGIN(KLuaAI)
	REGISTER_LUA_FUNC(SetAIType, "����Npc��AI", "d", "nAIType AI����;", "")
	REGISTER_LUA_FUNC(GetAIType, "��ȡAI����", "", "", "nAIType AI����")
	REGISTER_LUA_FUNC(FireAIEvent, "����AI�¼�", "ddd", "nEventID �¼�����;dwEventSrc �����¼���ID;dwEventParam;", "")
	REGISTER_LUA_FUNC(GetAIOriginPos, "��ȡNpc��¼��ԭ��", "dddd", "posX;posY;posZ;faceDirection;", "")
	REGISTER_LUA_FUNC(SetAIOriginPos, "��¼Npcԭ��", "dddd", "posX;posY;posZ;faceDirection;", "")
	REGISTER_LUA_FUNC(GetAISelectSkill, "��ȡ�ͷż���Id", "", "", "dwSkillID,dwSkillLevel")
	REGISTER_LUA_FUNC(GetAIEventSrcId, "��ȡ�¼�������ID", "", "", "nEventSrcId")
	REGISTER_LUA_FUNC(EnableDebug, "����AI���������Ϣ", "d", "nEnable 1 ���� 0 �ر�;", "")
	REGISTER_LUA_FUNC(SetPatrolPath, "����Ѳ��·��", "dd[d]", "nPatrolPath;nNextPointIndex;nOrderIndex;", "")
	REGISTER_LUA_FUNC(SetBattleZone, "����Npcս�������뿪����ᴥ��AI�¼�", "ddddd", "x;y;z;radius;height;", "")
DEFINE_LUA_CLASS_END()
