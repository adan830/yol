#ifndef _GODDESS_PROTOCOL_H_
#define _GODDESS_PROTOCOL_H_

#include "../ProtocolBasic.h"

enum GODDESS_C2S_PROTOCOL_ID    // Goddess client ==> server
{
    GODDESS_C2S_PROTOCOL_BEGIN = PROTOCOL_BIG_PACKAGE_BEGIN,
    GDC2S_SAVE_ROLE_DATA,         // �洢��ɫ����, ref : TProcessData
    GDC2S_SET_STATISTIC_INFO,     // ����ͳ����Ϣ, ref : TProcessData

    GDC2S_PING = PROTOCOL_NORMAL_PACKAGE_BEGIN + 1, // ping, ref : PING_COMMAND
    GDC2S_QUERY_ROLE_LIST,        // ��ȡ��ɫ�б�, ref : TProcessData
    GDC2S_QUERY_ROLE_DATA,        // ��ȡ��ɫ����, ref : TProcessData
    GDC2S_CREATE_ROLE,            // ������ɫ, ref : TProcessData
    GDC2S_DELETE_ROLE,            // ɾ����ɫ, ref : TProcessData

    GDC2S_LOCK_OR_UNLOCK_ROLE,    // ��ɫ���ݼ�/��������, ref : LOCK_OR_UNLOCK_ROLE
    GDC2S_PLAYER_ENTER_GAME,      // ��ɫ������Ϸ, ref : TProcessData
    GDC2S_PLAYER_LEAVE_GAME,      // ��ɫ�뿪��Ϸ�����ǽ�����Ϸʧ��, ref : TProcessData
    GDC2S_SHUTDOWN_GODDESS,       // �����عر�Goddess, ref : TProcessData
    GDC2S_QUERY_STATISTIC_INFO,   // ��ȡͳ����Ϣ, ref : TProcessData
    GDC2S_TRANSFER_ROLE,          // ��ɫ����ת��, ref : ???
    GDC2S_QUERY_ROLE_LIST_ITEM,   // ��ȡ������ɫ�б���Ϣ, ref : TProcessData

    GDC2S_LOCK_OR_UNLOCK_ROLE_EXT,// ��ɫ���ݼ�/��������, �ò����з��ذ� ref : LOCK_OR_UNLOCK_ROLE_EXT
    GDC2S_CREATE_TONGNAME,        // �����������ref : CREATE_TONG_NAME
    GDC2S_QUERY_ROLE_LIST_IN_ZONE // ��ȡһ��������һ���˺ŵ����н�ɫ���������ڷ�������ref : TProcessData
};

enum GODDESS_S2C_PROTOCOL_ID     // Goddess server ==> client
{
    GODDESS_S2C_PROTOCOL_BEGIN = PROTOCOL_BIG_PACKAGE_BEGIN,
    GDS2C_RETURN_ROLE_DATA,       // ���ؽ�ɫ����, ref : TProcessData + role data
    GDS2C_CREATE_ROLE_RESULT,     // ������ɫ���ݵĲ������, ref : TProcessData,pDataBuf[0]ȡֵ�μ�enum CREATE_ROLE_RESULT
    GDS2C_RETURN_ROLE_LIST_ITEM,  // ���ص�����ɫ�б���Ϣ, ref : TProcessData

    GDS2C_PING = PROTOCOL_NORMAL_PACKAGE_BEGIN + 1, // ping back, ref : PING_COMMAND    

    GDS2C_RETURN_ROLE_LIST,       // ���ؽ�ɫ�б�, ref : TProcessData + role list data
    GDS2C_SAVE_ROLE_DATA_RESULT,  // �洢��ɫ���ݷ��ؽ��, ref : TProcessData
    GDS2C_DELETE_ROLE_RESULT,     // ɾ����ɫ���ݷ��ؽ��, ref : TProcessData
    GDS2C_SHUTDOWN_CMD_RESPOND,   // �����¼�Э��: �ر��������Ӧ���, ref : TProcessData
    GDS2C_RETURN_STATISTIC_INFO,  // ����ͳ����Ϣ, ref : TProcessData

    GDS2C_RETURN_LOCK_OR_UNLOCK_ROLE_EXT, // ���ؽ�ɫ���ݼ�/�����Ĳ������, ref : TProcessData,  
                                          // TProcessData.pDataBuffer[0]:0 failed, TProcessData.pDataBuffer[0]:1 success

    GDS2C_CREATE_TONGNAME_RESULT, // ���ش���������Ľ��, ref : TProcessData
                                  // TProcessData.pDataBuffer[0]:0 failed, TProcessData.pDataBuffer[0]:1 success

    GDS2C_SET_STATISTIC_INFO_RESULT,   // ����ͳ����Ϣ���ؽ��, ref : TProcessData,
                                       // TProcessData.pDataBuffer[0]:0 failed, TProcessData.pDataBuffer[0]:1 success
    GDS2C_RETURN_ROLE_LIST_IN_ZONE     // ����һ��������һ���˺ŵ����н�ɫ���������ڷ�������ref : TProcessData,ROLE_IN_ZONE
                                       // TProcessData.pDataBuffer[0]  : 0 failed, 1 success
                                       // &TProcessData.pDataBuffer[1] : (unsigned)uRoleCount + ROLE_IN_ZONE[uRoleCount]
};

#pragma    pack(push, 1)
enum CREATE_ROLE_RESULT
{
    CREATE_ROLE_SUCCESS = 1,
    CREATE_ROLE_UNKNOW_FAILED  = -1,
    CREATE_ROLE_NAME_FILTER    = -2,
    CREATE_ROLE_NAME_EXIST     = -3,
    CREATE_ROLE_OVER_MAX_ROLE_PER_GATEWAY = -4,
    CREATE_ROLE_OVER_MAX_ROLE_PER_ZONE    = -5
};

struct LOCK_OR_UNLOCK_ROLE : tagProtocolHeader
{
    bool bLock;
    char szRoleName[_NAME_LEN];
};

struct LOCK_OR_UNLOCK_ROLE_EXT : tagProtocolHeader2
{
    bool bLock;
    char szRoleName[_NAME_LEN];
};

struct CREATE_TONG_NAME : tagProtocolHeader2
{
    char szTongName[_NAME_LEN];
};

struct ROLE_IN_ZONE
{
    char szRoleName[_NAME_LEN];
    char szGatewayName[_NAME_LEN];
};

#pragma pack(pop)

#endif


