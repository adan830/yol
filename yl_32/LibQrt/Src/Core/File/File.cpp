
#include "CorePrivate.h"
#include "AloneFile.h"
#include "QLog.h"
#include "Runtime/Debug.h"



//---------------------------------------------------------------------------
// �ļ���ȡģʽ 0 = ���ȴӴ��̶�ȡ !0 = ���ȴ��ļ�����ȡ
static int s_nEngineFindFilePackFirst = 1;

static int s_nUseNewPackageFile = 0;

//���ò����ļ������ȴ���(�Ƿ��Ȳ��Ҵ���ļ�)
void
g_SetFindFileMode(int FindPakFirst)
{
	s_nEngineFindFilePackFirst = FindPakFirst;
}

// 0-��Pak, 1-�°�Pak
void
g_SetPackageVersion(int nPackageVersion)
{
    if (nPackageVersion == 0)
    {
        s_nUseNewPackageFile = 0;
    }
    else if (nPackageVersion == 1)
    {
        s_nUseNewPackageFile = 1;
    }
}

//���ش���ļ�
int
g_LoadPackageFiles(const char* pListFile, const char* pSection)
{
	//if (pListFile && pSection && pListFile[0] && pSection[0])
	//	return g_EnginePackList.Open(pListFile, pSection);
	return false;
}

//ж�ش���ļ�
void g_ClearPackageFiles()
{
	//g_EnginePackList.Close();
}

IFile*
g_OpenFile(const char* FileName, int ForceSingleFile/* = false*/, int ForWrite/* = false*/)
{
	//QLogPrintf(LOG_INFO,"open file name is %s",FileName);
	if (FileName == NULL || FileName[0] == 0)
		return 0;

	int	TryTurn[3] = { 0, 0, 0};	//0-�����ԣ�1-��ȡ�����ļ���2-��ȡ����ļ�, 3-ʹ���°���ʽ���ļ�
	if (ForceSingleFile || ForWrite)
	{
		TryTurn[0] = 1;
	}
    else
    {
        if (s_nUseNewPackageFile)
        {
            TryTurn[0] = 3;
        }

	    if (s_nEngineFindFilePackFirst)
	    {
		    TryTurn[1] = 2;
		    TryTurn[2] = 1;
	    }
	    else
	    {
		    TryTurn[1] = 1;
		    TryTurn[2] = 2;
	    }
    }

	IFile*	pFile = NULL;

	//for (int nTry = 0; nTry < 3; nTry++)
	//{
 //       if (TryTurn[nTry] == 3)
 //       {
 //           KGPackFile	newPak;
 //           if (newPak.Open(FileName))
 //           {
 //               pFile = newPak.Deprive();
 //               break;
 //           }
 //       }
	//	else if (TryTurn[nTry] == 2)
	//	{
	//		KPackFile	pak;
 //           if (pak.Open(FileName))
 //           {
 //               pFile = pak.Deprive();
 //               break;
 //           }
	//	}
	//	else if (TryTurn[nTry] == 1)
		{
			pFile = QAloneFile::Open(FileName, ForWrite);
			//if (pFile)
			//	break;
		}
	//}
	return pFile;
}
//
//// add by zhuchengmin 2009.08.11
//CORE_API_C
//IFile* g_OpenFileInPak(const char* FileName)
//{
//    IFile* pFile = NULL;
//
//    if (FileName == NULL || FileName[0] == 0)
//        return 0;
//
//    if (s_nUseNewPackageFile)
//    {
//        KGPackFile pak;
//
//        if (pak.Open(FileName))
//            pFile = pak.Deprive();
//    }
//    else
//    {
//        KPackFile pak;
//
//        if (pak.Open(FileName))
//            pFile = pak.Deprive();
//    }
//
//    return pFile;
//}

IFile*	g_CreateFile(const char* FileName)
{
	IFile* piFile = QAloneFile::Create(FileName);

	if (!piFile)
		g_DebugLog("ERROR: failed to create file[%s]!", FileName);

	return piFile;
}

