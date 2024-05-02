#include "pch.h"
#include "GameObject.h"

#include "Collider.h"
#include "Animator.h"
#include "RigidBody.h"
#include "Gravity.h"
#include "Terrain.h"

#include "Fsm.h"
#include "Camera.h"
#include "Texture.h"
#include "SelectGDI.h"

GameObject::GameObject(Scene* _ownerScene)
	: m_strName{}
	, m_vPos{}
	, m_vScale{}
	, m_pCollider(nullptr)
	, m_pAnimator(nullptr)
	, m_pRigidBody(nullptr)
	, m_pGravity(nullptr)
	, m_bAlive(true)
	, m_pFsm(nullptr)
	, m_pTex(nullptr)
	, m_ownerScene(_ownerScene)
{

}

GameObject::GameObject(const GameObject& _origin)
	: m_strName{ _origin.m_strName }
	, m_vPos(_origin.m_vPos)
	, m_vScale(_origin.m_vScale)
	, m_pCollider(nullptr)
	, m_pAnimator(nullptr)
	, m_pRigidBody(nullptr)
	, m_pGravity(nullptr)
	, m_pFsm(_origin.m_pFsm)
	, m_bAlive(true)
	, m_pTex(_origin.m_pTex)
	, m_ownerScene(_origin.m_ownerScene)

{
	if (_origin.m_pCollider)
	{
		m_pCollider = new Collider(*(_origin.m_pCollider));
		m_pCollider->m_pOwner = this;
	}

	if (_origin.m_pAnimator)
	{
		m_pAnimator = new Animator(*_origin.m_pAnimator);
		m_pAnimator->m_pOwner = this;
	}

	if (_origin.m_pRigidBody)
	{
		m_pRigidBody = new RigidBody(*_origin.m_pRigidBody);
		m_pRigidBody->m_pOwner = this;
	}

	if (_origin.m_pGravity)
	{
		m_pGravity = new Gravity(*_origin.m_pGravity);
		m_pGravity->m_pOwner = this;
	}
}

GameObject::~GameObject()
{
	if (nullptr != m_pCollider)
		delete m_pCollider;
	if (nullptr != m_pAnimator)
		delete m_pAnimator;
	if (nullptr != m_pRigidBody)
		delete m_pRigidBody;	
	if (nullptr != m_pGravity)
		delete m_pGravity;
}

void GameObject::CreateCollider()
{
	m_pCollider = new Collider;
	m_pCollider->m_pOwner = this;
}

void GameObject::CreateAnimator()
{
	m_pAnimator = new Animator;
	m_pAnimator->m_pOwner = this;
}

void GameObject::CreateRigidBody()
{
	m_pRigidBody = new RigidBody;
	m_pRigidBody->m_pOwner = this;
}

void GameObject::CreateGravity()
{
	m_pGravity = new Gravity;
	m_pGravity->m_pOwner = this;
}

void GameObject::FinalUpdate()
{
	
	if (m_pAnimator)
		m_pAnimator->finalupdate();
	
	if (m_pGravity)
		m_pGravity->finalupdate();

	if (m_pRigidBody)
		m_pRigidBody->finalupdate();

	if (m_pCollider)
		m_pCollider->finalupdate();
}

void GameObject::SetFsm(Fsm* _Fsm)
{
	m_pFsm = _Fsm;
	m_pFsm->m_pOwner = this;
}

void GameObject::Render(HDC _dc)
{
	if (GetTex()) {
		Vector2 vPos = GetPos();
		Vector2 vScale = GetScale();
		vPos = Camera::GetInst()->GetRenderPos(vPos);

		TransparentBlt(_dc
			, (int)(vPos.x - vScale.x / 2.f)
			, (int)(vPos.y - vScale.y / 2.f)
			, (int)vScale.x
			, (int)vScale.y
			, GetTex()->GetDC()
			, 0, 0
			, (int)vScale.x
			, (int)vScale.y
			, RGB(255, 0, 255));
	ComponentRender(_dc);
	}
	else
	{
		Vector2 vPos = GetPos();
		Vector2 vScale = GetScale();
		vPos = Camera::GetInst()->GetRenderPos(vPos);
		SelectGDI::GetInst()->GetPen(PEN_TYPE::PEN_BLUE);
		SelectGDI::GetInst()->GetBrush(BRUSH_TYPE::BRUSH_BLUE);
		Rectangle(_dc
			, (int)(vPos.x - vScale.x / 2.f)
			, (int)(vPos.y - vScale.y / 2.f)
			, (int)(vPos.x + vScale.x / 2.f)
			, (int)(vPos.y + vScale.y / 2.f));
		SelectGDI::GetInst()->ReturnGDI(_dc);
	ComponentRender(_dc);
	}
}

void GameObject::ComponentRender(HDC _dc)
{
	if (nullptr != m_pCollider)
	{
	//	m_pCollider->render(_dc);
	}

	if (nullptr != m_pAnimator)
	{
		m_pAnimator->render(_dc);
	}
}


void GameObject::SetTexScale()
{
	assert(m_pTex && "텍스쳐 먼저 만들고 써죵!!");
	if (m_pTex) {
		UINT iWidth = m_pTex->Width();
		UINT iHeight = m_pTex->Height();

		SetScale(Vector2((float)iWidth, (float)iHeight));
	}
}