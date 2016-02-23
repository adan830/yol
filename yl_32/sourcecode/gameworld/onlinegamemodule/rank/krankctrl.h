#ifndef __KRANKCTRL_H__
#define __KRANKCTRL_H__

#include "onlinegameworld/kcharacterctrlbase.h"
#include "config/kcharacterdef.h"
#include "rankdef.h"

class KPlayer;

class KRankCtrl : public KCharacterCtrlBase
{
public:
	enum 
	{	emKCtrlId = emKCHARACTER_CTRL_PLAYER_RANK,	};


public:

	explicit KRankCtrl(KCharacter& rcPlayer);
	virtual ~KRankCtrl();

	virtual BOOL Init();
	virtual BOOL UnInit() { return TRUE; }
	virtual BOOL Active();
	virtual BOOL OnLogin();

	virtual BOOL OnDbLoad(LPCBYTE pData, SIZE_T uSize);
	virtual BOOL OnDbSave(LPBYTE pBuffer, SIZE_T uBuffSize, SIZE_T& uUsedSize);

public:
	//ͬ��"��������"��"ս������"
	BOOL SyncRoleRanks();
	
	BOOL SyncPetLvRanks();
	BOOL SyncPetFSRanks();
	BOOL SyncRideRanks();
	BOOL SyncMpjjRanks();
	BOOL SyncLgRanks();
	BOOL SyncSmzcRanks();
	BOOL SyncTongFSRanks();
	BOOL SyncTongSrRanks();


	
	BOOL SyncLastUpdateTime(INT nRankId);

	
	//ͬ��"ȫ��弶"�
	BOOL SyncRankRoleLvOfOpenServer();
	BOOL SyncRankRideLV();
	BOOL SyncRankArean();
	BOOL SyncPetLV();
	BOOL SyncLGRank_OS();
	BOOL SyncRankTower();
	BOOL SyncRoleFightScore_OS();

private:
	INT GetRoleRankNum();

	INT GetPetLvRankNum();

	INT GetPetFSRankNum();
	
	INT GetRideRankNum();

private:
	KPlayer& m_rcPlayer;	// �������

private:
	std::map<INT, DWORD> m_mapLastTakeAwardTime;		// �ϴ��콱ʱ��

public:
	VOID InitLastTakeAwardTime();

	BOOL SetLastTakeAwardTime(INT nRankId, DWORD dwTime);

	DWORD GetLastTakeAwardTime(INT nRankId);


};

#endif