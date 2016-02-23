
#include "stdafx.h"
#include "onlinegamebase/ktimeline.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// -------------------------------------------------------------------------

#ifndef GAME_CENTER
KTimeline g_cTimeline;
#endif

VOID KTimeline::Init()
{
	//m_uToDoTimer	= KD_TIMER_INTMAX;
	m_uCurrentTime	= 0;
	m_dwIDCounter	= 0;
	//return TRUE;
}

VOID KTimeline::Uninit()
{
}

VOID KTimeline::Activate()
{
	// ���ÿ��������ÿ�η����������Ǵ�0��ʼ��ÿ��16֡����Ҫ����8������
	m_uCurrentTime++;

	//if (m_uToDoTimer > m_uCurrentTime)
	//{
	//	return;
	//}

	//˳����ʱ����(�������)
	INT nActionCount = 0;
	KTIMELINE::iterator it = m_mapTimeline.begin();
	while (it != m_mapTimeline.end() && it->first < m_uCurrentTime)
	{
		UINT uCurrFrame		= it->first;
		KTIMERS& cTimers	= it->second; 
		++it; // �����������ܻᵼ��itʧЧ���Ȳ���һ��

		// �������ĳʱ����ϵ����ж�ʱ��(��������)
		UINT uCount = (UINT)cTimers.size();
		KTIMERS::iterator itTimer = cTimers.begin();
		while(uCount--)
		{
			DWORD dwTimerId	= itTimer->first;
			KTIMERDATA cTD	= itTimer->second;
			++itTimer;

			Unregister(dwTimerId);	// �˴�һ���ᵼ�����������ʧЧ�����ܻᵼ�º��������ʧЧ TODO �ɽ�һ���Ż�������ɾ���������Ķ�ʱ�������¼��ǰ�����ĸ���ʱ��������һ��δ����
			if (cTD.pCallBack)
			{
				INT nRet = cTD.pCallBack->OnTimer(cTD.pParam);
				if (nRet == E_TIMER_CONTINUE)
				{
					nRet = cTD.nInterval;
				}
				if (nRet > E_TIMER_DONE)
				{
					_Register(dwTimerId, cTD.nInterval, cTD.pCallBack, cTD.pParam);
				}
			}

			if (++nActionCount > KD_TIMER_MAX)
			{
				QLogPrintf(LOG_INFO, 
					"[Timer]��ʱ����֡ע��������%d,��������˳������֡����,ʱ����:%d.", KD_TIMER_MAX, uCurrFrame);
				return;
			}
		}

		//m_uToDoTimer = uCurrFrame;
	}
}

DWORD KTimeline::Register(UINT nInterval, CONST PKTIMECALLBACK pTimeCallBack, LPVOID pParam)
{
	//// �����������ֵ���ᵼ���¶�ʱ���������ò��뵽��ʱ���򣬵����޷��ֱ���"��ʱ"����"�¼���"
	//if (nInterval > (KD_TIMER_INTMAX - KD_TIMEOUT))
	//{
	//	QLogPrintf(LOG_ERR, "[Timer]��ʱ��ʱ�䷶Χ�������ƣ�ע�ᶨʱ��ʧ��.");
	//	return 0;
	//}

	DWORD dwTimerId = _NewId();
	if (dwTimerId <= 0)	
	{
		QLogPrintf(LOG_ERR, "[Timer]��ʱ��ID���Ѿ��ľ���ע�ᶨʱ��ʧ��.");
		return dwTimerId;
	}

	return _Register(dwTimerId, nInterval, pTimeCallBack, pParam);
}

VOID KTimeline::Unregister(DWORD dwTimerId)
{
	KTIMERINDEX::iterator itIdx = m_mapTimerIndex.find(dwTimerId);
	if (itIdx == m_mapTimerIndex.end())
	{
		QLogPrintf(LOG_WARNING, "[Timer]�����ڵĶ�ʱ��ID %d.", dwTimerId);
		return;
	}

	KTIMELINE::iterator itTimers = m_mapTimeline.find(itIdx->second);
	if (itTimers == m_mapTimeline.end())
	{
		QLogPrintf(LOG_ERR, "[Timer]��ʱ�����ݴ���. ID %d, nInterval %d", dwTimerId, itIdx->second);
		return;
	}

	KTIMERS& cTimers = itTimers->second;
	KTIMERS::iterator itT = cTimers.find(dwTimerId);
	if (itT == cTimers.end())
	{
		QLogPrintf(LOG_ERR, "[Timer]��ʱ�����ݴ���. ID %d", dwTimerId);
		return;
	}

	m_mapTimerIndex.erase(itIdx);
	cTimers.erase(itT);
	if (cTimers.size() <= 0)
	{
		m_mapTimeline.erase(itTimers);
	}
}

DWORD KTimeline::_NewId()
{
	INT nLoopCount = 50;
	KTIMERINDEX::iterator pos;
	do
	{
		pos = m_mapTimerIndex.find(++m_dwIDCounter);

		// ����50�ζ��Ҳ���һ����ЧID����ʧ�ܷ�����
		nLoopCount--;
		if (nLoopCount <= 0)
		{
			return 0;
		}

	}while((!m_dwIDCounter) || pos != m_mapTimerIndex.end());

	return m_dwIDCounter;
}

DWORD KTimeline::_Register(DWORD dwTimerId, UINT nInterval, CONST PKTIMECALLBACK pTimeCallBack, LPVOID pParam)
{
	KTIMERDATA cTimerData;
	cTimerData.pCallBack = pTimeCallBack;
	cTimerData.pParam = pParam;
	cTimerData.nInterval = nInterval;

	// ����ʱ���ҵ���Ӧ��ʱ������
	UINT uActiveFame = m_uCurrentTime + nInterval;
	KTIMELINE::iterator itTimers = m_mapTimeline.find(uActiveFame);
	if (itTimers == m_mapTimeline.end())
	{
		KTIMERS cTimers;
		cTimers[dwTimerId] = cTimerData;
		m_mapTimeline[uActiveFame] = cTimers;
	}
	else
	{
		KTIMERS& cTimers = itTimers->second;
		cTimers[dwTimerId] = cTimerData;
	}

	// ��������
	m_mapTimerIndex[dwTimerId] = uActiveFame;

	//m_uToDoTimer = m_mapTimeline.begin()->first;

	return dwTimerId;
}


// -------------------------------------------------------------------------
