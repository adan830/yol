/* -------------------------------------------------------------------------
//	�ļ���		��	kmailctrl.h
//	������		��	xiewenzhe
//	����ʱ��	��	2011/5/24 9:25:08
//	��������	��	
//
// -----------------------------------------------------------------------*/
#ifndef __KMAILCTRL_H__
#define __KMAILCTRL_H__

// -------------------------------------------------------------------------
#include "onlinegameworld/kcharacterctrlbase.h"
#include "onlinegamemodule/mail/kluaplayermail.h"
#include "config/kcharacterdef.h"

class KMailCtrl : public KCharacterCtrlBase
{
private:
	struct KSendTime
	{
		INT nYear;
		INT nMonth;
		INT nDay;

		BOOL IsSame(KSendTime& sSendTime)
		{
			if (nYear != sSendTime.nYear ||
				nMonth != sSendTime.nMonth ||
				nDay != sSendTime.nDay)
			{
				return FALSE;
			}

			return TRUE;
		}
	};

	// ��¼���췢���ʼ�����
	struct KMailSaveData
	{
		KSendTime sSendTime;	// ����ʱ�䣨�����գ�
		INT nSendCount;			// ���ʹ���
	};

public:
	enum {emKCtrlId = emKCHARACTER_CTRL_PLAYER_MAIL};
	KMailCtrl(KCharacter& rcPlayer);

public:
	virtual BOOL Init();
	virtual BOOL UnInit();
	virtual BOOL OnLogin();
	virtual BOOL OnLogout();

#ifdef GAME_SERVER
	BOOL OnDbLoad(LPCBYTE pData, SIZE_T uSize);
	BOOL OnDbSave(LPBYTE pBuffer, SIZE_T uBuffSize, SIZE_T& uUsedSize);
	BOOL OnClientReady();
#endif

	CONST KLuaPlayerMail& GetScriptInterface() CONST;

public:
	VOID SetMailBoxLoaded(BOOL bLoaded);
	BOOL IsMailBoxLoaded();

	VOID AddMailSendTime();
	BOOL CanSendMail(INT nSendLimit);

	DWORD GetPlayerId();

private:
	KLuaPlayerMail m_cLunaObj;
	BOOL m_bMailBoxLoaded;
	KMailSaveData m_sSaveData;
};

// -------------------------------------------------------------------------

#endif /* __KMAILCTRL_H__ */
