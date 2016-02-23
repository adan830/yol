/* -------------------------------------------------------------------------
//	�ļ���		��	KinScript_table.hpp
//	������		��	LuaScriptTool
//	��������	��	���ļ���VisualStudio�����ɣ��벻Ҫ�ֶ��޸ģ���
//	ʹ�÷���	��	����Ӧ��CPP�ļ�ĩ�ˣ�include���ļ�
//
// -----------------------------------------------------------------------*/

CONST SCRIPT_FUNCTION arFunction[]	=  
{
	{"CreateTongRequest", LuaCreateTongRequest, "��������", "dsd", "dwPlayerId���峤;szTongName�ַ�������������;nTemplateIndexΪ����ģ������;", "�����ɹ���1������ʧ�ܣ�0"},
	{"InvitePlayerJoinTongRequest", LuaInvitePlayerJoinTongRequest, "�������", "ds", "dwPlayerId;szMemberName;", "��"},
	{"InvitePlayerJoinTongRespond", LuaInvitePlayerJoinTongRespond, "����", "ds", "dwPlayerId;szMemberName;", "��"},
	{"ApplyKickOutTongMemberRequest", LuaApplyKickOutTongMemberRequest, "����", "dd", "dwPlayerId;nMemberId;", "��"},
	{"ApplyTongRosterRequest", LuaApplyTongRosterRequest, "������", "ddd", "dwPlayerId;nLastUpdateFrame;dwMemberList;", "��"},
	{"ApplyTongInfoRequest", LuaApplyTongInfoRequest, "ApplyTongInfo", "dd", "dwPlayerId;nLastUpdateFrame;", "��"},
	{"ApplyRepertoryPageRequest", LuaApplyRepertoryPageRequest, "�ֿ����", "d", "dwPlayerId;", "��"},
	{"ModifyTongSchemaRequest", LuaModifyTongSchemaRequest, "ModifyTongSchema", "d", "dwPlayerId;", "��"},
	{"ApplyQuitTongRequest", LuaApplyQuitTongRequest, "�˳�����", "d", "dwPlayerId;", "��"},
	{"GetKinLevelByPlayerId", LuaGetKinLevelByPlayerId, "�������id�õ����ڼ���ȼ�", "d", "dwPlayerId;", "��"},
	{"SetApplyerState", LuaSetApplyerState, "�����ܾ�����������", "dddd", "dwOperatorId;dwApplyerId;dwTongId;dwPlayerId;", "��"},
	{"UpgradeKin", LuaUpgradeKin, "��������", "d", "dwPlayerId;", "��"},
	{"ChangeTongMemberGroupRequest", LuaChangeTongMemberGroupRequest, "���ļ����Ա��", "ddd", "dwPlayerId;dwTargetMemberId;nTargetGroup;", "��"},
	{"ChangeTongMasterRequest", LuaChangeTongMasterRequest, "�ƽ��峤", "dd", "dwPlayerId;dwNewMasterId;", "��"},
	{"GetKinActivityOpenTimes", LuaGetKinActivityOpenTimes, "�õ����м����Ŀ���ʱ��", "", "", "��"},
	{"ChangeTongMemberRemarkRequest", LuaChangeTongMemberRemarkRequest, "���ļ����Աremark", "dds", "dwPlayerId;dwTargetMemberId;szRemark;", "��"},
	{"GetTongDescriptionRequest", LuaGetTongDescriptionRequest, "ȡ�ü�ͥ����", "d", "dwTongId;", "�����ִ�"},
	{"GetCurrentTime", LuaGetCurrentTime, "�õ���ǰʱ��", "", "", ""},
	{"GetPlayerConnectIndex", LuaGetPlayerConnectIndex, "ȡ��������ӵ�gs����", "d", "dwPlayerId;", ""},
	{"GetTongMembers", LuaGetTongMembers, "ȡ�ó�Ա��Ϣ", "d", "dwPlayerId;", ""},
	{"ResetTongMemberDailyContribution", LuaResetTongMemberDailyContribution, "���ü����Աÿ�չ��׶�", "d", "dwPlayerId;", ""},
	{"GetTongMember", LuaGetTongMember, "ȡ�ó�Աid�б�", "d", "dwTongId;", ""},
	{"SaveMoneyInTongRequest", LuaSaveMoneyInTongRequest, "��Ǯ", "ddddd", "dwPlayerId;dwPealNum;dwJadeiteNum;dwAgateNum;dwDiamondNum;", "��"},
	{"PayTongSalaryRequest", LuaPayTongSalaryRequest, "нˮ���", "dd", "dwPlayerId;nTotalSalary;", "��"},
	{"GetTongSalaryRequest", LuaGetTongSalaryRequest, "��ȡнˮ", "d", "dwPlayerId;", "��"},
	{"GetOnlineAndHaveKinPlayerIds", LuaGetOnlineAndHaveKinPlayerIds, "��ȡ�����������м�������id", "", "", "��"},
	{"GetTongSalaryFailRespond", LuaGetTongSalaryFailRespond, "��ȡ����ʧ��", "ddd", "dwTongId;dwPlayerId;nSalary;", "��"},
	{"ApplyOpenTongRepertoryRequest", LuaApplyOpenTongRepertoryRequest, "�򿪲ֿ�", "d", "dwPlayerId;", "��"},
	{"ChangeTongCampRequest", LuaChangeTongCampRequest, "�ı����Camp", "d", "dwPlayerId;", "��"},
	{"TakeTongRepertoryItemToPosRequest", LuaTakeTongRepertoryItemToPosRequest, "��", "d", "dwPlayerId;", "��"},
	{"TakeTongRepertoryItemRequest", LuaTakeTongRepertoryItemRequest, "��", "d", "dwPlayerId;", "��"},
	{"TakeTongRepertoryItemRespond", LuaTakeTongRepertoryItemRespond, "��", "d", "dwPlayerId;", "��"},
	{"PutTongRepertoryItemToPosRequest", LuaPutTongRepertoryItemToPosRequest, "��", "d", "dwPlayerId;", "��"},
	{"PutTongRepertoryItemRequest", LuaPutTongRepertoryItemRequest, "��", "d", "dwPlayerId;", "��"},
	{"PutTongRepertoryItemRespond", LuaPutTongRepertoryItemRespond, "��", "d", "dwPlayerId;", "��"},
	{"UnlockTongRepertoryGridRequest", LuaUnlockTongRepertoryGridRequest, "��", "d", "dwPlayerId;", "��"},
	{"ExchangeTongRepertoryItemPosRequest", LuaExchangeTongRepertoryItemPosRequest, "��", "d", "dwPlayerId;", "��"},
	{"ApplyStackTongRepertoryItemRequest", LuaApplyStackTongRepertoryItemRequest, "��", "d", "dwPlayerId;", "��"},
	{"StackTongRepertoryItemRequest", LuaStackTongRepertoryItemRequest, "��", "d", "dwPlayerId;", "��"},
	{"SetKinRepertoryEnable", LuaSetKinRepertoryEnable, "�򿪹رռ���ֿ⹦��", "d", "1��ʾ������0��ʾ�ر�;", "��"},
	{"SetKinRentEnable", LuaSetKinRentEnable, "�򿪹رռ���ֿ���蹦��", "d", "1��ʾ������0��ʾ�ر�;", "��"},
	{"SetKinRentPeriod", LuaSetKinRentPeriod, "����װ������ʱ�䣬����Ϊ��λ", "d", "ʱ��;", "��"},
	{"ImpeachKinMaster", LuaImpeachKinMaster, "�����峤�ɹ������峤�ƽ���������", "dd", "������ID;�峤����������ʱ��;", "d"},
};
