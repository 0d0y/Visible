#pragma once
#include "UI.h"
class TextUI :
    public UI
{
private:
	wstring m_str;
	float m_strSize;
	RECT m_printRect;
	bool m_playTrig;

public:
	virtual void Update();
	virtual void Render(HDC _dc);

	void SetString(LPCTSTR _str) { m_str = _str; }
	wstring GetString() { return m_str;}
	void SetStringSize(float _size) { m_strSize = _size; }
	float GetStringSize() { return m_strSize; }
	CLONE(TextUI);

public:



public:
	TextUI(bool _bCamAff, Scene* _ownerScene);
	~TextUI();
};