#pragma once
//�{�c
#ifndef _RESULT_H_
#define _RESULT_H_
#include "DxLib.h"
#include "iostream"
#include "vector"
#include "algorithm"
#include "SceneMgr.h"
#include "pointMng.h"
#include "Player.h"
#include "camera.h"
#include "Fadeout_in.h"
class SceneMgr;

class Result
{
public:
	Result();
	~Result();

	void Update();
	void Draw(pointMng* point);

	void Rode();
	void Delete();


private:
	// �ǂݍ��݃t���O
	bool rodeFlag;

	class Player* player;
	class Camera* camera;
	class Fade* fade;
	//�ҋ@���[�V�����@���
	const int motionResult = 003;
	const int motionResultFlame = 80;
	const int motionResultPlaySpeed = 0.1f;
	// �폜�t���O
	bool deleteFlag;

	//SPACE�L�[�̉摜�n���h��
	int BackgroundImg;
	//�摜���g������ۂɎg��
	float ExpansionRate;

	//�摜��ύX����ۂ̕ύX��
	float changeCode;
	
	//�摜�̔{��
	float imgSize = 1.0f;
	int GoTitle;
	int SpaceImg;

	int Font;
	int NameFont;
	int newFont;
	int ndFont;
	int rdFont;
	int NumberFont;
	int x = 300;
	int y = 90;
	const int RANKING_DRAW_X = 150;
	const int RANKING_DRAW_Y = 190;

	const int  SPACESIZE_X = 125;
	const int  SPACESIZE_Y = 50;
	const int  STARTSIZE_X = 250;
	const int  STARTSIZE_Y = 50;
	const int  STARTX = 20;
	const int  STARTY = 700;
	//70~720
	//50~170
 
	//�����L���O��score�̕\����؂�ւ���

};



#endif //_RESULT_H_
