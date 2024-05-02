#pragma once
#include "State.h"
class JumpState :
    public State
{
private:

public:
	virtual void update();
	virtual void Enter();
	virtual void Exit();

public:
	JumpState();
	~JumpState();
};

