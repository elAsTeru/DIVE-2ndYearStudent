#pragma once
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "DxLib.h"

class EnemyBase;

class Player final
{
private:
	const bool debugPermission = true;		//デバッグの使用を許可するか
	bool debug;
	int debugFont;
public:
	Player();						// コンストラクタ.
	~Player();						// デストラクタ.

	void Draw();					// 描画.
	void Update();
	int TitleFont;

	// モデルハンドルの取得.
	int GetModelHandle() { return modelHandle; }

	// ポジションのgetter/setter.
	const VECTOR& GetPos() const { return middlePos; }
	void SetPos(const VECTOR set) { middlePos = set; }
	void SetPosY(const float set) { middlePos.y = set; }

	void jump();									//ジャンプしてる時重力をかける、着地するとフラグ関係のリセット	
	void PlayAnim(int flameNum, float playSpeed, bool loopMotionFlag);								//anime再生用の関数
	void attachAnim(int animPlay);					//アニメーションのアタッチ

	void playerInit();								//プレイヤーの状態を初期化
	bool Getjumpflag() { return jumpFlag; }

	void playerSetVelocity(float SetSpeedFactor) { SpeedFactor = SetSpeedFactor; };

	void playerRadSetter(int Rad) { radAdd.z = Rad; };

	int playerRadGetter() { return (int)degree; };
	int modzelHandleGetter() { return modelHandle; };
	float GetSpeed();
	void nutralFlagON() { nutral = true; };
	void nutralFlagOFF() { nutral = false; };
	//モデルの座標
	VECTOR	middlePos;				//中心座標
	VECTOR	pos;					//足元座標
	float positionY;				// 落下時に使用するポジションこのポジションからプレイヤーのポジションをだす
	//モデルの角度
	float degree;
	//処理系
	VECTOR  mVelocity;				//加速度
	float SpeedFactor = 1;			//かけることで動作速度をx倍にする

	//---
	//モーション再生用(再生するモーションのアタッチ番号)
	//---
	int	  nowMotionFlame;			//現在のモーションのフレーム数
	float nowMotionPlaySpeed;		//現在のモーションの再生速度
	bool  endOf1Lap;				//モーションが1周したか？
	bool  loopMotionFlag;			//モーションをループするか
	bool  jumpFlag;					//ジャンプのフラグ 
	bool  entryFlag;

private:
	bool nutral=false;
	VECTOR Nutral_Num=VGet(1.0f, 1.0f, 1.0f);
	//画像を拡張する際に使う
	float ExpansionRate;

	//画像を変更する際の変更率
	float changeCode;
	int		modelHandle;			// モデルハンドル,モデルデータを格納する
	//---
	//プレイヤーの状態
	//---
	int state;
	enum
	{
		e_WAIT,						//待機状態
		e_RUN,						//飛び込み前まで
		e_JUMP,
		e_FALL,						//落下処理	
		e_ENETRY,					//着水
	};
	bool onNextCheck;				//状態を進めるときに連続で進まないようにするため
	//---
	//モーションデータと連動する処理
	//---
	//---
	//初期化
	//---
	const VECTOR firstRad = VGet(0.0f, 0.0f, 0.0f);
	const VECTOR firstRotate = VGet(270.0f * DX_PI_F / 180.0f, 270.0f * DX_PI_F / 180.0f, 90.0f * DX_PI_F / 180.0f);
	const VECTOR firstMiddlePos = VGet(-330.0f, 190.0f, 0.0f);
	//---
	//動きなし
	//---
	const int motion0 = 000;
	const int motion0Flame = 0;
	const float motion0PlaySpeed = 0.0f;
	
	//---
	//タイトル用に用意してる待機モーション
	//---
	const int motionWaitForTitle = 001;
	const int motionWaitForTitleFlame = 126;
	const float motionWaitForTitlePlaySpeed = 0.2f;
	const float addRotaWaitForTitle = 270.0f;
	
	//---
	//待機
	//---
	const int motionWait = 002;
	const int motionWaitFlame = 80;
	const float motionWaitPlaySpeed = 0.1f;
	
	//---
	//走り
	//---
	const int motionRun = 003;
	const int motionRunFlame = 137;
	const int motionRunPlaySpeed = 1;
	const float runEndPosX = -300.0f;		//走り動作終了位置
	const float fallPosX =-225.0f;			//落下地点
	//---
	//飛び 	  
	//---
	const int motionJump = 004;
	const int motionJumpFlame = 18;
	const int motionJumpPlaySpeed = 1;
	
	//---
	//腕クロス
	//---
	const int motionFall = 005;					//まだデータなし
	const int motionFallFlame = 1;
	const int motionFallPlaySpeed = 1;

	//---
	//空中縦回転
	//---
	const int motionRota = 006;
	const int motionRotaFlame = 1;
	const int motionRotaPlaySpeed = 1;
	void Fall();
	void RotateMiddlePos3DModel(float& rad, const float radSpeed, float& posSinRotate, float& posCosRotate, const float swingWidth, const bool rotateInverse);
	float radSpeed;
	float swingWidth;				//回転移動の幅		モーションによって変わる
	VECTOR	radAdd;		//回転用の角度の加算
	
	//---
	//着水後どうさ
	//---
	const int motionWater = 007;
	const int motionWaterFlame = 90;
	const int motionWaterPlaySpeed = 1;
	float middlePosDifferencePosX;		//中心座標と足元座標のx座標上での差

	//---
	//アニメーション
	//---
	float	animTotal;				//アニメーションの総再生時間
	float	animNowTime;			//アニメーションの現在の再生時間
	int		animIndex;				//アニメーションのインデックス


	/*int playerRad=1;*/
	/*float radTwo = 0;*/
	//保存

	//点数
	/*const float minimum_score=0.314f;
	int water_score;
	bool one[3][2] = { false };*/
	/*int stage=0;
	const int stageinterval;*/
};
#endif // !_PLAYER_H_



//10点が3.14
//0点が0
//一点あたり0.314