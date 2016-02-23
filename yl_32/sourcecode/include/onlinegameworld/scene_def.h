
#pragma once

#include "Core.h"
#include "config/gamedef.h"


#define DIRECTION_BIT_NUM       8
#define DIRECTION_COUNT			(1 << DIRECTION_BIT_NUM)
#define DIRECTION_TURN_SPEED    5

enum MOVE_MODE
{
	mmInvalid = 0,
	mmGround,
	mmWater,
	mmGroundAndWater,

	mmTotal
};

//����
#define DEFAULT_MASS			128			    // ��λ��g
#define DEFAULT_GRAVITY			(8 * 512 / GAME_FPS / GAME_FPS)	//��λ����/֡^2
//#define SYNC_CHARACTER_DELAY		1	// ͬ����ʱ  // �ӳ�һ֡�����ͬ�����⣬��Ϊ0
#define SYNC_CHARACTER_DELAY		0	// ͬ����ʱ
#define MAX_SYNC_PER_REGION		32	            // ͬ�������Ʋ���
#define KD_NEARBY_OBJ_SYNC_MAX		300	            // һ�����ͬ�����ٸ��������
#define	KD_SYNC_PACK_MAX		64 * 1024		// ͬ���������ֵ

#pragma pack(1)
struct KMOVE_CRITICAL_PARAM
{
	BYTE byMoveState;
	int  nRunSpeed;
	int  nGravity;
	int  nJumpSpeed;
	int  nX;
	int  nY;
	int  nZ;
};
#pragma pack()

#define ID_PREFIX_BIT_NUM	4

// ��̬�ϰ��������Чֵ(֮������0,������-1,��Ϊ�˼�����ǰ������)
#define INVALID_OBSTACLE_GROUP  0
// ��Ч�Ķ�̬�ϰ�����������ȡֵ��Χ(0, 4096)
#define MAX_OBSTACLE_GROUP      4096

// ��������Ϸ����Ŀռ仮�ִ�С����
#define MAX_REGION_WIDTH_BIT_NUM	6	//��ͼ��X����������Region����
#define MAX_REGION_HEIGHT_BIT_NUM	6	//��ͼ��Y����������Region����

#define REGION_GRID_WIDTH_BIT_NUM	6	//Region��X����������Cell����
#define REGION_GRID_HEIGHT_BIT_NUM	6	//Region��Y����������Cell����

#define CELL_LENGTH_BIT_NUM			5	//�����е����ص㾫��
#define ALTITUDE_BIT_NUM			6

#define MAX_Z_ALTITUDE_BIT_NUM		16	//Z������ֵλ��(ALTITUDE)
#define MAX_Z_POINT_BIT_NUM         (MAX_Z_ALTITUDE_BIT_NUM + ALTITUDE_BIT_NUM)

#define MOVE_DEST_RANGE_BIT_NUM		12
#define MOVE_DEST_RANGE				(1 << MOVE_DEST_RANGE_BIT_NUM)

#define	MAX_VELOCITY_XY_BIT_NUM		(CELL_LENGTH_BIT_NUM + 2)
#define MAX_VELOCITY_Z_BIT_NUM		(ALTITUDE_BIT_NUM + 6)
// ����ˮƽ�ٶ���������ʱ�����������,ע��,���ֵ��ò�ҪС����������ʱ�ķ�ĸ��ֵ
#define VELOCITY_ZOOM_BIT_NUM      4
#define VELOCITY_ZOOM_COEFFICIENT (1 << VELOCITY_ZOOM_BIT_NUM)

#define MAX_ZOOM_VELOCITY_BIT_NUM   (MAX_VELOCITY_XY_BIT_NUM + VELOCITY_ZOOM_BIT_NUM)
#define MAX_ZOOM_VELOCITY           ((1 << MAX_ZOOM_VELOCITY_BIT_NUM) - 1)

#define MAX_VELOCITY_XY				((1 << MAX_VELOCITY_XY_BIT_NUM) - 1)
// ע��,Z���ٶ����з���,����Ϊ��ֵ��,Ŀǰȡֵ����Ϊ[-512, 511], 10 bits
#define MAX_VELOCITY_Z				((1 << (MAX_VELOCITY_Z_BIT_NUM - 1)) - 1)
#define MIN_VELOCITY_Z				(-(1 << (MAX_VELOCITY_Z_BIT_NUM - 1)))

#define MAX_X_COORDINATE_BIT        (MAX_REGION_WIDTH_BIT_NUM  + REGION_GRID_WIDTH_BIT_NUM  + CELL_LENGTH_BIT_NUM)
#define MAX_Y_COORDINATE_BIT        (MAX_REGION_HEIGHT_BIT_NUM + REGION_GRID_HEIGHT_BIT_NUM + CELL_LENGTH_BIT_NUM)
#define MAX_X_COORDINATE            ((1 << MAX_X_COORDINATE_BIT) - 1)
#define MAX_Y_COORDINATE            ((1 << MAX_Y_COORDINATE_BIT) - 1)

//������ض���
#define MAX_REGION_WIDTH			(1 << MAX_REGION_WIDTH_BIT_NUM)
#define MAX_REGION_HEIGHT			(1 << MAX_REGION_HEIGHT_BIT_NUM)
#define MAX_Z_ALTITUDE				((1 << MAX_Z_ALTITUDE_BIT_NUM) - 1)
#define MAX_Z_POINT				    ((1 << MAX_Z_POINT_BIT_NUM) - 1)

//#define REGION_GRID_WIDTH			(1 << REGION_GRID_WIDTH_BIT_NUM)
//#define REGION_GRID_HEIGHT			(1 << REGION_GRID_HEIGHT_BIT_NUM)

//region ��СΪ 64 * 64 //change to 32*32
#define REGION_GRID_WIDTH			(1 << REGION_GRID_WIDTH_BIT_NUM)
#define REGION_GRID_HEIGHT			(1 << REGION_GRID_HEIGHT_BIT_NUM)


#define CELL_LENGTH					(1 << CELL_LENGTH_BIT_NUM)
#define POINT_PER_ALTITUDE			(1 << ALTITUDE_BIT_NUM)
#define ALTITUDE_2_CELL				(POINT_PER_ALTITUDE * LOGICAL_CELL_CM_LENGTH/ ALTITUDE_UNIT / CELL_LENGTH)

#define MAX_GRAVITY_BIT_NUM          5
#define MAX_GRAVITY                 ((1 << MAX_GRAVITY_BIT_NUM) - 1)

#define LOGICAL_CELL_CM_LENGTH		50
#define _3D_CELL_CM_LENGTH			100

// �ر�߶ȼ�����λ(����)
#define ALTITUDE_UNIT				((LOGICAL_CELL_CM_LENGTH) / 4.0f)
#define TERRAIN_MIN_HEIGHT			(-65536.0f / 4.0f * ALTITUDE_UNIT)
#define TERRAIN_MAX_HEIGHT			(65536.0f / 4.0f * ALTITUDE_UNIT)

#define ALTITUDE_TO_XYPOINT(Altitude)   ((Altitude) * 8)
#define ZPOINT_TO_XYPOINT(Z)            ((Z) / 8)
#define XYPOINT_TO_ZPOINT(XY)           ((XY) * 8)
#define ZPOINT_TO_ALTITUDE(Z)           ((Z) / POINT_PER_ALTITUDE)

// �����¶�(45��)
#define KD_STEEP_SLOPE_GRADIENT	(DIRECTION_COUNT / 8)
// ���·������ٶȷ���������������ͨ��
#define KD_STEEP_SLOPE_DIRECTION	(DIRECTION_COUNT / 4)


#define KD_PHYSICS_EARTH_GRAVITY		(DEFAULT_GRAVITY * 98 / 80)	// �����ϵ���������G=9.8m/s^2
#define KD_BASE_JUMP_SPEED				200 // ����õ�G=9.8ʱ��Ծ�߶�2m������
#define KD_BASE_RUN_SPEED					20 // ��8m/s = 32p/f����
#define KD_BASE_SWIM_SPEED              12
#define KD_BASE_WALK_SPEED				8

// �����ϰ��߶Ȳ�
#define CLIMB_ABILITY 	    (XYPOINT_TO_ZPOINT(CELL_LENGTH))
// �Զ�ת��Ծ�߶�
#define CRITICAL_JUMP_HEIGHT        XYPOINT_TO_ZPOINT(CELL_LENGTH * 3)

// �����ƶ�ʱ��λǰ��Ŀ���ľ���,30��
#define MOVE_TARGET_RANGE   (30 * 100 * 32 / 50)

#define MAX_MOVE_STATE_BIT_NUM  5
#define MAX_MOVE_STATE_VALUE    ((1 << MAX_MOVE_STATE_BIT_NUM) - 1)

#define MAX_JUMP_COUNT_BIT 2
#define MAX_JUMP_COUNT ((1 << MAX_JUMP_COUNT_BIT) - 1)

// ���MapID,MapIDȡֵ��Χ(0, MAX_MAP_ID]
#define MAX_MAP_ID 100

// �ϳɵĶ�̬��ͼId
#define DYNAMIC_SCENE_ID(nMapId, nMapCopyIndex) ((nMapId) | (nMapCopyIndex) << 16)

#define GET_SWIM_WATER_LINE(nHeight) ((nHeight) * 7 / 10)
#define IS_UNDER_WATER(nWaterLine, nCharacterHeight) ((nWaterLine) >= (nCharacterHeight) * 9 / 10)

// ��ͼ�ϰ��ͳ�������
#define	SCENE_DIRECTORY		"scene"			// Ŀ¼
#define	KD_REGION_FILE_EXT			".rgn"			// ��׺
#define	SCENE_LIST_FILE			"/scene/scenelist.txt"	// ��ͼ�б�(��ʱ�������Ժ��Ƶ�setting)
#define	MAP_GROUP_FILE			"/setting/scene/mapgroup.txt"
#define KD_SCENE_NPC_FILE			"npc.txt" // ����npc���ļ�
#define KD_SCENE_TRAP_FILE			"trap.txt" // ����trap���ļ�
#define KD_SCENE_DOODAD_FILE	"doodad.txt" // ����doodad�ļ�
#define KD_SCENE_NAVFILE_EXT		".nav"		//�����ļ���׺


//��ͼ��ǵ�ע�ͳ���
#define MAX_MAP_MARK_COMMENT_LEN 32
#define MAX_MIDMAP_MARK_COMMENT_LEN 32

struct KRegionTrapScript 
{
	CHAR szScript[MAX_NAME_LEN];
};

#define MAKE_IN_RANGE(Value, MinValue, MaxValue)        \
	do                                                  \
	{                                                   \
	ASSERT(MinValue <= MaxValue);                   \
	if ((Value) > (MaxValue)) (Value) = (MaxValue); \
	if ((Value) < (MinValue)) (Value) = (MinValue); \
	}                                                   \
	while (false)


//#ifdef GAME_CLIENT
// ��������ת��������
// ��ֹ�ڷ���˵��ã���ֹ���߼���ʹ��3D��������
// ֻ�����ڿͻ����߼�<->�������괫�ݵĽӿڴ�ʹ��
inline BOOL	Logic3DToRepresent3D(INT& rnX, INT& rnY, INT& rnZ)
{
	rnX = rnX * LOGICAL_CELL_CM_LENGTH / CELL_LENGTH;
	rnY = rnY * LOGICAL_CELL_CM_LENGTH / CELL_LENGTH;
	rnZ = INT(rnZ * ALTITUDE_UNIT / POINT_PER_ALTITUDE + TERRAIN_MIN_HEIGHT);

	INT nTmp = rnY;
	rnY = rnZ;
	rnZ = nTmp;

	return TRUE;
}

inline BOOL	Represent3DToLogic3D(INT& rnX, INT& rnY, INT& rnZ)
{
	rnX = rnX * CELL_LENGTH / LOGICAL_CELL_CM_LENGTH;
	rnY = (INT)((rnY - TERRAIN_MIN_HEIGHT) * POINT_PER_ALTITUDE / ALTITUDE_UNIT);
	rnZ = rnZ * CELL_LENGTH / LOGICAL_CELL_CM_LENGTH;

	INT nTmp = rnY;
	rnY = rnZ;
	rnZ = nTmp;

	return TRUE;
}
// ��ÿ֡ ==����ÿ��
inline INT LogicSpeedToRepresentSpeed(INT nSpeed)
{
	return nSpeed * GAME_FPS * LOGICAL_CELL_CM_LENGTH / CELL_LENGTH / 100;
}
// ��ÿ�� ==����ÿ֡
inline INT RepresentSpeedToLogicSpeed(INT nSpeed)
{
	return nSpeed * 100 * CELL_LENGTH / LOGICAL_CELL_CM_LENGTH / GAME_FPS;
}
//#endif // GAME_CLIENT

// -------------------------------------------------------------------------
