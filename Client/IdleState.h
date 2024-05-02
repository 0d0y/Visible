#pragma once
#include "State.h"
class IdleState :
	public State
{
private:

public:
	virtual void update();
	virtual void Enter();
	virtual void Exit();

public:
	IdleState();
	~IdleState();
};

