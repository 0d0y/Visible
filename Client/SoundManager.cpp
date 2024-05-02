#include "pch.h"
#include "SoundManager.h"

#include "fmod.hpp"

using namespace std;
using namespace FMOD;



System* g_system = NULL;
Sound* g_sounds[SD_END];
Channel* g_channelBgm;
Channel* g_channelSfx;
Channel* g_channelWalk;
Channel* g_channelBump;
ChannelGroup* g_channelGroupBGM;
ChannelGroup* g_channelGroupWALK;
ChannelGroup* g_channelGroupSFX;
ChannelGroup* g_channelGroupBump;
FMOD_RESULT g_result;

float g_volumeBgm = 0.4f;
float g_volumeSfx = 0.4f;


SoundManager::SoundManager()
{

}
SoundManager::~SoundManager()
{

}

void SoundManager::Initialize()
{
    g_result = System_Create(&g_system);
    if (g_result != FMOD_OK)
    {
        return;
    }

    g_result = g_system->init(32, FMOD_INIT_NORMAL, nullptr);
    if (g_result != FMOD_OK)
    {
        return;
    }

    // 사운드를 읽어와서 저장합니다.
    g_result = g_system->createSound("content/sound/Select.wav", FMOD_LOOP_NORMAL, nullptr, &g_sounds[MENU_SELECT]);
    if (g_result != FMOD_OK)
    {
        return;
    }
	g_result = g_system->createSound("content/sound/Lobby.wav", FMOD_LOOP_NORMAL, nullptr, &g_sounds[MENU_LOBBY]);
	if (g_result != FMOD_OK)
	{
		return;
	}
	g_result = g_system->createSound("content/sound/InGame1.wav", FMOD_LOOP_NORMAL, nullptr, &g_sounds[BGM_01]);
	if (g_result != FMOD_OK)
	{
		return;
	}
	g_result = g_system->createSound("content/sound/InGame2.wav", FMOD_LOOP_NORMAL, nullptr, &g_sounds[BGM_02]);
	if (g_result != FMOD_OK)
	{
		return;
	}
	g_result = g_system->createSound("content/sound/InGame3.wav", FMOD_LOOP_NORMAL, nullptr, &g_sounds[BGM_03]);
	if (g_result != FMOD_OK)
	{
		return;
	}
	g_result = g_system->createSound("content/sound/Credit.wav", FMOD_LOOP_NORMAL, nullptr, &g_sounds[BGM_ENDING]);
	if (g_result != FMOD_OK)
	{
		return;
	}
    g_result = g_system->createSound("content/sound/Walk.wav", FMOD_LOOP_NORMAL, nullptr, &g_sounds[SFX_WALK]);
    if (g_result != FMOD_OK)
    {
        return;
    }
    g_result = g_system->createSound("content/sound/Jump.wav", FMOD_DEFAULT, nullptr, &g_sounds[SFX_JUMP]);
    if (g_result != FMOD_OK)
    {
        return;
    }
	g_result = g_system->createSound("content/sound/Landing.wav", FMOD_DEFAULT, nullptr, &g_sounds[SFX_LAND]);
	if (g_result != FMOD_OK)
	{
		return;
	}
	g_result = g_system->createSound("content/sound/Drug.wav", FMOD_DEFAULT, nullptr, &g_sounds[SFX_DRUG]);
	if (g_result != FMOD_OK)
	{
		return;
	}
	g_result = g_system->createSound("content/sound/Drink.wav", FMOD_DEFAULT, nullptr, &g_sounds[SFX_DRINK]);
	if (g_result != FMOD_OK)
	{
		return;
	}
	g_result = g_system->createSound("content/sound/Save.wav", FMOD_DEFAULT, nullptr, &g_sounds[SFX_SAVE]);
	if (g_result != FMOD_OK)
	{
		return;
	}
	g_result = g_system->createSound("content/sound/Collider.wav", FMOD_DEFAULT, nullptr, &g_sounds[SFX_BUMP]);
	if (g_result != FMOD_OK)
	{
		return;
	}
	g_result = g_system->createSound("content/sound/Death.wav", FMOD_DEFAULT, nullptr, &g_sounds[SFX_DEATH]);
	if (g_result != FMOD_OK)
	{
		return;
	}
	g_result = g_system->createSound("content/sound/Clear.wav", FMOD_DEFAULT, nullptr, &g_sounds[SFX_CLEAR]);
	if (g_result != FMOD_OK)
	{
		return;
	}
	g_result = g_system->createSound("content/sound/SunglassTake.wav", FMOD_DEFAULT, nullptr, &g_sounds[SFX_GTAKE]);
	if (g_result != FMOD_OK)
	{
		return;
	}
	g_result = g_system->createSound("content/sound/SunglassWear.wav", FMOD_DEFAULT, nullptr, &g_sounds[SFX_GWEAR]);
	if (g_result != FMOD_OK)
	{
		return;
	}
	g_result = g_system->createSound("content/sound/UI.wav", FMOD_DEFAULT, nullptr, &g_sounds[UI_BUTTON]);
	if (g_result != FMOD_OK)
	{
		return;
	}
	g_result = g_system->createChannelGroup("GroupBGM", &g_channelGroupBGM);
	g_result = g_system->createChannelGroup("GroupWALK", &g_channelGroupWALK);
	g_result = g_system->createChannelGroup("GroupSFX", &g_channelGroupSFX);
	g_result = g_system->createChannelGroup("GroupBUMP", &g_channelGroupBump);
}

void SoundManager::PlayBGM(int m_soundKind)
{
    if (m_isPlaying == false)
    {
        if (m_isPaused)
            m_isPaused = false;
        g_result = g_system->playSound(g_sounds[m_soundKind], g_channelGroupBGM, false, &g_channelBgm);
        g_channelBgm->setPriority(0);
        g_channelBgm->setVolume(g_volumeBgm);
        if (g_result != FMOD_OK)
        {
            return;
        }
        m_isPlaying = true;
    }
}

void SoundManager::StopBGM()
{
    g_result = g_channelBgm->stop();
    if (g_result != FMOD_OK)
    {
        return;
    }
    m_isPlaying = false;
}

void SoundManager::PauseBGM()
{
    if (g_channelBgm)
    {
        if (m_isPaused)
        {
            g_channelBgm->setPaused(false); // 일시정지 해제
            m_isPaused = false;
        }
        else
        {
            g_channelBgm->setPaused(true); // 일시정지
            m_isPaused = true;
        }
    }
}

void SoundManager::PlayWALK()
{
    if (m_isWalking == false)
    {
        g_result = g_system->playSound(g_sounds[SFX_WALK], g_channelGroupWALK, false, &g_channelWalk);
        g_channelWalk->setPriority(2);
        g_channelWalk->setVolume(g_volumeSfx);
        if (g_result != FMOD_OK)
        {
            return;
        }
        m_isWalking = true;
    }
    else
    {
        return;
    }
}

void SoundManager::StopWALK()
{
    g_result = g_channelWalk->stop();
    if (g_result != FMOD_OK)
    {
        return;
    }
    m_isWalking = false;
}

void SoundManager::PlaySFX(int m_soundKind)
{
    g_system->playSound(g_sounds[m_soundKind], g_channelGroupSFX, false, &g_channelSfx);
    g_channelSfx->setVolume(g_volumeSfx);
    g_channelSfx->setPriority(100);
    if (g_result != FMOD_OK)
    {
        return;
    }
}

void SoundManager::PlayBUMP()
{
	g_system->playSound(g_sounds[SFX_BUMP], g_channelGroupBump, false, &g_channelBump);
	g_channelBump->setVolume(g_volumeSfx);
	g_channelBump->setPriority(3);
	if (g_result != FMOD_OK)
	{
		return;
	}
}


void SoundManager::AdjustChannelBgmVolume(float m_amount)
{
    g_volumeBgm += m_amount;
    if (g_volumeBgm > 1.0f) // 최대 볼륨 체크
        g_volumeBgm = 1.0f;
    if (g_volumeBgm < 0.0f) // 최소 볼륨 체크
        g_volumeBgm = 0.0f;
    g_channelBgm->setVolume(g_volumeBgm);
}

void SoundManager::AdjustChannelSfxVolume(float m_amount)
{
    g_volumeSfx += m_amount;
    if (g_volumeSfx > 1.0f) // 최대 볼륨 체크
        g_volumeSfx = 1.0f;
    if (g_volumeSfx < 0.0f) // 최소 볼륨 체크
        g_volumeSfx = 0.0f;
    g_channelSfx->setVolume(g_volumeSfx);
}


void SoundManager::EndSound()
{
    for (int i = 0; i < SD_END - 1; i++)
    {
        g_sounds[i]->release();
    }
    g_system->close();
    g_system->release();
}

