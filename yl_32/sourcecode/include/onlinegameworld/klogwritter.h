
#pragma once

#include "Protocol/KG_CSLogServerProtocal.h"

// -------------------------------------------------------------------------

enum KE_LOG_LEVEL
{
	emLOG_LEVEL_NOMAL = 0,              // ��ͨ
	emLOG_LEVEL_COUNT,
};

enum KE_PLAYERLOG_TYPE
{
	emKPLAYERLOG_TYPE_APPRAISAL = 35,   //����
	emKPLAYERLOG_TYPE_SHOP,
	emKPLAYERLOG_TYPE_COUNT,
};

class KLogWritter
{
	enum
	{
		emKSUBTYPE_MAXCOUNT = 32,	// ��־��������
		emKCOMMENT_MAXLEN = 4096,	// ע����󳤶�
	};
public:
	KLogWritter();
	~KLogWritter();
	static KLogWritter *GetInstance() { return &ms_logWritter; }

	VOID LogSever_PlayerLog(			
		LPCSTR				pszAccount,
		LPCSTR				pszRole,
		KE_PLAYERLOG_TYPE	nType,
		LPCSTR              pszTarget,
		LPCSTR				pszComment = NULL);

	VOID LogSever_Login(LPCSTR pszGatewayName);

	VOID LogSever_DataAnalysisLog(INT32 nLogType, LPCSTR pszComment = NULL);

	VOID LogSever_DataAnalysisLogV(INT32 nLogType, ...);

	VOID DoLogin();

	BOOL StrConcat( LPSTR pszLog, va_list vl);

private:
	static KLogWritter ms_logWritter;
	static BOOL bIsLogin;
	CHAR				m_szBuff[32 * 1024];
	ULONG				m_nIdentity;		// ��־��ˮ��
};

