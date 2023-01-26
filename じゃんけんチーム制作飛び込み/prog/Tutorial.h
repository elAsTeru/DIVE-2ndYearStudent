#pragma once
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

#include"SceneMgr.h"
#include "Player.h"
#include "Camera.h"
#include "bridge.h"
#include "Map.h"
#include "Gauge.h"
#include "slow.h"
#include "pointMng.h"
#include"BGM_SE.h"
#include<string.h>
#include <string>
using namespace std;
class Tutorial
{
public:
	Tutorial();
	~Tutorial();
	void Update();
	void Draw();
	void Load();
	void Delete();
private:
	bool LoadFlag;
	//
	bool deleteFlag;
	int BackGroundTImg;
	int backgroundImg;
	int TG;
	int stage;
	int Tutorial_Line_Img;
	int Tutorial_Box_Img;
	int SpaceImg;
	int sixbox[6];
	int sixboxR[6];
	int TutorialImg[6];
	int TitleFont;
	int textfont;
	int font;
	int Closefont;
	int arrowImg;
	int  arrow;
	int arrowX=50;
	int arrowY=40;
	int arrowMove;
	int x, y;

	int arrowL;
	int arrowR;
	string T_TEXT[6] = {"�S�̗̂����������܂��B�P.SPACE�������Ĕ�э��݂܂��B\n�Q.�~�b�V�������N���A���邱�Ƃœ��_�������܂��B\n�R.��э��݂̊p�x�𒲐����Đ��ʂɐ����ɂȂ�悤�ɒ������܂��傤",
		"�摜�̏ꏊ�Ƀ~�b�V�����̍ۂ̎��Ԑ������\������܂�",
		"�w��̏ꏊ�ɗ���Ɖ摜�̂悤�Ƀ~�b�V������������܂��B\n�Ԃ����ŗ΂̃Q�[�W���~�߂�Ɠ��_�����Z����A\n���Ԃ����ɋ߂��قǍ����_�������܂��B",
		"��ʉ����Ƀ~�b�V�����̑��삪����܂��B\n��Ő������钅���������l�ɉ�ʉ����ɑ��삪����܂��B",
		"�������̐����ł��B\n���Ԑ������ɃK�C�h���ɍ����悤�ɍ��E�L�[�Ŋp�x�𒲐����܂��傤�B\n���ʂɑ΂��Đ����ɋ߂��قǍ����_�ƂȂ�܂��B",
		"���U���g��ʂł͋��Z�̓��_���\������܂��B\n�܂��A���܂łŏ�ʂ�3���_���\������܂�"};
	const int stagemax=6;
	const int SPACE_SIZE_W = 700;
	const int SPACE_SIZE_H = 200;
	const float SPACE_SIZE = 0.5;
};

#endif