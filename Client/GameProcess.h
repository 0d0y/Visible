#pragma once


class SceneManager;

class GameProcess
{
	/// pch.h << define.h�� ���ǵ� ��ũ�� �Լ� SINGLE, public: ���ԵǾ� ����
	
public:
	GameProcess();
	~GameProcess();

private:
	HWND	m_hWnd;			// ���� ������ �ڵ�
	POINT	m_ptResolution;	// ���� ������ �ػ�
	HDC		m_hDC;			// ���� �����쿡 Draw �� DC

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

