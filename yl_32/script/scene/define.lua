


--��gamedef.h��MAP_TYPE����ƥ��
Scene.INVALID 		= 0		--δ֪����
Scene.NORMAL 		= 1		--��ͨ����
Scene.DUNGEON 		= 2		--��ͨ����/���¸���
Scene.BATTLEFIELD 	= 3	--ս������
Scene.BIRTHMAP 		= 4			--���鸱��

Scene.BASE_RUN_SPEED = 20	-- ��ɫ��ʼ�ƶ��ٶ�

Scene.CELL_LENGHT = 32	--cell lenght

--[[
enum KMAP_TYPE
{
	emtInvalid = -1,

	emtNormalMap,       // ��������
	emtDungeon,         // ���񸱱�
	emtBattleField,     // ս��
	emtBirthMap,        // ���ִ�

	emtTotal
};

--]]

-- ��������
Scene.MAP_TYPE_NORMAL = 0; -- ��������
Scene.MAP_TYPE_DUNGEON = 1; -- ���񸱱�
Scene.MAP_TYPE_BATTLE = 2; -- ս��
Scene.MAP_TYPE_BIRTH = 3; --���ִ�
