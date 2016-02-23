
#pragma once

// -------------------------------------------------------------------------


class KTimerMgr
{
public:
	KTimerMgr(void);
	~KTimerMgr(void);

	BOOL Breath();
	BOOL Init();
	BOOL UnInit();
	UINT AddScriptTimePoint(UINT uFrame);
	DWORD	GetCurTime() { return m_dwCurrentTime; }
public:
	typedef std::set<UINT> KScriptTimerSet;		// �ű�ע��ʱ�����Ϣ

private:
	KScriptTimerSet m_setScriptTimer;			// �ű�ע��ʱ���
	UINT			m_uNextScriptTime;			// �´δ����ű�ʱ��
	DWORD			m_dwCurrentTime;

};

extern KTimerMgr g_cTimerMgr;
