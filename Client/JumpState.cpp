#include "pch.h"
#include "JumpState.h"
#include "SceneManager.h"
#include "Scene.h"

#include "Animator.h"
#include "Animation.h"
#include "Player.h"
#include "Fsm.h"

JumpState::JumpState()
	:State(PLAYER_STATE::JUMP)
{
}

JumpState::~JumpState()
{
}


void JumpState::update()
{
}

void JumpState::Enter()
{
}

void JumpState::Exit()
{
}

