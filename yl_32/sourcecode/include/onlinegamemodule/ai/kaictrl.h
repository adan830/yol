
#pragma once

#include "onlinegameworld/kcharacter.h"
#include "config/kcharacterdef.h"
#include "onlinegameworld/kcharacterctrlbase.h"

#include "onlinegamemodule/ai/kaivm.h"
#include "onlinegamemodule/ai/PatrolPath.h"
#include "onlinegamemodule/ai/Target.h"

#define MAX_SKILL_LUA_BUFFER_LENGTH 512

class KNpc;
class KPlayer;
class KLuaAI;

class KAICtrl : public KCharacterCtrlBase
{
public:
	enum 
	{	emKCtrlId = emKCHARACTER_CTRL_AI_DATA	};

	KAICtrl(KCharacter& rcCharacter);

	KLuaAI* GetScriptInterface()
	{	return m_pLuna;	}

public:
	BOOL Init();

	void ResetData();

	BOOL UnInit();


protected:
	VOID Release();
	BOOL CallScript(LPCSTR pszFunName, LPCSTR pszFormat, ...);

public:
	int                 nAIType;

	int                 nOriginPosX;
	int                 nOriginPosY;
	int                 nOriginPosZ;
	int                 nOriginDirection;

	int                 nReturnPosX;
	int                 nReturnPosY;
	int                 nReturnPosZ;

	int                 nPatrolPathID;
	KPatrolPath*        pPatrolPath;
	int                 nPatrolOrderIndex;

	int                 nEscapeCount;

	static DWORD        dwAIEventSrc;
	static int          nAIEventParam;
	static int          nTargetGroupCount;

	int                 nCannotAttactCount;
	int                 nSkillFailedCount;
	int                 nSkillType;
	DWORD               dwRespondCharacterID;   // ��¼�����ߵ�ID
	int                 nAITotalDamageValue;

	DWORD               dwProtectCampMark;      // �ܱ�������Ӫ���
	DWORD               dwProtectForceMark;     // �ܱ������������(����)

	KTarget             ChoiceTarget[aittTotal];
	DWORD               nRecordSkillID[airstTotal];
	DWORD               nRecordSkillLevel[airstTotal];
	BOOL                bSpecialSelectTarget;

	static KCharacter*  TargetGroup[AI_TARGET_GROUP_MAX_COUNT];

	int             m_nSkillSelectIndex;            // ����ѡ�����Ľ��
private:
	KLuaAI* m_pLuna;
};

#define m_AIData GetCtrlRef<KAICtrl>()
