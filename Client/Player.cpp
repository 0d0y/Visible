#include "pch.h"
#include "Player.h"
#include "Terrain.h"
#include "Glasses.h"
#include "Drink.h"
#include "Thorn.h"
#include "SignPostPopUp.h"

#include "GameProcess.h"

#include "SceneManager.h"
#include "Scene.h"

#include "KeyManager.h"
#include "TimeManager.h"

#include "ResourceManager.h"
#include "Texture.h"
#include "SoundManager.h"

#include "Collider.h"
#include "Animator.h"
#include "RigidBody.h"
#include "Gravity.h"

#include "Animation.h"

#include "SelectGDI.h"

#include "Fsm.h"
#include "State.h"

#include "Camera.h"
#include "SceneStage.h"
#include "Arrow.h"

Player::Player(Scene* _ownerScene)
	: m_eWearglasses(COLOR_TYPE::BLACK)
	, m_eHaveglasses(COLOR_TYPE::EMPTY)
	, m_ePlayerColor(COLOR_TYPE::NONE)
	, m_ePrevPlayerColor(COLOR_TYPE::EMPTY)
	, m_eCurState(PLAYER_STATE::IDLE)
	, m_ePrevState(PLAYER_STATE::WALK)
	, m_iDir(1)
	, m_iPrevDir(1)
	, m_vSpawnPos(0, 0)
	, m_bClear(false)
	, m_bDead(false)
	, GameObject(_ownerScene)
	, m_reactionCount(0)
	, m_collisionHandledX(false)
	, m_collisionHandledY(false)
	, onImmortal(false)
	, m_spawnCameraPos{}
	, m_lastFrameRepeat(0)
	, inputKeyTrig(true)
	, m_prevPos{}
	, jumpTrig(false)
	, m_deadCheckToTexture(false)
	, infiJumpTrig(false)
{

	Texture* pTex = ResourceManager::GetInst()->LoadTexture(L"playerTex", L"texture\\player\\player.bmp");

	CreateCollider();
	GetCollider()->SetScale(Vector2(80.f, 60.0f));
	GetCollider()->SetOffsetPos(Vector2(0.0f, 36.0f));

	CreateRigidBody();
	CreateAnimator();
	CreateGravity();

	GetAnimator()->CreateAnimation(L"IDLE_RIGHT", pTex, Vector2(0.f, 0.f), Vector2(160.f, 150.f), Vector2(160.f, 0.f), 0.1f, 6);
	GetAnimator()->Play(L"IDLE_RIGHT", true);

	//CAnimation* pAnim = GetAnimator()->FindAnimation(L"IDLE");
	//for (int i = 0; i < pAnim->GetMaxFrame(); ++i)
	//	pAnim->GetFrame(i).vOffset = Vec2(0.f, -10.f);
}

Player::~Player()
{
	if (nullptr != GetFsm())
		delete GetFsm();
}

void Player::Update()
{

	if (KEY_TAP(KEY::ENTER)) {
		ChangeScene(SCENE_TYPE::SELECT);
	}

	update_move();

	update_interact();

	update_state();

	update_sound();

	update_texture();


	update_animation();

	m_collisionHandledX = false;
	m_collisionHandledY = false;

	if (m_deadCheckToTexture) {
		m_deadCheckToTexture = false;
	}
	else {
		m_ePrevPlayerColor = m_ePlayerColor;
	}
	m_ePrevState = m_eCurState;
	m_iPrevDir = m_iDir;
}

void Player::Render(HDC _dc)
{
	// 컴포넌트(충돌체, etc...) 가 있는 경우 랜더
	ComponentRender(_dc);

	SelectGDI::GetInst()->ReturnGDI(_dc);
}

void Player::update_texture()
{
	if (m_ePrevPlayerColor == m_ePlayerColor)
		return;
	GetAnimator()->DeleteAnim();
	Texture* pTex = ResourceManager::GetInst()->FindTexture(L"playerTex");
	int index = 0;
	if (m_ePlayerColor == COLOR_TYPE::NONE)
	{
		index = 0;
	}
	else
	{
		index = (int)m_ePlayerColor + 1;
	}

	GetAnimator()->CreateAnimation(L"IDLE_RIGHT", pTex, Vector2(0.f, ((index * 1500.f) + 0.f)), Vector2(160.f, 150.f), Vector2(160.f, 0.f), 0.1f, 6);
	GetAnimator()->CreateAnimation(L"WALK_RIGHT", pTex, Vector2(0.f, ((index * 1500.f) + 150.f)), Vector2(160.f, 150.f), Vector2(160.f, 0.f), 0.1f, 6);
	GetAnimator()->CreateAnimation(L"JUMP_RIGHT", pTex, Vector2(0.f, ((index * 1500.f) + 300.f)), Vector2(160.f, 150.f), Vector2(160.f, 0.f), 0.1f, 5);
	GetAnimator()->CreateAnimation(L"DEAD_RIGHT", pTex, Vector2(0.f, ((index * 1500.f) + 450.f)), Vector2(160.f, 150.f), Vector2(160.f, 0.f), 0.5f, 8);
	GetAnimator()->CreateAnimation(L"CLEAR_RIGHT", pTex, Vector2(0.f, ((index * 1500.f) + 600.f)), Vector2(160.f, 150.f), Vector2(160.f, 0.f), 0.2f, 8);
	GetAnimator()->CreateAnimation(L"IDLE_LEFT", pTex, Vector2(0.f, ((index * 1500.f) + 750.f)), Vector2(160.f, 150.f), Vector2(160.f, 0.f), 0.1f, 6);
	GetAnimator()->CreateAnimation(L"WALK_LEFT", pTex, Vector2(0.f, ((index * 1500.f) + 900.f)), Vector2(160.f, 150.f), Vector2(160.f, 0.f), 0.1f, 6);
	GetAnimator()->CreateAnimation(L"JUMP_LEFT", pTex, Vector2(0.f, ((index * 1500.f) + 1050.f)), Vector2(160.f, 150.f), Vector2(160.f, 0.f), 0.1f, 5);
	GetAnimator()->CreateAnimation(L"DEAD_LEFT", pTex, Vector2(0.f, ((index * 1500.f) + 1200.f)), Vector2(160.f, 150.f), Vector2(160.f, 0.f), 0.5f, 8);
	GetAnimator()->CreateAnimation(L"CLEAR_LEFT", pTex, Vector2(0.f, ((index * 1500.f) + 1350.f)), Vector2(160.f, 150.f), Vector2(160.f, 0.f), 0.2f, 8);
}

void Player::update_state()
{
	RigidBody* pRigid = GetRigidBody();
	Gravity* pGrav = GetGravity();

	if (m_eCurState != PLAYER_STATE::STUCK)
	{
		if (0.f < pRigid->GetVelocity().x)
		{
			m_iDir = 1;
			if (PLAYER_STATE::JUMP != m_eCurState)
				m_eCurState = PLAYER_STATE::WALK;
		}
		if (0.f > pRigid->GetVelocity().x)
		{
			m_iDir = -1;
			if (PLAYER_STATE::JUMP != m_eCurState)
				m_eCurState = PLAYER_STATE::WALK;
		}
		if (pRigid->GetVelocity().y < 0.f && !pGrav->GetGround()) //pGrav->GetGround() == false
		{
			m_eCurState = PLAYER_STATE::JUMP;
		}
		if (0.0001f >= pRigid->GetSpeed())
		{
			m_eCurState = PLAYER_STATE::IDLE;
		}
		if (m_bClear)
		{
			m_eCurState = PLAYER_STATE::CLEAR;
		}
		if (m_bDead)
		{
			m_eCurState = PLAYER_STATE::DEAD;
		}
	}
}



void Player::update_sound()
{
	switch (m_eCurState)
	{
	case PLAYER_STATE::IDLE:
	{
		g_checkJumping = false;
		SoundManager::GetInst()->m_isWalking = false;
		SoundManager::GetInst()->StopWALK();
	}
	break;
	case PLAYER_STATE::WALK:
	{
		g_checkJumping = false;
		SoundManager::GetInst()->PlayWALK();
	}
	break;
	case PLAYER_STATE::JUMP:
	{
		SoundManager::GetInst()->m_isWalking = false;
		SoundManager::GetInst()->StopWALK();
		if (!g_checkJumping)
		{
			g_checkJumping = true;
			SoundManager::GetInst()->PlaySFX(SFX_JUMP);
		}
	}
	break;
	case PLAYER_STATE::DEAD:
	{
		SoundManager::GetInst()->m_isWalking = false;
		SoundManager::GetInst()->StopWALK();
		if (!g_checkDeath)
		{
			SoundManager::GetInst()->PauseBGM();
			SoundManager::GetInst()->PlaySFX(SFX_DEATH);
			g_checkDeath = true;
		}
	}
	break;
	case PLAYER_STATE::CLEAR:
	{
		SoundManager::GetInst()->m_isWalking = false;
		SoundManager::GetInst()->StopWALK();
		if (!g_checkClear)
		{
			SoundManager::GetInst()->StopBGM();
			SoundManager::GetInst()->PlaySFX(SFX_CLEAR);
			g_checkClear = true;
		}
	}
	break;
	case PLAYER_STATE::STUCK:
	{
		SoundManager::GetInst()->m_isWalking = false;
		SoundManager::GetInst()->StopWALK();
		if (KEY_TAP(KEY::Z))
		{
			SoundManager::GetInst()->PlaySFX(SFX_BUMP);
		}
	}
	}
}

void Player::update_move()
{
	RigidBody* pRigid = GetRigidBody();

	if (inputKeyTrig && m_eCurState != PLAYER_STATE::STUCK)
	{
		if (KEY_HOLD(KEY::LEFT))
		{
			pRigid->AddForce(Vector2(-400.f, 0.f));
		}

		if (KEY_HOLD(KEY::RIGHT))
		{
			pRigid->AddForce(Vector2(400.f, 0.f));
		}

		if (KEY_TAP(KEY::LEFT))
		{
			pRigid->SetVelocity(Vector2(-200.f, pRigid->GetVelocity().y));
		}

		if (KEY_TAP(KEY::RIGHT))
		{
			pRigid->SetVelocity(Vector2(200.f, pRigid->GetVelocity().y));
		}

		if (!infiJumpTrig)
		{
			if (KEY_TAP(KEY::Z) && GetGravity()->GetGround())
			{
				GetRigidBody()->SetVelocity(Vector2(pRigid->GetVelocity().x, -800.f));
			}
		}
		if (infiJumpTrig)
		{
			if (KEY_TAP(KEY::Z))
			{
				GetRigidBody()->SetVelocity(Vector2(pRigid->GetVelocity().x, -800.f));
			}
		}

		if (KEY_HOLD(KEY::Q))
		{
			m_eCurState = PLAYER_STATE::STUCK;
		}
	}
}

void Player::update_interact()
{
	//갖고 있는 선슬라스와 착용 중인 선글라스 교체
	if (inputKeyTrig)
	{
		if (KEY_TAP(KEY::SPACE))
		{
			if (m_eHaveglasses != COLOR_TYPE::EMPTY)
			{
				COLOR_TYPE temp = m_eWearglasses;
				m_eWearglasses = m_eHaveglasses;
				m_eHaveglasses = temp;
				if (m_ePlayerColor == m_eWearglasses && m_eWearglasses != COLOR_TYPE::NONE)
				{
					m_bDead = true;
				}
				SoundManager::GetInst()->PlaySFX(SFX_GWEAR);
			}
		}
	}

	if (KEY_TAP(KEY::F1))
	{
		if (onImmortal)
			onImmortal = false;
		else
			onImmortal = true;
	}

	if (KEY_TAP(KEY::F2))
	{
		if (infiJumpTrig)
			infiJumpTrig = false;
		else
			infiJumpTrig = true;
	}
	if (KEY_TAP(KEY::F3))
	{
		if (m_eWearglasses == COLOR_TYPE::BLACK)
		{
			m_eWearglasses == COLOR_TYPE::NONE;
		}
		else if (m_eWearglasses == COLOR_TYPE::NONE)
		{
			m_eWearglasses == COLOR_TYPE::RED;
		}
		else if (m_eWearglasses == COLOR_TYPE::RED)
		{
			m_eWearglasses == COLOR_TYPE::GREEN;
		}
		else if (m_eWearglasses == COLOR_TYPE::GREEN)
		{
			m_eWearglasses == COLOR_TYPE::BLUE;
		}
		else if (m_eWearglasses == COLOR_TYPE::BLUE)
		{
			m_eWearglasses == COLOR_TYPE::BLACK;
		}
	}
}

void Player::update_gravity()
{
	GetRigidBody()->AddForce(Vector2(0.f, 500.f));
}

void Player::update_animation()
{
	//if (m_ePrevState == m_eCurState && m_iPrevDir == m_iDir)
		//return;
	Animator* pAnim = GetAnimator();

	if (m_eCurState != PLAYER_STATE::JUMP)
	{
		pAnim->FindAnimation(L"JUMP_LEFT")->SetFrame(3);
		pAnim->FindAnimation(L"JUMP_RIGHT")->SetFrame(3);
	}

	switch (m_eCurState)
	{
	case PLAYER_STATE::IDLE:
	{
		if (m_iDir == 1)
			pAnim->Play(L"IDLE_RIGHT", true);
		else
			pAnim->Play(L"IDLE_LEFT", true);
	}
	break;
	case PLAYER_STATE::WALK:
	{
		if (m_iDir == 1)
			pAnim->Play(L"WALK_RIGHT", true);
		else
			pAnim->Play(L"WALK_LEFT", true);
	}
	break;
	case PLAYER_STATE::JUMP:
	{
		if (pAnim->FindAnimation(L"JUMP_LEFT")->GetCurFrame() == pAnim->FindAnimation(L"JUMP_LEFT")->GetMaxFrame() - 1
			|| pAnim->FindAnimation(L"JUMP_RIGHT")->GetCurFrame() == pAnim->FindAnimation(L"JUMP_RIGHT")->GetMaxFrame() - 1)
		{
			pAnim->FindAnimation(L"JUMP_LEFT")->SetFrame(pAnim->FindAnimation(L"JUMP_RIGHT")->GetMaxFrame() - 1);
			pAnim->FindAnimation(L"JUMP_RIGHT")->SetFrame(pAnim->FindAnimation(L"JUMP_RIGHT")->GetMaxFrame() - 1);
		}
		if (m_iDir == 1)
			pAnim->Play(L"JUMP_RIGHT", true);
		else
			pAnim->Play(L"JUMP_LEFT", true);
	}
	break;
	case PLAYER_STATE::DEAD:
	{
		if (m_iDir == 1)
			pAnim->Play(L"DEAD_RIGHT", false);
		else
			pAnim->Play(L"DEAD_LEFT", false);

		if (pAnim->GetCurAnim()->GetName() == L"DEAD_RIGHT"
			|| pAnim->GetCurAnim()->GetName() == L"DEAD_LEFT")
		{
			inputKeyTrig = false;
			if (pAnim->GetCurAnim()->GetCurFrame() == pAnim->GetCurAnim()->GetMaxFrame() - 1)
			{
				pAnim->GetCurAnim()->SetFrame(pAnim->GetCurAnim()->GetMaxFrame() - 1);
				m_lastFrameRepeat++;
				if (3.5f < m_lastFrameRepeat * fDT)
				{
					pAnim->GetCurAnim()->SetFrame(0);
					m_eCurState = PLAYER_STATE::IDLE;
					pAnim->Play(L"IDLE_RIGHT", true);
					SetPos(m_vSpawnPos);
					Camera::GetInst()->SetLookAt(m_spawnCameraPos);
					((SceneStage*)GetOwnerScene())->ReloadBoundary();
					m_bDead = false;
					g_checkDeath = false;
					m_lastFrameRepeat = 0;
					inputKeyTrig = true;
					SoundManager::GetInst()->PauseBGM();
					if (GetOwnerScene()->GetName() == L"C2")
					{
						SetWearGlasses(COLOR_TYPE::BLUE);
						SetHaveGlasses(COLOR_TYPE::EMPTY);
						SetPlayerColor(COLOR_TYPE::NONE);
						m_deadCheckToTexture = true;
					}
					if (GetOwnerScene()->GetName() == L"C3")
					{
						SetWearGlasses(COLOR_TYPE::RED);
						SetHaveGlasses(COLOR_TYPE::EMPTY);
						SetPlayerColor(COLOR_TYPE::NONE);
						m_deadCheckToTexture = true;

					}
				}
			}
		}
	}
	break;
	case PLAYER_STATE::CLEAR:
	{
		if (m_iDir == 1)
			pAnim->Play(L"CLEAR_RIGHT", false);
		else
			pAnim->Play(L"CLEAR_LEFT", false);

		if (pAnim->GetCurAnim()->GetName() == L"CLEAR_RIGHT"
			|| pAnim->GetCurAnim()->GetName() == L"CLEAR_LEFT")
		{
			inputKeyTrig = false;
			if (pAnim->GetCurAnim()->GetCurFrame() == pAnim->GetCurAnim()->GetMaxFrame() - 1)
			{
				pAnim->GetCurAnim()->SetFrame(pAnim->GetCurAnim()->GetMaxFrame() - 1);
				m_lastFrameRepeat++;
				if (1.5f < m_lastFrameRepeat * fDT)
				{
					GetOwnerScene()->TogglePause();
					if (GetOwnerScene()->GetName() == L"C3") {
						m_vSpawnPos = (Vector2(0.f, 2160.f));
						ChangeScene(SCENE_TYPE::STAGE_04);
					}
					else {
						ChangeScene(SCENE_TYPE::SELECT);
					}
					//pAnim->GetCurAnim()->SetFrame(0);
					//m_eCurState = PLAYER_STATE::IDLE;
					//pAnim->Play(L"IDLE_RIGHT", true);
					//
					//Camera::GetInst()->SetLookAt(m_spawnCameraPos);
					//((SceneStage*)GetOwnerScene())->ReloadBoundary();
					//m_bDead = false;
					//g_checkDeath = false;
					//m_lastFrameRepeat = 0;
					//inputKeyTrig = true;




				}
			}
		}
	}
	break;
	case PLAYER_STATE::STUCK:
	{
		pAnim->FindAnimation(L"JUMP_LEFT")->SetFrame(3);
		pAnim->FindAnimation(L"JUMP_RIGHT")->SetFrame(3);

		if (m_iDir == 1)
			pAnim->Play(L"IDLE_RIGHT", true);
		else
			pAnim->Play(L"IDLE_LEFT", true);

		if (KEY_HOLD(KEY::LEFT))
		{
			m_iDir = -1;
			pAnim->Play(L"WALK_LEFT", true);
		}

		if (KEY_HOLD(KEY::RIGHT))
		{
			m_iDir = 1;
			pAnim->Play(L"WALK_RIGHT", true);
		}

		if (KEY_HOLD(KEY::Z))
		{
			if (m_iDir == 1)
			{
				pAnim->FindAnimation(L"JUMP_RIGHT")->SetFrame(pAnim->FindAnimation(L"JUMP_RIGHT")->GetMaxFrame() - 1);
				pAnim->Play(L"JUMP_RIGHT", true);
			}
			else
			{
				pAnim->FindAnimation(L"JUMP_LEFT")->SetFrame(pAnim->FindAnimation(L"JUMP_RIGHT")->GetMaxFrame() - 1);
				pAnim->Play(L"JUMP_LEFT", true);
			}
		}
	}
	break;
	}
}

void Player::OnCollisionEnter(Collider* _pOther)
{
	GameObject* pOtherObj = _pOther->GetObj();
	if (L"Terrain" == pOtherObj->GetName())
	{
		Vector2 vPos = GetPos();
		if (vPos.y < pOtherObj->GetPos().y)
		{
			m_eCurState = PLAYER_STATE::IDLE;
		}
	}
	//가시 충돌하면 플레이어 상태 데드로
	if (pOtherObj->GetName() == L"Thorn" && !onImmortal)
	{
		ColorObject* pColorObj = dynamic_cast<ColorObject*>(pOtherObj);
		if (GetWearGlasses() != pColorObj->GetColorState() && GetPlayerColor() != pColorObj->GetColorState())
			m_bDead = true;
	}
	//세이브 포인트 충돌하면 스폰 포인트 세이브 포인트로
	if (pOtherObj->GetName() == L"SavePoint")
	{
		SetSpawnPos(_pOther->GetObj()->GetPos());
		SoundManager::GetInst()->PlaySFX(SFX_SAVE);
		SetSpawnCameraPos(Camera::GetInst()->GetFinalLookAt());
	}
	// 클리어 포인트 충돌하면 플레이어 상태 클리어로
	if (pOtherObj->GetName() == L"ClearPoint")
	{
		ColorObject* pColorObj = dynamic_cast<ColorObject*>(pOtherObj);
		if (GetWearGlasses() != pColorObj->GetColorState() && GetPlayerColor() != pColorObj->GetColorState())
			m_bClear = true;
	}

	if (_pOther->GetObj()->GetName() == L"Drink" || _pOther->GetObj()->GetName() == L"Glasses") {
		Arrow* arrow = new Arrow(GetOwnerScene());
		Vector2 pos = _pOther->GetObj()->GetPos();
		arrow->SetName(L"Current Sunglass");
		arrow->SetTex(ResourceManager::GetInst()->LoadTexture(L"arrow", L"texture\\arrow.bmp"));
		arrow->SetTexScale();
		arrow->SetPos(Vector2(pos.x, pos.y - 30.f));
		arrow->SetOwnerObj(_pOther->GetObj());
		CreateObject(arrow, GROUP_TYPE::ARROW);
	}
}

void Player::OnCollision(Collider* _pOther)
{
	// Z키로 충돌 중인 썬글라스 오브젝트 컬러를 플레이어 보유 썬글라스 컬러로 
	if (_pOther->GetObj()->GetName() == L"Glasses")
	{
		Glasses* pColiglasses = dynamic_cast<Glasses*>(_pOther->GetObj());
		assert(pColiglasses);

		if (KEY_TAP(KEY::X) && (m_eHaveglasses != pColiglasses->GetColorState()) && (m_eWearglasses != pColiglasses->GetColorState()))
		{
			m_eHaveglasses = pColiglasses->GetColorState();
			SoundManager::GetInst()->PlaySFX(SFX_GTAKE);
		}
	}

	// Z키로 충돌 중인 술 오브젝트 컬러를 플레이어 컬러로 
	if (_pOther->GetObj()->GetName() == L"Drink")
	{
		Drink* pColidrink = dynamic_cast<Drink*>(_pOther->GetObj());
		assert(pColidrink);

		if (KEY_TAP(KEY::X) && (m_ePlayerColor != pColidrink->GetColorState()))
		{
			m_ePlayerColor = pColidrink->GetColorState();
			if (m_ePlayerColor == COLOR_TYPE::NONE)
				SoundManager::GetInst()->PlaySFX(SFX_DRUG);
			else
				SoundManager::GetInst()->PlaySFX(SFX_DRINK);
			if (m_ePlayerColor == m_eWearglasses && m_eWearglasses != COLOR_TYPE::NONE)
			{
				m_bDead = true;
			}
		}
	}

	if (_pOther->GetObj()->GetName() == L"SignPost1")
	{
		SignPostPopUp* pPopup = (SignPostPopUp*)_pOther->GetObj()->GetOwnerScene()->SetObject(GROUP_TYPE::POSTPOPUP, 0);
		if (pPopup->GetName() == L"PostPopUp1")
			pPopup->m_PostPopUp = true;
	}

	if (_pOther->GetObj()->GetName() == L"SignPost2")
	{
		SignPostPopUp* pPopup = (SignPostPopUp*)_pOther->GetObj()->GetOwnerScene()->SetObject(GROUP_TYPE::POSTPOPUP, 0);
		if (pPopup->GetName() == L"PostPopUp2")
			pPopup->m_PostPopUp = true;
	}

	if (_pOther->GetObj()->GetName() == L"SignPost3")
	{
		SignPostPopUp* pPopup = (SignPostPopUp*)_pOther->GetObj()->GetOwnerScene()->SetObject(GROUP_TYPE::POSTPOPUP, 1);
		if (pPopup->GetName() == L"PostPopUp3")
			pPopup->m_PostPopUp = true;
	}

	if (_pOther->GetObj()->GetName() == L"SignPost4")
	{
		SignPostPopUp* pPopup = (SignPostPopUp*)_pOther->GetObj()->GetOwnerScene()->SetObject(GROUP_TYPE::POSTPOPUP, 0);
		if (pPopup->GetName() == L"PostPopUp4")
			pPopup->m_PostPopUp = true;
	}

	if (_pOther->GetObj()->GetName() == L"SignPost5")
	{
		SignPostPopUp* pPopup = (SignPostPopUp*)_pOther->GetObj()->GetOwnerScene()->SetObject(GROUP_TYPE::POSTPOPUP, 1);
		if (pPopup->GetName() == L"PostPopUp5")
			pPopup->m_PostPopUp = true;
	}


	if (_pOther->GetObj()->GetName() == L"SignPost6")
	{
		SignPostPopUp* pPopup = (SignPostPopUp*)_pOther->GetObj()->GetOwnerScene()->SetObject(GROUP_TYPE::POSTPOPUP, 0);
		if (pPopup->GetName() == L"PostPopUp6")
			pPopup->m_PostPopUp = true;
	}
	if (_pOther->GetObj()->GetName() == L"SignPost7")
	{
		SignPostPopUp* pPopup = (SignPostPopUp*)_pOther->GetObj()->GetOwnerScene()->SetObject(GROUP_TYPE::POSTPOPUP, 1);
		if (pPopup->GetName() == L"PostPopUp7")
			pPopup->m_PostPopUp = true;
	}
	if (_pOther->GetObj()->GetName() == L"SignPost8")
	{
		SignPostPopUp* pPopup = (SignPostPopUp*)_pOther->GetObj()->GetOwnerScene()->SetObject(GROUP_TYPE::POSTPOPUP, 2);
		if (pPopup->GetName() == L"PostPopUp8")
			pPopup->m_PostPopUp = true;
	}
	if (_pOther->GetObj()->GetName() == L"SignPost9")
	{
		SignPostPopUp* pPopup = (SignPostPopUp*)_pOther->GetObj()->GetOwnerScene()->SetObject(GROUP_TYPE::POSTPOPUP, 3);
		if (pPopup->GetName() == L"PostPopUp9")
			pPopup->m_PostPopUp = true;
	}
	if (_pOther->GetObj()->GetName() == L"SignPost10")
	{
		SignPostPopUp* pPopup = (SignPostPopUp*)_pOther->GetObj()->GetOwnerScene()->SetObject(GROUP_TYPE::POSTPOPUP, 4);
		if (pPopup->GetName() == L"PostPopUp10")
			pPopup->m_PostPopUp = true;
	}

}

void Player::OnCollisionExit(Collider* _pOther)
{
	if (_pOther->GetObj()->GetName() == L"SignPost1")
	{
		SignPostPopUp* pPopup = (SignPostPopUp*)_pOther->GetObj()->GetOwnerScene()->SetObject(GROUP_TYPE::POSTPOPUP, 0);
		if (pPopup->GetName() == L"PostPopUp1")
			pPopup->m_PostPopUp = false;
	}

	if (_pOther->GetObj()->GetName() == L"SignPost2")
	{
		SignPostPopUp* pPopup = (SignPostPopUp*)_pOther->GetObj()->GetOwnerScene()->SetObject(GROUP_TYPE::POSTPOPUP, 0);
		if (pPopup->GetName() == L"PostPopUp2")
			pPopup->m_PostPopUp = false;
	}


	if (_pOther->GetObj()->GetName() == L"SignPost3")
	{
		SignPostPopUp* pPopup = (SignPostPopUp*)_pOther->GetObj()->GetOwnerScene()->SetObject(GROUP_TYPE::POSTPOPUP, 1);
		if (pPopup->GetName() == L"PostPopUp3")
			pPopup->m_PostPopUp = false;
	}

	if (_pOther->GetObj()->GetName() == L"SignPost4")
	{
		SignPostPopUp* pPopup = (SignPostPopUp*)_pOther->GetObj()->GetOwnerScene()->SetObject(GROUP_TYPE::POSTPOPUP, 0);
		if (pPopup->GetName() == L"PostPopUp4")
			pPopup->m_PostPopUp = false;
	}

	if (_pOther->GetObj()->GetName() == L"SignPost5")
	{
		SignPostPopUp* pPopup = (SignPostPopUp*)_pOther->GetObj()->GetOwnerScene()->SetObject(GROUP_TYPE::POSTPOPUP, 1);
		if (pPopup->GetName() == L"PostPopUp5")
			pPopup->m_PostPopUp = false;
	}

	if (_pOther->GetObj()->GetName() == L"SignPost6")
	{
		SignPostPopUp* pPopup = (SignPostPopUp*)_pOther->GetObj()->GetOwnerScene()->SetObject(GROUP_TYPE::POSTPOPUP, 0);
		if (pPopup->GetName() == L"PostPopUp6")
			pPopup->m_PostPopUp = false;
	}

	if (_pOther->GetObj()->GetName() == L"SignPost7")
	{
		SignPostPopUp* pPopup = (SignPostPopUp*)_pOther->GetObj()->GetOwnerScene()->SetObject(GROUP_TYPE::POSTPOPUP, 1);
		if (pPopup->GetName() == L"PostPopUp7")
			pPopup->m_PostPopUp = false;
	}

	if (_pOther->GetObj()->GetName() == L"SignPost8")
	{
		SignPostPopUp* pPopup = (SignPostPopUp*)_pOther->GetObj()->GetOwnerScene()->SetObject(GROUP_TYPE::POSTPOPUP, 2);
		if (pPopup->GetName() == L"PostPopUp8")
			pPopup->m_PostPopUp = false;
	}

	if (_pOther->GetObj()->GetName() == L"SignPost9")
	{
		SignPostPopUp* pPopup = (SignPostPopUp*)_pOther->GetObj()->GetOwnerScene()->SetObject(GROUP_TYPE::POSTPOPUP, 3);
		if (pPopup->GetName() == L"PostPopUp9")
			pPopup->m_PostPopUp = false;
	}

	if (_pOther->GetObj()->GetName() == L"SignPost10")
	{
		SignPostPopUp* pPopup = (SignPostPopUp*)_pOther->GetObj()->GetOwnerScene()->SetObject(GROUP_TYPE::POSTPOPUP, 4);
		if (pPopup->GetName() == L"PostPopUp10")
			pPopup->m_PostPopUp = false;
	}

	if (_pOther->GetObj()->GetName() == L"Drink" || _pOther->GetObj()->GetName() == L"Glasses") {
		const vector<Arrow*>& vecArrow = (const vector<Arrow*>&)(GetOwnerScene()->GetGroupObject(GROUP_TYPE::ARROW));

		for (size_t i = 0; i < vecArrow.size(); ++i) {
			if (vecArrow[i]->GetOwnerObj()->GetName() == _pOther->GetObj()->GetName()) {
				DeleteObject(vecArrow[i]);
			}
		}
	}

}