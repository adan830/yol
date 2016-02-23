/* -------------------------------------------------------------------------
//	�ļ���		��	bufferdef.h
//	������		��	zhangzhixiong
//	����ʱ��	��	2012-5-7 
//	��������	��	
//
// -----------------------------------------------------------------------*/
#ifndef __BUFFER_DEF_H__
#define __BUFFER_DEF_H__

// ���ܴ���λ��
enum BUFFER_POSITION
{
	BUFFER_POSITION_SELF,    // ����
	BUFFER_POSITION_TARGET // Ŀ���Ŀ���
};

#define BUFFER_TABLE_FILE                 "\\setting\\buffer_\\buffer.txt"
#define BUFFER_TIMER_EFFECT_TABLE_FILE    "\\setting\\buffer_\\e_timer.txt"
#define BUFFER_TRIGGER_EFFECT_TABLE_FILE  "\\setting\\buffer_\\e_trigger.txt"
#define BUFFER_NUMBER_TABLE_FILE		  "\\setting\\buffer_\\buff_numbers.txt"

#define BUFFER_POOL_MAX_COUNT	50000	//��ǰ�������������buff����

#define GROUND_BUFFER_POOL_MAX_COUNT	10000	//��ǰ���������ĵ���buff����

#define SCRIPT_MAX_LENGTH 1024	//ִ�нű�����󳤶�

#define BUFF_TIMER_EFFECT_COUNT 5	//ʱ��Ч��������

#define BUFF_TRIGGER_EFFECT_COUNT 5	//����Ч��������

enum TimerEffectLaunchType	//ʱ�䴥������
{
	UpperLaunch = 1,//���ش���
	LowerLaunch,	//���ش���
	BothLaunch,		//�����ض�����
	IntervalLaunch, //�������
};

enum BufferGroupType //buff����group,���������壬ȷ����ֵ�����ٽ����޸�
{
	NormalBuffer,
	SpecialBuffer
};

enum BufferStackMode	//buff�ĵ���ģʽ
{
	emOverWrite,		//��ͬStackCategory���ߵȼ�ֱ�Ӹ��ǵ͵ȼ��ģ����Ӳ������䣬ʱ�����
	emUpdateInterval,	//��ԭ��buff���棬�����Buff
	emForbidStack,		//���ɵ���
	emStackInterval,	//�滻ԭ��buff��ʱ����ӣ����Ӳ���+1
	emNoneStackBuff,	//û�е��ӹ�ϵ
};

enum BufferStackDetail
{
	emUpdate = 1,
	emReplace = 2,
	emForbid = 3,
	emStackTime = 4
};

enum BufferType // buff����
{
	emNoneEffectBuff,
	emNormalDeBuff,		// �����к�buff
	emHurtOnceDebuff,	// һ�����˺�
	emBleedDebuff,		// ��Ѫ
	emControlDebuff,	// ����
	emNiceBuff,			// ����
};

#define IS_DEBUFF(nBuffType) ((nBuffType) != emNiceBuff)

#endif
