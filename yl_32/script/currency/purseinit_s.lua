-- �ļ�������purseinit.lua
-- �����ߡ���wdb
-- ����ʱ�䣺2010-10-19 10:52:04
-- �������������Ǯ�� ��ʼ��

if not MODULE_GAMESERVER then
	return;
end

function Purse:Init(pPlayer)
	assert(pPlayer);
	
	for i = Purse.EM_CURRENCY_BEGIN, Purse.EM_CURRENCY_MAX - 1 do
		pPlayer.pPlayerPurse.RegistCurrencyType(i);
	end;
	
	for j = Purse.EM_MONEY_BEGIN, Purse.EM_MONEY_MAX - 1 do
		pPlayer.pPlayerPurse.RegistMoneyType(j);
	end;
	
	return 1;
end


