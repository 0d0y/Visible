#pragma once

class GameObject;

class Collider
{ 
private:
	static UINT	g_iNextID;

	GameObject*	m_pOwner;		// collidcer 를 소유하고 있는 오브젝트
	Vector2		m_vOffsetPos;	// 오브젝트로 부터 상대적인 위치
	Vector2		m_vFinalPos;	// finalupdate에서 매 프레임마다 계산

	Vector2		m_vScale;		// 충돌체의 크기

	UINT		m_iID;			// 충돌체 고유한 ID 값
	int			m_iCol;

public:
	void SetOffsetPos(Vector2 _vPos) { m_vOffsetPos = _vPos; }
	void SetScale(Vector2 _vScale) { m_vScale = _vScale; }

	Vector2 GetOffsetPos() { return m_vOffsetPos; }
	Vector2 GetScale() { return m_vScale; }

	Vector2 GetFinalPos() { return m_vFinalPos; }

	GameObject* GetObj() { return m_pOwner; }

	UINT GetID() { return m_iID; }

	int GetiCol() { return m_iCol; }

	const Vector2 GetLeftTop() const { return Vector2{ m_vFinalPos.x - m_vScale.x / 2.f, m_vFinalPos.y - m_vScale.y / 2.f }; }
	const Vector2 GetRightTop() const { return Vector2{ m_vFinalPos.x + m_vScale.x / 2.f, m_vFinalPos.y - m_vScale.y / 2.f }; }
	const Vector2 GetLeftBottom() const { return Vector2{ m_vFinalPos.x - m_vScale.x / 2.f, m_vFinalPos.y + m_vScale.y / 2.f }; }
	const Vector2 GetRightBottom() const { return Vector2{ m_vFinalPos.x + m_vScale.x / 2.f , m_vFinalPos.y + m_vScale.y / 2.f }; }

public:
	void finalupdate();
	void render(HDC _dc);

public:
	// 충돌 시점 함수
	void OnCollision(Collider* _pOther);	// 충돌중인 경우 호출되는 함수
	void OnCollisionEnter(Collider* _pOther);
	void OnCollisionExit(Collider* _pOther);

	// 콜라이더 대입연산자 삭제
	Collider& operator = (Collider& _origin) = delete;

	friend class GameObject;

public:
	Collider();
	Collider(const Collider& _origin);
	~Collider();

};