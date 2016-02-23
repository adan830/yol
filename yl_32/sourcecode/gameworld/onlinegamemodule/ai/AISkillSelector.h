// ����ѡ�����

class KNpc;
class KSkill;

// �������͵ļ���ѡ�����ķ���ֵ����������������
#define SKILL_SELECTOR_IGNORE       0   // ���ͷ�
#define SKILL_SELECTOR_CAST         1   // �ͷ�
#define SKILL_SELECTOR_CAST_SPECIAL 2   // �ͷ�,����Ŀ��(�ǵ�һ���)
#define SKILL_SELECTOR_READY        3   // �����ݸ��ʾ��� 

int StandardTargetPeriodEvaluator(KNpc* pNpc, KTarget* pTarget);
int StandardTargetPeriodRangeEvaluator(KNpc* pNpc, KTarget* pTarget);
int StandardSelfPeriodEvaluator(KNpc* pNpc, KTarget* pTarget);
int StandardPassiveRespond(KNpc* pNpc, KTarget* pTarget);
int StandardSelfHPEvaluator(KNpc* pNpc, KTarget* pTarget, int nLifeRate);
int StandardTargetCountEvaluator(KNpc* pNpc, KTarget* pTarget, int nSkillRate);
int StandardChannelingBreak(KNpc* pNpc, KTarget* pTarget, int nSkillRate);
int StandardNThreat(KNpc* pNpc, KTarget* pTarget, THREAT_TYPE eThreatType, int nThreatIndex);
int StandardRandomTargetByBase(KNpc* pNpc, KTarget* pTarget, BOOL bExceptSelectTarget);
int StandardRandomTargetByRange(KNpc* pNpc, KTarget* pTarget, int nMinRange, int nMaxRange, BOOL bExceptSelectTarget);
int StandardRandomTargetByNearest(KNpc* pNpc, KTarget* pTarget, BOOL bExceptSelectTarget);

// ����Ϊ�������ѡ��Ŀ�꺯��(��ʱ����TargetGroup)
BOOL FilterTargetGroupByBase(KCharacter* pSelf, BOOL bExceptSelectTarget);
BOOL FilterTargetGroupByRange(KCharacter* pSelf, BOOL bExceptSelectTarget, int nMinRange, int nMaxRange);
BOOL FilterTargetGroupByNearest(KCharacter* pSelf, BOOL bExceptSelectTarget);
