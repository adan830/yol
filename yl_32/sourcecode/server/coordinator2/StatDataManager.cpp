#include "stdafx.h"
#include "StatDataManager.h"
#include "GameCenter.h"
#include "MapInfo.h"

#include "KRole.h"

KStatDataManager::KStatDataManager()
{
    m_nStatTime  = 0;
    m_nMaxUsedID = 0;
    memset(m_StatValues, 0, sizeof(m_StatValues));
}

KStatDataManager::~KStatDataManager()
{
}

BOOL KStatDataManager::Init()
{
    time_t nTimeNow = time(NULL);

    m_nStatTime = (nTimeNow / 3600) * 3600;

    return true;
}

void KStatDataManager::UnInit()
{
    m_DataNameTable.clear();
}

void KStatDataManager::Activate()
{
    if (g_pGameCenter->m_nWorkLoop % (GAME_FPS * 60) == 0)
    {
        time_t nCurrentTime = (g_pGameCenter->m_nTimeNow / 3600) * 3600; // ���뵽Сʱ

        SaveAll();

        if (nCurrentTime != m_nStatTime)
        {
            memset(m_StatValues, 0, sizeof(m_StatValues));
            m_nMaxUsedID = 0;

            m_nStatTime = nCurrentTime;
        }
    }
}

BOOL KStatDataManager::OnGSUpdate(KSTAT_DATA_MODIFY* pData, int nCount)
{
    KSTAT_DATA_MODIFY*  pNode   = pData;
    KSTAT_DATA_MODIFY*  pTail   = pData + nCount;

    while (pNode < pTail)
    {
        m_StatValues[pNode->nID - 1] += pNode->nValue;
        
        if (pNode->nID > m_nMaxUsedID)
            m_nMaxUsedID = pNode->nID;

        pNode++;
    }
    
    return true;
}

int KStatDataManager::GetNameID(const char cszName[])
{
    int                         nResult    = 0;
    int                         nRetCode   = 0;
    int                         nNameID    = 0;
    UINT64                    uNewDataID = 0;
    KDATA_NAME_TABLE::iterator  it;

    it = m_DataNameTable.find(cszName);
    if (it == m_DataNameTable.end())
    {
        nRetCode = g_pGameCenter->m_piSequence->GenerateID("StatDataName", 1, &uNewDataID);
        LOG_PROCESS_ERROR(nRetCode);

        nNameID = (int)uNewDataID;
        LOG_PROCESS_ERROR(nNameID <= MAX_STAT_DATA_COUNT);

        m_DataNameTable[cszName] = nNameID;

        g_pGameCenter->m_MiscDB.DoSaveStatDataName((char*)cszName, nNameID);
    }
    else
    {
        nNameID = it->second;
    }

    nResult = nNameID;
EXIT0:
    return nResult;
}

// ֱ������ĳ��ͳ�����ݵ�ֵ������
BOOL KStatDataManager::SetDataValue(const char cszName[], INT64 nValue)
{
    BOOL                                        bResult     = false;
    int                                         nRetCode    = 0;
    int                                         nNameID     = 0;
    UINT64                                    uNewDataID  = 0;

    nNameID = GetNameID(cszName);
    LOG_PROCESS_ERROR(nNameID != 0);

    m_StatValues[nNameID - 1] = nValue;
    
    if (nNameID > m_nMaxUsedID)
        m_nMaxUsedID = nNameID;

    bResult = true;
EXIT0:
    return bResult;
}

BOOL KStatDataManager::SaveAll()
{
    BOOL    bResult         = false;
    int     nFarmerCount    = 0;
    int     nTeamCount      = 0;

    UpdateRoleStat();

    //nFarmerCount = g_pGameCenter->m_AntiFarmerManager.GetFarmerCount();

    SetDataValue("ANTI_FARMER", nFarmerCount);
    
    nTeamCount = g_pGameCenter->m_TeamCenter.GetTeamCount();
    SetDataValue("TEAM_COUNT", nTeamCount);

    PROCESS_ERROR(m_nMaxUsedID > 0);

    g_pGameCenter->m_MiscDB.DoSaveStatData(m_nStatTime, m_nMaxUsedID, &m_StatValues[0]);

    bResult = true;
EXIT0:
    return bResult;
}

BOOL KStatDataManager::LoadDataName(const char szName[], int nID)
{
    BOOL                                        bResult = false;
    KDATA_NAME_TABLE::iterator                  it;
    std::pair<KDATA_NAME_TABLE::iterator, BOOL> InsRet;

    assert(szName);
    LOG_PROCESS_ERROR(nID > 0 && nID <= MAX_STAT_DATA_COUNT);
    
    it = m_DataNameTable.find(szName);
    LOG_PROCESS_ERROR(it == m_DataNameTable.end());

    InsRet = m_DataNameTable.insert(std::make_pair(szName, nID));
    LOG_PROCESS_ERROR(InsRet.second);

    bResult = true;
EXIT0:
    return bResult;
}

BOOL KStatDataManager::LoadData(time_t nTime, BYTE* pbyData, size_t uDataLen)
{
    BOOL            bResult = false;
    KStatData_DB*   pDataDB = (KStatData_DB*)pbyData;
    
    assert(pDataDB);
    LOG_PROCESS_ERROR(nTime <= g_pGameCenter->m_nTimeNow);

    LOG_PROCESS_ERROR(uDataLen == sizeof(KStatData_DB) + pDataDB->nDataCount * sizeof(INT64));

    memcpy(&m_StatValues[0], pDataDB->nData, uDataLen - sizeof(pDataDB->nDataCount));

    m_nStatTime  = nTime;
    m_nMaxUsedID = pDataDB->nDataCount;

    bResult = true;
EXIT0:
    return bResult;
}

BOOL KStatDataManager::Update(const char cszName[], INT64 nValue)
{
    BOOL    bResult = false;
    int     nNameID = 0;

    nNameID = GetNameID(cszName);
    LOG_PROCESS_ERROR(nNameID);

    m_StatValues[nNameID - 1] += nValue;

    if (nNameID > m_nMaxUsedID)
        m_nMaxUsedID = nNameID;

    bResult = true;
EXIT0:
    return bResult;
}

struct KROLE_GROUP_MAP_KEY 
{
    BOOL    m_bOnline;
    BOOL    m_bInTong;
    //KCAMP   m_eCamp;

    KROLE_GROUP_MAP_KEY(BOOL bOnline, BOOL bInTong/*, KCAMP eCamp*/)
    {
        m_bOnline   = bOnline;
        m_bInTong   = bInTong;
        //m_eCamp     = eCamp;
    };
};

inline bool operator < (const KROLE_GROUP_MAP_KEY& crLeft, const KROLE_GROUP_MAP_KEY& crRight)
{
    if (crLeft.m_bOnline == crRight.m_bOnline)
    {
        //if (crLeft.m_bInTong == crRight.m_bInTong)
        //{
        //    return crLeft.m_eCamp < crRight.m_eCamp;
        //}
        return crLeft.m_bInTong < crRight.m_bInTong;
    }
    return crLeft.m_bOnline < crRight.m_bOnline;
}

struct KUPDATE_ROLE_STAT 
{
    BOOL operator () (DWORD dwRoleID, KRole& rRole)
    {
        g_pGameCenter->m_RoleManager.m_lock.Lock();
        BOOL    bRetCode    = false;
        time_t  nActiveTime = rRole.m_nLastSaveTime > 0 ? rRole.m_nLastSaveTime : rRole.m_nCreateTime;
        int     nOffDays    = (int)((g_pGameCenter->m_nTimeNow - nActiveTime) / (24 * 3600));
        KROLE_GROUP_MAP_KEY         GroupKey(rRole.IsOnline(), !!rRole.m_dwTongID/*, rRole.m_eCamp*/);
        KROLE_DIST_MAP::iterator    itDist;
        KROLE_GROUP_MAP::iterator   itGroup;
        KROLE_ACTIVE_MAP::iterator  itActive;

        // ���߽�ɫ�ֲ�
        bRetCode = rRole.IsOnline();
        if (bRetCode)
        {
            itDist = m_RoleDistMap.find(std::make_pair(rRole.m_dwMapID, rRole.m_byLevel));
            if (itDist == m_RoleDistMap.end())
                m_RoleDistMap.insert(std::make_pair(std::make_pair(rRole.m_dwMapID, rRole.m_byLevel), 1));
            else
                (itDist->second)++;
        }

        // Ⱥ��
        itGroup = m_RoleGroupMap.find(GroupKey);
        if (itGroup == m_RoleGroupMap.end())
            m_RoleGroupMap.insert(std::make_pair(GroupKey, 1));
        else
            (itGroup->second)++;

        // ��ʧ��
        if (nOffDays > 100)
            nOffDays = 100;

        itActive = m_RoleActiveMap.find(std::make_pair(nOffDays, rRole.m_byLevel));
        if (itActive == m_RoleActiveMap.end())
            m_RoleActiveMap.insert(std::make_pair(std::make_pair(nOffDays, rRole.m_byLevel), 1));
        else
            (itActive->second)++;
		g_pGameCenter->m_RoleManager.m_lock.Unlock();
        return true;
    };

    typedef std::map<std::pair<DWORD, int>, unsigned int, std::less<std::pair<DWORD, int> > >  KROLE_DIST_MAP;
    typedef std::map<KROLE_GROUP_MAP_KEY, unsigned int, std::less<KROLE_GROUP_MAP_KEY> >      KROLE_GROUP_MAP;
    typedef std::map<std::pair<int, int>, unsigned int, std::less<std::pair<int, int> > >    KROLE_ACTIVE_MAP;
    
    KROLE_DIST_MAP      m_RoleDistMap;
    KROLE_GROUP_MAP     m_RoleGroupMap;
    KROLE_ACTIVE_MAP    m_RoleActiveMap;
};

void KStatDataManager::UpdateRoleStat()
{
    int                 nRoleCount      = 0;
    int                 nAccountCount   = 0;
    KUPDATE_ROLE_STAT   UpdateRoleStat;
    char                szVarName[STAT_DATA_NAME_LEN];

    // ��ɫ��Ϣͳ��
    g_pGameCenter->m_RoleManager.Traverse(UpdateRoleStat);

    for (
        KUPDATE_ROLE_STAT::KROLE_DIST_MAP::iterator it = UpdateRoleStat.m_RoleDistMap.begin(), itEnd = UpdateRoleStat.m_RoleDistMap.end();
        it != itEnd;
        ++it
    )
    {
        snprintf(szVarName, sizeof(szVarName), "ROLE_DIST|%u|%d", it->first.first, it->first.second);
        szVarName[sizeof(szVarName) - 1] = '\0';

        g_pGameCenter->m_StatDataManager.SetDataValue(szVarName, it->second);
    }

    for (
        KUPDATE_ROLE_STAT::KROLE_GROUP_MAP::iterator it = UpdateRoleStat.m_RoleGroupMap.begin(), itEnd = UpdateRoleStat.m_RoleGroupMap.end();
        it != itEnd;
        ++it
    )
    {
        const char* pszCamp     = NULL;
        const char* pszOnline   = (it->first.m_bOnline ? "ONLINE" : "OFFLINE");
        const char* pszTong     = (it->first.m_bInTong ? "IN_TONG" : "OUT_TONG");

        //switch (it->first.m_eCamp)
        //{
        //case cGood:
        //    pszCamp = "GOOD";
        //    break;
        //case cEvil:
        //    pszCamp = "EVIL";
        //    break;
        //default:
        //    pszCamp = "NEUTRAL";
        //    break;
        //}

        snprintf(szVarName, sizeof(szVarName), "ROLE_GROUP|%s|%s|%s", pszOnline, pszCamp, pszTong);
        szVarName[sizeof(szVarName) - 1] = '\0';

        g_pGameCenter->m_StatDataManager.SetDataValue(szVarName, it->second);
    }

    for (
        KUPDATE_ROLE_STAT::KROLE_ACTIVE_MAP::iterator it = UpdateRoleStat.m_RoleActiveMap.begin(), itEnd = UpdateRoleStat.m_RoleActiveMap.end();
        it != itEnd;
        ++it
    )
    {
        snprintf(szVarName, sizeof(szVarName), "ROLE_ACTIVE|%d|%d", it->first.first, it->first.second);
        szVarName[sizeof(szVarName) - 1] = '\0';

        g_pGameCenter->m_StatDataManager.SetDataValue(szVarName, it->second);
    }

    // ��ɫ����
    snprintf(szVarName, sizeof(szVarName), "ROLE_TOTAL");
    szVarName[sizeof(szVarName) - 1] = '\0';

    nRoleCount = g_pGameCenter->m_RoleManager.GetRoleCountTotal();
    g_pGameCenter->m_StatDataManager.SetDataValue(szVarName, nRoleCount);

    // �˺�����
    snprintf(szVarName, sizeof(szVarName), "ACCOUNT_TOTAL");
    szVarName[sizeof(szVarName) - 1] = '\0';

    nAccountCount = g_pGameCenter->m_RoleManager.GetAccountCountTotal();
    g_pGameCenter->m_StatDataManager.SetDataValue(szVarName, nAccountCount);
}

void KStatDataManager::UpdateCreateMap(KMapInfo* pMapInfo)
{
    char szVarName[STAT_DATA_NAME_LEN];

    if (pMapInfo->m_nType != emtDungeon && pMapInfo->m_nType != emtBattleField)
        return;

    snprintf(szVarName, sizeof(szVarName), "MAP|%u|CREATE", pMapInfo->m_dwMapID);
    szVarName[sizeof(szVarName) - 1] = '\0';

    Update(szVarName, 1);
}

void KStatDataManager::UpdataAuctionItemStat(DWORD dwTabType, DWORD dwTabIndex, int nMoney)
{
    char szVarName[STAT_DATA_NAME_LEN];

    snprintf(szVarName, sizeof(szVarName), "AUCTION_COUNT|%u|%u", dwTabType, dwTabIndex);
    szVarName[sizeof(szVarName) - 1] = '\0';

    Update(szVarName, 1); // ͳ�������е��߽��׳ɹ�����

    snprintf(szVarName, sizeof(szVarName), "AUCTION_MONEY|%u|%u", dwTabType, dwTabIndex);
    szVarName[sizeof(szVarName) - 1] = '\0';

    Update(szVarName, nMoney); // ͳ�������е��߽��׽��
}

void KStatDataManager::UpdateMoneyStat(KRole* pRole, int nMoney, const char cszMethod[])
{
    const char* pszGain = (nMoney >= 0 ? "GAIN" : "COST");
    char szVarName[STAT_DATA_NAME_LEN];

    PROCESS_ERROR(nMoney != 0);

    snprintf(szVarName, sizeof(szVarName), "MONEY|%s|%u|%d|%s", pszGain, pRole->m_dwMapID, pRole->m_byLevel, cszMethod);
    szVarName[sizeof(szVarName) - 1] = '\0';

    if (nMoney < 0)
        nMoney = -nMoney;

    Update(szVarName, nMoney);

EXIT0:
    return;
}

void KStatDataManager::UpdataCreateOrDeleteRole(BOOL bCreate)
{
    const char* pszCreate = (bCreate ? "CREATE" : "DELETE");
    char szVarName[STAT_DATA_NAME_LEN];

    snprintf(szVarName, sizeof(szVarName), "ROLE|%s", pszCreate);
    szVarName[sizeof(szVarName) - 1] = '\0';

    Update(szVarName, 1);
}

void KStatDataManager::UpdateGameCardDealAmmount(int nCoin, int nMoney)
{
    Update("GAMECARD_COIN", nCoin);

    Update("GAMECARD_MONEY", nMoney);
}

void KStatDataManager::UpdateMentorCreateStat(DWORD dwMentorID, DWORD dwApprenticeID)
{
    KRole*  pMRole  = g_pGameCenter->m_RoleManager.GetRole(dwMentorID);
    KRole*  pARole  = g_pGameCenter->m_RoleManager.GetRole(dwApprenticeID);
    char    szVarName[STAT_DATA_NAME_LEN];

    LOG_PROCESS_ERROR(pMRole);
    LOG_PROCESS_ERROR(pARole);

    Update("MENTOR_NEW", 1);

    snprintf(szVarName, sizeof(szVarName), "MENTOR_CREATE_MENTOR_FORCE|%u", pMRole->m_dwForceID);
    szVarName[sizeof(szVarName) - 1] = '\0';

    Update(szVarName, 1);

    snprintf(szVarName, sizeof(szVarName), "MENTOR_CREATE_APPRENTICE_FORCE|%u", pARole->m_dwForceID);
    szVarName[sizeof(szVarName) - 1] = '\0';

    Update(szVarName, 1);

EXIT0:
    return;
}

void KStatDataManager::UpdateMentorDeleteStat()
{
    Update("MENTOR_DEL", 1);
}

void KStatDataManager::UpdateMentorGraduateStat(DWORD dwMentorID, DWORD dwApprenticeID)
{
    KRole* pMRole = g_pGameCenter->m_RoleManager.GetRole(dwMentorID);
    KRole* pARole = g_pGameCenter->m_RoleManager.GetRole(dwApprenticeID);

    Update("MENTOR_GRADUATE", 1);

    PROCESS_ERROR(pMRole);
    PROCESS_ERROR(pARole);

    if (pMRole->m_dwTongID != 0 && pMRole->m_dwTongID == pARole->m_dwTongID)
    {
        Update("MENTOR_GRADUATE_SAME_TONG", 1);
    }

EXIT0:
    return;
}

void KStatDataManager::UpdateMentorBrokenStat(DWORD dwMentorID, DWORD dwApprenticeID)
{
    KRole* pMRole = g_pGameCenter->m_RoleManager.GetRole(dwMentorID);
    KRole* pARole = g_pGameCenter->m_RoleManager.GetRole(dwApprenticeID);
    char szVarName[STAT_DATA_NAME_LEN];

    if (pMRole)
    {
        snprintf(szVarName, sizeof(szVarName), "MENTOR_BROKEN_MENTOR_LEVEL|%u", pMRole->m_byLevel);
        szVarName[sizeof(szVarName) - 1] = '\0';

        Update(szVarName, 1);
    }

    if (pARole)
    {
        snprintf(szVarName, sizeof(szVarName), "MENTOR_BROKEN_APPRENTICE_LEVEL|%u", pARole->m_byLevel);
        szVarName[sizeof(szVarName) - 1] = '\0';

        Update(szVarName, 1);
    }
}
