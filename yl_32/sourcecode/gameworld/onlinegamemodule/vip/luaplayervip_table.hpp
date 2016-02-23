/* -------------------------------------------------------------------------
//	�ļ���		��	luaplayervip_table.hpp
//	������		��	LuaScriptTool
//	��������	��	���ļ���VisualStudio�����ɣ��벻Ҫ�ֶ��޸ģ���
//	ʹ�÷���	��	����Ӧ��CPP�ļ�ĩ�ˣ�include���ļ�
//
// -----------------------------------------------------------------------*/

DEFINE_LUA_CLASS_BEGIN(LuaPlayerVip)
	REGISTER_LUA_FUNC(RefreshBuyCount, "ˢ�¹������", "d", "id;", "")
	REGISTER_LUA_FUNC(DoBuyCount, "�������", "dd", "id;����;", "")
	REGISTER_LUA_FUNC(CanBuyCount, "�������", "dd", "id;����;", "")
	REGISTER_LUA_FUNC(IsOpen, "�Ƿ񿪷�", "ddd", "playerid;id;nMsg;", "")
	REGISTER_LUA_FUNC(GetRate, "�Ƿ񿪷�", "dd", "playerid;id;", "")
	REGISTER_LUA_FUNC(SetFreeState, "����vip����״̬", "[d]", "nFreeTime;", "")
	REGISTER_LUA_FUNC(GetNowBuyCount, "��õ�ǰʹ������", "[d]", "nFreeTime;", "")
	REGISTER_LUA_FUNC(AddVipExpAndMoney, "����vip����", "d", "id;", "")
DEFINE_LUA_CLASS_END()
