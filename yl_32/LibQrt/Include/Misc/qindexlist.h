
#pragma once

#include <map>
#include "Core/QLinkArray.h"

class QIndexList
{
public:
	QIndexList()						{ Release(); }
	~QIndexList()						{ Release(); }

	BOOL Init(INT nMax);
	VOID Release(VOID);
	BOOL Use(INT nIndex);
	BOOL Free(INT nIndex);
	INT  FindFree(VOID) CONST			{ return m_cFreeIdx.GetNext(0); }
	INT  FindNext(INT nIndex) CONST		{ return m_cUseIdx.GetNext(nIndex); }
	INT  GetCount(VOID)					{ return m_cUseIdx.GetCount(); }
	INT  GetMax(VOID) CONST				{ return m_nMax; }

protected:
	INT				m_nMax;				// �����������
	QLinkArray		m_cFreeIdx;			// ���ñ�
	QLinkArray		m_cUseIdx;			// ���ñ�
};
