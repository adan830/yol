/* -------------------------------------------------------------------------
//	�ļ���		��	relationcounter.h
//	������		��	
//	����ʱ��	��	
//	��������	��	��Һ��Ѽ���������ֹ����������Ŀ���ƣ�
//
// -----------------------------------------------------------------------*/
#ifndef __KRELATIONCOUNTER_H__
#define __KRELATIONCOUNTER_H__

#include <map>
#include <functional>

class KRelationCounter
{
public:
	struct KRELATION_COUNT
	{
		INT		nCurCount;	// ��ǰ����
		INT		nMaxCount;	// �������
	};
	enum KEPLAYERRELATION_TYPE_MAXNUMBER
	{
		emKRELATION_FRIENDRELATION_COUNT	= 11, // ��ʱ������
		emKRELATION_BLACKRELATION_COUNT		= 11,
		emKRELATION_ENEMYRELATION_COUNT		= 40,
		emKRELATION_COUPLE_COUNT			= 1,
		//emKRELATION_TRAIN_AND_BUDDY_COUNT	= 240,		// ���ʦͽ,���ѹ�ϵ����
	};
	typedef std::map<INT, KRELATION_COUNT>	RELATION_MAP;
public:
	inline static KRelationCounter *Instance()
	{
		return &ms_isnt;
	}
	KRelationCounter();
	~KRelationCounter();
	INT  CheckReachMaxCount(INT nType, INT nPlayerId);
	INT  GetTrainAndBuddyCount(INT nPlayerId);// ��ȡ����ʦͽ�����ѹ�ϵ����
	INT  GetOneTypeCount(INT nPlayerId, BYTE btType, BOOL bMaster = TRUE);// ��ȡ�ƶ���ϵ���͵Ĺ�ϵ����
private:
	RELATION_MAP			m_mapRelationCount;
	static KRelationCounter	ms_isnt;
};

#endif //__KRELATIONCOUNTER_H__

