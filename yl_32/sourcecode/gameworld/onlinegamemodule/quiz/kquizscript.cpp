#include "stdafx.h"
#include "onlinegamebase/kscriptmanager.h"
#include "quiz/quizmanager.h"
#include "quiz/QuizRelayClient.h"
#include "quiz/quizsetting.h"
namespace KQuizScript
{
	// -------------------------------------------------------------------------
	// @ClientSvr(C/S)	: S
	// @ClassName		: --
	// @LuaApiName		: SetQuizIssueCurrentId
	// @Description		: ���ô�����
	// @ReturnCode		: 
	// @ArgumentFlag	: d
	// @ArgumentComment	: ������
	// @LuaMarkEnd
	// -------------------------------------------------------------------------
	INT LuaSetQuizIssueCurrentId(QLuaScript &sc)
	{
		INT nCurrentId = sc.GetInt(1);
		g_cQuizManager.SetCurrentQuizId(nCurrentId);

		return 0;
	}

	// -------------------------------------------------------------------------
	// @ClientSvr(C/S)	: S
	// @ClassName		: --
	// @LuaApiName		: NameListRequest
	// @Description		: �����
	// @ReturnCode		: 
	// @ArgumentFlag	: d
	// @ArgumentComment	: ����
	// @LuaMarkEnd
	// -------------------------------------------------------------------------
	INT LuaNameListRequest(QLuaScript &sc)
	{
		INT nRequest = sc.GetInt(1);
		QuizRelayClient::DoNameListRequest(nRequest);

		return 0;
	}

	// -------------------------------------------------------------------------
	// @ClientSvr(C/S)	: S
	// @ClassName		: --
	// @LuaApiName		: DoIssueStart
	// @Description		: ���������б�
	// @ReturnCode		: 
	// @ArgumentFlag	: 
	// @ArgumentComment	: 
	// @LuaMarkEnd
	// -------------------------------------------------------------------------
	INT LuaDoIssueStart(QLuaScript &sc)
	{
		INT nIssueCount = g_cQuizSetting.GetIssueCount();
		INT nIssueId = g_cQuizManager.GetIssueId();
		g_cQuizManager.SetIssueId(nIssueId+1);
		QuizRelayClient::DoQuestionListRequest(nIssueId+1, nIssueCount);

		return 0;
	}


	#include "kquizscript_table.hpp"
}

BOOL g_RegisterQuizScript()
{
	return g_cScriptManager.RegisterTableFuncs("KQuiz", KQuizScript::arFunction, countof(KQuizScript::arFunction));
}