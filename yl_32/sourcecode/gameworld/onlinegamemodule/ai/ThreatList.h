#ifndef _KTHREAT_LIST_H_
#define _KTHREAT_LIST_H_

#include "config/gamedef.h"
#include "onlinegameworld/kcharacterctrlbase.h"
#include "config/kcharacterdef.h"
#include <stddef.h>

#define CHECK_THREAT_INTERVAL		((GAME_FPS) * 2)
#define THREAT_FADE_FRAME			((GAME_FPS) * 1)

class KCharacter;
class KSkill;
class KPlayer;

#define KTHREAT_CONTAINING_RECORD(address, type, field)         \
    ((type *)((char *)(address) -                               \
    (ptrdiff_t)(&((type *)0x10)->field) + (ptrdiff_t)0x10))


#ifdef GAME_SERVER

class KThreatLink
{
public:
    BOOL                        AddMember(DWORD dwThreatLinkID, KCharacter* pCharacter);
    BOOL                        DelMember(DWORD dwThreatLinkID, KCharacter* pCharacter);

    BOOL                        NewThreat(DWORD dwThreatLinkID, KCharacter* pCharacter);
    BOOL                        SyncAllThreat(DWORD dwThreatLinkID, KCharacter* pDstCharacter);
    BOOL                        ClearAllMemberThreat(DWORD dwThreatLinkID);

private:
    typedef std::vector<DWORD>              MEMBER_VECTOR;
    typedef std::map<DWORD, MEMBER_VECTOR>  THREAT_LINK_MAP;

    THREAT_LINK_MAP             m_ThreatLinkMap;
};

struct KSimpThreatenNode;

struct KSimpThreatNode 
{
    KSimpThreatNode();

    KCharacter*                 pCharacter;
    KSimpThreatenNode*          pPairNode;		            // ʡ���������ң����Լ�¼��Եı��еĽڵ�ָ�루�Ż��ã�

    int				            nInitFrame;                 // ����޽ڵ��һ�ν����ޱ��ʱ��
    int				            nLastRefreshFrame;	        // ����޽ڵ����һ��ˢ��ʱ��
    int				            nLastInThreatFieldFrame;    // ���֡���ľ���ȡ���� CHECK_THREAT_INTERVAL

    int				            nThreat[thtTotal];
    QNode                       SortedListNode[thtTotal];   // ��ͬ���͵ĳ���Լ�ά��һ���Ӵ�С�����List

    BOOL                        bTopFlag;                   // ������ö�
    BOOL                        bPrimacord;                 // �����ж�˭�ȶ���
};

struct KSimpThreatenNode : QNode 
{
    KCharacter*		            pCharacter;
    KSimpThreatNode*	        pPairNode;
};

class KSimpThreatList : public KCharacterCtrlBase
{

public:
	enum 
	{	emKCtrlId = emCHARACTER_CTRL_THREAT_LIST	};

	KSimpThreatList(KCharacter& rcCharacter);

	virtual BOOL Init();
	virtual BOOL Active() { Activate(); return TRUE;}

    //BOOL                        Init(KCharacter* pSelf);
    BOOL                        UnInit();

    BOOL                        ModifyThreat(THREAT_TYPE eThreatType, KCharacter* pCharacter, int nThreat);     // �ҳ�� pCharacter
    BOOL                        ModifyThreaten(THREAT_TYPE eThreatType, KCharacter* pCharacter, int nThreat);   // ���г���ҵ���ȥ��� pCharacter
    BOOL                        ClearThreat(KCharacter* pCharacter);
    BOOL                        ClearAllThreat();
    BOOL                        ClearAllThreaten();

    BOOL                        StickThreat(KCharacter* pCharacter);
    BOOL                        UnstickThreat();

    BOOL                        ZeroThreat(KCharacter* pCharacter);

    const KSimpThreatNode*      GetFirstThreat(THREAT_TYPE eThreatType);
    const KSimpThreatNode*      GetNextThreat(THREAT_TYPE eThreatType, const KSimpThreatNode* cpThreatNode);
    const KSimpThreatNode*      GetNthThreat(THREAT_TYPE eThreatType, int n);
    const KSimpThreatNode*      FindThreat(KCharacter* pCharacter);

    const KSimpThreatenNode*    GetFirstThreaten();
    const KSimpThreatenNode*    GetNextThreaten(const KSimpThreatenNode* cpThreatenNode);

    BOOL                        IsInThreatList(KCharacter* pCharacter);
    BOOL                        IsInThreatenList(KCharacter* pCharacter);

    void                        UpdateKeepThreatField();

    void                        Activate();

    BOOL                        GetThreatListCount(THREAT_TYPE eThreatType, int& nCount);
    int                         GetMainThreatSum();

    BOOL                        SetBattleZone(int nX, int nY, int nZ, int nRadius, int nHeight);

private:
    BOOL                        IsDropCandidate(KPlayer* pPlayer);
    void                        OnCharacterEnterNpcThreatList(KCharacter* pEnterCharacter);
    void                        OnCharacterLeaveNpcThreatList(KCharacter* pLeaveCharacter);
    void                        OnPlayerEnterPlayerThreatList(KPlayer* pPlayer);

private:
    KSimpThreatNode*            _GetFirstThreat(THREAT_TYPE eThreatType);
    KSimpThreatNode*            _FindThreat(KCharacter* pCharacter);
    void                        _AdjustThreatList(KSimpThreatNode* pSimpThreatNode);
    BOOL                        _ClearThreat(KSimpThreatNode* pSimpThreatNode);

private:
    typedef std::map<DWORD, KSimpThreatNode> KSIMP_THREAT_MAP;

    KCharacter*                 m_pSelf;
    int                         m_nThreatPointX;
    int                         m_nThreatPointY;
    int                         m_nNextCheckLoop;

    int                         m_nBattleZoneCenterX;
    int                         m_nBattleZoneCenterY;
    int                         m_nBattleZoneCenterZ;
    int                         m_nBattleZoneRadius;
    int                         m_nBattleZoneHeight;

    QList                       m_SortedList[thtTotal];
    QList                       m_ThreatenList;
    int                         m_nMainThreatSum;
};

#endif // _SERVER

#ifdef _CLIENT
struct KThreatLiteNode : QNode
{
    DWORD   dwCharacterID;
};

//�ͻ����ó�ޱ�
class KThreatList
{
public:
	KThreatList();

	BOOL                        Init(KCharacter* pSelf);
	void                        UnInit();

	BOOL                        ModifyThreat(DWORD dwCharacterID);
	BOOL                        ModifyThreaten(DWORD dwCharacterID);
    
	BOOL                        ClearThreat(DWORD dwCharacterID);
	BOOL                        ClearThreaten(DWORD dwCharacterID);

	const KThreatLiteNode*      GetFirstThreat();
    const KThreatLiteNode*      GetFirstThreaten();

	BOOL                        IsInThreatList(DWORD dwCharacterID);
	BOOL                        IsInThreatenList(DWORD dwCharacterID);
private:
	BOOL                        ClearThreat(KThreatLiteNode* pNode);

private:
	KCharacter*                 m_pSelf;
	QList		                m_ThreatList;
	QList		                m_ThreatenList;
};

#endif //_CLIENT

#define m_SimpThreatList GetCtrlRef<KSimpThreatList>()

#endif	//_KTHREAT_LIST_H_
