/* -------------------------------------------------------------------------
//	�ļ���		��	KRegion_NS.h
//	������		��	simon
//	����ʱ��	��	2009-9-23 16:47:47
//	��������	��	adapted from Sword Online III, originally by Zhu JianQiu
//
// -----------------------------------------------------------------------*/
#ifndef __KREGION_NS_H__
#define __KREGION_NS_H__

// -------------------------------------------------------------------------
#include "kcell.h"
#include "onlinegameworld/ikscene.h"

#define SCRIPT_COUNT_PER_REGION		16
#define SCRIPT_DATA_SIZE (sizeof(KRegionTrapScript) * SCRIPT_COUNT_PER_REGION)

class KScene;
class KSceneObject;
class KPlayer;
class KNpc;
class KDoodad;

class KRegion
{
public:
	KRegion(void);
	virtual ~KRegion(void);

	BOOL Init(KScene* pScene, INT nRegionX, INT nRegionY);
	VOID UnInit();

	VOID Activate(VOID);

	BOOL LoadTerrain();
	//BOOL SaveTerrain(); // for the scene editor

	BOOL AddPlayer(KSceneObject* pSceneObj);
	BOOL RemovePlayer(KSceneObject* pSceneObj);
	BOOL AddNpc(KSceneObject* pSceneObj);
	BOOL RemoveNpc(KSceneObject* pSceneObj);
	BOOL AddDoodad(KSceneObject* pSceneObj);
	BOOL RemoveDoodad(KSceneObject* pSceneObj);

	BOOL DeleteAllNpc(VOID);
	BOOL DeleteAllDoodad(VOID);
	BOOL DeleteAllPlayer(VOID);
	BOOL DeleteAllObject(VOID);

	BOOL DeleteAllCell(VOID);	// �˺����ͻ��˺ͷ�����������
	LPCSTR GetScriptByIndex(DWORD dwIndex)
	{
		ASSERT(m_pScriptList);
		LPCTSTR pszScript = NULL;

		if (dwIndex < SCRIPT_COUNT_PER_REGION)
			pszScript = m_pScriptList[dwIndex].szScript;

		return pszScript;
	}


	// ����Region�е�Cell
	template <class TFunc> BOOL TraverseCell(TFunc& Func);
	BOOL TraversePlayer(IKTraverseHelper& rcHelper);
	BOOL TraverseNpc(IKTraverseHelper& rcHelper);
	BOOL TraverseCharacter(IKTraverseHelper& rcHelper);
	BOOL TraverseDoodad(IKTraverseHelper& rcHelper);

	// ����Region�еĳ�������
	template <class TFunc> BOOL TraverseNpc(TFunc& Func);
	template <class TFunc> BOOL TraverseDoodad(TFunc& Func);
	template <class TFunc> BOOL TraversePlayer(TFunc& Func);
public:
	// ��Region�е����½Ǹ��ӣ���������ͼ�ϵ����꣨��λ�����ӣ�
	INT					m_nLeftCell;
	INT					m_nBottomCell;

	// ��Region�е����½Ǹ��ӵ����µ㣬��������ͼ�ϵ����꣨��λ���㣩
	INT					m_nLeft;
	INT					m_nBottom;

	// ��Region��������ͼ�ϵ����꣨��λ��Region��
	INT				    m_nRegionX;
	INT				    m_nRegionY;

	KScene*			m_pScene;										
	KCell*			m_pCells;
	KRegionTrapScript*		m_pScriptList;
	INT				m_nEnterFrame;
	INT             m_nLeaveFrame;     // ���һ����ɫ�뿪��֡��
	DWORD		m_dwActiveFrame;

	QList			m_cNpcList;				// Npc�б�
	QList			m_cDoodadList;			// Doodad�б�
	QList			m_cPlayerList;		// ����б�

public:
	// optimization
#ifdef GAME_SERVER
	inline BOOL IsActive(DWORD dwFrame) { return dwFrame < m_dwActiveFrame + GAME_FPS * 3; }
#else
	inline BOOL IsActive(DWORD dwFrame) { return (UINT64)dwFrame < (UINT64)m_dwActiveFrame + GAME_FPS / 2; }
#endif

	VOID SetActive();
	BOOL IsActive();

	// ����ϰ�
	BOOL AddObstacle(INT nXCell, INT nYCell, KCell* pCell);
	BOOL AddObstacle(INT nXCell, INT nYCell, const KCell& crCellInfo, INT nDynamicObstacleGroupIndex);
	// ɾ���ϰ�
	KCell* RemoveObstacle(INT nXCell, INT nYCell, INT nZ);

	BOOL GetBaseCellInfo(INT nXCell, INT nYCell, KCell* pCell);
	BOOL SetBaseCellInfo(INT nXCell, INT nYCell, KCell& rCell);

	// ��ȡ�ϰ�: �±��� <= nZ <= �ϱ���
	KCell* GetObstacle(INT nXCell, INT nYCell, INT nZ);

	KCell* GetLowestObstacle(INT nXCell, INT nYCell);

	// ��ȡZ�����µ�һ�����ڻ����nZ��Cell, nZ: ��������,��λ:��
	KCell* GetLowerObstacle(INT nXCell, INT nYCell, INT nZ);

	// ��pnRelativeZ����ɹ����Z���������,���û�гɹ�,�򲻻��޸�*pnRelativeZ
	// �������Ŀ��Cell���ϰ����޷�����,��*pnObstacleDirection�����ϰ��ķ��߷���
	// ע��,������һ���ܹ��õ��ϰ����߷���,����Ҫ�ڵ��˺���ǰ��*pnObstacleDirection��Ϊ-1
	// ���ú�,�������CellΪ��,����*pnObstacleDirection��[0, DIRECTION_COUNT]��,��*pnObstacleDirection�ű�ʾ�ϰ�����
	KCell* GetAdaptedCellForObj(
		INT nXCell, INT nYCell, INT nFootPosZ, INT nClimb, 
		INT nHeight, BOOL bIgnoreDynamicSwitch,
		INT* pnRelativeZ, INT *pnObstacleDirection);

	// ע��,����ĺ����ϸ����߶�,���������������Ѱ��һ����ӽ���Cell,�����ϸ�ƥ��߶�

	// ��pnRelativeZ����ɹ����Z���������,���û�гɹ�,�򲻻��޸�*pnRelativeZ
	KCell* GetProximalCellForObj(
		INT nXCell, INT nYCell, INT nFootPosZ, INT nHeight, 
		BOOL bIgnoreDynamicSwitch, 
		BOOL bIgnoreBlock, 
		INT* pnRelativeZ
		);

	// ȡ��Cell�����е���һ��Cell,�ڲ��ᶯ̬�ϰ��Ŀ���
	KCell* GetPreCell(INT nCellX, INT nCellY, KCell* pCell);
	// ȡ����һ����Ч��Cell,�ڲ��ῼ�Ƕ�̬�ϰ�����
	KCell* GetNextCell(KCell* pCell, BOOL bIgnoreDynamicSwitch);

	BOOL CheckObstacle(INT nXCell, INT nYCell, INT nLayer);

private:
	enum KTERRAIN_DATA_VERSION
	{
		eTerrainDataVersionPrevious = 1,
		eTerrainDataVersionCurrent
	};

	struct KRegionHeader
	{
		INT nVersion;
		INT nRegionX;
		INT nRegionY;
		INT nReserved;
	};

	//KCell   m_Cells[REGION_GRID_WIDTH * REGION_GRID_HEIGHT];	
	KRegionTrapScript   m_dwScriptList[SCRIPT_COUNT_PER_REGION];

	BOOL LoadTerrainBufferV2(const BYTE* pbyData, size_t uDataLen);

	BOOL AddSceneObject(QList& rcList, KSceneObject* pSceneObj);
	BOOL RemoveSceneObject(KSceneObject* pSceneObj);

	friend class KScene;
};

template <class TFunc> 
BOOL KRegion::TraverseNpc(TFunc& Func)
{
	BOOL bResult  = false;
	BOOL bRetCode = false;

	SceneObjNode* pNode = (SceneObjNode*)m_cNpcList.GetHead();
	while (pNode != NULL)
	{
		KNpc* pNpc = (KNpc*)(pNode->m_pSceneObject);

		bRetCode = Func(pNpc);
		PROCESS_ERROR(bRetCode);

		pNode = (SceneObjNode*)pNode->GetNext();
	}

	bResult = true;
EXIT0:
	return bResult;
}

template <class TFunc> 
BOOL KRegion::TraverseDoodad(TFunc& Func)
{
	BOOL bResult  = false;
	BOOL bRetCode = false;

	SceneObjNode* pNode = (SceneObjNode*)m_cDoodadList.GetHead();
	while (pNode != NULL)
	{
		KDoodad* pDoodad = (KDoodad*)(pNode->m_pSceneObject);

		bRetCode = Func(pDoodad);
		PROCESS_ERROR(bRetCode);

		pNode = (SceneObjNode*)pNode->GetNext();
	}

	bResult = true;
EXIT0:
	return bResult;
}

template <class TFunc> 
BOOL KRegion::TraversePlayer(TFunc& Func)
{
	BOOL bResult  = false;
	BOOL bRetCode = false;

	SceneObjNode* pNode = (SceneObjNode*)m_cPlayerList.GetHead();
	while (pNode != NULL)
	{
		KPlayer* pPlayer = (KPlayer*)(pNode->m_pSceneObject);

		bRetCode = Func(pPlayer);
		PROCESS_ERROR(bRetCode);

		pNode = (SceneObjNode*)pNode->GetNext();
	}

	bResult = true;
EXIT0:
	return bResult;
}


// -------------------------------------------------------------------------

#endif /* __KREGION_NS_H__ */
