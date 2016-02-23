/* -------------------------------------------------------------------------
//	�ļ���		��	role_svc.cpp
//	������		��	simon
//	����ʱ��	��	2010/5/11 12:08:12
//	��������	��	
//
// -----------------------------------------------------------------------*/

#include "stdafx.h"
#include "kroleserver.h"
#include <signal.h>
#ifdef __unix
#include <sys/time.h>
#include <sys/resource.h>
#endif // __unix

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// -------------------------------------------------------------------------

static void _SignalHandler(int nSignal)
{
	// bugfix: async-signal-safe function [ISO/IEC 9945:2008]
	g_cRoleSvc.Shutdown();
}

#ifdef _WIN32
static BOOL WINAPI ConsoleHandlerRoutine(DWORD dwCtrlType)
{
	/*
	CTRL_C_EVENT        CTRL+C signal was received
	CTRL_BREAK_EVENT    CTRL+BREAK signal was received
	CTRL_CLOSE_EVENT    the user closes the console (either by clicking Close on the console window's window menu, or by clicking the End Task button command from Task Manager). 
	*/
	_SignalHandler(dwCtrlType);

	//QThread_Sleep(4000); // ���ⵯ�����������Ĵ���
	return FALSE;
}
#endif

int main(int argc, char *argv[])
{
	INT	nRet	= 0;
	INT	nLogInitFlag = FALSE;
	{
		QLOG_PARAM sLogParam;
		LPSTR       pszRetCWD    = NULL;
		CHAR        szCWD[MAX_PATH];

		pszRetCWD = getcwd(szCWD, sizeof(szCWD));

		memset(&sLogParam, 0, sizeof(sLogParam));
		snprintf(sLogParam.szPath, sizeof(sLogParam.szPath), "%s/log", szCWD);
		QStrCpyLen(sLogParam.szIdent, "roleserver", sizeof(sLogParam.szIdent));
		sLogParam.nMaxLineEachFile	= USHRT_MAX;
		sLogParam.Options = (QLOG_OPTIONS)(LOG_OPTION_FILE | LOG_OPTION_CONSOLE);

		QLogInit(sLogParam, NULL);

#ifndef _DEBUG
		//LogSetPriorityMask(KGLOG_UPTO(LOG_INFO));
#endif // _DEBUG

		nLogInitFlag = TRUE;
	}

#ifdef __unix
	// �������coredump�ļ�
	rlimit sLimit;
	sLimit.rlim_cur = -1;
	sLimit.rlim_max = -1;
	::setrlimit(RLIMIT_CORE, &sLimit);

	// ���ô��������ļ�Ȩ��Ϊ(rw.r.r)
	umask(022);
#endif
	QLogPrintf(LOG_DEBUG, "%s", "9SKy Role Server");
	QLogPrintf(LOG_DEBUG, "%s", "BUILD " __TIME__ " " __DATE__);

	g_SetRootPath(NULL);
	g_SetFilePath("\\");

	nRet = g_cRoleSvc.Init();

#ifdef WIN32
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDOUT);
	//_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
	//_CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDOUT);
	_CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	SetConsoleCtrlHandler(ConsoleHandlerRoutine, TRUE);
#endif // WIN32
	// the signal only has effect on Linux, windows just define it, do noting
	signal(SIGTERM, _SignalHandler);  // when terminal by kill, call OnQuitSignal
	signal(SIGINT,  _SignalHandler);  // when Ctrl+C, call OnQuitSignal

	if (nRet)
	{
		nRet = g_cRoleSvc.Start();
		//g_cRoleSvc.TestCase_Functionality();
	}
	g_cRoleSvc.Uninit();

	QLogPrintf(LOG_INFO, "RoleServer Closed.");

	if (nLogInitFlag)
		QLogUnInit(NULL);

	return nRet ? 0 : 1;
}
