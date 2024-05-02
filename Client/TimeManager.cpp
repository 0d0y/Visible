#include "pch.h"
#include "TimeManager.h"
#include "GameProcess.h"

TimeManager::TimeManager()
	: m_llCurCount{}	// 유니온
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
	// 현재 카운트
	QueryPerformanceCounter(&m_llPrevCount);

	// 초당 카운트 횟수
	QueryPerformanceFrequency(&m_llFrequnecy);
}

void TimeManager::Update()
{
	QueryPerformanceCounter(&m_llCurCount);

	// 이전 프레임의 카운팅과 현재 프레임 카운팅 값의 차이를 구한다.
	m_dDt = (double)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart) / (double)m_llFrequnecy.QuadPart;

	// 이전 카운트 값을 현재값으로 갱신(다음 번 계산을 위해서)
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
	
	//1초 체크를 위한 누적 시간
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
