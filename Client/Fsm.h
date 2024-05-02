#pragma once

class Player;
class State;

class Fsm
{
private:
	map <PLAYER_STATE, State*>		m_mapState;
	State* m_pCurState;
	GameObject* m_pOwner;

public:
	void update();

public:
	void Addstate(State* _pState);
	State* GetState(PLAYER_STATE _eState);
	void SetCurState(PLAYER_STATE _eState);

	void ChangeState(PLAYER_STATE _eNextState);

public:
	Fsm();
	~Fsm();
	friend class GameObject;
};

