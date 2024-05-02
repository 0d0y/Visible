#include "pch.h"
#include "func.h"
#include "Animation.h"

#include "EventManager.h"

void CreateObject(GameObject* _pObj, GROUP_TYPE _eGroup)
{
	tEvent evn = { };
	evn.eEven = EVENT_TYPE::CREATE_OBJECT;
	evn.lParam = (DWORD_PTR)_pObj;
	evn.wParam = (DWORD_PTR)_eGroup;

	EventManager::GetInst()->AddEvent(evn);
}

void DeleteObject(GameObject* _pObj)
{
	tEvent evn = { };
	evn.eEven = EVENT_TYPE::DELETE_OBJECT;
	evn.lParam = (DWORD_PTR)_pObj;

	EventManager::GetInst()->AddEvent(evn);
}

void ChangeScene(SCENE_TYPE _eNext)
{
	tEvent evn = { };
	evn.eEven = EVENT_TYPE::SCENE_CHANGE;
	evn.lParam = (DWORD_PTR)_eNext;

	EventManager::GetInst()->AddEvent(evn);
}

void ChangeFsmState(Fsm* _pFsm, PLAYER_STATE _eNextState)
{
	tEvent evn = { };
	evn.eEven = EVENT_TYPE::CHANGE_FSM_STATE;
	evn.lParam = (DWORD_PTR)_pFsm;
	evn.wParam = (DWORD_PTR)_eNextState;

	EventManager::GetInst()->AddEvent(evn);
}
