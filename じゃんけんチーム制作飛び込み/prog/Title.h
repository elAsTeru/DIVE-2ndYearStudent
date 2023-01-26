#pragma once
#ifndef _TITLE_H_
#define _TITLE_H_
#include "TitleCamera.h"
#include "Map.h"
#include"Fadeout_in.h"
class Title
{
public:
	Title();
	~Title();
	void Rode();
	/*
	@fn Rode();
	@brief データを読み込む
	*/

	void Delete();
	/*
	@fn Delete();
	@brief 動的なデータの開放
	*/

	void Update();
	/*
	@fn Update();
	@brief フレームごとに更新する内容
	*/

	void Draw();
	/*
	@fn Draw()
	@brief 描画
	*/
private:
	// 読み込みフラグ
	bool rodeFlag;

	// 削除フラグ
	bool deleteFlag;

	//SPACEキーの画像ハンドル
	int SPACEImg;

	//GAMESTARTの画像ハンドル
	int GAMESTARTimg;

	//画像を拡張する際に使う
	float ExpansionRate;

	//画像を変更する際の変更率
	float changeCode;

	//画像の倍率
	float imgSize = 1.0f;

	int background;

	class TitleCamera* camera;
	class Map* map ;
	class Fade* fade;
	
	const int  SPACESIZE_X = 125;
	const int  SPACESIZE_Y = 50;
	const int  STARTSIZE_X = 250;
	const int  STARTSIZE_Y = 50;
	const int  STARTX = 600;
	int TitleImg;
};
#endif // !_TITLE_H_
