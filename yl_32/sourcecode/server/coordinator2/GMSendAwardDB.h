#pragma once

#include "stdafx.h"
#include "DBBase.h"
#include "ProtocolBasic.h"
#include "config/kplayerbasedbdef.h"

class GMSendAwardDB
{
public:
	GMSendAwardDB();
	~GMSendAwardDB();

	BOOL                Init();
	void                UnInit();

	void				Activate();
	BOOL				connect();
	BOOL				FindTable(DWORD	dwPlayerId);
	BOOL				OnLogin(DWORD playerID);		//��ҵ�¼��ʱ��������ݿ�
	BOOL				DoQuery(const char cszSQL[]);
	BOOL				DoCommand(LPCSTR pszCommand);
	BOOL				R2S_SendCMD(DWORD id,INT nConnIndex, DWORD dwRoleId, char* pszGMCMD);
	BOOL				Send( int nConnIndex, IMemBlock* piBuffer );
	void				ChangeGMCMDMark(BYTE* pbyData, size_t uDataLen, int nConnIndex);
	BOOL				GetTimeStampByStr( char* pDate,time_t *pTime);//�ַ���תʱ���
	BOOL 				LoadRoleBlackList();
private:
	MYSQL*              m_pDBGMCMD;
	char				m_szSQL[1024];
	QLock				m_RespondGMCMD;
	time_t              m_nNextPingTime;
};


