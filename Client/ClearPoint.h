#pragma once
#include "ColorObject.h"

class ClearPoint:
    public ColorObject
{
private:
    bool bCanPaint;

public:
    virtual void Update();
    virtual void Render(HDC _dc);

    CLONE(ClearPoint);

public:
    ClearPoint(Scene* _ownerScene);
    ~ClearPoint();

public:
    bool GetbCanPaint() { return bCanPaint; }
    void SetbCanPaint(bool bPaint) { bCanPaint = bPaint; }
};

