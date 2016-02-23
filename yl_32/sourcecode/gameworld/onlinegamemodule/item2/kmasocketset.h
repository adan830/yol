
#ifndef __KMASOCKETSET_H__
#define __KMASOCKETSET_H__

#include "klibofbpt.h"

//---------------------------------------------------------------------------
// KMASocketSet��ϵ		ħ�����飬��¼һ����ص�ħ�����ԣ��������Լ���ϵͳ��

class KMASocketSet							// �������
{

public:

	struct KSOCKET							// ħ���׽ṹ
	{
		KMagicAttrib	sMagicAttrib;		// ħ������
		BOOL			bActive;			// �Ƿ񱻼���
		BOOL			bVisible;			// �Ƿ�ɼ�
	};

	explicit KMASocketSet(INT nCount);
	virtual ~KMASocketSet();

	virtual KMASocketSet &operator = (CONST KMASocketSet &cMASS);
	virtual	BOOL Init(VOID);				// ��ʼ��ħ������
	virtual BOOL Reset(VOID);				// �������ħ������

	INT		GetCount(VOID) CONST { return m_nCount; }
	CONST	KMagicAttrib* GetMagicAttrib(INT nIndex) CONST;
	BOOL	IsActive(INT nIndex) CONST;
	BOOL	IsVisible(INT nIndex) CONST;
	VOID	UpdateState(INT nPlayerIdx = 0, BOOL bActive = FALSE);	// idxPlayer��װ���˸�װ���Ľ�ɫ������Ϊ0��ʾ��װ��û��װ������ɫ���ϣ�bActive �Ƿ�ǿ�Ƽ���

protected:

	KSOCKET* CONST	m_pSocket;				// ħ��������
	CONST INT		m_nCount;				// ħ��������
	BOOL			m_bInit;				// �Ƿ��Ѿ���ʼ��

	virtual	VOID Update(INT nPlayerIdx, BOOL bActive = FALSE) = 0;

	BOOL	PreAssign(CONST KMASocketSet& cMASS);
	BOOL	ClearSocket(INT nIndex);

};

class KMASS_Item : public KMASocketSet		// Ӧ����Item��ħ���������
{
	friend class KItem;

public:
	KMASS_Item(KItem& cItem, INT nCount);
	virtual ~KMASS_Item() {}

	virtual KMASS_Item &operator = (CONST KMASS_Item& cMASS);
	virtual	BOOL Init(VOID);

protected:
	KItem* CONST	m_pItem;				// ��������
	virtual	VOID Update(INT nPlayerIdx, BOOL bActive = FALSE);
};

class KMASS_Random : public KMASS_Item		// ����װ�����ħ������
{
public:
	explicit KMASS_Random(KItem &cItem);
	virtual ~KMASS_Random() {}

	virtual	BOOL Init(VOID);

protected:
	virtual	VOID Update(INT nPlayerIdx = 0, BOOL bActive = FALSE);
};

class KMASS_Enhance : public KMASS_Item		// ����װ��ǿ����������
{
public:
	explicit KMASS_Enhance(KItem &cItem);
	virtual ~KMASS_Enhance() {}

	INT GetTimes(INT nIndex) CONST;
	virtual	BOOL Init(VOID);
	virtual BOOL Reset(VOID);

protected:
	CONST KBPT_EQUIP_ENHMA*	m_pBPT;
	virtual	VOID Update(INT nPlayerIdx = 0, BOOL bActive = FALSE);
};

class KMASS_Suite : public KMASocketSet		// ����װ����װ��������
{
public:
	typedef std::vector<KITEM_INDEX> KItemVec;

public:
	KMASS_Suite(CONST KSUITE_INFO& sSuiteInfo, KE_SUITE_TYPE eSuiteType);
	virtual ~KMASS_Suite() {}

	INT		GetSuiteID(VOID) CONST { return m_pSuiteInfo->pInfo->nSuiteID; }
	CONST	KItemVec& GetSuiteParts(INT nEquipType) CONST;
#ifndef GAME_SERVER
	PCSTR	GetSuiteName(VOID) CONST { return m_pSuiteInfo->pInfo->szName; }
#endif

protected:
	CONST KSUITE_INFO*	m_pSuiteInfo;
	KE_SUITE_TYPE		m_eType;

	virtual	VOID Update(INT nPlayerIdx = 0, BOOL bActive = FALSE);
};

class KMASS_Strengthen : public KMASS_Item		// ����װ����������
{
public:
	explicit KMASS_Strengthen(KItem &cItem);
	virtual ~KMASS_Strengthen() {}

	INT GetTimes(INT nIndex) CONST;
	virtual	BOOL Init(VOID);
	virtual BOOL Reset(VOID);

protected:
	CONST KBPT_EQUIP_ENHMA*	m_pBPT;
	virtual	VOID Update(INT nPlayerIdx = 0, BOOL bActive = FALSE);
};


// -------------------------------------------------------------------------

extern VOID g_PushMagicAttribAsTable(QLuaScript &sc, CONST KMagicAttrib *pMA);
extern VOID g_PushMASSAsTable(QLuaScript &sc, CONST KMASocketSet &cMASS);

// -------------------------------------------------------------------------

#endif /* __KMASOCKETSET_H__ */
