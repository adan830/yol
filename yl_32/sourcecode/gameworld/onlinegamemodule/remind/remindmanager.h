/* -------------------------------------------------------------------------
//	�ļ���		��	remindmanager.h
//	������		��	zhengbozhou
//	����ʱ��	��	2014-1-27
//	��������	��  
// -------------------------------------------------------------------------*/

#ifndef __REMIND_MANAGER_H__
#define __REMIND_MANAGER_H__
#include "stdafx.h"
#include "onlinegameworld/korpgworld.h"
#include "serverbase/protocol/Relay_GS_Protocol.h"

class RemindManager
{
public:
	RemindManager();
	~RemindManager();

	BOOL AddRemindToPlayer(INT nPlayerIndex, INT nRemindId, INT nCountDown = -1);

	BOOL RemoveRemindToPlayer(INT nPlayerIndex, INT nRemindId);

};

extern RemindManager g_cRemindManger;

#endif