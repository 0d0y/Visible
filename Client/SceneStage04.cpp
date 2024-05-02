#include "pch.h"
#include "SceneStage04.h"
#include "ResourceManager.h"
#include "ParseManager.h"
#include "Background.h"


#include "SignPost.h"
#include "Collider.h"
#include "Camera.h"
#include "SignPostPopUp.h"
#include "SoundManager.h"

#include "Player.h"

SceneStage04::SceneStage04(HWND _hWnd)
	: SceneStage(_hWnd)
{

}

SceneStage04::~SceneStage04()
{

}


void SceneStage04::Enter()
{
	Vector2 vResolution = GetResolution();
	/// 1. 파싱 소스 결정
	SetScvData(ParseCSV(L"csvData\\level4test.csv"));

	/// 2. 배경 한번에 넣기 
	ResourceManager::GetInst()->LoadTexture(L"C4_background_full_green", L"texture\\bg\\C4_background_full_green.bmp");
	ResourceManager::GetInst()->LoadTexture(L"C4_background_full_red", L"texture\\bg\\C4_background_full_red.bmp");
	ResourceManager::GetInst()->LoadTexture(L"C4_background_full_green", L"texture\\bg\\C4_background_full_green.bmp");
	ResourceManager::GetInst()->LoadTexture(L"C4_background_full_blue", L"texture\\bg\\C4_background_full_blue.bmp");
	ResourceManager::GetInst()->LoadTexture(L"C4_background_full_black", L"texture\\bg\\C4_background_full_black.bmp");

	/// 3. 거기서 배경 하드코딩으로 하나 넣어주기 
	Background* pTitleBG = new Background(true, this);
	pTitleBG->SetTex(ResourceManager::GetInst()->LoadTexture(L"C4_background_full_black", L"texture\\bg\\C4_background_full_black.bmp"));
	pTitleBG->SetPos(Vector2(0.f, 0.f));
	pTitleBG->SetScale(pTitleBG->GetBgScale());
	AddObject(pTitleBG, GROUP_TYPE::BACKGROUND);

	/// 4. 카메라 보이는 좌표 조절하기
	Vector2 vReslolution = GetResolution();

	Camera::GetInst()->SetCurLookAt(vReslolution / 2.f);

	/// 5. 부모클래스 엔터 호출하기
	SceneStage::Enter();

	((Player*)GetPlayer())->SetWearGlasses(COLOR_TYPE::BLACK);

	/// 6. 팻말 배치
	SignPost* pPostObj = nullptr;

	pPostObj = new SignPost(this);
	pPostObj->SetName(L"SignPost6");
	pPostObj->SetTex(ResourceManager::GetInst()->LoadTexture(L"signPost6", L"texture\\signpost\\obj_sign.bmp"));
	pPostObj->SetTexScale();
	pPostObj->SetPos(Vector2(960.f, 840.f));
	pPostObj->GetCollider()->SetScale(Vector2(300.f, 400.f));

	AddObject(pPostObj, GROUP_TYPE::SINGPOST);

	pPostObj = new SignPost(this);
	pPostObj->SetName(L"SignPost7");
	pPostObj->SetTex(ResourceManager::GetInst()->LoadTexture(L"signPost7", L"texture\\signpost\\obj_sign.bmp"));
	pPostObj->SetTexScale();
	pPostObj->SetPos(Vector2(960.f, 1920.f));
	pPostObj->GetCollider()->SetScale(Vector2(300.f, 400.f));

	AddObject(pPostObj, GROUP_TYPE::SINGPOST);

	pPostObj = new SignPost(this);
	pPostObj->SetName(L"SignPost8");
	pPostObj->SetTex(ResourceManager::GetInst()->LoadTexture(L"signPost8", L"texture\\signpost\\obj_sign.bmp"));
	pPostObj->SetTexScale();
	pPostObj->SetPos(Vector2(960.f, 3000.f));
	pPostObj->GetCollider()->SetScale(Vector2(300.f, 400.f));

	AddObject(pPostObj, GROUP_TYPE::SINGPOST);

	pPostObj = new SignPost(this);
	pPostObj->SetName(L"SignPost9");
	pPostObj->SetTex(ResourceManager::GetInst()->LoadTexture(L"signPost9", L"texture\\signpost\\obj_sign.bmp"));
	pPostObj->SetTexScale();
	pPostObj->SetPos(Vector2(960.f, 4080.f));
	pPostObj->GetCollider()->SetScale(Vector2(300.f, 400.f));

	AddObject(pPostObj, GROUP_TYPE::SINGPOST);

	pPostObj = new SignPost(this);
	pPostObj->SetName(L"SignPost10");
	pPostObj->SetTex(ResourceManager::GetInst()->LoadTexture(L"signPost10", L"texture\\signpost\\obj_sign.bmp"));
	pPostObj->SetTexScale();
	pPostObj->SetPos(Vector2(960.f, 5110.f));
	pPostObj->GetCollider()->SetScale(Vector2(300.f, 400.f));

	AddObject(pPostObj, GROUP_TYPE::SINGPOST);




	/// 7.팻말 팝업 메시지 오브젝트 생성
	SignPostPopUp* pPopObj = nullptr;
	pPopObj = new SignPostPopUp(this);
	pPopObj->SetName(L"PostPopUp6");
	pPopObj->SetTex(ResourceManager::GetInst()->LoadTexture(L"popUp6", L"texture\\signpost\\popup\\credit_popup_06.bmp"));
	pPopObj->SetTexScale();
	pPopObj->SetPos(Vector2(vResolution.x / 2, vResolution.y / 2));

	AddObject(pPopObj, GROUP_TYPE::POSTPOPUP);

	pPopObj = new SignPostPopUp(this);
	pPopObj->SetName(L"PostPopUp7");
	pPopObj->SetTex(ResourceManager::GetInst()->LoadTexture(L"popUp7", L"texture\\signpost\\popup\\credit_popup_07.bmp"));
	pPopObj->SetTexScale();
	pPopObj->SetPos(Vector2(vResolution.x / 2, vResolution.y / 2));

	AddObject(pPopObj, GROUP_TYPE::POSTPOPUP);

	pPopObj = new SignPostPopUp(this);
	pPopObj->SetName(L"PostPopUp8");
	pPopObj->SetTex(ResourceManager::GetInst()->LoadTexture(L"popUp8", L"texture\\signpost\\popup\\credit_popup_08.bmp"));
	pPopObj->SetTexScale();
	pPopObj->SetPos(Vector2(vResolution.x / 2, vResolution.y / 2));

	AddObject(pPopObj, GROUP_TYPE::POSTPOPUP);

	pPopObj = new SignPostPopUp(this);
	pPopObj->SetName(L"PostPopUp9");
	pPopObj->SetTex(ResourceManager::GetInst()->LoadTexture(L"popUp9", L"texture\\signpost\\popup\\credit_popup_09.bmp"));
	pPopObj->SetTexScale();
	pPopObj->SetPos(Vector2(vResolution.x / 2, vResolution.y / 2));

	AddObject(pPopObj, GROUP_TYPE::POSTPOPUP);

	pPopObj = new SignPostPopUp(this);
	pPopObj->SetName(L"PostPopUp10");
	pPopObj->SetTex(ResourceManager::GetInst()->LoadTexture(L"popUp10", L"texture\\signpost\\popup\\credit_popup_10.bmp"));
	pPopObj->SetTexScale();
	pPopObj->SetPos(Vector2(vResolution.x / 2, vResolution.y / 2));

	AddObject(pPopObj, GROUP_TYPE::POSTPOPUP);





	/// /////////////////////////////////////////////
	/// 8. 충돌체크는 위에서 됐지만 더 할거있으면 정하기
	/// /////////////////////////////////////////////



	//Scene::Start();

	//Camera::GetInst()->SetTarget(pPlayerObj);
	/// 9. BGM 재생
	/*if (SoundManager::GetInst()->m_isPaused == true)
		SoundManager::GetInst()->PauseBGM();*/
	SoundManager::GetInst()->PlayBGM(BGM_01);
	//Camera::GetInst()->FadeOut(5.f);

}

void SceneStage04::Exit()
{
	SceneStage::Exit();
}



