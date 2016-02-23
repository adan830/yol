/* -------------------------------------------------------------------------
//	�ļ���		��	kmailcenter.h
//	������		��	xiewenzhe
//	����ʱ��	��	2011/5/17 17:39:02
//	��������	��	�ʼ�����
//
// -----------------------------------------------------------------------*/
#ifndef __KMAILCENTER_H__
#define __KMAILCENTER_H__

// -------------------------------------------------------------------------
#ifdef GAME_CENTER
#include "Misc/objectpool.h"

struct KItemData_Common;

class KMailCenter
{
public:
	KMailCenter();
	~KMailCenter();

public:
	static KMailCenter *Instance() {return &ms_inst;}

public:
	BOOL Init();
	BOOL UnInit();
	BOOL ProcessData(INT nConnectId, LPBYTE pData, UINT uSize);
	BOOL OnPlayerLogin(DWORD dwPlayerId);
	BOOL OnPlayerLogout(DWORD dwPlayerId);
	BOOL OnShutDown();
	BOOL Breath();

public:
	// Ͷ��ϵͳ�ʼ�
	BOOL PostSysMail(DWORD dwReceiverId, LPCSTR pszCaption, LPCSTR pszContent, 
					 KItemData_Common* pItemData, INT nItemCount, INT nIconId);
	
private:
	static KMailCenter				ms_inst;
	BOOL							m_bStartSearch;			// �Ƿ�ʼ��������
	DWORD							m_dwLastPlayerId;		// �ϴ����������Id�����ڱ��������ʼ�
	INT								m_nSearchTime;			// ��һ�α�������ʱ��
	INT								m_nSearchMailBoxCount;	// ÿ֡�������������
	INT								m_nSearchTimeSpace;		// ���ֱ����ļ��ʱ��
};

#endif /* GAME_CENTER */
// -------------------------------------------------------------------------

#endif /* __KMAILCENTER_H__ */
