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
	map<ULONGLONG, bool> m_mapColInfo;			// 충돌체 간의 이전 프레임 충돌 정보
	UINT m_arrCheck[(UINT)GROUP_TYPE::END];		// 그룹 간의 충돌 체크 매트릭스


public:
	void Update(Scene* _pCurScene);
	void CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight);
	void Reset() { memset(m_arrCheck, 0, sizeof(UINT) * (UINT)GROUP_TYPE::END); }


private:
	void CollisionGroupUpdate(Scene* _pCurScene, GROUP_TYPE _eLeft, GROUP_TYPE _eRight);
	bool IsCollision(Collider* _pLeftCol, Collider* _pRightCol);
};

