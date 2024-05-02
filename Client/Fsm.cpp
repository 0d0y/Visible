#include "pch.h"
#include "Fsm.h"

#include "State.h"
#include "SceneManager.h"
#include "Scene.h"

#include "Player.h"
Fsm::Fsm()
	: m_pCurState(nullptr)
	, m_pOwner(nullptr)
{
}

Fsm::~Fsm()
{
	SafeDeleteMap(m_mapState);
}


void Fsm::update()
{
	m_pCurState->update();
}


void Fsm::Addstate(State* _pState)
{
	State* pState = GetState(_pState->GetState());
	assert(!pState);

	m_mapState.insert(make_pair(_pState->GetState(), _pState));
	_pState->m_pFsm = this;
}

State* Fsm::GetState(PLAYER_STATE _eState)
{
	map<PLAYER_STATE, State*>::iterator iter = m_mapState.find(_eState);
	if (iter == m_mapState.end())
		return nullptr;

	return iter->second;
}

void Fsm::SetCurState(PLAYER_STATE _eState)
{
	m_pCurState = GetState(_eState);
	assert(m_pCurState);
}

void Fsm::ChangeState(PLAYER_STATE _eNextState)
{
	State* pNextState = GetState(_eNextState);

	//assert(m_pCurState != pNextState);

	m_pCurState->Exit();

	m_pCurState = pNextState;

	m_pCurState->Enter();

}


