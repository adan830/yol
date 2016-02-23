/* -------------------------------------------------------------------------
//	�ļ���		��	qshopmodule.h
//	������		��	zhangzhixiong
//	����ʱ��	��	2012-10-8 
//	��������	��
//
// -----------------------------------------------------------------------*/
#ifndef __KPURSEMODULE_H__
#define __KPURSEMODULE_H__

// -------------------------------------------------------------------------
#include "onlinegameworld/kmodulebase.h"

class QShopModule : public KModuleBase
{
public:
	QShopModule();
	virtual ~QShopModule() {}

public:
	BOOL OnInit();

#ifdef GAME_SERVER
	BOOL ProcessProtocol(INT nPlayerIndex, LPCBYTE pbData, UINT uDataLen);
#endif
#ifdef KD_OP_GAME_CLIENT
	BOOL ProcessProtocol(LPCBYTE pbData, UINT uDataLen);
#endif
	BOOL InitProtocol();
};

extern QShopModule g_cShopModule;

//inline QShopModule& GetShopModule()
//{
//	static QShopModule s_m;
//	return s_m;
//}

// -------------------------------------------------------------------------

#endif /* __KPURSEMODULE_H__ */
