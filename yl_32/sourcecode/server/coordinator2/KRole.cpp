#include "stdafx.h"
#include "KRole.h"
#include "GameCenter.h"


KRole::KRole(void)
{
    m_pszAccount                = NULL;
    m_szName[0]                 = '\0';
    m_dwPlayerID                = 0;
    m_nConnIndex                = 0;
    m_dwMapID                   = 0;
    m_nMapCopyIndex             = 0;

    m_nDestConnIndex            = 0;
    m_dwDestMapID               = 0;
    m_nDestMapCopyIndex         = 0;
    
    m_dwSystemTeamID            = KD_BAD_ID;
    m_dwTeamID                  = KD_BAD_ID;
    //m_eCamp                     = cNeutral;
    m_dwTongID                  = KD_BAD_ID;

    m_byLevel                   = 0;
    m_byType                    = 0;
    m_dwForceID                 = 0;

	m_eRoleState                = rsOffline;
}

KRole::~KRole(void)
{
}

KROLE_STATE KRole::GetRoleState(void)
{
	return m_eRoleState;
}

void KRole::SetRoleState(KROLE_STATE eDestState)
{
	QLogPrintf(LOG_INFO,"..KRole::SetRoleState(KROLE_STATE eDestState=%d)",eDestState);
    assert(eDestState > rsInvalid && eDestState < rsTotal);

    if (eDestState == rsOffline && g_pGameCenter->m_Settings.m_nGlobalServerMode != emRUNMODE_MASTER)
    {
        g_pGameCenter->m_Gateway.DoPlayerLeaveGame(m_pszAccount);

		m_nConnIndex        = 0;
		m_nDestConnIndex    = 0;
        m_dwMapID           = 0;
        m_nMapCopyIndex     = 0;
        m_dwDestMapID       = 0;
        m_nDestMapCopyIndex = 0;

        //g_pGameCenter->m_ApexProxy.DoRoleLogout(m_dwPlayerID);
        g_pGameCenter->m_TongManager.OnPlayerLeaveGame(this);
		g_pGameCenter->m_RelationManager.OnPlayerLeave(m_dwPlayerID);
        //g_pGameCenter->m_GameServer.DoSyncFellowshipMapID(m_dwPlayerID, m_dwMapID);
        //g_pGameCenter->m_GameServer.DoSyncFellowshipPlayerLevel(m_dwPlayerID, 0, true);
		//g_pGameCenter->m_MentorCenter.ClearMaxApprenticeNum(m_dwPlayerID);
		g_pGameCenter->m_MailManager.UnLoadMailCount(m_dwPlayerID);

        CallLogoutScript();
    }

	m_eRoleState = eDestState;
}

BOOL KRole::IsOnline()
{
    BOOL bResult = false;

    switch (m_eRoleState)
    {
    case rsInvalid:
    case rsOffline:
    case rsLG_WaitForPermit:
    case rsLG_WaitForLogin:
        break;
    case rsOnline:
    case rsCG_WaitForSrcLeave:
    case rsCG_WaitForGuid:
    case rsCG_WaitForCreateMap:
    case rsCG_WaitForPlayerData:
    case rsCG_WaitForEnter_Leave:
    case rsCG_WaitForDestEnter:
    case rsCG_WaitForDestTimeout:
    case rsCG_WaitForSrcTimeout:
        bResult = true;
        break;
    default:
		QCONFIRM_RET_FALSE(false);
		break;
    }  
    return bResult;
}

BOOL KRole::UpdateMapCopyOwnerForTeamLeader()
{
    BOOL            bResult         = false;
    BOOL            bRetCode        = false;
    KTeam*          pTeam           = NULL;
    const KMapCopy* pcMapCopy       = NULL;
    KMapInfo*       pMapInfo        = NULL;
    KRole*          pOldOwner       = NULL;           

    PROCESS_ERROR(m_dwTeamID != KD_BAD_ID);

    pTeam = g_pGameCenter->m_TeamCenter.GetTeam(m_dwTeamID);
    LOG_PROCESS_ERROR(pTeam);

    PROCESS_ERROR(pTeam->dwAuthority[tatLeader] == m_dwPlayerID);

    // ���ڶӳ������ƽ���һ�������ߵ����,�����Ҳ�����ͼҲ��������
    pMapInfo = g_pGameCenter->m_MapManager.GetMapInfo(m_dwMapID);
    PROCESS_ERROR(pMapInfo);

    PROCESS_SUCCESS(pMapInfo->m_nType != emtDungeon);
    
    pcMapCopy = g_pGameCenter->m_MapManager.GetMapCopy(m_dwMapID, m_nMapCopyIndex);
    PROCESS_ERROR(pcMapCopy);
    
    if (pcMapCopy->m_dwOwnerID != KD_BAD_ID)
    {
        pOldOwner = g_pGameCenter->m_RoleManager.GetRole(pcMapCopy->m_dwOwnerID);
    }
    
    if (pOldOwner != NULL && pOldOwner->m_dwTeamID == m_dwTeamID)
    {
        bRetCode  = g_pGameCenter->m_MapManager.SetMapCopyOwner(m_dwMapID, m_nMapCopyIndex, m_dwPlayerID);    
        PROCESS_ERROR(bRetCode);
    }

EXIT1:
    bResult = true;
EXIT0:
    return bResult;
}

BOOL KRole::OnLeaveGS(int nConnIndex)
{
    BOOL        bResult         = false;
    BOOL        bRetCode        = false;
    KMapCopy*   pcMapCopy       = NULL;
    KMapInfo*   pMapInfo        = NULL;
    KTeam*      pTeam           = NULL;
	BOOL        bOffline        = false;
	KRole *     pRole           = NULL;
	if (nConnIndex == m_nConnIndex)
	{
		switch (m_eRoleState)
		{
        case rsOffline:
            assert(false);
            break;

		case rsOnline:            
            bRetCode = g_pGameCenter->m_MapManager.DecreaseMapCopyPlayerCount(m_dwMapID, m_nMapCopyIndex);
            LOG_PROCESS_ERROR(bRetCode);

			SetRoleState(rsOffline);
			bOffline = true;
			break;

        case rsCG_WaitForCreateMap:
            // ���,�ȴ���ͼ���صĹ�����,����˳�,����Դ������崻�(����Դ��Ŀ����ͬһ��������)
            bRetCode = g_pGameCenter->m_MapManager.DecreaseMapCopyPlayerCount(m_dwMapID, m_nMapCopyIndex);
            LOG_PROCESS_ERROR(bRetCode);

            // ������ҴӸ�����CallbackListɾ����
            pMapInfo = g_pGameCenter->m_MapManager.GetMapInfo(m_dwDestMapID);
            LOG_PROCESS_ERROR(pMapInfo);

            pcMapCopy = pMapInfo->GetMapCopy(m_nDestMapCopyIndex);
            LOG_PROCESS_ERROR(pcMapCopy);

            pcMapCopy->UnregisterCGCallbackPlayer(m_dwPlayerID);

            SetRoleState(rsOffline);
			bOffline = true;
            break;

		case rsCG_WaitForPlayerData:
            // ��Դ����������1
            bRetCode = g_pGameCenter->m_MapManager.DecreaseMapCopyPlayerCount(m_dwMapID, m_nMapCopyIndex);
            LOG_PROCESS_ERROR(bRetCode);

            // ��Ŀ�긱��������1
            pcMapCopy = g_pGameCenter->m_MapManager.GetMapCopy(m_dwDestMapID, m_nDestMapCopyIndex);
            if (pcMapCopy && pcMapCopy->m_nConnIndex == m_nDestConnIndex) // Ŀ��GS�����Ѿ�崻���,�����Ҳ���Ŀ�긱���ǿ��ܵ�
            {
                bRetCode = g_pGameCenter->m_MapManager.DecreaseMapCopyPlayerCount(m_dwDestMapID, m_nDestMapCopyIndex);
                LOG_PROCESS_ERROR(bRetCode);
            }

            SetRoleState(rsOffline);
			bOffline = true;

			
            break;

		case rsCG_WaitForGuid:
            // ��Դ����������1
            bRetCode = g_pGameCenter->m_MapManager.DecreaseMapCopyPlayerCount(m_dwMapID, m_nMapCopyIndex);
            LOG_PROCESS_ERROR(bRetCode);

            m_nConnIndex = 0;

			SetRoleState(rsCG_WaitForDestTimeout);
			break;

		case rsCG_WaitForEnter_Leave:
            // ��Դ����������1
            bRetCode = g_pGameCenter->m_MapManager.DecreaseMapCopyPlayerCount(m_dwMapID, m_nMapCopyIndex);
            LOG_PROCESS_ERROR(bRetCode);

            //g_pGameCenter->m_ApexProxy.DoLeaveServer(m_dwPlayerID, m_nConnIndex);

            m_nConnIndex = 0;

			SetRoleState(rsCG_WaitForDestEnter);
			break;

		case rsCG_WaitForSrcLeave:
            // ����Ѿ�����Ŀ��GS,�ȴ���ԴGS�뿪
            // ��Դ����������1
            bRetCode = g_pGameCenter->m_MapManager.DecreaseMapCopyPlayerCount(m_dwMapID, m_nMapCopyIndex);
            LOG_PROCESS_ERROR(bRetCode);

            //g_pGameCenter->m_ApexProxy.DoLeaveServer(m_dwPlayerID, m_nConnIndex);

            m_dwMapID            = m_dwDestMapID;
            m_nMapCopyIndex      = m_nDestMapCopyIndex;
            m_nConnIndex         = m_nDestConnIndex;

            //g_pGameCenter->m_ApexProxy.DoEntryServer(m_dwPlayerID, m_nConnIndex);
            
            //g_pGameCenter->m_GameServer.DoSyncFellowshipMapID(m_dwPlayerID, m_dwMapID);

		    SetRoleState(rsOnline);

			bOffline = true;
			
            g_pGameCenter->m_GameServer.DoConfirmPlayerLoginRespond(m_nDestConnIndex, m_dwPlayerID, true);

            if (m_dwTeamID != KD_BAD_ID)
            {
                pTeam = g_pGameCenter->m_TeamCenter.GetTeam(m_dwTeamID);
                LOG_PROCESS_ERROR(pTeam);

                pMapInfo = g_pGameCenter->m_MapManager.GetMapInfo(m_dwMapID);
                LOG_PROCESS_ERROR(pMapInfo);

                if (pMapInfo->m_nType == emtDungeon && pTeam->dwAuthority[tatLeader] == m_dwPlayerID)
                {
                    bRetCode = g_pGameCenter->m_MapManager.SetMapCopyOwner(m_dwMapID, m_nMapCopyIndex, m_dwPlayerID);
                    LOG_PROCESS_ERROR(bRetCode);
                }
            }
			break;

		case rsCG_WaitForSrcTimeout:
            // ��Դ����������1
            bRetCode = g_pGameCenter->m_MapManager.DecreaseMapCopyPlayerCount(m_dwMapID, m_nMapCopyIndex);
            LOG_PROCESS_ERROR(bRetCode);

			SetRoleState(rsOffline);
	
			bOffline = true;

			
			break;

        case rsCG_WaitForDestEnter:
        case rsCG_WaitForDestTimeout:
            assert(false);
            break;

		default:
			assert(false);
            break;
		}
	}
    else if (nConnIndex == m_nDestConnIndex)
	{
		switch (m_eRoleState)
		{
        case rsOffline:
        case rsOnline:
            break;

		case rsLG_WaitForPermit:
		case rsLG_WaitForLogin:
			bRetCode = g_pGameCenter->m_MapManager.DecreaseMapCopyPlayerCount(m_dwDestMapID, m_nDestMapCopyIndex);
            LOG_PROCESS_ERROR(bRetCode);

			SetRoleState(rsOffline);

			bOffline = true;
			break;

        case rsCG_WaitForCreateMap:
            // Ŀ���ͼ���ڷ�����崻���,��ʱҪ֪ͨԴ������"SearchMap"ʧ��,���л����״̬
            // ֪ͨ���,ǰ��·;��ͨ,�Ժ�����
            g_pGameCenter->m_GameServer.DoSearchMapRespond(
                m_nConnIndex, m_dwPlayerID, smrcFailed, false, 
                m_dwDestMapID, m_nDestMapCopyIndex,
                0, 0, 0
            );
            SetRoleState(rsOnline);
			bOffline = true;
            break;

        case rsCG_WaitForPlayerData:
            // ����ȴ���ɫ��Ϣ��ʱ��,Ŀ��GS崻�,��ʱʲôҲ������,�ȴ���ɫ��Ϣ�������˻�ȥ
            break;

        case rsCG_WaitForGuid:
            // �ڵȴ�GUID��ʱ��,Ŀ��GS崻���,��ʱӦ�ø�ԴGS�ذ������ο��
            // ��Ȼ,û��Ҫȥ��Ŀ�긱��������,��ΪĿ��Server��崻���,�Ǻ�
            g_pGameCenter->m_GameServer.DoTransferPlayerRespond(m_nConnIndex, m_dwPlayerID, false);

            SetRoleState(rsOnline);
			bOffline = true;
            break;

		case rsCG_WaitForEnter_Leave:
		case rsCG_WaitForSrcLeave:
            // ����ڿ�����ڴ�Ŀ��GS�˳�,��ʱҪ�ȴ���Ҵ�ԴGS�˳�,Ȼ������
            // ע��,��ʱ�����û���������,��ҵ�ConnIndex��������ԴGS�ϵ�
            // ��Ŀ�긱��������1
            bRetCode = g_pGameCenter->m_MapManager.DecreaseMapCopyPlayerCount(m_dwDestMapID, m_nDestMapCopyIndex);
            LOG_PROCESS_ERROR(bRetCode);
            
			SetRoleState(rsCG_WaitForSrcTimeout);

            m_dwDestMapID       = 0;
            m_nDestMapCopyIndex = 0;
            m_nDestConnIndex    = 0;
			break;

		case rsCG_WaitForDestEnter:
		case rsCG_WaitForDestTimeout:
            // ��Ŀ�긱��������1
            bRetCode = g_pGameCenter->m_MapManager.DecreaseMapCopyPlayerCount(m_dwDestMapID, m_nDestMapCopyIndex);
            LOG_PROCESS_ERROR(bRetCode);

			SetRoleState(rsOffline);
			bOffline = true;
			break;

        case rsCG_WaitForSrcTimeout:
            break;

		default:
            assert(false);
            break;
		}
	}
	//ldy:LogRoleLogout
	if(bOffline)
	{
		//pRole = g_pGameCenter->m_RoleManager.GetRole(m_dwPlayerID);
		g_pGameCenter->m_LogServerAgency.LogAction(PLAYER_ACTION_LOGOUT,this,0,"LogRoleLogout");
	}

    bResult = true;
EXIT0:
	return bResult;
}

BOOL KRole::CallLoginScript()
{
    BOOL        bResult             = false;
    BOOL        bRetCode            = false;
    int         nIndex              = 0;
    DWORD       dwScriptID          = 0;
    const char  cszFunction[]       = "OnRoleLogin";

//    dwScriptID = g_FileNameHash(ROLE_SCRIPT_NAME);
//
//    g_pGameCenter->m_ScriptManager.SafeCallBegin(&nIndex);
//
//    bRetCode = g_pGameCenter->m_ScriptManager.IsScriptExist(dwScriptID);
//    PROCESS_ERROR(bRetCode);
//
//    bRetCode = g_pGameCenter->m_ScriptManager.IsFuncExist(dwScriptID, cszFunction);
//    PROCESS_ERROR(bRetCode);
//
//    g_pGameCenter->m_ScriptManager.Push(this);
//
//    g_pGameCenter->m_ScriptManager.Call(dwScriptID, cszFunction, 0);
//
//    bResult = true;
//EXIT0:
//    g_pGameCenter->m_ScriptManager.SafeCallEnd(nIndex);
    return bResult;
}

BOOL KRole::CallLogoutScript()
{
    BOOL        bResult             = false;
    BOOL        bRetCode            = false;
    int         nIndex              = 0;
    DWORD       dwScriptID          = 0;
    const char  cszFunction[]       = "OnRoleLogout";
//
//    dwScriptID = g_FileNameHash(ROLE_SCRIPT_NAME);
//
//    g_pGameCenter->m_ScriptManager.SafeCallBegin(&nIndex);
//
//    bRetCode = g_pGameCenter->m_ScriptManager.IsScriptExist(dwScriptID);
//    PROCESS_ERROR(bRetCode);
//
//    bRetCode = g_pGameCenter->m_ScriptManager.IsFuncExist(dwScriptID, cszFunction);
//    PROCESS_ERROR(bRetCode);
//
//    g_pGameCenter->m_ScriptManager.Push(this);
//
//    g_pGameCenter->m_ScriptManager.Call(dwScriptID, cszFunction, 0);
//
//    bResult = true;
//EXIT0:
//    g_pGameCenter->m_ScriptManager.SafeCallEnd(nIndex);
    return bResult;
}

//int KRole::LuaIsOnline(Lua_State* L)
//{
//    BOOL bResult = 0;
//
//    bResult = IsOnline();
//
//    Lua_PushBoolean(L, bResult);
//    return 1;
//}
//
//DEFINE_LUA_CLASS_BEGIN(KRole)
//
//    REGISTER_LUA_STRING_READONLY(KRole, Account)
//    REGISTER_LUA_STRING_READONLY(KRole, Name)
//    REGISTER_LUA_DWORD_READONLY(KRole, PlayerID)
//    REGISTER_LUA_INTEGER_READONLY(KRole, ConnIndex)
//    REGISTER_LUA_DWORD_READONLY(KRole, MapID)
//    REGISTER_LUA_INTEGER_READONLY(KRole, MapCopyIndex)
//    REGISTER_LUA_DWORD_READONLY(KRole, TeamID)
//    REGISTER_LUA_ENUM_READONLY(KRole, Camp)
//    REGISTER_LUA_DWORD_READONLY(KRole, TongID)
//    REGISTER_LUA_INTEGER_READONLY(KRole, Level)
//    REGISTER_LUA_INTEGER_READONLY(KRole, Type)
//    REGISTER_LUA_TIME_READONLY(KRole, LastSaveTime)
//    REGISTER_LUA_DWORD_READONLY(KRole, ForceID)
//    REGISTER_LUA_FUNC(KRole, IsOnline)
//
//DEFINE_LUA_CLASS_END(KRole)

