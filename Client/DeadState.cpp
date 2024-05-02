#include "pch.h"
#include "DeadState.h"
#include "SceneManager.h"
#include "Scene.h"

#include "Animator.h"

#include "Player.h"
#include "Fsm.h"

DeadState::DeadState()
	:State(PLAYER_STATE::DEAD)
{
}

DeadState::~DeadState()
{
}

void DeadState::update()
{
}

void DeadState::Enter()
{
}

void DeadState::Exit()
{
}


