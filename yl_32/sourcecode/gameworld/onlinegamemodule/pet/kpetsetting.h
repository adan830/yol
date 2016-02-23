/* -------------------------------------------------------------------------
//	�ļ���		��	kpetsetting.h
//	������		��	zhaoyu
//	����ʱ��	��	2013-2-25
//	��������	��	�������ö�ȡ
// -----------------------------------------------------------------------*/

#ifndef kpetsetting_h__
#define kpetsetting_h__

#include "petdef.h"
#include "onlinegamemodule/item2/itemdef.h"

class ITabFile;

struct KPET_MAGIC_ATTR
{
	INT nAttrib;
	INT nValue;
};

typedef std::map<INT, INT> KMAP_PET_ATTR_SCORE;
typedef std::map<INT, INT> KMAP_RIDE_ATTR_SCORE;

// Petģ��
struct KPetTemplate
{
	BOOL Init(ITabFile* piFile, INT nRow);

	INT		m_nType;									// ����ID����ӦNpc�����NpcId
	CHAR	m_szName[MAX_NAME_LEN];						// ����									
	INT		m_nHungry;									// ս��ʱʳ������
	INT     nQuality;		 // ����Ʒ��
	INT		m_PetSkill1;
	INT     m_PetSkill2;
	INT     m_PetNpcId;				// ��Ӧ�ľ�̬NPCID
};

struct KPetSkillTemplate
{
	BOOL Init(ITabFile* piFile, INT nRow);

	INT		m_nTemplateId;
	CHAR	m_szSkillName[MAX_NAME_LEN];
	INT		m_nSkillCD;								// ����CDʱ��
	INT     m_nSkillType;                           // ��������
	BOOL	m_bToSelf;
	INT		m_arySkillId[emPET_COUNT_SKILL];
	INT		m_aryBuffId[emPET_COUNT_SKILL];		    // 1��5����buffid
};

struct KRideRankTemplate
{
	BOOL Init(ITabFile* piFile, INT nRow);

	INT m_nGrowId;

	KPET_MAGIC_ATTR m_aryRankAttr[emRIDE_COUNT_BASE];	// ��������
	KPET_MAGIC_ATTR m_aryRideAttr[emRIDE_COUNT_RIDE];	// �������
};

// ����ģ��
struct KRideTemplate
{
	BOOL Init(ITabFile* piFile, INT nRow);

	INT m_nGenre;
	INT m_nDetail;
	INT m_nParticular;
	INT m_nLevel;			// ����Ľ���

	CHAR m_szName[MAX_NAME_LEN];						// ����

	INT m_nRepresentId;			// ����ID
	INT m_nMaxLevel;		// ������
	INT m_nQuality;			// Ʒ��
	INT m_nRankId;
	INT m_nRankConsume;		// ������һ�����ĵĻû���
};

class KPetSetting
{
	typedef std::map<INT, KPetTemplate*> PET_TEMPLATE_MAP;
	typedef std::map<INT, KPetSkillTemplate*> PET_SKILL_TEMPLATE_MAP;

	typedef std::map<KITEM_INDEX, KRideTemplate*> RIDE_TEMPLATE_MAP;
	typedef std::map<INT, KRideRankTemplate*> RIDE_RANK_TEMPLATE_MAP;
	
public:
	KPetSetting();
	~KPetSetting();

	BOOL Init();
	BOOL UnInit();

	KPetTemplate* GetPetTemplate(INT nType);
	INT GetPetNpcIdByType(INT nType);  // ��ȡ����NPD
	KPetSkillTemplate* GetPetSkillTemplate(INT nSkillId);

	INT GetBuffIdBySkillId(INT nSkillId);

	KRideTemplate* GetRideTemplate(KITEM_INDEX sIndex);
	KRideRankTemplate* GetRideRankTemplate(INT nGrowId);

	INT GetPetAttribScore(INT nAttrib);
	INT GetRideAttribScore(INT nAttrib);

private:
	PET_TEMPLATE_MAP m_mapPetTemplates;
	PET_SKILL_TEMPLATE_MAP m_mapPetSkillTemplates;

	RIDE_TEMPLATE_MAP m_mapRideTemplates;
	RIDE_RANK_TEMPLATE_MAP m_mapRideRankTemplates;

	KMAP_PET_ATTR_SCORE m_mapPetAttrScore;
	KMAP_RIDE_ATTR_SCORE m_mapRideAttrScore;
	
};

extern KPetSetting g_cPetSetting;

#endif // petsetting_h__
