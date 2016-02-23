#include "stdafx.h"
#include "QRandomName.h"
#include "config/kconfigfile.h"
#include "GameCenter.h"

BOOL QRandomName::GenerateRandomName(CHAR* refNameStr, INT nSex, BOOL bDoubleMode)
{
	INT randFamilyName = g_Random(m_vecFamilyNames.size());
	std::string* familyName = m_vecFamilyNames[randFamilyName];

	INT randNickName = 0;
	std::string* nickName;

	if (nSex == 0)
	{
		randNickName = g_Random(m_vecMaleNames.size());  // ����
		nickName = m_vecMaleNames[randNickName];
	}
	else
	{
		randNickName = g_Random(m_vecFemaleNames.size());  // Ů��
		nickName = m_vecFemaleNames[randNickName];
	}
	
	CHAR szConcat[_NAME_LEN];
	if (!bDoubleMode)
	{
		sprintf(szConcat, "%s%s", familyName->c_str(), nickName->c_str());  // doubleMode�£����ظ�һ��
	}
	else
	{
		// doubleMode�£����ظ�һ��,   ���� -> ��������  ���ְ� -> ������
		sprintf(szConcat, "%s%s%s", familyName->c_str(), (nickName->substr(0, 2)).c_str() , (nickName->substr(0, 2)).c_str()); // ����2��bit
	}
	

	//std::string szConcat = *familyName + *nickName;
	//sprintf(refNameStr, "%s%s", *(familyName->CStr()), *(nickName->CStr())); // ����+����
	strcpy(refNameStr, szConcat);

	// ���һ��������֣����Ƿ�ռ�ã�ѭ��, ���ѭ������10000���ˣ�ֱ�����һ�����ּ�����

	/*KRole* pRole = NULL;
	pRole = g_pGameCenter->m_RoleManager.GetRole(pCreateRoleParam->szRoleName);
	if (pRole != NULL)
	{
		g_pGameCenter->m_Gateway.DoCreateRoleRespond(
			eCreateRoleNameAlreadyExist, pRequest->nPlayerIndex, NULL
			);
		goto EXIT1;
	}*/
	return TRUE;
}

BOOL QRandomName::GetRandomName(CHAR* refNameStr, INT nSex)
{
	CHAR szBuf[_NAME_LEN];
	INT nLoopCount = 0;
	while(TRUE)
	{
		nLoopCount++;
		if (nLoopCount > 10000)  // ѭ���������࣬ǿ�ƽ���
		{
			sprintf(refNameStr, "%s%d", szBuf, g_Random(999) );  // ���ֺ��������
			break;
		}
		else if (nLoopCount > 100)  //����ѭ����������, ��ʼ����˫�������
		{
			//this->GenerateRandomName(szBuf, nSex, TRUE);//by ldy;
		}
		else
		{
			this->GenerateRandomName(szBuf, nSex);
		}

		KRole* pRole = g_pGameCenter->m_RoleManager.GetRole(szBuf);
		if (pRole != NULL) // ������ע��
		{
			continue;
		}

		//���ֿ���
		sprintf(refNameStr, "%s", szBuf);
		break;
	}

	return TRUE;
}

BOOL QRandomName::Init()
{
	BOOL bResult = FALSE;
	ITabFile* pFile = g_OpenTabFile(QDF_RANDOM_NAME);
	LOG_PROCESS_ERROR(pFile);
	for (INT n = 2; n <= pFile->GetHeight(); ++n)
	{
		INT nTmp = 0;
		CHAR szBuf[_NAME_LEN] = "";

		bResult = pFile->GetInteger(n, "index", 0, &nTmp);

		bResult = pFile->GetString(n, "familyname", "", szBuf, countof(szBuf));
		if (szBuf[0] != 0)
		{
			std::string* familyName = new std::string(szBuf);
			m_vecFamilyNames.push_back(familyName);
		}

		bResult = pFile->GetString(n, "malename", "", szBuf, countof(szBuf));
		if (szBuf[0] != 0)
		{
			std::string* maleName = new std::string(szBuf);
			m_vecMaleNames.push_back(maleName);
		}

		bResult = pFile->GetString(n, "femalename", "", szBuf, countof(szBuf));
		if (szBuf[0] != 0)
		{
			std::string* femaleName = new std::string(szBuf);
			m_vecFemaleNames.push_back(femaleName);
		}
	}

	return TRUE;

EXIT0:
	return FALSE;
}

BOOL QRandomName::UnInit()
{
	return TRUE;
}