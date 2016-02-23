/* -------------------------------------------------------------------------
//	�ļ���		��	buftimereffect.h
//	������		��	zhangzhixiong
//	����ʱ��	��	2012-5-7 
//	��������	��	
//
// -----------------------------------------------------------------------*/
#ifndef __BUF_TIMER_EFFECT_H__
#define __BUF_TIMER_EFFECT_H__

#include "bufcommand.h"

class ITabFile;

class BufTimerEffect
{
public:
	BufTimerEffect();

	~BufTimerEffect();

	// ���ݱ���ļ���ʼ����������
	BOOL Init(ITabFile* tabFile, INT nRow);

	INT GetID() {return m_nID;}

	TimerEffectLaunchType GetLanuchType() const {return m_eLaunchType;}

	INT	GetInterval() const {return m_nInterval;}

	BufConditionCommand& GetCondition() {return m_cCondition;}

	BufMagicEffectCommand& GetUpperEffect() {return m_cUpperBoundEffect;}

	BufMagicEffectCommand& GetLowerEffect() {return m_cLowerBoundEffect;}

protected:
    INT m_nID;
	INT m_nInterval;
	TimerEffectLaunchType m_eLaunchType;
	BufConditionCommand   m_cCondition;
	BufMagicEffectCommand m_cUpperBoundEffect;
	BufMagicEffectCommand m_cLowerBoundEffect;
};

#endif