#pragma once

class Fsm;

class State
{
private:
	Fsm*				m_pFsm;
	PLAYER_STATE		m_eState;

public:
	Fsm* GetFsm() { return m_pFsm; }
	PLAYER_STATE GetState() { return m_eState; }

public:
	virtual void update() = 0;
	virtual void Enter() = 0;
	virtual void Exit() = 0;

public:
	State(PLAYER_STATE _eState);
	virtual ~State();

	friend class Fsm;
};

