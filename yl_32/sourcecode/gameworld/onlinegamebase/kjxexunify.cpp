

#include "stdafx.h"
#include "onlinegamebase/kjxexunify.h"
#include "onlinegamebase/ksysservice.h"
#include "kdatetimecontrol.h"
#include "onlinegamebase/ikbadwordfilter.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define KDF_NAME_WORD_FILTER "\\setting\\namewordfilter.txt"

INameFilter* g_piNameWordFilter = NULL;
KDateTimeControl g_cDataTimeControl;
IKSysService* KSysService::m_pService = NULL;
TRandomCombined KSysService::RG;

// -----------------------------------------------------------------------------

class KSysServiceImpl : public IKSysService
{
	KSysServiceImpl() {}
public:
	static IKSysService* Create()
	{
		return new KSysServiceImpl();
	}
	virtual void Release()
	{
		delete this;
	}
	virtual time_t Time(time_t* pTimer)
	{
		return g_cDataTimeControl.GetSysTime(pTimer);
	}
	virtual time_t GameTime(time_t* pTimer)
	{
		return g_cDataTimeControl.GetGameTime(pTimer);
	}
	virtual void SetGameTime(time_t* pTimer)
	{
		g_cDataTimeControl.SetGameTime(*pTimer);
	}
	// ��GetElapseһ��
	virtual DWORD GetTickCount()
	{
		return g_cDataTimeControl.GetGameElapse();
	}
	// ����0~(nMax - 1)������������nMax <= 0������32λ�����
	virtual DWORD Rand(INT nMax = 0)
	{
		return nMax <= 0 ? g_cDataTimeControl.Rand() :
			(DWORD)((INT64)g_cDataTimeControl.Rand() * nMax / 0x100000000LL);
	}
	// ����[0, 1)���������С��
	virtual DOUBLE Random()
	{
		return (DOUBLE)g_cDataTimeControl.Rand() / 0x100000000LL;
	}

	virtual IKBadwordFilter*	CreateBadWordFilter()
	{
		return ::CreateBadWordFilter();
	}

	//IsLeap�����ж�һ������Ƿ�Ϊ���꣬��������:
	bool IsLeap(int year)
	{
		return (year % 4 ==0 || year % 400 ==0) && (year % 100 !=0);
	}

	//DayInYear�ܸ��ݸ��������ڣ�������ڸ���ĵڼ��죬��������
	int DayInYear(int year, int month, int day)
	{
		//int _day = 0;
		int DAY[12]={31,28,31,30,31,30,31,31,30,31,30,31};
		if(IsLeap(year))
		{
			DAY[1] = 29;
		}
		for(int i=0; i< month - 1; ++i)
		{
			day += DAY[i];
		}
		return day;
	}
	
	//�������ʱ����Լ����������
	virtual INT	GetTimeDiffOfDay(time_t tBegin,time_t tEnd)
	{
		//ȡ�������е�������
		int year1, month1, day1;
		int year2, month2, day2;

		struct tm tmBegin;
		localtime_r(&tBegin,&tmBegin);

		struct tm tmEnd;
		localtime_r(&tEnd,&tmEnd);
		year1 = tmBegin.tm_year + 1900;
		month1 = tmBegin.tm_mon + 1;
		day1 = tmBegin.tm_mday;

		year2 = tmEnd.tm_year + 1900;
		month2 = tmEnd.tm_mon + 1;
		day2 = tmEnd.tm_mday;


		if(year1 == year2 && month1 == month2)
		{
			return day1 > day2 ? day1 - day2 : day2 - day1;

			//�������ͬ
		}
		else if(year1 == year2)
		{
			int d1, d2;
			d1 = DayInYear(year1, month1, day1);
			d2 = DayInYear(year2, month2, day2);
			return d1 > d2 ? d1 - d2 : d2 - d1;
			//���¶�����ͬ
		}
		else{
			//ȷ��year1��ݱ�year2��
			if(year1 > year2)
			{
				//swap��������ֵ�Ľ���
				std::swap(year1, year2);
				std::swap(month1, month2);
				std::swap(day1, day2);
			}
			int d1,d2,d3;
			if(IsLeap(year1))
				d1 = 366 - DayInYear(year1,month1, day1); //ȡ����������ڸ��껹���¶�����
			else
				d1 = 365 - DayInYear(year1,month1, day1);
			d2 = DayInYear(year2,month2,day2); //ȡ���ڵ����еĵڼ���
			//cout<<"d1:"<<d1<<", d2:"<<d2;

			d3 = 0;
			for(int year = year1 + 1; year < year2; year++)
			{
				if(IsLeap(year))
					d3 += 366;
				else
					d3 += 365;
			}
			return d1 + d2 + d3;
		}

	}

};

// -------------------------------------------------------------------------
BOOL g_UnifyInit() 
{
	INT nResult = 0;

	g_cDataTimeControl.Init();

	KSysService::SetService(KSysServiceImpl::Create());

	CreateNameFilter(&g_piNameWordFilter);
	LOG_PROCESS_ERROR(g_piNameWordFilter);

	// nRetCode = g_piNameWordFilter->InitFromFile(KDF_NAME_WORD_FILTER);
	// LOG_PROCESS_ERROR(nRetCode);

	nResult = 1;
EXIT0:
	return nResult;
}

BOOL g_UnifyUnInit() 
{
	if (g_piNameWordFilter)
		SAFE_RELEASE(g_piNameWordFilter);

	IKSysService* piSysService = KSysService::GetService();
	KSysService::SetService(NULL);

	if (piSysService)
		piSysService->Release();

	return TRUE;
}

BOOL g_UnifyLoop()
{
	g_cDataTimeControl.Loop();

	return TRUE;
}

