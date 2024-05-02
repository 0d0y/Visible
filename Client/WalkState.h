#pragma once
#include "State.h"
class WalkState :
    public State
{
private:

public:
	virtual void update();
	virtual void Enter();
	virtual void Exit();

public:
	WalkState();
	~WalkState();
};

