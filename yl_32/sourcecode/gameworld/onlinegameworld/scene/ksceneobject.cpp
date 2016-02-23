#include "stdafx.h"
#include "onlinegameworld/ksceneobject.h"
#include "kregion.h"
#include "kscene.h"
#include "onlinegameworld/korpgworld.h"
#include "kcell.h"
#include "onlinegameworld/kcharacter.h"
#include "onlinegamemodule/ai/kaivm.h" // TODO
#include "onlinegameworld/kplayer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

KSceneObject::KSceneObject()
{
	m_cRegionNode.m_pSceneObject = this;

	m_pCell = NULL;
	m_pRegion = NULL;
	m_pLastRegion = NULL;
	m_pScene = NULL;

	m_nDestX = 0;
	m_nDestY = 0;
	m_nDestZ = 0;
	m_IsSwim = FALSE;

	m_eMoveState = cmsOnStand;
	m_nDestDistance = 0;

	m_nCurrentGravity = KD_PHYSICS_EARTH_GRAVITY; // G = 9.8 m/s*s
	m_nGravity = DEFAULT_GRAVITY;

	m_nJumpSpeed = 0;

	m_nVelocityXY = 0;
	m_nDirectionXY = 0;
	m_nVelocityZ = 0;

	m_dwActiveFrame = 0;
	m_nClimbAbility = CLIMB_ABILITY;

	m_pRegenerationInfo = NULL;
	m_pszLastTrap = NULL;
	m_nMoveMode = 1;

	m_nStopedFaceDirection = -1;
}

KSceneObject::~KSceneObject()
{
	Uninit();
}

BOOL KSceneObject::Init()
{
	m_nX                = 0;
    m_nY                = 0;
    m_nZ                = 0;
    m_nTouchRange       = 0;
	m_nXCell            = 0;
    m_nYCell            = 0;
	m_nMass             = DEFAULT_MASS;
	m_nWidth            = 1;
    m_nLength           = 1;
	//m_nHeight           = 1;
	m_nHeight           = 920; // 180cm
	m_dwActiveFrame = 0;
	m_nFaceDirection = 0;
    m_nPitchDirection = 0;
	m_bVisible = TRUE;

	m_nDirectionXY = 0;
	m_nMoveSpeed = KD_BASE_RUN_SPEED;
	SetMoveSpeed(KD_BASE_RUN_SPEED);
	m_nJumpSpeed = KD_BASE_JUMP_SPEED; // ����õ�G=9.8ʱ��Ծ�߶�2m������
	m_eMoveState = cmsOnStand;

	m_bTryPathState	= FALSE;
	m_nTryPathSide		= 0;
	m_nTryPathStartFrame = 0;
	m_nMoveMode = 1;

	if (m_pRegion)
		m_cRegionNode.Remove();

	m_pCell             = NULL;
	m_pRegion           = NULL;
	m_pLastRegion       = NULL;
	m_pScene            = NULL;

	m_nClimbAbility = CLIMB_ABILITY;
	// ���ͬ������
	m_dwBroadcastFrame = 0;
#ifdef GAME_SERVER
	ResetRegionFrames(0);
#endif

	SAFE_DELETE(m_pRegenerationInfo);
	m_pszLastTrap = NULL;

	m_nStopedFaceDirection = -1;

	KObjGeneralEventCreator::Init();
	return TRUE;
}

BOOL KSceneObject::Uninit()
{
	if (m_pRegion)
		m_cRegionNode.Remove();
	if (m_pScene)
		m_pScene->RemoveNickName(m_strNickName);

#ifdef GAME_SERVER
	ResetRegionFrames(0);
#endif

	m_dwBroadcastFrame	= 0;
	m_pCell             = NULL;
	m_pRegion           = NULL;
	m_pScene            = NULL;

	m_strName.Clear();
	m_strNickName.Clear();
	m_pszLastTrap = NULL;

	SAFE_DELETE(m_pRegenerationInfo);

	KObjGeneralEventCreator::Release();

	m_nStopedFaceDirection = -1;

	return TRUE;
}

BOOL KSceneObject::CheckGameLoop(void)
{
	if (m_dwActiveFrame < g_cOrpgWorld.m_dwLogicFrames)
	{
		m_dwActiveFrame = g_cOrpgWorld.m_dwLogicFrames;
		return TRUE;
	}
	//printf("Detected Multiple Activation Within Single Logic Frame. %d, %d\n", 
	//	m_dwActiveFrame, g_cOrpgWorld.m_dwLogicFrames);
	return FALSE;
}

BOOL KSceneObject::SetPosition( INT nX, INT nY, INT nZ )
{
	//if(IS_PLAYER(GetId()))
	//{
	//	INT nDir = g_GetDirection(m_nX, m_nY, nX, nY);
	//	INT nFaceDir = GetFaceDirection();
	//	INT nDeltaDir = nDir - nFaceDir;
	//	if (nDeltaDir < 0) nDeltaDir = -nDeltaDir;
	//	if (nDeltaDir > (DIRECTION_COUNT/2)) nDeltaDir = DIRECTION_COUNT-nDeltaDir;
	//	INT nDist = g_GetDistance2(m_nX, m_nY, nX, nY);
	//	if (nDist >= 30*30)
	//	{
	//		QLogPrintf(LOG_DEBUG, "%s, MyId=%d, (%d,%d,%d)---->(%d,%d,%d) dist=%.2f Dir=%d, FaceDir=%d Delta=%d"
	//			, __FUNCTION__,  GetId(), m_nX, m_nY, m_nZ, nX, nY, nZ, sqrt((float)nDist)
	//			, nDir, nFaceDir, nDeltaDir
	//			);
	//	}
	//}

	BOOL        bResult             = FALSE;
	BOOL        bRetCode            = FALSE;
	KRegion*    pDstRegion          = NULL;
	int         nDstRegionX         = 0;
	int         nDstRegionY         = 0;
	KCell*      pDstCell            = NULL;
	int         nDstCellX           = 0;
	int         nDstCellY           = 0;
	int         nRelativeZ          = 0;
	int         nObstacleDirection  = -1;

	LOG_PROCESS_ERROR(nX >= 0);
	LOG_PROCESS_ERROR(nY >= 0);
	LOG_PROCESS_ERROR(m_pScene);
	LOG_PROCESS_ERROR(m_pRegion);

	nDstRegionX = nX / CELL_LENGTH / REGION_GRID_WIDTH;
	nDstRegionY = nY / CELL_LENGTH / REGION_GRID_HEIGHT;

//#ifdef _CLIENT
//	if (m_dwId == m_dwId != g_cOrpgWorld.m_dwClientPlayerId)
//	{
//		INT nDistance = g_GetDistance2(m_nX, m_nY, nX, nY);
//
//		nDistance = (int)(sqrt((float)nDistance) / 64);
//
//		if (nDistance > 0)
//		{
//			cprintf("Move: %d\n", nDistance);
//		}
//
//		// ValidateRegionsһ�����������л�Region��ʱ������
//		// ����Ҫ��һ������ΪMove������ܴܺ�,�Ѿ�����"����"��
//		bRetCode = m_pScene->ValidateRegions(nDstRegionX, nDstRegionY);
//		LOG_PROCESS_ERROR(bRetCode);
//	}
//#endif

	pDstRegion = m_pScene->GetRegion(nDstRegionX, nDstRegionY);
//#ifdef _CLIENT
//	if (pDstRegion == NULL && m_dwId != g_cOrpgWorld.m_dwClientPlayerId)
//	{
//		OnRemove();
//		goto EXIT0;
//	}
//#endif

	PROCESS_ERROR(pDstRegion);

	nDstCellX = nX / CELL_LENGTH % REGION_GRID_WIDTH;
	nDstCellY = nY / CELL_LENGTH % REGION_GRID_HEIGHT;    

	pDstCell = pDstRegion->GetProximalCellForObj(
		nDstCellX, nDstCellY, nZ, m_nHeight, false, TRUE, &nRelativeZ);
	LOG_PROCESS_ERROR(pDstCell);    

	if (pDstRegion != m_pRegion)
	{
		bRetCode = ChangeRegion(pDstRegion);
		LOG_PROCESS_ERROR(bRetCode);
	}

	m_nX     = nX;
	m_nY     = nY;
	m_nZ     = pDstCell->m_wHighLayer * POINT_PER_ALTITUDE + nRelativeZ;

	m_nXCell = nDstCellX;
	m_nYCell = nDstCellY;

	SetCell(pDstCell);

	bResult = true;
EXIT0:
	return bResult;
}

void KSceneObject::SetCell(KCell* pCell)
{
	LPCSTR pszNewTrap = NULL;
	LPCSTR pszLastTrap = m_pszLastTrap;

	if (pCell && pCell->m_BaseInfo.dwScriptIndex)
		pszNewTrap = m_pRegion->GetScriptByIndex(pCell->m_BaseInfo.dwScriptIndex);

	m_pCell = pCell; // ע����trap��˳��trapʱִ�д��ͻ����룩
	m_pszLastTrap = pszNewTrap;

	if(IS_PLAYER(GetId()))
	{
		if (pCell != NULL && pCell->m_BaseInfo.dwCellType == ctWaterArea) // ����ˮ��
		{
			m_nVelocityXY = KD_BASE_SWIM_SPEED * VELOCITY_ZOOM_COEFFICIENT;
			m_IsSwim = TRUE;
		}
		else
		{
			if (m_nVelocityXY == KD_BASE_SWIM_SPEED * VELOCITY_ZOOM_COEFFICIENT) // ����Ӿ״̬
			{
				m_nVelocityXY = GetMoveSpeed() * VELOCITY_ZOOM_COEFFICIENT;
			}
			m_IsSwim = FALSE;
		}
	}

	// Ŀ��cellΪ�ջ���ԭ��trap��ͬ
	if (pszLastTrap &&
		( !pszNewTrap || strncmp(pszNewTrap, pszLastTrap, MAX_NAME_LEN) != 0))
	{
		OnLeaveTrap(pszLastTrap);
	}

	//�ȵ���Trap
	if (pszNewTrap &&
		( !pszLastTrap || strncmp(pszNewTrap, pszLastTrap, MAX_NAME_LEN) != 0))
	{
		OnTrap(pszNewTrap);
	}
	
}

BOOL KSceneObject::Activate()
{
	BOOL bResult = FALSE;

	// ������RegionActivator����ֹ�ظ�����
	//bResult = CheckGameLoop();
	//PROCESS_ERROR(bResult); // �п��ܸո��ƶ���һ����û�������Region

	ASSERT(m_pScene);
	ASSERT(m_pRegion);

#ifdef GAME_CLIENT
	if (m_dwId == g_cOrpgWorld.m_dwClientPlayerId)
	{
		bResult = m_pScene->ValidateRegions(m_pRegion->m_nRegionX, m_pRegion->m_nRegionY);
		LOG_PROCESS_ERROR(bResult);
	}
#endif // GAME_CLIENT

#ifdef GAME_SERVER
	bResult = m_pScene->ValidateRegions(m_pRegion->m_nRegionX, m_pRegion->m_nRegionY);
	LOG_PROCESS_ERROR(bResult);
#endif

	//ProcessMove();

#ifdef GAME_SERVER
	// TODO: if is npc && fight? patrol?
	m_pRegion->SetActive();
#endif // GAME_SERVER

//EXIT1:
	bResult = TRUE;
EXIT0:
	return bResult;
}

BOOL KSceneObject::ChangeRegion(KRegion* pDestRegion)
{
	BOOL bResult  = FALSE;

	//printf("***ChangeRegion***");

	LOG_PROCESS_ERROR(m_pRegion);
	LOG_PROCESS_ERROR(pDestRegion);

	m_dwBroadcastFrame = 0;

#ifdef GAME_CLIENT
	if (IS_PLAYER(m_dwId) && m_dwId == g_cOrpgWorld.m_dwClientPlayerId)
	{
		bResult = m_pScene->ValidateRegions(pDestRegion->m_nRegionX, pDestRegion->m_nRegionY);
		LOG_PROCESS_ERROR(bResult);
	}
#else
	bResult = m_pScene->ValidateRegions(pDestRegion->m_nRegionX, pDestRegion->m_nRegionY);
	LOG_PROCESS_ERROR(bResult);
	//{
		// TODO: �����Npc�������
		//if (m_bFightState || m_AIData.nPatrolPathID > 0)
		//{
		//	pDestRegion->SetActive();
		//}
	//}

	UpdateRegionFrames(m_pRegion, pDestRegion);
	
#endif

	m_cRegionNode.Remove();
	if (IS_NPC(m_dwId))
	{
		pDestRegion->m_cNpcList.AddTail(&m_cRegionNode);
	}
	else if (IS_PLAYER(m_dwId))
	{
		pDestRegion->m_cPlayerList.AddTail(&m_cRegionNode);
	}
	else if (IS_DOODAD(m_dwId))
	{
		pDestRegion->m_cDoodadList.AddTail(&m_cRegionNode);
	}
	else
	{
		LOG_PROCESS_ERROR( !"Unknown ScnObjType!");
	}

	m_pLastRegion = m_pRegion;
	m_pRegion = pDestRegion;

	bResult = TRUE;
EXIT0:
	return bResult;
}

void KSceneObject::ResetRegionEnterAndLeaveFrame(KRegion* pCenterRegion)
{
	int nLeft       = 0;
	int nRight      = 0;
	int nBottom     = 0;
	int nTop        = 0;
	int nIndex      = 0;

	QCONFIRM(pCenterRegion);

	// 1. ����Region�����ڽ�Region��EnterFrame����Ϊ��ǰ֡
	nLeft       = pCenterRegion->m_nRegionX - m_pScene->m_nBroadcastRegion;
	nRight      = pCenterRegion->m_nRegionX + m_pScene->m_nBroadcastRegion;
	nBottom     = pCenterRegion->m_nRegionY - m_pScene->m_nBroadcastRegion;
	nTop        = pCenterRegion->m_nRegionY + m_pScene->m_nBroadcastRegion;

	for (int nX = nLeft; nX <= nRight; nX++)
	{
		for (int nY = nBottom; nY <= nTop; nY++)
		{
			KRegion* pRegion = m_pScene->GetRegion(nX, nY);
			if (pRegion)
			{
				pRegion->m_nEnterFrame = 0;
				pRegion->m_nLeaveFrame = 0;
			}
		}
	}
}

void KSceneObject::ResetRegionFrames(int nRadius)
{
	int nRegionCount = (nRadius * 2 + 1) * (nRadius * 2 + 1);

	m_vRegionEnterFrameTable.resize(nRegionCount * 2 + 1);

	for (int i = 0; i < nRegionCount; i++)
	{
		m_vRegionEnterFrameTable[i] = g_cOrpgWorld.m_dwLogicFrames;
	}

	m_vRegionLeaveFrameTable.resize(nRegionCount * 2 + 1);

	for (int i = 0; i < nRegionCount; i++)
	{
		m_vRegionLeaveFrameTable[i] = 0;
	}
}

BOOL KSceneObject::UpdateRegionFrames(KRegion* pFromRegion, KRegion* pToRegion)
{
	int nLeft       = 0;
	int nRight      = 0;
	int nBottom     = 0;
	int nTop        = 0;
	int nIndex      = 0;

	QCONFIRM_RET_FALSE(m_pScene);

	ResetRegionEnterAndLeaveFrame(pFromRegion);
	ResetRegionEnterAndLeaveFrame(pToRegion);

	// 1. ����Region�����ڽ�Region��EnterFrame����Ϊ��ǰ֡
	nLeft       = pToRegion->m_nRegionX - m_pScene->m_nBroadcastRegion;
	nRight      = pToRegion->m_nRegionX + m_pScene->m_nBroadcastRegion;
	nBottom     = pToRegion->m_nRegionY - m_pScene->m_nBroadcastRegion;
	nTop        = pToRegion->m_nRegionY + m_pScene->m_nBroadcastRegion;

	for (int nX = nLeft; nX <= nRight; nX++)
	{
		for (int nY = nBottom; nY <= nTop; nY++)
		{
			KRegion* pRegion = m_pScene->GetRegion(nX, nY);
			if (pRegion)
			{
				pRegion->m_nEnterFrame = g_cOrpgWorld.m_dwLogicFrames;
			}
		}
	}

	// 2. ����Region�����ڽ�Region��EnterFrame���õ�Region,��Ȼ,���ֻḲ����Region����ĸ�ֵ
	nLeft       = pFromRegion->m_nRegionX - m_pScene->m_nBroadcastRegion;
	nRight      = pFromRegion->m_nRegionX + m_pScene->m_nBroadcastRegion;
	nBottom     = pFromRegion->m_nRegionY - m_pScene->m_nBroadcastRegion;
	nTop        = pFromRegion->m_nRegionY + m_pScene->m_nBroadcastRegion;

	for (int nX = nLeft; nX <= nRight; nX++)
	{
		for (int nY = nBottom; nY <= nTop; nY++)
		{
			KRegion* pRegion = m_pScene->GetRegion(nX, nY);
			if (pRegion)
			{
				if (pRegion->m_nEnterFrame != g_cOrpgWorld.m_dwLogicFrames) // �뿪��ɫ��ͬ����Χ
				{
				    pRegion->m_nLeaveFrame = g_cOrpgWorld.m_dwLogicFrames;
				}

				QCONFIRM_RET_FALSE(nIndex < (int)m_vRegionEnterFrameTable.size());
				pRegion->m_nEnterFrame = m_vRegionEnterFrameTable[nIndex];
			}

			nIndex++;
		}
	}

	// 3. ����Region�Լ��ڽ�Region��EnterFrame�洢������Լ�����
	nLeft       = pToRegion->m_nRegionX - m_pScene->m_nBroadcastRegion;
	nRight      = pToRegion->m_nRegionX + m_pScene->m_nBroadcastRegion;
	nBottom     = pToRegion->m_nRegionY - m_pScene->m_nBroadcastRegion;
	nTop        = pToRegion->m_nRegionY + m_pScene->m_nBroadcastRegion;

	nIndex = 0;

	for (int nX = nLeft; nX <= nRight; nX++)
	{
		for (int nY = nBottom; nY <= nTop; nY++)
		{
			KRegion* pRegion = m_pScene->GetRegion(nX, nY);
			if (pRegion)
			{
				QCONFIRM_RET_FALSE(nIndex < (int)m_vRegionEnterFrameTable.size());
				m_vRegionEnterFrameTable[nIndex] = pRegion->m_nEnterFrame;
			}
			nIndex++;
		}
	}

	// 4. ����Region�Լ��ڽ�Region��leaveFrame�洢������Լ�����
	nLeft       = pFromRegion->m_nRegionX - m_pScene->m_nBroadcastRegion;
	nRight      = pFromRegion->m_nRegionX + m_pScene->m_nBroadcastRegion;
	nBottom     = pFromRegion->m_nRegionY - m_pScene->m_nBroadcastRegion;
	nTop        = pFromRegion->m_nRegionY + m_pScene->m_nBroadcastRegion;

	nIndex = 0;

	for (int nX = nLeft; nX <= nRight; nX++)
	{
		for (int nY = nBottom; nY <= nTop; nY++)
		{
			KRegion* pRegion = m_pScene->GetRegion(nX, nY);
			if (pRegion)
			{
				QCONFIRM_RET_FALSE(nIndex < (int)m_vRegionLeaveFrameTable.size());
				m_vRegionLeaveFrameTable[nIndex] = pRegion->m_nLeaveFrame;
			}
			nIndex++;
		}
	}
	return TRUE;
}

BOOL KSceneObject::Jump(BOOL bSyncSelf /*= FALSE*/ )
{
	BOOL bResult = FALSE;

	switch (m_eMoveState)
	{
	case cmsOnRun:
		{
			Jump(FALSE, m_nDirectionXY, FALSE);
		}
		break;
	case cmsOnStand:
		{
			Jump(TRUE, m_nDirectionXY, FALSE);
		}
		break;
	default:
		break;
	}

	bResult = TRUE;
//EXIT0:
	return bResult;
}

BOOL KSceneObject::JumpTo(INT nX, INT nY, INT nZ)
{
	GoTo(nX, nY, nZ);
	Jump();

	INT nDistance = (INT)sqrt((double) (m_nX - nX) * (m_nX - nX) + (m_nY - nY) * (m_nY - nY));
	//m_nVelocityZ = KD_PHYSICS_EARTH_GRAVITY * GAME_FPS * nDistance / m_nVelocityXY;
	m_nVelocityZ = (INT)sqrt((double) KD_PHYSICS_EARTH_GRAVITY * GAME_FPS * nDistance / 3);
	m_nVelocityXY = m_nVelocityZ * 3 / 2;

	return TRUE;
}

BOOL KSceneObject::GoTo( INT x, INT y, INT z, BOOL bSyncSelf /*= FALSE*/ )
{
	BOOL bResult = FALSE;

	//printf("sObj [%d] GoTo [%d, %d, %d] Region[%d, %d]\n", m_dwId, nX, nY, nZ,
	//	nX / REGION_GRID_WIDTH / CELL_LENGTH,	nY / REGION_GRID_HEIGHT / CELL_LENGTH);

	m_nDestX = x;
	m_nDestY = y;
	m_nDestZ = z;

	m_nDirectionXY = g_GetDirection(m_nX, m_nY, m_nDestX, m_nDestY);
	m_bTryPathState = FALSE;

	// �趨�ƶ�����
	m_nVelocityXY = this->GetMoveSpeed() * VELOCITY_ZOOM_COEFFICIENT;

	if (m_eMoveState != cmsOnJump && m_eMoveState != cmsOnDeath)
		SetMoveState(cmsOnRun);

	bResult = TRUE;
//EXIT0:
	return bResult;
}

BOOL KSceneObject::KnockTo(INT nX, INT nY, INT nZ, INT nDirection)
{
	KCharacter* pCharacter = (KCharacter*)this;
	/*if(pCharacter->GetIsFix() > 0 || pCharacter->GetIsStun() > 0)
		return FALSE;*/

	m_nDestX = nX;
	m_nDestY = nY;
	m_nDestZ = nZ;

	//m_nDirectionXY = nDirection;
	// �趨�ƶ�����
	//m_nVelocityXY = this->GetMoveSpeed() * 5 * VELOCITY_ZOOM_COEFFICIENT;
	m_nVelocityXY = 64 * VELOCITY_ZOOM_COEFFICIENT; // ���˹̶�16��ÿ��

	SetMoveState(cmsOnKnockedBack);

	return TRUE;
}

BOOL KSceneObject::Pull(INT nX, INT nY, INT nZ, INT nDirection)
{
	KCharacter* pCharacter = (KCharacter*)this;
	/*if(pCharacter->GetIsFix() > 0 || pCharacter->GetIsStun() > 0)
		return FALSE;*/

	m_nDestX = nX;
	m_nDestY = nY;
	m_nDestZ = nZ;

	//m_nDirectionXY = nDirection;
	// �趨�ƶ�����
	m_nVelocityXY = this->GetMoveSpeed() * 8 * VELOCITY_ZOOM_COEFFICIENT;

	SetMoveState(cmsOnPull);

	return TRUE;
}

BOOL KSceneObject::CheckObstacleDest(INT nStartX, INT nStartY, INT nStartZ, INT nEndX, INT nEndY, INT nEndZ, INT nTouchRange, INT& nLastOkX, INT& nLastOkY)
{
	INT nDistance = 0;
	INT nLastDistance = 0;
	INT nObStacleCount = 0;
	INT nDirection = 0;
	INT nStepLength = CELL_LENGTH / 2;
	INT nDeltaX = 0;
	INT nDeltaY = 0;
	INT nDestX = 0;
	INT nDestY = 0;
	INT             nDestCellX              = 0;
	INT             nDestCellY              = 0;
	INT             nDestRegionX            = 0;
	INT             nDestRegionY            = 0;
	KRegion*        pDestRegion             = NULL;
	KCell*          pDestCell               = NULL;
	INT             nRelativeZ              = 0;

	// ���ϴ�����ֵ��������ʼ��
	nLastOkX = nStartX;
	nLastOkY = nStartY;

	nTouchRange = 3;

	KScene* pScene = (KScene*)GetScene();
	QCONFIRM_RET_FALSE(pScene);

	nDirection = g_GetDirection(nStartX, nStartY, nEndX, nEndY);

	nDistance = g_GetDistance2(nStartX, nStartY, nEndX, nEndY);

	while(nDistance > CELL_LENGTH * CELL_LENGTH / 4 * nTouchRange)
	{
		nLastDistance = nDistance;

		nDeltaX = nStepLength * g_Cos(nDirection) / SIN_COS_NUMBER;
		nDeltaY = nStepLength * g_Sin(nDirection) / SIN_COS_NUMBER;

		nDestX = nStartX + nDeltaX;
		nDestY = nStartY + nDeltaY;

		nDestCellX      = nDestX / CELL_LENGTH % REGION_GRID_WIDTH;
		nDestCellY      = nDestY / CELL_LENGTH % REGION_GRID_HEIGHT;

		nDestRegionX    = nDestX / CELL_LENGTH / REGION_GRID_WIDTH;
		nDestRegionY    = nDestY / CELL_LENGTH / REGION_GRID_HEIGHT;

		QCONFIRM_RET_FALSE(nDestRegionX < REGION_GRID_WIDTH);
		QCONFIRM_RET_FALSE(nDestRegionY < REGION_GRID_HEIGHT);
		pDestRegion = pScene->GetRegion(nDestRegionX, nDestRegionY);
		QCONFIRM_RET_FALSE(pDestRegion);

		pDestCell = pDestRegion->GetProximalCellForObj(nDestCellX, nDestCellY, nStartZ, m_nHeight, TRUE, FALSE, &nRelativeZ);

		if (nRelativeZ > 0 && nRelativeZ < CRITICAL_JUMP_HEIGHT)
		{
			//if (m_eMoveState == cmsOnStand || m_eMoveState == cmsOnWalk || m_eMoveState == cmsOnRun)
			if (GetMoveState() == cmsOnRun ||
				GetMoveState() == cmsOnWalk ||
				GetMoveState() == cmsOnStand)
			{
				// ע��,�����0������Ӱ�쵽��Ч��
				// ���������ǲ��򻬵�,������ﲻ��0,������б�����ƶ�ʱ��״̬������
				nRelativeZ = 0;
			}
		}

		if(!pDestCell)
		{
			return FALSE;  // ���ϰ�
		}
		else
		{
			nLastOkX = nStartX;  // ���ѭ��û�ϰ����������������Ϊ0����ô����start������ϰ� (�������ϴ���������
			nLastOkY = nStartY;

			nStartX = nDestX;
			nStartY = nDestY;
			nStartZ = pDestCell->m_wHighLayer * POINT_PER_ALTITUDE + nRelativeZ;
		}

		nDistance = g_GetDistance2(nStartX, nStartY, nEndX, nEndY);

		if(nDistance > nLastDistance)
			break;
	}

	return TRUE;
}

BOOL KSceneObject::IsNearby( KSceneObject* pTarget, INT nDistance/* = REGION_GRID_WIDTH * LOGICAL_CELL_CM_LENGTH*/)
{
	BOOL    bResult     = FALSE;
	INT     nXb         = 0;
	INT     nYb         = 0;
	INT     nZb         = 0;
	PROCESS_ERROR(pTarget);

	PROCESS_ERROR(m_pScene == pTarget->m_pScene); // ����ͬһ��������
	PROCESS_ERROR(m_pCell);
	PROCESS_ERROR(pTarget->m_pCell);

	bResult = pTarget->GetPosition(nXb, nYb, nZb);
	PROCESS_ERROR(bResult);

	bResult = g_InRange(m_nX, m_nY, ZPOINT_TO_XYPOINT(m_nZ),
		nXb, nYb, ZPOINT_TO_XYPOINT(nZb),
		nDistance * CELL_LENGTH / LOGICAL_CELL_CM_LENGTH);
	PROCESS_ERROR(bResult);
	bResult = TRUE;
EXIT0:
	return bResult;
}


BOOL KSceneObject::IsNearbyIn2D( KSceneObject* pTarget, INT nDistance )
{
	BOOL    bResult     = FALSE;
	INT     nXb         = 0;
	INT     nYb         = 0;
	INT     nZb         = 0;
	INT		nRealDistance = 0;
	nDistance = nDistance / 2;

	
	PROCESS_ERROR(pTarget);

	PROCESS_ERROR(m_pScene == pTarget->m_pScene); // ����ͬһ��������
	PROCESS_ERROR(m_pCell);
	PROCESS_ERROR(pTarget->m_pCell);

	bResult = pTarget->GetPosition(nXb, nYb, nZb);
	PROCESS_ERROR(bResult);

	nRealDistance = g_GetDistance2(m_nX, m_nY, nXb, nYb);
	PROCESS_ERROR(nRealDistance <= nDistance);

	bResult = TRUE;
EXIT0:
	return bResult;
}

BOOL KSceneObject::ProcessMove()
{
	BOOL bRet = FALSE;
	INT nEarthPos = 0;

	assert(m_pScene);
	assert(m_pRegion);

	if (m_pCell->m_BaseInfo.dwCellType == ctWater)
		nEarthPos = m_pCell->m_wLowLayer * POINT_PER_ALTITUDE;
	else
		nEarthPos = 1048576;//m_pCell->m_wHighLayer * POINT_PER_ALTITUDE;  // �̶�Ϊ0��

	if (m_nZ - nEarthPos > 0)
	{
		// ����״̬���¼���
		m_nVelocityZ -= m_nCurrentGravity;
		MAKE_IN_RANGE(m_nVelocityZ, MIN_VELOCITY_Z, MAX_VELOCITY_Z);
	}

	/*BOOL needOutPut = FALSE;
	if (GetMoveState() == cmsOnKnockedBack)
	{
		needOutPut = TRUE;
	}*/

	ProcessHorizontalMove();

	//ProcessVerticalMove(); // TODO��û�д�ֱ�ƶ����Ƚ�����

	/*if (needOutPut)
	{
		KPlayer* pPlayer = (KPlayer*)this;
		printf("\nLogicFrame: %d  X: %d Y: %d Z: %d", pPlayer->m_cPlayerServer.m_dwVirtualFrame, m_nX, m_nY, m_nZ);
	}*/

	bRet = TRUE;
EXIT0:
	return bRet;
}

BOOL KSceneObject::StopMoving()
{
	m_nVelocityXY = 0;
	m_nVelocityZ = 0;
	m_nDestX = m_nX;
	m_nDestY = m_nY;
	m_nDestZ = m_nZ;

	if (GetMoveState() != cmsOnStand)
	{
		SetMoveState(cmsOnStand);
	}

	return TRUE;
}

BOOL KSceneObject::SetNickName( LPCSTR pszNickName )
{
	QCONFIRM_RET_FALSE(m_pScene);
	QCONFIRM_RET_FALSE(m_strNickName == ""); // ����ֻ������һ��

	BOOL bRet = m_pScene->AddNickName(pszNickName, this);
	QCONFIRM_RET_FALSE(bRet && "NickName already exists!");

	m_strNickName = pszNickName;
	return TRUE;
}

BOOL KSceneObject::SetRegenerationInfo( const KREGENERATION_INFO& info )
{
	SAFE_DELETE(m_pRegenerationInfo);
	m_pRegenerationInfo = new KREGENERATION_INFO;
	QCONFIRM_RET_FALSE(m_pRegenerationInfo);
	::memcpy(m_pRegenerationInfo, &info, sizeof(KREGENERATION_INFO));
	return TRUE;
}

BOOL KSceneObject::IsWithinSyncRange(KSceneObject* pTarget)
{
	QCONFIRM_RET_FALSE(pTarget);

	QCONFIRM_RET_FALSE(pTarget->m_pScene);
	QCONFIRM_RET_FALSE(m_pScene);
	QCONFIRM_RET_FALSE(pTarget->m_pRegion);
	QCONFIRM_RET_FALSE(m_pRegion);

	if (pTarget->m_pScene == m_pScene)
	{
		INT nRegionDiffX = abs(pTarget->m_pRegion->m_nRegionX - m_pRegion->m_nRegionX);
		INT nRegionDiffY = abs(pTarget->m_pRegion->m_nRegionY - m_pRegion->m_nRegionY);

		if (nRegionDiffY <= m_pScene->m_nBroadcastRegion && nRegionDiffX <= m_pScene->m_nBroadcastRegion)
			return TRUE;
	}
	return FALSE;
}

DWORD KSceneObject::GetSceneId()
{
	return m_pScene->GetId();
}

BOOL KSceneObject::Jump(BOOL bStandJump, INT nJumpDirection, BOOL bSyncSelf)
{
	BOOL bResult                = false;
	BOOL bRetCode               = false;
	INT  nDestX                 = 0;
	INT  nDestY                 = 0;
	INT  nDestDirection         = 0;
	INT  nVelocityXY            = 0;
	INT  nDirectionXY           = 0;
	INT  nConvergenceSpeed      = 0;
	INT  nVelocityZ             = 0;
	INT  nDirectionMargin       = 0;
	INT  nJumpSpeedXY           = 0;
	INT  nSwimWaterline         = GET_SWIM_WATER_LINE(m_nHeight);
	INT  nWaterLine             = GetWaterline();

	LOG_PROCESS_ERROR(nJumpDirection >= 0 && nJumpDirection < DIRECTION_COUNT);

	// �����ٴ���Ծ
	PROCESS_ERROR(m_eMoveState != cmsOnJump);

	SetMoveState(cmsOnJump);

	//if (!bStandJump)
	//{
	//	if (m_eMoveState == cmsOnWalk)
	//	{
	//		nJumpSpeedXY = GetWalkSpeed();
	//	}
	//	else if (m_eMoveState == cmsOnStand || m_eMoveState == cmsOnRun || m_eMoveState == cmsOnJump)
	//	{
	//		nJumpSpeedXY = m_nRunSpeed;
	//	}
	//	else if (m_eMoveState == cmsOnFloat || m_eMoveState == cmsOnSwim || m_eMoveState == cmsOnSwimJump)
	//	{
	//		nJumpSpeedXY = m_nRunSpeed / 2;
	//	}

	//	if (m_bSlip)
	//	{
	//		INT nAlpha = m_pCell->GetGradientDirection();
	//		if (g_Cos(nAlpha - nJumpDirection) <= SIN_COS_NUMBER / 2)
	//		{
	//			goto EXIT0;
	//		}
	//	}
	//}

	nDestDirection      = bStandJump ? m_nFaceDirection : nJumpDirection;
	nVelocityXY         = nJumpSpeedXY * VELOCITY_ZOOM_COEFFICIENT;
	nDirectionXY        = nDestDirection;
	nConvergenceSpeed   = nJumpSpeedXY;
	nVelocityZ          = m_nJumpSpeed;

	nDirectionMargin = nDestDirection - m_nFaceDirection;
	if (nDirectionMargin > DIRECTION_COUNT / 2)
	{
		nDirectionMargin = DIRECTION_COUNT - nDirectionMargin;
	}
	else if (nDirectionMargin < - DIRECTION_COUNT / 2)
	{
		nDirectionMargin = nDirectionMargin + DIRECTION_COUNT;
	}

	LOG_PROCESS_ERROR(nDirectionMargin >= -DIRECTION_COUNT / 2 &&
		nDirectionMargin <= DIRECTION_COUNT / 2);

	if (abs(nDirectionMargin) > 80)
	{
		nVelocityXY         /= 2;
		nConvergenceSpeed   /= 2;
	}

	nDestX              = m_nX + MOVE_DEST_RANGE * g_Cos(nDestDirection) / SIN_COS_NUMBER;
	nDestY              = m_nY + MOVE_DEST_RANGE * g_Sin(nDestDirection) / SIN_COS_NUMBER;

	//bRetCode = EmendateDestCoordinate(nDestX, nDestY);
	//LOG_PROCESS_ERROR(bRetCode);

	//if (nWaterLine < nSwimWaterline)
	//{
	//	PROCESS_ERROR(m_nJumpCount < m_nMaxJumpCount && m_nJumpCount < MAX_JUMP_COUNT);
	//	m_nJumpCount++;

	//	SetMoveState(cmsOnJump);
	//}
	//else
	//{
	//	SetMoveState(cmsOnSwimJump);
	//}

	LOG_PROCESS_ERROR(nVelocityXY >= 0 && nVelocityXY <= MAX_ZOOM_VELOCITY);
	LOG_PROCESS_ERROR(nVelocityZ >= MIN_VELOCITY_Z && nVelocityZ <= MAX_VELOCITY_Z);

	//m_nDestX            = nDestX;
	//m_nDestY            = nDestY;

	//m_nVelocityXY       = nVelocityXY;
	//m_nConvergenceSpeed = nConvergenceSpeed;
	//m_nDirectionXY      = nDirectionXY;
	m_nVelocityZ        = nVelocityZ;
	// TODO: ��Ҫ��Ŀ���ʱ��Ծ��ص�Ҳ���ԭĿ���Զ

	//#if defined(GAME_SERVER)
	//	InvalidateMoveState(0, bSyncSelf);
	//#endif

	bResult = true;
EXIT0:
	return bResult;
}

void KSceneObject::ProcessHorizontalMove()
{
	// ����ʱ�����沿��������Ժ��л��ˣ�ҲҪ����
	if (m_nVelocityXY > 0)
	{
		INT nDistance = g_GetDistance2(m_nX, m_nY, m_nDestX, m_nDestY);
		if (nDistance > CELL_LENGTH * CELL_LENGTH / 2)
		{
			m_nFaceDirection = g_GetDirection(m_nX,
				m_nY,
				m_nDestX,
				m_nDestY);
		}
	}

	// TODO: ��ʱ��������
	m_nDirectionXY = m_nFaceDirection;

	//if (m_eMoveState == cmsOnWalk || m_eMoveState == cmsOnRun)
		ProcessHorizontalMoveSmart();
	/*else
		ProcessHorizontalMoveStupid();*/
}

void KSceneObject::ProcessHorizontalMoveSmart()
{
	INT             nRetCode        = false;
	INT             nMoveDistance   = 0;

	PROCESS_ERROR(m_nVelocityXY);

	nMoveDistance = m_nVelocityXY / VELOCITY_ZOOM_COEFFICIENT;

	//if (m_eMoveState == cmsOnWalk || m_eMoveState == cmsOnRun || m_eMoveState == cmsOnDash || m_eMoveState == cmsOnPull)
	//{
	//	if (!m_bSlip)
	//	{
	//if (m_eMoveState == cmsOnRun)
	//{
	//		ASSERT(m_pCell);
	//		INT nGradient = m_pCell->GetGradientDegree(); // ����д���ã��ϲ���sobj�ͺ���
	//		nMoveDistance = nMoveDistance * g_Cos(nGradient) / SIN_COS_NUMBER;
	//}
	//	}
	//}

	while (nMoveDistance >= CELL_LENGTH)
	{
		CellMoveSmart(CELL_LENGTH);
		PROCESS_ERROR(m_pScene);
		nMoveDistance -= CELL_LENGTH;
	}

	if (nMoveDistance > 0)
	{
		CellMoveSmart(nMoveDistance);
		PROCESS_ERROR(m_pScene);
		nMoveDistance = 0;
	}

EXIT0:
	return;
}

BOOL KSceneObject::CellMoveSmart(INT nStepLength)
{
	BOOL bResult            = false;
	INT  nRetCode           = false;
	INT  nObstacleNormal    = -1;
	INT  nObstacleDirection = -1;
	INT  nMoveRetCode       = mrInvalid;
	INT  nTrySpeed          = 0;   
	INT  nTryDirection      = 0;
	INT  nDestDirection     = 0;

	nDestDirection = g_GetDirection(m_nX, m_nY, m_nDestX, m_nDestY);

	// ֻ����Щ״̬��Ҫ���"����Ŀ��",��Ծ״̬�Ǽ��"���"�л�״̬��,�����������
	// ����״̬��,����վ��״̬����Ϊ�򻬶�������ƶ�,������ν"����Ŀ��"
	//if (
	//	m_eMoveState == cmsOnWalk || m_eMoveState == cmsOnRun || m_eMoveState == cmsOnSwim ||
	//	m_eMoveState == cmsOnKnockedBack || m_eMoveState == cmsOnKnockedOff
	//	)
	//{
	if (m_nVelocityXY > 0)
	{
		INT nDistance = g_GetDistance2(m_nX, m_nY, m_nDestX, m_nDestY);

		if (nDistance <= CELL_LENGTH * CELL_LENGTH / 2)
		{
			m_nVelocityXY       = 0;
			//m_nConvergenceSpeed = 0;

			//if (m_eMoveState == cmsOnSwim)
			//{
			//	SetMoveState(cmsOnFloat);
			//}
			//else
			//{
			//	SetMoveState(cmsOnStand);
			//}

			nMoveRetCode = mrReachTarget;
			goto EXIT1;
		}
	}
	//}

	if (!m_bTryPathState)
	{
		INT nDelta = 0;

		nMoveRetCode = TryMove(nStepLength, nDestDirection, NULL);
		if (nMoveRetCode == mrSucceed)
		{
			m_nDirectionXY = nDestDirection;
			goto EXIT1;
		}
		PROCESS_ERROR(nMoveRetCode == mrObstacle && m_eMoveState == cmsOnRun);

		// �ж���·����
		for (nDelta = DIRECTION_COUNT / 16; nDelta < DIRECTION_COUNT / 2; nDelta += DIRECTION_COUNT / 16)
		{
			nTryDirection = nDestDirection - nDelta;

			nMoveRetCode = TryMove(nStepLength, nTryDirection, NULL);
			if (nMoveRetCode == mrSucceed)
			{
				m_bTryPathState = true;
				m_nTryPathSide  = 0;
				m_nTryPathStartFrame = g_cOrpgWorld.m_dwLogicFrames;
				m_nDirectionXY = nTryDirection;
				break;
			}
			PROCESS_ERROR(nMoveRetCode == mrObstacle);

			nTryDirection = nDestDirection + nDelta;

			nMoveRetCode = TryMove(nStepLength, nTryDirection, NULL);
			if (nMoveRetCode == mrSucceed)
			{
				m_bTryPathState = true;
				m_nTryPathSide  = 1;
				m_nTryPathStartFrame = g_cOrpgWorld.m_dwLogicFrames;
				m_nDirectionXY = nTryDirection;
				break;
			}
			PROCESS_ERROR(nMoveRetCode == mrObstacle);
		}

		PROCESS_ERROR(nDelta < DIRECTION_COUNT / 2);

		goto EXIT1;
	}

	// ����·״̬:
	if (g_cOrpgWorld.m_dwLogicFrames > (DWORD)m_nTryPathStartFrame + GAME_FPS)
	{
		m_bTryPathState = false;
		nMoveRetCode = mrObstacle;
		m_nTryPathStartFrame = 0;
		goto EXIT0;
	}

	nMoveRetCode = TryMove(nStepLength, nDestDirection, NULL);
	if (nMoveRetCode == mrSucceed)
	{
		m_nDirectionXY  = nDestDirection;
		m_bTryPathState = false;
		m_nTryPathStartFrame = 0;
		goto EXIT1;
	}
	PROCESS_ERROR(nMoveRetCode == mrObstacle);

	if (m_nTryPathSide == 0)
	{
		INT nDelta = 0;

		// ���Լ����������·
		for (nDelta = DIRECTION_COUNT / 16; nDelta < DIRECTION_COUNT / 2; nDelta += DIRECTION_COUNT / 16)
		{
			nTryDirection = nDestDirection - nDelta;

			nMoveRetCode = TryMove(nStepLength, nTryDirection, NULL);
			if (nMoveRetCode == mrSucceed)
			{
				m_nDirectionXY = nTryDirection;
				break;
			}
			PROCESS_ERROR(nMoveRetCode == mrObstacle);
		}

		PROCESS_ERROR(nDelta < DIRECTION_COUNT / 2);
	}
	else
	{
		INT nDelta = 0;

		// ���Լ������ұ���·
		for (nDelta = DIRECTION_COUNT / 16; nDelta < DIRECTION_COUNT / 2; nDelta += DIRECTION_COUNT / 16)
		{
			nTryDirection = nDestDirection + nDelta;

			nMoveRetCode = TryMove(nStepLength, nTryDirection, NULL);
			if (nMoveRetCode == mrSucceed)
			{
				m_nDirectionXY = nTryDirection;
				break;
			}
			PROCESS_ERROR(nMoveRetCode == mrObstacle);
		}

		PROCESS_ERROR(nDelta < DIRECTION_COUNT / 2);
	}

	PROCESS_ERROR(nMoveRetCode == mrSucceed);

EXIT1:
	bResult = true;
EXIT0:

	m_nDirectionXY = m_nDirectionXY % DIRECTION_COUNT;
	if (m_nDirectionXY < 0)
	{
		m_nDirectionXY += DIRECTION_COUNT;
	}
	ASSERT(m_nDirectionXY >= 0 && m_nDirectionXY < DIRECTION_COUNT);

	switch (nMoveRetCode)
	{
	case mrSucceed:
		break;

	case mrObstacle:
		m_nVelocityXY = 0;
		/*if (m_eMoveState == cmsOnRun ||
			m_eMoveState == cmsOnWalk)*/
		if(m_eMoveState != cmsOnDeath)
		{
			SetMoveState(cmsOnStand);
		}
		//m_nConvergenceSpeed = 0;

		//if (m_eMoveState == cmsOnWalk || m_eMoveState == cmsOnRun || m_eMoveState == cmsOnDash)
		//{
		//	// ��Щ״̬,�������ϰ�ʱ��תΪվ��
		//	SetMoveState(cmsOnStand);
		//}
		//else if (m_eMoveState == cmsOnSwim)
		//{
		//	SetMoveState(cmsOnFloat);
		//}

		//m_AIVM.FireEvent(aevOnPathFailed, m_dwID, 0);
		((KCharacter*)this)->m_AIVM.FireEvent(aevOnPathFailed, m_dwId, 0);
		break;

	case mrDeleteSelf:
		break;

	case mrOutOfMap:
		//if (
		//	m_eMoveState == cmsOnWalk || m_eMoveState == cmsOnRun || m_eMoveState == cmsOnJump ||
		//	m_eMoveState == cmsOnDash
		//	)
		//{
		//	// ��Щ״̬,�������ϰ�ʱ��תΪվ��
		//	SetMoveState(cmsOnStand);
		//}
		//else if (m_eMoveState == cmsOnSwim)
		//{
		//	SetMoveState(cmsOnFloat);
		//}
		//m_nConvergenceSpeed = 0;
		SetMoveState(cmsOnStand);
		break;

	case mrReachTarget:
		((KCharacter*)this)->m_AIVM.FireEvent(aevOnPathSuccess, m_dwId, 0);
		//m_AIVM.FireEvent(aevOnPathSuccess, m_dwID, 0);
		OnReachTarget();
		/*if (m_eMoveState == cmsOnRun ||
			m_eMoveState == cmsOnWalk)*/
		if(m_eMoveState != cmsOnDeath)
		{
			SetMoveState(cmsOnStand);
		}
		break;

	default:
		break;
	}
	//if (nMoveRetCode != mrSucceed)
	//	printf("[%d] cm %d\n", m_dwId, nMoveRetCode);
	return bResult;
}

BOOL KSceneObject::ProcessHorizontalMoveStupid()
{
	INT             nRetCode        = false;
	INT             nMoveDistance   = 0;

	PROCESS_ERROR(m_nVelocityXY);

	nMoveDistance = m_nVelocityXY / VELOCITY_ZOOM_COEFFICIENT;

	//printf("npc %d horizontal move %d,%d,%d\n", 
	//	m_dwID, 
	//	m_nX, 
	//	m_nY, 
	//	m_nZ);

	//if (m_eMoveState == cmsOnWalk || m_eMoveState == cmsOnRun || m_eMoveState == cmsOnDash || m_eMoveState == cmsOnPull)
	//{
	//	if (!m_bSlip)
	//	{
	//		INT nGradient = m_pCell->GetGradientDegree();
	//		nMoveDistance = nMoveDistance * g_Cos(nGradient) / SIN_COS_NUMBER;
	//	}
	//}

	while (nMoveDistance >= CELL_LENGTH)
	{
		CellMoveStupid(CELL_LENGTH);
		PROCESS_ERROR(m_pScene);
		nMoveDistance -= CELL_LENGTH;
	}

	if (nMoveDistance > 0)
	{
		CellMoveStupid(nMoveDistance);
		PROCESS_ERROR(m_pScene);
		nMoveDistance = 0;
	}

	nRetCode = true;
EXIT0:
	return nRetCode;
}

BOOL KSceneObject::CellMoveStupid(INT nStepLength)
{
	BOOL bResult            = false;
	INT  nRetCode           = false;
	INT  nObstacleNormal    = -1;
	INT  nObstacleDirection = -1;
	INT  nMoveRetCode       = mrInvalid;
	INT  nTrySpeed          = 0;   
	INT  nTryDirection      = 0;
	INT  nDestDirection     = 0;

	nDestDirection = g_GetDirection(m_nX, m_nY, m_nDestX, m_nDestY);

	// ֻ����Щ״̬��Ҫ���"����Ŀ��",��Ծ״̬�Ǽ��"���"�л�״̬��,�����������
	// ����״̬��,����վ��״̬����Ϊ�򻬶�������ƶ�,������ν"����Ŀ��"
	//if (
	//	m_eMoveState == cmsOnWalk || m_eMoveState == cmsOnRun || m_eMoveState == cmsOnSwim
	//	)
	//{
	if (m_nVelocityXY > 0)
	{
		INT nDistance = g_GetDistance2(m_nX, m_nY, m_nDestX, m_nDestY);

		// 4������������ƽ����
		if (nDistance <= CELL_LENGTH * CELL_LENGTH / 2)
		{
			m_nVelocityXY       = 0;
			if (m_eMoveState == cmsOnRun ||
				m_eMoveState == cmsOnPull ||
				m_eMoveState == cmsOnWalk)
			{
				SetMoveState(cmsOnStand);
			}

			nMoveRetCode        = mrReachTarget;
			goto EXIT1;
		}
	}
	//}

	nMoveRetCode = TryMove(nStepLength, m_nDirectionXY, &nObstacleNormal);
	PROCESS_SUCCESS(nMoveRetCode == mrSucceed);

	PROCESS_ERROR(nMoveRetCode == mrObstacle);

	//// ��Щ״̬������ҪѰ·
	//PROCESS_ERROR(
	//	m_eMoveState == cmsOnWalk || m_eMoveState == cmsOnRun ||
	//	m_eMoveState == cmsOnSwim || m_eMoveState == cmsOnDash ||
	//	m_eMoveState == cmsOnPull
	//	);

	// �������ܹ�ȡ���ϰ����߷����ʱ�����Ѱ·
	PROCESS_ERROR(nObstacleNormal != -1);

	LOG_PROCESS_ERROR(nObstacleNormal >= 0 && nObstacleNormal < DIRECTION_COUNT);
	LOG_PROCESS_ERROR(m_nDirectionXY >= 0 && m_nDirectionXY < DIRECTION_COUNT);

	if (nObstacleNormal - m_nDirectionXY > DIRECTION_COUNT / 4)
	{
		nObstacleNormal -= DIRECTION_COUNT / 2;
	}
	else if (nObstacleNormal - m_nDirectionXY < -DIRECTION_COUNT / 4)
	{
		nObstacleNormal += DIRECTION_COUNT / 2;
	}


	// �����ϰ�ʱ�Զ���·,ע��,����Ҷ���,�Ǹ���ǰ���ϰ������ж�Ӧ�����Ǹ�������·,����NPC����,ֻ�Ǹ����ϰ�����
	// �ж�Ӧ���������ĸ�������·

	// ���߷����90��,Ҳ�����ϰ������߷���
	nRetCode = g_Sin(nObstacleNormal - m_nDirectionXY);    
	if (nRetCode >= 0)
	{
		nTryDirection   = nObstacleNormal - DIRECTION_COUNT / 4;
		nTrySpeed       = nStepLength * g_Cos(m_nDirectionXY - nTryDirection) / SIN_COS_NUMBER;

		LOG_PROCESS_ERROR(nTrySpeed >= 0);

		if (nTrySpeed < 1)
		{
			nTrySpeed = 1;
		}

		for (INT i = 0; i < DIRECTION_COUNT / 4; i += DIRECTION_COUNT / 16)
		{
			nMoveRetCode = TryMove(nTrySpeed, nTryDirection - i, NULL);
			if (nMoveRetCode == mrSucceed)
			{
				break;
			}
			PROCESS_ERROR(nMoveRetCode == mrObstacle);
		}
	}
	else
	{
		nTryDirection = nObstacleNormal + DIRECTION_COUNT / 4;
		nTrySpeed     = nStepLength * g_Cos(m_nDirectionXY - nTryDirection) / SIN_COS_NUMBER;

		LOG_PROCESS_ERROR(nTrySpeed >= 0);

		if (nTrySpeed < 1)
		{
			nTrySpeed = 1;
		}

		for (INT i = 0; i < DIRECTION_COUNT / 4; i += DIRECTION_COUNT / 16)
		{
			nMoveRetCode = TryMove(nTrySpeed, nTryDirection + i, NULL);
			if (nMoveRetCode == mrSucceed)
			{
				break;
			}
			PROCESS_ERROR(nMoveRetCode == mrObstacle);
		}
	}

	PROCESS_ERROR(nMoveRetCode == mrSucceed);

EXIT1:
	bResult = true;
EXIT0:

	switch (nMoveRetCode)
	{
	case mrSucceed:
		break;

	case mrObstacle:
		m_nVelocityXY = 0;
		if (m_eMoveState == cmsOnRun ||
			m_eMoveState == cmsOnPull ||
			m_eMoveState == cmsOnWalk)
		{
			SetMoveState(cmsOnStand);
		}
		//m_nConvergenceSpeed = 0;

		//if (m_eMoveState == cmsOnWalk || m_eMoveState == cmsOnRun || m_eMoveState == cmsOnDash)
		//{
		//	// ��Щ״̬,�������ϰ�ʱ��תΪվ��
		//	// ע��,��Ծ״̬�ǲ�Ҫ��Ϊվ��,����ᵼ��"������"����
		//	SetMoveState(cmsOnStand);
		//}
		//else if (m_eMoveState == cmsOnSwim)
		//{
		//	SetMoveState(cmsOnFloat);
		//}
		break;

	case mrDeleteSelf:
		break;

	case mrOutOfMap:
		//if (
		//	m_eMoveState == cmsOnWalk || m_eMoveState == cmsOnRun || m_eMoveState == cmsOnJump ||
		//	m_eMoveState == cmsOnDash
		//	)
		//{
		//	// ��Щ״̬,�������ϰ�ʱ��תΪվ��
		//	SetMoveState(cmsOnStand);
		//}
		//else if (m_eMoveState == cmsOnSwim)
		//{
		//	SetMoveState(cmsOnFloat);
		//}
		//m_nConvergenceSpeed = 0;
		SetMoveState(cmsOnStand);
		break;

	case mrReachTarget:
		//OnReachTarget();
		break;

	default:
		break;
	}

	return bResult;
}

BOOL KSceneObject::TryMove(INT nStepLength, INT nDirection, INT* pnObstacleDirection)
{
	INT             nResult                 = mrInvalid;
	INT             nRetCode                = false;
	INT             nMargin                 = 0;
	INT             nDestX                  = 0;
	INT             nDestY                  = 0;
	INT             nDestCellX              = 0;
	INT             nDestCellY              = 0;
	KCell*          pDestCell               = NULL;
	INT             nDestRegionX            = 0;
	INT             nDestRegionY            = 0;
	KRegion*        pDestRegion             = NULL;
	KCell*          pCellNode               = NULL;
	INT             nRelativeZ              = 0;
	INT             nDeltaX                 = 0;
	INT             nDeltaY                 = 0;
	INT             nClimbAbility           = 0;
	KCell*          pNextCell               = NULL;
	BOOL            bIsChase                = false;
	BOOL            bIgnoreDynamicSwitch    = false;
	KCell*		pCurrentCell = m_pCell;
	KRegion*        pCurrentRegion = m_pRegion;
	KScene*		pScene = m_pScene;

	LOG_PROCESS_ERROR(m_pCell);
	LOG_PROCESS_ERROR(m_pRegion);
	LOG_PROCESS_ERROR(m_pScene);

	nDeltaX         = nStepLength * g_Cos(nDirection) / SIN_COS_NUMBER;
	nDeltaY         = nStepLength * g_Sin(nDirection) / SIN_COS_NUMBER;

	nDestX          = m_nX + nDeltaX;
	nDestY          = m_nY + nDeltaY;

	PROCESS_ERROR_RET_CODE(nDestX >= 0, mrOutOfMap);
	PROCESS_ERROR_RET_CODE(nDestY >= 0, mrOutOfMap);

	//PROCESS_ERROR_RET_CODE(nDestX < pScene->m_nRegionWidth * REGION_GRID_WIDTH * CELL_LENGTH, mrOutOfMap);
	//PROCESS_ERROR_RET_CODE(nDestY < pScene->m_nRegionHeight * REGION_GRID_HEIGHT * CELL_LENGTH, mrOutOfMap);

	nDestCellX      = nDestX / CELL_LENGTH % REGION_GRID_WIDTH;
	nDestCellY      = nDestY / CELL_LENGTH % REGION_GRID_HEIGHT;

	nDestRegionX    = nDestX / CELL_LENGTH / REGION_GRID_WIDTH;
	nDestRegionY    = nDestY / CELL_LENGTH / REGION_GRID_HEIGHT;

	PROCESS_ERROR_RET_CODE(nDestRegionX < REGION_GRID_WIDTH, mrOutOfMap);
	PROCESS_ERROR_RET_CODE(nDestRegionY < REGION_GRID_HEIGHT, mrOutOfMap);
	pDestRegion = pScene->GetRegion(nDestRegionX, nDestRegionY);

	if (!pDestRegion)
	{
#ifdef GAME_CLIENT
		//LOG_PROCESS_ERROR(m_dwID != g_pWorld->m_dwClientPlayerID);

		// TODO: notify removal of sobj
		//if (IS_PLAYER(m_dwID))
		//{
		//	nRetCode = g_pWorld->DelPlayer((KPlayer*)this);
		//	LOG_PROCESS_ERROR(nRetCode);
		//}
		//else
		//{
		//	nRetCode = g_pWorld->DeleteNpc((KNpc*)this);
		//	LOG_PROCESS_ERROR(nRetCode);
		//}
		nResult = mrDeleteSelf;
#endif
		goto EXIT0;
	}

	nClimbAbility = m_nClimbAbility;
	// ��Ծʱ�����ټ������������ɣ�
	if (m_eMoveState == cmsOnJump && nClimbAbility != TERRAIN_MAX_HEIGHT)
		nClimbAbility = 0;

	//bIsChase =  m_eMoveState == cmsOnRun || m_eMoveState == cmsOnWalk || m_eMoveState == cmsOnDash || m_eMoveState == cmsOnPull;
	//if (m_bFightState && IS_NPC(m_dwID) && bIsChase)
	//	nClimbAbility = INT_MAX / 2; // ��ֹ����ʱ���

	pNextCell = pCurrentCell->m_pNext;
	// ����Ѿ������˶�̬Cell����,��ô,���Զ�̬�ϰ�(һ����Ϊdisable)
	//if (pNextCell && pNextCell->m_BaseInfo.dwDynamic)
	//{
	//	KDynamicCell* pDynamicCell = (KDynamicCell*)pNextCell;
	//	BOOL          bCellEnable  = false;

	//	bCellEnable = m_pScene->GetDynamicObstacleState(pDynamicCell->m_wGroupIndex);
	//	if (bCellEnable)
	//	{
	//		INT nNextLowerLayer = pNextCell->m_wLowLayer * POINT_PER_ALTITUDE;
	//		bIgnoreDynamicSwitch = (nNextLowerLayer < m_nZ + m_nHeight);
	//	}
	//}

	pDestCell = pDestRegion->GetAdaptedCellForObj(
		nDestCellX, nDestCellY, m_nZ, nClimbAbility, 
		m_nHeight, bIgnoreDynamicSwitch,
		&nRelativeZ, pnObstacleDirection
		);
	//if (!pDestCell && nRelativeZ < m_nJumpSpeed * 64 * 100)
	//	Jump(); // experimental �Զ���Ծ
	PROCESS_ERROR_RET_CODE(pDestCell, mrObstacle);

	// ���µ����ϰ�
	if (pDestCell->GetGradientDegree() > KD_STEEP_SLOPE_GRADIENT &&
		//pDestCell->m_wHighLayer * POINT_PER_ALTITUDE > m_nZ)
		pDestCell->m_wHighLayer > pCurrentCell->m_wHighLayer &&
		nClimbAbility != TERRAIN_MAX_HEIGHT)
	{
		INT nDirectionDiff = pDestCell->GetGradientDirection() - m_nDirectionXY;
		// �ٶȷ�����б�·�������෴�������£���ֹ
		if (nDirectionDiff > KD_STEEP_SLOPE_DIRECTION || nDirectionDiff < - KD_STEEP_SLOPE_DIRECTION)
		{
			nResult = mrObstacle;
			goto EXIT0;
		}
	}

	if (nRelativeZ > 0 && nRelativeZ < CRITICAL_JUMP_HEIGHT)
	{
		//if (m_eMoveState == cmsOnStand || m_eMoveState == cmsOnWalk || m_eMoveState == cmsOnRun)
		if (m_eMoveState == cmsOnRun ||
			m_eMoveState == cmsOnWalk ||
			m_eMoveState == cmsOnStand)
		{
			// ע��,�����0������Ӱ�쵽��Ч��
			// ���������ǲ��򻬵�,������ﲻ��0,������б�����ƶ�ʱ��״̬������
			nRelativeZ = 0;
		}
	}

	//if (IS_NPC(m_dwID))
	//{
	//	KNpc*       pNpc           = (KNpc*)this;
	//	INT         nHeighMargin   = 0;

	//	if (pNpc->m_eMoveMode == mmGround && pDestCell->m_BaseInfo.dwCellType == ctWater)
	//	{
	//		INT nWaterDeepth = (pDestCell->m_wHighLayer - pDestCell->m_wLowLayer) * POINT_PER_ALTITUDE;

	//		if (!(m_bFightState && bIsChase))
	//		{
	//			// ��ֹ��ˮ
	//			PROCESS_ERROR_RET_CODE(nRelativeZ > -m_nHeight / 2, mrObstacle);
	//			PROCESS_ERROR_RET_CODE(nWaterDeepth < m_nHeight / 2, mrObstacle);
	//		}
	//	}
	//	else if (pNpc->m_eMoveMode == mmWater)
	//	{
	//		PROCESS_ERROR_RET_CODE(nRelativeZ < -m_nHeight / 2, mrObstacle);
	//	}

	//	// ��ֹ������
	//	//         if (m_eMoveState != cmsOnJump)
	//	//         {
	//	//             INT nCriticalHeight = min(CRITICAL_JUMP_HEIGHT, nClimbAbility);
	//	//             nHeighMargin = POINT_PER_ALTITUDE * ((INT)m_pCell->m_wHighLayer - (INT)pDestCell->m_wHighLayer);
	//	//             PROCESS_ERROR_RET_CODE(nHeighMargin < nCriticalHeight, mrObstacle);
	//	//         }
	//}

	m_nX = nDestX;
	m_nY = nDestY;
	m_nZ = pDestCell->m_wHighLayer * POINT_PER_ALTITUDE + nRelativeZ;

	m_nXCell = nDestCellX;
	m_nYCell = nDestCellY;

	if (pDestRegion != m_pRegion)
	{
		//		m_cRegionNode.Remove();
		//		pDestRegion->m_cPlayerList.AddTail(&m_cRegionNode);
		//		m_pRegion = pDestRegion;
		//
		//#ifdef GAME_SERVER
		//		UpdateRegionEnterFrames(pCurrentRegion, pDestRegion);
		//#endif // GAME_SERVER
		//printf("[%d] change region\n", m_dwId);
		nRetCode = ChangeRegion(pDestRegion);
		LOG_PROCESS_ERROR(nRetCode);
	}

	SetCell(pDestCell);

	//EXIT1:
	nResult = mrSucceed;
EXIT0:
	//if (nResult != mrSucceed)
	//	printf("[%d] trymove failed %d\n", m_dwId, nResult);
	return nResult;
}

BOOL KSceneObject::ProcessVerticalMove()
{
	ASSERT(m_pCell);

	KCell*    pCellNode           = NULL;
	KCell*    pNextCell           = NULL;
	INT       nWaterline          = 0;
	INT       nEarthPos           = 0;
	INT       nGradient           = 0;
	INT       nSwimWaterline      = GET_SWIM_WATER_LINE(m_nHeight);
	KCell* pCurrentCell = m_pCell;

	nGradient = pCurrentCell->GetGradientDegree();

	// ȡ�õر�߶�
	if (pCurrentCell->m_BaseInfo.dwCellType != ctWater)
	{
		nEarthPos = pCurrentCell->m_wHighLayer * POINT_PER_ALTITUDE;
	}
	else
	{
		nEarthPos = 1048576;//pCurrentCell->m_wLowLayer * POINT_PER_ALTITUDE; //�߶ȹ̶�Ϊ0��
	}

	//if (m_eMoveState == cmsOnSwim && m_nVelocityZ > 0)
	//{
	//	INT nWaterPos = m_pCell->m_wHighLayer * POINT_PER_ALTITUDE;

	//	m_nZ += m_nVelocityZ;

	//	if (m_nZ > nWaterPos - nSwimWaterline)
	//	{
	//		m_nZ = nWaterPos - nSwimWaterline;
	//	}
	//}
	//else
	{
		if (m_nZ + m_nVelocityZ <= nEarthPos)
		{
			if (m_nVelocityZ < 0)
			{
				// ���ˤ�˼���
				//ProcessDropDamage();

				// ����ٶȴ���
				ProcessDropSpeed();
			}

			if (m_eMoveState == cmsOnJump)
			{
				if (m_nVelocityXY == 0)
				{
					OnReachTarget();
					SetMoveState(cmsOnStand);
				}
				else
				{
					if (MoveMode())
						SetMoveState(cmsOnRun);
					else
						SetMoveState(cmsOnWalk);
				}
			}
			//// ���״̬�л�
			//if (m_eMoveState == cmsOnJump)
			//{
			//	if (!m_bSlip)
			//	{
			//		m_nVelocityXY = 0;
			//	}
			//	m_nConvergenceSpeed = 0;
			//	SetMoveState(cmsOnStand);
			//}

			m_nZ = nEarthPos;
		}
		//else if (
		//	IS_NPC(m_dwID) && (m_eMoveState == cmsOnRun || m_eMoveState == cmsOnWalk || 
		//	m_eMoveState == cmsOnDash || m_eMoveState == cmsOnPull || m_eMoveState == cmsOnStand)
		//	)
		//{
		//	m_nZ = nEarthPos;
		//	m_nVelocityZ = 0;
		//}
		else
		{
			m_nZ += m_nVelocityZ;
		}
	}

	// ---- ������� ---------------------------------
	// ȡ��һ����ˮ��Cell

	pCellNode = pCurrentCell->m_pNext;
	while (pCellNode)
	{
		if (pCellNode->m_BaseInfo.dwCellType != ctWater)
		{
			pNextCell = pCellNode;
			break;
		}
		pCellNode = pCellNode->m_pNext;
	}

	if (pNextCell)
	{
		INT nMaxZ   = pNextCell->m_wLowLayer * POINT_PER_ALTITUDE;
		INT nMyTop  = m_nZ + m_nHeight;

		// ����
		if (nMyTop > nMaxZ)
		{
			m_nZ = nMaxZ - m_nHeight;
			m_nVelocityZ = 0;
		}
	}

	//if (IS_PLAYER(m_dwID))
	//{
	//	ProcessDrowning();
	//}

	// ȡ�ó�ˮ���
	nWaterline = GetWaterline();
	//if (IS_NPC(m_dwID))
	//	nWaterline = 0;

	//// ��Ӿ���״̬�л�
	//switch (m_eMoveState)
	//{
	//case cmsOnStand:
	//case cmsOnWalk:
	//case cmsOnRun:
	//case cmsOnSit:
	//	if (nWaterline >= nSwimWaterline)
	//	{
	//		m_nConvergenceSpeed = 0;
	//		m_bSlip             = false;
	//		m_nVelocityXY       = 0;
	//		SetMoveState(cmsOnFloat);
	//	}
	//	break;

	//case cmsOnJump:
	//	if (m_nVelocityZ < 0 && nSwimWaterline <= nWaterline)
	//	{
	//		m_nConvergenceSpeed = 0;
	//		m_nVelocityZ        = 0;
	//		m_nVelocityXY       = 0;
	//		SetMoveState(cmsOnFloat);
	//	}
	//	break;

	//case cmsOnSwimJump:
	//	if (nSwimWaterline > nWaterline)
	//	{
	//		m_nJumpCount++;
	//		SetMoveState(cmsOnJump);
	//	}
	//	else
	//	{
	//		if (m_nVelocityZ <= 0)
	//		{
	//			m_nConvergenceSpeed = 0;
	//			m_nVelocityZ        = 0;
	//			m_nVelocityXY       = 0;
	//			SetMoveState(cmsOnFloat);
	//		}
	//	}
	//	break;

	//case cmsOnSwim:
	//case cmsOnFloat:
	//	if (nWaterline < nSwimWaterline)
	//	{
	//		//cprintf("water %d < %d, switch to stand !\n", nWaterline, nSwimWaterline);
	//		m_nConvergenceSpeed = 0;
	//		m_eMoveState        = cmsOnStand;
	//	}
	//	break;

	//default:
	//	break;
	//}

	// check jump state switching
	if (m_eMoveState == cmsOnRun ||
		m_eMoveState == cmsOnWalk ||
		m_eMoveState == cmsOnStand)
	{
		if (m_nZ - pCurrentCell->m_wHighLayer * POINT_PER_ALTITUDE > CRITICAL_JUMP_HEIGHT)
		{
			// ����
			SetMoveState(cmsOnJump);
			//m_nJumpCount++;
		}
	}
	//// ����/��״̬ʱ,������ճ���3��,�Զ�תΪ��Ծ״̬
	//if (m_eMoveState == cmsOnWalk || m_eMoveState == cmsOnRun || m_eMoveState == cmsOnSwim || m_eMoveState == cmsOnStand)
	//{
	//	if (IS_NPC(m_dwID))
	//		m_nZ = m_pCell->m_wHighLayer * POINT_PER_ALTITUDE;

	//	if (m_nZ - m_pCell->m_wHighLayer * POINT_PER_ALTITUDE > CRITICAL_JUMP_HEIGHT)
	//	{
	//		m_eMoveState = cmsOnJump;   
	//		m_nJumpCount++;
	//	}
	//}

	//if (
	//	(
	//	m_eMoveState == cmsOnStand || m_eMoveState == cmsOnRun || m_eMoveState == cmsOnWalk || 
	//	m_eMoveState == cmsOnSwim || m_eMoveState == cmsOnFloat
	//	)
	//	||
	//	(
	//	m_eMoveState == cmsOnJump && m_nWaterFlyAbility && 
	//	m_pCell->m_BaseInfo.dwCellType == ctWater && 
	//	m_nZ - m_pCell->m_wHighLayer * POINT_PER_ALTITUDE <= POINT_PER_ALTITUDE
	//	)
	//	)
	//{
	//	m_nJumpCount = 0;
	//}

	//EXIT0:
	return TRUE;
}

BOOL KSceneObject::ProcessDropSpeed()
{
	BOOL     bResult      = false;
	KCell*   pEarthCell   = NULL;
	INT      nAlpha       = 0;
	INT      nBeta        = 0;
	INT      nVelocityZ   = 0;
	INT      nVelocityXY  = 0;
	INT      nSinBeta     = g_Sin(nBeta);
	INT      nCosBeta     = g_Cos(nBeta);
	INT      nVelocityX   = 0;
	INT      nVelocityY   = 0;
	INT      nDropXY      = 0;
	INT      nDropXSub    = 0;
	INT      nDropYSub    = 0;
	INT      nSlipSpeed   = 0;

	pEarthCell = m_pCell;
	if (pEarthCell->m_BaseInfo.dwCellType == ctWater)
	{
		pEarthCell = m_pRegion->GetPreCell(m_nXCell, m_nYCell, pEarthCell);
	}
	LOG_PROCESS_ERROR(pEarthCell);

	nAlpha       = pEarthCell->GetGradientDirection();
	nBeta        = pEarthCell->GetGradientDegree();
	//nSlipSpeed   = pEarthCell->GetCriticalSlipSpeed();

	if (nBeta <= DIRECTION_COUNT / 4 / 8)
	{
		// ����������Լ򻯴���
		m_nVelocityZ = 0;
		goto EXIT0;
	}

	nVelocityZ  = m_nVelocityZ * nSinBeta / SIN_COS_NUMBER * nSinBeta / SIN_COS_NUMBER;
	nDropXY     = ZPOINT_TO_XYPOINT(m_nVelocityZ * nSinBeta * VELOCITY_ZOOM_COEFFICIENT) / SIN_COS_NUMBER * nCosBeta / SIN_COS_NUMBER;

	nDropXSub = nDropXY * g_Cos(nAlpha) / SIN_COS_NUMBER;
	nDropYSub = nDropXY * g_Sin(nAlpha) / SIN_COS_NUMBER;

	nVelocityX = m_nVelocityXY * g_Cos(m_nDirectionXY) / SIN_COS_NUMBER + nDropXSub;
	nVelocityY = m_nVelocityXY * g_Sin(m_nDirectionXY) / SIN_COS_NUMBER + nDropYSub;

	nVelocityXY = (INT)sqrt((float)(nVelocityX * nVelocityX + nVelocityY * nVelocityY));

	if (nVelocityXY >= nSlipSpeed * VELOCITY_ZOOM_COEFFICIENT/* || m_bSlip*/)
	{
		m_nVelocityZ   = nVelocityZ;
		//m_nVelocityXY  = nVelocityXY;
		//m_nDirectionXY = g_GetDirection(0, 0, nVelocityX, nVelocityY);
	}
	else
	{
		m_nVelocityZ = 0;
	}

	bResult = true;
EXIT0:
	return bResult;
}

BOOL  KSceneObject::GetWaterline()
{
	INT     nResult     = 0;

	KCell* pCurrentCell = m_pCell;
	LOG_PROCESS_ERROR(pCurrentCell);

	PROCESS_ERROR(pCurrentCell->m_BaseInfo.dwCellType == ctWater);

	PROCESS_ERROR(m_nZ - pCurrentCell->m_wHighLayer * POINT_PER_ALTITUDE <= 0);

	if (m_nZ < pCurrentCell->m_wLowLayer * POINT_PER_ALTITUDE)
	{
		m_nZ = pCurrentCell->m_wLowLayer * POINT_PER_ALTITUDE;
	}

	nResult = pCurrentCell->m_wHighLayer * POINT_PER_ALTITUDE - m_nZ;
EXIT0:
	ASSERT(nResult >= 0);
	return nResult;
}
