
#ifndef itemdef_h__
#define itemdef_h__

#include "onlinegameworld/kbaseprotocol.h"

#define F_LOG_PATH_ROOT			"\\log"
#define F_ItemSet_0				        "itemset"
#define		KD_STR_F_ITEM_CDTYPE		"\\setting\\item\\cdtype.txt"
#define		KD_STR_F_EQUIP_SCORE		"\\setting\\item\\equipscore.txt"
#define		KD_STR_F_STONE_SCORE		"\\setting\\item\\stonescore.txt"

#define		EQUIP_ENH_MODULE_NAME		"equip_enhance"
#define		EQUIP_APPEND_MODULE_NAME	"equip_refine"

// ռ��32λ��genre-8λ��detailtype/particular-12λ
#define MAKE_ITEM_TYPEID(genre, detailtype, particular)						\
	((genre << 24) + (detailtype << 12) + (particular))

#define		KD_ITEM_RECYCLE_TIME_OUT			15			// �ع���Ʒ��ʱ������� 15��
#define	KD_NPCRES_DEFAULT	0

#define KD_EQUIP_MAX_LEVEL	7	// װ�����ȼ�

#pragma pack(1)

struct TDBItemData
{
	BYTE 	byVersion;					// �汾
	WORD	wGenre;						// ����
	WORD	wDetailType;				// С��
	WORD	wParticularType;			// СС��
	BYTE	byLevel;					// �ȼ�
	DWORD	dwGenTime;					// ����ʱ��
	DWORD 	dwRandSeed;					// �������
	DWORD	dwRandSeedEx;				// �������EX
	WORD	wStackCount;				// ������Ŀ
	BYTE	byStateFlags;				// ״̬��־����0λ��������־��1��ʾ�����У���1λ����������1��ʾ���У���2λ��0��ʾ��1��ʾ������Ӧ��dwPrice����3λ������־��1��ʾ���װ���ǴӼ���ֿ������
	BYTE	byPlaceRoom;				// ������λ
	BYTE	byPlaceX;					// ������λX����
	BYTE	byPlaceY;					// ������λY����
	BYTE	byCustomType;				// �Զ����ַ�������
	BYTE	abyCustom[32];				// �Զ����ַ���
	// TODO: ���԰�������Ķ�����ΪUnion����ͬ������Ʒ�ɲ�ͬ����
	BYTE	byEnhance;					// ǿ����������װ����		
	BYTE	byTimeoutType;				// ��ʱ���ͣ���KE_ITEM_TIMEOUTTYPE��
	DWORD	dwTimeout;					// ��ʱʱ�䣨������byTimeoutType������
	GUID	sGuid;						// ��ƷID
	DWORD	dwPrice;					// ��̯�۸�,���������Ч��0��ʾ��Ϊ����״̬��,����״̬��byStateFlags�ĵڶ�λȷ���� 
	DWORD	dwCount;					// ��̯�չ�������������0��ʾû������״̬
	DWORD	dwBuyPrice;					// ����ʱ�۸��������Ʒ��
	DWORD	arydwStoneInfo[2];			// װ����Ƕ�ı�ʯ��Ϣ
	WORD	arywAppendData[10];			// ��������
	WORD	arywSaveAppendData[10];		// ����ĸ�������
	BYTE	aryAppendQuality[5];
	BYTE	arySaveAppendQuality[5];
	DWORD	dwKinRepteroryId;			// added by liyun ��¼���װ�������뵽�ĸ�����ֿ����ˣ���װ������ҵļ��屳������Ч
	DWORD	arydwExtParam[3];
};

#pragma pack()

enum KE_ITEM_ROOM
{
	emROOM_NONE	= -1,				// ��
	emROOM_EQUIP,					// װ���ŵ�
	emROOM_EQUIPEX,					// װ���л��ռ�
	emROOM_MAINBAG,					// ������
	emROOM_EXTBAGBAR,				// ��չ����������
	emROOM_EXTBAG,					// ��չ����
	emROOM_MAIL,					// �ʼ�����				// ���ڵ��ʼ��ߵ�����һ������
	emROOM_KIN,                     // ���屳��
	emROOM_NUM,
};

// ����Ʒ�ʣ���ɫ��
enum KE_ITEM_QUALITY
{
	emQUALITY_WHITE = 1,			// ��ɫ
	emQUALITY_BLUE,					// ��ɫ
	emQUALITY_PURPLE,				// ��ɫ
	emQUALITY_ORANGE,				// ��ɫ
};

enum KE_EQUIP_POSITION
{
	emEQUIPPOS_SWORD,
	emEQUIPPOS_SPEAR,
	emEQUIPPOS_NECKLACE,			// ����
	emEQUIPPOS_RING,				// ��ָ
	emEQUIPPOS_PENDANT,				// ��׹
	emEQUIPPOS_HEAD,
	emEQUIPPOS_ARMOR,				// �·�
	emEQUIPPOS_BELT,				// ����
	emEQUIPPOS_CLOAK,				// ����
	emEQUIPPOS_FOOT,				// Ь��

	emEQUIPPOS_SUIT,				// ��װ
	emEQUIPPOS_BOTTOM,				// ����
	emEQUIPPOS_BACK,				// ��
	
	emEQUIPPOS_NUM,
};

enum KE_EQUIPEX_POSITION
{
	emEQUIPEXPOS_SWORD,
	emEQUIPEXPOS_SPEAR,
	emEQUIPEXPOS_NECKLACE,			// ����
	emEQUIPEXPOS_RING,				// ��ָ
	emEQUIPEXPOS_PENDANT,				// ��׹
	emEQUIPEXPOS_HEAD,
	emEQUIPEXPOS_ARMOR,				// �·�
	emEQUIPEXPOS_BELT,				// ����
	emEQUIPEXPOS_CLOAK,				// ����
	emEQUIPEXPOS_FOOT,				// Ь��

	emEQUIPEXPOS_SUIT,				// ��װ
	emEQUIPEXPOS_BOTTOM,				// ����
	emEQUIPEXPOS_BACK,				// ��

	emEQUIPEXPOS_NUM,
};

enum KE_EXTBAG_POSITION
{
	emEXTBAGPOS_BAG1,				// ��չ����1
	emEXTBAGPOS_BAG2,				// ��չ����2
	emEXTBAGPOS_BAG3,				// ��չ����3
	emEXTBAGPOS_NUM,				// ��չ��������
};

enum KE_EXTREP_POSITION
{
	emEXTREPPOS_REP1,				// ��չ������1
	emEXTREPPOS_REP2,				// ��չ������2
	emEXTREPPOS_REP3,				// ��չ������3
	emEXTREPPOS_REP4,				// ��չ������4
	emEXTREPPOS_REP5,				// ��չ������5
	emEXTREPPOS_NUM,
};


// ��ROOM�ߴ綨��
#define KD_ROOM_EQUIP_WIDTH				emEQUIPPOS_NUM
#define KD_ROOM_EQUIP_HEIGHT			1
#define KD_ROOM_EQUIPEX_WIDTH			emEQUIPEXPOS_NUM
#define KD_ROOM_EQUIPEX_HEIGHT			1
#define	KD_ROOM_MAINBAG_WIDTH			7
#define	KD_ROOM_MAINBAG_HEIGHT			5
#define KD_ROOM_EXTBAGBAR_WIDTH			emEXTBAGPOS_NUM
#define KD_ROOM_EXTBAGBAR_HEIGHT		1
#define KD_ROOM_EXTBAG_WIDTH			1			
#define KD_ROOM_EXTBAG_HEIGHT			1
#define KD_ROOM_EXTBAG1_MAX_WIDTH		133					// 42 * 3 + 7
#define KD_ROOM_EXTBAG1_MAX_HEIGHT		1
#define KD_ROOM_MAIL_WIDTH				1
#define	KD_ROOM_MAIL_HEIGHT				1
#define KD_ROOM_KIN_WIDTH               9
#define KD_ROOM_KIN_HEIGHT              1

// ROOM�ܴ�С
#define KD_ROOM_EQUIP_SIZE				(KD_ROOM_EQUIP_WIDTH * KD_ROOM_EQUIP_HEIGHT)
#define KD_ROOM_EQUIPEX_SIZE			(KD_ROOM_EQUIPEX_WIDTH * KD_ROOM_EQUIPEX_HEIGHT)
#define	KD_ROOM_MAINBAG_SIZE			(KD_ROOM_MAINBAG_WIDTH * KD_ROOM_MAINBAG_HEIGHT)
#define KD_ROOM_EXTBAGBAR_SIZE			(KD_ROOM_EXTBAGBAR_WIDTH * KD_ROOM_EXTBAGBAR_HEIGHT)
#define KD_ROOM_EXTBAG_SIZE				(KD_ROOM_EXTBAG_WIDTH * KD_ROOM_EXTBAG_HEIGHT)
#define KD_ROOM_MAIL_SIZE				(KD_ROOM_MAIL_WIDTH * KD_ROOM_MAIL_HEIGHT)
#define KD_ROOM_KIN_SIZE                (KD_ROOM_KIN_WIDTH * KD_ROOM_KIN_HEIGHT)
#define KD_ROOM_EXTBAG1_SIZE		    (KD_ROOM_EXTBAG1_MAX_WIDTH * KD_ROOM_EXTBAG1_MAX_HEIGHT)
#define KD_ROOM_BAGSUM_SIZE             (KD_ROOM_MAINBAG_SIZE + KD_ROOM_EXTBAG1_SIZE)

#define	KD_PLAYER_ITEM_RESERVED			32

#define KD_MAX_PLAYER_ITEM				(KD_ROOM_EQUIP_SIZE + KD_ROOM_EQUIPEX_SIZE + KD_ROOM_MAINBAG_SIZE + \
	KD_ROOM_EXTBAGBAR_SIZE + emEXTBAGPOS_NUM * KD_ROOM_EXTBAG_SIZE + \
	emEXTREPPOS_NUM * KD_PLAYER_ITEM_RESERVED + KD_ROOM_EQUIPEX_SIZE + KD_ROOM_KIN_SIZE )			// �浵��������

// ��չ���������ͺųߴ�
#define	KD_ROOM_EXTBAG_WIDTH_4CELL		4			// 4�񱳰����
#define	KD_ROOM_EXTBAG_WIDTH_6CELL		6			// 6�񱳰����
#define	KD_ROOM_EXTBAG_WIDTH_8CELL		4			// 8�񱳰����
#define	KD_ROOM_EXTBAG_WIDTH_10CELL		5			// 10�񱳰����
#define	KD_ROOM_EXTBAG_WIDTH_12CELL		6			// 12�񱳰����
#define	KD_ROOM_EXTBAG_WIDTH_15CELL		5			// 15�񱳰����
#define	KD_ROOM_EXTBAG_WIDTH_18CELL		6			// 18�񱳰����
#define	KD_ROOM_EXTBAG_WIDTH_20CELL		5			// 20�񱳰����
#define	KD_ROOM_EXTBAG_WIDTH_24CELL		6			// 24�񱳰����
#define	KD_ROOM_EXTBAG_HEIGHT_4CELL		1			// 4�񱳰��߶�
#define	KD_ROOM_EXTBAG_HEIGHT_6CELL		1			// 6�񱳰��߶�
#define	KD_ROOM_EXTBAG_HEIGHT_8CELL		2			// 8�񱳰��߶�
#define	KD_ROOM_EXTBAG_HEIGHT_10CELL	2			// 10�񱳰��߶�
#define	KD_ROOM_EXTBAG_HEIGHT_12CELL	2			// 12�񱳰��߶�
#define	KD_ROOM_EXTBAG_HEIGHT_15CELL	3			// 15�񱳰��߶�
#define	KD_ROOM_EXTBAG_HEIGHT_18CELL	3			// 18�񱳰��߶�
#define	KD_ROOM_EXTBAG_HEIGHT_20CELL	4			// 20�񱳰��߶�
#define	KD_ROOM_EXTBAG_HEIGHT_24CELL	4			// 24�񱳰��߶�

enum KE_PURSE_TYPE						// Ǯ������
{
	emPURSE_CASH,						// �ֽ���������
	emPURSE_SAVE,						// �������䣩
	emPURSE_NUM,
};

enum KE_ENHANCE_MODE
{
	emENHANCE_ONCE = 1,
	emENHANCE_ALL,	// һ��ǿ��
};

struct KITEM_POS						// ��������λ��
{
	KE_ITEM_ROOM	eRoom;				// �ռ�
	INT				nX;					// X����
	INT				nY;					// Y����
	KITEM_POS() : eRoom(emROOM_NONE), nX(0), nY(0) {}

	bool operator == (CONST KITEM_POS &sPos) CONST
	{
		return eRoom == sPos.eRoom && nX == sPos.nX && nY == sPos.nY;
	}

	bool operator != (CONST KITEM_POS &sPos) CONST
	{
		return !operator == (sPos);
	}
};

#define KD_MAGIC_INVALID		0			// ��Ч��ħ������ID
#define KD_MAGIC_VALUE_NUM		2			// ħ�����Բ�������
#define KD_RIDE_VALUE_NUM		2			// �������Բ�������

//	ħ������
struct KMagicAttrib
{
	INT				nAttribType;					// ��������
	INT				nValue[KD_MAGIC_VALUE_NUM];		// ���Բ���

	KMagicAttrib(INT nType = KD_MAGIC_INVALID, INT nValue1 = 0, INT nValue2 = 0, INT nValue3 = 0)
		:nAttribType(nType)
	{
		nValue[0] = nValue1;
		nValue[1] = nValue2;
		//nValue[2] = nValue3;
	}
};



struct KITEM_INDEX								// ��ʶ���ñ��е�һ����Ʒ��һ�У�
{
	INT		nGenre;				// 8Bits
	INT		nDetailType;		// 12Bits
	INT		nParticular;		// 12Bits
	INT		nLevel;

	bool operator < (CONST KITEM_INDEX &sIndex) CONST
	{
		if (nGenre != sIndex.nGenre)
			return	nGenre < sIndex.nGenre;
		if (nDetailType != sIndex.nDetailType)
			return	nDetailType < sIndex.nDetailType;
		if (nParticular != sIndex.nParticular)
			return	nParticular < sIndex.nParticular;
		return	nLevel < sIndex.nLevel;
	}

	bool operator == (CONST KITEM_INDEX &sIndex) CONST
	{
		return	nGenre == sIndex.nGenre && nDetailType == sIndex.nDetailType &&
			nParticular == sIndex.nParticular && nLevel == sIndex.nLevel;
	}

	bool operator != (CONST KITEM_INDEX &sIndex) CONST
	{
		return !operator == (sIndex);
	}
};

struct KPos
{
	INT nX;
	INT nY;
};

enum KE_EQUIP_WEAPON_CATEGORY	// �������ͣ������ڼ��ܶ��������ж�
{
	emKEQUIP_WEAPON_CATEGORY_ALL		= 0,
	emKEQUIP_WEAPON_CATEGORY_UNLIMITED	= 0,

	emKEQUIP_WEAPON_CATEGORY_HAND			= 0,	// ����
	emKEQUIP_WEAPON_CATEGORY_SWORD			= 1,	// ��
	emKEQUIP_WEAPON_CATEGORY_BOOK			= 2,	// ��
	emKEQUIP_WEAPON_CATEGORY_DOUBLE_SWORD		= 3,	// ˫�ֽ�
	emKEQUIP_WEAPON_CATEGORY_SHIELD			= 4,	// ����
	emKEQUIP_WEAPON_CATEGORY_DOUBLE_BLUNT		= 5,	// ˫����
	emKEQUIP_WEAPON_CATEGORY_BLUNT			= 6,	// ������˫�ֳ֣�
	emKEQUIP_WEAPON_CATEGORY_DOUBLE_KNIFE		= 7,	// ˫ذ��
	emKEQUIP_WEAPON_CATEGORY_CROSSBOW		= 8,	// ���

	emKEQUIP_WEAPON_CATEGORY_NUM			= 9,
};

// ��Ʒ��ʱ����
enum KE_ITEM_TIMEOUTTYPE
{
	emKITEM_TIMEOUTTYPE_ABSOLUTE,		// ���Գ�ʱʱ�� ��λΪ��
	emKITEM_TIMEOUTTYPE_RELATIVE,		// ��Գ�ʱʱ�� ��λΪ��Ϸ֡��
	emKITEM_TIMEOUTTYPE_COUNT,
};

struct KITEM_TIMEOUT
{
	KE_ITEM_TIMEOUTTYPE		emType;
	DWORD					dwTimeout;
};

enum KE_ITEMDATA_FLAG
{
	emKITEMDATA_FLAG_NULL	= 0,		// 
	emKITEMDATA_FLAG_IBSHOP = 0x1,		// �Ƿ��������Ʒ
};

struct KLISTITEM
{
	KLISTITEM() : nIdx(0)
	{
		sPos.eRoom	= emROOM_NONE;
		sPos.nX		= 0;
		sPos.nY		= 0;
	}
	INT			nIdx;
	KITEM_POS	sPos;
	WORD		wRecycleDate;	// ����ع��ռ����ڣ��ع��ռ���Ч��
};

enum KE_REPAIR_TYPE			// ������������
{
	emREPAIR_ERROR,
	emREPAIR_COMMON,		// ��ͨ����
	emREPAIR_SPECIAL,		// ��������
	emREPAIR_ITEM,			// ʹ�õ�������
};

// Npc����˳��ö�٣���������������ļ���Ӧ��
enum KE_NPCRES_PART
{
	emNPCRES_PART_HEAD,				// ͷ������װ��
	emNPCRES_PART_SHOULDER,			// �磨��װ��
	emNPCRES_PART_BACK,				// �磨��װ��
	emNPCRES_PART_BOTTOM,			// �ţ���װ��
	emNPCRES_PART_WEAPON,			// ����
	emNPCRES_PART_BOTTEM,			// �ŵ�
	emNPCRES_PART_BODY,				// �·�
	emNPCRES_PART_CLOAK,			// ����
	emNPCRES_PART_SUIT,				// ��װ

	emNPCRES_PART_COUNT
};

enum KE_STONE_COUNT_ATTR_CONST					// ��ʯ������Ŀ����
{
	emSTONE_MIX_MAX_COUNT = 3,					// ��ʯ�ϳ����ϳ�����
	emSTONE_MAX_LV = 20,						// ��ʯ���ȼ�
	emSTONE_COUNT_ATTRIB = 3,					// ��ʯ����ħ�����Ը���
	emSTONE_MAX_SLOT = 3,						// װ�����ʯ�׸���

	emSTONE_LOCKED_ID = 255,					// ��ס��״̬id
};

enum KE_REFINE_COUNT_CONST
{
	emREFINE_MAX_LEVEL = 9,		// ϴ�����9���ȼ�
};

enum KE_MEDICINE_COUNT_ATTR_CONST
{
	emMEDICINE_COUNT_ATTRIB = 3,				// ҩƷ����ħ�����Ը���
};

class KRandom			// �������������
{

public:

	explicit KRandom(UINT uRandSeed = 42) : m_uRandSeed(uRandSeed) {}

	UINT GetSeed(VOID) CONST		{ return m_uRandSeed; }
	VOID SetSeed(UINT uRandSeed)	{ m_uRandSeed = uRandSeed; }
	UINT Random(VOID)				{ return m_uRandSeed = m_uRandSeed * 3877 + 29573; }
	INT  Random(INT nMin, INT nMax)	
	{
		UINT uRandom = Random();
		if (nMax - nMin >= 0)
		{
			return uRandom % (nMax - nMin + 1) + nMin;
		}
		else
			return nMin;
	}

private:

	UINT				m_uRandSeed;
};

class KRandomEx
{

public:

	explicit KRandomEx(UINT uRandSeed = 42) : m_uRandSeedEx(uRandSeed) {}

	UINT GetSeed(VOID) CONST		{ return m_uRandSeedEx; }
	VOID SetSeed(UINT uRandSeed)	{ m_uRandSeedEx = uRandSeed; }
	UINT Random(VOID)				{ return m_uRandSeedEx = m_uRandSeedEx * 3877 + 29573; }
	INT  Random(INT nMin, INT nMax)	
	{
		UINT uRandom = Random();
		if (nMax - nMin >= 0)
			return uRandom % (nMax - nMin + 1) + nMin;
		else
			return nMin;
	}

private:

	UINT				m_uRandSeedEx;
};

static inline INT GetRandomNumber(INT nMin, INT nMax)
{
	return g_Random(nMax - nMin + 1) + nMin;
}

//////////////////////////////////////////////////////////////////////////

enum KS2C_ITEM_PROTOCOL
{
	s2c_syncitem,
	s2c_removeitem,
	s2c_syncmoney,
	s2c_syncjbcoin,				// ͬ�������
	s2c_npcattrib,				// ͬ��NPCħ�����Ե��ͻ���

	s2c_itemride,
	s2c_switchitem,
	s2c_openrepository,			// �򿪴�����
	s2c_sync_ext_repo_state,
	s2c_viewequip,

	s2c_useitem_result,			// ʹ�õ��߽��
	s2c_switchitem_end,			// ���߽�������
	s2c_arrange_end,			// �������
	s2c_sellitems_end,			// �������߽���

	s2c_prepare_itemrepair,		// ֪ͨ�ͻ���׼����������
	s2c_enhance_result,			// ǿ�����
	s2c_itemcountsync,

	s2c_waititemstate,			// ���õȴ���ȡ��Ʒ����״̬
	s2c_stone_mix_result,		// ��ʯ�ϳɽ��

	s2c_end,
};

enum KC2S_ITEM_PROTOCOL
{
	c2s_switchitem,         
	c2s_playeruseitem,      //ʹ����Ʒ
	c2s_resizeextbag,       //��������
	c2s_arrangebag,			// ��������
	//c2s_playerpickupitem,
	c2s_playersellitem,
	c2s_playerbuyitem,
	c2s_playerthrowawayitem,
	c2s_viewequip,
	c2s_switchequip,			// װ���л�
	c2s_repairitem,
	c2s_itemride,				// ������
	c2s_applyenhance,			// װ��ǿ������
	c2s_upgrade,
	c2s_refine,					// ϴ��
	c2s_save_appendattr,		// ���渽������
	c2s_applybreakup,			// װ�����

	c2s_closerepository,		// �رմ�����
	c2s_splititem,				// ���߲������
	c2s_playeruseitem_with_param,	// ������ʹ�õ���
	c2s_stone_mix,				// ��ʯ�ϳ�
	c2s_stone_mount,			// ��ʯ��Ƕ
	c2s_stone_remove,			// ��ʯ���
	c2s_stone_punch,			// ���
	c2s_equip_rerand,			// װ������
	c2s_equip_identify,			// װ������

	c2s_reapply_pendant_request,

	c2s_end,
};

#pragma pack(1)

struct KPROTO_ITEMPOS
{
	BYTE	byRoom;
	BYTE	byX;
	BYTE	byY;
};

struct KPLAYER_USEITEM : KPTC_HEADER<c2s_playeruseitem>		// �������Ҽ����ʹ����Ʒ
{
	BYTE	byRoom;			// ��Ʒλ��
	BYTE	byX;			// ��Ʒx����
	BYTE	byY;			// ��Ʒy����
};

struct KPLAYER_RESIZE_EXTBAG : KPTC_HEADER<c2s_resizeextbag>
{
	BYTE		byRoom;
	BYTE		byDestWidth;
	BYTE		byDestHeight;
};

struct KPLAYER_USEITEM_RESULT : KPTC_HEADER<s2c_useitem_result>		// ʹ�õ��߽��
{
	DWORD	dwID;			// ����ID
	BYTE	bResult;		// ���
};

struct KITEM_REPAIR_SYNC : KLENPTC_HEADER<c2s_repairitem>			// ����
{
	BYTE	byType;
	BYTE	byCount;
	DWORD	dwUseItemID;
	DWORD	dwItemID[1];
};

struct KITEM_C2S_SPLIT_ITEM : KLENPTC_HEADER<c2s_splititem>			// ���
{
	DWORD dwItemId;
	BYTE bySplitCount;	// ��ָ���
};

struct KSYNC_PREPARE_ITEMREPAIR : KPTC_HEADER<s2c_prepare_itemrepair>	// ֪ͨ�ͻ���ʹ�õ��߶�װ����������
{
	DWORD	dwUseItemID;	// ��������ʱ������ƷID
};

struct KAPPEND_VIEW_INFO
{
	BYTE byAttrib;
	WORD wValue;
};

struct KVIEWITEMINFO
{
	DWORD	dwID;
	BYTE	byGenre;
	WORD	wDetail;
	WORD	wParticular;
	DWORD	dwLevel;
	DWORD	dwRandomSeed;
	DWORD	dwRandomSeedEx;
	WORD	wCount;
	BYTE	byEnhance;

	BYTE	byBaseAttrib;		// ��������
	WORD	wBaseValue;			// ��������ֵ
	WORD	wBaseNextValue;		// ��һ����������ֵ
	WORD	wEnhValue;			// ǿ������ֵ
	WORD	wEnhNextValue;		// ��һ��ǿ������ֵ
	DWORD	dwEnhanceCost;		// ǿ������
	KAPPEND_VIEW_INFO aryAppendInfo[5];	// ��������
	KAPPEND_VIEW_INFO arySaveAppendInfo[5];		// �ѱ���ĸ�������
	BYTE	aryAppendQuality[5];
	BYTE	arySaveAppendQuality[5];
	BYTE	byStoneInfo[6];			// ��ʯ��Ϣ

	BYTE	bBind;		// TRUE, FALSE
	BYTE	byTimeoutType;		// ��ʱʱ�����ͣ�0Ϊ����ʱ�䣬1Ϊ���ʱ�䣨֡���� (KE_ITEM_TIMEOUTTYPE, 2)

	DWORD	dwTimeout;				// ��ʱʱ��
	DWORD	dwFightScore;			// ս����
};

struct KITEM_EXTINFO
{
	BYTE			byRoom;				// �ռ�
	BYTE			byX;				// X����
	BYTE			byY;				// Y����
};
struct KITEM_SYNC : KLENPTC_HEADER<s2c_syncitem>, KITEM_EXTINFO, KVIEWITEMINFO
{
};

struct KITEM_C2S_SWITCH_SYNC : KPTC_HEADER<c2s_switchitem>
{
	BYTE	byPickRoom;
	BYTE	byPickX;
	BYTE	byPickY;
	BYTE	byDropRoom;
	BYTE	byDropX;
	BYTE	byDropY;
};

struct KITEM_C2S_ARRANGE_BAG : KPTC_HEADER<c2s_arrangebag>
{

};

struct KITEM_S2C_SWITCH_SYNC : KPTC_HEADER<s2c_switchitem>
{
	BYTE	bSuccess;
	BYTE	byPickRoom;
	BYTE	byPickX;
	BYTE	byPickY;
	BYTE	byDropRoom;
	BYTE	byDropX;
	BYTE	byDropY;
};

struct KITEM_C2S_VIEW_EQUIP: KPTC_HEADER<c2s_viewequip>
{
	DWORD m_dwPlayerIdx;
};

struct KITEM_REMOVE_SYNC : KPTC_HEADER<s2c_removeitem>
{
	DWORD	dwID;				// ��Ʒ��ID
};

struct KITEM_COUNT_SYNC : KPTC_HEADER<s2c_itemcountsync>
{
	DWORD	dwId;
	WORD	wCount;
};

struct KITEM_C2S_ENHANCE_APPLY_SYNC : KPTC_HEADER<c2s_applyenhance>
{
	DWORD	dwEquipId;
	BYTE	byMode;
};

struct KITEM_C2S_UPGRADE_APPLY_SYNC : KPTC_HEADER<c2s_upgrade>
{
	DWORD	dwEquipId;
};

struct KITEM_C2S_REFINE_APPLY_SYNC : KPTC_HEADER<c2s_refine>
{
	DWORD dwEquipId;
	BYTE byMoneyType;

	BYTE aryLock[5];
};

struct KITEM_C2S_SAVE_REFINE_ATTR : KPTC_HEADER<c2s_save_appendattr>
{
	DWORD dwEquipId;
	BYTE bySaveOriginal;
};

struct KITEM_C2S_EQUIP_IDENTIFY : KPTC_HEADER<c2s_equip_identify>
{
	DWORD	dwEquipId;
};

struct KITEM_C2S_STONE_MIX_SYNC : KLENPTC_HEADER<c2s_stone_mix>
{
	BYTE byStoneCount;
	DWORD adwStoneId[emSTONE_MIX_MAX_COUNT];
};

struct KITEM_C2S_SELL_ITEMS : KLENPTC_HEADER<c2s_playersellitem>
{
	BYTE byItemCount;
	DWORD adwItemIds[0];
};

struct KITEM_C2S_EQUIP_RERAND_SYNC : KPTC_HEADER<c2s_equip_rerand>
{
	DWORD	dwEquipId;
	BYTE	byMode;				// ����ģʽ,0=��ͨ����,1=һ������
	BYTE	byNeedScore;		// ��Ҫ�ķ�����ģʽΪ1����Ҫ
};

struct KITEM_C2S_STONE_MOUNT_SYNC : KLENPTC_HEADER<c2s_stone_mount>
{
	DWORD	dwEquipId;
	DWORD	adwStoneId[0];
};

struct KITEM_C2S_STONE_REMOVE_SYNC : KLENPTC_HEADER<c2s_stone_remove>
{
	DWORD	dwEquipId;
	BYTE	abySlot[0];
};

struct KITEM_C2S_STONE_PUNCH : KPTC_HEADER<c2s_stone_punch>
{
	DWORD dwEquipId;
	BYTE byPos;	// ��0��ʼ
};

struct KITEM_S2C_ENHANCE_RESULT_SYNC : KPTC_HEADER<s2c_enhance_result>
{
	BYTE	byMode;
	BYTE	byResult;		// -1:�޲�����0:ǿ��/����ʧ�ܣ�1:ǿ��/����ɹ�
};

struct KITEM_S2C_SWITCH_END : KPTC_HEADER<s2c_switchitem_end>
{
};

struct KITEM_S2C_ARRANGE_END : KPTC_HEADER<s2c_arrange_end>
{

};

struct KITEM_S2C_SELLITEMS_END : KPTC_HEADER<s2c_sellitems_end>
{

};

struct KITEM_THROWAWAY_SYNC : KPTC_HEADER<c2s_playerthrowawayitem>
{
	DWORD	dwId;
};

struct KSWITCH_EQUIP_PROTOCOL : KLENPTC_HEADER<c2s_switchequip>
{
	struct KPAIR
	{
		BYTE	byEquipPos;
		BYTE	byEquipExPos;
	};
	BYTE		byCount;		// �˴��л�װ��������Ҳ����sPairs����Ĵ�С��
	KPAIR		asPair[0];		// ������С����
};	// �л����װ����һ���л������

struct S2C_OPEN_REPOSITORY : KPTC_HEADER<s2c_openrepository>
{
};
struct C2S_CLOSE_REPOSITORY : KPTC_HEADER<c2s_closerepository>
{
};

struct C2S_REAPPLY_PENDANTS_REQUEST : KPTC_HEADER<c2s_reapply_pendant_request>
{

};

struct S2C_SYNC_EXT_REPO_STATE : KPTC_HEADER<s2c_sync_ext_repo_state>
{
	BYTE		byState;
};

struct KPLAYER_EQUIPVIEW
{
	//DWORD				dwNpcID;
	// 32Bits
	DWORD				bySex		:2;
	DWORD            	byPKValue	:4;	// (KD_MAX_PKVALUE, 10)
	DWORD				byFaction	:4;	// (KD_MAX_FACTION, 12)
	DWORD				nPortrait	:14;
	DWORD				byLevel		:8;	// ����

	CHAR				szRoleName[_NAME_LEN];		// �������
	BYTE				byItemCount;
	CHAR				szBuffer[1];
};
struct KVIEW_EQUIP_SYNC : KLENPTC_HEADER<s2c_viewequip>
{
	KPLAYER_EQUIPVIEW sView;
	BYTE byData[]; // KVIEWITEMINFO[]
};

#pragma pack()

#endif // itemdef_h__
