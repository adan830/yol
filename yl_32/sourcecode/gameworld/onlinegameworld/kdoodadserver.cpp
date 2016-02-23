/* -------------------------------------------------------------------------
//	�ļ���		��	KDoodadServer.cpp
//	������		��	simon
//	����ʱ��	��	2010/3/15 9:38:07
//	��������	��	
//
// -----------------------------------------------------------------------*/
#ifdef GAME_SERVER

#include "stdafx.h"
#include "onlinegameworld/kdoodad.h"
#include "onlinegameworld/kdoodadserver.h"
#include "onlinegameworld/synchelper.h"
#include "kplayerbaseprocess.h"
#include "onlinegameworld/kplayer.h"
#include "onlinegameworld/korpgworld.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// -------------------------------------------------------------------------



// -------------------------------------------------------------------------

KDoodadServer::KDoodadServer(KDoodad& rcDoodad) : m_rcDoodad(rcDoodad)
{
}
KDoodadServer::~KDoodadServer(void)
{
}

BOOL KDoodadServer::SyncChangeRegion()
{
	IKScene* pScene = m_rcDoodad.GetScene();
	QCONFIRM_RET_FALSE(pScene);

	// broadcast to new neighbors
	TKTraverseHelper<KPlayer> cTravHelper;
	pScene->FindNewNeighborPlayers(cTravHelper, &m_rcDoodad);

	if (m_rcDoodad.IsVisible() && cTravHelper.m_vObjList.size() > 0)
	{
		KS2C_SYNC_DOODAD sData;
		sData.byProtocol = emKPBP_S2C_SYNC_DOODAD;
		sData.dwId = m_rcDoodad.m_dwId;
		sData.dwTemplateId = m_rcDoodad.m_dwTemplateId;
		m_rcDoodad.GetPosition(sData.nX, sData.nY, sData.nZ);
		sData.nGenre = m_rcDoodad.m_nGenre;
		sData.nDetail = m_rcDoodad.m_nDetail;
		sData.nParticular = m_rcDoodad.m_nParticular;
		sData.nLevel = m_rcDoodad.m_nLevel;
		sData.nAmount = m_rcDoodad.m_nAmount;

		sData.byAutoPickUp = 0;
		if(m_rcDoodad.m_nVisibleMode == emDoodadVisibleSelf)
		{
			sData.byAutoPickUp = 1;
		}
		/*
		sData.nMoveState = m_rcDoodad.m_eMoveState;
		sData.nVelocityXY = m_rcDoodad.m_nVelocityXY;
		sData.nDirectionXY = m_rcDoodad.m_nDirectionXY;
		m_rcDoodad.GetDestination(sData.nDestX, sData.nDestY, sData.nDestZ);
		sData.nDoodadState = m_rcDoodad.GetState();
		*/
		std::vector<KPlayer*>::iterator it = cTravHelper.m_vObjList.begin();
		for (; it != cTravHelper.m_vObjList.end(); ++it)
		{
			KPlayer* pPlayer = *it;
			QCONFIRM_CONTINUE(pPlayer);

			// ����ս������Fork״̬
			if (pPlayer->GetScene() != m_rcDoodad.GetScene())
				continue;

			if (m_rcDoodad.m_dwOwnerId != KD_BAD_ID && !m_rcDoodad.IsPlayerVisible(pPlayer))
				continue;

			g_pBaseSender->SendData(pPlayer->GetPlayerIndex(), sData);
		}

		// ���Լ����뿪ͬ�����뿪��ͬ����Χ�ڵ����
		TKTraverseHelper<KPlayer> cSyncLeavePlayers;
		pScene->FindOldNeighborPlayers(cSyncLeavePlayers, &m_rcDoodad);

		if (cSyncLeavePlayers.m_vObjList.size() > 0)
		{
			SyncToOldNeighborPlayers(cSyncLeavePlayers.m_vObjList);   
		}
	}
	if (m_rcDoodad.m_dwBroadcastFrame == 0)
		m_rcDoodad.m_dwBroadcastFrame = g_cOrpgWorld.m_dwLogicFrames;
	return TRUE;
}

BOOL KDoodadServer::SyncToOldNeighborPlayers(std::vector<KPlayer*>& vPlayers)
{
	KS2C_SYNC_LEAVE sSync;
	sSync.dwId = m_rcDoodad.GetId();

	for (std::vector<KPlayer*>::iterator it = vPlayers.begin(); it != vPlayers.end(); ++it)
	{
		KPlayer* pPlayer = *it;
		QCONFIRM_CONTINUE(pPlayer);

		if (pPlayer->GetScene() == m_rcDoodad.GetScene())
		{
			g_pBaseSender->SendData(pPlayer->GetPlayerIndex(), sSync);
		}
	}
	return TRUE;
}

// �㲥���������
BOOL KDoodadServer::BroadcastNearby(LPCVOID pbyData, SIZE_T uSize,
									KPlayerProtocolProcessor* pProtocolSender /*= NULL*/)
{
	QCONFIRM_RET_FALSE(pbyData && uSize > 0);

	// broadcast
	KBroadcastFunc cBroadcaster;
	cBroadcaster.m_pvData = pbyData;
	cBroadcaster.m_uSize = uSize;
	//cBroadcaster.m_nRange = 1; //by ldy ���ƹ㲥��Χ

	if (pProtocolSender)
		cBroadcaster.m_pProcessor = pProtocolSender;

	IKScene* pScene = m_rcDoodad.GetScene();
	ASSERT(pScene);

	return pScene->TraverseNearbyPlayers(cBroadcaster, &m_rcDoodad); // ����Χ��ҹ㲥
}

BOOL KDoodadServer::SyncExtra()
{
	BOOL bResult = FALSE;
	return bResult;
}

BOOL KDoodadServer::TeleportTo( DWORD dwSceneId, INT nX, INT nY, INT nZ )
{
	BOOL bResult = FALSE;
	// DoodadӦ�ò��ܴ��͵���������

	g_cPlayerBaseProcess.DoSyncTeleport(&m_rcDoodad, nX, nY, nZ);

	bResult = m_rcDoodad.SetPosition(nX, nY, nZ);
	m_rcDoodad.StopMoving();
	SyncChangeRegion();

	return bResult;
}

#endif // GAME_SERVER
