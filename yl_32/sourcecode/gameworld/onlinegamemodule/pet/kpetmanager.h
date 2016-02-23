
/* -------------------------------------------------------------------------
//	�ļ���		��	kpetmanager.h
//	������		��	NiuNiu
//	����ʱ��	��	2012-11-28 18:13:00
//	��������	��  
// -------------------------------------------------------------------------*/

#ifndef __KPETMANAGER_H__
#define __KPETMANAGER_H__

#include "petdef.h"
#include "onlinegameworld/kidobjpool.h"
#include "kpet.h"
#include "kride.h"
#include "Misc/qindexlist.h"

class KPlayer;

class KPetManager
{
public:
	KPetManager();
	~KPetManager();

public:
	BOOL	Init();
	BOOL	UnInit();

	INT		AddPet(DWORD dwId = 0);

	BOOL	ContactPetWithOwner(KPet* pPet, DWORD dwOwnerId);

	BOOL	RemovePet(DWORD dwId);

	KPet*	GetPetByIndex(INT nIndex);

	KPet*	GetPetById(DWORD dwId);

	// �õ��ҵ��ĵ�һֻ��Ӧ���ͺͷ�ϵ������
	KPet*   GetPetByTypeAndNature(INT nType, INT nNature);

	KPet*	GetPetByOwnerId(DWORD dwOwnerId);

	KPet*	AddPlayerPet(KPlayer* pPlayer, INT nType, INT nCharacter = 0);

	INT		AddRide(DWORD dwId = 0);

	BOOL	RemoveRide(DWORD dwId);

	KRide*	GetRideByIndex(INT nIndex);

	KRide*	GetRideById(DWORD dwId);

	KRide* AddPlayerRide(KPlayer* pPlayer, 
		INT nGenre, 
		INT nDetail, 
		INT nParticular, 
		INT nLevel, 
		INT nHungry, 
		INT nMagicRate);

	BOOL ContactRideWithOwner(KRide* pRide, DWORD dwOwnerId);

	KRide* GetRideByOwnerId(DWORD dwOwnerId);

private:
	TKIdObjPool<KPet> m_cPetPool;				// ������ϵĳ���

	TKIdObjPool<KRide> m_cRidePool;				// ��ҵ�����

	std::map<DWORD, DWORD> m_mapCharacterId2PetId;		// ��ɫID������IDӳ��(ֻӳ��ս���ĳ���)

	std::map<DWORD, DWORD> m_mapCharacterId2RideId;

	QIndexList m_cPetIdList;			// �Ѿ�ʹ�õ�id�б�
	QIndexList m_cRideIdList;		
};

extern KPetManager g_cPetMgr;

#endif
