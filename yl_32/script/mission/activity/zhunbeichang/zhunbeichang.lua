Include("script/mission/activity/activitystep.lua")
Include("script/mission/activity/activitydef.lua")

Activity.ZHUNBEICHANG = Lib:NewClass(Activity.ActivityStep);

Activity.ACTSTEP_FACTORY[Activity.STEP_TYPE.ZHUNBEICHANG] = Activity.ZHUNBEICHANG -- ע�ᵽ�����

local ZHUNBEICHANG = Activity.ZHUNBEICHNAG