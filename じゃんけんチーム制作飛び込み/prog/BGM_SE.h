#pragma once
#include"DxLib.h"
#define BGM_NUM 3//BGMの数
#define SE_NUM 2//SEの数
class BGMSE
{
public:
	enum SoundTag//BGMのタグ
	{
		BGM_Title,
		BGM_GAMEMAIN,
		BGM_RESULT,
	};
	enum SeTag//SEのタグ
	{
		SE_WATER,
		SE_CHEER,
	};
	BGMSE();
	~BGMSE();
	void SoundBGM(int SoundNum);//soundNumにtagを入れるとBGMが流れる
	void SoundSE(int SoundNum);//soundNumにtagを入れるとSEが流れる

	void StopSoundSE(int SoundNum);//soundNumにtagを入れるとSEが止まる
private:
	int BgmData[3];//BGMを入れる
	int SeData[2];//SEを入れる
	int NowSound;//今流れているBGMを入れる
};

