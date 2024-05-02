#pragma once
#include "Scene.h"
class SceneNarrative03 :
	public Scene
{


public:
	virtual void Update();
	virtual void Enter();
	virtual void Exit();
public:
	SceneNarrative03(HWND _hWnd);
	~SceneNarrative03();
};

