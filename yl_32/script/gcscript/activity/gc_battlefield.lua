if not (MODULE_GAMECENTER) then
	return
end

Activity.MAX_BATTLE_MAP_PLAYER_COUNT = 10;

-- ��ħս������
function Activity:ApplyJoinBattleField_GC(nPlayerId, tbMaps)
	for _, nMapId in ipairs(tbMaps) do
		local nPlayerCount = GetMapPlayerCount(nMapId);
		if nPlayerCount < Activity.MAX_BATTLE_MAP_PLAYER_COUNT then
			GlobalExecute({"Activity:DoJoinBattleField", nPlayerId, nMapId});
			break;
		end
	end
end