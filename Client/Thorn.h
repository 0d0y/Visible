#pragma once
#include "ColorObject.h"
class Thorn :
    public ColorObject
{
private:
    bool bCanPaint;


public:
    virtual void Start();
    virtual void Update();
    virtual void Render(HDC _dc);

    CLONE(Thorn);

public:
    Thorn(Scene* _ownerScene);
    ~Thorn();

public:
    bool GetbCanPaint() { return bCanPaint; }
    void SetbCanPaint(bool bPaint) { bCanPaint = bPaint; }
};

