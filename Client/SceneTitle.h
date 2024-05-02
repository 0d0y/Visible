#pragma once
#include "Scene.h"
class SceneTitle :
    public Scene
{

public:
    
    virtual void Update();
    virtual void Enter();
    virtual void Exit();

public:
    SceneTitle(HWND _hWnd);
    ~SceneTitle();
};

