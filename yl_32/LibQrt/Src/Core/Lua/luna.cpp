#include "CorePrivate.h"

#ifdef SCRIPT_BINDK

#include "luna.h"
extern "C"
{
	#include "lua.h"
	#include "lualib.h"
	#include "lauxlib.h"
};


#define LUNA_ERROR_KEY(msg, key)	QLuaScript::OutPutErrMsgF(L, "[LUNA]<%s>:%s Error "msg"\n", pszClassName, key)	//, ASSERT(FALSE)
#define LUNA_ERROR(msg)				QLuaScript::OutPutErrMsgF(L, "[LUNA]<%s> Error "msg"\n", pszClassName)			//, ASSERT(FALSE)

#define KD_STR_TMPTABLE "_tbTempTable"

BOOL QLunaBase::GetScriptTempTable(lua_State* L, LPCSTR pszClassName, int nIndex)
{
	int nTopIndex	= lua_gettop(L);
	lua_getglobal(L, pszClassName);
	if (lua_type(L, nTopIndex + 1) != LUA_TTABLE)
	{
		lua_settop(L, nTopIndex);
		return FALSE;
	}

	lua_getfield(L, nTopIndex + 1, KD_STR_TMPTABLE);
	if (lua_type(L, nTopIndex + 2) != LUA_TTABLE)
	{
		lua_pop(L, 1);
		lua_newtable(L);
		lua_pushvalue(L, nTopIndex + 2);
		lua_setfield(L, nTopIndex + 1, KD_STR_TMPTABLE);
	}

	lua_remove(L, nTopIndex + 1);

	lua_rawgeti(L, nTopIndex + 1, nIndex);
	if (lua_type(L, nTopIndex + 2) != LUA_TTABLE)
	{
		lua_pop(L, 1);
		lua_newtable(L);
		lua_pushvalue(L, nTopIndex + 2);
		lua_rawseti(L, nTopIndex + 1, nIndex);
	}

	lua_remove(L, nTopIndex + 1);

	ASSERT(lua_gettop(L) == nTopIndex + 1);	// TODO: FanZai ��ջ��飬�ȶ������ȥ��

	return TRUE;
}

BOOL QLunaBase::ClearScriptTempTable(lua_State* L, LPCSTR pszClassName, int nIndex)
{
	int nTopIndex	= lua_gettop(L);
	lua_getglobal(L, pszClassName);
	if (lua_type(L, nTopIndex + 1) != LUA_TTABLE)
	{
		lua_settop(L, nTopIndex);
		return FALSE;
	}

	lua_getfield(L, nTopIndex + 1, KD_STR_TMPTABLE);
	if (lua_type(L, nTopIndex + 2) != LUA_TTABLE)
	{
		lua_settop(L, nTopIndex);
		return TRUE;
	}

	lua_pushnil(L);
	lua_rawseti(L, nTopIndex + 2, nIndex);

	lua_settop(L, nTopIndex);

	return TRUE;
}


BOOL QLunaBase::_RegisterExtFun(
								lua_State* L,
								LPCSTR pszClassName,
								LPCSTR pszFuncName,
								ExtFunc pExtFunc,
								QLuaData *pLuaData,
								LPCSTR *ppszDeriveClasses /* = NULL */, INT nDeriveClassCount /* = 0 */)
{
	if (!pLuaData)
	{
		_ASSERT(FALSE);
		return TRUE;
	}

	int nTopIndex	= lua_gettop(L);

	lua_pushstring(L, pszClassName);
	lua_rawget(L, LUA_GLOBALSINDEX);

	lua_pushlightuserdata(L, pLuaData);
	lua_setfield(L, -2, pLuaData->pszName);

	// �������������˲���
	for (INT i = 0; i < nDeriveClassCount; ++i)
	{
		lua_pushstring(L, ppszDeriveClasses[i]); // push
		lua_rawget(L, LUA_GLOBALSINDEX); // push
		// û�ҵ�Ҫע�����table����_KLuaPlayer
		if (lua_isnil(L, -1))
		{
			ASSERT(FALSE);
			continue;
		}
		lua_pushstring(L, pLuaData->pszName);// push
		lua_rawget(L, -2);

		// ��������Ѿ��������Ա�˾Ͳ���ע����
		if (!lua_isnil(L, -1))
			continue;

		lua_pushlightuserdata(L, pLuaData); // push
		lua_setfield(L, -3, pLuaData->pszName);
	}

	lua_settop(L, nTopIndex);
	return TRUE;
}


const QLunaBase::QLuaData* QLunaBase::GetLuaData(lua_State* L, int nIndex)
{
	if (lua_type(L, nIndex) != LUA_TLIGHTUSERDATA)
		return NULL;

	return (const QLuaData*)lua_touserdata(L, nIndex);
}

QLunaBase* QLunaBase::GetCObj(lua_State* L, int nIndex)
{
	if (lua_type(L, nIndex) != LUA_TUSERDATA)
		return NULL;

	_LuaLunaData* pUserData	= (_LuaLunaData*)lua_touserdata(L, nIndex);
	switch(pUserData->byType)
	{
	case emKLUNADATA_TYPE_POINTER:
		return (QLunaBase*)pUserData->pData;
	case emKLUNADATA_TYPE_COPY:
		return (QLunaBase*)&pUserData->pData;
	default:
		ASSERT(FALSE);	// ���ش���
		return NULL;
	}
}

BOOL QLunaBase::_PushCObj(lua_State* L, LPCSTR pszClassName, int nSize) const
{
	_LuaLunaData* pUserData	= NULL;
	if (nSize > 0)	// ���θ���
	{
		pUserData	= (_LuaLunaData*)lua_newuserdata(L, sizeof(_LuaLunaData) - sizeof(pUserData->pData) + nSize);
		pUserData->byType	= emKLUNADATA_TYPE_COPY;
		memcpy(&pUserData->pData, this, nSize);
	}
	else
	{
		pUserData	= (_LuaLunaData*)lua_newuserdata(L, sizeof(_LuaLunaData));
		pUserData->byType	= emKLUNADATA_TYPE_POINTER;
		pUserData->pData	= this;
	}

	luaL_getmetatable(L, pszClassName);
	if (lua_isnil(L, -1))	// ����δע��
	{
		QLuaScript::OutPutErrMsgF(L, "[LUNA]<%s> Not Registered!!!\n", pszClassName);
		//ASSERT(FALSE);
		lua_pop(L, 2);
		return FALSE;
	}
	lua_setmetatable(L, -2);

	return TRUE;
}


BOOL QLunaBase::_Register(
						  lua_State* L,
						  LPCSTR pszClassName,
						  QLuaData* pLuaData,
						  lua_CFunction pFunTos,
						  lua_CFunction pFunIdx,
						  lua_CFunction pFunNew,
						  lua_CFunction pFunInf,
						  QLuaData **ppExtLuaData /* = NULL */, INT nExtLuaDataCount /* = 0 */ )
{
	int nTopIndex	= lua_gettop(L);

	//----------
	//�����������ݱ���ҪΪ������Lua�ڽ����ַ���hash���ƣ�����Ҳ�����Լ�ʵ��
	//����Key : �����������ƣ�Value : QLuaDataָ��
	lua_newtable(L);

	lua_pushcfunction(L, pFunInf);
	lua_setfield(L, -2, "GetDataInfo");

	if (ppExtLuaData && nExtLuaDataCount > 0)
	{
		for (INT i = 0; i < nExtLuaDataCount; ++i)
		{
			_ASSERT(ppExtLuaData[i]);
			lua_pushlightuserdata(L, ppExtLuaData[i]);
			lua_setfield(L, -2, ppExtLuaData[i]->pszName);
		}
	}

	//����м���������Ҫע�������
	for (; pLuaData->pszName; pLuaData++) 
	{
		/* edited by Snaily: shouldn't it be const RegType *l ... ? */
		lua_pushlightuserdata(L, pLuaData);
		lua_setfield(L, -2, pLuaData->pszName);
	}

	//���������ݱ����ȫ�ֱ��У��Ա��Ժ����
	lua_pushstring(L, pszClassName);
	lua_pushvalue(L, -2);
	lua_rawset(L, LUA_GLOBALSINDEX);

	//----------
	//����Metatable���Ա�������صĲ�����
	if (luaL_newmetatable(L, pszClassName) != 1)
	{
		LUNA_ERROR("already registered!");
		lua_settop(L, nTopIndex);
		return FALSE;
	}

	// hide metatable from Lua getmetatable()
	lua_pushvalue(L, -2);
	lua_setfield(L, -2, "__metatable");

	//����GetTable����
	lua_pushcfunction(L, pFunIdx);
	lua_setfield(L, -2, "__index");

	//����SetTable����
	lua_pushcfunction(L, pFunNew);
	lua_setfield(L, -2, "__newindex");

	//�����ַ���ת������
	lua_pushcfunction(L, pFunTos);
	lua_setfield(L, -2, "__tostring");

	lua_settop(L, nTopIndex);

	return TRUE;
}

int QLunaBase::_LuaGetDataInfo(lua_State* L, LPCSTR pszClassName)
{
	LPCSTR pszKey	= NULL;
	const QLuaData* pLuaData	= NULL;

	CHECK_REPORT(lua_type(L, 1) == LUA_TSTRING);
	pszKey	= lua_tostring(L, 1);
	CHECK_REPORT(pszKey);

	lua_getglobal(L, pszClassName);
	CHECK_REPORT(lua_type(L, -1) == LUA_TTABLE);

	lua_getfield(L, -1, pszKey);
	pLuaData = GetLuaData(L, -1);
	CHECK_REPORT(pLuaData);

	lua_createtable(L, 0, 5);

	lua_pushstring(L, pszClassName);
	lua_setfield(L, -2, "Owner");

	lua_pushstring(L, pLuaData->pszName);
	lua_setfield(L, -2, "Name");

	lua_pushstring(L, pLuaData->pszDesc);
	lua_setfield(L, -2, "Desc");

	switch(pLuaData->eType)
	{
	case ldtInteger:
		lua_pushliteral(L, "Integer");
		break;
	case ldtString:
		lua_pushliteral(L, "String");
		break;
	case ldtDword:
		lua_pushliteral(L, "Dword");
		break;
	case ldtEnum:
		lua_pushliteral(L, "Enum");
		break;
	case ldtBool:
		lua_pushliteral(L, "Bool");
		break;
	case ldtFunc:
		lua_pushliteral(L, "Func");
		break;
	case ldtClass:
		lua_pushliteral(L, "Class");
		break;
	case ldtExtFun:
		lua_pushliteral(L, "ExtClass");
		break;
	default:
		lua_pushfstring(L, "Unknown:%d", pLuaData->eType);
		break;
	}
	lua_setfield(L, -2, "Type");

	if (pLuaData->eType == ldtFunc)
	{
		lua_pushstring(L, pLuaData->func.pszParam);
		lua_setfield(L, -2, "Param");
		lua_pushstring(L, pLuaData->func.pszParamDesc);
		lua_setfield(L, -2, "ParamDesc");
		lua_pushstring(L, pLuaData->func.pszReturnDesc);
		lua_setfield(L, -2, "Param");
	}
	else if (pLuaData->eType != ldtClass)
	{
		if (pLuaData->data.fnSet)
			lua_pushliteral(L, "Read&Write");
		else if (pLuaData->data.fnGet)
			lua_pushliteral(L, "ReadOnly");
		else
			lua_pushliteral(L, "None");
		lua_setfield(L, -2, "Access");
	}

	return 1;

EXIT0:
	return 0;
}

class KLuaStateSaverEx
{
private:
	lua_State *m_L;
	QLuaScript* m_pKJxScript;
public:
	KLuaStateSaverEx():m_pKJxScript(NULL){}
	void Init(QLuaScript* pJxScript, lua_State *pNewL)
	{
		m_L = pJxScript->GetLuaState();
		m_pKJxScript = pJxScript;
		((KJxScriptEx*)m_pKJxScript)->m_pLuaState = pNewL;
	}
	~KLuaStateSaverEx()
	{
		if (m_pKJxScript)
			((KJxScriptEx*)m_pKJxScript)->m_pLuaState = m_L;
	}
	class KJxScriptEx : public QLuaScript
	{
		friend class KLuaStateSaverEx;
	};
};

//�������������������Խ�static�ĵ��ã�ת������thisָ������Ա��������
int QLunaBase::_LuaDispatcher(lua_State *L, LPCSTR pszClassName)
{
	QLunaBase* pObj = NULL;
	const QLuaData* pLuaData = NULL;
	QLuaScript* psc = NULL;
	KLuaStateSaverEx _saver;

	CHECK_REPORT(L);

	CHECK_REPORT(lua_checkstack(L, KD_N_BASE_CALL_STACK));

	// Ϊ�����Ч�ʣ������Obj��LightUserData��������GetCObj()
	if (lua_type(L, lua_upvalueindex(1)) == LUA_TLIGHTUSERDATA)
		pObj	= (QLunaBase*)lua_touserdata(L, lua_upvalueindex(1));
	if (!pObj)
	{
		LUNA_ERROR("self not found!");
		return 0;
	}

	pLuaData = GetLuaData(L, lua_upvalueindex(2));
	if (!pLuaData)
	{
		LUNA_ERROR("index not found!");
		return 0;
	}

	psc	= QLuaScript::GetThis(L);
	CHECK_REPORT(psc);

	_saver.Init(psc, L); //by dzh:�����ֳ���������ָ��ֳ�
	
	if (pLuaData->func.pszParam)
	{
		if (!psc->CheckList(1, pLuaData->func.pszParam))
		{
			LUNA_ERROR_KEY("param!", pLuaData->pszName);
			return FALSE;
		}
	}

	return (pObj->*(LuaFunc)(pLuaData->func.fnLuaFunc))(*psc);

EXIT0:
	return 0;
}

//�����ַ���ת������
int QLunaBase::_LuaTostring (lua_State* L, LPCSTR pszClassName)
{
	const QLunaBase* pObj = GetCObj(L, 1);
	lua_pushfstring(L, "Ptr:%p ClassName:%s", pObj, pszClassName);

	return 1;
}

//����GetTable����
int QLunaBase::_LuaIndex(lua_State* L, LPCSTR pszClassName, lua_CFunction pFunDis)
{
	//��ȡSelfָ�������
	QLunaBase* pObj = GetCObj(L, 1);
	if (!pObj)
	{
		LUNA_ERROR("self not found");
		return 0;
	}

	//��ȡKey�ַ���
	LPCSTR pszKey = lua_tostring(L, 2);
	if (!pszKey)
	{
		LUNA_ERROR("key is null.");
		return 0;
	}

	//���ҵ������ݱ�
	lua_getglobal(L, pszClassName);
	//�ڵ������ݱ��в���Key��Ӧ��QLuaDataָ��
	lua_pushvalue(L, 2);
	lua_gettable(L, 3);

	if (lua_isfunction(L, -1))	// �ǽű���װ����
	{
		lua_pushvalue(L, 1);
		if (lua_setupvalue(L, -2, 1))	// ����UpValueΪself
			return 1;	// ����closure
		LUNA_ERROR_KEY("function upvalue missing.", pszKey);
		return 0;
	}

	const QLuaData* pLuaData = GetLuaData(L, -1);
	if (!pLuaData)
	{
		LUNA_ERROR_KEY("key not found!", pszKey);
		return 0;
	}

	if (pLuaData->eType == ldtFunc)
	{
		lua_pushlightuserdata(L, (void*)pObj);	// Ϊ�����Ч�ʣ������Obj����LightUserData
		lua_pushlightuserdata(L, (void*)pLuaData);
		lua_pushcclosure(L, pFunDis, 2);
		return 1;
	}

	if (pLuaData->eType == ldtExtFun)
	{
		KLuaStateSaverEx _saver;
		QLuaScript* psc = QLuaScript::GetThis(L);
		if (!psc)
		{
			ASSERT(FALSE);
			return 0;
		}
		_saver.Init(psc, L); //by dzh:�����ֳ���������ָ��ֳ�
		INT nRet = (*(ExtFunc)(pLuaData->extFunc.fnExtFunc))(*psc, pObj);
		return nRet;
	}

	if (!pLuaData->data.fnGet)
	{
		LUNA_ERROR_KEY("can't read!", pszKey);
		return 0;		
	}

	switch (pLuaData->eType)
	{
	case ldtInteger:
		{
			int nResult = (pObj->*(GetIntFunc)(pLuaData->data.fnGet))();
			lua_pushnumber(L, nResult);
			return 1;
		}
	case ldtString:
		{
			LPCSTR pszResult = (pObj->*(GetStrFunc)(pLuaData->data.fnGet))();
			lua_pushstring(L, pszResult);
			return 1;
		}
	case ldtEnum:
		{
			int nResult = (pObj->*(GetIntFunc)(pLuaData->data.fnGet))();
			lua_pushnumber(L, nResult);
			return 1;
		}
	case ldtDword:
		{
			DWORD dwResult = (pObj->*(GetDwordFunc)(pLuaData->data.fnGet))();
			lua_pushnumber(L, dwResult);
			return 1;
		}
	case ldtBool:
		{
			int bResult = (pObj->*(GetIntFunc)(pLuaData->data.fnGet))();
			lua_pushboolean(L, bResult);
			return 1;
		}
	case ldtClass:
		{
			QLunaBase* pLuna = NULL;
			pLuna = dynamic_cast<QLunaBase*>((pObj->*(GetClassFunc)(pLuaData->data.fnGet))());
			if (!pLuna)
			{
				ASSERT(FALSE);
				return 0;
			}
			pLuna->PushCObj(L);
			return 1;
		}
	default:
		{
			ASSERT(FALSE);
			return 0;
		}
	}
}

//����SetTable����
int QLunaBase::_LuaNewIndex(lua_State* L, LPCSTR pszClassName)
{
	//��ȡKey�ַ���
	LPCSTR pszKey = lua_tostring(L, 2);
	if (!pszKey)
	{
		LUNA_ERROR("key is null.");
		return 0;
	}

	//���ҵ������ݱ�
	lua_getglobal(L, pszClassName);
	//�ڵ������ݱ��в���Key��Ӧ��QLuaDataָ��
	lua_pushvalue(L, 2);
	lua_gettable(L, 4);
	const QLuaData* pLuaData = GetLuaData(L, -1);
	if (!pLuaData)
	{
		LUNA_ERROR_KEY("key not found!", pszKey);
		return 0;
	}

	if (pLuaData->eType == ldtFunc || !pLuaData->data.fnSet)
	{
		LUNA_ERROR_KEY("read only!", pszKey);
		return 0;
	}

	//��ȡSelfָ�������
	QLunaBase* pObj = GetCObj(L, 1);
	if (!pObj)
	{
		LUNA_ERROR_KEY("self not found", pszKey);
		return 0;
	}

	switch (pLuaData->eType)
	{
	case ldtInteger:
		{
			int nValue = lua_tointeger(L, 3);
			(pObj->*(SetIntFunc)(pLuaData->data.fnSet))(nValue);
			return 0;
		}
	case ldtString:
		{
			LPCSTR pszValue = lua_tostring(L, 3);
			(pObj->*(SetStrFunc)(pLuaData->data.fnSet))(pszValue);
			return 0;
		}
	case ldtEnum:
		{
			int nValue = lua_tointeger(L, 3);
			(pObj->*(SetIntFunc)(pLuaData->data.fnSet))(nValue);
			return 0;
		}
	case ldtBool:
		{
			int nValue = lua_toboolean(L, 3);
			(pObj->*(SetIntFunc)(pLuaData->data.fnSet))(nValue);
			return 0;
		}
	case ldtDword:
		{
			DWORD dwValue = (DWORD)lua_tointeger(L, 3);
			(pObj->*(SetDwordFunc)(pLuaData->data.fnSet))(dwValue);
			return 0;
		}
	default:
		{
			ASSERT(FALSE);
			return 0;
		}
	}
}

#endif	// SCRIPT_BINDK
