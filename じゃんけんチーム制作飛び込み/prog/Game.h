#pragma once
#ifndef _GAME_H_
#define _GAME_H_


#include "Player.h"
#include "Camera.h"
#include "bridge.h"
#include"Map.h"
#include "Gauge.h"
#include "slow.h"
#include "pointMng.h"
#include"BGM_SE.h"
#include "Fadeout_in.h"


class Game
{
public:
	Game();
	~Game();
	void Rode();
	void Delete();
	void Update(pointMng* pointM);
	void Loop();
	void GameInit();
private:
	//
	bool rodeFlag;
	//
	bool deleteFlag;
	// 各生成
	class Player* player;
	class Camera* camera;
	class Map* map;
	class SLOW* slow;
	class BGMSE* se;
	class Fade* fade;
	int Time;
	int TimeFont;//カウントダウン表示用のフォントサイズ
	int TitleFont;//カウントダウン表示用のフォントサイズ
	int CountDownFont;	//時間制限用のフォントサイズ
	float timerImgExtRate = 0.1f;				//時間制限用画像のサイズ倍率
	float timerImgAngle = 0.0f;			//時間制限用画像の回転
	int RedCode;//赤のカラーコード

	int startCount;//制限時間のカウント開始タイミング
	bool callend = false;
	bool firstCall = false;
	int Description;

	bool ClearFlag=false;//Scene遷移のフラグ

	//スローモードになる位置
	const float STAGE_POS_Y_START[4] = { 175.0f,140.0f,100.0f,60.0f };
	const float STAGE_POS_Y_END[4] = { 174.0f,139.0f ,99.0f ,55.0f };
	int NowStage;//今のいくつ目の課題か
	int WhiteBack;
	int BlackBack;
	int point = 0;
	//一回だけ呼び出したい
	bool oneceagain = true;


	/// <summary>
	/// 変更点＜緒方＞最後のミニゲームの点線画像を入れるハンドル
	/// </summary>
	int lastMiniGameModelHandel;
	

	


};
#endif // !_GAME_H_