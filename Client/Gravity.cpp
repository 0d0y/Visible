#include "pch.h"
#include "Gravity.h"

#include "GameObject.h"
#include "RigidBody.h"
#include "Collider.h"
#include "Player.h"

Gravity::Gravity()
	: m_pOwner(nullptr)
	, m_bGround(false)
{
}

Gravity::~Gravity()
{
}

void Gravity::SetGround(bool _b)
{
	m_bGround = _b;
	if (m_bGround)
	{
		Vector2 vV = m_pOwner->GetRigidBody()->GetVelocity();
		m_pOwner->GetRigidBody()->SetVelocity(Vector2(vV.x, 0.f));
	}
}

void Gravity::finalupdate()
{
	m_pOwner->GetRigidBody()->SetAccelAlpha(Vector2(0.f, 800.f));
}
