#include "pch.h"
#include "ButtonUI.h"
#include "Scene.h"
#include "Animator.h"


ButtonUI::ButtonUI(bool _bCamAff, Scene* _ownerScene)
	: ImageUI(_bCamAff, _ownerScene)
	, m_pFunc(nullptr)
	, m_param1(0)
	, m_param2(0)
{

}

ButtonUI::~ButtonUI()
{

}

void ButtonUI::MouseOn()
{
	Scene* curScene = GetOwnerScene();
	vector<GameObject*>& vecUI = curScene->GetUIGroup();
	if (curScene->GetSceneType() == SCENE_TYPE::SELECT && GetName() == L"StageBtn1")
	{
		for (size_t i = 0; i < vecUI.size(); ++i) {
			if (vecUI[i]->GetName() == L"StageSelecter")
			{
				
				vecUI[i]->GetAnimator()->Play(L"SELETER_WALK",true);
				vecUI[i]->SetPos(GetPos() + Vector2(95.f, 90.f));
			}
		}
	}
	if (curScene->GetSceneType() == SCENE_TYPE::SELECT && GetName() == L"StageBtn2")
	{
		for (size_t i = 0; i < vecUI.size(); ++i) {
			if (vecUI[i]->GetName() == L"StageSelecter")
			{

				vecUI[i]->GetAnimator()->Play(L"SELETER_JUMP", true);
				vecUI[i]->SetPos(GetPos() + Vector2(95.f, 90.f));
			}
		}
	}
	if (curScene->GetSceneType() == SCENE_TYPE::SELECT && GetName() == L"StageBtn3")
	{
		for (size_t i = 0; i < vecUI.size(); ++i) {
			if (vecUI[i]->GetName() == L"StageSelecter")
			{

				vecUI[i]->GetAnimator()->Play(L"SELETER_CLEAR", true);
				vecUI[i]->SetPos(GetPos() + Vector2(95.f, 90.f));
			}
		}
	}
}

void ButtonUI::MouseLbtnDown()
{

}

void ButtonUI::MouseLbtnUp()
{

}

void ButtonUI::MouseLbtnClick()
{
	if (nullptr != m_pFunc)
	{
		m_pFunc(m_param1, m_param2);
	}
}
