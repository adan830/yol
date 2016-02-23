#ifndef KTASKFUNCS_H
#define KTASKFUNCS_H

#include <string>
#include <list>
#include <map>
#include <set>


#define TASKVALUE_ARREST_TIME 2046	// ��ץ����Դ���ε�ʱ��
#define TASKVALUE_JAIL_TERM   2047	// ����Դ���δ����


class KPlayer;

enum KE_TIMERID
{
	KE_TIMERID_PROGRESS =  100000,
	KE_TIMERID_TASKTAG	=  100002,
	KE_TIMERID_GENERAL	=  100003,
};

#ifdef GAME_SERVER
// ����ʱ���ṹ
struct TTaskTimer
{
	UINT	nTimerId;	// ��ʱ��ID
	struct
	{
		INT nTime : 24;			// ʹ�ô���
		INT nMode : 4;			// ģʽ��0��������ߺ�ʧЧ��1��������ߺ���Ȼ���ڣ���ʱ����ʵʱ��Ϊ׼��2��������ߺ���Ȼ���ڣ���ʱ���������ʱ��Ϊ׼
		INT nSuspending : 4;	// �Ƿ���ͣ���� 
	}		cOption;
	INT		nInterval;	// ��ʱ�����ʱ�䣬1/18��Ϊ��λ������
	INT		nLastTime;	// �ϴμ�ʱʱ��
	INT		nLastQuit;	// �ϴ��˳�ʱ��
	DWORD	dwEvent;
	LPVOID	pData;
	DWORD	dwParam;
	INT		nParam;
};

// ����ʱ��
class KTaskTimer
{
public:
	enum Mode
	{
		MODE_LOSTTIME,		// ������ߺ�ʧЧ
		MODE_REALTIME,		// ������ߺ���Ȼ���ڣ���ʱ����ʵʱ��Ϊ׼
		MODE_GAMETIME,		// ������ߺ���Ȼ���ڣ���ʱ���������ʱ��Ϊ׼
		//MODE_NOMOVE,		// ����ڹ����в��ܹ��ƶ�
		//MODE_NOATTACKED,	// ����ڹ����в��ܱ���
		//MODE_NOMOVE_NOATTACKED, //�����ƶ�Ҳ���ܱ���
		MODE_COUNT
	};

	enum KE_CLOSE
	{
		KE_CLOSE_TIMEREND,
		KE_CLOSE_EVENT,
		KE_CLOSE_FORCE,

	};

	enum
	{
		VALUE_COUNT = 5 
	};

public:

	KTaskTimer();

	BOOL IsFree() {return m_cTimer.nTimerId == 0;}
	VOID Start(CONST TTaskTimer* pTimer);
	VOID Close(KPlayer* pOwner, KE_CLOSE emuCloseType);
	// ����TRUE��ʾ��ʱ���������ڣ�����FALSE��ʾ��ʱ����Ҫ�ر�
	BOOL Activate(KPlayer* pOwner, INT nCurrent);
	BOOL Load(CONST INT nTaskValues[VALUE_COUNT], INT nCurrent);
	VOID Save(INT nTaskValues[VALUE_COUNT], INT nCurrent);
	INT GetRestTime(INT nCurrent);
	INT GetRestCount();
	INT GetId() {return m_cTimer.nTimerId;}
	BOOL Suspend();
	BOOL Resume();
	BOOL IsSuspending();

private:

	BOOL Load(TTaskTimer* pTimer, INT nCurrent);
	VOID Save(TTaskTimer* pTimer, INT nCurrent);
	static VOID AdjustTime(INT nLostTime, INT nCurrent, TTaskTimer *pTimer);
	VOID OnTime(KPlayer* pOwner);
	TTaskTimer m_cTimer;
};

// ����ʱ������
class KTaskTimerList
{

public:

	enum
	{
		TIMER_COUNT = 10,
		TAKSVAL_IDX = 1611,						// ʹ�õ��������1611-1660
		VALUE_COUNT = KTaskTimer::VALUE_COUNT,	// ÿ����ʱ��ʹ�õ������������Ŀ
	};
	/*
	2.����ܣ��ƶ���ʹ�ü��ܣ�������������ʹ�õ��ߣ�����װ���������ʼ������ף��л�ս��״̬���˳���Ϸ
	3.�����ӳ٣��ƶ���ʹ�ü��ܣ�������������ʹ�õ��ߣ��ƶ���Ʒ���еĵ��ߣ�������Ʒ������װ���������ʼ������ף��л�ս��״̬
	*/
	// �����¼������ڶ���������ʱ������
	enum
	{
		EVENT_MOVE,					// �ƶ�
		EVENT_ATTACK,				// ��������(ʹ�ò��ּ���)
		EVENT_SITE,					// ����
		EVENT_RIDE,					// ������
		EVENT_USEITEM,				// ʹ�õ���
		EVENT_ARRANGEITEM,			// �ƶ���Ʒ���еĵ���
		EVENT_DROPITEM,				// ������Ʒ
		EVENT_CHANGEEQUIP,			// ����װ��
		EVENT_SENDMAIL,				// ���͵����ʼ�
		EVENT_TRADE,				// ����
		EVENT_CHANGEFIGHTSTATE,		// �ı�ս��״̬
		EVENT_ATTACKED,				// ������
		EVENT_DEATH,				// ����
		EVENT_LOGOUT,				// ����
		EVENT_REVIVE,				// �������
		EVENT_CLIENTCOMMAND,		// �ͻ������ǿ�ƴ��
		EVENT_BUYITEM,				// ��Npc������		
		EVENT_SELLITEM,				// ��Npc��������
	
		EVENT_TASK_TAG,				// ����Ŀ����
		EVENT_GENERAL_PROCESS,		// ͨ�ý�����
		EVENT_COUNT,
	};

private:

	typedef std::list<INT>		KTimerList;
	typedef std::set<INT>		KTimerSet;
	typedef std::map<INT, INT>	KTimerMap;

	struct TEvent
	{
		BYTE bEvent[TIMER_COUNT];
		INT	nCount;
	};

public:

	KTaskTimerList()
	{
		memset(&m_cEvent, 0, sizeof(m_cEvent));

		for (INT i = 0; i < TIMER_COUNT; i++)
		{
			m_setFreeTimers.insert(i);
		}
	}

	static VOID LoadTimer(CONST INT nTaskValues[VALUE_COUNT], TTaskTimer* pTimer);
	static VOID SaveTimer(INT nTaskValues[VALUE_COUNT], CONST TTaskTimer* pTimer);

	VOID Load(KPlayer* pOwner, INT nCurrent);
	VOID Save(KPlayer* pOwner, INT nCurrent);
	VOID Activate(KPlayer* pOwner, INT nCurrent, DWORD dwEvent);
	BOOL StartTimer(INT nTimerId, INT nInterval, INT nTime, INT nMode, DWORD dwParam = 0, INT nParam = 0,  LPVOID pData = NULL, DWORD dwEvent = 0);
	VOID CloseTimer(KPlayer* pOwner, INT nTimerId, KTaskTimer::KE_CLOSE eCloseType = KTaskTimer::KE_CLOSE_FORCE);
	INT  GetRestTime(INT nTimerId, INT nCurrent);
	INT	 GetRestCount(INT nTimerId);
	INT  GetTimerCount();
	BOOL SuspendTimer(INT nTimerId);		// ��ʱ��ֹ��ʱ��
	BOOL ResumeTimer(INT nTimerId);			// �ָ���ʱ��
	BOOL IsTimerSuspending(INT nTimerId);	// ��ʱ���Ƿ���ͣ
	BOOL HasTimer(INT nTimerId);

private:

	KTaskTimer		m_cTaskTimers[TIMER_COUNT];
	TEvent			m_cEvent[EVENT_COUNT];
	KTimerSet		m_setFreeTimers;	// ���ж�ʱ������
	KTimerMap		m_mapUsingTimers;	// ����ʹ�õĶ�ʱ������

	VOID GetTimerList(KTimerList& listTimers);
	INT  CreateTimer(CONST TTaskTimer* pTimer);
	BOOL RegisterTimerEvent(CONST TTaskTimer* pTimer, INT nIndex);

};

#endif //GAME_SERVER

#endif
