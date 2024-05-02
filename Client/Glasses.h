#pragma once
#include "ColorObject.h"
class Glasses :
    public ColorObject
{
   

public:
    virtual void Start();
    virtual void Update();

    CLONE(Glasses);

public:
    Glasses(Scene* _ownerScene);
    ~Glasses();
};

