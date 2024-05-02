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
		// ���ʱ׷� ������Ʈ �� �浹ü�� �������� �ʴ� ���
		if (vecLeft[i]->GetCollider() == nullptr)
			continue;

		for (size_t j = 0; j < vecRight.size(); ++j)
		{
			Collider* pLeftCol = vecLeft[i]->GetCollider();
			Collider* pRightCol = vecRight[j]->GetCollider();

			// ������ �׷� ������Ʈ�� �浹ü�� �������� �ʴ� ���
			// �Ǵ� �����ΰ��
			if (vecRight[j]->GetCollider() == nullptr
				|| vecLeft[i] == vecRight[j])
				continue;

			// �� �浹ü ���� ���̵� ����
			COLLIDER_ID ID;
			ID.Left_id = pLeftCol->GetID();
			ID.Right_id = pRightCol->GetID();

			iter = m_mapColInfo.find(ID.ID);

			// �浹 ������ �� ��� ������ ��� ���(�浹���� �ʾҴ� ��) 
			if (iter == m_mapColInfo.end()) {
				m_mapColInfo.insert(make_pair(ID.ID, false));
				iter = m_mapColInfo.find(ID.ID);
			}


			if (IsCollision(pLeftCol, pRightCol))
			{
				// ���� �浹 ���̴�.
				if (iter->second) {
					// �������� �浹 �ϰ� �־���. 

					if (vecLeft[i]->IsDead() || vecRight[j]->IsDead())
					{
						// �� �� �ϳ��� ���� �����̶��, �浹 ���������ش�. 
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
						// ������ �浹���� �ʾҴ�. 
						// �� �� �ϳ��� ���� �����̶��, �浹 ���� ���������� ���
						pLeftCol->OnCollisionEnter(pRightCol);
						pRightCol->OnCollisionEnter(pLeftCol);
						iter->second = true;
					}
				}
			}
			else
			{
				if (iter->second) {
					// �������� �浹 �ϰ� �־���. 
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
	// �� ���� ���� �׷� Ÿ���� ������,
	// ū ���� ��(��Ʈ) �� ���

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