
#ifndef __KLIBOFBPT_H__
#define __KLIBOFBPT_H__

#include "kbasproptbl.h"

class KItem;

//---------------------------------------------------------------------------
// �����ݽṹ���������ɫװ���ж���װ�ĳ���������������ϵģ�

typedef std::map<INT, INT>	KITEM_SUITE_COUNT_MAP;		// Key����װID, Value�ǳ��е���װ����

//---------------------------------------------------------------------------
// �����ݽṹ������¼��װ��������Ϣ

struct KSUITE_INFO
{
	KSUITE_INFO() : pInfo(NULL), nCount(0) {}
	CONST KBASICPROP_SUITEINFO*	pInfo;
	INT							nCount;
	std::vector<KITEM_INDEX>	aryPart[emEQUIPPOS_NUM];
};

//---------------------------------------------------------------------------
// KLibOfBPT

class KLibOfBPT
{
public:
	typedef std::map<INT, KSUITE_INFO>		KSuiteInfoMap;		// Suite Info Map �±���Suite ID
	typedef std::vector<KMAGIC_INDEX>		KMagicIndexVec;		// ħ������������


public:
	BOOL Init(INT nVersion);

	CONST KMagicIndexVec*		GetRandMAT(BOOL bDarkness, INT nEquipType) CONST;
	CONST KBASICPROP_BASEDATA*	GetBasicProp(CONST KITEM_INDEX &sIndex) CONST;

	CONST KSUITE_INFO*			GetGoldSuiteInfo(INT nSuiteId) CONST;
	CONST KSUITE_INFO*			GetGreenSuiteInfo(INT nSuiteId) CONST;
	CONST KBASICPROP_MAGICACTIVERULE*  GetActiveRuleInfo(INT nRuleId) CONST;

private:
	BOOL InitRandMAT(INT nVersion);
	VOID InitExternSetting(INT nVersion);					// ��ʼ���ⲿ����ĵ�������

	VOID InitSuiteInfo(INT nVersion);						// ������װ���ݣ�ͳ�ư�������װװ�����Լ��ܼ���
	template<typename KBPT_Equip, typename KBASICPROP_SUITE, typename KBPT_Info>
	VOID InitSuiteInfoT(KSuiteInfoMap &mapSuiteInfo, KBPT_Equip &cBPTEquip, KBPT_Info &cBPTInfo);

	CONST KBASICPROP_BASEDATA*	GetBasicPropStrictly(CONST KITEM_INDEX &sIndex) CONST;


public:
	KBPT_GE_Sword				m_cGE_Sword;
	KBPT_GE_Spear				m_cGE_Spear;
	KBPT_GE_Necklace			m_cGE_Necklace;						// ����
	KBPT_GE_Ring				m_cGE_Ring;							// ��ָ
	KBPT_GE_Pendant				m_cGE_Pendant;						// ����
	KBPT_GE_Head				m_cGE_Head;
	KBPT_GE_Armor				m_cGE_Armor;						// �·�
	KBPT_GE_Belt				m_cGE_Belt;							// ����
	KBPT_GE_Cloak				m_cGE_Cloak;						// ����
	KBPT_GE_Foot				m_cGE_Foot;							// Ь��
	
	KBPT_GE_Suit				m_cGE_Suit;							// ��װ����װ��
	KBPT_GE_Bottom				m_cGE_Bottom;						// �ŵף���װ��
	KBPT_GE_Back				m_cGE_Back;							// ������װ��

	// ��װ������
	KBPT_Medicine				m_cMedicine;						// ҩƷ
	KBPT_Script_Item			m_cScript;							// �����ű�����Ʒ
	KBPT_Upgrade_Material		m_cUpgradeMaterial;					// ��������
	KBPT_Box					m_cBox;
	KBPT_Stone					m_cStone;							// ��ʯ
	KBPT_Ride					m_cRide;							// ���￨Ƭ
	KBPT_Pet_Equip				m_cPetEquip;							// ����װ��
	KBPT_Pet_Item				m_cPetItem;								// ������ص���
	//KBPT_Skill_Item				m_cSkill;							// �������ܵ���Ʒ
	KBPT_Task_Quest				m_cQuest;							// ������Ʒ
	//KBPT_Extend_Bag				m_cExtBag;							// ��չ����
	//KBPT_Stuff_Item				m_cStuff;							// ����ܲ���
	//KBPT_Plan_Item				m_cPlan;							// ������䷽

	// �������
	KBPT_MagicAttrib			m_cMagicAttrib;						// ���ħ������
	KBPT_GoldInfo				m_cGoldInfo;						// �ƽ���װ��Ϣ
	KBPT_GreenInfo				m_cGreenInfo;						// ��ɫ��װ��Ϣ
	KBPT_EquipEffect			m_cEquipEffect;						// װ����Ч��Ϣ
	KBPT_MagicActiveRule		m_cMagicActiveRule;					// ħ�����Լ������

protected:
	KSuiteInfoMap				m_mapSIGold;						// �ƽ���װ��ʼ��Ϣ
	KSuiteInfoMap				m_mapSIGreen;						// ��ɫ��װ��ʼ��Ϣ

	KMagicIndexVec				m_RandMAT[emMATF_COUNT_BRIGHTDARK][emMATF_COUNT_EQUIPTYPE];
};

// -------------------------------------------------------------------------

#endif /* __KLIBOFBPT_H__ */
