#ifndef _KRECORDDEF_H_
#define _KRECORDDEF_H_

enum KE_RECORD_ID
{
	emRecordIdBegin = 0,

	emRecordKinBattle = 1,		// ����ս������ʼ�¼
	emRecordKinBattleWinnerId,			// ��ǰ�������
	emRecordLastWinKinInfo,			// ���һ��Ӯ�������Լ����¼
	emRecordBankInvest,			//ǮׯͶ�ʼ�¼(30����)
	emRecordBuyAllPurchase,		//�̵�ȫ���޹�
	emRecordServerStartTime,		// ����ʱ��
	emRecordOpenServerData,         //��������
	emRecordIdEnd,
};

#endif	// _KRECORDDEF_H_