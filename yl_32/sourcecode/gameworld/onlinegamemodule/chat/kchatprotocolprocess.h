
#pragma once

// -------------------------------------------------------------------------
class KChatProtocolProcessor
{
public:
#ifdef GAME_SERVER
	
public:
	// ����GC��Ӧ��
	static BOOL ProtocolGCProcess(LPCBYTE pProtocol, UINT nDataLen);
private:
	static BOOL ProcessRespondMsg(LPCBYTE pProtocol, UINT nDataLen);
	
public:
	// ����Client������
	static BOOL ProtocolProcess(INT nPlayerIdx, LPCBYTE pProtocol, UINT nDataLen);
private:
	static BOOL ProcessRequstMsg(INT nPlayerIdx, LPCBYTE pProtocol, UINT nDataLen);
	static BOOL ProcessSendMsgToPlayer(INT nPlayerIdx, LPCBYTE pProtocol, UINT nDataLen);

#else
	// ����GSӦ��
	static BOOL ProtocolProcess(LPCBYTE pProtocol, UINT nDataLen);
private:
	static BOOL ProcessRespondMsg(LPCBYTE pProtocol, UINT nDataLen);
#endif
};


