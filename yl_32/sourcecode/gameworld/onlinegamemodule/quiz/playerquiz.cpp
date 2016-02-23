#include "stdafx.h"
#include "playerquiz.h"
#include "quizsetting.h"
#include "quizprotocol.h"
#include "quizmanager.h"
#include "onlinegameworld/kplayerprotocolprocess.h"
#include "quizmodule.h"
#include <vector>
#include "onlinegamebase/ksysservice.h"
#include "award/kawardsetting.h"
#include "QuizRelayClient.h"
#include "vip/vipmanager.h"


PlayerQuiz::PlayerQuiz(KCharacter& rcPlayer) : 
				KCharacterCtrlBase(rcPlayer), 
				m_rcPlayer(dynamic_cast<KPlayer&>(rcPlayer)),
				m_bJoin(FALSE),m_bCorrect(FALSE),m_bDouble(FALSE),
				m_bSpirit(FALSE),m_tAnswerTime(0),m_nIssueId(0),m_nCurIssue(0),
				m_nAnswer(0)
{

}

PlayerQuiz::~PlayerQuiz(void)
{
}

BOOL PlayerQuiz::Init()
{
	m_pLunaObj = new LuaPlayerQuiz(m_rcCharacter);
	m_nCorrectQuizChoice = 0;
	m_nCurrentQuizId = 0;
	m_rcQuizSaveData.nDoubleVipCount = 0;
	m_rcQuizSaveData.nGiveAnswerCount = 0;
	m_rcQuizSaveData.nScore = 0;

	return TRUE;
}

BOOL PlayerQuiz::UnInit()
{

	SAFE_DELETE(m_pLunaObj);

	return TRUE;
}

BOOL PlayerQuiz::OnLogin()
{
	return TRUE;
}

BOOL PlayerQuiz::OnLogout()
{
	return TRUE;
}

BOOL PlayerQuiz::Active()
{
	return TRUE;
}

// ����
BOOL PlayerQuiz::OnDbLoad(LPCBYTE pData, SIZE_T uSize)
{
	if (uSize == 0)
		return TRUE;

	KQuizSaveData* pSaveDate				= (KQuizSaveData*)pData; 
	m_rcQuizSaveData.nDoubleVipCount		= MAX(pSaveDate->nDoubleVipCount,0);
	m_rcQuizSaveData.nGiveAnswerCount		= MAX(pSaveDate->nGiveAnswerCount,0);
	m_rcQuizSaveData.nScore					= MAX(pSaveDate->nScore,0);

	UpdateSaveDataNextDay();
	return TRUE;
}

// ����
BOOL PlayerQuiz::OnDbSave(LPBYTE pBuffer, SIZE_T uBuffSize, SIZE_T& uUsedSize)
{
	memcpy(pBuffer, &m_rcQuizSaveData, sizeof(KQuizSaveData));
	pBuffer += sizeof(KQuizSaveData);
	uUsedSize += sizeof(KQuizSaveData);
	return TRUE;
}


// ��������ѡ��
BOOL PlayerQuiz::DoChoice(INT nChoice)
{
	QCONFIRM_RET_FALSE(m_nCurrentQuizId > 0);  // ������������
	QCONFIRM_RET_FALSE(m_nCorrectQuizChoice > 0); // ��������ȷѡ��

	BOOL result = FALSE;
	if (nChoice == m_nCorrectQuizChoice)
	{
		// �ش���ȷ���ͻ��˷�����ȷ
		this->SendClientResult(TRUE);
		// ������д���
		m_nCorrectQuizChoice = 0;
		m_nCurrentQuizId = 0;
		result = TRUE;  // �ش���ȷ
	}
	else
	{
		this->SendClientResult(FALSE);
		result = FALSE;
	}

	ScriptSafe cSafeScript = g_cScriptManager.GetSafeScript();
	g_cScriptManager.SetMe((QLunaBase*)m_rcPlayer.GetScriptInterface());
	cSafeScript->CallTableFunction( "Quiz", "OnChoice", 1, "d", result);  // ѡ�����ýű���

	return result;
}

// ����һ�δ���
BOOL PlayerQuiz::CallQuiz(INT nQuizId)
{
	QuizTemplate* pQuizTemplate = g_cQuizSetting.GetQuizTemplate(nQuizId);
	QCONFIRM_RET_FALSE(pQuizTemplate);

	CHAR* vecAnswers[QUIZ_MAX_ANSWERS_COUNT];

	INT nValidAnswerCount = 1;
    if (strlen(pQuizTemplate->szAnswer2) > 0)
	{
		nValidAnswerCount++;
	}
	if (strlen(pQuizTemplate->szAnswer3) > 0)
	{
		nValidAnswerCount++;
	}
	if (strlen(pQuizTemplate->szAnswer4) > 0)
	{
		nValidAnswerCount++;
	}

	DWORD dwRandChoice = KSysService::Rand(nValidAnswerCount) + 1;  // ����� ��ȷѡ�� 
	vecAnswers[dwRandChoice-1] = pQuizTemplate->szCorrectAnswer;  // ��ȷ�𰸷���

	// ��������
	DWORD dwWrongAnswerCount = 0; // �Ѿ������˼��������
	for (DWORD i=1; i <= QUIZ_MAX_ANSWERS_COUNT; i++)
	{
		if (i != dwRandChoice)  // ��ȷ��λ������
		{
			if (dwWrongAnswerCount == 0) vecAnswers[i-1] = pQuizTemplate->szAnswer2;
			else if (dwWrongAnswerCount == 1) vecAnswers[i-1] = pQuizTemplate->szAnswer3;
			else if (dwWrongAnswerCount == 2) vecAnswers[i-1] = pQuizTemplate->szAnswer4;
			dwWrongAnswerCount++;
		}
	}

	// ������ȷѡ���ţ������𰸲���
	// ��֯�𰸳�һ���ַ���, ��<end>�ֿ�
	CHAR szAnswersGroup[MAX_SENTENCE_LENGTH * QUIZ_MAX_ANSWERS_COUNT];  // ������ 256 * 4��С

	sprintf(szAnswersGroup, "%s<end>%s<end>%s<end>%s", 
		vecAnswers[0], vecAnswers[1], vecAnswers[2], vecAnswers[3]);

	this->SendClientQuestion(pQuizTemplate->szQuestion, szAnswersGroup);

	// ��¼���ڴ���
	m_nCurrentQuizId = pQuizTemplate->nQuizId;

	// ��¼��ȷ��ѡ��
	m_nCorrectQuizChoice = (INT)dwRandChoice;

	return TRUE;
}

// ���߿ͻ����Ƿ���
BOOL PlayerQuiz::SendClientResult(BOOL bCorrect, BOOL bEndQuiz)
{
	PTC_S2C_RESULT ptcResult;
	ptcResult.byProtocol = (BYTE)emS2C_RESULT;
	ptcResult.byCorrected = (BYTE)bCorrect;
	ptcResult.byEndQuiz = (BYTE)bEndQuiz;

	if (bEndQuiz == TRUE)
	{
		// ��������
		// ������д���
		m_nCorrectQuizChoice = 0;
		m_nCurrentQuizId = 0;
	}

	return g_QuizModule.GetProtocolProcessor()->SendData(m_rcPlayer.GetPlayerIndex(), ptcResult);
}

BOOL PlayerQuiz::SendClientQuestion(CHAR* szQuestion, CHAR* szAnswers)
{
	// Э�鴫��
	BYTE _sbyPacketBuffer[64000]; // ���������
	// ����
	PTC_S2C_QUESTION* ptcQuestion = (PTC_S2C_QUESTION *)_sbyPacketBuffer;
	*ptcQuestion = PTC_S2C_QUESTION();  // ʹ�û���ռ����Э��

	ptcQuestion->byProtocol = (BYTE)emS2C_QUESTION;

	QStrCpyLen(ptcQuestion->szQuestions, szQuestion, sizeof(ptcQuestion->szQuestions));  // ���� �ַ������Ƶ�Э��

	size_t answerLen = strlen(szAnswers) + 1;
	QStrCpyLen(ptcQuestion->szAnswers, szAnswers, answerLen);  // �𰸸��Ƶ�Э��

	g_QuizModule.GetProtocolProcessor()->SendLenData(m_rcPlayer.GetPlayerIndex(), *ptcQuestion, sizeof(*ptcQuestion) + answerLen);// + sizeof("\0"));

	return TRUE;
}

//-----------------------------------------�����---------------------------------------
BOOL PlayerQuiz::UpdateSaveDataNextDay()
{
	INT nJoinFirst = 0;
	INT nJoinSecond = 0;
	ScriptSafe cSafeScript1 = g_cScriptManager.GetSafeScript();
	ScriptSafe cSafeScript2 = g_cScriptManager.GetSafeScript();
	cSafeScript1->CallTableFunction("Player" , "GetDegreeValue", 1, "os", m_rcPlayer.GetScriptInterface(), "QuizJoinFirst");
	nJoinFirst = cSafeScript1->GetInt(-1);
	cSafeScript2->CallTableFunction("Player" , "GetDegreeValue", 1, "os", m_rcPlayer.GetScriptInterface(), "QuizJoinSecond");
	nJoinSecond = cSafeScript2->GetInt(-1);

	if (nJoinFirst > 0 && nJoinSecond > 0)
	{
		m_rcQuizSaveData.nDoubleVipCount = 0;
		m_rcQuizSaveData.nGiveAnswerCount = 0;
		m_rcQuizSaveData.nScore = 0;
	}
	return TRUE;
}

//BOOL PlayerQuiz::DoSumitIntegral()
//{
//	ScriptSafe cSafeScript = g_cScriptManager.GetSafeScript();
//	g_cScriptManager.SetMe((QLunaBase*)m_rcPlayer.GetScriptInterface());
//	INT nMutilpe = 1;
//	if (m_bDouble != 0)
//		nMutilpe = 2;
//	cSafeScript->CallTableFunction("Quiz", "DoSumitIntegral", 0, "oddd",
//		m_rcPlayer.GetScriptInterface(), g_cQuizManager.GetCurrentQuizId(), nMutilpe, m_rcQuizSaveData.nScore);
//	return TRUE;
//}

BOOL PlayerQuiz::DoJoinIssue(INT nJoin)
{
	m_bJoin = nJoin;
	ScriptSafe cSafeScript = g_cScriptManager.GetSafeScript();
	g_cScriptManager.SetMe((QLunaBase*)m_rcPlayer.GetScriptInterface());
	cSafeScript->CallTableFunction( "Quiz", "JoinQuizIssue", 0, "od", m_rcPlayer.GetScriptInterface(), nJoin);
	return TRUE;
}

BOOL PlayerQuiz::DoClientAnswer(INT nIssueId, INT nAnswerChoice, BYTE byDouble, BYTE bySpirit)
{
	if (g_cQuizManager.GetCurrentQuizId() != nIssueId)
		return FALSE;

	m_tAnswerTime = KSysService::Time(NULL);
	m_rcQuizSaveData.nGiveAnswerCount += (INT)bySpirit;
	//m_rcQuizSaveData.nDoubleVipCount += (INT)byDouble;
	m_nAnswer = nAnswerChoice;
	m_nCurIssue = nIssueId;
	m_nIssueId = g_cQuizManager.GetIssueId();
	m_bSpirit = bySpirit == 1 ? TRUE : FALSE;
	if (bySpirit ==  1 || g_cQuizSetting.GetQuizIssueTemplate(g_cQuizManager.GetCurrentIssueValue())->nCorrectAnswer == nAnswerChoice)
	{
		m_bCorrect = TRUE;
		m_bDouble = byDouble == 1 ? TRUE : FALSE;
	}
	
	return TRUE;
}

BOOL PlayerQuiz::DoClientSpirit(INT nIssueId, INT nAnswerChoice)
{
	DoClientAnswer(nIssueId, nAnswerChoice, (BYTE)m_bDouble, 1);
	QUIZ_S2C_ISSUE_SPIRIT ptcSpirit;
	ptcSpirit.byProtocol		= (BYTE)emS2C_ISSUE_SPIRIT;
	ptcSpirit.nSpiritCount		= m_rcQuizSaveData.nGiveAnswerCount;
	INT nStage					= m_rcPlayer.GetVipLevel();
	if (nStage > 0)
	{
		CONST QNumericalAward* pNumericalAward	= g_cAwardSetting.RequestNumericalAward(QUIZ_SPIRIT, nStage, m_rcQuizSaveData.nGiveAnswerCount + 1);
		ptcSpirit.nNeedCoin		= pNumericalAward == NULL ? 0 : pNumericalAward->nCost;
	}
	else
	{
		ptcSpirit.nNeedCoin		= 0;
	}

	return g_QuizModule.GetProtocolProcessor()->SendData(m_rcPlayer.GetPlayerIndex(), ptcSpirit);
}

BOOL PlayerQuiz::SendIssueStart(INT ntTimeSpan, INT nInitSpiritCoin,INT nDoubleFreeTimes, INT nDoubleMaxFreeTimes)
{
	UpdateSaveDataNextDay();
	QUIZ_S2C_ISSUE_START ptcStart;
	ptcStart.byProtocol = (BYTE)emS2C_ISSUE_START;
	ptcStart.nTimeSpan = ntTimeSpan;
	ptcStart.nDoubleVipTimes			= m_rcQuizSaveData.nDoubleVipCount;
	ptcStart.nDoubleFreeTimes			= nDoubleFreeTimes;
	ptcStart.nDoubleAllFreeTimes		= nDoubleMaxFreeTimes;
	ptcStart.nSpiritNeedCoins			= 0;
	INT nStage							= m_rcPlayer.GetVipLevel();
	ptcStart.nDoubleAllVipTimes		= g_cVipManager.GetTotalBuyCount(m_rcCharacter.GetId(), 7);//g_cAwardSetting.RequestMaxLineValue(QUIZ_DOUBLE, nStage);
	ptcStart.nDoubleNeedCoins = 0;
	if (nStage > 0)
	{
		CONST QNumericalAward* pNumericalAward	= g_cAwardSetting.RequestNumericalAward(QUIZ_DOUBLE, nStage, m_rcQuizSaveData.nDoubleVipCount + 1);
		ptcStart.nDoubleNeedCoins		= pNumericalAward == NULL ? 0 : pNumericalAward->nCost;
	}

	return g_QuizModule.GetProtocolProcessor()->SendData(m_rcPlayer.GetPlayerIndex(), ptcStart);
}

BOOL PlayerQuiz::SendIssueResult(INT nTimeSpan)
{
	QUIZ_S2C_ISSUE_RESULT ptcResult;
	ptcResult.byProtocol = (BYTE)emS2C_ISSUE_RESULT;
	ptcResult.byCorrected = (BYTE)m_bCorrect;
	ptcResult.byEndQuiz = g_cQuizManager.GetCurrentQuizId() == QUESTION_COUNT ? 1 : 0;
	ptcResult.nIntegral = m_rcQuizSaveData.nScore;
	ptcResult.nTimeSpan = nTimeSpan;

	m_bCorrect = FALSE;
	m_bDouble = FALSE;
	return g_QuizModule.GetProtocolProcessor()->SendData(m_rcPlayer.GetPlayerIndex(), ptcResult);
}

BOOL PlayerQuiz::SendIssueRanking(QUIZ_S2C_ISSUE_RANKING* issueRank)
{
	IMemBlock* piPackage					= NULL;
	QUIZ_S2C_ISSUE_RANKING* ptcRanking		= NULL;
	piPackage = QCreateMemBlock(sizeof(QUIZ_S2C_ISSUE_RANKING)+sizeof(QUIZ_ISSUE_RANK_INFO) * issueRank->nCount);
	ptcRanking = (QUIZ_S2C_ISSUE_RANKING*)piPackage->GetData();
	LOG_PROCESS_ERROR(ptcRanking);
	LOG_PROCESS_ERROR(issueRank);

	ptcRanking->byProtocol					= (BYTE)emS2C_ISSUE_RANKING;
	ptcRanking->nCount						= issueRank->nCount;
	memcpy(ptcRanking->arrInfo, issueRank->arrInfo, sizeof(QUIZ_ISSUE_RANK_INFO) * issueRank->nCount);
	g_QuizModule.GetProtocolProcessor()->SendLenData(m_rcPlayer.GetPlayerIndex(), *ptcRanking, sizeof(QUIZ_S2C_ISSUE_RANKING)+sizeof(QUIZ_ISSUE_RANK_INFO) * issueRank->nCount);


EXIT0:
	SAFE_RELEASE(piPackage);
	return TRUE;
}

BOOL PlayerQuiz::SendIssueQuestion(INT nTimeSpan, INT nInitSpiritCoin, INT nAddSpiritCoin,INT nDoubleFreeTimes, INT nDoubleMaxFreeTimes)
{
	IMemBlock* piPackage					= NULL;
	QUIZ_S2C_ISSUE_QUESTION* ptcQuestion	= NULL;
	size_t answerLen						= 0;
	INT nStage								= 0;
	CONST QNumericalAward* pNumericalAward	= NULL;
	CHAR szAnswersGroup[MAX_SENTENCE_LENGTH * QUIZ_MAX_ANSWERS_COUNT];  // ������ 256 * 4��С
	QuizIssueTemplate *pIssue				= g_cQuizSetting.GetQuizIssueTemplate(g_cQuizManager.GetCurrentIssueValue());
	LOG_PROCESS_ERROR(pIssue);

	sprintf(szAnswersGroup, "%s<end>%s<end>%s<end>%s", 
		pIssue->szAnswer1, pIssue->szAnswer2, pIssue->szAnswer3, pIssue->szAnswer4);
	answerLen = strlen(szAnswersGroup) + 1;
	piPackage = QCreateMemBlock(sizeof(QUIZ_S2C_ISSUE_QUESTION)+answerLen);
	ptcQuestion = (QUIZ_S2C_ISSUE_QUESTION*)piPackage->GetData();
	LOG_PROCESS_ERROR(ptcQuestion);

	ptcQuestion->byProtocol					= (BYTE)emS2C_ISSUE_QUESTION;
	ptcQuestion->nQuestionId				= g_cQuizManager.GetCurrentQuizId();
	ptcQuestion->nQuestionCount				= QUESTION_COUNT;
	ptcQuestion->nTimeSpan					= nTimeSpan;
	ptcQuestion->nDoubleVipTimes			= m_rcQuizSaveData.nDoubleVipCount;
	ptcQuestion->nDoubleFreeTimes			= nDoubleFreeTimes;
	ptcQuestion->nDoubleAllFreeTimes		= nDoubleMaxFreeTimes;
	ptcQuestion->nCorrectAnswer				= pIssue->nCorrectAnswer;
	ptcQuestion->nSpiritTimes				= m_rcQuizSaveData.nGiveAnswerCount;

	if (m_nIssueId == g_cQuizManager.GetIssueId() && m_nCurIssue == g_cQuizManager.GetCurrentQuizId())
	{
		ptcQuestion->byDouble				= m_bDouble == TRUE ? 1 : 0;
		ptcQuestion->bySpirit				= m_bSpirit == TRUE ? 1 : 0;
		ptcQuestion->nAnswerChoice			= m_nAnswer;
	}
	else
	{
		ptcQuestion->byDouble				= 0;
		ptcQuestion->bySpirit				= 0;
		ptcQuestion->nAnswerChoice			= 0;

		m_bCorrect							= FALSE;//����
	}

	nStage								= m_rcPlayer.GetVipLevel();
	ptcQuestion->nDoubleAllVipTimes		= g_cVipManager.GetTotalBuyCount(m_rcCharacter.GetId(), 7);//g_cAwardSetting.RequestMaxLineValue(QUIZ_DOUBLE, nStage);
	pNumericalAward						= nStage > 0 ? g_cAwardSetting.RequestNumericalAward(QUIZ_DOUBLE, nStage, m_rcQuizSaveData.nDoubleVipCount + 1) : 0;
	ptcQuestion->nDoubleNeedCoins		= pNumericalAward == NULL ? 0 : pNumericalAward->nCost;

	ptcQuestion->nSpiritMaxTimes		= g_cVipManager.GetTotalBuyCount(m_rcCharacter.GetId(), 18);//g_cAwardSetting.RequestMaxLineValue(QUIZ_SPIRIT, nStage);
	pNumericalAward						= nStage > 0 ? g_cAwardSetting.RequestNumericalAward(QUIZ_SPIRIT, nStage, m_rcQuizSaveData.nGiveAnswerCount + 1) : 0;
	ptcQuestion->nSpiritNeedCoins		= pNumericalAward == NULL ? 0 : pNumericalAward->nCost;

	QStrCpyLen(ptcQuestion->szQuestions, pIssue->szQuestion, sizeof(ptcQuestion->szQuestions));

	QStrCpyLen(ptcQuestion->szAnswers, szAnswersGroup, answerLen);
	g_QuizModule.GetProtocolProcessor()->SendLenData(m_rcPlayer.GetPlayerIndex(), *ptcQuestion, sizeof(*ptcQuestion) + answerLen);
	
EXIT0:
	SAFE_RELEASE(piPackage);
	return TRUE;
}


LuaPlayerQuiz* PlayerQuiz::GetScriptInterface() CONST
{
	return m_pLunaObj;
}