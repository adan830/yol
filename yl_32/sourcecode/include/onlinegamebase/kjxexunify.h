
#pragma once

#include "Misc/namefilter_i.h"
#include "ksysservice.h"

// -------------------------------------------------------------------------
// ͳһ��ʼ��
BOOL g_UnifyInit();
// ͳһ����ʼ��
BOOL g_UnifyUnInit();
// ÿѭ��ִ��
BOOL g_UnifyLoop();

extern BOOL g_RegisterKUnifyScriptFun();

// ���ֵ��ʹ���
extern INameFilter* g_piNameWordFilter;

#if defined _WINDOWS_ && defined _DEBUG

VOID g_RunTimeMemLeakDetect(UINT uInterval);
INT g_RunTimeMemLeakDetectInit();

#endif

