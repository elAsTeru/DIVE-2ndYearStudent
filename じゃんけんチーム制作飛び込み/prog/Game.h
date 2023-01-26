#pragma once
#ifndef _GAME_H_
#define _GAME_H_


#include "Player.h"
#include "Camera.h"
#include "bridge.h"
#include"Map.h"
#include "Gauge.h"
#include "slow.h"
#include "pointMng.h"
#include"BGM_SE.h"
#include "Fadeout_in.h"


class Game
{
public:
	Game();
	~Game();
	void Rode();
	void Delete();
	void Update(pointMng* pointM);
	void Loop();
	void GameInit();
private:
	//
	bool rodeFlag;
	//
	bool deleteFlag;
	// �e����
	class Player* player;
	class Camera* camera;
	class Map* map;
	class SLOW* slow;
	class BGMSE* se;
	class Fade* fade;
	int Time;
	int TimeFont;//�J�E���g�_�E���\���p�̃t�H���g�T�C�Y
	int TitleFont;//�J�E���g�_�E���\���p�̃t�H���g�T�C�Y
	int CountDownFont;	//���Ԑ����p�̃t�H���g�T�C�Y
	float timerImgExtRate = 0.1f;				//���Ԑ����p�摜�̃T�C�Y�{��
	float timerImgAngle = 0.0f;			//���Ԑ����p�摜�̉�]
	int RedCode;//�Ԃ̃J���[�R�[�h

	int startCount;//�������Ԃ̃J�E���g�J�n�^�C�~���O
	bool callend = false;
	bool firstCall = false;
	int Description;

	bool ClearFlag=false;//Scene�J�ڂ̃t���O

	//�X���[���[�h�ɂȂ�ʒu
	const float STAGE_POS_Y_START[4] = { 175.0f,140.0f,100.0f,60.0f };
	const float STAGE_POS_Y_END[4] = { 174.0f,139.0f ,99.0f ,55.0f };
	int NowStage;//���̂����ڂ̉ۑ肩
	int WhiteBack;
	int BlackBack;
	int point = 0;
	//��񂾂��Ăяo������
	bool oneceagain = true;


	/// <summary>
	/// �ύX�_���������Ō�̃~�j�Q�[���̓_���摜������n���h��
	/// </summary>
	int lastMiniGameModelHandel;
	

	


};
#endif // !_GAME_H_