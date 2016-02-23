Instance.MOVIE_DIALOG = 1;
Instance.DO_SCRIPT	  = 2;		-- ִ�нű�
Instance.ADD_NPC      = 3;
Instance.BLACK_MSG	= 4;	-- ������ģ 	
Instance.TARGET_INFO	= 5;	-- Ŀ����Ϣ 
Instance.DEL_NPC 	= 6;
Instance.NPC_BUBBLE = 8;
Instance.ME_BUBBLE = 9;
Instance.CHANGE_TRAP = 10;
Instance.HOOK_TRAP = 11;
Instance.TIME_INFO = 12;
Instance.SHOW_REWARD_PANEL = 13;
Instance.SET_TASK = 14;
Instance.REVIVE_INFO = 15;
Instance.CLEAR_BUFF = 16;
Instance.NOVICE_GUIDE = 17;
Instance.SHOW_NOTICE_MSG = 18;
Instance.SHOW_NOTICE_STATE = 19;
Instance.REMOVE_NOTICE_STATE = 20;
Instance.UNLOCK_GOD = 21;

Instance.END_TIME = 1800;	-- 30���Ӻ��Զ��رո���


Instance.tbBeginPos = {}

Instance.UNLOCK_GOD_GID = 5004;
Instance.UNLOCK_GOD_STEP = 1;
Instance.UNLOCK_GOD_START = 2;

Instance.FINISH_TASK_GID = 2070;
Instance.LAST_FINISH_DAY = 1;
Instance.FINISH_TASK_ID = 2;

Instance.TIMES_FULL_REWARD = 6;

Instance.REMAIN_INSTANCE_COUNT_GID = 2080; -- ���ʣ�ั������
Instance.REMAIN_INSTANCE_COUNT_ID = 1; -- ���ʣ�ั������ID
Instance.REMAIN_INSTANCE_COUNT_DAY_ID = 2; -- ʣ�ั���������ڣ������ĵ���ÿ����Ҫ������Ӧ����

Instance.CURRENT_SWEEP_TASK_GID = 2081; -- ��¼��ǰ����ɨ���ĸ�����Ϣ
Instance.CURRENT_SWEEP_INSTANCE_ID = 1; -- ɨ������ID
Instance.CURRENT_SWEEP_START_TIME = 2; -- ��ʼʱ��
Instance.CURRENT_SWEEP_COUNT = 3; -- ��ǰ����ɨ�������ܴ���
Instance.CURRENT_SWEEP_FINISH_COUNT = 4; -- ��ǰ��ɵ�ɨ����������
Instance.CURRENT_SWEEP_FINISH = 5; -- ��ǰɨ���Ƿ��Ѿ����
Instance.CURRENT_SWEEP_SPEED_COUNT = 6; -- ��ǰɨ���ӵڼ�������
Instance.CURRENT_SWEEP_IS_SPEED = 7; -- ��ǰɨ���Ƿ����
Instance.TOTAL_SWEEP_FINISH_COUNT = 8; -- �ܹ���ɵ�ɨ������
Instance.CURRENT_SWEEP_TIMER_ID = 9; -- ��ʱ��id
Instance.CURRENT_INSTANCE_FINISH = 10; -- ���븱���Ƿ����

Instance.MAX_SWEEP_COUNT = 360; -- ����ɨ��������������
Instance.MAX_AUTO_ADD_COUNT = 120; -- ÿ����Ȼ���������޴���
Instance.DAY_AUTO_ADD_COUNT = 40; -- ÿ����Ȼ�����Ĵ���
Instance.SWEEP_ONCE_TIME = 2 * 60; -- ɨ������������ʱ�䣬��λΪ�룬�����ĵ����̶�Ϊ2����

Instance.BUY_NEED_COIN = 10;	--����һ�δ�����Ҫ��Ԫ��
Instance.UNLOCK_GOD_TOTAL_STEP = 4;	--����������ȫ������
-- �뿪��
Instance.LEAVE_POS =
{
	--[1] = {1648, 3185},
	100, 3120, 7152, 1048576
}

------------------------------------------------------------------------------------------------------------------------
-- ͨ��������

Instance.tbInstanceAward = {};
Instance.tbTaskInstanceAward = {};
local tbInstanceAward = Instance.tbInstanceAward;
local tbTaskInstanceAward = Instance.tbTaskInstanceAward;

function Instance:LoadInstanceAward()
	local tbFileData = Lib:LoadTabFile("/setting/award/instanceaward.txt")
	for _, tbRow in pairs(tbFileData) do
		local nMapId = tonumber(tbRow.MapId);
		assert(nMapId);
		if not tbInstanceAward[nMapId] then
			tbInstanceAward[nMapId] = {};
		end
		local tbInfo = tbInstanceAward[nMapId];
		tbInfo[tonumber(tbRow.Level)] = {
			ExpAward = tonumber(tbRow.ExpAward);
			CoinAward = tonumber(tbRow.CoinAward);
			ItemGerne = tonumber(tbRow.ItemGerne);
			ItemDetail = tonumber(tbRow.ItemDetail);
			ItemParticularType = tonumber(tbRow.ItemParticularType);
			ItemLevel = tonumber(tbRow.ItemLevel);
		};
	end
end

function Instance:LoadTaskInstanceAward()
	local tbFileData = Lib:LoadTabFile("setting/award/instancetaskaward.txt");
	for _, tbRow in pairs(tbFileData) do
		local nMapId = tonumber(tbRow.InstanceId);
		assert(nMapId);
		if not tbTaskInstanceAward[nMapId] then
			tbTaskInstanceAward[nMapId] = {};
		end
		local tbInfo = tbTaskInstanceAward[nMapId];
		tbInfo[tbRow.SlotNum] = {};
		local tbSlotAward = tbInfo[tbRow.SlotNum];
		tbSlotAward.Type = tonumber(tbRow.Type);
		tbSlotAward.Value = tbRow.Value;
	end
end

function Instance:Init()
	Instance:LoadInstanceAward();
	Instance.LoadTaskInstanceAward();
end

Instance:Init();

