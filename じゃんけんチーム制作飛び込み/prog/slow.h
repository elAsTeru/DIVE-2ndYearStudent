#pragma once
#ifndef _SLOW_H_
#define _SLOW_H_
#include "DxLib.h"
#include "Gauge.h"
#include "Player.h"
#include "WaterIn.h"
#include "Circle.h"
#define UI_IMG_NUM 5
#define PI    3.1415926535897932384626433832795f
class SLOW
{
public:
	SLOW();
	~SLOW();
	
	void SlowMode_Update(Player* player,int stage);
	void SlowMode_Draw(int Stage);
	void SlowSwitch_ON() { SlowFlag = true; };
	void SlowSwitch_OFF() { SlowFlag = false; };

	void LAST_SlowSwitch_ON() { lastMissionFlag = true; };
	void LAST_SlowSwitch_OFF() { lastMissionFlag = false; };
	int returnPoint() { return point; };
	bool returnSlowFlag();
	void Init();

private:
	bool SlowFlag=false;//���݃X���E��Ԃ�
	class Gauge* gauge = new Gauge;//�Q�[�W�����
	class WaterIn* water = new WaterIn;
	class Circle* circle = new Circle;
	bool beforeSlowFlag;//�O�t���[���̃X���E�t���O�̏��
	int point=0;//�󂯓n���p�̓��_�ϐ�
	int TitleFont;//�J�E���g�_�E���\���p�̃t�H���g�T�C�Y
	int SpaceImg;
	bool lastMissionFlag;
	int time;
	const int distance=1;
	const int Lastdistance = 1;
	int startTime;
	int EndTime;
	float speed;
	const float STAGE_POS_Y_START[4] = { 175.0f,140.0f,100.0f,60.0f };
	const float STAGE_POS_Y_END[4] = { 174.0f,139.0f ,99.0f ,55.0f };
	int CLOCKIMG[12];
	int x;
	int y;
	float Size = 0.7;
	const int Clock_SIZE_X=100*Size;
	const int Clock_SIZE_Y=120*Size;
	const int CLOCK_X=40;
	const int CLOCK_Y = 25;

	const int SCORE_X = 100;
	const int SCORE_Y = 100;

	float UISize = 0.7;
	const int UIBASE_SIZE_X= 875*UISize;
	const int UIBASE_SIZE_Y= 209 * UISize;
	const int UIBASE_X=-300;
	const int UIBASE_Y=0;



	int UiImg[UI_IMG_NUM];
};




#endif // !_SLOW_H_
