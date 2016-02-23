/* -------------------------------------------------------------------------
//	�ļ���		��	kgc_mailprotocalhandler.cpp
//	������		��	xiewenzhe
//	����ʱ��	��	2011/5/18 9:56:21
//	��������	��	��������GS��Э��
//
// -----------------------------------------------------------------------*/

#include "stdafx.h"
#include "kgc_mailprotocalhandler.h"
#include "kmailboxmanager.h"
#include "kgc_mailmodule.h"
#include "kcondmailmanager.h"
#include "kmailplayermanager.h"
#include "kmailcenter.h"
#include "onlinegamebase/ksysservice.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// -------------------------------------------------------------------------

KGC_MailProtocalHandler KGC_MailProtocalHandler::ms_inst;

BOOL KMailCountNotifier::Init(CONST KMAIL_INFO *pInfo)
{
	QCONFIRM_RET_FALSE(pInfo && pInfo->nMailID == 0);
	if (pInfo->nMailSize > sizeof(m_szBuffer))
	{
		QLogPrintf(LOG_ERR, "[mail] MailId:%lld MailContent's Size Too Large!", pInfo->nMailID);
		return FALSE;
	}
	m_sInfo = *pInfo;
	m_sInfo.pMailData = m_szBuffer;
	memcpy(m_szBuffer, pInfo->pMailData, pInfo->nMailSize);
	return TRUE;
}

BOOL KMailCountNotifier::NotifyMailCount(INT64 nMailCount)
{
	QCONFIRM_RET_FALSE(nMailCount >= 0);
	if (nMailCount < KD_MAIL_MAX_COMMON_COUNT)
	{
		// Ͷ�ݵ�����
		SendMail(m_sInfo.dwReceiverId, &m_sInfo);
	}
	else
	{
		if (m_sInfo.nType != emKMAIL_TYPE_PLAYER)
		{
			// ��������
			// �����������ʼ�����Ͷ�ݵ�����
			// ���������ʼ�����ֱ�Ӷ������ݲ���������
			SendMail(m_sInfo.dwReceiverId, &m_sInfo);
		}
		else
		{
			// ��������ͨ����ʼ�������ֱ�Ӻ��Ե�
			IKOnlinedPlayerMgr* pPlayerMgr = KGC_MailModule::Instance()->GetOnlinePlayerMgr();
			QCONFIRM_RET_FALSE(pPlayerMgr);
			KRole* pPlayer = pPlayerMgr->GetPlayerById(m_sInfo.dwReceiverId);
			QCONFIRM_RET_FALSE(pPlayer);

			QLogPrintf(LOG_ERR, "[mail] %s MailBox is FUll, Refuse Receive PlayerMail!", pPlayer->GetPlayerName());
		}
	}
	return TRUE;
}

BOOL KMailCountNotifier::SendMail(DWORD dwPlayerId, KMAIL_INFO *pMailInfo)
{
	// �ʼ�����ʧ�ܶ���LOG
	static LPCTSTR pszItemInfo = "{ClassId:%d,StackCount:%d,TimeOutType:%d,TimeOut:%d,BuyPrice:%d},";
	static LPCTSTR pszFormat = "[%s] SendSysMail PlayerName: %s, ItemInfo: %s, MailType: %d";
	BOOL bResult = FALSE;
	IKOnlinedPlayerMgr* pPlayerMgr = NULL;
	KRole* pPlayer = NULL;
	IKGcServer* pGcServer = NULL;
	KMailBox *pMailBox = NULL;
	KMail* pMail = NULL;
	INT nServerID = 0;
	INT nCount = 0;
		
	PROCESS_ERROR(pMailInfo && pMailInfo->nMailID == 0);
	pPlayerMgr = KGC_MailModule::Instance()->GetOnlinePlayerMgr();
	PROCESS_ERROR(pPlayerMgr);
	pPlayer = pPlayerMgr->GetPlayerById(dwPlayerId);
	PROCESS_ERROR(pPlayer);
	pGcServer = KGC_MailModule::Instance()->GetIKGcServer();
	PROCESS_ERROR(pGcServer);

	// �ȼӵ����ݿ���
	KMailDatabase::Instance()->AddMail(dwPlayerId, pMailInfo);
	PROCESS_ERROR(pMailInfo->nMailID > 0);

	// ��������������ʼ���
	if (pMailInfo->nType == emKMAIL_TYPE_PLAYER)
	{
		nCount = KMailPlayerManager::Instance()->GetPlayerMailCount(dwPlayerId);
		KMailPlayerManager::Instance()->SetPlayerMailCount(dwPlayerId, nCount + 1);
	}

	if (pMailInfo->nType == emKMAIL_TYPE_DELIVERY)
	{
		// ���������ߣ�������Ҫֱ������
		nServerID = pPlayer->GetOnlineServer();
		if (nServerID > 0)
			bResult = KGC_MailProtocalHandler::Instance()->DeliveryMailByInfo(pMailInfo, nServerID);
		else
			bResult = TRUE;
		
		PROCESS_ERROR(FALSE);
	}
	
	pMailBox = KMailBoxManager::Instance()->FindMailBox(dwPlayerId);
	if (pMailBox)
	{
		// ��������Ѿ����ص��ڴ���	
		if (!pMailBox->LoadMail(pMailInfo, &pMail) || !pMail)
		{
			QLogPrintf(
				LOG_ERR, 
				"[mail] KMailCountNotifier::SendMail playerId:%d mailbox load mailId:%lld mail failed!",
				dwPlayerId, pMailInfo->nMailID
				);

			PROCESS_ERROR(FALSE);
		}
		
		if (pMail->CanPost())
		{
			nServerID = pPlayer->GetOnlineServer();
			if (nServerID > 0)
			{
				// ���ʼ�֪ͨ	
				KMAIL_G2S_PROTO_ADDMAIL sNotify;
				sNotify.dwPlayerId	 = pPlayer->GetId();
				sNotify.nMailID		 = pMailInfo->nMailID;
				bResult = pGcServer->Send(nServerID, &sNotify, sizeof(sNotify));
			}
		}
	}
	else
	{
		pMail = KMailBoxManager::Instance()->AllocateMail();
		if (!pMail || !pMail->Load(pMailInfo))
		{
			KMailBoxManager::Instance()->FreeMail(pMail);
			
			QLogPrintf(
				LOG_ERR, 
				"[mail] KMailCountNotifier::SendMail playerId:%d mailbox load mailId:%lld mail failed!",
				dwPlayerId, pMailInfo->nMailID
				);

			PROCESS_ERROR(FALSE);
		}

		if (pMail->CanPost())
		{
			nServerID = pPlayer->GetOnlineServer();
			if (nServerID > 0)
			{
				// ���ʼ�֪ͨ	
				KMAIL_G2S_PROTO_ADDMAIL sNotify;
				sNotify.dwPlayerId	 = pPlayer->GetId();
				sNotify.nMailID		 = pMailInfo->nMailID;
				bResult = pGcServer->Send(nServerID, &sNotify, sizeof(sNotify));
			}
		}

		KMailBoxManager::Instance()->FreeMail(pMail);
	}

	bResult = TRUE;
EXIT0:
	if (!bResult)
	{
		// ϵͳ�ʼ�ʧ�ܶ�Ҫ��LOG
		QLogPrintf(LOG_ERR, "[mail] %s", "PostSysMail Failed!");

		//KMAIL_DBINFO* pDbInfo = (KMAIL_DBINFO*)pMailInfo->pMailData;
		//if (pDbInfo)
		//{
		//	CHAR szItemInfo[1024];
		//	CHAR szInfoData[1024];
		//	INT nItemCount = (pDbInfo->wSize - pDbInfo->wAttachOffet) / sizeof(KItemData_Common);

		//	if (nItemCount > 0)
		//	{
		//		LPTSTR pData = (LPTSTR)pDbInfo;
		//		KItemData_Common* pItem = (KItemData_Common*)(&(pData[pDbInfo->wAttachOffet]));
		//		LPSTR pszItem = szItemInfo;
		//		*pszItem++ = '{';

		//		for (INT i=0; i<nItemCount; ++i)
		//		{
		//			pszItem += sprintf(pszItem, pszItemInfo, pItem->dwClassID, pItem->wStackCount, 
		//				pItem->byTimeoutType, pItem->dwTimeout, pItem->dwBuyPrice);
		//		}

		//		*pszItem++ = '}';
		//	}
		//	else
		//	{
		//		sprintf(szItemInfo, "%s", "No Item");
		//	}

		//	sprintf(szInfoData, pszFormat, bResult ? "OK" : "Fail", pPlayer->GetPlayerName(), szItemInfo, pMailInfo->nType);
		//	QLogPrintf(LOG_ERR, "[mail] %s", szInfoData);
		//}
	}

	return TRUE;
}

KGC_MailProtocalHandler::KGC_MailProtocalHandler() : m_pIKOnlinePlayerMgr(NULL),
													 m_pIKGcServer(NULL)
{
	memset(m_szBuffer, 0, sizeof(m_szBuffer));
}

KGC_MailProtocalHandler::~KGC_MailProtocalHandler()
{

}

BOOL KGC_MailProtocalHandler::Init()
{
	m_pIKOnlinePlayerMgr = KGC_MailModule::Instance()->GetOnlinePlayerMgr();
	QCONFIRM_RET_FALSE(m_pIKOnlinePlayerMgr);
	m_pIKGcServer = KGC_MailModule::Instance()->GetIKGcServer();
	QCONFIRM_RET_FALSE(m_pIKGcServer);

	m_poolNotifiers.Init(1, 1);
	return TRUE;
}

BOOL KGC_MailProtocalHandler::UnInit()
{
	return TRUE;
}

BOOL KGC_MailProtocalHandler::PostSysMail(DWORD dwReceiverId, LPCSTR pszCaption, LPCSTR pszContent, 
										  KItemData_Common* pItemData, INT nItemCount, INT nIconId)
{
	QCONFIRM_RET_FALSE(pszCaption && pszContent);
	KRole  * pReceiver = m_pIKOnlinePlayerMgr->GetPlayerById(dwReceiverId);
	QCONFIRM_RET_FALSE(pReceiver);

	// ��֯�ʼ���Ϣ
	KMAIL_INFO sMailInfo;
	memset(&sMailInfo, 0, sizeof(KMAIL_INFO));
	sMailInfo.nMailID = 0;
	sMailInfo.nStat = emKMAIL_STAT_UNREAD;
	sMailInfo.dwSenderId = 0;
	sMailInfo.szSender[0] = '\0';
	sMailInfo.dwReceiverId = dwReceiverId;
	sMailInfo.nType = emKMAIL_TYPE_SYSTEM;
	sMailInfo.nCondLen = 0;
	sMailInfo.szCond[0] = '\0';

	KMAIL sMail;
	memset(&sMail, 0, sizeof(KMAIL));
	sMail.nCaptionLen	= (INT)(strlen(pszCaption) + 1);
	sMail.nContentLen	= (INT)(strlen(pszContent)+ 1);
	sMail.nIconId		= nIconId;
	sMail.pCaption		= (LPSTR)pszCaption;
	sMail.pContent		= (LPSTR)pszContent;
	sMail.pItemData		= pItemData;
	if (!pItemData || nItemCount < 0)
	{
		sMail.nItemCount = 0;
	}
	else
	{
		sMail.nItemCount = nItemCount;
	}

	KMAIL_DBINFO* pDBInfo = InitMailData(&sMail);
	QCONFIRM_RET_FALSE(pDBInfo);

	sMailInfo.nMailSize = pDBInfo->wSize;
	sMailInfo.pMailData = (CHAR*)pDBInfo;
	return SendSystemMail(pReceiver, &sMailInfo);
}

BOOL KGC_MailProtocalHandler::DeliveryMailByMail(KMail* pMail, INT nConnectId)
{
	QCONFIRM_RET_FALSE(pMail);

	IKEnumMailItem* pEnum = NULL;
	if (!pMail->GetItemList(&pEnum) || pEnum->GetCount() > KD_MAIL_MAX_ITEM_COUNT)
	{
		QLogPrintf(
			LOG_ERR, 
			"[mail] KGC_MailProtocalHandler::DeliveryMailByMail GetItemList Failed! or ItemCount > %d!", 
			KD_MAIL_MAX_ITEM_COUNT
			);
		return FALSE;
	}

	INT nContentLen = 0;
	LPCSTR pContent = pMail->GetContent(nContentLen);
	QCONFIRM_RET_FALSE(nContentLen > 0);

	INT nItemCount = pEnum->GetCount();
	INT nBufLen = sizeof(KMAIL_G2S_PROTO_FETCHMAIL) + nContentLen + nItemCount * sizeof(KMAIL_ITEM_DATA);
	if (nBufLen > sizeof(m_szBuffer))
	{
		QLogPrintf(
			LOG_ERR, 
			"[mail] %s", 
			"KGC_MailProtocalHandler::DeliveryMailByMail KMAIL_G2S_PROTO_FETCHMAIL size too large!"
			);
		return FALSE;
	}

	// �����ʼ����ĺ͸���
	KMAIL_G2S_PROTO_FETCHMAIL *pHead = (KMAIL_G2S_PROTO_FETCHMAIL*)m_szBuffer;
	*pHead = KMAIL_G2S_PROTO_FETCHMAIL();
	pHead->dwPlayerId = pMail->GetInfo()->dwReceiverId;
	pHead->nMailID = pMail->GetInfo()->nMailID;
	pHead->nIconId = pMail->GetInfo()->nIconId;
	pHead->nType = pMail->GetInfo()->nType;
	pHead->wContentLen = (WORD)nContentLen;
	pHead->nItemCount = nItemCount;
	KMAIL_ITEM_DATA* pItemData = pHead->aryItem;
	while (pEnum->Next(&(pItemData->sItem), pItemData->nItemIndex))
	{
		pItemData++;
	}
	QStrCpyLen((LPSTR)&pHead->aryItem[nItemCount], pContent, nContentLen);

	if (!m_pIKGcServer->Send(nConnectId, m_szBuffer, nBufLen))
	{
		QLogPrintf(
			LOG_ERR, 
			"[mail] %s", 
			"KGC_MailProtocalHandler::DeliveryMailByMail KMAIL_G2S_PROTO_FETCHMAIL send failed!"
			);
		return FALSE;
	}

	return TRUE;
}


BOOL KGC_MailProtocalHandler::DeliveryMailByInfo(KMAIL_INFO* pMailInfo, INT nConnectId)
{
	QCONFIRM_RET_FALSE(pMailInfo && pMailInfo->nMailID > 0);

	KMail* pMail = KMailBoxManager::Instance()->AllocateMail();
	if (!pMail || !pMail->Load(pMailInfo))
	{
		KMailBoxManager::Instance()->FreeMail(pMail);

		QLogPrintf(LOG_ERR, "[mail] %s", "KMailCountNotifier::DeliveryMailByInfo load mail failed!");
		return FALSE;
	}

	DeliveryMailByMail(pMail, nConnectId);
	KMailBoxManager::Instance()->FreeMail(pMail);

	return TRUE;
}

BOOL KGC_MailProtocalHandler::ProcessData(INT nConnectId, LPBYTE pData, UINT uSize)
{
	QCONFIRM_RET_FALSE(pData && nConnectId > 0);

	KPTC_HEADER_BASE* pMsg = (KPTC_HEADER_BASE*)pData;
	switch (pMsg->byProtocol)
	{
	case emKMAIL_S2G_PROTO_PLAYER_LOGIN:
		Process_PlayerLogin(pData, uSize, nConnectId);
		break;
	case emKMAIL_S2G_PROTO_PLAYER_LOGOUT:
		Process_PlayerLogout(pData, uSize, nConnectId);
		break;
	case emKMAIL_S2G_PROTO_FETCHINFO:
		Process_FetchInfo(pData, uSize, nConnectId);
		break;
	case emKMAIL_S2G_PROTO_FETCHCONDINFO:
		Process_FetchCondInfo(pData, uSize, nConnectId);
		break;
	case emKMAIL_S2G_PROTO_FETCHMAIL:
		Process_FetchMail(pData, uSize, nConnectId);
		break;
	case emKMAIL_S2G_PROTO_DELMAIL:
		Process_DeleteMail(pData, uSize, nConnectId);
		break;
	case emKMAIL_S2G_PROTO_FETCHITEM:
		Process_FetchItem(pData, uSize, nConnectId);
		break;
	case emKMAIL_S2G_PROTO_DELETEITEM:
		Process_DeleteItem(pData, uSize, nConnectId);
		break;
	case emKMAIL_S2G_PROTO_SENDMAIL:
		Process_SendMail(pData, uSize, nConnectId);
		break;
	case emKMAIL_S2G_PROTO_SENDCONDMAIL:
		Process_SendCondMail(pData, uSize, nConnectId);
		break;
	case emKMAIL_S2G_PROTO_CHECKRECEIVER:
		Process_CheckReceiver(pData, uSize, nConnectId);
		break;
	default:
		ASSERT(FALSE);
		QLogPrintf(LOG_ERR, "[mail] %s", "KGC_MailProtocalHandler::ProcessData Invalid S2G Protocol!");
		break;
	}

	return TRUE;
}

BOOL KGC_MailProtocalHandler::Process_PlayerLogin(LPBYTE pData, UINT uSize, INT nConnectId)
{
	QCONFIRM_RET_FALSE(pData && nConnectId > 0);

	KMAIL_S2G_PROTO_PLAYER_LOGIN* pMsg = (KMAIL_S2G_PROTO_PLAYER_LOGIN*)pData;
	if (uSize != sizeof(KMAIL_S2G_PROTO_PLAYER_LOGIN) ||
		pMsg->dwPlayerId == 0)
	{
		QLogPrintf(LOG_ERR, "[mail] %s", "KMAIL_S2G_PROTO_PLAYER_LOGIN size error!! or Login Player id = 0!!");
		return FALSE;
	}

	return KMailCenter::Instance()->OnPlayerLogin(pMsg->dwPlayerId);
}

BOOL KGC_MailProtocalHandler::Process_PlayerLogout(LPBYTE pData, UINT uSize, INT nConnectId)
{
	QCONFIRM_RET_FALSE(pData && nConnectId > 0);

	KMAIL_S2G_PROTO_PLAYER_LOGOUT* pMsg = (KMAIL_S2G_PROTO_PLAYER_LOGOUT*)pData;
	if (uSize != sizeof(KMAIL_S2G_PROTO_PLAYER_LOGOUT) ||
		pMsg->dwPlayerId == 0)
	{
		QLogPrintf(LOG_ERR, "[mail] %s", "KMAIL_S2G_PROTO_PLAYER_LOGOUT size error!! or Logout Player id = 0!!");
		return FALSE;
	}

	return KMailCenter::Instance()->OnPlayerLogout(pMsg->dwPlayerId);
}

BOOL KGC_MailProtocalHandler::Process_FetchInfo(LPBYTE pData, UINT uSize, INT nConnectId)
{
	QCONFIRM_RET_FALSE(pData && nConnectId > 0);
	KMAIL_S2G_PROTO_FETCHINFO* pMsg = (KMAIL_S2G_PROTO_FETCHINFO*)pData;
	if (uSize != sizeof(KMAIL_S2G_PROTO_FETCHINFO) ||
		pMsg->dwPlayerId == 0)
	{
		QLogPrintf(
			LOG_ERR, 
			"[mail] %s", 
			"KGC_MailProtocalHandler::Process_FetchInfo KMAIL_S2G_PROTO_FETCHINFO size error!! or Player id = 0!!"
		);
		return FALSE;
	}

	KMailBox* pMailBox = KMailBoxManager::Instance()->FindMailBox(pMsg->dwPlayerId);
	if (!pMailBox)
	{
		// û�����ڴ��Ҫ���¼����������
		KMAIL_FETCHMAIL_CALLBACK_PARAM_FETCHINFO sParam;
		sParam.nConnectId = nConnectId;
		return KMailBoxManager::Instance()->Load(pMsg->dwPlayerId, &sParam);
	}
	else
	{
		if (KMailPlayerManager::Instance()->GetMailLoaded(pMsg->dwPlayerId) == 1)
		{
			// �Ѿ��������
			IKEnumMail* pEnum = NULL;
			if (pMailBox->GetAllMail(&pEnum))
			{
				return FetchMailList(pEnum, pMsg->dwPlayerId, nConnectId);
			}
			else
			{
				// ���ʼ�
				KMailPlayerManager::Instance()->SetPlayerMailCount(pMsg->dwPlayerId, 0);

				KMAIL_G2S_PROTO_FETCHINFO sNotify;
				sNotify.wCount		 = 0;
				sNotify.dwPlayerId	 = pMsg->dwPlayerId;
				sNotify.nCurrentTime = (INT)KSysService::Time(NULL);

				QCONFIRM_RET_FALSE(m_pIKGcServer);
				return m_pIKGcServer->Send(nConnectId, &sNotify, sizeof(sNotify));
			}
		}
	}

	return TRUE;
}

BOOL KGC_MailProtocalHandler::FetchMailList(IKEnumMail *pEnum, DWORD dwPlayerId, INT nConnectId)
{
	QCONFIRM_RET_FALSE(pEnum && nConnectId > 0);
	INT nMailCount = pEnum->GetCount();
	QCONFIRM_RET_FALSE(nMailCount > 0);

	INT nDataLen = sizeof(KMAIL_G2S_PROTO_FETCHINFO) + sizeof(KMAIL_PROTO_INFO) * nMailCount;
	if (nDataLen > sizeof(m_szBuffer))
	{
		QLogPrintf(LOG_ERR, "[mail] %s", "KMAIL_G2S_PROTO_FETCHINFO size too large!!");
		return FALSE;
	}

	KMAIL_G2S_PROTO_FETCHINFO *pHead = (KMAIL_G2S_PROTO_FETCHINFO*)m_szBuffer;
	*pHead = KMAIL_G2S_PROTO_FETCHINFO();
	pHead->wCount		= nMailCount;
	pHead->dwPlayerId	= dwPlayerId;
	pHead->nCurrentTime = (INT)KSysService::Time(NULL);
	KMAIL_PROTO_INFO *pInfo = pHead->aryMails;

	KMail* pMail = NULL;
	INT nCount = 0;
	INT nPlayerMailCount = 0;
	while (pEnum->NextMail(&pMail) && nCount < nMailCount)
	{
		if (!pMail)
		{
			QLogPrintf(LOG_ERR, "[mail] %s", "FetchMailList mail null");
			continue;
		}

		CONST KMail::KMAILHEAD *pMailHead = pMail->GetInfo();
		if (pMailHead->dwReceiverId <= 0)
		{
			QLogPrintf(LOG_ERR, "[mail] %s", "FetchMailList receiverId <= 0");
			continue;
		}

		KRole* pReceiver = m_pIKOnlinePlayerMgr->GetPlayerById(pMailHead->dwReceiverId);
		if (!pReceiver)
		{
			QLogPrintf(LOG_ERR, "[mail] FetchMailList receiverId:%d player not exist!", pMailHead->dwReceiverId);
			continue;
		}

		if (!pMail->CanPost())
		{
			continue;
		}

		if (pMail->GetInfo()->nType == emKMAIL_TYPE_DELIVERY)
		{
			// ��������ʾ���ʼ��б���
			continue;
		}

		if (pMail->GetInfo()->nType == emKMAIL_TYPE_PLAYER)
		{
			// ͳ������ʼ�����
			nPlayerMailCount++;
		}

		pInfo->nMailID	 = pMailHead->nMailID;
		pInfo->nType	 = pMailHead->nType;
		pInfo->nStat	 = pMailHead->nStat;
		pInfo->nSendTime = (INT)KMail::MkTime(&pMailHead->sSendTime);
		pInfo->nIconId   = pMailHead->nIconId;
		
		// ����
		INT nCaptionLen = 0;
		LPCSTR pszCaption = pMail->GetCaption(nCaptionLen);
		strncpy(pInfo->szCaption, pszCaption, sizeof(pInfo->szCaption) - 1);
		pInfo->szCaption[sizeof(pInfo->szCaption) - 1] = 0;
		// ������
		if (pMailHead->dwSenderId == 0)
		{
			// ϵͳ�ʼ�
			strcpy(pInfo->szSender, "ϵͳ");
		}
		else
		{
			// ����ʼ�
			strncpy(pInfo->szSender, pMailHead->szSender, sizeof(pInfo->szSender) - 1);
			pInfo->szSender[sizeof(pInfo->szSender) - 1] = 0;
		}
		// ������
		strncpy(pInfo->szReceiver, pReceiver->GetPlayerName(), sizeof(pInfo->szReceiver) - 1);
		pInfo->szReceiver[sizeof(pInfo->szReceiver) - 1] = 0;
		
		pInfo++;
		nCount++;
	}

	// ��������������
	KMailPlayerManager::Instance()->SetPlayerMailCount(dwPlayerId, nPlayerMailCount);
	
	if (nCount < nMailCount)
	{
		nDataLen = sizeof(KMAIL_G2S_PROTO_FETCHINFO) + sizeof(KMAIL_PROTO_INFO) * nCount;
		pHead->wCount = nCount;
	}

	return m_pIKGcServer->Send(nConnectId, pHead, nDataLen);
}

BOOL KGC_MailProtocalHandler::Process_FetchCondInfo(LPBYTE pData, UINT uSize, INT nConnectId)
{
	QCONFIRM_RET_FALSE(pData && nConnectId > 0);
	KMAIL_S2G_PROTO_FETCHCONDINFO* pMsg = (KMAIL_S2G_PROTO_FETCHCONDINFO*)pData;
	if (uSize != sizeof(KMAIL_S2G_PROTO_FETCHCONDINFO) ||
		pMsg->dwPlayerId == 0)
	{
		QLogPrintf(LOG_ERR, "[mail] %s", "KMAIL_S2G_PROTO_FETCHCONDINFO size error!! or Player id = 0!!");
		return FALSE;
	}

	KMailBox* pMailBox = KMailBoxManager::Instance()->FindMailBox(pMsg->dwPlayerId);
	if (!pMailBox)
	{
		// û�����ڴ��Ҫ���¼����������
		KMAIL_FETCHMAIL_CALLBACK_PARAM_FETCHCONDINFO sParam;
		sParam.nConnectId = nConnectId;
		return KMailBoxManager::Instance()->Load(pMsg->dwPlayerId, &sParam);
	}
	else
	{
		if (KMailPlayerManager::Instance()->GetMailLoaded(pMsg->dwPlayerId) == 1)
		{
			KCondMailManager* pCondMailManager = KCondMailManager::Instance();
			QCONFIRM_RET_FALSE(pCondMailManager);

			//Ͷ��ϵͳ�ʼ�
			pCondMailManager->PostMail(pMsg->dwPlayerId);
			return Process_FetchInfo(pData, uSize, nConnectId);
		}
	}

	return TRUE;
}

BOOL KGC_MailProtocalHandler::Process_FetchMail(LPBYTE pData, UINT uSize, INT nConnectId)
{
	QCONFIRM_RET_FALSE(pData && nConnectId > 0);
	KMAIL_S2G_PROTO_FETCHMAIL* pMsg = (KMAIL_S2G_PROTO_FETCHMAIL*)pData;
	if (uSize != sizeof(KMAIL_S2G_PROTO_FETCHMAIL) || 
		pMsg->dwPlayerId == 0)
	{
		QLogPrintf(LOG_ERR, "[mail] %s", "KMAIL_S2G_PROTO_FETCHMAIL size error!! or Player id = 0!!");
		return FALSE;
	}

	KMailBox* pMailBox = KMailBoxManager::Instance()->FindMailBox(pMsg->dwPlayerId);
	if (!pMailBox)
	{
		// û�����ڴ��Ҫ���¼����������
		KMAIL_FETCHMAIL_CALLBACK_PARAM_FETCHMAIL sParam;
		sParam.nConnectId = nConnectId;
		sParam.nMailId = pMsg->nMailID;
		return KMailBoxManager::Instance()->Load(pMsg->dwPlayerId, &sParam);
	}
	else
	{
		if (KMailPlayerManager::Instance()->GetMailLoaded(pMsg->dwPlayerId) == 1)
		{
			KMail* pMail = KMailBoxManager::Instance()->FindMail(pMsg->dwPlayerId, pMsg->nMailID);
			QCONFIRM_RET_FALSE(pMail);
			
			IKEnumMailItem* pEnum = NULL;
			if (!pMail->GetItemList(&pEnum) || pEnum->GetCount() > KD_MAIL_MAX_ITEM_COUNT)
			{
				QLogPrintf(
					LOG_ERR, 
					"[mail] KGC_MailProtocalHandler::Process_FetchMail GetItemList Failed! or ItemCount > %d!", 
					KD_MAIL_MAX_ITEM_COUNT
				);
				return FALSE;
			}

			INT nContentLen = 0;
			LPCSTR pContent = pMail->GetContent(nContentLen);
			QCONFIRM_RET_FALSE(nContentLen > 0);

			INT nItemCount = pEnum->GetCount();
			INT nBufLen = sizeof(KMAIL_G2S_PROTO_FETCHMAIL) + nContentLen + nItemCount * sizeof(KMAIL_ITEM_DATA);
			if (nBufLen > sizeof(m_szBuffer))
			{
				QLogPrintf(LOG_ERR, "[mail] %s", "KMAIL_G2S_PROTO_FETCHMAIL size too large!");
				return FALSE;
			}

			// �����ʼ����ĺ͸���
			KMAIL_G2S_PROTO_FETCHMAIL *pHead = (KMAIL_G2S_PROTO_FETCHMAIL*)m_szBuffer;
			*pHead = KMAIL_G2S_PROTO_FETCHMAIL();
			pHead->dwPlayerId = pMsg->dwPlayerId;
			pHead->nMailID = pMsg->nMailID;
			pHead->nIconId = pMail->GetInfo()->nIconId;
			pHead->nType = pMail->GetInfo()->nType;
			pHead->wContentLen = (WORD)nContentLen;
			pHead->nItemCount = nItemCount;
			KMAIL_ITEM_DATA* pItemData = pHead->aryItem;
			while (pEnum->Next(&(pItemData->sItem), pItemData->nItemIndex))
			{
				pItemData++;
			}
			QStrCpyLen((LPSTR)&pHead->aryItem[nItemCount], pContent, nContentLen);

			if (!m_pIKGcServer->Send(nConnectId, m_szBuffer, nBufLen))
			{
				QLogPrintf(LOG_ERR, "[mail] %s", "KMAIL_G2S_PROTO_FETCHMAIL send failed!");
				return FALSE;
			}

			// ���ʼ��޸ĳ��Ѷ�״̬
			if (pMail->GetInfo()->nStat == emKMAIL_STAT_UNREAD)
			{
				pMail->SetStatus(emKMAIL_STAT_READED);
				return pMailBox->Save(pMail);
			}

			return TRUE;
		}
	}

	return TRUE;
}

BOOL KGC_MailProtocalHandler::Process_DeleteMail(LPBYTE pData, UINT uSize, INT nConnectId)
{
	QCONFIRM_RET_FALSE(pData && nConnectId > 0);

	KMAIL_S2G_PROTO_DELMAIL *pMsg = (KMAIL_S2G_PROTO_DELMAIL*)pData;
	if (uSize != sizeof(KMAIL_S2G_PROTO_DELMAIL) ||
		pMsg->dwPlayerId == 0)
	{
		QLogPrintf(LOG_ERR, "[mail] %s", "KMAIL_S2G_PROTO_DELMAIL size error!! or Player id = 0!!");
		return FALSE;
	}

	KMailBox* pMailBox = KMailBoxManager::Instance()->FindMailBox(pMsg->dwPlayerId);
	if (!pMailBox)
	{
		// û�����ڴ��Ҫ���¼����������
		KMAIL_FETCHMAIL_CALLBACK_PARAM_DELETEMAIL sParam;
		sParam.nConnectId = nConnectId;
		sParam.nMailId = pMsg->nMailID;
		return KMailBoxManager::Instance()->Load(pMsg->dwPlayerId, &sParam);
	}
	else
	{
		if (KMailPlayerManager::Instance()->GetMailLoaded(pMsg->dwPlayerId) == 1)
		{
			KMail* pMail = KMailBoxManager::Instance()->FindMail(pMsg->dwPlayerId, pMsg->nMailID);
			QCONFIRM_RET_FALSE(pMail);
			
			CONST KMail::KMAILHEAD* pInfo = pMail->GetInfo();
			if (pInfo->nMailID != pMsg->nMailID ||
				pInfo->nStat == emKMAIL_STAT_UNREAD ||		// δ���ʼ�����ɾ��
				pMail->GetAttachItem(0) != NULL)			// ������Ʒʱ����ɾ��
			{
				QLogPrintf(LOG_ERR, "[mail] %s", "DeleteMail not meet condition!");
				return FALSE;
			}

			if (pMail->GetInfo()->nType == emKMAIL_TYPE_PLAYER)
			{
				// ��������������
				INT nCount = KMailPlayerManager::Instance()->GetPlayerMailCount(pMsg->dwPlayerId);
				KMailPlayerManager::Instance()->SetPlayerMailCount(pMsg->dwPlayerId, nCount - 1);
			}

			if (!pMailBox->DeleteMail(pMsg->nMailID))
			{
				QLogPrintf(LOG_ERR, "[mail] MailBox deleteMail mailId:%lld Failed!", pMsg->nMailID);
				return FALSE;
			}

			// ֪ͨ�ʼ�ɾ��
			KMAIL_G2S_PROTO_DELMAIL sNotify;
			sNotify.dwPlayerId = pMsg->dwPlayerId;
			sNotify.nMailID = pMsg->nMailID;
			return m_pIKGcServer->Send(nConnectId, &sNotify, sizeof(sNotify));
		}
	}

	return TRUE;
}

BOOL KGC_MailProtocalHandler::Process_FetchItem(LPBYTE pData, UINT uSize, INT nConnectId)
{
	QCONFIRM_RET_FALSE(pData && nConnectId > 0);

	KMAIL_S2G_PROTO_FETCHITEM* pMsg = (KMAIL_S2G_PROTO_FETCHITEM*)pData;
	if (uSize != sizeof(KMAIL_S2G_PROTO_FETCHITEM) ||
		pMsg->dwPlayerId == 0)
	{
		QLogPrintf(LOG_ERR, "[mail] %s", "KMAIL_S2G_PROTO_FETCHITEM size error!! or Player id = 0!!");
		return FALSE;
	}

	KMailBox* pMailBox = KMailBoxManager::Instance()->FindMailBox(pMsg->dwPlayerId);
	if (!pMailBox)
	{
		// û�����ڴ��Ҫ���¼����������
		KMAIL_FETCHMAIL_CALLBACK_PARAM_FETCHITEM sParam;
		sParam.nConnectId = nConnectId;
		sParam.nMailId = pMsg->nMailID;
		sParam.byItemIndex = pMsg->nItemIdx;
		return KMailBoxManager::Instance()->Load(pMsg->dwPlayerId, &sParam);
	}
	else
	{
		if (KMailPlayerManager::Instance()->GetMailLoaded(pMsg->dwPlayerId) == 1)
		{
			KRole* pPlayer = m_pIKOnlinePlayerMgr->GetPlayerById(pMsg->dwPlayerId);
			QCONFIRM_RET_FALSE(pPlayer);

			KMail *pMail = KMailBoxManager::Instance()->FindMail(pMsg->dwPlayerId, pMsg->nMailID);
			if (!pMail || pMail->GetInfo()->nStat == emKMAIL_STAT_UNREAD)
			{
				if (!pMail)
				{
					QLogPrintf(
						LOG_ERR, 
						"[mail] KGC_MailProtocalHandler::Process_FetchItem Find no mail, playerId: %d, mailId: %lld", 
						pMsg->dwPlayerId, pMsg->nMailID
					);
				}
				else
				{
					QLogPrintf(
						LOG_ERR, 
						"[mail] KGC_MailProtocalHandler::Process_FetchItem Failed to fetch item because of illeagal status, playerId: %d , mailid: %lld, status:%d",
						pMsg->dwPlayerId, pMsg->nMailID, pMail->GetInfo()->nStat
					);
				}

				QLogPrintf(LOG_ERR, "[mail] %s", "FetchItem not meet condition!");
				return FALSE;
			}

			CONST KItemData_Common* pItem = pMail->GetAttachItem(pMsg->nItemIdx);
			if (!pItem)
			{
				QLogPrintf(LOG_ERR, "[mail] KGC_MailProtocalHandler::Process_FetchItem error ItemIndex: %d", pMsg->nItemIdx);
				return FALSE;
			}

			if (pMail->IsItemLocked(pMsg->nItemIdx))
			{
				QLogPrintf(
					LOG_ERR, 
					"[mail] Player:%d ask for mail:%lld itemidx:%d once more times!", 
					pPlayer->GetPlayerName(), pMsg->nMailID, pMsg->nItemIdx
				);
				return FALSE;
			}

			KMAIL_G2S_PROTO_FETCHITEM sNotify;
			sNotify.dwPlayerId = pMsg->dwPlayerId;
			sNotify.nMailID = pMsg->nMailID;
			sNotify.nItemIdx = pMsg->nItemIdx;
			sNotify.sItem = *pItem;
			sNotify.byMailType = pMail->GetInfo()->nType; // ����󷵻���Ʒ�Ƿ��
			if (m_pIKGcServer->Send(nConnectId, &sNotify, sizeof(sNotify)))
			{
				pMail->LockItem(pMsg->nItemIdx);
				return TRUE;
			}
			else
			{
				QLogPrintf(
					LOG_ERR, 
					"[mail] Player:%d ask for mail:%lld itemidx:%d Send2Gs Failed!", 
					pPlayer->GetPlayerName(), pMsg->nMailID, pMsg->nItemIdx
				);
				return FALSE;
			}
		}
	}

	return TRUE;
}

BOOL KGC_MailProtocalHandler::Process_DeleteItem(LPBYTE pData, UINT uSize, INT nConnectId)
{
	QCONFIRM_RET_FALSE(pData && nConnectId > 0);
	KMAIL_S2G_PROTO_DELETEITEM* pMsg = (KMAIL_S2G_PROTO_DELETEITEM*)pData;
	if (uSize != sizeof(KMAIL_S2G_PROTO_DELETEITEM) ||
		pMsg->dwPlayerId == 0)
	{
		QLogPrintf(LOG_ERR, "[mail] %s", "KMAIL_S2G_PROTO_DELETEITEM size error!! or Player id = 0!!");
		return FALSE;
	}

	KMailBox* pMailBox = KMailBoxManager::Instance()->FindMailBox(pMsg->dwPlayerId);
	if (!pMailBox)
	{
		// û�����ڴ��Ҫ���¼����������
		KMAIL_FETCHMAIL_CALLBACK_PARAM_DELETEITEM sParam;
		sParam.nConnectId = nConnectId;
		sParam.nMailId = pMsg->nMailID;
		sParam.byItemIndex = pMsg->nItemIdx;
		return KMailBoxManager::Instance()->Load(pMsg->dwPlayerId, &sParam);
	}
	else
	{
		if (KMailPlayerManager::Instance()->GetMailLoaded(pMsg->dwPlayerId) == 1)
		{
			KMail *pMail = KMailBoxManager::Instance()->FindMail(pMsg->dwPlayerId, pMsg->nMailID);
			if (!pMail || pMail->GetInfo()->nStat == emKMAIL_STAT_UNREAD)
			{
				QLogPrintf(LOG_ERR, "[mail] %s", "DeleteItem Mail is NUll or Mail UnRead!");
				return FALSE;
			}

			QCONFIRM_RET_FALSE(pMail->DeleteAttachItem(pMsg->nItemIdx));
			return pMailBox->Save(pMail);
		}
	}

	return TRUE;
}

BOOL KGC_MailProtocalHandler::Process_SendMail(LPBYTE pData, UINT uSize, INT nConnectId)
{
	QCONFIRM_RET_FALSE(pData && nConnectId > 0);
	KMAIL_S2G_PROTO_SENDMAIL *pMsg = (KMAIL_S2G_PROTO_SENDMAIL*)pData;
	if (uSize <= sizeof(KMAIL_S2G_PROTO_SENDMAIL) ||
		pMsg->wReceiverCount == 0 ||
		pMsg->wCaptionLen > KD_MAIL_MAX_CAPTION_LENGTH ||
		pMsg->wCaptionLen <= 0 ||
		pMsg->wContentLen > KD_MAIL_MAX_CONTENT_LENGTH ||
		pMsg->wContentLen <= 0)
	{
		QLogPrintf(LOG_ERR, "[mail] %s", "KMAIL_S2G_PROTO_SENDMAIL size error!");
		return FALSE;
	}

	INT nPackLen = sizeof(KMAIL_S2G_PROTO_SENDMAIL);
	nPackLen += pMsg->wReceiverCount * sizeof(DWORD);
	nPackLen += pMsg->byCondLen;
	nPackLen += pMsg->wCaptionLen;
	nPackLen += pMsg->wContentLen;
	nPackLen += pMsg->nItemCount * sizeof(KItemData_Common);
	QCONFIRM_RET_FALSE(uSize == nPackLen);

	KMAIL_INFO sMailInfo;
	memset(&sMailInfo, 0, sizeof(KMAIL_INFO));
	sMailInfo.nMailID = 0;
	sMailInfo.nStat = emKMAIL_STAT_UNREAD;
	sMailInfo.nType = pMsg->nType;
	if (!InitMailInfo(pMsg, &sMailInfo))
	{
		QLogPrintf(LOG_ERR, "[mail] %s", "Process_SendMail InitMailInfo Failed!");
		return FALSE;
	}

	return SendMail(pMsg, &sMailInfo);
}

BOOL KGC_MailProtocalHandler::Process_SendCondMail(LPBYTE pData, UINT uSize, INT nConnectId)
{
	QCONFIRM_RET_FALSE(pData && nConnectId > 0);

	KMAIL_S2G_PROTO_SENDCONDMAIL* pMsg = (KMAIL_S2G_PROTO_SENDCONDMAIL*)pData;
	if (uSize <= sizeof(KMAIL_S2G_PROTO_SENDCONDMAIL) ||
		pMsg->wCaptionLen == 0 ||
		pMsg->wContentLen == 0)
	{
		QLogPrintf(LOG_ERR, "[mail] %s", "KMAIL_S2G_PROTO_SENDCONDMAIL size error!");
		return FALSE;
	}

	INT nLen = sizeof(KMAIL_S2G_PROTO_SENDCONDMAIL);
	LPSTR pCondition = (LPSTR)&pData[nLen];
	nLen += pMsg->byCondLen;
	LPSTR pCaption = (LPSTR)&pData[nLen];
	nLen += pMsg->wCaptionLen;
	LPSTR pContent = (LPSTR)&pData[nLen];
	nLen += pMsg->wContentLen;
	KItemData_Common* pItemData = (KItemData_Common*)&pData[nLen];
	nLen += pMsg->nItemCount * sizeof(KItemData_Common);
	QCONFIRM_RET_FALSE(nLen == uSize);

	// ϵͳ�ʼ�ʧ�ܶ�Ҫ��LOG
	static LPCTSTR pszItemInfo = "{ClassId:%d,StackCount:%d,TimeOutType:%d,TimeOut:%d,BuyPrice:%d},";
	static LPCTSTR pszFormat = "[%s] SendCondMail ItemInfo: %s";
	BOOL bResult = TRUE;

	do 
	{
		KMAIL sInfo;
		sInfo.nCaptionLen	= pMsg->wCaptionLen;
		sInfo.nContentLen	= pMsg->wContentLen;
		sInfo.nItemCount	= pMsg->nItemCount;
		sInfo.nIconId		= pMsg->nIconId;
		sInfo.pCaption		= pCaption;
		sInfo.pContent		= pContent;
		sInfo.pItemData		= pItemData;
		KMAIL_DBINFO* pDBInfo = InitMailData(&sInfo);
		if (!pDBInfo)
		{
			QLogPrintf(LOG_ERR, "[mail] %s", "Process_SendCondMail InitMailData Failed!");
			bResult = FALSE;
			break;
		}


		KCONDMAIL_INFO sCondMail;
		memset(&sCondMail, 0, sizeof(KCONDMAIL_INFO));
		sCondMail.nCondLen	= pMsg->byCondLen;
		sCondMail.pCond		= pCondition;
		sCondMail.nMailID	= 0;
		sCondMail.pMail		= (CHAR*)pDBInfo;
		sCondMail.nMailLen	= pDBInfo->wSize;

		// �������ݿ�����ӣ��ɹ����ʼ����ᶪʧ�ˣ����������LOG��
		KMailDatabase::Instance()->AddCondMail(&sCondMail);
		if (sCondMail.nMailID <= 0)
		{
			bResult = FALSE;
			break;
		}

		KCondMailManager::Instance()->AddMail(&sCondMail);

		// ���������������Ͷ���ʼ�
		IKEnumPlayerId* pEnum = m_pIKOnlinePlayerMgr->EnumPlayer();
		QCONFIRM_RET_FALSE(pEnum);
		DWORD dwPlayerId = 0;
		KCondMailManager* pCondMailManager = KCondMailManager::Instance();
		while (pEnum->Next(dwPlayerId))
		{
			pCondMailManager->NotifyMail(dwPlayerId);
		}	
	} while (FALSE);

	if (!bResult)
	{
		// ϵͳ�ʼ�ʧ�ܶ�Ҫ��LOG
		QLogPrintf(LOG_ERR, "[mail] %s", "SendCondMail Failed!");

		//CHAR szItemInfo[1024];
		//CHAR szInfoData[1024];

		//if (pMsg->nItemCount > 0)
		//{
		//	LPSTR pszItem = szItemInfo;
		//	*pszItem++ = '{';

		//	for (INT i = 0; i < pMsg->nItemCount; ++i)
		//	{
		//		pszItem += sprintf(pszItem, pszItemInfo, pItemData->dwClassID, pItemData->wStackCount, 
		//			pItemData->byTimeoutType, pItemData->dwTimeout, pItemData->dwBuyPrice);
		//	}

		//	*pszItem++ = '}';
		//}
		//else
		//{
		//	sprintf(szItemInfo, "%s", "No Item");
		//}

		//sprintf(szInfoData, pszFormat, bResult ? "OK" : "Fail", szItemInfo);
		//QLogPrintf(LOG_ERR, "[mail] %s", szInfoData);
	}

	return TRUE;
}

BOOL KGC_MailProtocalHandler::Process_CheckReceiver(LPBYTE pData, UINT uSize, INT nConnectId)
{
	static CHAR szFailReason[2 * 1024];
	memset(szFailReason, 0, sizeof(szFailReason));
	static DWORD adwReceiverId[KD_MAIL_MAX_RECEIVER_COUNT];
	memset(adwReceiverId, 0, sizeof(DWORD) * KD_MAIL_MAX_RECEIVER_COUNT);
	
	QCONFIRM_RET_FALSE(pData && nConnectId > 0);
	if (uSize <= sizeof(KMAIL_S2G_PROTO_CHECKRECEIVER))
	{
		QLogPrintf(LOG_ERR, "[mail] %s", "KMAIL_S2G_PROTO_CHECKRECEIVER size error!");
		return FALSE;
	}

	BOOL bReceiverOk = TRUE;
	LPSTR pszFailReason = szFailReason;
	KMAIL_S2G_PROTO_CHECKRECEIVER *pMsg = (KMAIL_S2G_PROTO_CHECKRECEIVER*)pData;
	INT nReceiverCount = (INT)pMsg->wReceiverCount;
	if (nReceiverCount > KD_MAIL_MAX_RECEIVER_COUNT)
		nReceiverCount = KD_MAIL_MAX_RECEIVER_COUNT;			// �ռ��˸�������

	LPSTR pReceiver = (LPSTR)(pMsg + 1);
	CHAR szReceiverName[_NAME_LEN];
	for (INT i = 0; i < nReceiverCount; ++i)
	{
		QStrCpyLen(szReceiverName, pReceiver, _NAME_LEN);
		szReceiverName[_NAME_LEN - 1] = 0;
		
		// �ж��Ƿ���ڸ����ֵ����
		KRole* pPlayer = m_pIKOnlinePlayerMgr->GetPlayerByName(szReceiverName);
		if (!pPlayer)
		{
			bReceiverOk = FALSE;
			pszFailReason += sprintf(pszFailReason, "���'%s'������ ", szReceiverName);
		}
		else
		{
			if (pMsg->nType == emKMAIL_TYPE_PLAYER)
			{
				// �ж������Ƿ���
				INT nCount = KMailPlayerManager::Instance()->GetPlayerMailCount(pPlayer->GetId());
				if (nCount >= KD_MAIL_MAX_COMMON_COUNT)
				{
					bReceiverOk = FALSE;
					pszFailReason += sprintf(pszFailReason, "���'%s'��������,����ʼ�����%d�� ", szReceiverName, KD_MAIL_MAX_COMMON_COUNT);
				}
				else
				{
					adwReceiverId[i] = pPlayer->GetId();
				}
			}
			else
			{
				adwReceiverId[i] = pPlayer->GetId();
			}
		}
	}

	// ���ͼ����
	KMAIL_G2S_PROTO_CHECKRECEIVER *pHead = (KMAIL_G2S_PROTO_CHECKRECEIVER*)m_szBuffer;
	*pHead = KMAIL_G2S_PROTO_CHECKRECEIVER();
	pHead->dwPlayerId = pMsg->dwPlayerId;
	pHead->nMailIndex = pMsg->nMailIndex;
	if (bReceiverOk)
	{
		pHead->nResult = 1;
		pHead->nFailReasonLen = 0;
		pHead->wReceiverCount = nReceiverCount;
		DWORD* pIds = (DWORD*)(pHead + 1);
		memcpy(pIds, adwReceiverId, nReceiverCount * sizeof(DWORD));

		return m_pIKGcServer->Send(nConnectId, pHead, sizeof(KMAIL_G2S_PROTO_CHECKRECEIVER) + pHead->wReceiverCount * sizeof(DWORD));
	}
	else
	{
		pHead->nResult = 0;
		pHead->nFailReasonLen = QStrLen(szFailReason);

		CHAR* pszReason = (CHAR*)(pHead + 1);
		QStrCpy(pszReason, szFailReason);

		QLogPrintf(LOG_DEBUG, "[mail] Process_CheckReceiver %s", szFailReason);
		return m_pIKGcServer->Send(nConnectId, pHead, sizeof(KMAIL_G2S_PROTO_CHECKRECEIVER) + pHead->nFailReasonLen);
	}
}

BOOL KGC_MailProtocalHandler::InitMailInfo(CONST KMAIL_S2G_PROTO_SENDMAIL* pMsg, KMAIL_INFO* pInfo)
{
	QCONFIRM_RET_FALSE(pMsg && pInfo);
	
	KMAIL sMail;
	sMail.nCaptionLen	= pMsg->wCaptionLen;
	sMail.nContentLen	= pMsg->wContentLen;
	sMail.nItemCount	= pMsg->nItemCount;
	sMail.nIconId		= pMsg->nIconId;
	sMail.pCaption		= (LPSTR)(pMsg + 1) + pMsg->wReceiverCount * sizeof(DWORD);
	sMail.pContent		= sMail.pCaption + pMsg->wCaptionLen;
	sMail.pItemData		= pMsg->nItemCount == 0 ? NULL : (KItemData_Common*)&sMail.pContent[pMsg->wContentLen];
	KMAIL_DBINFO* pDBInfo = InitMailData(&sMail);
	if (!pDBInfo)
		return FALSE;

	pInfo->nMailSize = pDBInfo->wSize;
	pInfo->pMailData = (CHAR*)pDBInfo;

	// ��������
	if (pMsg->byCondLen > 0)
	{
		LPSTR pCond = (LPSTR)(sMail.pItemData + pMsg->nItemCount);
		memcpy(pInfo->szCond, pCond, pMsg->byCondLen);
		pInfo->nCondLen = (INT)pMsg->byCondLen;
	}

	return TRUE;
}

KMAIL_DBINFO* KGC_MailProtocalHandler::InitMailData(CONST KMAIL* pMail)
{
	QCONFIRM_RET_NULL(pMail && pMail->nCaptionLen > 0 && pMail->nContentLen > 0 && pMail->nIconId > 0);
	QCONFIRM_RET_NULL((pMail->nItemCount > 0 && pMail->pItemData != NULL) || pMail->nItemCount == 0);
	
	INT nBufLen = sizeof(KMAIL_DBINFO) + pMail->nCaptionLen + pMail->nContentLen;
	if (pMail->nItemCount > 0)
	{
		nBufLen += sizeof(KMAIL_DBINFO_ATTACHMENT) + pMail->nItemCount * sizeof(KItemData_Common);
	}
	QCONFIRM_RET_NULL(nBufLen <= sizeof(m_szBuffer));

	KMAIL_DBINFO *pDBInfo = (KMAIL_DBINFO*)m_szBuffer;
	pDBInfo->wVersion = 1;
	pDBInfo->wSize = nBufLen;
	pDBInfo->nIconId = pMail->nIconId;
	// ����
	pDBInfo->wCaptionOffset = sizeof(KMAIL_DBINFO);
	CHAR *pDstCaption = &m_szBuffer[pDBInfo->wCaptionOffset];
	QStrCpyLen(pDstCaption, pMail->pCaption, pMail->nCaptionLen);
	// ����
	pDBInfo->wContentOffset = pDBInfo->wCaptionOffset + pMail->nCaptionLen;
	CHAR *pDstContent = pDstCaption + pMail->nCaptionLen;
	QStrCpyLen(pDstContent, pMail->pContent, pMail->nContentLen);
	// ����
	pDBInfo->wAttachOffet = pDBInfo->wContentOffset + pMail->nContentLen;
	if (pMail->nItemCount > 0)
	{
		KMAIL_DBINFO_ATTACHMENT *pAttach = (KMAIL_DBINFO_ATTACHMENT*)(pDstContent + pMail->nContentLen);
		pAttach->wCount = pMail->nItemCount;
		for (INT i = 0; i < pMail->nItemCount; ++i)
		{
			pAttach->aryItems[i] = pMail->pItemData[i];
		}
	}
	return pDBInfo;
}

BOOL KGC_MailProtocalHandler::SendMail(CONST KMAIL_S2G_PROTO_SENDMAIL *pMsg, KMAIL_INFO *pMail)
{
	QCONFIRM_RET_FALSE(pMsg && pMail);

	// �ʼ�ʧ�ܶ�Ҫ��LOG
	static LPCTSTR pszItemInfo = "{ClassId:%d,StackCount:%d,TimeOutType:%d,TimeOut:%d,BuyPrice:%d},";
	static LPCTSTR pszFormat = "[%s] SendSysMail PlayerName: %s, ItemInfo: %s, MailType: %d";

	BOOL bSendResult = FALSE;	
	DWORD* pdwReceiverId = (DWORD*)(pMsg + 1);
	for (INT i = 0; i < pMsg->wReceiverCount; ++i, pdwReceiverId++)
	{
		if (*pdwReceiverId <= 0)
		{
			QLogPrintf(LOG_ERR, "[mail] %s", "SendMail ReceiverId <= 0!");
			continue;
		}

		KRole* pReceiver = m_pIKOnlinePlayerMgr->GetPlayerById(*pdwReceiverId);
		if (!pReceiver)
		{
			QLogPrintf(LOG_ERR, "[mail] SendMail ReceiverId:%d Receiver not Exist!", *pdwReceiverId);
			continue;
		}

		pMail->nMailID = 0;
		pMail->nStat   = emKMAIL_STAT_UNREAD;
		if (pMsg->nType == emKMAIL_TYPE_PLAYER)
		{
			// ��������ʼ�
			bSendResult = SendPlayerMail(pMsg->dwPlayerId, pReceiver, pMail);
		}
		else if (pMsg->nType == emKMAIL_TYPE_SYSTEM)
		{
			// ����ϵͳ�ʼ�
			bSendResult = SendSystemMail(pReceiver, pMail);
		}
		else if (pMsg->nType == emKMAIL_TYPE_DELIVERY)
		{
			// ���ͼ���
			bSendResult = SendDeliveryMail(pMsg->dwPlayerId, pReceiver, pMail);
		}
		else
		{
			QLogPrintf(LOG_ERR, "[mail] SendMail Invalid mail type:%d!", pMsg->nType);
			continue;
		}

		if (!bSendResult)
		{
			// �ʼ�ʧ�ܶ�Ҫ��LOG
			QLogPrintf(LOG_ERR, "[mail] %s", "SendMail Failed!");

			//KMAIL_DBINFO* pDbInfo = (KMAIL_DBINFO*)pMail->pMailData;
			//if (pDbInfo)
			//{
			//	CHAR szItemInfo[1024];
			//	CHAR szInfoData[1024];
			//	INT nItemCount = (pDbInfo->wSize - pDbInfo->wAttachOffet) / sizeof(KItemData_Common);

			//	if (nItemCount > 0)
			//	{
			//		LPTSTR pData = (LPTSTR)pDbInfo;
			//		KItemData_Common* pItem = (KItemData_Common*)(&(pData[pDbInfo->wAttachOffet]));
			//		LPSTR pszItem = szItemInfo;
			//		*pszItem++ = '{';

			//		for (INT i=0; i<nItemCount; ++i)
			//		{
			//			pszItem += sprintf(pszItem, pszItemInfo, pItem->dwClassID, pItem->wStackCount, 
			//				pItem->byTimeoutType, pItem->dwTimeout, pItem->dwBuyPrice);
			//		}

			//		*pszItem++ = '}';
			//	}
			//	else
			//	{
			//		sprintf(szItemInfo, "%s", "No Item");
			//	}

			//	sprintf(szInfoData, pszFormat, bSendResult ? "OK" : "Fail", pReceiver->GetPlayerName(), szItemInfo, pMsg->nType);
			//	QLogPrintf(LOG_ERR, "[mail] %s", szInfoData);
			//}
		}
	}
	return TRUE;
}

BOOL KGC_MailProtocalHandler::SendPlayerMail(DWORD dwSenderId, KRole* pReceiver, KMAIL_INFO* pMail)
{
	QCONFIRM_RET_FALSE(pReceiver && pMail);

	KRole* pSender = m_pIKOnlinePlayerMgr->GetPlayerById(dwSenderId);
	if (!pSender)
	{
		QLogPrintf(LOG_ERR, "[mail] SendPlayerMail Failed! Can't find sendplayerId:%d player!", dwSenderId);
		return FALSE;
	}

	pMail->dwSenderId = dwSenderId;
	strncpy(pMail->szSender, pSender->GetPlayerName(), sizeof(pMail->szSender) - 1);
	pMail->dwReceiverId = pReceiver->GetId();

	KMailCountNotifier *pNotifier = m_poolNotifiers.New();
	if (!pNotifier || !pNotifier->Init(pMail))
	{
		m_poolNotifiers.Free(pNotifier);
		return FALSE;
	}

	return KMailDatabase::Instance()->QueryMailCount(pReceiver->GetId(), this, pNotifier);
}

BOOL KGC_MailProtocalHandler::SendSystemMail(KRole* pReceiver, KMAIL_INFO* pMail)
{
	QCONFIRM_RET_FALSE(pReceiver && pMail);

	pMail->dwSenderId = 0;
	pMail->szSender[0] = '\0';
	pMail->dwReceiverId = pReceiver->GetId();
	
	KMailCountNotifier *pNotifier = m_poolNotifiers.New();
	if (!pNotifier || !pNotifier->Init(pMail))
	{
		m_poolNotifiers.Free(pNotifier);
		return FALSE;
	}

	return KMailDatabase::Instance()->QueryMailCount(pReceiver->GetId(), this, pNotifier);
}

BOOL KGC_MailProtocalHandler::SendDeliveryMail(DWORD dwSenderId, KRole* pReceiver, KMAIL_INFO* pMail)
{
	QCONFIRM_RET_FALSE(pReceiver && pMail);

	if (dwSenderId == 0)
	{
		// ϵͳ���͵�
		pMail->dwSenderId = 0;
		pMail->szSender[0] = '\0';
	}
	else
	{
		// ��ҷ��͵�
		KRole* pSender = m_pIKOnlinePlayerMgr->GetPlayerById(dwSenderId);
		if (!pSender)
		{
			QLogPrintf(LOG_ERR, "[mail] SendPlayerMail Failed! Can't find sendplayerId:%d player!", dwSenderId);
			return FALSE;
		}

		pMail->dwSenderId = dwSenderId;
		strncpy(pMail->szSender, pSender->GetPlayerName(), sizeof(pMail->szSender) - 1);
	}

	// ���������Ϊ�Ѷ�
	pMail->nStat = emKMAIL_STAT_READED;
	pMail->dwReceiverId = pReceiver->GetId();

	KMailCountNotifier *pNotifier = m_poolNotifiers.New();
	if (!pNotifier || !pNotifier->Init(pMail))
	{
		m_poolNotifiers.Free(pNotifier);
		return FALSE;
	}

	return KMailDatabase::Instance()->QueryMailCount(pReceiver->GetId(), this, pNotifier);
}

BOOL KGC_MailProtocalHandler::NotifyMailCount(DWORD dwOwnerId, INT64 nMailCount, LPVOID pParam)
{
	QCONFIRM_RET_FALSE(pParam && nMailCount >= 0);
	
	KMailCountNotifier *pNotifier = (KMailCountNotifier*)pParam;
	pNotifier->NotifyMailCount(nMailCount);
	m_poolNotifiers.Free(pNotifier);
	return TRUE;
}

// -------------------------------------------------------------------------

