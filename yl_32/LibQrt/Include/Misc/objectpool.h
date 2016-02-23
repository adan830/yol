
#pragma once

#include <vector>
#include <algorithm>
// -------------------------------------------------------------------------

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#ifndef NULL
#define NULL 0
#endif

#define _WARNING	_ASSERT
/*����Ҫ�������ú��ͷ�ʱ������������ػ�����������*/
template <typename T> inline
VOID KOP_ReUse(T &widget) {};
template <typename T> inline
VOID KOP_UnUse(T &widget) {};

/*---------------------------------------------------------
//��̬�ڴ���ֻ࣬������ռ�������ͷ�
//���������Ǽȿ�ʵ�ֶ�̬������ڴ���������ֿɷ�ֹ���������ڴ���Ƭ
//������ȫ���Ե��ڴ����󣬵������ڱ�����ȷ���ڴ��С�����Բ�����static�ڴ棩�����
//--------------------------------------------------------*/
class KStaticMemPool
{
public:
	//���캯��Ԥ����
	KStaticMemPool(INT size, INT increment) 
	{ _MemP = new CHAR[size]; MaxSize = size; curSize = 0; IncreSize = increment; NextBlock = NULL; }
	~KStaticMemPool()
	{ delete[] _MemP; if(NULL != NextBlock) delete NextBlock; }
	CHAR *GetBuf(INT blockSize)
	{
		if (blockSize > MaxSize)
			return NULL;
		if (curSize + blockSize > MaxSize) //�����ǰ���ڴ�鲻�� 
		{
			if (NULL == NextBlock)
			{
				//������һ���ڴ��
				if(blockSize>IncreSize)
					NextBlock = new KStaticMemPool(blockSize, IncreSize);
				else 
					NextBlock = new KStaticMemPool(IncreSize, IncreSize);
			}
			//����һ�����ڴ�ػ�ȡ�ڴ�
			return NextBlock->GetBuf(blockSize);
		}
		curSize += blockSize;
		return _MemP+curSize-blockSize;
	}
protected:
	CHAR *_MemP; //���ڴ����ָ��
	INT MaxSize; //���ڴ��Ĵ�С
	INT curSize; //��ʹ���ڴ��С
	INT IncreSize; //������С
	KStaticMemPool *NextBlock; //��һ���ڴ��ָ��
private:
};

//ȫ�����ö�����䣬�ⲿ���븺�������ͷ�
template <class T>
class FeuNew
{
	//�����͹�����ʵ��ָ�뼯���Զ��ͷ�
	class vec_auto_release_ptr
	{
		VOID	AddPtr(T *p) { vec_ptr.push_back(p); }
		static VOID	_release(T *p) { delete p; }
		~vec_auto_release_ptr() { std::for_each(vec_ptr.begin(), vec_ptr.end(), _release); }
	private:
		friend class FeuNew<T>;
		std::vector<T*> vec_ptr;
	};
public:
	static T* New()
	{
		return AddAutoRelease(new T);
	}
	// ����Զ��ͷŵĶ���ָ�루��������new����Ķ���
	static T* AddAutoRelease(T* p)
	{
		//����static����ʵ��ȫ�ֵ�������
		static vec_auto_release_ptr s_vecPtr;
		if (p)
			s_vecPtr.AddPtr(p);
		return p;
	}
};

/*-------------------------------------------------------------------------------
//���ƣ���Ч�������
//���ܣ��ȳ��ڴ�黺��ʽ�ڴ�ء�ʵ�ֵȳ��ڴ�Ŀ���������ͷţ�����ϵͳ�����ڴ���Ƭ
//���ԣ��������飬�޿ռ����䣬���ظ��ͷż�飬���̰߳�ȫ
//ʹ�ó��ϣ���׼ȷ�����ڴ�ʹ�÷�ֵ�����ܱ�֤���ظ��ͷţ�������������ѷ������
//------------------------------------------------------------------------------*/
template <class T>
class KObjPool
{
public:
	KObjPool()
	{
		m_pObject = NULL;
		m_pObject = NULL;
		m_nMaxSize = 0;
		m_nIndex= 0;
	}
	//������Ԥ�����С
	VOID Init(INT nSize)
	{
		m_pObject = new T[nSize];
		m_ppFreeList = new T*[nSize];
		m_nMaxSize = nSize;
		m_nIndex = 0;
		INT i = 0;
		while (i < nSize)
		{
			m_ppFreeList[i] = m_pObject + i;
			i++;
		}
	}
	//�Ӷ���ػ�ȡ����
	inline T* New()
	{
		if (m_nIndex < m_nMaxSize)
		{
			//��������ʱִ�еĺ�����ʹ��reuse����������placement-new��Ϊ�˸����
			//�������ú͹���ʱͨ����������ͬ��Ϊ������ͨ��ֻ���������ĳ�ʼ������
			KOP_ReUse(*(m_ppFreeList[m_nIndex]));
			return m_ppFreeList[m_nIndex++];
		}
		_WARNING(!"Object pool overflow!");
		return NULL;	//����һ���յķ�����
	}
	//�黹�ͷŶ���
	inline VOID Free(T* p)
	{
		if(m_nIndex > 0)
		{
			m_ppFreeList[--m_nIndex] = p;
			KOP_UnUse(*(m_ppFreeList[m_nIndex]));
		}
		else
		{
			_WARNING(!"Wrong releasing!");
		}
	}
	~KObjPool()
	{
		if (m_pObject)
			delete[] m_pObject;
		if (m_ppFreeList)
			delete[] m_ppFreeList;
	}
protected:
	T* m_pObject;	//�ڴ��׵�ַ
	T** m_ppFreeList;	//���ñ�
	INT m_nMaxSize;
	INT	m_nIndex;
};

/*-------------------------------------------------------------------------------
//���ƣ�����ʽ�������
//���ܣ�����ء������õķ�ʽʵ�ֶ������������ͷ�
//���ԣ�Ԥ���䣬������
//Ӧ�ó��ϣ���֤���ظ��ͷźͲ����ͷŲ��Ǹ��ڴ�ط�������Ķ���
//------------------------------------------------------------------------------*/
template <class T>
class KIncObjPool
{
public:
	KIncObjPool()
	{
		m_pCurPage = NULL;
		m_nIncSize = m_nCurFree = 0;
	}
	//������Ԥ����ҳ��С������ҳ��С
	VOID Init(INT nSize, INT nIncSize)
	{
		m_pCurPage = new T[nSize];
		m_nIncSize = nIncSize;
		m_nCurFree = nSize;
	}
	//�Ӷ���ػ�ȡ����
	T* New()
	{
		T* p = NULL;
		if (!m_vecRecycle.empty())
		{
			p = m_vecRecycle.back();
			m_vecRecycle.pop_back();
			return p;
		}
		else
		{
			if (m_nCurFree <= 0)	// �����ǰ��ҳ�����꣬�·���һ��Incҳ
			{
				m_vecPage.push_back(m_pCurPage);
				m_pCurPage = new T[m_nCurFree = m_nIncSize];
			}
			p = &m_pCurPage[--m_nCurFree];
		}
		//��������ʱִ�еĺ�����ʹ��reuse����������placement-new��Ϊ�˸����
		//�������ú͹���ʱͨ����������ͬ��Ϊ������ͨ��ֻ���������ĳ�ʼ������
		KOP_ReUse(*p);
		return p;
	}

	//�黹�ͷŶ���
	VOID Free(T* p)
	{
		KOP_UnUse(*p);
		m_vecRecycle.push_back(p);
	}

	~KIncObjPool()
	{
		if (m_pCurPage)
			delete[] m_pCurPage;
		for (size_t i = 0; i < m_vecPage.size(); ++i)
		{
			delete[] m_vecPage[i];
		}
	}
protected:
	T* m_pCurPage;	// ��ǰ�ɷ�����ڴ�ҳ
	INT m_nIncSize; // ����ҳ�Ĵ�С
	INT	m_nCurFree;	// ��ǰ�ɷ���ҳʣ�����
	std::vector<T*> m_vecRecycle;	// ���յĿ��ж���
	std::vector<T*> m_vecPage;	// �ѷ����ҳ
};

/*-------------------------------------------------------------------------------
//���ƣ���̬�����Ч�ڴ����
//���ܣ�ʹ��ID�������ȳ��ڴ�黺��ʽ�ڴ�ء�ʵ�ֵȳ��ڴ�Ŀ���������ͷţ�����ϵͳ�����ڴ���Ƭ
//���ԣ��������飬�пռ����䣬���ظ��ͷż�飬���̰߳�ȫ������ʹ�����ڴ�飬���ڴ�
		��ռ䲻��ʱʹ�ø����ڴ�飬��KObjPoolҪ��Щ
//Ӧ�ó��ϣ�û��ȷ�����ڴ�ʹ�÷�ֵ��ʹ��Index������ͷ��ڴ����ȷ�������ظ��ͷ�
//------------------------------------------------------------------------------*/
template<class T>
class KIncObjPool1	//��һ�࣬������ID��ID���ⲿ�ṩ��ID�����Ƕ�������ֵ
{
public:
	KIncObjPool1()
	{
		pObject = NULL;
		m_nIncSize = 256;
		m_nMaxIndex = 0;
	}
	~KIncObjPool1()
	{
		if (pObject)
			delete[] pObject;
		for (typename std::vector<T*>::iterator it = m_vecPObject.begin(); it != m_vecPObject.end(); ++it)
		{
			if (*it)
				delete [] (*it);
		}
	}
	//������Ԥ�����С������
	BOOL Init(INT nMaxSize, INT nIncSize)
	{
		m_nIncSize = nIncSize;
		if (m_nIncSize <= 0 )
		{
			ASSERT(FALSE);
			m_nIncSize = 256;
		}
		pObject = new T[nMaxSize];
		m_nMaxSize = nMaxSize;
		return pObject != NULL;
	}
	//�Ӷ���ػ�ȡ����
	T* New(INT nIndex)
	{
		if (!pObject || nIndex < 0)
		{
			ASSERT(FALSE);
			return NULL;
		}
		T *pRet;
		if (nIndex < m_nMaxSize)
		{
			pRet = pObject + nIndex;
		}
		else 
		{
			INT nIncIndex =  nIndex - m_nMaxSize;
			INT a = nIncIndex / m_nIncSize;
			INT b = nIncIndex % m_nIncSize;
			/*
			INT a,b;
			_asm{	//nIndex/m_nIncSize�̺������ֱ����a,b
					mov eax, nIndex
					mov ecx, m_nIncSize
					cdq
					idiv ecx
					mov a, eax
					mov b, edx
			}
			*/
			if ((size_t)a < m_vecPObject.size())
			{
				pRet = m_vecPObject[a] + b;
			}
			else if((size_t)a == m_vecPObject.size())
			{
				pRet = new T[m_nIncSize];
				if (!pRet)
				{
					ASSERT(FALSE);
					return NULL;
				}
				m_vecPObject.push_back(pRet);
				pRet += b;
			}
			else	//����һ��IncSize��������
			{
				ASSERT(FALSE);
				return NULL;
			}
		}
		KOP_ReUse(*pRet);
		if (nIndex > m_nMaxIndex)
			m_nMaxIndex = nIndex;
		return pRet;
	}
	//�黹�ͷŶ���
	VOID Free(INT nIndex)
	{
		if(nIndex < m_nMaxSize)	//�������ڴ��
		{
			KOP_UnUse(*(pObject + nIndex));
		}
		else
		{
			nIndex -= m_nMaxSize;
			KOP_UnUse(*(m_vecPObject[nIndex / m_nIncSize] + nIndex % m_nIncSize));
		}
	}
	T *GetObject(INT nIndex)
	{
		if (nIndex < 0 || nIndex > m_nMaxIndex)
		{
			ASSERT(FALSE);
			return NULL;
		}
		if (nIndex < m_nMaxSize)
			return pObject + nIndex;
		nIndex -= m_nMaxSize;
		INT a = nIndex / m_nIncSize;
		INT b = nIndex % m_nIncSize;
		/*
		INT a,b;
		_asm{	//nIndex/m_nIncSize�̺������ֱ����a,b
			mov eax, nIndex
			mov ecx, m_nIncSize
			cdq
			idiv ecx
			mov a, eax
			mov b, edx
		}
		*/
		if ((size_t)a >= m_vecPObject.size())
		{
			ASSERT(FALSE);
			return NULL;
		}
		return m_vecPObject[a] + b;
	};
	//��ȡ��������
	UINT GetIncBlockCount() { return (UINT)m_vecPObject.size(); }
	//��ȡnew�������id
	INT GetPeakValue()
	{
		return m_nMaxIndex;
	}
protected:
	T* pObject;	//�ڴ��׵�ַ
	INT m_nMaxSize; //���ڴ���С
	INT	m_nIncSize; //�����ڴ��ÿ����С
	INT m_nMaxIndex; //��ǰ����ڴ�id
	std::vector<T*> m_vecPObject;
};

template<class T>
class KIncObjPool2 :  private KIncObjPool1<T> //�ڶ��࣬�������ID
{
public:
	KIncObjPool2() { m_IDGenerator = 1; }
	//������Ԥ�����С������
	BOOL Init(INT nMaxSize, INT nIncSize)
	{
		m_IDGenerator = 1;	//��1��ʼ
		m_vecFreeID.reserve(nMaxSize);
		return KIncObjPool1<T>::Init(nMaxSize, nIncSize);
	}
	INT GenNewID()
	{
		if (m_vecFreeID.size() > 0)
		{
			INT nRet = m_vecFreeID.back();
			m_vecFreeID.pop_back();
			return nRet;
		}
		return m_IDGenerator++;
	}
	BOOL FreeID(INT nIndex)
	{
		if (nIndex < 0 || nIndex >= m_IDGenerator)
		{
			ASSERT(FALSE);
			return FALSE;
		}
		m_vecFreeID.push_back(nIndex);
		return TRUE;
	}
	T* New(LPINT pID)
	{
		INT nNewID = GenNewID();
		if (pID)
			*pID = nNewID;
		return KIncObjPool1<T>::New(nNewID);
	}
	VOID Free(INT nIndex)
	{
		if (FreeID(nIndex))
			KIncObjPool1<T>::Free(nIndex);
	}
	T *GetObject(INT nIndex)
	{
		if (nIndex <= 0)
		{
			ASSERT(FALSE);
			return NULL;
		}
		return KIncObjPool1<T>::GetObject(nIndex);
	}
	//��ȡ�ڴ�ʹ�÷�ֵ�����ʹ�ö�������
	INT GetPeakValue()
	{
		return m_IDGenerator - 1;
	}
	//��ȡ���п����ö�����
	INT GetFreeCount()
	{
		return (INT)m_vecFreeID.size();
	}
	UINT GetIncBlockCount()
	{
		return KIncObjPool1<T>::GetIncBlockCount();
	}
protected:
	std::vector<INT>	m_vecFreeID;
	INT					m_IDGenerator;
};


/*-------------------------------------------------------------------------------
//���ƣ���̬����ʽ�ڴ����
//���ܣ��ȳ��ڴ���ڴ�ء������õķ�ʽʵ�ֵȳ��ڴ�Ŀ���������ͷ�
//���ԣ���Ԥ���䣬�ͷŵĶ����ڴ棩���黹ϵͳ���������ã����޿������ڴ�����ϵͳ����
//Ӧ�ó��ϣ���֤���ظ��ͷźͲ����ͷŲ���new�������ڴ�
//------------------------------------------------------------------------------*/
template<class T>
class KDynReUseObjectPool
{
public:
	~KDynReUseObjectPool()
	{
		typename std::vector<T*>::iterator itPObject;
		for (itPObject = m_vecFreePObject.begin(); itPObject != m_vecFreePObject.end(); ++itPObject)
		{
			if (*itPObject)
				delete (*itPObject);
		}
	}
	T *New()
	{
		if (m_vecFreePObject.size() <= 0)
			return new T;
		T *pRet = m_vecFreePObject.back();
		KOP_ReUse(*pRet);
		m_vecFreePObject.pop_back();
		return pRet;
	}
	VOID Free(T *p)
	{
		KOP_UnUse(*p);
		m_vecFreePObject.push_back(p);
	}
protected:
	std::vector<T*> m_vecFreePObject;
};

/*-------------------------------------------------------------------------------
//���ƣ�Ԫ�ط�����
//���ܣ���ֵ����Ķ����
//���ԣ�����ͻ���Ԫ��ֵ�����Ƕ���ָ��
//Ӧ�ó��ϣ������÷���ID����
//------------------------------------------------------------------------------*/
template<typename TElement>
class TElementAssignPool
{
public:
	TElementAssignPool() : m_pFreeElement(NULL), m_nUseNum(0), m_nMaxNum(0) {}
	//�õ�һ������Ԫ��
	TElement GetFree() 
	{ 
		if (m_nUseNum >= m_nMaxNum)
		{
			Q_Error("Overflowed!");
			return TElement(0);
		}
		return m_pFreeElement[m_nUseNum++]; 
	};
	//�ͷ�һ��Ԫ��
	VOID Release(TElement elem) 
	{ 
		if (m_nUseNum <= 0)
		{
			Q_Error("");
			return;
		}	
		m_pFreeElement[--m_nUseNum] = elem;
	}
	//��ʼ������������Ԫ��ֵ
	template<class FnElementAssign> inline
		VOID Init_AssignElement(INT nMaxNum, FnElementAssign _fn)
	{
		m_pFreeElement = new TElement[nMaxNum];
		m_nMaxNum = nMaxNum;
		_fn(m_pFreeElement, nMaxNum);
		m_nUseNum = 0;
	}

protected:
	TElement*			m_pFreeElement;					//��������
	UINT				m_nUseNum;						//������������ID��ʼ������	
	UINT				m_nMaxNum;						//��������
};

// -------------------------------------------------------------------------
