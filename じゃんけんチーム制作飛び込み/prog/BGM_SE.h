#pragma once
#include"DxLib.h"
#define BGM_NUM 3//BGM�̐�
#define SE_NUM 2//SE�̐�
class BGMSE
{
public:
	enum SoundTag//BGM�̃^�O
	{
		BGM_Title,
		BGM_GAMEMAIN,
		BGM_RESULT,
	};
	enum SeTag//SE�̃^�O
	{
		SE_WATER,
		SE_CHEER,
	};
	BGMSE();
	~BGMSE();
	void SoundBGM(int SoundNum);//soundNum��tag�������BGM�������
	void SoundSE(int SoundNum);//soundNum��tag�������SE�������

	void StopSoundSE(int SoundNum);//soundNum��tag�������SE���~�܂�
private:
	int BgmData[3];//BGM������
	int SeData[2];//SE������
	int NowSound;//������Ă���BGM������
};

