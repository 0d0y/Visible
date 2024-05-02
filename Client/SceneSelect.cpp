#include "pch.h"
#include "SceneSelect.h"
#include "Background.h"
#include "ResourceManager.h"
#include "SoundManager.h"
#include "ImageUI.h"
#include "SelecterUI.h"
#include "ButtonUI.h"
#include "CollisionManager.h"
#include "Camera.h"
#include "GameProcess.h"
#include "Animator.h"


void SelectStage(DWORD_PTR _stage, DWORD_PTR);



SceneSelect::SceneSelect(HWND _hWnd)
	: Scene(_hWnd)
{

}

SceneSelect::~SceneSelect()
{

}

void SceneSelect::Update()
{
	Scene::Update();




}

void SceneSelect::Enter()
{
	Background* pTitleBG = new Background(false, this);
	pTitleBG->SetTex(ResourceManager::GetInst()->LoadTexture(L"BG_Selection", L"texture\\bg\\main.bmp"));
	pTitleBG->SetPos(Vector2(0.f, 0.f));
	pTitleBG->SetScale(pTitleBG->GetBgScale());
	AddObject(pTitleBG, GROUP_TYPE::BACKGROUND);


	ButtonUI* pBtn = new ButtonUI(false, this);
	pBtn->SetName(L"StageBtn1");
	pBtn->SetTex(ResourceManager::GetInst()->LoadTexture(L"StageBtn", L"texture\\stage_scene_checkpoint.bmp"));
	pBtn->SetTexScale();
	pBtn->AlignHorizontalLeft();
	pBtn->AlignVerticalTop();
	pBtn->SetPos(pBtn->GetPos() + Vector2(315.f, 465.f));
	pBtn->SetClickedCallBack(SelectStage, (DWORD_PTR)(SCENE_TYPE::STAGE_01), 0);

	
	ImageUI* imageUI = new ImageUI(false, this);
	imageUI->SetName(L"StageImage");
	imageUI->SetTex(ResourceManager::GetInst()->LoadTexture(L"chapter1_ui_prame", L"texture\\ui\\chapter1_ui_prame24.bmp"));
	imageUI->SetTexScale();
	pBtn->AddChild(imageUI);
	imageUI->AlignHorizontalCenter();
	imageUI->AlignVerticalTop();
	imageUI->SetPos(imageUI->GetPos() + Vector2(0.f, -210.f));

	AddObject(pBtn, GROUP_TYPE::UI);


	pBtn = new ButtonUI(false, this);
	pBtn->SetName(L"StageBtn2");
	pBtn->SetTex(ResourceManager::GetInst()->LoadTexture(L"StageBtn", L"texture\\stage_scene_checkpoint.bmp"));
	pBtn->SetTexScale();
	pBtn->AlignHorizontalLeft();
	pBtn->AlignVerticalTop();
	pBtn->SetPos(pBtn->GetPos() + Vector2(865.f, 560.f));
	pBtn->SetClickedCallBack(SelectStage, (DWORD_PTR)(SCENE_TYPE::STAGE_02), 0);


	imageUI = new ImageUI(false, this);
	imageUI->SetName(L"StageImage");
	imageUI->SetTex(ResourceManager::GetInst()->LoadTexture(L"chapter2_ui_prame", L"texture\\ui\\chapter2_ui_prame24.bmp"));
	imageUI->SetTexScale();
	pBtn->AddChild(imageUI);
	imageUI->AlignHorizontalCenter();
	imageUI->AlignVerticalTop();
	imageUI->SetPos(imageUI->GetPos() + Vector2(0.f, -210.f));


	AddObject(pBtn, GROUP_TYPE::UI);




	pBtn = new ButtonUI(false, this);
	pBtn->SetName(L"StageBtn3");
	pBtn->SetTex(ResourceManager::GetInst()->LoadTexture(L"StageBtn", L"texture\\stage_scene_checkpoint.bmp"));
	pBtn->SetTexScale();
	pBtn->AlignHorizontalLeft();
	pBtn->AlignVerticalTop();
	pBtn->SetPos(pBtn->GetPos() + Vector2(1535.f, 365.f));
	pBtn->SetClickedCallBack(SelectStage, (DWORD_PTR)(SCENE_TYPE::STAGE_03), 0);

	imageUI = new ImageUI(false, this);
	imageUI->SetName(L"StageImage");
	imageUI->SetTex(ResourceManager::GetInst()->LoadTexture(L"chapter3_ui_prame", L"texture\\ui\\chapter3_ui_prame24.bmp"));
	imageUI->SetTexScale();
	pBtn->AddChild(imageUI);
	imageUI->AlignHorizontalCenter();
	imageUI->AlignVerticalTop();
	imageUI->SetPos(imageUI->GetPos() + Vector2(0.f, -210.f));


	AddObject(pBtn, GROUP_TYPE::UI);



	pBtn = new ButtonUI(false, this);
	pBtn->SetName(L"BackKey");
	pBtn->SetTex(ResourceManager::GetInst()->LoadTexture(L"BackBtn", L"texture\\backkey24.bmp"));
	pBtn->SetTexScale();
	pBtn->AlignVerticalBottom();
	pBtn->AlignHorizontalRight();
	pBtn->SetClickedCallBack(SelectStage, (DWORD_PTR)(SCENE_TYPE::TITLE), 0);
	AddObject(pBtn, GROUP_TYPE::UI);


	SelecterUI* stageSeleter = new SelecterUI(false, this);
	stageSeleter->SetName(L"StageSelecter");
	stageSeleter->SetTex(ResourceManager::GetInst()->LoadTexture(L"StageSelecter", L"texture\\player_sprite_A.bmp"));
	stageSeleter->SetPos(Vector2(415.f, 565.f));
	stageSeleter->GetAnimator()->CreateAnimation(L"SELETER_WALK", stageSeleter->GetTex(), Vector2(0.f, 150.f), Vector2(160.f, 150.f), Vector2(160.f, 0.f), 0.1f, 6);
	stageSeleter->GetAnimator()->CreateAnimation(L"SELETER_JUMP", stageSeleter->GetTex(), Vector2(0.f, 300.f), Vector2(160.f, 150.f), Vector2(160.f, 0.f), 0.1f, 5);
	stageSeleter->GetAnimator()->CreateAnimation(L"SELETER_CLEAR", stageSeleter->GetTex(), Vector2(0.f, 600.f), Vector2(160.f, 150.f), Vector2(160.f, 0.f), 0.1f, 8);
	AddObject(stageSeleter, GROUP_TYPE::UI);



	Vector2 vReslolution = GetResolution();

	Camera::GetInst()->SetLookAt(vReslolution / 2.f);

	SoundManager::GetInst()->StopBGM();
	SoundManager::GetInst()->PlayBGM(MENU_SELECT);
}

void SceneSelect::Exit()
{
	DeleteAll();

	CollisionManager::GetInst()->Reset();

	SoundManager::GetInst()->StopBGM();
}

void SelectStage(DWORD_PTR _stage, DWORD_PTR) {
	ChangeScene((SCENE_TYPE)_stage);
}