
#pragma once

class KCharacter;
// -------------------------------------------------------------------------
class KCharacterCtrlBase
{
public:
	KCharacterCtrlBase(KCharacter& rcCharacter) 
		: m_rcCharacter(rcCharacter)
	{}
	virtual ~KCharacterCtrlBase() {}

	virtual BOOL Init() = 0;
	virtual BOOL UnInit() = 0;
	virtual BOOL OnLogin() { return TRUE; }
	virtual BOOL OnLogout() { return TRUE; }
	virtual BOOL Active() {return TRUE;}

#ifdef GAME_SERVER
	// ���̹��ܣ���playerctrldbdef���岢��������ʵ����Ժ������Ϳ��Բ�����̺Ͷ��̣�
	virtual BOOL OnDbLoad(LPCBYTE pData, SIZE_T uSize)
	{ Q_Error("ָ���˸�CtrlҪ���̣�����ȴδʵ�֣�"); return FALSE; }
	virtual BOOL OnDbSave(LPBYTE pBuffer, SIZE_T uBuffSize, SIZE_T& uUsedSize)
	{ Q_Error("ָ���˸�CtrlҪ���̣�����ȴδʵ�֣�"); return FALSE; }

	virtual BOOL OnClientReady() { return TRUE; }
#endif

	KCharacter& m_rcCharacter;
};
// -------------------------------------------------------------------------

