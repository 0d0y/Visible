#include "pch.h"
#include "IdleState.h"
#include "SceneManager.h"
#include "Scene.h"

#include "Animator.h"

#include "Player.h"
#include "Fsm.h"


IdleState::IdleState()
	: State(PLAYER_STATE::IDLE)
{
}

IdleState::~IdleState()
{
}

void IdleState::update()
{
	

}

void IdleState::Enter()
{
}

void IdleState::Exit()
{
}
