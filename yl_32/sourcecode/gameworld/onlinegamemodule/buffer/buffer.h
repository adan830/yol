/* -------------------------------------------------------------------------
//	�ļ���		��	Buffer.h
//	������		��	zhangzhixiong
//	����ʱ��	��	2012-5-7 
//	��������	��	
//
// -----------------------------------------------------------------------*/
#ifndef __BUFFER_H__
#define __BUFFER_H__

#include <string>
#include <vector>
#include "onlinegamemodule/bufferdef.h"
#include "buftriggereffect.h"

class KCharacter;
struct BufferTemplate;
class BufTriggerEffect;
class BufTimerEffect;
struct FightSkillTemplate;

struct BuffData
{
	BYTE	data_type;
	INT		data_value;
};

class Buffer
{
public:
	Buffer();

	~Buffer();

//const ��������Ӧ����ĳЩ��Ҫconst Buffer*�Ķ�����
public:
	DWORD GetID() CONST {return m_dwId;}

	INT  GetTemplateID() CONST {return m_nBuffTemplateID;}

	INT GetBuffPersist() CONST {return m_nBuffPersist;}

	INT GetCurrentBuffPersist() CONST {return m_nCurrentPersist;}

	BufferGroupType GetBuffType() CONST {return m_eBuffType;}

	BYTE GetBuffLevel() CONST {return m_nBuffLevel;}

	BUFFER_POSITION GetBuffPosition() CONST {return m_BuffPosition;}

	INT GetStackCategory() CONST {return m_nStackCategory;}	//��ͬ�Ĳſɵ���

	//INT GetStackDetail() CONST {return m_nStackDetail;}

	INT GetMaxStackCount() CONST {return m_nStackCount;}

	INT GetStatckCount() CONST {return m_nCurrentStackCount;}

	BOOL IsSync() CONST {return m_bSync;}

	BOOL IsSave() CONST {return m_bSave;}

	BOOL IsDeathKeep() CONST {return m_bDeath;}

	BOOL IsCanPlus() CONST {return m_bPlus;}

	BOOL IsNeedAgree() CONST {return m_bNeedAgree;}

	FLOAT GetBuffRadius() CONST {return m_fBuffRadius;}

	INT GetBuffEffectNum() CONST {return m_nBuffEffectNum;}

	KCharacter* GetReceiveCharacter() CONST { return m_pCharacter;}

	KCharacter* GetCasterCharacter() CONST { return m_pSender;}

	INT GetCastSkill() CONST {return m_nSkillTemplateId;}

	INT GetMagnification() CONST {return m_nMagnification;}

	INT GetGrow() CONST {return m_nGrow;}

	INT GetK() CONST {return m_nK;}

	INT GetIfUseSkillLv() CONST {return m_nIfUseSkillLv;}

	INT GetBuffCategory(INT index);

//���⹫�ú���
public:
	BOOL Init(BufferTemplate* buffTemplate, INT nPersist = 0);

	BOOL BindCharacter(KCharacter* pCharacter);	//�󶨽�����,�ڽ����߽��ܵ�ʱ���

	BOOL BindSender(KCharacter* pCharacter);//���ͷ���,���ͷ����ͷŵ�ʱ���

	BOOL BindFightSkill(INT nFightSkillTemplateId); // ���ͷŴ�buffer�ļ���ID

	BOOL SetSkillLevel(INT nSkillLevel);  // ����buffer�ȼ�

	BOOL Reset();

    VOID Breath();

	INT GetCurrentStackCount() { return m_nCurrentStackCount; }

	VOID UpdateBufferStack();

	VOID UpdateInterval(BOOL bStack = FALSE);	//����ʱ��

	VOID SetInterval(INT nInterval)	{ if (nInterval > 0) m_nCurrentPersist = nInterval;}

	INT GetBufferType() {return m_nBuffType;}

//����������
public:
	BOOL OnRemoveBuff();	//���buff

	BOOL CheckSelfCondition(BOOL& bSync);	//��������һЩ����

	BOOL CheckSceneBuffEffect();

	BOOL IsLifeEnd()	{return m_nCurrentPersist <= 0; }	//�Ƿ�������������

	BOOL CheckRelation(KCharacter* pCaster, KCharacter* pTarget);

	BOOL ModifyThreat(KCharacter* pCaster, KCharacter* pTarget);

	BOOL CheckTimerCondition(INT nIndex);		//ʱ�䴥����һЩ�ж�

	BOOL ProcessTimer();		//���������buffЧ��

	/*
	* �¼�������һЩ�ж�(���ܻ��޸��������Buff���е�״̬)
	* args:
	* return:
	*/
	BOOL CheckTriggerCondition(LPCSTR szEvent, KCharacter* pEventReceive, KCharacter* pEventSender);

	BOOL ProcessTrigger();				//�����¼�����

	BOOL TriggerEffect(INT nIndex);				//����Ч��

	VOID AddBuffPersist(INT value) { m_nBuffPersist += value; }

	VOID RefreshBuffPersist();

	DWORD m_dwId;

	CONST std::vector<BuffData>& GetAppendData() CONST { return m_vecAppendData; };
	VOID SetAppendDataFromDB(CONST VOID* pAppendData, size_t append_size);

	//���һ��ӳ����ݣ���Ӧ�õ��������
	VOID AppendData(BYTE type, INT value);

	INT GetAppendData(BYTE type);

	CONST FightSkillTemplate* GetBelongSkillTemplate() CONST;

	VOID SetDestPosition(INT nX, INT nY, INT nZ);

	VOID GetDestPosition(INT& nX, INT& nY, INT& nZ) { nX = m_nDestX; nY = m_nDestY; nZ = m_nDestZ;}

protected:
    INT		m_nBuffTemplateID;		// Buffer ģ��ID
	INT		m_nBuffPersist;			// Buffer ����ʱ��,֡��
	INT		m_nCurrentPersist;		// ��ǰ��ʱ��
	BYTE	m_nBuffLevel;			// buff�ȼ�
	INT		m_nBuffType;			// �Ƿ���debuff
	INT		m_nStackCategory;		// ��������
	INT		m_nStackCategory1;		// ����ϸ��
	INT		m_nStackCategory2;		// ����ϸ��
	INT		m_nMagnification;		// ϵ��
	INT		m_nGrow;				// �ɳ�
	INT		m_nStackCount;			// ���Ӳ���
	INT		m_nCurrentStackCount;	// ��ǰ���Ӳ���
	BOOL	m_bSync;				// �Ƿ�Ҫͬ�����ͻ���
	BOOL	m_bSave;				// �Ƿ����߱���
	BOOL	m_bDeath;				// �����Ƿ���
	BOOL	m_bPlus;				// �Ƿ���Ե��
	BOOL	m_bNeedAgree;			// �Ƿ�����ȷ��
	BOOL	m_bAffectOnce;			// ��������ֻ��Чһ�εı�־
	BOOL	m_bStackAffectOnce;		// buff����ֻ��Чһ�εı�־

	INT		m_nDestX;
	INT		m_nDestY;
	INT		m_nDestZ;

	BufferGroupType		m_eBuffType;
	BUFFER_POSITION		m_BuffPosition;		// ����λ��
	FLOAT				m_fBuffRadius;		// Ӱ�췶Χ,�뾶
	INT					m_nBuffEffectNum;	// buffӰ������
	INT					m_nBuffDelayFrame;	// BUffЧ���ӳ�
	INT					m_nK;				// buff��Kֵ
	INT					m_nIfUseSkillLv;	// buff�ڼ�����ֵʱ�Ƿ��õ����ܵȼ�
	CHAR				m_szEffectMapType[MAX_NAME_LEN];		// ��Ч�ĵ�ͼ����


	std::vector<BufTimerEffect*>		m_vecBufTimerEffect;			// ������Ч��
	std::vector<INT>					m_vecBufTimerInterval;			// ������Ч����Ӧ��ʱ�䣬��Ч��vec��Ӧ

	std::vector<TriggerData>			m_vecBufTriggerEffect;			// ������Ч��

	KCharacter* m_pCharacter;	//������
	KCharacter* m_pSender;		//�ͷ���
	INT m_nSkillTemplateId;

	DWORD m_dwSenderId;		// �ͷ���id

	INT m_nSkillLevel;

	std::vector<BuffData> m_vecAppendData;		// ��ǰBuff�Ľű��ӳ�����
};

#endif