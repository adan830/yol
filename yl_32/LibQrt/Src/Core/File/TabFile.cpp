
#include "CorePrivate.h"
#include "File.h"
#include "TabFile.h"
#include "TabFileWritable.h"
#include "QStrBase.h"
#include "QLog.h"


ITabFile*
g_OpenTabFile(const char* FileName, int ForceUnpakFile/* = false*/, int ForWrite/* = false*/)
{
	ITabFile*	pTab = NULL;
	IFile*		pFile = g_OpenFile(FileName, ForceUnpakFile, ForWrite);
	int			nResult = false;
	QLogPrintf(LOG_INFO, "..g_OpenTabFile=%s", FileName);
	if (pFile)
	{
		if (!ForWrite)
		{
			if ((pTab = QTabFileImpl::New()) != NULL)
				nResult = ((QTabFileImpl*)pTab)->LoadData(pFile);
		}
		else if ((pTab = QTabFileWritable::New()) != NULL)
		{
			nResult = ((QTabFileWritable*)pTab)->LoadData(pFile);
		}
	}
	if (!nResult)
		SAFE_RELEASE(pTab);
	SAFE_RELEASE(pFile);
	return pTab;
}

bool g_OpenFile(ITabFile** ppTabFile, const char* FileName, int ForceUnpakFile /* = false */, int ForWrite /* = false */)
{
	
	*ppTabFile = g_OpenTabFile(FileName, ForceUnpakFile, ForWrite);
	return (*ppTabFile != NULL);
}

ITabFile* g_CreateTabFile()
{
	return QTabFileWritable::New();
}

#define _IS_NEWLINE(c) ((c) == 0x0d || (c) == 0x0a)

static inline BOOL s_GoNextLine(LPBYTE& pbyBuf, INT& nOffset, INT nSize)
{
	BOOL bResult	= FALSE;
	PROCESS_ERROR(nOffset < nSize);

	// ���ҵ�����
	while (!_IS_NEWLINE(*pbyBuf))
	{
		pbyBuf ++;
		nOffset ++;
		LOG_PROCESS_ERROR(nOffset < nSize);	// �����ļ�β����ӻ���
	}

	// �������з�
	pbyBuf ++;
	nOffset ++;

	// ˫�ֽڻ��з�
	if (nOffset < nSize && pbyBuf[-1] == 0x0d && pbyBuf[0] == 0x0a)
	{
		pbyBuf ++;
		nOffset ++;
	}

	bResult	= TRUE;

EXIT0:
	return bResult;
}

//---------------------------------------------------------------------------
// ����:	KTabFileImpl
// ����:	���캯��
//---------------------------------------------------------------------------
QTabFileImpl::QTabFileImpl()
{
	m_Width		= 0;
	m_Height	= 0;
	m_pMemory	= NULL;
	m_uMemorySize = 0;
	m_pOffsetTable = NULL;
    m_bErrorLogEnable = true;
}

//---------------------------------------------------------------------------
// ����:	~KTabFileImpl
// ����:	���캯��
//---------------------------------------------------------------------------
QTabFileImpl::~QTabFileImpl()
{
	Clear();
}

//����һ���յ�KTabFileImpl����
QTabFileImpl* QTabFileImpl::New()
{
    QTabFileImpl* pTabFile = new QTabFileImpl();
    if (pTabFile)
    {
        pTabFile->SetErrorLog(true);
    }
	return pTabFile;
}

// ����:	����һ��Tab�ļ�
int	QTabFileImpl::LoadData(IFile* pFile)
{
	assert(pFile);
	Clear();

	int				nResult = false;
	unsigned int	dwSize = pFile->Size();
	if (dwSize == 0)
		return true;

	m_pMemory = (unsigned char *)malloc(dwSize);
	if (m_pMemory)
	{
		m_uMemorySize = dwSize;
		if (pFile->Read(m_pMemory, dwSize) == dwSize)
		{
			if (CreateTabOffset())
				nResult = true;
		}
	}
	if (!nResult)
		Clear();
	return nResult;
}

int	QTabFileImpl::GetWidth()
{
	return m_Width;
}

int QTabFileImpl::GetHeight()
{
	return m_Height;
}

//---------------------------------------------------------------------------
// ����:	CreateTabOffset
// ����:	������������ָ��ļ���ƫ�Ʊ�
//---------------------------------------------------------------------------
int QTabFileImpl::CreateTabOffset()
{
	int		nWidth, nHeight, nOffset, nSize;
	unsigned char	*Buffer;

	nWidth	= 1;
	nHeight	= 0;
	nOffset = 0;

	Buffer	= m_pMemory;
	nSize	= m_uMemorySize;
	
	if (!Buffer || !nSize)
		return true;

	// ����һ�о����ж�����
	while (nOffset < nSize && !_IS_NEWLINE(*Buffer))
	{
		if (*Buffer == 0x09)
			nWidth++;

		Buffer++;
		nOffset++;
	}

	while(s_GoNextLine(Buffer, nOffset, nSize))
		nHeight++;

	m_Width		= nWidth;
	m_Height	= nHeight;

	m_pOffsetTable = (TABOFFSET*)malloc(m_Width * m_Height * sizeof(TABOFFSET));
	if (m_pOffsetTable == NULL)
		return false;

	memset(m_pOffsetTable, 0, m_Width * m_Height * sizeof(TABOFFSET));
	TABOFFSET* TabBuffer = m_pOffsetTable;
	Buffer = m_pMemory;

	nOffset = 0;
	int nLength;
	for (int i = 0; i < nHeight; i++)
	{
		for (int j = 0; j < nWidth; j++)
		{
			TabBuffer->dwOffset = nOffset;
			nLength = 0;
			while(nOffset < nSize && *Buffer != 0x09 && !_IS_NEWLINE(*Buffer))
			{
				Buffer++;
				nOffset++;
				nLength++;
			}
			TabBuffer->dwLength = nLength;

			if (nOffset >= nSize)
				break;

			if (_IS_NEWLINE(*Buffer))	//	�����Ѿ������ˣ���Ȼ����û��nWidth
			{
				TabBuffer	+= nWidth - j;
				break;
			}

			Buffer++;	// 0x09����
			nOffset++;

			TabBuffer++;
		}
		if (nOffset >= nSize)
			break;

		s_GoNextLine(Buffer, nOffset, nSize);
	}
	return true;
}

//---------------------------------------------------------------------------
// ����:	Str2Column
// ����:	ȡ��ĳ��ĳ���ַ�����ֵ
// ����:	szColumn
// ����:	�ڼ���
//---------------------------------------------------------------------------
int QTabFileImpl::Str2Col(const char* szColumn)
{
	char	szTemp[4];
	strncpy(szTemp, szColumn, 3);
	szTemp[2] = 0;
	QStrLower(szTemp);

	int		nIndex;
	if (szTemp[0])
	{
		if (szTemp[1] == 0)
			nIndex = (szTemp[0] - 'a');
		else
			nIndex = ((szTemp[0] - 'a' + 1) * 26 + szTemp[1] - 'a') + 1;
	}
	else
	{
		nIndex = -1;
	}
	return nIndex;
}

//---------------------------------------------------------------------------
// ����:	GetString
// ����:	ȡ��ĳ��ĳ���ַ�����ֵ
// ����:	nRow			��
//			nColomn			��
//			lpDefault		ȱʡֵ
//			lpRString		����ֵ
//			dwSize			�����ַ�������󳤶�
// ����:	1���ɹ�	0����񲻶�	-1��δ�ʹ��Ĭ��ֵ
//---------------------------------------------------------------------------
int	QTabFileImpl::GetString(int nRow, const char* szColumn, const char* lpDefault,
						char* lpRString, unsigned int dwSize, int bColumnLab)
{
	int nColumn;
	int	nRet = 0;

	if (bColumnLab)
		nColumn = FindColumn(szColumn);
	else
		nColumn = Str2Col(szColumn);

	nRet = GetValue(nRow - 1, nColumn - 1, lpRString, dwSize);
	if (1 != nRet)
		QStrCpyLen(lpRString, lpDefault, dwSize);

    if (nRet == 0 && m_bErrorLogEnable)
    {
        QLogPrintf(LOG_ERR, "GetString(%d, %s) failed !\n", nRow, szColumn);
    }
	return nRet;
}

//---------------------------------------------------------------------------
// ����:	GetString
// ����:	ȡ��ĳ��ĳ���ַ�����ֵ
// ����:	szRow			��	���ؼ��֣�
//			szColomn		��	���ؼ��֣�
//			lpDefault		ȱʡֵ
//			lpRString		����ֵ
//			dwSize			�����ַ�������󳤶�
// ����:	1���ɹ�	0����񲻶�	-1��δ�ʹ��Ĭ��ֵ
//---------------------------------------------------------------------------
int	QTabFileImpl::GetString(const char* szRow, const char* szColumn,
					const char* lpDefault, char* lpRString, unsigned int dwSize)
{
	int nRow, nColumn;
	int nRet = 0;

	nRow = FindRow(szRow);
	nColumn = FindColumn(szColumn);
	nRet = GetValue(nRow - 1, nColumn - 1, lpRString, dwSize);
	if (1 != nRet)
		QStrCpyLen(lpRString, lpDefault, dwSize);

    if (nRet == 0 && m_bErrorLogEnable)
    {
        QLogPrintf(LOG_ERR, "GetString(%s, %s) failed !\n", szRow, szColumn);
    }
	return nRet;
}

//---------------------------------------------------------------------------
// ����:	GetString
// ����:	ȡ��ĳ��ĳ���ַ�����ֵ
// ����:	nRow			��		��1��ʼ
//			nColomn			��		��1��ʼ
//			lpDefault		ȱʡֵ
//			lpRString		����ֵ
//			dwSize			�����ַ�������󳤶�
// ����:	1���ɹ�	0����񲻶�	-1��δ�ʹ��Ĭ��ֵ
//---------------------------------------------------------------------------
int	QTabFileImpl::GetString(int nRow, int nColumn, const char* lpDefault,
						char* lpRString, unsigned int dwSize)
{
	int nRet = 0;

	nRet = GetValue(nRow - 1, nColumn - 1,  lpRString, dwSize);

	if (1 != nRet)
		QStrCpyLen(lpRString, lpDefault, dwSize);

    if (nRet == 0 && m_bErrorLogEnable)
    {
        QLogPrintf(LOG_ERR, "GetString(%d, %d) failed !\n", nRow, nColumn);
		
    }

	return nRet;
}

//---------------------------------------------------------------------------
// ����:	GetInteger
// ����:	ȡ��ĳ��ĳ���ַ�����ֵ
// ����:	nRow			��
//			szColomn		��
//			nDefault		ȱʡֵ
//			pnValue			����ֵ
// ����:	1���ɹ�	0����񲻶�	-1��δ�ʹ��Ĭ��ֵ
//---------------------------------------------------------------------------
int	QTabFileImpl::GetInteger(int nRow, const char* szColumn, int nDefault,
						int *pnValue, int bColumnLab)
{
	char	Buffer[32];
	int		nColumn;
	int		nRet = 0;

	if (bColumnLab)
		nColumn = FindColumn(szColumn);
	else
		nColumn = Str2Col(szColumn);
	nRet = GetValue(nRow - 1, nColumn - 1, Buffer, sizeof(Buffer));

	if (1 == nRet)
	{
		*pnValue = atoi(Buffer);
	}
	else
	{
		*pnValue = nDefault;
	}

    if (nRet == 0 && m_bErrorLogEnable)
    {
        QLogPrintf(LOG_ERR, "GetInteger(%d, %s) failed !\n", nRow, szColumn);
		//assert(FALSE);
		
    }

	return nRet;
}

//---------------------------------------------------------------------------
// ����:	GetInteger
// ����:	ȡ��ĳ��ĳ���ַ�����ֵ
// ����:	szRow			��
//			szColomn		��
//			nDefault		ȱʡֵ
//			pnValue			����ֵ
// ����:	1���ɹ�	0����񲻶�	-1��δ�ʹ��Ĭ��ֵ
//---------------------------------------------------------------------------
int	QTabFileImpl::GetInteger(const char* szRow, const char* szColumn,
						int nDefault, int *pnValue)
{
	int		nRow, nColumn;
	char	Buffer[32];
	int		nRet = 0;

	nRow = FindRow(szRow);
	nColumn = FindColumn(szColumn);

	nRet = GetValue(nRow - 1, nColumn - 1, Buffer, sizeof(Buffer));
	if (1 == nRet)
	{
		*pnValue = atoi(Buffer);
	}
	else
	{
		*pnValue = nDefault;
	}

    if (nRet == 0 && m_bErrorLogEnable)
    {
        QLogPrintf(LOG_ERR, "GetInteger(%s, %s) failed !\n", szRow, szColumn);
		//assert(FALSE);
    }

	return nRet;
}

//---------------------------------------------------------------------------
// ����:	GetInteger
// ����:	ȡ��ĳ��ĳ���ַ�����ֵ
// ����:	nRow			��		��1��ʼ
//			nColomn			��		��1��ʼ
//			nDefault		ȱʡֵ
//			pnValue			����ֵ
// ����:	1���ɹ�	0����񲻶�	-1��δ�ʹ��Ĭ��ֵ
//---------------------------------------------------------------------------
int QTabFileImpl::GetInteger(int nRow, int nColumn, int nDefault, int *pnValue)
{
	char	Buffer[32];
	int		nRet = 0;

	nRet = GetValue(nRow - 1, nColumn - 1, Buffer, sizeof(Buffer));
	if (1 == nRet)
	{
		*pnValue = atoi(Buffer);
	}
	else
	{
		*pnValue = nDefault;
	}

    if (nRet == 0 && m_bErrorLogEnable)
    {
        QLogPrintf(LOG_ERR, "GetInteger(%d, %d) failed !\n", nRow, nColumn);
		//assert(FALSE);
    }

	return nRet;
}

//---------------------------------------------------------------------------
// ����:	GetFloat
// ����:	ȡ��ĳ��ĳ���ַ�����ֵ
// ����:	nRow			��
//			szColomn		��
//			nDefault		ȱʡֵ
//			pnValue			����ֵ
// ����:	1���ɹ�	0����񲻶�	-1��δ�ʹ��Ĭ��ֵ
//---------------------------------------------------------------------------
int	QTabFileImpl::GetFloat(int nRow, const char* szColumn, float fDefault,
						float *pfValue, int bColumnLab)
{
	char	Buffer[32];
	int		nColumn;
	int		nRet = 0;
	if (bColumnLab)
		nColumn = FindColumn(szColumn);
	else
		nColumn = Str2Col(szColumn);
	nRet = GetValue(nRow - 1, nColumn - 1, Buffer, sizeof(Buffer));
	if (1 == nRet)
	{
		*pfValue = (float)atof(Buffer);
	}
	else
	{
		*pfValue = fDefault;
	}

    if (nRet == 0 && m_bErrorLogEnable)
    {
        QLogPrintf(LOG_ERR, "GetFloat(%d, %s) failed !\n", nRow, szColumn);
    }

	return nRet;
}

//---------------------------------------------------------------------------
// ����:	GetFloat
// ����:	ȡ��ĳ��ĳ���ַ�����ֵ
// ����:	szRow			��
//			szColomn		��
//			nDefault		ȱʡֵ
//			pnValue			����ֵ
// ����:	1���ɹ�	0����񲻶�	-1��δ�ʹ��Ĭ��ֵ
//---------------------------------------------------------------------------
int	QTabFileImpl::GetFloat(const char* szRow, const char* szColumn,
						float fDefault, float *pfValue)
{
	int		nRow, nColumn;
	char	Buffer[32];
	int		nRet = 0;

	nRow = FindRow(szRow);
	nColumn = FindColumn(szColumn);
	nRet = GetValue(nRow - 1, nColumn - 1, Buffer, sizeof(Buffer));
	if (1 == nRet)
	{
		*pfValue = (float)atof(Buffer);
	}
	else
	{
		*pfValue = fDefault;
	}

    if (nRet == 0 && m_bErrorLogEnable)
    {
        QLogPrintf(LOG_ERR, "GetFloat(%s, %s) failed !\n", szRow, szColumn);
    }

	return nRet;
}

//---------------------------------------------------------------------------
// ����:	GetFloat
// ����:	ȡ��ĳ��ĳ���ַ�����ֵ
// ����:	nRow			��		��1��ʼ
//			nColomn			��		��1��ʼ
//			nDefault		ȱʡֵ
//			pnValue			����ֵ
// ����:	1���ɹ�	0����񲻶�	-1��δ�ʹ��Ĭ��ֵ
//---------------------------------------------------------------------------
int QTabFileImpl::GetFloat(int nRow, int nColumn, float fDefault, float *pfValue)
{
	char	Buffer[32];
	int nRet = 0;
	
	nRet = GetValue(nRow - 1, nColumn - 1, Buffer, sizeof(Buffer));
	if (1 == nRet)
	{
		*pfValue = (float)atof(Buffer);
	}
	else
	{
		*pfValue = fDefault;
	}

    if (nRet == 0 && m_bErrorLogEnable)
    {
        QLogPrintf(LOG_ERR, "GetFloat(%d, %d) failed !\n", nRow, nColumn);
    }

	return nRet;
}
//---------------------------------------------------------------------------
// ����:	GetValue
// ����:	ȡ��ĳ��ĳ���ַ�����ֵ
// ����:	nRow			��
//			nColomn			��
//			lpRString		����ֵ
//			dwSize			�����ַ�������󳤶�
// ����:	1���ɹ�	0����񲻶�	-1��δ�ʹ��Ĭ��ֵ
//---------------------------------------------------------------------------
int	QTabFileImpl::GetValue(int nRow, int nColumn, char* lpRString, unsigned int dwSize)
{
	if (nRow >= m_Height || nColumn >= m_Width || nRow < 0 || nColumn < 0)
		return 0;

	CONST TABOFFSET& rsTempOffset	= m_pOffsetTable[nRow * m_Width + nColumn];
	LPCSTR pchBuffer				= (LPCSTR)&m_pMemory[rsTempOffset.dwOffset];

	if (rsTempOffset.dwLength == 0)
	{
		lpRString[0] = 0;
		return -1;
	}

	if (dwSize > rsTempOffset.dwLength)
	{
		memcpy(lpRString, pchBuffer, rsTempOffset.dwLength);
		lpRString[rsTempOffset.dwLength] = 0;
	}
	else
	{
		memcpy(lpRString, pchBuffer, dwSize);
		lpRString[dwSize - 1] = 0;
	}

	return 1;
}
//---------------------------------------------------------------------------
// ����:	Clear
// ����:	���TAB�ļ�������
// ����:	void
// ����:	void
//---------------------------------------------------------------------------
void QTabFileImpl::Clear()
{
	m_Width = 0;
	m_Height = 0;
	m_uMemorySize = 0;
	SAFE_FREE(m_pMemory);
	SAFE_FREE(m_pOffsetTable);
}

//---------------------------------------------------------------------------
// ����:	FindRow
// ����:	�����йؼ���
// ����:	szRow���йؼ��֣�
// ����:	int
//---------------------------------------------------------------------------
int QTabFileImpl::FindRow(const char* szRow)
{
	CONST TABOFFSET* psTempOffset	= m_pOffsetTable;
	INT nStrLen	= QStrLen(szRow);

	for (int i = 0; i < m_Height; i++, psTempOffset+=m_Width)
	{
		if (nStrLen != psTempOffset->dwLength)
			continue;

		// strncmp��memcmp�죬ԭ��δ֪
		if (strncmp((LPCSTR)m_pMemory + psTempOffset->dwOffset, szRow, nStrLen))
			continue;


		return i + 1;//�Ķ��˴�Ϊ��һ by Romandou,��������1Ϊ���ı��
	}
	return -1;
}

//---------------------------------------------------------------------------
// ����:	FindColumn
// ����:	�����йؼ���
// ����:	szColumn���йؼ��֣�
// ����:	int
//---------------------------------------------------------------------------
int QTabFileImpl::FindColumn(const char* szColumn)
{
	CONST TABOFFSET* psTempOffset	= m_pOffsetTable;
	INT nStrLen	= strlen(szColumn);

	for (int i = 0; i < m_Width; i++, psTempOffset++)
	{
		if (nStrLen != psTempOffset->dwLength)
			continue;

		// strncmp��memcmp�죬ԭ��δ֪
		if (strncmp((LPCSTR)m_pMemory + psTempOffset->dwOffset, szColumn, nStrLen))
			continue;

		return i + 1;//�Ķ��˴�Ϊ��һ by Romandou,��������1Ϊ���ı��
	}
	return -1;
}

//---------------------------------------------------------------------------
// ����:	Col2Str
// ����:	������ת���ַ���
// ����:	szColumn
// ����:	�ڼ���
//---------------------------------------------------------------------------
void QTabFileImpl::Col2Str(int nCol, char* szColumn)
{
	if (nCol < 26)
	{
		szColumn[0] = 'A' + nCol;
		szColumn[1]	= 0;
	}
	else
	{
		szColumn[0] = 'A' + (nCol / 26 - 1);
		szColumn[1] = 'A' + nCol % 26;
		szColumn[2] = 0;
	}
}

void QTabFileImpl::Release()
{
	Clear();
	delete this;
}

void QTabFileImpl::SetErrorLog(BOOL bEnable)
{
    m_bErrorLogEnable = bEnable;
}
