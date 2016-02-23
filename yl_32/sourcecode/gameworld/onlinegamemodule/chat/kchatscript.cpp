

#include "stdafx.h"

#include "onlinegamemodule/chat/kchatmodule.h"
#include "onlinegamebase/kscriptmanager.h"
#include "gcmodule/chat/kchatchannelptc.h"
#include "onlinegameworld/ikscene.h"
#include "onlinegameworld/ikscenemgr.h"
#include "onlinegameworld/synchelper.h"
#include "onlinegameworld/kplayer.h"
#include "onlinegameworld/kplayermgr.h"
#include "onlinegameworld/kbaseprotocol.h"
#include "onlinegamemodule/chat/kplayerchat.h"
#include "onlinegameworld/kluaplayer.h"
#include "onlinegamebase/ksysservice.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static CHAR _pszTempText[KD_CHANNEL_MSG_MAX_LEN];		// chat��Ϣ��ʱ�ַ���

// -------------------------------------------------------------------------
namespace kchatscript
{
	// -------------------------------------------------------------------------
	// @ClientSvr(C/S)	: 
	// @ClassName		: --
	// @LuaApiName		: HasBadWords
	// @Description		: �Ƿ���chat���д�
	// @ReturnCode		: 
	// @ArgumentFlag	: s
	// @ArgumentComment	: ��������
	// @LuaMarkEnd
	// -------------------------------------------------------------------------
	INT LuaHasBadWords(QLuaScript& sc)
	{
		BOOL bRet = g_pChatFilter->HasBadword(sc.GetStr(1));
		sc.PushNumber(bRet);

		return 1;
	}

	// -------------------------------------------------------------------------
	// @ClientSvr(C/S)	: 
	// @ClassName		: --
	// @LuaApiName		: KillBadWords
	// @Description		: ����chat���д�
	// @ReturnCode		: 
	// @ArgumentFlag	: s
	// @ArgumentComment	: ��������
	// @LuaMarkEnd
	// -------------------------------------------------------------------------
	INT LuaKillBadWords(QLuaScript& sc)
	{
		BOOL bRet = g_pChatFilter->KillBadword(sc.GetStr(1), _pszTempText, KD_CHANNEL_MSG_MAX_LEN);
		sc.PushString(_pszTempText);

		return 1;
	}

#ifdef GAME_SERVER
// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: S
// @ClassName		: --
// @LuaApiName		: SendMsg
// @Description		: 
// @ReturnCode		: 
// @ArgumentFlag	: dddss
// @ArgumentComment	: Ƶ��Id
// @ArgumentComment	: ������Id
// @ArgumentComment	: ���ն���
// @ArgumentComment	: ������Head
// @ArgumentComment	: ��Ϣ����
// @LuaMarkEnd
// -------------------------------------------------------------------------
	INT LuaSendMsg(QLuaScript& sc)
	{
		BOOL bRet = g_ChatChannelManager.RequestSendMsg(sc.GetInt(1) , sc.GetInt(2), sc.GetInt(3), sc.GetStr(4), sc.GetStr(5), emQCHAT_PANEL);
		sc.PushNumber(bRet);

		return 1;
	}

	// -------------------------------------------------------------------------
	// @ClientSvr(C/S)	: S
	// @ClassName		: --
	// @LuaApiName		: BroadcastSysMsg
	// @Description		: ��������ҷ���ϵͳ��Ϣ
	// @ReturnCode		: 
	// @ArgumentFlag	: s[dds]
	// @ArgumentComment	: ϵͳ��Ϣ
	// @ArgumentComment	: ϵͳ��Ϣ����
	// @ArgumentComment	: nSenderId
	// @LuaMarkEnd
	// -------------------------------------------------------------------------
	INT LuaBroadcastSysMsg(QLuaScript& sc)
	{
		LPCSTR pszMsg = sc.GetStr(1);
		LPCTSTR szSenderName = NULL;
		INT nChannelId = trGlobalSys;
		DWORD dwSenderId = 0;
		if(sc.IsNumber(2))
		{
			nChannelId = sc.GetInt(2);
		}
		if(sc.IsNumber(3))
		{
			dwSenderId = sc.GetInt(3);
		}
		if(sc.IsString(4))
		{
			szSenderName = sc.GetStr(4);
		}
		//KE_SYSTEMMSG_TYPE nType = emKSYSTEMMSG_NORMAL;
		g_ChatChannelManager.RequestBroadcastSystemMsg(nChannelId, pszMsg, dwSenderId, szSenderName);
		/*static BYTE bySyncPackBuffer[KD_CHANNEL_PACKET_MAX_LEN];

		ZeroMemory(bySyncPackBuffer, sizeof(bySyncPackBuffer));

		if (sc.GetTopIndex() >= 2)
			nType = (KE_SYSTEMMSG_TYPE)sc.GetInt(2);

		QCONFIRM_RET_FALSE(pszMsg);

		KPlayerProtocolProcessor* pProtocolProcessor = g_ChatChannelManager.GetProtocolProcessor();
		QCONFIRM_RET_FALSE(pProtocolProcessor);

		KCHATPROTO_S2C_MSG& cSendData = *(KCHATPROTO_S2C_MSG* )bySyncPackBuffer;
		cSendData = KCHATPROTO_S2C_MSG();
		cSendData.nChannelId = trLocalSys;
		cSendData.nSenderId = nType;
		ZeroMemory(cSendData.szSenderName, sizeof(cSendData.szSenderName));
		cSendData.nReceiverId = 0;

		size_t uMsgLen = strlen(pszMsg) + 1;
		QCONFIRM_RET_FALSE(uMsgLen < sizeof(bySyncPackBuffer) - sizeof(cSendData));
		QStrCpyLen(cSendData.szMsg, pszMsg, uMsgLen);

		KCharacterServer::BroadcastThisServer(
			(LPCBYTE)bySyncPackBuffer, sizeof(cSendData) + uMsgLen, NULL, pProtocolProcessor);*/

		return 0;
	}

	// -------------------------------------------------------------------------
	// @ClientSvr(C/S)	: S
	// @ClassName		: --
	// @LuaApiName		: BroadcastBlackMsg
	// @Description		: ��������ҷ��ͺ�����Ϣ
	// @ReturnCode		: 
	// @ArgumentFlag	: s
	// @ArgumentComment	: ϵͳ��Ϣ
	// @LuaMarkEnd
	// -------------------------------------------------------------------------
	INT LuaBroadcastBlackMsg(QLuaScript& sc)
	{
		INT nLen = 0;
		LPCSTR pszString = sc.GetLStr(1, nLen);
		nLen++;

		g_ChatChannelManager.RequestBroadcastBlackMsg(pszString);

		return 0;
	}

	// -------------------------------------------------------------------------
	// @ClientSvr(C/S)	: S
	// @ClassName		: --
	// @LuaApiName		: BroadcastKinNoticeMsg
	// @Description		: �����м�����ҷ��͹�����Ϣ
	// @ReturnCode		: 
	// @ArgumentFlag	: ds
	// @ArgumentComment	: ���id
	// @ArgumentComment	: ϵͳ��Ϣ
	// @LuaMarkEnd
	// -------------------------------------------------------------------------
	INT LuaBroadcastKinNoticeMsg(QLuaScript& sc)
	{
		INT nLen = 0;
		INT nPlayerId = sc.GetInt(1);
		LPCSTR pszString = sc.GetLStr(2, nLen);
		nLen++;

		g_ChatChannelManager.RequestSendKinNoticeMsg(nPlayerId, pszString);

		return 0;
	}

	// -------------------------------------------------------------------------
	// @ClientSvr(C/S)	: S
	// @ClassName		: --
	// @LuaApiName		: BroadcastNoticeMsg
	// @Description		: ��������ҷ��͹�����Ϣ
	// @ReturnCode		: 
	// @ArgumentFlag	: s
	// @ArgumentComment	: ϵͳ��Ϣ
	// @LuaMarkEnd
	// -------------------------------------------------------------------------
	INT LuaBroadcastNoticeMsg(QLuaScript& sc)
	{
		INT nLen = 0;
		LPCSTR pszString = sc.GetLStr(1, nLen);
		nLen++;

		g_ChatChannelManager.RequestBroadcastNoticeMsg(pszString);

		return 0;
	}

	// -------------------------------------------------------------------------
	// @ClientSvr(C/S)	: S
	// @ClassName		: --
	// @LuaApiName		: GetFreeWorldSpeakerCount
	// @Description		: ��ȡÿ����������������
	// @ReturnCode		: 
	// @ArgumentFlag	: 
	// @ArgumentComment	: 
	// @LuaMarkEnd
	// -------------------------------------------------------------------------
	INT LuaGetFreeWorldSpeakerCount(QLuaScript& sc)
	{
		INT nCount = g_ChatChannelManager.GetFreeWorldSpeaker();
		sc.PushNumber(nCount);

		return 1;
	}

	// -------------------------------------------------------------------------
	// @ClientSvr(C/S)	: S
	// @ClassName		: --
	// @LuaApiName		: SetFreeWorldSpeakerCount
	// @Description		: ����ÿ����������������
	// @ReturnCode		: 
	// @ArgumentFlag	: 
	// @ArgumentComment	: 
	// @LuaMarkEnd
	// -------------------------------------------------------------------------
	INT LuaSetFreeWorldSpeakerCount(QLuaScript& sc)
	{
		INT nCount = sc.GetInt(1);
		g_ChatChannelManager.SetFreeWorldSpeaker(nCount);

		return 0;
	}

	// -------------------------------------------------------------------------
	// @ClientSvr(C/S)	: S
	// @ClassName		: --
	// @LuaApiName		: SetChatDisableAuth
	// @Description		: �����Ƿ��н���Ȩ��
	// @ReturnCode		: 
	// @ArgumentFlag	: od
	// @ArgumentComment	: pPlayer
	// @ArgumentComment	: 0��1
	// @LuaMarkEnd
	// -------------------------------------------------------------------------
	INT LuaSetChatDisableAuth(QLuaScript& sc)
	{
		KPlayer* pPlayer = NULL;
		KPlayerChat* pPlayerChat = NULL;
		INT nHasAuth = sc.GetInt(2) ? 1 : 0;

		KLuaPlayer *pLuaPlayer = dynamic_cast<KLuaPlayer *>(sc.GetObj(1));
		if (pLuaPlayer)
			pPlayer = pLuaPlayer->GetHim();
		LOG_PROCESS_ERROR(pPlayer);

		pPlayerChat = pPlayer->GetCtrl<KPlayerChat>();
		LOG_PROCESS_ERROR(pPlayerChat);

		pPlayerChat->SetDisableAuthority(nHasAuth);

		pPlayerChat->SyncDisableInfo();

	EXIT0:
		return 0;
	}

	// -------------------------------------------------------------------------
	// @ClientSvr(C/S)	: S
	// @ClassName		: --
	// @LuaApiName		: GetChatDisableAuth
	// @Description		: �Ƿ��н���Ȩ��
	// @ReturnCode		: 
	// @ArgumentFlag	: o
	// @ArgumentComment	: pPlayer
	// @LuaMarkEnd
	// -------------------------------------------------------------------------
	INT LuaGetChatDisableAuth(QLuaScript& sc)
	{
		KPlayer* pPlayer = NULL;
		KPlayerChat* pPlayerChat = NULL;

		KLuaPlayer *pLuaPlayer = dynamic_cast<KLuaPlayer *>(sc.GetObj(1));
		if (pLuaPlayer)
			pPlayer = pLuaPlayer->GetHim();
		LOG_PROCESS_ERROR(pPlayer);

		pPlayerChat = pPlayer->GetCtrl<KPlayerChat>();
		LOG_PROCESS_ERROR(pPlayerChat);

		sc.PushNumber(pPlayerChat->HasDisableAuthority());

	EXIT0:
		return 1;
	}

	// -------------------------------------------------------------------------
	// @ClientSvr(C/S)	: S
	// @ClassName		: --
	// @LuaApiName		: DisablePlayerChat
	// @Description		: ����
	// @ReturnCode		: 
	// @ArgumentFlag	: o[dd]
	// @ArgumentComment	: pPlayer
	// @ArgumentComment	: ����Ƶ��
	// @ArgumentComment	: ����ʱ��
	// @LuaMarkEnd
	// -------------------------------------------------------------------------
	INT LuaDisablePlayerChat(QLuaScript& sc)
	{
		KPlayer* pPlayer = NULL;
		KPlayerChat* pPlayerChat = NULL;
		INT nChannelId = trNearby;
		INT nLastTime = 30;		// Ĭ��30����

		KLuaPlayer *pLuaPlayer = dynamic_cast<KLuaPlayer *>(sc.GetObj(1));
		if (pLuaPlayer)
			pPlayer = pLuaPlayer->GetHim();
		LOG_PROCESS_ERROR(pPlayer);

		pPlayerChat = pPlayer->GetCtrl<KPlayerChat>();
		LOG_PROCESS_ERROR(pPlayerChat);

		if(sc.IsNumber(2))
		{
			nChannelId = sc.GetInt(2);
		}

		if(sc.IsNumber(3))
		{
			nLastTime = sc.GetInt(3);
		}

		pPlayerChat->SetDisableChannel(nChannelId);
		pPlayerChat->SetDisableEndTime(nLastTime);

		pPlayerChat->SyncDisableInfo();

	EXIT0:
		return 0;
	}

	// -------------------------------------------------------------------------
	// @ClientSvr(C/S)	: S
	// @ClassName		: --
	// @LuaApiName		: SetChatDisableStartTime
	// @Description		: ���ÿ�ʼ�������Ե�ʱ��
	// @ReturnCode		: 
	// @ArgumentFlag	: o
	// @ArgumentComment	: pPlayer
	// @LuaMarkEnd
	// -------------------------------------------------------------------------
	INT LuaSetChatDisableStartTime(QLuaScript& sc)
	{
		KPlayer* pPlayer = NULL;
		KPlayerChat* pPlayerChat = NULL;
		time_t tNow = KSysService::Time(NULL);

		KLuaPlayer *pLuaPlayer = dynamic_cast<KLuaPlayer *>(sc.GetObj(1));
		if (pLuaPlayer)
			pPlayer = pLuaPlayer->GetHim();
		LOG_PROCESS_ERROR(pPlayer);

		pPlayerChat = pPlayer->GetCtrl<KPlayerChat>();
		LOG_PROCESS_ERROR(pPlayerChat);

		pPlayerChat->SetDisableStartTime(tNow);

EXIT0:
		return 0;
	}

	// -------------------------------------------------------------------------
	// @ClientSvr(C/S)	: S
	// @ClassName		: --
	// @LuaApiName		: GetChatDisableStartTime
	// @Description		: �õ���ʼ���Ե�ʱ��
	// @ReturnCode		: 
	// @ArgumentFlag	: o
	// @ArgumentComment	: pPlayer
	// @LuaMarkEnd
	// -------------------------------------------------------------------------
	INT LuaGetChatDisableStartTime(QLuaScript& sc)
	{
		KPlayer* pPlayer = NULL;
		KPlayerChat* pPlayerChat = NULL;

		KLuaPlayer *pLuaPlayer = dynamic_cast<KLuaPlayer *>(sc.GetObj(1));
		if (pLuaPlayer)
			pPlayer = pLuaPlayer->GetHim();
		LOG_PROCESS_ERROR(pPlayer);

		pPlayerChat = pPlayer->GetCtrl<KPlayerChat>();
		LOG_PROCESS_ERROR(pPlayerChat);

		sc.PushNumber(pPlayerChat->GetDisableStartTime());
EXIT0:
		return 1;
	}

	// -------------------------------------------------------------------------
	// @ClientSvr(C/S)	: S
	// @ClassName		: --
	// @LuaApiName		: ModifyLastBroadcastTime
	// @Description		: �޸��ϴ���Ҹ��˹���ʱ��
	// @ReturnCode		: 
	// @ArgumentFlag	: odd
	// @ArgumentComment	: pPlayer
	// @ArgumentComment	: nId
	// @ArgumentComment	: dwLastTime
	// @LuaMarkEnd
	// -------------------------------------------------------------------------
	INT LuaModifyLastBroadcastTime(QLuaScript& sc)
	{
		KPlayer* pPlayer = NULL;
		KPlayerChat* pPlayerChat = NULL;
		INT nId = sc.GetInt(2);
		DWORD dwLastTime = sc.GetInt(3);

		KLuaPlayer *pLuaPlayer = dynamic_cast<KLuaPlayer *>(sc.GetObj(1));
		if (pLuaPlayer)
			pPlayer = pLuaPlayer->GetHim();
		LOG_PROCESS_ERROR(pPlayer);

		pPlayerChat = pPlayer->GetCtrl<KPlayerChat>();
		LOG_PROCESS_ERROR(pPlayerChat);

		pPlayerChat->ModifyBroadcastInfo(nId, dwLastTime);
EXIT0:
		return 0;
	}

	// -------------------------------------------------------------------------
	// @ClientSvr(C/S)	: S
	// @ClassName		: --
	// @LuaApiName		: GetLastBroadcastTime
	// @Description		: �õ��ϴ���Ҹ��˹���ʱ��
	// @ReturnCode		: 
	// @ArgumentFlag	: od
	// @ArgumentComment	: pPlayer
	// @ArgumentComment	: nId
	// @LuaMarkEnd
	// -------------------------------------------------------------------------
	INT LuaGetLastBroadcastTime(QLuaScript& sc)
	{
		KPlayer* pPlayer = NULL;
		KPlayerChat* pPlayerChat = NULL;
		INT nId = sc.GetInt(2);
		DWORD dwLastTime = 0;

		KLuaPlayer *pLuaPlayer = dynamic_cast<KLuaPlayer *>(sc.GetObj(1));
		if (pLuaPlayer)
			pPlayer = pLuaPlayer->GetHim();
		LOG_PROCESS_ERROR(pPlayer);

		pPlayerChat = pPlayer->GetCtrl<KPlayerChat>();
		LOG_PROCESS_ERROR(pPlayerChat);

		dwLastTime = pPlayerChat->GetLastBroadcastTime(nId);
		sc.PushNumber(dwLastTime);
EXIT0:
		return 1;
	}

#endif

	#include "kchatscript_table.hpp"
}

BOOL g_RegisterChatScriptFun()
{
	return g_cScriptManager.RegisterTableFuncs("KChat", kchatscript::arFunction, countof(kchatscript::arFunction));
}



// -------------------------------------------------------------------------
