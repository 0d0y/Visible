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
	// 1. FocusedUI Ȯ��
	m_pFocusedUI = GetFocusedUI(pCurScene);


	if (!m_pFocusedUI)
		return;


	// 2. FocusedUI������ �θ� UI ���� �ڽ� UI ���� ���� Ÿ���� �� UI�Ӹ� �����´�. 
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
			// ���� ��ư ����, ������ üũ�� �ٽ� �����Ѵ�.  
			pTargetUI->m_bLbtnDown = false;
		}
	}

}

void UIManager::SetFocusedUI(UI* _pUI, Scene* _pCurScene)
{

	// �̹� ��Ŀ�� ���̰ų�, ��Ŀ�� ���� ��û�ΰ��
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

	// ���� ��Ŀ�� UI�� �޾Ƶΰ� ����Ǿ����� Ȯ���Ѵ�. 
	UI* pFocusedUI = m_pFocusedUI;

	/*if (!bLbtnTap)
	{
		return pFocusedUI;
	}*/

	// ���� tap�� �߻��ߴٴ� ����
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

	// ���� ������ �ǵڷ� ���� ��ü
// 	vecUI.erase(targetiter);
// 	vecUI.push_back(pFocusedUI);

	return pFocusedUI;
}

UI* UIManager::GetTargetUI(UI* _pParentUI)
{

	bool bLbtnAway = KEY_AWAY(KEY::LBTN);
	// 1. �θ� UI����, ��� �ڽĵ��� �˻��Ѵ�. 
	UI* pTargetUI = nullptr;
	static list<UI*> queue;
	static vector<UI*> vecNoneTarget;

	queue.clear();
	vecNoneTarget.clear();

	queue.push_back(_pParentUI);

	while (!queue.empty())
	{
		// ť���� ������ �ϳ� ������
		UI* pUI = queue.front();
		queue.pop_front();

		// ť���� ������ UI�� TargetUI ���� Ȯ��
		// 2. Ÿ�� UI�帮 �� , �� �켱������ ���� ������ �� ���� ������ �ڽ� UI


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
		// ���� ��ư ����, ������ üũ�� �ٽ� �����Ѵ�. 
		for (size_t i = 0; i < vecNoneTarget.size(); ++i)
		{
			vecNoneTarget[i]->m_bLbtnDown = false;
		}
		
	}
	return pTargetUI;
}
