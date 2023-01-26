#pragma once
#ifndef _CAMERA_H_
#define _CAMERA_H_
#include "DxLib.h"

class Player;

class Camera
{
public:
	Camera();							// �R���X�g���N�^.
	~Camera();							// �f�X�g���N�^.

	// �|�W�V�����̎擾
	void GetPos(const Player& player,bool jumpflag);
	void Titlecamera(const Player& player);
	void GameEndCamera(const Player& player);
private:
	VECTOR	pos;			// �|�W�V����
	VECTOR  screenPos;
	int switchNum;
	VECTOR neopos;
	VECTOR neoScreenPos;
	bool one=false;
	int x=0;
	int y=0;
	int z=0;

	bool cameraMoveFlag;		//�J�������ړ�����
	//�J�����̈ړ�
	VECTOR beforePos;
	VECTOR afterPos;
	//�J�����̈ړ���
	VECTOR cameraMoveAmount;
	//���݂̃J�����̈ړ���
	int nowCMoveNum;

	//�V�[���̈ړ�
	VECTOR beforeScreenPos;
	VECTOR afterScreenPos;
	//�X�N���[���̈ړ���
	VECTOR screenMoveAmount;
	//���݂̃X�N���[���̈ړ���
	int nowSMoveNum;

	//�ړ��񐔂̍ő�l
	const int MoveNumMax = 10;
	//�J����,�X�N���[�������炩�Ɉړ����邽�߂̊֐�
	void movePosCameraOrScreen(VECTOR& _pos, const VECTOR _moveAmount, const VECTOR _before, const VECTOR _after_, const int _divide, int& _nowMoveNum);
};
#endif // !_CAMERA_H_