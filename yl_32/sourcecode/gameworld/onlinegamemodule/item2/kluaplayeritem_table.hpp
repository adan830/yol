/* -------------------------------------------------------------------------
//	�ļ���		��	kluaplayeritem_table.hpp
//	������		��	LuaScriptTool
//	��������	��	���ļ���VisualStudio�����ɣ��벻Ҫ�ֶ��޸ģ���
//	ʹ�÷���	��	����Ӧ��CPP�ļ�ĩ�ˣ�include���ļ�
//
// -----------------------------------------------------------------------*/

DEFINE_LUA_CLASS_BEGIN(KLuaPlayerItem)
	REGISTER_LUA_FUNC(GetItem, "��ý�ɫָ��λ�õĵ���", "ddd", "nRoom:�������ڿռ�;nX:������;nY:������;", "���ص��߶���ʧ�ܷ���nil")
	REGISTER_LUA_FUNC(GetItemCount, "��ȡָ���ռ�����Ʒ������", "d[?????]", "nRoom;nGenre;nDetail;nParticular;nBind;nTimeOut;", "�������������ռ䲻���ڷ���nil")
	REGISTER_LUA_FUNC(HaveItem, "��һ�����Ƿ�ӵ��ĳ�����ߣ���������ڿռ������", "o", "pItem:Ŀ����ߵĶ���;", "û�ҵ�����nil�����򷵻�һ��Table��{ nRoom = �������ڿռ�, nX = ������, nY = ������ }")
	REGISTER_LUA_FUNC(CountFreeBagCell, "��ȡ���б����п��и��ӵ���Ŀ", "", "", "���и�����")
	REGISTER_LUA_FUNC(CalcFreeItemCountInBags, "�������б����ռ��л��ɷ���ĳ����Ʒ������", "dddd", "nGenre;nDetail;nParticular;bBind;", "���ɷ�����Ʒ������")
	REGISTER_LUA_FUNC(FindItem, "��ָ���ռ������ָ�����͵ĵ���", "d[????]", "nRoom;nGenre/szClass;nDetail;nParticular;nLevel;", "�����ҵ��ĵ����б�nil��ʾʧ�ܣ���������ȷ������Table��ʾû�ҵ�")
	REGISTER_LUA_FUNC(FindItemInBags, "������������չ���������ָ����Ʒ", "ddd[?]", "nGenre/szClass;nDetail;nParticular;nLevel;", "�����ҵ��ĵ����б�nil��ʾʧ�ܣ���������ȷ������Table��ʾû�ҵ�")
	REGISTER_LUA_FUNC(FindItemId, "��ָ���ռ������ָ�����͵ĵ���", "d", "nItemId;", "����nRoom,nX,nY,ʧ�ܷ���nil")
	REGISTER_LUA_FUNC(FindClassItem, "��ָ���ռ������ָ��Class�ĵ���", "ds", "nRoom;szClass;", "�����ҵ��ĵ����б�nil��ʾʧ�ܣ���������ȷ������Table��ʾû�ҵ�")
	REGISTER_LUA_FUNC(CanAddItemIntoBag, "��鵱ǰ�����Ƿ��ܹ��ŵ���ָ���Ķ������Ὣ���ָ��ӵĵ������Ҳ�������ڣ�", "?", "�����б�ÿһ��ĸ�ʽ��{ nGenre, nDetail, nParticular, bBind, nCount [bTimeOut]}����������;", "1�ŵ���")
	REGISTER_LUA_FUNC(GetItemAbsTimeout, "��ȡ��Ʒ���Գ�ʱʱ��", "o", "��Ʒ����;", "���ؾ��Գ�ʱʱ���{�꣬�£��գ�ʱ����}����nil")
	REGISTER_LUA_FUNC(GetItemRelTimeout, "��ȡ��Ʒ��Գ�ʱʱ��", "o", "��Ʒ����;", "������Գ�ʱʱ���{�죬ʱ����}����nil")
	REGISTER_LUA_FUNC(GetJbCoin, "��ȡ�����", "", "", "")
	REGISTER_LUA_FUNC(GetMaxCarryMoney, "��ȡ���Я����������", "", "", "")
	REGISTER_LUA_FUNC(GetCashCoin, "��ȡ��ҽ�������Ʒ������", "", "", "")
	REGISTER_LUA_FUNC(GetBindMoney, "��ȡ��Ұ�����", "", "", "")
	REGISTER_LUA_FUNC(GetItemPos, "������֪���߶��󷵻������Լ����ϵ�λ��", "o", "pItem:Ҫ���ҵĵ��߶���;", "{ nRoom, nX, nY }��ʧ�ܷ���nil")
	REGISTER_LUA_FUNC(ThrowAway, "�ӵ����ϵ�ָ����Ʒ", "d[dd]", "nRoom:Ҫ�ӵ���Ʒ���ڿռ�;nX:Ҫ�ӵ���Ʒ����X;nY:Ҫ�ӵ���Ʒ����Y;", "1�ɹ�")
	REGISTER_LUA_FUNC(GetEquipByDetail, "����Dֵ��ý�ɫ����װ��", "d", "nDetail;", "���ص��߶���ʧ�ܷ���nil")

#ifdef GAME_SERVER
	REGISTER_LUA_FUNC(DropRateItem, "����ָ����DropRate�������", "s[do]", "szDropRateFile:�����������ļ�;nCount:����������Ĭ��Ϊ1;pNpc:����λ�����ĸ�npcΪ���ģ�Ĭ��Ϊ��ǰ���;", "��")
	REGISTER_LUA_FUNC(OpenRepository, "�򿪴�����", "o", "pNpc:�򿪴������NPC;", "1�ɹ�")
	REGISTER_LUA_FUNC(SetExtRepState, "������չ�����伤��״̬", "d", "nState;", "--")
	REGISTER_LUA_FUNC(ConsumeItemInBags, "���ļ���һ��������ָ�����͵���Ʒ������Ϊ��Ʒ������������Ʒ�����ڱ�����", "d[????]", "nCount:������Ŀ;nGenre;nDetail;nParticular;nLevel;", "�����������ѵ�����Ŀ - ʵ��������Ŀ")
	REGISTER_LUA_FUNC(SetItemTimeout, "������Ʒ��ʱʱ��", "??[d]", "��Ʒ���������Ʒ����;����ʱ�䣨�ַ���������'YYYY-MM-DD HH:MM:SS'�����߷�������������;BOOL:1��ʾ���ʱ�䣬0��ʾ����ʱ�䣬�ڶ�������Ϊ����ʱ��Ч��ȱʡΪ1;", "�ɹ�����1��ʧ�ܷ���0")
	REGISTER_LUA_FUNC(DelItemTimeout, "ȡ����Ʒ��ʱʱ��", "?", "��Ʒ���������Ʒ����;", "�ɹ�����1��ʧ�ܷ���0")
	REGISTER_LUA_FUNC(CostMoney, "�۳�������", "dd", "�۳�����Ŀ;�۳�;��;", "�۳��ɹ����")
	REGISTER_LUA_FUNC(CostBindMoney, "�۳�������", "d[d]", "nCostCount �۳�����Ŀ;nCostWay �۳���;��;", "�۳��ɹ����")
	REGISTER_LUA_FUNC(IsMyItem, "�ƶ���Ʒ���Ƿ������Լ���", "d", "nItemIndex����Ʒ����;", "0�����ǣ�1���ǵ�")
	REGISTER_LUA_FUNC(CalcFreeItemCellCount, "��ȡ��ǰ��ұ����п��ŵĸ�����", "", "", "�����п��ŵĸ�����")
	REGISTER_LUA_FUNC(ReApplyEquipRes, "", "", "", "")
	REGISTER_LUA_FUNC(ThrowAllItem, "�����������������Ʒ", "", "", "")
	REGISTER_LUA_FUNC(FindAllItem, "����ָ���ռ�������Ʒָ���ռ�������Ʒ", "d", "nRoom ָ���ռ�;", "{}")
	REGISTER_LUA_FUNC(ItemLog, "��Ʒ������־������Goddess��", "odd[sd]", "pItem: ��Ʒ;BOOL���Ƿ�����Ʒ;nType����Ϊ���ͣ���KE_PLAYERLOG_TYPE@klogtype.h;szComment��ע��;bForce���Ƿ�ǿ��д��־,ȱʡΪFALSE;", "")
	REGISTER_LUA_FUNC(AddBindCoin, "�԰󶨽�ҵĲ���", "d[d]", "nBindCoin;nWay;", "1���ɹ���0��ʧ��")
	REGISTER_LUA_FUNC(AutoEquip, "�Զ�װ������", "?", "nItemIndex/pItem;", "�ɹ�����1")
	REGISTER_LUA_FUNC(AutoUse, "�Զ�ʹ��", "?", "nItemIndex/pItem;", "�ɹ�����1")
#endif // #ifdef GAME_SERVER
DEFINE_LUA_CLASS_END()
