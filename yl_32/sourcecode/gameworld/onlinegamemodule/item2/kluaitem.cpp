
#include "stdafx.h"
#include "onlinegamebase/kscriptmanager.h"
#include "Protocol/AccountLoginDef.h"
#include "kluaitem.h"
#include "kitem.h"
#include "onlinegameworld/kplayer.h"
#include "onlinegameworld/kplayermgr.h"
#include "kitemmgr.h"
#include "kmagicattribmanager.h"
#include "../gameworld/nsworld/kcharacterhelper.h"
#include "onlinegamemodule/trade/kplayerpurse_i.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static CHAR THIS_FILE[] = __FILE__;
#endif

// -------------------------------------------------------------------------

KItem* KLuaItem::GetIt(QLuaScript& sc, INT nIndex)
{
	KLuaItem* pLuaItem = dynamic_cast<KLuaItem *>(GetCObj(sc.GetLuaState(), nIndex));
	if (pLuaItem)
		return pLuaItem->m_pIt;

	return NULL;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: KLuaItem
// @LuaApiName		: Name
// @Description		: �������ƣ�������׺����
// @Property(R/RW)	: R
// @PropertyType	: STRING
// @LuaMarkEnd
// -------------------------------------------------------------------------
LPCSTR KLuaItem::getName(VOID) CONST
{
	return	m_pIt->GetOrgName();
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: KLuaItem
// @LuaApiName		: OrgName
// @Description		: ����ԭ����������׺����
// @Property(R/RW)	: R
// @PropertyType	: STRING
// @LuaMarkEnd
// -------------------------------------------------------------------------
LPCSTR KLuaItem::getOrgName(VOID) CONST
{
	return	m_pIt->GetOrgName();
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: KLuaItem
// @LuaApiName		: Suffix
// @Description		: ���ߺ�׺��
// @Property(R/RW)	: R
// @PropertyType	: STRING
// @LuaMarkEnd
// -------------------------------------------------------------------------
LPCSTR KLuaItem::getSuffix(VOID) CONST
{
	return	m_pIt->GetSuffix();
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: KLuaItem
// @LuaApiName		: Genre
// @Description		: �������� (����? ҩƷ? ��ʯ?)
// @Property(R/RW)	: R
// @PropertyType	: INTEGER
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT KLuaItem::getGenre(VOID) CONST
{
	return	m_pIt->GetGenre();
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: KLuaItem
// @LuaApiName		: Detail
// @Description		: ������ϸ���
// @Property(R/RW)	: R
// @PropertyType	: INTEGER
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT KLuaItem::getDetail(VOID) CONST
{
	return	m_pIt->GetDetailType();
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: KLuaItem
// @LuaApiName		: Particular
// @Description		: ���߾������
// @Property(R/RW)	: R
// @PropertyType	: INTEGER
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT KLuaItem::getParticular(VOID) CONST
{
	return	m_pIt->GetParticular();
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: KLuaItem
// @LuaApiName		: Level
// @Description		: ���ߵȼ�
// @Property(R/RW)	: R
// @PropertyType	: INTEGER
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT KLuaItem::getLevel(VOID) CONST
{
	return	m_pIt->GetLevel();
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: KLuaItem
// @LuaApiName		: ReqLevel
// @Description		: 
// @Property(R/RW)	: R
// @PropertyType	: INTEGER
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT KLuaItem::getReqLevel(VOID) CONST
{
	return	m_pIt->GetReqLevel();
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: KLuaItem
// @LuaApiName		: Quality
// @Description		: ����Ʒ��
// @Property(R/RW)	: R
// @PropertyType	: INTEGER
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT KLuaItem::getQuality(VOID) CONST
{
	return	m_pIt->GetQuality();
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: KLuaItem
// @LuaApiName		: FightPower
// @Description		: ս����
// @Property(R/RW)	: R
// @PropertyType	: INTEGER
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT KLuaItem::getFightPower(VOID) CONST
{
	return	m_pIt->GetFightPower();
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: KLuaItem
// @LuaApiName		: RandSeed
// @Description		: �����������
// @Property(R/RW)	: R
// @PropertyType	: DWORD
// @LuaMarkEnd
// -------------------------------------------------------------------------
DWORD KLuaItem::getRandSeed(VOID) CONST
{
	return	m_pIt->GetRandSeed();
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: KLuaItem
// @LuaApiName		: RandSeedEx
// @Description		: �����������
// @Property(R/RW)	: R
// @PropertyType	: DWORD
// @LuaMarkEnd
// -------------------------------------------------------------------------
DWORD KLuaItem::getRandSeedEx(VOID) CONST
{
	return	m_pIt->GetRandSeedEx();
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: KLuaItem
// @LuaApiName		: Count
// @Description		: ���ߵ�ǰ������Ŀ
// @Property(R/RW)	: R
// @PropertyType	: INTEGER
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT KLuaItem::getCount(VOID) CONST
{
	return	m_pIt->GetCount();
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: KLuaItem
// @LuaApiName		: MaxCount
// @Description		: ������������Ŀ
// @Property(R/RW)	: R
// @PropertyType	: INTEGER
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT KLuaItem::getMaxCount(VOID) CONST
{
	return	m_pIt->GetMaxCount();
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: KLuaItem
// @LuaApiName		: Price
// @Description		: ���߼۸�
// @Property(R/RW)	: R
// @PropertyType	: INTEGER
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT KLuaItem::getPrice(VOID) CONST
{
	return	m_pIt->GetPrice();
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: KLuaItem
// @LuaApiName		: BindType
// @Description		: ���߰�����
// @Property(R/RW)	: R
// @PropertyType	: INTEGER
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT KLuaItem::getBindType(VOID) CONST
{
	return	m_pIt->GetBindType();
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: KLuaItem
// @LuaApiName		: EnhTimes
// @Description		: ������ǿ������
// @Property(R/RW)	: RW
// @PropertyType	: INTEGER
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT KLuaItem::getEnhTimes(VOID) CONST
{
	return	m_pIt->GetEnhanceTimes();
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: KLuaItem
// @LuaApiName		: SlotSize
// @Description		: װ���ı�ʯ������
// @Property(R/RW)	: R
// @PropertyType	: INTEGER
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT KLuaItem::getSlotSize(VOID) CONST
{
	return	m_pIt->GetStoneSlot();
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: KLuaItem
// @LuaApiName		: Strengthen
// @Description		: ���߸���ȼ�
// @Property(R/RW)	: R
// @PropertyType	: INTEGER
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT KLuaItem::getStrengthen(VOID) CONST
{
	return	m_pIt->GetStrengthen();
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: KLuaItem
// @LuaApiName		: EquipPos
// @Description		: װ��Ӧ������װ����λ��
// @Property(R/RW)	: R
// @PropertyType	: INTEGER
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT KLuaItem::getEquipPos(VOID) CONST
{
	if (!KD_ISEQUIP(m_pIt->GetGenre()))
		return	-1;
	return	KPlayerItem::GetEquipPos(m_pIt->GetDetailType());
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: KLuaItem
// @LuaApiName		: Value
// @Description		: ���ߵļ�ֵ��
// @Property(R/RW)	: R
// @PropertyType	: INTEGER
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT KLuaItem::getValue(VOID) CONST
{
	return	m_pIt->GetValue();
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: KLuaItem
// @LuaApiName		: StarLevel
// @Description		: ���ߵļ�ֵ���Ǽ�
// @Property(R/RW)	: R
// @PropertyType	: INTEGER
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT KLuaItem::getStarLevel(VOID) CONST
{
	return	m_pIt->GetStarLevel();
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: KLuaItem
// @LuaApiName		: NameColor
// @Description		: ���ߵ�������ɫ
// @Property(R/RW)	: R
// @PropertyType	: INTEGER
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT KLuaItem::getNameColor(VOID) CONST
{
	return	m_pIt->GetNameColor();
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: KLuaItem
// @LuaApiName		: CdType
// @Description		: ���ߵ�CDʱ������
// @Property(R/RW)	: R
// @PropertyType	: INTEGER
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT KLuaItem::getCdType(VOID) CONST
{
	return	m_pIt->GetCDType();
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: KLuaItem
// @LuaApiName		: CustomType
// @Description		: ���ߵ��Զ����ַ�������
// @Property(R/RW)	: R
// @PropertyType	: INTEGER
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT KLuaItem::getCustomType(VOID) CONST
{
	return	m_pIt->GetCustomType();
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: KLuaItem
// @LuaApiName		: EquipCategory
// @Description		: װ�����
// @Property(R/RW)	: R
// @PropertyType	: INTEGER
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT KLuaItem::getEquipCategory(VOID) CONST
{
	return	m_pIt->GetEquipCategory();
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: KLuaItem
// @LuaApiName		: Id
// @Description		: ����ID
// @Property(R/RW)	: R
// @PropertyType	: DWORD
// @LuaMarkEnd
// -------------------------------------------------------------------------
DWORD KLuaItem::getId(VOID) CONST
{
	return	m_pIt->GetID();
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: KLuaItem
// @LuaApiName		: Class
// @Description		: Class����
// @Property(R/RW)	: R
// @PropertyType	: STRING
// @LuaMarkEnd
// -------------------------------------------------------------------------
LPCSTR KLuaItem::getClass(VOID) CONST
{
	return	m_pIt->GetClass();
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: KLuaItem
// @LuaApiName		: CustomString
// @Description		: �����Զ����ַ���
// @Property(R/RW)	: R
// @PropertyType	: STRING
// @LuaMarkEnd
// -------------------------------------------------------------------------
LPCSTR KLuaItem::getCustomString(VOID) CONST
{
	return	m_pIt->GetCustomString();
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: KLuaItem
// @LuaApiName		: ForbidType
// @Description		: ��������
// @Property(R/RW)	: R
// @PropertyType	: STRING
// @LuaMarkEnd
// -------------------------------------------------------------------------
LPCSTR KLuaItem::getForbidType(VOID) CONST
{
	return	m_pIt->GetForbidType();
}

VOID KLuaItem::setEnhTimes(INT nEnhTimes)
{
	m_pIt->SetEnhanceTimes(nEnhTimes);
}

BOOL KLuaItem::ClearTempTable(VOID)
{
	return ClearScriptTempTable(g_cScriptManager.GetSafeScript()->GetLuaState(), s_szClassName, m_pIt->GetID());
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: KLuaItem
// @LuaApiName		: GetTempTable
// @Description		: ȡ�ýű��õ���ʱTable
// @ReturnCode		: �����󶨵���ʱTable
// @ArgumentFlag	: 
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT KLuaItem::LuaGetTempTable(QLuaScript& sc)
{
	if (!GetScriptTempTable(sc.GetLuaState(), s_szClassName, m_pIt->GetID()))
	{
		_ASSERT(FALSE);
		return 0;
	}

	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: KLuaItem
// @LuaApiName		: IsEquip
// @Description		: �жϸõ����Ƿ�һ��װ��
// @ReturnCode		: 1-��װ��
// @ArgumentFlag	: 
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT KLuaItem::LuaIsEquip(QLuaScript& sc)
{
	sc.PushNumber(KD_ISEQUIP(m_pIt->GetGenre()));
	return	1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: KLuaItem
// @LuaApiName		: IsStone
// @Description		: �жϸõ����Ƿ�ʯ
// @ReturnCode		: 1-�Ǳ�ʯ
// @ArgumentFlag	: 
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT KLuaItem::LuaIsStone(QLuaScript& sc)
{
	sc.PushNumber(KD_ISSTONE(m_pIt->GetGenre(), m_pIt->GetDetailType()));
	return	1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: KLuaItem
// @LuaApiName		: IsInvalid
// @Description		: �жϸõ����Ƿ���ʧЧ״̬
// @ReturnCode		: 1-ʧЧ
// @ArgumentFlag	: 
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT KLuaItem::LuaIsInvalid(QLuaScript& sc)
{
	sc.PushNumber(m_pIt->IsInvalid());
	return	1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: KLuaItem
// @LuaApiName		: IsDuped
// @Description		: �ж��Ƿ��Ƶ���
// @ReturnCode		: 1-�Ǹ��Ƶ���
// @ArgumentFlag	: 
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT KLuaItem::LuaIsDuped(QLuaScript& sc)
{
	sc.PushNumber(m_pIt->IsDupedItem());
	return	1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: KLuaItem
// @LuaApiName		: IsTemp
// @Description		: �ж��Ƿ���ʱ����
// @ReturnCode		: 1-����ʱ����
// @ArgumentFlag	: 
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT KLuaItem::LuaIsTemp(QLuaScript& sc)
{
	sc.PushNumber(m_pIt->IsTemporary());
	return	1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: KLuaItem
// @LuaApiName		: GetLockIntervale
// @Description		: ȡ��������ڣ�Ϊ0��ʾ�����Զ����
// @ReturnCode		: dwTime������
// @ArgumentFlag	: 
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT KLuaItem::LuaGetLockIntervale(QLuaScript& rcScript)
{
	rcScript.PushNumber(m_pIt->GetLockIntervale());
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: KLuaItem
// @LuaApiName		: IsLock
// @Description		: �ж��Ƿ�������
// @ReturnCode		: 1-������
// @ArgumentFlag	: 
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT KLuaItem::LuaIsLock(QLuaScript& sc)
{
	sc.PushNumber(m_pIt->IsLock());
	return	1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: KLuaItem
// @LuaApiName		: IsBind
// @Description		: �ж��Ƿ��Ѱ�
// @ReturnCode		: 1-�Ѱ�
// @ArgumentFlag	: 
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT KLuaItem::LuaIsBind(QLuaScript& sc)
{
	sc.PushNumber(m_pIt->IsBind());
	return	1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: KLuaItem
// @LuaApiName		: CanBeShortcut
// @Description		: �Ƿ���ԷŽ������
// @ReturnCode		: 1����
// @ArgumentFlag	: 
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT KLuaItem::LuaCanBeShortcut(QLuaScript& sc)
{
	sc.PushNumber(m_pIt->CanBeShortcut());
	return	1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: KLuaItem
// @LuaApiName		: GetBaseAttrib
// @Description		: ��ȡ��Ʒ�Ļ�������
// @ReturnCode		: ħ�����Ա�
// @ArgumentFlag	: 
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT KLuaItem::LuaGetBaseAttrib(QLuaScript& sc)
{
	sc.PushTable();
	for (INT i = 0; i < emITEM_COUNT_BASE; ++i)
	{
		sc.PushTable();
		::g_PushMagicAttribAsTable(sc, &m_pIt->m_aryBaseAttrib[i]);
		sc.SetTableIndex(i + 1);
	}
	return	1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: KLuaItem
// @LuaApiName		: GetReqAttrib
// @Description		: ��ȡ��Ʒ����������
// @ReturnCode		: ħ�����Ա�
// @ArgumentFlag	: 
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT KLuaItem::LuaGetReqAttrib(QLuaScript& sc)
{
	sc.PushTable();
	for (INT i = 0; i < emITEM_COUNT_REQ; ++i)
	{
		CONST KItem::KREQUIRE_ATTR *pReq = &m_pIt->m_aryReqAttrib[i];
		sc.PushTable();
		sc.PushNumber(pReq->eRequire);
		sc.SetTableField("nReq");
		sc.PushNumber(pReq->nValue);
		sc.SetTableField("nValue");
		sc.SetTableIndex(i + 1);
	}
	return	1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: KLuaItem
// @LuaApiName		: GetExtParam
// @Description		: ��ȡ��Ʒ����չ������
// @ReturnCode		: ָ����չ��������չ������
// @ArgumentFlag	: [d]
// @ArgumentComment	: nIndex	���ص�nIndex����չ������0��ʾ����������չ������
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT KLuaItem::LuaGetExtParam(QLuaScript& sc)
{
	INT nIndex = sc.GetInt(1);
	if (!nIndex)
	{
		sc.PushTable();
		for (INT i = 0; i < emITEM_COUNT_EXTPARAM; ++i)
		{
			sc.PushNumber(m_pIt->GetExtParam(i));
			sc.SetTableIndex(i + 1);
		}
		return	1;
	}
	else
	{
		sc.PushNumber(m_pIt->GetExtParam(nIndex - 1));
			return	1;
	}
	return	0;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: KLuaItem
// @LuaApiName		: IsStackable
// @Description		: �Ƿ�ɵ�����Ʒ
// @ReturnCode		: 1�ɵ�����Ʒ
// @ArgumentFlag	: 
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT KLuaItem::LuaIsStackable(QLuaScript& sc)
{
	sc.PushNumber(m_pIt->IsStackable());
	return	1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: KLuaItem
// @LuaApiName		: IsDestoriable
// @Description		: �ɷ�����
// @ReturnCode		: 1������
// @ArgumentFlag	: 
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT KLuaItem::LuaIsDestoriable(QLuaScript& sc)
{
	sc.PushNumber(m_pIt->IsDestoriable());
	return	1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: KLuaItem
// @LuaApiName		: IsForbitThrow
// @Description		: �ɷ���
// @ReturnCode		: 1���ɶ���
// @ArgumentFlag	: 
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT KLuaItem::LuaIsForbitThrow(QLuaScript& sc)
{
	sc.PushNumber(m_pIt->IsForbitThrow());
	return	1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: KLuaItem
// @LuaApiName		: IsForbitSell
// @Description		: �ɷ�����
// @ReturnCode		: 1��������
// @ArgumentFlag	: 
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT KLuaItem::LuaIsForbitSell(QLuaScript& sc)
{
	sc.PushNumber(m_pIt->IsForbitSell());
	return	1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: KLuaItem
// @LuaApiName		: GetOwner
// @Description		: ��õ��������Ľ�ɫ����
// @ReturnCode		: �������κν�ɫ�򷵻�nil
// @ArgumentFlag	: 
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT KLuaItem::LuaGetOwner(QLuaScript& rcScript)
{
	INT nPlayerIdx = m_pIt->GetBelong();
	if (nPlayerIdx < 0 || nPlayerIdx >= MAX_PLAYER)
		return	0;

	KPlayer* pPlayer = g_cPlayerMgr.GetByIndex(nPlayerIdx);
	if (pPlayer)
		rcScript.PushObj((QLunaBase*)pPlayer->GetScriptInterface());
	else
		rcScript.PushNull();
	return	1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: KLuaItem
// @LuaApiName		: Remove
// @Description		: �����߶������Ϸ����ɾ�������ߴ�ʱӦ�ò������κ�һ����ɫ��
// @ReturnCode		: �ɹ�����1
// @ArgumentFlag	: 
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT KLuaItem::LuaRemove(QLuaScript& rcScript)
{
	if (m_pIt->GetBelong() > 0)
		return	0;

	BOOL bRet = g_cItemMgr.Remove(m_pIt->GetGameIndex(), emITEM_DATARECORD_REMOVE);
	rcScript.PushNumber(bRet);
	return	1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: KLuaItem
// @LuaApiName		: SetTimeOut
// @Description		: ���ù���ʱ��
// @ReturnCode		: 
// @ArgumentFlag	: dd
// @ArgumentComment	: �������ͣ�0����ʱ�䣨��������1���ʱ�䣨Ҳ��������
// @ArgumentComment	: ʱ��
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT KLuaItem::LuaSetTimeOut(QLuaScript& sc)
{
	INT nType = sc.GetInt(1);
	UINT uTime = (UINT)sc.GetInt(2);
	// ���ʱ����ת��Ϊ֡��
	if (nType == emKITEM_TIMEOUTTYPE_RELATIVE)
		uTime *= GAME_FPS;
	KITEM_TIMEOUT timeOut;
	timeOut.emType = (KE_ITEM_TIMEOUTTYPE)nType;
	timeOut.dwTimeout = uTime;
	m_pIt->SetTimeout(&timeOut);
	return	1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: KLuaItem
// @LuaApiName		: SetCount
// @Description		: ������Ʒ�ĸ���
// @ReturnCode		: 1�ɹ�
// @ArgumentFlag	: d[d]
// @ArgumentComment	: ���õĸ���
// @ArgumentComment	: �����������;��
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT KLuaItem::LuaSetCount(QLuaScript& sc)
{
	INT nRet = 0;
	INT nWay = emKADDITEM_BYSCRIPT;
	INT nCount = sc.GetInt(1);

#ifndef GAME_SERVER
	if (!m_pIt->IsTemporary())
		return 0;			// �ͻ���ֻ���޸���ʱ���ߵĸ���
#endif

	INT nPlayerIdx = m_pIt->GetBelong();
	if (nPlayerIdx <= 0)
		return 0;

	KE_ITEM_DATARECORD_WAY eRecordWay = emITEM_DATARECORD_NORMAL;
	if (sc.IsNumber(2))
		eRecordWay = (KE_ITEM_DATARECORD_WAY)sc.GetInt(2);

	KPlayer* pPlayer = g_cPlayerMgr.GetByIndex(nPlayerIdx);
	QCONFIRM_RET_FALSE(pPlayer);
	KPlayerItem* pPlayerItem = pPlayer->GetCtrl<KPlayerItem>();
	QCONFIRM_RET_FALSE(pPlayerItem);

	nRet = pPlayerItem->SetItemStackCount(
		m_pIt->GetGameIndex(), nCount, eRecordWay,
		(KE_LOSE_ITEM_WAY)nWay, (KE_ADD_ITEM_WAY)nWay
		);

	sc.PushNumber(nRet);
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: KLuaItem
// @LuaApiName		: SetGenerateMoneyType
// @Description		: ���õ��߲���ʱѡ��Ľ�Ǯ����
// @ReturnCode		: 
// @ArgumentFlag	: d
// @ArgumentComment	: ���ý�Ǯ����
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT KLuaItem::LuaSetGenerateMoneyType(QLuaScript& sc)
{
	INT nMoneyType = sc.GetInt(1);
	QCONFIRM_RET_FALSE(nMoneyType == EM_MONEY_SILVER || nMoneyType == EM_MONEY_COIN);
	m_pIt->SetGenerateMoneyType(nMoneyType);
	return 0;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: KLuaItem
// @LuaApiName		: GetSellMoneyType
// @Description		: ��������ɻ�õ���������
// @ReturnCode		: 0:������; 1:��ͨ����
// @ArgumentFlag	: 
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT KLuaItem::LuaGetSellMoneyType(QLuaScript& rcScript)
{
	rcScript.PushNumber((INT)m_pIt->GetSellMoneyType());
	return	1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: KLuaItem
// @LuaApiName		: HasStone
// @Description		: ����װ����λ�����Ƿ�����Ƕ��ʯ������У����ر�ʯ�ȼ�
// @ReturnCode		: 1:�� 0:û��
// @ArgumentFlag	: d
// @ArgumentComment	: ��ʯ��λ��1-3
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT KLuaItem::LuaHasStone(QLuaScript& rcScript)
{
	INT nPos = rcScript.GetInt(1);
	QCONFIRM_RET_NULL(nPos > 0 && nPos <= m_pIt->GetStoneSlot());
	rcScript.PushNumber(m_pIt->HasStone(nPos));
	return	1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: KLuaItem
// @LuaApiName		: GetEquipScore
// @Description		: 
// @ReturnCode		: װ������
// @ArgumentFlag	: 
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT KLuaItem::LuaGetEquipScore(QLuaScript& rcScript)
{
	KPlayerItem* pPlayerItem = NULL;
	KPlayer* pOwner = g_cPlayerMgr.GetByIndex(m_pIt->GetBelong());
	QCONFIRM_RET_NULL(pOwner);
	pPlayerItem = pOwner ? pOwner->GetCtrl<KPlayerItem>() : NULL;
	QCONFIRM_RET_NULL(pPlayerItem);

	INT nScore = pPlayerItem->CalcEquipScore(m_pIt);
	rcScript.PushNumber(nScore);
	return	1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: KLuaItem
// @LuaApiName		: GetResourceId
// @Description		: 
// @ReturnCode		: 
// @ArgumentFlag	: 
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT KLuaItem::LuaGetResourceId(QLuaScript& rcScript)
{
	BOOL bSex = rcScript.GetInt(1);
	INT nResId = m_pIt->GetResourceID(bSex);
	rcScript.PushNumber(nResId);
	return	1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: KLuaItem
// @LuaApiName		: GetChangeColorScheme
// @Description		: 
// @ReturnCode		: 
// @ArgumentFlag	: 
// @ArgumentComment	: 
// @ArgumentComment	: 
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT KLuaItem::LuaGetChangeColorScheme(QLuaScript& rcScript)
{
	//INT nColorScheme = m_pIt->GetChangeColorScheme();
	//rcScript.PushNumber(nColorScheme);
	return	1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: KLuaItem
// @LuaApiName		: GetTimeOut
// @Description		: ���װ����ʱʱ��
// @ReturnCode		: 0:����ʱ�䣨������; 1:���ʱ�䣨Ҳ��������
// @ReturnCode		: d:����
// @ArgumentFlag	: 
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT KLuaItem::LuaGetTimeOut(QLuaScript& sc)
{
	CONST KITEM_TIMEOUT *timeOut	= m_pIt->GetTimeout();
	INT nResult						= 0;
	INT nType						= (INT)timeOut->emType;
	DWORD dwTimeout					= timeOut->dwTimeout;
	
	if (nType == emKITEM_TIMEOUTTYPE_RELATIVE)
		dwTimeout = timeOut->dwTimeout / GAME_FPS;
	
	sc.PushNumber(nType);
	nResult ++;
	sc.PushNumber(dwTimeout);
	nResult ++;

	return nResult;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: KLuaItem
// @LuaApiName		: Bind
// @Description		: �󶨵���
// @ReturnCode		: 1�ɹ���
// @ArgumentFlag	: d
// @ArgumentComment	: bForce:ǿ��
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT KLuaItem::LuaBind(QLuaScript& sc)
{
	BOOL bForce = sc.GetInt(1);
	sc.PushNumber(m_pIt->Bind(bForce));

#ifdef GAME_SERVER
	KPlayerItem* pPlayerItem = NULL;
	KPlayer* pOwner = g_cPlayerMgr.GetByIndex(m_pIt->GetBelong());
	LOG_PROCESS_ERROR(pOwner);
	pPlayerItem = pOwner ? pOwner->GetCtrl<KPlayerItem>() : NULL;
	LOG_PROCESS_ERROR(pPlayerItem);
	pPlayerItem->SyncItem(m_pIt->GetGameIndex());
#endif

EXIT0:
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: KLuaItem
// @LuaApiName		: GetGDPLStr
// @Description		: �õ���Ʒ��gdpl�ַ���
// @ReturnCode		: 1 �ɹ�
// @ArgumentFlag	: 
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT KLuaItem::LuaGetGDPLStr(QLuaScript& sc)
{
	CHAR buf[32];
	KPlayerItem* pPlayerItem = NULL;
	KPlayer* pOwner = g_cPlayerMgr.GetByIndex(m_pIt->GetBelong());
	QCONFIRM_RET_NULL(pOwner);
	pPlayerItem = pOwner ? pOwner->GetCtrl<KPlayerItem>() : NULL;
	QCONFIRM_RET_NULL(pPlayerItem);

	snprintf(buf, sizeof(buf), "%d,%d,%d,%d", m_pIt->GetGenre(), m_pIt->GetDetailType(), 
		m_pIt->GetParticular(), m_pIt->GetLevel());

	sc.PushString(buf);

	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: KLuaItem
// @LuaApiName		: StoneClean
// @Description		: ��ʯժȡ�������Ѻ���ı�ʯ�ᵽǰ�棩
// @ReturnCode		: 1 �ɹ�
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT KLuaItem::LuaStoneClean(QLuaScript& sc)
{
	KPlayerItem* pPlayerItem = NULL;
	KPlayer* pOwner = g_cPlayerMgr.GetByIndex(m_pIt->GetBelong());
	QCONFIRM_RET_NULL(pOwner);
	pPlayerItem = pOwner ? pOwner->GetCtrl<KPlayerItem>() : NULL;
	QCONFIRM_RET_NULL(pPlayerItem);

	KItem* pEquip = m_pIt;
	QCONFIRM_RET_NULL(pEquip);
	if(pPlayerItem->CleanStone(pEquip))
		sc.PushNumber(1);
	else
		sc.PushNumber(2);

	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: KLuaItem
// @LuaApiName		: StonePunch
// @Description		: ��ʯ���
// @ReturnCode		: 1 �ɹ�
// @ArgumentFlag	: d
// @ArgumentComment	: ��ʯ��λ��
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT KLuaItem::LuaStonePunch(QLuaScript& sc)
{
	INT nSlot = sc.GetInt(1);
	KPlayerItem* pPlayerItem = NULL;
	KPlayer* pOwner = g_cPlayerMgr.GetByIndex(m_pIt->GetBelong());
	QCONFIRM_RET_NULL(pOwner);
	pPlayerItem = pOwner ? pOwner->GetCtrl<KPlayerItem>() : NULL;
	QCONFIRM_RET_NULL(pPlayerItem);

	KItem* pEquip = m_pIt;

	sc.PushNumber(pPlayerItem->StonePunch(pEquip, nSlot));

	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: KLuaItem
// @LuaApiName		: GetStoneInfo
// @Description		: �õ�һ��װ���ı�ʯ��Ϣ
// @ReturnCode		: ��ʯ��Ϣ { {nStoneId = ?, nStoneLevel = ?}, 0, -1 } // 0:δ��ʯ�Ŀף�-1:û�п�
// @ArgumentFlag	: 
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT KLuaItem::LuaGetStoneInfo(QLuaScript& sc)
{
	INT nSlot = 0;
	KItem* pEquip = m_pIt;
	QCONFIRM_RET_NULL(pEquip);
	QCONFIRM_RET_NULL(KD_ISEQUIP(pEquip->GetGenre()));

	sc.PushTable();
		
	for(; nSlot < emSTONE_MAX_SLOT; ++nSlot)
	{
		sc.PushTable();

		if(nSlot < pEquip->GetStoneSlot())
		{
			sc.PushNumber(pEquip->m_aryStoneInfo[nSlot].byStoneId);
		}
		else
		{
			sc.PushNumber(-1);
		}
		sc.SetTableField("nStoneId");

		if(nSlot < pEquip->GetStoneSlot())
		{
			sc.PushNumber(pEquip->m_aryStoneInfo[nSlot].byStoneLevel);
		}
		else
		{
			sc.PushNumber(-1);
		}
		sc.SetTableField("nStoneLevel");

		sc.SetTableIndex(nSlot + 1);
	}

	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: KLuaItem
// @LuaApiName		: GetAppendAttr
// @Description		: �õ�һ��װ���ĸ���������Ϣ
// @ReturnCode		: ����������Ϣ { {nAttr = ?, nValue = ?}, ...}
// @ArgumentFlag	: 
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT KLuaItem::LuaGetAppendAttr(QLuaScript& sc)
{
	KItem* pEquip = m_pIt;
	QCONFIRM_RET_NULL(pEquip && KD_ISEQUIP(pEquip->GetGenre()));

	sc.PushTable();

	for(INT i = 0; i < emITEM_COUNT_APPEND; ++i)
	{
		sc.PushTable();

		sc.PushNumber(pEquip->m_aryAppendAttrib[i].nAttribType);
		sc.SetTableField("nAttr");

		sc.PushNumber(pEquip->m_aryAppendAttrib[i].nValue[0]);
		sc.SetTableField("nValue");

		sc.SetTableIndex(i + 1);
	}

	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: KLuaItem
// @LuaApiName		: GetUpgradeItems
// @Description		: �õ�װ���������������Ϣ
// @ReturnCode		: 
// @ArgumentFlag	: 
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT KLuaItem::LuaGetUpgradeItems(QLuaScript& sc)
{
	QCONFIRM_RET_FALSE(KD_ISEQUIP(m_pIt->GetGenre()));

	CONST KLibOfBPT* pLibBPT = g_cItemMgr.GetGenerator()->GetLibOfBPT();
	QCONFIRM_RET_FALSE(pLibBPT);
	KITEM_INDEX sIndex = { m_pIt->GetGenre(), m_pIt->GetDetailType(), m_pIt->GetParticular(), m_pIt->GetLevel() + 1};
	CONST KBASICPROP_EQUIPMENT* pEq = static_cast<CONST KBASICPROP_EQUIPMENT*>(pLibBPT->GetBasicProp(sIndex));
	QCONFIRM_RET_FALSE(pEq);

	sc.PushTable();

	for(INT i = 0; i < emITEM_COUNT_UPGRADE; ++i)
	{
		sc.PushTable();
		sc.PushNumber(pEq->aryNeedItems[i].nGenre);
		sc.SetTableField("nGenre");
		sc.PushNumber(pEq->aryNeedItems[i].nDetail);
		sc.SetTableField("nDetail");
		sc.PushNumber(pEq->aryNeedItems[i].nParticular);
		sc.SetTableField("nParticular");
		sc.PushNumber(pEq->aryNeedItems[i].nAmount);
		sc.SetTableField("nAmount");

		sc.SetTableIndex(i+1);
	}

	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: KLuaItem
// @LuaApiName		: GetSaveAppendAttr
// @Description		: �õ�һ��װ����ϴ����ĸ���������Ϣ
// @ReturnCode		: ����������Ϣ { {nAttr = ?, nValue = ?}, ...}
// @ArgumentFlag	: 
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT KLuaItem::LuaGetSaveAppendAttr(QLuaScript& sc)
{
	KItem* pEquip = m_pIt;
	QCONFIRM_RET_NULL(pEquip && KD_ISEQUIP(pEquip->GetGenre()));

	sc.PushTable();

	for(INT i = 0; i < emITEM_COUNT_APPEND; ++i)
	{
		sc.PushTable();

		sc.PushNumber(pEquip->m_arySaveAppendAttrib[i].nAttribType);
		sc.SetTableField("nAttr");

		sc.PushNumber(pEquip->m_arySaveAppendAttrib[i].nValue[0]);
		sc.SetTableField("nValue");

		sc.SetTableIndex(i + 1);
	}

	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: KLuaItem
// @LuaApiName		: GetBagPosLimit
// @Description		: ��ñ���λ������
// @ReturnCode		: 1�ɹ���
// @ArgumentFlag	: 
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT KLuaItem::LuaGetBagPosLimit(QLuaScript& sc)
{
	sc.PushNumber(m_pIt->GetBagPosLimit());
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: KLuaItem
// @LuaApiName		: GetNextReqLevel
// @Description		: �����һ�ȼ�װ��������ȼ�
// @ReturnCode		: 
// @ArgumentFlag	: 
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT KLuaItem::LuaGetNextReqLevel(QLuaScript& sc)
{
	QCONFIRM_RET_FALSE(KD_ISEQUIP(m_pIt->GetGenre()));
	CONST KLibOfBPT* pLibBPT = g_cItemMgr.GetGenerator()->GetLibOfBPT();
	QCONFIRM_RET_FALSE(pLibBPT);
	KITEM_INDEX sIndex = { m_pIt->GetGenre(), m_pIt->GetDetailType(), m_pIt->GetParticular(), m_pIt->GetLevel() + 1};
	CONST KBASICPROP_EQUIPMENT* pEq = static_cast<CONST KBASICPROP_EQUIPMENT*>(pLibBPT->GetBasicProp(sIndex));
	QCONFIRM_RET_FALSE(pEq);

	sc.PushNumber(pEq->nReqLevel);

	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: KLuaItem
// @LuaApiName		: GetStoneType
// @Description		: ��ñ�ʯ����
// @ReturnCode		: 
// @ArgumentFlag	: 
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT KLuaItem::LuaGetStoneType(QLuaScript& sc)
{
	QCONFIRM_RET_FALSE(KD_ISSTONE(m_pIt->GetGenre(), m_pIt->GetDetailType()));
	CONST KLibOfBPT* pLibBPT = g_cItemMgr.GetGenerator()->GetLibOfBPT();
	QCONFIRM_RET_FALSE(pLibBPT);
	KITEM_INDEX sIndex = { m_pIt->GetGenre(), m_pIt->GetDetailType(), m_pIt->GetParticular(), m_pIt->GetLevel()};
	CONST KBASICPROP_STONE* pEq = static_cast<CONST KBASICPROP_STONE*>(pLibBPT->GetBasicProp(sIndex));
	QCONFIRM_RET_FALSE(pEq);

	sc.PushNumber(pEq->nStoneType);

	return 1;
}

#ifdef GAME_SERVER

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: S
// @ClassName		: KLuaItem
// @LuaApiName		: BuyPrice
// @Description		: Ib��ֵ
// @Property(R/RW)	: RW
// @PropertyType	: INTEGER
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT KLuaItem::getBuyPrice(VOID) CONST
{
	return	m_pIt->GetBuyPrice();
}

VOID KLuaItem::setBuyPrice(INT nPrice)
{
	m_pIt->SetBuyPrice(nPrice);
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: S
// @ClassName		: KLuaItem
// @LuaApiName		: GUID
// @Description		: GUID���ַ���
// @Property(R/RW)	: R
// @PropertyType	: STRING
// @LuaMarkEnd
// -------------------------------------------------------------------------
LPCSTR KLuaItem::getGUID(VOID) CONST
{
	return m_pIt->GetGuidString();
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: S
// @ClassName		: KLuaItem
// @LuaApiName		: GenTime
// @Description		: ��������ʱ��
// @Property(R/RW)	: R
// @PropertyType	: DWORD
// @LuaMarkEnd
// -------------------------------------------------------------------------
DWORD KLuaItem::getGenTime(VOID) CONST
{
	return	m_pIt->GetGenTime();
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: S
// @ClassName		: KLuaItem
// @LuaApiName		: IsIbItem
// @Description		: �Ƿ�IB��Ʒ
// @ReturnCode		: 1:��,0:��
// @ArgumentFlag	: 
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT KLuaItem::LuaIsIbItem(QLuaScript& sc)
{
	sc.PushNumber(IB_IS_IB_ITEM(m_pIt->GetItemGUID()));
	return	1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: S
// @ClassName		: KLuaItem
// @LuaApiName		: Regenerate
// @Description		: ��������һ������
// @ReturnCode		: �ɹ�����1
// @ArgumentFlag	: ddddd???uu
// @ArgumentComment	: nGenre		
// @ArgumentComment	: nDetailType	
// @ArgumentComment	: nParticularType
// @ArgumentComment	: nLevel:���ߵȼ�
// @ArgumentComment	: nEnhTimes:������ǿ������
// @ArgumentComment	: ����table���ͣ���ΪStoneInfo��Table
// @ArgumentComment	: ����table���ͣ���Ϊ����������Ϣ
// @ArgumentComment	: ����table���ͣ���Ϊϴ��ʱ��ס������( {0, 0, 1, 1, 0, 0} ��ʾ��3��4������������ס�� )
// @ArgumentComment	: uRandSeed
// @ArgumentComment	: uRandSeedEx
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT KLuaItem::LuaRegenerate(QLuaScript& sc)
{
	INT nGenre			= sc.GetInt(1);
	INT nDetailType		= sc.GetInt(2);
	INT nParticularType	= sc.GetInt(3);
	INT nLevel			= sc.GetInt(4);
	INT nEnhTimes		= sc.GetInt(5);
	UINT uRandSeed		= sc.GetInt(9);
	UINT uRandSeedEx	= sc.GetInt(10);
	
	KItem::KREFINE_LOCK	aryLock[emITEM_COUNT_APPEND];
	KItem::KREFINE_LOCK* pRefineLock = NULL;

	KItem::KSTONE_INFO	aryStoneInfo[emSTONE_MAX_SLOT];
	KItem::KSTONE_INFO	*pStoneInfo = NULL;

	KMagicAttrib aryAppendAttr[emITEM_COUNT_APPEND];
	KMagicAttrib* pAppendAttr = NULL;

	INT nPlayerIdx = m_pIt->GetBelong();
	KPlayer* pPlayer = g_cPlayerMgr.GetByIndex(nPlayerIdx);
	QCONFIRM_RET_FALSE(pPlayer);

	KPlayerItem* pPlayerItem = pPlayer->GetCtrl<KPlayerItem>();
	QCONFIRM_RET_FALSE(pPlayerItem);

	if (sc.IsTable(6))
	{	// ��StoneInfo��Table
		pStoneInfo = aryStoneInfo;
		for (INT i = 0; i < emSTONE_MAX_SLOT; i++)
		{
			sc.GetTableIndex(6, i + 1);
			INT nIndex = sc.GetTopIndex();
			sc.GetTableField(nIndex, "nStoneId");
			pStoneInfo[i].byStoneId = sc.GetInt(nIndex + 1);

			sc.GetTableIndex(6, i + 1);
			nIndex = sc.GetTopIndex();
			sc.GetTableField(nIndex, "nStoneLevel");
			pStoneInfo[i].byStoneLevel = sc.GetInt(nIndex + 1);
		}
	}

	if (sc.IsTable(7))
	{
		pAppendAttr = aryAppendAttr;
		for(INT i = 0; i < emITEM_COUNT_APPEND; ++i)
		{
			sc.GetTableIndex(7, i + 1);
			INT nIndex = sc.GetTopIndex();
			sc.GetTableField(nIndex, "nAttr");
			pAppendAttr[i].nAttribType = sc.GetInt(nIndex + 1);

			sc.GetTableIndex(7, i + 1);
			nIndex = sc.GetTopIndex();
			sc.GetTableField(nIndex, "nValue");
			pAppendAttr[i].nValue[0] = sc.GetInt(nIndex + 1);
		}
	}

	if (sc.IsTable(8))
	{
		for(INT i = 0; i < emITEM_COUNT_APPEND; ++i)
		{
			pRefineLock = aryLock;
			sc.GetTableIndex(8, i + 1);
			INT nIndex = sc.GetTopIndex();
			INT nLock = sc.GetInt(nIndex);
			pRefineLock[i] = nLock;
		}
	}

	BOOL bRet = m_pIt->Regenerate(
		nGenre,
		nDetailType,
		nParticularType,
		nLevel,
		nEnhTimes,
		pStoneInfo,
		pAppendAttr,
		pRefineLock,
		uRandSeed,
		uRandSeedEx
	);

	if(KD_ISEQUIP(m_pIt->GetGenre()))
	{
		KITEM_POS sPos;
		pPlayerItem->GetItemPos(m_pIt->GetGameIndex(), sPos);

		if(sPos.eRoom == emROOM_EQUIP || sPos.eRoom == emROOM_EQUIPEX)
		{
			// ���¼�������ս����
			g_cCharacterHelper.CalcFightScore(*pPlayer);
			pPlayer->FireEvent(emKOBJEVENTTYPE_PLAYER_EQUIP_OPS, pPlayer->GetId(), 0, 0);
		}
	}
	
	sc.PushNumber(bRet);
	return	1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: S
// @ClassName		: KLuaItem
// @LuaApiName		: ClearSaveAppendAttr
// @Description		: ����ѱ����ϴ����������
// @ReturnCode		: 1�ɹ�
// @ArgumentFlag	: d
// @ArgumentComment	: nSaveOri
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT KLuaItem::LuaClearSaveAppendAttr(QLuaScript& sc)
{
	INT nSaveOri = sc.GetInt(1);

	m_pIt->ClearSaveAppendAttr(nSaveOri);

	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: S
// @ClassName		: KLuaItem
// @LuaApiName		: Sync
// @Description		: ͬ���������ݵ��ͻ���
// @ReturnCode		: 1�ɹ�
// @ArgumentFlag	: 
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT KLuaItem::LuaSync(QLuaScript& sc)
{
	INT nRet = 0;
	INT nPlayerIdx = m_pIt->GetBelong();
	if (nPlayerIdx <= 0)
		return	0;

	KPlayer* pPlayer = g_cPlayerMgr.GetByIndex(nPlayerIdx);
	QCONFIRM_RET_FALSE(pPlayer);
	KPlayerItem* pPlayerItem = pPlayer->GetCtrl<KPlayerItem>();
	QCONFIRM_RET_FALSE(pPlayerItem);
	nRet = pPlayerItem->SyncItem(m_pIt->GetGameIndex());

	sc.PushNumber(nRet);
	return	1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: S
// @ClassName		: KLuaItem
// @LuaApiName		: ChangeColorScheme
// @Description		: ����װ����ɫ����
// @ReturnCode		: 1�ɹ�
// @ArgumentFlag	: d
// @ArgumentComment	: nScheme:�µĻ�ɫ����
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT KLuaItem::LuaChangeColorScheme(QLuaScript& sc)
{
	return	1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: S
// @ClassName		: KLuaItem
// @LuaApiName		: SetCustom
// @Description		: ���õ����Զ����ַ���
// @ReturnCode		: 1�ɹ�
// @ArgumentFlag	: ds
// @ArgumentComment	: nCustomType:���ͣ���
// @ArgumentComment	: szCustom:�Զ����ַ���
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT KLuaItem::LuaSetCustom(QLuaScript& rcScript)
{
	KItem::KE_CUSTOM_TYPE eCustomType = (KItem::KE_CUSTOM_TYPE)rcScript.GetInt(1);
	LPCSTR pszCustom = rcScript.GetStr(2);
	rcScript.PushNumber(m_pIt->SetCustom(eCustomType, pszCustom));
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: S
// @ClassName		: KLuaItem
// @LuaApiName		: SetExtParam
// @Description		: ���õ���ExtParam
// @ReturnCode		: 1�ɹ�
// @ArgumentFlag	: dd
// @ArgumentComment	: λ��
// @ArgumentComment	: ����
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT KLuaItem::LuaSetExtParam(QLuaScript& rcScript)
{
	INT nIdx = rcScript.GetInt(1);
	INT nValue = rcScript.GetInt(2);

	// �������3��
	QCONFIRM_RET_NULL(nIdx >= 1 && nIdx <= 3);

	m_pIt->SetExtParam(nIdx - 1, nValue);

	return 0;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: S
// @ClassName		: KLuaItem
// @LuaApiName		: ApplyMagicAttrib
// @Description		: Ӧ��ħ�����ԣ�Ӧ���Ƶ�����ħ�������
// @ReturnCode		: 
// @ArgumentFlag	: s{dd}[d]
// @ArgumentComment	: szAttrib:ħ��������
// @ArgumentComment	: nValue1:ħ�����Բ���1
// @ArgumentComment	: nValue2:ħ�����Բ���2
// @ArgumentComment	: bSync:�Ƿ�ͬ���ͻ���
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT KLuaItem::LuaApplyMagicAttrib(QLuaScript &sc)
{
	INT nValue = 0;
	INT nAttrib = g_cMagicAttribMgr.GetIdFormString(sc.GetStr(1));
	if (nAttrib <= KD_MAGIC_INVALID)
		return	0;

	KCharacter* pPlayer = (KCharacter*)g_cPlayerMgr.GetByIndex(m_pIt->GetBelong());
	if(!pPlayer) return 0;

	KMagicAttrib sAttrib;
	sAttrib.nAttribType = nAttrib;
	for (INT i = 0; i < KD_MAGIC_VALUE_NUM; ++i)
	{
		sc.GetTableIndex(2, i + 1);
		nValue = sc.GetInt(-1);
		if(KD_ISMEDICINE(m_pIt->GetGenre()))
		{
			INT nMedicineEffect = pPlayer->GetMedicineEffect();
			// ҩƷ��ʵ�ʻظ��� = int��ҩƷ�������ظ��� * ��1 + ҩЧ / 100����
			nValue = (nValue * 100 + nMedicineEffect * nValue) / 100;
		}
		sAttrib.nValue[i] = nValue;
	}

	g_cMagicAttribMgr.ModifyAttrib(pPlayer, pPlayer, 0, sAttrib, FALSE);

	//if (sc.GetInt(4))
	//{
	//	// ͬ�����ͻ���
	//	KSYNC_NPC_ATTRIB sSync;
	//	sSync.cProtocol		= (PROTOCOL_MSG_TYPE)s2c_npcattrib;
	//	sSync.dwId			= m_pHim->GetId();
	//	sSync.sAttrib		= sAttrib;
	//	m_pHim->SendDataToNearRegion(&sSync, sizeof(sSync));
	//}

	return	0;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: S
// @ClassName		: KLuaItem
// @LuaApiName		: RemoveMagicAttrib
// @Description		: �Ƴ�NPC��ħ������
// @ReturnCode		: ��
// @ArgumentFlag	: s{dd}
// @ArgumentComment	: szAttrib:ħ��������
// @ArgumentComment	: nValue1:ħ�����Բ���1
// @ArgumentComment	: nValue2:ħ�����Բ���2
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT KLuaItem::LuaRemoveMagicAttrib(QLuaScript &sc)
{
	INT nAttrib = g_cMagicAttribMgr.GetIdFormString(sc.GetStr(1));
	if (nAttrib <= KD_MAGIC_INVALID)
		return	0;

	KCharacter* pPlayer = (KCharacter*)g_cPlayerMgr.GetByIndex(m_pIt->GetBelong());
	if(!pPlayer) return 0;

	KMagicAttrib sAttrib;
	sAttrib.nAttribType = nAttrib;
	for (INT i = 0; i < KD_MAGIC_VALUE_NUM; ++i)
	{
		sc.GetTableIndex(2, i + 1);
		sAttrib.nValue[i] = sc.GetInt(-1);
	}

	g_cMagicAttribMgr.ModifyAttrib(pPlayer, pPlayer, 0, sAttrib, TRUE);
	return	0;
}

#else	// #ifdef GAME_SERVER

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: C
// @ClassName		: KLuaItem
// @LuaApiName		: Intro
// @Description		: ���ߵ�������Ϣ
// @Property(R/RW)	: R
// @PropertyType	: STRING
// @LuaMarkEnd
// -------------------------------------------------------------------------
LPCSTR KLuaItem::getIntro(VOID) CONST
{
	return	m_pIt->GetIntro();
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: C
// @ClassName		: KLuaItem
// @LuaApiName		: Help
// @Description		: ���ߵ�������Ϣ
// @Property(R/RW)	: R
// @PropertyType	: STRING
// @LuaMarkEnd
// -------------------------------------------------------------------------
LPCSTR KLuaItem::getHelp(VOID) CONST
{
	return	m_pIt->GetHelp();
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: C
// @ClassName		: KLuaItem
// @LuaApiName		: Index
// @Description		: ���ߵ�ȫ��������
// @Property(R/RW)	: R
// @PropertyType	: INTEGER
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT KLuaItem::getIndex(VOID) CONST
{
	return	m_pIt->GetGameIndex();
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: C
// @ClassName		: KLuaItem
// @LuaApiName		: IconImage
// @Description		: 
// @Property(R/RW)	: R
// @PropertyType	: STRING
// @LuaMarkEnd
// -------------------------------------------------------------------------
LPCSTR KLuaItem::getIconImage(VOID) CONST
{
	return	m_pIt->GetIconImage();
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: C
// @ClassName		: KLuaItem
// @LuaApiName		: ViewImage
// @Description		: 
// @Property(R/RW)	: R
// @PropertyType	: STRING
// @LuaMarkEnd
// -------------------------------------------------------------------------
LPCSTR KLuaItem::getViewImage(VOID) CONST
{
	return	m_pIt->GetViewImage();
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: C
// @ClassName		: KLuaItem
// @LuaApiName		: TransparencyIcon
// @Description		: ����͸��ͼ��ͼ��
// @Property(R/RW)	: R
// @PropertyType	: STRING
// @LuaMarkEnd
// -------------------------------------------------------------------------
LPCSTR KLuaItem::getTransparencyIcon(VOID) CONST
{
	return	m_pIt->GetTransparencyIcon();
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: C
// @ClassName		: KLuaItem
// @LuaApiName		: MaskLayerIcon
// @Description		: ������ͼ��ͼ��
// @Property(R/RW)	: R
// @PropertyType	: STRING
// @LuaMarkEnd
// -------------------------------------------------------------------------
LPCSTR KLuaItem::getMaskLayerIcon(VOID) CONST
{
	return m_pIt->GetMaskLayerIcon();
}

#endif

#include "kluaitem_table.hpp"
// -------------------------------------------------------------------------
