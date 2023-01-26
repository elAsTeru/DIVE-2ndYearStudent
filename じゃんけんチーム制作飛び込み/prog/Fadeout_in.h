#pragma once
#include"DxLib.h"
class Fade
{
public:
	Fade();
	~Fade();
	//fadeout
	bool GetFadeoutEndFlag();//fadeout���I����������t���O�ŕԂ�
	void DrawFadeOut();
	//fadein
	bool GetFadeinEndFlag();//fadein���I����������t���O�ŕԂ�
	void DrawFadein();

	void OutChange();//�t�F�[�h�J�n���}
	void InChange();//�t�F�[�h�J�n���}

	void SetChangeScene() { changeScene = true; };//�t�F�[�h�J�n���}
	void SetinScene() { inScene = true; };//�t�F�[�hin�J�n���}
private:
	int WhiteImg;//���C���[�W�̃t�F�[�h�A�E�g�p�摜
	int BlackImg;//���C���[�W�̃t�F�[�h�A�E�g�p�摜
	const int EndNumMax=255;//�t�F�[�h�A�E�g�̍ۂ̐��l���E
	const int EndNumMin = 0;//�t�F�[�h�A�E�g�̍ۂ̐��l���E
	int fadeoutNum;//�t�F�[�h�A�E�g�p�ϐ�
	int fadeinNum;//�t�F�[�h�C���p�ϐ�
	bool changeScene;
	bool inScene;
	const int fadeSpeed;//�f�t�H���g��4
};

