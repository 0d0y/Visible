#include "pch.h"
#include "SelectGDI.h"

#include "GameProcess.h"

SelectGDI::SelectGDI() {
	CreateBrushPen();
}


void SelectGDI::SelectBrush(HDC _dc, BRUSH_TYPE _eBrushType)

{
	m_hDC = _dc;
	HBRUSH hBrush = m_arrBrush[(int)_eBrushType];
	m_hDefaultBrush = (HBRUSH)SelectObject(_dc, hBrush);
}

void SelectGDI::SelectPen(HDC _dc, PEN_TYPE _ePenType)

{
	m_hDC = _dc;
	HPEN hPen = m_arrPen[(int)_ePenType];
	m_hDefaultPen = (HPEN)SelectObject(_dc, hPen);
	
}

void SelectGDI::ReturnGDI(HDC _dc) {
	SelectObject(m_hDC, m_hDefaultPen);
	SelectObject(m_hDC, m_hDefaultBrush);
}

SelectGDI::~SelectGDI()
{

	for (int i = 0; i < (UINT)PEN_TYPE::END; ++i)
	{
		DeleteObject(m_arrPen[i]);
	}
	for (int i = 0; i < (UINT)BRUSH_TYPE::END; ++i)
	{
		DeleteObject(m_arrBrush[i]);
	}
}


void SelectGDI::CreateBrushPen()
{
	// hollow brush
	m_arrBrush[(UINT)BRUSH_TYPE::BRUSH_HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	m_arrBrush[(UINT)BRUSH_TYPE::BRUSH_RED] = CreateSolidBrush(RGB(255, 0, 0));
	m_arrBrush[(UINT)BRUSH_TYPE::BRUSH_GREEN] = CreateSolidBrush(RGB(0, 255, 0));
	m_arrBrush[(UINT)BRUSH_TYPE::BRUSH_BLUE] = CreateSolidBrush(RGB(0, 0, 255));
	m_arrBrush[(UINT)BRUSH_TYPE::BRUSH_BLACK] = CreateSolidBrush(RGB(0, 0, 0));
	m_arrBrush[(UINT)BRUSH_TYPE::BRUSH_WHITE] = CreateSolidBrush(RGB(239, 231, 219));

	// red green blue pen
	m_arrPen[(UINT)PEN_TYPE::PEN_RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_arrPen[(UINT)PEN_TYPE::PEN_GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_arrPen[(UINT)PEN_TYPE::PEN_BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	m_arrPen[(UINT)PEN_TYPE::PEN_BLACK] = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	m_arrPen[(UINT)PEN_TYPE::PEN_WHITE] = CreatePen(PS_SOLID, 1, RGB(239, 231, 219));


}
