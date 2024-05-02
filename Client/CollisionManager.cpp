#include "pch.h"
#include "CollisionManager.h"

#include "SceneManager.h"
#include "Scene.h"
#include "GameObject.h"
#include "Collider.h"



CollisionManager::CollisionManager()
	: m_arrCheck{}
{

}

CollisionManager::~CollisionManager()
{

}

void CollisionManager::Update(Scene* _pCurScene)
{
	for (UINT iRow = 0; iRow < (UINT)GROUP_TYPE::END; ++iRow)
	{
		for (UINT iCol = iRow; iCol < (UINT)GROUP_TYPE::END; ++iCol)
		{
			if (m_arrCheck[iRow] & (1 << iCol))
			{
				CollisionGroupUpdate(_pCurScene, (GROUP_TYPE)iRow, (GROUP_TYPE)iCol);
			}
		}
	}
}

void CollisionManager::CollisionGroupUpdate(Scene* _pCurScene, GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
	Scene* pCurScene = _pCurScene;
	const vector<GameObject*>& vecLeft = pCurScene->GetGroupObject(_eLeft);
	const vector<GameObject*>& vecRight = pCurScene->GetGroupObject(_eRight);
	map<ULONGLONG, bool>::iterator iter;


	for (size_t i = 0; i < vecLeft.size(); ++i)
	{
		// 왼쪽그룹 오브젝트 에 충돌체를 보유하지 않는 경우
		if (vecLeft[i]->GetCollider() == nullptr)
			continue;

		for (size_t j = 0; j < vecRight.size(); ++j)
		{
			Collider* pLeftCol = vecLeft[i]->GetCollider();
			Collider* pRightCol = vecRight[j]->GetCollider();

			// 오른쪽 그룹 오브젝트에 충돌체를 보유하지 않는 경우
			// 또는 본인인경우
			if (vecRight[j]->GetCollider() == nullptr
				|| vecLeft[i] == vecRight[j])
				continue;

			// 두 충돌체 조합 아이디 생성
			COLLIDER_ID ID;
			ID.Left_id = pLeftCol->GetID();
			ID.Right_id = pRightCol->GetID();

			iter = m_mapColInfo.find(ID.ID);

			// 충돌 정보가 미 등록 상태인 경우 등록(충돌하지 않았다 로) 
			if (iter == m_mapColInfo.end()) {
				m_mapColInfo.insert(make_pair(ID.ID, false));
				iter = m_mapColInfo.find(ID.ID);
			}


			if (IsCollision(pLeftCol, pRightCol))
			{
				// 현재 충돌 중이다.
				if (iter->second) {
					// 이전에도 충돌 하고 있었다. 

					if (vecLeft[i]->IsDead() || vecRight[j]->IsDead())
					{
						// 둘 중 하나가 삭제 예정이라면, 충돌 해제시켜준다. 
						pLeftCol->OnCollisionExit(pRightCol);
						pRightCol->OnCollisionExit(pLeftCol);
						iter->second = false;
					}

					else
					{
						pLeftCol->OnCollision(pRightCol);
						pRightCol->OnCollision(pLeftCol);
					}
				}
				else {
					if (!vecLeft[i]->IsDead() && !vecRight[j]->IsDead())
					{
						// 이전에 충돌하지 않았다. 
						// 둘 중 하나가 삭제 예정이라면, 충돌 하지 않은것으로 취급
						pLeftCol->OnCollisionEnter(pRightCol);
						pRightCol->OnCollisionEnter(pLeftCol);
						iter->second = true;
					}
				}
			}
			else
			{
				if (iter->second) {
					// 이전에는 충돌 하고 있었다. 
					pLeftCol->OnCollisionExit(pRightCol);
					pRightCol->OnCollisionExit(pLeftCol);
					iter->second = false;
				}
			}
		}
	}
}

bool CollisionManager::IsCollision(Collider* _pLeftCol, Collider* _pRightCol)
{
	Vector2 vLeftPos = _pLeftCol->GetFinalPos();
	Vector2 vLeftScale = _pLeftCol->GetScale();

	Vector2 vRightPos = _pRightCol->GetFinalPos();
	Vector2 vRightScale = _pRightCol->GetScale();

	if (abs(vRightPos.x - vLeftPos.x) <= (vLeftScale.x + vRightScale.x) / 2.0f
		&& abs(vRightPos.y - vLeftPos.y) <= (vLeftScale.y + vRightScale.y) / 2.0f)
	{
		return true;
	}

	return false;
}

void CollisionManager::CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
	// 더 작은 값의 그룹 타입을 행으로,
	// 큰 값을 열(비트) 로 사용

	UINT iRow = (UINT)_eLeft;
	UINT iCol = (UINT)_eRight;

	if (iCol < iRow)
	{
		iRow = (UINT)_eRight;
		iCol = (UINT)_eLeft;
	}

	if (m_arrCheck[iRow] & (1 << iCol))
	{
		m_arrCheck[iRow] &= ~(1 << iCol);
	}
	else
	{
		m_arrCheck[iRow] |= (1 << iCol);

	}
	m_arrCheck[iRow] |= (1 << iCol);

}