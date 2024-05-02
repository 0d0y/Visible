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
	/// 원래는 virtual을 안적어줘도 되지만 명시적으로 virtual을 적어준다.
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

