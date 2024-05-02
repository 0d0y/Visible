#pragma once

class GameObject;

class Collider
{ 
private:
	static UINT	g_iNextID;

	GameObject*	m_pOwner;		// collidcer �� �����ϰ� �ִ� ������Ʈ
	Vector2		m_vOffsetPos;	// ������Ʈ�� ���� ������� ��ġ
	Vector2		m_vFinalPos;	// finalupdate���� �� �����Ӹ��� ���

	Vector2		m_vScale;		// �浹ü�� ũ��

	UINT		m_iID;			// �浹ü ������ ID ��
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
	// �浹 ���� �Լ�
	void OnCollision(Collider* _pOther);	// �浹���� ��� ȣ��Ǵ� �Լ�
	void OnCollisionEnter(Collider* _pOther);
	void OnCollisionExit(Collider* _pOther);

	// �ݶ��̴� ���Կ����� ����
	Collider& operator = (Collider& _origin) = delete;

	friend class GameObject;

public:
	Collider();
	Collider(const Collider& _origin);
	~Collider();

};