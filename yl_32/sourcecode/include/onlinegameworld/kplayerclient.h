
#pragma once

#ifdef GAME_CLIENT
#include "onlinegameworld/kcharacterclient.h"

class KPlayer;

// -------------------------------------------------------------------------
// ��ҿͻ�����չ����������ͻ�����ң��������ͻ��˵�������ң�
class KPlayerClient : public KCharacterClient
{
public:
	KPlayerClient(KPlayer& rcPlayer);;

	BOOL DoGoTo(INT nX, INT nY, INT nZ, INT nMoveMode);
	BOOL SwitchMoveMode(INT nRun);
	BOOL DoRequestOffline();
	BOOL DoJump();
	BOOL MoveCtrl(BOOL bWalk, BOOL bForward, BOOL bBackward, BOOL bLeft, BOOL bRight, INT nCamDirection); // TODO: ��Ӧ�÷����߼���
	BOOL DoMoveCtrl(BOOL bMove, BOOL bWalk, INT nDirection);
	BOOL DoDialogDoodad(DWORD dwDoodadId);

	//��������NPC�Ự
	BOOL DoApplyNpcTalk(KPlayer& rPlayer, DWORD dwNpcId);

	INT DynamicSceneFlag() const { return m_nDynamicSceneFlag; }
	void DynamicSceneFlag(INT val) { m_nDynamicSceneFlag = val; }
protected:
	KPlayer& m_rcPlayer;
	INT m_nDynamicSceneFlag; // ��ʱ
private:
};

// -------------------------------------------------------------------------
#endif // #ifdef GAME_CLIENT

