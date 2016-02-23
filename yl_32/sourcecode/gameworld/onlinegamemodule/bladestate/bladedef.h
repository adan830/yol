#ifndef _BLADEDEF_H__
#define _BLADEDEF_H__

// ����֮��ļӳ�����
struct KBLADE_ATTR
{
	INT nLife;
	INT nMana;
	INT nAttack;
	INT nDef;
	INT nHit;
	INT nMiss;
	INT nCrit;
	INT nResist;
};

// �����������Լӳɰٷֱ�
struct KBLADE_ATTR_PERCENT
{
	INT nLifeP;
	INT nManaP;
	INT nAttackP;
	INT nDefP;
	INT nHitP;
	INT nMissP;
	INT nCritP;
	INT nResistP;
};

struct KBLADE_PENDENTS
{
	INT nBodyPendant;
	INT nWeaponPendant;
	INT nHatPendant;
	INT nHeadPendant;
	INT nBackPendant;
};

#define BLADE_STATE_TIME (20)		// ����ʱ��(s)

#define BLADE_SPEED_ADD (10)		// �����ٶȼӳ�

#define BLADE_OPEN_LEVEL (16)		// 16������


#define BLADE_MALE_BODY_PENDANT (92)		// ����������Ҽ�
#define BLADE_FEMALE_BODY_PENDANT (93)		// ����Ů����Ҽ�
#define BLADE_MALE_HEAD_PENDANT (1562)
#define BLADE_FEMALE_HEAD_PENDANT (1563)
#define BLADE_MALE_BACK_PENDANT (1564)
#define BLADE_FEMALE_BACK_PENDANT (1565)
#define BLADE_FEMALE_WEAPON_PENDANT (1561)
#define BLADE_MALE_WEAPON_PENDANT (1566)


#endif // _BLADEDEF_H__