#pragma once
#include "Scene.h"
class SceneNarrative01 :
    public Scene
{


public:
    virtual void Update();
    virtual void Enter();
    virtual void Exit();
public:
    SceneNarrative01(HWND _hWnd);
    ~SceneNarrative01();
};

