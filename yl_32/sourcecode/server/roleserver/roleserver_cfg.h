/* -------------------------------------------------------------------------
//	�ļ���		��	rolesvc_cfg.h
//	������		��	simon
//	����ʱ��	��	2010/5/19 15:15:03
//	��������	��	
//
// -----------------------------------------------------------------------*/
#ifndef __ROLESVC_CFG_H__
#define __ROLESVC_CFG_H__

// -------------------------------------------------------------------------

const static INT ROLESVC_DEFAULT_MAX_ROLE_LIST_SIZE = 524000; // Ĭ��ÿ�˻��Ľ�ɫ�б��ֶ�֮��С��512KB
const static INT ROLESVC_DEFAULT_MAX_ACCOUNTS_PER_DB = 1000000; // Ĭ��ÿ���ݿ������˻���

const static INT ROLESVC_CFG_STRING_MAX_LEN = 256;
const static INT ROLESVC_CFG_DEFAULT_DB_PORT = 3306;

const static CHAR ROLESVC_CFG_FILE_NAME[] = "roleserver_cfg.ini";

const static CHAR ROLESVC_CFG_SECTION_NETWORK[] = "Network";
const static CHAR ROLESVC_CFG_SECTION_LIMIT[] = "Limit";
const static CHAR ROLESVC_CFG_SECTION_NAMESERVER[] = "NameServer";
const static CHAR ROLESVC_CFG_SECTION_DB_CLUSTER[] = "DatabaseCluster";
const static CHAR ROLESVC_CFG_SECTION_DB_NODE[] = "DatabaseNode";

struct KROLESVC_DB_PARAM 
{
	CHAR szServer[ROLESVC_CFG_STRING_MAX_LEN];
	INT nPort;
	CHAR szUserName[ROLESVC_CFG_STRING_MAX_LEN];
	CHAR szPassword[ROLESVC_CFG_STRING_MAX_LEN];
	CHAR szDatabase[ROLESVC_CFG_STRING_MAX_LEN];
	INT nThread;
};

struct KROLESVC_NETWORK_PARAM
{
	INT  nSendRecvTimeout;    // ����
	INT  nPingTimeOut; // ping��ʱ

	INT nInAdapterIdx;
	INT nOutAdapterIdx;
	CHAR szIntranetIp[ROLESVC_CFG_STRING_MAX_LEN]; // ����Ip
	CHAR szInternetIp[ROLESVC_CFG_STRING_MAX_LEN]; // ����Ip
	INT nListenPort;
};

struct KROLESVC_PARAM
{
	KROLESVC_NETWORK_PARAM sNetwork;
	INT  nMaxRolePerAccount; // ÿ�˻���ɫ������
	INT nMaxRoleListBuffer; // ÿ�˻�����ɫ�б�������С
	INT nMaxAccountPerDB; // ÿ���ݿ����ɵ��˻�����

	KROLESVC_DB_PARAM sNameServerParam;

	INT nDatabaseNodeCount; // ��ɫ���ݿ�ڵ���
	CHAR szDbClusterUser[ROLESVC_CFG_STRING_MAX_LEN];
	CHAR szDbClusterPassword[ROLESVC_CFG_STRING_MAX_LEN];
	KROLESVC_DB_PARAM* pDbNodeParams; // ����ʱ��̬����
};

extern KROLESVC_PARAM g_sRoleSvcCfg;

BOOL g_RoleSvcReadCfg(KROLESVC_PARAM& rcParam);
BOOL g_RoleSvcReadClusterCfg(KROLESVC_PARAM& rcParam);

INT g_GetLocalTimeString(CHAR szTime[], SIZE_T uBufferSize);
// -------------------------------------------------------------------------

#endif /* __ROLESVC_CFG_H__ */
