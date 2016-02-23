
#pragma once

#include "onlinegameworld/kmodulebase.h"
#include "onlinegameworld/ikgamecentersvc.h"
// -------------------------------------------------------------------------
class KGcModuleBase : public KModuleBase
{
public:
	KGcModuleBase(CHAR cModuleId, BYTE byGcModuleId);
	~KGcModuleBase();
	// ����gamecenterЭ��
	virtual BOOL ProcessGcProtocol(LPCBYTE pbData, UINT uDataLen) { return TRUE; }
#ifdef GAME_SERVER
	IKGcSvcClient* GetGcSvcProvider() { return m_piGcSvcClient; }
#endif
protected:
	virtual BYTE GetGcModuleId() { return m_byGcModuleId; }
protected:
	BYTE m_byGcModuleId;
#ifdef GAME_SERVER
	IKGcSvcClient* m_piGcSvcClient;
#endif // GAME_SERVER
};


