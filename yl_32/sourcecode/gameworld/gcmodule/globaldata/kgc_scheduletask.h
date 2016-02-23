/* -------------------------------------------------------------------------
//	�ļ���		��	kgc_scheduletask.h
//	������		��	luobaohang
//	����ʱ��	��	2007-3-12 14:32:58
//	��������	��	ʱ������ϵͳ
//
// -----------------------------------------------------------------------*/
#ifndef __KGC_SCHEDULETASK_H__
#define __KGC_SCHEDULETASK_H__

#include <vector>

#define KDF_GC_SCHEDULETASKINI	"\\setting\\scheduletask\\tasklist.ini"
#define MAX_TASK_SIZE 100
#define MAX_TIME_NUM 100
#define KD_MAX_DYN_TASK_NUM 32	// ��̬ע��������������
#define KD_MAX_TASKNAME_SIZE	64
#define KD_MAX_GROUPNAME_SIZE	128
#define KD_MAX_SCRIPTFUN_NAME_SIZE	128
#define KD_MAX_SPAN_MIN	10	// ����ȷ�����

// -------------------------------------------------------------------------
class KGC_ScheduleTask
{
	struct KTaskDef
	{
		CHAR szTaskName[KD_MAX_TASKNAME_SIZE];
		CHAR szGroupName[KD_MAX_GROUPNAME_SIZE];	// �ű�������
		CHAR szScriptFun[KD_MAX_SCRIPTFUN_NAME_SIZE];	// �ű�������
	};
	struct KTaskInfo 
	{
		INT nTime;	// ִ��ʱ��
		INT nSeqNum; // ִ�����
		KTaskDef *pTaskDef;	// ����
		BOOL operator < (CONST KTaskInfo &r)CONST { return nTime < r.nTime; }
	};
public:
	KGC_ScheduleTask()
	{ m_nLoop = m_nCurPos = m_nLastHourMin = -1; m_nDynTaskNum = 0; }
	// ��̬���һ�����񣬷��ض�̬����ID����1��ʼ����ʧ�ܷ���0
	INT AddDynTask(LPCSTR szTaskName, LPCSTR szGroupName, LPCSTR szScriptFun);
	// ��̬ע��һ��ʱ�������nDynTask����Ϊ�Ѷ�̬��ӵ�����Id
	BOOL ResterTimeTask(INT nDynTask, INT nHourMin, INT nSeqNum);

	BOOL	ExecTask(CONST KTaskDef &Task, INT nSeqNum);
	virtual BOOL Breath();
	virtual BOOL Init();
protected:
	std::vector<KTaskInfo> m_vecTask;
	KTaskDef m_Task[MAX_TASK_SIZE];
	KTaskDef m_DynTask[KD_MAX_DYN_TASK_NUM];
	INT m_nDynTaskNum;	// ��ǰ��̬ע����������
	INT m_nCurPos;		// ��һ����Ҫִ�е������±�
	INT m_nLastHourMin;	// ��һ��Breath��ʱ��
	INT m_nLoop;
private:
};
extern KGC_ScheduleTask g_ScheduleTask;
// -------------------------------------------------------------------------

#endif /* __KGC_SCHEDULETASK_H__ */
