///////////////////////////////////////////////////////////////////////

///	File Name	: kregeneration_mgr.h
///	Author		: Dai Zejun
///	Created Date: 2010-10-29
///
/// Version history:
///		2010-10-29dzj: Created
///	
///	Purpose		: NPC/doodad��������
///				  Ŀǰʵ���ݲ�֧��scence_id���õ������
///				  ���Ҫ֧��scence_id���ã���ʵ��OnScenceRemove()�ӿڣ����ڳ���ɾ����ʱ��ص���ɾ���ó����������
///
///////////////////////////////////////////////////////////////////////
#ifndef __KREGENERATION_MGR__H__
#define __KREGENERATION_MGR__H__

#ifdef GAME_SERVER

#include <map>
#include "Misc/objectpool.h"
#include "Runtime/qstring.h"

enum KE_OBJTYPE
{
	emKOBJ_PLAYER,
	emKOBJ_NPC,
	emKOBJ_DOODAD,
};

class KS_REGENERATION_INFO
{
public:
	KS_REGENERATION_INFO() : 
	dwIdExpect(0),
	dwFrames(0),
	dwTemplateId(0),
	dwSceneId(0),
	nX(0),
	nY(0),
	nZ(0),
	nFaceDirection(0),
	nNormalAIType(0),
	nRelation(0),
	byType(0),
	dwExValue(0),
	bRegnerate(1),
	pDetailInfo(NULL)
	{
		
	}
	~KS_REGENERATION_INFO()
	{
		if (pDetailInfo)
		{
			free(pDetailInfo);
		}
	}
	DWORD dwIdExpect;	//����ID(�ɽ��ʵ��ID����)
	DWORD dwFrames;		//����ʱ����(��λ��֡)
	DWORD dwTemplateId; //ģ��ID
	DWORD dwSceneId;	//��������ID
	INT nX;				//������X
	INT nY;				//������Y
	INT nZ;				//������Z
	INT nFaceDirection;	//��ʼ����
	INT nNormalAIType;	//Normal AI type
	INT nRelation;		//Relation
	BYTE byType;		//���������
	QString szNickName;
	DWORD dwExValue;
	BOOL bRegnerate;		// �Ƿ���Ҫ����
	CHAR szExInfo[MAX_NAME_LEN];
	void* pDetailInfo;	//ָ��malloc������ڴ棬����չ�õĸ�����Ϣָ�룬Ŀǰ����ȫ�����
};

typedef std::multimap<UINT32, KS_REGENERATION_INFO*> KRegenerationMMap;

typedef KDynReUseObjectPool<KS_REGENERATION_INFO> KRegenerationMemPool;

class KRegenerationMgr
{
private:
	KRegenerationMgr();
	~KRegenerationMgr();

public:
	//��ʱ��(ÿ֡����)
	BOOL	Activate();

	//ע�������¼�
	BOOL	Register(const KS_REGENERATION_INFO& sInfo);

	BOOL UnRegister(DWORD dwTemplateId, DWORD dwSceneId);

	//�����������
	VOID	Clear();

	//scenceж��ʱ�Ļص�(���scence_id���õĽӿڣ��ȱ����ӿڣ��������Ŀǰ�Ȳ���)
	BOOL	OnScenceRemove(DWORD dwScenceId){ QCONFIRM_RET_FALSE(FALSE); }

private:
	//ִ������
	BOOL	_ActionRegeneration(const KS_REGENERATION_INFO& sInfo);

	//NPC����
	BOOL	_ActionRegenerationNPC(const KS_REGENERATION_INFO& sInfo);

	//doodad����
	BOOL	_ActionRegenerationDoodad(const KS_REGENERATION_INFO& sInfo);

private:
	//���ݹ�����
	KRegenerationMMap		m_cDataMMap;//KEY:����������֡

	//֡������
	DWORD					m_dwFrameCounter;

	//��һ����Ҫ�����Ķ���Frame(Ч���Ż�����)
	DWORD					m_dwFirstRegenerationFrame;

	//�����
	KRegenerationMemPool*	m_pObjPool;

public:
	//��ȡʵ��
	static KRegenerationMgr& GetInstance(){ return ms_instance; }
private:
	//ʵ��
	static KRegenerationMgr ms_instance;
};

#endif

#endif //__KREGENERATION_MGR__H__

