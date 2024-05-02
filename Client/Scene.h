#pragma once

#include <windows.h>
/// ����� ��ȣ ������ �������� CObject ���� ����
/// ������ Ÿ������ �ۿ� ��� ���Ѵ�.
class GameObject;

class Scene
{
private:
	// ������Ʈ�� ���� �� ������ ���͸� �׷� ������ŭ ����
	vector<GameObject*>	m_arrObj[(UINT)GROUP_TYPE::END];

	wstring				m_strName;	// Scene �̸�
	GameObject*			m_pPlayer;  // Player
	bool				m_bPause;	// Pause ��������

	HWND				m_hWnd;		// hWnd�� �˾ƾ��Ѵ�.

	SCENE_TYPE			m_sceneType;

public:
	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }

	GameObject* GetPlayer() { return m_pPlayer; }
	GameObject* SetObject(GROUP_TYPE _eType, UINT _index) { return m_arrObj[(UINT)_eType][_index]; }

	bool IsPause() { return m_bPause; }
	void TogglePause() { m_bPause = !m_bPause; }

	void SetSceneType(SCENE_TYPE _sType) { m_sceneType = _sType; }
	SCENE_TYPE GetSceneType() { return m_sceneType; }

	HWND GetCurrendWindow() { return m_hWnd; }

public:
	virtual void Start();
	virtual void Update();
	virtual void FinalUpdate();
	virtual void Render(HDC _dc);

	// ���� �����Լ�, ���� �����Լ��� ���Ե� Ŭ������ ��ü�� ������ �� ����.
	virtual void Enter() = 0;	// �ش� Scene�� ���Խ� ȣ��
	virtual void Exit() = 0;	// �ش� Scene�� Ż��� ȣ��

public:
	/// Ŭ������ ����� �����ϸ� �ζ��� ó���Ǽ� ����� ����
	void AddObject(GameObject* _pObj, GROUP_TYPE _eType)
	{
		m_arrObj[(UINT)_eType].push_back(_pObj);
	}
	
	const vector<GameObject*>& GetGroupObject(GROUP_TYPE _eType) 
	{
		return m_arrObj[(UINT)_eType];
	}

	void DeleteGroup(GROUP_TYPE _eTarget);
	void DeleteAll();
	void RegisterPlayer(GameObject* _pPlayer) { m_pPlayer = _pPlayer; }

	vector<GameObject*>& GetUIGroup() { return m_arrObj[(UINT)GROUP_TYPE::UI]; }

	Vector2 GetResolution();

public:
	Scene(HWND _hWnd);
	virtual ~Scene();
};

