#include "pch.h"
#include "SavePoint.h"
#include "SelectGDI.h"
#include "Camera.h"

#include "Texture.h"
#include "ResourceManager.h"

#include "Collider.h"
#include "Animator.h"
#include "Animation.h"

SavePoint::SavePoint(Scene* _ownerScene)
	: GameObject(_ownerScene)
	, onSave(false)
{
	CreateCollider();
	CreateAnimator();
}

SavePoint::~SavePoint()
{
}

void SavePoint::Update()
{
	if (!onSave)
	{
		GetAnimator()->GetCurAnim()->SetFrame(0);
	}
	else
	{
		if (GetAnimator()->GetCurAnim()->GetCurFrame() == 3)
		{
			GetAnimator()->GetCurAnim()->SetFrame(3);
		}

		GetCollider()->SetOffsetPos(Vector2(0.f, 10000.f));//이게 맞나..
	}
}

void SavePoint::OnCollisionEnter(Collider* _pOther)
{
	GameObject* pOtherObj = _pOther->GetObj();
	if (pOtherObj->GetName() == L"Player")
	{
		onSave = true;
	}
}