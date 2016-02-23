
#pragma once

// �޸Ĵ�ö����Ҫ����Э��汾��kprotocol.h
// ��ģ��ʵ��IKModuleInterface* GetModuleInterFace<>()�ӿڣ�����kmodulelist.cpp�м���ģ���б�
// -------------------------------------------------------------------------
enum KE_MODULE_ID
{
	emKMODULE_NONE			= 0,
	emKMODULE_RPG			= 1,	// ��������ģ�飬����Timer�Ȼ�������

	emMODULE_TEAM			= 3,
	emKMODULE_ITEM			= 4,

	//emKMODULE_FACTION,			//ְҵϵͳ
	emKMODULE_TASK			= 6,	//����ϵͳ
	emKMODULE_PURSE			= 7,	//Ǯ��
	emKMODULE_CHAT_NEW		= 8,	// ����
	emKMODULE_GLOBALDATA	= 9,	// ȫ�ֱ���
	emKMODULE_MAP			= 10,
	emKMODULE_AI			= 11,	//AI
	emKMODULE_MAIL			= 12,	//�ʼ�
	emKMODULE_FINDPATH		= 13,   //Ѱ·
	emMODULE_BUFFER_		= 14,   // ����Buffer
	emMODULE_FIGHT_SKILL	= 15,   // ����ս������
	emMODULE_FACTION		= 16,   // ��������ϵͳ
	emMODULE_SHOP			= 17,   // �̵�
	emMODULE_MYSTERYSHOP	= 18,   // �����̵�////////////////////////////�ǵ�ȥ��
	emMODULE_KIN			= 19,	// ����
	emMODULE_RELATION		= 20,   // ���ѹ�ϵ
	emMODULE_PET			= 21,	// ����
	emMODULE_AUTOMATIC		= 22,	// �Զ�����ֻռλ
	emMODULE_ESCORT			= 23,	// ����
	emMODULE_AUCTION		= 24,	// ������
	emMODULE_AWARD			= 25,	// ����

	emMODULE_QUIZ			= 26,   // �ʴ���
	
	emMODULE_ARENA			= 28,  	// PVE������

	emMODULE_TOWER			= 29,	// ��ħ��
	emMODULE_STAGE			= 30,	// �ؿ�

	emMODULE_TITLE			= 31,	//�ƺ�
	
	emMODULE_INSTANCE		= 32,	// ����
	
	emMODULE_MEDITATION		= 33,	//����

	emMODULE_REMIND			= 34,	//����

	emMODULE_RANK			= 35,	// ���а�

	emMODULE_TARGET			= 36,	//Ŀ��

	emMODULE_ACTIVITY		= 37,	// �

	emMODULE_VIP			= 38,	//vip

	emMODULE_AWARD_LOBBY	= 39,	//��������

	emMODULE_BLADE			= 40,	// ����

	emMODULE_GEM			= 41,	//��ʯ

	emMODULE_ARTIFACT		= 42,	//����

	emMODULE_BANK			= 43,	//Ǯׯ

	emMODULE_Opense         = 44,	//�����
	
	// ���Ϊ127, ��չģ��
	emKGAMEEXT_RESERVED		 = 126,	//GameExtension����
	emKMAX_ID = 127,
};

class IKModuleInterface;
extern IKModuleInterface** g_GetModuleList();

