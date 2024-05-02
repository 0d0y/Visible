#pragma once
class SoundManager
{
	SINGLE(SoundManager);

public:
	void Initialize();
	void PlayBGM(int);
	void StopBGM();
	void PauseBGM();
	void PlayWALK();
	void StopWALK();
	void PlaySFX(int);
	void PlayBUMP();
	void AdjustChannelBgmVolume(float);
	void AdjustChannelSfxVolume(float);
	void EndSound();

	bool m_isPlaying = false;
	bool m_isPaused = false;
	bool m_isWalking = false;
	//void update();
};

// 사운드의 종류를 설정한 enum문입니다.
enum SOUNDKIND
{
	MENU_LOBBY = 0,
	MENU_SELECT,

	UI_BUTTON,

	BGM_01,
	BGM_02,
	BGM_03,
	BGM_ENDING,

	SFX_WALK,
	SFX_JUMP,
	SFX_LAND,
	SFX_DEATH,
	SFX_SAVE,
	SFX_GTAKE,
	SFX_GWEAR,
	SFX_DRUG,
	SFX_DRINK,
	SFX_BUMP,
	SFX_CLEAR,

	SD_END
};