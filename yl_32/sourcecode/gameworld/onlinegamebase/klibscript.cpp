
#include "stdafx.h"
#include "onlinegamebase/kscriptmanager.h"
#include "Misc/randomgen.h"
#include "Misc/Misc.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// -------------------------------------------------------------------------
namespace KLibScriptNameSpace
{

// ��ʽ�����ʱ�䣨���أ��ַ�����
// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: --
// @LuaApiName		: FormatTime2String
// @Description		: ���ݸ�����������ת�����ƶ���ʽ���ַ�������
// @ReturnCode		: str����ʽ�����ʱ���ʾ
// @ArgumentFlag	: sd
// @ArgumentComment	: szParam����ʽ
// @ArgumentComment	: tTime������
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT LuaFormatTime2String(QLuaScript& sc)
{
	LPCSTR szParam = sc.GetStr(1);
	time_t tTime = (time_t)sc.GetInt(2);
	tm* pStm = localtime(&tTime);

	CHAR str[256] = "";
	if (!strftime(str, sizeof(str), szParam, pStm))
		puts("invalid \'date\' format");

	sc.PushString(str);
	return 1;
}
// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: --
// @LuaApiName		: GetRootPath
// @Description		: 
// @ReturnCode		: ���ظ�Ŀ¼
// @ArgumentFlag	: 
// @ArgumentComment	: 
// @ArgumentComment	: 
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT LuaGetRootPath(QLuaScript& sc)
{
	CHAR lszCurrentDirectory[200];
	g_GetRootPath(lszCurrentDirectory);
	INT nLen = strlen(lszCurrentDirectory);
	if (lszCurrentDirectory[nLen - 1] == '\\' || lszCurrentDirectory[nLen - 1] == '/')
		lszCurrentDirectory[nLen - 1] = 0;
	sc.PushString(lszCurrentDirectory);
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: --
// @LuaApiName		: SplitStr
// @Description		: ��һ���ָ����з��ַ���
// @ReturnCode		: �зֵ����ַ������飬ʧ�ܷ���nil
// @ArgumentFlag	: ss
// @ArgumentComment	: Ҫ�зֵ��ַ���
// @ArgumentComment	: �зַ���ȡ������һ���ַ���
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT LuaSplitStr(QLuaScript& sc)
{
	INT nResult		= 0;
	LPCSTR pszSrc	= sc.GetStr(1);
	CHAR cSplit		= *sc.GetStr(2);	// �������е�ss�Ѿ����Ա�֤GetStr(1)��GetStr(2)��Ȼ�õ��ǿ�ָ�룬���ﲻ�ټ��
	INT nCount		= 0;

	LOG_PROCESS_ERROR(cSplit);

	sc.PushTable();
	nResult ++;

	for (LPCSTR pszSubStr = pszSrc; ; ++pszSubStr)
	{
		if (*pszSubStr && cSplit != *pszSubStr)
			continue;

		sc.PushLString(pszSrc, pszSubStr - pszSrc);
		sc.SetTableIndex(++nCount);

		if (!*pszSubStr)
			break;
		
		pszSrc = pszSubStr + 1;
	}

EXIT0:
	return nResult;
}


// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: --
// @LuaApiName		: Number2Int
// @Description		: ������ת����INT��ȡ����ͬʱתΪ�з������֣�
// @ReturnCode		: ����
// @ArgumentFlag	: d
// @ArgumentComment	: dNumber:Ҫȡ������
// @ArgumentComment	: 
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT LuaNumber2Int(QLuaScript& sc)
{
	sc.PushNumber(sc.GetInt(1));
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: --
// @LuaApiName		: Number2UInt
// @Description		: ������ת����UINT��ȡ����ͬʱתΪ�޷������֣�
// @ReturnCode		: ת�������
// @ArgumentFlag	: d
// @ArgumentComment	: dNumber:��ת������
// @ArgumentComment	: 
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT LuaNumber2UInt(QLuaScript& sc)
{
	sc.PushNumber((DWORD)sc.GetNum(1));
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: --
// @LuaApiName		: FileName2Id
// @Description		: ����ָ���ļ��Ĺ�ϣID
// @ReturnCode		: DWORD ��ϣID, ʧ�ܷ���nil
// @ArgumentFlag	: s
// @ArgumentComment	: pszFile���ļ���
// @ArgumentComment	: 
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT LuaFileName2Id(QLuaScript& sc)
{
	LPCSTR pszFile = (CHAR*)sc.GetStr(1);
	INT bRet = 0;
	PROCESS_ERROR(pszFile);
	sc.PushNumber(g_FileNameHash(pszFile));
	bRet = 1;
EXIT0:
	if (bRet == 0)
		sc.PushNull();
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: --
// @LuaApiName		: String2Id
// @Description		: ����ָ���ַ����Ĺ�ϣID
// @ReturnCode		: 
// @ArgumentFlag	: s
// @ArgumentComment	: str: �ַ���
// @ArgumentComment	: 
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT LuaString2Id(QLuaScript& sc)
{
	DWORD dwId		= 0;
	LPCSTR szName	= NULL;
	szName	= sc.GetStr(1);
	PROCESS_ERROR(szName && szName[0]);
	dwId	= g_StringHash((LPSTR)szName);
EXIT0:
	sc.PushNumber(dwId);
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: --
// @LuaApiName		: GetValByStr
// @Description		: �����ַ���ȡ��Table��Ա������֧�ֶ༶��.���͡�:����
// @ReturnCode		: value
// @ArgumentFlag	: s
// @ArgumentComment	: �ַ���
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT LuaGetValByStr(QLuaScript& sc)
{
	return sc.GetGlobalF(sc.GetStr(1));
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: --
// @LuaApiName		: SaveValue2Buffer
// @Description		: ��һ��ֵת���ɿ��Դ��桢���͵�Buffer
// @ReturnCode		: Buffer
// @ArgumentFlag	: {}
// @ArgumentComment	: 
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT LuaSaveValue2Buffer(QLuaScript& sc)
{
	CHAR szBuf[1024];
	INT nLen	= sc.SaveValue2Buffer((LPBYTE)szBuf, sizeof(szBuf), 1);
	if (nLen <= 0)
		return 0;

	sc.PushLString(szBuf, nLen);
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: --
// @LuaApiName		: LoadBuffer2Value
// @Description		: ��һ��Buffer����ֵ
// @ReturnCode		: value
// @ArgumentFlag	: s
// @ArgumentComment	: Buffer
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT LuaLoadBuffer2Value(QLuaScript& sc)
{
	INT nLen;
	LPCSTR pszBuf	= sc.GetLStr(1, nLen);
	if (!pszBuf)
		return 0;

	if (!sc.LoadBuffer2Value((LPCBYTE)pszBuf, nLen))
		return 0;

	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: --
// @LuaApiName		: GetBitTB
// @Description		: ��һ����ֵװ����һ����ʾÿ��������λ��Table
// @ReturnCode		: table
// @ArgumentFlag	: d
// @ArgumentComment	: Number
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT LuaGetBitTB(QLuaScript& sc)
{
	if (!sc.IsNumber(1))
		return 0;
	DWORD dwValue	= (DWORD)sc.GetInt(1);
	sc.PushTable();
	for (INT i = 0; i < 32; i++)
	{
		sc.PushNumber((dwValue >> i) & 1);
		sc.SetTableIndex(i);
	}

	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: --
// @LuaApiName		: LoadTabFile
// @Description		: ����table�ļ�
// @ReturnCode		: table����
// @ArgumentFlag	: s
// @ArgumentComment	: �ļ���
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT LuaLoadTabFile(QLuaScript& sc)
{
	LPCSTR pszFileName = sc.GetStr(1);
	CHECK_REPORT(pszFileName);

	{
		QTabFile tabFile;
		if (!tabFile.Load(pszFileName))
			return 0;

		INT nWidth	= tabFile.GetWidth();
		INT nHeight	= tabFile.GetHeight();
		CHAR szBuffer[10240];

		sc.PushTable();
		for (INT i = 1; i <= nHeight; i++)
		{
			sc.PushTable();
			for (INT j = 1; j <= nWidth; j++)
			{
				tabFile.GetString(i, j, "", szBuffer, sizeof(szBuffer));
				sc.PushString(szBuffer);
				sc.SetTableIndex(j);
			}
			sc.SetTableIndex(i);
		}

		return 1;
	}

EXIT0:
	return 0;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: --
// @LuaApiName		: LoadIniFile
// @Description		: ����ini�ļ�
// @ReturnCode		: ini����
// @ArgumentFlag	: s
// @ArgumentComment	: �ļ���
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT LuaLoadIniFile(QLuaScript& sc)
{
	LPCSTR pszFileName	= sc.GetStr(1);
	CHECK_REPORT(pszFileName);

	{
		QIniFile iniFile;
		if (!iniFile.Load(pszFileName))
			return 0;

		CHAR szSection[256];
		CHAR szKey[256];
		CHAR szValue[10240];

		sc.PushTable();
		szSection[0]	= '\0';
		while (iniFile.GetNextSection(szSection, szSection))
		{
			sc.PushTable();
			szKey[0]	= '\0';
			while (iniFile.GetNextKey(szSection, szKey, szKey))
			{
				iniFile.GetString(szSection, szKey, "", szValue, sizeof(szValue));
				sc.PushString(szValue);
				sc.SetTableField(szKey);
			}
			sc.SetTableField(szSection);
		}

		return 1;
	}

EXIT0:
	return 0;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: --
// @LuaApiName		: FindStr
// @Description		: ���ַ����������Ӵ�������������ȫ��˫�ֽں���
// @ReturnCode		: nil��ʾδ�ҵ������򷵻��ҵ����Ӵ���ʼλ�ã��±��1��ʼ������0��
// @ArgumentFlag	: ss[d]
// @ArgumentComment	: szStr: ԭ�ַ���
// @ArgumentComment	: szSub: Ҫ���ҵ��Ӵ�
// @ArgumentComment	: nStart: ������ʼλ�ã��±��1��ʼ������0��
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT LuaFindStr(QLuaScript& sc)
{
	INT nResult		= 0;

	INT nStrLen		= 0;
	LPCSTR pszStr	= sc.GetLStr(1, nStrLen);
	INT nSubLen		= 0;
	LPCSTR pszSub	= sc.GetLStr(2, nSubLen);
	INT nStart		= 0;

	LPCSTR pszFindEnd	= NULL;

	LOG_PROCESS_ERROR(nStrLen > 0);
	LOG_PROCESS_ERROR(nSubLen > 0);

	if (sc.GetTopIndex() >= 3)
	{
		nStart	= sc.GetInt(3) - 1;
		LOG_PROCESS_ERROR(nStart >= 0);
		LOG_PROCESS_ERROR(nStart <= nStrLen);
	}

	pszFindEnd	= pszStr + nStrLen - nSubLen;

	for (LPCSTR pszFind = pszStr + nStart; pszFind <= pszFindEnd; ++pszFind)
	{
		if (memcmp(pszFind, pszSub, nSubLen) == 0)
		{
			sc.PushNumber(pszFind - pszStr + 1);
			nResult	++;
			break;
		}

		// TODO: FanZai	δ���ж����Ե��ж�
		if (*pszFind < 0)	// ���ֶ��1
			pszFind	++;
	}

EXIT0:
	return nResult;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: --
// @LuaApiName		: GetScriptMemSize
// @Description		: �õ��ű��ѷ����ڴ��С
// @ReturnCode		: nSize
// @ArgumentFlag	: 
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT LuaGetScriptMemSize(QLuaScript& sc)
{
	sc.PushNumber(sc.GetMemSize());

	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: --
// @LuaApiName		: GetScriptAllocTimes
// @Description		: �õ��ű��ѷ����ڴ����
// @ReturnCode		: nTimes
// @ArgumentFlag	: 
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT LuaGetScriptAllocTimes(QLuaScript& sc)
{
	sc.PushNumber(sc.GetAllocTimes());

	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: --
// @LuaApiName		: GetScriptBlockMaxSize
// @Description		: �õ��ű��ѷ�����ڴ�������С
// @ReturnCode		: nSize
// @ArgumentFlag	: 
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT LuaGetScriptBlockMaxSize(QLuaScript& sc)
{
	sc.PushNumber(sc.GetBlockMaxSize());

	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: --
// @LuaApiName		: GetScriptAllocMemSize
// @Description		: �õ��ű�ȫ���ѷ�����ڴ���С
// @ReturnCode		: nSize
// @ArgumentFlag	: 
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT LuaGetScriptAllocMemSize(QLuaScript& sc)
{
	sc.PushNumber(sc.GetAllocMemSize());

	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: --
// @LuaApiName		: GetScriptFreeMemSize
// @Description		: �õ��ű�δʹ�õĻ����ڴ���С
// @ReturnCode		: nSize
// @ArgumentFlag	: 
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT LuaGetScriptFreeMemSize(QLuaScript& sc)
{
	sc.PushNumber(sc.GetFreeMemSize());

	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: --
// @LuaApiName		: ReleaseScriptFreeMemory
// @Description		: �ͷŽű����õĻ����ڴ�
// @ReturnCode		: 1���ɹ���0��ʧ��
// @ArgumentFlag	: 
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT LuaReleaseScriptFreeMemory(QLuaScript& sc)
{
	sc.PushNumber(sc.ReleaseAllFreeMemory());

	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: --
// @LuaApiName		: ClrScr
// @Description		: ��տ���̨��Ϣ
// @ReturnCode		: 
// @ArgumentFlag	: 
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT LuaClrScr(QLuaScript& sc)
{
#ifdef _DEBUG
#ifdef WIN32
	system("cls");
#else
	printf("\33[2J");			// δ���Թ�
#endif
#endif
	return 0;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: --
// @LuaApiName		: HashDword
// @Description		: ��ò�����Ӧ��32λHashֵ������������һ��ֵ��ȡ���൱�ڵõ�һ����α�����
// @ReturnCode		: 
// @ArgumentFlag	: d
// @ArgumentComment	: 32λ����(�������)
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT LuaHashDword(QLuaScript& sc)
{
	DWORD dwSeed = (DWORD)sc.GetInt(1);
	sc.PushNumber(g_HashWord(dwSeed));
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: --
// @LuaApiName		: GetMD5String
// @Description		: ��MD5����һ���ַ���
// @ReturnCode		: 
// @ArgumentFlag	: s
// @ArgumentComment	: һ��Ҫ���ܵ��ַ���
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT LuaGetMD5String(QLuaScript& sc)
{
	LPCSTR pszString = sc.GetStr(1);
	if (pszString == NULL)
		return 0;

	CHAR szMD5[64] = {0};

	Misc_MD5String(szMD5, (BYTE*)pszString, strlen(pszString));

	sc.PushString(szMD5);
	return 1;
}
//
//// -------------------------------------------------------------------------
//// @ClientSvr(C/S)	: 
//// @ClassName		: --
//// @LuaApiName		: Base64Encode
//// @Description		: base64����
//// @ReturnCode		: 
//// @ArgumentFlag	: s
//// @ArgumentComment	: һ��Ҫ������ַ���
//// @LuaMarkEnd
//// -------------------------------------------------------------------------
//INT LuaBase64Encode(QLuaScript& sc)
//{
//	LPCSTR pszString = sc.GetStr(1);
//	if (pszString == NULL)
//		return 0;
//	INT nLen = strlen(pszString);
//	LPCSTR pszBuffer = NULL;
//	INT nEstimateSize = 0;
//	INT nGetSize = 0;
//	EstimateEncodeBufferSize(nLen, &nEstimateSize);
//	pszBuffer = new CHAR[nEstimateSize + 1];
//	if (pszBuffer == NULL)
//		return 0;
//	Base64Encode(pszString, nLen, (char*)pszBuffer, nEstimateSize, &nGetSize, TRUE);
//	sc.PushLString(pszBuffer, nGetSize);
//	SAFE_DELETE_ARRAY(pszBuffer);
//	return 1;
//}
//
//// -------------------------------------------------------------------------
//// @ClientSvr(C/S)	: 
//// @ClassName		: --
//// @LuaApiName		: Base64Decode
//// @Description		: base64����
//// @ReturnCode		: 
//// @ArgumentFlag	: s
//// @ArgumentComment	: һ��Ҫ������ַ���
//// @LuaMarkEnd
//// -------------------------------------------------------------------------
//INT LuaBase64Decode(QLuaScript& sc)
//{
//	LPCSTR pszIn = sc.GetStr(1);
//	if (pszIn == NULL)
//		return 0;
//	INT nLen = strlen(pszIn);
//	LPCSTR pszOut = NULL;
//	INT nMaxSize = nLen + 1;
//	INT nGetSize = 0;
//	pszOut = new CHAR[nMaxSize];
//	if (pszOut == NULL)
//		return 0;
//	Base64Decode(pszIn, nLen, (char*)pszOut, nMaxSize, &nGetSize);
//	sc.PushLString(pszOut, nGetSize);
//	SAFE_DELETE_ARRAY(pszOut);
//	return 1;
//}

#include "klibscript_table.hpp"
}; // KLibScriptNameSpace

BOOL g_RegisterKLibScriptFun()
{
	return g_cScriptManager.RegisterTableFuncs("KLib", KLibScriptNameSpace::arFunction, countof(KLibScriptNameSpace::arFunction));
}
// -------------------------------------------------------------------------
