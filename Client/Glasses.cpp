#include "pch.h"
#include "Glasses.h"
#include "SelectGDI.h"
#include "Camera.h"
#include "Collider.h"

Glasses::Glasses(Scene* _ownerScene)
	:ColorObject(_ownerScene)
{
	CreateCollider();
}


Glasses::~Glasses()
{
}

void Glasses::Start()
{
	GetCollider()->SetScale(Vector2(GetScale()));
}

void Glasses::Update()
{
}


