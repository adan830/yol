#include "stdafx.h"
#include "AISearchTactics.h"
#include "ThreatList.h"
#include "onlinegameworld/kdoodad.h"
#include "onlinegameworld/ksceneobject.h"


#define MAX_ALARM_RANGE_REVISE 1000

bool g_CompByDistance(const KSearchNode& left, const KSearchNode& right)
{
	return left.m_nDistance2 < right.m_nDistance2;
}

int g_GetLevelByTargetLife(int nLifeConversionLevel, double fPrecentLife)
{
    int nDeltaLevel = 0;

    if (fPrecentLife < 0.5)
        nDeltaLevel += nLifeConversionLevel;
    if (fPrecentLife < 0.1)
        nDeltaLevel += nLifeConversionLevel;

    return nDeltaLevel;
}

double g_GetRangeByLevelDiff(int nLevelDiff)
{
    double fRangePercent = 1.0;

    if (nLevelDiff > 8)
        nLevelDiff = 8;
    else if (nLevelDiff < -8)
        nLevelDiff = -8;

    fRangePercent -= 0.1 * (8 - nLevelDiff) / 2;

EXIT0:
    return fRangePercent;
}

BOOL KSearchForAnyDoodad::operator ()(KDoodad* pDoodad)
{
	BOOL	bRetCode = false;
	int     nSrcZ       = 0;
	int     nDstZ       = 0;
	int		nDistance2	= 0;

	if (m_dwDoodadTemplateID && m_dwDoodadTemplateID != pDoodad->m_dwTemplateId)
		return true;

	bRetCode = g_InRange(m_pSelf, pDoodad, m_nDistance);
	if (bRetCode)
	{
		m_pResult = pDoodad;
		return false;
	}

	return true;
}

BOOL KSearchForTeamMember::operator ()(KPlayer* pPlayer)
{
    BOOL  bRetCode        = false;
    DWORD dwSelfTeamID    = m_pSelf->GetTeamId();
    DWORD dwPlayerTeamID  = pPlayer->GetTeamId();

    if (dwSelfTeamID == ERROR_ID)
        return false;

    if (dwPlayerTeamID != dwSelfTeamID)
        return true;

    bRetCode = m_pSelf->IsNearby(pPlayer, m_nDistance);
    if (bRetCode)
    {
        m_Result.push_back(pPlayer);
    }

    return true;
}

BOOL KSearchForAnyVisiblePlayer::operator()(KPlayer* pPlayer)
{
    BOOL     bRetCode   = false;
    int      nSrcZ      = 0;
    int      nDstZ      = 0;

    nSrcZ = ZPOINT_TO_ALTITUDE(m_pSelf->m_nZ + m_pSelf->m_nHeight + POINT_PER_ALTITUDE / 2);
    nDstZ = ZPOINT_TO_ALTITUDE(pPlayer->m_nZ + pPlayer->m_nHeight + POINT_PER_ALTITUDE / 2);

    bRetCode = m_pSelf->m_pScene->IsVisible(
        m_pSelf->m_nX, m_pSelf->m_nY, nSrcZ,
        pPlayer->m_nX, pPlayer->m_nY, nDstZ
    );
    if (bRetCode)
    {
        m_pResult = pPlayer;
        return false;
    }
    
    return true;
}

BOOL KSearchVisiblePlayerClosest::operator()(KPlayer* pPlayer)
{
    BOOL     bRetCode   = false;
    int      nSrcZ      = 0;
    int      nDstZ      = 0;
    int      nDistance2 = 0;

    nDistance2 = g_GetDistance2(m_pSelf->m_nX, m_pSelf->m_nY, pPlayer->m_nX, pPlayer->m_nY);
    if (nDistance2 > m_nDistance2)
        return true;

    nSrcZ = ZPOINT_TO_ALTITUDE(m_pSelf->m_nZ + m_pSelf->m_nHeight + POINT_PER_ALTITUDE / 2);
    nDstZ = ZPOINT_TO_ALTITUDE(pPlayer->m_nZ + pPlayer->m_nHeight + POINT_PER_ALTITUDE / 2);

    bRetCode = m_pSelf->m_pScene->IsVisible(
        m_pSelf->m_nX, m_pSelf->m_nY, nSrcZ,
        pPlayer->m_nX, pPlayer->m_nY, nDstZ
    );
    if (bRetCode)
    {
        m_pResult    = pPlayer;
        m_nDistance2 = nDistance2;
    }
    
    return true;
}

BOOL KSearchForCharacter::operator ()(KCharacter *pCharacter)
{
	BOOL	bRetCode	= false;
	int		nSrcZ		= 0;
	int		nDstZ		= 0;
	int		nDistance2	= 0;
	int		nAngle		= 0;
	int		nFaceTo		= 0;
	int		nCheckDistance2 = m_nDistance2;

	if (pCharacter == m_pSelf)
		return true;

	//��ʱ���룬������������NPC
	if (pCharacter->m_eMoveState == cmsOnDeath)
		return true;

    //��ʱ���룬���Խ�ͨϵͳ�ϵ�Character
    if (pCharacter->m_eMoveState == cmsOnAutoFly)
        return true;

	//����NPC�������,�������ڷ����е�Npc
	if (IS_NPC(pCharacter->m_dwId) && IS_NPC(m_pSelf->m_dwId) && pCharacter->m_bSystemShield)
        return true;

    //ս����ϵ�ж�
    int nRelation = g_GetRelation(m_pSelf, pCharacter);
    if (!(nRelation & m_nRelation))
        return true;

	//�жϾ���
	nDistance2 = g_GetDistance2(m_pSelf->m_nX, m_pSelf->m_nY, pCharacter->m_nX, pCharacter->m_nY);

	//��Χ�ܵȼ���Ӱ��
	if (m_bAdjustRangeByLevelDiff)
	{
        int nSelfLevel = m_pSelf->GetLevel();
        int nTargetLevel = pCharacter->GetLevel();
        double fDistanceAdjustRate = 1.0;

        if (m_bAdjustRangeByTargetLife)
        {
            assert(pCharacter->GetMaxLife() > 0);

            nSelfLevel += g_GetLevelByTargetLife(m_nLifeConversionLevel, (double)pCharacter->GetCurrentLife() / (double)pCharacter->GetMaxLife());
        }

		fDistanceAdjustRate = g_GetRangeByLevelDiff(nSelfLevel - nTargetLevel);
		nCheckDistance2 = (int)(nCheckDistance2 * fDistanceAdjustRate * fDistanceAdjustRate);
	}

	//��Χ��ħ������Ӱ��,������ĳ�����پ��䷶Χ��BUFF,�������鰲��
	if (m_bAdjustByAttribute)
	{
		double fSelfAlarmRangeRevise = 0.0;
		double fOtherAlarmRangeRevise = 0.0;
			
		//�Ƿ�������о����NPC
		if (pCharacter->m_nIgnoreOtherAlarmRange > 0)
		{
			return true;
		}

		fSelfAlarmRangeRevise = m_pSelf->m_nSelfAlarmRangeRevise / (double)MAX_ALARM_RANGE_REVISE;
		fOtherAlarmRangeRevise = pCharacter->m_nOtherAlarmRangeRevise / (double)MAX_ALARM_RANGE_REVISE;

		//������Χ
		if (fSelfAlarmRangeRevise < 0.0)
			fSelfAlarmRangeRevise = 0.0;
		if (fSelfAlarmRangeRevise > 1.0)
			fSelfAlarmRangeRevise = 1.0;
		if (fOtherAlarmRangeRevise < 0.0)
			fOtherAlarmRangeRevise = 0.0;
		if (fOtherAlarmRangeRevise > 1.0)
			fOtherAlarmRangeRevise = 1.0;

		fSelfAlarmRangeRevise = 1.0 - fSelfAlarmRangeRevise;
		fOtherAlarmRangeRevise = 1.0 - fOtherAlarmRangeRevise;

		nCheckDistance2 = (int)(nCheckDistance2 * fSelfAlarmRangeRevise * fSelfAlarmRangeRevise);
		nCheckDistance2 = (int)(nCheckDistance2 * fOtherAlarmRangeRevise * fOtherAlarmRangeRevise);
	}

	if (nDistance2 > nCheckDistance2)
		return true;

	//�жϽǶ�
	nFaceTo = m_pSelf->m_nFaceDirection;

	nAngle = g_GetDirection(m_pSelf->m_nX, m_pSelf->m_nY, pCharacter->m_nX, pCharacter->m_nY) - nFaceTo;
	if (nAngle < 0)
		nAngle = -nAngle;

	if (nAngle > DIRECTION_COUNT / 2)
		nAngle = DIRECTION_COUNT - nAngle;

	if (m_nAngle >= 0)
	{
		if (nAngle > m_nAngle / 2)
			return true;
	}
	else
	{
		if (nAngle <= -m_nAngle / 2)
			return true;
	}

	//�жϿɼ���
    if (m_bAdjustByVisible)
    {
        nSrcZ = ZPOINT_TO_ALTITUDE(m_pSelf->m_nZ + m_pSelf->m_nHeight + POINT_PER_ALTITUDE / 2);
        nDstZ = ZPOINT_TO_ALTITUDE(pCharacter->m_nZ + pCharacter->m_nHeight + POINT_PER_ALTITUDE / 2);

        bRetCode = m_pSelf->m_pScene->IsVisible(
            m_pSelf->m_nX, m_pSelf->m_nY, nSrcZ,
            pCharacter->m_nX, pCharacter->m_nY, nDstZ
        );
    }

	if (bRetCode)
	{
		KSearchNode SearchNode;
		SearchNode.m_pCharacter = pCharacter;
		SearchNode.m_nDistance2 = nDistance2;

		m_Result.push_back(SearchNode);
	}

	return true;
}

BOOL SearchCharacter(
    KCharacter** ppResult, 
    KCharacter* pCharacter, KCharacter* pSelf, 
    int nSearchDistance2, int nSearchAngle, int nSearchRelation, int nLifeConversionLevel, 
    BOOL bAdjustRangeByLevelDiff, BOOL bAdjustByAttribute, BOOL bAdjustRangeByTargetLife, BOOL bAdjustByVisible
)
{
    BOOL    bResult     = false;
    BOOL	bRetCode    = false;
    int		nSrcZ       = 0;
    int		nDstZ       = 0;
    int		nDistance2  = 0;
    int		nAngle      = 0;
    int		nFaceTo     = 0;
    int     nRelation   = 0;

    assert(ppResult);
    assert(pCharacter);
    assert(pSelf);

    PROCESS_ERROR(pCharacter != pSelf);
    PROCESS_ERROR(pCharacter->m_eMoveState != cmsOnDeath);
    PROCESS_ERROR(pCharacter->m_eMoveState != cmsOnAutoFly);

    //����NPC�������,�������ڷ����е�Npc
    PROCESS_ERROR(IS_PLAYER(pCharacter->m_dwId) || IS_PLAYER(pSelf->m_dwId) || !pCharacter->m_bSystemShield);

    //ս����ϵ�ж�
    nRelation = g_GetRelation(pSelf, pCharacter);
    PROCESS_ERROR(nRelation & nSearchRelation);

    //�жϾ���
    nDistance2 = g_GetDistance2(pSelf->m_nX, pSelf->m_nY, pCharacter->m_nX, pCharacter->m_nY);

    //��Χ�ܵȼ���Ӱ��
    if (bAdjustRangeByLevelDiff)
    {
        int nSelfLevel = pSelf->GetLevel();
        int nTargetLevel = pCharacter->GetLevel();
        double fDistanceAdjustRate = 1.0;

        if (bAdjustRangeByTargetLife)
        {
            assert(pCharacter->GetMaxLife() > 0);

            nSelfLevel += g_GetLevelByTargetLife(nLifeConversionLevel, (double)pCharacter->GetCurrentLife() / (double)pCharacter->GetMaxLife());
        }

        fDistanceAdjustRate = g_GetRangeByLevelDiff(nSelfLevel - nTargetLevel);
        nSearchDistance2 = (int)(nSearchDistance2 * fDistanceAdjustRate * fDistanceAdjustRate);
    }

    //��Χ��ħ������Ӱ��,������ĳ�����پ��䷶Χ��BUFF,�������鰲��
    if (bAdjustByAttribute)
    {
        double fSelfAlarmRangeRevise = 0.0;
        double fOtherAlarmRangeRevise = 0.0;

        //�Ƿ�������о����NPC
        PROCESS_ERROR(!pCharacter->m_nIgnoreOtherAlarmRange);

        fSelfAlarmRangeRevise = pSelf->m_nSelfAlarmRangeRevise / (double)MAX_ALARM_RANGE_REVISE;
        fOtherAlarmRangeRevise = pCharacter->m_nOtherAlarmRangeRevise / (double)MAX_ALARM_RANGE_REVISE;

        //������Χ
        if (fSelfAlarmRangeRevise < 0.0)
            fSelfAlarmRangeRevise = 0.0;
        if (fSelfAlarmRangeRevise > 1.0)
            fSelfAlarmRangeRevise = 1.0;
        if (fOtherAlarmRangeRevise < 0.0)
            fOtherAlarmRangeRevise = 0.0;
        if (fOtherAlarmRangeRevise > 1.0)
            fOtherAlarmRangeRevise = 1.0;

        fSelfAlarmRangeRevise = 1.0 - fSelfAlarmRangeRevise;
        fOtherAlarmRangeRevise = 1.0 - fOtherAlarmRangeRevise;

        nSearchDistance2     = (int)(nSearchDistance2 * fSelfAlarmRangeRevise * fSelfAlarmRangeRevise);
        nSearchDistance2     = (int)(nSearchDistance2 * fOtherAlarmRangeRevise * fOtherAlarmRangeRevise);
    }

    PROCESS_ERROR(nDistance2 < nSearchDistance2);

    //�жϽǶ�
    nFaceTo = pSelf->m_nFaceDirection;

    nAngle = g_GetDirection(pSelf->m_nX, pSelf->m_nY, pCharacter->m_nX, pCharacter->m_nY) - nFaceTo;
    if (nAngle < 0)
        nAngle = -nAngle;

    if (nAngle > DIRECTION_COUNT / 2)
        nAngle = DIRECTION_COUNT - nAngle;

    if (nSearchAngle >= 0)
        PROCESS_ERROR(nAngle <= nSearchAngle / 2);
    else
        PROCESS_ERROR(nAngle >= -nSearchAngle / 2);

    //�жϿɼ���
    if (bAdjustByVisible)
    {
       nSrcZ = ZPOINT_TO_ALTITUDE(pSelf->m_nZ + pSelf->m_nHeight + POINT_PER_ALTITUDE / 2);
       nDstZ = ZPOINT_TO_ALTITUDE(pCharacter->m_nZ + pCharacter->m_nHeight + POINT_PER_ALTITUDE / 2);

       bRetCode = pSelf->m_pScene->IsVisible(pSelf->m_nX, pSelf->m_nY, nSrcZ, pCharacter->m_nX, pCharacter->m_nY, nDstZ);
       PROCESS_ERROR(bRetCode);
    }

	// �鿴Ŀ���Ƿ�����
	bRetCode = (pCharacter->IsSkillHidden(pSelf) == FALSE);
	PROCESS_ERROR(bRetCode);

    *ppResult = pCharacter;

    bResult = true;
EXIT0:
    return bResult;
}

BOOL KSearchForAnyCharacter::operator ()(KCharacter* pCharacter)
{
    BOOL bRetCode = false;

    bRetCode = SearchCharacter(
        &m_pResult, 
        pCharacter, m_pSelf, 
        m_nDistance2, m_nAngle, m_nRelation, m_nLifeConversionLevel, 
        m_bAdjustRangeByLevelDiff, m_bAdjustByAttribute, m_bAdjustRangeByTargetLife, m_bAdjustByVisible
    );

    if (bRetCode)
        return false;

    return true;
}

BOOL KSearchForMultiCharacterAddThreatList::operator ()(KCharacter* pCharacter)
{
    BOOL bRetCode = false;

    bRetCode = SearchCharacter(
        &m_pResult, 
        pCharacter, m_pSelf, 
        m_nDistance2, m_nAngle, m_nRelation, m_nLifeConversionLevel, 
        m_bAdjustRangeByLevelDiff, m_bAdjustByAttribute, m_bAdjustRangeByTargetLife, m_bAdjustByVisible
    );

    if (bRetCode)
    {
        #ifdef GAME_SERVER
        m_pSelf->m_SimpThreatList.ModifyThreat(thtSpecialThreat, pCharacter, 0);
        #endif

        m_nCharacterCounter--;

        if (m_nCharacterCounter <= 0)
            return false;
    }

    return true;
}

#ifdef GAME_SERVER
BOOL _IsMalefactor(KCharacter* pCharacter)
{
    BOOL bResult    = false;

    assert(pCharacter);

    if (IS_PLAYER(pCharacter->m_dwId))
    {
        KPlayer* pPlayer = (KPlayer*)pCharacter;

        //if (pPlayer->m_PK.IsOnSlay())
        //    bResult = true;
        //
        //if (pPlayer->m_nCurrentKillPoint > 300)
        //    bResult = true;
    }

    return bResult;
}

BOOL _IsGuardian(KCharacter* pGuarder, KCharacter* pTarget)
{
    BOOL bResult    = false;
    int  nCampMark  = 0;
    int  nForceMark = 0;

    assert(pTarget);
    assert(pGuarder);

    //if (IS_NPC(pTarget->m_dwId))
    //{
    //    bResult = pGuarder->m_dwForceID == pTarget->m_dwGuardForceID;
    //}
    //else
    //{
    //    KPlayer* pPlayer = (KPlayer*)pTarget;

    //    nCampMark   = 1 << pPlayer->m_eCamp;
    //    nForceMark  = 1 << pPlayer->m_dwForceID;

    //    bResult = (pGuarder->m_AIData.dwProtectCampMark  & nCampMark) 
    //           && (pGuarder->m_AIData.dwProtectForceMark & nForceMark);
    //}
    
    return bResult;
}

BOOL KSearchBustupCharacterList::operator ()(KCharacter* pCharacter)
{
    BOOL        bRetCode    = false;
    KCharacter* pResult     = NULL;

    bRetCode = SearchCharacter(
        &pResult, 
        pCharacter, m_pSelf, 
        m_nDistance2, m_nAngle, m_nRelation, m_nLifeConversionLevel, 
        m_bAdjustRangeByLevelDiff, m_bAdjustByAttribute, m_bAdjustRangeByTargetLife, m_bAdjustByVisible
    );

    if (bRetCode)
    {
        int                     nMaxThreatCount = 5;
        BOOL                    bProtectPlayer  = false;
        BOOL                    bProtectThreat  = false;
        KPlayer*                pPlayer         = (KPlayer*)pResult;
        const KSimpThreatNode*  cpThreatNode    = NULL;

        if (_IsMalefactor(pResult))
            m_Result.insert(pResult);

        //// �д���ս����������
        //if (!pPlayer->m_bFightState || pPlayer->m_PK.IsDuel())
        //    return true;
        
        bProtectPlayer = _IsGuardian(m_pSelf, pResult);

        cpThreatNode = pResult->m_SimpThreatList.GetFirstThreat(thtMainThreat);
        while (--nMaxThreatCount && cpThreatNode)
        {
			assert(cpThreatNode->pCharacter);

            BOOL bIsPlayer = IS_PLAYER(cpThreatNode->pCharacter->m_dwId);

            bProtectThreat = _IsGuardian(m_pSelf, cpThreatNode->pCharacter);

            // ��޹�ϵΪPlayer->NPC
            if (!bIsPlayer && bProtectThreat)
                m_Result.insert(pResult);

            // ��޹�ϵΪPlayer->Player
            if (bIsPlayer)
            {
                KCharacter* pCandidate = NULL;

                if (_IsMalefactor(cpThreatNode->pCharacter))
                    m_Result.insert(cpThreatNode->pCharacter);
               
                if (bProtectPlayer == bProtectThreat)
                {
                    pCandidate = cpThreatNode->bPrimacord ? cpThreatNode->pCharacter : pResult;
                    m_Result.insert(pCandidate);
                }
                else
                {
                    if (bProtectPlayer && cpThreatNode->bPrimacord)
                        m_Result.insert(cpThreatNode->pCharacter);

                    if (bProtectThreat && !(cpThreatNode->bPrimacord))
                        m_Result.insert(pResult);
                }
            }

            cpThreatNode = pResult->m_SimpThreatList.GetNextThreat(thtMainThreat, cpThreatNode);
        }
    }

    return true;
}
#endif

void TestFunc()
{
    KPlayer Player;
    KSearchForAnyVisiblePlayer Search;

    Search.m_pSelf   = &Player;
    Search.m_pResult = NULL;

    AISearchPlayer(Search);
}
