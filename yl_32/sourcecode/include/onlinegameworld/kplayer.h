
#pragma once

#include "Runtime/qstring.h"
#include "config/kplayerdef.h"
#include "onlinegameworld/kcharacter.h"

#include "onlinegameworld/kplayerserver.h"
#include "onlinegameworld/kplayerclient.h"

struct IMemBlock;
class KLuaPlayer;
class KDoodad;
class KLuaCharacter;

// ��ҵ���Ϸ״̬
enum PLAYER_GAME_STATE
{
	emPLAYERSTATE_BEGIN,			// ��ʼ״̬�������յ�¼�����Э�� 0

	gsWaitForConnect,			// ���ڵȴ��ͻ��˵����� 1
	gsWaitForPermit,		    // ��½ʱ���ڵȴ�GC��ȷ�� 2
	gsWaitForRoleData,		    // ��¼ʱ���ڵȴ�Goddess�Ļذ� 3
	gsWaitForLoginLoading,      // ��¼(����)�����еȴ��ͻ������� 4
	gsWaitForNewMapLoading,     // �л���ͼ�����еȴ��ͻ������� 5

	gsPlaying,				    // ������Ϸ�� 6

	gsSearchMap,			    // ����������ͼ,��һ����Ҫ��� 7
	gsWaitForTransmissionSave,  // ��������׼����� 8
	gsWaitForTransmissionGuid,	// ���ʱ���ڵȴ�Ŀ�����������GUID  9 

	gsWaitForBZoneTransferSave, // ս��������� 10 

	gsDeleting,				    // �ͻ��˶����������ʱ�ǳ� 11

};

// -------------------------------------------------------------------------
class KPlayer : public KCharacter
{
public:
	KD_CHARACTER_TASKFUN_U(OnlineTime,			emKVARGROUP_PLAYER,	emKPLAYER_TASK_ONLINE_TIME)
	KD_CHARACTER_TASKFUN_U(LastUpdateMysteryShopTime,	emKVARGROUP_PLAYER,	emKPLAYER_LAST_UPDATE_MYSTERY_SHOP_TIME)
public:
	INT GetPlayerIndex() const { return m_nIndex; }
	DWORD GetPlayerId() const { return m_dwId; }
	// Player Game State
	PLAYER_GAME_STATE GetGameState() const { return m_eGameState; }
	VOID SetGameState(PLAYER_GAME_STATE eState) { QLogPrintf(LOG_INFO, "SetGameState %d %d\n", m_dwId, eState); m_eGameState = eState; }

	// ��ýű��ӿ�
	virtual KLuaCharacter* GetScriptInterface() {return (KLuaCharacter*)m_pLuna;}
public:
	KPlayer();
	virtual ~KPlayer();

#ifdef GAME_SERVER
	KPlayerServer m_cPlayerServer;
	friend class KPlayerServer;

	KDoodad* m_pDoodad;

	virtual BOOL LogicGoTo(INT nX, INT nY, INT nZ); // ��ʱ�����Ż�
#endif
#ifdef GAME_CLIENT
	KPlayerClient m_cPlayerClient;
	friend class KPlayerClient;
	BOOL ClientGoTo(INT nX, INT nY, INT nZ);
	BOOL ClientJump();
#endif

	BOOL Activate();
	BOOL OnRemove();
	BOOL GoTo(INT nX, INT nY, INT nZ, BOOL bSyncSelf = FALSE);
	BOOL StopMove(BOOL bSyncSelf /* = FALSE */);
	BOOL Jump(BOOL bSyncSelf = FALSE);
	BOOL JumpTo(INT nX, INT nY, INT nZ);
	BOOL KnockTo(INT nX, INT nY, INT nZ, INT nDirection);
	BOOL Pull(INT nX, INT nY, INT nZ, INT nDirection);
	BOOL OnTrap(LPCSTR pszTrapScript);
	BOOL OnLeaveTrap(LPCSTR pszTrapScript);
	virtual	BOOL	OnReachTarget();

	BOOL ForwardPosition(int nFrame);

protected:
	BOOL Init(INT nPlayerIndex, const QString& strName);
	BOOL Uninit();

	BOOL	ChangeRegion(KRegion* pDestRegion);
protected:
	PLAYER_GAME_STATE	m_eGameState;

	INT					m_nIndex; // PlayerIndex
	KLuaPlayer*			m_pLuna; // �ű�ָ��

public:
	struct KMOVE_CTRL 
	{
		BOOL bDisable;      // ��ֹ�������������
		BOOL bMove;         // �Ƿ����ƶ�
		BOOL bWalk;         // �Ƿ���Walk(������Run,����Swim)
		int  nDirection;   // �ƶ��ķ���
		int  nMoveCount;    // �ͻ����ƶ�����������
		BOOL bUpdate;

		INT	nDestX;
		INT	nDestY;
		INT	nDestZ;
		INT	nMoveState;
	};
	KMOVE_CTRL m_sMoveCtrl;
	void MoveCtrl();

	friend class KPlayerMgr;

	DWORD m_dwTeamId;
	DWORD m_dwSystemTeamId;
	DWORD m_dwKinId;
	DWORD m_dwKinMasterId;
	BYTE m_byIsKinMaster;

	INT				m_nTimer; // ���������״̬��ʱ��
public:
	//������������Զʱ �߽��ٳ���������Ի��������¼��·ֹͣ�� ��Ҫ�ӳٶԻ��ĳ�������ID
	DWORD GetDelayTalkObjId()						{ return m_dwDelayTalkObjId; }
	DWORD GetSetDelayTalkObjIdFrame()				{ return m_dwSetDelayTalkObjIdFrame; }
	VOID  SetDelayTalkObjId(DWORD dwDelayTalkNpcId);

	VOID SetPlayerTeamId(BOOL bSystem, DWORD dwTeamID)
	{
		if (bSystem)
		{
			m_dwSystemTeamId = dwTeamID;
		}
		m_dwTeamId = dwTeamID;

		SetTeamId(dwTeamID);
	}
	DWORD GetTeamId()
	{
		if (m_dwSystemTeamId != KD_BAD_ID)
			return m_dwSystemTeamId;
		return m_dwTeamId;
	}

	DWORD GetSysTeamId()
	{
		return m_dwSystemTeamId;
	}

	DWORD GetKinId()
	{
		return m_dwKinId;
	}

	BOOL IsKinMaster()
	{
		return (m_dwKinMasterId == GetId());
	}

	DWORD GetKinMasterId() { return m_dwKinMasterId; }

	//ԭ��KPlayerUiScript::ApplyTalk()NPC�Ự�ӿ��Ƶ�����
	BOOL ApplyNpcTalk(DWORD dwNpcId);

	//��doodad
	BOOL ApplyOpenDoodad(DWORD dwDoodadId);

	//��Ⲣ�����ӳٻỰ��Ϣ������TRUE��ʾ�����ã�����FALSE��ʾδ����
	//nDistance2Limit��ʾ�Ự�����ƽ������ֹ�ڲ�����������
	BOOL CheckAndSetDelayOpen(KSceneObject* pScenceObj, INT32 nDistanceLimit = KD_MIN_SCENCE_OBJ_TALK_DISTANCE);

	//��·ֹͣʱ�Ļص�
	BOOL OnPlayerMoveStop();

	//Ŀ���ı�ص�����Ҫ���������������
	BOOL OnTargetChange();

	//�Ƿ�����ƶ�
	virtual BOOL	CanMove();
private:
	//�ƶ�ֹͣʱ���Ự�ĳ�������ID
	DWORD m_dwDelayTalkObjId;
	//����m_dwDelayTalkObjId���߼�֡
	DWORD m_dwSetDelayTalkObjIdFrame;

private:
	std::map<INT, INT> m_mapTrapInvalid;	// ��Ч��trap��id����

public:
	VOID SetTrapInvalid(INT nTemplateId);
	VOID RemoveTrapInvalid(INT nTemplateId);
	BOOL IsTrapInvalid(INT nTemplateId);

private:
	std::map<DWORD, INT> m_mapDoodadIds;		// ����ĵ���id����

public:
	VOID AddDropDoodadId(DWORD dwDoodadId);

	VOID RemoveDropDoodadId(DWORD dwDoodadId);

	VOID PickUpAllDoodad();

};

