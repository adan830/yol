#pragma once

#include "ProtocolBasic.h"
#include "onlinegameworld/kprotocol.h"

#pragma pack(push, 1)

enum
{
	c2s_send_mail_request = 0,
	c2s_get_maillist_request,        //����ʼ��б�
	c2s_query_mail_content,          //��ѯ�ʼ�����
	c2s_acquire_mail_money_request,  //�����ʼ���Ǯ
	c2s_acquire_mail_item_request,   //�����ʼ���Ʒ
	c2s_set_mail_read,               //�����ʼ��Ѷ�
	c2s_delete_mail,                 //ɾ���ʼ�
	c2s_return_mail,
	c2s_mail_end,
};

enum
{
	s2c_send_mail_respond = 0,
	s2c_get_mail_list_respond,
	s2c_new_mail_notify,
	s2c_sync_mail_content,
	s2c_mail_general_respond,
	s2c_mail_end,
};

// c2s
// ==========================================================================

struct C2S_SEND_MAIL_REQUEST : KLENPTC_HEADER<c2s_send_mail_request>
{
	DWORD       dwNpcID;
	BYTE        byRequestID;
	char        szDstName[_NAME_LEN];
	char        szTitle[_NAME_LEN];
	int         nMoney;
	BYTE        byBox[KMAIL_MAX_ITEM_COUNT];        // �ʼ���Ʒ���ڵİ���
	BYTE        byX[KMAIL_MAX_ITEM_COUNT];          // �ʼ���Ʒ���ڰ������λ��
	int         nItemPrice[KMAIL_MAX_ITEM_COUNT];   // ��������ļ۸�
	WORD        wTextLen;     
	char        szText[0];                          // �ż��ı�����
};

struct C2S_GET_MAILLIST_REQUEST : KPTC_HEADER<c2s_get_maillist_request>
{
	DWORD dwStartID;
};

struct C2S_QUERY_MAIL_CONTENT : KPTC_HEADER<c2s_query_mail_content>
{
	DWORD   dwNpcID;
	DWORD   dwMailID;
	BYTE    byMailType;
};

struct C2S_ACQUIRE_MAIL_MONEY_REQUEST : KPTC_HEADER<c2s_acquire_mail_money_request>
{
	DWORD       dwMailID;
};

struct C2S_ACQUIRE_MAIL_ITEM_REQUEST : KPTC_HEADER<c2s_acquire_mail_item_request>
{
	DWORD       dwMailID;
	BYTE        byIndex;
};

struct C2S_SET_MAIL_READ : KPTC_HEADER<c2s_set_mail_read>
{
	DWORD   dwMailID;
};

struct C2S_DELETE_MAIL : KPTC_HEADER<c2s_delete_mail>
{
	DWORD   dwMailID;
};

struct C2S_RETURN_MAIL : KPTC_HEADER<c2s_return_mail>
{
	DWORD   dwMailID;
};

// s2c
// ============================================================================

struct S2C_SEND_MAIL_RESPOND : KPTC_HEADER<s2c_send_mail_respond>
{
	BYTE            byRespondID;
	BYTE            byResult;
};

struct S2C_GET_MAIL_LIST_RESPOND : KLENPTC_HEADER<s2c_get_mail_list_respond>
{
	BYTE            byMailCount;
	KMailListInfo   MailListInfo[0];
};

struct S2C_NEW_MAIL_NOTIFY : KPTC_HEADER<s2c_new_mail_notify>
{
	KMailListInfo   NewMailListInfo;
};

struct S2C_SYNC_MAIL_CONTENT : KLENPTC_HEADER<s2c_sync_mail_content>
{
	DWORD           dwMailID;
	BYTE            byResult;   // Success, mail not found, data not ready.
	BYTE            byData[0];
};

struct S2C_MAIL_GENERAL_RESPOND : KPTC_HEADER<s2c_mail_general_respond>
{
	DWORD           dwMailID;
	BYTE            byResult;   // Success, mail not found, data not ready.
};

#pragma pack(pop)