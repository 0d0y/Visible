#pragma once
#include "Scene.h"
class SceneNarrative02 :
	public Scene
{


public:
	virtual void Update();
	virtual void Enter();
	virtual void Exit();
public:
	SceneNarrative02(HWND _hWnd);
	~SceneNarrative02();
};

