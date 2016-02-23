
#pragma once

// -------------------------------------------------------------------------
#include "onlinegamemodule/trade/kplayerpurse_i.h"

class KPurseData
{
public:
	typedef std::map<BYTE, INT>  MPCURRENCYS;	//���: ���ϻ���
	typedef std::map<BYTE, INT>  MPMONEYS;		//Ǯ: �������, ����������

	KPurseData() : m_nJbCoin(0) 
	{
		m_mpCurrencys.clear();
		ASSERT(0 == m_mpCurrencys.size());
		m_mpMoneys.clear();
		ASSERT(0 == m_mpMoneys.size());
	}

public:
	
	VOID Clear();

	// ���ϻ���
	BOOL RegistCurrency(BYTE byCurrencyId);
	BOOL SetCurrency(BYTE byCurrencyId, INT nCurrency, KE_PURSE_RESULT* pResult);
	INT  GetCurrency(BYTE byCurrencyId);	

	// ��ͨ��Ϸ��, ������������
	BOOL RegistMoney(BYTE byMoneyType);	
	BOOL SetMoney(BYTE byMoneyType, INT nMoney, KE_PURSE_RESULT* pResult);
	INT  GetMoney(BYTE byMoneyType);
	
	//��Ҳ����̣���bishopͬ������, �Ƚ������Ǯ
	INT  GetCoin() { return m_nJbCoin; }
	BOOL SetCoin(INT nCoin, KE_PURSE_RESULT* pResult);
	
	MPCURRENCYS* GetCurrencyList();
	MPMONEYS*    GetMoneyList();

private:	
	MPCURRENCYS	m_mpCurrencys;	
	MPMONEYS	m_mpMoneys;	
	INT			m_nJbCoin;
};

// -------------------------------------------------------------------------

