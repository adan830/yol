#ifndef _QUIZ_SERVERHANDLER_H__
#define _QUIZ_SERVERHANDLER_H__

#include "serverbase/protocol/Relay_GS_Protocol.h"

class QuizServerHandler
{
public:
	QuizServerHandler();
	~QuizServerHandler();

public:
	//����ύ����
	static VOID OnSubmitIntegralRequest(BYTE* pbyData, size_t uDataLen, int nConnIndex);

	//�����
	static VOID OnNameListRequest(BYTE* pbyData, size_t uDataLen, int nConnIndex);

	//��Ŀ���
	static VOID OnQuestionListRequest(BYTE* pbyData, size_t uDataLen, int nConnIndex);

	//���ذ�
	static VOID DoNameListRespond(INT nConnIndex);

	//������Ŀ
	static VOID DoQuestionListRespond(INT nConnIndex, INT nIssue, INT nMaxQuestionCount);

private:
	static inline BOOL Send(int nConnIndex, IMemBlock* piBuffer);
};

#endif