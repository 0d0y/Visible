#pragma once
#include "ButtonUI.h"

class Texture;


class DimButtonUI :
    public ButtonUI
{
private:
    Texture* m_veilTex;

public:
    virtual void Render(HDC _dc);

    CLONE(DimButtonUI);
public:
    DimButtonUI(bool _bCamAff, Scene* _ownerScene);
    ~DimButtonUI();
};

