#include "pch.h"
#include "Camera.h"

#include "GameObject.h"
#include "GameProcess.h"
#include "TimeManager.h"
#include "KeyManager.h"
#include "ResourceManager.h"
#include "Texture.h"

Camera::Camera()
	: m_pTargetObj(nullptr)
	, m_fTime(0.2f)
	, m_fSpeed(0.f)
	, m_fAccTime(0.2f)
	, m_hWnd(0)
	, m_veilTex(nullptr)
	, m_duringFade(false)
{

}

Camera::~Camera() {

}

void Camera::Initialize(HWND _hWnd)
{
	m_hWnd = _hWnd;

	Vector2 resolution = GetResolution();
	m_veilTex = ResourceManager::GetInst()->CreateTexture(L"cameraVeil", (UINT)resolution.x, (UINT)resolution.y);	
	//m_veilTex = ResourceManager::GetInst()->LoadTexture(L"vextile", L"texture\\vextile.bmp");
}
void Camera::Update()
{
	if (m_pTargetObj)
	{
		if (m_pTargetObj->IsDead())
		{
			m_pTargetObj = nullptr;
		}
		else
		{
			m_vLookAt = m_pTargetObj->GetPos();
		}
	}

	//if (KEY_HOLD(KEY::UP))
	//	m_vLookAt.y -= 500.f * fDT;
	//if (KEY_HOLD(KEY::DOWN))
	//	m_vLookAt.y += 500.f * fDT;
	//if (KEY_HOLD(KEY::LEFT))
	//	m_vLookAt.x -= 500.f * fDT;
	//if (KEY_HOLD(KEY::RIGHT))
	//	m_vLookAt.x += 500.f * fDT;

	CalDiff();
}

void Camera::Render(HDC _dc)
{
	if (m_camEffect.empty())
	{
		m_duringFade = false;
		return;
	}

	Vector2 resolution = GetResolution();
	m_veilTex = ResourceManager::GetInst()->CreateTexture(L"cameraVeil", (UINT)resolution.x, (UINT)resolution.y);

	//시간 누적값을 체크해서
	CamEffect& effect = m_camEffect.front();
	effect.curTime += fDT;

	float ratio = 0.f; //이펙트 진행 비율
	ratio = effect.curTime / effect.duration;

	if (ratio < 0.f)
		ratio = 0.f;
	if (ratio > 1.f)
		ratio = 1.f;

	BYTE alpha = 0;
	if (CAM_EFFECT::FADE_OUT == effect.effect)
	{
		m_duringFade = true;
		alpha = (BYTE)(255.f * ratio);
	}
	else if (CAM_EFFECT::FADE_IN == effect.effect)
	{
		m_duringFade = false;
		alpha = (BYTE)(255.f * (1.f - ratio));
	}
	BLENDFUNCTION bf = {};
	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.AlphaFormat = 0;
	bf.SourceConstantAlpha = alpha;

	AlphaBlend(_dc, 0, 0
		, (int)m_veilTex->Width()
		, (int)m_veilTex->Height()
		, m_veilTex->GetDC()
		, 0, 0
		, (int)m_veilTex->Width()
		, (int)m_veilTex->Height()
		, bf);

	//진행 시간이 이펙트 최대 지정 시간을 넘어선 경우
	if (effect.duration < effect.curTime)
	{
		//효과 종료
		m_camEffect.pop_front();
	}
}

void Camera::CalDiff()
{
	// 이전 LookAt과 현재 LookAt의 차이값을 보정해서 현재의 LookAt을 구한다.

	Vector2 vLookDir = m_vLookAt - m_vPrevLookAt;

	if (vLookDir.Length() == 0.f)
		m_fAccTime = m_fTime;
	m_fAccTime += fDT;

	if (m_fAccTime >= m_fTime)
	{
		m_vCurLookAt = m_vLookAt;
	}
	else
	{
		m_vCurLookAt = m_vPrevLookAt + vLookDir.Normalize() * m_fSpeed * fDT;
	}
	// 
	// 	m_vCurLookAt = m_vLookAt;

	Vector2 vResolution = GetResolution();
	Vector2 vCenter = vResolution / 2;

	m_vDiff = m_vCurLookAt - vCenter;


	m_vPrevLookAt = m_vCurLookAt;
}

Vector2 Camera::GetResolution()
{
	RECT clientRect = {};
	GetClientRect(m_hWnd, &clientRect);

	return Vector2((float)clientRect.right, (float)clientRect.bottom);
}
