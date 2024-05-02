#pragma once


class SceneManager;

class GameProcess
{
	/// pch.h << define.h에 정의된 매크로 함수 SINGLE, public: 포함되어 있음
	
public:
	GameProcess();
	~GameProcess();

private:
	HWND	m_hWnd;			// 메인 윈도우 핸들
	POINT	m_ptResolution;	// 메인 윈도우 해상도
	HDC		m_hDC;			// 메인 윈도우에 Draw 할 DC

	HBITMAP m_hBit;
	HDC		m_memDC;

private:
	SceneManager* m_sceneManager;


public:
	int Initialize(HWND _hWnd, POINT _ptResolution);
	void Progress();



public:
	HWND GetMainHwnd() { return m_hWnd; }
	HDC GetMainDC() { return m_hDC; }
	HDC GetMemDC() { return m_memDC; }
	POINT GetResolution() { return m_ptResolution; }
	SceneManager* GetSceneManager() { return m_sceneManager; }

};

