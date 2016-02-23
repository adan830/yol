
#pragma once

#include "Misc/randomgen.h"
// -------------------------------------------------------------------------
// ʱ��������ڿ�����Ϸʱ�䣬��Ϸʱ����Զ�̬�趨�������ܲ���ϵͳʱ�����
class KDateTimeControl
{
public:
	KDateTimeControl();
	BOOL Init();
	// ��ȡ�����������ں�������49.7��������ֻ�Ǽ����ʱ���ڣ�24.5���ڣ���ֵʱ�������
	UINT GetGameElapse();
	// ��ȡ��������������ʵ�������������
	INT64 GetRealGameElapse();
	// ��ȡ��Ϸ��time()ֵ
	time_t GetGameTime(time_t* pTime);
	// ��ȡ������ϵͳʱ��time()ֵ
	time_t GetSysTime(time_t* );
	// ÿִ֡��
	BOOL Loop();
	// ������Ϸʱ��
	BOOL SetGameTime(const time_t& tTime);
	// ��ȡ�������32λ��
	DWORD Rand();
protected:
	UINT m_uStartElapse;
	UINT m_uCurElapse;
	UINT m_uCurElapseHigh;

	time_t m_tTimeAdjust; // ʱ��У׼�����ⲿʱ��Դ�Ĳ�ֵ��
	time_t m_tCurGameTime;
	QRandGentor m_cRandGentor;
private:
};

