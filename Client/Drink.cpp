#include "pch.h"
#include "Drink.h"
#include "SelectGDI.h"
#include "Camera.h"
#include "ResourceManager.h"
#include "Animator.h"
#include "Texture.h"
#include "Collider.h"

Drink::Drink(Scene* _ownerScene)
	: ColorObject(_ownerScene)
{
	CreateCollider();
	CreateAnimator();
}

Drink::~Drink()
{
}

void Drink::Start()
{
	GetCollider()->SetScale(Vector2(GetScale()));
}

void Drink::Update()
{
}


