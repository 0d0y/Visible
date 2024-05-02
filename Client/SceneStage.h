#pragma once
#include "Scene.h"

class ImageUI;
class Texture;
class Background;

class SceneStage :
    public Scene
{
private:
	vector<vector<wstring>> m_csvData;
	ImageUI* m_pCurrSunglassUI;
	ImageUI* m_pNextSunglassUI;


public:
	/// ������ virtual�� �������൵ ������ ��������� virtual�� �����ش�.
	virtual void Update();
	virtual void Enter();
	virtual void Exit();
	virtual void FinalUpdate();

public:
	void SetScvData(vector<vector<wstring>> _csvData) { m_csvData = _csvData; }

public:
	virtual void UpdateStageUI(Background* _background);

public:
	SceneStage(HWND _hWnd);
	virtual ~SceneStage();
	void ReloadBoundary();

};

