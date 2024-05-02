#pragma once
#include "GameObject.h"
#include "RigidBody.h"
#include "TimeManager.h"
#include "SoundManager.h"

class Texture;
class Fsm;
class Collider;

class Player :
	public GameObject
{
private:
	COLOR_TYPE m_ePlayerColor;
	COLOR_TYPE m_ePrevPlayerColor;
	COLOR_TYPE m_eWearglasses;
	COLOR_TYPE m_eHaveglasses;
	Vector2	m_vSpawnPos;
	Vector2 m_spawnCameraPos;
	PLAYER_STATE m_eCurState;
	PLAYER_STATE m_ePrevState;
	UINT m_lastFrameRepeat;
	RigidBody m_rigidBody;
	int	m_iDir;
	int	m_iPrevDir;
	Vector2 m_prevPos;
	int	m_reactionCount;
	bool m_bDead;
	bool m_bClear;
	bool m_collisionHandledX;
	bool m_collisionHandledY;
	bool onImmortal;
	bool inputKeyTrig;
	bool jumpTrig;
	bool m_deadCheckToTexture;
	bool infiJumpTrig;


public:
	virtual void Update();
	virtual void Render(HDC _dc);

	bool g_checkJumping = false;
	bool g_checkDeath = false;
	bool g_checkClear = false;

public:
	COLOR_TYPE GetWearGlasses() { return m_eWearglasses; }
	void SetWearGlasses(COLOR_TYPE _eGlasses) { m_eWearglasses = _eGlasses; }
	COLOR_TYPE GetHaveGlasses() { return m_eHaveglasses; }
	void SetHaveGlasses(COLOR_TYPE _eGlasses) { m_eHaveglasses = _eGlasses; }
	COLOR_TYPE GetPlayerColor() { return m_ePlayerColor; }
	void SetPlayerColor(COLOR_TYPE _Color) { m_ePlayerColor = _Color; }
	Vector2 GetSpawnPos() { return m_vSpawnPos; }
	void SetSpawnPos(Vector2 _Pos) { m_vSpawnPos = _Pos; }
	void SetPlayerState(PLAYER_STATE _state) { m_eCurState = _state; }

	void SetReaction(int _reactionCount) { m_reactionCount = _reactionCount; }
	int GetReaction() { return m_reactionCount; }

	void SetSpawnCameraPos(Vector2 _pos) { m_spawnCameraPos = _pos; }

	void SetCollisionHandledX(bool _collisionHandledX) { m_collisionHandledX = _collisionHandledX; }
	bool IsCollisionHandledX() { return m_collisionHandledX; }	
	void SetCollisionHandledY(bool _collisionHandledY) { m_collisionHandledY = _collisionHandledY; }
	bool IsCollisionHandledY() { return m_collisionHandledY; }

private:
	CLONE(Player);

	void update_sound();
	void update_state();
	void update_move();
	void update_texture();
	void update_animation();
	void update_interact();
	void update_gravity();

	virtual void OnCollisionEnter(Collider* _pOther);
	virtual void OnCollision(Collider* _pOther);
	virtual void OnCollisionExit(Collider* _pOther);
public:
	Player(Scene* _ownerScene);
	~Player();

//public:
//	void CheckColliderSound()
//	{
//		static Vector2 vPreviousPlayerPos = GetPos();
//		Vector2 vCurrentPlayerPos = GetPos();
//		Vector2 vMaxVelocity = m_rigidBody.GetMaxVelocity();
//		float deltaTime = TimeManager::GetInst()->GetfDT();
//		
//		float deltaX = abs(vCurrentPlayerPos.x - vPreviousPlayerPos.x);
//		float deltaY = abs(vCurrentPlayerPos.y - vPreviousPlayerPos.y);
//
//
//
//		if ((deltaX > 75.f && deltaX < 150.f && deltaY < 1.0f)||(deltaY > 50.f && deltaY < 110.f && deltaX < 1.0f))
//		{
// 			//SoundManager::GetInst()->PlaySFX(SFX_BUMP);
//			SoundManager::GetInst()->PlayBUMP();
//		}
//
//		vPreviousPlayerPos = vCurrentPlayerPos;
//	} 
};

