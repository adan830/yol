
#pragma once

// -------------------------------------------------------------------------
#include "onlinegameworld/kmodulebase.h"

class KPurseModule : public KModuleBase
{
public:
	KPurseModule();
	virtual ~KPurseModule() {}

public:
	BOOL OnInit();

#ifdef GAME_SERVER
	BOOL ProcessProtocol(INT nPlayerIndex, LPCBYTE pbData, UINT uDataLen);
#endif
#ifdef GAME_CLIENT
	BOOL ProcessProtocol(LPCBYTE pbData, UINT uDataLen);
#endif
	BOOL InitProtocol();

	INT GetMaxCarryCurrency() { return m_nPlayerMaxCarryCurrency; }

private:
	INT m_nPlayerMaxCarryCurrency;		//Ǯ�������������
};

inline KPurseModule& GetPurseModule()
{
	static KPurseModule s_m;
	return s_m;
}

// -------------------------------------------------------------------------
