-- ��ħ����7��������ļ�

Include("script/mission/tower/tower_def.lua")
if not Tower.tbSetting then
	Tower.tbSetting = {}
end

local TowerSetting = Tower.tbSetting;

TowerSetting[61]=
{
	nTimeLimit = 180,  --����ʱ��5����
	nMapId = 242,
	nEnemyNum = 8,
    tbBeginPos = {1078, 1016, 1048576},

    -- �����漰��NPC����
	NPC =
	{
	-- 		���  	npcģ��				�ȼ�(-1Ĭ�����npcpro��)	5��(Ĭ��-1)
        [1] = {nTemplate = 8001, nLevel = -1, nSeries = -1},		-- С��
	},

    LOCK =
    {
       -- 1�������ܲ��Ĭ��1��Ϊ��ʼ��
		[1] = {nTime = 3, nNum = 0,		-- �ܼ�ʱ
			tbPrelock = {},
			tbStartEvent =
			{
			    {Tower.TIME_INFO, Lang.mission.str989[Lang.Idx],1},
			},
			tbUnLockEvent =
			{
			},
		},
		[2] = {nTime = 0, nNum = 8 ,		-- ��ͨ����������ʱ�䵹��ʱ��ɱ�ָ�����
			tbPrelock = {1},
			tbStartEvent =
			{
				{Tower.TIME_INFO, Lang.mission.str990[Lang.Idx]},
				{Tower.TARGET_INFO, Lang.mission.str1237[Lang.Idx], 2}, --�������
				{Tower.ADD_NPC, 1, 2, 2, "1", "leftshang"},     --ħ��
				{Tower.ADD_NPC, 1, 2, 2, "1", "leftxia"},  		--ħ��
				{Tower.ADD_NPC, 1, 2, 2, "1", "rightshang"},    --ħ��
				{Tower.ADD_NPC, 1, 2, 2, "1", "rightxia"},      --ħ��
			},
			tbUnLockEvent =
			{
			},
		},

		[3] = {nTime = 3, nNum = 0 ,		-- �ܼ�ʱ
			tbPrelock = {2},
			tbStartEvent =
			{
				{Tower.TARGET_INFO, Lang.mission.str991[Lang.Idx]},
				{Tower.TIME_INFO, Lang.mission.str992[Lang.Idx], 3},
			},
			tbUnLockEvent =
			{
				{Tower.DO_SCRIPT, "self.bFinishLayer = 1"},
			},
		}
    }
}


TowerSetting[62]=
{
	nTimeLimit = 180,
	nMapId = 242,
	nEnemyNum = 8,
    tbBeginPos = {1078, 1016, 1048576},

    -- �����漰��NPC����
	NPC =
	{
-- 		���  	npcģ��				�ȼ�(-1Ĭ��)	5��(Ĭ��-1)
        [1] = {nTemplate = 8011, nLevel = -1, nSeries = -1},		-- С��
	},

    LOCK =
    {
       -- 1�������ܲ��Ĭ��1��Ϊ��ʼ��
		[1] = {nTime = 3, nNum = 0,		-- �ܼ�ʱ
			tbPrelock = {},
			tbStartEvent =
			{
			    {Tower.TIME_INFO, Lang.mission.str989[Lang.Idx],1},
			},
			tbUnLockEvent =
			{
			},
		},
		[2] = {nTime = 0, nNum = 8 ,		-- �ܼ�ʱ
			tbPrelock = {1},
			tbStartEvent =
			{
				{Tower.ADD_NPC, 1, 2, 2, "2", "leftshang"},     --������
				{Tower.ADD_NPC, 1, 2, 2, "2", "leftxia"},  		--������
				{Tower.ADD_NPC, 1, 2, 2, "2", "rightshang"},    --������
				{Tower.ADD_NPC, 1, 2, 2, "2", "rightxia"},      --������
				
				{Tower.TARGET_INFO, Lang.mission.str1238[Lang.Idx], 2},
				{Tower.TIME_INFO, Lang.mission.str990[Lang.Idx]},
			},
			tbUnLockEvent =
			{
			},
		},
		[3] = {nTime = 3, nNum = 0 ,		-- �ܼ�ʱ
			tbPrelock = {2},
			tbStartEvent =
			{
				{Tower.TARGET_INFO, Lang.mission.str991[Lang.Idx]},
				{Tower.TIME_INFO, Lang.mission.str992[Lang.Idx], 3},
			},
			tbUnLockEvent =
			{
				{Tower.DO_SCRIPT, "self.bFinishLayer = 1"},
			},
		}
    }
}

TowerSetting[63]=
{
	nTimeLimit = 180,
	nMapId = 242,
	nEnemyNum = 8,
    tbBeginPos = {1078, 1016, 1048576},

    -- �����漰��NPC����
	NPC =
	{
-- 		���  	npcģ��				�ȼ�(-1Ĭ��)	5��(Ĭ��-1)
        [1] = {nTemplate = 8021, nLevel = -1, nSeries = -1},		-- С��
	},

    LOCK =
    {
       -- 1�������ܲ��Ĭ��1��Ϊ��ʼ��
		[1] = {nTime = 3, nNum = 0,		-- �ܼ�ʱ
			tbPrelock = {},
			tbStartEvent =
			{
			   {Tower.TIME_INFO, Lang.mission.str989[Lang.Idx],1},
			},
			tbUnLockEvent =
			{
			},
		},
		[2] = {nTime = 0, nNum = 8 ,		-- �ܼ�ʱ
			tbPrelock = {1},
			tbStartEvent =
			{
				{Tower.ADD_NPC, 1, 2, 2, "2", "leftshang"},     --������
				{Tower.ADD_NPC, 1, 2, 2, "2", "leftxia"},  		--������
				{Tower.ADD_NPC, 1, 2, 2, "2", "rightshang"},    --������
				{Tower.ADD_NPC, 1, 2, 2, "2", "rightxia"},      --������
				
				{Tower.TARGET_INFO, Lang.mission.str1239[Lang.Idx], 2},
				{Tower.TIME_INFO, Lang.mission.str990[Lang.Idx]},
			},
			tbUnLockEvent =
			{
			},
		},
		[3] = {nTime = 3, nNum = 0 ,		-- �ܼ�ʱ
			tbPrelock = {2},
			tbStartEvent =
			{
				{Tower.TARGET_INFO, Lang.mission.str991[Lang.Idx]},
				{Tower.TIME_INFO, Lang.mission.str992[Lang.Idx], 3},
			},
			tbUnLockEvent =
			{
				{Tower.DO_SCRIPT, "self.bFinishLayer = 1"},
			},
		}
    }
}

TowerSetting[64]=
{
	nTimeLimit = 180,
	nMapId = 242,
	nEnemyNum = 8,
    tbBeginPos = {1078, 1016, 1048576},

    -- �����漰��NPC����
	NPC =
	{
-- 		���  	npcģ��				�ȼ�(-1Ĭ��)	5��(Ĭ��-1)
        [1] = {nTemplate = 8031, nLevel = -1, nSeries = -1},		-- С��
	},

    LOCK =
    {
       -- 1�������ܲ��Ĭ��1��Ϊ��ʼ��
		[1] = {nTime = 3, nNum = 0,		-- �ܼ�ʱ
			tbPrelock = {},
			tbStartEvent =
			{
			   {Tower.TIME_INFO, Lang.mission.str989[Lang.Idx],1},
			},
			tbUnLockEvent =
			{
			},
		},
		[2] = {nTime = 0, nNum = 8 ,		-- �ܼ�ʱ
			tbPrelock = {1},
			tbStartEvent =
			{
				{Tower.ADD_NPC, 1, 2, 2, "2", "leftshang"},     --���
				{Tower.ADD_NPC, 1, 2, 2, "2", "leftxia"},  		--���
				{Tower.ADD_NPC, 1, 2, 2, "2", "rightshang"},    --���
				{Tower.ADD_NPC, 1, 2, 2, "2", "rightxia"},      --���
				
				{Tower.TARGET_INFO, Lang.mission.str1240[Lang.Idx], 2},
				{Tower.TIME_INFO, Lang.mission.str990[Lang.Idx]},
			},
			tbUnLockEvent =
			{
			},
		},
		[3] = {nTime = 3, nNum = 0 ,		-- �ܼ�ʱ
			tbPrelock = {2},
			tbStartEvent =
			{
				{Tower.TARGET_INFO, Lang.mission.str991[Lang.Idx]},
				{Tower.TIME_INFO, Lang.mission.str992[Lang.Idx], 3},
			},
			tbUnLockEvent =
			{
				{Tower.DO_SCRIPT, "self.bFinishLayer = 1"},
			},
		}
    }
}


TowerSetting[65]=
{
	nTimeLimit = 180,
	nMapId = 242,
	nEnemyNum = 1,
    tbBeginPos = {1078, 1016, 1048576},

    -- �����漰��NPC����
	NPC =
	{
-- 		���  	npcģ��				�ȼ�(-1Ĭ��)	5��(Ĭ��-1)
        [1] = {nTemplate = 8041, nLevel = -1, nSeries = -1},	-- �ֵ�С��	
        [2] = {nTemplate = 8031, nLevel = -1, nSeries = -1},  -- С��

	},

    LOCK =
    {
       -- 1�������ܲ��Ĭ��1��Ϊ��ʼ��
		[1] = {nTime = 3, nNum = 0,		-- �ܼ�ʱ
			tbPrelock = {},
			tbStartEvent =
			{
			   {Tower.TIME_INFO, Lang.mission.str989[Lang.Idx],1},
			},
			tbUnLockEvent =
			{
			},
		},
		[2] = {nTime = 0, nNum = 1 ,		-- �ܼ�ʱ
			tbPrelock = {1},
			tbStartEvent =
			{
				{Tower.ADD_NPC, 1, 1, 2, "2", "all"},     --С��boss	
				{Tower.TARGET_INFO, Lang.mission.str1241[Lang.Idx], 2},
				{Tower.TIME_INFO, Lang.mission.str990[Lang.Idx]},
			},
			tbUnLockEvent =
			{
			},
		},
		[3] = {nTime = 3, nNum = 0 ,		-- �ܼ�ʱ
			tbPrelock = {2},
			tbStartEvent =
			{
				{Tower.TARGET_INFO, Lang.mission.str991[Lang.Idx]},
				{Tower.TIME_INFO, Lang.mission.str992[Lang.Idx], 3},
			},
			tbUnLockEvent =
			{
				{Tower.DO_SCRIPT, "self.bFinishLayer = 1"},
			},
		}
    }
}


TowerSetting[66]=
{
	nTimeLimit = 180,
	nMapId = 242,
	nEnemyNum = 8,
    tbBeginPos = {1078, 1016, 1048576},

    -- �����漰��NPC����
	NPC =
	{
-- 		���  	npcģ��				�ȼ�(-1Ĭ��)	5��(Ĭ��-1)
        [1] = {nTemplate = 8051, nLevel = -1, nSeries = -1},		-- ����
	},

    LOCK =
    {
       -- 1�������ܲ��Ĭ��1��Ϊ��ʼ��
		[1] = {nTime = 3, nNum = 0,		-- �ܼ�ʱ
			tbPrelock = {},
			tbStartEvent =
			{
			   {Tower.TIME_INFO, Lang.mission.str989[Lang.Idx],1},
			},
			tbUnLockEvent =
			{
			},
		},
		[2] = {nTime = 0, nNum = 8 ,		-- �ܼ�ʱ
			tbPrelock = {1},
			tbStartEvent =
			{
				{Tower.ADD_NPC, 1, 2, 2, "2", "leftshang"},     --����
				{Tower.ADD_NPC, 1, 2, 2, "2", "leftxia"},  		--����
				{Tower.ADD_NPC, 1, 2, 2, "2", "rightshang"},    --����
				{Tower.ADD_NPC, 1, 2, 2, "2", "rightxia"},      --����
				
				{Tower.TARGET_INFO, Lang.mission.str1242[Lang.Idx], 2},
				{Tower.TIME_INFO, Lang.mission.str990[Lang.Idx]},
			},
			tbUnLockEvent =
			{
			},
		},
		[3] = {nTime = 3, nNum = 0 ,		-- �ܼ�ʱ
			tbPrelock = {2},
			tbStartEvent =
			{
				{Tower.TARGET_INFO, Lang.mission.str991[Lang.Idx]},
				{Tower.TIME_INFO, Lang.mission.str992[Lang.Idx], 3},
			},
			tbUnLockEvent =
			{
				{Tower.DO_SCRIPT, "self.bFinishLayer = 1"},
			},
		}
    }
}


TowerSetting[67]=
{
	nTimeLimit = 180,
	nMapId = 242,
	nEnemyNum = 8,
    tbBeginPos = {1078, 1016, 1048576},

    -- �����漰��NPC����
	NPC =
	{
-- 		���  	npcģ��				�ȼ�(-1Ĭ��)	5��(Ĭ��-1)
        [1] = {nTemplate = 8061, nLevel = -1, nSeries = -1},		-- С��
	},

    LOCK =
    {
       -- 1�������ܲ��Ĭ��1��Ϊ��ʼ��
		[1] = {nTime = 3, nNum = 0,		-- �ܼ�ʱ
			tbPrelock = {},
			tbStartEvent =
			{
			   {Tower.TIME_INFO, Lang.mission.str989[Lang.Idx],1},
			},
			tbUnLockEvent =
			{
			},
		},
		[2] = {nTime = 0, nNum = 8 ,		-- �ܼ�ʱ
			tbPrelock = {1},
			tbStartEvent =
			{
				{Tower.ADD_NPC, 1, 2, 2, "2", "leftshang"},     --���
				{Tower.ADD_NPC, 1, 2, 2, "2", "leftxia"},  		--���
				{Tower.ADD_NPC, 1, 2, 2, "2", "rightshang"},    --���
				{Tower.ADD_NPC, 1, 2, 2, "2", "rightxia"},      --���
				
				{Tower.TARGET_INFO, Lang.mission.str1243[Lang.Idx], 2},
				{Tower.TIME_INFO, Lang.mission.str990[Lang.Idx]},
			},
			tbUnLockEvent =
			{
			},
		},
		[3] = {nTime = 3, nNum = 0 ,		-- �ܼ�ʱ
			tbPrelock = {2},
			tbStartEvent =
			{
				{Tower.TARGET_INFO, Lang.mission.str991[Lang.Idx]},
				{Tower.TIME_INFO, Lang.mission.str992[Lang.Idx], 3},
			},
			tbUnLockEvent =
			{
				{Tower.DO_SCRIPT, "self.bFinishLayer = 1"},
			},
		}
    }
}



TowerSetting[68]=
{
	nTimeLimit = 180,
	nMapId = 242,
	nEnemyNum = 8,
    tbBeginPos = {1078, 1016, 1048576},

    -- �����漰��NPC����
	NPC =
	{
-- 		���  	npcģ��				�ȼ�(-1Ĭ��)	5��(Ĭ��-1)
        [1] = {nTemplate = 8071, nLevel = -1, nSeries = -1},		-- С��
	},

    LOCK =
    {
       -- 1�������ܲ��Ĭ��1��Ϊ��ʼ��
		[1] = {nTime = 3, nNum = 0,		-- �ܼ�ʱ
			tbPrelock = {},
			tbStartEvent =
			{
			   {Tower.TIME_INFO, Lang.mission.str989[Lang.Idx],1},
			},
			tbUnLockEvent =
			{
			},
		},
		[2] = {nTime = 0, nNum = 8 ,		-- �ܼ�ʱ
			tbPrelock = {1},
			tbStartEvent =
			{
				{Tower.ADD_NPC, 1, 2, 2, "2", "leftshang"},     --����
				{Tower.ADD_NPC, 1, 2, 2, "2", "leftxia"},  		--����
				{Tower.ADD_NPC, 1, 2, 2, "2", "rightshang"},    --����
				{Tower.ADD_NPC, 1, 2, 2, "2", "rightxia"},      --����
				
				{Tower.TARGET_INFO, Lang.mission.str1244[Lang.Idx], 2},
				{Tower.TIME_INFO, Lang.mission.str990[Lang.Idx]},
			},
			tbUnLockEvent =
			{
			},
		},
		[3] = {nTime = 3, nNum = 0 ,		-- �ܼ�ʱ
			tbPrelock = {2},
			tbStartEvent =
			{
				{Tower.TARGET_INFO, Lang.mission.str991[Lang.Idx]},
				{Tower.TIME_INFO, Lang.mission.str992[Lang.Idx], 3},
			},
			tbUnLockEvent =
			{
				{Tower.DO_SCRIPT, "self.bFinishLayer = 1"},
			},
		}
    }
}


TowerSetting[69]=
{
	nTimeLimit = 180,
	nMapId = 242,
	nEnemyNum = 8,
    tbBeginPos = {1078, 1016, 1048576},

    -- �����漰��NPC����
	NPC =
	{
-- 		���  	npcģ��				�ȼ�(-1Ĭ��)	5��(Ĭ��-1)
        [1] = {nTemplate = 8081, nLevel = -1, nSeries = -1},		-- С��
	},

    LOCK =
    {
       -- 1�������ܲ��Ĭ��1��Ϊ��ʼ��
		[1] = {nTime = 3, nNum = 0,		-- �ܼ�ʱ
			tbPrelock = {},
			tbStartEvent =
			{
			   {Tower.TIME_INFO, Lang.mission.str989[Lang.Idx],1},
			},
			tbUnLockEvent =
			{
			},
		},
		[2] = {nTime = 0, nNum = 8 ,		-- �ܼ�ʱ
			tbPrelock = {1},
			tbStartEvent =
			{
				{Tower.ADD_NPC, 1, 2, 2, "2", "leftshang"},     --ǿ��
				{Tower.ADD_NPC, 1, 2, 2, "2", "leftxia"},  		--ǿ��
				{Tower.ADD_NPC, 1, 2, 2, "2", "rightshang"},    --ǿ��
				{Tower.ADD_NPC, 1, 2, 2, "2", "rightxia"},      --ǿ��
				
				{Tower.TARGET_INFO, Lang.mission.str1245[Lang.Idx], 2},
				{Tower.TIME_INFO, Lang.mission.str990[Lang.Idx]},
			},
			tbUnLockEvent =
			{
			},
		},
		[3] = {nTime = 3, nNum = 0 ,		-- �ܼ�ʱ
			tbPrelock = {2},
			tbStartEvent =
			{
				{Tower.TARGET_INFO, Lang.mission.str991[Lang.Idx]},
				{Tower.TIME_INFO, Lang.mission.str992[Lang.Idx], 3},
			},
			tbUnLockEvent =
			{
				{Tower.DO_SCRIPT, "self.bFinishLayer = 1"},
			},
		}
    }
}


TowerSetting[70]=
{
	nTimeLimit = 180,
	nMapId = 242,
	nEnemyNum = 1,
    tbBeginPos = {1078, 1016, 1048576},

    -- �����漰��NPC����
	NPC =
	{
-- 		���  	npcģ��				�ȼ�(-1Ĭ��)	5��(Ĭ��-1)
        [1] = {nTemplate = 8091, nLevel = -1, nSeries = -1},		-- а�������
	},

    LOCK =
    {
       -- 1�������ܲ��Ĭ��1��Ϊ��ʼ��
		[1] = {nTime = 3, nNum = 0,		-- �ܼ�ʱ
			tbPrelock = {},
			tbStartEvent =
			{
			   {Tower.TIME_INFO, Lang.mission.str989[Lang.Idx],1},
			},
			tbUnLockEvent =
			{
			},
		},
		[2] = {nTime = 0, nNum = 1 ,		-- �ܼ�ʱ
			tbPrelock = {1},
			tbStartEvent =
			{
				{Tower.ADD_NPC, 1, 1, 2, "2", "all"},     --а�������	
				{Tower.TARGET_INFO, Lang.mission.str1246[Lang.Idx], 2},
				{Tower.TIME_INFO, Lang.mission.str990[Lang.Idx]},
			},
			tbUnLockEvent =
			{
			},
		},
		[3] = {nTime = 3, nNum = 0 ,		-- �ܼ�ʱ
			tbPrelock = {2},
			tbStartEvent =
			{
				{Tower.TARGET_INFO, Lang.mission.str991[Lang.Idx]},
				{Tower.TIME_INFO, Lang.mission.str992[Lang.Idx], 3},
			},
			tbUnLockEvent =
			{
				{Tower.DO_SCRIPT, "self.bFinishLayer = 1"},
			},
		}
    }
}