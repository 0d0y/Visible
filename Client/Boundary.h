#pragma once
#include "GameObject.h"
class Boundary :
	public GameObject
{

private:
	Vector2 m_vDir;

public:
	virtual void Update();
	virtual void Render(HDC _dc);

	CLONE(Boundary);


public:
	virtual void OnCollisionEnter(Collider* _pOther);

public:

	Boundary(Vector2 _vDir, Collider* _pPlayerCollider, Scene* _ownerScene);
	~Boundary();
};
