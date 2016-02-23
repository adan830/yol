-- ��ħ����9��������ļ�

Include("script/mission/tower/tower_def.lua")
if not Tower.tbSetting then
	Tower.tbSetting = {}
end

local TowerSetting = Tower.tbSetting;


TowerSetting[81]=
{
	nTimeLimit = 180,  --����ʱ��5����
	nMapId = 244,
    tbBeginPos = {1831, 312, 1048576},


    -- �����漰��NPC����
	NPC =
	{
	-- 		���  	npcģ��				�ȼ�(-1Ĭ��)	5��(Ĭ��-1)
        [1] = {nTemplate = 8201, nLevel = -1, nSeries = -1},		-- ����ѻ
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
				{Tower.TIME_INFO, Lang.mission.str989[Lang.Idx]},
				{Tower.TARGET_INFO, Lang.mission.str1257[Lang.Idx], 2}, --�������
				{Tower.ADD_NPC, 1, 8, 2, "1", "monster"}, --����ѻ
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


TowerSetting[82]=
{
	nTimeLimit = 180,
	nMapId = 244,
    tbBeginPos = {1831, 312, 1048576},


    -- �����漰��NPC����
	NPC =
	{
-- 		���  	npcģ��				�ȼ�(-1Ĭ��)	5��(Ĭ��-1)
        [1] = {nTemplate = 8211, nLevel = -1, nSeries = -1},		-- ����
	},

    LOCK =
    {
       -- 1�������ܲ��Ĭ��1��Ϊ��ʼ��
		[1] = {nTime = 3, nNum = 0,		-- �ܼ�ʱ
			tbPrelock = {},
			tbStartEvent =
			{
			    {Tower.TIME_INFO, Lang.mission.str989[Lang.Idx]},
			},
			tbUnLockEvent =
			{
			},
		},
		[2] = {nTime = 0, nNum = 8 ,		-- �ܼ�ʱ
			tbPrelock = {1},
			tbStartEvent =
			{
				{Tower.ADD_NPC, 1, 8, 2, "1", "monster"}, --����
				{Tower.TARGET_INFO, Lang.mission.str1258[Lang.Idx], 2},
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

TowerSetting[83]=
{
	nTimeLimit = 180,
	nMapId = 244,
    tbBeginPos = {1831, 312, 1048576},

    -- �����漰��NPC����
	NPC =
	{
-- 		���  	npcģ��				�ȼ�(-1Ĭ��)	5��(Ĭ��-1)
        [1] = {nTemplate = 8221, nLevel = -1, nSeries = -1},		-- ⨺�
	},

    LOCK =
    {
       -- 1�������ܲ��Ĭ��1��Ϊ��ʼ��
		[1] = {nTime = 3, nNum = 0,		-- �ܼ�ʱ
			tbPrelock = {},
			tbStartEvent =
			{
			    {Tower.TIME_INFO, Lang.mission.str989[Lang.Idx]},
			},
			tbUnLockEvent =
			{
			},
		},
		[2] = {nTime = 0, nNum = 8 ,		-- �ܼ�ʱ
			tbPrelock = {1},
			tbStartEvent =
			{
				{Tower.ADD_NPC, 1, 8, 2, "1", "monster"}, --⨺�
				{Tower.TARGET_INFO, Lang.mission.str1259[Lang.Idx], 2},
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

TowerSetting[84]=
{
	nTimeLimit = 180,
	nMapId = 244,
    tbBeginPos = {1831, 312, 1048576},

    -- �����漰��NPC����
	NPC =
	{
-- 		���  	npcģ��				�ȼ�(-1Ĭ��)	5��(Ĭ��-1)
        [1] = {nTemplate = 8231, nLevel = -1, nSeries = -1},		-- ������ʿ
	},

    LOCK =
    {
       -- 1�������ܲ��Ĭ��1��Ϊ��ʼ��
		[1] = {nTime = 3, nNum = 0,		-- �ܼ�ʱ
			tbPrelock = {},
			tbStartEvent =
			{
			    {Tower.TIME_INFO, Lang.mission.str989[Lang.Idx]},
			},
			tbUnLockEvent =
			{
			},
		},
		[2] = {nTime = 0, nNum = 8 ,		-- �ܼ�ʱ
			tbPrelock = {1},
			tbStartEvent =
			{
				{Tower.ADD_NPC, 1, 8, 2, "1", "monster"}, --������ʿ
				{Tower.TARGET_INFO, Lang.mission.str1260[Lang.Idx], 2},
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


TowerSetting[85]=
{
	nTimeLimit = 180,
	nMapId = 244,
    tbBeginPos = {1831, 312, 1048576},


    -- �����漰��NPC����
	NPC =
	{
-- 		���  	npcģ��				�ȼ�(-1Ĭ��)	5��(Ĭ��-1)
        [1] = {nTemplate = 8241, nLevel = -1, nSeries = -1},		-- �����
	},

    LOCK =
    {
       -- 1�������ܲ��Ĭ��1��Ϊ��ʼ��
		[1] = {nTime = 3, nNum = 0,		-- �ܼ�ʱ
			tbPrelock = {},
			tbStartEvent =
			{
			    {Tower.TIME_INFO, Lang.mission.str989[Lang.Idx]},
			},
			tbUnLockEvent =
			{
			},
		},
		[2] = {nTime = 0, nNum = 1 ,		-- �ܼ�ʱ
			tbPrelock = {1},
			tbStartEvent =
			{
				{Tower.ADD_NPC, 1, 1, 2, "1", "monster"}, --�����
				{Tower.TARGET_INFO, Lang.mission.str1261[Lang.Idx], 2},
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


TowerSetting[86]=
{
	nTimeLimit = 180,
	nMapId = 244,
    tbBeginPos = {1831, 312, 1048576},

    -- �����漰��NPC����
	NPC =
	{
-- 		���  	npcģ��				�ȼ�(-1Ĭ��)	5��(Ĭ��-1)
        [1] = {nTemplate = 8251, nLevel = -1, nSeries = -1},		-- ������
	},

    LOCK =
    {
       -- 1�������ܲ��Ĭ��1��Ϊ��ʼ��
		[1] = {nTime = 3, nNum = 0,		-- �ܼ�ʱ
			tbPrelock = {},
			tbStartEvent =
			{
			    {Tower.TIME_INFO, Lang.mission.str989[Lang.Idx]},
			},
			tbUnLockEvent =
			{
			},
		},
		[2] = {nTime = 0, nNum = 8 ,		-- �ܼ�ʱ
			tbPrelock = {1},
			tbStartEvent =
			{
				{Tower.ADD_NPC, 1, 8, 2, "1", "monster"}, --������
				{Tower.TARGET_INFO, Lang.mission.str1262[Lang.Idx], 2},
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


TowerSetting[87]=
{
	nTimeLimit = 180,
	nMapId = 244,
    tbBeginPos = {1831, 312, 1048576},


    -- �����漰��NPC����
	NPC =
	{
-- 		���  	npcģ��				�ȼ�(-1Ĭ��)	5��(Ĭ��-1)
        [1] = {nTemplate = 8261, nLevel = -1, nSeries = -1},		-- ���ҹ�
	},

    LOCK =
    {
       -- 1�������ܲ��Ĭ��1��Ϊ��ʼ��
		[1] = {nTime = 3, nNum = 0,		-- �ܼ�ʱ
			tbPrelock = {},
			tbStartEvent =
			{
			    {Tower.TIME_INFO, Lang.mission.str989[Lang.Idx]},
			},
			tbUnLockEvent =
			{
			},
		},
		[2] = {nTime = 0, nNum = 8 ,		-- �ܼ�ʱ
			tbPrelock = {1},
			tbStartEvent =
			{
				{Tower.ADD_NPC, 1, 8, 2, "1", "monster"}, --���ҹ�
				{Tower.TARGET_INFO, Lang.mission.str1263[Lang.Idx], 2},
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



TowerSetting[88]=
{
	nTimeLimit = 180,
	nMapId = 244,
    tbBeginPos = {1831, 312, 1048576},


    -- �����漰��NPC����
	NPC =
	{
-- 		���  	npcģ��				�ȼ�(-1Ĭ��)	5��(Ĭ��-1)
        [1] = {nTemplate = 8271, nLevel = -1, nSeries = -1},		-- ���
	},

    LOCK =
    {
       -- 1�������ܲ��Ĭ��1��Ϊ��ʼ��
		[1] = {nTime = 3, nNum = 0,		-- �ܼ�ʱ
			tbPrelock = {},
			tbStartEvent =
			{
			    {Tower.TIME_INFO, Lang.mission.str989[Lang.Idx]},
			},
			tbUnLockEvent =
			{
			},
		},
		[2] = {nTime = 0, nNum = 8 ,		-- �ܼ�ʱ
			tbPrelock = {1},
			tbStartEvent =
			{
				{Tower.ADD_NPC, 1, 8, 2, "1", "monster"}, --���
				{Tower.TARGET_INFO, Lang.mission.str1264[Lang.Idx], 2},
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


TowerSetting[89]=
{
	nTimeLimit = 180,
	nMapId = 244,
    tbBeginPos = {1831, 312, 1048576},


    -- �����漰��NPC����
	NPC =
	{
-- 		���  	npcģ��				�ȼ�(-1Ĭ��)	5��(Ĭ��-1)
        [1] = {nTemplate = 8281, nLevel = -1, nSeries = -1},		-- ʳ�˻�
	},

    LOCK =
    {
       -- 1�������ܲ��Ĭ��1��Ϊ��ʼ��
		[1] = {nTime = 3, nNum = 0,		-- �ܼ�ʱ
			tbPrelock = {},
			tbStartEvent =
			{
			    {Tower.TIME_INFO, Lang.mission.str989[Lang.Idx]},
			},
			tbUnLockEvent =
			{
			},
		},
		[2] = {nTime = 0, nNum = 8 ,		-- �ܼ�ʱ
			tbPrelock = {1},
			tbStartEvent =
			{
				{Tower.ADD_NPC, 1, 8, 2, "1", "monster"}, --ʳ�˻�
				{Tower.TARGET_INFO, Lang.mission.str1265[Lang.Idx], 2},
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


TowerSetting[90]=
{
	nTimeLimit = 180,
	nMapId = 244,
    tbBeginPos = {1831, 312, 1048576},


    -- �����漰��NPC����
	NPC =
	{
-- 		���  	npcģ��				�ȼ�(-1Ĭ��)	5��(Ĭ��-1)
        [1] = {nTemplate = 8291, nLevel = -1, nSeries = -1},		-- �ҷ�ӡ����
	},

    LOCK =
    {
       -- 1�������ܲ��Ĭ��1��Ϊ��ʼ��
		[1] = {nTime = 3, nNum = 0,		-- �ܼ�ʱ
			tbPrelock = {},
			tbStartEvent =
			{
			    {Tower.TIME_INFO, Lang.mission.str989[Lang.Idx]},
			},
			tbUnLockEvent =
			{
			},
		},
		[2] = {nTime = 0, nNum = 1 ,		-- �ܼ�ʱ
			tbPrelock = {1},
			tbStartEvent =
			{
				{Tower.ADD_NPC, 1, 1, 2, "1", "monster"}, --�ҷ�ӡ����
				{Tower.TARGET_INFO, Lang.mission.str1266[Lang.Idx], 2},
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
