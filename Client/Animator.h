#pragma once

class GameObject;
class Animation;
class Texture;

class Animator
{
private:
	map<wstring, Animation*> m_mapAnim;		//��� Animation map
	Animation* m_pCurAnim;		//���� ������� Animation
	GameObject* m_pOwner;		//Animator ���� Object
	bool m_bRepeat;		//�ݺ���� ����

public:
	GameObject* GetObj() { return m_pOwner; }

public:
	void CreateAnimation(const wstring& _strName, Texture* _pTex, Vector2 _vLT, Vector2 _vSliceSize, Vector2 _vStep, float _fDuration, UINT _iFrameCount);
	Animation* FindAnimation(const wstring& _strName);
	Animation* GetCurAnim() { return m_pCurAnim; }
	void Play(const wstring& _strName, bool m_bRepeat);
	void DeleteAnim() { SafeDeleteMap(m_mapAnim); }

	void update();
	void finalupdate();
	void render(HDC _dc);

public:
	Animator();
	~Animator();

	friend class GameObject;
};

