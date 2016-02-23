
#pragma once

// -------------------------------------------------------------------------
enum KE_PURSE_RESULT
{
	emKPURSE_S_SUCCESS = 0,				//��Զ���ڵ�һλ
	emKPURSE_E_FAILED,					//δ֪ԭ��ʧ��,ͨ���������
	emKPURSE_E_CURRENCYTYPE_NOTEXIST,   //������Ͳ�����
	emKPURSE_E_CURRENCYADD_OVERLIMIT,   //���������������
	emKPURSE_E_CURRENCYCOST_NOENOUGH,   //�����������
	emKPURSE_E_MONEYTYPE_NOTEXIST,		//Ǯ���Ͳ�����
	emKPURSE_E_MONEYADD_OVERLIMIT,		//Ǯ������������
	emKPURSE_E_MONEYCOST_NOENOUGH,		//Ǯ��������
	emKPURSE_E_COINADD_OVERLIMIT,		//��������������ޣ�����̫���ܰ�
	emKPURSE_E_COINCOST_NOENOUGH,		//�����������

	emKPURSE_E_MAX = 255,				//�ں˴��������ֵ���ű���256��ʼ����
};

enum KMONEYTYPE				// ����ʱ�����õ���Ʒ�Ļ�������
{
	EM_MONEY_COIN     = 1,  // Ԫ��
	EM_MONEY_BEGIN    = 1,
	EM_MONEY_SILVER	  = 2,  //����
	EM_MONEY_YLENERGY = 3,	// ��������
	EM_MONEY_SPIRIT   = 4,	// ս��
	EM_MONEY_PRESTIGE = 5,	// ����
	EM_MONEY_CONTRIBUTION = 6, // ���幱�׶�
	EM_MONEY_MPJJ_SCORE = 7,//���ɾ�������
	EM_MONEY_JINGPO = 8,	// ����
	EM_MONEY_BIND_COIN = 9,  // ��Ԫ��
	EM_MONEY_SHENMO_SCORE = 10, // ��ħ����
	EM_MONEY_MAX      = 11
};

class KPlayer;

interface IKPlayerPurse
{
	//���
	virtual BOOL RegistCurrencyType(BYTE byCurrencyID)	PURE;
	virtual BOOL SetCurrency(BYTE byCurrencyID, INT nCurrency, KE_PURSE_RESULT* pResult, BOOL bSync = 1)  PURE;
	virtual INT  GetCurrency(BYTE byCurrencyID) PURE;
	
	//Ǯ
	virtual BOOL RegistMoneyType(BYTE byMoneyType) PURE;
	virtual INT  GetMoney(BYTE byMoneyType)        PURE;
	virtual BOOL SetMoney(BYTE byMoneyType, INT nMoney, KE_PURSE_RESULT* pResult, BOOL bSync = 1) PURE;

	//���	
	virtual BOOL SetCoin(INT nCoin, KE_PURSE_RESULT* pResult, BOOL bSync = 1) PURE;
	virtual INT  GetCoin() PURE;

#ifdef GAME_SERVER
	virtual BOOL AddCurrency(BYTE byCurrencyID, INT nCurrency, KE_PURSE_RESULT* pResult, BOOL bSync = 1)  PURE;
	virtual BOOL AddMoney(BYTE byMoneyType, INT nMoney, KE_PURSE_RESULT* pResult, BOOL bSync = 1) PURE;
	virtual BOOL LogMoney(BYTE byMoneyType, INT nMoney,INT nActionType, KE_PURSE_RESULT* pResult, BOOL bSync = 1,char *str = "") PURE;
	
	virtual BOOL AddCoin(INT nCoin, KE_PURSE_RESULT* pResult, BOOL bSync = 1) PURE;
#endif
};
// -------------------------------------------------------------------------

IKPlayerPurse* GetPlayerPurse(KPlayer* pPlayer);

