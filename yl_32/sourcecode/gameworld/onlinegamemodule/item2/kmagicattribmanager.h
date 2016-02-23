
#ifndef __KMAGICATTRIBMANAGER_H__
#define __KMAGICATTRIBMANAGER_H__

// -------------------------------------------------------------------------
#include "kmanager_i.h"
#include "kmagicdesc.h"
//#include "knpcattribmodify.h"

class KMagicDesc;
struct KMagicAttrib;
class KNpc;
class KNpcAttribModify;
class KCharacter;

// -------------------------------------------------------------------------

// ����Ϊһ����ӿڣ����幦����ͨ������KNpcAttribModify��KMagicDesc��ʵ��
class KMagicAttribMgr : public IKManager
{
public:
	LPCSTR	GetName() CONST	{ return "MagicAttrib"; };
	
	// ����Id�����Ӧ��ħ��������
	LPCSTR GetStringFromId(INT nAttrib);

	// ����ħ�������������Ӧ��Id
	INT GetIdFormString(PCSTR szMagicAttribName);

	// ���ָ������ָ��ħ�����Ե�����
	LPCSTR	GetMagicDesc(CONST KMagicAttrib *pData, INT nSkillId);

	// Ϊָ��NpcӦ��ħ������
	VOID ModifyAttrib(KCharacter *pCharacterLauncher, KCharacter *pCharacter, INT nSkillId, CONST KMagicAttrib& rcpMagic, BOOL bIsEndProcess);

	// �Ƿ���ħ������ʧЧ
	BOOL IsEndProcess() CONST;

	// ���ħ�����Ե��ͷ���
	KNpc* GetMagicLauncher() CONST;

private:
	//KNpcAttribModify m_cNpcAttribModify;		// �����������޸�Npc������

	KMagicDesc m_cMagicDesc;					// ������ά��һ��ħ�������ַ�����ħ������ֵ�ı�
};

extern KMagicAttribMgr g_cMagicAttribMgr;

// -------------------------------------------------------------------------

#endif /* __KMAGICATTRIBMANAGER_H__ */
