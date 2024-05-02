#include "SelecterUI.h"
#include "Animator.h"
#include "KeyManager.h"

SelecterUI::SelecterUI(bool _bCamAff, Scene* _ownerScene)
	: ImageUI(_bCamAff, _ownerScene)
	, stage(1)
{
	CreateAnimator();
}

SelecterUI::~SelecterUI()
{
}

void SelecterUI::Update()
{
	//update_move();
	ImageUI::Update();
}

void SelecterUI::Render(HDC _dc)
{
	ImageUI::Render(_dc);
}



void SelecterUI::update_move()
{
	if (KEY_TAP(KEY::LEFT))
	{
		if (stage > 1)
			stage--;
	}
	if (KEY_TAP(KEY::RIGHT))
	{
		if (stage < 3)
			stage++;
	}

	switch (stage)
	{
	case 1:
		SetPos(Vector2(230.f, 270.f));
		break;
	case 2:
		SetPos(Vector2(965.f, 470.f));
		break;
	case 3:
		SetPos(Vector2(1670.f, 270.f));
		break;
	}
}

