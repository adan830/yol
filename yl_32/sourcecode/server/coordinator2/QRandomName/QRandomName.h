#pragma once
#include "stdafx.h"
#include "Runtime/qstring.h"

//
//struct QRandomNameTemplate
//{
//	DWORD dwId;
//	QString strFamilyName;// ����
//	QString strMaleName;// ������
//	QString strFemaleName;// Ů����
//};
//
//typedef std::map<DWORD, QRandomNameTemplate> QRandomNameMap;


class QRandomName
{
public:
	BOOL Init();
	BOOL UnInit();
	BOOL GetRandomName(CHAR* refNameStr, INT nSex);

private:
	std::vector<std::string*> m_vecFamilyNames;
	std::vector<std::string*> m_vecFemaleNames;
	std::vector<std::string*> m_vecMaleNames;

	BOOL GenerateRandomName(CHAR* refNameStr, INT nSex, BOOL bDobuleMode = FALSE);  // doubleģʽ��  ���������ظ����Σ�

};