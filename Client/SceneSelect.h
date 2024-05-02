#pragma once
#include "Scene.h"
class SceneSelect :
    public Scene
{

public:

	virtual void Update();
	virtual void Enter();
	virtual void Exit();

public:
	SceneSelect(HWND _hWnd);
	~SceneSelect();
};

