#pragma once
#include "SceneStage.h"

class Background;

class SceneStage02 :
	public SceneStage
{

private:



public:
	/// 원래는 virtual을 안적어줘도 되지만 명시적으로 virtual을 적어준다.

	virtual void Enter();
	virtual void Exit();


public:

public:
	SceneStage02(HWND _hWnd);
	~SceneStage02();
};