
#pragma once

#include <map>
#include <vector>

#define OBJ_EVENT_ANY 0xffffffff

struct KOBJEVENT
{
	KOBJEVENT(UINT nEvent, INT nParam1 = 0, INT nParam2 = 0, INT nParam3 = 0)
		:nEvent(nEvent)
	{
		anEventParam[0] = nParam1;
		anEventParam[1] = nParam2;
		anEventParam[2] = nParam3;
	}

	UINT nEvent;
	INT anEventParam[3];
};


class KObjEventWatch;

typedef std::map<KObjEventWatch*, BOOL> WATCHSET;		// <�۲��߶���, �Ƿ���Ч>
typedef std::map<INT, WATCHSET> EVENTWATCHMAP;			// <�¼�����, �۲����б�>

// �¼��ķ����ߣ���Ҫ�ɷ��¼���Class����Ӵ�����
class KEventCreator
{
	friend class KObjEventWatch;
	
public:
	static BOOL AddWatcher(UINT nEvent, KObjEventWatch* pWatch);
	static BOOL RemoveWatcher(UINT nEvent, KObjEventWatch* pWatch);

public:
	KEventCreator();
	virtual ~KEventCreator();

	virtual BOOL Init();
	BOOL Release();

public:
	template<typename T1, typename T2, typename T3>
	BOOL FireEvent(UINT nEvent, T1 Param1, T2 nParam2, T3 nParam3);

private:
	BOOL FireEvent(CONST KOBJEVENT& rcEvent);

protected:
	virtual BOOL DispatchEvent(LPCSTR szFormat, ...);

private:
	// ���һ����nEvent����Ȥ��pWatch
	BOOL __AddWatcher(UINT nEvent, KObjEventWatch* pWatch);

	// ɾ��һ����nEvent����Ȥ��pWatch
	BOOL __RemoveWatcher(UINT nEvent, KObjEventWatch* pWatch);

	// ɾ��һ��Watch
	BOOL __RemoveWatch(KObjEventWatch* pWatch);

	// ���һ��Watch�Դ�KEventCreator����Ȥ��Event��Ŀ
	INT __GetCareEventCount(KObjEventWatch* pWatch);

private:
	static EVENTWATCHMAP m_sEventWatchMap;	// ȫ���¼��۲��ߣ������¼���������˭
	static BOOL  m_sbProcessEvent;
private:
	EVENTWATCHMAP m_mapObjEventWatch;		// �۲���Map
	BOOL m_bProcessEvent;					// �Ƿ����ڷ����¼�
};


template<>
inline BOOL KEventCreator::FireEvent(UINT nEvent, INT nParam1, INT nParam2, INT nParam3)
{
	FireEvent(KOBJEVENT(nEvent, nParam1, nParam2, nParam3));
	DispatchEvent("uddd", nEvent, nParam1, nParam2, nParam3);
	return TRUE;
}

template<>
inline BOOL KEventCreator::FireEvent(UINT nEvent, INT nParam1, INT nParam2, DWORD nParam3)
{
	FireEvent(KOBJEVENT(nEvent, nParam1, nParam2, nParam3));
	DispatchEvent("uddu", nEvent, nParam1, nParam2, nParam3);
	return TRUE;
}

template<>
inline BOOL KEventCreator::FireEvent(UINT nEvent, INT nParam1, DWORD nParam2, INT nParam3)
{
	FireEvent(KOBJEVENT(nEvent, nParam1, nParam2, nParam3));
	DispatchEvent("udud", nEvent, nParam1, nParam2, nParam3);
	return TRUE;
}

template<>
inline BOOL KEventCreator::FireEvent(UINT nEvent, INT nParam1, DWORD nParam2, DWORD nParam3)
{
	FireEvent(KOBJEVENT(nEvent, nParam1, nParam2, nParam3));
	DispatchEvent("uduu", nEvent, nParam1, nParam2, nParam3);
	return TRUE;
}

template<>
inline BOOL KEventCreator::FireEvent(UINT nEvent, DWORD nParam1, INT nParam2, INT nParam3)
{
	FireEvent(KOBJEVENT(nEvent, nParam1, nParam2, nParam3));
	DispatchEvent("uudd", nEvent, nParam1, nParam2, nParam3);
	return TRUE;
}

template<>
inline BOOL KEventCreator::FireEvent(UINT nEvent, DWORD nParam1, INT nParam2, DWORD nParam3)
{
	FireEvent(KOBJEVENT(nEvent, nParam1, nParam2, nParam3));
	DispatchEvent("uudu", nEvent, nParam1, nParam2, nParam3);
	return TRUE;
}

template<>
inline BOOL KEventCreator::FireEvent(UINT nEvent, DWORD nParam1, DWORD nParam2, INT nParam3)
{
	FireEvent(KOBJEVENT(nEvent, nParam1, nParam2, nParam3));
	DispatchEvent("uuud", nEvent, nParam1, nParam2, nParam3);
	return TRUE;
}

template<>
inline BOOL KEventCreator::FireEvent(UINT nEvent, DWORD nParam1, DWORD nParam2, DWORD nParam3)
{
	FireEvent(KOBJEVENT(nEvent, nParam1, nParam2, nParam3));
	DispatchEvent("uuuu", nEvent, nParam1, nParam2, nParam3);
	return TRUE;
}


// �¼��Ĺ۲��ߣ���Ҫ�����¼�����Ӵ�����
class KObjEventWatch
{
	friend class KEventCreator;
	typedef std::map<KEventCreator*, BOOL> EVENTCREATORMAP;			// <���۲���, �Ƿ����ڹ۲�(0��ʾ��ͣ)>
public:
	virtual ~KObjEventWatch();

	BOOL Release();
public:
	// �۲�ָ��KEventCreator��ָ���¼������û��ָ��pEventCreator���ǹ۲����е�pEventCreator
	BOOL Watch(UINT nEvent, KEventCreator* pEventCreator = NULL);

	// ȡ���۲�
	BOOL CancelWatch(UINT nEvent, KEventCreator* pEventCreator = NULL);

	// ��ͣ��һ��KEventCreator�Ĺ۲�
	BOOL Suspend(KEventCreator* pEventCreator);
	
	// �ָ���һ��KEventCreator�Ĺ۲�
	BOOL Resume(KEventCreator* pEventCreator);

	// �Ƿ��һ��KEventCreator��ͣ�۲�
	BOOL IsSuspend(KEventCreator* pEventCreator);

public:
	// ��Ӧ�¼�
	virtual BOOL OnEvent(KEventCreator& rcSender, CONST KOBJEVENT& rcEvent) = 0;
	
private:
	EVENTCREATORMAP m_mapEventCreator;	// ����[���۲���]�б����۲���Release��ʱ�����֪ͨ����[���۲���]
};

