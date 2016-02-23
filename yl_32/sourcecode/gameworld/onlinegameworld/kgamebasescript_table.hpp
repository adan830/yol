/* -------------------------------------------------------------------------
//	�ļ���		��	kgamebasescript_table.hpp
//	������		��	LuaScriptTool
//	��������	��	���ļ���VisualStudio�����ɣ��벻Ҫ�ֶ��޸ģ���
//	ʹ�÷���	��	����Ӧ��CPP�ļ�ĩ�ˣ�include���ļ�
//
// -----------------------------------------------------------------------*/

CONST SCRIPT_FUNCTION arFunction[]	=  
{
	{"Sleep", LuaSleep, "Debug: ʹ���߳�ֹͣһ��ʱ��", "d", "dwMilliSeconds;", ""},
	{"WriteLog", LuaWriteLog, "д�ű���־", "ds", "��־��Ҫ�ȼ� LOG_RECORD_REMIND_LEVEL;����;", ""},
	{"WriteLogServer", LuaWriteLogServer, "дlogserver��־", "ds", "��־����;����;", ""},
	{"GetPlayerByName", LuaGetPlayerByName, "ͨ����ɫ�����Player", "s", "szName;", "o"},
	{"GetPlayerById", LuaGetPlayerById, "ͨ��Id���Player", "d", "dwId;", "o"},
	{"SaveAllPlayers", LuaSaveAllPlayers, "���̵�ǰ�������", "", "", ""},
	{"SavePlayerDelayData", LuaSavePlayerDelayData, "�洢�����������", "", "", ""},
	{"GetNpcById", LuaGetNpcById, "ͨ��Id���Npc", "d", "dwId;", "o"},
	{"GetNpcByNickName", LuaGetNpcByNickName, "ͨ���������Npc", "ds", "dwSceneId;szNickName;", "o"},
	{"GetDoodadByNickName", LuaGetDoodadByNickName, "ͨ���������Doodad", "ds", "dwSceneId;szNickName;", "o"},
	{"GetNameByTemplateId", LuaGetNameByTemplateId, "����Npc��ģ��ID������NpcName", "d", "nNpcTemplateID:Npc��ģ��ID;", "�ɹ�����npc���ƣ�ʧ�ܷ��ؿ�"},
	{"GetNpcTitleByTemplateId", LuaGetNpcTitleByTemplateId, "����Npc��ģ��ID������NpcTitle", "d", "Npc��ģ��ID;", "�ɹ�����npc���ƣ�ʧ�ܷ��ؿ�"},
	{"FindNpcWithTemplateId", LuaFindNpcWithTemplateId, "����ģ��ID����Npc", "ud", "dwSceneId ����Id;nNpcTemplateId: Npc��ģ��Id;", "�����б�{o}"},
	{"GetDoodadNameByTemplateId", LuaGetDoodadNameByTemplateId, "����Doodad��ģ��ID������DoodadName", "d", "nDoodadTemplateID:Doodad��ģ��ID;", "�ɹ�����Doodad���ƣ�ʧ�ܷ��ؿ�"},
	{"GetCharacterById", LuaGetCharacterById, "ͨ��Id�õ�Character", "d", "CharacterId;", "o"},
	{"GetDoodadById", LuaGetDoodadById, "ͨ��Id�õ�Doodad", "d", "DoodadId;", "o"},
	{"IsNpc", LuaIsNpc, "ͨ��Id�ж��Ƿ�Npc", "d", "dwId;", "y/n"},
	{"IsPlayer", LuaIsPlayer, "ͨ��Id�ж��Ƿ�Player", "d", "dwId;", "y/n"},
	{"GetTime", LuaGetTime, "��õ�ǰʱ�䣨������", "", "", "��1970��1��1��0ʱ�����������UTCʱ��������������ʱ�䣩"},
	{"EnableWorldDebug", LuaEnableWorldDebug, "����/��ֹ�������ڲ�������Ϣ", "d", "1 ���� 0 ��ֹ;", ""},
	{"GetPlayerCount", LuaGetPlayerCount, "��������", "", "", "d"},
	{"GetNpcCount", LuaGetNpcCount, "���Npc��", "", "", "d"},
	{"GetDoodadCount", LuaGetDoodadCount, "���Doodad��", "", "", "d"},
	{"GetAllPlayers", LuaGetAllPlayers, "��ȡ������ҿ��գ���Ҫ�洢pPlayer����Ϊplayer��������ã�", "", "", "*o"},
	{"GetServerId", LuaGetServerId, "��ȡ��������Id", "", "", "d"},
	{"GetServerStartTime", LuaGetServerStartTime, "�õ�����ʱ��", "", "", "d"},
	

	
#ifdef GAME_SERVER
	{"CallNpc", LuaCallNpc, "�ٻ�Npc", "ddddd[d]", "dwNpcTemplateId;dwSceneId;nX;nY;nZ;nFaceDirection ���򣨿�ѡ��;", ""},
	{"AddNpc", LuaAddNpc, "�ٻ�Npc", "odddd[d]", "npcĿ��;dwSceneId;nX;nY;nZ;nFaceDirection ���򣨿�ѡ��;", ""},
	{"SetNpcRegenerationInfo", LuaSetNpcRegenerationInfo, "����NPC����������", "dddddddd[ds]", "dwNpcId;nX;nY;nZ;nFaceDirection;nRegenerationTime;nNormalAIType;nRelation;dwExValue;szExInfo;", "1/0"},
	{"RemoveNpc", LuaRemoveNpc, "ɾ��Npc", "d[d]", "dwNpcId;bRegenerate;", ""},
	{"GetDistance", LuaGetDistance, "�õ�����֮��ľ����ƽ��", "dddd", "X1;Y1;X2;Y2;", ""},
	{"StartOfflineFight", LuaStartOfflineFight, "", "dddddd", "dwStartPlayer;dwOfflinePlayer;dwStartRoleMapNpcId;dwStartPetMapNpcId;dwOfflineRoleMapNpcId;dwOfflinePetMapNpcId;", ""},
	{"GetPosition", LuaGetPosition, "���ݷ���;���õ�xyz���Ŀ���", "ddddd", "nX;nY;nZ;nDirection;nDistance;", ""},
	{"GetDirection", LuaGetDirection, "�õ�������ķ���", "dddd", "nX1;nY1;nX2;nY2;", ""},
	{"CallDoodad", LuaCallDoodad, "����Doodad", "dd???", "dwDoodadTemplateId;���䷢���ߣ�һ����˭���һ����;ӵ�еõ�������ʸ�����б�����ݵ��䷢���ߺ͵���ģʽɸѡ��һ���ɼ��б�;table {dwSceneId = XXX, nX = XX, nY = XX, nZ = XX};table {nGenre = XXX, nDetail = XX, nParticular = XX, nLevel = XX, nAmount = XX};", ""},
	{"RemoveDoodad", LuaRemoveDoodad, "ɾ��Doodad", "d", "dwDoodadId;", ""},
	{"GetNextLevelExp", LuaGetNextLevelExp, "", "d", "nLevel;", ""},
	{"Shutdown", LuaShutdown, "�رշ�����", "", "", ""},
	{"ReloadGmList", LuaReloadGmList, "���ر�GS��GM������", "", "", ""},
	{"IsDevMode", LuaIsDevMode, "�Ƿ��ڲ����԰�", "", "", "d"},
	{"CenterExecute", LuaCenterExecute, "��Coordinatorִ�нű�ָ��", "{s}", "szCall��Ҫִ�к�������������;", ""},
	{"GetIsSwimByPlayerId", LuaGetIsSwimByPlayerId, "�Ƿ�����Ӿ״̬", "d", "���id;", ""},
	{"LeaveOverallTeam", LuaLeaveOverallTeam, "�뿪���������Ŷ�", "o", "pPlayer;", ""},
	{"CheckRemoveBladeState", LuaCheckRemoveBladeState, "ȡ������״̬", "o", "pPlayer;", ""},
#endif // #ifdef GAME_SERVER

#ifdef GAME_CLIENT
	{"GetPing", LuaGetPing, "��ȡping������ʱ��", "", "", "d"},
	{"GetClientPlayerId", LuaGetClientPlayerId, "��ÿͻ����Լ���Id��", "", "", "d"},
	{"Console", LuaConsole, "�򿪿���̨���", "", "", "d"},
	{"ShutDown", LuaShutDown, "�رտͻ�������", "", "", "d"},
	{"GetServerTime", LuaGetServerTime, "��ȡ������ʱ�䣨���������ݵ�¼ʱ������ʱ���������", "", "", "d"},
#endif // #ifdef GAME_CLIENT
};
