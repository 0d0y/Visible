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
	textUI->SetString(L"������ �ʹ� ��ģ ſ�̾������?\n\n��ſ��Լ� �����ΰ� �귯������ �־����ϴ�.\n\n\n�̰� ���������� �� �𸣰�����,\n\n��ſ��� �ſ� ������ �͵��̶�� Ȯ���� ��ϴ�.");
	AddObject(textUI, GROUP_TYPE::UI);

	Vector2 vReslolution = GetResolution();

	Camera::GetInst()->SetLookAt(vReslolution / 2.f);
}

void SceneNarrative02::Exit()
{
	DeleteAll();

	CollisionManager::GetInst()->Reset();
}
