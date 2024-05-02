#pragma once

class Texture;
class GameObject;
class Texture;

enum class CAM_EFFECT
{
	FADE_IN,
	FADE_OUT,
	NONE,
};

struct CamEffect
{
	CAM_EFFECT effect;
	float duration;
	float curTime;
};

class Camera
{
	SINGLE(Camera);
private:
	Vector2		m_vLookAt;	//카메라가 보는 위치
	Vector2		m_vCurLookAt;
	Vector2		m_vPrevLookAt;	//카메라가 보는 이전프레임 위치
	GameObject* m_pTargetObj; // 카메라 타겟 오브젝트

	Vector2		m_vDiff;	// 해상도 중심위치와, 카메라 LookAt 간의 차이값

	float		m_fTime;	// 타겟을 따라가는데 걸리는 시간.
	float		m_fSpeed;	// 타겟을 따라가는 속도 
	float		m_fAccTime;	// 누적 시간 
	
	list<CamEffect> m_camEffect;
	Texture* m_veilTex; //페이드 인아웃용 텍스쳐

	HWND m_hWnd;

	bool m_duringFade;


public:
	void SetLookAt(Vector2 _vLook) {

		m_vLookAt = _vLook;
		float fMoveDist = (m_vLookAt - m_vPrevLookAt).Length();
		m_fSpeed = fMoveDist / m_fTime;
		m_fAccTime = 0.f;
	}
	void SetTarget(GameObject* _pTarget) { m_pTargetObj = _pTarget; }
	void SetCurLookAt(Vector2 _vLook) {
		m_vLookAt = _vLook;
		m_vCurLookAt = _vLook;
	}
	Vector2 GetCurLookAt() { return m_vCurLookAt; }
	Vector2 GetFinalLookAt() { return m_vLookAt; }

	Vector2 GetRenderPos(Vector2 _vObjPos) { return _vObjPos - m_vDiff; }
	Vector2 GetRealPos(Vector2 _vRenderPos) { return _vRenderPos + m_vDiff; }

	bool GetDuringFade() { return m_duringFade; }
	void FadeIn(float _duration)
	{
		CamEffect ef = {};
		ef.effect = CAM_EFFECT::FADE_IN;
		ef.duration = _duration;
		ef.curTime = 0.f;
		m_camEffect.push_back(ef);
		if (0.f == _duration)
			assert(nullptr);
	}
	void FadeOut(float _duration)
	{
		CamEffect ef = {};
		ef.effect = CAM_EFFECT::FADE_OUT;
		ef.duration = _duration;
		ef.curTime = 0.f;
		m_camEffect.push_back(ef);
		m_duringFade = true;
		if (0.f == _duration)
			assert(nullptr);
	}

public:
	void Initialize(HWND _hWnd);
	void Update();
	void Render(HDC _dc);


private:
	void CalDiff();
	Vector2 GetResolution();

};

