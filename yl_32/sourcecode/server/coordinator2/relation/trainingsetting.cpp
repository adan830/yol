/* -------------------------------------------------------------------------
//	�ļ���		��	trainingsetting.cpp
//	������		��	
//	����ʱ��	��	
//	��������	��	ʦͽ������Ϣ
// -----------------------------------------------------------------------*/
#include "stdafx.h"
#include "trainingsetting.h"

#define KD_INI_TRAINING					"\\setting\\relation\\training.ini"
#define KD_SEC_GLOBAL					"Global"
#define KD_KEY_STUDENTMINLEVEL			"StudentMinLevel"					// ������С����
#define KD_KEY_STUDENTMAXLEVEL			"StudentMaxLevel"					// ������߼���
#define KD_KEY_TEACHERMINLEVEL			"TeacherMinLevel"					// ʦ����С����
#define KD_KEY_CURRENTSTUDENTMAXCOUNT	"CurrentStudentMaxCount"			// ��ǰ���������Ŀ
#define KD_KEY_MONTHLYSTUDENTMAXCOUNT	"MonthlyStudentMaxCount"			// ������ͽ�����Ŀ
#define KD_KEY_GAPMINLEVEL				"GapMinLevel"						// ʦ���͵��ӵ���С�ȼ����
#define KD_KEY_CHECKINDAYCOUNT			"CheckInDayCount"					// ���ӱ����������
#define KD_KEY_STUDENTHINTMAXLEVEL		"StudentHintMaxLevel"				// �����ڴ˼���ʱ���������ʱ���ٳ��ְ�ʦ��ʾ

KTrainingSetting g_cTrainingSetting;

KTrainingSetting::KTrainingSetting() :
	m_nStudentMinLevel(20),			// ������С����
	m_nStudentMaxLevel(50),			// ������߼���
	m_nTeacherMinLevel(69),			// ʦ����С����
	m_nCurrentStudentMaxCount(3),	// ��ǰ���������Ŀ
	m_nMonthlyStudentMaxCount(3),	// ������ͽ�����Ŀ
	m_nGapMinLevel(30),				// ʦ���͵��ӵ���С�ȼ����
	m_nCheckInDayCount(7),			// ���ӱ������ʱ�䣨������
	m_nCheckInSecCount(168 * 3600),	// ���ӱ������ʱ�䣨�룩
	m_nStudentHintMaxLevel(50)		// �����ڴ˼���ʱ���������ʱ���ٳ��ְ�ʦ��ʾ
{
}

KTrainingSetting::~KTrainingSetting()
{
}

BOOL KTrainingSetting::Init()
{
// 	KIniFile iniTraining;
// 	if (!iniTraining.Load(KD_INI_TRAINING))
// 		KGC_CONFIRM_RET_FALSE(FALSE);
// 	iniTraining.GetInteger(KD_SEC_GLOBAL, KD_KEY_STUDENTMINLEVEL, 20, &m_nStudentMinLevel);
// 	iniTraining.GetInteger(KD_SEC_GLOBAL, KD_KEY_STUDENTMAXLEVEL, 60, &m_nStudentMaxLevel);
// 	iniTraining.GetInteger(KD_SEC_GLOBAL, KD_KEY_TEACHERMINLEVEL, 90, &m_nTeacherMinLevel);
// 	iniTraining.GetInteger(KD_SEC_GLOBAL, KD_KEY_CURRENTSTUDENTMAXCOUNT, 3, &m_nCurrentStudentMaxCount);
// 	iniTraining.GetInteger(KD_SEC_GLOBAL, KD_KEY_MONTHLYSTUDENTMAXCOUNT, 3, &m_nMonthlyStudentMaxCount);
// 	iniTraining.GetInteger(KD_SEC_GLOBAL, KD_KEY_GAPMINLEVEL, 30, &m_nGapMinLevel);
// 	iniTraining.GetInteger(KD_SEC_GLOBAL, KD_KEY_CHECKINDAYCOUNT, 7, &m_nCheckInDayCount);
// 	m_nCheckInSecCount = m_nCheckInDayCount * 24 * 3600;
// 	iniTraining.GetInteger(KD_SEC_GLOBAL, KD_KEY_STUDENTHINTMAXLEVEL, 60, &m_nStudentHintMaxLevel);
	return TRUE;
}
