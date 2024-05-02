#include "pch.h"
#include "UI.h"

#include "Camera.h"
#include "KeyManager.h"

#include "SelectGDI.h"


UI::UI(bool _bCamAff, Scene* _ownerScene)
	: m_pParentUI(nullptr)
	, m_bCamAffected(_bCamAff)
	, m_bMouseOn(false)
	, m_bLbtnDown(false)
	, GameObject(_ownerScene)
{

}

UI::UI(const UI& _origin)
	: GameObject(_origin)
	, m_pParentUI(nullptr)
	, m_bCamAffected(_origin.m_bCamAffected)
	, m_bMouseOn(false)
	, m_bLbtnDown(false)
{
	for (size_t i = 0; i < _origin.m_vecChildUI.size(); ++i)
	{
		AddChild(_origin.m_vecChildUI[i]->Clone());
	}
}


UI::~UI()
{
	SafeDeleteVector(m_vecChildUI);
}

void UI::Update()
{


	update_child();
}

void UI::FinalUpdate()
{
	GameObject::FinalUpdate();

	m_vFinalPos = GetPos();
	//UI의 최종 좌표를 구한다. 
	if (GetParent())
	{
		Vector2 vParentPos = GetParent()->GetFinalPos();
		m_vFinalPos += vParentPos;
	}

	MouseOnCheck();


	finalupdate_child();
}

void UI::Render(HDC _dc)
{
// 	Vec2 vPos = GetFinalPos();
// 	Vec2 vScale = GetScale();
// 
// 	if (m_bCamAffected)
// 	{
// 		vPos = CCamera::GetInst()->GetRenderPos(vPos);
// 	}
// 
// 
// 	if (m_bLbtnDown)
// 	{
// 		SelectGDI p = SelectGDI(_dc, PEN_TYPE::PEN_GREEN);
// 		Rectangle(_dc
// 			, (int)(vPos.x)
// 			, (int)(vPos.y)
// 			, (int)(vPos.x + vScale.x)
// 			, (int)(vPos.y + vScale.y));
// 	}
// 	else
// 	{
// 		Rectangle(_dc
// 			, (int)(vPos.x)
// 			, (int)(vPos.y)
// 			, (int)(vPos.x + vScale.x)
// 			, (int)(vPos.y + vScale.y));
// 	}
	// child UI render
	render_child(_dc);
}

void UI::update_child()
{
	for (size_t i = 0; i < m_vecChildUI.size(); ++i) {
		m_vecChildUI[i]->Update();
	}
}

void UI::finalupdate_child()
{
	for (size_t i = 0; i < m_vecChildUI.size(); ++i) {
		m_vecChildUI[i]->FinalUpdate();
	}
}

void UI::render_child(HDC _dc)
{
	for (size_t i = 0; i < m_vecChildUI.size(); ++i) {
		m_vecChildUI[i]->Render(_dc);
	}
}


void UI::MouseOnCheck()
{
	Vector2 vMousePos = MOUSE_POS;

	if (m_bCamAffected)
		vMousePos = Camera::GetInst()->GetRenderPos(vMousePos);

	Vector2 vScale = GetScale();
	if (m_vFinalPos.x <= vMousePos.x && m_vFinalPos.x + vScale.x >= vMousePos.x
		&& m_vFinalPos.y <= vMousePos.y && m_vFinalPos.y + vScale.y >= vMousePos.y)
	{
		m_bMouseOn = true;
	}
	else
	{
		m_bMouseOn = false;
	}
}



void UI::MouseOn()
{

}

void UI::MouseLbtnDown()
{

}

void UI::MouseLbtnUp()
{

}

void UI::MouseLbtnClick()
{

}
