
/* -------------------------------------------------------------------------
//	�ļ���		��	quizmanager.h
//	������		��	zhengbozhou
//	����ʱ��	��	2013-12-11
//	��������	��  
// -------------------------------------------------------------------------*/

#ifndef __KQUIZMANAGER_H__
#define __KQUIZMANAGER_H__
#include "stdafx.h"
#include "onlinegameworld/korpgworld.h"
#include "quizprotocol.h"
#include "serverbase/protocol/Relay_GS_Protocol.h"
#define QUESTION_COUNT 30
#define RANK_COUNT 10

struct KQUIZ_ISSUE_RANK
{
	QUIZ_RANK_INFO arrInfo[10];
};

class KQuizManager
{
public:
	KQuizManager();
	~KQuizManager();

public:
	BOOL Init();
	BOOL UnInit();
	BOOL Breath();

private:
	INT m_nIssueId;															//����id��ÿ�λ+1
	INT m_nCurrentQuizId;													// ����������Ŀ 1-30
	std::vector<INT> m_vecQuestion;											//���δ���������
	KQUIZ_ISSUE_RANK m_Rank;

public:
	VOID SetCurrentQuizId(INT nCurrentQuizId);
	INT GetCurrentQuizId();

	VOID SetIssueId(INT nIssueId);
	INT GetIssueId();

	VOID SetVecQuestion(INT nQuestion[]);
	INT GetCurrentIssueValue();

	VOID SetRank(R2S_QUIZ_NAME_LIST_RESPOND* pRank);
	INT GetRank(DWORD dwRoldId);

	BOOL SendRankAward(KPlayer *pPlayer, INT nRank);
};

extern KQuizManager g_cQuizManager;
extern KOrpgWorld g_cOrpgWorld;
#endif