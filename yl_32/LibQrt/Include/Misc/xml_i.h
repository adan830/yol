
#pragma once

class QLuaScript;

// -------------------------------------------------------------------------
interface IXmlNode
{
	// ��ȡ��һ��ָ���ӽڵ��textֵ�����szNodeName = NULL�����ȡ�Լ���textֵ
	virtual LPCSTR GetValue(LPCSTR szNodeName = NULL, LPSTR pszValue = NULL) = 0;
	// ���Ҫ��ȡ�Լ��ڵ��ֵ��szNodeName��ΪNULL�������ȡ��һ������ΪszNodeName���ӽڵ��ֵ
	virtual LPCSTR GetValue(LPCSTR szNodeName, int* pnValue) = 0;
	// ���Ҫ��ȡ�Լ��ڵ��ֵ��szNodeName��ΪNULL�������ȡ��һ������ΪszNodeName���ӽڵ��ֵ
	virtual LPCSTR GetValue(LPCSTR szNodeName, double* pdValue) = 0;

	virtual LPCTSTR GetAttribute(LPCSTR szNodeName, LPSTR pszValue = NULL) = 0;
	virtual LPCTSTR GetAttribute(LPCSTR szNodeName, int* pnValue) = 0;
	virtual LPCTSTR GetAttribute(LPCSTR szNodeName, double* pdValue) = 0;

	virtual VOID SetAttribute(LPCSTR szNodeName, LPSTR pszValue = NULL) = 0;
	virtual IXmlNode* GetFirstChild(LPCSTR szNodeName) = 0;
	virtual IXmlNode* GetNextSibling(LPCSTR szNodeName) = 0;
};

interface IXmlDocument
{
	virtual BOOL Load(LPCSTR pszXMLFileName) = 0;
	virtual UINT Release() = 0;
	virtual IXmlNode* GetNode(LPCSTR szNodeName) = 0;
	virtual BOOL Push2Script(QLuaScript& sc) = 0;
	virtual BOOL Save(LPCSTR pszXmlFile) = 0;
	virtual BOOL LoadFromBuffer(LPCTSTR szBuffer, INT nLength)= 0;
	virtual BOOL SaveToBuffer(LPSTR szBuffer, INT nLength) = 0;
};

// nCodePage for Windows, pszCodePage for linux
IXmlDocument* gCreateXmlDocument(INT nCodePage = 0, LPCSTR pszCodePage = "gbk");

// -------------------------------------------------------------------------
