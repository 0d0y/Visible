#pragma once
#include <windows.h>

class Scene;



class SceneManager
{

public:
	SceneManager();
	~SceneManager();

private:
	HWND  m_hWnd;
	Scene* m_arrScene[(UINT)SCENE_TYPE::END];	// ¸ðµç ¾À ¸ñ·Ï
	Scene* m_pCurScene;						// ÇöÀç ¾À

public:
	void Initialize(HWND _hWnd);
	void Update();
	void Render(HDC _dc);

public:
	Scene* GetCurScene() { return m_pCurScene; }	
	SCENE_TYPE GetCurSceneType()
	{
		int i = 0;
		for (; i < (int)SCENE_TYPE::END; ++i) {
			if (m_pCurScene == m_arrScene[i])
				break;
		}
		return (SCENE_TYPE)i;
	}

private:
	void ChangeScene(SCENE_TYPE _eNext);
	friend class EventManager;
};

