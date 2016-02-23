/* -------------------------------------------------------------------------
//	�ļ���		��	luacharacterskill_table.hpp
//	������		��	LuaScriptTool
//	��������	��	���ļ���VisualStudio�����ɣ��벻Ҫ�ֶ��޸ģ���
//	ʹ�÷���	��	����Ӧ��CPP�ļ�ĩ�ˣ�include���ļ�
//
// -----------------------------------------------------------------------*/

DEFINE_LUA_CLASS_BEGIN(LuaCharacterSkill)
	REGISTER_LUA_FUNC(CastSkill, "�ͷż���", "dd[ddd]", "����ID;������ID;��������Ŀ���X;��������Ŀ���Y;��������Ŀ���Z;", "")
	REGISTER_LUA_FUNC(GetResistSkillLevel, "��ȡָ�����Լ��ܵȼ�", "d", "���Լ�������;", "")
	REGISTER_LUA_FUNC(CanCastSkill, "�Ƿ����ͷż���", "ddddd", "����ID;������ID;��������Ŀ���X;��������Ŀ���Y;��������Ŀ���Z;", "")
	REGISTER_LUA_FUNC(GetSkillCoefficient, "���ܵ�Ӌ����Ϣ(�Ƿ������������Lֵ)", "d", "����ID;", "")
	REGISTER_LUA_FUNC(GetSkillFightInfo, "���ܵ�Ӌ����Ϣ(�Ƿ������������Lֵ)", "d", "����ID;", "")
	REGISTER_LUA_FUNC(GetSkillCate, "��ǰBuff�������ܵ�Cate��Ϣ", "d", "����ID;", "")
	REGISTER_LUA_FUNC(GetSkillAttackType, "���ܵĹ�������(NeedTarget, IsImmediately)", "d", "����ID;", "")
	REGISTER_LUA_FUNC(ReduceSkillCost, "�޸ļ��ܵ�����", "dddd", "����nCateType;����nCateId;��ֵ���ǰٷֱ�;�޸�ֵ;", "")
	REGISTER_LUA_FUNC(ResetSkillCost, "���ü��ܵ�����", "dd", "����nCateType;����nCateId;", "")
	REGISTER_LUA_FUNC(ResetSkillMagnification, "�޸ļ��ܵĹ�����ϵ��", "ddd", "����nCateType;����nCateId;�޸�ֵ;", "")
	REGISTER_LUA_FUNC(CancelChannelSkill, "��ϵ�ǰ���ڶ����ļ���", "", "", "")
	REGISTER_LUA_FUNC(ResetSkillChannelTime, "�޸ļ��ܵ�ʩ��ʱ��", "ddd", "����nCateType;����nCateId;�޸�ֵ;", "")
	REGISTER_LUA_FUNC(AddSkillCriticalPercent, "�޸ļ��ܵı�����", "ddd", "����nCateType;����nCateId;�޸�ֵ;", "")
	REGISTER_LUA_FUNC(ClearSkillCD, "�޸ļ���CD", "dd", "����nCateType;����nCateId;", "")
	REGISTER_LUA_FUNC(ResetSkillChannelType, "�޸ļ�����������", "ddd", "����nCateType;����nCateId;���ü����ͷŵ�����(0��1��2��-1:���Ĭ��);", "")
	REGISTER_LUA_FUNC(AddBuffToSkill, "�޸ļ�����������", "ddd", "����nCateType;����nCateId;Buff ID(+:��Buff��-:��Buff);", "")
	REGISTER_LUA_FUNC(CheckObstacle, "�ж�Ŀ���Ŀ����ϰ�", "dddddd", "��ʼ��X;��ʼ��Y;��ʼ��Z;������X;������Y;������Z;", "")
DEFINE_LUA_CLASS_END()
