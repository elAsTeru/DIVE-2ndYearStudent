#pragma once
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "DxLib.h"

class EnemyBase;

class Player final
{
private:
	const bool debugPermission = true;		//�f�o�b�O�̎g�p�������邩
	bool debug;
	int debugFont;
public:
	Player();						// �R���X�g���N�^.
	~Player();						// �f�X�g���N�^.

	void Draw();					// �`��.
	void Update();
	int TitleFont;

	// ���f���n���h���̎擾.
	int GetModelHandle() { return modelHandle; }

	// �|�W�V������getter/setter.
	const VECTOR& GetPos() const { return middlePos; }
	void SetPos(const VECTOR set) { middlePos = set; }
	void SetPosY(const float set) { middlePos.y = set; }

	void jump();									//�W�����v���Ă鎞�d�͂�������A���n����ƃt���O�֌W�̃��Z�b�g	
	void PlayAnim(int flameNum, float playSpeed, bool loopMotionFlag);								//anime�Đ��p�̊֐�
	void attachAnim(int animPlay);					//�A�j���[�V�����̃A�^�b�`

	void playerInit();								//�v���C���[�̏�Ԃ�������
	bool Getjumpflag() { return jumpFlag; }

	void playerSetVelocity(float SetSpeedFactor) { SpeedFactor = SetSpeedFactor; };

	void playerRadSetter(int Rad) { radAdd.z = Rad; };

	int playerRadGetter() { return (int)degree; };
	int modzelHandleGetter() { return modelHandle; };
	float GetSpeed();
	void nutralFlagON() { nutral = true; };
	void nutralFlagOFF() { nutral = false; };
	//���f���̍��W
	VECTOR	middlePos;				//���S���W
	VECTOR	pos;					//�������W
	float positionY;				// �������Ɏg�p����|�W�V�������̃|�W�V��������v���C���[�̃|�W�V����������
	//���f���̊p�x
	float degree;
	//�����n
	VECTOR  mVelocity;				//�����x
	float SpeedFactor = 1;			//�����邱�Ƃœ��쑬�x��x�{�ɂ���

	//---
	//���[�V�����Đ��p(�Đ����郂�[�V�����̃A�^�b�`�ԍ�)
	//---
	int	  nowMotionFlame;			//���݂̃��[�V�����̃t���[����
	float nowMotionPlaySpeed;		//���݂̃��[�V�����̍Đ����x
	bool  endOf1Lap;				//���[�V������1���������H
	bool  loopMotionFlag;			//���[�V���������[�v���邩
	bool  jumpFlag;					//�W�����v�̃t���O 
	bool  entryFlag;

private:
	bool nutral=false;
	VECTOR Nutral_Num=VGet(1.0f, 1.0f, 1.0f);
	//�摜���g������ۂɎg��
	float ExpansionRate;

	//�摜��ύX����ۂ̕ύX��
	float changeCode;
	int		modelHandle;			// ���f���n���h��,���f���f�[�^���i�[����
	//---
	//�v���C���[�̏��
	//---
	int state;
	enum
	{
		e_WAIT,						//�ҋ@���
		e_RUN,						//��э��ݑO�܂�
		e_JUMP,
		e_FALL,						//��������	
		e_ENETRY,					//����
	};
	bool onNextCheck;				//��Ԃ�i�߂�Ƃ��ɘA���Ői�܂Ȃ��悤�ɂ��邽��
	//---
	//���[�V�����f�[�^�ƘA�����鏈��
	//---
	//---
	//������
	//---
	const VECTOR firstRad = VGet(0.0f, 0.0f, 0.0f);
	const VECTOR firstRotate = VGet(270.0f * DX_PI_F / 180.0f, 270.0f * DX_PI_F / 180.0f, 90.0f * DX_PI_F / 180.0f);
	const VECTOR firstMiddlePos = VGet(-330.0f, 190.0f, 0.0f);
	//---
	//�����Ȃ�
	//---
	const int motion0 = 000;
	const int motion0Flame = 0;
	const float motion0PlaySpeed = 0.0f;
	
	//---
	//�^�C�g���p�ɗp�ӂ��Ă�ҋ@���[�V����
	//---
	const int motionWaitForTitle = 001;
	const int motionWaitForTitleFlame = 126;
	const float motionWaitForTitlePlaySpeed = 0.2f;
	const float addRotaWaitForTitle = 270.0f;
	
	//---
	//�ҋ@
	//---
	const int motionWait = 002;
	const int motionWaitFlame = 80;
	const float motionWaitPlaySpeed = 0.1f;
	
	//---
	//����
	//---
	const int motionRun = 003;
	const int motionRunFlame = 137;
	const int motionRunPlaySpeed = 1;
	const float runEndPosX = -300.0f;		//���蓮��I���ʒu
	const float fallPosX =-225.0f;			//�����n�_
	//---
	//��� 	  
	//---
	const int motionJump = 004;
	const int motionJumpFlame = 18;
	const int motionJumpPlaySpeed = 1;
	
	//---
	//�r�N���X
	//---
	const int motionFall = 005;					//�܂��f�[�^�Ȃ�
	const int motionFallFlame = 1;
	const int motionFallPlaySpeed = 1;

	//---
	//�󒆏c��]
	//---
	const int motionRota = 006;
	const int motionRotaFlame = 1;
	const int motionRotaPlaySpeed = 1;
	void Fall();
	void RotateMiddlePos3DModel(float& rad, const float radSpeed, float& posSinRotate, float& posCosRotate, const float swingWidth, const bool rotateInverse);
	float radSpeed;
	float swingWidth;				//��]�ړ��̕�		���[�V�����ɂ���ĕς��
	VECTOR	radAdd;		//��]�p�̊p�x�̉��Z
	
	//---
	//������ǂ���
	//---
	const int motionWater = 007;
	const int motionWaterFlame = 90;
	const int motionWaterPlaySpeed = 1;
	float middlePosDifferencePosX;		//���S���W�Ƒ������W��x���W��ł̍�

	//---
	//�A�j���[�V����
	//---
	float	animTotal;				//�A�j���[�V�����̑��Đ�����
	float	animNowTime;			//�A�j���[�V�����̌��݂̍Đ�����
	int		animIndex;				//�A�j���[�V�����̃C���f�b�N�X


	/*int playerRad=1;*/
	/*float radTwo = 0;*/
	//�ۑ�

	//�_��
	/*const float minimum_score=0.314f;
	int water_score;
	bool one[3][2] = { false };*/
	/*int stage=0;
	const int stageinterval;*/
};
#endif // !_PLAYER_H_



//10�_��3.14
//0�_��0
//��_������0.314