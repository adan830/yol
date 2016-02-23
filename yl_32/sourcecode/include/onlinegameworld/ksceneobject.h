
/************************************************************************/
#ifndef _KSCENEOBJECT_H_
#define	_KSCENEOBJECT_H_

#include "Misc/utilities.h"
#include "scene_def.h"
#include "kbaseobject.h"
#include "ksceneobjnode.h"
#include "kmath.h"
#include "Runtime/qstring.h"


struct KCell;
class KRegion;
class IKScene;
class KScene;

//������Ϣ
struct KREGENERATION_INFO
{
	KREGENERATION_INFO()
	{
		::memset(this, 0, sizeof(KREGENERATION_INFO));
	}
	//DWORD		dwTemplateId;	// Npcģ��Id
	INT			nX;				// �߼�����x
	INT			nY;				// y
	INT			nZ;				// z	
	INT			nFaceDirection; // �沿����
	INT			nGenerationTime;// ����ʱ��,��λ��
	INT			nNormalAIType;	//Normal AI type
	INT			nRelation;		//Relation

	DWORD		dwExValue;		// ����������Ϣ
	CHAR		szExInfo[MAX_NAME_LEN];	// ����������Ϣ
};

enum KE_MOVE_STATE
{
	cmsInvalid,

	// �ܿ�״̬
	cmsOnStand,					// վ��״̬
	cmsOnWalk,					// ��·״̬
	cmsOnRun,					// �ܲ�״̬
	cmsOnJump,                  // ��Ծ״̬
	cmsOnSwimJump,              // ˮ����Ծ
	cmsOnSwim,                  // ˮ����Ӿ
	cmsOnFloat,                 // ˮ������
	cmsOnSit,					// ��״̬

	// ���ܿ�״̬
	cmsOnChannelSkill,          // ����������״̬������·��ϣ�
	cmsOnSkill,					// ������״̬, ��״̬�²����ٶഥ��һ�μ���

	cmsOnKnockedDown,			// ������״̬
	cmsOnKnockedBack,			// ������״̬
	cmsOnKnockedOff,			// ������״̬ 
	cmsOnHalt,                  // ����(ѣ�Ρ�ЦѨ�ȵ�)
	cmsOnFreeze,                // ���ܶ�(�̶�����)
	cmsOnEntrap,                // �����ƶ�
	cmsOnAutoFly,               // �Զ��ƶ�,����������

	cmsOnDeath,					// ����״̬
	cmsOnDash,					// ���״̬
	cmsOnPull,                  // ��ץ״̬��������ץס�Լ������Է����
	cmsOnRepulsed,              // ����״̬��һ������ٵ�״̬

	cmsOnRise,                  // ����״̬
	cmsOnSkid,                  // ͣ��״̬

	cmsTotal,
};

class KSceneObject : public KBaseObject
{
public:
	KSceneObject();
	virtual ~KSceneObject();
	
	virtual	BOOL	Init();
	virtual	BOOL	Uninit();
	virtual	BOOL	Activate();
	BOOL	CheckGameLoop();

	virtual	BOOL	GoTo(INT x, INT y, INT z, BOOL bSyncSelf = FALSE);
	virtual	BOOL	Jump(BOOL bSyncSelf = FALSE);
	BOOL Jump(BOOL bStandJump, INT nJumpDirection, BOOL bSyncSelf);
	virtual	BOOL	JumpTo(INT nX, INT nY, INT nZ); // Test
	virtual BOOL	KnockTo(INT nX, INT nY, INT nZ, INT nDirection);
	virtual BOOL	Pull(INT nX, INT nY, INT nZ, INT nDirection);
	virtual	INT GetMoveSpeed() const { return m_nMoveSpeed; }
	virtual	BOOL	SetMoveSpeed(INT nMoveSpeed) { m_nMoveSpeed = nMoveSpeed; return TRUE; }
	virtual	BOOL	StopMoving();
	virtual	BOOL	ProcessMove();

	BOOL CheckObstacleDest(INT nStartX, INT nStartY, INT nStartZ, INT nEndX, INT nEndY, INT nEndZ, INT nTouchRange, INT& nLastOkX, INT& nLastOkY);

	inline INT GetVelocityXY() const { return m_nVelocityXY / VELOCITY_ZOOM_COEFFICIENT; } // ��λ ��ÿ֡
	inline INT GetVelocityZ() const { return ZPOINT_TO_XYPOINT(m_nVelocityZ); } // ��λ ��ÿ֡

	virtual	BOOL	OnRemove()
	{
		Q_Printl(std::hex << "Sobj[0x" << m_dwId << "] OnRemove.");
		Uninit();
		return FALSE;
	} 
	// Trap��
	virtual	BOOL	OnTrap(LPCSTR pszScript)
	{
		//if (IS_PLAYER(GetId()))
		//	QLogPrintf(LOG_DEBUG, "[0x%x][%s] OnEnterTrap [%s]", m_dwId, GetName(), pszScript);
		return FALSE;
	}
	virtual	BOOL	OnLeaveTrap(LPCSTR pszScript)
	{
		//if (IS_PLAYER(GetId()))
		//	QLogPrintf(LOG_DEBUG, "[0x%x][%s] OnLeaveTrap [%s]", m_dwId, GetName(), pszScript);
		return FALSE;
	}
	// �ƶ�״̬�仯
	virtual	BOOL	OnMoveStateChanged(KE_MOVE_STATE eMoveState)
	{
		QLogPrintf(LOG_DEBUG, "[0x%x][%s] MoveStateChanged -> %d", m_dwId, GetName(), eMoveState);
		return FALSE;
	}
	virtual	BOOL	OnReachTarget()
	{
		Q_Printl("[ReachTarget] [" << m_nX << "," << m_nY << "," << m_nZ << "].");
		return FALSE;
	}

	 // �Ƿ���Ŀ�긽��(��λcm Ĭ��1Region)
	virtual	BOOL	IsNearby(KSceneObject* pTarget, INT nDistance = REGION_GRID_WIDTH * LOGICAL_CELL_CM_LENGTH);
	virtual BOOL	IsNearbyIn2D(KSceneObject* pTarget, INT nDistance);
	// �ж��Ƿ���ͬ����Χ��
	BOOL IsWithinSyncRange(KSceneObject* pTarget);
	BOOL IsVisible() { return m_bVisible; }
	virtual VOID SetVisible(BOOL bVisible) { m_bVisible = bVisible; }
	inline INT GetFaceDirection() const { return m_nFaceDirection; }
	// ���Ŀ�ĵ�����
	inline BOOL	GetDestination(INT& rnX, INT& rnY, INT& rnZ) { rnX = m_nDestX; rnY = m_nDestY; rnZ = m_nDestZ; return TRUE; }
	// ����߼�λ��
	inline BOOL	GetPosition(INT& rnX, INT& rnY, INT& rnZ) 
	{
		rnX = m_nX; rnY = m_nY; rnZ = 1048576;//m_nZ; //TODO: ǿ�����0�߶�
		return TRUE; 
	}
	// �����߼�λ��(ע�⣺��Ϊ��һ�㲻����ͬ����˲��Ӧ�õ���Player��Npc��TeleportTo�ӿڶ��������)
	BOOL	SetPosition(INT x, INT y, INT z);

	BOOL    IsSwim() { return m_IsSwim; }

	DWORD GetSceneId();
	inline IKScene*	GetScene() { return (IKScene*)m_pScene; }

	inline KE_MOVE_STATE GetMoveState() const { return m_eMoveState; }
	virtual void SetMoveState(KE_MOVE_STATE eMoveState)
	{
		QCONFIRM_RET(eMoveState > cmsInvalid && eMoveState < cmsTotal, );
		//printf("movestate %d,%d\n", eMoveState, m_eMoveState);
		if (eMoveState != m_eMoveState)
		{
			OnMoveStateChanged(eMoveState);
			m_eMoveState = eMoveState;
		}
	}
	INT MoveMode() const { return m_nMoveMode; }
	void SetMoveMode(INT val) { m_nMoveMode = val; }
	// ��ͨGetName�����ַ���ָ�룬����ֱ����KQString���µĸ�ʽ�������voidָ��ת��������
	inline LPCSTR GetName() const { return m_strName; }
	const QString& GetStrName() const { return m_strName; }
	inline LPCSTR GetNickName() const { return m_strNickName; }
	BOOL SetNickName(LPCSTR pszNickName);

public:
	INT			m_nTouchRange;      // �ܻ���Χ��������Χ������뾶
	INT			m_nDestDistance;
	INT			m_nClimbAbility; // ��������

	// ��ǰRegion�еĸ������꣬Region���½�Ϊԭ��
	INT			m_nXCell;			// Region�еĸ���X����		��λ������
	INT			m_nYCell;			// Region�еĸ���Y����		��λ������

	INT			m_nMass;			// ����						��λ��g
	
	INT			m_nWidth;			// ��ȣ�X���ϵ�				��λ����
	INT			m_nLength;			// ���ȣ�Y���ϵ�				��λ����
	INT			m_nHeight;			// ��ȣ�Z���ϵ�				��λ����
	
	INT			m_nPitchDirection;  // ������,��λ(360/256)��

	BOOL		m_bTryPathState;            // �Ƿ�������·����֮��
	INT			m_nTryPathSide;             // ����������������·
	INT			m_nTryPathStartFrame;	// ��·��ʼ֡
	//INT			m_nTryPathDestX;            // ��·��ʼ��ʱ����ƶ�Ŀ���X
	//INT			m_nTryPathDestY;            // ��·��ʼ��ʱ����ƶ�Ŀ���Y
	QString	m_strName;
	QString	m_strNickName; // ����
	BOOL		m_bVisible;	// �Ƿ�ɼ����������˲��ɼ����ѷ�Ҳ��������
	INT			m_nDestX;
	INT			m_nDestY;
	INT			m_nDestZ;
	KScene*		m_pScene;			// �����ĵ�ͼ

	INT m_nMoveMode; // Ŀǰֻ����0��1

	BOOL       m_IsSwim; // �Ƿ���Ӿ��
public:
	INT				m_nVelocityXY;  // ˮƽ�ٶ�
	INT				m_nDirectionXY; // ˮƽ�ٶȷ���
	INT				m_nFaceDirection;	// ��������ĳ��� ��λ: (360/256)��
	INT				m_nVelocityZ;   // ��ֱ�ٶ�
	INT				m_nGravity; // ��������
	INT				m_nCurrentGravity;		// ��ǰ����
	INT				m_nJumpSpeed;               // ��Ծ�Ĵ�ֱ���ٶ�
	INT				m_nMoveSpeed;               // ˮƽ�˶��ٶ�

	KE_MOVE_STATE		m_eMoveState;	// ��ǰ�ƶ�״̬
	DWORD	m_dwBroadcastFrame;

	INT				m_nStopedFaceDirection;	// �˶�ֹͣʱ��������ĳ��� ��λ: (360/256)��

	INT			m_nX;
	INT			m_nY;
	INT			m_nZ;

	KCell*						m_pCell;			// ������Cell
	KRegion*					m_pRegion;			// ������Region
	KRegion*                    m_pLastRegion;      // �ϴ�������Region
	SceneObjNode		m_cRegionNode;	// ����ά��KRegion�еĳ�����������
	

	std::vector<INT>		m_vRegionEnterFrameTable;
	std::vector<INT>		m_vRegionLeaveFrameTable;
	DWORD					m_dwActiveFrame;		// ��Ϸѭ��������Ҫ�����ж��ظ�����
	LPCSTR m_pszLastTrap;

public:
	//����������Ϣ
	BOOL				SetRegenerationInfo(const KREGENERATION_INFO& info);
	//��ȡ������Ϣ
	KREGENERATION_INFO* GetRegenerationInfo(){ return m_pRegenerationInfo; }
private:
	//������Ϣ
	KREGENERATION_INFO*		m_pRegenerationInfo;//��ָ�����û������Ϣ�Ķ�����Ҫ�ռ�

protected:
	BOOL	TryMove(int nStepLength, int nDirection, int* pnObstacleDirection);
	BOOL	CellMoveStupid(int nStepLength);
	BOOL	ProcessHorizontalMoveStupid();
	BOOL	ProcessVerticalMove();
	BOOL	ProcessDropSpeed();
	BOOL	GetWaterline();

	BOOL	CellMoveSmart(int nStepLength);
	void	ProcessHorizontalMoveSmart();
	void	ProcessHorizontalMove();

	BOOL	ForwardPosition(INT nFrame);
	virtual BOOL	ChangeRegion(KRegion* pDestRegion);
	void	SetCell(KCell* pCell);

	void	ResetRegionFrames(INT nRadius);
	void	ResetRegionEnterAndLeaveFrame(KRegion* pCenterRegion);
	BOOL	UpdateRegionFrames(KRegion* pFromRegion, KRegion* pToRegion);

protected:
	// ���߽��
	enum KMOVE_RESULT
	{
		mrInvalid,
		mrSucceed,      // �����ƶ���
		mrOutOfMap,     // ����ͼ��Ե��,��Ч������
		mrObstacle,     // ���ϰ�,�޷�ǰ��
		mrDeleteSelf,   // �ڿͻ���,����ͬ����Χ֮��,���Լ�ɾ����
		mrReachTarget,  // �Ѿ�����Ŀ��
		mrTotal
	};
public:
	friend class KScene;
	friend class KRegion;
	// ���⴦����Ҫֱ�Ӳ����ڲ�����
	friend class KPlayerBaseProcess;
};

inline BOOL g_InRange(KSceneObject* pObjA, KSceneObject* pObjB, int nRange)
{
	BOOL    bResult     = false;
	BOOL    bRetCode    = false;
	int     nXa         = 0;
	int     nYa         = 0;
	int     nZa         = 0;
	int     nXb         = 0;
	int     nYb         = 0;
	int     nZb         = 0;

	assert(pObjA);
	assert(pObjB);

	PROCESS_ERROR(pObjA->m_pScene);
	PROCESS_ERROR(pObjB->m_pScene);

	PROCESS_ERROR(pObjA->m_pScene == pObjB->m_pScene);

	bRetCode = pObjA->GetPosition(nXa, nYa, nZa);
	PROCESS_ERROR(bRetCode);

	bRetCode = pObjB->GetPosition(nXb, nYb, nZb);
	PROCESS_ERROR(bRetCode);

	bRetCode = g_InRange(nXa, nYa, ZPOINT_TO_XYPOINT(nZa), nXb, nYb, ZPOINT_TO_XYPOINT(nZb), nRange);
	PROCESS_ERROR(bRetCode);

	bResult = true;
EXIT0:
	return bResult;
}

inline IN_RANGE_RESULT g_InRange(KSceneObject* pObjA, KSceneObject* pObjB, int nMinRange, int nMaxRange)
{
	IN_RANGE_RESULT nResult     = irrInvalid;
	BOOL            bRetCode    = false;
	int             nXa         = 0;
	int             nYa         = 0;
	int             nZa         = 0;
	int             nXb         = 0;
	int             nYb         = 0;
	int             nZb         = 0;

	assert(pObjA);
	assert(pObjB);

	PROCESS_ERROR(pObjA->m_pScene);
	PROCESS_ERROR(pObjB->m_pScene);

	PROCESS_ERROR(pObjA->m_pScene == pObjB->m_pScene);

	bRetCode = pObjA->GetPosition(nXa, nYa, nZa);
	PROCESS_ERROR(bRetCode);

	bRetCode = pObjB->GetPosition(nXb, nYb, nZb);
	PROCESS_ERROR(bRetCode);

	nResult = g_InRange(nXa, nYa, ZPOINT_TO_XYPOINT(nZa), nXb, nYb, ZPOINT_TO_XYPOINT(nZb), nMinRange, nMaxRange);

EXIT0:
	return nResult;
}

#endif	// _KSCENEOBJECT_H_
