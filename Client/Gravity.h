#pragma once

class GameObject;

class Gravity
{
private:
	GameObject*	m_pOwner;

	bool		m_bGround;
public :
	void SetGround(bool _b);
	bool GetGround() { return m_bGround; }

public :
	void finalupdate();

public:
	Gravity();
	~Gravity();

	friend class GameObject;
};

