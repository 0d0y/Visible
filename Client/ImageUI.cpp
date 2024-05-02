#include "pch.h"
#include "ImageUI.h"
#include "Texture.h"
#include "GameProcess.h"
#include "Camera.h"
#include "Scene.h"

ImageUI::ImageUI(bool _bCamAff , Scene* _ownerScene)
	: UI(_bCamAff, _ownerScene)
{

}

ImageUI::~ImageUI()
{

}


void ImageUI::Update()
{
	
	UI::Update();
}

void ImageUI::Render(HDC _dc)
{
	Vector2 vPos = GetFinalPos();
	Vector2 vScale = GetScale();

	if (IsCameraAffected())
	{
		vPos = Camera::GetInst()->GetRenderPos(vPos);
	}

	if (GetTex()) {
		TransparentBlt(_dc
			, (int)vPos.x
			, (int)vPos.y
			, (int)vScale.x
			, (int)vScale.y
			, GetTex()->GetDC()
			, 0, 0
			, (int)vScale.x
			, (int)vScale.y
			, RGB(255, 0, 255));

		UI::Render(_dc);
		ComponentRender(_dc);
	}
	
	else {
		
	}
}


void ImageUI::AlignHorizontalCenter()
{	
	Vector2 vScale = GetScale();
	Vector2 vResolution = GetOwnerScene()->GetResolution();
	if (GetParent())
	{
		Vector2 vParentsPos = GetParent()->GetPos();
		Vector2 vParentsScale = GetParent()->GetScale();
		SetPos(Vector2(vParentsScale.x / 2.f - vScale.x / 2.f, GetPos().y));
	}

	else 
	{
		
		SetPos(Vector2(vResolution.x / 2.f - vScale.x / 2.f, GetPos().y));
	}
}

void ImageUI::AlignHorizontalRight()
{
	Vector2 vScale = GetScale();
	Vector2 vResolution = GetOwnerScene()->GetResolution();
	if (GetParent())
	{
		Vector2 vParentsPos = GetParent()->GetPos();
		Vector2 vParentsScale = GetParent()->GetScale();
		SetPos(Vector2(vParentsScale.x - vScale.x, GetPos().y));
	}

	else
	{
		SetPos(Vector2(vResolution.x - vScale.x, GetPos().y));
	}
}

void ImageUI::AlignHorizontalLeft()
{
	Vector2 vScale = GetScale();
	Vector2 vResolution = GetOwnerScene()->GetResolution();
	if (GetParent())
	{
		Vector2 vParentsPos = GetParent()->GetPos();
		SetPos(Vector2(0.f , GetPos().y));
	}

	else
	{
		SetPos(Vector2(0.f, GetPos().y));
	}
}

void ImageUI::AlignVerticalCenter()
{
	Vector2 vScale = GetScale();
	Vector2 vResolution = GetOwnerScene()->GetResolution();
	if (GetParent())
	{
		Vector2 vParentsPos = GetParent()->GetPos();
		Vector2 vParentsScale = GetParent()->GetScale();
		SetPos(Vector2(GetPos().x, vParentsScale.y / 2.f - vScale.y / 2.f));
	}

	else
	{
		SetPos(Vector2(GetPos().x, vResolution.y / 2.f - vScale.y / 2.f));
	}
}

void ImageUI::AlignVerticalTop()
{
	Vector2 vScale = GetScale();
	Vector2 vResolution = GetOwnerScene()->GetResolution();
	if (GetParent())
	{
		Vector2 vParentsPos = GetParent()->GetPos();
		SetPos(Vector2(GetPos().x, 0.f));
	}

	else
	{
		SetPos(Vector2(GetPos().x, 0.f));
	}
}

void ImageUI::AlignVerticalBottom()
{
	Vector2 vScale = GetScale();
	Vector2 vResolution = GetOwnerScene()->GetResolution();
	if (GetParent())
	{
		Vector2 vParentsPos = GetParent()->GetPos();
		Vector2 vParentsScale = GetParent()->GetScale();
		SetPos(Vector2(GetPos().x, vParentsScale.y - vScale.y));
	}

	else
	{
		SetPos(Vector2(GetPos().x, vResolution.y - vScale.y));
	}
}

