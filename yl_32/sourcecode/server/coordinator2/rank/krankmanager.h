
#pragma once

#include "ProtocolBasic.h"
#include "krankpool.h"
#include "config/gamedef.h"

class KRankManager
{
public:
    KRankManager();

    BOOL Init();
    void UnInit();

    void Activate();

	void SaveAll();

	BOOL LoadRankData(INT nRankId, BYTE* pbyData, size_t uRankDataLen);

	KRankPool* GetRankPool(INT nRankId);

	BOOL ModifyRankValue(INT nRankId, DWORD dwId, DWORD dwValue, DWORD dwModifyTime = 0);

	BOOL EraseRankValue(INT nRankId, DWORD dwId);				//Ĩȥ��dwid�����а���Ϣ

	//BOOL SaveRankForOpenService(int OpenServiceDay);			//���ݿ��������������а�
private:
	BOOL CreateRankPool(INT nPoolId, INT nMaxCount);

	INT GetPoolMaxCount(INT nRankId);

private:

	typedef std::map<DWORD, KRankPool>  KRANK_TABLE;

	KRANK_TABLE                     m_RankTable;
};