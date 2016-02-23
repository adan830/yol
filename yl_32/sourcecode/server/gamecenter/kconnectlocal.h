/* -------------------------------------------------------------------------
//	�ļ���		��	kconnectlocal.h
//	������		��	luobaohang
//	����ʱ��	��	2010/6/9 16:03:07
//	��������	��	
//
// -----------------------------------------------------------------------*/
#ifndef __KCONNECTLOCAL_H__
#define __KCONNECTLOCAL_H__
#include "serverbase/kgcmoduleinterface.h"
#include "kgcinterfacedef.h"

// ����������
class KConnectLocal : public KConnectBase
{
public:
	KConnectLocal();
	// ʵ��KConnectBase�ӿ�
	virtual BOOL Send(BYTE byAcceptorModuleId, BYTE byConnectId, LPVOID pvData, UINT uDataSize);
	virtual BOOL IsValid() { return TRUE; }
};

// -------------------------------------------------------------------------
class KConnnectLocalMgr 
{
public:
	KConnnectLocalMgr();
	~KConnnectLocalMgr();
	static KConnnectLocalMgr* Inst();
	KConnectLocal* NewConnect();
	// ����һ����������д�뻺����ָ��
	LPBYTE NewPackage(UINT uDataLen);
	// Э�鴦��
	BOOL ProcessPackage();
private:
	BOOL NewPackageBufBlock();
private:
	std::list<KConnectLocal> m_lstConnect;	// ���Ӷ���
	std::vector<LPBYTE> m_vecPackageBuf;	// Э�黺������Connect��accept��Э�����ݶ��������棬ͨ����ʶλ����
	INT m_nCurblock;						// ��ǰ��������
	LPBYTE m_pCurBlockWritepos;				// ��ǰ��������дָ��
	UINT m_uCurBlockRestSize;				// ��ǰ��������ʣ���ڴ��С
};

// -------------------------------------------------------------------------

#endif /* __KCONNECTLOCAL_H__ */
