
#include "CorePrivate.h"
#include "QStrBase.h"
#ifdef WIN32
#include <string.h>
#else
#include <strings.h>
#endif

int QStrLen(LPCSTR lpStr)
{
	return strlen(lpStr);
}
//---------------------------------------------------------------------------
// ����:	StrEnd
// ����:	�����ַ�����βָ��
// ����:	lpStr	:	�ַ�����ͷ��ָ��
// ����:	lpEnd	:	�ַ���ĩβ��ָ��
//---------------------------------------------------------------------------
LPSTR QStrEnd(LPCSTR lpStr)
{
	return (char *)lpStr + strlen(lpStr);
}
//---------------------------------------------------------------------------
// ����:	StrCpy
// ����:	�ַ�������
// ����:	lpDest	:	Ŀ���ַ���
//			lpSrc	:	Դ�ַ���
// ����:	void
//---------------------------------------------------------------------------
void QStrCpy(LPSTR lpDest, LPCSTR lpSrc)
{
	strcpy(lpDest, lpSrc);
}
//---------------------------------------------------------------------------
// ����:	StrCpyLen
// ����:	�ַ�������,����󳤶�����
// ����:	lpDest	:	Ŀ���ַ���
//			lpSrc	:	Դ�ַ���
//			nMaxLen	:	��󳤶�
// ����:	void
//---------------------------------------------------------------------------
void QStrCpyLen(LPSTR lpDest, LPCSTR lpSrc, int nMaxLen)
{
	strncpy(lpDest, lpSrc, nMaxLen);
}
//---------------------------------------------------------------------------
// ����:	StrCat
// ����:	�ַ���ĩβ׷����һ���ַ���
// ����:	lpDest	:	Ŀ���ַ���
//			lpSrc	:	Դ�ַ���
// ����:	void
//---------------------------------------------------------------------------
void QStrCat(LPSTR lpDest, LPCSTR lpSrc)
{
	register LPSTR lpEnd;

	lpEnd = QStrEnd(lpDest);
	QStrCpy(lpEnd, lpSrc);
}
//---------------------------------------------------------------------------
// ����:	StrCatLen
// ����:	�ַ���ĩβ׷����һ���ַ���,����󳤶�����
// ����:	lpDest	:	Ŀ���ַ���
//			lpSrc	:	Դ�ַ���
//			nMaxLen	:	��󳤶�
// ����:	void
//---------------------------------------------------------------------------
void QStrCatLen(LPSTR lpDest, LPCSTR lpSrc, int nMaxLen)
{
	register LPSTR lpEnd;

	lpEnd = QStrEnd(lpDest);
	QStrCpyLen(lpEnd, lpSrc, nMaxLen);
}
//---------------------------------------------------------------------------
// ����:	StrCmp
// ����:	�ַ����Ƚ�
// ����:	lpDest	:	�ַ���1	
//			lpSrc	:	�ַ���2
// ����:	TRUE	:	��ͬ
//			FALSE	:	��ͬ
//---------------------------------------------------------------------------
BOOL QStrCmp(LPCSTR lpDest, LPCSTR lpSrc)
{
	return strcmp(lpDest, lpSrc) == 0;
}
//---------------------------------------------------------------------------
// ����:	StrCmpLen
// ����:	�ַ����Ƚ�,�޶�����
// ����:	lpDest	:	�ַ���1	
//			lpSrc	:	�ַ���2
//			nLen	:	����
// ����:	TRUE	:	��ͬ
//			FALSE	:	��ͬ
//---------------------------------------------------------------------------
BOOL QStrCmpLen(LPCSTR lpDest, LPCSTR lpSrc, int nMaxLen)
{
	return strncmp(lpDest, lpSrc, nMaxLen) == 0;
}
//---------------------------------------------------------------------------
// ����:	StrUpper
// ����:	Сд��ĸת��д��ĸ
// ����:	lpDest	:	�ַ���
// ����:	void
//---------------------------------------------------------------------------
void QStrUpper(LPSTR lpDest)
{
     char *ptr = lpDest;
     while(*ptr) {
         if(*ptr >= 'a' && *ptr <= 'z') 
			 *ptr += 'A' - 'a';
//          *ptr = toupper(*ptr);
          ptr++;
     }
}
//---------------------------------------------------------------------------
// ����:	StrLower
// ����:	��д��ĸתСд��ĸ
// ����:	lpDest	:	�ַ���
// ����:	void
//---------------------------------------------------------------------------
void QStrLower(LPSTR lpDest)
{
     char *ptr = lpDest;
     while(*ptr) {
         if(*ptr >= 'A' && *ptr <= 'Z')
			*ptr += 'a' - 'A';
//          *ptr = tolower(*ptr);
          ptr++;
     }
}
//---------------------------------------------------------------------------
void QStrRep(LPSTR lpDest, LPSTR lpSrc, LPSTR lpRep)
{
	int		nSrcLen = QStrLen(lpSrc);
	int		nDestLen = QStrLen(lpDest);
	int		nMaxLen = nDestLen - nSrcLen + QStrLen(lpRep) + 1;
	char	*pStart = NULL;
        int i;
	for (i = 0; i < nDestLen - nSrcLen; i++)
	{
		if (QStrCmpLen(&lpDest[i], lpSrc, nSrcLen))
			break;
	}
	if (i == nDestLen - nSrcLen)
		return;

	pStart = new char[nMaxLen];

	if (i != 0)
	{
		QStrCpyLen(pStart, lpDest, i);
		QStrCat(pStart, lpRep);
		QStrCat(pStart, &lpDest[i + nSrcLen]);
	}
	else
	{
		QStrCpy(pStart, lpRep);
		QStrCat(pStart, &lpDest[nSrcLen]);
	}
	QStrCpy(lpDest, pStart);
	if (pStart)
	{
		delete [] pStart;
		pStart = NULL;
	}
}

int QStrCaseCmp(LPCSTR pszSrc, LPCSTR pszDst)
{
#ifdef WIN32
	return stricmp(pszSrc, pszDst);
#else
	return strcasecmp(pszSrc, pszDst);
#endif
}

int QStrNCaseCmp(LPCSTR pszSrc, LPCSTR pszDst, int nLen)
{
#ifdef WIN32
	return strnicmp(pszSrc, pszDst, nLen);
#else
	return strncasecmp(pszSrc, pszDst, nLen);
#endif
}

