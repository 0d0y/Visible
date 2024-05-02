#pragma once
#include "UI.h"
class PanelUI :
	public UI
{

private:
	Vector2    m_vDragStart;

public:
	virtual void MouseOn();
	virtual void MouseLbtnDown();
	virtual void MouseLbtnUp();

	CLONE(PanelUI);

public:
	PanelUI(Scene* _ownerScene);
	~PanelUI();
};

