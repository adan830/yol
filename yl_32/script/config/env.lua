-- ��Ϸ��������������壨ע�Ᵽ��������һ�£�

if not (MODULE_GAMECLIENT or MODULE_GAMESERVER or MODULE_GC_SERVER or MODULE_SKILLSIMULATOR or MODULE_GAMECENTER) then
	return
end

Env.GAME_FPS			= 16;		-- ��Ϸ����ÿ��֡��

-- �Ա���
Env.SEX_MALE			= 0;		-- ����
Env.SEX_FEMALE			= 1;		-- Ů��

-- �Ա������ַ���
Env.SEX_NAME =
{
	[Env.SEX_MALE]		= "����",
	[Env.SEX_FEMALE]	= "Ů��",
};

-- ������������
Env.NEWSMSG_NORMAL 		= 0;    -- ��ͨ
Env.NEWSMSG_COUNT		= 1;	-- ��ʱ����
Env.NEWSMSG_TIMEEND		= 2;	-- ��ʱֹͣ

Env.WEIWANG_BATTLE		= 1;
Env.WEIWANG_MENPAIJINGJI= 2;
Env.WEIWANG_DATI		= 3;
Env.WEIWANG_BAIHUTANG 	= 4;
Env.WEIWANG_TREASURE	= 5;
Env.WEIWANG_BAOWANTONG	= 6;
Env.WEIWANG_GUOZI		= 7;
Env.WEIWANG_BOSS		= 8;