#include "stdafx.h"
#include "onlinegamebase/kscriptmanager.h"
#include "onlinegameworld/kplayer.h"
#include "onlinegameworld/kluaplayer.h"
#include "onlinegameworld/kcharactermgr.h"
#include "kstagectrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static CHAR THIS_FILE[] = __FILE__;
#endif

namespace KStageScript
{

	// -------------------------------------------------------------------------
	// @ClientSvr(C/S)	: S
	// @ClassName		: --
	// @LuaApiName		: StartMopStage
	// @Description		: ��ʼɨ���ؿ�
	// @ReturnCode		: 
	// @ArgumentFlag	: od
	// @ArgumentComment	: pPlayer
	// @ArgumentComment	: nTotalTime
	// @LuaMarkEnd
	// -------------------------------------------------------------------------
	INT LuaStartMopStage(QLuaScript &sc)
	{
		KPlayer* pPlayer = NULL;

		KLuaPlayer *pLuaPlayer = dynamic_cast<KLuaPlayer *>(sc.GetObj(1));
		if (pLuaPlayer)
			pPlayer = pLuaPlayer->GetHim();

		QCONFIRM_RET_FALSE(pPlayer);

		INT nTotalTime = sc.GetInt(2);

		KStageCtrl* pStageCtrl = pPlayer->GetCtrl<KStageCtrl>();
		QCONFIRM_RET_FALSE(pStageCtrl);

		pStageCtrl->StartMopStage(nTotalTime);

		return 0;
	}

	// -------------------------------------------------------------------------
	// @ClientSvr(C/S)	: S
	// @ClassName		: --
	// @LuaApiName		: GetRushStartTime
	// @Description		: �õ���ʼ��ս�ؿ�ʱ��
	// @ReturnCode		: 
	// @ArgumentFlag	: o
	// @ArgumentComment	: pPlayer
	// @LuaMarkEnd
	// -------------------------------------------------------------------------
	INT LuaGetRushStartTime(QLuaScript &sc)
	{
		KPlayer* pPlayer = NULL;

		KLuaPlayer *pLuaPlayer = dynamic_cast<KLuaPlayer *>(sc.GetObj(1));
		if (pLuaPlayer)
			pPlayer = pLuaPlayer->GetHim();

		QCONFIRM_RET_FALSE(pPlayer);

		KStageCtrl* pStageCtrl = pPlayer->GetCtrl<KStageCtrl>();
		QCONFIRM_RET_FALSE(pStageCtrl);

		sc.PushNumber(pStageCtrl->GetRushStartTime());

		return 1;
	}

	// -------------------------------------------------------------------------
	// @ClientSvr(C/S)	: S
	// @ClassName		: --
	// @LuaApiName		: SetRushStartTime
	// @Description		: ���ÿ�ʼ��ս�ؿ�ʱ��
	// @ReturnCode		: 
	// @ArgumentFlag	: od
	// @ArgumentComment	: pPlayer
	// @ArgumentComment	: ��ʼ��սʱ��
	// @LuaMarkEnd
	// -------------------------------------------------------------------------
	INT LuaSetRushStartTime(QLuaScript &sc)
	{
		KPlayer* pPlayer = NULL;

		KLuaPlayer *pLuaPlayer = dynamic_cast<KLuaPlayer *>(sc.GetObj(1));
		if (pLuaPlayer)
			pPlayer = pLuaPlayer->GetHim();

		QCONFIRM_RET_FALSE(pPlayer);

		KStageCtrl* pStageCtrl = pPlayer->GetCtrl<KStageCtrl>();
		QCONFIRM_RET_FALSE(pStageCtrl);


		DWORD dwTime = sc.GetInt(2);

		pStageCtrl->SetRushStartTime(dwTime);

		return 0;
	}

	// -------------------------------------------------------------------------
	// @ClientSvr(C/S)	: S
	// @ClassName		: --
	// @LuaApiName		: GetRushLayer
	// @Description		: �õ���ǰ��ս��Ĺؿ���
	// @ReturnCode		: 
	// @ArgumentFlag	: o
	// @ArgumentComment	: pPlayer
	// @LuaMarkEnd
	// -------------------------------------------------------------------------
	INT LuaGetRushLayer(QLuaScript &sc)
	{
		KPlayer* pPlayer = NULL;

		KLuaPlayer *pLuaPlayer = dynamic_cast<KLuaPlayer *>(sc.GetObj(1));
		if (pLuaPlayer)
			pPlayer = pLuaPlayer->GetHim();

		QCONFIRM_RET_FALSE(pPlayer);

		KStageCtrl* pStageCtrl = pPlayer->GetCtrl<KStageCtrl>();
		QCONFIRM_RET_FALSE(pStageCtrl);

		sc.PushNumber(pStageCtrl->GetRushLayer());

		return 1;
	}

	// -------------------------------------------------------------------------
	// @ClientSvr(C/S)	: S
	// @ClassName		: --
	// @LuaApiName		: SetRushLayer
	// @Description		: ���õ�ǰ��ս��Ĺؿ���
	// @ReturnCode		: 
	// @ArgumentFlag	: od
	// @ArgumentComment	: pPlayer
	// @ArgumentComment	: �ؿ���
	// @LuaMarkEnd
	// -------------------------------------------------------------------------
	INT LuaSetRushLayer(QLuaScript &sc)
	{
		KPlayer* pPlayer = NULL;

		KLuaPlayer *pLuaPlayer = dynamic_cast<KLuaPlayer *>(sc.GetObj(1));
		if (pLuaPlayer)
			pPlayer = pLuaPlayer->GetHim();

		QCONFIRM_RET_FALSE(pPlayer);

		KStageCtrl* pStageCtrl = pPlayer->GetCtrl<KStageCtrl>();
		QCONFIRM_RET_FALSE(pStageCtrl);


		INT nLayer = sc.GetInt(2);

		pStageCtrl->SetRushLayer(nLayer);

		return 0;
	}

	// -------------------------------------------------------------------------
	// @ClientSvr(C/S)	: S
	// @ClassName		: --
	// @LuaApiName		: GetRushDifficulty
	// @Description		: �õ���ǰ��ս�Ĺؿ��Ѷ�
	// @ReturnCode		: 
	// @ArgumentFlag	: o
	// @ArgumentComment	: pPlayer
	// @LuaMarkEnd
	// -------------------------------------------------------------------------
	INT LuaGetRushDifficulty(QLuaScript &sc)
	{
		KPlayer* pPlayer = NULL;

		KLuaPlayer *pLuaPlayer = dynamic_cast<KLuaPlayer *>(sc.GetObj(1));
		if (pLuaPlayer)
			pPlayer = pLuaPlayer->GetHim();

		QCONFIRM_RET_FALSE(pPlayer);

		KStageCtrl* pStageCtrl = pPlayer->GetCtrl<KStageCtrl>();
		QCONFIRM_RET_FALSE(pStageCtrl);

		sc.PushNumber(pStageCtrl->GetRushDifficulty());

		return 1;
	}

	// -------------------------------------------------------------------------
	// @ClientSvr(C/S)	: S
	// @ClassName		: --
	// @LuaApiName		: SetRushDifficulty
	// @Description		: ���õ�ǰ��ս�ؿ��Ѷ�
	// @ReturnCode		: 
	// @ArgumentFlag	: od
	// @ArgumentComment	: pPlayer
	// @ArgumentComment	: �ؿ��Ѷ�
	// @LuaMarkEnd
	// -------------------------------------------------------------------------
	INT LuaSetRushDifficulty(QLuaScript &sc)
	{
		KPlayer* pPlayer = NULL;

		KLuaPlayer *pLuaPlayer = dynamic_cast<KLuaPlayer *>(sc.GetObj(1));
		if (pLuaPlayer)
			pPlayer = pLuaPlayer->GetHim();

		QCONFIRM_RET_FALSE(pPlayer);

		KStageCtrl* pStageCtrl = pPlayer->GetCtrl<KStageCtrl>();
		QCONFIRM_RET_FALSE(pStageCtrl);

		INT nDifficulty = sc.GetInt(2);

		pStageCtrl->SetRushDifficulty(nDifficulty);

		return 0;
	}

	// -------------------------------------------------------------------------
	// @ClientSvr(C/S)	: S
	// @ClassName		: --
	// @LuaApiName		: SetStageStar
	// @Description		: ������ս�Ǽ�
	// @ReturnCode		: 
	// @ArgumentFlag	: odd
	// @ArgumentComment	: pPlayer
	// @ArgumentComment	: �Ѷ�
	// @ArgumentComment	: �Ǽ�
	// @LuaMarkEnd
	// -------------------------------------------------------------------------
	INT LuaSetStageStar(QLuaScript &sc)
	{
		KPlayer* pPlayer = NULL;

		KLuaPlayer *pLuaPlayer = dynamic_cast<KLuaPlayer *>(sc.GetObj(1));
		if (pLuaPlayer)
			pPlayer = pLuaPlayer->GetHim();

		QCONFIRM_RET_FALSE(pPlayer);

		KStageCtrl* pStageCtrl = pPlayer->GetCtrl<KStageCtrl>();
		QCONFIRM_RET_FALSE(pStageCtrl);

		INT nDifficulty = sc.GetInt(2); 
		INT nStar = sc.GetInt(3);

		pStageCtrl->SetStageStar(nDifficulty, nStar);

		return 0;
	}

	// -------------------------------------------------------------------------
	// @ClientSvr(C/S)	: S
	// @ClassName		: --
	// @LuaApiName		: GetStageStar
	// @Description		: �õ���ս�Ǽ�
	// @ReturnCode		: 
	// @ArgumentFlag	: od
	// @ArgumentComment	: pPlayer
	// @ArgumentComment	: �Ѷ�
	// @LuaMarkEnd
	// -------------------------------------------------------------------------
	INT LuaGetStageStar(QLuaScript &sc)
	{
		KPlayer* pPlayer = NULL;

		KLuaPlayer *pLuaPlayer = dynamic_cast<KLuaPlayer *>(sc.GetObj(1));
		if (pLuaPlayer)
			pPlayer = pLuaPlayer->GetHim();

		QCONFIRM_RET_FALSE(pPlayer);

		KStageCtrl* pStageCtrl = pPlayer->GetCtrl<KStageCtrl>();
		QCONFIRM_RET_FALSE(pStageCtrl);

		INT nDifficulty = sc.GetInt(2); 

		sc.PushNumber(pStageCtrl->GetStageStar(nDifficulty));

		return 1;
	}

	// -------------------------------------------------------------------------
	// @ClientSvr(C/S)	: S
	// @ClassName		: --
	// @LuaApiName		: GetLeftMopTime
	// @Description		: �õ�ʣ��ɨ��ʱ��
	// @ReturnCode		: 
	// @ArgumentFlag	: o
	// @ArgumentComment	: pPlayer
	// @LuaMarkEnd
	// -------------------------------------------------------------------------
	INT LuaGetLeftMopTime(QLuaScript &sc)
	{
		KPlayer* pPlayer = NULL;

		KLuaPlayer *pLuaPlayer = dynamic_cast<KLuaPlayer *>(sc.GetObj(1));
		if (pLuaPlayer)
			pPlayer = pLuaPlayer->GetHim();

		QCONFIRM_RET_FALSE(pPlayer);

		KStageCtrl* pStageCtrl = pPlayer->GetCtrl<KStageCtrl>();
		QCONFIRM_RET_FALSE(pStageCtrl);

		sc.PushNumber(pStageCtrl->GetMopLeftTime());

		return 1;
	}

	// -------------------------------------------------------------------------
	// @ClientSvr(C/S)	: S
	// @ClassName		: --
	// @LuaApiName		: StopMopStage
	// @Description		: ���ֹͣɨ���ؿ�
	// @ReturnCode		: 
	// @ArgumentFlag	: ?d
	// @ArgumentComment	: nPlayerId/pPlayer:��ɫId���߶���
	// @ArgumentComment	: �Ƿ���ɨ��һ��
	// @LuaMarkEnd
	// -------------------------------------------------------------------------
	INT LuaStopMopStage(QLuaScript &sc)
	{
		KPlayer* pPlayer = NULL;
		KStageCtrl* pStageCtrl = NULL;

		if (sc.IsNumber(1))
		{
			INT nPlayerId = sc.GetInt(1);
			QCONFIRM_RET_FALSE(IS_PLAYER(nPlayerId));
			pPlayer = (KPlayer*)g_cCharacterMgr.GetById(nPlayerId);
		}
		else
		{
			KLuaPlayer *pLuaPlayer = dynamic_cast<KLuaPlayer *>(sc.GetObj(1));
			if (pLuaPlayer)
				pPlayer = pLuaPlayer->GetHim();
		}
		QCONFIRM_RET_FALSE(pPlayer);

		INT bFinish = sc.GetInt(2);

		pStageCtrl = pPlayer->GetCtrl<KStageCtrl>();
		QCONFIRM_RET_FALSE(pStageCtrl);

		pStageCtrl->StopMopStage(bFinish);

		return 0;
	}

	// -------------------------------------------------------------------------
	// @ClientSvr(C/S)	: S
	// @ClassName		: --
	// @LuaApiName		: FinishMop
	// @Description		: ֱ�����ɨ��
	// @ReturnCode		: 
	// @ArgumentFlag	: ?
	// @ArgumentComment	: nPlayerId/pPlayer:��ɫId���߶���
	// @LuaMarkEnd
	// -------------------------------------------------------------------------
	INT LuaFinishMop(QLuaScript &sc)
	{
		KPlayer* pPlayer = NULL;
		KStageCtrl* pStageCtrl = NULL;

		if (sc.IsNumber(1))
		{
			INT nPlayerId = sc.GetInt(1);
			QCONFIRM_RET_FALSE(IS_PLAYER(nPlayerId));
			pPlayer = (KPlayer*)g_cCharacterMgr.GetById(nPlayerId);
		}
		else
		{
			KLuaPlayer *pLuaPlayer = dynamic_cast<KLuaPlayer *>(sc.GetObj(1));
			if (pLuaPlayer)
				pPlayer = pLuaPlayer->GetHim();
		}
		QCONFIRM_RET_FALSE(pPlayer);

		pStageCtrl = pPlayer->GetCtrl<KStageCtrl>();
		QCONFIRM_RET_FALSE(pStageCtrl);

		pStageCtrl->OnFinishMop();

		return 0;
	}

	// -------------------------------------------------------------------------
	// @ClientSvr(C/S)	: S
	// @ClassName		: --
	// @LuaApiName		: GetMopStage
	// @Description		: �õ���ǰ����ɨ���Ĺؿ��Ѷ�
	// @ReturnCode		: 
	// @ArgumentFlag	: o
	// @ArgumentComment	: pPlayer
	// @LuaMarkEnd
	// -------------------------------------------------------------------------
	INT LuaGetMopStage(QLuaScript &sc)
	{
		KPlayer* pPlayer = NULL;

		KLuaPlayer *pLuaPlayer = dynamic_cast<KLuaPlayer *>(sc.GetObj(1));
		if (pLuaPlayer)
			pPlayer = pLuaPlayer->GetHim();

		QCONFIRM_RET_FALSE(pPlayer);

		KStageCtrl* pStageCtrl = pPlayer->GetCtrl<KStageCtrl>();
		QCONFIRM_RET_FALSE(pStageCtrl);

		sc.PushNumber(pStageCtrl->GetMopStage());

		return 1;
	}

	// -------------------------------------------------------------------------
	// @ClientSvr(C/S)	: S
	// @ClassName		: --
	// @LuaApiName		: GetMopState
	// @Description		: �õ���ǰɨ��״̬
	// @ReturnCode		: 
	// @ArgumentFlag	: o
	// @ArgumentComment	: pPlayer
	// @LuaMarkEnd
	// -------------------------------------------------------------------------
	INT LuaGetMopState(QLuaScript &sc)
	{
		KPlayer* pPlayer = NULL;

		KLuaPlayer *pLuaPlayer = dynamic_cast<KLuaPlayer *>(sc.GetObj(1));
		if (pLuaPlayer)
			pPlayer = pLuaPlayer->GetHim();

		QCONFIRM_RET_FALSE(pPlayer);

		KStageCtrl* pStageCtrl = pPlayer->GetCtrl<KStageCtrl>();
		QCONFIRM_RET_FALSE(pStageCtrl);

		sc.PushNumber(pStageCtrl->GetMopState());

		return 1;
	}

	// -------------------------------------------------------------------------
	// @ClientSvr(C/S)	: S
	// @ClassName		: --
	// @LuaApiName		: SetMopStage
	// @Description		: ���õ�ǰ����ɨ���Ĺؿ��Ѷ�
	// @ReturnCode		: 
	// @ArgumentFlag	: od
	// @ArgumentComment	: pPlayer
	// @ArgumentComment	: �ؿ��Ѷ�
	// @LuaMarkEnd
	// -------------------------------------------------------------------------
	INT LuaSetMopStage(QLuaScript &sc)
	{
		KPlayer* pPlayer = NULL;

		KLuaPlayer *pLuaPlayer = dynamic_cast<KLuaPlayer *>(sc.GetObj(1));
		if (pLuaPlayer)
			pPlayer = pLuaPlayer->GetHim();

		QCONFIRM_RET_FALSE(pPlayer);

		KStageCtrl* pStageCtrl = pPlayer->GetCtrl<KStageCtrl>();
		QCONFIRM_RET_FALSE(pStageCtrl);


		INT nStage = sc.GetInt(2);

		pStageCtrl->SetMopStage(nStage);

		return 0;
	}

	// -------------------------------------------------------------------------
	// @ClientSvr(C/S)	: S
	// @ClassName		: --
	// @LuaApiName		: GetRushState
	// @Description		: �õ���ǰ����״̬
	// @ReturnCode		: 
	// @ArgumentFlag	: o
	// @ArgumentComment	: pPlayer
	// @LuaMarkEnd
	// -------------------------------------------------------------------------
	INT LuaGetRushState(QLuaScript &sc)
	{
		KPlayer* pPlayer = NULL;

		KLuaPlayer *pLuaPlayer = dynamic_cast<KLuaPlayer *>(sc.GetObj(1));
		if (pLuaPlayer)
			pPlayer = pLuaPlayer->GetHim();

		QCONFIRM_RET_FALSE(pPlayer);

		KStageCtrl* pStageCtrl = pPlayer->GetCtrl<KStageCtrl>();
		QCONFIRM_RET_FALSE(pStageCtrl);

		sc.PushNumber(pStageCtrl->GetRushState());

		return 1;
	}

	// -------------------------------------------------------------------------
	// @ClientSvr(C/S)	: S
	// @ClassName		: --
	// @LuaApiName		: SetRushState
	// @Description		: 
	// @ReturnCode		: 
	// @ArgumentFlag	: od
	// @ArgumentComment	: pPlayer
	// @ArgumentComment	: ����
	// @LuaMarkEnd
	// -------------------------------------------------------------------------
	INT LuaSetRushState(QLuaScript &sc)
	{
		KPlayer* pPlayer = NULL;

		KLuaPlayer *pLuaPlayer = dynamic_cast<KLuaPlayer *>(sc.GetObj(1));
		if (pLuaPlayer)
			pPlayer = pLuaPlayer->GetHim();

		QCONFIRM_RET_FALSE(pPlayer);

		KStageCtrl* pStageCtrl = pPlayer->GetCtrl<KStageCtrl>();
		QCONFIRM_RET_FALSE(pStageCtrl);

		INT nState = sc.GetInt(2);

		pStageCtrl->SetRushState(nState);

		return 0;
	}

	// -------------------------------------------------------------------------
	// @ClientSvr(C/S)	: S
	// @ClassName		: --
	// @LuaApiName		: SpeedUpMop
	// @Description		: ����ɨ��
	// @ReturnCode		: 
	// @ArgumentFlag	: ?
	// @ArgumentComment	: nPlayerId/pPlayer:��ɫId���߶���
	// @LuaMarkEnd
	// -------------------------------------------------------------------------
	INT LuaSpeedUpMop(QLuaScript &sc)
	{
		KPlayer* pPlayer = NULL;
		KStageCtrl* pStageCtrl = NULL;

		if (sc.IsNumber(1))
		{
			INT nPlayerId = sc.GetInt(1);
			QCONFIRM_RET_FALSE(IS_PLAYER(nPlayerId));
			pPlayer = (KPlayer*)g_cCharacterMgr.GetById(nPlayerId);
		}
		else
		{
			KLuaPlayer *pLuaPlayer = dynamic_cast<KLuaPlayer *>(sc.GetObj(1));
			if (pLuaPlayer)
				pPlayer = pLuaPlayer->GetHim();
		}
		QCONFIRM_RET_FALSE(pPlayer);

		pStageCtrl = pPlayer->GetCtrl<KStageCtrl>();
		QCONFIRM_RET_FALSE(pStageCtrl);

		pStageCtrl->OnSpeedUp();

		return 0;
	}

	// -------------------------------------------------------------------------
	// @ClientSvr(C/S)	: S
	// @ClassName		: --
	// @LuaApiName		: GetSpeedUp
	// @Description		: �õ��Ƿ��ڼ���
	// @ReturnCode		: 
	// @ArgumentFlag	: ?
	// @ArgumentComment	: nPlayerId/pPlayer:��ɫId���߶���
	// @LuaMarkEnd
	// -------------------------------------------------------------------------
	INT LuaGetSpeedUp(QLuaScript &sc)
	{
		KPlayer* pPlayer = NULL;
		KStageCtrl* pStageCtrl = NULL;

		if (sc.IsNumber(1))
		{
			INT nPlayerId = sc.GetInt(1);
			QCONFIRM_RET_FALSE(IS_PLAYER(nPlayerId));
			pPlayer = (KPlayer*)g_cCharacterMgr.GetById(nPlayerId);
		}
		else
		{
			KLuaPlayer *pLuaPlayer = dynamic_cast<KLuaPlayer *>(sc.GetObj(1));
			if (pLuaPlayer)
				pPlayer = pLuaPlayer->GetHim();
		}
		QCONFIRM_RET_FALSE(pPlayer);

		pStageCtrl = pPlayer->GetCtrl<KStageCtrl>();
		QCONFIRM_RET_FALSE(pStageCtrl);

		sc.PushNumber(pStageCtrl->sMopInfo.bSpeedUp);

		return 1;
	}


	#include "kstagescript_table.hpp"
}

BOOL g_RegisterStageScript()
{
	return g_cScriptManager.RegisterTableFuncs("KStage", KStageScript::arFunction, countof(KStageScript::arFunction));
}