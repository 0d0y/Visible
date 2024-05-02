#include "pch.h"
#include "Terrain.h"
#include "SelectGDI.h"
#include "Camera.h"
#include "Collider.h"
#include "Gravity.h"

#include "Player.h"
#include "Texture.h"
#include "RigidBody.h"
#include "GameObject.h"
#include "ColorObject.h"

extern RigidBody* SetterVelocity = nullptr;
extern Vector2 CurrentVelocity = {};
extern Vector2 CurrentVelocityXZero = {};
extern Vector2 CurrentVelocityYZero = {};
extern Vector2 CurrentVelocityYReverse = {};

Terrain::Terrain(Scene* _ownerScene)
	: ColorObject(_ownerScene)
	, bCanPaint(true)

{
	CreateCollider();
}

Terrain::~Terrain()
{

}

void Terrain::HandleCollision(Collider* _pOther)
{
	float deltaX = GetCollider()->GetFinalPos().x - _pOther->GetFinalPos().x;
	float deltaY = GetCollider()->GetFinalPos().y - _pOther->GetFinalPos().y;

	float totalWidth = (_pOther->GetScale().x + GetCollider()->GetScale().x) / 2.0f;
	float totalHeight = (_pOther->GetScale().y + GetCollider()->GetScale().y) / 2.0f;

	if (abs(deltaX) < totalWidth && abs(deltaY) < totalHeight)
	{
		((Player*)_pOther->GetObj())->SetPlayerState(PLAYER_STATE::STUCK);
		return;
	}

	int directionX = (deltaX > 0) ? 1 : -1;
	int directionY = (deltaY > 0) ? 1 : -1;

	float penetrationX = totalWidth - abs(deltaX);
	float penetrationY = totalHeight - abs(deltaY);

	if (penetrationX < penetrationY) {
		// Adjust positions along the x-axis
		float adjustmentX = penetrationX * directionX;
		float px = _pOther->GetObj()->GetPos().x + adjustmentX;
		float tx = GetPos().x - adjustmentX;
	}
	else {
		// Adjust positions along the y-axis
		float adjustmentY = penetrationY * directionY;
		float py = _pOther->GetObj()->GetPos().y + adjustmentY;
		float ty = GetPos().y - adjustmentY;
	}
}


void Terrain::Start()
{
	GetCollider()->SetScale(Vector2(GetScale()));
}

void Terrain::Update()
{
	

}

void Terrain::OnCollisionEnter(Collider* _pOther)
{
	GameObject* pOtherObj = _pOther->GetObj();
	if (pOtherObj->GetName() == L"Player")
	{
		Player* pColPlayer = dynamic_cast<Player*>(pOtherObj);
		assert(pColPlayer);

		if (pColPlayer->GetWearGlasses() == GetColorState() || pColPlayer->GetPlayerColor() == GetColorState())
		{
			if (pColPlayer->IsCollisionHandledY() == false) {
				pColPlayer->GetGravity()->SetGround(false);
			}
		}
		else
		{
			Vector2 vObjPos = _pOther->GetFinalPos();
			Vector2 vObjScale = _pOther->GetScale();

			Vector2 vPos = GetCollider()->GetFinalPos();
			Vector2 vScale = GetCollider()->GetScale();


			float fLenY = abs(vObjPos.y - vPos.y);
			float fValueY = 0.f;
			float fLenX = abs(vObjPos.x - vPos.x);
			float fValueX = 0.f;
			int colHandleX = 0;
			int colHandleY = 0;
			if (vPos.x + vScale.x / 2.f >= vObjPos.x + vObjScale.x / 2.f &&
				vPos.y + vScale.y / 2.f >= vObjPos.y + vObjScale.y / 2.f - 10.f &&
				vPos.x - vScale.x / 2.f <= vObjPos.x - vObjScale.x / 2.f &&
				vPos.y - vScale.y / 2.f <= vObjPos.y - vObjScale.y / 2.f)
			{
				//fValueY = (vObjScale.y / 2.f + vScale.y / 2.f) - fLenY;
				Vector2 temp = pOtherObj->GetRigidBody()->GetVelocity();
				pOtherObj->GetRigidBody()->SetVelocity(Vector2(0.f, 0.f));
				//pOtherObj->GetRigidBody()->SetVelocity(-temp);
				//pOtherObj->GetRigidBody()->SetAccelAlpha();

				vObjPos = pOtherObj->GetPos();
				vObjPos -= temp * fDT;
				pOtherObj->SetPos(vObjPos);




				// 				if (fValueY > 0.f) {
				// 					colHandleY = -1;
				// 				}
				pColPlayer->SetCollisionHandledY(true);
				pColPlayer->SetCollisionHandledX(true);
				pColPlayer->SetPlayerState(PLAYER_STATE::STUCK);

				return;
			}

			pColPlayer->SetPlayerState(PLAYER_STATE::IDLE);
			if (!pColPlayer->IsCollisionHandledY())
			{


				Vector2 vObjPos = _pOther->GetFinalPos();
				Vector2 vObjScale = _pOther->GetScale();

				Vector2 vPos = GetCollider()->GetFinalPos();
				Vector2 vScale = GetCollider()->GetScale();


				pColPlayer->SetCollisionHandledY(true);


				if (vPos.y + vScale.y / 2.f >= vObjPos.y - vObjScale.y / 2.f &&
					vPos.y <= vObjPos.y &&
					vPos.x + vScale.x / 2.f >= vObjPos.x - vObjScale.x / 2.f + 5.f &&
					vPos.x - vScale.x / 2.f <= vObjPos.x + vObjScale.x / 2.f - 5.f)
				{

					fValueY = (vObjScale.y / 2.f + vScale.y / 2.f) - fLenY;
					//pOtherObj->GetGravity()->SetGround(true);

					if (fValueY > 0.f) {
						colHandleY = 1;
					}
				}
				else if (vPos.y - vScale.y / 2.f <= vObjPos.y + vObjScale.y / 2.f &&
					vPos.y >= vObjPos.y &&
					vPos.x + vScale.x / 2.f >= vObjPos.x - vObjScale.x / 2.f + 5.f &&
					vPos.x - vScale.x / 2.f <= vObjPos.x + vObjScale.x / 2.f - 5.f)

				{

					fValueY = (vObjScale.y / 2.f + vScale.y / 2.f) - fLenY;

					if (fValueY > 0.f) {
						colHandleY = -1;
					}
				}
				else
				{
					pColPlayer->SetCollisionHandledY(false);
				}


			}

			if (!pColPlayer->IsCollisionHandledX())
			{

				Vector2 vObjPos = _pOther->GetFinalPos();
				Vector2 vObjScale = _pOther->GetScale();

				Vector2 vPos = GetCollider()->GetFinalPos();
				Vector2 vScale = GetCollider()->GetScale();

				pColPlayer->SetCollisionHandledX(true);
				if (vPos.x - vScale.x / 2.f <= vObjPos.x + vObjScale.x / 2.f &&
					vPos.x >= vObjPos.x &&
					vPos.y + vScale.y / 2.f >= vObjPos.y - vObjScale.y / 2.f + 5.f &&
					vPos.y - vScale.y / 2.f <= vObjPos.y + vObjScale.y / 2.f - 5.f)
				{

					fValueX = (vObjScale.x / 2.f + vScale.x / 2.f) - fLenX;
					if (fValueX > 0.f) {
						colHandleX = -1;

					}

				}
				else if (vPos.x + vScale.x / 2.f >= vObjPos.x - vObjScale.x / 2.f &&
					vPos.x <= vObjPos.x &&
					vPos.y + vScale.y / 2.f >= vObjPos.y - vObjScale.y / 2.f + 5.f &&
					vPos.y - vScale.y / 2.f <= vObjPos.y + vObjScale.y / 2.f - 5.f)
				{
					//pOtherObj->GetRigidBody()->SetVelocity(Vector2(0.f, pOtherObj->GetRigidBody()->GetVelocity().y));
					fValueX = (vObjScale.x / 2.f + vScale.x / 2.f) - fLenX;
					if (fValueX > 0.f) {
						colHandleX = 1;
					}

				}
				else
				{
					pColPlayer->SetCollisionHandledX(false);
				}


			}

			if (fValueX <= fValueY && (colHandleX && colHandleY))
			{
				pOtherObj->GetRigidBody()->SetVelocity(Vector2(0.f, pOtherObj->GetRigidBody()->GetVelocity().y));
				vObjPos = pOtherObj->GetPos();
				vObjPos.x += fValueX * colHandleX;
				pOtherObj->SetPos(vObjPos);
			}
			else if (fValueX > fValueY && (colHandleX && colHandleY))
			{
				pOtherObj->GetGravity()->SetGround(true);
				vObjPos = pOtherObj->GetPos();
				vObjPos.y += fValueY * colHandleY;
				pOtherObj->SetPos(vObjPos);
			}
			else if (fValueX > 0.f)
			{
				pOtherObj->GetRigidBody()->SetVelocity(Vector2(0.f, pOtherObj->GetRigidBody()->GetVelocity().y));
				vObjPos = pOtherObj->GetPos();
				vObjPos.x += fValueX * colHandleX;
				pOtherObj->SetPos(vObjPos);
			}
			else if (fValueY > 0.f)
			{
				pOtherObj->GetGravity()->SetGround(true);
				vObjPos = pOtherObj->GetPos();
				vObjPos.y += fValueY * colHandleY;
				pOtherObj->SetPos(vObjPos);
			}
		}
	}
}

void Terrain::OnCollision(Collider* _pOther)
{
	GameObject* pOtherObj = _pOther->GetObj();
	if (pOtherObj->GetName() == L"Player")
	{
		Player* pColPlayer = dynamic_cast<Player*>(pOtherObj);
		assert(pColPlayer);

		if (pColPlayer->GetWearGlasses() == GetColorState() || pColPlayer->GetPlayerColor() == GetColorState())
		{
			if (pColPlayer->IsCollisionHandledY() == false) {
				pColPlayer->GetGravity()->SetGround(false);
			}
		}
		else
		{
			Vector2 vObjPos = _pOther->GetFinalPos();
			Vector2 vObjScale = _pOther->GetScale();

			Vector2 vPos = GetCollider()->GetFinalPos();
			Vector2 vScale = GetCollider()->GetScale();


			float fLenY = abs(vObjPos.y - vPos.y);
			float fValueY = 0.f;
			float fLenX = abs(vObjPos.x - vPos.x);
			float fValueX = 0.f;
			int colHandleX = 0;
			int colHandleY = 0;
			if (vPos.x + vScale.x / 2.f >= vObjPos.x + vObjScale.x / 2.f &&
				vPos.y + vScale.y / 2.f >= vObjPos.y + vObjScale.y / 2.f - 10.f &&
				vPos.x - vScale.x / 2.f <= vObjPos.x - vObjScale.x / 2.f &&
				vPos.y - vScale.y / 2.f <= vObjPos.y - vObjScale.y / 2.f)
			{
				//fValueY = (vObjScale.y / 2.f + vScale.y / 2.f) - fLenY;
				Vector2 temp = pOtherObj->GetRigidBody()->GetVelocity();
				pOtherObj->GetRigidBody()->SetVelocity(Vector2(0.f, 0.f));
				//pOtherObj->GetRigidBody()->SetVelocity(-temp);
				//pOtherObj->GetRigidBody()->SetAccelAlpha();

				vObjPos = pOtherObj->GetPos();
				vObjPos -= temp * fDT;
				pOtherObj->SetPos(vObjPos);




				// 				if (fValueY > 0.f) {
				// 					colHandleY = -1;
				// 				}
				pColPlayer->SetCollisionHandledY(true);
				pColPlayer->SetCollisionHandledX(true);
				pColPlayer->SetPlayerState(PLAYER_STATE::STUCK);
				
				return;
			}

			pColPlayer->SetPlayerState(PLAYER_STATE::IDLE);
			if (!pColPlayer->IsCollisionHandledY())
			{


				Vector2 vObjPos = _pOther->GetFinalPos();
				Vector2 vObjScale = _pOther->GetScale();

				Vector2 vPos = GetCollider()->GetFinalPos();
				Vector2 vScale = GetCollider()->GetScale();


				pColPlayer->SetCollisionHandledY(true);


				if (vPos.y + vScale.y / 2.f >= vObjPos.y - vObjScale.y / 2.f &&
					vPos.y <= vObjPos.y &&
					vPos.x + vScale.x / 2.f >= vObjPos.x - vObjScale.x / 2.f + 5.f &&
					vPos.x - vScale.x / 2.f <= vObjPos.x + vObjScale.x / 2.f - 5.f)
				{

					fValueY = (vObjScale.y / 2.f + vScale.y / 2.f) - fLenY;
					//pOtherObj->GetGravity()->SetGround(true);

					if (fValueY > 0.f) {
						colHandleY = 1;
					}
				}
				else if (vPos.y - vScale.y / 2.f <= vObjPos.y + vObjScale.y / 2.f &&
					vPos.y >= vObjPos.y &&
					vPos.x + vScale.x / 2.f >= vObjPos.x - vObjScale.x / 2.f + 5.f &&
					vPos.x - vScale.x / 2.f <= vObjPos.x + vObjScale.x / 2.f - 5.f)

				{

					fValueY = (vObjScale.y / 2.f + vScale.y / 2.f) - fLenY;

					if (fValueY > 0.f) {
						colHandleY = -1;
					}
				}
				else
				{
					pColPlayer->SetCollisionHandledY(false);
				}


			}

			if (!pColPlayer->IsCollisionHandledX())
			{

				Vector2 vObjPos = _pOther->GetFinalPos();
				Vector2 vObjScale = _pOther->GetScale();

				Vector2 vPos = GetCollider()->GetFinalPos();
				Vector2 vScale = GetCollider()->GetScale();

				pColPlayer->SetCollisionHandledX(true);
				if (vPos.x - vScale.x / 2.f <= vObjPos.x + vObjScale.x / 2.f &&
					vPos.x >= vObjPos.x &&
					vPos.y + vScale.y / 2.f >= vObjPos.y - vObjScale.y / 2.f + 5.f &&
					vPos.y - vScale.y / 2.f <= vObjPos.y + vObjScale.y / 2.f - 5.f)
				{

					fValueX = (vObjScale.x / 2.f + vScale.x / 2.f) - fLenX;
					if (fValueX > 0.f) {
						colHandleX = -1;

					}

				}
				else if (vPos.x + vScale.x / 2.f >= vObjPos.x - vObjScale.x / 2.f &&
					vPos.x <= vObjPos.x &&
					vPos.y + vScale.y / 2.f >= vObjPos.y - vObjScale.y / 2.f + 5.f &&
					vPos.y - vScale.y / 2.f <= vObjPos.y + vObjScale.y / 2.f - 5.f)
				{
					//pOtherObj->GetRigidBody()->SetVelocity(Vector2(0.f, pOtherObj->GetRigidBody()->GetVelocity().y));
					fValueX = (vObjScale.x / 2.f + vScale.x / 2.f) - fLenX;
					if (fValueX > 0.f) {
						colHandleX = 1;
					}

				}
				else
				{
					pColPlayer->SetCollisionHandledX(false);
				}


			}

			if (fValueX <= fValueY && (colHandleX && colHandleY))
			{
				pOtherObj->GetRigidBody()->SetVelocity(Vector2(0.f, pOtherObj->GetRigidBody()->GetVelocity().y));
				vObjPos = pOtherObj->GetPos();
				vObjPos.x += fValueX * colHandleX;
				pOtherObj->SetPos(vObjPos);
			}
			else if (fValueX > fValueY && (colHandleX && colHandleY))
			{
				pOtherObj->GetGravity()->SetGround(true);
				vObjPos = pOtherObj->GetPos();
				vObjPos.y += fValueY * colHandleY;
				pOtherObj->SetPos(vObjPos);
			}
			else if (fValueX > 0.f)
			{
				pOtherObj->GetRigidBody()->SetVelocity(Vector2(0.f, pOtherObj->GetRigidBody()->GetVelocity().y));
				vObjPos = pOtherObj->GetPos();
				vObjPos.x += fValueX * colHandleX;
				pOtherObj->SetPos(vObjPos);
			}
			else if (fValueY > 0.f)
			{
				pOtherObj->GetGravity()->SetGround(true);
				vObjPos = pOtherObj->GetPos();
				vObjPos.y += fValueY * colHandleY;
				pOtherObj->SetPos(vObjPos);
			}
		}
	}
}

void Terrain::OnCollisionExit(Collider* _pOther)
{
	GameObject* pOtherObj = _pOther->GetObj();
	if (pOtherObj->GetName() == L"Player")
	{
		Player* pColPlayer = dynamic_cast<Player*>(pOtherObj);
		assert(pColPlayer);
		pOtherObj->GetGravity()->SetGround(false);
	}
}


void Terrain::Render(HDC _dc)
{
	if (bCanPaint)
		ColorObject::Render(_dc);
	ComponentRender(_dc);
}


