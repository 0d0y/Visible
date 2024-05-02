#pragma once

class UI;
class Scene;

class UIManager
{
	SINGLE(UIManager);

private:
	UI* m_pFocusedUI;

public:

	void Update(Scene* pCurScene);
	void SetFocusedUI(UI* _pUI, Scene* _pCurScene);
private:
	// 부모 UI 내에서 실제로 타겟팅 된 UI를 찾아서 반환한다. 

	UI* GetFocusedUI(Scene* _pCurScene);
	UI* GetTargetUI(UI* _pParentUI);


};

