
#pragma once

#include "QLuaScript.h"


#include <vector>
#include <list>

//ӳ����غ궨��
#define __DECLARE_LUA_CLASS_COMMON(__CLASS_NAME__)												\
	typedef void (__CLASS_NAME__::*VoidFunc)(void);												\
	static const char s_szClassName[];															\
	static QLuaData s_LuaInterface[];															\
	static LuaDataList	s_lsExtInterface;														\
	static std::vector<LPCSTR> s_vecDeriveClasses;												\
	static int LuaDispatcher(lua_State* L)														\
	{ return _LuaDispatcher(L, s_szClassName); };												\
	static int LuaTostring(lua_State* L)														\
	{ return _LuaTostring(L, s_szClassName); };													\
	static int LuaIndex(lua_State* L)															\
	{ return _LuaIndex(L, s_szClassName, LuaDispatcher); };										\
	static int LuaNewIndex(lua_State* L)														\
	{ return _LuaNewIndex(L, s_szClassName); };													\
	static int LuaGetDataInfo(lua_State* L)														\
	{ return _LuaGetDataInfo(L, s_szClassName); };												\
	static BOOL RegisterExtFun(lua_State* L, LPCSTR pszFuncName, ExtFunc pExtFunc)				\
	{																							\
		LuaDataList::iterator it = 																\
		s_lsExtInterface.insert(																\
			s_lsExtInterface.end(), QLuaData(pszFuncName, "", pExtFunc));						\
		return _RegisterExtFun(L, s_szClassName, pszFuncName, pExtFunc,	&(*it),					\
			s_vecDeriveClasses.size() > 0 ? &s_vecDeriveClasses[0] : NULL,						\
			(INT)s_vecDeriveClasses.size()); };


//����������Ҫ�����������ߺ�����Luaʹ��
#define __DECLARE_LUA_CLASS(__CLASS_NAME__)														\
	__DECLARE_LUA_CLASS_COMMON(__CLASS_NAME__);													\
	static VOID RegisterBaseDataList() {														\
		static int s_nRegisterBase = FALSE;														\
		if (!s_nRegisterBase) {																	\
			for (QLuaData* pLuaData = s_LuaInterface; pLuaData->pszName; pLuaData++) {			\
				s_lsExtInterface.push_back(*pLuaData);											\
			}																					\
			s_nRegisterBase = TRUE;																\
		}																						\
	}																							\
	static void RegisterDeriveClass(LPCSTR pszClassName) {										\
		s_vecDeriveClasses.push_back(pszClassName);												\
	}																							\
	static BOOL Register(QLuaScript& sc){														\
		return _Register(sc.GetLuaState(), s_szClassName,										\
			s_LuaInterface, LuaTostring, LuaIndex,												\
			LuaNewIndex, LuaGetDataInfo);														\
	}																							\



// �������������
#define __DECLARE_LUA_DRIVATE_CLASS(__CLASS_NAME__, __BASE_CLASS_NAME__)						\
	__DECLARE_LUA_CLASS_COMMON(__CLASS_NAME__);													\
	static VOID RegisterBaseDataList() {														\
		static int s_nRegisterBase = FALSE;														\
		if (!s_nRegisterBase) {																	\
			__BASE_CLASS_NAME__::RegisterBaseDataList();										\
			for (QLuaData* pLuaData = __BASE_CLASS_NAME__::s_LuaInterface; pLuaData->pszName; pLuaData++) {			\
				s_lsExtInterface.push_back(*pLuaData);											\
			}																					\
			s_nRegisterBase = TRUE;																\
		}																						\
	}																							\
	static void RegisterDeriveClass(LPCSTR pszClassName) {										\
		s_vecDeriveClasses.push_back(pszClassName);												\
		__BASE_CLASS_NAME__::RegisterDeriveClass(pszClassName);									\
	}																							\
	static BOOL Register(QLuaScript& sc)	{														\
		static BOOL s_bRegisterDerive = FALSE;													\
		if (!s_bRegisterDerive) {																\
			RegisterDeriveClass(s_szClassName);													\
			RegisterBaseDataList();																\
			std::vector<QLunaBase::QLuaData *> tmp;tmp.reserve(s_lsExtInterface.size());		\
			for (LuaDataList::iterator it = s_lsExtInterface.begin();							\
					it != s_lsExtInterface.end(); ++it)											\
						tmp.push_back(&(*it));													\
			_Register(sc.GetLuaState(), s_szClassName,											\
				s_LuaInterface, LuaTostring, LuaIndex,											\
				LuaNewIndex, LuaGetDataInfo,													\
				tmp.size() > 0 ? &tmp[0] : NULL,												\
				(INT)tmp.size());																	\
			s_bRegisterDerive = TRUE;															\
		}																						\
		return FALSE;																			\
	}																							\



#define DECLARE_LUA_CLASS(__CLASS_NAME__)														\
	__DECLARE_LUA_CLASS(__CLASS_NAME__);														\
	BOOL PushCObj(lua_State* L) const															\
	{ return _PushCObj(L, s_szClassName); };													\


#define DECLARE_LUA_DRIVATE_CLASS(__CLASS_NAME__, __BASE_CLASS_NAME__)							\
	__DECLARE_LUA_DRIVATE_CLASS(__CLASS_NAME__, __BASE_CLASS_NAME__);							\
	BOOL PushCObj(lua_State* L) const															\
	{ return _PushCObj(L, s_szClassName); };													\


#define DECLARE_LUA_CLASS_COPYMODE(__CLASS_NAME__)												\
	__DECLARE_LUA_CLASS(__CLASS_NAME__);														\
	BOOL PushCObj(lua_State* L) const															\
	{ return _PushCObj(L, s_szClassName, sizeof(__CLASS_NAME__)); };							\


#define DECLARE_LUA_DRIVATE_CLASS_COPYMODE(__CLASS_NAME__, __BASE_CLASS_NAME__)					\
	__DECLARE_LUA_DRIVATE_CLASS(__CLASS_NAME__, __BASE_CLASS_NAME__);							\
	BOOL PushCObj(lua_State* L) const															\
	{ return _PushCObj(L, s_szClassName, sizeof(__CLASS_NAME__)); };							\


/************************************************************************/

//�������������α���
#define DECLARE_LUA_STRUCT_INTEGER(__VAR_NAME__, __REAL_NAME__)					\
	int get##__VAR_NAME__(void) const {return __REAL_NAME__;};					\
	void set##__VAR_NAME__(int nValue)	{__REAL_NAME__ = nValue;}

//�����������޷������α���
#define DECLARE_LUA_STRUCT_DWORD(__VAR_NAME__, __REAL_NAME__)					\
	DWORD get##__VAR_NAME__(void) const {return __REAL_NAME__;};				\
	void set##__VAR_NAME__(DWORD dwValue)	{__REAL_NAME__ = dwValue;}

//�����������ַ���
#define DECLARE_LUA_STRUCT_STRING(__VAR_NAME__, __STR_LEN__, __REAL_NAME__)		\
	LPCSTR get##__VAR_NAME__(void) const {return __REAL_NAME__;};				\
	void set##__VAR_NAME__(LPCSTR pszValue)										\
	{strncpy((__REAL_NAME__), pszValue, __STR_LEN__);							\
	(__REAL_NAME__)[(__STR_LEN__) - 1] = 0;}

//����������ö���ͱ���
#define DECLARE_LUA_STRUCT_ENUM(__VAR_NAME__, __REAL_NAME__)					\
	int get##__VAR_NAME__(void) const {return (int)(__REAL_NAME__);};			\
	void set##__VAR_NAME__(int nValue)	{*(int*)&(__REAL_NAME__) = nValue;	}	// TODO: ��������ȫ by FanZai

//���������ò����ͱ���
#define DECLARE_LUA_STRUCT_BOOL(__VAR_NAME__, __REAL_NAME__)					\
	int get##__VAR_NAME__(void) const {return (int)(__REAL_NAME__);};			\
	void set##__VAR_NAME__(int nValue)	{*(int*)&(__REAL_NAME__) = nValue;}		// TODO: ��������ȫ by FanZai

/************************************************************************/

#define DECLARE_LUA_INTEGER(__VAR_NAME__)	DECLARE_LUA_STRUCT_INTEGER(__VAR_NAME__, m_n##__VAR_NAME__)
#define DECLARE_LUA_DWORD(__VAR_NAME__)		DECLARE_LUA_STRUCT_DWORD(__VAR_NAME__, m_dw##__VAR_NAME__)
#define DECLARE_LUA_STRING(__VAR_NAME__)	DECLARE_LUA_STRUCT_STRING(__VAR_NAME__, sizeof(m_sz##__VAR_NAME__), m_sz##__VAR_NAME__)
#define DECLARE_LUA_ENUM(__VAR_NAME__)		DECLARE_LUA_STRUCT_ENUM(__VAR_NAME__, m_e##__VAR_NAME__)
#define DECLARE_LUA_BOOL(__VAR_NAME__)		DECLARE_LUA_STRUCT_BOOL(__VAR_NAME__, m_dw##__VAR_NAME__)

/************************************************************************/

//��ʼ���嵼����
#define DEFINE_LUA_CLASS_BEGIN(__CLASS_NAME__)									\
	typedef __CLASS_NAME__	__TClass;											\
	const char __TClass::s_szClassName[] = "_"#__CLASS_NAME__;					\
	LuaDataList __TClass::s_lsExtInterface;										\
		std::vector<LPCSTR> __TClass::s_vecDeriveClasses;						\
	QLunaBase::QLuaData __TClass::s_LuaInterface[] = {

/************************************************************************/

//ע�����α���
#define REGISTER_LUA_INTEGER(__VAR_NAME__, __VAR_DESC__)						\
	QLunaBase::_MkLuaValueInt("n"#__VAR_NAME__, __VAR_DESC__,					\
	&__TClass::set##__VAR_NAME__, &__TClass::get##__VAR_NAME__),

//ע���޷������α���
#define REGISTER_LUA_DWORD(__VAR_NAME__, __VAR_DESC__)							\
	QLunaBase::_MkLuaValueDword("dw"#__VAR_NAME__, __VAR_DESC__,				\
	&__TClass::set##__VAR_NAME__, &__TClass::get##__VAR_NAME__),

//ע���ַ�������
#define REGISTER_LUA_STRING(__VAR_NAME__, __VAR_DESC__)							\
	QLunaBase::_MkLuaValueStr("sz"#__VAR_NAME__, __VAR_DESC__,					\
	&__TClass::set##__VAR_NAME__, &__TClass::get##__VAR_NAME__),

//ע��ö���ͱ���
#define REGISTER_LUA_ENUM(__VAR_NAME__, __VAR_DESC__)							\
	QLunaBase::QLuaData("e"#__VAR_NAME__, QLunaBase::ldtEnum, __VAR_DESC__,		\
	(QLunaBase::SetIntFunc)(&__TClass::set##__VAR_NAME__),						\
	(QLunaBase::GetIntFunc)(&__TClass::get##__VAR_NAME__)),

//ע�᲼���ͱ���
#define REGISTER_LUA_BOOL(__VAR_NAME__, __VAR_DESC__)							\
	QLunaBase::QLuaData("b"#__VAR_NAME__, QLunaBase::ldtBool, __VAR_DESC__,		\
	(QLunaBase::SetIntFunc)(&__TClass::set##__VAR_NAME__),						\
	(QLunaBase::GetIntFunc)(&__TClass::get##__VAR_NAME__)),

/************************************************************************/

//ע��ֻ�����α���
#define REGISTER_LUA_INTEGER_READONLY(__VAR_NAME__, __VAR_DESC__)				\
	QLunaBase::_MkLuaValueInt("n"#__VAR_NAME__, __VAR_DESC__,					\
	(void (__TClass::*)(int))NULL, &__TClass::get##__VAR_NAME__),

//ע��ֻ���޷������α���
#define REGISTER_LUA_DWORD_READONLY(__VAR_NAME__, __VAR_DESC__)					\
	QLunaBase::_MkLuaValueDword("dw"#__VAR_NAME__, __VAR_DESC__,				\
	(void (__TClass::*)(DWORD))NULL, &__TClass::get##__VAR_NAME__),

//ע��ֻ���ַ�������
#define REGISTER_LUA_STRING_READONLY(__VAR_NAME__, __VAR_DESC__)				\
	QLunaBase::_MkLuaValueStr("sz"#__VAR_NAME__, __VAR_DESC__,					\
	(void (__TClass::*)(LPCSTR))NULL, &__TClass::get##__VAR_NAME__),

//ע��ֻ��ö���ͱ���
#define REGISTER_LUA_ENUM_READONLY(__VAR_NAME__, __VAR_DESC__)					\
	QLunaBase::QLuaData("e"#__VAR_NAME__, QLunaBase::ldtEnum, __VAR_DESC__,		\
	(QLunaBase::VoidFunc)NULL,													\
	(QLunaBase::GetIntFunc)(&__TClass::get##__VAR_NAME__)),

//ע��ֻ�������ͱ���
#define REGISTER_LUA_BOOL_READONLY(__VAR_NAME__, __VAR_DESC__)					\
	QLunaBase::QLuaData("b"#__VAR_NAME__, QLunaBase::ldtBool, __VAR_DESC__,		\
	(QLunaBase::VoidFunc)NULL,													\
	(QLunaBase::GetIntFunc)(&__TClass::get##__VAR_NAME__)),

// ע��ֻ����userdata
#define REGISTER_LUA_CLASS_READONLY(__VAR_NAME__, __VAR_DESC__)					\
	QLunaBase::QLuaData("p"#__VAR_NAME__, QLunaBase::ldtClass, __VAR_DESC__,	\
	(QLunaBase::VoidFunc)NULL,													\
	(QLunaBase::VoidFunc)(&__TClass::get##__VAR_NAME__)),


/************************************************************************/

//ע�ᵼ������
#define REGISTER_LUA_FUNC(__FUNC_NAME__, __FUNC_DESC__, __FUNC_PARAM__,			\
	__PARAM_DESC__, __RETURN_DESC__)											\
	QLunaBase::_MkLuaFunc(#__FUNC_NAME__, __FUNC_DESC__,						\
	&__TClass::Lua##__FUNC_NAME__, __FUNC_PARAM__,								\
	__PARAM_DESC__, __RETURN_DESC__),

/************************************************************************/

//���嵼�������
#define DEFINE_LUA_CLASS_END()													\
	QLunaBase::QLuaData()														\
};



//��������	����ʹ��ģ�棬Ŀ���ǿ��԰Ѳ��ִ���ת�Ƶ�.cpp��
class CORE_API QLunaBase
{
public:
	//Lua�������������ͣ����ڲ�ʹ��
	enum LUA_DATA_TYPE
	{
		ldtInvalid = 0,

		ldtInteger,
		ldtString,
		ldtDword,
		ldtEnum,
		ldtBool,
		ldtFunc,
		ldtClass,
		ldtExtFun,

		ldtTotal
	};

	typedef void (QLunaBase::*VoidFunc)(void) const;

	typedef void (QLunaBase::*SetIntFunc)(int);
	typedef int (QLunaBase::*GetIntFunc)(void) const;

	typedef void (QLunaBase::*SetStrFunc)(LPCSTR);
	typedef LPCSTR (QLunaBase::*GetStrFunc)(void) const;

	typedef void (QLunaBase::*SetDwordFunc)(DWORD);
	typedef DWORD (QLunaBase::*GetDwordFunc)(void) const;

	typedef int (QLunaBase::*LuaFunc)(QLuaScript& sc);

	typedef QLunaBase* (QLunaBase::*GetClassFunc)(void) const;

	typedef int (*ExtFunc)(QLuaScript& sc, QLunaBase*);

	struct QLuaData
	{
		LPCSTR			pszName;		//��Ա����
		LUA_DATA_TYPE	eType;			//��Ա����
		LPCSTR			pszDesc;		//��������
		union
		{
			struct 
			{
				VoidFunc	fnSet;			//����д�ӿں���
				VoidFunc	fnGet;			//���ݶ��ӿں���
				DWORD		dwReserve1;		// �����ֶ�
				DWORD		dwReserve2;		// �����ֶ�
			}data;
			struct 
			{
				LuaFunc		fnLuaFunc;		//���õĺ���
				LPCSTR		pszParam;		//��ڲ���
				LPCSTR		pszParamDesc;	//��ڲ�����������
				LPCSTR		pszReturnDesc;	//����ֵ����������
			}func;
			struct
			{
				ExtFunc		fnExtFunc;
				DWORD		dwReserv1;
				DWORD		dwReserv2;
				DWORD		dwReserv3;
			}extFunc;
		};

		// ��������
		QLuaData(LPCSTR pszDataName, LUA_DATA_TYPE eDataType, LPCSTR pszDataDesc, VoidFunc fnSet, VoidFunc fnGet)
		{
			pszName			= pszDataName;
			eType			= eDataType;
			pszDesc			= pszDataDesc;
			data.fnSet		= fnSet;
			data.fnGet		= fnGet;
			data.dwReserve1	= 0;
			data.dwReserve2	= 0;
		}
		// ��������
		QLuaData(LPCSTR pszFuncName, LPCSTR pszFuncDesc, LuaFunc fnLunFunc, LPCSTR pszParam,
			LPCSTR pszParamDesc, LPCSTR pszReturnDesc)
		{
			pszName				= pszFuncName;
			eType				= ldtFunc;
			pszDesc				= pszFuncDesc;
			func.fnLuaFunc		= fnLunFunc;
			func.pszParam		= pszParam;
			func.pszParamDesc	= pszParamDesc;
			func.pszReturnDesc	= pszReturnDesc;
		}
		QLuaData(LPCSTR pszFuncName, LPCSTR pszFuncDesc, ExtFunc fnExtFunc)
		{
			pszName					= pszFuncName;
			eType					= ldtExtFun;
			pszDesc					= pszFuncDesc;
			
			extFunc.fnExtFunc		= fnExtFunc;
			extFunc.dwReserv1		= 0;
			extFunc.dwReserv2		= 0;
			extFunc.dwReserv3		= 0;
		}
		// ��������
		QLuaData()
		{
			ZeroStruct(*this);
		}
	};

	// ��������
	template <class _TClass_>
	static QLuaData _MkLuaValueInt(LPCSTR pszDataName, LPCSTR pszDataDesc,
		void (_TClass_::*fnSet)(int), int (_TClass_::*fnGet)(void) const)
	{ return QLuaData(pszDataName, ldtInteger, pszDataDesc, (VoidFunc)fnSet, (VoidFunc)fnGet); }

	template <class _TClass_>
	static QLuaData _MkLuaValueDword(LPCSTR pszDataName, LPCSTR pszDataDesc,
		void (_TClass_::*fnSet)(DWORD), DWORD (_TClass_::*fnGet)(void) const)
	{ return QLuaData(pszDataName, ldtDword, pszDataDesc, (VoidFunc)fnSet, (VoidFunc)fnGet); }

	template <class _TClass_>
	static QLuaData _MkLuaValueStr(LPCSTR pszDataName, LPCSTR pszDataDesc,
		void (_TClass_::*fnSet)(LPCSTR), LPCSTR (_TClass_::*fnGet)(void) const)
	{ return QLuaData(pszDataName, ldtString, pszDataDesc, (VoidFunc)fnSet, (VoidFunc)fnGet); }

	// ��������
	template <class _TClass_>
	static QLuaData _MkLuaFunc(LPCSTR pszFuncName, LPCSTR pszFuncDesc, int (_TClass_::*fnLunFunc)(QLuaScript&),
		LPCSTR pszParam, LPCSTR pszParamDesc, LPCSTR pszReturnDesc)
	{ return QLuaData(pszFuncName, pszFuncDesc, (LuaFunc)fnLunFunc, pszParam, pszParamDesc, pszReturnDesc); }

	virtual BOOL PushCObj(lua_State* L) const	= 0;
	static QLunaBase* GetCObj(lua_State* L, int nIndex);

private:
	static const QLuaData* GetLuaData(lua_State* L, int nIndex);

protected:
	BOOL _PushCObj(lua_State* L, LPCSTR pszClassName, int nSize = 0) const;

	static BOOL _Register(lua_State* L, LPCSTR pszClassName, QLuaData* pLuaData,
		lua_CFunction pFunTos, lua_CFunction pFunIdx, lua_CFunction pFunNew, lua_CFunction pFunInf,
		QLuaData **ppExtLuaData = NULL, INT nExtLuaDataCount = 0
		);

	static int _LuaGetDataInfo(lua_State* L, LPCSTR pszClassName);

	// �������������������Խ�static�ĵ��ã�ת������thisָ������Ա��������
	static int _LuaDispatcher(lua_State *L, LPCSTR pszClassName);

	// �����ַ���ת������
	static int _LuaTostring (lua_State* L, LPCSTR pszClassName);

	// ����GetTable����
	static int _LuaIndex(lua_State* L, LPCSTR pszClassName, lua_CFunction pFunDis);

	// ����SetTable����
	static int _LuaNewIndex(lua_State* L, LPCSTR pszClassName);

	// ����ű���������ʱTable
	static BOOL GetScriptTempTable(lua_State* L, LPCSTR pszClassName, int nIndex);
	static BOOL ClearScriptTempTable(lua_State* L, LPCSTR pszClassName, int nIndex);

	static BOOL _RegisterExtFun(lua_State* L, LPCSTR pszClassName, LPCSTR pszFuncName, ExtFunc pExtFunc,  QLuaData *pLuaData, LPCSTR *ppszDeriveClasses = NULL, INT nDeriveClassCount = 0);

private:
	struct _LuaLunaData 
	{
		BYTE byType;
		const void* pData;
	};

	enum _KE_LUNADATA_TYPE
	{
		emKLUNADATA_TYPE_POINTER,
		emKLUNADATA_TYPE_COPY,
	};
};

typedef std::list<QLunaBase::QLuaData> LuaDataList;

