Include("script/mission/activity/activitystep.lua")
Include("script/mission/activity/activitydef.lua")

Activity.ZHANBAOTANG_ZHUNBEICHANG = Lib:NewClass(Activity.ActivityStep);

Activity.ACTSTEP_FACTORY[Activity.STEP_TYPE.ZHANBAOTANG_ZHUNBEICHANG] = Activity.ZHANBAOTANG_ZHUNBEICHANG -- ע�ᵽ�����

--local ZHANBAOTANG_ZHUNBEICHANG = Activity.ZHANBAOTANG_ZHUNBEICHANG
