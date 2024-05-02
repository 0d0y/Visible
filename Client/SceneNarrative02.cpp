#include "pch.h"
#include "SceneNarrative02.h"
#include "Background.h"
#include "ResourceManager.h"
#include "ImageUI.h"
#include "Camera.h"
#include "TextUI.h"
#include "CollisionManager.h"
#include "KeyManager.h"

SceneNarrative02::SceneNarrative02(HWND _hWnd)
	: Scene(_hWnd)
{

}

SceneNarrative02::~SceneNarrative02()
{

}

void SceneNarrative02::Update()
{
	Scene::Update();

	GameObject* textObj = SetObject(GROUP_TYPE::UI, 0);
	TextUI* textUI = dynamic_cast<TextUI*>(textObj);
	assert(textUI);

	if (KEY_TAP(KEY::LBTN)) {
		if (textUI->GetStringSize() >= textUI->GetString().size())
		{
			ChangeScene(SCENE_TYPE::NARRATIVE_03);
		}
		else if (textUI->GetStringSize() > 1.f)
		{
			textUI->SetStringSize((float)textUI->GetString().size());
		}
		else
		{

		}
	}


}

void SceneNarrative02::Enter()
{
	Background* pTitleBG = new Background(false, this);
	pTitleBG->SetTex(ResourceManager::GetInst()->LoadTexture(L"cutscene2", L"texture\\cutscene\\cut_scene_02.bmp"));
	pTitleBG->SetPos(Vector2(0.f, 0.f));
	pTitleBG->SetScale(pTitleBG->GetBgScale());
	AddObject(pTitleBG, GROUP_TYPE::BACKGROUND);

	TextUI* textUI = new TextUI(false, this);
	textUI->SetName(L"cutscene02image");
	textUI->SetPos(Vector2(0.f, 800.f));
	textUI->SetScale(Vector2(1920.f, 400.f));
	textUI->SetString(L"하지만 너무 지친 탓이었을까요?\n\n당신에게서 무엇인가 흘러나오고 있었습니다.\n\n\n이게 무엇인지는 잘 모르겠지만,\n\n당신에게 매우 소중한 것들이라는 확신이 듭니다.");
	AddObject(textUI, GROUP_TYPE::UI);

	Vector2 vReslolution = GetResolution();

	Camera::GetInst()->SetLookAt(vReslolution / 2.f);
}

void SceneNarrative02::Exit()
{
	DeleteAll();

	CollisionManager::GetInst()->Reset();
}
