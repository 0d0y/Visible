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
	/// 1. �Ľ� �ҽ� ����
	SetScvData(ParseCSV(L"csvData\\tabletest1.csv"));
	//vector<vector<wstring>> csvData = ParseCSV(L"content/csvData/tabletest1.csv");

	/// 2. ��� �ѹ��� �ֱ� 
	ResourceManager::GetInst()->LoadTexture(L"C1_background_full_green", L"texture\\bg\\C1_background_full_green.bmp");
	ResourceManager::GetInst()->LoadTexture(L"C1_background_full_red", L"texture\\bg\\C1_background_full_red.bmp");
	ResourceManager::GetInst()->LoadTexture(L"C1_background_full_green", L"texture\\bg\\C1_background_full_green.bmp");
	ResourceManager::GetInst()->LoadTexture(L"C1_background_full_blue", L"texture\\bg\\C1_background_full_blue.bmp");
	ResourceManager::GetInst()->LoadTexture(L"C1_background_full_black", L"texture\\bg\\C1_background_full_black.bmp");

	/// 3. �ű⼭ ��� �ϵ��ڵ����� �ϳ� �־��ֱ� 
	Background* pTitleBG = new Background(true, this);
	pTitleBG->SetTex(ResourceManager::GetInst()->LoadTexture(L"C1_background_full_black", L"texture\\bg\\C1_background_full_black.bmp"));
	pTitleBG->SetPos(Vector2(0.f, -1080.f));
	pTitleBG->SetScale(pTitleBG->GetBgScale());
	AddObject(pTitleBG, GROUP_TYPE::BACKGROUND);


	/// 4. �θ�Ŭ���� ���� ȣ���ϱ�
	SceneStage::Enter();


	/// 5. �ָ� ��ġ
	//SignPost* pPostObj = nullptr;
	//pPostObj = new SignPost(this);
	//pPostObj->SetName(L"SignPost");
	//pPostObj->SetTex(ResourceManager::GetInst()->LoadTexture(L"signPost", L"texture\\signpost\\obj_sign.bmp"));
	//pPostObj->SetTexScale();
	//pPostObj->SetPos(Vector2(vResolution.x / 2 + 500, (float)200));
	//pPostObj->GetCollider()->SetScale(pPostObj->GetScale());

	//AddObject(pPostObj, GROUP_TYPE::SINGPOST);


	/// 6.�ָ� �˾� �޽��� ������Ʈ ����
	SignPostPopUp* pPopObj = nullptr;
	pPopObj = new SignPostPopUp(this);
	pPopObj->SetName(L"PostPopUp");
	pPopObj->SetTex(ResourceManager::GetInst()->LoadTexture(L"popUp", L"texture\\signpost\\popup\\popup_temp.bmp"));
	pPopObj->SetTexScale();
	pPopObj->SetPos(Vector2(vResolution.x / 2, vResolution.y / 2));

	AddObject(pPopObj, GROUP_TYPE::POSTPOPUP);

	/// /////////////////////////////////////////////
	/// 7. �浹üũ�� ������ ������ �� �Ұ� ���ϱ�
	/// /////////////////////////////////////////////



	//Scene::Start();
	/// 8. ī�޶� ���̴� ��ǥ �����ϱ�
	Vector2 vReslolution = GetResolution();

	Camera::GetInst()->SetLookAt(vReslolution / 2.f);

	//Camera::GetInst()->SetTarget(pPlayerObj);
	/// 9. BGM ���
	/*if (SoundManager::GetInst()->m_isPaused == true)
		SoundManager::GetInst()->PauseBGM();*/
	SoundManager::GetInst()->PlayBGM(BGM_01);
	//Camera::GetInst()->FadeOut(5.f);

}

void SceneStart::Exit()
{
	SceneStage::Exit();
}

