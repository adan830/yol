------------------------------------------  ħ�����Ժ���������  ----------------------------------

-- �˺�����ֵ
function BufferMagicEffect:de_me_damagelife_v()
	--self:DebugPrint("");
end

-- �˺������ٷֱ�
function BufferMagicEffect:de_me_damagelife_p()
	-- self:DebugPrint("");
end

-- �˺�����ֵ
function BufferMagicEffect:de_me_damagemana_v()
	-- self:DebugPrint("");
end

-- �˺������ٷֱ�
function BufferMagicEffect:de_me_damagemana_p()
	-- self:DebugPrint("");
end

-- ����
function BufferMagicEffect:de_me_knock()
	-- self:DebugPrint("");
end

-- ��ɱĿ��
function BufferMagicEffect:de_me_dodeath()
	-- self:DebugPrint("");
end

-- ����Ŀ��
function BufferMagicEffect:de_me_dorevive()
	-- self:DebugPrint("");
end

-- �����Ӧid��buff
function BufferMagicEffect:de_me_clearbuff()
	-- self:DebugPrint("");
end

-- ���debuff��debuff����1��buff��
function BufferMagicEffect:de_me_cleardebuff()
	-- self:DebugPrint("");
end

-- �����Ӧid��skill��cdʱ��
function BufferMagicEffect:de_me_clearcd()
	-- self:DebugPrint("");
end

-- ��Ŀ�������Լ���ǰ
function BufferMagicEffect:de_me_pulltarget()
	-- self:DebugPrint("");
end

-- ���͵�Ŀ���ͼ�Ķ�Ӧ�㣬�õ�ɶ�̬���ɣ��������������͵ļ���
function BufferMagicEffect:de_me_setmappos()
	-- self:DebugPrint("");
end

-- �سǣ��ص�֮ǰ������İ�ȫ���Ķ�Ӧλ��
function BufferMagicEffect:de_me_tp()
	-- self:DebugPrint("");
end

-- ���Ӷ�Ӧid��buff��ʱ��
function BufferMagicEffect:de_me_addbufftime()
	-- self:DebugPrint("");
end

-- ����id��buff��ʱ��
function BufferMagicEffect:de_me_refreshbufftime()
	-- self:DebugPrint("");
end

-- ɾ������Ч�����ڵ�buff����
function BufferMagicEffect:de_me_kill_self()
	-- self:DebugPrint("");
end


function BufferMagicEffect:de_me_cast_skill()
	-- self:DebugPrint("");
end

function BufferMagicEffect:de_me_hide()
	self:DebugPrint("de_me_hide");
	me.SetSkillHidden(0);
end

-- ����Ӧcate�ļ�����Ӷ�Ӧid��buff
function BufferMagicEffect:de_me_add_bufftoskill(nBuffTemplateId)
	local nAppendValue	= me.pBufferEffect.GetAppendData(nBuffTemplateId, self.BuffDataType.DATATYPE_SKILL_BUFF);
	him.pFightSkill.AddBuffToSkill(nSkillCateType, nSkillCateId, -nAppendValue);

	self:DebugPrint("de_me_add_bufftoskill");
end

-- �Ӷ�Ӧcate�ļ���ɾ����Ӧid��buff
function BufferMagicEffect:de_me_del_bufffromskill(nBuffTemplateId)
	local nAppendValue	= me.pBufferEffect.GetAppendData(nBuffTemplateId, self.BuffDataType.DATATYPE_SKILL_BUFF);
	him.pFightSkill.AddBuffToSkill(nSkillCateType, nSkillCateId, -nAppendValue);

	self:DebugPrint("de_me_del_bufffromskill");
end

-- ���ӵ�ǰ����ֵ
function BufferMagicEffect:de_me_addcurlife_v()
	-- self:DebugPrint("");
end

-- ���ӵ�ǰ�����ٷֱ�
function BufferMagicEffect:de_me_addcurlife_p()
	-- self:DebugPrint("");
end

function BufferMagicEffect:de_me_state_add_buff()

end

-- ���ӵ�ǰ����ֵ
function BufferMagicEffect:de_me_addcurmana_v()
	-- self:DebugPrint("");
end

function BufferMagicEffect:de_me_add_groundbuffer()
	self:DebugPrint("de_me_add_groundbuffer");
end

-- ���ӵ�ǰ�����ٷֱ�
function BufferMagicEffect:de_me_addcurmana_p()
	-- self:DebugPrint("");
end

-- ���ӵ�ǰ����ֵ
function BufferMagicEffect:de_me_addcurpower_v()
	-- self:DebugPrint("");
end

-- ѣ��
function BufferMagicEffect:de_me_stun(nBuffTemplateId)
	--local nAppendValue = me.pBufferEffect.GetAppendData(nBuffTemplateId, self.BuffDataType.DATATYPE_STUN);
	--self:Add_IsStun(me, -nAppendValue);
	me.SetIsStun(0);
	if me.GetMoveState() == Character.MOVE_STATE_ON_HALT then
		me.SetMoveState(Character.MOVE_STATE_ON_STAND);
	end

	self:DebugPrint("de_me_stun");
end

function BufferMagicEffect:de_me_pet_damagelife_v(nBuffTemplateId)

end

function BufferMagicEffect:de_me_pet_addselflife(nBuffTemplateId)

end

function BufferMagicEffect:de_me_pet_subtargetlife(nValue, nBuffTemplateId, nSkillLevel)

end

function BufferMagicEffect:de_me_pet_addselfattack(nBuffTemplateId)
	local nAppendValue = me.pBufferEffect.GetAppendData(nBuffTemplateId, self.BuffDataType.DATATYPE_ATTACK);

	self:Add_Attack(him, -nAppendValue);

	self:DebugPrint("de_me_pet_addselfattack", nAppendValue);
	print("de_me_pet_addselfattack", nAppendValue);
end

function BufferMagicEffect:de_me_pet_subtargetdefence(nBuffTemplateId)
	local nAppendValue = me.pBufferEffect.GetAppendData(nBuffTemplateId, self.BuffDataType.DATATYPE_ARMOR);

	self:Add_Def(him, nAppendValue);

	self:DebugPrint("de_me_pet_subtargetdefence", nAppendValue);
end

function BufferMagicEffect:de_me_invisibleToNpc()
    me.SetIsVisiontoNPC(0)
    print("de_me_invisibleToNpc", me.szName)
end

-- ����
function BufferMagicEffect:de_me_fix()
	me.SetIsFix(0);
	if me.GetMoveState() == Character.MOVE_STATE_ON_FREEZE then
		me.SetMoveState(Character.MOVE_STATE_ON_STAND);
	end

  print("de_me_fix", me.szName);
	self:DebugPrint("de_me_fix");
end

-- �־�
function BufferMagicEffect:de_me_fear(nBuffTemplateId)
	local nAppendValue = me.pBufferEffect.GetAppendData(nBuffTemplateId, self.BuffDataType.DATATYPE_FEAR);
	self:Add_IsFear(me, -nAppendValue);

	if me.GetMoveState() == Character.MOVE_STATE_ON_HALT then
		me.SetMoveState(Character.MOVE_STATE_ON_STAND);
	end

	self:DebugPrint("de_me_fear");
end

-- ��Ĭ
function BufferMagicEffect:de_me_silence(nBuffTemplateId)
	local nAppendValue = me.pBufferEffect.GetAppendData(nBuffTemplateId, self.BuffDataType.DATATYPE_SILENCE);
	self:Add_IsSilence(me, -nAppendValue);

	if me.GetMoveState() == Character.MOVE_STATE_ON_HALT then
		me.SetMoveState(Character.MOVE_STATE_ON_STAND);
	end

	self:DebugPrint("de_me_silence");
end

-- ���
function BufferMagicEffect:de_me_crazy(nBuffTemplateId)
	local nAppendValue = me.pBufferEffect.GetAppendData(nBuffTemplateId, self.BuffDataType.DATATYPE_CRAZY);
	self:Add_IsCrazy(me, -nAppendValue);

	self:DebugPrint("de_me_crazy");
end

function BufferMagicEffect:de_me_ignoredmg()
	me.SetIgnorDmg(0);
	self:DebugPrint("de_me_ignoredmg");
end

-- ����
function BufferMagicEffect:de_me_slow_p(nBuffTemplateId)
	local nSpeed = me.pBufferEffect.GetAppendData(nBuffTemplateId, self.BuffDataType.DATATYPE_SPEED);
	me.pBufferEffect.AppendData(nBuffTemplateId, self.BuffDataType.DATATYPE_SPEED, -nSpeed);
	self:Add_Speed(me, -nSpeed);

	local nSpeedPercent = me.pBufferEffect.GetAppendData(nBuffTemplateId, self.BuffDataType.DATATYPE_SPEED_PERCENT);
	me.pBufferEffect.AppendData(nBuffTemplateId, self.BuffDataType.DATATYPE_SPEED_PERCENT, -nSpeedPercent);
	self:DebugPrint("de_me_slow_p");
end

-- ����Ŀ�껤��
function BufferMagicEffect:de_me_ignorearmor_v(nBuffTemplateId)
	local nAppendValue	= me.pBufferEffect.GetAppendData(nBuffTemplateId, self.BuffDataType.DATATYPE_ARMOR);
	self:Add_Def(me, -nAppendValue);

	self:DebugPrint("de_me_ignorarmor_v");
end

-- ������ɵ��˺��ٷֱ�
function BufferMagicEffect:de_me_modifydmg_p(nBuffTemplateId)
	local nModifyDmgP = me.pBufferEffect.GetAppendData(nBuffTemplateId, self.BuffDataType.DATATYPE_MODIFYDMG_P);
	me.pBufferEffect.AppendData(nBuffTemplateId, self.BuffDataType.DATATYPE_MODIFYDMG_P, -nModifyDmgP);
	self:Add_ModifyDmgP(me, -nModifyDmgP);

	self:DebugPrint("de_me_modifydmg_p");
end

function BufferMagicEffect:de_me_add_medicineeffect_p(nBuffTemplateId)
	local nMedicineEffect = me.pBufferEffect.GetAppendData(nBuffTemplateId, self.BuffDataType.DATATYPE_MEDICINE_EFFECT);
	me.pBufferEffect.AppendData(nBuffTemplateId, self.BuffDataType.DATATYPE_MEDICINE_EFFECT, -nMedicineEffect);
	self:Add_ModifyDmgP(me, -nMedicineEffect);

	self:DebugPrint("de_me_add_medicineeffect_p");
end

-- ������ɵ��˺�ֵ
function BufferMagicEffect:de_me_modifydmg_v()
	self:DebugPrint("de_me_modifydmg_v");
end

-- �����������ֵ
function BufferMagicEffect:de_me_addmaxlife_v(nBuffTemplateId)
	local nAppendValue	= me.pBufferEffect.GetAppendData(nBuffTemplateId, self.BuffDataType.DATATYPE_MAXLIFE);
	self:Add_MaxLife(me, -nAppendValue);

	self:DebugPrint("de_me_addmaxlife_v");
end

-- ������������ٷֱ�
function BufferMagicEffect:de_me_addmaxlife_p(nBuffTemplateId)
	local nAppendValue	= me.pBufferEffect.GetAppendData(nBuffTemplateId, self.BuffDataType.DATATYPE_MAXLIFE);
	self:Add_MaxLife(me, -nAppendValue);

	self:DebugPrint("de_me_addmaxlife_p");
end

-- �����������ֵ
function BufferMagicEffect:de_me_addmaxmana_v(nBuffTemplateId)
	local nAppendValue	= me.pBufferEffect.GetAppendData(nBuffTemplateId, self.BuffDataType.DATATYPE_MAXMANA);
	self:Add_MaxMana(me, -nAppendValue);

	self:DebugPrint("de_me_addmaxmana_v");
end

-- ������������ٷֱ�
function BufferMagicEffect:de_me_addmaxmana_p(nBuffTemplateId)
	local nAppendValue	= me.pBufferEffect.GetAppendData(nBuffTemplateId, self.BuffDataType.DATATYPE_MAXMANA);
	self:Add_MaxMana(me, -nAppendValue);

	self:DebugPrint("de_me_addmaxmana_p");
end

-- ���������ֵ
function BufferMagicEffect:de_me_addmaxpower_v(nBuffTemplateId)
	local nAppendValue	= me.pBufferEffect.GetAppendData(nBuffTemplateId, self.BuffDataType.DATATYPE_MAXPOWER);
	self:Add_MaxPower(me, -nAppendValue);

	self:DebugPrint("de_me_addmaxpower_v");
end

-- ���������ֵ�ٷֱ�
function BufferMagicEffect:de_me_addmaxpower_p(nBuffTemplateId)
	local nAppendValue	= me.pBufferEffect.GetAppendData(nBuffTemplateId, self.BuffDataType.DATATYPE_MAXPOWER);
	self:Add_MaxPower(me, -nAppendValue);

	self:DebugPrint("de_me_addmaxpower_p");
end

-- ����������ֵ
function BufferMagicEffect:de_me_addhitrate_v(nBuffTemplateId)
	local nAppendValue	= me.pBufferEffect.GetAppendData(nBuffTemplateId, self.BuffDataType.DATATYPE_HITCOEFFICIENT);
	self:Add_HitCoefficient(me, -nAppendValue);

	self:DebugPrint("de_me_addhitrate_v");
end

function BufferMagicEffect:de_me_addattack_v(nBuffTemplateId)
	local nAppendValue	= me.pBufferEffect.GetAppendData(nBuffTemplateId, self.BuffDataType.DATATYPE_ATTACK);
	self:Add_Attack(me, -nAppendValue);

	self:DebugPrint("de_me_addattack_v");
end

function BufferMagicEffect:de_me_addresist_v(nBuffTemplateId)
	local nAppendValue	= me.pBufferEffect.GetAppendData(nBuffTemplateId, self.BuffDataType.DATATYPE_RESIST);
	self:Add_Resist(me, -nAppendValue);

	self:DebugPrint("de_me_addattack_v");
end

-- ���ӻ���һ��ֵ
function BufferMagicEffect:de_me_addcriticalrate_v(nBuffTemplateId)
	local nAppendValue	= me.pBufferEffect.GetAppendData(nBuffTemplateId, self.BuffDataType.DATATYPE_CRITICALVALUE);
	self:Add_CriticalValue(me, -nAppendValue);

	self:DebugPrint("de_me_addcriticalrate_v nAppendValue = ", nAppendValue);
end

function BufferMagicEffect:de_me_back_add_buff()
end

-- ���ӻ���һ���˺��ٷֱ�
function BufferMagicEffect:de_me_addcriticaldmg_p(nBuffTemplateId)
	local nAppendValue	= me.pBufferEffect.GetAppendData(nBuffTemplateId, self.BuffDataType.DATATYPE_CRITICALATTACK);
	self:Add_CriticalAttack(me, -nAppendValue);

	self:DebugPrint("de_me_addcriticaldmg_p");
end

-- �����ƶ��ٶ�
function BufferMagicEffect:de_me_addrunspeed_v(nBuffTemplateId)
	local nAppendValue	= me.pBufferEffect.GetAppendData(nBuffTemplateId, self.BuffDataType.DATATYPE_SPEED_PERCENT);
	self:Add_Speed(me, -nAppendValue);

	self:DebugPrint("de_me_addrunspeed_v");
end

-- ���ӻ���ֵ
function BufferMagicEffect:de_me_addarmor_v(nBuffTemplateId)
	local nAppendValue	= me.pBufferEffect.GetAppendData(nBuffTemplateId, self.BuffDataType.DATATYPE_ARMOR);
	self:Add_Def(me, -nAppendValue);

	self:DebugPrint("de_me_addarmor_v");
end

-- ��������ֵ
function BufferMagicEffect:de_me_adddodge_v(nBuffTemplateId)
	local nAppendValue	= me.pBufferEffect.GetAppendData(nBuffTemplateId, self.BuffDataType.DATATYPE_DODGEALL);
	self:Add_Dodge(me, -nAppendValue);

	self:DebugPrint("de_me_adddodge_v");
end

-- ��npc����
function BufferMagicEffect:de_me_hidetonpc(nBuffTemplateId)
	local nAppendValue	= me.pBufferEffect.GetAppendData(nBuffTemplateId, self.BuffDataType.DATATYPE_HIDETO_NPC);
	self:Add_IsHidetoNPC(me, -nAppendValue);

	self:DebugPrint("de_me_hidetonpc");
end

-- ���������
function BufferMagicEffect:de_me_hidetoplayer(nBuffTemplateId)
	local nAppendValue	= me.pBufferEffect.GetAppendData(nBuffTemplateId, self.BuffDataType.DATATYPE_HIDETO_PLAYER);
	self:Add_IsHidetoPlayer(me, -nAppendValue);

	self:DebugPrint("de_me_hidetoplayer");
end

-- ���ٷֱȷ����ܵ����˺�
function BufferMagicEffect:de_me_rebound_dmg_p()
	local nPercent = me.GetReboundP();
	self:Add_ReboundP(me, -nPercent);

	self:DebugPrint("de_me_rebound_dmg_p");
end

-- ��ֵ�����ܵ����˺�
function BufferMagicEffect:de_me_rebound_dmg_v(nBuffTemplateId)
	local nAppendValue	= me.pBufferEffect.GetAppendData(nBuffTemplateId, self.BuffDataType.DATATYPE_REBOUND_V);
	self:Add_ReboundV(me, -nAppendValue);

	self:DebugPrint("de_me_rebound_dmg_v");
end

-- �����������ܵ����˺�
function BufferMagicEffect:de_me_reducedmg()
	self:Set_WithstandNormalP(me, 0);
	self:Set_WithstandNormalV(me, 0);

	self:DebugPrint("de_me_reducedmg");
end

-- ����˺�������ת��Ϊ�����ظ�
function BufferMagicEffect:de_me_transdmgtolife(nBuffTemplateId)
	local nAppendValue	= me.pBufferEffect.GetAppendData(nBuffTemplateId, self.BuffDataType.DATATYPE_TRANSTOLIFE_P);
	self:Add_TransToLifeP(me, -nAppendValue);

	self:DebugPrint("de_me_transdmgtolife");
end

-- ����˺�������ת��Ϊ�����ظ�
function BufferMagicEffect:de_me_transdmgtomana(nBuffTemplateId)
	local nAppendValue	= me.pBufferEffect.GetAppendData(nBuffTemplateId, self.BuffDataType.DATATYPE_TRANSTOMANA_P);
	self:Add_TransToManaP(me, -nAppendValue);

	self:DebugPrint("de_me_transdmgtomana");
end

function BufferMagicEffect:de_me_ignorbuff(nBuffTemplateId)
	local nAppendValue	= me.pBufferEffect.GetAppendData(nBuffTemplateId, self.BuffDataType.DATATYPE_IGNOREBUFF_ID);
	me.pBufferEffect.IgnorBuff(-nBuffId);

	self:DebugPrint("de_me_ignorbuff");
end


function BufferMagicEffect:de_me_ignorbuffgroup(nBuffTemplateId)
	local nAppendValue	= me.pBufferEffect.GetAppendData(nBuffTemplateId, self.BuffDataType.DATATYPE_IGNOREBUFF_GROUP);
	me.pBufferEffect.IgnorBuffGroup(-nAppendValue);

	self:DebugPrint("de_me_ignorbuffgroup");
end


function BufferMagicEffect:de_me_ignorbuffcate(nBuffTemplateId)
	local nAppendValue1	= me.pBufferEffect.GetAppendData(nBuffTemplateId, self.BuffDataType.DATATYPE_IGNOREBUFF_CATETYPE);
	local nAppendValue2	= me.pBufferEffect.GetAppendData(nBuffTemplateId, self.BuffDataType.DATATYPE_IGNOREBUFF_CATEID);
	me.pBufferEffect.IgnorBuffCate(-nAppendValue1,nAppendValue2);

	self:DebugPrint("de_me_ignorbuffcate");
end

function BufferMagicEffect:de_me_ignoredebuff()
	me.SetIgnorDebuff(0);
	self:DebugPrint("de_me_ignoredebuff");
end

-- ����������������
function BufferMagicEffect:de_me_addtreatlife_v(nBuffTemplateId)
	local nAppendValue	= me.pBufferEffect.GetAppendData(nBuffTemplateId, self.BuffDataType.DATATYPE_CURING_LIFE);
	self:Add_CuringLifeBase(me, -nAppendValue);

	self:DebugPrint("de_me_addtreatlife_v");
end

-- �������������ٷֱ�
function BufferMagicEffect:de_me_addtreatlife_p(nBuffTemplateId)
	local nAppendValue	= me.pBufferEffect.GetAppendData(nBuffTemplateId, self.BuffDataType.DATATYPE_CURING_LIFE_PERCENT);
	self:Add_CuringLifePercent(me, -nAppendValue);

	self:DebugPrint("de_me_addtreatlife_p");
end

-- ����������������
function BufferMagicEffect:de_me_addtreatmana_v(nBuffTemplateId)
	local nAppendValue	= me.pBufferEffect.GetAppendData(nBuffTemplateId, self.BuffDataType.DATATYPE_CURING_MANA_BASE);
	self:Add_CuringManaBase(me, -nAppendValue);

	self:DebugPrint("de_me_addtreatmana_v");
end

-- �������������ٷֱ�
function BufferMagicEffect:de_me_addtreatmana_p(nBuffTemplateId)
	local nAppendValue	= me.pBufferEffect.GetAppendData(nBuffTemplateId, self.BuffDataType.DATATYPE_CURING_MANA_PERCENT);
	self:Add_CuringManaPercent(me, -nAppendValue);

	self:DebugPrint("de_me_addtreatmana_p");
end

-- ��ֵ���ټ�������
function BufferMagicEffect:de_me_reducecost_v(nBuffTemplateId)
	local nCateId	= me.pBufferEffect.GetAppendData(nBuffTemplateId, self.BuffDataType.DATATYPE_SKILLCOST_CATEID);
	me.pFightSkill.ResetSkillCost(1, nCateId);

	self:DebugPrint("de_me_reducecost_v");
end

-- ���������ټ�������
function BufferMagicEffect:de_me_reducecost_p(nBuffTemplateId)
	local nCateId	= me.pBufferEffect.GetAppendData(nBuffTemplateId, self.BuffDataType.DATATYPE_SKILLCOST_CATEID);
	me.pFightSkill.ResetSkillCost(1, nCateId);

	self:DebugPrint("de_me_reducecost_p");
end

-- �����˺�
function BufferMagicEffect:de_me_ignordmg(nBuffTemplateId)
	local nAppendValue	= me.pBufferEffect.GetAppendData(nBuffTemplateId, self.BuffDataType.DATATYPE_IGNORE_DMG);
	self:Add_IgnorDmg(me, -nAppendValue);

	self:DebugPrint("de_me_ignordmg");
end

-- ���Ӷ�Ӧcate���ܵĹ������ٷֱ�
function BufferMagicEffect:de_me_addmagnification()
	-- self:DebugPrint("");
end

-- ���ӹ�����ֵ
function BufferMagicEffect:de_me_addatkdmg_v(nBuffTemplateId)
	local nAppendValue11	= me.pBufferEffect.GetAppendData(nBuffTemplateId, self.BuffDataType.DATATYPE_PHYSICATTACK_MAX);
	local nAppendValue12	= me.pBufferEffect.GetAppendData(nBuffTemplateId, self.BuffDataType.DATATYPE_PHYSICATTACK_MIN);
	local nAppendValue21	= me.pBufferEffect.GetAppendData(nBuffTemplateId, self.BuffDataType.DATATYPE_MAGICATTACK_MAX);
	local nAppendValue22	= me.pBufferEffect.GetAppendData(nBuffTemplateId, self.BuffDataType.DATATYPE_MAGICATTACK_MIN);

	self:modifydmg_v(-nAppendValue11, -nAppendValue12, -nAppendValue21, -nAppendValue22);

	self:DebugPrint("de_me_addatkdmg_v");
end

-- ���߻��Ĺ���
function BufferMagicEffect:de_me_ignorcristal(nBuffTemplateId)
	local nAppendValue	= me.pBufferEffect.GetAppendData(nBuffTemplateId, self.BuffDataType.DATATYPE_IGNORE_CRISTAL);
	self:Add_IgnorCristal(me, -nAppendValue);

	self:DebugPrint("de_me_ignorcristal");
end

-- ������nParam1����nPercent���ӵ�nParam2��
function BufferMagicEffect:de_me_trans_param(nBuffTemplateId)
	local nAppendValue1	= me.pBufferEffect.GetAppendData(nBuffTemplateId, self.BuffDataType.DATATYPE_TRANSPARAM_TYPE);
	local nAppendValue2	= me.pBufferEffect.GetAppendData(nBuffTemplateId, self.BuffDataType.DATATYPE_TRANSPARAM_VALUE);
	self:AddParamValue(me, nAppendValue1, -nAppendValue2);

	self:DebugPrint("de_me_trans_param");
end

-- ���Ķ�Ӧ���ܵ��������ͣ���ԭ�����������ܱ��˲������
function BufferMagicEffect:de_me_changechanneltype(nBuffTemplateId)
	local nCateType	= me.pBufferEffect.GetAppendData(nBuffTemplateId, self.BuffDataType.DATATYPE_CHANGE_CHANNEL_CATETYPE);
	local nCateId	= me.pBufferEffect.GetAppendData(nBuffTemplateId, self.BuffDataType.DATATYPE_CHANGE_CHANNEL_CATEID);

	me.pFightSkill.ResetSkillChannelType(nCateType, nCateId, -1);
	self:DebugPrint("de_me_changechanneltype");
end

function BufferMagicEffect:de_me_add_bufftoself()
end

-- ��������ʱ��
function BufferMagicEffect:de_me_reducechanneltime(nBuffTemplateId)
	local nAppendValue = me.pBufferEffect.GetAppendData(nBuffTemplateId, self.BuffDataType.DATATYPE_SKILL_CHANNELTIME);
	me.pFightSkill.ResetSkillChannelTime(nCateType, nCateId, -nAppendValue);

	self:DebugPrint("de_me_reducechanneltime");
end

-- ��˸��Ŀ�걳��
function BufferMagicEffect:de_me_twinkle()
	self:DebugPrint("de_me_twinkle");
end


-- ����Ŀ����ǰ(������˸),  by KK
function BufferMagicEffect:de_me_jumpto()
	self:DebugPrint("de_me_jumpto");
end

-- �Լ��󷭹�  by KK
function BufferMagicEffect:de_me_backflip()
	self:DebugPrint("de_me_backflip");
end

-- �����ܵ����˺��ٷֱ�
function BufferMagicEffect:de_me_addrecievedmg_p(nBuffTemplateId)
	local nAppendValue	= me.pBufferEffect.GetAppendData(nBuffTemplateId, self.BuffDataType.DATATYPE_ENLARGE_ATTACK_P);
	self:Add_EnlargeAttackP(me, -nAppendValue);

	self:DebugPrint("de_me_addrecievedmg_p");
end

function BufferMagicEffect:de_me_reducerecievedmg_p(nBuffTemplateId)
	local nAppendValue	= me.pBufferEffect.GetAppendData(nBuffTemplateId, self.BuffDataType.DATATYPE_REDUCE_ATTACK_P);
	self:Add_ReduceAttackP(me, -nAppendValue);

	self:DebugPrint("de_me_reducerecievedmg_p");
end

-- ͬʱ����hide��visionʱ���ɼ�
function BufferMagicEffect:de_me_visiontonpc()
	me.SetIsVisiontoNPC(0);
	self:DebugPrint("de_me_visiontonpc");
end

-- ͬʱ����hide��visionʱ���ɼ�
function BufferMagicEffect:de_me_visiontoplayer()
	me.SetIsVisiontoPlayer(0);
	self:DebugPrint("me_visiontoplayer");
end

-- ��Ѫ��һ�����ԣ�
function BufferMagicEffect:de_me_vampire()
	self:DebugPrint("de_me_vampire");
end

-- ΪĿ������˺�(�ɵ���)
function BufferMagicEffect:de_me_divertdmgtoself()
	me.SetWithstandBuffPlayer(0);
	me.SetWithstandBuffPercent(0);
	me.SetWithstandBuffLifePercent(0);

	self:DebugPrint("de_me_divertdmgtoself"," ","Target Name:",me.szName,"Caster Name:",him and him.szName or "No Caster");
end

function BufferMagicEffect:de_me_add_self_groundbuffer()

end

function BufferMagicEffect:de_me_add_bufftoreceiver()
end

function BufferMagicEffect:de_me_add_bufftosender()
end

function BufferMagicEffect:de_me_add_bufftotriggerreceiver()
end

function BufferMagicEffect:de_me_add_bufftotriggersender()
end

function BufferMagicEffect:de_me_explode()
end

function BufferMagicEffect:de_me_yongzhewudi(nBuffTemplateId) --�����޵У����ݵ�ǰ������ʧ����������ֵ
	local nValue = me.pBufferEffect.GetAppendData(nBuffTemplateId, self.BuffDataType.DATATYPE_YONGZHEWUDI);
	self:Add_Dodge(me, -nValue);
	--self:DebugPrint("de_me_yongzhewudi()");  --������ʾ��ˢ��̫��
end

function BufferMagicEffect:de_me_add_battleintegration_v()
end





-- �������ܸ���buff ------------
function BufferMagicEffect:de_me_inactive_addselflife_v(nBuffTemplateId, nSkillLevel)

end

function BufferMagicEffect:de_me_inactive_subtargetlife_v(nBuffTemplateId, nSkillLevel)

end

function BufferMagicEffect:de_me_inactive_subtargetmana_v(nBuffTemplateId, nSkillLevel)

end

function BufferMagicEffect:de_me_inactive_addhit_v(nBuffTemplateId)
	local nAppendValue = me.pBufferEffect.GetAppendData(nBuffTemplateId, self.BuffDataType.DATATYPE_HITCOEFFICIENT);

	self:Add_CriticalValue(me, -nAppendValue);

	self:DebugPrint("de_me_inactive_addhit_v");
end
-- �������ܸ���buff ------------


--------------------------------------------------------------------------------
