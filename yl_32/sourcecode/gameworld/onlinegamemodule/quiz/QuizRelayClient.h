#ifndef _QUIZ_RELAYCLIENT_H__
#define _QUIZ_RELAYCLIENT_H__

class QuizRelayClient
{
public:
	QuizRelayClient();
	~QuizRelayClient();

public:

	//���������Ŀ
	static VOID DoQuestionListRequest(INT nIssueId, INT nMaxQuestionCount);

	//�ύ����
	static VOID DoSumitScoreRequest(DWORD dwRoldId, INT nIntegral, CONST CHAR* szName);

	//�����s
	static VOID DoNameListRequest(INT nRequest);
	
	//����ǰʮ����
	static VOID OnNameListRespond(BYTE* pbyData, size_t uDataLen);

	//������Ŀ���
	static VOID OnQuestionListRespond(BYTE* pbyData, size_t uDataLen);

private:
	static inline BOOL Send(IMemBlock* piBuffer);
};
#endif