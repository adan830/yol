/* -------------------------------------------------------------------------
//	�ļ���		��	KCell.h
//	������		��	xiewen
//	����ʱ��	��	2009-9-23 16:43:35
//	��������	��	
//
// -----------------------------------------------------------------------*/
#ifndef __KCELL_H__
#define __KCELL_H__

// -------------------------------------------------------------------------
#include "onlinegameworld/scene_def.h"

#pragma pack(push, 1)

enum CELL_TYPE
{
	ctPlain = 0,
	ctWater,
	ctIce,
    ctWaterArea,
	ctTotal,
	ctForceDWORD = 0x7fffffff
};

struct KCell
{
public:
	struct KBaseInfo
	{
		DWORD		dwCellType			:	2;		// �ر�����		
		DWORD		dwIndoor			:	1;		// �Ƿ�����
		DWORD		dwPassWidth			:	3;		// ͨ��������
		DWORD		dwGradientDirection :   3;		// ��������,8������,�ϲ�ʱȡ���
		DWORD		dwGradientDegree    :	3;		// �¶�,��λ: 90��Բ����1/8,�ϲ�ʱȡ��ϵ�,����90��ȡ����
		DWORD		dwBarrierDirection  :	3;		// �ϰ�����,��λ: 180��Բ����1/8,�ϲ�ʱȡ��б����
		DWORD		dwFaceUp			:	1;		// �Ƿ������ϣ����ڱ༭ʱ�ϲ�CELL
		DWORD		dwDynamic			:	1;		// �Ƿ�̬Cell

		DWORD		dwNoObstacleRange	:	6;		// ���ϰ���Χ
		DWORD		dwScriptIndex		:	4;		// �ű�����
		DWORD		dwPutObj			:	1;		// �ɰڷ�	
		DWORD		dwRest				:	1;		// �Ƿ�����Ϣ��
		DWORD		dwStall			    :	1;		// �Ƿ�ɰ�̯
		DWORD		dwRideHorse		    :	1;		// �Ƿ�����
		DWORD		dwBlockCharacter	:	1;		// �ϰ���Ϣ
	} m_BaseInfo;

	WORD    m_wLowLayer;					// �²�߶�(�Ժ�ƽ��Ϊ��׼)
	WORD    m_wHighLayer;					// �ϲ�߶�(�Ժ�ƽ��Ϊ��׼)
	KCell*  m_pNext;						// ��Ƭ����

	inline void SetGradientDegree(int nDegree)
	{ 
		ASSERT(nDegree >= 0 && nDegree < DIRECTION_COUNT / 4);
		m_BaseInfo.dwGradientDegree = nDegree / (DIRECTION_COUNT / 4 / 8);
	}

	inline int GetGradientDegree()
	{ 
		return m_BaseInfo.dwGradientDegree * DIRECTION_COUNT / 4 / 8; 
	}

	inline void SetGradientDirection(int nDirection)
	{ 
		ASSERT(nDirection >= 0 && nDirection < DIRECTION_COUNT);
		m_BaseInfo.dwGradientDirection = nDirection / (DIRECTION_COUNT / 8);
	}

	inline int GetGradientDirection()
	{ 
		return m_BaseInfo.dwGradientDirection * DIRECTION_COUNT / 8; 
	}

	inline void SetBarrierDirection(int nDirection)
	{ 
		ASSERT(nDirection >= 0 && nDirection < DIRECTION_COUNT);
		if (nDirection >= DIRECTION_COUNT / 2)
		{
			nDirection -= DIRECTION_COUNT / 2;
		}
		m_BaseInfo.dwBarrierDirection = nDirection / (DIRECTION_COUNT / 2 / 8);
	}

	inline int GetBarrierDirection()
	{ 
		return m_BaseInfo.dwBarrierDirection * DIRECTION_COUNT / 2 / 8; 
	}

	//inline void SetWaterFlowSpeed(int nSpeed)
	//{
	//}

	//inline int GetWaterFlowSpeed()
	//{
	//	return 0;
	//}

	//inline void SetWaterFlowDirection(int nDirection)
	//{
	//}

	//inline int GetWaterFlowDirection()
	//{
	//	return 0;
	//}

	//inline int GetStaticFrictionCoefficient()
	//{
	//	ASSERT(false);
	//	return 0;
	//}

	//inline int GetDynamicFrictionCoefficient()
	//{
	//	const int nDynamicFrictionCoefficients[ctTotal] = {768, 0, 128};
	//	return nDynamicFrictionCoefficients[m_BaseInfo.dwCellType];
	//}

	//inline int GetCriticalSlipSpeed()
	//{
	//	const int nCriticalSlipSpeed[ctTotal] = {24, 0, 10};
	//	return nCriticalSlipSpeed[m_BaseInfo.dwCellType];
	//}  

	inline BOOL CheckSlip()
	{
		const int nCriticalGradientDegree[ctTotal]  = {4, 8, 1};
		int       nCellType                         = m_BaseInfo.dwCellType;
		int       nGradientDegree                   = m_BaseInfo.dwGradientDegree;

		// ½�ع�45�ȴ�,ˮ�治�����жϴ�(Ҫ�ж�ˮ�׵ر�Ĵ�),������Զ��
		if (nCellType == ctWater)
		{
			return false;
		}

		if (nCellType == ctIce)
		{
			return true;
		}

		return nGradientDegree >= nCriticalGradientDegree[nCellType];
	}

};

struct KDynamicCell : KCell 
{
	WORD m_wGroupIndex;
};

#pragma pack(pop)
// -------------------------------------------------------------------------

#endif /* __KCELL_H__ */
