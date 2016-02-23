#ifndef _KMAIL_DEF_H_
#define _KMAIL_DEF_H_

#include "ProtocolBasic.h"
#include <stdint.h>

#define MAILSYS_VERSION      5

#define KMAIL_MAX_ITEM_COUNT 5
#define MAIL_TITLE_LEN       16
#define MAX_MAIL_TEXT_LEN    256
#define MAX_COND_DATA_LEN	 32		// �ʼ�����������󳤶�
#define MAX_COND_NUM		 5		// �ʼ�����������

enum KMAIL_TYPE
{
    eMailType_Player = 0,//����ʼ�
    eMailType_System,    //ϵͳ�ʼ�
    eMailType_Auction,   //�����ʼ�
    eMailType_GmMessage, //gm�ʼ�
    eMailType_PlayerMessage,//����ʼ���Ϣ
    eMailType_Total
};

enum KMAIL_RESULT_CODE
{
    mrcSucceed,
    mrcFailed,

    mrcSystemBusy,
    mrcDstNotExist,
    mrcNotEnoughMoney,
    mrcItemAmountLimit,
    mrcNotEnoughRoom,
    mrcMoneyLimit,
    mrcMailNotFound,
    mrcMailBoxFull,
    mrcReturnMailFailed,
    mrcItemBeBind,
    mrcTimeLimitItem,
    mrcItemNotInPackage,
    mrcDstNotSelf,
    mrcDeleteRefused,
    mrcSelfMailBoxFull,
    mrcTooFarAway,

    mrcTotal
};

#pragma pack(1)
struct KMailItemDesc 
{  
    bool   bAcquired;   // true ��ʾ�Ѿ��ַ�������� 
    BYTE   byDataLen;
    int    nPrice;      // ��������ĵ��߼۸�
};

struct KMail
{
    DWORD           dwMailID;
    BYTE            byType;
    bool            bRead;
    DWORD           dwSenderID;
    char            szSenderName[_NAME_LEN];
    char            szTitle[MAIL_TITLE_LEN];
    uint32_t          nSendTime;
    uint32_t          nRecvTime;
    uint32_t          nLockTime;
    int             nMoney; //Ǯ
	int             nSilver;//����
	int             nEnergy;//����
	BYTE			byCondNum;
	BYTE			byCond[MAX_COND_DATA_LEN];
    WORD            wTextLen;
    KMailItemDesc   ItemDesc[KMAIL_MAX_ITEM_COUNT];
    BYTE            byData[0];
};

struct KMailContent
{
    int             nMoney;
	int             nSilver;//add 
	int             nEnergy;//add
    WORD            wTextLen;
    KMailItemDesc   ItemDesc[KMAIL_MAX_ITEM_COUNT];
    BYTE            byData[0];
};

struct KMailListInfo
{
    BYTE        byType;
    DWORD       dwMailID;
    char        szSender[_NAME_LEN];
    char        szTitle[MAIL_TITLE_LEN];
    uint32_t    nSendTime;
    uint32_t    nRecvTime;
    bool        bReadFlag;
    bool        bMoneyFlag;
    bool        bItemFlag;
};


enum MAIL_CHECK_TYPE
{
	emMailCheckSex = 0,
	emMailCheckLevel,
	emMailCheckTypeTotal,
};

enum MAIL_CONDITION_OP
{
	emMailCondOpGreater,		// >
	emMailCondOpGreaterEqual,	// >=
	emMailCondOpLess,			// <
	emMailCondOpLessEqual,		// <=
	emMailCondOpEqual,			// ==
	emMailCondOpNotEqual,		// !=
	emMailCondOpIgnore,			// ...
};

struct MAIL_CONDITION_HEAD
{
};

struct MAIL_CONDITION_SEX : MAIL_CONDITION_HEAD
{
	BYTE byCondOp;
	BYTE bySex;
};

struct MAIL_CONDITION_LEVEL : MAIL_CONDITION_HEAD
{
	BYTE byLevel1Op;
	BYTE byLevel1;
	BYTE byLevel2Op;
	BYTE byLevel2;
};

#pragma pack()

#endif //_KMAIL_DEF_H_
