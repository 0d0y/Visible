#include "pch.h"
#include "Scene.h"

#include "GameObject.h"

#include "Camera.h"

Scene::Scene(HWND _hWnd)
	: m_pPlayer(nullptr)
	, m_bPause(false)
	, m_hWnd(_hWnd)
	, m_sceneType(SCENE_TYPE::END)
{

}

Scene::~Scene()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j)
		{
			// m_arrObj[i] 그룹 벡터의 j 물체 삭제
			delete m_arrObj[i][j];
		}
	}
}

void Scene::Start()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j)
		{
			m_arrObj[i][j]->Start();
		}
	}
}

void Scene::Update()
{


	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j)
		{
			if (!m_arrObj[i][j]->IsDead())
			{
				m_arrObj[i][j]->Update();
			}
		}
	}
}

// 작업을 마무리할 때
void Scene::FinalUpdate()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j)
		{
			m_arrObj[i][j]->FinalUpdate();
		}
	}
}

void Scene::Render(HDC _dc)
{
	if (Camera::GetInst()->GetDuringFade()) {
		vector<GameObject*> vecBG = GetGroupObject(GROUP_TYPE::PREVBACKGROUND);
		vecBG[0]->Render(_dc);
	}
	else
	{
		for (UINT i = (UINT)GROUP_TYPE::BACKGROUND; i < (UINT)GROUP_TYPE::END; ++i)
		{
			vector<GameObject*>::iterator iter = m_arrObj[i].begin();
			for (; iter != m_arrObj[i].end();)
			{
				if (!(*iter)->IsDead())
				{
					(*iter)->Render(_dc);
					++iter;
				}
				else
				{
					iter = m_arrObj[i].erase(iter);
				}
			}
		}
	}
	
}

void Scene::DeleteGroup(GROUP_TYPE _eTarget)
{
	SafeDeleteVector<GameObject*>(m_arrObj[(UINT)_eTarget]);
}

void Scene::DeleteAll()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		DeleteGroup((GROUP_TYPE)i);
	}
}


Vector2 Scene::GetResolution()
{
	RECT clientRect;
	GetClientRect(m_hWnd, &clientRect);
	return Vector2((float)clientRect.right, (float)clientRect.bottom);
}