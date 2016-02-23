
#include "stdafx.h"
#include "onlinegamemodule/ktasktimer.h"
#include "onlinegamebase/ksysservice.h"
#include "onlinegamemodule/ktaskctrl.h"
#include "onlinegameworld/kplayer.h"

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/timeb.h>


#ifdef GAME_SERVER

KTaskTimer::KTaskTimer()
{
	memset(&m_cTimer, 0, sizeof(m_cTimer));
}

VOID KTaskTimer::Start(CONST TTaskTimer* pTimer)
{
	ASSERT(pTimer);
	m_cTimer =* pTimer;
}

VOID KTaskTimer::Close(KPlayer* pOwner, KE_CLOSE emuCloseType)
{
//	ASSERT(pOwner && m_cTimer.nTimerId != 0);
	//pOwner->OnCloseTimer(emuCloseType, m_cTimer.nTimerId, m_cTimer.dwParam, m_cTimer.nParam, m_cTimer.pData); // todo [7/20/2012 simon]

	memset(&m_cTimer, 0, sizeof(m_cTimer));
}

BOOL KTaskTimer::Activate(KPlayer* pOwner, INT nCurrent)
{
	ASSERT(pOwner && m_cTimer.nTimerId != 0);

	if (m_cTimer.nInterval == 0 ||
		m_cTimer.cOption.nSuspending == 1)	// ��ͣ״̬
		return TRUE;

	if (m_cTimer.nLastTime == 0)
	{
		m_cTimer.nLastTime = nCurrent;
		return TRUE;
	}

	if (m_cTimer.cOption.nTime == 0 ||							// ��ʱ��ʹ�ô�����
		nCurrent - m_cTimer.nLastTime < m_cTimer.nInterval)		// ��ʱʱ��δ�� 
		return TRUE;

	// �޸�ʱ���ʹ�ô���
	m_cTimer.nLastTime = nCurrent;
	if (m_cTimer.cOption.nTime > 0)
	{
		m_cTimer.cOption.nTime--;
	}

	// ִ�ж�ʱ���ű�
	OnTime(pOwner);
	return m_cTimer.cOption.nTime != 0;
}

VOID KTaskTimer::OnTime(KPlayer* pOwner)
{
	ASSERT(pOwner && m_cTimer.nTimerId != 0);
	//pOwner->OnTaskTimer(m_cTimer.nTimerId, m_cTimer.dwParam, m_cTimer.nParam,  m_cTimer.pData); // todo [7/20/2012 simon]
}

INT KTaskTimer::GetRestTime(INT nCurrent)
{
	ASSERT(m_cTimer.nTimerId != 0 && m_cTimer.nInterval > 0);
	INT nResult = m_cTimer.nLastTime + m_cTimer.nInterval - nCurrent;
	ASSERT(nResult >= 0);
	return nResult;
}

INT KTaskTimer::GetRestCount()
{
	ASSERT(m_cTimer.nTimerId != 0);
	return m_cTimer.cOption.nTime;
}

VOID KTaskTimer::AdjustTime(INT nLostTime, INT nCurrent, TTaskTimer* pTimer)
{
	ASSERT(pTimer && nLostTime >= 0 && pTimer->nInterval > 0);
	// ������߶�ʱ���ʱ�������ִ�иö�ʱ��
	if (pTimer->nInterval <= 0 || pTimer->cOption.nTime < 0)
		pTimer->cOption.nTime = 0;
	if (pTimer->cOption.nTime == 0)
		return;

	// �˴�TTaskTimer::nLastTime�������ʣ��ʱ�䣨֡����
	if (nLostTime > pTimer->nLastTime)
	{
		pTimer->nLastTime = -pTimer->nInterval;
	}
	else
	{
		pTimer->nLastTime -= nLostTime;
		pTimer->nLastTime += nCurrent - pTimer->nInterval;
	}
	
	// Ҫ�۳��Ķ�ʱ������
	INT nTime = nLostTime / pTimer->nInterval;
	if (nTime >= pTimer->cOption.nTime)
		pTimer->cOption.nTime = 0;
	else
		pTimer->cOption.nTime -= nTime;
}

BOOL KTaskTimer::Load(CONST INT nTaskValues[VALUE_COUNT], INT nCurrent)
{
	KTaskTimerList::LoadTimer(nTaskValues, &m_cTimer);
	return Load(&m_cTimer, nCurrent);
}

VOID KTaskTimer::Save(INT nTaskValues[VALUE_COUNT], INT nCurrent)
{
	TTaskTimer tag;
	Save(&tag, nCurrent);
	KTaskTimerList::SaveTimer(nTaskValues, &tag);
}

BOOL KTaskTimer::Load(TTaskTimer* pTimer, INT nCurrent)
{
	ASSERT(pTimer);
	if (pTimer->nTimerId == 0)
		return FALSE;

	if (pTimer->cOption.nMode == MODE_REALTIME)		// ������ߺ���Ȼ���ڣ���ʱ����ʵʱ��Ϊ׼
	{
		ASSERT(pTimer->nLastTime >= 0);
		ASSERT(pTimer->nLastQuit != 0);
		ASSERT(pTimer->nInterval > 0);
		// ����ʱ��δ���ߣ�
		INT nLostTime = (KSysService::Time(NULL) - pTimer->nLastQuit) * GAME_FPS;
		// ���ʱ������ʱ��������nLostTime����Ϊ��������������µ���Ϊ0
		if (nLostTime < 0)
			nLostTime = 0;
		AdjustTime(nLostTime, nCurrent, pTimer);
		return pTimer->cOption.nTime != 0;
	}
	else if (pTimer->cOption.nMode == MODE_GAMETIME)	// ������ߺ���Ȼ���ڣ���ʱ���������ʱ��Ϊ׼
	{
		ASSERT(pTimer->nLastQuit == 0);
		ASSERT(pTimer->nLastTime >= 0);
		ASSERT(pTimer->nInterval > 0);
		pTimer->nLastTime += nCurrent - pTimer->nInterval;
		return pTimer->nInterval > 0;
	}
	else
	{
		ASSERT(FALSE);
		return FALSE;
	}
}

VOID KTaskTimer::Save(TTaskTimer* pTimer, INT nCurrent)
{
	ASSERT(pTimer);
	switch (m_cTimer.cOption.nMode)
	{
	case MODE_LOSTTIME:		// ������ߺ�ʧЧ
		::memset(pTimer, 0, sizeof(TTaskTimer));
		break;
	case MODE_REALTIME:		// ������ߺ���Ȼ���ڣ���ʱ����ʵʱ��Ϊ׼
		*pTimer = m_cTimer;
		// nLastTime�������ʣ��ʱ�䣨֡������nLastQuit���浱ǰ����ʱ��
		pTimer->nLastTime = GetRestTime(nCurrent);
		pTimer->nLastQuit = KSysService::Time(NULL);
		break;
	case MODE_GAMETIME:		// ������ߺ���Ȼ���ڣ���ʱ���������ʱ��Ϊ׼
		*pTimer = m_cTimer;
		// nLastTime�������ʣ��ʱ�䣨֡����
		pTimer->nLastTime = GetRestTime(nCurrent);
		pTimer->nLastQuit = 0;
		break;
	default:
		ASSERT(FALSE);
	}
}

BOOL KTaskTimer::Suspend()
{
	if (m_cTimer.cOption.nSuspending != 0)
		return FALSE;
	m_cTimer.cOption.nSuspending = 1;
	return TRUE;
}

BOOL KTaskTimer::IsSuspending()
{
	return m_cTimer.cOption.nSuspending != 0;
}

BOOL KTaskTimer::Resume()
{
	if (m_cTimer.cOption.nSuspending == 0)
		return FALSE;
	m_cTimer.cOption.nSuspending = 0;
	return TRUE;
}

VOID KTaskTimerList::LoadTimer(CONST INT nTaskValues[VALUE_COUNT], TTaskTimer* pTimer)
{
	ASSERT(pTimer);
	INT nIndex = 0;
	pTimer->nTimerId = nTaskValues[nIndex++];
	pTimer->nInterval = nTaskValues[nIndex++];
	pTimer->nLastTime = nTaskValues[nIndex++];
	pTimer->nLastQuit = nTaskValues[nIndex++];
	memcpy(&pTimer->cOption, &nTaskValues[nIndex], sizeof(DWORD));
}

VOID KTaskTimerList::SaveTimer(INT nTaskValues[VALUE_COUNT], CONST TTaskTimer* pTimer)
{
	ASSERT(pTimer);
	INT nIndex = 0;
	nTaskValues[nIndex++] = pTimer->nTimerId;
	nTaskValues[nIndex++] = pTimer->nInterval;
	nTaskValues[nIndex++] = pTimer->nLastTime;
	nTaskValues[nIndex++] = pTimer->nLastQuit;
	memcpy(&nTaskValues[nIndex], &pTimer->cOption, sizeof(DWORD));
}

VOID KTaskTimerList::Load(KPlayer* pOwner, INT nCurrent)
{
	ASSERT(pOwner);

	m_mapUsingTimers.clear();
	m_setFreeTimers.clear();

	for (INT i = 0; i < TIMER_COUNT; i++)
	{
		INT nIndex = TAKSVAL_IDX + i * VALUE_COUNT;
		INT nTaskVals[VALUE_COUNT];
		for (INT j = 0; j < VALUE_COUNT; j++)
		{
			nTaskVals[j] = pOwner->GetCtrl<KTaskCtrl>()->GetTaskValue(nIndex + j);
		}

		KTaskTimer* pTimer = &m_cTaskTimers[i];
		if (!pTimer->Load(nTaskVals, nCurrent) ||
			m_mapUsingTimers.find(pTimer->GetId()) != m_mapUsingTimers.end())
		{
			pTimer->Close(pOwner, KTaskTimer::KE_CLOSE_FORCE);
			m_setFreeTimers.insert(i);
		}
		else
		{
			m_mapUsingTimers[pTimer->GetId()] = i;
		}
	}
}

VOID KTaskTimerList::Save(KPlayer* pOwner, INT nCurrent)
{
	ASSERT(pOwner && m_mapUsingTimers.size() + m_setFreeTimers.size() == TIMER_COUNT);
	for (INT i = 0; i < TIMER_COUNT; i++)
	{
		INT nTaskVals[VALUE_COUNT];
		KTaskTimer* pTimer = &m_cTaskTimers[i];
		if (!pTimer->IsFree())
		{
			pTimer->Save(nTaskVals, nCurrent);	
		}
		else
		{
			memset(nTaskVals, 0, sizeof(nTaskVals));
		}

		INT nIndex = TAKSVAL_IDX + i * VALUE_COUNT;
		for (INT j = 0; j < VALUE_COUNT; j++)
		{
			pOwner->GetCtrl<KTaskCtrl>()->SetTaskValue(nIndex + j, nTaskVals[j]);
		}
	}
}

VOID KTaskTimerList::GetTimerList(KTimerList& listTimers)
{
	KTimerMap::iterator it = m_mapUsingTimers.begin();
	for (; it != m_mapUsingTimers.end(); it++)
	{
		listTimers.push_back(it->second);
	}
}

VOID KTaskTimerList::Activate(KPlayer* pOwner, INT nCurrent, DWORD dwEvent)
{
	if (m_mapUsingTimers.size() <= 0)
		return;

	ASSERT(pOwner);
	
	INT i = 0;
	
	BYTE bCloseByEvent[TIMER_COUNT];
	memset(&bCloseByEvent, 0, sizeof(bCloseByEvent));

	INT nCloseCount = 0;
	for (INT i = 0;i < EVENT_COUNT; i++)
	{
		if ((dwEvent & (1 << (i))) && m_cEvent[i].nCount)
		{
			INT j = 0;
			for (j = 0; j < TIMER_COUNT; j ++)
			{
				if (m_cEvent[i].bEvent[j] > 0)
				{
					bCloseByEvent[j] = 1;
					nCloseCount++;
				}
			}
		}
	}

	if (nCloseCount)
	{
		for (INT j = 0; j < TIMER_COUNT; j ++)
		{
			if (bCloseByEvent[j])
			{
				INT nIndex = j;
				ASSERT(nIndex >= 0 && nIndex < TIMER_COUNT);
				CloseTimer(pOwner, m_cTaskTimers[j].GetId());

				for (INT t = 0; t <  EVENT_COUNT; t ++)
				{
					if (m_cEvent[t].bEvent [j])
					{
						m_cEvent[t].bEvent[j] = 0;
						m_cEvent[t].nCount--;
						_ASSERT(m_cEvent[t].nCount >= 0);
					}
				}

			}
		}
		
	}

	KTimerMap::iterator it = m_mapUsingTimers.begin();
	for (; it != m_mapUsingTimers.end();)
	{
		INT nIndex = it->second;
		ASSERT(nIndex >= 0 && nIndex < TIMER_COUNT);
		KTaskTimer* pTimer = &m_cTaskTimers[nIndex];
		INT nTimerId = pTimer->GetId();
		
		it++;

		if (nTimerId == 0)
			continue;

		// Activate����ִ�й����п��ܸı�������ʱ��
		if (!pTimer->Activate(pOwner, nCurrent))
		{
			CloseTimer(pOwner, nTimerId, KTaskTimer::KE_CLOSE_TIMEREND);
		}
	}
}

INT KTaskTimerList::CreateTimer(CONST TTaskTimer* pTimer)
{
	ASSERT(pTimer && m_setFreeTimers.size() != 0);

	KTimerSet::iterator it = m_setFreeTimers.begin();
	INT nIndex = *it;
	ASSERT(nIndex >= 0 && nIndex < TIMER_COUNT);
	m_cTaskTimers[nIndex].Start(pTimer);

	m_setFreeTimers.erase(it);
	m_mapUsingTimers[pTimer->nTimerId] = nIndex;
	RegisterTimerEvent(pTimer, nIndex);
	return nIndex;
}

BOOL KTaskTimerList::RegisterTimerEvent(CONST TTaskTimer* pTimer, INT nIndex)
{
	if (nIndex < 0)
		return FALSE;
	
	if (pTimer->dwEvent)
	{
		for (INT i = 0; i < EVENT_COUNT ; i ++)
		{
			if (pTimer->dwEvent & (1 << i))
			{
				if (m_cEvent[i].bEvent[nIndex] == 0)
				{
					m_cEvent[i].bEvent[nIndex] = 1;
					m_cEvent[i].nCount ++;
				}
			}
		}
	}
	return TRUE;
}

BOOL KTaskTimerList::StartTimer(INT nTimerId, INT nInterval, INT nTime, INT nMode, DWORD dwParam, INT nParam, LPVOID pData, DWORD dwEvent)
{
	ASSERT(nTimerId != 0);
	KTimerMap::iterator it = m_mapUsingTimers.find(nTimerId);
	if (it == m_mapUsingTimers.end() && m_setFreeTimers.size() == 0)
		return FALSE;

	TTaskTimer timer;
	memset(&timer, 0, sizeof(timer));
	timer.nInterval = nInterval;
	timer.nLastTime = 0;
	timer.nLastQuit = 0;
	timer.cOption.nMode = nMode & 0x0ff;
	timer.cOption.nTime = nTime;
	timer.cOption.nSuspending = 0;
	timer.nTimerId = nTimerId;
	timer.dwEvent = dwEvent;
	timer.dwParam = dwParam;
	timer.nParam = nParam;

	if (it != m_mapUsingTimers.end())
	{
		INT nIndex = it->second;
		ASSERT(nIndex >= 0 && nIndex < TIMER_COUNT);
		m_cTaskTimers[nIndex].Start(&timer);
		RegisterTimerEvent(&timer, nIndex );
	}
	else
	{
		CreateTimer(&timer);
	}
	
	return TRUE;
}

VOID KTaskTimerList::CloseTimer(KPlayer* pOwner, INT nTimerId, KTaskTimer::KE_CLOSE eCloseType /* = KTaskTimer::KE_CLOSE_FORCE */)
{
	KTimerMap::iterator it = m_mapUsingTimers.find(nTimerId);
	if (it != m_mapUsingTimers.end())
	{
		INT nIndex = it->second;
		KTaskTimer* pTimer = &m_cTaskTimers[nIndex];
		pTimer->Close(pOwner, eCloseType);

		m_setFreeTimers.insert(nIndex);
		m_mapUsingTimers.erase(it);
	}
}

INT KTaskTimerList::GetRestTime(INT nTimerId, INT nCurrent)
{
	KTimerMap::iterator it = m_mapUsingTimers.find(nTimerId);
	if (it == m_mapUsingTimers.end())
		return -1;

	INT nIndex = it->second;
	ASSERT(nIndex >= 0 && nIndex < TIMER_COUNT);
	return m_cTaskTimers[nIndex].GetRestTime(nCurrent);
}

INT	KTaskTimerList::GetRestCount(INT nTimerId)
{
	KTimerMap::iterator it = m_mapUsingTimers.find(nTimerId);
	if (it == m_mapUsingTimers.end())
		return -1;

	INT nIndex = it->second;
	ASSERT(nIndex >= 0 && nIndex < TIMER_COUNT);
	return m_cTaskTimers[nIndex].GetRestCount();
}

INT KTaskTimerList::GetTimerCount()
{
	return m_mapUsingTimers.size();
}

// ��ʱ��ֹ��ʱ��
BOOL KTaskTimerList::SuspendTimer(INT nTimerId)
{
	KTimerMap::iterator it = m_mapUsingTimers.find(nTimerId);
	if (it == m_mapUsingTimers.end())
		return FALSE;

	INT nIndex = it->second;
	ASSERT(nIndex >= 0 && nIndex < TIMER_COUNT);
	return m_cTaskTimers[nIndex].Suspend();
}

// �ָ���ʱ��
BOOL KTaskTimerList::ResumeTimer(INT nTimerId)
{
	KTimerMap::iterator it = m_mapUsingTimers.find(nTimerId);
	if (it == m_mapUsingTimers.end())
		return FALSE;

	INT nIndex = it->second;
	ASSERT(nIndex >= 0 && nIndex < TIMER_COUNT);
	return m_cTaskTimers[nIndex].Resume();
}

// ��ʱ���Ƿ���ͣ
BOOL KTaskTimerList::IsTimerSuspending(INT nTimerId)
{
	KTimerMap::iterator it = m_mapUsingTimers.find(nTimerId);
	if (it == m_mapUsingTimers.end())
		return FALSE;

	INT nIndex = it->second;
	ASSERT(nIndex >= 0 && nIndex < TIMER_COUNT);
	return m_cTaskTimers[nIndex].IsSuspending();
}

BOOL KTaskTimerList::HasTimer(INT nTimerId)
{
	KTimerMap::iterator it = m_mapUsingTimers.find(nTimerId);
	return it != m_mapUsingTimers.end();
}

#endif //_SERVER
