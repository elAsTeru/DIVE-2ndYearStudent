#include "Player.h"
#include <math.h>
#define PLAYER_JUMP_POWER			1.5f		// ジャンプ力
#define PLAYER_GRAVITY				0.05f		// 重力
#define PLAYER_X_VELOCITY			0.003f		// x軸ベース速度
#define PLAYER_FALLSPEED_MAX        1.0f		//おちる速度最大
// コンストラクタ
Player::Player()
	: modelHandle(1)
	, animIndex(0)
	, animTotal(0)
	, SpeedFactor(1.0f)
{
	////デバッグ
	debugFont = CreateFontToHandle(NULL, 16, -1, DX_FONTTYPE_NORMAL);
	// ３Ｄモデルの読み込み
	modelHandle = MV1LoadModel("data/mizugi/mizugi.pmx");
	//初期のポーズにセット
	attachAnim(motionWait);
	nowMotionFlame = motionWaitFlame;
	nowMotionPlaySpeed = motionWaitPlaySpeed;
	loopMotionFlag = true;
	//位置初期化
	middlePos = firstMiddlePos;
	pos = middlePos;
	pos.y = middlePos.y - 10;			//-10 することで中心位置から足元の位置にする
	//ラジアン角初期化
	radAdd = firstRad;
	//加速度初期化
	mVelocity = VGet(0.0f, 0.0f, 0.0f);
	//アニメの再生時間を初期化
	animNowTime = 0;
	//プレイヤーの状態を初期化
	state = e_WAIT;
	//ジャンプのフラグの初期化
	jumpFlag = false;
	//入水のフラグ初期化
	entryFlag = false;
	//デバッグ情報を表示するときのフラグの初期化
	debug = false;
	//x軸の加速度設定
	mVelocity.x = PLAYER_X_VELOCITY;
	TitleFont = CreateFontToHandle(NULL, 50, 10);
	//---
	//落下
	//---
	radSpeed = 3.0f;
	swingWidth = radSpeed / 5.3f;
	//degree角
	degree = 0.0f;
	ExpansionRate = 0;
	changeCode = 0.3f;
}

// デストラクタ
Player::~Player()
{
	// モデルのアンロード.
	MV1DeleteModel(modelHandle);
	DeleteFontToHandle(TitleFont);
}


// 描画
void Player::Draw()
{
	// ３Dモデルのポジション設定
	MV1SetPosition(modelHandle, pos);
	// 3Dモデルの回転
	MV1SetRotationXYZ(modelHandle, VGet(firstRotate.x, firstRotate.y, firstRotate.z + radAdd.z));
	// 3Dモデルの描画
	MV1DrawModel(modelHandle);
	
	//VECTOR posi = pos;
	//posi.y += 10;
	// 
	//---
	//デバッグあたり判定.
	//---
	if (debug == true)
	{
		//球の表示
		DrawSphere3D(middlePos, 1.0f, 32, GetColor(255, 0, 0), GetColor(255, 255, 255), TRUE);
		DrawFormatStringToHandle(0, 0, GetColor(0, 0, 0), debugFont,"中心座標_x：%.2f、y：%.2f、z：%.2f", middlePos.x, middlePos.y,middlePos.z);
		DrawFormatStringToHandle(0, 16, GetColor(0, 0, 0), debugFont, "回転値x：%.2f、y：%.2f、z：%.2f", radAdd.x, radAdd.y, degree);
	}
}

void Player::Update()
{
	if (debugPermission == true)
	{
		//デバッグ情報切り替え
		if (CheckHitKey(KEY_INPUT_0) == 1)
		{
			if (debug == false)
			{
				debug = true;
			}
			else if (debug == true)
			{
				debug = false;
			}
		}
		//プレイヤーの位置初期化
		if (CheckHitKey(KEY_INPUT_9) == 1)
		{
			playerInit();
			WaitTimer(500);
		}
	}
	//情報表示
	if (debug == true)
	{
		if (pos.y < 0)
		{
			//フラグを折る
			jumpFlag = false;
			//座標のリセット
			pos.y = 0.0f;
			pos.x = 50.0f;
		}

	}
	//モーションの動きをみるためのデバッグ
	if (state == e_WAIT && debug == true)
	{
		attachAnim(motionWater);
		nowMotionFlame = motionWaterFlame;
		nowMotionPlaySpeed = motionWaterPlaySpeed;
	}
	//待機状態
	else if (state == e_WAIT)
	{
		//待機状態じゃなければ
		attachAnim(motionWait);
		nowMotionFlame = motionWaitFlame;
		nowMotionPlaySpeed = motionWaitPlaySpeed;
		loopMotionFlag = true;
		//次の状態に進める
		if (CheckHitKey(KEY_INPUT_SPACE)&&!nutral)
		{
			if (onNextCheck == true)
			{
				onNextCheck = false;
				animNowTime = 0;
				state = e_RUN;
			}
		}
		else
		{
			onNextCheck = true;
		}
	}
	else if (state == e_RUN)
	{
		if (middlePos.x < runEndPosX)
		{
			middlePos.x += motionRunPlaySpeed / 30.0 + 0.2;
			pos.x += motionRunPlaySpeed / 30.0 + 0.2;
		}
		else
		{
			middlePos.x += nowMotionPlaySpeed / 30 + 0.1;
			pos.x += motionRunPlaySpeed / 30.0 + 0.1;
			middlePos.y += nowMotionPlaySpeed / 30 + 0.2;
			pos.y += motionRunPlaySpeed / 30.0 + 0.2;
		}
		//ジャンプ状態でないかつ上ボタンでジャンプ
		if (CheckHitKey(KEY_INPUT_SPACE) == 1)
		{
			//ジャンプフラグを立てる
			attachAnim(motionRun);
			nowMotionFlame = motionRunFlame;
			nowMotionPlaySpeed = motionRunPlaySpeed;
			loopMotionFlag = false;
		}
		//状態を次に進める
		if (endOf1Lap == true)
		{
			onNextCheck = false;
			state = e_JUMP;
		}
	}
	else if (state == e_JUMP)
	{
		if (middlePos.x < runEndPosX + 30.0f)
		{
			middlePos.x += motionJumpPlaySpeed / static_cast<float>(30) + 0.2f;
			pos.x += motionRunPlaySpeed / 30.0 + 0.2;
		}
		attachAnim(motionJump);
		nowMotionFlame = motionJumpFlame;
		nowMotionPlaySpeed = motionJumpPlaySpeed;
		loopMotionFlag = false;
		if (endOf1Lap == true)
		{
			state = e_FALL;
		}

	}
	else if (state == e_FALL)
	{
	
		if (jumpFlag == false)
		{
			middlePos.x = pos.x = fallPosX;
			jumpFlag = true;
			loopMotionFlag = true;
			attachAnim(motionRota);
			nowMotionFlame = motionRotaFlame;
			nowMotionPlaySpeed = motionRotaPlaySpeed;
			//上方向の加速度にジャンプパワーを代入
			mVelocity.y = PLAYER_JUMP_POWER;
		}
		if(pos.y < 60)
		{
			attachAnim(motionFall);
			nowMotionFlame = motionFallFlame;
			nowMotionPlaySpeed = motionFallPlaySpeed;
			if (degree == 0 || degree == 180)
			{
				middlePos.x = fallPosX;
				pos = middlePos;
			}
		}
		if (pos.y <= 50)
		{
			state = e_ENETRY;
		}
	}
	else if (state == e_ENETRY)
	{
		if (entryFlag == false)
		{
			//jumpFlag = false;		//ジャンプ状態じゃなくして、落下処理が入らないようにする
			//entryFlag = true;
			middlePosDifferencePosX = pos.x - middlePos.x;
			middlePos.x = fallPosX;
			pos.x = middlePos.x + middlePosDifferencePosX;
		}
	}
	//ジャンプ中重力
	jump();
	//縦加速度の代入
	if (middlePos.y > -15)
	{
		middlePos.y += (mVelocity.y / SpeedFactor);
		pos.y += (mVelocity.y / SpeedFactor);
	}
	if (jumpFlag == true )
	{
		//落下処理
		Fall();
	}

	//アニメーション再生関数
	PlayAnim(nowMotionFlame, nowMotionPlaySpeed, loopMotionFlag);
}

void Player::jump()
{
	//ジャンプフラグが立っているかの判定
	if (jumpFlag == true)
	{
		//重力をかける
		mVelocity.y -= PLAYER_GRAVITY;
		if (mVelocity.y <= -PLAYER_FALLSPEED_MAX)
		{
			mVelocity.y = -PLAYER_FALLSPEED_MAX;
		}
	}
	else
	{
		//ジャンプではないとき縦加速度０
		mVelocity.y = 0;
	}
}

/// <summary>
/// モーション再生用
/// </summary>
/// <param name="flameNum">フレーム数</param>
/// <param name="playSpeed">再生速度</param>
/// <param name="loopMotionFlag">ループするか</param>
void Player::PlayAnim(int flameNum, float playSpeed, bool loopMotionFlag)
{
	endOf1Lap = false;
	if (animNowTime > flameNum)
	{
		endOf1Lap = true;
		if (loopMotionFlag == true)
		{
			animNowTime = 0;
		}
	}
	animNowTime += playSpeed;
	MV1SetAttachAnimTime(modelHandle, animIndex, animNowTime);
}


void Player::attachAnim(int animPlay)
{
	//アニメーションがアタッチされていたらデタッチ
	if (animIndex != -1)
	{
		MV1DetachAnim(modelHandle, animIndex);
	}
	//アニメーションをモデルハンドルにアタッチ
	animIndex = MV1AttachAnim(modelHandle, animPlay);
	//アタッチしたアニメの総再生時間を出す
	animTotal = MV1GetAnimTotalTime(modelHandle, animIndex);

}

void Player::playerInit()
{
	//状態初期化
	state = e_WAIT;
	//位置初期化
	//位置初期化
	middlePos = firstMiddlePos;
	pos = middlePos;
	pos.y = middlePos.y - 10;
	//ラジアン角初期化
	radAdd = firstRad;
	//加速度初期化
	mVelocity = VGet(0.0f, 0.0f, 0.0f);
	//アニメの再生時間を初期化
	animNowTime = 0;
	//ジャンプのフラグの初期化
	jumpFlag = false;
	//入水フラグの初期化
	entryFlag = false;
	//x軸の加速度設定
	mVelocity.x = PLAYER_X_VELOCITY;
	radAdd.y = 270;
}

float Player::GetSpeed()
{
	float speed;
	speed = (mVelocity.y / SpeedFactor);
	return speed;
}



void Player::Fall()
{
	//角度が359°を超えたら0にする
	if ((double)radAdd.z * 180.0 / 3.14 >= 359.0 || (double)radAdd.z * 180.0 / 3.14 <= -359.0)
	{
		radAdd.z = 0;
	}
	//脚の座標を中心座標のzを合わせる
	if ((int)radAdd.z >= 360)
	{
		radAdd.z = 0.0f;
		pos.y = middlePos.y - 10;
	}
	if (middlePos.y >= 60.0f)
	{
		//プレイヤーを回転させる
		RotateMiddlePos3DModel(radAdd.z, radSpeed, pos.y, pos.x, swingWidth, true);
	}
	//左右キーを押せるようになる
	if (middlePos.y <= 60.0f && middlePos.y >= 55.0f)
	{
		//プレイヤーを回転させる
		RotateMiddlePos3DModel(radAdd.z, radSpeed / 2, pos.y, pos.x, swingWidth / 2, true);
		if (CheckHitKey(KEY_INPUT_LEFT))
		{
			RotateMiddlePos3DModel(radAdd.z, radSpeed ,pos.y, pos.x, swingWidth, true);
		}
		else if (CheckHitKey(KEY_INPUT_RIGHT))
		{
			RotateMiddlePos3DModel(radAdd.z, radSpeed , pos.y, pos.x, swingWidth, false);
		}
	}
	degree = 180.0 / 3.14 * (double)radAdd.z;
	if (degree < 0)
	{
		degree *= -1;
	}
}

/// <summary>
/// 中心が足元にある3Dモデルを体の中心から回しているように見せる
/// </summary>
/// <param name="_rad">ラジアン角</param>
/// <param name="_radSpeed">回転運動速度</param>
/// <param name="_posSinRotate">SIN回転させるべきモデルの座標</param>
/// <param name="_posCosRotate">COS回転させるべきモデルの座標</param>
/// <param name="_swingWidth">回転移動の振れ幅</param>
/// <param name="_rotateInverse">回転方向を逆転する</param>
void Player::RotateMiddlePos3DModel(float& _rad, const float _radSpeed, float& _posSinRotate, float& _posCosRotate, const float _swingWidth, const bool _rotateInverse)
{
	const float PI = 3.14159265358979323846;	//円周率

	if (_rotateInverse != true)
	{
		//ラジアン角を取得
		_rad += (PI / 180) * _radSpeed / SpeedFactor * 10;
		//円運動
		_posSinRotate += sinf(_rad) * _swingWidth / SpeedFactor * 10;
		_posCosRotate += cosf(_rad) * _swingWidth / SpeedFactor * 10;
	}
	else if (_rotateInverse == true)
	{
		//ラジアン角をとる
		_rad -= (PI / 180) * _radSpeed / SpeedFactor * 10;
		//円運動
		_posSinRotate -= sinf(_rad) * _swingWidth / SpeedFactor * 10;
		_posCosRotate -= cosf(_rad) * _swingWidth / SpeedFactor * 10;
	}
}
