if not MODULE_GAMECENTER then
	return
end

function GlobalData:GiveRankAward()
	print("����������");
	GlobalExecute({"Arena:WorldGiveRankAwards"});
	
	-- �����һ��
	local dwRoleId = GetRankIdByIdx(Rank.ARENA_RANK, 0);
  local szName = GetRoleName(dwRoleId);
  if szName ~= nil then
  	local nConnectIndex = GetPlayerConnectIndex(dwRoleId);
  	GlobalExecute({"Arena:BroadcastWinnerInfo", string.format(Lang.gcscript.str1[Lang.Idx],szName)}, nConnectIndex);
  else
    print("��������һ���Ľ�ɫ�Ҳ���",  dwRoleId, szName)
  end
end

function GlobalData:ResetArena()
	print("���þ�����");
	GlobalExecute({"Arena:WorldResetArena"});
end