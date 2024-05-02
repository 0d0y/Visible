#include "pch.h"
#include "DimButtonUI.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "Scene.h"

void DimButtonUI::Render(HDC _dc)
{
	BLENDFUNCTION bf = {};
	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.AlphaFormat = 0;
	bf.SourceConstantAlpha = 145;

	AlphaBlend(_dc, 0, 0
		, (int)m_veilTex->Width()
		, (int)m_veilTex->Height()
		, m_veilTex->GetDC()
		, 0, 0
		, (int)m_veilTex->Width()
		, (int)m_veilTex->Height()
		, bf);
}

DimButtonUI::DimButtonUI(bool _bCamAff, Scene* _ownerScene)
	: ButtonUI(_bCamAff, _ownerScene)
	, m_veilTex(nullptr)
{
	Vector2 vResolution = _ownerScene->GetResolution();
	m_veilTex = ResourceManager::GetInst()->CreateTexture(L"cameraVeil", (UINT)vResolution.x, (UINT)vResolution.y);
	

}

DimButtonUI::~DimButtonUI()
{

}
