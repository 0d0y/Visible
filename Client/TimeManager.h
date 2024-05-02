#pragma once


class TimeManager
{
	SINGLE(TimeManager);
private:
	LARGE_INTEGER	m_llCurCount;
	LARGE_INTEGER	m_llPrevCount;
	LARGE_INTEGER	m_llFrequnecy;

	double			m_dDt;	// 프레임 간의 시간 값, 델타 타임
	double			m_dAcc;	// 1초 체크를 위한 누적 시간
	UINT			m_iCallCount;	// 함수 호출 회수 체크
	UINT			m_iFPS;			// 초당 호출 횟수 
	
	// FPS
	// 1. 프레임당 시간, delta Time

public:
	// GetTickCount는 프레임 체크를 하기에는 너무 느리고 오차도 있음
	// 정밀하고 정확한 카운트를 할 함수가 필요함
	void Initialize();
	void Update();
	void Render();

public:
	double GetDT() { return m_dDt; }
	float GetfDT() { return (float)m_dDt; }
};

