
#include "CorePrivate.h"
#include <stdarg.h>

//---------------------------------------------------------------------------
// ����:	g_DebugLog
// ����:	����Դ������������Ϣ
// ����:	Fmt		��ʽ���ַ���
//			...		������ַ���
//---------------------------------------------------------------------------
void g_DebugLog(const char* Fmt, ...)
{
	#ifdef _DEBUG
		char buffer[1024];
		va_list va;
		va_start(va, Fmt);
		vsprintf(buffer, Fmt, va);
		va_end(va);
		strcat(buffer, "\n");
#ifdef WIN32
		OutputDebugStringA(buffer);
#else
		printf("%s", buffer);
#endif
	#endif
}
