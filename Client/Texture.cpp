#include "pch.h"
#include "GameProcess.h"
#include "Texture.h"


Texture::Texture()
	: m_hBit(0)
	, m_dc(0)
	, m_bitInfo{}
{
}

Texture::~Texture()
{
	DeleteDC(m_dc);
	DeleteObject(m_hBit);

}


void Texture::Load(const wstring& _strFilePath, HDC _maindc)
{
	// ���Ϸκ��� �ε��� �����͸� ��Ʈ������ ����
	m_hBit = (HBITMAP)LoadImage(nullptr, _strFilePath.c_str(), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	assert(m_hBit);

	//��Ʈ�ʰ� ������ DC
	m_dc = CreateCompatibleDC(_maindc);

	//��Ʈ�ʰ� DC ����
	HBITMAP hPrevBit = (HBITMAP)SelectObject(m_dc, m_hBit);
	DeleteObject(hPrevBit);

	//��Ʈ�� ����
	GetObject(m_hBit, sizeof(BITMAP), &m_bitInfo);
}

void Texture::Create(UINT _width, UINT _height, HDC _mainDc)
{
	m_hBit = CreateCompatibleBitmap(_mainDc, _width, _height);
	m_dc = CreateCompatibleDC(_mainDc);

	HBITMAP hOldBit = (HBITMAP)SelectObject(m_dc, m_hBit);
	DeleteObject(hOldBit);

	GetObject(m_hBit, sizeof(BITMAP), &m_bitInfo);
}
