
#pragma once

#include "ProtocolBasic.h"
//#include "KHometownList.h"
//#include "KMailDef.h"

struct QGameCenterSettings
{
	QGameCenterSettings();

    BOOL Load();

    // Global
    char    m_szLocale[64];

    // Gateway
    char    m_szGatewayIP[_NAME_LEN];
	int     m_nGatewayPort;
    time_t  m_nGatewayPingCycle;

    // Game server
	int	    m_nGameServerPort;
	int     m_nConnectionTimeout;
    int     m_nMemoryLimitForCreateMap; // �ڴ�ռ��С�ڸ�ֵʱ����������ͼ,��λ: M
    float   m_fAveragePerformanceLimitForCreateMap;
    float   m_fImmediatePerformanceLimitForCreateMap;
    float   m_fAveragePerformanceLimitForNewPlayer;
    float   m_fImmediatePerformanceLimitForNewPlayer;

    // Database
	char    m_szDBIP[_NAME_LEN];
	int     m_nDBPort;
	char    m_szDBAcc[_NAME_LEN];
	char    m_szDBPsw[_NAME_LEN];
	char    m_szDBName[_NAME_LEN];

    // Mail System
    int  m_nMailSurvivalTime;
    int  m_nMaxPlayerMailCount;
    int  m_nMaxAuctionMailCount;
    int  m_nMaxSystemMailCount;
    int  m_nMaxGmMsgMailCount;
    int  m_nMaxPlayerMsgMailCount;
    char m_szMailSendFailedName[_NAME_LEN];
    char m_szMailWithdrawName[_NAME_LEN];
    char m_szMailUserReturnTitle[_NAME_LEN];
    char m_szSystemMailSender[_NAME_LEN];

    // Fellowship System
    int  m_nFellowshipSaveInterval;

    // Auction
    char m_szAuctionName[_NAME_LEN];
    char m_szGold[_NAME_LEN];
    char m_szSilver[_NAME_LEN];
    char m_szCopper[_NAME_LEN];
    char m_szSellSucceed[_NAME_LEN];
    char m_szBuyyer[_NAME_LEN];
    char m_szPrice[_NAME_LEN];
    char m_szCustodyCharges[_NAME_LEN];
    char m_szTaxMoney[_NAME_LEN];
    char m_szGetMoney[_NAME_LEN];
    char m_szCancelSucceed[_NAME_LEN];
    char m_szBidFailed[_NAME_LEN];
    char m_szBuySucceed[_NAME_LEN];
    char m_szBuyItNowPrice[_NAME_LEN];
    char m_szTopPrice[_NAME_LEN];
    char m_szSeller[_NAME_LEN];
    char m_szCoin[_NAME_LEN];
    int  m_nAuctionTaxRate;
    int  m_nGameCardTaxRate;

    // Role
    int  m_nMaxRoleNameLength;
    int  m_nMinRoleNameLength;
    int  m_nMaxRoleCount;
    int  m_nDeleteProtectLevel; // ��������ȼ��Ľ���ɾ���ӳٶ���
    int  m_nDeleteDelayTime;    // ɾ���ӳ�ʱ��

    // Tong
    char m_szTongReturnMoneyMailTitle[_NAME_LEN];

    // Apex Proxy
    char m_szApexServerIP[_NAME_LEN];
    int  m_nApexServerPort;
    int  m_nApexPingCycle;
    int  m_nMaxKickCount;

    // LogServer
    char m_szLogServerIP[_NAME_LEN];
    int  m_nLogServerPort;
    int  m_nLogServerPingCycle;
    char m_szLogServerIdentity[_NAME_LEN];

    // AntiFarmer
    BOOL m_bAntiFarmerEnable;

	// BattleZone
	INT m_nGlobalServerMode;
	INT m_nGlobalServerPort;
	CHAR m_szGlobalServerAddr[16];	// MasterCR IP Address
	INT m_nGlobalServerPingInterval;

	//pay agency
	INT m_nPayAgencyPort;
	CHAR m_szPayAgencyIP[_NAME_LEN];	// MasterCR IP Address

private:
    BOOL LoadRelaySettings();
    BOOL LoadCenterConst();

public:
};

