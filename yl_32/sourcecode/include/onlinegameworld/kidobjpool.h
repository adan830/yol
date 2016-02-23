/* -------------------------------------------------------------------------
//	�ļ���		��	kidobjpool.h
//	������		��	simon
//	����ʱ��	��	2009/11/21 15:57:01
//	��������	��	Id�����
//
// -----------------------------------------------------------------------*/
#ifndef __KIDOBJPOOL_H__
#define __KIDOBJPOOL_H__

#include <map>
#include "Misc/qidpool.h"
#include "onlinegameworld/kbaseobject.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// -------------------------------------------------------------------------

// T�����KBaseObject�̳л���m_dwId public��Ա
template<class T, DWORD dwIdMask = 0>
class TKIdObjPool
{
public:
	TKIdObjPool(void);
	virtual ~TKIdObjPool(void);

public:
	virtual BOOL	Init(INT nMaxCount);
	virtual BOOL	Uninit();

	// ��Ӷ���ʧ�ܷ���0
	virtual INT		Add(DWORD dwId = KD_BAD_ID);
	virtual BOOL	Remove(DWORD dwId);
	virtual BOOL	RemoveByIndex(INT nIndex);

	// ��ȡ����ָ�룬ʧ�ܷ���NULL
	virtual T* GetByIndex(INT nIndex);
	virtual T* GetById(DWORD dwId);

	// ͨ��Id��ȡ�����Index(��ЧID��IndexΪ0)
	INT GetIndexById(DWORD dwId);

	// ��ȡ����Ķ�������
	INT GetMaxCount()
	{ return m_cIdPool.GetMaxNum(); }

	// ��ȡ��ǰʹ������
	INT GetUsedCount()
	{ return m_cIdPool.GetUsedCount(); }

	INT NextUsedIndex(INT nLastIdx)
	{ return m_cIdPool.GetNextUsedId(nLastIdx); }

	VOID	SetIdMask(DWORD dwIM)
	{ m_dwIdMask = dwIM; }

protected:
	T*						m_pObjects;
	QIdPool					m_cIdPool;			// ����index������
	std::map<DWORD, INT>	m_mapId2Index;		// ID��Indexӳ��
	DWORD					m_dwIdMask;
	DWORD					m_dwIdGenerator;	// ID����
private:
};

template<class T, DWORD dwIdMask>
TKIdObjPool<T, dwIdMask>::TKIdObjPool()
{
	m_pObjects = NULL;
	m_dwIdMask = dwIdMask;
	m_dwIdGenerator = 0;
}

template<class T, DWORD dwIdMask>
TKIdObjPool<T, dwIdMask>::~TKIdObjPool(void)
{
}

template<class T, DWORD dwIdMask>
T* TKIdObjPool<T, dwIdMask>::GetByIndex( INT nIndex )
{
	if (nIndex <= 0 || nIndex > m_cIdPool.GetMaxNum())
		return NULL;

	return &m_pObjects[nIndex];
}

template<class T, DWORD dwIdMask>
T* TKIdObjPool<T, dwIdMask>::GetById( DWORD dwId )
{
	std::map<DWORD, INT>::const_iterator it = m_mapId2Index.find(dwId);
	if (it == m_mapId2Index.end())
		return NULL;

	INT nIndex = it->second;
	QCONFIRM_RET_NULL(nIndex > 0 && nIndex <= m_cIdPool.GetMaxNum());

	return &m_pObjects[nIndex];
}

template<class T, DWORD dwIdMask>
INT TKIdObjPool<T, dwIdMask>::GetIndexById(DWORD dwId)
{
	std::map<DWORD, INT>::const_iterator it = m_mapId2Index.find(dwId);
	if (it == m_mapId2Index.end())
	{
		return 0;
	}
	else
	{
		return m_mapId2Index[dwId];
	}
}

template<class T, DWORD dwIdMask>
BOOL TKIdObjPool<T, dwIdMask>::Remove( DWORD dwId )
{
	std::map<DWORD, INT>::const_iterator it = m_mapId2Index.find(dwId);
	if (it != m_mapId2Index.end() && it->second > 0 && it->second <= m_cIdPool.GetMaxNum())
	{
		m_cIdPool.Delete(it->second);
	}
	m_mapId2Index.erase(dwId);
	return TRUE;
}


template<class T, DWORD dwIdMask>
BOOL TKIdObjPool<T, dwIdMask>::RemoveByIndex( INT nIndex )
{
	// Խ��
	if (nIndex <= 0 || nIndex > m_cIdPool.GetMaxNum())
		return FALSE;
	//KBaseObject* pObject = static_cast<KBaseObject*>(&m_pObjects[nIndex]);
	T* pObject = &m_pObjects[nIndex];
	m_mapId2Index.erase(pObject->m_dwId);
	return m_cIdPool.Delete(nIndex);
}

template<class T, DWORD dwIdMask>
INT TKIdObjPool<T, dwIdMask>::Add(DWORD dwId /* = KD_BAD_ID */)
{
	// ����
	if (m_cIdPool.GetUsedCount() >= m_cIdPool.GetMaxNum())
	{
		Q_Error("Too many Objects!");
		return 0;
	}

	INT nIndex = m_cIdPool.New();
	if (nIndex <= 0)
	{
		Q_Error("Can't allocate index from IdPool!");
		return 0;
	}

	T* pObj = &m_pObjects[nIndex];

	if (pObj)
	{
		if (KD_BAD_ID == dwId)
		{
			dwId = m_dwIdGenerator++;
			dwId |= m_dwIdMask;
		}

		pObj->m_dwId = dwId;
		//static_cast<KBaseObject*>(pObj)->m_dwId = dwId;

		// ����ID->Indexӳ��
		m_mapId2Index[dwId] = nIndex;
	}

	return nIndex;
}

template<class T, DWORD dwIdMask>
BOOL TKIdObjPool<T, dwIdMask>::Init( INT nMaxCount )
{
	// ��ʼ����������
	m_pObjects = new T[nMaxCount + 1];
	QCONFIRM_RET_FALSE(m_pObjects);

	// ��ʼ����������
	m_cIdPool.Init(nMaxCount);

	m_dwIdGenerator = 1;

	return TRUE;
}

template<class T, DWORD dwIdMask>
BOOL TKIdObjPool<T, dwIdMask>::Uninit()
{
	SAFE_DELETE_ARRAY(m_pObjects);
	m_cIdPool.Uninit();
	m_mapId2Index.clear();

	return TRUE;
}

// -------------------------------------------------------------------------

#endif /* __KIDOBJPOOL_H__ */
