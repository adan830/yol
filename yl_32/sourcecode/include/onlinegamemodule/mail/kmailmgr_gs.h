/* -------------------------------------------------------------------------
//	�ļ���		��	kmailmgr_gs.h
//	������		��	xiewenzhe
//	����ʱ��	��	2011/5/23 17:28:48
//	��������	��	�ʼ�GSģ��
//
// -----------------------------------------------------------------------*/
#ifndef __KMAILMGR_GS_H__
#define __KMAILMGR_GS_H__

// -------------------------------------------------------------------------
#ifdef GAME_SERVER

class KMailManager_GS
{
public:
	KMailManager_GS();
	~KMailManager_GS();

public:
	static KMailManager_GS* Instance() {return &ms_inst;}

public:
	//����GC������Э��
	BOOL ProcessGcProtocol(LPCBYTE pbData, UINT uDataLen);
	// ������ҿͻ���Э��
	BOOL ProcessClientProtocol(INT nPlayerIndex, LPCBYTE pbData, UINT uDataLen);

private:
	BOOL GameCenter_LoadOK(LPCBYTE pbData, UINT uSize);
	BOOL GameCenter_FetchInfo(LPCBYTE pbData, UINT uSize);
	BOOL GameCenter_FetchMail(LPCBYTE pbData, UINT uSize);
	BOOL GameCenter_FetchItem(LPCBYTE pbData, UINT uSize);
	BOOL GameCenter_AddMail(LPCBYTE pbData, UINT uSize);
	BOOL GameCenter_DeleteMail(LPCBYTE pbData, UINT uSize);
	BOOL GameCenter_CheckReceiver(LPCBYTE pbData, UINT uSize);

	BOOL GameClient_FetchInfo(INT nPlayerIndex, LPCBYTE pbData, UINT uSize);
	BOOL GameClient_FetchCondInfo(INT nPlayerIndex, LPCBYTE pbData, UINT uSize);
	BOOL GameClient_FetchMail(INT nPlayerIndex, LPCBYTE pbData, UINT uSize);
	BOOL GameClient_FetchItem(INT nPlayerIndex, LPCBYTE pbData, UINT uSize);
	BOOL GameClient_SendMail(INT nPlayerIndex, LPCBYTE pbData, UINT uSize);
	BOOL GameClient_DeleteMail(INT nPlayerIndex, LPCBYTE pbData, UINT uSize);

private:
	static KMailManager_GS	ms_inst;
	CHAR					m_szBuffer[32 * 1024];
};

#endif /* GAME_SERVER */
// -------------------------------------------------------------------------

#endif /* __KMAILMGR_GS_H__ */
