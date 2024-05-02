#pragma once
#include "GameObject.h"

class Scene;
class Arrow :
    public GameObject
{
private:
	GameObject* m_ownerObject;

public:
	virtual void Update();
	//virtual void Render(HDC _dc);

	void SetOwnerObj(GameObject* _gameObj) { m_ownerObject = _gameObj; }
	GameObject* GetOwnerObj() { return m_ownerObject; }

	CLONE(Arrow);

public:
	Arrow(Scene* _ownerScene);
	~Arrow();

};

