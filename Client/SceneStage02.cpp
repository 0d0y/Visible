#include "pch.h"
#include "SceneStage02.h"
#include "ResourceManager.h"
#include "ParseManager.h"
#include "Background.h"


#include "SignPost.h"
#include "Collider.h"
#include "Camera.h"
#include "SignPostPopUp.h"
#include "SoundManager.h"

#include "Player.h"

SceneStage02::SceneStage02(HWND _hWnd)
	: SceneStage(_hWnd)
{

}

SceneStage02::~SceneStage02()
{

}


void SceneStage02::Enter()
{
	Vector2 vResolution = GetResolution();
	/// 1. �Ľ� �ҽ� ����
	SetScvData(ParseCSV(L"csvData\\level2test.csv"));

	/// 2. ��� �ѹ��� �ֱ� 
	ResourceManager::GetInst()->LoadTexture(L"C2_background_full_green", L"texture\\bg\\C2_background_full_green.bmp");
	ResourceManager::GetInst()->LoadTexture(L"C2_background_full_red", L"texture\\bg\\C2_background_full_red.bmp");
	ResourceManager::GetInst()->LoadTexture(L"C2_background_full_green", L"texture\\bg\\C2_background_full_green.bmp");
	ResourceManager::GetInst()->LoadTexture(L"C2_background_full_blue", L"texture\\bg\\C2_background_full_blue.bmp");
	ResourceManager::GetInst()->LoadTexture(L"C2_background_full_black", L"texture\\bg\\C2_background_full_black.bmp");

	/// 3. �ű⼭ ��� �ϵ��ڵ����� �ϳ� �־��ֱ� 
	Background* pTitleBG = new Background(true, this);
	pTitleBG->SetTex(ResourceManager::GetInst()->LoadTexture(L"C2_background_full_blue", L"texture\\bg\\C2_background_full_blue.bmp"));
	pTitleBG->SetPos(Vector2(0.f, 0.f));
	pTitleBG->SetScale(pTitleBG->GetBgScale());
	AddObject(pTitleBG, GROUP_TYPE::BACKGROUND);

	/// 4. ī�޶� ���̴� ��ǥ �����ϱ�!!(��� ��ġ ����ؼ� ������ �����ش�..?)
	Vector2 vReslolution = GetResolution();

	Camera::GetInst()->SetCurLookAt(vReslolution / 2.f - Vector2(0.f, -1080.f * 4.f));

	/// 5. �θ�Ŭ���� ���� ȣ���ϱ�
	SceneStage::Enter();

	((Player*)GetPlayer())->SetWearGlasses(COLOR_TYPE::BLUE);

	//6. �ָ� ��ġ
	SignPost* pPostObj = nullptr;
	pPostObj = new SignPost(this);
	pPostObj->SetName(L"SignPost2");
	pPostObj->SetTex(ResourceManager::GetInst()->LoadTexture(L"signPost2", L"texture\\signpost\\obj_sign.bmp"));
	pPostObj->SetTexScale();
	pPostObj->SetPos(Vector2(544.f, 5169.f));
	pPostObj->GetCollider()->SetScale(Vector2(150.f, 200.f));

	AddObject(pPostObj, GROUP_TYPE::SINGPOST);

	pPostObj = new SignPost(this);
	pPostObj->SetName(L"SignPost3");
	pPostObj->SetTex(ResourceManager::GetInst()->LoadTexture(L"signPost3", L"texture\\signpost\\obj_sign.bmp"));
	pPostObj->SetTexScale();
	pPostObj->SetPos(Vector2(4116.f, 5169.f));
	pPostObj->GetCollider()->SetScale(Vector2(150.f, 200.f));

	AddObject(pPostObj, GROUP_TYPE::SINGPOST);



	/// 7.�ָ� �˾� �޽��� ������Ʈ ����
	SignPostPopUp* pPopObj = nullptr;
	pPopObj = new SignPostPopUp(this);
	pPopObj->SetName(L"PostPopUp2");
	pPopObj->SetTex(ResourceManager::GetInst()->LoadTexture(L"popUp2", L"texture\\signpost\\popup\\Information_popup_02.bmp"));
	pPopObj->SetTexScale();
	pPopObj->SetPos(Vector2(vResolution.x / 2, vResolution.y / 2));

	AddObject(pPopObj, GROUP_TYPE::POSTPOPUP);

	pPopObj = new SignPostPopUp(this);
	pPopObj->SetName(L"PostPopUp3");
	pPopObj->SetTex(ResourceManager::GetInst()->LoadTexture(L"popUp3", L"texture\\signpost\\popup\\Information_popup_03.bmp"));
	pPopObj->SetTexScale();
	pPopObj->SetPos(Vector2(vResolution.x / 2, vResolution.y / 2));

	AddObject(pPopObj, GROUP_TYPE::POSTPOPUP);

	/// /////////////////////////////////////////////
	/// 8. �浹üũ�� ������ ������ �� �Ұ� ���ϱ�
	/// /////////////////////////////////////////////



	//Scene::Start();

	//Camera::GetInst()->SetTarget(pPlayerObj);
	/// 9. BGM ���
	/*if (SoundManager::GetInst()->m_isPaused == true)
		SoundManager::GetInst()->PauseBGM();*/
	SoundManager::GetInst()->PlayBGM(BGM_02);
	//Camera::GetInst()->FadeOut(5.f);

}

void SceneStage02::Exit()
{
	SceneStage::Exit();
}
