#pragma once
#include "SceneStage.h"

class Background;

class SceneStage01 :
	public SceneStage
{

private:



public:
	/// ������ virtual�� �������൵ ������ ��������� virtual�� �����ش�.

	virtual void Enter();
	virtual void Exit();


public:



public:
	SceneStage01(HWND _hWnd);
	~SceneStage01();
};