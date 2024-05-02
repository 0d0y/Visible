#pragma once

class Object;

class RigidBody
{
private:
	GameObject*	m_pOwner;

	Vector2		m_vForce;		// ũ��, ����
	Vector2		m_vAccel;		// ���ӵ�
	Vector2		m_vAccelA;		// �߰� ���ӵ� 
	Vector2		m_vVelocity;	// �ӵ�( ũ�� : �ӷ�, ����)
	Vector2		m_vMaxVelocity;	// �ִ� �ӵ�

	float		m_fMass;		// ����
	float		m_fFricCoeff;	// �������


	// F  = M * A
	// V += A * DT

public:
	void finalupdate();

public:
	void AddForce(Vector2 _vF) { m_vForce += _vF; }
	void SetMass(float _fMass) { m_fMass = _fMass; }
	float GetMass() { return m_fMass; }
	float GetSpeed() { return m_vVelocity.Length(); }
	Vector2 GetVelocity() { return m_vVelocity; }
	Vector2 GetAccel() { return m_vAccel; }
	Vector2 GetAccelA() { return m_vAccelA; }

	void AddVelocity(Vector2 _v) { m_vVelocity += _v; }
	void SetVelocity(Vector2 _v) { m_vVelocity = _v; }
	void SetMaxVelocity(Vector2 _v) { m_vMaxVelocity = _v; }
	void SetAccel(Vector2 _VAccel) { m_vAccel = _VAccel; }
	void SetAccelAlpha(Vector2 _vAccelA) { m_vAccelA = _vAccelA; }

private:
	void Move();

public:
	RigidBody();
	~RigidBody();

	friend class GameObject;
	
public:
	Vector2 GetMaxVelocity() const { return m_vMaxVelocity; }
};

