#pragma once
#include "SceneStage.h"

class Background;

class SceneStage02 :
	public SceneStage
{

private:



public:
	/// ������ virtual�� �������൵ ������ ��������� virtual�� �����ش�.

	virtual void Enter();
	virtual void Exit();


public:

public:
	SceneStage02(HWND _hWnd);
	~SceneStage02();
};