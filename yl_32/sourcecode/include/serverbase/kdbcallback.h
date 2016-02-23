/* -------------------------------------------------------------------------
//	�ļ���		��	kbcallback.h
//	������		��	luobaohang
//	����ʱ��	��	2007-5-16 9:58:48
//	��������	��	���ݿ�����ص��ӿ�
//
// -----------------------------------------------------------------------*/
#ifndef __KGC_DBCALLBACK_H__
#define __KGC_DBCALLBACK_H__

#include "Misc/utilities.h"
#include "Misc/objectpool.h"
#include "onlinegamebase/mysqldatabase.h"

// -------------------------------------------------------------------------
class IKDBThreadCallback;
class IKMainThreadCallback;
struct IKGcDatabase
{
	// �������ݿ�����
	virtual BOOL PushDBAffair(IKDBThreadCallback *pAffair, INT nParam = 0,
		LPVOID pParam = NULL, BOOL bPriority = FALSE) = 0;
	// ���ݿ���������߳̽���ص�
	virtual BOOL PushMainThreadCallBack(IKMainThreadCallback *pCallback,
		INT nParam = 0, LPVOID pParam = NULL) = 0;
	// �����ⲿ��ִ�����ݿ��ȡ��ѯ����ͨ��IKDBThreadCallback��
	virtual KMySqlDatabase& GetDatabase()  = 0;
	// �߳���������ݿ��߳������߳����ݷ��ʳ�ͻ
	virtual BOOL DBThreadLock() = 0;
	virtual BOOL DBThreadUnLock() = 0;
};

class KDBBaseCallback
{
public:
	INT m_nObjectId;	//���ڴ洢�ص�����ID�Ա��ͷ�
};

//���ݿ��̵߳�����ص��ӿڣ��������߳���push�������ݿ��̻߳ص������е���
//ע�����е����ݿ�������������ݿ��߳̽��У��߳�������ʹ��IKGcDatabase::DBThreadLock()����Ҫ���ⶨ����
class IKDBThreadCallback
{
public:
	//�ͷ�����ص��������̺߳����ݿ��̶߳����ܵ���
	virtual VOID Release() {};
	//���ݿ��̵߳���
	virtual BOOL DBThreadCallback(INT nParam, LPVOID pParam) = 0;
};
//�����ص�������ʱ�Ӹ���̳�
class KDBThreadCallback : public IKDBThreadCallback, public KDBBaseCallback
{
};

//���̻߳ص��ӿڣ��������ݿ��߳���push�������̻߳ص������е���
class IKMainThreadCallback
{
public:
	//�ͷ�����ص��������̺߳����ݿ��̶߳����ܵ���
	virtual VOID Release() {};
	//���̵߳���
	virtual BOOL MainThreadCallback(INT nParam, LPVOID pParam) = 0;
};
//�����ص�������ʱ�Ӹ���̳�
class KMainThreadCallback : public IKMainThreadCallback, public KDBBaseCallback
{
};

//�������ݿ��̲߳�ѯ��ϣ������̴߳����ѯ���
class KDBQueryRSCallback : public KMainThreadCallback
{
public:
	//���������Release�б�����ñ����Release
	virtual VOID Release() { m_QueryResult.Release(); }
	virtual BOOL MainThreadCallback(INT nParam, LPVOID pParam) = 0;
	KMySqlResult m_QueryResult;
};	

//���ݿ�ص����������������ڻص��������ɺ��ͷ�
//ICLASST��ʵ�ʵĻص������࣬һ���KDBThreadCallback��KMainThreadCallback�̳�
template<class ICLASST, INT TN_BASESIZE = 64, INT TN_INCSIZE = TN_BASESIZE>
class KDBCallbackClassGentor
{
public:
	KDBCallbackClassGentor(){ m_DBCBObjGenerator.Init(TN_BASESIZE, TN_INCSIZE); }
	//Call this to create new callback object
	static ICLASST *CreateNew(IKGcDatabase* pDatabase)
	{
		INT nObjectID;
		pDatabase->DBThreadLock();
		ICLASST * pNewObject = s_Self.m_DBCBObjGenerator.New(&nObjectID);
		pDatabase->DBThreadUnLock();
		if (!pNewObject)
		{
			ASSERT(FALSE);
			return NULL;
		}
		//ICLASST Must be Drived From KDBBaseCallback
		static_cast<KDBBaseCallback *>(pNewObject)->m_nObjectId = nObjectID;
		return pNewObject;
	}
	//Call this in callback object's release() function
	static VOID Free(IKGcDatabase* pDatabase, ICLASST *piClass)
	{
		pDatabase->DBThreadLock();
		s_Self.m_DBCBObjGenerator.Free(static_cast<KDBBaseCallback *>(piClass)->m_nObjectId);
		pDatabase->DBThreadUnLock();
	}
	~KDBCallbackClassGentor()
	{
		if (m_DBCBObjGenerator.GetPeakValue() != m_DBCBObjGenerator.GetFreeCount())
			Q_Error(m_DBCBObjGenerator.GetPeakValue() << " " << m_DBCBObjGenerator.GetFreeCount());
	}
private:
	KIncObjPool2<ICLASST> m_DBCBObjGenerator;
	static KDBCallbackClassGentor<ICLASST, TN_BASESIZE, TN_INCSIZE> s_Self;
};
template<class ICLASST, INT TN_BASESIZE, INT TN_INCSIZE> 
	KDBCallbackClassGentor<ICLASST, TN_BASESIZE, TN_INCSIZE> 
		KDBCallbackClassGentor<ICLASST, TN_BASESIZE, TN_INCSIZE>::s_Self;
// -------------------------------------------------------------------------
#endif /* __KGC_DBCALLBACK_H__ */
