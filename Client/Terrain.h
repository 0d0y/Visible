#pragma once
#include "ColorObject.h"

class Terrain
	:public ColorObject
{
private:
	bool bCanPaint;


public:
	virtual void Start();
	virtual void Update();
	virtual void Render(HDC _dc);

public:
	virtual void OnCollisionEnter(Collider* _pOther);
	virtual void OnCollision(Collider* _pOther);
	virtual void OnCollisionExit(Collider* _pOther);


	CLONE(Terrain);

public:
	Terrain(Scene* _ownerScene);
	~Terrain();

public:
	bool GetbCanPaint() { return bCanPaint; }
	void SetbCanPaint(bool bPaint) { bCanPaint = bPaint; }
	void HandleCollision(Collider* _pOther);
};

