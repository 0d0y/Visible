#pragma once
#include "Scene.h"
class SceneTool :
    public Scene
{
private:

public:
    virtual void Update();
    virtual void Enter();
    virtual void Exit();

public:
    SceneTool(HWND _hWnd);
    ~SceneTool();
};

