
#include "CorePrivate.h"
#include "File.h"
#ifdef WIN32
	#include <direct.h>
	#include <mbstring.h>
#else
	#include <unistd.h>
	#include <sys/stat.h>
#endif

#ifdef __GNUC__
void strlwr(char* str)
{
	char c;
	for (int i = 0; 0 != (c = str[i]); i++)
	{
		if (c >= 'A' && c <= 'Z')
			str[i] = c + ('a' - 'A');
	}
}

#endif //#ifdef __GNUC__
//---------------------------------------------------------------------------
#ifdef WIN32
	static char s_szRootPath[MAX_PATH] = "C:";		// ����·��
	static char s_szCurrPath[MAX_PATH] = "\\";		// ��ǰ·��
	#define		PATH_SPLITTER		'\\'
	#define		PATH_SPLITTER_STR	"\\"
#else
	static char s_szRootPath[MAX_PATH] = "/";		// ����·��
	static char s_szCurrPath[MAX_PATH] = "/";		// ��ǰ·��
	#define		PATH_SPLITTER		'/'
	#define		PATH_SPLITTER_STR	"/"
#endif

int RemoveTwoPointPath(char* szPath, int nLength)
{
	int nRemove = 0;
	assert(szPath);

#ifdef WIN32
	const char* lpszOld = "\\..\\";
#else
	const char* lpszOld = "/../";
#endif

	char* lpszTarget = strstr(szPath, lpszOld);

	if (lpszTarget)
	{
		const char* lpszAfter = lpszTarget + 3;
		while(lpszTarget > szPath)
		{
			lpszTarget--;
			if ((*lpszTarget) == '\\' ||(*lpszTarget) == '/')
				break;
		}
		memmove(lpszTarget, lpszAfter, (nLength - (lpszAfter - szPath) + 1) * sizeof(char));
		nRemove = (int)(lpszAfter - lpszTarget);
		return RemoveTwoPointPath(szPath, nLength - nRemove);
	}

	return nLength - nRemove;
}

int RemoveOnePointPath(char* szPath, int nLength)
{
	int nRemove = 0;
	assert(szPath);
#ifdef WIN32
	const char* lpszOld = "\\.\\";
#else
	const char* lpszOld = "/./";
#endif
	char* lpszTarget = strstr(szPath, lpszOld);
	if (lpszTarget)
	{
		char* lpszAfter = lpszTarget + 2;
		memmove(lpszTarget, lpszAfter, (nLength - (lpszAfter - szPath) + 1) * sizeof(char));
		nRemove = (int)(lpszAfter - lpszTarget);
		return RemoveOnePointPath(szPath, nLength - nRemove);
	}

	return nLength - nRemove;
}

int RemoveAllPointPath(char* szPath, int nLength)
{
	return RemoveOnePointPath(szPath, RemoveTwoPointPath(szPath, nLength));
}

//---------------------------------------------------------------------------
// ����:	���ó���ĸ�·��
// ����:	lpPathName	������argv[0]
//---------------------------------------------------------------------------
void g_SetRootPath(const char* lpPathName)
{
	char excutePath[MAX_PATH];
	g_ExtractFilePath(excutePath, lpPathName);
	if (excutePath[0] != '\0')
	{
		int ret =chdir(excutePath);
		assert(ret == 0);
	}
	char* ret = getcwd(s_szRootPath, MAX_PATH);
	assert(ret != NULL);
}

//---------------------------------------------------------------------------
// ����:	GetRootPath
// ����:	ȡ�ó���ĸ�·��
// ����:	lpPathName	·����
//---------------------------------------------------------------------------
void g_GetRootPath(char* lpPathName)
{
	strcpy(lpPathName, s_szRootPath);
}

//---------------------------------------------------------------------------
// ����:	SetFilePath
// ����:	���õ�ǰ�ļ�·��
// ����:	lpPathName	·����
// ����:	void
//---------------------------------------------------------------------------
void g_SetFilePath(const char* lpPathName)
{
	// ȥ��ǰ��� "\\"
	if (lpPathName[0] == '\\' ||lpPathName[0] == '/')
	{
		strcpy(s_szCurrPath, lpPathName + 1);
	}
	else
	{
		strcpy(s_szCurrPath, lpPathName);
	}

	// ĩβ���� "\\"
	int len = (int)strlen(s_szCurrPath);
	if (len > 0 && s_szCurrPath[len - 1] != '\\' && s_szCurrPath[len - 1] != '/')
	{
		s_szCurrPath[len] = PATH_SPLITTER;
		s_szCurrPath[len + 1] = 0;
	}
	RemoveAllPointPath(s_szCurrPath, len + 1);
#ifndef WIN32
	//'\\' -> '/' [wxb 2003-7-29]
	for (len = 0; s_szCurrPath[len]; len++)
	{
		if (s_szCurrPath[len] == '\\')
			s_szCurrPath[len] = '/';
	}
#endif
}

//---------------------------------------------------------------------------
// ����:	GetFilePath
// ����:	ȡ�õ�ǰ�ļ�·��
// ����:	lpPathName	·����
// ����:	void
//---------------------------------------------------------------------------
void g_GetFilePath(char* lpPathName)
{
	strcpy(lpPathName, s_szCurrPath);
}

//---------------------------------------------------------------------------
// ����:	GetFullPath
// ����:	ȡ���ļ���ȫ·����
// ����:	lpPathName	·����
//			lpFileName	�ļ���
// ����:	void
//---------------------------------------------------------------------------
void g_GetFullPath(char* lpPathName, const char* lpFileName)
{
#ifdef WIN32
	if (lpFileName[1] == ':' ||	// �ļ�����ȫ·��
		(lpFileName[0] == '\\' && lpFileName[1] == '\\'))// ������'\\'���־�����·��
	{
		strcpy(lpPathName, lpFileName);
		return;
	}
#endif

	// �ļ����в���·��
	if (lpFileName[0] == '\\' || lpFileName[0] == '/')
	{
		strcpy(lpPathName, s_szRootPath);
		strcat(lpPathName, lpFileName);
		return;
	}

	// ��ǰ·��Ϊȫ·��
#ifdef WIN32
	if (s_szCurrPath[1] == ':')
	{
		strcpy(lpPathName, s_szCurrPath);
		strcat(lpPathName, lpFileName);
		return;
	}
#endif
	// ��ǰ·��Ϊ����·��
	strcpy(lpPathName, s_szRootPath);
	if(s_szCurrPath[0] != '\\' && s_szCurrPath[0] != '/')
	{
		strcat(lpPathName, PATH_SPLITTER_STR);
	}
	strcat(lpPathName, s_szCurrPath);

	if (lpFileName[0] == '.' && (lpFileName[1] == '\\'||lpFileName[1] == '/') )
		strcat(lpPathName, lpFileName + 2);
	else
		strcat(lpPathName, lpFileName);
}

//---------------------------------------------------------------------------
// ����:	GetHalfPath
// ����:	ȡ���ļ��İ�·������������·��
// ����:	lpPathName	·����
//			lpFileName	�ļ���
// ����:	void
//---------------------------------------------------------------------------
void g_GetHalfPath(char* lpPathName, const char* lpFileName)
{
	// �ļ����в���·��
	if (lpFileName[0] == '\\' || lpFileName[0] == '/')
	{
		strcpy(lpPathName, lpFileName);
	}
	else
	{
		strcpy(lpPathName, PATH_SPLITTER_STR);
		strcat(lpPathName, s_szCurrPath);
		strcat(lpPathName, lpFileName);
	}
}

//---------------------------------------------------------------------------
// ����:	GetPackPath
// ����:	ȡ���ļ���ѹ�����е�·����
// ����:	lpPathName	·����
//			lpFileName	�ļ���
// ����:	void
//---------------------------------------------------------------------------
void g_GetPackPath(char* lpPathName, const char* lpFileName)
{
	// �ļ����в���·��
	if (lpFileName[0] == '\\' || lpFileName[0] == '/')
	{
		strcpy(lpPathName, lpFileName + 1);
	}
	else
	{
		strcpy(lpPathName, s_szCurrPath);
		strcat(lpPathName, lpFileName);
	}
	int len = (int)strlen(lpPathName);
	RemoveAllPointPath(lpPathName, len + 1);
	// ȫ��ת��ΪСд��ĸ
	strlwr(lpPathName);
}

//---------------------------------------------------------------------------
// ����:	GetDiskPath
// ����:	ȡ��CDROM��Ӧ���ļ�·����
// ����:	lpPathName	·����
//			lpFileName	�ļ���
// ����:	void
//---------------------------------------------------------------------------
/*CORE_API void g_GetDiskPath(char* lpPathName, char* lpFileName)
{
	strcpy(lpPathName, "C:");
	for (int i = 0; i < 24; lpPathName[0]++, i++)
	{
//		if (GetDriveType(lpPathName) == DRIVE_CDROM)
//			break;
	}
	if (lpFileName[0] == '\\' || lpPathName[0] == '/')
	{
		strcat(lpPathName, lpFileName);
	}
	else
	{
#ifdef WIN32
		strcat(lpPathName, "\\");
#else
		strcat(lpPathName, "/");
#endif
		strcat(lpPathName, s_szCurrPath);
		strcat(lpPathName, lpFileName);
	}
}
*/

//---------------------------------------------------------------------------
// ����:	CreatePath
// ����:	����Ϸ��Ŀ¼�½���һ��·��
// ����:	lpPathName	·����
//---------------------------------------------------------------------------
int	g_CreatePath(const char* lpPathName)
{
	if (!lpPathName || !lpPathName[0])
		return false;

	char szFullPath[MAX_PATH] = "";
	g_GetFullPath(szFullPath, lpPathName);
#ifdef unix
	{
		char *ptr = szFullPath;
		while(*ptr)
		{
			if (*ptr == '\\')
				*ptr = '/';
			ptr++;
		}
	}
#endif	// #ifdef unix

	int nResult = true;
	#ifdef WIN32
		CreateDirectoryA(szFullPath, NULL);
		DWORD dwAtt = GetFileAttributesA(szFullPath);
		nResult = ((dwAtt != 0xFFFFFFFF)  && (dwAtt & FILE_ATTRIBUTE_DIRECTORY));
	#else
		mkdir(szFullPath, 0777);
	#endif

	return nResult;
}

//---------------------------------------------------------------------------
// ����:	g_UnitePathAndName
// ����:	һ��·����һ���ļ������ϲ���lpGet���γ�һ��������·���ļ���
// ����:	pcszPath ����·���� pcszFile �����ļ��� pszFullName ��õ����������ļ���
// ����:	void
// ע�⣺   ����û�п����ַ����ĳ��ȣ�ʹ�õ�ʱ��Ҫ��֤�ַ����ĳ����㹻
//---------------------------------------------------------------------------
void	g_UnitePathAndName(const char *pcszPath, const char *pcszFile, char *pszRetFullName)
{
    if (pszRetFullName)
        pszRetFullName[0] = '\0';

	if (
        (!pcszPath) || 
        (!pcszFile) || 
        (!pszRetFullName)
    )
		return;

	strcpy(pszRetFullName, pcszPath);
	int	nSize = (int)strlen(pszRetFullName);
    if (nSize > 0)
    {
	    if (pszRetFullName[nSize - 1] != '\\')
	    {
		    pszRetFullName[nSize] = '\\';
            nSize++;
		    pszRetFullName[nSize] = '\0';
	    }
    }

	if (pcszFile[0] != '\\')
	{
		strcat(pszRetFullName + nSize, pcszFile);
	}
	else
	{
		strcat(pszRetFullName + nSize, &pcszFile[1]);
	}
}

//---------------------------------------------------------------------------
// ����:	find if file exists in pak or in hard disk
// ����:	����ָ�����ļ��Ƿ����
// ����:	lpPathName	·�������ļ���
// ����:	TRUE���ɹ���false��ʧ�ܡ�
//---------------------------------------------------------------------------
int g_IsFileExist(const char* FileName)
{
	int	bExist = false;
	char szFullName[MAX_PATH];

	if (FileName && FileName[0])
	{
      //  bExist = KG_IsFileExist(FileName);

      //  if (!bExist)
      //  {
		    ////�Ȳ����Ƿ��ڴ���ļ���
		    //XPackFile::XPackElemFileRef	PackRef;
		    //bExist = g_EnginePackList.FindElemFile(FileName, PackRef);
      //  }

		//�ڼ���Ƿ񵥶������ļ�ϵͳ��
		if (bExist == false)
		{
			g_GetFullPath(szFullName, FileName);
			#ifdef	WIN32
				bExist = !(GetFileAttributesA(szFullName) & FILE_ATTRIBUTE_DIRECTORY);// || dword == INVALID_FILE_ATTRIBUTES)
			#else
//				bExist = _sopen(szFullName, _O_BINARY, _SH_DENYNO, 0);
//				if (bExist != -1)
//				{
//					_close(bExist);
//					bExist = true;
//				}
//				else
//				{
//					bExist = false;
//				}
			#endif
		}
	}
	return bExist;
}

//---------------------------------------------------------------------------
// ����:	String to 32bit Id
// ����:	�ļ���ת���� Hash 32bit ID
// ����:	lpFileName	�ļ���
// ����:	FileName Hash 32bit ID
// ע��:	��Ϸ����������ؽ����������õĹ�ϣ��������Ҳ����
//			������������������޸��������ʱҲ��Ӧ�޸�������
//			�����Ӧ���Ǹ��������������������Common.lib���̵�Utils.h
//			�У���������Ϊ unsigned int HashStr2ID( const char * const pStr );
//---------------------------------------------------------------------------
unsigned int g_StringHash(const char* pString)
{
	unsigned int Id = 0;
	char c = 0;
	for (int i = 0; pString[i]; i++)
	{
		c = pString[i];
		Id = (Id + (i + 1) * c) % 0x8000000b * 0xffffffef;
	}
	return (Id ^ 0x12345678);
}

//��һ���ַ���Сд������תΪhash��ֵ
unsigned int	g_StringLowerHash(const char* pString)
{
	unsigned int Id = 0;
	char c = 0;
	for (int i = 0; pString[i]; i++)
	{
		c = pString[i];
		if (c >= 'A' && c <= 'Z')
			c += 0x20;	//�����ַ��ĺ��ֽ�����ܱ�ת������Ϊ�ؼӴ�������ĸ��ʡ�
		Id = (Id + (i + 1) * c) % 0x8000000b * 0xffffffef;
	}
	return (Id ^ 0x12345678);
}

//��һ���ַ���Сд������תΪhash��ֵ
unsigned int	g_FileNameHash(const char* pString)
{
	unsigned int Id = 0;
	char c = 0;
	for (int i = 0; pString[i]; i++)
	{
		c = pString[i];
		if (c >= 'A' && c <= 'Z')
			c += 0x20;	//�����ַ��ĺ��ֽ�����ܱ�ת������Ϊ�ؼӴ�������ĸ��ʡ�
		else if (c == '/')
			c = '\\';
		Id = (Id + (i + 1) * c) % 0x8000000b * 0xffffffef;
	}
	return (Id ^ 0x12345678);
}

//---------------------------------------------------------------------------
// ����:	change file extention
// ����:	�ı��ļ�����չ��
// ����:	lpFileName	�ļ���
//			lpNewExt	����չ����������'.'
// ����:	void
//---------------------------------------------------------------------------
void g_ChangeFileExt(char* lpFileName, const char* lpNewExt)
{
	char* pDot = strrchr(lpFileName, '.');
	char* pPathSplit = strrchr(lpFileName, PATH_SPLITTER);

	if (pDot && pPathSplit < pDot)
	{
		strcpy(pDot + 1, lpNewExt);
	}
	else
	{
		strcat(lpFileName, ".");
		strcat(lpFileName, lpNewExt);
	}
}

//---------------------------------------------------------------------------
// ����:	Extract File Name from path name
// ����:	ȡ���ļ�����������·����
// ����:	lpFileName	�ļ�����������·����
//			lpFilePath	�ļ���������·����
// ����:	void
//---------------------------------------------------------------------------
void g_ExtractFileName(char* lpFileName, const char* lpFilePath)
{
	int nPos = (int)strlen(lpFilePath);
//	if (nPos < 5)
//		return;
	while ((--nPos) >= 0)
	{
		if (lpFilePath[nPos] == '\\' || lpFilePath[nPos] == '/')
			break;
	}
	strcpy(lpFileName, &lpFilePath[nPos + 1]);
}

//---------------------------------------------------------------------------
// ����:	Extract File Path from path name
// ����:	ȡ��·����
// ����:	lpFileName	·����
//			lpFilePath	·�������ļ���
// ����:	void
//---------------------------------------------------------------------------
void g_ExtractFilePath(char* lpPathName, const char* lpFilePath)
{
	int nPos = (int)strlen(lpFilePath);
//	if (nLen < 5)
//		return;
//	int nPos = nLen;
	while ((--nPos) > 0)
	{
		if (lpFilePath[nPos] == '\\' ||lpFilePath[nPos] == '/')
			break;
	}
	if (nPos > 0)
	{
		memcpy(lpPathName, lpFilePath, nPos);
		lpPathName[nPos] = 0;
	}
	else
	{
		lpPathName[0] = 0;
	}
}

//---------------------------------------------------------------------------
// ����:	Get File Path from full path name
// ����:	��ȫ·����ȡ�����·����
// ����:	lpPathName		���·����
//			lpFullFilePath	ȫ·����
// ����:	void
//---------------------------------------------------------------------------
BOOL g_GetFilePathFromFullPath(char* lpPathName, const char* lpFullFilePath)
{
	if (!lpPathName || !lpFullFilePath)
		return FALSE;

	int nRootSize = strlen(s_szRootPath);
	int nFullSize = strlen(lpFullFilePath);

	if (nFullSize <= nRootSize)
		return FALSE;

	memcpy(lpPathName, lpFullFilePath, nRootSize);
	lpPathName[nRootSize] = 0;

	if (stricmp(lpPathName, s_szRootPath))
		return FALSE;

	//������·�����"\\"
	memcpy(lpPathName, &lpFullFilePath[nRootSize + 1], nFullSize - nRootSize - 1);
	lpPathName[nFullSize - nRootSize - 1] = 0;

	return TRUE;
}

//---------------------------------------------------------------------------
// ����:	Get relative file path from a path
// ����:	��ĳ��·����ȡ�����·����
// ����:	lpRelativePathName		���·����
//			lpFilePath				·����
// ����:	void
//---------------------------------------------------------------------------
// TODO: Fanghao_Wu �ύ��Base�Ƿ����g_GetFilePathFromFullPath��
void g_GetRelativePath(char* lpRelativePathName, const char* lpFilePath)
{
	int nLenRoot = strlen(s_szRootPath);
	int nLenPath = strlen(lpFilePath);
	if (nLenPath > nLenRoot && (memcmp(s_szRootPath, lpFilePath, nLenRoot) == 0))
	{
		strcpy(lpRelativePathName, lpFilePath + nLenRoot);
	}
	else
	{
		memcpy(lpRelativePathName, lpFilePath, nLenPath + 1);
	}
	for (int i = 0; lpRelativePathName[i]; i++)
	{
		if (lpRelativePathName[i] == '/')
			lpRelativePathName[i] = '\\';
	}
}
