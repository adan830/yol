
#pragma once

#include <string>
#include <time.h>
#include "kpursedata.h"
#include "onlinegamemodule/item2/itemdef.h"
//#include "kservertime.h"
#include "stdlib.h"

class KPromotionSaleDate
{

public:

	INT nBeginSaleDate;			// ��ʼ��������20051202
	INT nEndSaleDate;			// ���۽�ֹ����
	INT nBeginAbateDate;		// ��ʼ��������
	INT nEndAbateDate;			// ���۽�ֹ����

#ifndef _SERVER

	//��ʼ��������
	LPSTR GetBeginAbateDate(LPSTR szDate)
	{
		InteagerToDateStr(nBeginAbateDate, szDate);
		return szDate;
	}

	//���۽�ֹ�����ַ���
	LPSTR GetAbateEndDate(LPSTR szDate)
	{
		InteagerToDateStr(nEndAbateDate, szDate);
		return szDate;
	}

	//��ʼ�������ڣ��¼����ڣ�
	LPSTR GetSellEndDate(LPSTR szDate)
	{
		InteagerToDateStr(nEndSaleDate, szDate);
		return szDate;
	}

	//���۽�ֹ���ڣ��¼����ڣ�
	LPSTR GetBeginSellDate(LPSTR szDate)
	{
		InteagerToDateStr(nBeginSaleDate, szDate);
		return szDate;
	}

#endif

private:

#ifndef _SERVER

	BOOL PickUpDate(INT nDate, std::string& year, std::string& month, std::string& day)
	{
		if(nDate <= 0)
			return FALSE;

		CHAR szTmpDate[32] = {0};
		sprintf(szTmpDate, "%d", nDate);
		//itoa(nDate, szTmpDate, 10);

		std::string strTemp = szTmpDate;

		if(strTemp.length() != 8)
		{
			ASSERT(0 == "Time format of table Goods is illegal, it should be like��20051202��");
			return FALSE;
		}

		year = strTemp.substr(0, 4);
		month = strTemp.substr(4, 2);
		day = strTemp.substr(6, 7);

		return TRUE;
	}

	VOID InteagerToDateStr(INT nDate, LPSTR szDate)
	{
		if(szDate == NULL)
			return;

		std::string year, month, day;
		if(!PickUpDate(nDate, year, month, day))
			return;

		sprintf(szDate, "%s-%s-%s", year.c_str(), month.c_str(), day.c_str());

		return;
	}

	VOID InteagerToStandardDate(INT nDate, tm& tmDate)
	{
		std::string year, month, day;
		if(!PickUpDate(nDate, year, month, day))
			return;

		INT nYear = 0, nMonth = 0, nDay = 0;
		nYear = atoi(year.c_str()) - 1900;
		nMonth = atoi(month.c_str());
		nDay = atoi(day.c_str());

		if(nYear < 0 || nMonth <= 0 || nDay <= 0 || nMonth > 12 || nDay > 31)
		{
			ASSERT(0);
			return;
		}

		memset(&tmDate, 0,  sizeof(tmDate));
		tmDate.tm_year = nYear;
		tmDate.tm_mon = nMonth;
		tmDate.tm_mday = nDay;
	}

#endif

};

class KGoods
{

public:
	enum enumStatType
	{
		StatType_LateCache = 0,									// �������
		StatType_TotalForStart,									// �ӷ����������������
		StatType_End,
	};

	struct KReputeCondition										// ��������
	{
		INT nCamp;												// ��Ӫ
		INT nClass;												// ���
		INT nLevel;												// �ȼ�
	};

public:

	KGoods();
#ifndef _SERVER	// �˺���ֻ�ڿͻ���ʹ�ã�����������Ʒ�۸��KItem::GetPrice()��ȡ
	INT 	GetGoodsPrice_Money();								// ��ȡ��Ʒ�Ľ������ۼ�
	INT		GetGoodsPrice_BindMoney();							// ��ȡ��Ʒ�İ������ۼ�
	INT		GetGoodsPrice_MachineCoin();						// ��ȡ��Ʒ�Ļ������;ö�
#endif
	INT 	GetGoodsPrice_FuYuan();								// ��ȡ��Ʒ�ĸ�Ե�ۼ�
	INT 	GetGoodsPrice_Coin();								// ��ȡ��Ʒ��ͭǮ�ۼ� תΪ ��ȡ��Ʒ�����л�ʯ�һ�����
	INT 	GetGoodsPrice_Score();								// ��ȡ��Ʒ�Ļ����ۼ�
	INT 	GetGoodsPrice_Honour();								// ��ȡ��Ʒ���������ۼ�
	INT		GetGoodsPrice_FightPowerRank();						// ��ȡ��Ʒ��ս���������۸�
	INT 	GetGoodsPrice_OrginCoin();
	INT 	GetGoodsPrice_AbateCoin();
	INT 	GetGoodsPrice_Contribution();						// ��ȡ��Ʒ�Ĺ��׶��ۼ�
	INT		GetGoodsPrice_TongFund();						// ��ȡ��Ʒ�ۼ�(��Ὠ���ʽ�)
	INT		GetGoodsPrice_CoinItem();							// ��ȡ�̵�Ľ�������Ʒ�ۼ�
	INT		GetGoodsPrice_ValueCoin();							// ��ȡ��Ʒ����ֵ�����ۼ�
	INT 	GetGoodsPrice_BuildFund();							// ��ȡ��Ʒ�Ľ�����ۼ�
	INT		GetGoodsPrice_TongEnergy(VOID)	{return m_nGoodsPrice_Energy; }
	DWORD	GetTimeout() CONST;										// ��ȡ��Ʒ��ʱЧ
	BOOL	IsGetBind();											// �Ƿ�Ϊ��ȡ��
	INT		GetItemCoinIndex();									// ��ȡ��������Ʒ��gamesetting�е�index
	INT		GetValueCoinIndex();								// ��ȡʵ�������gamesetting�е�index
	

	//VOID 	SetGoodsPrice_Money(INT nNewPrice);					// ������Ʒ�Ľ������ۼ�
	VOID 	SetGoodsPrice_FuYuan(INT nNewPrice);				// ������Ʒ�ĸ�Ե�ۼ�
	VOID 	SetGoodsPrice_AbateCoin(INT nNewPrice);				// ������Ʒ��ͭǮ�ۼ�
	VOID 	SetGoodsPrice_OrginCoin(INT nNewPrice);				// ������Ʒ��ͭǮ�ۼ�
	VOID 	SetGoodsPrice_Score(INT nNewPrice);					// ������Ʒ�Ļ����ۼ�
	VOID 	SetGoodsPrice_Contribution(INT nNewPrice);			// ��ȡ��Ʒ�Ĺ��׶��ۼ�
	VOID 	SetGoodsPrice_TongFund(INT nNewPrice);			// ��ȡ��Ʒ�ۼ�(��Ὠ���ʽ�)
	VOID 	SetGoodsPrice_BuildFund(INT nNewPrice);				// ��ȡ��Ʒ�Ľ�����ۼ�
	VOID 	SetGoodsPrice_Honour(INT nNewPrice);				// ������Ʒ���������ۼ�
	VOID	SetGoodsPrice_FightPowerRank(INT nNewPrice);		// ������Ʒ��ս���������۸�
	VOID	SetGoodsPrice_CoinItem(INT nGoodsIndex, INT nNewPrice);	// ������Ʒ�Ľ�������Ʒ�ۼ�
	VOID	SetGoodsPrice_ValueCoin(INT nGoodsInidex, INT nNewPrice);	// ������Ʒ����ֵ�����ۼ�
	VOID	SetGoodsPrice_TongEnergy(INT nEnergy){ m_nGoodsPrice_Energy = nEnergy;}
	VOID 	SetTimeout(DWORD dwTimeout);						// ������Ʒ��ʱЧ
	BOOL 	IsSaleLogRequired();								// �ж��Ƿ���Ҫ��������־
	VOID 	SetIfSaleLog(BOOL bLogRequired);					// �����Ƿ���Ҫ��������־
	VOID 	SetGoods_SaleDate(INT nBeginDate, INT nEndDate);
	VOID 	SetGoods_AbateDate(INT nBeginDate, INT nEndDate);

	INT		GetId(VOID) CONST;									// �����Ʒ����
	VOID	SetId(INT nId);										// �趨��Ʒ����
	LPCSTR	GetName(VOID) CONST;								// �����Ʒ����
	VOID	SetGoods_Repute(CONST KReputeCondition *pCond);		// ������������
	BOOL	OnSale(KMONEYTYPE type, DWORD dwCount);
	DWORD	GetSaleStat(KMONEYTYPE currType, enumStatType statType);
	VOID	CleanSaleStat(KMONEYTYPE currType, enumStatType statType);

	KPromotionSaleDate* GetGoods_PromotionDate();		
	CONST KReputeCondition *GetGoods_Repute() CONST { return &m_sReputeCond; }

	VOID	SetGood_OfficialLevel(INT nOfficialLevel){ m_nOfficialLevel = nOfficialLevel;}
	INT		GetGood_OfficialLevel(VOID)	 {return m_nOfficialLevel;}

	INT		GetTimeFrameStartDay();
	VOID	SetTimeFrameStartDay(int nTimeFrameStartDay);

	time_t	GetTimeSaleStart();
	VOID	SetTimeSaleStart(time_t timeSaleStart);
	time_t  GetTimeSaleClose();
	VOID	SetTimeSaleClose(time_t timeSaleClose);

	INT		GetStock();
	VOID	SetStock(INT nStock);
	INT		GetPurchaseLimit();
	VOID	SetPurchaseLimit(INT nPursechaseLimit);
	INT		GetVip();
	VOID	SetVip(INT nVip);
	INT		GetDiscount();
	VOID	SetDiscount(INT nDiscount);

public:

#ifdef GAME_SERVER
	KITEM_INDEX	m_sIndex;										// ��Ʒ�ĵ�������
	INT			m_nSeries;										// ��Ʒ������
#else
	INT			m_nItemIdx;										// ��Ʒ��Ӧ�ĵ���Index
#endif
	INT			m_nId;		
	INT			m_nBind;										// �Ƿ��
	INT         m_nCurrencyType;                                // ����Ʒ���ĵĻ�������
	INT         m_nPrice;                                       // �۸�
	INT			m_nStock;											//���
	INT			m_nPurchaseLimit;								//�޹�
	INT			m_nVip;											//vip
	INT			m_nDiscount;									//�ۿ�
	DWORD		m_dwTimeout;									// ʱЧ
	INT			m_nLimitType;									//�޹�����
	INT			m_nLimitTime;									//�޹���ʱ����

	// ��Ʒ�Ƿ�������״̬�Ŀ��ƣ���ʱ����;���ʱ�����������ƣ�ֻ�������������������ʱ��ſ�����

	// ��Ʒ�Ƿ�������״̬��ʱ�������
	INT			m_nTimeFrameStartDay;								// ���������쿪ʼ��(Ĭ��ֵ0��ʾ���Դ��ֶΣ�

	// ��Ʒ�Ƿ�������״̬�ľ���ʱ�����
	time_t		m_timeSaleStart;									// ʲôʱ��ʼ��������ʱ�䣬Ĭ��ֵ0��ʾ���Դ��ֶΣ�
	time_t		m_timeSaleClose;									// ����ʲôʱ�����������ʱ�䣬Ĭ��ֵ0��ʾ���Դ��ֶΣ�
	INT         m_maxCount;											//ȫ���޹��������
private:
									// ��Ʒ����
	INT			m_nGoodsPrice_Money;							// ��NPC��ʱ�Ľ����Ҽ۸�
	INT			m_nGoodsPrice_FuYuan;							// ��Ե�۸�
	INT			m_nGoodsPrice_AbateCoin;						// ͭǮ�۸�
	INT			m_nGoodsPrice_OrginCoin;						
	INT			m_nGoodsPrice_Score;							// ���ּ۸�
	INT			m_nGoodsPrice_Contribution;						// ���׶ȼ۸�
	INT			m_nGoodsPrice_TongFund;							// ��Ὠ���ʽ�۸�
	INT			m_nGoodsPrice_Energy;							// ����ж���
	INT			m_nGoodsPrice_BuildFund;						// ����ȼ۸�
	INT			m_nGoodsPrice_Honour;							// ������۸�
	INT			m_nGoodsPrice_FightPowerRank;					// ս���������۸�
	BOOL		m_bSaleLogRequired;								// �Ƿ���Ҫ��������־
	DWORD		m_dwSaleStats[EM_MONEY_MAX - 2][StatType_End];	// ��Ʒ����ͳ��(���ֻ���)
	INT			m_nOfficialLevel;								// ��������

	INT			m_nItemCoinIndex;								// ʵ����ҵ�����
	INT			m_nPrice_ItemCoin;								// ʵ����ҵļ۸�

	INT			m_nValueCoinIndex;								// ��ֵ���ҵ�����
	INT			m_nPrice_ValueCoin;								// ��ֵ���ҵļ۸�

	KReputeCondition	m_sReputeCond;							// ��������
	KPromotionSaleDate	m_PromotionData;						// TODO: xyf ��ʱ���Ӵ�������

};


