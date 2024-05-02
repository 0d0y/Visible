#include "pch.h"
#include "SceneNarrative01.h"
#include "Background.h"
#include "ResourceManager.h"
#include "ImageUI.h"
#include "Camera.h"
#include "TextUI.h"
#include "CollisionManager.h"
#include "KeyManager.h"

SceneNarrative01::SceneNarrative01(HWND _hWnd)
	: Scene(_hWnd)
{

}

SceneNarrative01::~SceneNarrative01()
{

}

void SceneNarrative01::Update()
{
	
	Scene::Update();

	GameObject* textObj = SetObject(GROUP_TYPE::UI, 0);
	TextUI* textUI = dynamic_cast<TextUI*>(textObj);
	assert(textUI);

	if (KEY_TAP(KEY::LBTN)) {
		if (textUI->GetStringSize() >= textUI->GetString().size())
		{
			ChangeScene(SCENE_TYPE::NARRATIVE_02);
		}
		else if(textUI->GetStringSize() > 1.f)
		{
			textUI->SetStringSize((float)textUI->GetString().size());
		}
		else
		{

		}
	}

}

void SceneNarrative01::Enter()
{
	Background* pTitleBG = new Background(false, this);
	pTitleBG->SetTex(ResourceManager::GetInst()->LoadTexture(L"cutscene1", L"texture\\cutscene\\cut_scene_01.bmp"));
	pTitleBG->SetPos(Vector2(0.f, 0.f));
	pTitleBG->SetScale(pTitleBG->GetBgScale());
	AddObject(pTitleBG, GROUP_TYPE::BACKGROUND);

	TextUI* textUI = new TextUI(false, this);
	textUI->SetName(L"cutscene01image");
	textUI->SetPos(Vector2(0.f, 800.f));
	textUI->SetScale(Vector2(1920.f, 400.f));
	textUI->SetString(L"그동안 지나치게 바빴습니다.\n\n당신은 그동안의 노고를 뒤로 하고 휴양지에 도착했습니다.\n\n따뜻한 햇살과 바닷바람을 맞으며 나른하고 졸린 기분을 즐깁니다.\n");
	AddObject(textUI, GROUP_TYPE::UI);

	Vector2 vReslolution = GetResolution();

	Camera::GetInst()->SetLookAt(vReslolution / 2.f);
}

void SceneNarrative01::Exit()
{
	DeleteAll();

	CollisionManager::GetInst()->Reset();
}
