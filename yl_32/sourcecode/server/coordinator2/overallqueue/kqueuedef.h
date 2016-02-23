
#pragma once

#define MAX_OVERALL_TEAM_NUM 3	// ������3��

// �������id��connidx�ϳɶ�̬����
#define DYNAMIC_TEAM_INDEX(nPlayerId, nConnIdx) ((nPlayerId) | (nConnIdx) << 16)

#define GET_COMBINED_MEMBER_ID(nCombineIdx) ((nCombineIdx) & 0xFFFF)
#define GET_COMBINED_CONNIDX(nCombineIdx) ( (0xFFFF0000 & (nCombineIdx)) >> 16)

#pragma	pack(1)

// master �洢����ṹ

struct KOVERALL_MEMBER
{
	INT nConnectIdx;
	INT nMemberId;
	CHAR szMemberName[MAX_NAME_LEN];
	BYTE byLevel;
	BYTE bySex;
	INT nFightScore;
	BYTE byPrepare;
};

struct KOVERALL_TEAM_INFO
{
	CHAR szCreaterName[MAX_NAME_LEN];
	INT nRequireFightscore;
	DWORD dwLeaderCombinedIdx;
	BYTE byStarting;		// �Ƿ��Ѿ���ʼ����

	std::list<KOVERALL_MEMBER> listMembers;
};


// ��ҿ����������Ҫ����Ϣ
struct KCROSS_SV_ROLEINFO
{
	INT nInstanceMapId;
	INT nInstanceMapCopyIdx;
	DWORD dwTeamId;
};

typedef std::map<DWORD, KOVERALL_TEAM_INFO> MAP_MULTI_TEAM_INFO;		// �洢һ����ͼid����Ŷ���Ϣ

typedef std::map<INT, MAP_MULTI_TEAM_INFO> MAP_OVERALL_TEAMS;		// �洢�������Ŷ���Ϣ


// slave �洢����ṹ
struct KSLAVE_TEAM_INFO
{
	CHAR szCreaterName[MAX_NAME_LEN];
	INT nRequireFightscore;
	DWORD dwCombinedIdx;
	BYTE byCurrentMemberNum;
};

typedef std::list<KSLAVE_TEAM_INFO> LIST_SLAVE_TEAMS;
typedef std::map<INT, LIST_SLAVE_TEAMS> MAP_SLAVE_TEAMS;

enum emOVERALL_TEAM_RESULT
{
	emOVERALL_JOINTEAM_FULL = 1, // ������Ա������ʧ��
	emOVERALL_JOINTEAM_NOT_EXIST, // ���鲻���ڼ���ʧ��
	emOVERALL_JOINTEAM_ALREADY,	// �ظ�����
	emOVERALL_LEAVETEAM_SELF, // �Լ��뿪����
	emOVERALL_BE_KICKED,	// ���ӳ��߳�����
	emOVERALL_LEAVE_NO_TIPS,	// ���鿪ʼ���Զ�ɾ��
	emOVERALL_TEAM_DISMISSED,	// �����ɢ
	emOVERALL_TEAM_STARTING,	// �����Ѿ�����
};

#pragma pack()
