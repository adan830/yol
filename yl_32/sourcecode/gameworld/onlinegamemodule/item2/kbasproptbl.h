
#ifndef	KBasPropTblH
#define	KBasPropTblH

#include "kitemdatadef.h"
#include "config/knpcdef.h"
#include <vector>

//------------------------------------------------------------------------

#define	SZBUFLEN_0					64							// ���͵��ַ�������������
#define	SZBUFLEN_1					256							// ���͵��ַ�������������

#define	KD_ITEM_SETTING_PATH		"\\setting\\item"

//------------------------------------------------------------------------

struct KBPT_RANGE												// ��¼����ֵ
{
	INT			nMin;
	INT			nMax;
};

struct KBPT_EQUIP_BASEATTR										// װ���Ļ�������
{
	INT			nAttrib;										// ��������ID
	KBPT_RANGE	aryRange[KD_MAGIC_VALUE_NUM];					// ȡֵ��Χ
};

struct KBPT_EQUIP_RIDEATTR
{
	INT			nAttrib;										// ��������ID
	KBPT_RANGE	aryRange[KD_RIDE_VALUE_NUM];					// ȡֵ��Χ  add by NiuNiu
};

struct KBPT_EQUIP_REQATTR										// װ������������
{
	KE_ITEM_REQUIREMENT	eType;									// ������������
	INT					nValue;									// ��ֵ
};

struct KBPT_EQUIP_RANDMA										// ����װ�����ħ������
{
	INT			nAttrib;										// ���ħ������ID
	KBPT_RANGE	aryRange[KD_MAGIC_VALUE_NUM];					// ħ������ȡֵ��Χ
};

struct KBPT_SUITE_RANDMA										// ��װ�����ħ������
{
	INT			nAttrib;										// ���ħ������ID
	KBPT_RANGE	aryRange[KD_MAGIC_VALUE_NUM];					// ħ������ȡֵ��Χ
};

struct KBPT_ENH_ATTR
{
	INT			nAttrib;										// ǿ������ħ������ID
	KBPT_RANGE	aryRange[KD_MAGIC_VALUE_NUM];					// ħ������ȡֵ��Χ
	KBPT_RANGE	aryGrow;										// ħ�����Գɳ�ֵ
};

struct KBPT_EQUIP_ENHMA											// װ����ǿ������ħ������
{
	INT			nTimes;											// ��������������ǿ������
	KBPT_ENH_ATTR aryAttr[emITEM_COUNT_ENHATTR];
};

struct KBPT_EQUIP_SUITEMA										// װ������װ����ħ������
{
	INT			nNum;											// ����������������װ����
	INT			nAttrib;										// ��װ����ħ������ID
	INT			aryValue[KD_MAGIC_VALUE_NUM];					// ħ������ȷ����ֵ
};

struct KBPT_MED_ATTRIB											// ����ҩƷ���Ե����ԣ���ֵ��ʱ��
{
	INT			nAttrib;										// ҩƷħ������ID
	INT			nValue;											// ҩƷħ��ֵ����
	INT			nTime;											// ҩƷħ������ʱ��
};

struct KBPT_STONE_ATTRIB										// ��ʯ�������ԣ�ħ�����Ժ�1-20������ֵ
{
	INT			nAttrib;										// ��ʯħ������ID
	INT			aryParam;										// ��ʯħ������ID��Ӧ�Ĳ�����Ŀǰֻ��1��
};

struct KBPT_EQUIP_ACTIVEMA : public KBPT_EQUIP_BASEATTR
{
	INT			nRuleId;										// �������ID����KBASICPROP_MAGICACTIVERULE�е�nRuleId��Ӧ
};

//------------------------------------------------------------------------
// ��Ʒ�������ԵĻ�������(�������� 14��)

struct KBASICPROP_BASEDATA
{
	CHAR		szName[SZBUFLEN_0];								// ����
	CHAR		szKind[SZBUFLEN_1];								// �Զ������
	CHAR		szClass[SZBUFLEN_0];							// CLASS
	INT			nItemGenre;										// ��������
	INT			nDetailType;									// �������
	INT			nParticular;									// ��ϸ���
	INT			nLevel;											// �ȼ�
	INT			nCanDestroy;									// �Ƿ�ɴݻ�
	INT			nPrice;											// �۸�
	BYTE		byCurrencyType;									// ��������
	INT			nQuality;										// ����Ʒ�ʣ���ɫ��
	INT			nBindType;										// ���߰���ʽ (KE_ITEM_BINDTYPEö��)
	BOOL		bValuable;										// �Ƿ���ص��� (��ˢ��дLOG)
	INT			aryExtParam[emITEM_COUNT_EXTPARAM];				// ��չ����
#ifndef GAME_SERVER	
	CHAR		szIconImage[SZBUFLEN_0];						// ����ͼ�궯���ļ���
	CHAR		szViewImage[SZBUFLEN_0];						// ����Ԥ�������ļ���
	CHAR		szIntro[SZBUFLEN_1*2];							// ˵������
	CHAR		szHelp[SZBUFLEN_1];								// ��������
#endif
};

//------------------------------------------------------------------------
// ���½ṹ����������װ�������

struct KBASICPROP_OTHER : KBASICPROP_BASEDATA
{
	INT			nStackMax;										// ���ŵ����ֵ (1��ʾ���ɵ���)
	INT			nReqLevel;										// ʹ�õ������輶��
	INT			nCDType;										// ����ʱ������
	BOOL		bShortcut;										// �Ƿ�ɷſ����
	CHAR		szForbidType[SZBUFLEN_0];						// ��������
};

typedef KBASICPROP_OTHER	KBASICPROP_SCRIPT;					// �ű���Ʒ����
typedef KBASICPROP_OTHER	KBASICPROP_SKILL;					// ������Ʒ����
typedef KBASICPROP_OTHER	KBASICPROP_QUEST;					// ������Ʒ����
typedef KBASICPROP_OTHER	KBASICPROP_STUFF;					// ����ܲ�������
typedef KBASICPROP_OTHER	KBASICPROP_PLAN;					// ������䷽����

struct KBASICPROP_EXTBAG : KBASICPROP_OTHER				// ��չ��������
{
	INT			nPos;
};

struct KBASICPROP_MEDICINE : KBASICPROP_OTHER					// ҩƷ��������
{
	INT			nCanUseInBZone;									// �ܷ��ڿ��ս��ʹ��
	KBPT_MED_ATTRIB		aryAttrib[emMEDICINE_COUNT_ATTRIB];		// ҩƷ������
};

struct KBASICPROP_STONE : KBASICPROP_BASEDATA					// ��ʯ��������
{
	INT			nColor;											// ��ʯ��ɫ
	INT			nStackMax;										// ���ŵ����ֵ (1��ʾ���ɵ���)
	INT			nReqLevel;										// ����ȼ�����
	INT			nEquipLevel;									// װ���ȼ�����
	INT			nStoneType;										// ��ʯ����
	KBPT_STONE_ATTRIB	aryAttrib[emSTONE_COUNT_ATTRIB];		// ��ʯ��3��ħ������
};

//------------------------------------------------------------------------
// ���½ṹ��������װ���ĳ�ʼ����

struct KUPGRADE_NEEDITEM
{
	INT nGenre;
	INT nDetail;
	INT nParticular;
	INT nAmount;
};

// modified by dengyong 20100429, ��װ�����Ͻ���ʱ��
struct KBASICPROP_EQUIPMENT : KBASICPROP_BASEDATA
{
	KBPT_EQUIP_BASEATTR	aryBasic[emITEM_COUNT_BASE];			// ��������
	KBPT_EQUIP_REQATTR	aryReq[emITEM_COUNT_REQ];				// ��������
	KBPT_EQUIP_ENHMA	aryStr[emITEM_COUNT_STRENGTHEN];		// װ�����켤������
	KBPT_RANGE			arySlot;								// ��ʯ��
	/*
	INT					nResMale;								// ����װ�����
	INT					nResFemale;								// Ů��װ�����
	*/
	INT					nPandent1;								// ������
	INT					nPandent2;								// �ұ����
	INT					nCategory;								// װ�����
	INT					nFightPower;							// װ��ԭʼս����
	INT					nReqLevel;								// װ������ȼ�
	INT					aryExPandents[emITEM_COUNT_EX_PENDANT];	// װ������Ҽ�
	KUPGRADE_NEEDITEM	aryNeedItems[emITEM_COUNT_UPGRADE];		// װ�������������
};

typedef KBASICPROP_EQUIPMENT	KBASICPROP_GENERALEQUIP;		// ��ͨװ������

//------------------------------------------------------------------------

// ���½ṹ����������������������
struct KBASICPROP_WEAPON : KBASICPROP_EQUIPMENT
{
	KBPT_EQUIP_BASEATTR	aryDmg;									// ��������������ֵ������
};

struct KBASICPROP_SUIT : KBASICPROP_BASEDATA
{
	KBPT_EQUIP_BASEATTR	aryBasic[emITEM_COUNT_BASE];			// ��������
	INT					nPandent1;								// ������
	INT					nPandent2;								// �ұ����
	INT					nReqLevel;								// װ������ȼ�
	INT					aryExPandents[emITEM_COUNT_SUIT_EX_PENDANT];			// ����Ҽ�
};

//------------------------------------------------------------------------
// ���½ṹ����������װ�ĳ�ʼ����

struct KBASICPROP_PURPLEEQUIP : KBASICPROP_EQUIPMENT
{
	KMAGIC_INDEX		aryRand[emITEM_COUNT_RANDOM];			// ���ħ������������
};

//------------------------------------------------------------------------
// ���½ṹ���������ƶ���װ����װ���ĳ�ʼ����
struct KBASICPROP_GREENSUITE : KBASICPROP_PURPLEEQUIP 
{
	INT					nSuiteID;
};


//------------------------------------------------------------------------
// ���½ṹ����������װ�ĳ�ʼ����

struct KBASICPROP_EQUIP_SUITE : KBASICPROP_EQUIPMENT
{
	KBPT_SUITE_RANDMA	aryRand[emITEM_COUNT_RANDOM];			// ���ħ�����Ա�
	INT					nSuiteID;								// ������װ��ID������0��Ч
};

typedef KBASICPROP_EQUIP_SUITE	KBASICPROP_GOLDEQUIP;			// �ƽ�װ������

//------------------------------------------------------------------------
// ���½ṹ�������������ļ��и�����ħ������

struct KBASICPROP_MAGICATTRIB
{
	CHAR				szSuffix[SZBUFLEN_0];					// ��׺��
	INT					nLevel;									// ħ�����Եȼ�
	BOOL				bDarkness;								// �Ƿ�����
	//INT					nSeries;								// ����Ҫ��
	INT					aryDropRate[equip_detailnum];			// ���ָ���
	INT					nValue;									// ��ֵ��
	KBPT_EQUIP_RANDMA	sMA;									// ���Ĳ���
};

//------------------------------------------------------------------------
// ���½ṹ�������������ļ��и�����ħ�����Լ������
struct KBASICPROP_MAGICACTIVERULE
{
	INT		nRuleId;				// �������к�
	INT		nSkillId;				// ����BUFF�ļ���ID
	INT		nBeginLevel;			// ������Ч�ȼ�,��ʼֵ
	INT		nEndLevel;				// ������Ч�ȼ�,��ĩֵ
	CHAR	szDesc[SZBUFLEN_1];		// ������Ϣ
};

//------------------------------------------------------------------------
// ���½ṹ���ڱ�����װ��Ϣ

struct KBASICPROP_SUITEINFO
{
	INT					nSuiteID;								// ��װID
	KBPT_EQUIP_SUITEMA	arySuite[emITEM_COUNT_SUITE];			// ��װ��������
#ifndef GAME_SERVER
	CHAR				szName[SZBUFLEN_0];						// ��װ����
	CHAR				aryName[emEQUIPPOS_NUM][SZBUFLEN_0];	// ������װ���������֣�����Ϊ�մ���
#endif
};

//------------------------------------------------------------------------
// ���½ṹ��������װ����Ч����
struct KBASICPROP_EQUIPEFFECT
{
	//INT					nSeries;								// ��������
	INT					nCategory;								// װ�����
	INT					anEquipEffectRes[1/*series_num*/];			// ��ͬ���е���Ч��ԴId
};


//------------------------------------------------------------------------
// KBasicPropertyTable

class KBasicPropertyTable										// ��д: BPT������������
{

public:

	KBasicPropertyTable();
	~KBasicPropertyTable();

	virtual BOOL Load(INT nVersion);        					// ��tabfile�ж�����ʼ����ֵ, �������Ա�

protected:

	LPBYTE m_pBuf;												// ָ�����Ա�������ָ��
																// ���Ա���һ���ṹ����,
																// ��������������������
	INT		m_nNumOfEntries;									// ���Ա��ж���������
    INT     m_nSizeOfEntry;										// ÿ�����ݵĴ�С(���ṹ�Ĵ�С)
	CHAR	m_szTabFile[MAX_PATH];								// tabfile���ļ���

	VOID	GetMemory(VOID);
	VOID	ReleaseMemory(VOID);
	VOID	SetCount(INT);
	virtual	VOID LoadRecord(INT i, QTabFile *pTF) = 0;

};

//------------------------------------------------------------------------
// KBPT_BaseT	������ģ��

template<typename KINDEXT, typename KBASICPROPT>
class KBPT_BaseT : public KBasicPropertyTable
{

public:

	typedef std::map<KINDEXT, KBASICPROPT*> KINDEX_MAP;

	KINDEX_MAP& GetIndexMap(VOID) { return m_mapIndex; }
	CONST KBASICPROPT* GetData(CONST KINDEXT& rcIndex) CONST
	{
		typename KINDEX_MAP::const_iterator it = m_mapIndex.find(rcIndex);
		if (it == m_mapIndex.end())
			return	NULL;
		return	it->second;
	}

protected:

	KINDEX_MAP	m_mapIndex;

	explicit KBPT_BaseT(PCSTR pszTabFile)
	{
		m_nSizeOfEntry = sizeof(KBASICPROPT);
		::strncpy(m_szTabFile, pszTabFile, sizeof(m_szTabFile));
		m_szTabFile[sizeof(m_szTabFile) - 1] = 0;
	}

	CONST KBASICPROPT* GetRecord(INT nIndex) CONST
	{
		if (nIndex >= 0 && nIndex < m_nNumOfEntries)
			return	(((KBASICPROPT*)m_pBuf) + nIndex);
		return	NULL;
	}

};

//------------------------------------------------------------------------
// KBPT_BaseT��ʵ������

// �����ļ�·��
#define _KD_TABFILE_GE_SWORD			"equip\\sword"
#define _KD_TABFILE_GE_SPEAR			"equip\\spear"
#define	_KD_TABFILE_GE_NECKLACE			"equip\\necklace"
#define	_KD_TABFILE_GE_RING				"equip\\ring"
#define	_KD_TABFILE_GE_PENDANT			"equip\\pendant"
#define	_KD_TABFILE_GE_HEAD				"equip\\head"
#define	_KD_TABFILE_GE_ARMOR			"equip\\armor"
#define	_KD_TABFILE_GE_BELT				"equip\\belt"
#define	_KD_TABFILE_GE_CLOAK			"equip\\cloak"
#define	_KD_TABFILE_GE_FOOT				"equip\\foot"

#define	_KD_TABFILE_GE_SUIT				"equip\\suit"
#define	_KD_TABFILE_GE_BOTTOM			"equip\\bottom"
#define	_KD_TABFILE_GE_BACK				"equip\\back"


#define _KD_TABFILE_STONE				"other\\gem"		// ��ʯ

#define _KD_TABFILE_GE_GARMENT			"equip\\general\\garment"		// ����
#define _KD_TABFILE_GE_OUTHAT			"equip\\general\\outhat"		// ��ñ
#define	_KD_TABFILE_PE_MELEEWEAPON		"equip\\purple\\meleeweapon"
#define	_KD_TABFILE_PE_RANGEWEAPON		"equip\\purple\\rangeweapon"
#define	_KD_TABFILE_PE_ARMOR			"equip\\purple\\armor"
#define	_KD_TABFILE_PE_HELM				"equip\\purple\\helm"
#define	_KD_TABFILE_PE_BOOTS			"equip\\purple\\boots"
#define	_KD_TABFILE_PE_BELT				"equip\\purple\\belt"
#define	_KD_TABFILE_PE_AMULET			"equip\\purple\\amulet"
#define	_KD_TABFILE_PE_RING				"equip\\purple\\ring"
#define	_KD_TABFILE_PE_NECKLACE			"equip\\purple\\necklace"
#define	_KD_TABFILE_PE_CUFF				"equip\\purple\\cuff"
#define	_KD_TABFILE_PE_PENDANT			"equip\\purple\\pendant"
#define	_KD_TABFILE_MEDICINE			"other\\medicine"
#define	_KD_TABFILE_SCRIPT				"other\\scriptitem"
#define _KD_TABFILE_UPGRADE_MATERIAL	"material\\upgrade_material"
#define _KD_TABFILE_BOX					"other\\box"
#define _KD_TABFILE_PET_EQUIP			"pet\\equip"
#define _KD_TABFILE_PET_ITEM			"pet\\other"
#define	_KD_TABFILE_RIDE				"other\\rideitem"
#define _KD_TABFILE_SKILL				"other\\skillitem"
#define _KD_TABFILE_QUEST				"other\\taskitem"
#define _KD_TABFILE_EXTBAG				"other\\extbag"
#define _KD_TABFILE_STUFF				"other\\stuffitem"
#define _KD_TABFILE_PLAN				"other\\planitem"
#define	_KD_TABFILE_GOLDEQUIP			"equip\\goldequip"
#define	_KD_TABFILE_GREENEQUIP			"equip\\greenequip"
#define	_KD_TABFILE_MAGICATTRIB			"magic\\magicattrib"
#define _KD_TABFILE_MAGICACTIVERULE		"magic\\magicactiverule"
#define _KD_TABFILE_GOLDINFO			"equip\\goldinfo"
#define _KD_TABFILE_GREENINFO			"equip\\greeninfo"
#define _KD_TABFILE_EQUIPEFFECT			"equip\\effect"

#define _DECLARE_BPTCLASS(CLASSNAME, INDEX, BASICPROP, TABFILE, LOADRECORDPROC)			\
	class CLASSNAME : public KBPT_BaseT<INDEX, BASICPROP>								\
	{																					\
	public:																				\
		CLASSNAME() : KBPT_BaseT<INDEX, BASICPROP>(TABFILE) {}							\
	protected:																			\
		virtual	VOID LoadRecord(INT i, QTabFile* pTF)									\
		{																				\
			extern VOID LOADRECORDPROC(INT, QTabFile*, BASICPROP*, KINDEX_MAP&);		\
			LOADRECORDPROC(i, pTF, (BASICPROP*)(m_pBuf), m_mapIndex);					\
		}																				\
	}


// ��ͨװ��
_DECLARE_BPTCLASS(KBPT_GE_Sword,		KITEM_INDEX,	KBASICPROP_GENERALEQUIP,	_KD_TABFILE_GE_SWORD,		_BPT_GeneralEquip_LoadRecord);		// ��
_DECLARE_BPTCLASS(KBPT_GE_Spear,		KITEM_INDEX,	KBASICPROP_GENERALEQUIP,	_KD_TABFILE_GE_SPEAR,		_BPT_GeneralEquip_LoadRecord);		// ǹ
_DECLARE_BPTCLASS(KBPT_GE_Necklace,		KITEM_INDEX,	KBASICPROP_GENERALEQUIP,	_KD_TABFILE_GE_NECKLACE,	_BPT_GeneralEquip_LoadRecord);		// ����
_DECLARE_BPTCLASS(KBPT_GE_Ring,			KITEM_INDEX,	KBASICPROP_GENERALEQUIP,	_KD_TABFILE_GE_RING,		_BPT_GeneralEquip_LoadRecord);		// ��ָ
_DECLARE_BPTCLASS(KBPT_GE_Pendant,		KITEM_INDEX,	KBASICPROP_GENERALEQUIP,	_KD_TABFILE_GE_PENDANT,		_BPT_GeneralEquip_LoadRecord);		// ����
_DECLARE_BPTCLASS(KBPT_GE_Head,			KITEM_INDEX,	KBASICPROP_GENERALEQUIP,	_KD_TABFILE_GE_HEAD,		_BPT_GeneralEquip_LoadRecord);		// ͷ��
_DECLARE_BPTCLASS(KBPT_GE_Armor,		KITEM_INDEX,	KBASICPROP_GENERALEQUIP,	_KD_TABFILE_GE_ARMOR,		_BPT_GeneralEquip_LoadRecord);		// �·�
_DECLARE_BPTCLASS(KBPT_GE_Belt,			KITEM_INDEX,	KBASICPROP_GENERALEQUIP,	_KD_TABFILE_GE_BELT,		_BPT_GeneralEquip_LoadRecord);		// ����
_DECLARE_BPTCLASS(KBPT_GE_Cloak,		KITEM_INDEX,	KBASICPROP_GENERALEQUIP,	_KD_TABFILE_GE_CLOAK,		_BPT_GeneralEquip_LoadRecord);		// ����
_DECLARE_BPTCLASS(KBPT_GE_Foot,			KITEM_INDEX,	KBASICPROP_GENERALEQUIP,	_KD_TABFILE_GE_FOOT,		_BPT_GeneralEquip_LoadRecord);		// Ь��


_DECLARE_BPTCLASS(KBPT_GE_Suit,			KITEM_INDEX,	KBASICPROP_SUIT,	_KD_TABFILE_GE_SUIT,		_BPT_Suit_LoadRecord);		// ��װ����װ��
_DECLARE_BPTCLASS(KBPT_GE_Bottom,		KITEM_INDEX,	KBASICPROP_SUIT,	_KD_TABFILE_GE_BOTTOM,		_BPT_Suit_LoadRecord);		// �ŵף���װ��
_DECLARE_BPTCLASS(KBPT_GE_Back,			KITEM_INDEX,	KBASICPROP_SUIT,	_KD_TABFILE_GE_BACK,		_BPT_Suit_LoadRecord);		// ������װ��


// ��װ������
_DECLARE_BPTCLASS(KBPT_Medicine,		KITEM_INDEX,	KBASICPROP_MEDICINE,		_KD_TABFILE_MEDICINE,		_BPT_Medicine_LoadRecord);		// ҩƷ
_DECLARE_BPTCLASS(KBPT_Stone,			KITEM_INDEX,	KBASICPROP_STONE,			_KD_TABFILE_STONE,			_BPT_Stone_LoadRecord);			// ��ʯ
_DECLARE_BPTCLASS(KBPT_Script_Item,		KITEM_INDEX,	KBASICPROP_SCRIPT,			_KD_TABFILE_SCRIPT,			_BPT_Script_LoadRecord);		// �ű�����
_DECLARE_BPTCLASS(KBPT_Pet_Equip,		KITEM_INDEX,	KBASICPROP_SCRIPT,			_KD_TABFILE_PET_EQUIP,		_BPT_Script_LoadRecord);		// ����װ��
_DECLARE_BPTCLASS(KBPT_Pet_Item,		KITEM_INDEX,	KBASICPROP_SCRIPT,			_KD_TABFILE_PET_ITEM,		_BPT_Script_LoadRecord);		// �������
_DECLARE_BPTCLASS(KBPT_Ride,			KITEM_INDEX,	KBASICPROP_SCRIPT,			_KD_TABFILE_RIDE,			_BPT_Ride_LoadRecord);			// ���￨ 
_DECLARE_BPTCLASS(KBPT_Skill_Item,		KITEM_INDEX,	KBASICPROP_SKILL,			_KD_TABFILE_SKILL,			_BPT_Skill_LoadRecord);			// ���ܵ���
_DECLARE_BPTCLASS(KBPT_Task_Quest,		KITEM_INDEX,	KBASICPROP_QUEST,			_KD_TABFILE_QUEST,			_BPT_Quest_LoadRecord);			// �������
_DECLARE_BPTCLASS(KBPT_Extend_Bag,		KITEM_INDEX,	KBASICPROP_EXTBAG,			_KD_TABFILE_EXTBAG,			_BPT_ExtBag_LoadRecord);		// ��չ����
_DECLARE_BPTCLASS(KBPT_Stuff_Item,		KITEM_INDEX,	KBASICPROP_STUFF,			_KD_TABFILE_STUFF,			_BPT_Stuff_LoadRecord);			// ����ܲ���
_DECLARE_BPTCLASS(KBPT_Plan_Item,		KITEM_INDEX,	KBASICPROP_PLAN,			_KD_TABFILE_PLAN,			_BPT_Plan_LoadRecord);			// ������䷽
_DECLARE_BPTCLASS(KBPT_Upgrade_Material, KITEM_INDEX,	KBASICPROP_SCRIPT,			_KD_TABFILE_UPGRADE_MATERIAL, _BPT_Script_LoadRecord);		// ����װ������
_DECLARE_BPTCLASS(KBPT_Box,				KITEM_INDEX,	KBASICPROP_SCRIPT,			_KD_TABFILE_BOX,			_BPT_Script_LoadRecord);		// ����

// �������
_DECLARE_BPTCLASS(KBPT_MagicAttrib,		KMAGIC_INDEX,	KBASICPROP_MAGICATTRIB,		_KD_TABFILE_MAGICATTRIB,	_BPT_MagicAttrib_LoadRecord);	// ��ɫװ��ħ�����Ա�
_DECLARE_BPTCLASS(KBPT_GoldInfo,		INT,			KBASICPROP_SUITEINFO,		_KD_TABFILE_GOLDINFO,		_BPT_SuiteInfo_LoadRecord);		// �ƽ�װ����װ���Ʊ�
_DECLARE_BPTCLASS(KBPT_GreenInfo,		INT,			KBASICPROP_SUITEINFO,		_KD_TABFILE_GREENINFO,		_BPT_SuiteInfo_LoadRecord);		// ��ɫװ����װ���Ʊ�
_DECLARE_BPTCLASS(KBPT_EquipEffect,		INT,			KBASICPROP_EQUIPEFFECT,		_KD_TABFILE_EQUIPEFFECT,	_BPT_EquipEffect_LoadRecord);	// װ����Ч��
_DECLARE_BPTCLASS(KBPT_MagicActiveRule,	INT,			KBASICPROP_MAGICACTIVERULE,	_KD_TABFILE_MAGICACTIVERULE,_BPT_MagicActiveRule_LoadReord);// ħ�����Լ�������

#undef _DECLARE_BPTCLASS

#undef _KD_TABFILE_GE_MELEEWEAPON
#undef _KD_TABFILE_GE_RANGEWEAPON
#undef _KD_TABFILE_GE_ARMOR
#undef _KD_TABFILE_GE_HELM
#undef _KD_TABFILE_GE_BOOT
#undef _KD_TABFILE_GE_BELT
#undef _KD_TABFILE_GE_AMULET
#undef _KD_TABFILE_GE_RING
#undef _KD_TABFILE_GE_NECKLACE
#undef _KD_TABFILE_GE_BRACERS
#undef _KD_TABFILE_GE_PENDANT
#undef _KD_TABFILE_PE_MELEEWEAPON
#undef _KD_TABFILE_PE_RANGEWEAPON
#undef _KD_TABFILE_PE_ARMOR
#undef _KD_TABFILE_PE_HELM
#undef _KD_TABFILE_PE_BOOTS
#undef _KD_TABFILE_PE_BELT
#undef _KD_TABFILE_PE_AMULET
#undef _KD_TABFILE_PE_RING
#undef _KD_TABFILE_PE_NECKLACE
#undef _KD_TABFILE_PE_CUFF
#undef _KD_TABFILE_PE_PENDANT
#undef _KD_TABFILE_PE_BOTTOM


#undef _KD_TABFILE_MEDICINE
#undef _KD_TABFILE_SCRIPT
#undef _KD_TABFILE_SKILL
#undef _KD_TABFILE_QUEST
#undef _KD_TABFILE_EXTBAG
#undef _KD_TABFILE_STUFF
#undef _KD_TABFILE_PLAN
#undef _KD_TABFILE_GOLDEQUIP
#undef _KD_TABFILE_GREENEQUIP
#undef _KD_TABFILE_MAGICATTRIB
#undef _KD_TABFILE_GOLDINFO
#undef _KD_TABFILE_GREENINFO
#undef _KD_TABFILE_EQUIPEFFECT

//------------------------------------------------------------------------

#endif		// #ifndef KBasPropTblH
