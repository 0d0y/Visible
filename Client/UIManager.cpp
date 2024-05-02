#include "pch.h"
#include "UIManager.h"

#include "SceneManager.h"
#include "KeyManager.h"
#include "Scene.h"
#include "UI.h"
#include "SoundManager.h"

UIManager::UIManager()
	: m_pFocusedUI(nullptr)
{

}

UIManager::~UIManager()
{

}

void UIManager::Update(Scene* pCurScene)
{
	// 1. FocusedUI 확인
	m_pFocusedUI = GetFocusedUI(pCurScene);


	if (!m_pFocusedUI)
		return;


	// 2. FocusedUI내에서 부모 UI 포함 자식 UI 들중 실제 타겟팅 된 UIㅣ를 가져온다. 
	UI* pTargetUI = GetTargetUI(m_pFocusedUI);

	bool bLbtnTap = KEY_TAP(KEY::LBTN);
	bool bLbtnAway = KEY_AWAY(KEY::LBTN);

	if (pTargetUI != nullptr)
	{
		pTargetUI->MouseOn();

		if (bLbtnTap)
		{
			pTargetUI->MouseLbtnDown();
			pTargetUI->m_bLbtnDown = true;
		}
		else if (bLbtnAway)
		{
			pTargetUI->MouseLbtnUp();

			if (pTargetUI->m_bLbtnDown)
			{
				pTargetUI->MouseLbtnClick();
				SoundManager::GetInst()->PlaySFX(UI_BUTTON);
			}
			// 왼쪽 버튼 떼면, 눌렀던 체크를 다시 해제한다.  
			pTargetUI->m_bLbtnDown = false;
		}
	}

}

void UIManager::SetFocusedUI(UI* _pUI, Scene* _pCurScene)
{

	// 이미 포커싱 중이거나, 포커싱 해제 요청인경우
	if (m_pFocusedUI == _pUI || _pUI == nullptr)
	{
		m_pFocusedUI = _pUI;
		return;
	}

	m_pFocusedUI = _pUI;

	Scene* pCurScene = _pCurScene;

	vector<GameObject*>& vecUI = pCurScene->GetUIGroup();


	vector<GameObject*>::iterator iter = vecUI.begin();
	for (; iter < vecUI.end(); ++iter)
	{
		if (m_pFocusedUI == *iter) {
			break;
		}
	}

	vecUI.erase(iter);
	vecUI.push_back(m_pFocusedUI);

}

UI* UIManager::GetFocusedUI(Scene* _pCurScene)
{
	Scene* pCurScene = _pCurScene;

	vector<GameObject*>& vecUI = pCurScene->GetUIGroup();

	bool bLbtnTap = KEY_TAP(KEY::LBTN);

	// 기존 포커싱 UI를 받아두고 변경되었는지 확인한다. 
	UI* pFocusedUI = m_pFocusedUI;

	/*if (!bLbtnTap)
	{
		return pFocusedUI;
	}*/

	// 왼쪽 tap이 발생했다는 전제
	vector<GameObject*>::iterator targetiter = vecUI.end();
	vector<GameObject*>::iterator iter = vecUI.begin();
	for (; iter < vecUI.end(); ++iter)
	{
		if (((UI*)(*iter))->IsMouseOn())
		{
			targetiter = iter;
		}
	}

	if (vecUI.end() == targetiter)
	{
		return nullptr;
	}


	pFocusedUI = (UI*)*targetiter;

	// 벡터 내에서 맨뒤로 순번 교체
// 	vecUI.erase(targetiter);
// 	vecUI.push_back(pFocusedUI);

	return pFocusedUI;
}

UI* UIManager::GetTargetUI(UI* _pParentUI)
{

	bool bLbtnAway = KEY_AWAY(KEY::LBTN);
	// 1. 부모 UI포함, 모든 자식들을 검사한다. 
	UI* pTargetUI = nullptr;
	static list<UI*> queue;
	static vector<UI*> vecNoneTarget;

	queue.clear();
	vecNoneTarget.clear();

	queue.push_back(_pParentUI);

	while (!queue.empty())
	{
		// 큐에서 데이터 하나 꺼내기
		UI* pUI = queue.front();
		queue.pop_front();

		// 큐에서 꺼내온 UI가 TargetUI 인지 확인
		// 2. 타겟 UI드리 중 , 더 우선순위가 높은 기준은 더 낮은 계층의 자식 UI


		if (pUI->IsMouseOn())
		{
			if (pTargetUI != nullptr) {
				vecNoneTarget.push_back(pTargetUI);
			}
			pTargetUI = pUI;
		}
		else
		{
			vecNoneTarget.push_back(pUI);
		}

		const vector<UI*>& vecChild = pUI->GetChildUI();
		for (size_t i = 0; i < vecChild.size(); ++i)
		{
			queue.push_back(vecChild[i]);
		}

	}
	if (bLbtnAway)
	{
		// 왼쪽 버튼 떼면, 눌렀던 체크를 다시 해제한다. 
		for (size_t i = 0; i < vecNoneTarget.size(); ++i)
		{
			vecNoneTarget[i]->m_bLbtnDown = false;
		}
		
	}
	return pTargetUI;
}
