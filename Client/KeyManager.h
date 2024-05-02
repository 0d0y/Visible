#pragma once

/// 1. ������ ����ȭ �ʿ�
// ���� ������ ������ ���� Ű�� ����, ������ �̺�Ʈ�� ��������.

/// 2. Ű �Է� �̺�Ʋ ó��
// tap, hold, away

enum class KEY_STATE
{
	NONE,	// ������ �ʰ�, �������� ������ ���� ����
	TAP,	// �� ���� ����
	HOLD,	// ������ �ִ�
	AWAY,	// �� �� ����
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
	KEY_STATE	eState;			// Ű�� ��밪
	bool		bPrevPush;		// ���� �����ӿ��� ���ȴ��� ����
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

