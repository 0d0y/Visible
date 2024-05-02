#pragma once


// Singleton ¸ÅÅ©·Î
#define SINGLE(type) public:\
						static type* GetInst()\
					 {\
						static type mgr;\
						return &mgr;\
					 }\
					 private:\
						type();\
						~type();

#define fDT TimeManager::GetInst()->GetfDT()
#define DT TimeManager::GetInst()->GetDT()

#define CLONE(type) type* Clone() {return new type(*this);}

#define KEY_CHECK(key, state) KeyManager::GetInst()->GetKeyState(key) == state
#define KEY_HOLD(key) KEY_CHECK(key, KEY_STATE::HOLD)
#define KEY_TAP(key) KEY_CHECK(key, KEY_STATE::TAP)
#define KEY_AWAY(key) KEY_CHECK(key, KEY_STATE::AWAY)
#define KEY_NONE(key) KEY_CHECK(key, KEY_STATE::NONE)
#define MOUSE_POS KeyManager::GetInst()->GetMousePos()

#define PI 3.1415926535f


enum class GROUP_TYPE
{
	PREVBACKGROUND,  // 0
	BACKGROUND,	     // 1
	DEFAULT,
	TERRAIN,
	GLASSES,
	DRINK,
	THORN,
	SINGPOST,
	SAVEPOINT,
	CLEARPOINT,
	ARROW,
	PLAYER,


	POSTPOPUP = 27, 
	BOUNDARY = 28, 

	UI = 31,
	END = 32
};

enum class SCENE_TYPE
{

	TOOL,
	TITLE,
	SELECT,
	START,
	NARRATIVE_01,
	NARRATIVE_02,
	NARRATIVE_03,
	STAGE_01,
	STAGE_02,
	STAGE_03,
	STAGE_04,

	END

};

enum class EVENT_TYPE
{
	CREATE_OBJECT,
	DELETE_OBJECT,
	SCENE_CHANGE,
	CHANGE_FSM_STATE,

	END,
};

enum class PLAYER_STATE
{
	IDLE,
	WALK,
	JUMP,
	DEAD,
	CLEAR,
	STUCK
};

enum class BRUSH_TYPE
{
	BRUSH_RED,
	BRUSH_GREEN,
	BRUSH_BLUE,
	BRUSH_BLACK,
	BRUSH_WHITE,
	BRUSH_HOLLOW,
	END
};

enum class PEN_TYPE
{
	PEN_RED,
	PEN_GREEN,
	PEN_BLUE,
	PEN_BLACK,
	PEN_WHITE,
	END
};

enum class COLOR_TYPE 
{
	RED,
	GREEN,
	BLUE,
	BLACK,
	WHITE,
	
	NONE,
	EMPTY,



	BLOCK,
};
