-- ��ħ����8��������ļ�

Include("script/mission/tower/tower_def.lua")
if not Tower.tbSetting then
	Tower.tbSetting = {}
end

local TowerSetting = Tower.tbSetting;


TowerSetting[71]=
{
	nTimeLimit = 180,  --����ʱ��5����
	nMapId = 243,
	nEnemyNum = 8,
    tbBeginPos = {1078, 1016, 1048576},

    -- �����漰��NPC����
	NPC =
	{
	-- 		���  	npcģ��				�ȼ�(-1Ĭ��)	5��(Ĭ��-1)
        [1] = {nTemplate = 8101, nLevel = -1, nSeries = -1},		-- ����
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
				{Tower.TARGET_INFO, Lang.mission.str1247[Lang.Idx], 2}, --�������
				{Tower.ADD_NPC, 1, 2, 2, "1", "leftshang"},     --����
				{Tower.ADD_NPC, 1, 2, 2, "1", "leftxia"},  		--����
				{Tower.ADD_NPC, 1, 2, 2, "1", "rightshang"},    --����
				{Tower.ADD_NPC, 1, 2, 2, "1", "rightxia"},      --����
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


TowerSetting[72]=
{
	nTimeLimit = 180,
	nMapId = 243,
	nEnemyNum = 8,
         tbBeginPos = {1078, 1016, 1048576},

    -- �����漰��NPC����
	NPC =
	{
-- 		���  	npcģ��				�ȼ�(-1Ĭ��)	5��(Ĭ��-1)
        [1] = {nTemplate = 8111, nLevel = -1, nSeries = -1},		-- �ܾ�
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
				{Tower.TARGET_INFO, Lang.mission.str1248[Lang.Idx], 2}, --�������
				{Tower.ADD_NPC, 1, 2, 2, "1", "leftshang"},     --�ܾ�
				{Tower.ADD_NPC, 1, 2, 2, "1", "leftxia"},  		--�ܾ�
				{Tower.ADD_NPC, 1, 2, 2, "1", "rightshang"},    --�ܾ�
				{Tower.ADD_NPC, 1, 2, 2, "1", "rightxia"},      --�ܾ�
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

TowerSetting[73]=
{
	nTimeLimit = 180,
	nMapId = 243,
	nEnemyNum = 8,
    tbBeginPos = {1078, 1016, 1048576},

    -- �����漰��NPC����
	NPC =
	{
-- 		���  	npcģ��				�ȼ�(-1Ĭ��)	5��(Ĭ��-1)
        [1] = {nTemplate = 8121, nLevel = -1, nSeries = -1},		-- ����
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
				{Tower.TARGET_INFO, Lang.mission.str1249[Lang.Idx], 2}, --�������
				{Tower.ADD_NPC, 1, 2, 2, "1", "leftshang"},     --����
				{Tower.ADD_NPC, 1, 2, 2, "1", "leftxia"},  		--����
				{Tower.ADD_NPC, 1, 2, 2, "1", "rightshang"},    --����
				{Tower.ADD_NPC, 1, 2, 2, "1", "rightxia"},      --����
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

TowerSetting[74]=
{
	nTimeLimit = 180,
	nMapId = 243,
	nEnemyNum = 8,
    tbBeginPos = {1078, 1016, 1048576},

    -- �����漰��NPC����
	NPC =
	{
-- 		���  	npcģ��				�ȼ�(-1Ĭ��)	5��(Ĭ��-1)
        [1] = {nTemplate = 8131, nLevel = -1, nSeries = -1},		-- ��֩��
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
				{Tower.TARGET_INFO, Lang.mission.str1250[Lang.Idx], 2}, --�������
				{Tower.ADD_NPC, 1, 2, 2, "1", "leftshang"},     --��֩��
				{Tower.ADD_NPC, 1, 2, 2, "1", "leftxia"},  		--��֩��
				{Tower.ADD_NPC, 1, 2, 2, "1", "rightshang"},    --��֩��
				{Tower.ADD_NPC, 1, 2, 2, "1", "rightxia"},      --��֩��
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


TowerSetting[75]=
{
	nTimeLimit = 180,
	nMapId = 243,
	nEnemyNum = 1,
    tbBeginPos = {1078, 1016, 1048576},

    -- �����漰��NPC����
	NPC =
	{
-- 		���  	npcģ��				�ȼ�(-1Ĭ��)	5��(Ĭ��-1)
        [1] = {nTemplate = 8141, nLevel = -1, nSeries = -1},		-- ţħ��
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
		[2] = {nTime = 0, nNum = 1 ,		-- ��ͨ����������ʱ�䵹��ʱ��ɱ�ָ�����
			tbPrelock = {1},
			tbStartEvent =
			{
				{Tower.TIME_INFO, Lang.mission.str989[Lang.Idx]},
				{Tower.TARGET_INFO, Lang.mission.str1251[Lang.Idx], 2}, --�������
				{Tower.ADD_NPC, 1, 1, 2, "1", "all"},     --ţħ��
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


TowerSetting[76]=
{
	nTimeLimit = 180,
	nMapId = 243,
	nEnemyNum = 8,
   tbBeginPos = {1078, 1016, 1048576},

    -- �����漰��NPC����
	NPC =
	{
-- 		���  	npcģ��				�ȼ�(-1Ĭ��)	5��(Ĭ��-1)
        [1] = {nTemplate = 8151, nLevel = -1, nSeries = -1},		-- ���
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
				{Tower.TARGET_INFO, Lang.mission.str1252[Lang.Idx], 2}, --�������
				{Tower.ADD_NPC, 1, 2, 2, "1", "leftshang"},     --���
				{Tower.ADD_NPC, 1, 2, 2, "1", "leftxia"},  		--���
				{Tower.ADD_NPC, 1, 2, 2, "1", "rightshang"},    --���
				{Tower.ADD_NPC, 1, 2, 2, "1", "rightxia"},      --���
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


TowerSetting[77]=
{
	nTimeLimit = 180,
	nMapId = 243,
	nEnemyNum = 8,
     tbBeginPos = {1078, 1016, 1048576},

    -- �����漰��NPC����
	NPC =
	{
-- 		���  	npcģ��				�ȼ�(-1Ĭ��)	5��(Ĭ��-1)
        [1] = {nTemplate = 8161, nLevel = -1, nSeries = -1},		-- �ֵ�С��
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
				{Tower.TARGET_INFO, Lang.mission.str1253[Lang.Idx], 2}, --�������
				{Tower.ADD_NPC, 1, 2, 2, "1", "leftshang"},     --�ֵ�С��
				{Tower.ADD_NPC, 1, 2, 2, "1", "leftxia"},  		--�ֵ�С��
				{Tower.ADD_NPC, 1, 2, 2, "1", "rightshang"},    --�ֵ�С��
				{Tower.ADD_NPC, 1, 2, 2, "1", "rightxia"},      --�ֵ�С��
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



TowerSetting[78]=
{
	nTimeLimit = 180,
	nMapId = 243,
	nEnemyNum = 8,
     tbBeginPos = {1078, 1016, 1048576},

    -- �����漰��NPC����
	NPC =
	{
-- 		���  	npcģ��				�ȼ�(-1Ĭ��)	5��(Ĭ��-1)
        [1] = {nTemplate = 8171, nLevel = -1, nSeries = -1},		-- ţ��
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
				{Tower.TARGET_INFO, Lang.mission.str1254[Lang.Idx], 2}, --�������
				{Tower.ADD_NPC, 1, 2, 2, "1", "leftshang"},     --ţ��
				{Tower.ADD_NPC, 1, 2, 2, "1", "leftxia"},  		--ţ��
				{Tower.ADD_NPC, 1, 2, 2, "1", "rightshang"},    --ţ��
				{Tower.ADD_NPC, 1, 2, 2, "1", "rightxia"},      --ţ��
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


TowerSetting[79]=
{
	nTimeLimit = 180,
	nMapId = 243,
	nEnemyNum = 8,
    tbBeginPos = {1078, 1016, 1048576},

    -- �����漰��NPC����
	NPC =
	{
-- 		���  	npcģ��				�ȼ�(-1Ĭ��)	5��(Ĭ��-1)
        [1] = {nTemplate = 8181, nLevel = -1, nSeries = -1},		-- ����Ȯ
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
				{Tower.TARGET_INFO, Lang.mission.str1255[Lang.Idx], 2}, --�������
				{Tower.ADD_NPC, 1, 2, 2, "1", "leftshang"},     --����Ȯ
				{Tower.ADD_NPC, 1, 2, 2, "1", "leftxia"},  		--����Ȯ
				{Tower.ADD_NPC, 1, 2, 2, "1", "rightshang"},    --����Ȯ
				{Tower.ADD_NPC, 1, 2, 2, "1", "rightxia"},      --����Ȯ
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


TowerSetting[80]=
{
	nTimeLimit = 180,
	nMapId = 243,
	nEnemyNum = 1,
    tbBeginPos = {1078, 1016, 1048576},

    -- �����漰��NPC����
	NPC =
	{
-- 		���  	npcģ��				�ȼ�(-1Ĭ��)	5��(Ĭ��-1)
        [1] = {nTemplate = 8191, nLevel = -1, nSeries = -1},		-- �������
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
		[2] = {nTime = 0, nNum = 1 ,		-- ��ͨ����������ʱ�䵹��ʱ��ɱ�ָ�����
			tbPrelock = {1},
			tbStartEvent =
			{
				{Tower.TIME_INFO, Lang.mission.str989[Lang.Idx]},
				{Tower.TARGET_INFO, Lang.mission.str1256[Lang.Idx], 2}, --�������
				{Tower.ADD_NPC, 1, 1, 2, "1", "all"},     --�������
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
