#ifndef _QPURSEDEF_H__
#define _QPURSEDEF_H__

#define TIMESPAN_TABLE_FILE                 "\\setting\\purse\\free_time_span.txt"
#define EXCHANGE_RATE						"\\setting\\purse\\exchange_rate.txt"
#define MAX_BOWL_TIME_SPAN     1200

enum BOWL_REQUEST_STYPE
{
	emInit = 0,			//ͬ��
	emFree = 1,			//��ѻ�ȡ
	emCoin = 2			//Ԫ����ȡ
};

#endif