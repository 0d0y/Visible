#include "pch.h"
#include "SceneStage.h"

#include "GameObject.h"
#include "Scene.h"
#include "Player.h"
#include "Terrain.h"
#include "Glasses.h"
#include "Drink.h"
#include "Thorn.h"
#include "SavePoint.h"
#include "ClearPoint.h"
#include "SignPost.h"
#include "SignPostPopUp.h"

#include "GameProcess.h"

#include "PathManager.h"
#include "Texture.h"

#include "Collider.h"
#include "CollisionManager.h"

#include "Animator.h"

#include "KeyManager.h"
#include "SceneManager.h"
#include "ParseManager.h"
#include "SoundManager.h"

#include "Fsm.h"
#include "IdleState.h"
#include "WalkState.h"
#include "JumpState.h"
#include "DeadState.h"
#include "ClearState.h"

#include "ImageUI.h"
#include "ButtonUI.h"
#include "ResourceManager.h"

#include "Boundary.h"
#include "Camera.h"

#include "Background.h"
#include "Scene.h"
#include "DimButtonUI.h"

void PauseGame(DWORD_PTR, DWORD_PTR);

void RestartGame(DWORD_PTR, DWORD_PTR);
void ResumeGame(DWORD_PTR, DWORD_PTR);
void ReturnToRobby(DWORD_PTR, DWORD_PTR);
void MinimizeGame(DWORD_PTR _pCurScene, DWORD_PTR);

SceneStage::SceneStage(HWND _hWnd)
	: Scene(_hWnd)
	, m_pNextSunglassUI(nullptr)
	, m_pCurrSunglassUI(nullptr)
{

}

SceneStage::~SceneStage()
{
}


void SceneStage::ReloadBoundary()
{
	const vector<GameObject*>& vecBound = this->GetGroupObject(GROUP_TYPE::BOUNDARY);
	for (int i = 0; i < vecBound.size(); ++i) {
		DeleteObject(vecBound[i]);
	}

	Boundary* pBoundary = new Boundary(Vector2(1, 0), GetPlayer()->GetCollider(), this);
	AddObject(pBoundary, GROUP_TYPE::BOUNDARY);
	pBoundary = new Boundary(Vector2(-1, 0), GetPlayer()->GetCollider(), this);
	AddObject(pBoundary, GROUP_TYPE::BOUNDARY);
	pBoundary = new Boundary(Vector2(0, 1), GetPlayer()->GetCollider(), this);
	AddObject(pBoundary, GROUP_TYPE::BOUNDARY);
	pBoundary = new Boundary(Vector2(0, -1), GetPlayer()->GetCollider(), this);
	AddObject(pBoundary, GROUP_TYPE::BOUNDARY);
}



void SceneStage::Update()
{

	if (IsPause())
	{
		if (KEY_TAP(KEY::ESC))
		{
			ResumeGame((DWORD_PTR)this, 0);
		}
	}
	else
	{
		if (KEY_TAP(KEY::ENTER))
		{
			Camera::GetInst()->FadeOut(2.f);
			Camera::GetInst()->FadeIn(2.f);
			//Camera::GetInst()->Dim();
		}

		if (KEY_TAP(KEY::ESC))
		{
			PauseGame((DWORD_PTR)this, 0);
		}

		const vector<Background*>& vecBackground = (const vector<Background*>&)GetGroupObject(GROUP_TYPE::BACKGROUND);


		UpdateStageUI(vecBackground[0]);



		const vector<Terrain*>& vecTerrain = (const vector<Terrain*>&)GetGroupObject(GROUP_TYPE::TERRAIN);
		const vector<Thorn*>& vecThorn = (const vector<Thorn*>&)GetGroupObject(GROUP_TYPE::THORN);
		const vector<ClearPoint*>& vecClearPoint = (const vector<ClearPoint*>&)GetGroupObject(GROUP_TYPE::CLEARPOINT);




		Player* pPlayer = (Player*)GetPlayer();

		for (int i = 0; i < vecTerrain.size(); ++i)
		{
			if (pPlayer->GetWearGlasses() == vecTerrain[i]->GetColorState())
			{
				vecTerrain[i]->SetbCanPaint(false);
			}
			else
			{
				vecTerrain[i]->SetbCanPaint(true);
			}
		}
		for (int i = 0; i < vecThorn.size(); ++i)
		{
			if (pPlayer->GetWearGlasses() == vecThorn[i]->GetColorState())
			{
				vecThorn[i]->SetbCanPaint(false);
			}
			else
			{
				vecThorn[i]->SetbCanPaint(true);
			}
		}
		for (int i = 0; i < vecClearPoint.size(); ++i)
		{
			if (pPlayer->GetWearGlasses() == vecClearPoint[i]->GetColorState())
			{
				vecClearPoint[i]->SetbCanPaint(false);
			}
			else
			{
				vecClearPoint[i]->SetbCanPaint(true);

			}
		}
		Scene::Update();
	}
}


void SceneStage::Enter()
{
	Vector2 vResolution = GetResolution();


	//플레이어 배치
	Player* pPlayerObj = new Player(this);
	pPlayerObj->SetName(L"Player");
	pPlayerObj->SetSpawnPos(pPlayerObj->GetSpawnPos() + Camera::GetInst()->GetFinalLookAt());
	pPlayerObj->SetPos(pPlayerObj->GetSpawnPos());
	pPlayerObj->SetScale(Vector2(100.0f, 100.0f));
	pPlayerObj->SetSpawnCameraPos(Camera::GetInst()->GetFinalLookAt());
	AddObject(pPlayerObj, GROUP_TYPE::PLAYER);


	RegisterPlayer(pPlayerObj);

	//땅 배치
	Terrain* pTerrainObj = nullptr;
	Vector2 vTerrianScale;
	for (size_t i = 1; i < 151; i++)
	{
		pTerrainObj = new Terrain(this);

		pTerrainObj->SetName(m_csvData[i][0]);
		if (m_csvData[i][0] == L"")
			break;

		wstring str = L"texture\\";
		str += m_csvData[i][0] + L"\\" + m_csvData[i][2] + L"\\" + m_csvData[i][3];

		pTerrainObj->SetTex(ResourceManager::GetInst()->LoadTexture(str.c_str(), str.c_str()));
		pTerrainObj->SetTexScale();
		if (m_csvData[i][7] == L"TRUE")
			pTerrainObj->GetCollider()->SetScale(pTerrainObj->GetScale());
		else
		{
			pTerrainObj->GetCollider()->SetScale(Vector2(stof(m_csvData[i][8]), stof(m_csvData[i][9])));
		}
		pTerrainObj->GetCollider()->SetOffsetPos(Vector2(0.0f, stof(m_csvData[i][10])));
		pTerrainObj->SetPos(Vector2(stof(m_csvData[i][5]), stof(m_csvData[i][6])));

		pTerrainObj->SetColorState(StringToColorType(m_csvData[i][2]));

		AddObject(pTerrainObj, GROUP_TYPE::TERRAIN);
	}

	// 	pTerrainObj = new Terrain(this);
	// 	pTerrainObj->SetName(L"Terrain");
	// 	pTerrainObj->SetScale(Vector2(1980.f, 196.f));
	// 	pTerrainObj->SetPos(Vector2(960.f, 1080.f));
	// 	pTerrainObj->SetColorState(COLOR_TYPE::BLUE);
	// 	AddObject(pTerrainObj, GROUP_TYPE::TERRAIN);
		//썬글라스 배치
	Glasses* pGlassesObj = nullptr;
	Vector2 vGlassesScale = { 50, 50 };
	for (size_t i = 151; i < 161; i++)
	{
		pGlassesObj = new Glasses(this);

		pGlassesObj->SetName(m_csvData[i][0]);
		if (m_csvData[i][0] == L"")
			break;


		wstring str = L"texture\\";
		str += m_csvData[i][0] + L"\\" + m_csvData[i][3];

		pGlassesObj->SetTex(ResourceManager::GetInst()->LoadTexture(str.c_str(), str.c_str()));
		pGlassesObj->SetTexScale();

		if (m_csvData[i][7] == L"TRUE")
		{
			pGlassesObj->GetCollider()->SetScale(pGlassesObj->GetScale());
		}
		else
		{
			pGlassesObj->GetCollider()->SetScale(Vector2(stof(m_csvData[i][8]), stof(m_csvData[i][9])));
		}
		pGlassesObj->GetCollider()->SetOffsetPos(Vector2(0.0f, stof(m_csvData[i][10])));
		pGlassesObj->SetPos(Vector2(stof(m_csvData[i][5]), stof(m_csvData[i][6])));

		pGlassesObj->SetColorState(StringToColorType(m_csvData[i][2]));

		AddObject(pGlassesObj, GROUP_TYPE::GLASSES);
	}

	//술과 약 배치
	Drink* pDrinkObj = nullptr;
	for (size_t i = 161; i < 181; i++)
	{
		pDrinkObj = new Drink(this);

		pDrinkObj->SetName(m_csvData[i][0]);
		if (m_csvData[i][0] == L"")
			break;

		wstring str = L"texture\\";
		str += m_csvData[i][0] + L"\\" + m_csvData[i][3];

		pDrinkObj->SetTex(ResourceManager::GetInst()->LoadTexture(str.c_str(), str.c_str()));
		pDrinkObj->SetTexScale();

		if (m_csvData[i][7] == L"TRUE")
		{
			pDrinkObj->GetCollider()->SetScale(pDrinkObj->GetScale());
		}
		else
		{
			pDrinkObj->GetCollider()->SetScale(Vector2(stof(m_csvData[i][8]), stof(m_csvData[i][9])));
		}
		pDrinkObj->GetCollider()->SetOffsetPos(Vector2(0.0f, stof(m_csvData[i][10])));
		pDrinkObj->SetPos(Vector2(stof(m_csvData[i][5]), stof(m_csvData[i][6])));

		pDrinkObj->SetColorState(StringToColorType(m_csvData[i][2]));

		AddObject(pDrinkObj, GROUP_TYPE::DRINK);
	}

	//가시 배치
	Thorn* pThornObj = nullptr;
	for (size_t i = 181; i < 211; i++)
	{
		pThornObj = new Thorn(this);

		pThornObj->SetName(m_csvData[i][0]);
		if (m_csvData[i][0] == L"")
			break;

		wstring str = L"texture\\";
		str += m_csvData[i][0] + L"\\" + m_csvData[i][3];

		pThornObj->SetTex(ResourceManager::GetInst()->LoadTexture(str.c_str(), str.c_str()));
		pThornObj->SetTexScale();

		if (m_csvData[i][7] == L"TRUE")
		{
			pThornObj->GetCollider()->SetScale(pThornObj->GetScale());
		}
		else
		{
			pThornObj->GetCollider()->SetScale(Vector2(stof(m_csvData[i][8]), stof(m_csvData[i][9])));
		}
		pThornObj->GetCollider()->SetOffsetPos(Vector2(0.0f, stof(m_csvData[i][10])));
		pThornObj->SetPos(Vector2(stof(m_csvData[i][5]), stof(m_csvData[i][6])));

		pThornObj->SetColorState(StringToColorType(m_csvData[i][2]));

		AddObject(pThornObj, GROUP_TYPE::THORN);
	}

	//세이브 포인트 배치
	SavePoint* pSaveObj = nullptr;
	for (size_t i = 211; i < 214; i++)
	{
		pSaveObj = new SavePoint(this);

		pSaveObj->SetName(m_csvData[i][0]);
		if (m_csvData[i][0] == L"")
			break;

		wstring str = L"texture\\";
		str += m_csvData[i][0] + L"\\" + m_csvData[i][3];

		//pSaveObj->SetTex(ResourceManager::GetInst()->LoadTexture(str.c_str(), str.c_str()));
		pSaveObj->SetTex(ResourceManager::GetInst()->LoadTexture(str.c_str(), L"texture\\savepoint\\savepoint_Sheet.bmp"));
		pSaveObj->GetAnimator()->CreateAnimation(L"savePoint", pSaveObj->GetTex(), Vector2(0.f, 0.f), Vector2(80.f, 70.f), Vector2(80.f, 0.f), 0.3f, 4);
		pSaveObj->GetAnimator()->Play(L"savePoint", true);
		pSaveObj->SetScale(Vector2(80.f, 70.f));

		if (m_csvData[i][7] == L"TRUE")
		{
			pSaveObj->GetCollider()->SetScale(pSaveObj->GetScale());
		}
		else
		{
			pSaveObj->GetCollider()->SetScale(Vector2(stof(m_csvData[i][8]), stof(m_csvData[i][9])));
		}
		pSaveObj->GetCollider()->SetOffsetPos(Vector2(0.0f, stof(m_csvData[i][10])));
		pSaveObj->SetPos(Vector2(stof(m_csvData[i][5]), stof(m_csvData[i][6])));

		AddObject(pSaveObj, GROUP_TYPE::SAVEPOINT);
	}

	//클리어 포인트 배치
	ClearPoint* pClearObj = nullptr;
	for (size_t i = 214; i < 215; i++)
	{
		pClearObj = new ClearPoint(this);

		pClearObj->SetName(m_csvData[i][0]);
		if (m_csvData[i][0] == L"")
			break;

		wstring str = L"texture\\";
		str += m_csvData[i][0] + L"\\" + m_csvData[i][3];

		pClearObj->SetTex(ResourceManager::GetInst()->LoadTexture(str.c_str(), str.c_str()));
		pClearObj->GetAnimator()->CreateAnimation(L"clearPoint", pClearObj->GetTex(), Vector2(0.f, 0.f), Vector2(78.f, 68.f), Vector2(78.f, 0.f), 0.1f, 4);
		pClearObj->GetAnimator()->Play(L"clearPoint", true);
		pClearObj->SetScale(Vector2(39.f, 34.f));

		if (m_csvData[i][7] == L"TRUE")
		{
			pClearObj->GetCollider()->SetScale(pClearObj->GetScale());
		}
		else
		{
			pClearObj->GetCollider()->SetScale(Vector2(stof(m_csvData[i][8]), stof(m_csvData[i][9])));
		}
		pClearObj->GetCollider()->SetOffsetPos(Vector2(0.0f, stof(m_csvData[i][10])));
		pClearObj->SetPos(Vector2(stof(m_csvData[i][5]), stof(m_csvData[i][6])));
		pClearObj->SetColorState(StringToColorType(m_csvData[i][2]));

		AddObject(pClearObj, GROUP_TYPE::CLEARPOINT);
	}

	////팻말 배치
	//SignPost* pPostObj = nullptr;
	//for (size_t i = 215; i < 220; i++)
	//{
	//	pPostObj = new SignPost(this);

	//	pPostObj->SetName(m_csvData[i][0]);
	//	if (m_csvData[i][0] == L"")
	//		break;

	//	wstring str = L"texture\\";
	//	str += m_csvData[i][0] + L"\\" + m_csvData[i][3];

	//	pPostObj->SetTex(ResourceManager::GetInst()->LoadTexture(str.c_str(), str.c_str()));
	//	pPostObj->SetTexScale();

	//	if (m_csvData[i][7] == L"TRUE")
	//	{
	//		pPostObj->GetCollider()->SetScale(pPostObj->GetScale());
	//	}
	//	else
	//	{
	//		pPostObj->GetCollider()->SetScale(Vector2(stof(m_csvData[i][8]), stof(m_csvData[i][9])));
	//	}
	//	pPostObj->GetCollider()->SetOffsetPos(Vector2(0.0f, stof(m_csvData[i][10])));
	//	pPostObj->SetPos(Vector2(stof(m_csvData[i][5]), stof(m_csvData[i][6])));
	//	pPostObj->GetCollider()->SetScale(pPostObj->GetScale());

	//	AddObject(pPostObj, GROUP_TYPE::SINGPOST);
	//}




	// 충돌 지정
	// Player 그룹과 Monster 그룹 간의 충돌체크
	CollisionManager::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::TERRAIN);
	CollisionManager::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::GLASSES);
	CollisionManager::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::DRINK);
	CollisionManager::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::THORN);
	CollisionManager::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::SINGPOST);
	CollisionManager::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::SAVEPOINT);
	CollisionManager::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::CLEARPOINT);
	CollisionManager::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::BOUNDARY);



	// 일시정지 버튼 UI생성
	ButtonUI* pBtnUI = new ButtonUI(false, this);
	pBtnUI->SetName(L"PauseBtn");
	pBtnUI->SetTex(ResourceManager::GetInst()->LoadTexture(L"PauseBtn", L"texture\\pause_button24.bmp"));
	pBtnUI->SetTexScale();
	pBtnUI->AlignHorizontalLeft();
	pBtnUI->AlignVerticalTop();
	pBtnUI->SetPos(pBtnUI->GetPos() + Vector2(45.f, 45.f));
	pBtnUI->SetClickedCallBack(PauseGame, (DWORD_PTR)this, 0);
	AddObject(pBtnUI, GROUP_TYPE::UI);


	// 지금 끼고 있는 선글라스 UI생성
	ImageUI* pImageUI = new ImageUI(false, this);
	pImageUI->SetName(L"Current Sunglass");
	pImageUI->SetTex(ResourceManager::GetInst()->LoadTexture(L"CurrSunglass", L"texture\\ui\\sunglass_frame_black_19019024.bmp"));
	pImageUI->SetTexScale();
	pImageUI->AlignHorizontalRight();
	pImageUI->AlignVerticalTop();
	pImageUI->SetPos(pImageUI->GetPos() + Vector2(-45.f, 25.f));

	m_pCurrSunglassUI = pImageUI;

	AddObject(pImageUI, GROUP_TYPE::UI);




	// 인벤토리 선글라스 UI생성
	Vector2 vGlassOffset = pImageUI->GetPos();

	pImageUI = new ImageUI(false, this);
	pImageUI->SetName(L"Next Sunglass");
	pImageUI->SetTex(ResourceManager::GetInst()->LoadTexture(L"NextSunglass", L"texture\\ui\\sunglass_frame_black_15015024.bmp"));
	pImageUI->SetTexScale();

	pImageUI->AlignVerticalTop();
	pImageUI->SetPos(Vector2(vGlassOffset.x - pImageUI->GetTex()->Width() - 20.f, pImageUI->GetPos().y + 45.f));
	/*	pImageUI->SetPos(pImageUI->GetPos() + Vec2(0, 500));*/


	m_pNextSunglassUI = pImageUI;

	AddObject(pImageUI, GROUP_TYPE::UI);


	ReloadBoundary();

	//Scene::Start();



}


void SceneStage::UpdateStageUI(Background* _background)
{
	Player* pPlayer = dynamic_cast<Player*>(GetPlayer());
	assert(pPlayer);

	wstring bgPath = GetName();

	switch (pPlayer->GetWearGlasses())
	{
	case COLOR_TYPE::RED:
		m_pCurrSunglassUI->SetTex(ResourceManager::GetInst()->LoadTexture(L"sunglass_frame_red_19019024", L"texture\\ui\\sunglass_frame_red_19019024.bmp"));
		_background->SetTex(ResourceManager::GetInst()->LoadTexture(bgPath + L"_background_full_red", L"texture\\bg\\" + bgPath + L"_background_full_red.bmp"));
		break;
	case COLOR_TYPE::GREEN:
		m_pCurrSunglassUI->SetTex(ResourceManager::GetInst()->LoadTexture(L"sunglass_frame_green_19019024", L"texture\\ui\\sunglass_frame_green_19019024.bmp"));
		_background->SetTex(ResourceManager::GetInst()->LoadTexture(bgPath + L"_background_full_green", L"texture\\bg\\" + bgPath + L"_background_full_green.bmp"));
		break;
	case COLOR_TYPE::BLUE:
		m_pCurrSunglassUI->SetTex(ResourceManager::GetInst()->LoadTexture(L"sunglass_frame_blue_19019024", L"texture\\ui\\sunglass_frame_blue_19019024.bmp"));
		_background->SetTex(ResourceManager::GetInst()->LoadTexture(bgPath + L"_background_full_blue", L"texture\\bg\\" + bgPath + L"_background_full_blue.bmp"));
		break;
	case COLOR_TYPE::WHITE:
		m_pCurrSunglassUI->SetTex(ResourceManager::GetInst()->LoadTexture(L"sunglass_frame_beige_19019024", L"texture\\ui\\sunglass_frame_black_19019024.bmp"));
		_background->SetTex(ResourceManager::GetInst()->LoadTexture(bgPath + L"_background_full_beige", L"texture\\bg\\" + bgPath + L"_background_full_blue.bmp"));
		break;
	case COLOR_TYPE::BLACK:
		m_pCurrSunglassUI->SetTex(ResourceManager::GetInst()->LoadTexture(L"sunglass_frame_black_19019024", L"texture\\ui\\sunglass_frame_black_19019024.bmp"));
		_background->SetTex(ResourceManager::GetInst()->LoadTexture(bgPath + L"_background_full_black", L"texture\\bg\\" + bgPath + L"_background_full_black.bmp"));
		break;
	default:
		break;
	}

	switch (pPlayer->GetHaveGlasses())
	{

	case COLOR_TYPE::RED:
		m_pNextSunglassUI->SetTex(ResourceManager::GetInst()->LoadTexture(L"sunglass_frame_red_15015024", L"texture\\ui\\sunglass_frame_red_15015024.bmp"));
		break;
	case COLOR_TYPE::GREEN:
		m_pNextSunglassUI->SetTex(ResourceManager::GetInst()->LoadTexture(L"sunglass_frame_green_15015024", L"texture\\ui\\sunglass_frame_green_15015024.bmp"));
		break;
	case COLOR_TYPE::BLUE:
		m_pNextSunglassUI->SetTex(ResourceManager::GetInst()->LoadTexture(L"sunglass_frame_blue_15015024", L"texture\\ui\\sunglass_frame_blue_15015024.bmp"));
		break;
	case COLOR_TYPE::WHITE:
		m_pNextSunglassUI->SetTex(ResourceManager::GetInst()->LoadTexture(L"sunglass_frame_beige_15015024", L"texture\\ui\\sunglass_frame_empty_15015024.bmp"));
		break;
	case COLOR_TYPE::BLACK:
		m_pNextSunglassUI->SetTex(ResourceManager::GetInst()->LoadTexture(L"sunglass_frame_black_15015024", L"texture\\ui\\sunglass_frame_black_15015024.bmp"));
		break;
	case COLOR_TYPE::EMPTY:
		m_pNextSunglassUI->SetTex(ResourceManager::GetInst()->LoadTexture(L"sunglass_frame_empty150150_24", L"texture\\ui\\sunglass_frame_empty_15015024.bmp"));
		break;

	}
}



void SceneStage::Exit()
{


	DeleteAll();

	TogglePause();
	CollisionManager::GetInst()->Reset();
	SoundManager::GetInst()->StopWALK();
	ResourceManager::GetInst()->ClearResource();

}

void SceneStage::FinalUpdate()
{
	vector<GameObject*> vecCUI = GetUIGroup();
	if (!IsPause())
	{

		Scene::FinalUpdate();
	}
	else
	{
		for (size_t j = 0; j < vecCUI.size(); ++j)
		{
			vecCUI[j]->FinalUpdate();
		}
	}
}






void PauseGame(DWORD_PTR _pCurScene, DWORD_PTR) {
	if (!((Scene*)_pCurScene)->IsPause())
	{
		DimButtonUI* dimUI = new DimButtonUI(false, (Scene*)_pCurScene);
		dimUI->SetName(L"veil");
		dimUI->SetScale(((Scene*)_pCurScene)->GetResolution());
		dimUI->SetPos(Vector2(0.f, 0.f));
		dimUI->SetClickedCallBack(ResumeGame, (DWORD_PTR)_pCurScene, 0);
		CreateObject(dimUI, GROUP_TYPE::UI);


		ImageUI* pImageUI = new ImageUI(false, (Scene*)_pCurScene);
		pImageUI->SetName(L"Pause Popup UI");
		pImageUI->SetTex(ResourceManager::GetInst()->LoadTexture(L"PausePopUp", L"texture\\pause_popup.bmp"));
		pImageUI->SetTexScale();
		pImageUI->AlignHorizontalCenter();
		pImageUI->AlignVerticalCenter();


		ButtonUI* pChildUI = new ButtonUI(false, (Scene*)_pCurScene);
		pChildUI->SetName(L"ResumeBtn");
		pImageUI->AddChild(pChildUI);

		pChildUI->SetClickedCallBack(ResumeGame, _pCurScene, 0);
		pChildUI->SetTex(ResourceManager::GetInst()->LoadTexture(L"ResumeBtn", L"texture\\pause_button_resume.bmp"));
		pChildUI->SetTexScale();
		pChildUI->AlignHorizontalCenter();
		pChildUI->AlignVerticalTop();
		pChildUI->SetPos(pChildUI->GetPos() + Vector2(0.f, 260.f));

		Vector2 childOffset = pChildUI->GetPos();
		Vector2 childScale = pChildUI->GetScale();

		pChildUI = new ButtonUI(false, (Scene*)_pCurScene);
		pChildUI->SetName(L"RestartBtn");
		pImageUI->AddChild(pChildUI);
		pChildUI->SetClickedCallBack(RestartGame, _pCurScene, 0);
		pChildUI->SetTex(ResourceManager::GetInst()->LoadTexture(L"RestartBtn", L"texture\\pause_button_restart.bmp"));
		pChildUI->SetTexScale();
		pChildUI->AlignHorizontalCenter();
		pChildUI->AlignVerticalTop();
		pChildUI->SetPos(pChildUI->GetPos() + Vector2(0.f, childScale.y + childOffset.y + 10.f));

		childOffset = pChildUI->GetPos();
		pChildUI = new ButtonUI(false, (Scene*)_pCurScene);
		pChildUI->SetName(L"RobbyBtn");
		pImageUI->AddChild(pChildUI);
		pChildUI->SetClickedCallBack(ReturnToRobby, 0, 0);
		pChildUI->SetTex(ResourceManager::GetInst()->LoadTexture(L"RobbyBtn", L"texture\\pause_button_lobby.bmp"));
		pChildUI->SetTexScale();
		pChildUI->AlignHorizontalCenter();
		pChildUI->AlignVerticalTop();
		pChildUI->SetPos(pChildUI->GetPos() + Vector2(0.f, childScale.y + childOffset.y + 10.f));




		pChildUI = new ButtonUI(false, (Scene*)_pCurScene);
		pChildUI->SetName(L"ExitBtn");
		pImageUI->AddChild(pChildUI);
		pChildUI->SetClickedCallBack(ResumeGame, (DWORD_PTR)_pCurScene, 0);
		pChildUI->SetScale(Vector2(28.f, 26.f));
		pChildUI->AlignHorizontalRight();
		pChildUI->AlignVerticalTop();
		pChildUI->SetPos(pChildUI->GetPos() + Vector2(-26.f, 8.f));


		pChildUI = new ButtonUI(false, (Scene*)_pCurScene);
		pChildUI->SetName(L"MinimizeBtn");
		pImageUI->AddChild(pChildUI);
		pChildUI->SetClickedCallBack(MinimizeGame, (DWORD_PTR)_pCurScene, 0);
		pChildUI->SetScale(Vector2(28.f, 26.f));
		pChildUI->AlignHorizontalRight();
		pChildUI->AlignVerticalTop();
		pChildUI->SetPos(pChildUI->GetPos() + Vector2(-68.f, 8.f));

		CreateObject(pImageUI, GROUP_TYPE::UI);
		((Scene*)_pCurScene)->TogglePause();
	}
}


void ResumeGame(DWORD_PTR _pCurScene, DWORD_PTR)
{
	vector<GameObject*> vecCUI = ((Scene*)_pCurScene)->GetUIGroup();


	vector<GameObject*>::iterator iter = vecCUI.begin();

	for (; iter != vecCUI.end(); ++iter)
	{
		if ((*iter)->GetName() == L"veil") {
			DeleteObject(*iter);
		}
		if ((*iter)->GetName() == L"Pause Popup UI")
		{
			DeleteObject(*iter);
		}
	}

	((Scene*)_pCurScene)->TogglePause();
}

void RestartGame(DWORD_PTR _pCurScene, DWORD_PTR)
{

	ChangeScene(((Scene*)_pCurScene)->GetSceneType());

}

void ReturnToRobby(DWORD_PTR, DWORD_PTR)
{
	ChangeScene(SCENE_TYPE::TITLE);
}

void MinimizeGame(DWORD_PTR _pCurScene, DWORD_PTR)
{
	ShowWindow(((Scene*)_pCurScene)->GetCurrendWindow(), SW_MINIMIZE);
}

