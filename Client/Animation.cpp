#include "pch.h"
#include "Animation.h"

#include "TimeManager.h"

#include "Animator.h"
#include "Texture.h"
#include "GameObject.h"

#include "Camera.h"
#include "Fsm.h"


Animation::Animation()
	: m_pAnimator(nullptr)
	, m_pTex(nullptr)
	, m_iCurFrm(0)
	, m_fAccTime(0.f)
	, m_bFinish(false)
{
}

Animation::~Animation()
{
}

void Animation::update()
{
	if (m_bFinish)
		return;


	m_fAccTime += fDT;

	if (m_vecFrm[m_iCurFrm].fDuration < m_fAccTime)
	{
		++m_iCurFrm;

		if (m_vecFrm.size() <= m_iCurFrm)
		{
			m_iCurFrm = -1;
			m_bFinish = true;
			m_fAccTime = 0.f;
			return;
		}
		m_fAccTime = m_fAccTime - m_vecFrm[m_iCurFrm].fDuration;
	}
}

void Animation::render(HDC _dc)
{
	if (m_bFinish)
		return;

	GameObject* pObj = m_pAnimator->GetObj();
	Vector2 vPos = pObj->GetPos();

	vPos += m_vecFrm[m_iCurFrm].vOffset; // Object Position 에 Offset 만큼 추가 이동 위치

	// 렌더링 좌표로 변환
	if (m_pAnimator->GetObj()->GetName() == L"TitleBG")
		;
	else
		vPos = Camera::GetInst()->GetRenderPos(vPos);

	TransparentBlt(_dc
		, (int)(vPos.x - m_vecFrm[m_iCurFrm].vSlice.x / 2.f)
		, (int)(vPos.y - m_vecFrm[m_iCurFrm].vSlice.y / 2.f)
		, (int)(m_vecFrm[m_iCurFrm].vSlice.x)
		, (int)(m_vecFrm[m_iCurFrm].vSlice.y)
		, m_pTex->GetDC()
		, (int)(m_vecFrm[m_iCurFrm].vLT.x)
		, (int)(m_vecFrm[m_iCurFrm].vLT.y)
		, (int)(m_vecFrm[m_iCurFrm].vSlice.x)
		, (int)(m_vecFrm[m_iCurFrm].vSlice.y)
		, RGB(255, 0, 255)
	);
}

void Animation::Create(Texture* _pTex, Vector2 _vLT, Vector2 _vSliceSize, Vector2 _vStep, float _fDuration, UINT _iFrameCount)
{
	m_pTex = _pTex;

	tAnimFrm frm = {};
	for (int i = 0; i < (int)_iFrameCount; ++i)
	{
		frm.fDuration = _fDuration;
		frm.vSlice = _vSliceSize;
		frm.vLT = _vLT + _vStep * i;

		m_vecFrm.push_back(frm);
	}
}

