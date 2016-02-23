-- ��ħ����11��������ļ�

Include("script/mission/tower/tower_def.lua")
if not Tower.tbSetting then
	Tower.tbSetting = {}
end

local TowerSetting = Tower.tbSetting;


TowerSetting[101]=
{
	nTimeLimit = 180,  --����ʱ��5����
	nMapId = 246,
	nEnemyNum = 8,
    tbBeginPos = {1078, 1016, 1048576},

    -- �����漰��NPC����
	NPC =
	{
	-- 		���  	npcģ��				�ȼ�(-1Ĭ��)	5��(Ĭ��-1)
        [1] = {nTemplate = 8401, nLevel = -1, nSeries = -1},		-- ��������
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
				{Tower.TARGET_INFO, Lang.mission.str1277[Lang.Idx], 2}, --�������
				{Tower.ADD_NPC, 1, 2, 2, "1", "leftshang"},     --��������
				{Tower.ADD_NPC, 1, 2, 2, "1", "leftxia"},  		--��������
				{Tower.ADD_NPC, 1, 2, 2, "1", "rightshang"},    --��������
				{Tower.ADD_NPC, 1, 2, 2, "1", "rightxia"},      --��������
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


TowerSetting[102]=
{
	nTimeLimit = 180,
	nMapId = 246,
	nEnemyNum = 8,
         tbBeginPos = {1078, 1016, 1048576},

    -- �����漰��NPC����
	NPC =
	{
-- 		���  	npcģ��				�ȼ�(-1Ĭ��)	5��(Ĭ��-1)
        [1] = {nTemplate = 8411, nLevel = -1, nSeries = -1},		-- ����ͯ
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
				{Tower.TARGET_INFO, Lang.mission.str1278[Lang.Idx], 2}, --�������
				{Tower.ADD_NPC, 1, 2, 2, "1", "leftshang"},     --����ͯ
				{Tower.ADD_NPC, 1, 2, 2, "1", "leftxia"},  		--����ͯ
				{Tower.ADD_NPC, 1, 2, 2, "1", "rightshang"},    --����ͯ
				{Tower.ADD_NPC, 1, 2, 2, "1", "rightxia"},      --����ͯ
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

TowerSetting[103]=
{
	nTimeLimit = 180,
	nMapId = 246,
	nEnemyNum = 8,
    tbBeginPos = {1078, 1016, 1048576},

    -- �����漰��NPC����
	NPC =
	{
-- 		���  	npcģ��				�ȼ�(-1Ĭ��)	5��(Ĭ��-1)
        [1] = {nTemplate = 8421, nLevel = -1, nSeries = -1},		-- �з��
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
				{Tower.TARGET_INFO, Lang.mission.str1279[Lang.Idx], 2}, --�������
				{Tower.ADD_NPC, 1, 2, 2, "1", "leftshang"},     --�з��
				{Tower.ADD_NPC, 1, 2, 2, "1", "leftxia"},  		--�з��
				{Tower.ADD_NPC, 1, 2, 2, "1", "rightshang"},    --�з��
				{Tower.ADD_NPC, 1, 2, 2, "1", "rightxia"},      --�з��
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

TowerSetting[104]=
{
	nTimeLimit = 180,
	nMapId = 246,
	nEnemyNum = 8,
    tbBeginPos = {1078, 1016, 1048576},

    -- �����漰��NPC����
	NPC =
	{
-- 		���  	npcģ��				�ȼ�(-1Ĭ��)	5��(Ĭ��-1)
        [1] = {nTemplate = 8431, nLevel = -1, nSeries = -1},		-- ��ʬ��
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
				{Tower.TARGET_INFO, Lang.mission.str1280[Lang.Idx], 2}, --�������
				{Tower.ADD_NPC, 1, 2, 2, "1", "leftshang"},     --��ʬ��
				{Tower.ADD_NPC, 1, 2, 2, "1", "leftxia"},  		--��ʬ��
				{Tower.ADD_NPC, 1, 2, 2, "1", "rightshang"},    --��ʬ��
				{Tower.ADD_NPC, 1, 2, 2, "1", "rightxia"},      --��ʬ��
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


TowerSetting[105]=
{
	nTimeLimit = 180,
	nMapId = 246,
	nEnemyNum = 1,
    tbBeginPos = {1078, 1016, 1048576},

    -- �����漰��NPC����
	NPC =
	{
-- 		���  	npcģ��				�ȼ�(-1Ĭ��)	5��(Ĭ��-1)
        [1] = {nTemplate = 8441, nLevel = -1, nSeries = -1},		-- [��Ӣ]���ħ��
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
				{Tower.TARGET_INFO, Lang.mission.str1281[Lang.Idx], 2}, --�������
				{Tower.ADD_NPC, 1, 1, 2, "1", "all"},     --[��Ӣ]���ħ��
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


TowerSetting[106]=
{
	nTimeLimit = 180,
	nMapId = 246,
	nEnemyNum = 8,
   tbBeginPos = {1078, 1016, 1048576},

    -- �����漰��NPC����
	NPC =
	{
-- 		���  	npcģ��				�ȼ�(-1Ĭ��)	5��(Ĭ��-1)
        [1] = {nTemplate = 8451, nLevel = -1, nSeries = -1},		-- ���ۺ�
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
				{Tower.TARGET_INFO, Lang.mission.str1282[Lang.Idx], 2}, --�������
				{Tower.ADD_NPC, 1, 2, 2, "1", "leftshang"},     --���ۺ�
				{Tower.ADD_NPC, 1, 2, 2, "1", "leftxia"},  		--���ۺ�
				{Tower.ADD_NPC, 1, 2, 2, "1", "rightshang"},    --���ۺ�
				{Tower.ADD_NPC, 1, 2, 2, "1", "rightxia"},      --���ۺ�
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


TowerSetting[107]=
{
	nTimeLimit = 180,
	nMapId = 246,
	nEnemyNum = 8,
     tbBeginPos = {1078, 1016, 1048576},

    -- �����漰��NPC����
	NPC =
	{
-- 		���  	npcģ��				�ȼ�(-1Ĭ��)	5��(Ĭ��-1)
        [1] = {nTemplate = 8461, nLevel = -1, nSeries = -1},		-- Թ��
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
				{Tower.TARGET_INFO, Lang.mission.str1283[Lang.Idx], 2}, --�������
				{Tower.ADD_NPC, 1, 2, 2, "1", "leftshang"},     --Թ��
				{Tower.ADD_NPC, 1, 2, 2, "1", "leftxia"},  		--Թ��
				{Tower.ADD_NPC, 1, 2, 2, "1", "rightshang"},    --Թ��
				{Tower.ADD_NPC, 1, 2, 2, "1", "rightxia"},      --Թ��
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



TowerSetting[108]=
{
	nTimeLimit = 180,
	nMapId = 246,
	nEnemyNum = 8,
     tbBeginPos = {1078, 1016, 1048576},

    -- �����漰��NPC����
	NPC =
	{
-- 		���  	npcģ��				�ȼ�(-1Ĭ��)	5��(Ĭ��-1)
        [1] = {nTemplate = 8471, nLevel = -1, nSeries = -1},		-- ��������
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
				{Tower.TARGET_INFO, Lang.mission.str1284[Lang.Idx], 2}, --�������
				{Tower.ADD_NPC, 1, 2, 2, "1", "leftshang"},     --��������
				{Tower.ADD_NPC, 1, 2, 2, "1", "leftxia"},  		--��������
				{Tower.ADD_NPC, 1, 2, 2, "1", "rightshang"},    --��������
				{Tower.ADD_NPC, 1, 2, 2, "1", "rightxia"},      --��������
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


TowerSetting[109]=
{
	nTimeLimit = 180,
	nMapId = 246,
	nEnemyNum = 8,
    tbBeginPos = {1078, 1016, 1048576},

    -- �����漰��NPC����
	NPC =
	{
-- 		���  	npcģ��				�ȼ�(-1Ĭ��)	5��(Ĭ��-1)
        [1] = {nTemplate = 8481, nLevel = -1, nSeries = -1},		-- �����ܾ�
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
				{Tower.TARGET_INFO, Lang.mission.str1285[Lang.Idx], 2}, --�������
				{Tower.ADD_NPC, 1, 2, 2, "1", "leftshang"},     --�����ܾ�
				{Tower.ADD_NPC, 1, 2, 2, "1", "leftxia"},  		--�����ܾ�
				{Tower.ADD_NPC, 1, 2, 2, "1", "rightshang"},    --�����ܾ�
				{Tower.ADD_NPC, 1, 2, 2, "1", "rightxia"},      --�����ܾ�
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


TowerSetting[110]=
{
	nTimeLimit = 180,
	nMapId = 246,
	nEnemyNum = 1,
    tbBeginPos = {1078, 1016, 1048576},

    -- �����漰��NPC����
	NPC =
	{
-- 		���  	npcģ��				�ȼ�(-1Ĭ��)	5��(Ĭ��-1)
        [1] = {nTemplate = 8491, nLevel = -1, nSeries = -1},		-- [BOSS]�����
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
				{Tower.TARGET_INFO, Lang.mission.str1286[Lang.Idx], 2}, --�������
				{Tower.ADD_NPC, 1, 1, 2, "1", "all"},     --[BOSS]�����
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
