#pragma once
#include"DxLib.h"
class Fade
{
public:
	Fade();
	~Fade();
	//fadeout
	bool GetFadeoutEndFlag();//fadeoutが終わったかをフラグで返す
	void DrawFadeOut();
	//fadein
	bool GetFadeinEndFlag();//fadeinが終わったかをフラグで返す
	void DrawFadein();

	void OutChange();//フェード開始合図
	void InChange();//フェード開始合図

	void SetChangeScene() { changeScene = true; };//フェード開始合図
	void SetinScene() { inScene = true; };//フェードin開始合図
private:
	int WhiteImg;//白イメージのフェードアウト用画像
	int BlackImg;//黒イメージのフェードアウト用画像
	const int EndNumMax=255;//フェードアウトの際の数値限界
	const int EndNumMin = 0;//フェードアウトの際の数値限界
	int fadeoutNum;//フェードアウト用変数
	int fadeinNum;//フェードイン用変数
	bool changeScene;
	bool inScene;
	const int fadeSpeed;//デフォルトで4
};

