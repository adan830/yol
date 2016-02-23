
#pragma once

#define KD_SERVER_OVERLOAD_CFG	"Overload"

#ifdef GAME_SERVER
	#define	KD_DEFAULT_MAX_PLAYER	500 // Ĭ��player����
	#define	KD_DEFAULT_MAX_NPC		1000 // Ĭ��npc����
	#define KD_DEFAULT_MAX_DOODAD	600 // Ĭ��doodad����

	#define KD_DEFAULT_MAX_WAIT_PLAYER 1000 // Ĭ�ϵȴ����ӵ��������
	#define KD_DEFAULT_VIP_RESERVATION 50 // VIP����Ԥ���ɵ�¼����
	#define KD_DEFAULT_START_SEVER_TIME "2014-08-01 12:00:00"
#else
// �ͻ���Ĭ��ֵ
	#define	KD_DEFAULT_MAX_PLAYER	400
	#define	KD_DEFAULT_MAX_NPC		500
	#define KD_DEFAULT_MAX_DOODAD	300
#endif // GAME_SERVER

// �������ò���
struct KENV_CONFIG
{
	INT nMaxPlayer; // ��󵥷������
	INT nMaxNpc; // ��󵥷�����Npc��
	INT nMaxDoodad; // ��󵥷�����Doodad��
	INT nMaxItem; // �ܵ�������
	DWORD dwStartSeverTime;//����������ʱ��

#ifdef GAME_SERVER
	INT nMaxWaitPlayer; // �ȴ����ӵ��������
	INT nMaxVipPlayer; // vip�������
	INT nCharacterArrayValueMaxIndexDw; // ��ɫ���ֽڳ��ñ���������
	INT nCharacterArrayValueMaxIndexW; // ��ɫ���ֽڳ��ñ���������
	INT nCharacterArrayValueMaxIndexBy; // ��ɫһ�ֽڳ��ñ���������
#endif // GAME_SERVER
};
class IKModuleInterface;
// -------------------------------------------------------------------------

class IKNsBaseRequire
{
public:
	// ��ȡ�������ò���
	virtual const KENV_CONFIG* GetEnvConfig() PURE;
	// ��ȡģ���б���NULL��β
	virtual IKModuleInterface** GetModuleList() PURE;
};

extern IKNsBaseRequire* g_piNsBaseRequire;
// -------------------------------------------------------------------------

