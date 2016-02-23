//---------------------------------------------------------------------------
// ������Ե�����2 GameMasterCentral ������ͨ
// ��Ȩ����:       2006-2007 ��ɽ���(Kingsoft)
// ��������������: 2006 Խ��(wooy)
//---------------------------------------------------------------------------
// GameMasterCentral����Ϸ����ĸ���Master����֮���Э��ӿ�
//---------------------------------------------------------------------------
#ifndef __LOG_SERVER_PROTOCOL_H__
#define __LOG_SERVER_PROTOCOL_H__

#pragma	pack(push, 1)

enum LOG_SERVER_PROTOCOL_LIST
{
	LOG_SERVER_P_LOGIN	= 32,
	LOG_SERVER_P_PING,
	LOG_SERVER_P_QUERY_LOG,
};

struct LOG_SERVER_S_LOGIN
{
	unsigned char	cProtocol;	// = LOG_SERVER_P_LOGIN
	char			szGameSpaceName[32];
	char			Reserved[32];
};

//LogServer�յ�Ping��Ϣ�����ԭ������
struct LOG_SERVER_S_PING
{
	unsigned char	cProtocol;	// = LOG_SERVER_P_PING
	unsigned int	uTime;		// = �¼���
};

struct LOG_SERVER_S_QUERY_LOG
{
	unsigned char	cProtocol;		// = LOG_SERVER_P_QUERY_LOG
	char			szLogSort[32];	// ��־����
	char			szLogObject[64];// ��־��ص�Ŀ�������
	unsigned int	uParamLen;		// �����szParam�ĳ���(����β��)
	char			szParam[1];		// szParam�����һ���ֽڿռ�Ϊ�ַ�����β����'\0'
	
};

#pragma	pack(pop)

#endif// #ifndef __LOG_SERVER_PROTOCOL_H__
