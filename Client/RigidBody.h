#pragma once

class Object;

class RigidBody
{
private:
	GameObject*	m_pOwner;

	Vector2		m_vForce;		// 크기, 방향
	Vector2		m_vAccel;		// 가속도
	Vector2		m_vAccelA;		// 추가 가속도 
	Vector2		m_vVelocity;	// 속도( 크기 : 속력, 방향)
	Vector2		m_vMaxVelocity;	// 최대 속도

	float		m_fMass;		// 질량
	float		m_fFricCoeff;	// 마찰계수


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

