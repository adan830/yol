/* -------------------------------------------------------------------------
//	�ļ���		��	kunifyscript_table.hpp
//	������		��	JXLuaMapTableMaker
//	��������	��	���ļ���VS2005 Macro�Զ����ɣ��벻Ҫ�ֶ��޸ģ���
//	ʹ�÷���	��	����Ӧ��CPP�ļ�ĩ�ˣ�include���ļ�
//
// -----------------------------------------------------------------------*/

CONST SCRIPT_FUNCTION arFunction[]	=  
{
	{"IsNameWordPass", LuaIsNameWordPass, "��������еĵ����Ƿ����Ҫ��", "s", "����;", "1 or 0"},
	{"EnableLeakDectect", LuaEnableLeakDectect, "[Windows��Debug������Ч]����/�ر��ڴ�й¶��⣨���̣߳�", "d", "��0���������ر�;", ""},
	{"MathRandom", LuaMathRandom, "���һ�������", "[dd]", "����޲�������[0,1)�����һ����������[1,max];���������������[min,max];", "�����"},
};
