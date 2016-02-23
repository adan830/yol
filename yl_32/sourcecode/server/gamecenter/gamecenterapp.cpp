/* -------------------------------------------------------------------------
//	�ļ���		��	gamecenterapp.cpp
//	������		��	simon
//	����ʱ��	��	2011/5/22 1:46:54
//	��������	��	
//
// -----------------------------------------------------------------------*/

#include "stdafx.h"
#include <signal.h>
#ifdef __unix
#include <sys/time.h>
#include <sys/resource.h>
#endif // __unix
#include "kgamecenter.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// -------------------------------------------------------------------------
#define GAMECENTER_PACKAGE_FILE "package.txt"



// -------------------------------------------------------------------------

static void _SignalHandler(int nSignal)
{
	// bugfix: async-signal-safe function [ISO/IEC 9945:2008]
	//QLogPrintf(LOG_INFO, "Received signal %d! Shutdown pending...", nSignal);
	g_cGameCenter.Shutdown();
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

	return FALSE;
}
#endif

int main(int argc, char* argv[])
{
	INT	nRet	= 0;
	INT	nLogInitFlag = FALSE;
	{
		QLOG_PARAM sLogParam;
		LPSTR       pszRetCWD    = NULL;
		CHAR        szCWD[MAX_PATH];

		pszRetCWD = getcwd(szCWD, sizeof(szCWD));

		memset(&sLogParam, 0, sizeof(sLogParam));         // Engine�е���־ϵͳ
		snprintf(sLogParam.szPath, sizeof(sLogParam.szPath), "%s/log", szCWD);
		QStrCpyLen(sLogParam.szIdent, "gamecenter", sizeof(sLogParam.szIdent));
		sLogParam.nMaxLineEachFile	= USHRT_MAX;
		sLogParam.Options = (QLOG_OPTIONS)(LOG_OPTION_FILE | LOG_OPTION_CONSOLE);

		QLogInit(sLogParam, NULL);
		nLogInitFlag = TRUE;
	}
	QLogPrintf(LOG_INFO, "%s\n", "9Sky GameCenter");
	QLogPrintf(LOG_INFO, "%s\n", "BUILD " __TIME__ " " __DATE__);

#ifdef __unix
	// �������coredump�ļ�
	rlimit sLimit;
	sLimit.rlim_cur = -1;
	sLimit.rlim_max = -1;
	::setrlimit(RLIMIT_CORE, &sLimit);

	// ���ô��������ļ�Ȩ��Ϊ(rw.r.r)
	umask(022);

	// the signal only has effect on Linux, windows just define it, do noting
	signal(SIGTERM, _SignalHandler);  // when terminal by kill, call OnQuitSignal
	signal(SIGINT,  _SignalHandler);  // when Ctrl+C, call OnQuitSignal
#endif

	g_SetRootPath(NULL);
	g_SetFilePath("\\");
	srand((UINT)time(NULL));

#ifdef WIN32
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDOUT);
	_CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// �������̨�Ҽ��˵�
	DWORD dwConsoleMode = 0;
	GetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), &dwConsoleMode);
	SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), ~ENABLE_MOUSE_INPUT & dwConsoleMode);

	SetConsoleCtrlHandler(ConsoleHandlerRoutine, TRUE);
#endif // WIN32

	g_SetPackageVersion(1);			// ʹ���µ�pak��ʽ
	//// ע��˳���ǵ������ȣ�Խ�����Խ����
	//if (!KGPack_LoadPackageFiles(GAMECENTER_PACKAGE_FILE, KGPACK_FILE_PRIORITY_EXTERNAL_FILE_FIRST))
	//{
	//	QLogPrintf(LOG_ERR, "LoadPackageFile '%s' failed!", GAMECENTER_PACKAGE_FILE);
	//}

	// engine inits
	nRet = g_cGameCenter.Init();
	LOG_PROCESS_ERROR(nRet);
	nRet = g_cGameCenter.Run();
	LOG_PROCESS_ERROR(nRet);

	nRet = TRUE;
EXIT0:
	g_cGameCenter.Uninit();
	return nRet ? 0 : 1;
}

