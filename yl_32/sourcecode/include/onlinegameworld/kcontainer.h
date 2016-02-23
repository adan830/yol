
//	��������	��	��������
//
//	Key������һ��ID��Key����Ӧһ��ֵ�ı�����������ID�Ա������й���

#pragma once

#include <limits>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// ������ʽKey����������ID�����ޣ�ID��ռ�ڴ漰�洢�ռ䣬����Ч�ʸߣ�����������ֵ��һֱռ���ڴ漰�洢�ռ�
template<class T>
class KTArrayValue
{
public:
	BOOL SetValue(UINT uIndex, T tValue)
	{
		QCONFIRM_RET_FALSE(uIndex <= m_nMaxIndex);
		m_pValue[uIndex] = tValue;
		return TRUE;
	}
	BOOL AddValue(UINT uIndex, T tValue)
	{
		QCONFIRM_RET_FALSE(uIndex <= m_nMaxIndex);
		m_pValue[uIndex] += tValue;
		return TRUE;
	}
	BOOL AddValueU(UINT uIndex, T tValue)
	{
		QCONFIRM_RET_FALSE(uIndex <= m_nMaxIndex);
		if (m_pValue[uIndex] > std::numeric_limits<T>::max() - tValue)
			return FALSE;
		m_pValue[uIndex] += tValue;
		return TRUE;
	}
	BOOL DecValueU(UINT uIndex, T tValue)
	{
		QCONFIRM_RET_FALSE(uIndex <= m_nMaxIndex);
		if (m_pValue[uIndex] < std::numeric_limits<T>::min() + tValue)
			return FALSE;
		m_pValue[uIndex] -= tValue;
		return TRUE;
	}
	T GetValue(UINT uIndex) const
	{
		QCONFIRM_RET_FALSE(uIndex <= m_nMaxIndex);
		return m_pValue[uIndex];
	}
	BOOL GetFlag(UINT uIndex, UINT uBit) const // ��ȡһ��λ
	{
		QCONFIRM_RET_FALSE(uIndex <= m_nMaxIndex);
		return (m_pValue[uIndex] & (1 << uBit)) != 0;
	}
	BOOL SetFlag(UINT uIndex, UINT uBit, BOOL bSet) // ����һ��λ����λ������������Χ����FALSE
	{
		QCONFIRM_RET_FALSE(uIndex <= m_nMaxIndex && uBit < sizeof(T) * 8);
		if (bSet)
			m_pValue[uIndex] |= (1 << uBit);
		else
			m_pValue[uIndex] &= ~(1 << uBit);
		return TRUE;
	}
	// ��ȡֵ���ã������Խ�磡
	T& RefValue(UINT uIndex)
	{
		return m_pValue[uIndex];
	}
	KTArrayValue() : m_pValue(NULL), m_nMaxIndex(0)
	{

	}
	~KTArrayValue()
	{
		SAFE_DELETE_ARRAY(m_pValue);
	}	

	BOOL Create(INT nMaxIndex)
	{
		m_pValue = new T[nMaxIndex + 1];
		ZeroMemory(m_pValue, sizeof(T) * (nMaxIndex + 1));
		m_nMaxIndex = nMaxIndex;
		return m_pValue != NULL;
	}
	BOOL Init()
	{
		QCONFIRM_RET_FALSE(m_pValue);
		ZeroMemory(m_pValue, sizeof(T) * (m_nMaxIndex + 1));
		return TRUE;
	}
	SIZE_T Count() const { return SIZE_T(m_nMaxIndex + 1); }
	// ֻ׼����ģ�����
	LPVOID RawGet() { return m_pValue; }
	LPCVOID GetBuffer() const { return m_pValue; }
protected:
	T* m_pValue;
	UINT m_nMaxIndex;
	friend class KContainer_Save;
};

// -------------------------------------------------------------------------
#define KD_VAR_KEY(varGroup, varId)		((varGroup) << 16 | (varId))
#define KD_VAR_GROUP(varKey)		(((varKey) & 0xFFFF0000) >> 16)
#define KD_VAR_ID(varKey)		((varKey) & 0xFFFF)

class KContainer
{
public:
	KContainer();
	~KContainer();
	BOOL Create(INT nByValueNum, INT nWValueNum, INT nDwValueNum);
	BOOL Init();
	VOID UnInit();
	INT GetMapValue(DWORD dwKey) const;
	BOOL SetMapValue(DWORD dwKey, INT nValue);
	BOOL AppendMapValue(DWORD dwKey, INT nAdd);
	BOOL AppendMapValueU(DWORD dwKey, INT nAdd);
public:
	// ������ʽKey��������DWORD��WORD, BYTE��
	KTArrayValue<DWORD> m_cDwArrayValue;
	KTArrayValue<WORD> m_cWArrayValue;
	KTArrayValue<BYTE> m_cByArrayValue;
	// map��ʽKey����
	std::map<DWORD, DWORD> m_mpDynValue;
};

class KContainer_Save : public KContainer
{
public:
	// �����������ݴ���pBuffer������ʵ�ʴ洢���ȣ����������Ȳ��㷵��-1
	INT Save(LPBYTE pBuffer, UINT uBufSize);
	// ������������
	BOOL Load(LPCBYTE pData, UINT uDataLen);
};
// -------------------------------------------------------------------------

