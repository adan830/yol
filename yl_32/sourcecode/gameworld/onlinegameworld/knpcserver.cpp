

#ifdef GAME_SERVER
#include "stdafx.h"
#include "onlinegameworld/knpcserver.h"
#include "onlinegameworld/knpc.h"
#include "onlinegameworld/kbaseprotocol.h"
#include "kvarsetting.h"
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
KNpcServer::KNpcServer( KNpc& rNpc ) : m_rcNpc(rNpc), KCharacterServer(rNpc)
{

}

BOOL KNpcServer::SyncChangeRegion()
{
	IKScene* pScene = m_rcNpc.GetScene();
	QCONFIRM_RET_FALSE(pScene);

	// broadcast to new neighbors
	TKTraverseHelper<KPlayer> cTravHelper;
	pScene->FindNewNeighborPlayers(cTravHelper, &m_rcNpc);

	if (m_rcNpc.IsVisible() && cTravHelper.m_vObjList.size() > 0)
		SyncToNeighborPlayers(cTravHelper.m_vObjList);
    
	// ���Լ����뿪ͬ�����뿪��ͬ����Χ�ڵ����
	TKTraverseHelper<KPlayer> cSyncLeavePlayers;
	pScene->FindOldNeighborPlayers(cSyncLeavePlayers, &m_rcNpc);

	if (cSyncLeavePlayers.m_vObjList.size() > 0)
	{
		SyncToOldNeighborPlayers(cSyncLeavePlayers.m_vObjList);   
	}

	if (m_rcNpc.m_dwBroadcastFrame == 0)
		m_rcNpc.m_dwBroadcastFrame = g_cOrpgWorld.m_dwLogicFrames;
	return TRUE;
}

BOOL KNpcServer::FillSyncVar( KCHARACTER_VAR_SYNC_OTHER& rsVarSync, SIZE_T uInLen, SIZE_T& ruOutLen )
{
	BOOL bRet = FALSE;
	ruOutLen = 0;

	// �������ñ���
	for (UINT i = 0; i < countof(csByteVarSyncOther); ++i)
		rsVarSync.aByVarSet[i] = m_rcNpc.m_cContainer.m_cByArrayValue.GetValue(csByteVarSyncOther[i]);
	for (UINT i = 0; i < countof(csWordVarSyncOther); ++i)
		rsVarSync.aWVarSet[i] = m_rcNpc.m_cContainer.m_cWArrayValue.GetValue(csWordVarSyncOther[i]);
	for (UINT i = 0; i < countof(csDWordVarSyncOther); ++i)
		rsVarSync.aDwVarSet[i] = m_rcNpc.m_cContainer.m_cDwArrayValue.GetValue(csDWordVarSyncOther[i]);
	// �Զ�ͬ������չ����
	const KVarSetting::VEC_VARKEY& vecSyncVarKey = g_cCharacterVarSetting.GetSyncOtherTask();
	// ������vecSyncVarKey�ı���ȫ��Ҫ����ʱ���ͻ������Ƿ��㹻
	if (vecSyncVarKey.size() * sizeof(rsVarSync.aMapVarSet[0]) < uInLen)
	{
		rsVarSync.wMapVarNum = 0;
		KVarSetting::VEC_VARKEY::const_iterator it;
		for (it = vecSyncVarKey.begin(); it != vecSyncVarKey.end(); ++it)
		{
			DWORD dwValue = m_rcNpc.GetVar(it->byVarGroup, it->byVarId);
			if (dwValue)
			{
				rsVarSync.aMapVarSet[rsVarSync.wMapVarNum].byVarGroup = it->byVarGroup;
				rsVarSync.aMapVarSet[rsVarSync.wMapVarNum].byVarId = it->byVarId;
				rsVarSync.aMapVarSet[rsVarSync.wMapVarNum].dwVarValue = dwValue;
				++rsVarSync.wMapVarNum;
				ruOutLen += sizeof(rsVarSync.aMapVarSet[0]);
			}
		}

		bRet = TRUE;
	}
	else
	{
		Q_Error("Too much data to synchronize!");
	}

	return bRet;
}

BOOL KNpcServer::TeleportTo( DWORD dwSceneId, INT nX, INT nY, INT nZ )
{
	BOOL bResult = FALSE;
	// NpcӦ�ò���˲�Ƶ���������

	// ��ʱ�Ѵ���Zֵǿ����Ϊ1048576��������Ϊ������ͼ����û�и߶ȣ�ͳһ��0�㣬�߻�����ʱ��ûע����һ������ܶ����⣬Ϊ�˱�֤����������ǿ�����ã�
	// TODO: ����ֻΪ�����������Ŀ�ܼ�ʱ���ߵ�������֮������������Ŀ�õ�����룬����ȥ��
	nZ = 1048576;
	g_cPlayerBaseProcess.DoSyncTeleport(&m_rcNpc, nX, nY, nZ);

	bResult = m_rcNpc.SetPosition(nX, nY, nZ);
	m_rcNpc.StopMoving();

	return bResult;
}

BOOL KNpcServer::SyncToOldNeighborPlayers(std::vector<KPlayer*>& vPlayers)
{
	KS2C_SYNC_LEAVE sSync;
	sSync.dwId = m_rcNpc.GetId();

	for (std::vector<KPlayer*>::iterator it = vPlayers.begin(); it != vPlayers.end(); ++it)
	{
		KPlayer* pPlayer = *it;
		QCONFIRM_CONTINUE(pPlayer);

		if (pPlayer->GetScene() == m_rcNpc.GetScene())
		{
			g_pBaseSender->SendData(pPlayer->GetPlayerIndex(), sSync);
		}
	}
	return TRUE;
}

BOOL KNpcServer::SyncToNeighborPlayers( std::vector<KPlayer*>& vPlayers )
{
	SIZE_T uSizeUsed = 0;
	SIZE_T uSizeBuffer = sizeof(g_abySyncPackBuffer) - _offsetof(KS2C_SYNC_NPC, sVarSync);
	KS2C_SYNC_NPC& sData = *(KS2C_SYNC_NPC* )g_abySyncPackBuffer;
	sData = KS2C_SYNC_NPC();
	sData.dwId = m_rcNpc.m_dwId;
	QStrCpyLen(sData.szName, m_rcNpc.GetName(), sizeof(sData.szName));
	sData.dwTemplateId = m_rcNpc.m_dwTemplateId;
	sData.nMoveState = m_rcNpc.m_eMoveState;
	sData.nVelocityXY = m_rcNpc.m_nVelocityXY;
	sData.nDirectionXY = m_rcNpc.m_nDirectionXY;
	m_rcNpc.GetPosition(sData.nX, sData.nY, sData.nZ);
	m_rcNpc.GetDestination(sData.nDestX, sData.nDestY, sData.nDestZ);

	// fill variant sync
	BOOL bRet = FillSyncVar(sData.sVarSync, uSizeBuffer, uSizeUsed);
	QCONFIRM_RET_FALSE(bRet && uSizeBuffer > 0);
	uSizeUsed += _offsetof(KS2C_SYNC_NPC, sVarSync.aMapVarSet);

	for (std::vector<KPlayer*>::iterator it = vPlayers.begin(); it != vPlayers.end(); ++it)
	{
		KPlayer* pPlayer = *it;
		QCONFIRM_CONTINUE(pPlayer);

		// ֻ�е���Һ�npc��ͬһ��������ͬ��Npc�����ݣ�����ս������Fork״̬��
		if (pPlayer->GetScene() == m_rcNpc.GetScene())
		{
			if (g_cOrpgWorld.m_bDebugSelf)
				printf("[0x%08x] sync to [%u] %d,", m_rcNpc.GetId(), pPlayer->GetId(), g_cOrpgWorld.m_dwLogicFrames);

			g_pBaseSender->SendLenData(pPlayer->GetPlayerIndex(), sData, uSizeUsed);
		}
	}
	return TRUE;
}

// -------------------------------------------------------------------------
#endif // #ifdef GAME_SERVER
