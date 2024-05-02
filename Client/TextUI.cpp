#include "pch.h"
#include "TextUI.h"
#include "TimeManager.h"
#include "KeyManager.h"
#include "PathManager.h"


void TextUI::Update()
{
	UI::Update();
	Vector2 pos = GetPos();
	Vector2 scale = GetScale();
	if (KEY_TAP(KEY::LBTN) && !m_playTrig)
	{
		m_playTrig = true;
	}

	if (m_strSize < m_str.size() && m_playTrig)
	{
		m_strSize += 20 * fDT;
	}

	m_printRect.left = (LONG)pos.x;
	m_printRect.top = (LONG)pos.y;
	m_printRect.right = (LONG)(pos.x + scale.x);
	m_printRect.bottom = (LONG)(pos.y + scale.y);
}

void TextUI::Render(HDC _dc)
{
	wstring path = PathManager::GetInst()->GetContentPath();
	path += L"font\\DOSGothic.ttf";
	AddFontResource(path.c_str());
	HFONT hFont = CreateFont(27, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"DOSGothic");

	HFONT hOldFont = static_cast<HFONT>(SelectObject(_dc, hFont));

// 	LOGFONT lf;
// 	ZeroMemory(&lf, sizeof(LOGFONT));
// 	lf.lfHeight = 20; // ��Ʈ ����
// 	lf.lfWeight = FW_NORMAL; // ��Ʈ �β�
// 	wcscpy_s(lf.lfFaceName, LF_FACESIZE, L"DOSGothic"); // ��Ʈ �̸�
// 	HFONT hFont = CreateFontIndirect(&lf);

	// ��Ʈ ����
// 	HFONT hOldFont = static_cast<HFONT>(SelectObject(_dc, hFont));

	SetTextColor(_dc, RGB(255, 255, 255)); // �ؽ�Ʈ ���� ����
	SetBkColor(_dc, RGB(0, 0, 0)); // �ؽ�Ʈ�� ��� ���� ����

	DrawText(_dc
		, m_str.c_str()
		, m_strSize
		, &m_printRect
		, DT_CENTER);
	//DeleteObject(hBrushBackground);

// 	SelectObject(_dc, hOldFont);
// 
// 	// ��Ʈ ����
// 	DeleteObject(hFont);

	SelectObject(_dc, hOldFont); // ���� ��Ʈ�� ����
	DeleteObject(hFont); // ��Ʈ ����
	RemoveFontResource(L"C:\\Path\\To\\FontFile.ttf"); // �ܺ� ��Ʈ ����
}

TextUI::TextUI(bool _bCamAff, Scene* _ownerScene)
	: UI(_bCamAff, _ownerScene)
	, m_strSize(0.f)
	, m_printRect{}
{

}

TextUI::~TextUI()
{

}
