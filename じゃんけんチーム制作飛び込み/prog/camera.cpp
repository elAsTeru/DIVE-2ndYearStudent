#include "Player.h"
#include "Camera.h"


// コンストラクタ
Camera::Camera()
{
	//奥行0.1～1000までをカメラの描画範囲とする
	SetCameraNearFar(4.0f, 1000.0f);

	pos = VGet(0.0f, 0.0f, 0.0f);
	screenPos = VGet(0.0f, 0.0f, 0.0f);
	

	Player* player;

	cameraMoveFlag = false;
}

// デストラクタ
Camera::~Camera()
{
	// 処理なし.
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
			//カメラの初期化
			if (cameraMoveFlag == false)
			{
				cameraMoveFlag = true;										//カメラのを移動中に変更する

				//カメラの位置が変化する前の場所を記憶する-------------------------------------------------------------
				beforePos = pos;											//beforeのpos : 50 -10 0
				//カメラの移動量をセットする
				cameraMoveAmount.x = -50;
				cameraMoveAmount.y = 20;
				cameraMoveAmount.z = 50;
				//カメラの移動先のポジションになるように移動量を足す		//after後のpos : 0 10 50
				afterPos.x = beforePos.x + cameraMoveAmount.x;
				afterPos.y = beforePos.y + cameraMoveAmount.y;
				afterPos.z = beforePos.z + cameraMoveAmount.z;
				//シーンの位置が変化する前の場所を記憶する-------------------------------------------------------------
				beforeScreenPos = screenPos;								//beforeのsceenPos : -30 -10 0
				//スクリーンの移動量をセットする
				screenMoveAmount.x = 30;
				screenMoveAmount.y = 10;
				screenMoveAmount.z = -30;
				//シーンの移動先のポジションになるように移動量を足す		//after後のsceenPos : 0 0 -30
				afterScreenPos.x = beforeScreenPos.x + screenMoveAmount.x;
				afterScreenPos.y = beforeScreenPos.y + screenMoveAmount.y;
				afterScreenPos.z = beforeScreenPos.z + screenMoveAmount.z;

				//カメラとスクリーンの移動回数を初期化する
				if (nowCMoveNum != 0 || nowSMoveNum != 0)
				{
					nowCMoveNum = 0;
					nowSMoveNum = 0;
				}
			}

			if (nowCMoveNum < MoveNumMax)
			{
				movePosCameraOrScreen(pos, cameraMoveAmount, beforePos, afterPos, MoveNumMax, nowCMoveNum);		//カメラの移動
			}
			if (nowSMoveNum < MoveNumMax)
			{
				movePosCameraOrScreen(screenPos, screenMoveAmount, beforeScreenPos, afterScreenPos, MoveNumMax, nowSMoveNum);		//スクリーンの移動
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
//タイトルのカメラ
void Camera::Titlecamera(const Player& player)
{
	pos = VGet(player.middlePos.x - 10.0f, player.middlePos.y, player.middlePos.z - 3);
	screenPos = VGet(player.middlePos.x + 20.0f, player.middlePos.y, player.middlePos.z + 0.0f);
	//ScreenPos = VGet(0.0f, player.GetPos().y + 15.0f, player.GetPos().z + 10.0f);
	SetCameraPositionAndTarget_UpVecY(pos, screenPos);
}

//Gameclear,GameOverで呼び出されるカメラ
void Camera::GameEndCamera(const Player& player)
{

	//x縦後ろ
	//z奥行
	pos = VGet(player.middlePos.x + 20.0f, player.middlePos.y + 5.0, player.middlePos.z + 5.0f);
	screenPos = VGet(player.middlePos.x - 5.0f, player.middlePos.y+5.0, player.middlePos.z - 20.0f);
	//ScreenPos = VGet(0.0f, player.GetPos().y + 15.0f, player.GetPos().z + 10.0f);
	SetCameraPositionAndTarget_UpVecY(pos, screenPos);
}

/// <summary>
/// カメラを移動量を分割して滑らかに移動していく
/// </summary>
/// <param name="_pos">カメラが移動していく量</param>
/// <param name="_moveAmount">移動量</param>
/// <param name="_before">カメラ移動前に位置</param>
/// <param name="_after_">カメラ移動後の位置</param>
/// <param name="_divide">カメラ移動量の分割</param>
/// <param name="_nowMoveNum">現在移動した回数</param>
void Camera::movePosCameraOrScreen(VECTOR& _pos, const VECTOR _moveAmount, const VECTOR _before, const VECTOR _after_, const int _divide, int& _nowMoveNum)
{
	//移動量を分割する
	VECTOR divideMoveAmount = VGet(_moveAmount.x / _divide, _moveAmount.y / _divide, _moveAmount.z / _divide);

	//位置を移動する
	_pos.x += divideMoveAmount.x;
	_pos.y += divideMoveAmount.y;
	_pos.z += divideMoveAmount.z;

	//移動した回数を増やす
	_nowMoveNum++;
}