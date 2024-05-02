#pragma once
#include "GameObject.h"

class SavePoint :
    public GameObject
{
private:
    bool onSave;

public:
    virtual void Update();
    virtual void OnCollisionEnter(Collider* _pOther);

    CLONE(SavePoint);

public:
    SavePoint(Scene* _ownerScene);
    ~SavePoint();
};

