#pragma once

class Animator;
class Texture;

struct tAnimFrm
{
	Vector2	vLT;
	Vector2	vSlice;
	Vector2	vOffset;
	float	fDuration;

};

class Animation
{
private:
	wstring				m_strName;
	Animator* m_pAnimator;
	Texture* m_pTex;		// Animation이 사용하는 텍스쳐
	vector<tAnimFrm>	m_vecFrm;	// 모든 프레임 정보
	int					m_iCurFrm;  // 현재 프레임
	float				m_fAccTime; // 시간 누적

	bool				m_bFinish;  // 재생 끝에 도달 여부

public:
	const wstring& GetName() { return m_strName; }
	bool IsFinish() { return m_bFinish; }
	void SetFrame(int _iFrameIdx)
	{
		m_bFinish = false;
		m_iCurFrm = _iFrameIdx;
		m_fAccTime = 0.f;
	}

	tAnimFrm& GetFrame(int _iIdx) { return m_vecFrm[_iIdx]; }
	int GetMaxFrame() { return (int)m_vecFrm.size(); }
	int	GetCurFrame() { return m_iCurFrm; }

private:
	void SetName(const wstring& _strName) { m_strName = _strName; }

public:
	void update();
	void render(HDC _dc);
	void Create(Texture* _pTex, Vector2 _vLT, Vector2 _vSliceSize, Vector2 _vStep, float _fDuration, UINT _iFrameCount);

public:
	Animation();
	~Animation();

	friend class Animator;
};

