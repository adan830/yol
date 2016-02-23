/* -------------------------------------------------------------------------
//	�ļ���		��	kmempipesys.cpp
//	������		��	luobaohang
//	����ʱ��	��	2010/4/29 16:40:13
//	��������	��
//	�����ڴ�ģ��ʵ�ֹܵ���ʵ�ָ���ݼ��������Ľ��̼�ͨ�š�ΪGcGateway��ÿ��Loader�������Ǳ������ģ�
//	������һ�������ڴ�ܵ����ܵ����ݴ�ȡ��Ϊһ�����ڴ濽�����������������ʡ���������Loader�ܵ������ɶ�Ӧ��
//	Loader����ֱ�Ӷ�ȡ���Ǳ�������Loader�ܵ���������GcGatewayͨ��GcGateway���Socket���ӷ��͵���Ӧ������������
//	��һ��Loader�ڵ�ģ��Ҫ�������ݵ���һ��Loader��ģ��ʱ�����Ͳ���Ҫ������һ��Loader�Ƿ��ڱ�������ֻ�������
//	Loader��Ӧ�Ĺܵ�д�����ݼ��ɡ�
// -----------------------------------------------------------------------*/

#include "stdafx.h"
#include "kmempipesys.h"
#include "ksharememoryprovider.h"
#include "ksharememorypool.h"
#include "kkeysharemem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


// -------------------------------------------------------------------------
BOOL KShareMemPacker::Init( INT nMinBufferSize )
{
	m_byBufferPageType = KShareMemProvider::Inst()->GetPageTypeBySize(nMinBufferSize);
	m_ptrBuffer = KShareMemPool::Inst()->Alloc(m_byBufferPageType);
	m_pbBuffer = (LPBYTE)KShareMemProvider::Inst()->SharePtr2Pointer(m_ptrBuffer);
	// �Է��䵽�Ķ����ڴ�鳤����Ϊ��󳤶ȣ������˷�
	m_nBufSize = KShareMemProvider::Inst()->GetPageBlockSize(m_byBufferPageType);
	m_nCurWritePos = sizeof(DWORD); // ��ͷһ��DWORD������д�������ܳ��ȣ����Դ�sizeof(DWORD)��ʼ
	m_bInited = TRUE;
	return TRUE;
}

BOOL KShareMemPacker::Pack( LPVOID pvData, UINT uDataSize )
{
	if (!m_bInited)
		m_bInited = Init(KMemPipeSys::emKMAX_MIN_PACKING_BUF_SIZE);
	if ( uDataSize + sizeof(DWORD) > UINT(m_nBufSize - m_nCurWritePos))
		return FALSE;	// ����������
	*(LPDWORD)(m_pbBuffer + m_nCurWritePos) = (DWORD)uDataSize;
	m_nCurWritePos += sizeof(DWORD);
	memcpy(m_pbBuffer + m_nCurWritePos, pvData, uDataSize);
	m_nCurWritePos += uDataSize;
	return TRUE;
}

BOOL KShareMemPacker::Pack( BYTE byConnectId, BYTE byInterfaceId, LPVOID pvData, UINT uDataSize )
{
	if (!m_bInited)
		m_bInited = Init(KMemPipeSys::emKMAX_MIN_PACKING_BUF_SIZE);
	uDataSize += 2;
	if ( uDataSize + sizeof(DWORD) > UINT(m_nBufSize - m_nCurWritePos))
		return FALSE;	// ����������
	*(LPDWORD)(m_pbBuffer + m_nCurWritePos) = (DWORD)uDataSize;
	m_nCurWritePos += sizeof(DWORD);
	*(m_pbBuffer + m_nCurWritePos++) = byConnectId;
	*(m_pbBuffer + m_nCurWritePos++) = byInterfaceId;
	memcpy(m_pbBuffer + m_nCurWritePos, pvData, uDataSize - 2);
	m_nCurWritePos += uDataSize - 2;
	return TRUE;
}

KSHARE_MEM_PTR KShareMemPacker::Flush()
{
	*(LPDWORD)m_pbBuffer = m_nCurWritePos;
	KSHARE_MEM_PTR ptrRet = m_ptrBuffer;
	m_ptrBuffer = KShareMemPool::Inst()->Alloc(m_byBufferPageType);
	m_pbBuffer = (LPBYTE)KShareMemProvider::Inst()->SharePtr2Pointer(m_ptrBuffer);
	m_nCurWritePos = sizeof(DWORD); // ��ͷһ��DWORD������д�������ܳ��ȣ����Դ�sizeof(DWORD)��ʼ
	return ptrRet;
}

KShareMemPacker::KShareMemPacker()
{
	m_bInited = FALSE;
	m_nCurWritePos = 0;
}

BOOL KShareMemPacker::IsEmpty()
{
	return m_nCurWritePos > sizeof(DWORD);
}
// -------------------------------------------------------------------------

KShareMemPakPak::KShareMemPakPak()
{
	m_bInited = FALSE;
}

BOOL KShareMemPakPak::Pack( KSHARE_MEM_PTR ptr )
{
	if (!m_bInited)
		m_bInited = Init(KMemPipeSys::emKMAX_PACKING_COUNT);
	if (m_nCurPakCount >= m_nMaxPakCount)
		return FALSE;
	((KSHARE_MEM_PTR* )(m_pbBuffer + sizeof(DWORD)))[m_nCurPakCount++] = ptr;
	return TRUE;
}

KSHARE_MEM_PTR KShareMemPakPak::Flush()
{
	*(LPDWORD)m_pbBuffer = m_nCurPakCount;
	KSHARE_MEM_PTR ptrRet = m_ptrBuffer;
	m_ptrBuffer = KShareMemPool::Inst()->Alloc(m_byBufferPageType);
	m_pbBuffer = (LPBYTE)KShareMemProvider::Inst()->SharePtr2Pointer(m_ptrBuffer);
	m_nCurPakCount = 0;
	return ptrRet;
}

BOOL KShareMemPakPak::Init( INT nMaxPakCount )
{
	m_byBufferPageType = KShareMemProvider::Inst()->
		GetPageTypeBySize(nMaxPakCount * sizeof(KSHARE_MEM_PTR) + sizeof(DWORD));
	m_ptrBuffer = KShareMemPool::Inst()->Alloc(m_byBufferPageType);
	m_pbBuffer = (LPBYTE)KShareMemProvider::Inst()->SharePtr2Pointer(m_ptrBuffer);
	m_nMaxPakCount = nMaxPakCount;
	m_nCurPakCount = 0;
	m_bInited = TRUE;
	return TRUE;
}

BOOL KShareMemPakPak::IsFull()
{
	return m_nCurPakCount >= m_nMaxPakCount;
}
// -------------------------------------------------------------------------
KMemPipeSys::KMemPipeSys()
{
	// �������ƻ���KSHARE_MEM_PTR��ת��Ϊһ��ԭ����
	ASSERT(sizeof(ATOM_T) == sizeof(KSHARE_MEM_PTR));
	m_pMemPacker = NULL;
	m_pMemPakPak = NULL;
	m_bDataFlag = FALSE;
}

KMemPipeSys::~KMemPipeSys()
{
	SAFE_DELETE_ARRAY(m_pMemPacker);
	SAFE_DELETE_ARRAY(m_pMemPakPak);
}

KMemPipeSys* KMemPipeSys::Inst()
{
	static KMemPipeSys _sObject;
	return &_sObject;
}

BOOL KMemPipeSys::GwInit(INT nTotalLoaderCount)
{
	Q_Printl("Init MemPipeSys...");

	// Share Data Init
	// �����ڴ棬ע��aMemPtr��Ԫ�ظ���Ϊ nTotalLoaderCount + 1 ����Loader��GcGatewayҲռ��һ���ܵ���
	m_pShareMemData = (KSHARE_MEM_DATA* )KKeyShareMem::Inst()->CreateMem(emKSMKEY_MEMPIPESYS,
		sizeof(KSHARE_MEM_DATA) + nTotalLoaderCount * sizeof(KSHARE_MEM_PTR));
	QCONFIRM_RET_FALSE(m_pShareMemData);
	m_pShareMemData->nLoaderCount = nTotalLoaderCount;
	ZeroStruct(m_pShareMemData->aMemPtr);

	QCONFIRM_RET_FALSE(!m_pMemPacker && !m_pMemPakPak);
	m_pMemPacker = new KShareMemPacker[nTotalLoaderCount + 1];
	m_pMemPakPak = new KShareMemPakPak[nTotalLoaderCount + 1];
	return TRUE;
}

BOOL KMemPipeSys::LoaderInit()
{
	Q_Printl("Init MemPipeSys for Loader...");

	m_pShareMemData = (KSHARE_MEM_DATA* )KKeyShareMem::Inst()->GetMem(emKSMKEY_MEMPIPESYS);
	QCONFIRM_RET_FALSE(m_pShareMemData);

	QCONFIRM_RET_FALSE(!m_pMemPacker && !m_pMemPakPak);
	m_pMemPacker = new KShareMemPacker[m_pShareMemData->nLoaderCount + 1];
	m_pMemPakPak = new KShareMemPakPak[m_pShareMemData->nLoaderCount + 1];
	return TRUE;
}

BOOL KMemPipeSys::Write( INT nLoaderId, LPVOID pvData, UINT uSize )
{
	QCONFIRM_RET_FALSE(nLoaderId >= 0 && nLoaderId <= m_pShareMemData->nLoaderCount);
	QCONFIRM_RET_FALSE(uSize < emKMAX_PACKET_SIZE);
	// ĿǰLoader����Ӧ�����±꣬�Ժ��������µĹܵ���LoaderId��-1��-2�ȣ����Ӧ��ϵ���ܸı�
	INT nPos = nLoaderId;
	if (!m_pMemPacker[nPos].Pack(pvData, uSize))
	{
		// �ϰ���������������ϰ���
		if (m_pMemPakPak[nPos].IsFull())
		{
			static BYTE s_aByReported[256] = { 0 };
			if (s_aByReported[nLoaderId & 0xff] == 0)	// ��ֻ֤����һ��
			{
				Q_Error("Write Pipe Data Error��Buffer is Full��" << nLoaderId);
				s_aByReported[nLoaderId & 0xff] = 1;
			}
			return FALSE;;
		}
		QCONFIRM_RET_FALSE(m_pMemPakPak[nPos].Pack(m_pMemPacker[nPos].Flush()));
		// �ѵ�ǰ���ٷ������ú�ĺϰ�������ʱӦ���ܷ���
		QCONFIRM_RET_FALSE(m_pMemPacker[nPos].Pack(pvData, uSize));
	}
	m_bDataFlag = TRUE;
	return TRUE;
}

BOOL KMemPipeSys::WriteInterfaceData( INT nLoaderId, BYTE byConnectId,
									 BYTE byInterfaceId, LPVOID pvData, UINT uSize )
{
	QCONFIRM_RET_FALSE(nLoaderId >= 0 &&  nLoaderId <= m_pShareMemData->nLoaderCount);
	QCONFIRM_RET_FALSE(uSize + 2 < emKMAX_PACKET_SIZE);
	// ĿǰLoader����Ӧ�����±꣬�Ժ��������µĹܵ���LoaderId��-1��-2�ȣ����Ӧ��ϵ���ܸı�
	INT nPos = nLoaderId;
	if (!m_pMemPacker[nPos].Pack(pvData, uSize))
	{
		// �ϰ���������������ϰ���
		QCONFIRM_RET_FALSE(m_pMemPakPak[nPos].Pack(m_pMemPacker[nPos].Flush()));
		// �ѵ�ǰ���ٷ������ú�ĺϰ�������ʱӦ���ܷ���
		QCONFIRM_RET_FALSE(m_pMemPacker[nPos].Pack(pvData, uSize));
	}
	m_bDataFlag = TRUE;
	return TRUE;
}

INT KMemPipeSys::Read( INT nPos, KSHARE_MEM_PTR& ptr )
{
	QCONFIRM_RET((UINT)nPos <= (UINT)m_pShareMemData->nLoaderCount, -1);
	ATOM_T t = _AtomRead(m_pShareMemData->aMemPtr + nPos);
	// �����ȡ��������Ϊ��
	if (t)
	{
		ptr = *(KSHARE_MEM_PTR* )&t;
		_AtomSet(m_pShareMemData->aMemPtr + nPos, 0);
		return 1;
	}
	return 0;
}

INT KMemPipeSys::Process( INT nLoaderId, IKPacketProcess* piProcess )
{
	// ��GcGateway��Process�����ڳ�ʼ��ǰ�͵���
	if (!m_pShareMemData)
		return 0;

	QCONFIRM_RET_FALSE(nLoaderId >= 0 && nLoaderId <= m_pShareMemData->nLoaderCount);
	KSHARE_MEM_PTR ptr;
	// ĿǰLoader����Ӧ�����±꣬�Ժ��������µĹܵ���LoaderId��-1��-2�ȣ����Ӧ��ϵ���ܸı�
	INT nPos = nLoaderId;
	INT nRet = Read(nPos, ptr);
	if (nRet != 1)
		return nRet;
	LPBYTE pbBuffer = (LPBYTE)KShareMemProvider::Inst()->SharePtr2Pointer(ptr);
	QCONFIRM_RET(pbBuffer, -1);
	DWORD dwPakCount = *(LPDWORD)pbBuffer;	// ����������
	pbBuffer += sizeof(DWORD);
	for (UINT i = 0; i < dwPakCount; ++i)
	{
		KSHARE_MEM_PTR ptrPak = *(KSHARE_MEM_PTR* )pbBuffer;
		pbBuffer += sizeof(KSHARE_MEM_PTR);
		LPBYTE pbPakBuffer = (LPBYTE)KShareMemProvider::Inst()->SharePtr2Pointer(ptrPak);
		DWORD dwDataLen = *(LPDWORD)pbPakBuffer;
		LPBYTE pbPakBufEnd = pbPakBuffer + dwDataLen;
		pbPakBuffer += sizeof(DWORD);
		while (pbPakBuffer < pbPakBufEnd)
		{
			DWORD dwPacketLen = *(LPDWORD)pbPakBuffer;
			pbPakBuffer += sizeof(DWORD);
			piProcess->ProcessData(pbPakBuffer, dwPacketLen);
			pbPakBuffer += dwPacketLen;
		}
		// �����ڴ�
		KShareMemPool::Inst()->Free(ptrPak);
	}
	// �����ڴ�
	KShareMemPool::Inst()->Free(ptr);
	return nRet;
}

BOOL KMemPipeSys::Flush()
{
	// �����ݼ����أ������Ч�ʣ�ҲΪ��ֹGcGatewayδ��GwInitʱ������Ϸѭ��ִ��Flush()�����
	if (!m_bDataFlag)
		return TRUE;

	// ����ΪFALSE
	m_bDataFlag = FALSE;

	for (INT i = 0; i <= m_pShareMemData->nLoaderCount; ++i)
	{
		// �����ǰд�뻺������Ϊ��
		if (!m_pMemPacker[i].IsEmpty())
		{
			// �����ȡ�������ѿճ���
			if(!_AtomRead(m_pShareMemData->aMemPtr + i))
			{
				m_pMemPakPak[i].Pack(m_pMemPacker[i].Flush());
				KSHARE_MEM_PTR ptr = m_pMemPakPak[i].Flush();
				_AtomSet(m_pShareMemData->aMemPtr + i, *(ATOM_T* )&ptr);
			}
			else // �ϴ����ݻ��ڶ�ȡ״̬�����������ݲ��ܴ���
			{
				m_bDataFlag = TRUE;	// �¸���Ϸѭ������
			}
		}
	}

	return TRUE;
}

ATOM_T KMemPipeSys::_AtomRead( LPVOID pvData )
{
	return *(ATOM_T* )pvData;
}

VOID KMemPipeSys::_AtomSet( LPVOID pvData, ATOM_T tValue )
{
	*(ATOM_T* )pvData = tValue;
}

// -------------------------------------------------------------------------

