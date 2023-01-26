#include "Player.h"
#include "Camera.h"


// �R���X�g���N�^
Camera::Camera()
{
	//���s0.1�`1000�܂ł��J�����̕`��͈͂Ƃ���
	SetCameraNearFar(4.0f, 1000.0f);

	pos = VGet(0.0f, 0.0f, 0.0f);
	screenPos = VGet(0.0f, 0.0f, 0.0f);
	

	Player* player;

	cameraMoveFlag = false;
}

// �f�X�g���N�^
Camera::~Camera()
{
	// �����Ȃ�.
}

void Camera::GetPos(const Player& player, bool jumpflag)
{


	/*if (CheckHitKey(KEY_INPUT_D))
	{
		x++;
	}
	if (CheckHitKey(KEY_INPUT_A))
	{
		x--;
	}
	if (CheckHitKey(KEY_INPUT_W))
	{
		y++;
	}
	if (CheckHitKey(KEY_INPUT_S))
	{
		y--;
	}
	if (CheckHitKey(KEY_INPUT_R))
	{
		z++;
	}
	if (CheckHitKey(KEY_INPUT_F))
	{
		z--;
	}*/
	if (!jumpflag)
	{

		pos = VGet(player.middlePos.x + 20.0f+x, player.middlePos.y+y, player.middlePos.z + -60.0f+z);
		screenPos = VGet(player.middlePos.x + 20.0f+x, player.middlePos.y+y, player.middlePos.z + 0.0f+z);
		//ScreenPos = VGet(0.0f, player.GetPos().y + 15.0f, player.GetPos().z + 10.0f);
		SetCameraPositionAndTarget_UpVecY(pos, screenPos);
	}
	else
	{
		if (player.middlePos.y > 60.0f)
		{

			pos = VGet(player.middlePos.x + 50, player.middlePos.y - 10.0, player.middlePos.z);
			screenPos = VGet(player.middlePos.x - 30, player.middlePos.y-10, player.middlePos.z);
			//ScreenPos = VGet(0.0f, player.GetPos().y + 15.0f, player.GetPos().z + 10.0f);
			SetCameraPositionAndTarget_UpVecY(pos, screenPos);
		}
		else if (player.middlePos.y <= 60.0f && player.middlePos.y > 55.0f)
		{
			//�J�����̏�����
			if (cameraMoveFlag == false)
			{
				cameraMoveFlag = true;										//�J�����̂��ړ����ɕύX����

				//�J�����̈ʒu���ω�����O�̏ꏊ���L������-------------------------------------------------------------
				beforePos = pos;											//before��pos : 50 -10 0
				//�J�����̈ړ��ʂ��Z�b�g����
				cameraMoveAmount.x = -50;
				cameraMoveAmount.y = 20;
				cameraMoveAmount.z = 50;
				//�J�����̈ړ���̃|�W�V�����ɂȂ�悤�Ɉړ��ʂ𑫂�		//after���pos : 0 10 50
				afterPos.x = beforePos.x + cameraMoveAmount.x;
				afterPos.y = beforePos.y + cameraMoveAmount.y;
				afterPos.z = beforePos.z + cameraMoveAmount.z;
				//�V�[���̈ʒu���ω�����O�̏ꏊ���L������-------------------------------------------------------------
				beforeScreenPos = screenPos;								//before��sceenPos : -30 -10 0
				//�X�N���[���̈ړ��ʂ��Z�b�g����
				screenMoveAmount.x = 30;
				screenMoveAmount.y = 10;
				screenMoveAmount.z = -30;
				//�V�[���̈ړ���̃|�W�V�����ɂȂ�悤�Ɉړ��ʂ𑫂�		//after���sceenPos : 0 0 -30
				afterScreenPos.x = beforeScreenPos.x + screenMoveAmount.x;
				afterScreenPos.y = beforeScreenPos.y + screenMoveAmount.y;
				afterScreenPos.z = beforeScreenPos.z + screenMoveAmount.z;

				//�J�����ƃX�N���[���̈ړ��񐔂�����������
				if (nowCMoveNum != 0 || nowSMoveNum != 0)
				{
					nowCMoveNum = 0;
					nowSMoveNum = 0;
				}
			}

			if (nowCMoveNum < MoveNumMax)
			{
				movePosCameraOrScreen(pos, cameraMoveAmount, beforePos, afterPos, MoveNumMax, nowCMoveNum);		//�J�����̈ړ�
			}
			if (nowSMoveNum < MoveNumMax)
			{
				movePosCameraOrScreen(screenPos, screenMoveAmount, beforeScreenPos, afterScreenPos, MoveNumMax, nowSMoveNum);		//�X�N���[���̈ړ�
			}

			//ScreenPos = VGet(0.0f, player.GetPos().y + 15.0f, player.GetPos().z + 10.0f);
			SetCameraPositionAndTarget_UpVecY(pos, screenPos);
		}
		else if (player.middlePos.y <= 55.0f && player.middlePos.y > 40 )
		{
			pos = VGet(player.middlePos.x, player.middlePos.y + 10.0, player.middlePos.z + 50.0f);
			screenPos = VGet(player.middlePos.x, player.middlePos.y, player.middlePos.z - 30.0f);
			//ScreenPos = VGet(0.0f, player.GetPos().y + 15.0f, player.GetPos().z + 10.0f);
			SetCameraPositionAndTarget_UpVecY(pos, screenPos);
		}
	}
}
//�^�C�g���̃J����
void Camera::Titlecamera(const Player& player)
{
	pos = VGet(player.middlePos.x - 10.0f, player.middlePos.y, player.middlePos.z - 3);
	screenPos = VGet(player.middlePos.x + 20.0f, player.middlePos.y, player.middlePos.z + 0.0f);
	//ScreenPos = VGet(0.0f, player.GetPos().y + 15.0f, player.GetPos().z + 10.0f);
	SetCameraPositionAndTarget_UpVecY(pos, screenPos);
}

//Gameclear,GameOver�ŌĂяo�����J����
void Camera::GameEndCamera(const Player& player)
{

	//x�c���
	//z���s
	pos = VGet(player.middlePos.x + 20.0f, player.middlePos.y + 5.0, player.middlePos.z + 5.0f);
	screenPos = VGet(player.middlePos.x - 5.0f, player.middlePos.y+5.0, player.middlePos.z - 20.0f);
	//ScreenPos = VGet(0.0f, player.GetPos().y + 15.0f, player.GetPos().z + 10.0f);
	SetCameraPositionAndTarget_UpVecY(pos, screenPos);
}

/// <summary>
/// �J�������ړ��ʂ𕪊����Ċ��炩�Ɉړ����Ă���
/// </summary>
/// <param name="_pos">�J�������ړ����Ă�����</param>
/// <param name="_moveAmount">�ړ���</param>
/// <param name="_before">�J�����ړ��O�Ɉʒu</param>
/// <param name="_after_">�J�����ړ���̈ʒu</param>
/// <param name="_divide">�J�����ړ��ʂ̕���</param>
/// <param name="_nowMoveNum">���݈ړ�������</param>
void Camera::movePosCameraOrScreen(VECTOR& _pos, const VECTOR _moveAmount, const VECTOR _before, const VECTOR _after_, const int _divide, int& _nowMoveNum)
{
	//�ړ��ʂ𕪊�����
	VECTOR divideMoveAmount = VGet(_moveAmount.x / _divide, _moveAmount.y / _divide, _moveAmount.z / _divide);

	//�ʒu���ړ�����
	_pos.x += divideMoveAmount.x;
	_pos.y += divideMoveAmount.y;
	_pos.z += divideMoveAmount.z;

	//�ړ������񐔂𑝂₷
	_nowMoveNum++;
}