
#pragma once

#include <map>
#include <set>
#include "RoleDB.h"

#define MAX_MAP_COPY_DATA_LEN   (1024 * 32)

class KRole;

// ���ڸ�����Owner����:
// 1. ��һ���ͼ���븱��
//    1.1 ������Ļ�,��SearchMapʱ�����л�Owner,������CreateMapRespond��ʱ��
//    1.2 ����Ļ�,��ConfirmLogin��ʱ����Owner�л�
// 2. ����ڸ��������߿��ܷ����ӳ��л�,���������Ӵ���������
// 3. �ӳ��л�,�����Ҫ����Ӵ����д���,ע��,�ӳ��л��ڵ�¼��ʱ��Ҳ���ܷ���
// 4. ���븱�������(���->������->��ɢ->�����),����,��CreateMap��ʱ��Ҫ����


enum KMAP_COPY_STATE
{
    eMapStateInvalid = 0,

    eMapStateOffline,
    eMapStateCreating,
    eMapStateNormal,
    eMapStateRefreshing,
    eMapStateUnloading,

    eMapStateTotal
};

struct KCreateMapCGCallbackInfo
{
    DWORD               dwPlayerID;
    int                 nX;
    int                 nY;
    int                 nZ;
    time_t              nStartWaitTime;
};

typedef std::list<KCreateMapCGCallbackInfo> KCREATE_MAP_CG_CALLBACK_LIST;
typedef std::set<DWORD, std::less<DWORD> > KMAP_COPY_PLAYER_LIST;
typedef std::map<DWORD, time_t, std::less<DWORD> > KMAP_COPY_PLAYER_KEEP_LIST;

struct KMapCopy
{
    KMapCopy();
    ~KMapCopy();

    void Activate();

    BOOL RegisterCGCallbackPlayer( DWORD dwPlayerID, int nX, int nY, int nZ);

    BOOL UnregisterCGCallbackPlayer(DWORD dwPlayerID);

    BOOL ClearCGCallbackPlayer()
    {
        m_CGCallbackList.clear();
        return true;
    }

    BOOL CanReset();

    BOOL Save(BYTE* pbyBuffer, size_t uBufferSize, size_t* puUsedSize);
    BOOL Load(BYTE* pbyData, size_t uDataLen);

    BOOL RegisterKeepPlayer(DWORD dwPlayerID);
    BOOL UnRegisterKeepPlayer(DWORD dwPlayerID);
    BOOL IsPlayerKeeped(DWORD dwPlayerID);

    int                             m_nCopyIndex;
    KMAP_COPY_STATE	                m_eState;	               // ��ͼ����״̬
    BOOL                            m_bAutoDelete;             // �Ƿ�Ҫ�Զ�ɾ��
    time_t                          m_nCreateTime;             // �����Ĵ���ʱ��
    time_t                          m_nUnloadTime;             // ��������������ʱ,���ֵ�ʲôʱ��Ϊֹ
    time_t                          m_nRefreshTime;            // ��������ʲôʱ��ʼ����
    time_t                          m_nLastSaveTime;           // ���һ�α���ʱ��
    int				                m_nConnIndex;		       // ������ͼ������GS�����Ӻ�
    int			                    m_nPlayerCount;	           // �����Ÿ����е������Ŀ
    int                             m_nMinPlayerCount;         // �����Ÿ�����������Ҫ�������

    DWORD			                m_dwOwnerID;		       // ����ӵ���ߵĽ�ɫID
    KMAP_COPY_PLAYER_LIST           m_PlayerList;              // ӵ�и�������Ȩ�޵�����б�  
    IMemBlock*                     m_piSceneData;             // ������������,���������Զ������ݺͳ�����������
    BOOL                            m_bIsChanged;              // ӵ���ߺ͵�ͼ�����Ƿ�ı�   

    KCREATE_MAP_CG_CALLBACK_LIST    m_CGCallbackList;          // ��ͼ���������еȴ��Ŀ��ͼ����б�

    DWORD                           m_dwQueueID;               // ����ID 
    time_t                          m_nLastTryLoginTime;       // ��һ�γ��Ե�¼��ʱ��

    KMAP_COPY_PLAYER_KEEP_LIST      m_KeepList;

    //DECLARE_LUA_CLASS(KMapCopy);
    //DECLARE_LUA_INTEGER(CopyIndex);
    //DECLARE_LUA_TIME(CreateTime);
    //DECLARE_LUA_TIME(UnloadTime);
    //DECLARE_LUA_TIME(RefreshTime);
    //DECLARE_LUA_INTEGER(ConnIndex);
    //DECLARE_LUA_INTEGER(PlayerCount);
    //DECLARE_LUA_INTEGER(MinPlayerCount);
    //DECLARE_LUA_DWORD(OwnerID);
    //DECLARE_LUA_DWORD(QueueID);
};



