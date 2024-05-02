#pragma once
#include "GameObject.h"
class UI :
	public GameObject
{
private:
	vector<UI*>    m_vecChildUI;
	UI* m_pParentUI;

	Vector2            m_vFinalPos;

	bool            m_bCamAffected;     // UI가 카메라의 영향을 받는다. 
	bool            m_bMouseOn;
	bool            m_bLbtnDown;        // UI에 왼쪽 마우스가 클릭되었는지

public:
	Vector2 GetFinalPos() { return m_vFinalPos; }

	UI* GetParent() { return m_pParentUI; }
	void AddChild(UI* _pUI) {
		m_vecChildUI.push_back(_pUI);
		_pUI->m_pParentUI = this;
	}

	bool IsMouseOn() { return m_bMouseOn; }
	bool IsLbtnDown() { return m_bLbtnDown; }

	bool IsCameraAffected() { return m_bCamAffected; }

	const vector<UI*>& GetChildUI() { return m_vecChildUI; }
public:
	virtual void Update();
	virtual void FinalUpdate();
	virtual void Render(HDC _dc);

	virtual UI* Clone() = 0;

private:
	void update_child();
	void finalupdate_child();
	void render_child(HDC _dc);

	void MouseOnCheck();

public:
	virtual void MouseOn();

	virtual void MouseLbtnDown();
	virtual void MouseLbtnUp();
	virtual void MouseLbtnClick();


public:
	UI(const UI& _origin);
	UI(bool _bCamAff, Scene* _ownerScene);
	virtual ~UI();

	friend class UIManager;
};

