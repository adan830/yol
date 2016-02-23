
#pragma once

#include "kgoods.h"
#include <map>

// ע�⣺��ö�ٲ��������
enum KE_SERIES_TYPE
{
	series_none		= 0,				// ��ϵ
	series_metal	= 1,				// ��ϵ
	series_wood		= 2,				// ľϵ
	series_water	= 3,				// ˮϵ
	series_fire		= 4,				// ��ϵ
	series_earth	= 5,				// ��ϵ
	series_num,
};

class KBuySellSetting
{

public:
	enum
	{
		emMAX_ITEMCOUNT = 150,
	};
	KBuySellSetting();
	~KBuySellSetting();

	BOOL	Init();
	BOOL	Release();
	//KGoods* GetGoodsByItemIdx(CONST KITEM_INDEX& crItemIdx);
	//KGoods* GetGoods(LPCSTR pszItemName);
	//KGoods* GetGoods(INT nId);
	//INT		GetGoodsIndex(INT nShop, INT nIndex);
	//INT		GetWidth() CONST	{ return m_nWidth; }
	//INT		GetHeight() CONST	{ return m_nHeight; }

#ifdef GAME_SERVER
	INT		ItemBusinessShopName2ID(LPSTR pszName);
#else
	// �����Ʒ�ڶ�Ӧ�̵��е�λ��
	INT	 GetGoodsShopIdx(INT nGoodsId);
#endif

private:

	typedef std::map<std::string, INT>	MAP_GOODSNAME2INDEX;
	typedef std::map<INT, LPINT>		KShopGoodsMap;
	typedef std::map<INT, KGoods>		KGoodsMap;

	MAP_GOODSNAME2INDEX	m_mapGoodsName;		// ����-�±�������Ӧ��
	KGoodsMap			m_mapGoods;			// ��Ʒ��
	KShopGoodsMap		m_mapShopGoods;
	INT					m_nWidth;			// �̵�ģ��������Ʒ������ӦBuysell.txt��������
	INT					m_nHeight;			// �̵�ģ��ĸ�������Ӧg_cBuySellMgr.txt��������1��g_cBuySellMgr.txt����1��������

#ifdef GAME_SERVER
	QTabFile			m_tabItemShop;			
#endif

public:
	BOOL TryGetDateTime(ITabFile* pTabFile, INT nRowIdx, LPCSTR pszColName, time_t &t);
	BOOL TryParseTime(LPCSTR pszTime, time_t& t);

public:
	BOOL ReadShopCfg();
	BOOL ClearShopMap();

	KGoods* GetGoodsByGDPL(CONST KITEM_INDEX& crItemIdx);
	KGoods* GetGoodsByIndex(INT nShopIndex, INT nCategoryIndex, INT nGoodsIndex);
	//KGoodsVec* GetGoodsVecByIndex(INT nShopIndex, INT nCategoryIndex);
public:
	typedef std::vector<KGoods*>		KGoodsVec;
	typedef std::map<INT, KGoodsVec*>	KCategoryMap;
	typedef std::map<INT, KCategoryMap*> KShopMap;
private:
	KShopMap m_mapShop;
};


