
/* -------------------------------------------------------------------------
//	�ļ���		��	kawardmanager.h
//	������		��	zhaoyu
//	����ʱ��	��	2013-8-12
//	��������	��  
// -------------------------------------------------------------------------*/

#ifndef __KAWARDMANAGER_H__
#define __KAWARDMANAGER_H__

#include "onlinegameworld/kidobjpool.h"
#include "Misc/qindexlist.h"
#include "awarddef.h"
#include "kaward.h"
#include "Runtime/qstring.h"

class KPlayer;

class KAwardManager
{
public:
	KAwardManager();
	~KAwardManager();

public:
	BOOL	Init();
	BOOL	UnInit();

	INT AddAward(DWORD dwId = 0);

	BOOL RemoveAward(DWORD dwId);

	KAward* GetAwardById(DWORD dwId);

	KAward* GetAwardByIndex(INT nIndex);

	KAward* AddPlayerAward(KPlayer* pPlayer, LPCSTR szModuleName, INT nLevel, INT nTimes = 1, INT nAwardPercent = 100, BOOL bGiveExp = TRUE);

private:
	TKIdObjPool<KAward> m_cAwardPool;

	QIndexList m_cAwardIdList;			// �Ѿ�ʹ�õ�id�б�
};

extern KAwardManager g_cAwardMgr;

#endif
