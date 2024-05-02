#include "pch.h"
#include "GameProcess.h"

#include "TimeManager.h"
#include "KeyManager.h"
#include "SceneManager.h"
#include "GameObject.h"
#include "PathManager.h"
#include "CollisionManager.h"
#include "SoundManager.h"
#include "ParseManager.h"
#include "EventManager.h"

#include "Camera.h"
#include "UIManager.h"
#include "ResourceManager.h"
#include "Scene.h"

GameProcess::GameProcess()
	: m_hWnd(0)
	, m_ptResolution{}
	, m_hDC(0)
	, m_hBit(0)
	, m_memDC(0)
	, m_sceneManager(nullptr)
{

}

GameProcess::~GameProcess()
{
	// GetDC�� ���� DC�� ������ ReleaseDC�� ����
	ReleaseDC(m_hWnd, m_hDC);

	// CreateCompatibleDC�� ���� DC�� ������ DeleteDC�� ����
	DeleteDC(m_memDC);
	DeleteObject(m_hBit);


	delete m_sceneManager;

}

int GameProcess::Initialize(HWND _hWnd, POINT _ptResolution)
{
	m_hWnd = _hWnd;
	m_ptResolution = _ptResolution;

	//ȭ�� �ػ� ������
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);
	int WinPosX = screenWidth / 2 - m_ptResolution.x / 2;
	int WinPosY = screenHeight / 2 - m_ptResolution.y / 2;

	// �ػ󵵿� �°� ������ ũ�� ����
	RECT rt = { 0, 0, (long)m_ptResolution.x, (long)m_ptResolution.y };
	AdjustWindowRect(&rt, WS_POPUP, false);
	SetWindowPos(m_hWnd, nullptr, 0 /*WinPosX - 10*/, 0/*WinPosY*/, rt.right - rt.left, rt.bottom - rt.top, 0);

	m_hDC = GetDC(m_hWnd);

	// ���� ���۸� �뵵�� ��Ʈ�ʰ� DC�� �����.
	m_hBit = CreateCompatibleBitmap(m_hDC, (int)m_ptResolution.x, (int)m_ptResolution.y);
	m_memDC = CreateCompatibleDC(m_hDC);

	HBITMAP hOldBit = (HBITMAP)SelectObject(m_memDC, m_hBit);
	DeleteObject(hOldBit);

	
	

	// Manager �ʱ�ȭ
	PathManager::GetInst()->Initialize();
	TimeManager::GetInst()->Initialize();
	KeyManager::GetInst()->Initialize();
	
	ResourceManager::GetInst()->Initialize(m_hDC);
	Camera::GetInst()->Initialize(m_hWnd);
	m_sceneManager = new SceneManager;
	m_sceneManager->Initialize(m_hWnd);
	EventManager::GetInst()->Initialize(this);

	return S_OK;
}


void GameProcess::Progress()
{
	// ==============
	// Manager Update
	// ==============
	TimeManager::GetInst()->Update();
	KeyManager::GetInst()->Update();

	// ī�޶� ������Ʈ

	// ============
	// Scene Update
	// ============
	


	Camera::GetInst()->Update();
	
	m_sceneManager->Update();
	Scene* pCurScene = m_sceneManager->GetCurScene();
	CollisionManager::GetInst()->Update(pCurScene);

	// UI �̺�Ʈ üũ
	UIManager::GetInst()->Update(pCurScene);
	
	
	
	// =========
	// Rendering
	// =========
	// ȭ�� Clear
	// Solid ���� �׷����� �� ����� �� ����� -1, �� �ϴ��� +1
	Rectangle(m_memDC, -1, -1, (int)m_ptResolution.x + 1, (int)m_ptResolution.y + 1);

	m_sceneManager->Render(m_memDC);
	Camera::GetInst()->Render(m_memDC);

	BitBlt(m_hDC, 0, 0, (int)m_ptResolution.x, (int)m_ptResolution.y
		, m_memDC, 0, 0, SRCCOPY);

	TimeManager::GetInst()->Render();
	
	// ===============
	// �̺�Ʈ ���� ó��
	// ===============
	EventManager::GetInst()->Update();
}

