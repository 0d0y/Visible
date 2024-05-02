#include "pch.h"
#include "Background.h"
#include "GameProcess.h"
#include "Camera.h"
#include "Texture.h"
#include "Animator.h"



Background::Background(bool _bCamAffected, Scene* _ownerScene)
	: m_bCamAffected(_bCamAffected)
	, GameObject(_ownerScene)
{
	CreateAnimator();
}

Background::~Background()
{

}

void Background::Update()
{

}


void Background::Render(HDC _dc)
{
	Vector2 vPos = GetPos();
	Vector2 vScale = GetScale();

	if(m_bCamAffected)
	vPos = Camera::GetInst()->GetRenderPos(vPos);
	BitBlt(_dc
		, (int)(vPos.x)
		, (int)(vPos.y)
		, (int)(vScale.x)
		, (int)(vScale.y)
		, GetTex()->GetDC()
		, 0, 0, SRCCOPY);

	ComponentRender(_dc);

}

Vector2 Background::GetBgScale()
{
	assert(GetTex());
	if (GetTex())
		return Vector2((float)GetTex()->Width(), (float)GetTex()->Height());
	else
		return Vector2(0.f, 0.f);
}

