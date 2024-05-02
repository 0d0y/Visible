#pragma once
#include "GameObject.h"
class SignPost :
    public GameObject
{

public:
    virtual void Update();

    CLONE(SignPost);

public:
    SignPost(Scene* _ownerScene);
    ~SignPost();
};

