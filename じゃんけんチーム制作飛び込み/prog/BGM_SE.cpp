#include "BGM_SE.h"

BGMSE::BGMSE()
	:NowSound(0)
{
	BgmData[SoundTag::BGM_Title]=LoadSoundMem("data/SE/魔王魂  アコースティック45.mp3");
	BgmData[SoundTag::BGM_GAMEMAIN] = LoadSoundMem("data/SE/魔王魂 BGM ネオロック83.mp3");
	BgmData[SoundTag::BGM_RESULT] = LoadSoundMem("data/SE/魔王魂  8bit01.mp3");
	SeData[SeTag::SE_WATER] = LoadSoundMem("data/SE/水ドポン(1).mp3");
	SeData[SeTag::SE_CHEER] = LoadSoundMem("data/SE/スタジアムのざわめき.mp3");
	
	for (int i = 0; i < BGM_NUM; i++)
	{
		ChangeVolumeSoundMem(255 * 50 / 100, BgmData[i]);
	}

}

BGMSE::~BGMSE()
{
	for (int i = 0; i < BGM_NUM; i++)
	{
		DeleteSoundMem(BgmData[i]);
	}
	for (int i = 0; i < SE_NUM; i++)
	{
		DeleteSoundMem(SeData[i]);
	}
}

void BGMSE::SoundBGM(int Sound)
{
	//今流れているBGMを止める
	StopSoundMem(NowSound);
	//Sceneによって流れるBGMが変わる
	if (Sound == BGM_Title)
	{
		PlaySoundMem(BgmData[SoundTag::BGM_Title], DX_PLAYTYPE_LOOP);
		NowSound = BgmData[SoundTag::BGM_Title];
	}
	if (Sound == BGM_GAMEMAIN)
	{
		PlaySoundMem(BgmData[SoundTag::BGM_GAMEMAIN], DX_PLAYTYPE_LOOP);
		NowSound = BgmData[SoundTag::BGM_GAMEMAIN];
	}
	if (Sound == BGM_RESULT)
	{
		PlaySoundMem(BgmData[SoundTag::BGM_RESULT], DX_PLAYTYPE_BACK);
		NowSound = BgmData[SoundTag::BGM_RESULT];
	}
}

void BGMSE::SoundSE(int SoundNum)
{
	PlaySoundMem(SeData[SoundNum], DX_PLAYTYPE_BACK);
}

void BGMSE::StopSoundSE(int SoundNum)
{
	StopSoundMem(SeData[SoundNum]);
}
