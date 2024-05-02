#include "pch.h"
#include "State.h"

State::State(PLAYER_STATE _eState)
	: m_pFsm(nullptr)
	, m_eState(_eState)
{
}

State::~State()
{
}
