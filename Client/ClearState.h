#pragma once
#include "State.h"
class ClearState :
    public State
{
private:

public:
	virtual void update();
	virtual void Enter();
	virtual void Exit();

public:
	ClearState();
	~ClearState();
};

