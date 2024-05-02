#include "pch.h"
#include "SceneStart.h"
#include "ResourceManager.h"
#include "ParseManager.h"
#include "Background.h"


#include "SignPost.h"
#include "Collider.h"
#include "Camera.h"
#include "SignPostPopUp.h"
#include "SoundManager.h"

#include "Player.h"

SceneStart::SceneStart(HWND _hWnd)
	: SceneStage(_hWnd)
{

}

SceneStart::~SceneStart()
{

}


void SceneStart::Enter()
{
	Vector2 vResolution = GetResolution();
	/// 1. 파싱 소스 결정
	SetScvData(ParseCSV(L"csvData\\tabletest1.csv"));
	//vector<vector<wstring>> csvData = ParseCSV(L"content/csvData/tabletest1.csv");

	/// 2. 배경 한번에 넣기 
	ResourceManager::GetInst()->LoadTexture(L"C1_background_full_green", L"texture\\bg\\C1_background_full_green.bmp");
	ResourceManager::GetInst()->LoadTexture(L"C1_background_full_red", L"texture\\bg\\C1_background_full_red.bmp");
	ResourceManager::GetInst()->LoadTexture(L"C1_background_full_green", L"texture\\bg\\C1_background_full_green.bmp");
	ResourceManager::GetInst()->LoadTexture(L"C1_background_full_blue", L"texture\\bg\\C1_background_full_blue.bmp");
	ResourceManager::GetInst()->LoadTexture(L"C1_background_full_black", L"texture\\bg\\C1_background_full_black.bmp");

	/// 3. 거기서 배경 하드코딩으로 하나 넣어주기 
	Background* pTitleBG = new Background(true, this);
	pTitleBG->SetTex(ResourceManager::GetInst()->LoadTexture(L"C1_background_full_black", L"texture\\bg\\C1_background_full_black.bmp"));
	pTitleBG->SetPos(Vector2(0.f, -1080.f));
	pTitleBG->SetScale(pTitleBG->GetBgScale());
	AddObject(pTitleBG, GROUP_TYPE::BACKGROUND);


	/// 4. 부모클래스 엔터 호출하기
	SceneStage::Enter();


	/// 5. 팻말 배치
	//SignPost* pPostObj = nullptr;
	//pPostObj = new SignPost(this);
	//pPostObj->SetName(L"SignPost");
	//pPostObj->SetTex(ResourceManager::GetInst()->LoadTexture(L"signPost", L"texture\\signpost\\obj_sign.bmp"));
	//pPostObj->SetTexScale();
	//pPostObj->SetPos(Vector2(vResolution.x / 2 + 500, (float)200));
	//pPostObj->GetCollider()->SetScale(pPostObj->GetScale());

	//AddObject(pPostObj, GROUP_TYPE::SINGPOST);


	/// 6.팻말 팝업 메시지 오브젝트 생성
	SignPostPopUp* pPopObj = nullptr;
	pPopObj = new SignPostPopUp(this);
	pPopObj->SetName(L"PostPopUp");
	pPopObj->SetTex(ResourceManager::GetInst()->LoadTexture(L"popUp", L"texture\\signpost\\popup\\popup_temp.bmp"));
	pPopObj->SetTexScale();
	pPopObj->SetPos(Vector2(vResolution.x / 2, vResolution.y / 2));

	AddObject(pPopObj, GROUP_TYPE::POSTPOPUP);

	/// /////////////////////////////////////////////
	/// 7. 충돌체크는 위에서 됐지만 더 할거 정하기
	/// /////////////////////////////////////////////



	//Scene::Start();
	/// 8. 카메라 보이는 좌표 조절하기
	Vector2 vReslolution = GetResolution();

	Camera::GetInst()->SetLookAt(vReslolution / 2.f);

	//Camera::GetInst()->SetTarget(pPlayerObj);
	/// 9. BGM 재생
	/*if (SoundManager::GetInst()->m_isPaused == true)
		SoundManager::GetInst()->PauseBGM();*/
	SoundManager::GetInst()->PlayBGM(BGM_01);
	//Camera::GetInst()->FadeOut(5.f);

}

void SceneStart::Exit()
{
	SceneStage::Exit();
}

