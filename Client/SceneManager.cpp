#include "pch.h"
#include "SceneManager.h"
#include "SoundManager.h"

#include "SceneStart.h"
#include "SceneTool.h"
#include "SceneTitle.h"
#include "SceneSelect.h"
#include "SceneStage01.h"
#include "SceneStage02.h"
#include "SceneStage03.h"
#include "SceneStage04.h"
#include "Camera.h"
#include "GameObject.h"
#include "Texture.h"
#include "Background.h"
#include "ResourceManager.h"
#include "SceneNarrative01.h"
#include "SceneNarrative02.h"
#include "SceneNarrative03.h"
SceneManager::SceneManager()
	: m_arrScene{}
	, m_pCurScene(nullptr)
	, m_hWnd(0)
{

}

SceneManager::~SceneManager()
{
	// 씬 전부 삭제
	for (UINT i = 0; i < (UINT)SCENE_TYPE::END; ++i)
	{
		if (nullptr != m_arrScene)
		{
			delete m_arrScene[i];
		}
	}
}

void SceneManager::Initialize(HWND _hWnd)
{
	/// 일단 여기서 초기화..
	m_hWnd = _hWnd;
	// Scene 생성
	m_arrScene[(UINT)SCENE_TYPE::START] = new SceneStart(m_hWnd);
	m_arrScene[(UINT)SCENE_TYPE::START]->SetSceneType(SCENE_TYPE::START);
	m_arrScene[(UINT)SCENE_TYPE::START]->SetName(L"Start Scene");

	m_arrScene[(UINT)SCENE_TYPE::TOOL] = new SceneTool(m_hWnd);
	m_arrScene[(UINT)SCENE_TYPE::TOOL]->SetSceneType(SCENE_TYPE::TOOL);
	m_arrScene[(UINT)SCENE_TYPE::TOOL]->SetName(L"Tool Scene");


	m_arrScene[(UINT)SCENE_TYPE::TITLE] = new SceneTitle(m_hWnd);
	m_arrScene[(UINT)SCENE_TYPE::TITLE]->SetSceneType(SCENE_TYPE::TITLE);
	m_arrScene[(UINT)SCENE_TYPE::TITLE]->SetName(L"Title Scene");


	m_arrScene[(UINT)SCENE_TYPE::SELECT] = new SceneSelect(m_hWnd);
	m_arrScene[(UINT)SCENE_TYPE::SELECT]->SetSceneType(SCENE_TYPE::SELECT);
	m_arrScene[(UINT)SCENE_TYPE::SELECT]->SetName(L"Select Scene");



	m_arrScene[(UINT)SCENE_TYPE::NARRATIVE_01] = new SceneNarrative01(m_hWnd);
	m_arrScene[(UINT)SCENE_TYPE::NARRATIVE_01]->SetSceneType(SCENE_TYPE::NARRATIVE_01);
	m_arrScene[(UINT)SCENE_TYPE::NARRATIVE_01]->SetName(L"Narrative01 Scene");

	m_arrScene[(UINT)SCENE_TYPE::NARRATIVE_02] = new SceneNarrative02(m_hWnd);
	m_arrScene[(UINT)SCENE_TYPE::NARRATIVE_02]->SetSceneType(SCENE_TYPE::NARRATIVE_02);
	m_arrScene[(UINT)SCENE_TYPE::NARRATIVE_02]->SetName(L"Narrative02 Scene");

	m_arrScene[(UINT)SCENE_TYPE::NARRATIVE_03] = new SceneNarrative03(m_hWnd);
	m_arrScene[(UINT)SCENE_TYPE::NARRATIVE_02]->SetSceneType(SCENE_TYPE::NARRATIVE_03);
	m_arrScene[(UINT)SCENE_TYPE::NARRATIVE_02]->SetName(L"Narrative03 Scene");



	m_arrScene[(UINT)SCENE_TYPE::STAGE_01] = new SceneStage01(m_hWnd);
	m_arrScene[(UINT)SCENE_TYPE::STAGE_01]->SetSceneType(SCENE_TYPE::STAGE_01);
	m_arrScene[(UINT)SCENE_TYPE::STAGE_01]->SetName(L"C1");


	m_arrScene[(UINT)SCENE_TYPE::STAGE_02] = new SceneStage02(m_hWnd);
	m_arrScene[(UINT)SCENE_TYPE::STAGE_02]->SetSceneType(SCENE_TYPE::STAGE_02);
	m_arrScene[(UINT)SCENE_TYPE::STAGE_02]->SetName(L"C2");


	m_arrScene[(UINT)SCENE_TYPE::STAGE_03] = new SceneStage03(m_hWnd);
	m_arrScene[(UINT)SCENE_TYPE::STAGE_03]->SetSceneType(SCENE_TYPE::STAGE_03);
	m_arrScene[(UINT)SCENE_TYPE::STAGE_03]->SetName(L"C3");


	m_arrScene[(UINT)SCENE_TYPE::STAGE_04] = new SceneStage04(m_hWnd);
	m_arrScene[(UINT)SCENE_TYPE::STAGE_04]->SetSceneType(SCENE_TYPE::STAGE_04);
	m_arrScene[(UINT)SCENE_TYPE::STAGE_04]->SetName(L"C4");




	// 현재 씬 지정
	m_pCurScene = m_arrScene[(UINT)SCENE_TYPE::TITLE];
	m_pCurScene->Enter();

}

void SceneManager::Update()
{
	m_pCurScene->Update();

	m_pCurScene->FinalUpdate();
}

void SceneManager::Render(HDC _dc)
{
	m_pCurScene->Render(_dc);
}

void SceneManager::ChangeScene(SCENE_TYPE _eNext)
{
	Camera::GetInst()->FadeOut(0.3f);
	
	Vector2 camOffset = Camera::GetInst()->GetCurLookAt();
	camOffset -= m_pCurScene->GetResolution() / 2.f;
	const vector<GameObject*>& vecObj = m_pCurScene->GetGroupObject(GROUP_TYPE::BACKGROUND);
	wstring key = m_pCurScene->SetObject(GROUP_TYPE::BACKGROUND, (UINT)(vecObj.size()-1))->GetTex()->GetKey();
	wstring path = m_pCurScene->SetObject(GROUP_TYPE::BACKGROUND, (UINT)(vecObj.size()-1))->GetTex()->GetRealtivePath();

	m_pCurScene->Exit();

	m_pCurScene = m_arrScene[(UINT)_eNext];
	
	Background* prevBg = new Background(false, m_pCurScene);

	prevBg->SetName(L"PrevBG");
	prevBg->SetTex(ResourceManager::GetInst()->LoadTexture(key,  path));
	prevBg->SetPos(Vector2(-camOffset.x, -camOffset.y));
	prevBg->SetScale(prevBg->GetBgScale());

	m_pCurScene->AddObject(prevBg, GROUP_TYPE::PREVBACKGROUND);

	m_pCurScene->Enter();


	Camera::GetInst()->FadeIn(0.3f);
}
