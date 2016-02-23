#ifndef __GAMEWORLD_COREUSENAMEDEF_H__
#define __GAMEWORLD_COREUSENAMEDEF_H__

#define		MAX_PLAYER_IN_ACCOUNT			3


enum enumMSG_ID
{
	enumMSG_ID_NONE = 0,
	enumMSG_ID_TEAM_KICK_One,
	enumMSG_ID_TEAM_DISMISS,
	enumMSG_ID_TEAM_LEAVE,
	enumMSG_ID_TEAM_REFUSE_INVITE,
	enumMSG_ID_TEAM_REFUSE_APPLYJOIN,
	enumMSG_ID_TEAM_REFUSE_DISABLETEAM,
	enumMSG_ID_TEAM_REFUSE_SUMMON,
	enumMSG_ID_TEAM_CANNOT_ADDHIM,
	enumMSG_ID_TEAM_SELF_ADD,
	enumMSG_ID_TEAM_CHANGE_CAPTAIN_FAIL,
	enumMSG_ID_TEAM_CHANGE_CAPTAIN_FAIL2,
	enumMSG_ID_OBJ_CANNOT_PICKUP,
	enumMSG_ID_OBJ_TOO_FAR,
	enumMSG_ID_DEC_MONEY,
	enumMSG_ID_GET_ITEM,
	enumMSG_ID_TEAMATE_GET_ITEM,
	enumMSG_ID_MONEY_CANNOT_PICKUP,
	enumMSG_ID_CANNOT_ADD_TEAM,
	enumMSG_ID_TARGET_CANNOT_ADD_TEAM,
	enumMSG_ID_PK_REFUSE_EXERCISE,
	enumMSG_ID_PK_ACCETP_EXERCISE,
	enumMSG_ID_PK_READY_EXERCISE,
	enumMSG_ID_PK_EXERCISE_WIN,
	enumMSG_ID_PK_EXERCISE_LOSE,
	enumMSG_ID_PK_ERROR_1,
	enumMSG_ID_PK_ERROR_2,
	enumMSG_ID_PK_ERROR_3,
	enumMSG_ID_PK_ERROR_4,
	enumMSG_ID_PK_ERROR_5,
	enumMSG_ID_PK_ERROR_6,
	enumMSG_ID_PK_ERROR_7,
	enumMSG_ID_PK_ERROR_8,
	enumMSG_ID_PK_ERROR_9,
	enumMSG_ID_PK_ERROR_10,
	enumMSG_ID_PK_ERROR_11,
	enumMSG_ID_PK_ERROR_12,
	enumMSG_ID_PK_ERROR_13,
	enumMSG_ID_PK_ERROR_14,
	enumMSG_ID_PK_ERROR_15,
	enumMSG_ID_PK_ERROR_16,
	enumMSG_ID_PK_ERROR_17,
	enumMSG_ID_PK_ERROR_18,
	enumMSG_ID_PK_ERROR_19,
	enumMSG_ID_PK_ERROR_20,
	enumMSG_ID_PK_ERROR_21,
	enumMSG_ID_PK_ERROR_22,
	enumMSG_ID_PK_ERROR_23,
	enumMSG_ID_PK_ERROR_24,
	enumMSG_ID_DEATH_LOSE_ITEM,
	enumMSG_ID_TONG_REFUSE_ADD,
	enumMSG_ID_TONG_BE_KICK,
	enumMSG_ID_TONG_LEAVE_SUCCESS,
	enumMSG_ID_TONG_LEAVE_FAIL,
	enumMSG_ID_TONG_CHANGE_AS_MASTER,
	enumMSG_ID_TONG_CHANGE_AS_MEMBER,
	enumMSG_ID_TONG_DISMISS,
	enumMSG_ID_TEAM_ERROR01,
	enumMSG_ID_TEAM_ERROR02,
	enumMSG_ID_TEAM_ERROR03,
	enumMSG_ID_TEAM_ERROR04,
	enumMSG_ID_TEAM_ERROR05,
	enumMSG_ID_TONG_MONEY,
	enumMSG_ID_ITEM_USINGTIMES_END,
	enumMSG_ID_CANNOT_PK_WHEN_USEEXTBOX,		// ����װ������֮�����PKֵ����3���޷��ٽ���PK,�Է�ֹװ���������ͷ�ʱ��ʧ
	enumMSG_ID_CANNOT_MOVEORTRADE_ITEM,			// ��ֹ���ߵ��ƶ��뽻��
	enumMSG_ID_PARTNER_DEATH_NOT_CALLOUT,		// ͬ�������ͷ��в��ܱ��ٻ�
	enumMSG_ID_PARTNER_INTERVAL_NOT_CALLOUT,	// ͬ���ٻ����δ�����ܱ��ٻ�
	enumMSG_ID_PARTNER_FORBID_CALLOUT,			// ͬ���ֹ�ٻ�״̬
	enumMSG_ID_PARTNER_FORBID_REMOVE,			// ��ֹ��ɢͬ��(��������)
	enumMSG_ID_PARTNER_FORBID_REMOVE2,			// ��ֹ��ɢͬ��(���һ��)
	enumMSG_ID_BANTIME_CANNOT_ACCESS,			// ��ʱ��ֹ����
	enumMSG_ID_PASSWORD_FAILED_TIMES,			// �����������
	enumMSG_ID_LIFESKILL_FORBIDSTATE,
	enumMSG_ID_PEER_FORBITPLAYERTRADE,			// �Է����ڲ��ܽ��뽻��״̬
	enumMSG_ID_TRADE_SELF_ACCOUNT_LOCK	,		// �Լ��˺��������ܽ���
	enumMSG_ID_TRADE_TARGET_ACCOUNT_LOCK,		// �Է��˺��������ܽ���
	enumMSG_ID_TRADE_COSUMEINFO,				// �ڽ��н���ʱ���ĵķǰ������Ʒ������֪ͨ
	enumMSG_ID_NUM,
	
};

//---------------------------- ���ָ����� ------------------------------
enum CURSOR_INDEX
{
	CURSOR_NORMAL = 0,
	CURSOR_POINT_TO_ATTACKABLE,	//�Ƶ�����Ŀ����
	CURSOR_POINT_TO_OBJ_NPC,	//�Ƶ�һ��OBJ��NPC��
	CURSOR_PICKABLE,			//��ʰȡ
	CURSOR_SKILL_ENABLE,		//�Ƶ���ʹ�����漼�ܵĽ�ɫ��������
	CURSOR_BUY,					//����
	CURSOR_SELL,				//������
	CURSOR_REPAIR,				//�޶���
	CURSOR_USE,                 //�������ͼ��
	CURSOR_QUERY_STALL,			//��̯λ
	CURSOR_STALL_MARK_PIRCE,	//Ϊ��̯���
	CURSOR_HAND,				//��
	CURSOR_FORGET,				//ͬ����������
	CURSOR_HELP,				//������ѯͼ�꣨������֧��Ϊ����ϲ����ϣ�
	CURSOR_BIND,				//����Ʒ
	CURSOR_UNBIND,				//�����
	CURSOR_INDEX_COUNT,
};
#endif
