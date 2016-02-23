/* -------------------------------------------------------------------------
//	�ļ���		��	buftimereffect.h
//	������		��	zhangzhixiong
//	����ʱ��	��	2012-5-7 
//	��������	��	
//
// -----------------------------------------------------------------------*/
#include "buffer/buftimereffect.h"

BufTimerEffect::BufTimerEffect()
{
	m_nID = 0;
	m_nInterval = 0;
	m_eLaunchType =	UpperLaunch;
}

BufTimerEffect::~BufTimerEffect()
{

}

//��ʼ��ʱ�䴥����buff
BOOL BufTimerEffect::Init(ITabFile* tabFile, INT nRow)
{
	CHAR szTemp[SCRIPT_MAX_LENGTH] = {0};
	LOG_PROCESS_ERROR(tabFile);
	LOG_PROCESS_ERROR(nRow > 0);
	tabFile->GetInteger(nRow, "ID", 0 ,(INT*)&m_nID);
	tabFile->GetInteger(nRow, "Interval" , 0 , (INT*)&m_nInterval);
	tabFile->GetInteger(nRow, "LaunchType", 0 , (INT*)&m_eLaunchType);
	tabFile->GetString(nRow, "Precond" , "", szTemp, countof(szTemp));
	m_cCondition.Init(szTemp);
	ZeroMemory(szTemp,SCRIPT_MAX_LENGTH);
	tabFile->GetString(nRow, "StartEffect" , "", szTemp, countof(szTemp));
	m_cUpperBoundEffect.Init(szTemp);
	ZeroMemory(szTemp,SCRIPT_MAX_LENGTH);
	tabFile->GetString(nRow, "EndEffect" , "", szTemp, countof(szTemp));
	m_cLowerBoundEffect.Init(szTemp);
	return TRUE;
EXIT0:
	return FALSE;
}

