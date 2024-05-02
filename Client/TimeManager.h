#pragma once


class TimeManager
{
	SINGLE(TimeManager);
private:
	LARGE_INTEGER	m_llCurCount;
	LARGE_INTEGER	m_llPrevCount;
	LARGE_INTEGER	m_llFrequnecy;

	double			m_dDt;	// ������ ���� �ð� ��, ��Ÿ Ÿ��
	double			m_dAcc;	// 1�� üũ�� ���� ���� �ð�
	UINT			m_iCallCount;	// �Լ� ȣ�� ȸ�� üũ
	UINT			m_iFPS;			// �ʴ� ȣ�� Ƚ�� 
	
	// FPS
	// 1. �����Ӵ� �ð�, delta Time

public:
	// GetTickCount�� ������ üũ�� �ϱ⿡�� �ʹ� ������ ������ ����
	// �����ϰ� ��Ȯ�� ī��Ʈ�� �� �Լ��� �ʿ���
	void Initialize();
	void Update();
	void Render();

public:
	double GetDT() { return m_dDt; }
	float GetfDT() { return (float)m_dDt; }
};

