#include "pch.h"
#include "Collider.h"

#include "GameObject.h"
#include "GameProcess.h"

#include "SelectGDI.h"
#include "Camera.h"

UINT Collider::g_iNextID = 0;

Collider::Collider()
	: m_pOwner(nullptr)
	, m_iID(g_iNextID++)
	, m_iCol(0)
{

}

Collider::Collider(const Collider& _origin)
	: m_pOwner(nullptr)
	, m_vOffsetPos(_origin.m_vOffsetPos)
	, m_vScale(_origin.m_vScale)
	, m_iID(g_iNextID++)
	, m_iCol(0)
{

}

Collider::~Collider()
{

}


void Collider::finalupdate()
{
	//Object의 위치를 따라간다.
	Vector2 vObjectPos = m_pOwner->GetPos();
	m_vFinalPos = vObjectPos + m_vOffsetPos;

	assert(0 <= m_iCol);
}

void Collider::render(HDC _dc)
{
	PEN_TYPE ePen = PEN_TYPE::PEN_GREEN;

	if (m_iCol)
		ePen = PEN_TYPE::PEN_RED;

	SelectGDI::GetInst()->SelectPen(_dc, ePen);
	SelectGDI::GetInst()->SelectBrush(_dc, BRUSH_TYPE::BRUSH_HOLLOW);

	Vector2 vRenderPos = Camera::GetInst()->GetRenderPos(m_vFinalPos);

	Rectangle(_dc
		, (int)(vRenderPos.x - m_vScale.x / 2.0f)
		, (int)(vRenderPos.y - m_vScale.y / 2.0f)
		, (int)(vRenderPos.x + m_vScale.x / 2.0f)
		, (int)(vRenderPos.y + m_vScale.y / 2.0f));

	SelectGDI::GetInst()->ReturnGDI(_dc);
}

void Collider::OnCollision(Collider* _pOther)
{
	m_pOwner->OnCollision(_pOther);
}

void Collider::OnCollisionEnter(Collider* _pOther)
{
	++m_iCol;
	m_pOwner->OnCollisionEnter(_pOther);
}

void Collider::OnCollisionExit(Collider* _pOther)
{
	--m_iCol;
	m_pOwner->OnCollisionExit(_pOther);
}
