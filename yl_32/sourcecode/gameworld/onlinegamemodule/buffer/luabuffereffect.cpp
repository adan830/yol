/********************************************************************
	created:	2012/06/20 11:55
	file base:	luabuffereffect.cpp
	author:		zhangjunjie
*********************************************************************/

#include "stdafx.h"
#include "onlinegamemodule/luabuffereffect.h"
#include "onlinegamemodule/characterbuffer.h"
#include "onlinegameworld/kluacharacter.h"
#include "buffer.h"
#include "buffermanager.h"
#include "../fightskill/fightskillsetting.h"
#include "onlinegameworld/kcharacter.h"
#include "onlinegameworld/kplayer.h"
#include "onlinegameworld/knpc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// -------------------------------------------------------------------------
INT LuaCharacterBufferEffect::Register2Character(QLuaScript& sc, QLunaBase* pLunaObj)
{
	KLuaCharacter* pLunaCharacter = dynamic_cast<KLuaCharacter*>(pLunaObj);
	QCONFIRM_RET_FALSE(pLunaCharacter);
	KCharacter* pCharacter = pLunaCharacter->GetHim();
	QCONFIRM_RET_FALSE(pCharacter);

	CharacterBuffer* pKCharacterBuffer = pCharacter->GetCtrl<CharacterBuffer>();
	QCONFIRM_RET_FALSE(pKCharacterBuffer);
	sc.PushObj(&pKCharacterBuffer->GetScriptInterface());

	return 1;
}



// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: LuaCharacterBufferEffect
// @LuaApiName		: DamageLifeV
// @Description		: �˺�����ֵ
// @ReturnCode		: 
// @ArgumentFlag	: d
// @ArgumentComment	: �˺�����ֵ��ֵ
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT	LuaCharacterBufferEffect::LuaDamageLifeV(QLuaScript& sc)
{
	return 1;
}


// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: LuaCharacterBufferEffect
// @LuaApiName		: DamageLifeP
// @Description		: �˺������ٷֱ�
// @ReturnCode		: 
// @ArgumentFlag	: d
// @ArgumentComment	: �˺�����ֵ�ٷֱ�ֵ
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT	LuaCharacterBufferEffect::LuaDamageLifeP(QLuaScript& sc)
{
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: LuaCharacterBufferEffect
// @LuaApiName		: DamageManaV
// @Description		: �˺�����ֵ
// @ReturnCode		: 
// @ArgumentFlag	: d
// @ArgumentComment	: �˺�����ֵ��ֵ
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT	LuaCharacterBufferEffect::LuaDamageManaV(QLuaScript& sc)
{
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: LuaCharacterBufferEffect
// @LuaApiName		: DamageManaP
// @Description		: �˺������ٷֱ�
// @ReturnCode		: 
// @ArgumentFlag	: d
// @ArgumentComment	: �˺�����ֵ�ٷֱ�ֵ
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT	LuaCharacterBufferEffect::LuaDamageManaP(QLuaScript& sc)
{
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: LuaCharacterBufferEffect
// @LuaApiName		: Stun
// @Description		: ѣ��
// @ReturnCode		: 
// @ArgumentFlag	: 
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT	LuaCharacterBufferEffect::LuaStun(QLuaScript& sc)
{
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: LuaCharacterBufferEffect
// @LuaApiName		: Fix
// @Description		: ����
// @ReturnCode		: 
// @ArgumentFlag	: 
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT	LuaCharacterBufferEffect::LuaFix(QLuaScript& sc)
{
	/*if (IS_PLAYER(m_rcCharacter.GetId()))
	{
		KPlayer* pPlayer = (KPlayer*)(&m_rcCharacter);
		DWORD dwSceneId = pPlayer->GetSceneId();
		pPlayer->m_cPlayerServer.TeleportTo2(GET_MAP_ID(dwSceneId), GET_MAP_COPY_INDEX(dwSceneId), pPlayer->m_nX, pPlayer->m_nY, pPlayer->m_nZ);
	}
	else if (IS_NPC(m_rcCharacter.GetId()))
	{
		KNpc* pNpc = (KNpc*)(&m_rcCharacter);
		pNpc->m_cNpcServer.TeleportTo(pNpc->GetSceneId(), pNpc->m_nX, pNpc->m_nY, pNpc->m_nZ);
	}*/
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: LuaCharacterBufferEffect
// @LuaApiName		: Fear
// @Description		: �־�
// @ReturnCode		: 
// @ArgumentFlag	: 
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT	LuaCharacterBufferEffect::LuaFear(QLuaScript& sc)
{
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: LuaCharacterBufferEffect
// @LuaApiName		: Silence
// @Description		: ��Ĭ
// @ReturnCode		: 
// @ArgumentFlag	: 
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT	LuaCharacterBufferEffect::LuaSilence(QLuaScript& sc)
{
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: LuaCharacterBufferEffect
// @LuaApiName		: Crazy
// @Description		: ���
// @ReturnCode		: 
// @ArgumentFlag	: 
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT	LuaCharacterBufferEffect::LuaCrazy(QLuaScript& sc)
{
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: LuaCharacterBufferEffect
// @LuaApiName		: SlowP
// @Description		: �����ƶ��ٶȰٷֱ�
// @ReturnCode		: 
// @ArgumentFlag	: d
// @ArgumentComment	: ���ٰٷֱ���ֵ
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT	LuaCharacterBufferEffect::LuaSlowP(QLuaScript& sc)
{
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: LuaCharacterBufferEffect
// @LuaApiName		: Knock
// @Description		: ����
// @ReturnCode		: 
// @ArgumentFlag	: ddddd
// @ArgumentComment	: ���˾���
// @ArgumentComment	: �Է�����x
// @ArgumentComment	: �Է�����y
// @ArgumentComment	: �Է�����z
// @ArgumentComment	: �Է�����
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT	LuaCharacterBufferEffect::LuaKnock(QLuaScript& sc)
{
	BOOL	bRet = FALSE;
	INT		nLength			= sc.GetInt(1) * CELL_LENGTH * 2;
	INT		nMePx			= sc.GetInt(2);
	INT		nMePy			= sc.GetInt(3);
	INT		nMePz			= sc.GetInt(4);
	INT		nHimDirection	= sc.GetInt(5);

	INT nDeltaX         = nLength * g_Cos(nHimDirection) / SIN_COS_NUMBER;
	INT nDeltaY         = nLength * g_Sin(nHimDirection) / SIN_COS_NUMBER;

	INT nDestX          = nMePx + nDeltaX;
	INT nDestY          = nMePy + nDeltaY;
	INT nDestZ			= nMePz;

	INT nLastOkX = 0;
	INT nLastOkY = 0;

	m_rcCharacter.CheckObstacleDest(nMePx, nMePy, nMePz, nDestX, nDestY, nDestZ, m_rcCharacter.m_nTouchRange, nLastOkX, nLastOkY);

	if (m_rcCharacter.GetIsFix() == 0 && m_rcCharacter.GetIsStun() == 0 && m_rcCharacter.GetMoveState() != cmsOnKnockedDown)
	{
		if (IS_PLAYER(m_rcCharacter.GetId()))
		{
			KPlayer* pPlayer = (KPlayer*)(&m_rcCharacter);
			pPlayer->m_cPlayerServer.SyncKnockToSelf(nDestX, nDestY, nDestZ);
		}
		else
		{
			m_rcCharacter.KnockTo(nLastOkX, nLastOkY, nDestZ, nHimDirection);
		}
	}

	sc.PushNumber(bRet);

	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: KLuaCharacter
// @LuaApiName		: JumpTo
// @Description		: ��Ծ��ָ����
// @ReturnCode		: 
// @ArgumentFlag	: dddddd
// @ArgumentComment	: ��ʼ������x
// @ArgumentComment	: ��ʼ������y
// @ArgumentComment	: ��ʼ������z
// @ArgumentComment	: Ŀ�������x
// @ArgumentComment	: Ŀ�������y
// @ArgumentComment	: Ŀ�������z
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT	LuaCharacterBufferEffect::LuaJumpTo(QLuaScript& sc)
{
	BOOL	bRet = FALSE;
	INT		nHimPx			= sc.GetInt(1);
	INT		nHimPy			= sc.GetInt(2);
	INT		nHimPz			= sc.GetInt(3);
	INT		nDestX			= sc.GetInt(4);
	INT		nDestY			= sc.GetInt(5);
	INT		nDestZ			= sc.GetInt(6);

	INT nLastOkX = 0;
	INT nLastOkY = 0;

	m_rcCharacter.CheckObstacleDest(nHimPx, nHimPy, nHimPz, nDestX, nDestY, nDestZ, m_rcCharacter.m_nTouchRange, nLastOkX, nLastOkY);

	sc.PushNumber(nLastOkX);
	sc.PushNumber(nLastOkY);
	sc.PushNumber(nDestZ);

	return 3;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: LuaCharacterBufferEffect
// @LuaApiName		: AddCurLifeV
// @Description		: ���ӵ�ǰ����ֵ
// @ReturnCode		: 
// @ArgumentFlag	: d
// @ArgumentComment	: ��������ֵ��ֵ
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT	LuaCharacterBufferEffect::LuaAddCurLifeV(QLuaScript& sc)
{
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: LuaCharacterBufferEffect
// @LuaApiName		: AddCurLifeP
// @Description		: ���ӵ�ǰ�����ٷֱ�
// @ReturnCode		: 
// @ArgumentFlag	: d
// @ArgumentComment	: ���������ٷֱ���ֵ
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT	LuaCharacterBufferEffect::LuaAddCurLifeP(QLuaScript& sc)
{
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: LuaCharacterBufferEffect
// @LuaApiName		: AddCurManaV
// @Description		: ���ӵ�ǰ����ֵ
// @ReturnCode		: 
// @ArgumentFlag	: d
// @ArgumentComment	: ��������ֵ��ֵ
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT	LuaCharacterBufferEffect::LuaAddCurManaV(QLuaScript& sc)
{
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: LuaCharacterBufferEffect
// @LuaApiName		: AddCurManaP
// @Description		: ���ӵ�ǰ�����ٷֱ�
// @ReturnCode		: 
// @ArgumentFlag	: d
// @ArgumentComment	: ���������ٷֱ���ֵ
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT	LuaCharacterBufferEffect::LuaAddCurManaP(QLuaScript& sc)
{
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: LuaCharacterBufferEffect
// @LuaApiName		: AddCurPowerV
// @Description		: ���ӵ�ǰ����ֵ
// @ReturnCode		: 
// @ArgumentFlag	: d
// @ArgumentComment	: ���Ӽ���ֵ��ֵ
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT	LuaCharacterBufferEffect::LuaAddCurPowerV(QLuaScript& sc)
{
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: LuaCharacterBufferEffect
// @LuaApiName		: AddCurPowerP
// @Description		: ���ӵ�ǰ����ֵ�ٷֱ�
// @ReturnCode		: 
// @ArgumentFlag	: d
// @ArgumentComment	: ���Ӽ���ֵ�ٷֱ���ֵ
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT	LuaCharacterBufferEffect::LuaAddCurPowerP(QLuaScript& sc)
{
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: LuaCharacterBufferEffect
// @LuaApiName		: DoDeath
// @Description		: ����
// @ReturnCode		: 
// @ArgumentFlag	: 
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT	LuaCharacterBufferEffect::LuaDoDeath(QLuaScript& sc)
{
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: LuaCharacterBufferEffect
// @LuaApiName		: DoRevive
// @Description		: ����
// @ReturnCode		: 
// @ArgumentFlag	: dd
// @ArgumentComment	: �����ǰ����ֵռ�������ֵ�İٷֱ�
// @ArgumentComment	: �����ǰ����/����ֵռ�������/����ֵ�İٷֱ�
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT	LuaCharacterBufferEffect::LuaDoRevive(QLuaScript& sc)
{
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: LuaGetCurrentBufferStack
// @LuaApiName		: GetCurrentBufferStack
// @Description		: �õ���ǰ��buff����
// @ReturnCode		: 
// @ArgumentFlag	: d
// @ArgumentComment	: nBufTemplateId
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT	LuaCharacterBufferEffect::LuaGetCurrentBufferStack(QLuaScript& sc)
{
	INT		nStack = 0;
	INT		nBufTemplateId	= sc.GetInt(1);
	CharacterBuffer* pCharacterBuffer = NULL;
	Buffer* pBuffer = NULL;

	pCharacterBuffer = m_rcCharacter.GetCtrl<CharacterBuffer>();
	LOG_PROCESS_ERROR(pCharacterBuffer);

	pBuffer = pCharacterBuffer->GetBufferByTemplateId(nBufTemplateId);
	LOG_PROCESS_ERROR(pBuffer);

	nStack = pBuffer->GetCurrentStackCount();

	sc.PushNumber(nStack);

	return 0;
EXIT0:
	sc.PushNumber(0);
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: LuaCharacterBufferEffect
// @LuaApiName		: ClearBuff
// @Description		: �����ӦID��Buff
// @ReturnCode		: 
// @ArgumentFlag	: d
// @ArgumentComment	: ��Ҫ�����Buff��ID
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT	LuaCharacterBufferEffect::LuaClearBuff(QLuaScript& sc)
{
	INT		nBufTemplateId	= sc.GetInt(1);
	INT nIdx = 0;
	BOOL bResult = FALSE;
	CharacterBuffer* pCharacterBuffer = NULL;
	Buffer* pBuffer = NULL;

	pCharacterBuffer = m_rcCharacter.GetCtrl<CharacterBuffer>();
	LOG_PROCESS_ERROR(pCharacterBuffer);

	pBuffer = pCharacterBuffer->GetBufferByTemplateId(nBufTemplateId);
	if (!pBuffer) 
	{
		g_cBufferMgr.RemoveGroundBufferByCasterId(m_rcCharacter.GetId(), nBufTemplateId);
		return 0;
	}

	nIdx = g_cBufferMgr.GetIndexById(pBuffer->GetID());
	bResult = g_cBufferMgr.RemoveBufferFromCharacter(m_rcCharacter.GetId(), nIdx);

	LOG_PROCESS_ERROR(bResult);

	return 0;
EXIT0:
	sc.PushNumber(0);
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: LuaCharacterBufferEffect
// @LuaApiName		: HasBuff
// @Description		: �ж���������Ƿ��ж�Ӧģ��id��buff
// @ReturnCode		: 
// @ArgumentFlag	: d
// @ArgumentComment	: buffTemplateId
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT	LuaCharacterBufferEffect::LuaHasBuff(QLuaScript& sc)
{
	INT nBufTemplateId	= sc.GetInt(1);
	CharacterBuffer* pCharacterBuffer = NULL;
	Buffer* pBuffer = NULL;

	pCharacterBuffer = m_rcCharacter.GetCtrl<CharacterBuffer>();
	LOG_PROCESS_ERROR(pCharacterBuffer);

	pBuffer = pCharacterBuffer->GetBufferByTemplateId(nBufTemplateId);
	if (pBuffer) 
	{
		sc.PushNumber(1);
	}
	else
	{
		sc.PushNumber(0);
	}

EXIT0:
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: LuaCharacterBufferEffect
// @LuaApiName		: ClearCurrentBuff
// @Description		: �����ӦID��Buff
// @ReturnCode		: 
// @ArgumentFlag	: 
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT	LuaCharacterBufferEffect::LuaClearCurrentBuff(QLuaScript& sc)
{
	CharacterBuffer*	pCharacterBuffer = NULL;
	GroundBuffer*	pGroundProcBuff = NULL;
	Buffer*			pCharacterProcBuff = NULL;
	BOOL bC = FALSE;
	BOOL bG = FALSE;
	INT nIdx = 0;

	pCharacterBuffer = m_rcCharacter.GetCtrl<CharacterBuffer>();
	LOG_PROCESS_ERROR(pCharacterBuffer);

	pCharacterProcBuff = pCharacterBuffer->GetCurrentProcessingBuffer();
	pGroundProcBuff		= g_cBufferMgr.GetCurrentProcessingBuff();
	bC = (pCharacterProcBuff != NULL);
	bG = (pGroundProcBuff != NULL);
	PROCESS_ERROR(bC | bG);

	if (pGroundProcBuff)
	{
		g_cBufferMgr.RemoveGroundBuffer(pGroundProcBuff->m_dwId, TRUE);
	}
	else
	{
		nIdx = g_cBufferMgr.GetIndexById(pCharacterProcBuff->GetID());
		g_cBufferMgr.RemoveBufferFromCharacter(m_rcCharacter.GetId(), nIdx);
		
	}

	return 0;
EXIT0:
	sc.PushNumber(0);
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: LuaSetCurrentBuffer
// @LuaApiName		: SetCurrentBuffer
// @Description		: ���õ�ǰ��Чbuffer
// @ReturnCode		: 
// @ArgumentFlag	: 
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT	LuaCharacterBufferEffect::LuaSetCurrentBuffer(QLuaScript& sc)
{
	Buffer* pBuffer = NULL;
	INT nBufTemplateId = sc.GetInt(1);
	CharacterBuffer* pCharacterBuffer = m_rcCharacter.GetCtrl<CharacterBuffer>();
	LOG_PROCESS_ERROR(pCharacterBuffer);

	pBuffer = pCharacterBuffer->GetBufferByTemplateId(nBufTemplateId);
	LOG_PROCESS_ERROR(pBuffer);
	pCharacterBuffer->SetCurrentProcessingBuffer(pBuffer);
	
	return 0;
EXIT0:
	sc.PushNumber(0);
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: LuaCharacterBufferEffect
// @LuaApiName		: ClearBuffByType
// @Description		: ����ض����͵�buff
// @ReturnCode		: 
// @ArgumentFlag	: d
// @ArgumentComment	: ��Ҫ�����Buff������
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT	LuaCharacterBufferEffect::LuaClearBuffByType(QLuaScript& sc)
{
	INT nType = sc.GetInt(1);
	CharacterBuffer* pCharacterBuffer = m_rcCharacter.GetCtrl<CharacterBuffer>();
	LOG_PROCESS_ERROR(pCharacterBuffer);

	{
		const ObjectBuffer::BUFFER_ARRAY& buffers = pCharacterBuffer->GetBuffers();
		std::vector<DWORD> delete_buffer;

		for(size_t i = 0; i < buffers.size(); ++i)
		{
			if( buffers[i]->GetBufferType() == nType)
			{
				INT nIdx = g_cBufferMgr.GetIndexById(buffers[i]->GetID());
				delete_buffer.push_back(nIdx);
			}
		}

		for(size_t i = 0; i < delete_buffer.size(); ++i)
		{
			g_cBufferMgr.RemoveBufferFromCharacter(m_rcCharacter.GetId(), delete_buffer[i]);
		}
	}

	return 0;
EXIT0:
	sc.PushNumber(0);
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: LuaCharacterBufferEffect
// @LuaApiName		: ClearCD
// @Description		: ������ܵ���ȴʱ��
// @ReturnCode		: 
// @ArgumentFlag	: dd
// @ArgumentComment	: ���ܵ�Category���ͣ���Ӧ��Skill��
// @ArgumentComment	: ���ܵ�Categoryֵ����Ӧ��Skill��Ķ�ӦCategory��
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT	LuaCharacterBufferEffect::LuaClearCD(QLuaScript& sc)
{

	// TODO zhaoyu
	/*
	return 0;
EXIT0:
	sc.PushNumber(0);
	return 1;
	*/
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: LuaCharacterBufferEffect
// @LuaApiName		: PullTarget
// @Description		: ��Ŀ�������Լ���ߣ����ص��ٶȹ̶���Ŀ����Ҫִ�������غ����ִ������ָ��
// @ReturnCode		: 
// @ArgumentFlag	: ddddd
// @ArgumentComment	: ���˾���
// @ArgumentComment	: �Է�����x
// @ArgumentComment	: �Է�����y
// @ArgumentComment	: �Է�����z
// @ArgumentComment	: �Է�����
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT	LuaCharacterBufferEffect::LuaPullTarget(QLuaScript& sc)
{
	BOOL	bRet = FALSE;
	INT		nLength			= sc.GetInt(1) * CELL_LENGTH * 2;
	INT		nHimPx			= sc.GetInt(2);
	INT		nHimPy			= sc.GetInt(3);
	INT		nHimPz			= sc.GetInt(4);
	INT		nHimDirection	= sc.GetInt(5);

	INT nSelfX, nSelfY, nSelfZ;
	m_rcCharacter.GetPosition(nSelfX, nSelfY, nSelfZ);

	nHimDirection = g_GetDirection(nHimPx, nHimPy, nSelfX, nSelfY);

	INT nDeltaX         = nLength * g_Cos(nHimDirection) / SIN_COS_NUMBER;
	INT nDeltaY         = nLength * g_Sin(nHimDirection) / SIN_COS_NUMBER;

	INT nDestX          = nHimPx + nDeltaX;
	INT nDestY          = nHimPy + nDeltaY;
	INT nDestZ			= nHimPz;

	INT nLastOkX = 0;
	INT nLastOkY = 0;

	m_rcCharacter.CheckObstacleDest(nSelfX, nSelfY, nSelfZ, nDestX, nDestY, nDestZ, m_rcCharacter.m_nTouchRange, nLastOkX, nLastOkY);

	//if (m_rcCharacter.GetIsFix() == 0 && m_rcCharacter.GetIsStun() == 0 && m_rcCharacter.GetMoveState() != cmsOnPull)
	if (m_rcCharacter.GetMoveState() != cmsOnPull)
	{
		if (IS_PLAYER(m_rcCharacter.GetId()))
		{
			KPlayer* pPlayer = (KPlayer*)(&m_rcCharacter);
			pPlayer->m_cPlayerServer.SyncPullToSelf(nDestX, nDestY, nDestZ);
		}
		else
		{
			bRet = m_rcCharacter.Pull(nDestX, nDestY, nDestZ, nHimDirection);
		}
	}
	
	sc.PushNumber(bRet);

	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: LuaCharacterBufferEffect
// @LuaApiName		: SetMapPos
// @Description		: ���͵�Ŀ���ͼ�Ķ�Ӧ��
// @ReturnCode		: 
// @ArgumentFlag	: ddd
// @ArgumentComment	: ��ͼID����Ӧ��MapList֮������ñ�
// @ArgumentComment	: X��ƫ����
// @ArgumentComment	: Y��ƫ����
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT	LuaCharacterBufferEffect::LuaSetMapPos(QLuaScript& sc)
{
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: LuaCharacterBufferEffect
// @LuaApiName		: Tp
// @Description		: ������
// @ReturnCode		: 
// @ArgumentFlag	: d
// @ArgumentComment	: ����Id��1��������ԯ��2����а���ף�3��������ڤ��4����Ӱɭ��
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT	LuaCharacterBufferEffect::LuaTp(QLuaScript& sc)
{
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: LuaCharacterBufferEffect
// @LuaApiName		: IgnorarmorV
// @Description		: ����Ŀ�껤��ֵ
// @ReturnCode		: 
// @ArgumentFlag	: d
// @ArgumentComment	: ���Ի���ֵ��ֵ
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT	LuaCharacterBufferEffect::LuaIgnorarmorV(QLuaScript& sc)
{
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: LuaCharacterBufferEffect
// @LuaApiName		: AddBuffTime
// @Description		: ��Ӷ�ӦBuff�ĳ���ʱ��
// @ReturnCode		: 
// @ArgumentFlag	: ddd
// @ArgumentComment	: ���ܵ�Category���ͣ���Ӧ��Buff��
// @ArgumentComment	: ���ܵ�Categoryֵ����Ӧ��Buff��Ķ�ӦCategory��
// @ArgumentComment	: ���ӵ�֡����ֵ
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT	LuaCharacterBufferEffect::LuaAddBuffTime(QLuaScript& sc)
{
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: LuaCharacterBufferEffect
// @LuaApiName		: RefreshBuffTime
// @Description		: ˢ�¶�ӦBuff�ĳ���ʱ��
// @ReturnCode		: 
// @ArgumentFlag	: dd
// @ArgumentComment	: ���ܵ�Category���ͣ���Ӧ��Buff��
// @ArgumentComment	: ���ܵ�Categoryֵ����Ӧ��Buff��Ķ�ӦCategory�� 
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT	LuaCharacterBufferEffect::LuaRefreshBuffTime(QLuaScript& sc)
{
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: LuaCharacterBufferEffect
// @LuaApiName		: ModifyDmgP
// @Description		: ������ɵ��˺��ٷֱȣ�Ϊ�����˺�
// @ReturnCode		: 
// @ArgumentFlag	: ddd
// @ArgumentComment	: ���ܵ�Category���ͣ���Ӧ��Skill������-1������Ϊ���м��ܶ�����
// @ArgumentComment	: ���ܵ�Categoryֵ����Ӧ��Skill��Ķ�ӦCategory�У�����һ������Ϊ-1ʱ�����壬����һ��������Ϊ-1ʱ����ֵ����-1 
// @ArgumentComment	: �����˺��İٷֱ���ֵ
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT	LuaCharacterBufferEffect::LuaModifyDmgP(QLuaScript& sc)
{
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: LuaCharacterBufferEffect
// @LuaApiName		: ModifyDmgV
// @Description		: ������ɵ��˺���ֵ��Ϊ�����˺�
// @ReturnCode		: 
// @ArgumentFlag	: ddd
// @ArgumentComment	: ���ܵ�Category���ͣ���Ӧ��Buff��
// @ArgumentComment	: ���ܵ�Categoryֵ����Ӧ��Buff��Ķ�ӦCategory�У�����һ������Ϊ-1ʱ�����壬����һ��������Ϊ-1ʱ����ֵ����-1  
// @ArgumentComment	: �����˺�����ֵ
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT	LuaCharacterBufferEffect::LuaModifyDmgV(QLuaScript& sc)
{
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: LuaCharacterBufferEffect
// @LuaApiName		: AddConst
// @Description		: ��������
// @ReturnCode		: 
// @ArgumentFlag	: d
// @ArgumentComment	: ���ӵ����ʵ���ֵ
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT	LuaCharacterBufferEffect::LuaAddConst(QLuaScript& sc)
{
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: LuaCharacterBufferEffect
// @LuaApiName		: AddStrth
// @Description		: ���ӽ��
// @ReturnCode		: 
// @ArgumentFlag	: d
// @ArgumentComment	: ���ӽ�ǵ���ֵ
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT	LuaCharacterBufferEffect::LuaAddStrth(QLuaScript& sc)
{
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: LuaCharacterBufferEffect
// @LuaApiName		: AddAgile
// @Description		: ������
// @ReturnCode		: 
// @ArgumentFlag	: d
// @ArgumentComment	: ����������ֵ
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT	LuaCharacterBufferEffect::LuaAddAgile(QLuaScript& sc)
{
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: LuaCharacterBufferEffect
// @LuaApiName		: AddIntel
// @Description		: ��������
// @ReturnCode		: 
// @ArgumentFlag	: d
// @ArgumentComment	: ������������ֵ
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT	LuaCharacterBufferEffect::LuaAddIntel(QLuaScript& sc)
{
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: LuaCharacterBufferEffect
// @LuaApiName		: AddSpirt
// @Description		: ���Ӿ���
// @ReturnCode		: 
// @ArgumentFlag	: d
// @ArgumentComment	: ���Ӿ������ֵ
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT	LuaCharacterBufferEffect::LuaAddSpirt(QLuaScript& sc)
{
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: LuaCharacterBufferEffect
// @LuaApiName		: AddAllAttributeV
// @Description		: ����ȫ����ֵ
// @ReturnCode		: 
// @ArgumentFlag	: d
// @ArgumentComment	: ����ȫ���Ե���ֵ
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT	LuaCharacterBufferEffect::LuaAddAllAttributeV(QLuaScript& sc)
{
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: LuaCharacterBufferEffect
// @LuaApiName		: AddAllAttributeP
// @Description		: ����ȫ���԰ٷֱ�
// @ReturnCode		: 
// @ArgumentFlag	: d
// @ArgumentComment	: ���Ӱٷֱȵ���ֵ
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT	LuaCharacterBufferEffect::LuaAddAllAttributeP(QLuaScript& sc)
{
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: LuaCharacterBufferEffect
// @LuaApiName		: AddMaxLifeV
// @Description		: ��ֵ������������ֵ
// @ReturnCode		: 
// @ArgumentFlag	: d
// @ArgumentComment	: ���ӵ���������ֵ��ֵ
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT	LuaCharacterBufferEffect::LuaAddMaxLifeV(QLuaScript& sc)
{
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: LuaCharacterBufferEffect
// @LuaApiName		: AddMaxLifeP
// @Description		: ���ٷֱ�������������ֵ
// @ReturnCode		: 
// @ArgumentFlag	: d
// @ArgumentComment	: ���ӵ��������ްٷֱ���ֵ
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT	LuaCharacterBufferEffect::LuaAddMaxLifeP(QLuaScript& sc)
{
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: LuaCharacterBufferEffect
// @LuaApiName		: AddMaxManaV
// @Description		: ��ֵ������������ֵ
// @ReturnCode		: 
// @ArgumentFlag	: d
// @ArgumentComment	: ���ӵ���������ֵ��ֵ
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT	LuaCharacterBufferEffect::LuaAddMaxManaV(QLuaScript& sc)
{
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: LuaCharacterBufferEffect
// @LuaApiName		: AddMaxManaP
// @Description		: ���ٷֱ�������������ֵ
// @ReturnCode		: 
// @ArgumentFlag	: d
// @ArgumentComment	: ���ӵ��������ްٷֱ���ֵ
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT	LuaCharacterBufferEffect::LuaAddMaxManaP(QLuaScript& sc)
{
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: LuaCharacterBufferEffect
// @LuaApiName		: AddMaxPowerV
// @Description		: ��ֵ���Ӽ���ֵ����ֵ
// @ReturnCode		: 
// @ArgumentFlag	: d
// @ArgumentComment	: ���ӵļ���ֵ����ֵ��ֵ
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT	LuaCharacterBufferEffect::LuaAddMaxPowerV(QLuaScript& sc)
{
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: LuaCharacterBufferEffect
// @LuaApiName		: AddMaxPowerP
// @Description		: ���ٷֱ����Ӽ���ֵ����ֵ
// @ReturnCode		: 
// @ArgumentFlag	: d
// @ArgumentComment	: ���ӵļ���ֵ���ްٷֱ���ֵ
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT	LuaCharacterBufferEffect::LuaAddMaxPowerP(QLuaScript& sc)
{
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: LuaCharacterBufferEffect
// @LuaApiName		: AddHitRateV
// @Description		: ��������ֵ
// @ReturnCode		: 
// @ArgumentFlag	: d
// @ArgumentComment	: ��������ֵ��ֵ
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT	LuaCharacterBufferEffect::LuaAddHitRateV(QLuaScript& sc)
{
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: LuaCharacterBufferEffect
// @LuaApiName		: AddCriticalRateV
// @Description		: ���ӻ���һ��ֵ
// @ReturnCode		: 
// @ArgumentFlag	: d
// @ArgumentComment	: ���ӻ���һ������ֵ
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT	LuaCharacterBufferEffect::LuaAddCriticalRateV(QLuaScript& sc)
{
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: LuaCharacterBufferEffect
// @LuaApiName		: AddSkillCriticalRateV
// @Description		: ���ӹ̶����ܵĻ���һ��ֵ
// @ReturnCode		: 
// @ArgumentFlag	: ddd
// @ArgumentComment	: ���ܵ�Category���ͣ���Ӧ��Skill��
// @ArgumentComment	: ���ܵ�Categoryֵ����Ӧ��Skill��Ķ�ӦCategory�У�����һ������Ϊ-1ʱ�����壬����һ��������Ϊ-1ʱ����ֵ����-1  
// @ArgumentComment	: ���ӵĻ���һ��ֵ����ֵ
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT	LuaCharacterBufferEffect::LuaAddSkillCriticalRateV(QLuaScript& sc)
{
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: LuaCharacterBufferEffect
// @LuaApiName		: AddCriticalDmgP
// @Description		: ���ӻ���һ���˺��ٷֱ�
// @ReturnCode		: 
// @ArgumentFlag	: d
// @ArgumentComment	: �����˺��İٷֱ�
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT	LuaCharacterBufferEffect::LuaAddCriticalDmgP(QLuaScript& sc)
{
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: LuaCharacterBufferEffect
// @LuaApiName		: AddRunSpeedV
// @Description		: �����ƶ��ٶ�
// @ReturnCode		: 
// @ArgumentFlag	: d
// @ArgumentComment	: �����ٶ���ֵ
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT	LuaCharacterBufferEffect::LuaAddRunSpeedV(QLuaScript& sc)
{
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: LuaCharacterBufferEffect
// @LuaApiName		: AddArmorV
// @Description		: ���ӻ���ֵ
// @ReturnCode		: 
// @ArgumentFlag	: d
// @ArgumentComment	: ���ӻ��׵���ֵ
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT	LuaCharacterBufferEffect::LuaAddArmorV(QLuaScript& sc)
{
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: LuaCharacterBufferEffect
// @LuaApiName		: AddDodgeV
// @Description		: ��������ֵ
// @ReturnCode		: 
// @ArgumentFlag	: d
// @ArgumentComment	: �������ܵ���ֵ
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT	LuaCharacterBufferEffect::LuaAddDodgeV(QLuaScript& sc)
{
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: LuaCharacterBufferEffect
// @LuaApiName		: HideToNpc
// @Description		: ��npc����
// @ReturnCode		: 
// @ArgumentFlag	: 
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT	LuaCharacterBufferEffect::LuaHideToNpc(QLuaScript& sc)
{
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: LuaCharacterBufferEffect
// @LuaApiName		: HideToPlayer
// @Description		: ���������
// @ReturnCode		: 
// @ArgumentFlag	: 
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT	LuaCharacterBufferEffect::LuaHideToPlayer(QLuaScript& sc)
{
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: LuaCharacterBufferEffect
// @LuaApiName		: AddThreat
// @Description		: ���ӳ��ֵ
// @ReturnCode		: 
// @ArgumentFlag	: d
// @ArgumentComment	: ���ӵĳ�޵���ֵ
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT	LuaCharacterBufferEffect::LuaAddThreat(QLuaScript& sc)
{
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: LuaCharacterBufferEffect
// @LuaApiName		: ReboundDmgP
// @Description		: �����������˺�
// @ReturnCode		: 
// @ArgumentFlag	: d
// @ArgumentComment	: �����˺��İٷֱ�
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT	LuaCharacterBufferEffect::LuaReboundDmgP(QLuaScript& sc)
{
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: LuaCharacterBufferEffect
// @LuaApiName		: ReboundDmgV
// @Description		: ��ֵ�����˺�
// @ReturnCode		: 
// @ArgumentFlag	: d
// @ArgumentComment	: �����˺�����ֵ
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT	LuaCharacterBufferEffect::LuaReboundDmgV(QLuaScript& sc)
{
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: LuaCharacterBufferEffect
// @LuaApiName		: ReduceDmg
// @Description		: ��������С�˺�
// @ReturnCode		: 
// @ArgumentFlag	: dd
// @ArgumentComment	: ��С�˺��ٷֱ�
// @ArgumentComment	: ��С���˺����ֵռ�������޵İٷֱȣ���-1Ϊ������
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT	LuaCharacterBufferEffect::LuaReduceDmg(QLuaScript& sc)
{
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: LuaCharacterBufferEffect
// @LuaApiName		: ReduceDmgByMana
// @Description		: ʹ������ֵ�ֵ��˺�
// @ReturnCode		: 
// @ArgumentFlag	: ddd
// @ArgumentComment	: �ֵ��˺��İٷֱ�
// @ArgumentComment	: ÿ�ֵ�һ���˺���Ҫ���ĵ�����ֵ
// @ArgumentComment	: �ֵ��˺�������ռ�������޵İٷֱȣ���-1Ϊ������
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT	LuaCharacterBufferEffect::LuaReduceDmgByMana(QLuaScript& sc)
{
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: LuaCharacterBufferEffect
// @LuaApiName		: TransDmgToLife
// @Description		: ��ɵ��˺�ת��Ϊ���������ظ�
// @ReturnCode		: 
// @ArgumentFlag	: d
// @ArgumentComment	: �˺�ת�������İٷֱ���ֵ
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT	LuaCharacterBufferEffect::LuaTransDmgToLife(QLuaScript& sc)
{
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: LuaCharacterBufferEffect
// @LuaApiName		: TransDmgToMana
// @Description		: ��ɵ��˺�ת��Ϊ���������ظ�
// @ReturnCode		: 
// @ArgumentFlag	: d
// @ArgumentComment	: �˺�ת����������
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT	LuaCharacterBufferEffect::LuaTransDmgToMana(QLuaScript& sc)
{
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: LuaCharacterBufferEffect
// @LuaApiName		: ForceAttack
// @Description		: ǿ��Buff�Ľ����߹���Buff�ķ�����
// @ReturnCode		: 
// @ArgumentFlag	: 
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT	LuaCharacterBufferEffect::LuaForceAttack(QLuaScript& sc)
{
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: LuaCharacterBufferEffect
// @LuaApiName		: ChangeChannelType
// @Description		: �ı似�ܵ���������
// @ReturnCode		: 
// @ArgumentFlag	: dd
// @ArgumentComment	: ���ܵ�Category���ͣ���Ӧ��Skill��
// @ArgumentComment	: ���ܵ�Categoryֵ����Ӧ��Skill��Ķ�ӦCategory�У�����һ������Ϊ-1ʱ�����壬����һ��������Ϊ-1ʱ����ֵ����-1  
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT	LuaCharacterBufferEffect::LuaChangeChannelType(QLuaScript& sc)
{
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: LuaCharacterBufferEffect
// @LuaApiName		: ReduceChannelTime
// @Description		: ��������ʱ��
// @ReturnCode		: 
// @ArgumentFlag	: ddd
// @ArgumentComment	: ���ܵ�Category���ͣ���Ӧ��Skill��������-1
// @ArgumentComment	: ���ܵ�Categoryֵ����Ӧ��Skill��Ķ�ӦCategory�У���ֵ����-1 
// @ArgumentComment	: ���̵�֡��
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT	LuaCharacterBufferEffect::LuaReduceChannelTime(QLuaScript& sc)
{
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: LuaCharacterBufferEffect
// @LuaApiName		: AddBuff
// @Description		: ��Buff�Ľ��������Buff
// @ReturnCode		: 
// @ArgumentFlag	: d
// @ArgumentComment	: ��ӵ�Buff��ID
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT	LuaCharacterBufferEffect::LuaAddBuff(QLuaScript& sc)
{
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: LuaCharacterBufferEffect
// @LuaApiName		: AddBuffToSender
// @Description		: ��Buff�ķ��������Buff
// @ReturnCode		: 
// @ArgumentFlag	: d
// @ArgumentComment	: ��ӵ�Buff��ID
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT	LuaCharacterBufferEffect::LuaAddBuffToSender(QLuaScript& sc)
{
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: LuaCharacterBufferEffect
// @LuaApiName		: KillSelf
// @Description		: ������ħ������������Buff����
// @ReturnCode		: 
// @ArgumentFlag	: 
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT	LuaCharacterBufferEffect::LuaKillSelf(QLuaScript& sc)
{
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: LuaCharacterBufferEffect
// @LuaApiName		: IgnorBuff
// @Description		: ����Buff���ɳ�Ϊ������Buff�Ľ����ߣ����Ǹ�Buff������Ч������Ը�Ŀ�����Ӱ��
// @ReturnCode		: 
// @ArgumentFlag	: d
// @ArgumentComment	: ���ߵ�Buff��ID(+:���-:)
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT	LuaCharacterBufferEffect::LuaIgnorBuff(QLuaScript& sc)
{
	INT nBuffID = sc.GetInt(1);

	ObjectBuffer::BUFFER_ARRAY::const_iterator iter;
	CharacterBuffer* pCharacterBuffer = m_rcCharacter.GetCtrl<CharacterBuffer>();
	LOG_PROCESS_ERROR(pCharacterBuffer);

	pCharacterBuffer->AddIgnoreBuffID(nBuffID);

EXIT0:
	return 0;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: LuaCharacterBufferEffect
// @LuaApiName		: IgnorBuffGroup
// @Description		: ����ĳһ��Group��BuffЧ�����ɳ�Ϊ������Buff�Ľ����ߣ����Ǹ�Buff������Ч������Ը�Ŀ�����Ӱ��
// @ReturnCode		: 
// @ArgumentFlag	: d
// @ArgumentComment	: ���ߵ�Buff��Group��ID
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT	LuaCharacterBufferEffect::LuaIgnorBuffGroup(QLuaScript& sc)
{
	INT nCateGroup = sc.GetInt(1);

	ObjectBuffer::BUFFER_ARRAY::const_iterator iter;
	CharacterBuffer* pCharacterBuffer = m_rcCharacter.GetCtrl<CharacterBuffer>();
	LOG_PROCESS_ERROR(pCharacterBuffer);

	pCharacterBuffer->AddIgnoreBuffGroup(nCateGroup);

EXIT0:
	return 0;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: LuaCharacterBufferEffect
// @LuaApiName		: IgnorBuffCate
// @Description		: ����ĳһ��Cate��BuffЧ�����ɳ�Ϊ������Buff�Ľ����ߣ����Ǹ�Buff������Ч������Ը�Ŀ�����Ӱ��
// @ReturnCode		: 
// @ArgumentFlag	: dd
// @ArgumentComment	: ���ܵ�Category���ͣ���Ӧ��Buff��������-1
// @ArgumentComment	: ���ܵ�Categoryֵ����Ӧ��Buff��Ķ�ӦCategory�У���ֵ����-1 
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT	LuaCharacterBufferEffect::LuaIgnorBuffCate(QLuaScript& sc)
{
	INT		nCateType		= sc.GetInt(1);
	INT		nCateId			= sc.GetInt(2);

	ObjectBuffer::BUFFER_ARRAY::const_iterator iter;
	CharacterBuffer* pCharacterBuffer = m_rcCharacter.GetCtrl<CharacterBuffer>();
	LOG_PROCESS_ERROR(pCharacterBuffer);

	pCharacterBuffer->AddIgnoreBuffCate(nCateType, nCateId);

EXIT0:
	return 0;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: LuaCharacterBufferEffect
// @LuaApiName		: CastSkill
// @Description		: �ͷż��ܣ���ΪOut������������Buff��ӵ�������¼��Ľ������ͷţ���ΪIn���¼�������Buff��ӵ�������¼��ķ������ͷ�
// @ReturnCode		: 
// @ArgumentFlag	: d
// @ArgumentComment	: �ͷŵļ��ܵ�ID
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT	LuaCharacterBufferEffect::LuaCastSkill(QLuaScript& sc)
{
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: LuaCharacterBufferEffect
// @LuaApiName		: AddTreatLifeV
// @Description		: ������������ֵ
// @ReturnCode		: 
// @ArgumentFlag	: d
// @ArgumentComment	: ���ӵ���ֵ
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT	LuaCharacterBufferEffect::LuaAddTreatLifeV(QLuaScript& sc)
{
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: LuaCharacterBufferEffect
// @LuaApiName		: AddTreatLifeP
// @Description		: �������������ٷֱ�
// @ReturnCode		: 
// @ArgumentFlag	: d
// @ArgumentComment	: �������������İٷֱ���ֵ����Ӧ��Skill���SkillMagnification��
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT	LuaCharacterBufferEffect::LuaAddTreatLifeP(QLuaScript& sc)
{
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: LuaCharacterBufferEffect
// @LuaApiName		: AddTreatManaV
// @Description		: ������������ֵ
// @ReturnCode		: 
// @ArgumentFlag	: d
// @ArgumentComment	: ���ӵ���ֵ
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT	LuaCharacterBufferEffect::LuaAddTreatManaV(QLuaScript& sc)
{
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: LuaCharacterBufferEffect
// @LuaApiName		: AddTreatManaP
// @Description		: �������������ٷֱ�
// @ReturnCode		: 
// @ArgumentFlag	: d
// @ArgumentComment	: �������������İٷֱ���ֵ����Ӧ��Skill���SkillMagnification��
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT	LuaCharacterBufferEffect::LuaAddTreatManaP(QLuaScript& sc)
{
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: LuaCharacterBufferEffect
// @LuaApiName		: ReduceCostV
// @Description		: ��ֵ�����ͷż��ܵ�����
// @ReturnCode		: 
// @ArgumentFlag	: ddd
// @ArgumentComment	: ���ٵ���ֵ
// @ArgumentComment	: ���ܵ�Category���ͣ���Ӧ��Skill������-1
// @ArgumentComment	: ���ܵ�Categoryֵ����Ӧ��Buff��Ķ�ӦCategory�У�ǰһ��������-1ʱ����ֵ�����壬ǰһ��������Ϊ-1ʱ����ֵ����-1 
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT	LuaCharacterBufferEffect::LuaReduceCostV(QLuaScript& sc)
{
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: LuaCharacterBufferEffect
// @LuaApiName		: ReduceCostP
// @Description		: ���ٷֱȼ����ͷż��ܵ�����
// @ReturnCode		: 
// @ArgumentFlag	: ddd
// @ArgumentComment	: ���ٵİٷֱ�
// @ArgumentComment	: ���ܵ�Category���ͣ���Ӧ��Skill������-1
// @ArgumentComment	: ���ܵ�Categoryֵ����Ӧ��Buff��Ķ�ӦCategory�У�ǰһ��������-1ʱ����ֵ�����壬ǰһ��������Ϊ-1ʱ����ֵ����-1 
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT	LuaCharacterBufferEffect::LuaReduceCostP(QLuaScript& sc)
{
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: LuaCharacterBufferEffect
// @LuaApiName		: IgnorDmg
// @Description		: �����˺������п�����Buffӵ�����������ֵ���ٵ�Ч��������Ч
// @ReturnCode		: 
// @ArgumentFlag	: 
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT	LuaCharacterBufferEffect::LuaIgnorDmg(QLuaScript& sc)
{
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: LuaCharacterBufferEffect
// @LuaApiName		: AddExtSkillBuff
// @Description		: ��ĳһ�༼�����һ��Buff
// @ReturnCode		: 
// @ArgumentFlag	: ddd
// @ArgumentComment	: ���ܵ�Category���ͣ���Ӧ��Skill������-1
// @ArgumentComment	: ���ܵ�Categoryֵ����Ӧ��Buff��Ķ�ӦCategory�У�ǰһ��������-1ʱ����ֵ�����壬ǰһ��������Ϊ-1ʱ����ֵ����-1 
// @ArgumentComment	: ���ӵ�Buff��ID
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT	LuaCharacterBufferEffect::LuaAddExtSkillBuff(QLuaScript& sc)
{
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: LuaCharacterBufferEffect
// @LuaApiName		: DelExtSkillBuff
// @Description		: ɾ��ĳһ�༼�ܵ�һ��Buff
// @ReturnCode		: 
// @ArgumentFlag	: ddd
// @ArgumentComment	: ���ܵ�Category���ͣ���Ӧ��Skill������-1
// @ArgumentComment	: ���ܵ�Categoryֵ����Ӧ��Buff��Ķ�ӦCategory�У�ǰһ��������-1ʱ����ֵ�����壬ǰһ��������Ϊ-1ʱ����ֵ����-1 
// @ArgumentComment	: ɾ����Buff��ID 
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT	LuaCharacterBufferEffect::LuaDelExtSkillBuff(QLuaScript& sc)
{
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: LuaCharacterBufferEffect
// @LuaApiName		: AddMagnification
// @Description		: ����ĳһ�༼�ܵĹ������ٷֱ�
// @ReturnCode		: 
// @ArgumentFlag	: ddd
// @ArgumentComment	: ���ܵ�Category���ͣ���Ӧ��Skill������-1
// @ArgumentComment	: ���ܵ�Categoryֵ����Ӧ��Buff��Ķ�ӦCategory�У�ǰһ��������-1ʱ����ֵ�����壬ǰһ��������Ϊ-1ʱ����ֵ����-1 
// @ArgumentComment	: ���ӵİٷֱ���ֵ������Ϊ���ӣ�����Ϊ����
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT	LuaCharacterBufferEffect::LuaAddMagnification(QLuaScript& sc)
{
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: LuaCharacterBufferEffect
// @LuaApiName		: AddWeaponDmgP
// @Description		: ���ٷֱ���������������
// @ReturnCode		: 
// @ArgumentFlag	: d
// @ArgumentComment	: ���ӵİٷֱ���ֵ
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT	LuaCharacterBufferEffect::LuaAddWeaponDmgP(QLuaScript& sc)
{
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: LuaCharacterBufferEffect
// @LuaApiName		: GetCurrProcBuffFightInfo
// @Description		: �@��Ŀǰbuff��nSkillId,nMagnification,nGrow,nIfUseSkillLv, nK
// @ReturnCode		: 
// @ArgumentFlag	: [d]
// @ArgumentComment	: nBufferTemplateId
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT LuaCharacterBufferEffect::LuaGetCurrProcBuffFightInfo(QLuaScript& sc)
{
	INT nBuffTemplateId = sc.GetInt(1);
	const Buffer*		pCharacterProcBuff = NULL;
	const GroundBuffer*	pGroundProcBuff = NULL;
	CharacterBuffer* pCharacterBuffer = NULL;
	BOOL bC = FALSE;
	BOOL bG = FALSE;
	INT nSkillId		= 0;
	INT nMagnification	= 0;
	INT nGrow			= 0;
	INT nK				= 0;
	INT nIfUseSkillLv	= 0;

	pCharacterBuffer = m_rcCharacter.GetCtrl<CharacterBuffer>();
	LOG_PROCESS_ERROR(pCharacterBuffer);

	pGroundProcBuff	= g_cBufferMgr.GetCurrentProcessingBuff();
	if(pGroundProcBuff)
	{
		nSkillId		= pGroundProcBuff->GetCastSkill();
		nMagnification	= pGroundProcBuff->GetMagnification();
		nGrow			= pGroundProcBuff->GetGrow();
		nIfUseSkillLv = pGroundProcBuff->GetIfUseSkillLv();
		nK = pGroundProcBuff->GetK();
	}
	else
	{
		pCharacterProcBuff = pCharacterBuffer->GetBufferByTemplateId(nBuffTemplateId);
		if(!pCharacterProcBuff)
		{
			pCharacterProcBuff = pCharacterBuffer->GetCurrentProcessingBuffer();
		}
		PROCESS_ERROR(pCharacterProcBuff);
		nSkillId		= pCharacterProcBuff->GetCastSkill();
		nMagnification	= pCharacterProcBuff->GetMagnification();
		nGrow			= pCharacterProcBuff->GetGrow();
		nIfUseSkillLv	= pCharacterProcBuff->GetIfUseSkillLv();
		nK				= pCharacterProcBuff->GetK();
	}

	sc.PushNumber(nSkillId);
	sc.PushNumber(nMagnification);
	sc.PushNumber(nGrow);
	sc.PushNumber(nIfUseSkillLv);
	sc.PushNumber(nK);

	return 5;
EXIT0:
	sc.PushNumber(0);
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: S
// @ClassName		: LuaCharacterBufferEffect
// @LuaApiName		: GetGroundBuffPosition
// @Description		: �õ�����bufferλ��
// @ReturnCode		: 
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT LuaCharacterBufferEffect::LuaGetGroundBuffPosition(QLuaScript& sc)
{
	INT nX = 0, nY = 0, nZ = 0;
	GroundBuffer* pGroundProcBuff = NULL;
	CharacterBuffer* pCharacterBuffer = m_rcCharacter.GetCtrl<CharacterBuffer>();
	LOG_PROCESS_ERROR(pCharacterBuffer);

	pGroundProcBuff = g_cBufferMgr.GetCurrentProcessingBuff();
	m_rcCharacter.GetPosition(nX, nY, nZ);
	if(pGroundProcBuff)
	{
		pGroundProcBuff->GetPosition(nX, nY, nZ);
	}
	else
	{
		//ASSERT(FALSE && "����ħ������ʱ��ǰbufferΪ�գ�");
	}
  
	sc.PushNumber(nX);
	sc.PushNumber(nY);
	sc.PushNumber(nZ);

EXIT0:
	return 3;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: LuaCharacterBufferEffect
// @LuaApiName		: ResetBufferTime
// @Description		: ����Bufferʱ��
// @ReturnCode		: 
// @ArgumentFlag	: ddd
// @ArgumentComment	: ����nCateType
// @ArgumentComment	: ����nCateId
// @ArgumentComment	: �޸�ֵ
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT LuaCharacterBufferEffect::LuaResetBufferTime(QLuaScript& sc)
{
	INT		nCateType		= sc.GetInt(1);
	INT		nCateId			= sc.GetInt(2);
	INT		nValue			= sc.GetInt(3);

	ObjectBuffer::BUFFER_ARRAY::const_iterator iter;
	CharacterBuffer* pCharacterBuffer = m_rcCharacter.GetCtrl<CharacterBuffer>();
	LOG_PROCESS_ERROR(pCharacterBuffer);

	{
		const ObjectBuffer::BUFFER_ARRAY& buffers = pCharacterBuffer->GetBuffers();

		for( iter = buffers.begin(); iter != buffers.end(); ++iter)
		{
			if( (*iter)->GetBuffCategory(nCateType) == nCateId )
			{
				(*iter)->AddBuffPersist(nValue);
			}
		}
	}

	return 0;
EXIT0:
	sc.PushNumber(0);
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: LuaCharacterBufferEffect
// @LuaApiName		: RefreshBufferTime
// @Description		: ����Bufferʱ��Ϊԭʱ��
// @ReturnCode		: 
// @ArgumentFlag	: dd
// @ArgumentComment	: ����nCateType
// @ArgumentComment	: ����nCateId
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT LuaCharacterBufferEffect::LuaRefreshBufferTime(QLuaScript& sc)
{
	INT		nCateType		= sc.GetInt(1);
	INT		nCateId			= sc.GetInt(2);

	ObjectBuffer::BUFFER_ARRAY::const_iterator iter;
	CharacterBuffer* pCharacterBuffer = m_rcCharacter.GetCtrl<CharacterBuffer>();
	LOG_PROCESS_ERROR(pCharacterBuffer);

	{
		const ObjectBuffer::BUFFER_ARRAY& buffers = pCharacterBuffer->GetBuffers();

		for( iter = buffers.begin(); iter != buffers.end(); ++iter)
		{
			switch(nCateType)
			{
			case 1:
				{
					if( (*iter)->GetBuffCategory(nCateType) == nCateId )
					{
						(*iter)->RefreshBuffPersist();
					}
				}
				break;
			case 2:
				break;
			case 3:
				break;
			}
		}
	}

	return 0;
EXIT0:
	sc.PushNumber(0);
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: LuaCharacterBufferEffect
// @LuaApiName		: AppendData
// @Description		: ���������Buff��Ӹ�������
// @ReturnCode		: 
// @ArgumentFlag	: ddd
// @ArgumentComment	: buffģ��id
// @ArgumentComment	: ������������
// @ArgumentComment	: ��������ֵ
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT LuaCharacterBufferEffect::LuaAppendData(QLuaScript& sc)
{
	BOOL	bRet								= FALSE;
	INT		nBuffTemplateId						= sc.GetInt(1);
	INT		nType								= sc.GetInt(2);
	INT		nValue								= sc.GetInt(3);
	CONST BufferTemplate* pTemplate				= NULL;
	CharacterBuffer*	pCharacterBuffer		= NULL;
	GroundBuffer*	pGroundProcBuff				= NULL;
	Buffer*			pCharacterProcBuff			= NULL;

	pTemplate = g_cBufferSetting.GetBufferTemplate(nBuffTemplateId);
	LOG_PROCESS_ERROR(pTemplate);

	pCharacterBuffer = m_rcCharacter.GetCtrl<CharacterBuffer>();
	LOG_PROCESS_ERROR(pCharacterBuffer);

	if(!pTemplate->m_bIsGroundBuffer && pTemplate->m_fBuffRadius == 0.0f)
	{
		Buffer* pCharacterProcBuff = pCharacterBuffer->GetBufferByTemplateId(nBuffTemplateId);
		if(!pCharacterProcBuff)
		{
			pCharacterProcBuff = pCharacterBuffer->GetCurrentProcessingBuffer();
		}
		LOG_PROCESS_ERROR(pCharacterProcBuff);
		pCharacterProcBuff->AppendData(nType, nValue);
	}
	else
	{
		pGroundProcBuff	= g_cBufferMgr.GetCurrentProcessingBuff();
		LOG_PROCESS_ERROR(pGroundProcBuff);
		pGroundProcBuff->AppendData(nType, nValue);
	}

	bRet = TRUE;
EXIT0:
	sc.PushNumber(bRet);
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: LuaCharacterBufferEffect
// @LuaApiName		: GetAppendData
// @Description		: ���������Buff��Ӹ�������
// @ReturnCode		: 
// @ArgumentFlag	: d
// @ArgumentComment	: ������������
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT LuaCharacterBufferEffect::LuaGetAppendData(QLuaScript& sc)
{
	INT nBuffTemplateId						= sc.GetInt(1);
	INT	nType								= sc.GetInt(2);
	INT	nValue								= 0;

	CONST BufferTemplate* pTemplate			= NULL;
	CharacterBuffer*	pCharacterBuffer	= NULL;
	GroundBuffer*	pGroundProcBuff			= NULL;
	Buffer*			pCharacterProcBuff		= NULL;

	pTemplate = g_cBufferSetting.GetBufferTemplate(nBuffTemplateId);
	LOG_PROCESS_ERROR(pTemplate);

	pCharacterBuffer = m_rcCharacter.GetCtrl<CharacterBuffer>();
	LOG_PROCESS_ERROR(pCharacterBuffer);

	if(!pTemplate->m_bIsGroundBuffer && pTemplate->m_fBuffRadius == 0.0f)
	{
		pCharacterProcBuff = pCharacterBuffer->GetBufferByTemplateId(nBuffTemplateId);
		if(!pCharacterProcBuff)
		{
			pCharacterProcBuff = pCharacterBuffer->GetCurrentProcessingBuffer();
		}
		LOG_PROCESS_ERROR(pCharacterProcBuff);
		nValue = pCharacterProcBuff->GetAppendData(nType);
	}
	else
	{
		pGroundProcBuff	= g_cBufferMgr.GetCurrentProcessingBuff();
		LOG_PROCESS_ERROR(pGroundProcBuff);
		nValue = pGroundProcBuff->GetAppendData(nType);
	}
	
	sc.PushNumber(nValue);

	return 1;
EXIT0:
	sc.PushNumber(0);
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: LuaCharacterBufferEffect
// @LuaApiName		: GetDestPosition
// @Description		: �õ��������buff���õ�Ŀ���
// @ReturnCode		: 
// @ArgumentFlag	: d
// @ArgumentComment	: buffģ��id
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT LuaCharacterBufferEffect::LuaGetDestPosition(QLuaScript& sc)
{
	INT nDestX = 0;
	INT nDestY = 0;
	INT nDestZ = 0;

	INT nBuffTemplateId						= sc.GetInt(1);
	INT	nValue								= 0;

	CONST BufferTemplate* pTemplate			= NULL;
	CharacterBuffer*	pCharacterBuffer	= NULL;
	GroundBuffer*	pGroundProcBuff			= NULL;
	Buffer*			pCharacterProcBuff		= NULL;

	pTemplate = g_cBufferSetting.GetBufferTemplate(nBuffTemplateId);
	LOG_PROCESS_ERROR(pTemplate);

	pCharacterBuffer = m_rcCharacter.GetCtrl<CharacterBuffer>();
	LOG_PROCESS_ERROR(pCharacterBuffer);

	if(!pTemplate->m_bIsGroundBuffer)
	{
		pCharacterProcBuff = pCharacterBuffer->GetBufferByTemplateId(nBuffTemplateId);
		if(!pCharacterProcBuff)
		{
			pCharacterProcBuff = pCharacterBuffer->GetCurrentProcessingBuffer();
		}
		LOG_PROCESS_ERROR(pCharacterProcBuff);
		pCharacterProcBuff->GetDestPosition(nDestX, nDestY, nDestZ);
	}
	else
	{
		pGroundProcBuff	= g_cBufferMgr.GetCurrentProcessingBuff();
		LOG_PROCESS_ERROR(pGroundProcBuff);
		pGroundProcBuff->GetPosition(nDestX, nDestY, nDestZ);
	}

EXIT0:
	sc.PushNumber(nDestX);
	sc.PushNumber(nDestY);
	sc.PushNumber(nDestZ);
	return 3;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: LuaCharacterBufferEffect
// @LuaApiName		: SetTransParam
// @Description		: ����ת����������
// @ReturnCode		: 
// @ArgumentFlag	: ddd
// @ArgumentComment	: ת����ԭ����
// @ArgumentComment	: Ҫת��������
// @ArgumentComment	: ת���ٷֱ�
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT LuaCharacterBufferEffect::LuaSetTransParam(QLuaScript& sc)
{
	BOOL	bRet								= FALSE;
	INT		nSrcParam							= sc.GetInt(1);
	INT		nDstParam							= sc.GetInt(2);
	DOUBLE	dPercent							= sc.GetNum(3);
	CharacterBuffer*	pCharacterBuffer		= NULL;

	pCharacterBuffer = m_rcCharacter.GetCtrl<CharacterBuffer>();
	LOG_PROCESS_ERROR(pCharacterBuffer);

	bRet = pCharacterBuffer->SetTransParam(nSrcParam, nDstParam, dPercent);

EXIT0:
	sc.PushNumber(bRet);
	return 1;
}

// -------------------------------------------------------------------------
// @ClientSvr(C/S)	: 
// @ClassName		: LuaCharacterBufferEffect
// @LuaApiName		: GetTransParam
// @Description		: �õ�һ�����ԵĹ�������
// @ReturnCode		: 
// @ArgumentFlag	: d
// @ArgumentComment	: ԭ����
// @LuaMarkEnd
// -------------------------------------------------------------------------
INT LuaCharacterBufferEffect::LuaGetTransParam(QLuaScript& sc)
{
	BOOL bRet = FALSE;
	INT		nDstParam							= 0;
	INT		nPercent							= 0;
	INT		nSrcParam							= sc.GetInt(1);
	CharacterBuffer*	pCharacterBuffer		= NULL;
	MAP_TRANSPARAM_DATA mapParam;

	pCharacterBuffer = m_rcCharacter.GetCtrl<CharacterBuffer>();
	LOG_PROCESS_ERROR(pCharacterBuffer);

	pCharacterBuffer->GetTransParam(nSrcParam, mapParam);

	sc.PushTable();

	for(MAP_TRANSPARAM_DATA::iterator it = mapParam.begin(); it != mapParam.end(); ++it)
	{
		sc.PushNumber(it->second);
		sc.SetTableIndex(it->first);
	}

EXIT0:
	return 1;
}

#include "luabuffereffect_table.hpp"