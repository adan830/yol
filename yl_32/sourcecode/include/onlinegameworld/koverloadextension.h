
#pragma once
// -------------------------------------------------------------------------
class KCharacter;
class KPlayer;
class KNpc;

namespace KNSBASE_EXT
{
	// Npc��ʼ��ʱ
	extern BOOL (*DoNpcInit)(KNpc& rcNpc);

	// DoingЭ����ˣ�return FALSE��ʾЭ�鲻ͨ��
	extern BOOL (*DoingProtocolFilter[])(KPlayer& rcPlayer, LPCBYTE pbyData, UINT uDataLen);
};

