
#ifndef __KITEMMGR_H__
#define __KITEMMGR_H__

#include "itemenv_i.h"
#include "kitem.h"
#include "kdupeditemdeal.h"
#include "kitemsetting.h"
#include "Misc/qindexlist.h"
#include "kitemgenerator.h"
#include "kplayeritem.h"
#include <map>
#include "onlinegameworld/kgcmodulebase.h"


// ��Ʒ���ķ�ʽ
enum KE_ITEM_CONSUMEMODE
{
	emITEM_CONSUMEMODE_NORMAL = 0,

	emITEM_CONSUMEMODE_REALCONSUME_START,								// ��ʵ����

	emITEM_CONSUMEMODE_SELL = emITEM_CONSUMEMODE_REALCONSUME_START,		// ���̵�
	emITEM_CONSUMEMODE_ENCHASER,										// װ������
	emITEM_CONSUMEMODE_USINGTIMESEND,									// ʹ�ô�������
	emITEM_CONSUMEMODE_USINGTIMEOUT,									// ʹ��ʱ�䵽
	emITEM_CONSUMEMODE_EXPIREDTIMEOUT,									// ��ֵ�ڵ�
	emITEM_CONSUMEMODE_EAT_QUICK,										// ͨ���Ҽ����ݼ�ʹ��(�Ե�)
	emITEM_CONSUMEMODE_EAT,												// ͨ���ű�ʹ��(�Ե�)
	emITEM_CONSUMEMODE_CONSUME,											// ͨ���ű�����
	emITEM_CONSUMEMODE_ERRORLOST_STACK,									// ����Ʒ�����쳣ɾ��
	emITEM_CONSUMEMODE_PICKUP,											// ������ʧ
	emITEM_CONSUMEMODE_COMMONSCRIPT,									// ͨ��ͨ�ýű�ɾ��
	emITEM_CONSUMEMODE_DUPEDITEM,										// ����Ʒ����ɾ��
	emITEM_CONSUMEMODE_ERRORLOST_PK,									// ��PKԭ��ʧ���쳣ɾ��
	emITEM_CONSUMEMODE_ERRORLOST_THROWALLITEM,							// ����Ʒ�����ϣ��쳣ɾ��
	emITEM_CONSUMEMODE_ERRORLOST_ADDONBODY,								// �������������Ʒʧ�ܣ��쳣ɾ��
	emITEM_CONSUMEMODE_REALCONSUME_END = emITEM_CONSUMEMODE_ERRORLOST_ADDONBODY,	// ��������

	emITEM_CONSUMEMODE_STACK,											// ����Ʒ����
};

enum KE_ITEM_DATARECORD_WAY
{
	emITEM_DATARECORD_NORMAL,			// Ĭ��;��������¼
	emITEM_DATARECORD_SYSTEMADD,		// ϵͳ����(ϵͳ���䡢�������, ���������)
	emITEM_DATARECORD_ROLLOUT,			// ��ֵ��ת�����(����װ��������ͬ�飬�������)
	emITEM_DATARECORD_ROLLIN,			// ��ֵ��ת��ɾ��(ǿ��װ����ιͬ�飬�����ϳ�)
	emITEM_DATARECORD_REMOVE,			// ������ɾ��(���������ơ���Ʒ����Ʒ�ڵ���ϵͳ���գ��ڻع��������������߶һ�)
};

// -------------------------------------------------------------------------
// KItemMgr

class KItemMgr : public KModuleBase
{
// ���Ͷ���

private:

	struct KPARAM
	{
		INT		nGenre;
		INT		nDetail;
		INT		nParticular;
		INT		nLevel;
		INT		nEnhTimes;
		UINT	uRandSeed;
		UINT	uRandSeedEx;
	};

	struct KDATARECORD
	{
		CHAR szKey[MAX_NAME_LEN];	// ��ʽΪG_D_P
		BOOL bConsume;
		BOOL bAdd;
	};
// �ӿڷ���ʵ��

public:
	LPCSTR	GetName() CONST	{ return "Item"; }

	virtual BOOL OnInit();
	virtual BOOL OnUnInit();

	virtual BOOL ProcessProtocol(INT nPlayerIndex, LPCBYTE pbData, UINT uDataLen);

	virtual BOOL InitProtocol();

	virtual BOOL Breath() { return TRUE; }

// ��Ա��������

public:

	KItemMgr();

	INT		Add(
		CONST KITEM_INDEX&		sIdx,
		INT						nEnhTimes,
		KE_ITEM_DATARECORD_WAY	eWay,
		CONST KItem::KSTONE_INFO*	pStoneInfo	= NULL,
		CONST KMagicAttrib*		pAppendAttr = NULL,
		UINT					uRandomSeed	= 0,
		UINT					uRandomSeedEx	= 0,
		IItemEnv*				pEnv		= NULL)
	{
		return Add(
			sIdx.nGenre,
			sIdx.nDetailType,
			sIdx.nParticular,
			sIdx.nLevel,
			nEnhTimes,
			eWay,
			pStoneInfo,
			pAppendAttr,
			uRandomSeed,
			uRandomSeedEx,
			pEnv
		);
	}

	INT		Add(
		INT						nItemGenre,
		INT						nDetailType,
		INT						nParticularType,
		INT						nLevel,
		INT						nEnhTimes,
		KE_ITEM_DATARECORD_WAY	eWay,
		CONST KItem::KSTONE_INFO* pStoneInfo = NULL,
		CONST KMagicAttrib*		pAppendAttr = NULL,
		UINT					uRandomSeed	= 0,
		UINT					uRandomSeedEx = 0,
		IItemEnv*				pEnv		= NULL
	);

	INT		Add(KItem* pcItem);				// �����е��߸���һ���µĵ���
	BOOL	Remove(INT nIdx, KE_ITEM_DATARECORD_WAY eRecord = emITEM_DATARECORD_NORMAL, KE_ITEM_CONSUMEMODE eConsumeMode = emITEM_CONSUMEMODE_NORMAL, 
						KPlayer* pPlayer = NULL, BOOL bEraseInMap = TRUE);
	VOID	RemoveAll(VOID);
	INT		GetItemCount(VOID)		{ return m_cIdxList.GetCount(); }
	INT		SearchID(DWORD dwID) CONST;
	KItemGenerator* GetGenerator(INT nVersion = 0) CONST;

	//VOID RegistLimitUse(QLuaScript& sc);
	VOID RegistLimitUse(LPCSTR szForbidType, KPlayerItem::KE_LIMITUSE_TYPE eType, LPCSTR szMap, INT bRegister);

#ifdef GAME_SERVER
	INT		Add(
		CONST KItem*			pcItem, 
		INT						nPlayerIndex,
		DupedDef::OP_LEVEL		dupedOpLevel, 
		DupedDef::OP_RESULT&	dupedRet, 
		IItemEnv*				pcEnv = NULL
	);
#else
	BOOL	IsUnknownItem(INT nVersion, KITEM_INDEX sIndex);			// ����Ƿ��ǿͻ���δ֪�ĵ���
#endif

private:

	VOID	SetID(INT nIdx);
	INT		FindFree(VOID) CONST	{ return m_cIdxList.FindFree(); }
	INT		Add_Impl(CONST KPARAM& rsParam,
					CONST KItem::KSTONE_INFO* pStoneInfo,
					CONST KMagicAttrib* pAppendAttr,
					INT nExtParamMask = 0);

#ifdef GAME_SERVER
	INT		Add_Impl(CONST KItem* pcItem, INT nPlayerIndex, DupedDef::OP_LEVEL dupedOpLevel, DupedDef::OP_RESULT& dupedRet);
	BOOL	CanLogThisItem(KItem* pcItem);		// �Ƿ���Ҫ��¼�������־
#endif

// ��Ա���ݶ���

public:

	KItemSetting	m_cSetting;			// ��Ʒ����
#ifdef GAME_SERVER
	std::map<std::string, KDATARECORD*> m_mpDataRecordList;	//��Ҫ��¼�������ĵ�����Ϣ�б�
#endif
	std::map<DWORD, INT> m_mpIdToIdx;	// �������ߵ�ID��ֵ�����ߵ�����,���map������һ��Ҫ��m_)cIdxList������ͬ������Ȼ��������
	
	typedef std::map<std::string, INT> KMP_DATA;
	struct KLIMITUSE_DATA
	{
		KMP_DATA mpData;
		CHAR szProperMap[32];
	};

	typedef std::map<KPlayerItem::KE_LIMITUSE_TYPE, KMP_DATA> KMP_LIMITUSE;
	std::map<std::string, KMP_LIMITUSE> m_mpLimitUseData;

	typedef std::map<KPlayerItem::KE_LIMIT_PRIORITY, KPlayerItem::vecLimitUseRule> mapLimitPriority;
	mapLimitPriority m_mpLimitPri;

private:

	DWORD			m_dwIDCreator;		// ID�����������ڿͻ�����������˵Ľ���
	QIndexList		m_cIdxList;			// ������
	KItemGenerator*	m_pItemGen;			// ��������������

#ifdef GAME_SERVER
	KDupedItemDeal	m_dupedItemDeal;	// �Ը���װ���Ĵ���
	INT				m_nLastIdentity;	// ��һ��ʹ�õ���Ʒ��ˮ��
#endif

};

// -------------------------------------------------------------------------

extern KItemMgr	g_cItemMgr;
extern QLogFile	g_ItemLogFile;

// -------------------------------------------------------------------------

#endif /* __KITEMMGR_H__ */
