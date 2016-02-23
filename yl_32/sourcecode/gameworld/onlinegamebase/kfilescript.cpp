
#include "stdafx.h"
#include "onlinegamebase/kscriptmanager.h"
#include "Misc/xml_i.h"
#include <map>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define FILELIB_DATA_MAXLEN	1024

// ����ҳ����	TODO: Ӧ����Ϊ�������ļ�����Ҫͳһ������һ��CORE��LIB��UI���ɷ��ʵĵط�
#define KD_N_CODE_PAGE		936		// 936 ANSI/OEM - Simplified Chinese (PRC, Singapore) 
#define KD_STR_CODE_PAGE	"gbk"	// for linux (iconv)

namespace KFileScriptNameSpace{

template < class T >
class _KFileLib
{
private:
	struct KPrivateData
	{
		T*			pFile;
		std::string strFileName;
		DWORD		cRef;

	};

	typedef std::map<std::string, KPrivateData> MAPFILESET;
	MAPFILESET m_mpFileSet; //<key, Data>
public:
	_KFileLib()
	{
	}
	~_KFileLib()
	{
		UnLoadAll();
	}

public:	
	BOOL	Load(LPSTR strFileName, LPSTR szKeyName);
	T*		GetFileHandle(LPSTR szKeyName);
	BOOL	UnLoad(LPSTR szKeyName);
	BOOL	UnLoadAll();
	BOOL	UnLoadDirectly(LPSTR szKeyName);
};

template <class T>
BOOL _KFileLib<T>::Load(LPSTR szFileName, LPSTR szKeyName)
{
	if (NULL == szFileName || 0 == szFileName[0] ||
		NULL == szKeyName || 0 == szKeyName[0])
		return FALSE;

	typename MAPFILESET::iterator it = m_mpFileSet.find(szKeyName);
	if (it != m_mpFileSet.end())
	{
		// ��ͬKey�Ѵ���, �ٿ��ļ����Ƿ���ͬ
		if (it->second.strFileName == szFileName)
		{
			it->second.cRef ++;
			return TRUE;
		}

		return FALSE;
	}

	T* pFile = new T;
	BOOL bOk = pFile->Load(szFileName);
	if (!bOk)
	{
		SAFE_DELETE(pFile);
		return FALSE;
	}

	KPrivateData data;
	data.pFile = pFile;
	data.strFileName = szFileName;
	data.cRef = 1;

	m_mpFileSet[szKeyName] = data;

	return TRUE;
}



template <class T>
T* _KFileLib<T>::GetFileHandle(LPSTR szKeyName)
{
	if (NULL == szKeyName || 0 == szKeyName[0])
		return NULL;

	typename MAPFILESET::iterator it = m_mpFileSet.find(szKeyName);
	if (it != m_mpFileSet.end())
	{
		return it->second.pFile;
	}

	return NULL;
}

template <class T>
BOOL _KFileLib<T>::UnLoad(LPSTR szKeyName)
{
	typename MAPFILESET::iterator it = m_mpFileSet.find(szKeyName);
	if (it != m_mpFileSet.end())
	{
		it->second.cRef --;
		if (0 == it->second.cRef)
		{
			delete (it->second.pFile);
			it->second.pFile = NULL;
			m_mpFileSet.erase(it);
		}

		return TRUE;
	}

	return FALSE;
}


template <class T>
BOOL _KFileLib<T>::UnLoadDirectly(LPSTR szKeyName)
{
	typename MAPFILESET::iterator it = m_mpFileSet.find(szKeyName);
	if (it != m_mpFileSet.end())
	{
		it->second.cRef = 0;
		delete (it->second.pFile);
		it->second.pFile = NULL;
		m_mpFileSet.erase(it);
		return TRUE;
	}

	return FALSE;
}

// ���ܼ�����ȫ��ֱ�����
template <class T>
BOOL _KFileLib<T>::UnLoadAll()
{
	for (typename MAPFILESET::iterator it = m_mpFileSet.begin(); it != m_mpFileSet.end(); ++it)
	{
		if (it->second.pFile)
		{
			delete (it->second.pFile);
			it->second.pFile = NULL;
		}
	}

	m_mpFileSet.clear();

	return TRUE;
}

_KFileLib< QTabFile > _g_TabFileLib;
_KFileLib< QTabFileCtrl > _g_TabFileCtrlLib;
_KFileLib< QIniFile > _g_IniFileLib;


// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: --
// @LuaApiName		: TabFile_Load
// @Description		: 
// @ReturnCode		: 
// @ArgumentFlag	: ss[d]
// @ArgumentComment	: filename
// @ArgumentComment	: szKey
// @ArgumentComment	: bWritable�Ƿ��д
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT LuaTabFile_Load(QLuaScript& cScript)
{
	INT nParamCount = cScript.GetTopIndex();
	if (nParamCount < 2)
		return 0;

	LPSTR szFileName = (LPSTR)cScript.GetStr(1);
	LPSTR szKey = (LPSTR)cScript.GetStr(2);
	bool bWritable = FALSE;
	BOOL bOk = FALSE;

	if (nParamCount >= 3)
	{
		bWritable = (bool)cScript.GetStr(3);
	}

	if (!bWritable)
	{
		bOk = _g_TabFileLib.Load(szFileName, szKey);
	}
	else
	{
		bOk = _g_TabFileCtrlLib.Load(szFileName, szKey);
	}

	cScript.PushNumber(bOk);
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: --
// @LuaApiName		: TabFile_UnLoad
// @Description		: 
// @ReturnCode		: 
// @ArgumentFlag	: s
// @ArgumentComment	: szKey
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT LuaTabFile_UnLoad(QLuaScript& cScript)
{
	if (cScript.GetTopIndex() < 1) 
		return 0;	

	LPSTR szKey = (LPSTR)cScript.GetStr(1);
	BOOL bOk = FALSE;

	QTabFile* pTabFile = _g_TabFileLib.GetFileHandle(szKey);
	if (pTabFile)
	{
		bOk = _g_TabFileLib.UnLoad(szKey);
	}
	else
	{
		QTabFileCtrl* pTabFileCtrl = _g_TabFileCtrlLib.GetFileHandle(szKey);
		if (pTabFileCtrl)
		{
			bOk = _g_TabFileCtrlLib.UnLoad(szKey);
		}
	}

	cScript.PushNumber(bOk);
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: --
// @LuaApiName		: TabFile_GetRowCount
// @Description		: ��ȡָ��Table�ļ��ĸ߶ȣ�������ͷ��
// @ReturnCode		: INT �ļ��ĸ߶�
// @ArgumentFlag	: s
// @ArgumentComment	: szKey
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT LuaTabFile_GetRowCount(QLuaScript& cScript)
{
	if (cScript.GetTopIndex() < 1)
	{		
		cScript.PushNumber(0);
		return 1;
	}

	INT nHeight = 0;
	LPSTR szKey = (LPSTR)cScript.GetStr(1);

	QTabFile* pTabFile = _g_TabFileLib.GetFileHandle(szKey);
	if (pTabFile)
	{
		nHeight = pTabFile->GetHeight();
	}
	else
	{
		QTabFileCtrl* pTabFileCtrl = _g_TabFileCtrlLib.GetFileHandle(szKey);
		if (pTabFileCtrl)
		{
			nHeight = pTabFileCtrl->GetHeight();
		}
	}

	cScript.PushNumber(nHeight);
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: --
// @LuaApiName		: TabFile_GetCell
// @Description		: ��ȡָ��Table�ļ�ָ��λ�õ�ֵ���С��ж��Ǵ�1��ʼ��
// @ReturnCode		: string ���� ��"" ��ʾ��ȡʧ�� ��
// @ArgumentFlag	: sd?[s]
// @ArgumentComment	: strFileKey
// @ArgumentComment	: nRow
// @ArgumentComment	: nColumn / strColumnName
// @ArgumentComment	: strDefaultValue
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT LuaTabFile_GetCell(QLuaScript& cScript)
{
	INT nParamCount = cScript.GetTopIndex();
	if (nParamCount < 3)
	{
		cScript.PushString("");
		return 1;
	}

	CHAR strValue[FILELIB_DATA_MAXLEN] = "";

	INT nRow = cScript.GetInt(2);
	LPCSTR strDefaultValue = "";

	if( nParamCount >= 4 )
	{
		strDefaultValue = cScript.GetStr(4);
	}

	LPSTR szKey = (LPSTR)cScript.GetStr(1);

	QTabFile* pTabFile = _g_TabFileLib.GetFileHandle(szKey);
	if(pTabFile)
	{
		if(cScript.IsNumber(3))
		{
			INT nColumn = cScript.GetInt(3);
			pTabFile->GetString(nRow, nColumn, strDefaultValue, strValue, sizeof( strValue));
		}
		else
		{
			LPSTR strColumn = (LPSTR)cScript.GetStr(3);
			pTabFile->GetString(nRow, strColumn, strDefaultValue, strValue, sizeof( strValue));
		}
	}
	else
	{
		QTabFileCtrl* pTabFileCtrl = _g_TabFileCtrlLib.GetFileHandle(szKey);
		if (pTabFileCtrl)
		{
			if(cScript.IsNumber(3))
			{
				INT nColumn = cScript.GetInt(3);
				pTabFileCtrl->GetString(nRow, nColumn, strDefaultValue, strValue, sizeof( strValue));
			}
			else
			{
				LPSTR strColumn = (LPSTR)cScript.GetStr(3);
				pTabFileCtrl->GetString(nRow, strColumn, strDefaultValue, strValue, sizeof( strValue));
			}
		}
	}

	cScript.PushString(strValue);
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: --
// @LuaApiName		: TabFile_SetCell
// @Description		: ����ָ��Table�ļ�ָ��λ�õ�ֵ���С��ж��Ǵ�1��ʼ��
// @ReturnCode		: ���ý��	1���ɹ�		0��ʧ��
// @ArgumentFlag	: sd?s
// @ArgumentComment	: strFileKey
// @ArgumentComment	: nRow
// @ArgumentComment	: nColumn / strColumnName
// @ArgumentComment	: strValue
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT LuaTabFile_SetCell(QLuaScript& cScript)
{
	INT nParamCount = cScript.GetTopIndex();
	if (nParamCount < 4)
	{
		cScript.PushNumber(0);
		return 1;
	}

	QTabFileCtrl* pTabFileCtrl = _g_TabFileCtrlLib.GetFileHandle((LPSTR)cScript.GetStr(1));
	if(!pTabFileCtrl)
	{
		cScript.PushNumber(0);
		return 1;
	}

	INT nRow = cScript.GetInt(2);
	LPCSTR strValue = cScript.GetStr(4);
	if(!strValue)
	{
		cScript.PushNumber(0);
		return 1;
	}	

	if(cScript.IsNumber(3))
	{
		INT nColumn = cScript.GetInt(3);
		pTabFileCtrl->WriteString(nRow, nColumn, (CHAR*)strValue, strlen(strValue));
	}
	else
	{
		LPSTR strColumn = (LPSTR)cScript.GetStr(3);
		pTabFileCtrl->WriteString(nRow, strColumn, (CHAR*)strValue, strlen(strValue));
	}

	cScript.PushNumber(1);
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: --
// @LuaApiName		: TabFile_Search
// @Description		: ����ĳһ�е�ָ��ֵ
// @ReturnCode		: ָ��ֵ������������-1ʧ��
// @ArgumentFlag	: s?s[d]
// @ArgumentComment	: strFileKey
// @ArgumentComment	: nColumn / strColumnName
// @ArgumentComment	: strSearchWord
// @ArgumentComment	: [nStartRow = 2]
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT LuaTabFile_Search(QLuaScript& cScript)
{
	INT nParamCount = cScript.GetTopIndex();
	INT nResultRow = -1;

	LPSTR strSearchWord = (LPSTR)cScript.GetStr(3);
	INT nStartRow = 2;

	if (nParamCount >= 4)
	{
		nStartRow = cScript.GetInt(4);
	}

	LPSTR szKey = (LPSTR)cScript.GetStr(1);

	QTabFile* pTabFile = _g_TabFileLib.GetFileHandle(szKey);
	if (pTabFile)
	{
		if (cScript.IsNumber(2))
		{
			INT nColumn = cScript.GetInt(2);
			nResultRow = pTabFile->SearchStringInColumn(strSearchWord, nColumn, nStartRow);
		}
		else
		{
			LPSTR strColumn = (LPSTR)cScript.GetStr(2);
			nResultRow = pTabFile->SearchStringInColumn(strSearchWord, strColumn, nStartRow);
		}
	}
	else
	{
		QTabFileCtrl* pTabFileCtrl = _g_TabFileCtrlLib.GetFileHandle(szKey);
		if (pTabFileCtrl)
		{
			if (cScript.IsNumber(2))
			{
				INT nColumn = cScript.GetInt(2);
				nResultRow = pTabFileCtrl->SearchStringInColumn(strSearchWord, nColumn, nStartRow);
			}
			else
			{
				LPSTR strColumn = (LPSTR)cScript.GetStr(2);
				nResultRow = pTabFileCtrl->SearchStringInColumn(strSearchWord, strColumn, nStartRow);
			}
		}
	}

	cScript.PushNumber(nResultRow);
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: --
// @LuaApiName		: TabFile_SaveFile
// @Description		: ����Table�ļ�
// @ReturnCode		: ������	1���ɹ�		0��ʧ��
// @ArgumentFlag	: s
// @ArgumentComment	: strFileKey
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT LuaTabFile_SaveFile(QLuaScript& cScript)
{
	INT nParamCount = cScript.GetTopIndex();
	if (nParamCount < 1)
	{
		cScript.PushNumber(0);
		return 1;
	}

	QTabFileCtrl* pTabFileCtrl = _g_TabFileCtrlLib.GetFileHandle((LPSTR)cScript.GetStr(1));
	if(!pTabFileCtrl)
	{
		cScript.PushNumber(0);
		return 1;
	}

	cScript.PushNumber(pTabFileCtrl->Save());
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: --
// @LuaApiName		: IniFile_Load
// @Description		: 
// @ReturnCode		: 0 or 1
// @ArgumentFlag	: ss
// @ArgumentComment	: szFileName
// @ArgumentComment	: szKey
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT LuaIniFile_Load(QLuaScript& cScript)
{
	LPSTR szFileName = (LPSTR)cScript.GetStr(1);
	LPSTR szKey = (LPSTR)cScript.GetStr(2);
	BOOL bOk = _g_IniFileLib.Load(szFileName, szKey);

	cScript.PushNumber(bOk);
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: --
// @LuaApiName		: IniFile_UnLoad
// @Description		: 
// @ReturnCode		: 
// @ArgumentFlag	: s
// @ArgumentComment	: szKey
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT LuaIniFile_UnLoad(QLuaScript& cScript)
{
	LPSTR szKey = (LPSTR)cScript.GetStr(1);
	BOOL bOk = _g_IniFileLib.UnLoad(szKey);

	cScript.PushNumber(bOk);
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: --
// @LuaApiName		: IniFile_GetData
// @Description		: ��ȡָ��Ini�ļ�ָ��Section��Key��ֵ
// @ReturnCode		: string ���� ��"" ��ʾ��ȡʧ�ܣ�
// @ArgumentFlag	: sss
// @ArgumentComment	: szFileKey
// @ArgumentComment	: szSection
// @ArgumentComment	: szKey
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT LuaIniFile_GetData(QLuaScript& cScript)
{
	LPSTR strKeyName = (CHAR*)cScript.GetStr(1);
	LPSTR strSection = (CHAR*)cScript.GetStr(2);
	LPSTR strKey = (CHAR*)cScript.GetStr(3);
	CHAR strValue[FILELIB_DATA_MAXLEN];

	QIniFile * pFile = _g_IniFileLib.GetFileHandle((LPSTR)cScript.GetStr(1));
	if (NULL == pFile)
	{		
		cScript.PushString("");
		return 1;
	}	

	pFile->GetString(strSection, strKey, "", (CHAR *)&strValue, sizeof(strValue));

	cScript.PushString(strValue);
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: --
// @LuaApiName		: IniFile_SetData
// @Description		: ����ֵ
// @ReturnCode		: 
// @ArgumentFlag	: ssss
// @ArgumentComment	: szFileKey
// @ArgumentComment	: szSection
// @ArgumentComment	: szKey
// @ArgumentComment	: szValue
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT LuaIniFile_SetData(QLuaScript& cScript)
{
	LPSTR strKeyName = (CHAR*)cScript.GetStr(1);
	LPSTR strSection = (CHAR*)cScript.GetStr(2);
	LPSTR strKey = (CHAR*)cScript.GetStr(3);
	LPSTR strValue = (CHAR*)cScript.GetStr(4);
	if (!strKeyName || !strSection || !strKey || !strValue)
		return 0;

	QIniFile * pFile = _g_IniFileLib.GetFileHandle((LPSTR)cScript.GetStr(1));
	if (NULL == pFile)
	{		
		return 0;
	}	

	if (strValue)
		pFile->WriteString(strSection, strKey, strValue);

	return 0;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: --
// @LuaApiName		: IniFile_EraseSection
// @Description		: ɾ��Section
// @ReturnCode		: 
// @ArgumentFlag	: ss
// @ArgumentComment	: szFileKey
// @ArgumentComment	: szSection
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT LuaIniFile_EraseSection(QLuaScript& cScript)
{
	LPSTR pszKeyName = (CHAR*)cScript.GetStr(1);
	LPSTR pszSection = (CHAR*)cScript.GetStr(2);
	if (pszKeyName == NULL || pszSection == NULL)
		return 0;
	QIniFile * pFile = _g_IniFileLib.GetFileHandle(pszKeyName);
	if (NULL == pFile)
		return 0;

	pFile->EraseSection(pszSection);
	return 0;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: --
// @LuaApiName		: IniFile_EraseKey
// @Description		: ɾ��Section�µ�Key
// @ReturnCode		: 
// @ArgumentFlag	: sss
// @ArgumentComment	: szFileKey
// @ArgumentComment	: szSection
// @ArgumentComment	: szKey
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT LuaIniFile_EraseKey(QLuaScript& cScript)
{
	LPSTR pszKeyName = (CHAR*)cScript.GetStr(1);
	LPSTR pszSection = (CHAR*)cScript.GetStr(2);
	LPCSTR pszKey = (CHAR*)cScript.GetStr(3);
	if (pszKeyName == NULL || pszSection == NULL || pszKey == NULL)
		return 0;
	QIniFile * pFile = _g_IniFileLib.GetFileHandle(pszKeyName);
	if (NULL == pFile)
		return 0;

	pFile->EraseKey(pszSection, pszKey);
	return 0;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: --
// @LuaApiName		: File_CreateFile
// @Description		: 
// @ReturnCode		: 
// @ArgumentFlag	: s
// @ArgumentComment	: szFileName
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT LuaFile_CreateFile(QLuaScript& cScript)
{
	LPCSTR pFileName = cScript.GetStr(1);
	if (!pFileName || !pFileName[0])
	{
		cScript.PushNumber(0);
		return 1;
	}

	QFile File;
	if (File.Open((LPSTR)pFileName))
	{
		cScript.PushNumber(0);
		return 1;
	}

	INT nFileLen = strlen(pFileName);
	CHAR szFileDir[MAX_PATH];
	strcpy(szFileDir, pFileName);
	for (INT i = 0; i < nFileLen; i ++)
	{
		if (pFileName[nFileLen - i - 1] == '\\')
		{
			szFileDir[nFileLen - i - 1] = 0;
			g_CreatePath(szFileDir);
			break;
		}
	}

	cScript.PushNumber(File.Create((LPSTR)pFileName));
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: --
// @LuaApiName		: IniFile_SaveFile
// @Description		: 
// @ReturnCode		: 0 or 1
// @ArgumentFlag	: ss
// @ArgumentComment	: strSrcKeyName
// @ArgumentComment	: strDesFileName
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT LuaIniFile_SaveFile(QLuaScript& cScript)
{
	LPSTR strSrcKeyName = (CHAR*)cScript.GetStr(1);
	LPSTR strDesFileName = (CHAR*)cScript.GetStr(2);

	if (!strSrcKeyName || !strDesFileName)
	{
		cScript.PushNumber(0);
		return 1;
	}

	QIniFile * pFile = _g_IniFileLib.GetFileHandle((LPSTR)cScript.GetStr(1));
	if (NULL == pFile)
	{
		cScript.PushNumber(0);
		return 1;
	}	

	BOOL bResult = pFile->Save(strDesFileName);
	_g_IniFileLib.UnLoadDirectly(strSrcKeyName);
	_g_IniFileLib.Load(strDesFileName, strSrcKeyName);

	cScript.PushNumber(bResult);
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: --
// @LuaApiName		: LoadXmlFile
// @Description		: ����Xml�ļ�
// @ReturnCode		: tbXmlData
// @ArgumentFlag	: s
// @ArgumentComment	: szFileName
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT LuaLoadXmlFile(QLuaScript& sc)
{
	INT nResult	= 0;
	LPCSTR pszFileName	= sc.GetStr(1);
	IXmlDocument* pIXmlDoc	= gCreateXmlDocument();//KD_N_CODE_PAGE, KD_STR_CODE_PAGE);

	LOG_PROCESS_ERROR(pIXmlDoc);

	PROCESS_ERROR(pIXmlDoc->Load(pszFileName));

	LOG_PROCESS_ERROR(pIXmlDoc->Push2Script(sc));

	nResult	= 1;

EXIT0:
	SAFE_RELEASE(pIXmlDoc);
	return nResult;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: --
// @LuaApiName		: WriteFile
// @Description		: д���ļ�����һ���ǵ����ı��ļ���
// @ReturnCode		: 1����ʾ�ɹ�
// @ArgumentFlag	: ss
// @ArgumentComment	: szFilePath: Txt�ļ�·�� 
// @ArgumentComment	: szContent: �ļ����ݣ������Ƿ��ı����ַ����������԰��������ַ�'\0'�ȣ�
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT LuaWriteFile(QLuaScript& sc)
{
	LPCSTR pszFilePath	= sc.GetStr(1);
	INT nContentLen		= 0;
	LPCSTR pszContent	= sc.GetLStr(2, nContentLen);
	QFile cFile;
	INT nResult			= 0;
	INT nFileLen		= 0;
	CHAR szFileDir[MAX_PATH];

	PROCESS_ERROR(pszFilePath && pszFilePath[0]);

	strcpy(szFileDir, pszFilePath);
	
	nFileLen = strlen(pszFilePath);
	for (INT i = 1; i < nFileLen; i ++)
	{
		if (pszFilePath[i] == '\\')
		{
			szFileDir[i] = 0;
			g_CreatePath(szFileDir);
			szFileDir[i] = '\\';
		}
	}

	LOG_PROCESS_ERROR(cFile.Create(pszFilePath));
	cFile.Write((LPVOID)pszContent, nContentLen);
	cFile.Close();

	sc.PushNumber(1);
	nResult ++;

EXIT0:
	return nResult;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: --
// @LuaApiName		: AppendFile
// @Description		: ׷��д���ļ�����һ���ǵ����ı��ļ���
// @ReturnCode		: 1����ʾ�ɹ�
// @ArgumentFlag	: ss
// @ArgumentComment	: szFilePath: Txt�ļ�·�� 
// @ArgumentComment	: szContent: �ļ����ݣ������Ƿ��ı����ַ����������԰��������ַ�'\0'�ȣ�
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT LuaAppendFile(QLuaScript& sc)
{
	LPCSTR pszFilePath	= sc.GetStr(1);
	INT nContentLen		= 0;
	LPCSTR pszContent	= sc.GetLStr(2, nContentLen);

	QFile cFile;
	INT nResult	= 0;

	LOG_PROCESS_ERROR(cFile.Append(pszFilePath));
	cFile.Seek(0, SEEK_END);
	cFile.Write((LPVOID)pszContent, nContentLen);
	cFile.Close();

	sc.PushNumber(1);
	nResult ++;

EXIT0:
	return nResult;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: --
// @LuaApiName		: ReadTxtFile
// @Description		: ��ȡTxt�ļ�
// @ReturnCode		: 
// @ArgumentFlag	: s
// @ArgumentComment	: pszTxtFilePath: Txt�ļ�·�� 
// @ArgumentComment	: 
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT LuaReadTxtFile(QLuaScript& sc)
{
	LPCSTR pszTxtFilePath = sc.GetStr(1);
	QFile cFile;
	INT nResult = 0;

	if (cFile.Open(pszTxtFilePath))
	{
		LPCSTR pszBuffer = (LPCSTR)cFile.GetBuffer();
		if (pszBuffer)
			nResult += sc.PushLString(pszBuffer, cFile.Size());
		cFile.Close();
	}

	return nResult;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: --
// @LuaApiName		: IsFileExist
// @Description		: �ļ��Ƿ����
// @ReturnCode		: 1���ڣ�0������
// @ArgumentFlag	: s
// @ArgumentComment	: �ļ�·�� 
// @ArgumentComment	: 
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT LuaIsFileExist(QLuaScript& sc)
{
	LPCSTR pszTxtFilePath = sc.GetStr(1);
	BOOL bResult = g_IsFileExist(pszTxtFilePath);

	sc.PushNumber(bResult);
	return 1;
}

#include "kfilescript_table.hpp"
} // KFileScriptNameSpace

BOOL g_RegisterKFileScriptFun()
{
	return g_cScriptManager.RegisterTableFuncs("QFile", KFileScriptNameSpace::arFunction, countof(KFileScriptNameSpace::arFunction));
}
