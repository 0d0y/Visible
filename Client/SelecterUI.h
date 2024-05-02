#pragma once
#include "ImageUI.h"
class SelecterUI :
    public ImageUI
{
private:
    UINT stage;
    
public:
    virtual void Update();
    virtual void Render(HDC _dc);

    CLONE(ImageUI);


public:
    void update_move();
public:
    SelecterUI(bool _bCamAff, Scene* _ownerScene);
    ~SelecterUI();
};

