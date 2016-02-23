#ifndef _ESCORTDEF_H__
#define _ESCORTDEF_H__

#pragma pack(1)

#define MAX_ESCORTPAGE_PLAYER_NUM 11	// ÿҳ��������

#define MAX_ESCORT_POS_NUM 2000		// ������ɳ�������
#ifdef VIETNAM
#define ESCORT_TIME (60*15)		// Խ������ʱ��15����
#else
#define ESCORT_TIME (60)		// ����ʱ��1����
#endif
enum ESCORT_STATE
{
	emESCORT_STATE_NONE,
	emESCORT_STATE_NORMAL,		// ������
	emESCORT_STATE_BEHIT,		// ���ټ�
	emESCORT_STATE_COMPLETE_NORMAL,	// �������
	emESCORT_STATE_COMPLETE_BEHIT, // ���ټ����
};

// ������ɽṹ
struct KPlayerEscort
{
	INT nPlayerId;
	BYTE byPlayerLevel;
	CHAR szPlayerName[_NAME_LEN];
	DWORD dwFightScore;
	BYTE byEscortLevel;		// ���ݵȼ� 1 - 5
	DWORD dwProtectRoleId;
	CHAR szProtecterName[_NAME_LEN];
	DWORD dwRoberId;		// �ټݽ�ɫid
	DWORD dwRoberFightscore;
	CHAR szRoberName[_NAME_LEN];
	INT nLeftTime;
	BYTE byIfSpeedUp;
	BYTE byEscortState;
};

// �ټݽṹ
struct KRobEscort
{
	INT nRobPlayerId;
	INT nRoberId;	// ������
	CHAR szPlayerName[_NAME_LEN];
	INT nLeftTime;
	BYTE byPlayerLevel;
	BYTE byEscortLevel;
	BYTE byCanTakeAward;
};

#pragma pack()


#endif // _ESCORTDEF_H__
