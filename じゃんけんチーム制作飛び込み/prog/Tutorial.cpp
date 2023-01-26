#include"Tutorial.h"
#define PI 3.141592654
Tutorial::Tutorial()
{
	LoadFlag = TRUE;
	deleteFlag = FALSE;
	x = 0;
	y = 0;
	arrow = 255;
	arrowMove = 0;
}

Tutorial::~Tutorial()
{
}

void Tutorial::Update()
{
	if (arrow >= 255)
	{
		arrowMove = -5;
	}
	if (arrow <= 120)
	{
		arrowMove = 5;
	}
	arrow += arrowMove;
	if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		if (stage < stagemax-1 )
		{
			stage++;
			WaitTimer(300);
		}
	}
	if (CheckHitKey(KEY_INPUT_LEFT))
	{
		if (0 < stage)
		{
			stage--;
			WaitTimer(300);
		}
	}
	if (CheckHitKey(KEY_INPUT_SPACE))
	{

			SceneMgr_ChangeScene(eScene::eScene_Game);
			deleteFlag = true;
	}
	if (CheckHitKey(KEY_INPUT_A))
	{
		x++;
	}
	if (CheckHitKey(KEY_INPUT_D))
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


}

void Tutorial::Draw()
{
	DrawGraph(0, 0, backgroundImg, false);
	DrawGraph(0, 0, BackGroundTImg, true);
	DrawGraph(0, 0, TG, true);
	DrawExtendGraph(830, 640, 830 + (int)(SPACE_SIZE_W * SPACE_SIZE), 640 + (int)(SPACE_SIZE_H * SPACE_SIZE), SpaceImg, true);
	for (int i = 0; i < stagemax; i++)
	{
		DrawGraph(290 + (i* 60), 645, sixbox[i], true);
		
	}
	DrawFormatStringToHandle(250, 550, GetColor(255, 255, 255), textfont, T_TEXT[stage].c_str());
	DrawGraph(290 + (stage * 60), 645, sixboxR[stage], true);
	DrawGraph(0, 0, TutorialImg[stage], true);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, arrow);
	DrawExtendGraph(690 , 663, 690 + arrowX, 663  + arrowY, arrowL, true);
	DrawExtendGraph(230, 663, 230  + arrowX, 663  + arrowY, arrowR, true);
	
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

	///*z
	//DrawFormatStringToHandle(800, 20.0, GetColor(255, 255, 255), TitleFont, "x:%d", stage);*/
	DrawFormatStringToHandle(1015, 673, GetColor(255, 255, 255), Closefont, "CLOSE");
	//DrawFormatStringToHandle(930, 650, GetColor(255, 255, 255), TitleFont, "%d / 5", stage + 1); 
	//DrawFormatStringToHandle(800, 750, GetColor(255, 255, 255), font, "左キー　戻る");
	//if (stage<3)
	//{
	//	DrawFormatStringToHandle(800, 700, GetColor(255, 255, 255), font, "右キー　進む");
	//}
	//else
	//{
	//	DrawFormatStringToHandle(800, 700, GetColor(255, 255, 255), font, "SPACE ゲームへ");
	//}



}

void Tutorial::Load()
{
	if (LoadFlag)
	{

		BackGroundTImg = LoadGraph("data/img/2021_09_18newTutorial.png");
		SpaceImg = LoadGraph("data/img/スタイリッシュSPACE.png");
		backgroundImg = LoadGraph("data/img/Back.png");
		TG = LoadGraph("data/img/ガイドチュートリアル.png");

		sixbox[0]= LoadGraph("data/img/グループ1.png");
		sixbox[1]= LoadGraph("data/img/グループ2.png");
		sixbox[2]= LoadGraph("data/img/グループ3.png");
		sixbox[3]= LoadGraph("data/img/グループ4.png");
		sixbox[4]= LoadGraph("data/img/グループ5.png");
		sixbox[5]= LoadGraph("data/img/グループ6.png");


		sixboxR[0] = LoadGraph("data/img/赤グループ1.png");
		sixboxR[1] = LoadGraph("data/img/赤グループ2.png");
		sixboxR[2] = LoadGraph("data/img/赤グループ3.png");
		sixboxR[3] = LoadGraph("data/img/赤グループ4.png");
		sixboxR[4] = LoadGraph("data/img/赤グループ5.png");
		sixboxR[5] = LoadGraph("data/img/赤グループ6.png");

		TutorialImg[0] = LoadGraph("data/img/Tutorial/ALL_T.png");
		TutorialImg[1] = LoadGraph("data/img/Tutorial/Time_T.png");;
		TutorialImg[2] = LoadGraph("data/img/Tutorial/Gauge_T.png");
		TutorialImg[3] = LoadGraph("data/img/Tutorial/SOUSA_T.png");
		TutorialImg[4] = LoadGraph("data/img/Tutorial/DIVE_T.png");
		TutorialImg[5] = LoadGraph("data/img/Tutorial/POINT_T.png");
		arrowR = LoadGraph("data/img/left.png");
		arrowL = LoadGraph("data/img/right.png");

		Tutorial_Box_Img = LoadGraph("data/img/mini.png");
		arrowImg = LoadGraph("data/img/miniT.png");
		stage = 0;
		TitleFont = CreateFontToHandle(NULL, 50, 10, DX_FONTTYPE_EDGE, -1, 5, true);
		font = CreateFontToHandle(NULL, 20, 10, DX_FONTTYPE_EDGE, -1, 5, true);
		Closefont = CreateFontToHandle("Impact", 32, 15, DX_FONTTYPE_EDGE, -1, 1, true);
		textfont = CreateFontToHandle(NULL, 20, 2, DX_FONTTYPE_EDGE, -1, 2, true);
		LoadFlag = false;
	}
}

void Tutorial::Delete()
{
	if (deleteFlag)
	{
		DeleteGraph(BackGroundTImg);
		DeleteGraph(backgroundImg);
		DeleteGraph(TG);
		for (int i = 0; i < 6; i++)
		{
			DeleteGraph(sixbox[i]);
			DeleteGraph(sixboxR[i]);
			DeleteGraph(TutorialImg[i]);
		}
		DeleteGraph(arrowL);
		DeleteGraph(arrowR);

		DeleteGraph(Tutorial_Box_Img);
		DeleteFontToHandle(TitleFont);
		DeleteFontToHandle(font);
		DeleteFontToHandle(Closefont);
		DeleteFontToHandle(textfont);
		deleteFlag = false;
		LoadFlag = true;
	}

}
