
-- ��ҩ

------------------------------------------------------------------------------------------
-- initialize

local tbGem= Item:GetClass("gem");

------------------------------------------------------------------------------------------

function tbGem:CheckUsable()
	return 1;
end

-- function tbGem:CanTakeAward(pPlayer, tbAward)
	-- assert(tbAward);
	
	-- local nItemCellCount = Reward:GetNeedBagCell(tbAward);
	
	-- if pPlayer.pItem.CountFreeBagCell() < nItemCellCount then
		-- pPlayer.SendBlackMsg(string.format("��������Ҫ��%d����λ���������°�����", nItemCellCount));
		-- return 0;
	-- end
	
	-- return 1;
-- end


function tbGem:OnUse()
	local pItem = it;
	me.pGem.OnUse(pItem.nGenre, pItem.nDetail, pItem.nParticular, pItem.nLevel);
	me.pItem.ConsumeItemInBags(1, pItem.nGenre, pItem.nDetail, pItem.nParticular, pItem.nLevel);
end
