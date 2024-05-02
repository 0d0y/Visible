#include "pch.h"
#include "Boundary.h"
#include "Camera.h"
#include "GameProcess.h"
#include "Collider.h"
#include "SceneManager.h"
#include "Scene.h"

void Boundary::OnCollisionEnter(Collider* _other)
{

	Vector2 vCurrLookAt = Camera::GetInst()->GetFinalLookAt();
	Camera::GetInst()->SetLookAt(vCurrLookAt + m_vDir * GetOwnerScene()->GetResolution());

	Scene* pCurScene = GetOwnerScene();
	const vector<GameObject*>& vecBound = pCurScene->GetGroupObject(GROUP_TYPE::BOUNDARY);

	for (size_t i = 0; i < vecBound.size(); ++i) {
		vecBound[i]->SetPos(vecBound[i]->GetPos() + m_vDir * GetOwnerScene()->GetResolution());
	}
}



Boundary::Boundary(Vector2 _vDir, Collider* _pPlayerCollider, Scene* _ownerScene)
	: m_vDir(_vDir)
	, GameObject(_ownerScene)
{
	Vector2 curLookAt = Camera::GetInst()->GetFinalLookAt();

	Vector2 playerScale = _pPlayerCollider->GetScale();
	Vector2 vResolution = GetOwnerScene()->GetResolution();
	Vector2 vAbs = _vDir * _vDir;
	Vector2 vScale = vAbs.Reverse() * vResolution + vAbs * playerScale;
	Vector2 vPos = curLookAt + _vDir * (vResolution / 2.f + playerScale * 4.f /3.f);

	SetPos(vPos);
	SetScale(vScale);


	CreateCollider();

	GetCollider()->SetScale(vScale);



}

Boundary::~Boundary()
{

}

void Boundary::Update()
{


}

void Boundary::Render(HDC _dc)
{
	ComponentRender(_dc);
}

