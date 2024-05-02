#include "pch.h"
#include "KeyManager.h"

#include "GameProcess.h"

int g_arrVK[(int)KEY::LAST] =
{
	VK_LEFT,		//LEFT,
	VK_RIGHT,		//RIGHT,
	VK_UP,			//UP,
	VK_DOWN,		//DOWN,

	'Q',
	'W',
	'E',
	'R',
	'T',
	'Y',
	'U',
	'I',
	'O',
	'P',
	'A',
	'S',
	'D',
	'F',
	'G',
	'H',
	'J',
	'K',
	'L',
	'Z',
	'X',
	'C',
	'V',
	'B',
	'N',
	'M',

	VK_MENU,		//ALT,
	VK_CONTROL,		//CTRL,
	VK_LSHIFT,		//LSHIFT,
	VK_SPACE,		//SPACE,
	VK_RETURN,		//ENTER,
	VK_ESCAPE,		//ESC,
	VK_F1,
	VK_F2,
	VK_F3,
	VK_F4,
	VK_F5,

	VK_LBUTTON,		// ���콺 ���� ��ư
	VK_RBUTTON,		// ���콺 ������ ��ư
	//LAST
};

KeyManager::KeyManager()
{}

KeyManager::~KeyManager()
{}

void KeyManager::Initialize()
{
	for (int i = 0; i < (int)KEY::LAST; ++i)
	{
		m_vecKey.push_back(tKeyInfo{ KEY_STATE::NONE, false });
	}

	//m_vecKey[(int)KEY::LEFT].eState;
	//m_vecKey[(int)KEY::LEFT].bPrev;
}

void KeyManager::Update()
{
	// ������ ��Ŀ�� �˾Ƴ���
	//HWND hMainhWnd = CCore::GetInst()->GetMainHwnd();
	HWND hWnd = GetFocus();

	// ������ ��Ŀ�� ���� �� Ű �̺�Ʈ ����
	if (nullptr != hWnd)
	{
		for (int i = 0; i < (int)KEY::LAST; ++i)
		{
			if (GetAsyncKeyState(g_arrVK[i]) & 0x8000)
			{
				if (m_vecKey[i].bPrevPush)
				{
					// �������� ���� �־���.
					m_vecKey[i].eState = KEY_STATE::HOLD;
				}
				else
				{
					// �������� �������� �ʾҴ�.
					m_vecKey[i].eState = KEY_STATE::TAP;
				}

				m_vecKey[i].bPrevPush = true;
			}

			// Ű�� �ȴ����ִ�.
			else
			{
				if (m_vecKey[i].bPrevPush)
				{
					// ������ ���� �־���.
					m_vecKey[i].eState = KEY_STATE::AWAY;
				}
				else
				{
					// �������� �������� �־���
					m_vecKey[i].eState = KEY_STATE::NONE;
				}

				m_vecKey[i].bPrevPush = false;
			}
		}
		// Mouse ��ġ ��� 
		POINT ptPos = {};
		GetCursorPos(&ptPos);
		ScreenToClient(hWnd, &ptPos);

		m_vCurMousePos = Vector2((float)ptPos.x, (float)ptPos.y);
	}

	// ������ ��Ŀ�� ���� ����
	else
	{
		for (int i = 0; i < (int)KEY::LAST; ++i)
		{
			m_vecKey[i].bPrevPush = false;

			if (KEY_STATE::TAP == m_vecKey[i].eState || KEY_STATE::HOLD == m_vecKey[i].eState || KEY_STATE::TAP == m_vecKey[i].eState)
			{
				m_vecKey[i].eState = KEY_STATE::AWAY;
			}
			else if (KEY_STATE::AWAY == m_vecKey[i].eState)
			{
				m_vecKey[i].eState = KEY_STATE::NONE;
			}
		}

	}

	
}