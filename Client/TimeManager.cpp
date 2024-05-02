#include "pch.h"
#include "TimeManager.h"
#include "GameProcess.h"

TimeManager::TimeManager()
	: m_llCurCount{}	// ���Ͽ�
	, m_llPrevCount{}
	, m_llFrequnecy{}
	, m_dDt(0.0)
	, m_iCallCount(0)
	, m_dAcc(0)
	, m_iFPS(0)
{

}

TimeManager::~TimeManager()
{

}

void TimeManager::Initialize()
{
	// ���� ī��Ʈ
	QueryPerformanceCounter(&m_llPrevCount);

	// �ʴ� ī��Ʈ Ƚ��
	QueryPerformanceFrequency(&m_llFrequnecy);
}

void TimeManager::Update()
{
	QueryPerformanceCounter(&m_llCurCount);

	// ���� �������� ī���ð� ���� ������ ī���� ���� ���̸� ���Ѵ�.
	m_dDt = (double)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart) / (double)m_llFrequnecy.QuadPart;

	// ���� ī��Ʈ ���� ���簪���� ����(���� �� ����� ���ؼ�)
	m_llPrevCount = m_llCurCount;


#ifdef _DEBUG
	if (m_dDt > (1. / 30.))
		m_dDt = (1. / 30.);
#endif // DEBUG
}

void TimeManager::Render()
{
	// FPS
	++m_iCallCount;
	HWND hWnd = GetFocus();
	
	//1�� üũ�� ���� ���� �ð�
	m_dAcc += m_dDt;

	if (m_dAcc >= 1.0 && hWnd)
	{
		m_iFPS = m_iCallCount;
		m_dAcc = 0.0;
		m_iCallCount = 0;

		wchar_t szBuffer[255] = {};

		swprintf_s(szBuffer, L"FPS : %d, DT : %f", m_iFPS, m_dDt);
		
		wstring frameBuffer = szBuffer;
		SetWindowText(hWnd, szBuffer);

		OutputDebugString(frameBuffer.c_str());
		OutputDebugString(TEXT("\n"));
	}

}
