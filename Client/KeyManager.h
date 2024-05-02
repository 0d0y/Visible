#pragma once

/// 1. 프레임 동기화 필요
// 동일 프레임 내에서 같은 키에 대해, 동일한 이벤트를 가져간다.

/// 2. 키 입력 이벤틀 처리
// tap, hold, away

enum class KEY_STATE
{
	NONE,	// 눌리지 않고, 이전에도 눌리지 않은 상태
	TAP,	// 막 누른 시점
	HOLD,	// 누르고 있는
	AWAY,	// 막 뗀 시점
};

enum class KEY
{
	LEFT,
	RIGHT,
	UP,
	DOWN,

	Q,
	W,
	E,
	R,
	T,
	Y,
	U,
	I,
	O,
	P,
	A,
	S,
	D,
	F,
	G,
	H,
	J,
	K,
	L,
	Z,
	X,
	C,
	V,
	B,
	N,
	M,

	ALT,
	CTRL,
	LSHIFT,
	SPACE,
	ENTER,
	ESC,
	F1,
	F2,
	F3,
	F4,
	F5,

	LBTN,
	RBTN,

	LAST
};

struct tKeyInfo
{
	KEY_STATE	eState;			// 키의 상대값
	bool		bPrevPush;		// 이전 프레임에서 눌렸는지 여부
};

class KeyManager
{
	SINGLE(KeyManager);
private:
	vector<tKeyInfo> m_vecKey;
	Vector2 m_vCurMousePos;

public:
	void Initialize();
	void Update();

public:
	KEY_STATE GetKeyState(KEY _eKey) { return m_vecKey[(int)_eKey].eState; }

	Vector2 GetMousePos() { return m_vCurMousePos; }
};

