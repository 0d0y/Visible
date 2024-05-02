#include "pch.h"
#include "EventManager.h"

#include "GameObject.h"
#include "SceneManager.h"
#include "Scene.h"

#include "Fsm.h"
#include "State.h"
#include "UIManager.h"
#include "GameProcess.h"
#include "Camera.h"

EventManager::EventManager()
	: m_triggeredProcess(nullptr)
{

}
EventManager::~EventManager()
{

}

void EventManager::Initialize(GameProcess* _gameProcess)
{
	m_triggeredProcess = _gameProcess;
}

void EventManager::Update()
{
	//=================================================
	// ���� �����ӿ��� ����ص� Dead Object ���� �����Ѵ�.
	//=================================================
	for (size_t i = 0; i < m_vecDead.size(); ++i)
	{
		delete m_vecDead[i];
	}
	m_vecDead.clear();

	//==========
	//Event ó��
	//==========
	for (size_t i = 0; i < m_vecEvent.size(); ++i)
	{
		Excute(m_vecEvent[i]);
	}
	m_vecEvent.clear();
}

void EventManager::Excute(const tEvent& _eve)
{
	switch (_eve.eEven)
	{
	case EVENT_TYPE::CREATE_OBJECT:
	{
		// lParam : Object Adress
		// wParam : Group Type
		GameObject* pNewObj = (GameObject*)_eve.lParam;
		GROUP_TYPE eType = (GROUP_TYPE)_eve.wParam;

		pNewObj->GetOwnerScene()->AddObject(pNewObj, eType);
	}
		break;
	case EVENT_TYPE::DELETE_OBJECT:
	{
		// lParam : Object Adress
		// Object �� Dead ���·� ����
		// �������� ������Ʈ���� ��Ƶд�.
		GameObject* pDeadObj = (GameObject*)_eve.lParam;
		pDeadObj->SetDead();
		if(!pDeadObj->IsDead())
			m_vecDead.push_back(pDeadObj);
	}
		break;
	case EVENT_TYPE::SCENE_CHANGE:
	{
		//lParam : Next Scene Type
		m_triggeredProcess->GetSceneManager()->ChangeScene((SCENE_TYPE)_eve.lParam);
		UIManager::GetInst()->SetFocusedUI(nullptr, nullptr);
	}
		break;
	case EVENT_TYPE::CHANGE_FSM_STATE:
	{
		// lParam : FSM
		// wParam : Next_Type
		Fsm* pFsm = (Fsm*)_eve.lParam;
		PLAYER_STATE eNextState = (PLAYER_STATE)_eve.wParam;

		pFsm->ChangeState(eNextState);
	}
		break;
	}


		
}
