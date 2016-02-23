
#pragma once

#include <map>
// -------------------------------------------------------------------------
// ��16λΪGroupId����16λΪValueId
enum KE_GLOBAL_DATA_KEY
{
	// ---------------------------------------------------------------------
	// ����ϵͳȫ�ֱ���
	emKGLOBAL_DATA_TASK_BEGIN									= 0x00000000,
	emKGLOBAL_DATA_TASK_ACCUM_BEGIN								= 0x00000001,
	emKGLOBAL_DATA_TASK_ACCUM_END								= 0x00001000,
	emKGLOBAL_DATA_RECOMMEND_BEGIN								= 0x00001001,
	emKGLOBAL_DATA_RECOMMEND_END								= 0x00001014,


	// ---------------------------------------------------------------------
	// ��ᷢչˮƽ
	emKGLOBAL_DATA_SOCIETY_RANK_BEGIN							= 0x00010000,
	emKGLOBAL_DATA_SOCIETY_RANK_VALUE							= 0x00010001,
	emKGLOBAL_DATA_SOCIETY_RANK_VERSION							= 0x00010002,
	emKGLOBAL_DATA_SOCIETY_RANK_SUM_LOW32						= 0x00010003,
	emKGLOBAL_DATA_SOCIETY_RANK_SUM_HIGH32						= 0x00010004,
	emKGLOBAL_DATA_SOCIETY_RANK_CNT								= 0x00010005,

	//����ϵͳ
	emKGLOBAL_DATA_STORY_BEGIN									= 0x00020000,
	emKGLOBAL_DATA_STORY_SRV_INIT_TIME							= 0x00020001,
	emKGLOBAL_DATA_STORY_END									= 0x00020002,
};

// ��Ҫ�浵�ķ�Χ
struct KGlobalDataRange 
{
	DWORD dwBegin;
	DWORD dwEnd;
};

const static KGlobalDataRange csNeedSaveValue[] = 
{
	// ����
	{emKGLOBAL_DATA_TASK_ACCUM_BEGIN,			emKGLOBAL_DATA_TASK_ACCUM_END,},
	{emKGLOBAL_DATA_RECOMMEND_BEGIN,			emKGLOBAL_DATA_RECOMMEND_END},

	// ���ˮƽ
	{emKGLOBAL_DATA_SOCIETY_RANK_VERSION,		emKGLOBAL_DATA_SOCIETY_RANK_VERSION},
	{emKGLOBAL_DATA_SOCIETY_RANK_SUM_LOW32,		emKGLOBAL_DATA_SOCIETY_RANK_SUM_LOW32},
	{emKGLOBAL_DATA_SOCIETY_RANK_SUM_HIGH32,	emKGLOBAL_DATA_SOCIETY_RANK_SUM_HIGH32},
	{emKGLOBAL_DATA_SOCIETY_RANK_CNT,			emKGLOBAL_DATA_SOCIETY_RANK_CNT},

	//����ϵͳ
	{emKGLOBAL_DATA_STORY_SRV_INIT_TIME,		emKGLOBAL_DATA_STORY_SRV_INIT_TIME},
};

static std::map<DWORD, DWORD> s_mapNeedSaved;
BOOL s_init_save_map()
{
	for (UINT i = 0; i < countof(csNeedSaveValue); ++i)
	{
		QCONFIRM_RET_FALSE(csNeedSaveValue[i].dwEnd >= csNeedSaveValue[i].dwBegin);
		s_mapNeedSaved[csNeedSaveValue[i].dwBegin] = csNeedSaveValue[i].dwEnd - csNeedSaveValue[i].dwBegin + 1;
	}

	for (std::map<DWORD, DWORD>::iterator it = s_mapNeedSaved.begin(); it != s_mapNeedSaved.end(); ++it)
	{
		std::map<DWORD, DWORD>::iterator itNext = it;
		++itNext;
		if (itNext == s_mapNeedSaved.end())
			break;

		QCONFIRM_RET_FALSE(it->first + it->second <= itNext->first);
	}

	return TRUE;
}

static BOOL s_need_save(DWORD dwKey)
{
	std::map<DWORD, DWORD>::iterator itUp = s_mapNeedSaved.upper_bound(dwKey);
	if (itUp == s_mapNeedSaved.begin())
		return FALSE;

	if (--itUp == s_mapNeedSaved.end())
		return FALSE;

	return dwKey >= itUp->first && dwKey <= (itUp->first + itUp->second);
}


