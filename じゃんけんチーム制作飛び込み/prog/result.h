#pragma once
//本田
#ifndef _RESULT_H_
#define _RESULT_H_
#include "DxLib.h"
#include "iostream"
#include "vector"
#include "algorithm"
#include "SceneMgr.h"
#include "pointMng.h"
#include "Player.h"
#include "camera.h"
#include "Fadeout_in.h"
class SceneMgr;

class Result
{
public:
	Result();
	~Result();

	void Update();
	void Draw(pointMng* point);

	void Rode();
	void Delete();


private:
	// 読み込みフラグ
	bool rodeFlag;

	class Player* player;
	class Camera* camera;
	class Fade* fade;
	//待機モーション　情報
	const int motionResult = 003;
	const int motionResultFlame = 80;
	const int motionResultPlaySpeed = 0.1f;
	// 削除フラグ
	bool deleteFlag;

	//SPACEキーの画像ハンドル
	int BackgroundImg;
	//画像を拡張する際に使う
	float ExpansionRate;

	//画像を変更する際の変更率
	float changeCode;
	
	//画像の倍率
	float imgSize = 1.0f;
	int GoTitle;
	int SpaceImg;

	int Font;
	int NameFont;
	int newFont;
	int ndFont;
	int rdFont;
	int NumberFont;
	int x = 300;
	int y = 90;
	const int RANKING_DRAW_X = 150;
	const int RANKING_DRAW_Y = 190;

	const int  SPACESIZE_X = 125;
	const int  SPACESIZE_Y = 50;
	const int  STARTSIZE_X = 250;
	const int  STARTSIZE_Y = 50;
	const int  STARTX = 20;
	const int  STARTY = 700;
	//70~720
	//50~170
 
	//ランキングとscoreの表示を切り替える

};



#endif //_RESULT_H_
