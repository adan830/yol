#ifndef _KRANKDEF_H_
#define _KRANKDEF_H_

enum KE_RANK_ID
{
	emRANK_ID_BEGIN = 0,

	emRANK_ARENA = 1,	// ������
	emRANK_ROLE_FIGHTSCORE = 2, //�������� -> ս������
	emRANK_PET_LEVEL = 3,	//��������  -> ���ɵȼ���
	emRANK_PET_FIGHTSCORE = 4,	// �������� -> ����ս����
	emRANK_RIDE_FIGHTSCORE = 5, // �������� -> ����ս����
	emRANK_MPJJ,	// ���ɾ��� �������� -> ս����˫��
	emRANK_LG,		// ����   �������� -> ����������
	emRANK_SMZC,	// ��ħս��  �������� -> ��ħ���ְ�

	// �����Ǽ�������
	emRANK_TONG_FIGHTSCORE,
	emRANK_TONG_SALARY,

	//����
	emRANK_ROLE_LEVEL_OPEN_SERVER = 11,//��ҵȼ�  ��������а�  -> ȫ��弶
	emRANK_RIDE_LV,     //����ȼ�   ��������а�  -> ����֮��
	emRANK_AREAN_OS,//������   ��������а�  -> ��������
	emRANK_PET_LV_OS,     //����ȼ�   ��������а�  -> ��������
	emRANK_LG_OS,//����   ��������а�  -> �޵а���
	emRANK_TOWER,     //��ħ��   ��������а�  -> ն����ħ
	emRANK_ROLE_FIGSHTSCORE_OS,//ս����   ��������а�  -> ս����˫
	emRANK_ID_END,
};

enum KE_RANK_MAX_COUNT
{
	emRANK_ARENA_MAX_COUNT = 500,

	emRANK_MAX_COUNT = 100,		// �������а��������

};

#define emRANK_MAX_COUNT_OPEN_SERVICE 10//�������а����������
#define RANK_POOL_MAX_COUNT 500

#endif	// _KRANKDEF_H_