/* -------------------------------------------------------------------------
//	�ļ���		��	kconnectlocal.cpp
//	������		��	luobaohang
//	����ʱ��	��	2010/6/9 16:03:18
//	��������	��	
//
// -----------------------------------------------------------------------*/

#include "stdafx.h"
#include "kloader.h"
#include "kconnectlocal.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// LocalConnect��Э�黺������С����4MΪ����
#define KD_LOCAL_CONN_BUF_MEM_BLOCK_SIZE (4 * 1024 * 1024)

// -------------------------------------------------------------------------

KConnectLocal::KConnectLocal() : KConnectBase(emKGC_CONNECT_LOCAL)
{
}

BOOL KConnectLocal::Send(BYTE byAcceptorModuleId, BYTE byConnectId, LPVOID pvData, UINT uDataSize)
{
	LPBYTE pbWritepos = KConnnectLocalMgr::Inst()->NewPackage(uDataSize + 2);
	// д��InterfaceType��ConnectorModule����ͷ
	*pbWritepos++ = byConnectId;
	*pbWritepos++ = byAcceptorModuleId;
	memcpy(pbWritepos, pvData, uDataSize);
	return TRUE;
}

// -------------------------------------------------------------------------
KConnnectLocalMgr::KConnnectLocalMgr()
{
	NewPackageBufBlock();
	m_pCurBlockWritepos = m_vecPackageBuf.back();
	m_uCurBlockRestSize = KD_LOCAL_CONN_BUF_MEM_BLOCK_SIZE;
	m_nCurblock = 0;
}

KConnnectLocalMgr::~KConnnectLocalMgr()
{
	for (UINT i = 0; i < m_vecPackageBuf.size(); i++)
	{
		delete[] m_vecPackageBuf[i];
	}
}

KConnectLocal* KConnnectLocalMgr::NewConnect()
{
	m_lstConnect.push_back(KConnectLocal());
	return &m_lstConnect.back();
}

BOOL KConnnectLocalMgr::NewPackageBufBlock()
{
	LPBYTE pBlock = new BYTE [KD_LOCAL_CONN_BUF_MEM_BLOCK_SIZE];
	QCONFIRM_RET_FALSE(pBlock);
	m_vecPackageBuf.push_back(pBlock);
	return TRUE;
}

LPBYTE KConnnectLocalMgr::NewPackage(UINT uDataLen)
{
	QCONFIRM_RET_NULL(m_pCurBlockWritepos && uDataLen <= 65535);
	LPBYTE pBuf = NULL;
	// �����л�������С����
	if (m_uCurBlockRestSize < uDataLen + sizeof(WORD))
	{
		// �������һ��WORD��С����0
		if (m_uCurBlockRestSize >= sizeof(WORD))
			*(LPWORD)m_pCurBlockWritepos = 0;
		if (++m_nCurblock >= (INT)m_vecPackageBuf.size())
			NewPackageBufBlock(); // ������һ��Block
		m_pCurBlockWritepos = m_vecPackageBuf.back();
		m_uCurBlockRestSize = KD_LOCAL_CONN_BUF_MEM_BLOCK_SIZE;

	}
	*(LPWORD)m_pCurBlockWritepos = uDataLen;
	m_pCurBlockWritepos += sizeof(WORD) + uDataLen;
	m_uCurBlockRestSize -= sizeof(WORD) + uDataLen;
	return m_pCurBlockWritepos - uDataLen;
}

BOOL KConnnectLocalMgr::ProcessPackage()
{
	for (INT i = 0; i <= m_nCurblock; i++)
	{
		LPBYTE pBuf = m_vecPackageBuf[i];
		LPBYTE pEndBuf = pBuf + KD_LOCAL_CONN_BUF_MEM_BLOCK_SIZE;
		if (i == m_nCurblock)	// ��������һ��Block����m_pCurBlockWriteposΪ��ֹ
			pEndBuf = m_pCurBlockWritepos;
		while(pEndBuf - pBuf >= sizeof(WORD))	// sizeof(WORD)�������һ������С��λ��
		{
			WORD wSize = *(LPWORD)pBuf;
			if (wSize <= 2)
				break;	// �����ĺ�����Ч����������һ��Block
			pBuf += sizeof(WORD);
			BYTE byConnectId = *pBuf++;
			BYTE byInterfaceTypeId = *pBuf++;
			wSize -= 2;	// �����ֽ�����ConnectorModuleId��InterfaceTypeId
			KLoader::Inst()->ProcessInterfaceData(byConnectId, byInterfaceTypeId, pBuf, wSize);
			pBuf += wSize;
		}
	}
	m_pCurBlockWritepos = m_vecPackageBuf.front();
	m_uCurBlockRestSize = KD_LOCAL_CONN_BUF_MEM_BLOCK_SIZE;
	m_nCurblock = 0;
	return TRUE;
}

KConnnectLocalMgr* KConnnectLocalMgr::Inst()
{
	static KConnnectLocalMgr sMgr;
	return &sMgr;
}
// -------------------------------------------------------------------------
