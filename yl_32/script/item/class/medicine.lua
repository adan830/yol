
-- ҩƷ��ͨ�ù��ܽű�

local tbMedicine = Item:GetClass("medicine");

--local PK_LIMIT_USE_MEDICINE	= 9;			-- ����ֵ���ߺ�ҩ��Ч

------------------------------------------------------------------------------------------

-- �ж��Ƿ����
function tbMedicine:CheckUsable()
	return 1;
end

function tbMedicine:OnUse()					-- ��ҩ
	local tbBaseAttrib = it.GetBaseAttrib()
	for _, tb in ipairs(tbBaseAttrib) do
		it.ApplyMagicAttrib(tb.szName, tb.tbValue) -- TODO refact
	end
	return	1
end

function tbMedicine:GetTip(nState)			-- ��ȡTip
	local szTip = "";
	szTip = szTip..self:Tip_Attrib();
	return szTip;
end

function tbMedicine:Tip_Attrib()			-- ���Tip�ַ�����ҩƷ����

	local szTip = "<color=white>";
	local tbAttrib = it.GetBaseAttrib();	-- ���ҩƷ����
	local tbDesc = {};

	for _, tbMA in ipairs(tbAttrib) do
		if tbMA.szName ~= "" then
			local szDesc = FightSkill:GetMagicDesc(tbMA.szName, tbMA.tbValue, nil, 1);
			if szDesc ~= "" then
				table.insert(tbDesc, szDesc);
			end
		end
	end

	return	szTip..table.concat(tbDesc, "\n").."<color>";

end
