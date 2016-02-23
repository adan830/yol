
#ifndef __KSWITCHITEM_H__
#define __KSWITCHITEM_H__

#include "onlinegamemodule/item2/itemdef.h"

class KPlayerItem;

// ���д�����Ʒ������һЩ�¼�
class KSwitchNotify
{
public:
	explicit KSwitchNotify(KPlayerItem& rcPlayerItem) : m_rcPlayerItem(rcPlayerItem) {}
	BOOL SwitchBegin();
	BOOL SwitchEnd();
	BOOL OnPickNotify(CONST KITEM_POS& rsPos, INT nPickList);
	BOOL OnDropNotify(CONST KITEM_POS& rsPos, INT nPickList);
private:
	KPlayerItem& m_rcPlayerItem;
};

// -------------------------------------------------------------------------
// ������Ҫ�Ķ��ⷽ��Switch()���𽻻�����λ�õ���Ʒ��ע�ⲻ����Դ��Ŀ�ģ���������������ӵ����Ӧ�÷ŵ�����Χȥ����
// ���е��ж϶�Ӧ����CheckProc����У�SwitchProcû��ʧ�ܣ�Ŀǰ��û�ж�Ӧ���쳣����
// Switch���Ʊ�֤�ص������Ĳ���һ������ȷ�޳�ͻ�ĵģ�Drop��Pick���߲�����ͬһ��λ�ã�û��Ҫ��Ҫ��������жϡ�

class KSwitchItem
{

private:

	typedef BOOL (KSwitchItem::*CheckProc)(CONST KITEM_POS& rsPos, INT nPick, INT nDrop);	// �л����ص�����
	typedef VOID (KSwitchItem::*PickProc)(CONST KITEM_POS& rsPos, INT nPickList);			// ������ص�����
	typedef VOID (KSwitchItem::*DropProc)(CONST KITEM_POS& rsPos, INT nDropList);			// ���´���ص�����

	struct KPROCPAIR
	{
		CheckProc	pfnCheck;
		PickProc	pfnPick;
		DropProc	pfnDrop;
	};

public:

	static VOID	InitProc(VOID);		// ע�����������໥�����Ŀռ�

public:

	explicit KSwitchItem(KPlayerItem& rcPlayerItem) : m_rcPlayerItem(rcPlayerItem), m_SwitchNotify(rcPlayerItem) {}

	BOOL Switch(CONST KITEM_POS& rsLeft, CONST KITEM_POS& rsRight);

	// CheckProc Callbacks
	BOOL CheckBase		(CONST KITEM_POS& rsPos, INT nPick, INT nDrop);
	BOOL CheckEquip		(CONST KITEM_POS& rsPos, INT nPick, INT nDrop);
	BOOL CheckEquipEx2	(CONST KITEM_POS& rsPos, INT nPick, INT nDrop);
	BOOL CheckRepository(CONST KITEM_POS& rsPos, INT nPick, INT nDrop);
	BOOL CheckExtBagBar	(CONST KITEM_POS& rsPos, INT nPick, INT nDrop);
	BOOL CheckExtBag	(CONST KITEM_POS& rsPos, INT nPick, INT nDrop);
	BOOL CheckExtRep	(CONST KITEM_POS& rsPos, INT nPick, INT nDrop);

	// PickProc Callbacks
	VOID PickBase		(CONST KITEM_POS& rsPos, INT nPickList);
	VOID PickEquip		(CONST KITEM_POS& rsPos, INT nPickList);
	VOID PickExtBagBar	(CONST KITEM_POS& rsPos, INT nPickList);
	
	// DropProc Callbacks
	VOID DropBase		(CONST KITEM_POS& rsPos, INT nDropList);
	VOID DropEquip		(CONST KITEM_POS& rsPos, INT nDropList);
	VOID DropEquipEx	(CONST KITEM_POS& rsPos, INT nDropList);
	VOID DropExtBagBar	(CONST KITEM_POS& rsPos, INT nDropList);
	
private:

	static KPROCPAIR	ms_asProc[emROOM_NUM];
	static BOOL			ms_aabSwitchProc[emROOM_NUM][emROOM_NUM];

public:

	KSwitchNotify		m_SwitchNotify;

private:

	KPlayerItem&		m_rcPlayerItem;

};

// -------------------------------------------------------------------------

#endif /* __KSWITCHITEM_H__ */
