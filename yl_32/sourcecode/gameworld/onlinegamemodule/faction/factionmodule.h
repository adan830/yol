/* -------------------------------------------------------------------------
//	�ļ���		��	factionmanager.h
//	������		��	zhangzhixiong
//	����ʱ��	��	2012-5-25 
//	��������	��	
//
// -----------------------------------------------------------------------*/
#ifndef factionmodule_h__
#define factionmodule_h__

#include "onlinegameworld/kmodulebase.h"

class KPlayer;
struct FACTION_PLAYER_SETTING;
class FactionModule : public KModuleBase
{
public:
	FactionModule();
	virtual ~FactionModule();

public:	
	BOOL OnInit();

	BOOL OnUnInit();

	BOOL Breath();

	BOOL ProcessProtocol(INT nPlayerIndex, LPCBYTE pbData, UINT uDataLen);

	BOOL DoSyncPlayerSetting(KPlayer& rPlayer, CONST FACTION_PLAYER_SETTING& cSetting);

	BOOL InitProtocol();

private:
	BOOL ApplyPlayerSetting(LPCBYTE pData, INT nDataLen, KPlayer* pPlayer);
};

inline FactionModule* GetFactionModule()
{
	static FactionModule s_FactionModule;
	return &s_FactionModule;
}

#endif // factionmodule_h__