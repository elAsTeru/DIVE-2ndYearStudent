#pragma once
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

#include"SceneMgr.h"
#include "Player.h"
#include "Camera.h"
#include "bridge.h"
#include "Map.h"
#include "Gauge.h"
#include "slow.h"
#include "pointMng.h"
#include"BGM_SE.h"
#include<string.h>
#include <string>
using namespace std;
class Tutorial
{
public:
	Tutorial();
	~Tutorial();
	void Update();
	void Draw();
	void Load();
	void Delete();
private:
	bool LoadFlag;
	//
	bool deleteFlag;
	int BackGroundTImg;
	int backgroundImg;
	int TG;
	int stage;
	int Tutorial_Line_Img;
	int Tutorial_Box_Img;
	int SpaceImg;
	int sixbox[6];
	int sixboxR[6];
	int TutorialImg[6];
	int TitleFont;
	int textfont;
	int font;
	int Closefont;
	int arrowImg;
	int  arrow;
	int arrowX=50;
	int arrowY=40;
	int arrowMove;
	int x, y;

	int arrowL;
	int arrowR;
	string T_TEXT[6] = {"全体の流れを説明します。１.SPACEを押して飛び込みます。\n２.ミッションをクリアすることで得点が得られます。\n３.飛び込みの角度を調整して水面に垂直になるように着水しましょう",
		"画像の場所にミッションの際の時間制限が表示されます",
		"指定の場所に来ると画像のようにミッションがだされます。\n赤い線で緑のゲージを止めると得点が加算され、\nより赤い線に近いほど高得点が得られます。",
		"画面下部にミッションの操作が現れます。\n後で説明する着水時も同様に画面下部に操作が現れます。",
		"着水時の説明です。\n時間制限内にガイド線に合うように左右キーで角度を調整しましょう。\n水面に対して垂直に近いほど高得点となります。",
		"リザルト画面では競技の得点が表示されます。\nまた、今までで上位の3得点が表示されます"};
	const int stagemax=6;
	const int SPACE_SIZE_W = 700;
	const int SPACE_SIZE_H = 200;
	const float SPACE_SIZE = 0.5;
};

#endif