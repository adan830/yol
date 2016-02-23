#ifndef __KBLADECTRL_H__
#define __KBLADECTRL_H__

#include "onlinegameworld/kcharacterctrlbase.h"
#include "config/kcharacterdef.h"
#include "bladedef.h"

class KPlayer;

class KBladeCtrl : public KCharacterCtrlBase
{
public:
	enum 
	{	emKCtrlId = emKCHARACTER_CTRL_PLAYER_BLADE,	};

public:

	explicit KBladeCtrl(KCharacter& rcPlayer);
	virtual ~KBladeCtrl();

	virtual BOOL Init();
	virtual BOOL UnInit() { return TRUE; }
	virtual BOOL Active();
	virtual BOOL OnLogin();

private:
	KPlayer& m_rcPlayer;	// �������

public:
	BOOL ApplyBladeAttr();

	VOID ApplyBladePendants();

	VOID ResetPendants();

	BOOL RemoveBladeAttr();

	BOOL OnStartCrazy();

	VOID CheckRemoveBladeState();

	VOID ResetBladeState();

	CONST KBLADE_ATTR& GetBladeAttr();

private:
	KBLADE_ATTR m_sBladeAttr;

	KBLADE_ATTR m_sCurBladeAttr;		// ��ǰ������ҵı������ԣ�ͬ�����ͻ�����
};

#endif