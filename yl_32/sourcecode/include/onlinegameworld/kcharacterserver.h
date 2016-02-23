
#pragma once

#ifdef GAME_SERVER
class KCharacter;
class KPlayerProtocolProcessor;
// -------------------------------------------------------------------------
class KCharacterServer
{
public:
	KCharacterServer(KCharacter& rCharacter) : m_rcCharacter(rCharacter) {};
	// ͬ��������������Χ���
	BOOL SyncVarAround(WORD wVarGroup, WORD wVarId);
	// �㲥��������� (bIncludeHimself�Ƿ�㲥�����Լ��Ŀͻ���)
	BOOL BroadcastNearby(LPCVOID pbyData, SIZE_T uSize,
		BOOL bIncludeHimself, KPlayerProtocolProcessor* pProtocolSender = NULL);
	// �㲥������ͼ��� (bIncludeHimself�Ƿ�㲥�����Լ��Ŀͻ���)
	BOOL BroadcastScene(LPCBYTE pbyData, SIZE_T uSize,
		BOOL bIncludeHimself, KPlayerProtocolProcessor* pProtocolSender = NULL);

	// �㲥������������ �����������pPlayerToExclude
	static BOOL BroadcastThisServer(LPCBYTE pbyData, SIZE_T uSize, 
		KCharacter* pPlayerToExclude, KPlayerProtocolProcessor* pProtocolSender = NULL);

	// ����ͬ������ͬ�������ı�
	BOOL SyncVarChange(WORD wVarGroup, WORD wVarId);
	VOID SetVisible(BOOL bVisible);
	VOID SetSkillHidden(BOOL bHidden);

	BOOL SyncActionAround(INT nActionId, INT nPendantId);
private:
	virtual BOOL DoSyncVarSelf(WORD wVarGroup, WORD wVarId) { return TRUE; }
protected:
	KCharacter& m_rcCharacter;
};

// -------------------------------------------------------------------------
#endif // #ifdef GAME_SERVER
