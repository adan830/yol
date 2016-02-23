/* -------------------------------------------------------------------------
//	�ļ���		��	kloader.h
//	������		��	luobaohang
//	����ʱ��	��	2010/6/12 15:03:59
//	��������	��	Loaderʵ��gcgateway���ӽ����߼�
//
// -----------------------------------------------------------------------*/
#ifndef __KLOADER_H__
#define __KLOADER_H__

#include "serverbase/kgcmoduleinterface.h"
#include "kgcinterface.h"
// -------------------------------------------------------------------------
class KLoader
{
public:
	KLoader(void);
	~KLoader(void);
	static KLoader* Inst();

	BOOL Init(INT nLoaderId);
	BOOL Uninit();
	VOID GameLoop();
	INT InitScript();

	// ע��һ��Gc��ͨѸ�Ľ��նˣ���ģ���ʼ��ʱ����
	IKInterfaceAcceptor* RegisterAcceptor(BYTE byModuleId, IKProcessAcceptor* pIServer);
	// ע��һ��Gc��ͨѸ����ˣ���ģ���ʼʱ����
	IKInterfaceConnector* RegisterConnector(
		BYTE byConnectorModuleId,
		BYTE byAcceptorModuleId,
		IKProcessConnector* pIClient,
		BOOL bIsEssencial);

	BOOL ProcessInterfaceData(BYTE byConnectId, BYTE byAcceptorModuleId, LPBYTE pbData, UINT uDataSize);
private:
	// Acceptor��ProcessorЭ�鴦�����
	BOOL ProcessAcceptorData(BYTE byConnectorModuleId, BYTE byAcceptorModuleId, LPBYTE pbData, UINT uDataSize);
	// Connector��ProcessorЭ�鴦�����
	BOOL ProcessConnectorData(BYTE byConnectorModuleId, BYTE byAcceptorModuleId, LPBYTE pbData, UINT uDataSize);
	// Pipe���ݴ���
	BOOL ProcessPipeData(LPVOID pvData, UINT uDataSize);
	BOOL LoadModules();
	// ����Gc��������
	BOOL CreateGcInterfaces();
private:
	typedef std::list<KInterfaceAcceptor> LST_ACCEPTOR;
	typedef std::list<KInterfaceConnector> LST_CONNECTOR;
	// AcceptModuleId��Ӧ��IKProcessAcceptor
	typedef std::map<BYTE, IKProcessAcceptor*> MP_PROCESS_ACCEPTOR;
	// ConnectorModuleId | AcceptorModuleId��Ӧ��IKProcessConnector
	typedef std::map<WORD, IKProcessConnector*> MP_PROCESS_CONNECTOR;
	// ģ���б�
	typedef std::vector<IKGC_Module*> VEC_MODULE_LIST;
	LST_ACCEPTOR m_lstAcceptor;
	LST_CONNECTOR m_lstConnetor;
	MP_PROCESS_ACCEPTOR m_mpProcessAcceptor;
	MP_PROCESS_CONNECTOR m_mpProcessConnector;
	VEC_MODULE_LIST m_vecModuleList;
	UINT m_nCurElapse;
	INT m_nLoaderId;
};

// -------------------------------------------------------------------------

#endif /* __KLOADER_H__ */
