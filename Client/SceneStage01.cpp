#include "pch.h"
#include "SceneStage01.h"
#include "ResourceManager.h"
#include "ParseManager.h"
#include "Background.h"


#include "SignPost.h"
#include "Collider.h"
#include "Camera.h"
#include "SignPostPopUp.h"
#include "SoundManager.h"

#include "Player.h"

SceneStage01::SceneStage01(HWND _hWnd)
	: SceneStage(_hWnd)
{

}


SceneStage01::~SceneStage01()
{

}


void SceneStage01::Enter()
{
	
	Vector2 vResolution = GetResolution();
	/// 1. 파싱 소스 결정
	SetScvData(ParseCSV(L"csvData\\level1test.csv"));

	/// 2. 배경 한번에 넣기 
	ResourceManager::GetInst()->LoadTexture(L"C1_background_full_green", L"texture\\bg\\C1_background_full_green.bmp");
	ResourceManager::GetInst()->LoadTexture(L"C1_background_full_red", L"texture\\bg\\C1_background_full_red.bmp");
	ResourceManager::GetInst()->LoadTexture(L"C1_background_full_green", L"texture\\bg\\C1_background_full_green.bmp");
	ResourceManager::GetInst()->LoadTexture(L"C1_background_full_blue", L"texture\\bg\\C1_background_full_blue.bmp");
	ResourceManager::GetInst()->LoadTexture(L"C1_background_full_black", L"texture\\bg\\C1_background_full_black.bmp");

	/// 3. 거기서 배경 하드코딩으로 하나 넣어주기 
	Background* pTitleBG = new Background(true, this);
	pTitleBG->SetTex(ResourceManager::GetInst()->LoadTexture(L"C1_background_full_green", L"texture\\bg\\C1_background_full_green.bmp"));
	pTitleBG->SetPos(Vector2(0.f, 0.f));
	pTitleBG->SetScale(pTitleBG->GetBgScale());
	AddObject(pTitleBG, GROUP_TYPE::BACKGROUND);


	/// 4. 카메라 보이는 좌표 조절하기!!(배경 위치 계산해서 밑으로 내려준다..?)
	Vector2 vReslolution = GetResolution();

	Camera::GetInst()->SetCurLookAt(vReslolution / 2.f - Vector2(0.f, -1080.f));;



	/// 5. 부모클래스 엔터 호출하기
	SceneStage::Enter();

	((Player*)GetPlayer())->SetWearGlasses(COLOR_TYPE::GREEN);


	 //6. 팻말 배치
	SignPost* pPostObj = nullptr;
	pPostObj = new SignPost(this);
	pPostObj->SetName(L"SignPost1");
	pPostObj->SetTex(ResourceManager::GetInst()->LoadTexture(L"signPost1", L"texture\\signpost\\obj_sign.bmp"));
	pPostObj->SetTexScale();
	pPostObj->SetPos(Vector2(537.f, 1929.f));
	pPostObj->GetCollider()->SetScale(Vector2(150.f, 200.f));
	
	AddObject(pPostObj, GROUP_TYPE::SINGPOST);


	/// 7.팻말 팝업 메시지 오브젝트 생성
	SignPostPopUp* pPopObj = nullptr;
	pPopObj = new SignPostPopUp(this);
	pPopObj->SetName(L"PostPopUp1");
	pPopObj->SetTex(ResourceManager::GetInst()->LoadTexture(L"popUp1", L"texture\\signpost\\popup\\Information_popup_01.bmp"));
	pPopObj->SetTexScale();
	pPopObj->SetPos(Vector2(vResolution.x / 2, vResolution.y / 2));
	
	AddObject(pPopObj, GROUP_TYPE::POSTPOPUP);

	
	/// /////////////////////////////////////////////
	/// 8. 충돌체크는 위에서 됐지만 더 할거 정하기
	/// /////////////////////////////////////////////


	//Scene::Start();

	//Camera::GetInst()->SetTarget(pPlayerObj);
	/// 9. BGM 재생
	/*if (SoundManager::GetInst()->m_isPaused == true)
		SoundManager::GetInst()->PauseBGM();*/
	SoundManager::GetInst()->PlayBGM(BGM_01);
	//Camera::GetInst()->FadeOut(5.f);

}

void SceneStage01::Exit()
{
	SceneStage::Exit();
}

