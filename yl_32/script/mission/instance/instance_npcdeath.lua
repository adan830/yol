
-- 

local InstanceNpc_Death = Npc:GetClass("instancenpc_death")

function InstanceNpc_Death:OnDeath(pKiller, pNpc)
	Instance:NpcUnLock(pNpc);
	if pKiller.IsNpc() == 1 then
		return;
	end
	self:GiveExp(pKiller, pNpc);
	self:DropItems(pKiller, pNpc);
end

function InstanceNpc_Death:DropItems(pKiller, pNpc)
	local pInstance = Instance:GetMyInstance(pKiller.dwId);
	
	if not pInstance then
		return;
	end
	
	local tbSetting = Instance.tbSetting[pKiller.dwSceneTemplateId];
	
	local mPos = pNpc.GetPosition();
	
	Npc:DropItems(pNpc.dwTemplateId, pKiller.dwId, mPos, {pKiller.dwId});
end

function InstanceNpc_Death:GiveExp(pKiller, pNpc)
	local tbTmp = pNpc.GetTempTable("Instance");
	if not tbTmp then
		return;
	end
	local tbInstance = tbTmp.tbInstance;
	local nEnemyNum = 20;	-- Ĭ��20
	if tbInstance.nEnemyNum then
		nEnemyNum = tbInstance.nEnemyNum;
	end
	
	local tbAssetAward = KAward.GetAssetAwardData("Instance", tbInstance.nMapId);
	local nExpAwardId = tbAssetAward.nExpAwardId;
	
	--local nExp = KAward.GetExpByLevel(nExpAwardId, pKiller.GetLevel() + 1);
	local nPropId = KCharacter.GetNpcPropId(pNpc.dwTemplateId);
	local nExp = KCharacter.GetNpcExp(nPropId,pNpc.GetLevel())
	--nExp = math.floor(nExp / nEnemyNum);	-- ����ƽ����
	pKiller.AddExp(nExp);
end
