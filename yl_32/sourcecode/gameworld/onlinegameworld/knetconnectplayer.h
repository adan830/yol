
#pragma once

#ifdef GAME_SERVER

#include "ksocketinterface.h" 
#include "Runtime/qstring.h"

class KPlayer;
// -------------------------------------------------------------------------
class KNetConnectPlayer : public IKSocketEventProcessor
{
	friend class KPlayerProtocolProcessor;
public:
	KNetConnectPlayer();
	~KNetConnectPlayer();

	virtual BOOL Init(INT nMaxConnectId);
	virtual BOOL ProcessEvent(INT nConnectId, INT nEventId, LPCVOID pData, INT nData);
	virtual BOOL ProcessPacket(INT nConnectId, LPCBYTE pData, UINT uDataLen);

	// Client����GameServer
	INT OnClientLogin2( DWORD dwRoleId, const GUID& rConnGuid, INT nConnectId, BOOL bHidden /*= FALSE*/,BOOL bTinyTerminal);
	// �����ߵ����
	BOOL KickOutPlayer(INT nPlayerIndex);
	// ��Ҷ��߻�SocketServer�Ͽ�
	BOOL OnPlayerDisconnect(INT nPlayerIndex);
	// ÿ֡����
	virtual BOOL Activate();
	BOOL Uninit();

	LPCSTR GetProtocolStat(std::string& rstrBuffer);

	KPlayer* GetPlayerByAccount(LPCSTR pszAccount);
	BOOL KickByAccount(LPCSTR pszAccount);

	INT GetConnIndex(INT nPlayerIndex);
private:
	BOOL SendData(INT nPlayerIndex, LPCBYTE pData, UINT uDataLen);
	VOID RxStat(LPCBYTE pData, UINT uDataLen); // ��������ͳ��
	VOID TxStat(LPCBYTE pData, UINT uDataLen); // ��������ͳ��
private:
	INT* m_pnConnId2PlayerIndex;
	INT* m_pnPlayerIndex2ConnId;
	INT m_nMaxConnId; // �������id

	std::map<QString, INT> m_mpAccount2Player;

	SIZE_T m_uBytesRxBaseProtocol[USHRT_MAX+1]; // ͳ�ƻ���ģ���Э���������
	SIZE_T m_uBytesRxProtocolFamily[USHRT_MAX+1]; // ͳ�Ƹ�Э���壨ģ�飩��������
	SIZE_T m_uBytesTxBaseProtocol[USHRT_MAX+1]; // ͳ�ƻ���ģ���Э�鷢������
	SIZE_T m_uBytesTxProtocolFamily[USHRT_MAX+1]; // ͳ�Ƹ�Э���壨ģ�飩��������

	SIZE_T m_uRxBaseProtocol[USHRT_MAX+1]; // ͳ�ƻ���ģ���Э����մ���
	SIZE_T m_uRxProtocolFamily[USHRT_MAX+1]; // ͳ�Ƹ�Э���壨ģ�飩���մ���
	SIZE_T m_uTxBaseProtocol[USHRT_MAX+1]; // ͳ�ƻ���ģ���Э�鷢�ʹ���
	SIZE_T m_uTxProtocolFamily[USHRT_MAX+1]; // ͳ�Ƹ�Э���壨ģ�飩���ʹ���
};

extern KNetConnectPlayer g_cNetConnectPlayer;
// -------------------------------------------------------------------------
#endif

