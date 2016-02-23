/* -------------------------------------------------------------------------
//	�ļ���		��	kmailbox.h
//	������		��	xiewenzhe
//	����ʱ��	��	2011/5/16 17:54:08
//	��������	��	����
//
// -----------------------------------------------------------------------*/
#ifndef __KMAILBOX_H__
#define __KMAILBOX_H__

// -------------------------------------------------------------------------
#ifdef GAME_CENTER

#include "kmail.h"
#include <map>

class IKEnumMail
{
public:
	virtual BOOL NextMail(KMail **ppMail) = 0;
	virtual BOOL Reset() = 0;
	virtual INT GetCount() = 0;
};

class KEnumMail : public IKEnumMail
{
public:
	KEnumMail() : m_pMap(NULL)
	{
	}
	virtual ~KEnumMail()
	{
	}
	BOOL Init(std::map<INT64, KMail*> *pMap)
	{
		QCONFIRM_RET_FALSE(pMap);
		m_pMap = pMap;
		m_iter = pMap->begin();
		return TRUE;
	}
	virtual BOOL NextMail(KMail **ppMail)
	{
		QCONFIRM_RET_FALSE(ppMail && m_pMap);
		if (m_iter == m_pMap->end())
			return FALSE;
		*ppMail = m_iter->second;
		m_iter++;
		return TRUE;
	}
	virtual BOOL Reset()
	{
		QCONFIRM_RET_FALSE(m_pMap);
		m_iter = m_pMap->begin();
		return TRUE;
	}
	virtual INT GetCount()
	{
		QCONFIRM_RET(m_pMap, 0);
		return (INT)m_pMap->size();
	}
private:
	std::map<INT64, KMail*>*			m_pMap;
	std::map<INT64, KMail*>::iterator	m_iter;
};

class KMailBox
{
public:
	KMailBox();
	~KMailBox();
	VOID Init(DWORD dwOwnerId, INT nTime);
	VOID UnInit();
	BOOL CreateMail(KMAIL_INFO *pData, KMail **ppMail = NULL);
	BOOL DeleteMail(INT64 nMailID);
	BOOL GetAllMail(IKEnumMail **ppEnum);
	BOOL LoadMail(CONST KMAIL_INFO *pData, KMail **ppMail = NULL);
	KMail *FindMail(INT64 nMailID);
	VOID Save();
	BOOL Save(INT64 nMailID);
	BOOL Save(KMail *pMail);
	BOOL Clear();

	BOOL GetInitTime();

private:
	std::map<INT64, KMail*>	m_mapMail;		// ���ʼ�IDΪ����
	KEnumMail				m_enumMail;		// �ʼ�ö����
	BOOL					m_bLoaded;		// �ʼ��Ƿ��Ѿ��������
	DWORD					m_dwOwnerId;	// ����������Id
	INT						m_nInitTime;	// �����ʼʹ��ʱ��
};

#endif /* GAME_CENTER */
// -------------------------------------------------------------------------

#endif /* __KMAILBOX_H__ */
