/* -------------------------------------------------------------------------
//	�ļ���		��	klibscript_table.hpp
//	������		��	JXLuaMapTableMaker
//	��������	��	���ļ���VS2005 Macro�Զ����ɣ��벻Ҫ�ֶ��޸ģ���
//	ʹ�÷���	��	����Ӧ��CPP�ļ�ĩ�ˣ�include���ļ�
//
// -----------------------------------------------------------------------*/

CONST SCRIPT_FUNCTION arFunction[]	=  
{
	{"FormatTime2String", LuaFormatTime2String, "���ݸ�����������ת�����ƶ���ʽ���ַ�������", "sd", "szParam����ʽ;tTime������;", "str����ʽ�����ʱ���ʾ"},
	{"GetRootPath", LuaGetRootPath, "", "", "", "���ظ�Ŀ¼"},
	{"SplitStr", LuaSplitStr, "��һ���ָ����з��ַ���", "ss", "Ҫ�зֵ��ַ���;�зַ���ȡ������һ���ַ���;", "�зֵ����ַ������飬ʧ�ܷ���nil"},

	{"Number2Int", LuaNumber2Int, "������ת����INT��ȡ����ͬʱתΪ�з������֣�", "d", "dNumber:Ҫȡ������;", "����"},
	{"Number2UInt", LuaNumber2UInt, "������ת����UINT��ȡ����ͬʱתΪ�޷������֣�", "d", "dNumber:��ת������;", "ת�������"},
	{"FileName2Id", LuaFileName2Id, "����ָ���ļ��Ĺ�ϣID", "s", "pszFile���ļ���;", "DWORD ��ϣID, ʧ�ܷ���nil"},
	{"String2Id", LuaString2Id, "����ָ���ַ����Ĺ�ϣID", "s", "str: �ַ���;", ""},
	{"GetValByStr", LuaGetValByStr, "�����ַ���ȡ��Table��Ա������֧�ֶ༶��.���͡�:����", "s", "�ַ���;", "value"},
	{"SaveValue2Buffer", LuaSaveValue2Buffer, "��һ��ֵת���ɿ��Դ��桢���͵�Buffer", "{}", "", "Buffer"},
	{"LoadBuffer2Value", LuaLoadBuffer2Value, "��һ��Buffer����ֵ", "s", "Buffer;", "value"},
	{"GetBitTB", LuaGetBitTB, "��һ����ֵװ����һ����ʾÿ��������λ��Table", "d", "Number;", "table"},	
	{"LoadTabFile", LuaLoadTabFile, "����table�ļ�", "s", "�ļ���;", "table����"},
	{"LoadIniFile", LuaLoadIniFile, "����ini�ļ�", "s", "�ļ���;", "ini����"},
	{"FindStr", LuaFindStr, "���ַ����������Ӵ�������������ȫ��˫�ֽں���", "ss[d]", "szStr: ԭ�ַ���;szSub: Ҫ���ҵ��Ӵ�;nStart: ������ʼλ�ã��±��1��ʼ������0��;", "nil��ʾδ�ҵ������򷵻��ҵ����Ӵ���ʼλ�ã��±��1��ʼ������0��"},
	{"GetScriptMemSize", LuaGetScriptMemSize, "�õ��ű��ѷ����ڴ��С", "", "", "nSize"},
	{"GetScriptAllocTimes", LuaGetScriptAllocTimes, "�õ��ű��ѷ����ڴ����", "", "", "nTimes"},
	{"GetScriptBlockMaxSize", LuaGetScriptBlockMaxSize, "�õ��ű��ѷ�����ڴ�������С", "", "", "nSize"},
	{"GetScriptAllocMemSize", LuaGetScriptAllocMemSize, "�õ��ű�ȫ���ѷ�����ڴ���С", "", "", "nSize"},
	{"GetScriptFreeMemSize", LuaGetScriptFreeMemSize, "�õ��ű�δʹ�õĻ����ڴ���С", "", "", "nSize"},
	{"ReleaseScriptFreeMemory", LuaReleaseScriptFreeMemory, "�ͷŽű����õĻ����ڴ�", "", "", "1���ɹ���0��ʧ��"},
	{"ClrScr", LuaClrScr, "��տ���̨��Ϣ", "", "", ""},
	{"HashDword", LuaHashDword, "��ò�����Ӧ��32λHashֵ������������һ��ֵ��ȡ���൱�ڵõ�һ����α�����", "d", "32λ����(�������);", ""},
	{"GetMD5String", LuaGetMD5String, "��MD5����һ���ַ���", "s", "һ��Ҫ���ܵ��ַ���;", ""},
	//{"Base64Encode", LuaBase64Encode, "base64����", "s", "һ��Ҫ������ַ���;", ""},
	//{"Base64Decode", LuaBase64Decode, "base64����", "s", "һ��Ҫ������ַ���;", ""},
};
