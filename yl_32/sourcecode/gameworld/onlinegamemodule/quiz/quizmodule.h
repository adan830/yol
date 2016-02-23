/* -------------------------------------------------------------------------
//	�ļ���		��	quizmodule.h
//	������		��	kk
//	����ʱ��	��	2013-8-12 
//	��������	��	
//
// -----------------------------------------------------------------------*/
#pragma once

#include "onlinegameworld/kmodulebase.h"

class QuizModule : public KModuleBase
{
public:
	QuizModule();
	virtual ~QuizModule();

	BOOL OnInit();

	BOOL OnUnInit();

	BOOL Breath();

	virtual BOOL InitProtocol();

	BOOL ProcessProtocol(INT nPlayerIndex, LPCBYTE pbData, UINT uDataLen);
};

extern QuizModule g_QuizModule;

//inline QuizModule* GetQuizModule()
//{
//	static QuizModule s_m;
//	return &s_m;
//}