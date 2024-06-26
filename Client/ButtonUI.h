#pragma once
#include "ImageUI.h"


typedef void(*BTN_FUNC)(DWORD_PTR, DWORD_PTR);
class ButtonUI :
	public ImageUI
{

private:
	BTN_FUNC	m_pFunc;
	DWORD_PTR	m_param1;
	DWORD_PTR	m_param2;

public:
	virtual void MouseOn();
	virtual void MouseLbtnDown();
	virtual void MouseLbtnUp();
	virtual void MouseLbtnClick();


	void SetClickedCallBack(BTN_FUNC _pFunc, DWORD_PTR	_param1, DWORD_PTR	_param2)
	{
		m_pFunc = _pFunc;
		m_param1 = _param1;
		m_param2 = _param2;
	}
	CLONE(ButtonUI);


public:
	ButtonUI(bool _bCamAff, Scene* _ownerScene);
	~ButtonUI();


};

