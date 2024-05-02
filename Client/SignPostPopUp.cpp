#include "pch.h"
#include "SignPostPopUp.h"
#include "SelectGDI.h"
#include "GameProcess.h"
#include "Collider.h"
#include "Camera.h"
#include "Scene.h"
#include "Texture.h"

SignPostPopUp::SignPostPopUp(Scene* _ownerScene)
	: m_PostPopUp(false)
	, GameObject(_ownerScene)
{
}

SignPostPopUp::~SignPostPopUp()
{
}

void SignPostPopUp::Update()
{
}

void SignPostPopUp::Render(HDC _dc)
{
	if (m_PostPopUp)
	{
		Vector2 vPos = GetPos();
		Vector2 vScale = GetScale();

		TransparentBlt(_dc
			, (int)(vPos.x - vScale.x / 2.f)
			, (int)(vPos.y - vScale.y / 2.f)
			, (int)vScale.x
			, (int)vScale.y
			, GetTex()->GetDC()
			, 0, 0
			, (int)vScale.x
			, (int)vScale.y
			, RGB(255, 0, 255));
	}

}

