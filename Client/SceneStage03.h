#pragma once
#include "SceneStage.h"
class Background;

class SceneStage03 :
	public SceneStage
{

private:



public:
	/// ������ virtual�� �������൵ ������ ��������� virtual�� �����ش�.

	virtual void Enter();
	virtual void Exit();


public:

public:
	SceneStage03(HWND _hWnd);
	~SceneStage03();
};