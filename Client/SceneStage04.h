#pragma once
#include "SceneStage.h"
class Background;

class SceneStage04 :
	public SceneStage
{

private:



public:
	/// ������ virtual�� �������൵ ������ ��������� virtual�� �����ش�.

	virtual void Enter();
	virtual void Exit();


public:

public:
	SceneStage04(HWND _hWnd);
	~SceneStage04();
};