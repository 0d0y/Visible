#include "pch.h"
#include "RigidBody.h"

#include "GameObject.h"
#include "TimeManager.h"

RigidBody::RigidBody()
	: m_pOwner(nullptr)
	, m_fMass(1.f)
	, m_fFricCoeff(300.f)
	, m_vMaxVelocity(400.f, 600.f)
{
}

RigidBody::~RigidBody()
{
}

void RigidBody::finalupdate()
{
	float fForce = m_vForce.Length();

	if (0.f != fForce)
	{
		//가속도
		m_vAccel = m_vForce / m_fMass;
	}

	//추가 가속도
	m_vAccel += m_vAccelA;

	//속도
	m_vVelocity += m_vAccel * fDT;

	//마찰력에 의한 반대 방향으로의 가속도
	if (!m_vVelocity.IsZero())
	{
		Vector2 vFircDir = -m_vVelocity;
		vFircDir.Normalize();

		Vector2 vFriction = vFircDir * m_fFricCoeff * fDT;
		if (m_vVelocity.Length() <= vFriction.Length())
		{
			// 마찰 가속도가 본래 속도보다 더 큰 경우
			m_vVelocity = Vector2(0.f, 0.f);
		}
		else
		{
			m_vVelocity += vFriction;
		}
	}

	//속도 제한 검사
	if (abs(m_vMaxVelocity.x) < abs(m_vVelocity.x))
	{
		m_vVelocity.x = (m_vVelocity.x / abs(m_vVelocity.x)) * abs(m_vMaxVelocity.x);
	}
	if (abs(m_vMaxVelocity.y) < abs(m_vVelocity.y))
	{
		m_vVelocity.y = (m_vVelocity.y / abs(m_vVelocity.y)) * abs(m_vMaxVelocity.y);
	}

	//속도에 따른 이동 
	Move();

	// 힘 초기화 
	m_vForce = Vector2(0.f, 0.f);

	//가속도 초기화
	m_vAccel = Vector2(0.f, 0.f);
	m_vAccelA = Vector2(0.f, 0.f);
}

void RigidBody::Move()
{
	Vector2 vPos = m_pOwner->GetPos();

	vPos += m_vVelocity * fDT;

	m_pOwner->SetPos(vPos);
}
