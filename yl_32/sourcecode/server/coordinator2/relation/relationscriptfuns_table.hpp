/* -------------------------------------------------------------------------
//	�ļ���		��	relationscriptfuns_table.hpp
//	������		��	LuaScriptTool
//	��������	��	���ļ���VisualStudio�����ɣ��벻Ҫ�ֶ��޸ģ���
//	ʹ�÷���	��	����Ӧ��CPP�ļ�ĩ�ˣ�include���ļ�
//
// -----------------------------------------------------------------------*/

CONST SCRIPT_FUNCTION arFunction[]	=  
{
	{"CheckIsLoadEnd", LuaCheckIsLoadEnd, "����ɫ�����Ƿ�������", "d", "nAppId �������;", "TRUE ������ݼ�����ɣ�FALSE ��û�м������"},
	{"CheckCreateDepRep", LuaCheckCreateDepRep, "��鴴����ϵ�������ͳ�ͻ��ϵ", "dddd", "nType ��ϵ����;nRole �Ƿ�����λ;nAppId �������id;nDstId �Է�id;", "BOOL"},
	{"CanCreateRelation", LuaCanCreateRelation, "�������ĳ�ֹ�ϵ�����Ƿ���Խ���", "dddd", "nType Ҫ��ӵĹ�ϵ����;nRole: �����߽�ɫ��1Ϊ��λ��ϵ��0Ϊ��λ��ϵ��;nAppId ���ID;nDstId ���ID;", "BOOL �����"},
	{"CreateRelation", LuaCreateRelation, "������飬ֱ�Ӵ����˼ʹ�ϵ", "ddd[d]", "nType Ҫ��ӵĹ�ϵ����;nAppId ���ID;nDstId ���ID;bIsMaster Ĭ��Ϊ1����ʾ�Ƿ��ǹ�ϵ����λ 1��λ 0��λ;", "BOOL  ������ϵ�Ľ��"},
	{"CheckDelDepRep", LuaCheckDelDepRep, "���ɾ����ϵ�������ͳ�ͻ��ϵ", "dddd", "nType ��ϵ����;nRole �Ƿ�����λ;nAppId �������id;nDstId �Է�id;", "BOOL"},
	{"DelRelation", LuaDelRelation, "������飬ֱ��ɾ��ָ�����˼ʹ�ϵ", "ddd[d]", "nType Ҫɾ���Ĺ�ϵ����;nAppId ���ID;nDstId ��ϵ���ID;bIsMaster Ĭ��Ϊ1����ʾ�Ƿ��ǹ�ϵ����λ 1��λ 0��λ;", "BOOL  ������ϵ�Ľ��"},
	{"ResetLimtWhenCrossDay", LuaResetLimtWhenCrossDay, "�������ܶȵ����ڣ����������ÿ������", "dd", "nAppId �������id;nDstId �Է����id;", ""},
	{"AddFriendFavor", LuaAddFriendFavor, "�������ܶ�", "ddd[dd]", "nAppId ������id;nDstId �Է����id;nFavor Ҫ���ӵ����ܶ�;nMethod ;�� 0����;�� 1ͨ��ib���� Ĭ����0;bByHand �Ƿ��ֹ���ӣ����ж�ÿ�����ޣ�0��ʾϵͳ���1��ʾ�ֹ���ӣ�;", "BOOL ���Ӻ������ܶ��Ƿ�ɹ�"},
	{"SetFriendTalkTime", LuaSetFriendTalkTime, "�������һ������ʱ��", "ddd", "nAppId ������id;nDstId �Է����id;dwTime;", ""},
	{"GetRoleName", LuaGetRoleName, "��ȡ��ɫ����", "d", "nAppId ������id;", ""},
	{"SyncRelation", LuaSyncRelation, "ͬ�����й�ϵ", "d", "nAppId ������id;", ""},
	{"SyncFriendInfo", LuaSyncFriendInfo, "���������ܶȺ�ͬ��������Ϣ", "dd", "nAppId ���뷽���id;nDstId �Է����id;", "BOOL"},
	{"GetCloseFriendTimeInfo", LuaGetCloseFriendTimeInfo, "��ȡ���ѣ������˫�����ѣ���ϵ�Ƿ��Ҫ����", "d", "nAppPlayerId	���id;", "{{nPlayerId, nTime, nType}, {nPlayerId, nTime, nType}, ...}"},
	{"DelOverTimeRelation", LuaDelOverTimeRelation, "ɾ��һ�굽�ڵ����ѣ�ʦͽ�ͽ����˹�ϵ", "dddd", "nType			Ҫɾ���Ĺ�ϵ����;nMasterId		��λ���id;nTargetId		��λ���id;bIsMaster		��ɫ�Ƿ�����λ;", "BOOL			�Ƿ�ɾ���ɹ�"},
	{"GetOneRelationCount", LuaGetOneRelationCount, "��ȡָ����ĳ���˼ʹ�ϵ������", "dd[d]", "nPlayerId		���id;nType			��ϵ����;bAsMaster		�Ƿ�����λ���;", "INT			����"},
	{"HasRelation", LuaHasRelation, "����Ƿ����ָ�����˼ʹ�ϵ", "ddd[d]", "nAppId	��λid;nDstId	��λid;nType		��ϵ����;bAsMaster	����λ;", "BOOL"},
	{"GetFriendFavor", LuaGetFriendFavor, "��ȡָ����ҵ����ܶ�", "dd", "nPlayerId1	��һ�����id;nPlayerId2	�ڶ������id;", "nFavor"},
};
