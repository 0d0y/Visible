#pragma once

class GameProcess;

struct tEvent
{
	EVENT_TYPE		eEven;
	DWORD_PTR		lParam;
	DWORD_PTR		wParam;
};

class EventManager
{
	SINGLE(EventManager)
private:
	GameProcess* m_triggeredProcess;

	vector<tEvent> m_vecEvent;
	vector<GameObject*> m_vecDead;


public:
	void Initialize(GameProcess* _gameProcess);
	void Update();

private:
	void Excute(const tEvent& _eve);

public: 
	void AddEvent(const tEvent& _eve) { m_vecEvent.push_back(_eve); }
};

