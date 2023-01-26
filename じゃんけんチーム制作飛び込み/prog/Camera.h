#pragma once
#ifndef _CAMERA_H_
#define _CAMERA_H_
#include "DxLib.h"

class Player;

class Camera
{
public:
	Camera();							// コンストラクタ.
	~Camera();							// デストラクタ.

	// ポジションの取得
	void GetPos(const Player& player,bool jumpflag);
	void Titlecamera(const Player& player);
	void GameEndCamera(const Player& player);
private:
	VECTOR	pos;			// ポジション
	VECTOR  screenPos;
	int switchNum;
	VECTOR neopos;
	VECTOR neoScreenPos;
	bool one=false;
	int x=0;
	int y=0;
	int z=0;

	bool cameraMoveFlag;		//カメラが移動中か
	//カメラの移動
	VECTOR beforePos;
	VECTOR afterPos;
	//カメラの移動量
	VECTOR cameraMoveAmount;
	//現在のカメラの移動回数
	int nowCMoveNum;

	//シーンの移動
	VECTOR beforeScreenPos;
	VECTOR afterScreenPos;
	//スクリーンの移動量
	VECTOR screenMoveAmount;
	//現在のスクリーンの移動回数
	int nowSMoveNum;

	//移動回数の最大値
	const int MoveNumMax = 10;
	//カメラ,スクリーンを滑らかに移動するための関数
	void movePosCameraOrScreen(VECTOR& _pos, const VECTOR _moveAmount, const VECTOR _before, const VECTOR _after_, const int _divide, int& _nowMoveNum);
};
#endif // !_CAMERA_H_