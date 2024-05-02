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
		//���ӵ�
		m_vAccel = m_vForce / m_fMass;
	}

	//�߰� ���ӵ�
	m_vAccel += m_vAccelA;

	//�ӵ�
	m_vVelocity += m_vAccel * fDT;

	//�����¿� ���� �ݴ� ���������� ���ӵ�
	if (!m_vVelocity.IsZero())
	{
		Vector2 vFircDir = -m_vVelocity;
		vFircDir.Normalize();

		Vector2 vFriction = vFircDir * m_fFricCoeff * fDT;
		if (m_vVelocity.Length() <= vFriction.Length())
		{
			// ���� ���ӵ��� ���� �ӵ����� �� ū ���
			m_vVelocity = Vector2(0.f, 0.f);
		}
		else
		{
			m_vVelocity += vFriction;
		}
	}

	//�ӵ� ���� �˻�
	if (abs(m_vMaxVelocity.x) < abs(m_vVelocity.x))
	{
		m_vVelocity.x = (m_vVelocity.x / abs(m_vVelocity.x)) * abs(m_vMaxVelocity.x);
	}
	if (abs(m_vMaxVelocity.y) < abs(m_vVelocity.y))
	{
		m_vVelocity.y = (m_vVelocity.y / abs(m_vVelocity.y)) * abs(m_vMaxVelocity.y);
	}

	//�ӵ��� ���� �̵� 
	Move();

	// �� �ʱ�ȭ 
	m_vForce = Vector2(0.f, 0.f);

	//���ӵ� �ʱ�ȭ
	m_vAccel = Vector2(0.f, 0.f);
	m_vAccelA = Vector2(0.f, 0.f);
}

void RigidBody::Move()
{
	Vector2 vPos = m_pOwner->GetPos();

	vPos += m_vVelocity * fDT;

	m_pOwner->SetPos(vPos);
}
