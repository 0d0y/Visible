#pragma once

class Collider;
class Scene;

union COLLIDER_ID
{
	struct
	{
		UINT Left_id;
		UINT Right_id;
	};
	ULONGLONG ID;
};



class CollisionManager
{
	SINGLE(CollisionManager)
private:
	map<ULONGLONG, bool> m_mapColInfo;			// �浹ü ���� ���� ������ �浹 ����
	UINT m_arrCheck[(UINT)GROUP_TYPE::END];		// �׷� ���� �浹 üũ ��Ʈ����


public:
	void Update(Scene* _pCurScene);
	void CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight);
	void Reset() { memset(m_arrCheck, 0, sizeof(UINT) * (UINT)GROUP_TYPE::END); }


private:
	void CollisionGroupUpdate(Scene* _pCurScene, GROUP_TYPE _eLeft, GROUP_TYPE _eRight);
	bool IsCollision(Collider* _pLeftCol, Collider* _pRightCol);
};

