#pragma once
#include "pch.h"

class Collider;
class Animator;
class RigidBody;
class Gravity;
class Terrain;
class Player;
class Scene;
class Texture;

class GameObject
{
private:
	wstring		m_strName;
	Vector2		m_vPos;
	Vector2		m_vScale;

	Scene* m_ownerScene;

	Collider* m_pCollider;
	Animator* m_pAnimator;
	RigidBody* m_pRigidBody;
	Gravity* m_pGravity;

	Fsm* m_pFsm;

	bool m_bAlive;

	Texture* m_pTex;


public:
	void SetPos(Vector2 _vPos) { m_vPos = _vPos; }
	void SetScale(Vector2 _vScale) { m_vScale = _vScale; }

	Vector2 GetPos() { return m_vPos; }
	Vector2 GetScale() { return m_vScale; }

	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }

	Scene* GetOwnerScene() { return m_ownerScene; }
	void SetOwnerScene(Scene* _scene) { m_ownerScene = _scene; }
	Collider* GetCollider() { return m_pCollider; }
	void SetCollider(Collider* _col) { m_pCollider = _col; }
	Animator* GetAnimator() { return m_pAnimator; }
	RigidBody* GetRigidBody() { return m_pRigidBody; }
	Gravity* GetGravity() { return m_pGravity; }


	Texture* GetTex() { return m_pTex; }
	void SetTex(Texture* _pTex) { m_pTex = _pTex; };

	bool IsDead() { return !m_bAlive; }

	void CreateCollider();
	void CreateAnimator();
	void CreateRigidBody();
	void CreateGravity();

	virtual void OnCollision(Collider* _pOther) {}
	virtual void OnCollisionEnter(Collider* _pOther) {}
	virtual void OnCollisionExit(Collider* _pOther) {}

private:
	void SetDead() { m_bAlive = false; }


public:
	Fsm* GetFsm() { return m_pFsm; }
	void SetFsm(Fsm* _Fsm);

public:
	virtual void Start() {}; //Scene이 시작되기 직전에 호출되는 함수
	virtual void Update() = 0;
	virtual void FinalUpdate();
	virtual void Render(HDC _dc);

	void ComponentRender(HDC _dc);


	void SetTexScale();
	virtual GameObject* Clone() = 0;

public:
	GameObject(const GameObject& _origin);
	GameObject(Scene* _ownerScene);
	virtual ~GameObject();

	friend class EventManager;
};

