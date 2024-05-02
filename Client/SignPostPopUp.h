#pragma once
#include "GameObject.h"
class SignPostPopUp :
    public GameObject
{
private:
    bool    m_PostPopUp;
    friend class Player;

public:
    virtual void Update();
    virtual void Render(HDC _dc);

public:
    void SetPostPopUp(bool _trigger) { m_PostPopUp = _trigger; }

    CLONE(SignPostPopUp);

public:
    SignPostPopUp(Scene* _ownerScene);
    ~SignPostPopUp();

};

