#pragma once
#include "State.h"
class DeadState :
    public State
{
private:

public:
	virtual void update();
	virtual void Enter();
	virtual void Exit();

public:
	DeadState();
	~DeadState();
};

