#pragma once
#include "ColorObject.h"
class Drink :
    public ColorObject
{
private:

public:
    virtual void Start();
    virtual void Update();

    CLONE(Drink);

public:
    Drink(Scene* _ownerScene);
    ~Drink();
};

