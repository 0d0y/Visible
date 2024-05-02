#include "pch.h"
#include "WalkState.h"
#include "SceneManager.h"
#include "Scene.h"

#include "Animator.h"

#include "Player.h"
#include "Fsm.h"

WalkState::WalkState()
	:State(PLAYER_STATE::WALK)
{
}

WalkState::~WalkState()
{
}

void WalkState::update()
{
}

void WalkState::Enter()
{
}

void WalkState::Exit()
{
}


