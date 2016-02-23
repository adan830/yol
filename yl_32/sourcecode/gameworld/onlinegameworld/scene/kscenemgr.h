/* -------------------------------------------------------------------------
//	�ļ���		��	kscenemgr.h
//	������		��	xiewen
//	����ʱ��	��	2009-9-17 9:57:00
//	��������	��	�߼�����������
//
// -----------------------------------------------------------------------*/
#ifndef __KSCENEMGR_H__
#define __KSCENEMGR_H__

#include <map>
#include "kscene.h"
#include "kterraindata.h"
#include "kobjectindex.h"
#include "onlinegameworld/ikscenemgr.h"
#include "../onlinegamemodule/ai/PatrolPathList.h"

// -------------------------------------------------------------------------

class KSceneMgr : public IKSceneMgr, public KEventCreator
{
public:
	KSceneMgr(void);
	virtual ~KSceneMgr(void);

	BOOL		Init();
	BOOL		Uninit();
	BOOL		Activate();

	KScene*	GetScene(INT nMapId, INT nMapCopyIndex = 0);
	INT			GetCount(); // get count of loaded scenes

	// ���ء�ж�ص�ͼ
	KScene*		LoadScene(INT nMapId, INT nMapCopyIndex); // ����
	BOOL		UnloadScene(INT nMapId, INT nMapCopyIndex = 0);
	BOOL		UnloadAllScenes();

	IKScene*	FirstScene();
	IKScene*	NextScene();

	CONST KSCENE_CONFIG* GetSceneInfo(DWORD dwMapTemplateId);

	INT GetSceneType(DWORD dwMapTemplateId);

	BOOL IsFightMap(DWORD dwMapTemplateId);
	
	BOOL CanTeam(DWORD dwMapTemplateId);

	BOOL IsSetFightMode(DWORD dwMapTemplateId);

private:
	BOOL		_ReadSceneList();

public:
	typedef std::map<DWORD, KSCENE_CONFIG> KSCENE_CONFIG_LIST;

	KSCENE_CONFIG_LIST	m_cSceneCfgList;	// scenelist.txt���ñ�
	KPatrolPathList		m_PatrolPathList;
private:
	KObjectIndex<KScene>	m_cSceneSet;			// ���м��صĵ�ͼ
	KObjectIndex<KTerrainScene>	m_cTerrainCache;			// ��������ϰ�

};

extern	KSceneMgr	g_SceneMgr;

// -------------------------------------------------------------------------

#endif /* __KSCENEMGR_H__ */
