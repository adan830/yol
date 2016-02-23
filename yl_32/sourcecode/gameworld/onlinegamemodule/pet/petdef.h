#ifndef PETDEF_H__
#define PETDEF_H__

#define PET_TABLE_FILE "\\setting\\pet\\pet.txt"
#define PET_SKILL_TABLE_FILE "\\setting\\pet\\petskill.txt"
#define PET_ATTR_SCORE_FILE "\\setting\\pet\\petattrscore.txt"
#define RIDE_ATTR_SCORE_FILE "\\setting\\pet\\rideattrscore.txt"

#define RIDE_TABLE_FILE "\\setting\\pet\\ride.txt"
#define RIDE_TABLE_RANK_FILE "\\setting\\pet\\riderank.txt"

#define PET_BASE_MODULE_NAME "pet_base"
#define PET_LEVEL_MODULE_NAME "pet_level"		// ����ȼ�����ģ������
#define PET_TACTIC_MODULE_NAME "pet_tactic"     //
#define PET_UPRANK_MODULE_NAME "pet_uprank"		//����
#define PET_BLADE_MODULE_NAME "pet_blade"		// ���������󷨼ӳɰٷֱ�

#define KD_PET_TACTIC_NUM 7		// ��λ����

// ��ҳ�������С�����ֵ
#define KD_MIN_PET_COUNT 6
#define KD_MAX_PET_COUNT 30

#define KD_PET_INIT_LEVEL 1
#define KD_PET_INIT_RANKLEVEL 1

#define KD_PET_MAX_QUALITY 6

// �ͷż���������
#define KD_PET_CAST_DISTANCE (10 * CELL_LENGTH)

#define KD_PET_HUNGRY_MAX 100	// ��ʳ������

#define KD_RIDE_HUNGRY_MAX 100	// ���ﱥʳ������

#define KD_PET_ABRADE_SECOND (6000)			// ÿ5���Ӵ���һ�γ��ﱥʳ�Ⱥ����ܶ�

#define KD_RIDE_ABRADE_SECOND (300)		

#define PET_POOL_MAX_COUNT	20000	// ��ǰ������������ҳ�������

#define RIDE_POOL_MAX_COUNT	3000		// ��ǰ���������������������

#define PET_CAST_SKILL_FRAME 1	// ÿ0.5��ʩ��һ�μ���

#define PET_INIT_EQUIP_SLOT_NUM 3  // ��ʼ��3�����ò�λ

enum KE_PET_FIGHT_STATE  // �����ս״̬
{
	emPET_STATE_REST = 0,	// ��Ϣ
	emPET_STATE_FIGHT = 1,  // ��ս
};

enum KE_RIDE_STATE
{
	emRIDE_STATE_REST = 0,		// ��Ϣ
	emRIDE_STATE_UP = 1,		// ���
};

enum KE_PET_CHARACTER	// �����Ը�
{
	emPET_CHARACTER_LIFE = 1,	// ����
	emPET_CHARACTER_ATTACK = 2,	// ����
	emPET_CHARACTER_HIT	= 3,	// �ᶨ
	emPET_CHARACTER_CRIT = 4,	// ����
	emPET_CHARACTER_RESIST = 5,	// ��˳
	emPET_CHARACTER_DEF = 6,	// ����
	emPET_CHARACTER_DODGE = 7,	// ����
	
};

enum KE_PET_COUNT_ATTR_CONST					// ����������Ŀ����
{
	emPET_COUNT_BASE		= 7,				// �������Ե���Ŀ
	emPET_MAX_SKILL_LEVEL   = 5,				// �������ȼ�
	emPET_COUNT_SKILL		= 2,				// ����ܲ۸���
	emPET_COUNT_VALUE		= 3,				// ������ֵ����
	emPET_COUNT_EQUIP		= 7,				// ���װ���۸���
};

enum KE_RIDE_COUNT_ATTR_CONST				// ����������Ŀ����
{
	emRIDE_COUNT_BASE		= 6,		// �������������Ե���Ŀ
	emRIDE_COUNT_RIDE		= 2,		// ������������Ŀ
};

// ����������Զ���˳��
enum QE_PET_BASE_ATTR
{
	emPET_ATTR_LIFE,
	emPET_ATTR_ATTACK,
	emPET_ATTR_HIT,
	emPET_ATTR_CRIT,  // ����
	emPET_ATTR_RESIST,  // ����
	emPET_ATTR_DEFENSE,
	emPET_ATTR_DODGE,
};

enum QE_PET_SKILL_TYPE
{
	emPET_NORMAL_ATTACK,    // ��ͨ����
	emPET_BUFF_ADD_BLOOD,   // ��Ѫbuff����
	emPET_BUFF_SUB_BLOOD,   // ��Ѫbuff����
	emPET_BUFF_ADD_ATTACK,  // �ӹ�buff����
	emPET_BUFF_SUB_DEFENCE, // ����buff����
};

enum QE_PET_SKILLBOOK
{
	emPET_SKILL_BOOK_G = 24,
	emPET_SKILL_BOOK_D = 8,
	emPET_SKILL_BOOK_P = 1
};

enum QE_PET_UPRANKBALL
{
	emPET_UPRANKBALL_G = 24,
	emPET_UPRANKBALL_D = 2,
	emPET_UPRANKBALL_P = 8
};

//enum KE_PET_SKILL_ID
//{
//	emPET_SKILL_LL = 1,		// ����
//	emPET_SKILL_TB = 2,		// ����
//	emPET_SKILL_WR = 3,		// ����
//	emPET_SKILL_EC = 4,		// ����
//	emPET_SKILL_CR = 5,		// ����
//};

//CONST KE_PET_SKILL_ID g_aePetSkill[] =
//{
//	emPET_SKILL_LL,
//	emPET_SKILL_TB,
//	emPET_SKILL_WR,
//	emPET_SKILL_EC,
//	emPET_SKILL_CR,
//};

struct KBASEATTR
{
	LONGLONG nAttrib;
	LONGLONG nValue;
};

struct KPETEQUIP
{
	INT   nParticular;
	WORD  wNumberIndex; // װ���������Ե���ֵ����
	BYTE  byLock;       // ��װ�����Ƿ�����
};

struct KSKILL_DATA
{
	INT		nBuffId;

	INT nSkillLevel;        // ���ܵȼ�
	INT nSkillType;         // ��������
	INT nSkillValues[emPET_COUNT_VALUE * 2];    // ���������ֵ�����ݼ������ʹ���ͬ������
	INT nCDTime;			// CDʱ��
	INT nCurrentCDTime;		// ��ǰcdʱ��
	BOOL bStartCalcCD;		// �Ƿ�ʼ����CDʱ��
	BOOL bToSelf;		// �Ƿ�Ӹ��Լ�
};

struct KPET_INDEX								// ��ʶ���ñ��е�һ������
{
	INT		nType;				// ����ID����ӦNpc�����NpcId
	INT		nQuality;		// Ʒ��
	INT		nCharacter;		// �Ը�

	bool operator < (CONST KPET_INDEX &sIndex) CONST
	{
		if (nType != sIndex.nType)
			return	nType < sIndex.nType;
		if (nQuality != sIndex.nQuality)
			return	nQuality < sIndex.nQuality;
		return	nCharacter < sIndex.nCharacter;
	}

	bool operator == (CONST KPET_INDEX &sIndex) CONST
	{
		return	nType == sIndex.nType && nQuality == sIndex.nQuality &&
			nCharacter == sIndex.nCharacter;
	}

	bool operator != (CONST KPET_INDEX &sIndex) CONST
	{
		return !operator == (sIndex);
	}
};

struct QPET_CARD  // ���ɿ�Ƭ��Ϣ
{
    int nPetId;       // ����ID
	int nPetNature;   // ���ɷ�ϵ
};

class KPetRandom			// �������������
{

public:

	explicit KPetRandom(UINT uRandSeed = 42) : m_uRandSeed(uRandSeed) {}

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

#endif // petdef_h__