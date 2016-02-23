/* -------------------------------------------------------------------------
//	�ļ���		��	fightskill.h
//	������		��	zhangzhixiong
//	ʵ����		��	
//	����ʱ��	��	2011.5.22
//	��������	��	
//
// -----------------------------------------------------------------------*/
#include "stdafx.h"
#include <math.h>
#include "fightskill/fightskill.h"
#include "fightskill/fightskillsetting.h"
#include "buffer/buffermanager.h"
#include "onlinegameworld/kcharacter.h"
#include "onlinegameworld/kplayer.h"
#include "onlinegameworld/ikscene.h"
#include "onlinegameworld/synchelper.h"
#include "onlinegameworld/korpgworld.h"
#include "onlinegamemodule/characterskill.h"
#include <algorithm>
#include "onlinegamemodule/ai/kaivm.h"
#include "faction/factionmanager.h"
#include "../onlinegamemodule/bladestate/bladedef.h"


struct CharacterDistanceGreater
{
	INT nX;
	INT nY;
	INT nZ;

	bool operator ()(KCharacter* elem1, KCharacter* elem2) CONST
	{
		INT nX2, nY2, nZ2;
		elem1->GetPosition(nX2, nY2, nZ2);
		INT nDistance1 = g_GetDistance2(nX, nY, nX2, nY2);
		elem2->GetPosition(nX2, nY2, nZ2);
		INT nDistance2 = g_GetDistance2(nX, nY, nX2, nY2);
		return nDistance1 < nDistance2;
	}
};
//////////////////////////////////////////////////////////////////////////

FightSkill::FightSkill()
{

}

FightSkill::~FightSkill()
{
	m_pFightSkillTemplate = NULL;
	m_nCurrentChannelTime = 0;
	m_pCaster = NULL;
	m_pTarget = NULL;
}

BOOL FightSkill::Init(KCharacter* pCaster,WORD nTemplateId, INT nSkillLevel)
{
	FLOAT fTimeBeforeCast = 0;
	LOG_PROCESS_ERROR(pCaster);
	m_pFightSkillTemplate = g_cFightSkillSetting.GetFightSkillTemplate(nTemplateId);
	LOG_PROCESS_ERROR(m_pFightSkillTemplate);
	m_pCaster = pCaster;
	m_pTarget = NULL;
	m_bIsActive = FALSE;
	m_nSkillLevel = nSkillLevel;
	m_arrCurrentIncroBuffer[0] = m_pFightSkillTemplate->nIncorBuff1Id;
	m_arrCurrentIncroBuffer[1] = m_pFightSkillTemplate->nIncorBuff2Id;
	m_arrCurrentIncroBuffer[2] = m_pFightSkillTemplate->nIncorBuff3Id;
	m_nIncroBuffer1Id = 0;
	m_nIncroBuffer2Id = 0;
	m_nIncroBuffer3Id = 0;
	m_nIncroBuffer4 = 0;
	m_nDestX = 0;
	m_nDestY = 0;
	m_nDestZ = 0;
	m_bSpecialTimeScale = FALSE;
	
	m_nCurrentChainLightningTargetIndex = 0;  // ������
	m_nChainFixedBuffAddonDelay = 2;
	m_bChainSelfBufferAdded = FALSE;

	if(IS_PLAYER(pCaster->GetId()) && pCaster->GetAngerLeftTime() > 0)
	{
		fTimeBeforeCast = m_pFightSkillTemplate->nSpecialTimeBeforeCast;
	}
	else
	{
		fTimeBeforeCast = m_pFightSkillTemplate->nTimeBeforeCast;
	}
	m_nCurrentCastDelay = (INT)(fTimeBeforeCast * GAME_FPS * (m_bSpecialTimeScale ? m_pFightSkillTemplate->fSpecialTimeScale : 1));  // ��ת֡
	m_nCurrentChannelTime = (INT)(m_pFightSkillTemplate->nChannelTime * (m_bSpecialTimeScale ? m_pFightSkillTemplate->fSpecialTimeScale : 1));
	m_nCostPercent = m_pFightSkillTemplate->nCostPercent;
	m_nFightSkillChannel = m_pFightSkillTemplate->nFightSkillChannel;
	m_nReduceCost = 0;
	m_fReduceCostPercent = 0;

	m_bIsMissileTimeInit = FALSE; // �ӵ�����ʱ���Ƿ��Ѽ���

	return TRUE;
EXIT0:
	return FALSE;
}

VOID FightSkill::StartSkill() // ��ʼ����
{
	m_bIsActive = TRUE;
	FLOAT fTimeBeforeCast = 0;

	if (m_nFightSkillChannel != FIGHT_SKILL_CHANNEL_NO)
	{
		// ��������, 
		m_eSkillState = SKILL_CHANNEL_GOING;
		m_pCaster->SetMoveState(cmsOnChannelSkill);  // ���ó���������״̬
	}
	else
	{
		m_eSkillState = SKILL_CASTING;
		// ��ɫ������״̬
		m_pCaster->SetMoveState(cmsOnSkill);   // End Skill �������ó�stand
	}

	if(IS_PLAYER(m_pCaster->GetId()) && m_pCaster->GetAngerLeftTime() > 0)
	{
		fTimeBeforeCast = m_pFightSkillTemplate->nSpecialTimeBeforeCast;
	}
	else
	{
		fTimeBeforeCast = m_pFightSkillTemplate->nTimeBeforeCast;
	}

	if (m_pFightSkillTemplate->bNeedJumpTo) // �������ң��ͻ���Ҳ���Լ���������ͬ��
	{
		m_pCaster->SetPosition(m_nDestX, m_nDestY, 1048576);
	}

	// ��������ʱ��
	m_nCurrentChannelTime = (INT)(m_pFightSkillTemplate->nChannelTime * (m_bSpecialTimeScale ? m_pFightSkillTemplate->fSpecialTimeScale : 1));
	// �����ӳ�
	m_nCurrentCastDelay = (INT)(fTimeBeforeCast * GAME_FPS * (m_bSpecialTimeScale ? m_pFightSkillTemplate->fSpecialTimeScale : 1)); // ��ת֡
}

VOID FightSkill::EndSkill() // ��������ʱ��ͨ�ô���
{
	FLOAT fTimeBeforeCast = 0;
	m_eSkillState = SKILL_STOP;
	if (m_pCaster->GetMoveState() == cmsOnSkill || m_pCaster->GetMoveState() == cmsOnChannelSkill) // ����Ѿ�����״̬�ˣ��Ͳ��ı����������״̬��
	{
		m_pCaster->SetMoveState(cmsOnStand);  // ����״̬Ϊվ�����
	}

	if(IS_PLAYER(m_pCaster->GetId()) && m_pCaster->GetAngerLeftTime() > 0)
	{
		fTimeBeforeCast = m_pFightSkillTemplate->nSpecialTimeBeforeCast;
	}
	else
	{
		fTimeBeforeCast = m_pFightSkillTemplate->nTimeBeforeCast;
	}

	m_bIsActive = FALSE;
	m_pTarget = NULL;
	m_nCurrentCastDelay = (INT)(fTimeBeforeCast * GAME_FPS * (m_bSpecialTimeScale ? m_pFightSkillTemplate->fSpecialTimeScale : 1)); // ��ת֡
	m_nCurrentChannelTime = m_pFightSkillTemplate->nChannelTime * (m_bSpecialTimeScale ? m_pFightSkillTemplate->fSpecialTimeScale : 1);
	m_bIsMissileTimeInit = FALSE;  // ���´ε�������ʱ���¼���

	// m_pCaster����Ӧ��ŭ��ֵ����Ҳ��ڴ���״̬�żӣ�
	if(IS_PLAYER(m_pCaster->GetId()) && m_pCaster->GetAngerLeftTime() <= 0 && m_pCaster->GetLevel() >= BLADE_OPEN_LEVEL)
	{
		INT nCurrentAnger = m_pCaster->GetAnger();
		InactiveSkillNumber* pSkillNumber = g_cFightSkillSetting.GetInactiveSkillNumber(ChangeGodSkillId(m_pFightSkillTemplate->nSkillID), m_nSkillLevel);
		LOG_PROCESS_ERROR(pSkillNumber);

		nCurrentAnger += pSkillNumber->nAddAnger;
		if(nCurrentAnger > 100)
		{
			nCurrentAnger = 100;
		}

		m_pCaster->SetAnger(nCurrentAnger);
	}

EXIT0:
	return;
}

BOOL FightSkill::BindTarget(KCharacter* pTarget)
{
	LOG_PROCESS_ERROR(pTarget);
	m_pTarget = pTarget;
	
	// ������������������¼����ʼλ���Լ��ٶ�
	if (m_pFightSkillTemplate->nFightSkillType == FIGHT_SKILL_MISSILE || this->IsChainLightningSkill()) 
	{
		pTarget->GetPosition(m_nMissileX, m_nMissileY, m_nMissileHeight);
		m_nMissileHeight = m_nMissileHeight + m_pFightSkillTemplate->nMissileHeight;

		//m_nMissileHorizontalSpeed = m_pFightSkillTemplate->nMissileHorizontalSpeed;//RepresentSpeedToLogicSpeed(m_pFightSkillTemplate->nMissileHorizontalSpeed * _3D_CELL_CM_LENGTH);
		//m_nMissileVerticalSpeed = m_pFightSkillTemplate->nMissileVerticalSpeed;	
	}

	if (m_pFightSkillTemplate->nFightSkillStartPos == FIGHT_SKILL_STARTPOS_SELF)	//ˮƽ
	{
		INT castX, castY, castZ;
		m_pCaster->GetPosition(castX, castY, castZ);
		m_nMissileX = castX;
		m_nMissileY = castY;
	}
	else if (m_pFightSkillTemplate->nFightSkillStartPos == FIGHT_SKILL_STARTPOS_TARGET)	//��ֱ
	{
		INT targetX, targetY, targetZ;
		m_pTarget->GetPosition(targetX, targetY, targetZ);
		m_nMissileX = targetX;
		m_nMissileY = targetY;
	}
	return TRUE;
EXIT0:
	return FALSE;
}

VOID FightSkill::GenerateChainLightningTargets(KCharacter* pCenterTarget, FLOAT nRadius)
{
	BOOL bOk = TRUE;
	INT nX = 0, nY = 0, nZ = 0;
	INT nX1 = 0, nY1 = 0, nZ1 = 0;
	std::vector<KCharacter*> arrCharacters;
	TKTraverseHelper<KCharacter> cTravHelper;	//������ɫ��Ҫ�ı�����
	INT nMaxDistance = 0;
	KCharacter* pCharMaxDistance = NULL;
	std::vector<KCharacter*>::iterator it_find;

    IKScene* pScene = pCenterTarget->GetScene();
	LOG_PROCESS_ERROR(pScene);

    bOk = pScene->TraverseNearbyPlayers(cTravHelper, pCenterTarget);
	LOG_PROCESS_ERROR(bOk);
	bOk = pScene->TraverseNearbyNpcs(cTravHelper, pCenterTarget);
	LOG_PROCESS_ERROR(bOk);

	pCenterTarget->GetPosition(nX1, nY1, nZ1);

	if (m_pFightSkillTemplate->bDmgOrRvv == 2)  // ���������ȸ��Լ�����һ������buffer
	{
		if (m_bChainSelfBufferAdded == FALSE)
		{
			m_pTarget = m_pCaster;
			ApplyBuffer();
			m_bChainSelfBufferAdded = TRUE;
		}
	}

	for (std::vector<KCharacter*>::iterator it = cTravHelper.m_vObjList.begin(); it != cTravHelper.m_vObjList.end(); ++it)
	{
		if ((*it) == m_pCaster) // ���ÿ��Ƿ�����
			continue;
		
		it_find = std::find(m_arrChainLightningTargets.begin(), m_arrChainLightningTargets.end(), (*it));  // �ж��Ƿ�����Ŀ���б�
		if (it_find != m_arrChainLightningTargets.end()) // �Ѿ�����Ŀ���б�Ľ�ɫ����
			continue;

		// ���м��ܹ�ϵ�ж�
		if (!CheckRelation(m_pCaster, (*it), FALSE))  // ��ϵ�����ʣ�����, �����������Ϣ
			continue;

        (*it)->GetPosition(nX, nY, nZ);
		INT nDistance = g_GetDistance2(nX, nY, nX1, nY1);
		if (nDistance < (INT)((nRadius * CELL_LENGTH * 2) * (nRadius * CELL_LENGTH * 2)))
		{
			if (nDistance > nMaxDistance)
			{
				pCharMaxDistance = (*it);
				nMaxDistance = nDistance;
			}

			arrCharacters.push_back((*it));
		}
	}

	CharacterDistanceGreater cGreater;
	cGreater.nX = nX;
	cGreater.nY = nY;
	cGreater.nZ = nZ;
	std::sort(arrCharacters.begin(), arrCharacters.end(), cGreater);
	for (std::vector<KCharacter*>::iterator it = arrCharacters.begin(); it != arrCharacters.end(); ++it)
	{
        m_arrChainLightningTargets.push_back((*it));

		if ((INT)m_arrChainLightningTargets.size() >= m_pFightSkillTemplate->nChainLightningTargetNum)
		{
			goto EXIT0;
		}
	}

	if (pCharMaxDistance != NULL)
	{
		GenerateChainLightningTargets(pCharMaxDistance, nRadius);
	}

EXIT0:;
}

// ����ɫ�����Ƿ�Ϊ��, ͬ�ͻ���
BOOL FightSkill::CheckSkillCharacters()
{
	if (!m_pCaster)
	{
		//QLogPrintf(LOG_INFO, "[FightSkill:CheckSkillCharacters]�����ͷŹ����У�Caster�����߲�����");
		return FALSE;
	}
	
	if (m_pFightSkillTemplate->bNeedTarget == TRUE)
	{
		// ���������ܲ���Ŀ���ɫ��ʧ�ж�
		if (m_pFightSkillTemplate->nFightSkillType != FIGHT_SKILL_OTHER)
		{
			if (!this->IsChainLightningSkill())
			{
				// Ŀ���ж�
				if (!m_pTarget)
				{
					//QLogPrintf(LOG_INFO, "[FightSkill:CheckSkillCharacters]�����ͷŹ����У�TargetĿ�겻����");
					return FALSE;
				}
			}
		}
	}

	// ���������������ܽ���
	if (m_pCaster->GetMoveState() == cmsOnDeath)
	{
		//QLogPrintf(LOG_INFO, "[FightSkill:CheckSkillCharacters]�����ͷŹ����У�Caster����");
		return FALSE;
	}

	return TRUE;
}

BOOL FightSkill::OnChannelSkillState()  // �������ܹ�����
{
	if (m_nFightSkillChannel == FIGHT_SKILL_CHANNEL_REVERSE) // ������������
	{ 
		ProcessResult();  // ���������в������Ч��
	}

	if (m_nCurrentChannelTime > 0)
	{
		m_nCurrentChannelTime--;
	}
	else
	{
		// ������������������������һ�׶Σ������������ܽ���
		if (m_nFightSkillChannel == FIGHT_SKILL_CHANNEL_FORWARD)
		{
			m_eSkillState = SKILL_CASTING;
		}
		else if (m_nFightSkillChannel == FIGHT_SKILL_CHANNEL_REVERSE)
		{
			this->EndSkill();
		}
	}

	return TRUE;
}

BOOL FightSkill::OnSkillState()  // ��������
{
	if (m_nCurrentCastDelay > 0) // �����ӳ�
	{
		m_nCurrentCastDelay--;
		if (m_nCurrentCastDelay <= 0)
		{
			// �������������ܵ�Ŀ���б�
			if (this->IsChainLightningSkill())
			{
				m_arrChainLightningTargets.clear();
				m_arrChainLightningTargets.push_back(m_pTarget);
				m_nCurrentChainLightningTargetIndex = 0;
				GenerateChainLightningTargets(m_pTarget, m_pFightSkillTemplate->fChainLightningRange);
			}
		}

		goto EXIT0;
	}

	// �ǵ�����������Ӧ��Ч��
	//if (m_pFightSkillTemplate->nFightSkillType != FIGHT_SKILL_MISSILE && m_pFightSkillTemplate->nFightSkillType != FIGHT_SKILL_CHAIN_LIGHTNING) 
	if (m_pFightSkillTemplate->nFightSkillType != FIGHT_SKILL_MISSILE) 
	{
		ProcessResult();
		goto EXIT0;
	}
	else
	{
		// �������ܼ���ʱ�� TODO:

		if (m_pFightSkillTemplate->bNeedTarget)
		{
			// ֻ����ʱ��
			if (TrackHorizontalOperation())	//��������ˣ���Ӧ������
			{
				ProcessResult();
			}
		}
		else
		{
			//if (TrackVerticalOperation())
			//{
			//Q_Printl("��ֱ��������δʵ�֣�");
			//}
		}
	}

EXIT0:
	return TRUE;
}

VOID FightSkill::CancelChannelSkill()
{
	if (m_nFightSkillChannel != FIGHT_SKILL_CHANNEL_NO)  // ����������
	{
		if (m_eSkillState == SKILL_CHANNEL_GOING)
		{
			// ȡ������, �������
			this->EndSkill();
		}
		else 
		{
			//QLogPrintf(LOG_ERR, "[CancelChannelSkill]�����ͼ���,������״ִ̬��ȡ������������");
		}
	}
	else 
	{
		//QLogPrintf(LOG_ERR, "[CancelChannelSkill]�������ͼ���ִ��ȡ������������");
	}
}

VOID FightSkill::Breath()
{
	if (!m_bIsActive)
	{
		goto EXIT0;
	}

	// ��鼼�ܽ�ɫ�Ƿ������
	if (!CheckSkillCharacters())
	{
		//QLogPrintf(LOG_INFO, "���ܷ����н�ɫ�����쳣��ֱ�ӽ�������");
		this->EndSkill();
		goto EXIT0;
	}

	if (m_eSkillState == SKILL_CASTING)
	{
		this->OnSkillState();
	}
	else if (m_eSkillState == SKILL_CHANNEL_GOING)
	{
		this->OnChannelSkillState();
	}
	else
	{
		//QLogPrintf(LOG_INFO, "������Fightskill��������״̬");
	}

EXIT0:;
}

BOOL FightSkill::TrackHorizontalOperation()
{
	INT targetX, targetY, targetZ;
	m_pTarget->GetPosition(targetX, targetY, targetZ);
	INT casterX, casterY, casterZ;
	m_pCaster->GetPosition(casterX, casterY, casterZ);

	DWORD nowTimeFrame = g_cOrpgWorld.m_dwLogicFrames;

	if (!m_bIsMissileTimeInit) // ��һ�ε������У��������ʱ��
	{
		INT startDistance2 = g_GetDistance2(casterX, casterY, targetX, targetY);
		//INT attackRadius2 = (INT)(m_pFightSkillTemplate->fAttackRadius * 64 * m_pFightSkillTemplate->fAttackRadius * 64); // ���ֶ˳���ת���߼��ˣ�ƽ��
		//// ����
		//FLOAT timeRatio = sqrtf((FLOAT)startDistance2 / (FLOAT)attackRadius2); // ʱ����ʵĿ���		
		//DWORD dwMissileTime = (DWORD)((m_pFightSkillTemplate->fMissileSpeed * GAME_FPS) * timeRatio); // ��������ʱ�����,  ����ʱ�� = ���ʱ��(��, ת֡) * (��ǰ���� / ������)
		//m_dwMissileEndTime = nowTimeFrame + dwMissileTime;
		DWORD dwSpeed = m_pFightSkillTemplate->fMissileSpeed * CELL_LENGTH / (DWORD)GAME_FPS; // ת�߼��ٶ�,,  ��Ҫ����16��!�������ÿ�߼�֡�ٶ�
		DWORD dwMissileTime = sqrtf(startDistance2) / dwSpeed; // t= S / v

		m_dwMissileTimeRemaining = dwMissileTime;

		m_bIsMissileTimeInit = TRUE;
	}
	
	if (m_dwMissileTimeRemaining <= 0)
	{
		return TRUE;  // Over
	}
	
	m_dwMissileTimeRemaining--;

	return FALSE;
}

BOOL FightSkill::CheckRelation(KCharacter* pCaster, KCharacter* pTarget, BOOL outputWarning)
{
	int nRelation = g_GetRelation(pCaster, pTarget);
	if (
			((nRelation == sortSelf) &&   
			!m_pFightSkillTemplate->abRelation[emRELATION_SELF-1]) // ��ϵ���Լ���������û�����Լ�����
			||
			((nRelation == sortAlly) && 
			!m_pFightSkillTemplate->abRelation[emRELATION_FRIEND-1])   // �ѷ�
			||
			((nRelation == sortTeammate) && 
			!m_pFightSkillTemplate->abRelation[emRELATION_TEAMMATE-1])  // ����
			||
			((nRelation == sortEnemy) && 
			!m_pFightSkillTemplate->abRelation[emRELATION_ENEMY-1]) // ����  
		)
	{
		if (outputWarning)
		{
			//QLogPrintf(LOG_WARNING, "[FightSkill::CheckRelation]�����ͷŵ������ϵ�����ʺ�. ˫����ϵ:%d", nRelation);
		}
		return FALSE;
	}
	return TRUE;
}

INT FightSkill::ChangeGodSkillId(int nGodSkillId)
{
	int mapSkillId = nGodSkillId;
    int nAngerLeftTime = m_pCaster->GetAngerLeftTime();
	int nFactionRoute = m_pCaster->GetCurrentRoute();
	if (nAngerLeftTime > 0)
	{		
		switch (nGodSkillId)
		{
		case emGOD_SINGLE_SKILL_ID:
			if (nFactionRoute == 1)
			{
                mapSkillId = emNEAR_SINGLE_SKILL_ID;
			}
			else
			{
                mapSkillId = emFAR_SINGLE_SKILL_ID;
			}
			break;
		case emGOD_GROUP_SKILL_ID:
			if (nFactionRoute == 1)
			{
                mapSkillId = emNEAR_GROUP_SKILL_ID;
			}
			else
			{
                mapSkillId = emFAR_GROUP_SKILL_ID;
			}
			break;
		case emGOD_DEATH_SKILL_ID:
			if (nFactionRoute == 1)
			{
                mapSkillId = emNEAR_DEATH_SKILL_ID;
			}
			else
			{
                mapSkillId = emFAR_DEATH_SKILL_ID;
			}
			break;
		}
	}

	return mapSkillId;
}

// ����������
BOOL FightSkill::CheckCastConsume()
{
	INT nRealSkillId = ChangeGodSkillId(m_pFightSkillTemplate->nSkillID);
	if (m_pFightSkillTemplate->nSkillCostType == FIGHT_SKILL_COST_TYPE_MANA) // ����
	{
		INT nCurrentMana = m_pCaster->GetCurrentMana();
		InactiveSkillNumber* pSkillNumber = g_cFightSkillSetting.GetInactiveSkillNumber(nRealSkillId, m_nSkillLevel);
		INT nCost = 0, nNewMana = 0;
		LOG_PROCESS_ERROR(pSkillNumber);
		
		nCost = pSkillNumber->nManaCost;
		nNewMana = nCurrentMana - nCost;
		nNewMana = nNewMana < 0 ? 0 : nNewMana;
		m_pCaster->SetCurrentMana(nNewMana);
	}
	else if (m_pFightSkillTemplate->nSkillCostType == FIGHT_SKILL_COST_TYPE_LIFE) // ����
	{
		INT nCurrentLife = m_pCaster->GetCurrentLife();
		INT nBaseMaxLife = g_cFactionManager.GetBaseMaxLife(*m_pCaster);
		INT nCost = nBaseMaxLife * m_nCostPercent / 100;

		if(m_fReduceCostPercent != 0)
		{
			nCost = static_cast<INT>((FLOAT)nCost * (100.0f - m_fReduceCostPercent) / 100.0f);
		}

		nCost -= m_nReduceCost;
		ASSERT(nCost >= 0);

		if(nCurrentLife < nCost)
			return FALSE;
		INT nNewLife = nCurrentLife - nCost;
		m_pCaster->SetCurrentLife(nNewLife);
	}
	else
	{
		//QLogPrintf(LOG_ERR, "[Skill]Wrong skill cost type");
	}

	return TRUE;
EXIT0:
	return FALSE;
}

BOOL FightSkill::CheckCastRelation()
{
	if(m_pFightSkillTemplate->bNeedTarget && !CheckRelation(m_pCaster, m_pTarget))
		return FALSE;

	return TRUE;
}

BOOL FightSkill::ProcessResult()
{
    if (m_nFightSkillChannel == FIGHT_SKILL_CHANNEL_REVERSE)
	{
		if (m_nCurrentChannelTime % m_pFightSkillTemplate->nChannelFreq == 0) // �������bufferʱ��, ���϶�ʱ���
		{
			ApplyBuffer();
		}
	}
	else if (this->IsChainLightningSkill()) // ������
	{
		if (m_nChainFixedBuffAddonDelay == 2) // ����һ��Ŀ�꣬����Ŀ��̶�2֡�����buf
		{
			if (m_nCurrentChainLightningTargetIndex < (INT)m_arrChainLightningTargets.size())
			{
				m_pTarget = m_arrChainLightningTargets[m_nCurrentChainLightningTargetIndex++];
				ApplyBuffer();
			}
			else
			{
                 goto EXIT0;
			}

			m_nChainFixedBuffAddonDelay = 0;
		}
		m_nChainFixedBuffAddonDelay++;
	}
	else
	{
		ApplyBuffer();  // һ�㼼��
		goto EXIT0;
	}

	return TRUE;
EXIT0:
	this->EndSkill();
	return TRUE;
}

VOID FightSkill::AddBuffer(INT nBufId, INT& rnSelfBufIdVal)
{
	CONST BufferTemplate* pTemplate = NULL;

	if(!nBufId)
		goto EXIT0;

	pTemplate = g_cBufferSetting.GetBufferTemplate(nBufId);
	LOG_PROCESS_ERROR(pTemplate);

	PROCESS_ERROR(nBufId != 0);

	if (!pTemplate->m_bIsGroundBuffer)
	{
		DWORD dwTargetId = 0;
		if(m_pTarget)
		{
			dwTargetId = m_pTarget->GetId();
		}

		rnSelfBufIdVal = g_cBufferMgr.AddBufferToCharacter(m_pCaster->GetId(), m_pFightSkillTemplate->nSkillID, dwTargetId, nBufId, 0, TRUE, m_nDestX,m_nDestY,m_nDestZ, m_nSkillLevel);
		//LOG_PROCESS_ERROR(rnSelfBufIdVal);
		if (!(rnSelfBufIdVal))       
		{                       
			//QLogPrintf(LOG_DEBUG, "�޷���Ӽ���buffer(%d,%d) at line %d in %s\n", m_pFightSkillTemplate->nSkillID, nBufId, __LINE__, __FUNCTION__);                  
			goto EXIT0;    
		}

		if (g_cOrpgWorld.m_bDebugSelf)
		{
			//std::cout << "AddBuffer BuffId: " << nBufId << " Caster: " << m_pCaster->GetName() << " Target: " << 
			//	(m_pTarget ? m_pTarget->GetName() : m_pCaster->GetName()) << std::endl;
		}
	}
	else
	{
		if (m_pCaster && m_pCaster->GetScene())
		{
			DWORD dwSceneId = m_pCaster->GetScene()->GetId();
			rnSelfBufIdVal = g_cBufferMgr.AddGroundBuffer(nBufId, m_pCaster->GetId(), m_pFightSkillTemplate->nSkillID, dwSceneId,m_nDestX,m_nDestY,m_nDestZ, pTemplate->m_bSync, 0, m_nSkillLevel);
			LOG_PROCESS_ERROR(rnSelfBufIdVal);

			if (g_cOrpgWorld.m_bDebugSelf)
			{
			    //std::cout << "AddGroundBuffer BuffId: " << nBufId << " Caster: " << m_pCaster->GetName() << std::endl;
			}
		}
	}
EXIT0:;
}

BOOL FightSkill::ApplyBuffer()
{
	// ��Ӽ��ʴ�����Buffer
	if (m_pFightSkillTemplate->nFightSkillType == FIGHT_SKILL_BUFFER || m_pFightSkillTemplate->nFightSkillType == FIGHT_SKILL_MISSILE)
	{
	    if (m_pCaster && m_pTarget && IS_PLAYER(m_pCaster->GetId()))
		{
			ResistSkillNumber* pResistSkillNumber = NULL;
			InactiveSkillNumber* pInactiveSkillNumber = NULL;
			CharacterSkill* pCharSkill = NULL;
			INT nResistSkillLevel = 0;
			pInactiveSkillNumber = g_cFightSkillSetting.GetInactiveSkillNumber(ChangeGodSkillId(m_pFightSkillTemplate->nSkillID), m_nSkillLevel);
            LOG_PROCESS_ERROR(pInactiveSkillNumber);

			if (pInactiveSkillNumber->nResistSkillId != 0)
			{
                INT nResistIncroRate = 0;
				pCharSkill = m_pTarget->GetCtrl<CharacterSkill>();
				LOG_PROCESS_ERROR(pCharSkill);
				nResistSkillLevel = pCharSkill->GetSkillLevel(pInactiveSkillNumber->nResistSkillId);
				pResistSkillNumber = g_cFightSkillSetting.GetResistSkillNumber(m_pFightSkillTemplate->nSkillID, nResistSkillLevel);
				if (pResistSkillNumber != NULL)
				{
					nResistIncroRate = pResistSkillNumber->nValue;
				}

				INT nIncroRate = pInactiveSkillNumber->nBufferIncroRate - nResistIncroRate;
				nIncroRate = nIncroRate < 0 ? 0 : nIncroRate;

				//printf("�˴���������ʵ��buff��������: %d  �������ܴ������ʣ�%d, ���Լ��ܼ��ٴ������ʣ�%d", nIncroRate, pInactiveSkillNumber->nBufferIncroRate, pResistSkillNumber->nValue);

				INT nRateValue = KSysService::Rand() % 1000;
				if (nRateValue < nIncroRate)
				{
					if (pInactiveSkillNumber->nAddBuffToSelf) // �Ƿ���Լ���buff�����Ѫ
					{
						g_cBufferMgr.AddBufferToCharacter(m_pCaster->GetId(), m_pFightSkillTemplate->nSkillID , m_pCaster->GetId(), pInactiveSkillNumber->nBufferId, pInactiveSkillNumber->nBufferExistTime, TRUE, m_nDestX,m_nDestY,m_nDestZ, m_nSkillLevel);
					}
					else
					{
						g_cBufferMgr.AddBufferToCharacter(m_pCaster->GetId(), m_pFightSkillTemplate->nSkillID , m_pTarget->GetId(), pInactiveSkillNumber->nBufferId, pInactiveSkillNumber->nBufferExistTime, TRUE, m_nDestX,m_nDestY,m_nDestZ, m_nSkillLevel);
					}
				}
			}
		}
	}

	AddBuffer(m_arrCurrentIncroBuffer[0], m_nIncroBuffer1Id);  // �����ж��ǼӸ��˻��ǼӸ���
	AddBuffer(m_arrCurrentIncroBuffer[1], m_nIncroBuffer2Id);
	AddBuffer(m_arrCurrentIncroBuffer[2], m_nIncroBuffer3Id);
	AddBuffer(m_nIncroBuffer4, m_nIncroBuffer4Id);

	return TRUE;
EXIT0:
	return FALSE;
}


VOID FightSkill::SetDestPostion(INT nX,INT nY,INT nZ)
{
	m_nDestX = nX;
	m_nDestY = nY;
	m_nDestZ = nZ;
	if (m_pFightSkillTemplate->nFightSkillType == FIGHT_SKILL_MISSILE) // ��������¼����ʼλ���Լ��ٶ�
	{
		m_nMissileHeight = m_nDestZ + m_pFightSkillTemplate->nMissileHeight;
		//m_nMissileHorizontalSpeed = m_pFightSkillTemplate->nMissileHorizontalSpeed;//RepresentSpeedToLogicSpeed(m_pFightSkillTemplate->nMissileHorizontalSpeed * _3D_CELL_CM_LENGTH);
		//m_nMissileVerticalSpeed = m_pFightSkillTemplate->nMissileVerticalSpeed;
	}
	if (m_pFightSkillTemplate->nFightSkillStartPos == FIGHT_SKILL_STARTPOS_SELF)	//ˮƽ
	{
		INT castX, castY, castZ;
		m_pCaster->GetPosition(castX, castY, castZ);
		m_nMissileX = castX;
		m_nMissileY = castY;
	}
	else if (m_pFightSkillTemplate->nFightSkillStartPos == FIGHT_SKILL_STARTPOS_TARGET)	//��ֱ
	{
		m_nMissileX = m_nDestX;
		m_nMissileY = m_nDestY;
	}
}

VOID FightSkill::SetCurrentIncroBuffer(INT nIndex, INT nBuffId)
{
	if (nIndex < 4)
	{
	    m_arrCurrentIncroBuffer[nIndex - 1] = nBuffId;
	}
	else if (nIndex == 4)
	{
		m_nIncroBuffer4 = nBuffId;
	}
	else
	{
		//QLogPrintf(LOG_ERR, "[FightSkill]Wrong incro buffer index[%d]", nIndex);
	}
}

INT FightSkill::GetCurrentIncroBuffer(INT nIndex)
{
	if (nIndex < 4)
	{
	    return m_arrCurrentIncroBuffer[nIndex - 1];
	}
	else if (nIndex == 4)
	{
		return m_nIncroBuffer4;
	}
	else
	{
		//QLogPrintf(LOG_ERR, "[FightSkill]Wrong incro buffer index[%d]", nIndex);
		return -1;//��������
	}
}

BOOL FightSkill::IsChainLightningSkill()  // �ж��Ƿ�����������
{
	if (this->m_pFightSkillTemplate->nFightSkillType == FIGHT_SKILL_OTHER)
	{
		//QString skillPlugins = this->m_pFightSkillTemplate->szPlugins;
		string skillPlugins(this->m_pFightSkillTemplate->szPlugins);
		if (skillPlugins.find("QRLSkillChainLightning") != string::npos)
		//if (skillPlugins.Find("QRLSkillChainLightning") )
		{
			return TRUE;
		}
	}

	return FALSE;
}