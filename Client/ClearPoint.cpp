#include "pch.h"
#include "ClearPoint.h"
#include "SelectGDI.h"
#include "Camera.h"

#include "Texture.h"
#include "ResourceManager.h"
#include "Animator.h"

ClearPoint::ClearPoint(Scene* _ownerScene)
	: ColorObject(_ownerScene)
	, bCanPaint(true)
{
	CreateCollider();
	CreateAnimator();
}

ClearPoint::~ClearPoint()
{
}

void ClearPoint::Update()
{
}

void ClearPoint::Render(HDC _dc)
{
	if (bCanPaint)
		ColorObject::Render(_dc);
}

