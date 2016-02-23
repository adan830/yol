
#pragma once

#include "Core/QTime.h"

#include "kplayerback_interface.h"
#include "rancombi.h"

class KSysService
{
public:
	// Declare object of combined generator
	static TRandomCombined RG; // ���������������

	static VOID SetService(IKSysService* pService)
	{
		m_pService = pService;
	};
	static IKSysService* GetService()
	{
		return m_pService;
	};
	static time_t Time(time_t* pTimer)
	{
		return time(pTimer);
	}
	static time_t GameTime(time_t* pTimer)
	{
		return m_pService ? m_pService->GameTime(pTimer) : time(pTimer);
	}
	static void SetGameTime(time_t* pTimer)
	{
		m_pService ? m_pService->SetGameTime(pTimer) : (void)NULL;
	}
	static DWORD GetTickCount()
	{
		return m_pService ? m_pService->GetTickCount() : GetTickCount();
	}
	static time_t StringToDateTime(CHAR* str)
	{
		int year, month, day, hour, minute, second;
		sscanf(str, "%d-%d-%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second);

		tm tm_;
		memset(&tm_, 0, sizeof(tm));
		tm_.tm_year = year - 1900;
		tm_.tm_mon = month - 1;
		tm_.tm_mday = day;
		tm_.tm_hour = hour;
		tm_.tm_min = minute;
		tm_.tm_sec = second;
		tm_.tm_isdst = 0;

		time_t t_ = mktime(&tm_);
		return t_;
		
	}
	// ����0~(nMax - 1)������������nMax <= 0�����ؾ��ȷֲ���32λ�����
	static DWORD Rand(INT nMax = 0)
	{
		return RG.IRandomMax(nMax);
		/*return m_pService != NULL ?
			m_pService->Rand(nMax) : (nMax <= 0 ? rand() :
			(DWORD)((INT64)rand() * nMax / RAND_MAX));*/
	}
    static DWORD Rand(INT nMin, INT nMax)
	{
		return RG.IRandomRange(nMin, nMax);
	}
	// ����[0, 1)���������С��
	static DOUBLE Random()
	{
		return RG.Random();
		/*return m_pService != NULL ?
			m_pService->Random() : (DOUBLE)rand() / RAND_MAX;*/
	}

	static IKBadwordFilter* CreateBadWordFilter()
	{
		return m_pService != NULL ?
			m_pService->CreateBadWordFilter() : NULL;
	}

	static INT ValidateStringGBK(CHAR* pString)
	{
		BYTE byChar;
		while ((byChar = *pString++))
		{
			if (byChar == 0xFF)
				return FALSE;
			if (byChar > 0x80)
			{
				BYTE bySecond = *pString++;
				if (bySecond == 0)
					break;
				if (bySecond == 0x7F)
					return FALSE; // ����0x7Fɨ����
				if (bySecond < 0x40 || bySecond == 0xFF)
					return FALSE;
				// ��ֹGBK�û��Զ���1/2/3��
				if (byChar >= 0xAA && byChar <= 0xAF && bySecond >= 0xA1 && bySecond <= 0xFE)
					return FALSE;
				if (byChar >= 0xF8 && byChar <= 0xFE && bySecond >= 0xA1 && bySecond <= 0xFE)
					return FALSE;
				if (byChar >= 0xA1 && byChar <= 0xA7 && bySecond >= 0x40 && bySecond <= 0xA0)
					return FALSE;
			}
			else
			{
				if ( ! isalnum(byChar))
					return FALSE;
			}
		}
		return TRUE;

	}
	//��ȡ����ʱ���֮�����������
	static INT GetDayDiff(time_t tBegin,time_t tEnd)
	{
		return m_pService->GetTimeDiffOfDay( tBegin, tEnd);
	}

	
private:
	static IKSysService* m_pService;
};
