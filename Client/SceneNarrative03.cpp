#include "pch.h"
#include "SceneNarrative03.h"
#include "Background.h"
#include "ResourceManager.h"
#include "ImageUI.h"
#include "Camera.h"
#include "TextUI.h"
#include "CollisionManager.h"
#include "KeyManager.h"

SceneNarrative03::SceneNarrative03(HWND _hWnd)
	: Scene(_hWnd)
{

}

SceneNarrative03::~SceneNarrative03()
{

}

void SceneNarrative03::Update()
{
	Scene::Update();

	GameObject* textObj = SetObject(GROUP_TYPE::UI, 0);
	TextUI* textUI = dynamic_cast<TextUI*>(textObj);
	assert(textUI);

	if (KEY_TAP(KEY::LBTN)) {
		if (textUI->GetStringSize() >= textUI->GetString().size())
		{
			ChangeScene(SCENE_TYPE::SELECT);
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

void SceneNarrative03::Enter()
{
	Background* pTitleBG = new Background(false, this);
	pTitleBG->SetTex(ResourceManager::GetInst()->LoadTexture(L"cutscene3", L"texture\\cutscene\\cut_scene_03.bmp"));
	pTitleBG->SetPos(Vector2(0.f, 0.f));
	pTitleBG->SetScale(pTitleBG->GetBgScale());
	AddObject(pTitleBG, GROUP_TYPE::BACKGROUND);

	TextUI* textUI = new TextUI(false, this);
	textUI->SetName(L"cutscene01image");
	textUI->SetPos(Vector2(0.f, 800.f));
	textUI->SetScale(Vector2(1920.f, 400.f));
	textUI->SetString(L"모든 것이 흘러나온 후, 당신의 앞에는 안경 하나만 덩그러니 놓여있습니다.\n\n\n갑자기 길고 긴 휴가동안 할 게 생겼습니다.\n\n잃어버린 것을 찾아야만 합니다.");
	AddObject(textUI, GROUP_TYPE::UI);

	Vector2 vReslolution = GetResolution();

	Camera::GetInst()->SetLookAt(vReslolution / 2.f);
}

void SceneNarrative03::Exit()
{
	DeleteAll();

	CollisionManager::GetInst()->Reset();
}
