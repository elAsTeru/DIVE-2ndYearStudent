#include "Result.h"


Result::Result()
{
	rodeFlag = TRUE;
	deleteFlag = FALSE;
	Font     = CreateFontToHandle("Impact", 30, 5 ,DX_FONTTYPE_EDGE, -1, 2, true);
	newFont  = CreateFontToHandle("Impact", 100, 10, DX_FONTTYPE_EDGE,-1,5,true);
	ndFont   = CreateFontToHandle("Impact", 90, 10,DX_FONTTYPE_EDGE, -1, 5, true);
	rdFont   = CreateFontToHandle("Impact", 80, 10,DX_FONTTYPE_EDGE, -1, 5, true);
	NameFont = CreateFontToHandle(NULL, 70, 10);
}

Result::~Result()
{



}


void Result::Update()
{

	///*if (CheckHitKey(KEY_INPUT_LEFT))
	//{
	//	x++;
	//}
	//if (CheckHitKey(KEY_INPUT_RIGHT))
	//{
	//	x--;
	//}
	//if (CheckHitKey(KEY_INPUT_UP))
	//{
	//	y++;
	//}
	//if (CheckHitKey(KEY_INPUT_DOWN))
	//{
	//	y--;
	//}*/
	ExpansionRate += changeCode;
	if (ExpansionRate >= 3)
	{
		changeCode = -0.3f;
	}
	if (ExpansionRate < 0)
	{
		changeCode = 0.3f;
	}
	player->Update();
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		fade->SetChangeScene();
	}
	if (fade->GetFadeoutEndFlag())
	{
		SceneMgr_ChangeScene(eScene_Title);
		deleteFlag = true;
	}
	/*player->PlayAnim(player->nowMotionFlame, player->nowMotionPlaySpeed, player->loopMotionFlag);*/
}

void Result::Draw(pointMng* point)
{
	int MAX_RANK = 10;
	DrawExtendGraph(0, 0, 1280, 800, BackgroundImg, true);
	

	camera->GameEndCamera(*player);
	player->Draw();

	
	DrawFormatStringToHandle(600, 180, GetColor(255, 255, 255), newFont, "pt");
	DrawFormatStringToHandle(325, 178, GetColor(255, 255, 255), newFont, "%4d", point->getRankPoint(0));

	DrawFormatStringToHandle(613+5, 337, GetColor(255, 255, 255), ndFont, "pt");
	DrawFormatStringToHandle(368, 336, GetColor(255, 255, 255), ndFont, "%4d", point->getRankPoint(1));

	DrawFormatStringToHandle(622 + 10, 478, GetColor(255, 255, 255), rdFont, "pt");
	DrawFormatStringToHandle(402, 473, GetColor(255, 255, 255), rdFont, "%4d", point->getRankPoint(2));

	DrawFormatStringToHandle(930, 650, GetColor(255, 255, 255), newFont, "pt");
	DrawFormatStringToHandle(660, 650, GetColor(255, 255, 255), newFont, "%4d", point->LatestRankPoint());
	/*DrawExtendGraph(x,y,x+150+ ExpansionRate,y+50+ ExpansionRate, SpaceImg, false);*/
	DrawExtendGraph(STARTX - (int)ExpansionRate, STARTY - (int)ExpansionRate, STARTX + (SPACESIZE_X) + (int)ExpansionRate, STARTY + (SPACESIZE_Y) + (int)ExpansionRate, SpaceImg,false);
	DrawFormatStringToHandle(160, 700, GetColor(255, 255, 255), Font, "NEXT");
	//DrawExtendGraph(STARTX + 50 + (SPACESIZE_X * imgSize), STARTY, STARTX + 50 + (SPACESIZE_X * imgSize) + (STARTSIZE_X * imgSize), STARTY + (STARTSIZE_Y * imgSize), GoTitle, true);
	//SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)ExpansionRate * 30);
	//DrawBox(STARTX + 50 + (SPACESIZE_X * imgSize), STARTY, STARTX + 50 + (SPACESIZE_X * imgSize) + (STARTSIZE_X * imgSize), STARTY + (STARTSIZE_Y * imgSize), GetColor(255, 255, 0), true);
	//SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	/*DrawFormatStringToHandle(800, 100, GetColor(0, 0, 0), Font, "x:%d", x);
	DrawFormatStringToHandle(800, 150, GetColor(0, 0, 0), Font, "y:%d", y);*/


	fade->DrawFadein();
	fade->DrawFadeOut();
}

void Result::Rode()
{
	if (rodeFlag == TRUE)
	{
		ExpansionRate = 0;
		changeCode = 0.3f;
		BackgroundImg = LoadGraph("data/img/リザルト2.png");
		SpaceImg = LoadGraph("data/img/SPACEキー1.png");
		GoTitle = LoadGraph("data/img/たいとる.png");
		
		player = new Player;
		//待機モーション
		player->attachAnim(motionResult);
		player->nowMotionFlame = motionResultFlame;
		player->nowMotionPlaySpeed = motionResultPlaySpeed;
		camera = new Camera;
		fade = new Fade;
		rodeFlag = FALSE;
		Font = CreateFontToHandle(NULL, 50, 10);
		newFont = CreateFontToHandle("Impact", 100, 10, DX_FONTTYPE_EDGE, -1, 5, true);
		ndFont = CreateFontToHandle("Impact", 90, 10, DX_FONTTYPE_EDGE, -1, 5, true);
		rdFont = CreateFontToHandle("Impact", 80, 10, DX_FONTTYPE_EDGE, -1, 5, true);
		NameFont = CreateFontToHandle(NULL, 70, 10);
		fade->SetinScene();
		player->nutralFlagON();
	}
}

void Result::Delete()
{
	if (deleteFlag == TRUE)
	{
		delete(player);
		delete(camera);
		delete(fade);
		DeleteGraph(BackgroundImg);
		DeleteGraph(GoTitle);
		DeleteGraph(SpaceImg);
		// フォントの削除
		DeleteFontToHandle(Font);
		DeleteFontToHandle(newFont);
		DeleteFontToHandle(ndFont);
		DeleteFontToHandle(rdFont);
		DeleteFontToHandle(NameFont);
			
			
			



		rodeFlag = TRUE;
		deleteFlag = FALSE;

	}
}
