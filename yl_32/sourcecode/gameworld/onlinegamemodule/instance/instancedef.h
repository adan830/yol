#ifndef _INSTANCEDEF_H__
#define _INSTANCEDEF_H__

#include "serverbase/protocol/Relay_GS_Protocol.h"

typedef std::list<KTEAM_INFO> LIST_OVERALL_TEAMS;
typedef std::map<INT, LIST_OVERALL_TEAMS> MAP_OVERALL_TEAMS;

// ���˸�����Ϣ
struct KMultiInstanceInfo
{
	DWORD dwStartTime;		// ��ս��ʼʱ��
	INT nState;				// ��ս״̬
	INT nRushStar;			// ��ս����
	INT nRushMapId;			// ѡ����ս��mapId
};

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

#endif // _INSTANCEDEF_H__