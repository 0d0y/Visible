#pragma once

#include <windows.h>
/// 헤더별 상호 참조를 막기위해 CObject 전방 선언
/// 포인터 타입으로 밖에 사용 못한다.
class GameObject;

class Scene
{
private:
	// 오브젝트를 저장 및 관리할 벡터를 그룹 개수만큼 선언
	vector<GameObject*>	m_arrObj[(UINT)GROUP_TYPE::END];

	wstring				m_strName;	// Scene 이름
	GameObject*			m_pPlayer;  // Player
	bool				m_bPause;	// Pause 상태인지

	HWND				m_hWnd;		// hWnd를 알아야한다.

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

	// 순수 가상함수, 순수 가상함수가 포함된 클래스는 객체를 생성할 수 없다.
	virtual void Enter() = 0;	// 해당 Scene에 진입시 호출
	virtual void Exit() = 0;	// 해당 Scene을 탈출시 호출

public:
	/// 클래스를 헤더에 구현하면 인라인 처리되서 비용이 적다
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

