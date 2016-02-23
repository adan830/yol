

-- ҩ�＼��
function FightSkill:ApplyMedicineSkill(nMeidicineType, nSkillLevel)
	local nValue = KFightSkill.GetMeidicineSkillNumber(nMeidicineType, nSkillLevel)

	if (nValue == nil) then
		return
	end

	if (nMeidicineType == 1) then -- ��ҩ
		local nNewLife = math.min(me.GetMaxLife(), me.GetCurrentLife() + nValue) -- ȡ�������ܳ���
		me.SetCurrentLife(nNewLife)
	elseif (nMeidicineType == 2) then
		local nNewMana = math.min(me.GetMaxMana(), me.GetCurrentMana() + nValue) -- ȡ�������ܳ���
		me.SetCurrentMana(nNewMana)
	end
end

-- ��������
--function FightSkill:SetPassiveSkill(nPassiveType, nSkillLevel, bAddOrRemove, bSync)
	--local nValue = KFightSkill.GetPassiveSkillNumber(nPassiveType, nSkillLevel)
--end


-- ��ȡĳ�����ܵĶ�Ӧ�Ŀ��Լ�������~~~ ͨ��slot�ж�
function FightSkill:GetSkillResistType(pPlayer, nSkillTemplateId)
	local nSlot = KFightSkill.GetSkillSlot(nSkillTemplateId)
	local nRoute = KFightSkill.GetSkillRoute(nSkillTemplateId)  -- ·�� 1��2Զ

	local nResistType =0
	if (nSlot == 1) then  -- ���弼�ܣ�����1
		if (nRoute == 1) then
			nResistType = 1  -- ��������1
		elseif (nRoute == 2) then
			nResistType = 2  -- Զ������2
		end
	elseif (nSlot == 2) then
		nResistType = 3      ----Ⱥ�忹��2
	elseif (nSlot == 3) then
		if (nRoute == 1) then
			nResistType = 4  -- ���ؿ��� 4
		elseif (nRoute == 2) then
			nResistType = 5  -- Զ�ؿ��� 5
		end
	elseif (nSlot == 4) then
		nResistType = 4      -- ��ɱ����6
	
	end

	return nResistType
end