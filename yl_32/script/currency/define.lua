if not (MODULE_GAMECLIENT or MODULE_GAMESERVER) then
	return
end

--������ϻ�������
Purse.EM_CURRENCY_BEGIN    =  1;
Purse.EM_CURRENCY_MAX    =  1; -- ���ܳ���255

--����Ǯ������
Purse.EM_MONEY_COIN      =  1;  -- ��ң� ���ܸ��ģ����ڵ�һλ
Purse.EM_MONEY_BEGIN     =  1;
Purse.EM_MONEY_SILVER	 =  2;  -- ����
Purse.EM_MONEY_YLENERGY  =  3;  -- ���� kk
Purse.EM_MONEY_SPIRIT  	 =  4;	-- ս��
Purse.EM_MONEY_PRESTIGE  =  5;  -- ����
Purse.EM_MONEY_CONTRIBUTION = 6; -- ���幱�׶�
Purse.EM_MONEY_MPJJ_SCORE = 7;  --ս����˫(���ɾ���)����
Purse.EM_MONEY_JINGPO 		= 8;  --����
Purse.EM_MONEY_BIND_COIN  = 9;  --��Ԫ��
Purse.EM_MONEY_SHENMO_SCORE = 10; -- ��ħ���ְ�
Purse.EM_MONEY_MAX       =  11;

Purse.EM_PLAYER_MAXCARRYCURRENCY = 99999999;	--���������Я����

--Ǯ��ģ�鷵��ֵ

Purse.EM_S_SUCCESS = 0;					--��Զ���ڵ�һλ
Purse.EM_E_FAILED = 1;					--δ֪ԭ��ʧ��,ͨ���������
Purse.EM_E_CURRENCYTYPE_NOTEXIST = 2;   --������Ͳ�����
Purse.EM_E_CURRENCYADD_OVERLIMIT = 3;   --���������������
Purse.EM_E_CURRENCYCOST_NOENOUGH = 4;   --�����������
Purse.EM_E_MONEYTYPE_NOTEXIST    = 5;   --Ǯ���Ͳ�����
Purse.EM_E_MONEYADD_OVERLIMIT    = 6;	--Ǯ������������
Purse.EM_E_MONEYCOST_NOENOUGH    = 7; 	--Ǯ��������
Purse.EM_E_COINADD_OVERLIMIT     = 8;	--��������������ޣ�����̫���ܰ�
Purse.EM_E_COINCOST_NOENOUGH     = 9;	--�����������

--�ű�Ҫ���巵��ֵ����256��ʼ, ������ں˶����ص�
