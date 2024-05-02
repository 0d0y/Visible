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
	Vector2		m_vLookAt;	//ī�޶� ���� ��ġ
	Vector2		m_vCurLookAt;
	Vector2		m_vPrevLookAt;	//ī�޶� ���� ���������� ��ġ
	GameObject* m_pTargetObj; // ī�޶� Ÿ�� ������Ʈ

	Vector2		m_vDiff;	// �ػ� �߽���ġ��, ī�޶� LookAt ���� ���̰�

	float		m_fTime;	// Ÿ���� ���󰡴µ� �ɸ��� �ð�.
	float		m_fSpeed;	// Ÿ���� ���󰡴� �ӵ� 
	float		m_fAccTime;	// ���� �ð� 
	
	list<CamEffect> m_camEffect;
	Texture* m_veilTex; //���̵� �ξƿ��� �ؽ���

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

