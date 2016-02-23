
#pragma once

// -------------------------------------------------------------------------
class KPlayerFindPath;

class KLuaPlayerFindPath : public QLunaBase
{
public:
	explicit KLuaPlayerFindPath(KPlayerFindPath* pPlayerFindPath) : m_pPlayerFindPath(pPlayerFindPath)
	{}
	~KLuaPlayerFindPath() {}

	static INT RegisterToPlayer(QLuaScript& sc, QLunaBase* pLunaObj);

	// �ű��ӿڶ���
	DECLARE_LUA_CLASS(KLuaPlayerFindPath);

	INT LuaStartAutoPath(QLuaScript& sc);
	INT LuaGetNavPath(QLuaScript& sc);

private:
	KPlayerFindPath* m_pPlayerFindPath;
};


