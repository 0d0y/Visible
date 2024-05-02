#pragma once
#include "GameObject.h"

class Texture;

class Background
	: public GameObject
{
private:
	bool m_bCamAffected;

public:
	virtual void Update();
	virtual void Render(HDC _dc);
	

	CLONE(Background);

	Vector2 GetBgScale();

public:
	Background(bool _bCamAffected, Scene* _ownerScene);
	~Background();
};

