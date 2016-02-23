/* -------------------------------------------------------------------------
//	�ļ���		��	buftriggereffect.h
//	������		��	zhangzhixiong
//	����ʱ��	��	2012-5-7 
//	��������	��	
//
// -----------------------------------------------------------------------*/
#ifndef __BUF_TRIGGER_EFFECT_H__
#define __BUF_TRIGGER_EFFECT_H__

#include "bufcommand.h"
#include "onlinegameworld/kcharacter.h"
#include "onlinegamebase/ksysservice.h"
#include <cstdarg>

class ITabFile;

class BufTriggerEffect
{
public:
	BufTriggerEffect();

	~BufTriggerEffect();

	// ���ݱ���ļ���ʼ����������
	BOOL Init(ITabFile* tabFile, INT nRow);

	INT GetID() {return m_nID;}

	INT GetProbPercent() {return m_nProbPercent;}

	CONST string& GetEvent() {return m_szEvent;}

	//�Ƿ���CD
	BOOL BeHaveCD() CONST { return m_nIntervalTime; }

	BufMagicEffectCommand& GetMagicEffect() {return m_cEffect;}

	BufConditionCommand& GetCondition() {return m_cCondition;}

private:
	INT			m_nID;
	INT			m_nProbPercent;					// �����ĸ���
	INT         m_nIntervalTime;				// ������ʱ��

	string		m_szEvent;				// �������¼�,���ַ�����¼�����¼��������ű����лص�
	BufConditionCommand m_cCondition;   // ���ǳ�����״̬����ͨ���¼��������������ж��Ƿ���Դ���
	BufMagicEffectCommand m_cEffect;    // �¼�Ч��

friend struct TriggerData;
};

struct TriggerData
{
	TriggerData(BufTriggerEffect* _psEffect = 0)
		: m_bTriggered(FALSE), m_nCDTime(0), psEffect(_psEffect) { }
	BOOL		m_bTriggered;					// �Ƿ񴥷���
	INT			m_nCDTime;						// ʣ��CDʱ��
	BufTriggerEffect* psEffect;

	//����CDʱ��
	VOID UpdateCDTime() { (0 < m_nCDTime) ? --m_nCDTime : 0 ; }

	//����CDʱ��
	INT GetCDTime() { return m_nCDTime; }

	//����CDʱ��
	VOID ResetCDTime() { psEffect ? m_nCDTime = psEffect->m_nIntervalTime: 0; }

	//�Ƿ񴥷���
	BOOL BeTriggered() { return m_bTriggered; }

	//�����ѱ�������
	VOID SetTriggered() { m_bTriggered = true; }
};

#endif