/* -------------------------------------------------------------------------
//	�ļ���		��	kgcgateway.h
//	������		��	luobaohang
//	����ʱ��	��	2010/4/27 10:31:11
//	��������	��	
//
// -----------------------------------------------------------------------*/
#ifndef __KGCGATEWAY_H__
#define __KGCGATEWAY_H__

// -------------------------------------------------------------------------
class KGcGateway
{
public:
	BOOL Init();
	BOOL Uninit();
	BOOL Run();
	~KGcGateway() { Uninit(); }
private:
	BOOL ProcessPipeData(LPVOID pvData, UINT uDataSize);
	BOOL GameLoop();
private:
	BOOL m_bRunStatus;
};

// -------------------------------------------------------------------------

#endif /* __KGCGATEWAY_H__ */
