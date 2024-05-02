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
	// �θ� UI ������ ������ Ÿ���� �� UI�� ã�Ƽ� ��ȯ�Ѵ�. 

	UI* GetFocusedUI(Scene* _pCurScene);
	UI* GetTargetUI(UI* _pParentUI);


};

