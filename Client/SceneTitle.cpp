#include "pch.h"
#include "SceneTitle.h"
#include "Background.h"
#include "ResourceManager.h"
#include "SoundManager.h"
#include "ImageUI.h"
#include "ButtonUI.h"
#include "CollisionManager.h"
#include "Camera.h"
#include "GameProcess.h"
#include "Scene.h"
#include "TimeManager.h"
#include "Animator.h"

void StartGame(DWORD_PTR, DWORD_PTR);
void ExitGame(DWORD_PTR, DWORD_PTR);

SceneTitle::SceneTitle(HWND _hWnd)
	: Scene(_hWnd)
{
}

SceneTitle::~SceneTitle()
{

}

void SceneTitle::Update()
{
	Scene::Update();
// 
// 	vector<GameObject*>& uiGroup = GetUIGroup();
// 	vector<GameObject*>::iterator iter = uiGroup.begin();
// 	for (; iter != uiGroup.end(); ++iter) {
// 		if ((*iter)->GetName() == L"cursor")
// 		{
// 			break;
// 		}
// 	}
// 	if (iter == uiGroup.end())
// 		return;
// 	if ((*iter)->GetPos().x >= 960.f)
// 	{
// 		Vector2 pos = (*iter)->GetPos();
// 		pos.x += -800.f * fDT;
// 		(*iter)->SetPos(pos);
// 	}
// 	if ((*iter)->GetPos().x < 960.f)
// 	{
// 		
// 	}


}

void SceneTitle::Enter()
{

	Background* pTitleBG = new Background(false, this);
	pTitleBG->SetName(L"TitleBG");
	pTitleBG->SetTex(ResourceManager::GetInst()->LoadTexture(L"BG_Title", L"texture\\bg\\main_uiani-Sheet.bmp"));
	pTitleBG->GetAnimator()->CreateAnimation(L"bg_title", pTitleBG->GetTex(), Vector2(0.f, 0.f), Vector2(1920.f, 1080.f), Vector2(1920.f, 0.f), 0.1f, 10);
	pTitleBG->GetAnimator()->Play(L"bg_title", true);
	pTitleBG->SetPos(Vector2(960.f, 540.f));
	pTitleBG->SetScale(pTitleBG->GetBgScale());
	AddObject(pTitleBG, GROUP_TYPE::BACKGROUND);


	ImageUI* pTitle = new ImageUI(false, this);
	pTitle->SetName(L"Title");
	pTitle->SetTex(ResourceManager::GetInst()->LoadTexture(L"TitleName", L"texture\\Main_title24.bmp"));
	pTitle->SetTexScale();
	pTitle->AlignHorizontalCenter();
	pTitle->SetPos(pTitle->GetPos() + Vector2(0, 225));
	AddObject(pTitle, GROUP_TYPE::UI);

	ButtonUI* pBtn = new ButtonUI(false, this);
	pBtn->SetName(L"StartBtn");
	pBtn->SetTex(ResourceManager::GetInst()->LoadTexture(L"StartBtn", L"texture\\Main_button_START24.bmp"));
	pBtn->SetTexScale();
	pBtn->AlignHorizontalCenter();
	pBtn->AlignVerticalBottom();
	pBtn->SetPos(pBtn->GetPos() + Vector2(0.f, -440.f));
	pBtn->SetClickedCallBack(StartGame, (DWORD_PTR)this, 0);
	AddObject(pBtn, GROUP_TYPE::UI);

	pBtn = new ButtonUI(false, this);
	pBtn->SetName(L"ExitBtn");
	pBtn->SetTex(ResourceManager::GetInst()->LoadTexture(L"ExitBtn", L"texture\\Main_button_EXIT24.bmp"));
	pBtn->SetTexScale();
	pBtn->AlignHorizontalCenter();
	pBtn->AlignVerticalBottom();
	pBtn->SetPos(pBtn->GetPos() + Vector2(0.f, -290.f));
	pBtn->SetClickedCallBack(ExitGame, (DWORD_PTR)this, 0);
	AddObject(pBtn, GROUP_TYPE::UI);

	Vector2 vReslolution = GetResolution();

	Camera::GetInst()->SetLookAt(vReslolution /2.f);

	SoundManager::GetInst()->Initialize();

	SoundManager::GetInst()->StopBGM();
	SoundManager::GetInst()->PlayBGM(MENU_LOBBY);
}

void SceneTitle::Exit()
{
	DeleteAll();

	CollisionManager::GetInst()->Reset();
}


void StartGame(DWORD_PTR _curScene, DWORD_PTR) 
{
// 	Scene* curScene = (Scene*)_curScene;
// 	ImageUI* imageUI = new ImageUI(false, curScene);
// 	imageUI->SetName(L"cursor");
// 	imageUI->SetTex(ResourceManager::GetInst()->LoadTexture(L"cursor", L"texture\\cursor.bmp"));
// 	imageUI->SetTexScale();
// 	imageUI->SetPos(Vector2(curScene->GetResolution().x, 500.f));
// 
// 	CreateObject(imageUI, GROUP_TYPE::UI);
// 
// 	
	ChangeScene(SCENE_TYPE::NARRATIVE_01);
}

void ExitGame(DWORD_PTR _curScene, DWORD_PTR) {
	DestroyWindow(((Scene*)_curScene)->GetCurrendWindow());
}