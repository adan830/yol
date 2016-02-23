//////////////////////////////////////////////////////////////////////////////////////
//	�ļ���			:	PassGen.h
//	������			:	������
//	����ʱ��		:	2003-6-11 11:59:42
//	�ļ�˵��		:	���ļ�ʵ��һ���򵥼��ܺͽ����㷨
//  ʹ�÷���		:	���ܺ���	SimplyEncryptPassword(...)
//						���ܺ���	SimplyDecryptPassword(...)
//						�����ַ�ֵ�ķ�Χ			0x20-0x7E
//						֧����ַ���				20
//						���ɵļ��ܴ�����			32
//						�������ַ������������С	64
//
//	��������		:	���ɵļ��ܽ����Զ���� 32 ���ַ�
//						���������ַ�����ʲô���ܽ����Զ����Ӣ�ĺ������Լ��»���
//						���ܹ�����������ܹ���Ψһ��Ҳ���Ƕ���ͬһ���ַ���--
//						----���μ��ܵĽ����ȫ��ͬ�������ܵĽ������ԭ�����ַ���
//
//////////////////////////////////////////////////////////////////////////////////////

#ifndef __PASSGEN_H__
#define __PASSGEN_H__

#ifndef ASSERT
#define ASSERT(x)
#endif

//public use
#define PG_MAXBUFFER			64
#define PG_MAXPASSWORDLEN		20
#define PG_RESULTLENSTD			32

//private use
#define PG_MINPKEYLEN			(PG_RESULTLENSTD - PG_MAXPASSWORDLEN - 2)
#define PG_MAXPKEYLEN			(PG_RESULTLENSTD - 2)
#define PG_PKEYMASK				151
#define PG_PKEYOFF				7
#define PG_ENOFF				5
#define PG_MINCHAR				0x20
#define PG_MAXCHAR				0x7E
#define PG_CHARCOUNT			(PG_MAXCHAR - PG_MINCHAR + 1)

#define PG_VALIDCHAR(c)			((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '_') || (c >= '0' && c <= '9'))
#define PG_INVALIDCHAR(c)		!PG_VALIDCHAR(c)

inline int pgChar2Int(char b)
{
    //char i = 0;
    int x = 0, y = 0;
    int nKeyoff = PG_PKEYOFF % 8;
    x = b ^ PG_PKEYMASK;
    y = 0x1 & x;
    y = y << nKeyoff;
    x = x >> (8 - nKeyoff);
    x = x | y;
    x = x & 0x1f;
    return x;
}

inline int pgStrLen(const char* sz)
{
	int i = 0;
	while (sz[i])
		i++;
	return i;
}

inline void pgSwapChars(char* sz)
{
	char c;
#define PG_SWAP(n1, n2)	c = sz[n1]; sz[n1] = sz[n2]; sz[n2] = c

	PG_SWAP(0, 13);
	PG_SWAP(31, 25);
	PG_SWAP(12, 30);
	PG_SWAP(7, 19);
	PG_SWAP(3, 21);
	PG_SWAP(9, 20);
	PG_SWAP(15, 18);
}

inline void pgDecrypt(char* szKey, int nKeyLen, char* szBuffer, const char* szEnc, int nStrLen)
{
	int i, c, cc;
	for (i = 0; i < nStrLen; i++)
	{
		cc = szKey[i % nKeyLen];
		c = szEnc[i];
		szBuffer[i] = ((PG_CHARCOUNT + (c - PG_MINCHAR ) - (cc - PG_MINCHAR)) % PG_CHARCOUNT) + PG_MINCHAR;
	}
	szBuffer[i] = 0;
}

//���ܣ��ɹ����� 1, ʧ�ܷ��� 0
inline int SimplyDecryptPassword(char* szPass, const char* szEncrypted)
{
	int nLen = pgStrLen(szEncrypted), nPKLen = 0, i = 0;
	char szBuffer[PG_RESULTLENSTD + 1];
	if (nLen != PG_RESULTLENSTD)
		return 0;

	for (i = 0; i < PG_RESULTLENSTD; i++)
		szBuffer[i] = szEncrypted[i];
	szBuffer[PG_RESULTLENSTD] = 0;

	pgSwapChars(szBuffer);

	nPKLen = pgChar2Int(szBuffer[0]);
	if (nPKLen < PG_MINPKEYLEN || nPKLen > PG_MAXPKEYLEN)
		return 0;
	nLen = pgChar2Int(szBuffer[nPKLen + 1]);
	if (nLen < 0 || nLen > PG_MAXPASSWORDLEN)
		return 0;
	pgDecrypt(szBuffer + 1, nPKLen, szPass, szBuffer + nPKLen + 2, nLen);

	return 1;
}

#endif //__PASSGEN_H__
