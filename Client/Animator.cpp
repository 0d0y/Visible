#include "pch.h"
#include "Animator.h"

#include "Animation.h"
#include "GameObject.h"
#include "Player.h"

Animator::Animator()
	: m_pCurAnim(nullptr)
	, m_pOwner(nullptr)
	, m_bRepeat(false)
{
}

Animator::~Animator()
{
	SafeDeleteMap(m_mapAnim);
}

void Animator::update()
{
}
void Animator::finalupdate()
{
	if (m_pCurAnim != nullptr)
	{
		m_pCurAnim->update();

		if (m_bRepeat && m_pCurAnim->IsFinish())
		{
			m_pCurAnim->SetFrame(0);
		}
	}
}

void Animator::render(HDC _dc)
{
	if (nullptr != m_pCurAnim)
		m_pCurAnim->render(_dc);
}

void Animator::CreateAnimation(const wstring& _strName, Texture* _pTex, Vector2 _vLT
	, Vector2 _vSliceSize, Vector2 _vStep, float _fDuration, UINT _iFrameCount)
{
	Animation* pAnim = FindAnimation(_strName);
	assert(nullptr == pAnim);

	pAnim = new Animation;

	pAnim->SetName(_strName);
	pAnim->m_pAnimator = this;
	pAnim->Create(_pTex, _vLT, _vSliceSize, _vStep, _fDuration, _iFrameCount);

	m_mapAnim.insert(make_pair(_strName, pAnim));
}



Animation* Animator::FindAnimation(const wstring& _strName)
{
	map<wstring, Animation*>::iterator iter = m_mapAnim.find(_strName);

	if (iter == m_mapAnim.end())
		return nullptr;

	return iter->second;
}

void Animator::Play(const wstring& _strName, bool _bRepeat)
{
	m_pCurAnim = FindAnimation(_strName);
	m_bRepeat = _bRepeat;
}
