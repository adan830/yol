/* -------------------------------------------------------------------------
//	�ļ���		��	kluatask_table.hpp
//	������		��	LuaScriptTool
//	��������	��	���ļ���VisualStudio�����ɣ��벻Ҫ�ֶ��޸ģ���
//	ʹ�÷���	��	����Ӧ��CPP�ļ�ĩ�ˣ�include���ļ�
//
// -----------------------------------------------------------------------*/

DEFINE_LUA_CLASS_BEGIN(KLuaTask)
	REGISTER_LUA_FUNC(GetTask, "��ȡ�������", "uu", "wGroupID:���������ID;wTaskID:����������ڵ���ID;", "�ɹ�-���ر���ֵ��ʧ��-����nil")
	REGISTER_LUA_FUNC(SetTask, "�����������", "uud[d]", "wGroupID:���������ID;wTaskID:����������ڵ���ID;nTaskValue:����ֵ;nSyncMode:ͬ��ģʽ(0:Auto, 1:Force, -1:No);", "�޷���ֵ")
	REGISTER_LUA_FUNC(DirectSetTask, "ֱ�������������", "uud[d]", "wGroupID:���������ID;wTaskID:����������ڵ���ID;nTaskValue:����ֵ;nSyncMode:ͬ��ģʽ(0:Auto, 1:Force, -1:No);", "�޷���ֵ")
	REGISTER_LUA_FUNC(GetTaskBit, "��һ�������������(65536��)��ֵ��λ����(0-65536*32)����λ�����TaskID(ÿ32λΪһ��ID)������ȡ��Ӧ����ֵ��λֵ", "uu", "wGroupID:���������ID;dwBit:ָ����λ(��Χ��0-65536*32);", "�ɹ�-����ָ��λ��ֵ��ʧ��-����nil")
	REGISTER_LUA_FUNC(SetTaskBit, "��һ�������������(65536��)��ֵ��λ����(0-65536*32)����λ�����TaskID(ÿ32λΪһ��ID)�������ö�Ӧ����ֵ��λֵ", "uud", "wGroupID:���������ID;dwBit:ָ����λ(��Χ��0-65536*32);bValue:λֵ(0 or 1);", "�޷���ֵ")
	REGISTER_LUA_FUNC(ClearTaskGroup, "���һ���������", "u[d]", "wGroupID:���������ID;bSync:�Ƿ�ͬ�����ͻ���(�������Ч)(0 or 1);", "�޷���ֵ")
	REGISTER_LUA_FUNC(GetAllTask, "��ȡȫ��Task����", "", "", "{[nTaskId]=nValue,[nTaskId]=nValue,...}")
	REGISTER_LUA_FUNC(SendAccept, "������/�ͻ��˷��ͽ�����������", "dd[d]", "nTaskId:������ID;nReferId:����������ID;bAccept:�Ƿ����;", "1���ɹ���nil��ʧ��")
	REGISTER_LUA_FUNC(SendAward, "������/�ͻ��˷�������������", "dd[d]", "nTaskId:������ID;nReferId:����������ID;nSelIdx:��ѡ�������;", "1���ɹ���nil��ʧ��")
	REGISTER_LUA_FUNC(GetTaskStr, "��ȡ�������(ÿ��ʹ��4���������,�16���ַ�����,��ɫ���ĳ���)", "uu", "wGroupID:���������ID;wTaskID:����������ڵ���ID,��Ҫ4����ID,��IDΪ���ID;", "�ɹ�-���ر���ֵ��ʧ��-����nil")
	REGISTER_LUA_FUNC(SetTaskStr, "�����������(ÿ��ʹ��8���������,�32���ַ�����)", "uus[d]", "wGroupID:���������ID;wTaskID:����������ڵ���ID,��Ҫ4����ID,��IDΪ���ID;szTaskValue:����ֵ(32���ַ�,16������,��ɫ������8������,Ԥ��8������Խ�ϰ�);;nSyncMode:ͬ��ģʽ(0:Auto, 1:Force, -1:No);", "�޷���ֵ")

#ifdef GAME_SERVER
	REGISTER_LUA_FUNC(SendRefresh, "��ͻ��˷���ˢ��Ҫ��", "dd[d]", "nTaskId:������ID;nReferId:����������ID;nTaskGroupID:�����񱣴��TaskGroup;", "1���ɹ���nil��ʧ��")
	REGISTER_LUA_FUNC(StartProgressTimer, "����һ����ʱ���������ÿͻ��˵Ľ�����", "ods", "pPlayer;���ʱ��;��������;", "��")
	REGISTER_LUA_FUNC(StepStart, "֪ͨ�ͻ���Ŀ�꿪ʼ", "ddd", "����Id;������Id;������;", "��")
	REGISTER_LUA_FUNC(SyncTaskGroup, "ͬ��һ���������", "u", "���������ID;", "�ɹ���1, ʧ�ܣ�0")
#endif // #ifdef GAME_SERVER
DEFINE_LUA_CLASS_END()
