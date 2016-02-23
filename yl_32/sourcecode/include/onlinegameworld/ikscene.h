
#pragma once

#include "scene_def.h"


// -------------------------------------------------------------------------
class KSceneObject;

class IKTraverseHelper
{
public:
	BOOL operator()(KSceneObject* pObj) { return OnTraverse(pObj); }
	virtual BOOL OnTraverse(KSceneObject* pObj) PURE;
};
//class IKTraverseHelper2
//{
//public:
//	virtual BOOL operator()(KSceneObject* pObj, INT nEnterFrame) PURE;
//};

struct KSCENE_CONFIG
{
	DWORD	dwTemplateId;
	CHAR		szClass[MAX_NAME_LEN];					// ��������
	CHAR		szName[MAX_NAME_LEN];		// ��ʾ������
	CHAR		szPath[MAX_PATH];					// �߼�����·��
	CHAR		szSceneType[MAX_NAME_LEN];			// �����������ƣ�С���ͣ�
	INT			nBroadcastRange;		// ͬ����Χ
	BOOL		bCanPK;                // �Ƿ�����PK

	INT			nBattleSceneId;         // �ĳ���Ĭ��ʹ�õ�ս������Id
	INT		nType;					// �������
	BYTE	bFightMap;				// �Ƿ�ս����ͼ  add by NN
	BYTE	bCanTeam;				// �Ƿ����� add by GG
	BYTE	bSetFightMode;			// �Ƿ��������ս��ģʽ
};

class IKScene
{
public:
	virtual	BOOL	Init(CONST KSCENE_CONFIG& rCfg)	PURE;
	virtual	BOOL	Uninit()	PURE;
	virtual	BOOL	Activate()	PURE;

	// ���Player��Npc��Doodad��û��ʲô��ͬ��ֻ��Ϊ�����ܷŵ��˲�ͬ���б���
	virtual	BOOL	AddPlayer(KSceneObject* pSceneObj, INT x, INT y, INT z)	PURE;
	virtual	BOOL	RemovePlayer(KSceneObject* pSceneObj)	PURE;
	virtual	BOOL	AddNpc(KSceneObject* pSceneObj, INT x, INT y, INT z)	PURE;
	virtual	BOOL	RemoveNpc(KSceneObject* pSceneObj)	PURE;
	virtual	BOOL	AddDoodad(KSceneObject* pSceneObj, INT x, INT y, INT z)	PURE;
	virtual	BOOL	RemoveDoodad(KSceneObject* pSceneObj)	PURE;

	virtual	DWORD	GetId()	PURE;
	virtual	DWORD	GetTemplateId()	PURE;
	virtual	LPCSTR		GetClass()	PURE;
	virtual	LPCSTR		GetName()	PURE;
	virtual	BOOL		GetCanPK()	PURE;
	virtual INT         GetSceneBattleId() PURE;

	virtual	KSceneObject*	GetByNickName(LPCSTR pszNickName)	PURE;
	virtual INT		GetPlayerCount()	PURE;
	virtual INT		GetNpcCount()	PURE;
	virtual INT		GetDoodadCount()	PURE;
	virtual INT		GetRegionCount()	PURE;

	virtual	BOOL	SetBroadcastRange(INT nRange)	PURE; // Ŀǰû��֪ͨ�ͻ��ˣ���������ʱ��̬�ı�ͬ����ΧҪ��Э��

	virtual	BOOL	TraverseNearbyPlayers(IKTraverseHelper& rcHelper, KSceneObject* pCenterObj)	PURE; // �����������
	virtual	BOOL	TraverseAllPlayers(IKTraverseHelper& rcHelper)	PURE; // ���������ڵ��������
	virtual	BOOL	TraverseNearbyNpcs(IKTraverseHelper& rcHelper, KSceneObject* pCenterObj)	PURE; // ��������npc
	virtual	BOOL	TraverseAllNpcs(IKTraverseHelper& rcHelper)	PURE; // ���������ڵ�����npc
	virtual	BOOL	TraverseNearbyDoodads(IKTraverseHelper& rcHelper, KSceneObject* pCenterObj)	PURE; // ��������doodad
	virtual	BOOL	TraverseAllDoodads(IKTraverseHelper& rcHelper)	PURE; // ���������ڵ�����doodad

#ifdef GAME_SERVER
	// ���½ӿ��Ƿ���ͬ������ʹ�õģ�����ָ���ĳ�������(sobj)�ƶ����������"�ھ�"�����ƶ���û���κ���"�ھ�"
	// ���˶����Լ�Ҫ����㲥�ƶ�����ոյ��������㲥�Լ��ĵ����͡���������Χ����ҡ�Npc��Doodad��
	// ԭ�ز������˱����ؽ��ܱ��˵Ĺ㲥���������н���������ָ���֡��ȡ��Χ��ҵ��������һ��"Lazy-Sync"��
	virtual	BOOL	FindNewNeighborPlayers(IKTraverseHelper& rcHelper, KSceneObject* pCenterObj)	PURE;
	virtual	BOOL	FindNewNeighborNpcs(IKTraverseHelper& rcHelper, KSceneObject* pCenterObj)	PURE;
	virtual	BOOL	FindNewNeighborDoodads(IKTraverseHelper& rcHelper, KSceneObject* pCenterObj)	PURE;
	virtual	BOOL	FindOldNeighborPlayers(IKTraverseHelper& rcHelper, KSceneObject* pCenterObj)	PURE;
	virtual	BOOL	FindOldNeighborNpcs(IKTraverseHelper& rcHelper, KSceneObject* pCenterObj)	PURE;
	virtual	BOOL	FindOldNeighborDoodads(IKTraverseHelper& rcHelper, KSceneObject* pCenterObj)	PURE;
#endif // GAME_SERVER
};

// -------------------------------------------------------------------------

