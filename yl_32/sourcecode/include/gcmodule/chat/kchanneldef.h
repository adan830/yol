
#pragma once

// -------------------------------------------------------------------------

// Ƶ�������� 
#define KD_CHANNEL_NAME_MAX_LEN	32

// ��Ϣ����󳤶ȣ�ֻ�������ƿͻ��˷�������Ϣ��
#define KD_CHANNEL_MSG_MAX_LEN	1024

#define KD_CHANNEL_PACKET_MAX_LEN 64000

// Ƶ�������ļ�
#define KD_CHANNEL_CONFIG_FILE	"\\setting\\chat\\channelcfg_new.ini"
#define KD_CHANNEL_SETTING_FILE "\\setting\\chat\\channel.ini"

// ϵͳ��Ϣ����
enum KE_SYSTEMMSG_TYPE
{
	emKSYSTEMMSG_NORMAL,        // ��ͨ��������Ϣ��
	emKSYSTEMMSG_IMPORTANT,     // ��Ҫ��������ʾ
	emKSYSTEMMSG_NOTICE,        // ���棬���������ʾ
	emKSYSTEMMSG_NUM,
};

// ��Ϣ��ʾ����
enum QE_MSG_SHOWN_TYPE
{
    emQCHAT_PANEL,              // ���������ʾ 
	emQNOTICE_BOARD,            // ��������ʾ
	emBLACK_STRIPE              // ������ʾ
};

class IKChatChannelProcessor;

#ifdef GAME_CENTER
	class IKInterfaceConnector;
#endif

// Ƶ����Ϣ
struct KChannelInfo
{
	INT						nChannelId;
	BOOL					nOffLineMsg;
	IKChatChannelProcessor*	pProcessor;
#ifdef GAME_CENTER
	IKInterfaceConnector*	pInterface;	// ����GC����ģ��������ģ�鷢����Ϣ
#endif
};

typedef std::map<INT, KChannelInfo> KT_CHANNEL_INFO;
// -------------------------------------------------------------------------


