#pragma once
#include "SceneStage.h"

class Background;

class SceneStart : 
	public SceneStage
{

private:



public:
	/// ������ virtual�� �������൵ ������ ��������� virtual�� �����ش�.

	virtual void Enter();
	virtual void Exit();


public:


public:
	SceneStart(HWND _hWnd);
	~SceneStart();
};

