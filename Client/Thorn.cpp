#include "pch.h"
#include "Thorn.h"
#include "Collider.h"
#include "SelectGDI.h"
#include "Camera.h"
#include "Collider.h"

Thorn::Thorn(Scene* _ownerScene)
	: ColorObject(_ownerScene)
	, bCanPaint(true)
{
	CreateCollider();
}

Thorn::~Thorn()
{
}

void Thorn::Start()
{
	GetCollider()->SetScale(Vector2(GetScale()));
}

void Thorn::Update()
{
}

void Thorn::Render(HDC _dc)
{
	if (bCanPaint)
		ColorObject::Render(_dc);

}