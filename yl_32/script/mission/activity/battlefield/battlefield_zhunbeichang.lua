Include("script/mission/activity/activitystep.lua")
Include("script/mission/activity/activitydef.lua")

Activity.BattleFieldZhunbeichang1 = Lib:NewClass(Activity.ActivityStep);  -- �췽׼����
Activity.ACTSTEP_FACTORY[Activity.STEP_TYPE.BATTLE_FIELD_ZHUNBEICHANG_1] = Activity.BattleFieldZhunbeichang1 -- ע�ᵽ�����
local BattleFieldZhunbeichang1 = Activity.BattleFieldZhunbeichang1

-- �췽׼������ҷ���
function BattleFieldZhunbeichang1:OnEnterActivityScene(nPlayerId)
	--local nCamp = Activity.START_CAMP + self.nGroupNum - 1;
	--local pPlayer = KGameBase.GetPlayerById(nPlayerId);
	-- ������Ӫ
	--pPlayer.SetCurrentCamp(nCamp);
	print(string.format("[OnJoinPlayer]1��ʼս��׼���������Ӫ���䣬 Group:%d", self.nGroupNum));
	-- ��������Ӫ��
	self:AddPlayerToGroup(nPlayerId, 1)  -- group 1,2  TODO:BUG:�ӵ�group��ʱ�򣬻������Զ�����Camp
end

Activity.BattleFieldZhunbeichang2 = Lib:NewClass(Activity.ActivityStep);  -- ����׼����
Activity.ACTSTEP_FACTORY[Activity.STEP_TYPE.BATTLE_FIELD_ZHUNBEICHANG_2] = Activity.BattleFieldZhunbeichang2 -- ע�ᵽ�����
local BattleFieldZhunbeichang2 = Activity.BattleFieldZhunbeichang2

-- ����׼������ҷ���
function BattleFieldZhunbeichang2:OnEnterActivityScene(nPlayerId)
	-- ��������Ӫ��
	print(string.format("[OnJoinPlayer]2��ʼս��׼���������Ӫ���䣬 Group:%d", self.nGroupNum));
	self:AddPlayerToGroup(nPlayerId, 2)  -- group 1,2  TODO:BUG:�ӵ�group��ʱ�򣬻������Զ�����Camp
end
