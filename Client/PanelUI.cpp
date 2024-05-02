#include "pch.h"
#include "PanelUI.h"
#include "KeyManager.h"


PanelUI::PanelUI(Scene* _ownerScene)
	: UI(false, _ownerScene)
{

}

PanelUI::~PanelUI()
{

}

void PanelUI::MouseOn()
{
	if (IsLbtnDown())
	{
		Vector2 vDiff = MOUSE_POS - m_vDragStart;

		Vector2 vCurPos = GetPos();
		vCurPos += vDiff;
		SetPos(vCurPos);

		m_vDragStart = MOUSE_POS;
	}
}

void PanelUI::MouseLbtnDown()
{
	m_vDragStart = MOUSE_POS;
}

void PanelUI::MouseLbtnUp()
{

}
