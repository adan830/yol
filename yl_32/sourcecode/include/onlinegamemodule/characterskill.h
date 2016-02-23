/********************************************************************
	created:	2012/05/28  9:12
	filename: 	characterskill.h
	author:		zhangjunjie
*********************************************************************/
#ifndef __CHARACTER_SKILL_H__
#define __CHARACTER_SKILL_H__

#include "onlinegameworld/kcharacterctrlbase.h"
#include "config/kcharacterdef.h"

#include "onlinegamemodule/luacharacterskill.h"
#include "../onlinegamemodule/fightskilldef.h"
//#include "onlinegameworld/kcharacter.h"
//#include "onlinegameworld/kplayermgr.h"
#include <map>

class FightSkill;
struct QDelaySkillData;

enum SKILL_SLOT_DEF
{
	PASSIVE_SKILL_SLOT = 6,
};

#pragma pack(push, 1)
struct SkillSaveData
{
	SkillSaveData(INT nSkillId = 0,INT nCDTime = 0,INT nCurrentCDTime = 0, INT nSkillLevel=1)
		:nSkillId(nSkillId), nCDTime(nCDTime), nCurrentCDTime(nCurrentCDTime), nSkillLevel(nSkillLevel)
	{}
	INT nSkillId;
	INT nCDTime;			// CDʱ��
	INT nCurrentCDTime;		// ��ǰcdʱ��
	INT nSkillLevel;	// ���ܵȼ�
};

// ���ܵȼ�����
struct SkillLevelDbSaveData
{
	SkillLevelDbSaveData(INT nSkillTemplateId = 0, INT nGrade = 0)
		:nSkillTemplateId(nSkillTemplateId), nGrade(nGrade)
	{}
	INT nSkillTemplateId;				// ��λ
	INT nGrade;							// �ȼ�
};
#pragma pack(pop)


class CharacterSkill: public KCharacterCtrlBase
{
public:
	static CONST INT COMMON_SKILL_COOLDOWN = 11; // ����CD����
	//static CONST INT SKILL_CHANGE_RUNE_COOLDOWN = 16; // �����л���ȴCD

	struct SKILLDATA
	{
		SKILLDATA(INT nSkillId = 0,INT nSkillLevel=1, INT nCDTime = 0,INT nCurrentCDTime = 0)
			:nSkillId(nSkillId), nSkillLevel(nSkillLevel), nCDTime(nCDTime), nCurrentCDTime(nCurrentCDTime),pSkill(NULL),bStartCalcCD(FALSE)
		{}
		INT nSkillId;
		FightSkill* pSkill;		// ����
		INT nCDTime;			// CDʱ��
		INT nCurrentCDTime;		// ��ǰcdʱ��
		BOOL bStartCalcCD;		// �Ƿ�ʼ����CDʱ��
		
		INT nSkillLevel;			// ���ܵȼ�

		INT nSlotId;  // �����ID�ͷ���ID
		//INT nRuneId;
	};

	typedef std::map<INT,SKILLDATA*> SKILLDATAMAP;
	typedef std::map<INT, INT> FACTIONSKILLMAP;  // SkillId -> Level

	CharacterSkill(KCharacter& rcPlayer);

	~CharacterSkill();

	virtual BOOL Active();

	VOID ForwardFrame(INT nFrame);

	INT GetCastingSkill();

	enum { emKCtrlId = emKCHARACTER_CTRL_FIGHTSKILL };

	BOOL m_bDbLoaded;    // �ж��Ƿ��Ѿ���ȡ���ݿ�~~~ �ս�����Ϸʱ SetLevel������ReloadPlayerSkills, ��SetLevel��DbLoad���ȣ����Իᵼ�»�û��ȡ���＼�ܵȼ����ݾʹ��ݴ�����
protected:
	virtual BOOL Init();
	virtual BOOL UnInit();	
	virtual BOOL OnLogin();
	virtual BOOL OnLogout()	{return TRUE;}
	// ����
	virtual BOOL OnDbLoad(LPCBYTE pData, SIZE_T uSize);
	// ����
	virtual BOOL OnDbSave(LPBYTE pBuffer, SIZE_T uBuffSize, SIZE_T& uUsedSize);

	virtual BOOL OnClientReady();

public:

	// ��ȡ���ܵȼ�
	INT GetSkillLevel(INT nSkillTemplateId);

	// ��������
	BOOL UpgradeSkill(DWORD nSkillTemplateId);
	// ��ȡ���Լ��ܵĵȼ�
	INT GetResistSkillLevel(INT nResistType);
	// ˢ�´��ͼ���
	BOOL ReloadPlayerSkills();

	// �ж����޴˼���
	BOOL HasSkill(WORD wSkillId);
	// ���һ��ָ��Id�ļ���
	BOOL AddSkill(WORD nSkillId, BOOL bSync = TRUE, INT nSkillLevel = 1);
	// Ӧ�ñ�������
	BOOL SetPassiveSkill(INT nPassiveType, INT nSkillLevel, BOOL bAddOrRemove, BOOL bSync = TRUE);
	// �����Ӧ�ȼ��ı���������ֵ
	BOOL AddPassiveSkillValue(INT nPassiveType, INT nSkillLevel, BOOL bTakeBackNumber = FALSE, BOOL bSync = FALSE);
	// Ӧ�ñ�������
	/*BOOL ApplyPassiveSkill();*/
	//ɾ��һ������
	BOOL RemoveSkill(WORD nSkillId, BOOL bSync = TRUE);
	// ������м��ܣ�����ͬ�����ͻ���
	BOOL ClearSkill();
	// ��ռ���CD
	BOOL ClearSkillCD(WORD wSkillId);
	//�Ƿ���Էŵ�ǰ�ļ���
	BOOL CanCastSkill(WORD wSkillId,DWORD dwTargetId, INT nX, INT nY, INT nZ);
	// ��鼼���ͷž���
	BOOL CheckSkillCastDistance(WORD wSkillId, DWORD dwTargetId, INT nX, INT nY, INT nZ);
	//��ǰ�����Ƿ���CD��
	BOOL IsSkillInCD(WORD wSkillId);

	// ��ȴ����, ��ȴ�����л�
	BOOL CooldownSkill(WORD wSkillId);
	// �ͷż���ǰ��������
	VOID TurnToBeforeCast(KCharacter* pCaster, KCharacter* pTarget);

	//�ͷż���
	BOOL CastSkill(WORD wSkillId,DWORD dwTargetId,INT nX,INT nY,INT nZ);
	BOOL CastSkill(WORD wSkillId,DWORD dwTargetId,INT nX,INT nY,INT nZ, BOOL syncSelf = FALSE, BOOL bSpecialTimeScale = FALSE);

		// ������������ʱɾ��ԭ����������rawset
	VOID RawSetLock();
	VOID RawSetUnLock();

	// ȡ����������
	BOOL CancelChannelSkill(WORD wSkillId);

	// ��Ӽ���ǰ����
	BOOL PreAddSkill(WORD wSkillId);

	// ��ü���map
	CONST SKILLDATAMAP& GetSkillMap() CONST;
	SKILLDATAMAP& GetSkillMap();

	LuaCharacterSkill* GetScriptInterface() CONST;

	// ��鼼����������
	BOOL CheckSkillUpgradeCost(DWORD dwSkillTemplateId);

	/*
	* ��������ӻ��İٷֱ�
	*/
	VOID AddSkillCritical(WORD wCateType, WORD wCateId, UINT uPercent);

	/*
	* ���ټ��ܻ��İٷֱ�
	*/
	VOID DelSkillCritical(WORD wCateType, WORD wCateId, UINT uPercent);

	/*
	* ��ü��ܻ��İٷֱ�
	*/
	INT GetSkillCritical(WORD wCateType, WORD wCateId);

	BOOL SaveDelaySkillData(QDelaySkillData* pDelaySkillData);

	INT GetSkillType(INT nSkillId);

	BOOL SyncSkillsToClient(BOOL resetCD = FALSE);

	BOOL CheckObstacle(INT nStartX, INT nStartY, INT nStartZ, INT nEndX, INT nEndY, INT nEndZ, INT nTouchRange, INT& nLastOkX, INT& nLastOkY);
	BOOL CheckObstacle(INT nStartX, INT nStartY, INT nStartZ, INT nEndX, INT nEndY, INT nEndZ, INT nTouchRange);
	BOOL CheckObstacle(DWORD dwTargetId);

public:
	INT m_LastChangeRouteTime;

private:
	//typedef std::map<INT, INT> SKILLLEVELMAP;
	//SKILLLEVELMAP m_mapSkillLevelData;  // ��¼��ɫ���ܵȼ����� SLOT->�ȼ�

	FACTIONSKILLMAP m_mapSkillLevelData;  // ��¼��ɫ���ܵȼ�����
	SKILLDATAMAP m_mapSkillData;
	
	LuaCharacterSkill* m_pLunaObj;

	BOOL m_bMapLoadEmpty;	//������ص����ݿ�Ϊ�գ�˵�����½�ɫ����OnClientReady�Ͳ���ͬ����

	std::map<DWORD, INT> m_tSkillCriticalP;		//���ӱ����ʵ�Skill����,KEY=MAKEWORD(nCateType, nCateId)
	
	BOOL m_arrPassiveSkill[emSKILL_ATTR_COUNT];  //��¼��������״̬

	BOOL ApplyMedicineSkill(INT nSkillSlot, INT nSkillLevel);  // ��ҩ����
};


#endif