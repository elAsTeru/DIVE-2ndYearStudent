#pragma once
#ifndef _TITLE_H_
#define _TITLE_H_
#include "TitleCamera.h"
#include "Map.h"
#include"Fadeout_in.h"
class Title
{
public:
	Title();
	~Title();
	void Rode();
	/*
	@fn Rode();
	@brief �f�[�^��ǂݍ���
	*/

	void Delete();
	/*
	@fn Delete();
	@brief ���I�ȃf�[�^�̊J��
	*/

	void Update();
	/*
	@fn Update();
	@brief �t���[�����ƂɍX�V������e
	*/

	void Draw();
	/*
	@fn Draw()
	@brief �`��
	*/
private:
	// �ǂݍ��݃t���O
	bool rodeFlag;

	// �폜�t���O
	bool deleteFlag;

	//SPACE�L�[�̉摜�n���h��
	int SPACEImg;

	//GAMESTART�̉摜�n���h��
	int GAMESTARTimg;

	//�摜���g������ۂɎg��
	float ExpansionRate;

	//�摜��ύX����ۂ̕ύX��
	float changeCode;

	//�摜�̔{��
	float imgSize = 1.0f;

	int background;

	class TitleCamera* camera;
	class Map* map ;
	class Fade* fade;
	
	const int  SPACESIZE_X = 125;
	const int  SPACESIZE_Y = 50;
	const int  STARTSIZE_X = 250;
	const int  STARTSIZE_Y = 50;
	const int  STARTX = 600;
	int TitleImg;
};
#endif // !_TITLE_H_
