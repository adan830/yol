#pragma once

class KCharacter;

class LuaPlayerAwardLobby : public QLunaBase
{
private:
	KCharacter& m_rcCharacter;

public:
	explicit LuaPlayerAwardLobby(KCharacter& rcCharacter) : m_rcCharacter(rcCharacter){}
	~LuaPlayerAwardLobby(){}

	static INT Register2Player(QLuaScript& sc, QLunaBase* pLunaObj);

	DECLARE_LUA_CLASS(LuaPlayerAwardLobby);

	INT LuaDoFinishActivity(QLuaScript& sc);

	INT LuaDoFinishRankActivity(QLuaScript& sc);

	INT LuaDoSignIn(QLuaScript& sc);

	//ǮׯͶ���������(�����ã���ʱд������)
	INT LuaDoGetBankIncomeTest(QLuaScript& sc);
};