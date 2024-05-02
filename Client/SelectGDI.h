#pragma once
class SelectGDI
{

	SINGLE(SelectGDI);

private:
	HDC		m_hDC;
	HPEN	m_hDefaultPen;
	HBRUSH	m_hDefaultBrush;

	// 자주 사용하는 GDI Object
	HBRUSH	m_arrBrush[(UINT)BRUSH_TYPE::END];
	HPEN	m_arrPen[(UINT)PEN_TYPE::END];

public:
	void CreateBrushPen();

	HBRUSH GetBrush(BRUSH_TYPE _eType) { return m_arrBrush[(UINT)_eType]; }
	HPEN GetPen(PEN_TYPE _eType) { return m_arrPen[(UINT)_eType]; }

public:


	void SelectBrush(HDC _dc, BRUSH_TYPE _eBrushType);

	void SelectPen(HDC _dc, PEN_TYPE _ePenType);
	void ReturnGDI(HDC _dc);
};

