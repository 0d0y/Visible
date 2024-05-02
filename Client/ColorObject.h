#pragma once
#include "GameObject.h"

class ColorObject :
    public GameObject
{
private:
    COLOR_TYPE  m_eColorState;
    


public:
    //virtual void Render(HDC _dc);


public:
    void SetColorState(COLOR_TYPE _eState) { m_eColorState = _eState; }
    COLOR_TYPE GetColorState() { return m_eColorState; }

public:
    ColorObject(Scene* _ownerScene);
    ~ColorObject();
};

