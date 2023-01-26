#include "slow.h"

SLOW::SLOW()
	:lastMissionFlag(false)
{
	TitleFont = CreateFontToHandle(NULL, 50, 10, DX_FONTTYPE_EDGE, -1, 5, true);
	SpaceImg = LoadGraph("data/img/UI_BASE.png");
	LoadDivGraph("data/img/clock.png",12,12,1,375,432,CLOCKIMG);
	UiImg[0] = LoadGraph("data/img/UI_BASE.png");
	UiImg[1] = LoadGraph("data/img/UI_SPACE.png");
	UiImg[2] = LoadGraph("data/img/HUD1.png");
}

SLOW::~SLOW()
{
	DeleteGraph(SpaceImg);
	DeleteFontToHandle(TitleFont);
}

void SLOW::SlowMode_Update(Player* player,int stage)
{
	
	if (!beforeSlowFlag&&SlowFlag)
	{
		player->playerSetVelocity(500.0f);
		speed = player->GetSpeed();
		startTime = GetNowCount();
		player->SetPosY(STAGE_POS_Y_START[stage]);
		EndTime=(int)(distance / -(speed*60));
	}
	else if (lastMissionFlag)
	{
		EndTime = (int)(Lastdistance / -(speed * 60));
	}
	time= (GetNowCount() - startTime) / 1000;

	if (SlowFlag&&!lastMissionFlag)
	{
		
		if (stage%2==0)
		{

			gauge->Gauge_Calculation();
			gauge->Gauge_Point();
			
			point = gauge->Gauge_point_get();
			if (gauge->GetputKey())
			{
				SlowFlag = false;
				WaitTimer(100);
			}
		}
		else
		{
			circle->Circle_Calculation();
			circle->Circle_Point();
			
			point = circle->Getpoint();
			if (circle->GetputKey())
			{
				SlowFlag = false;
				WaitTimer(100);
			}
		}
	}
	else if (SlowFlag && lastMissionFlag)
	{
		player->playerSetVelocity(100.0f);
		//player->playerRadSetter((float)water->Update());
		point =water->getPointRad(player->playerRadGetter());
	}
	if (!SlowFlag)
	{
		if (beforeSlowFlag!=SlowFlag&&!lastMissionFlag)
		{
			gauge->Gauge_Init();
			circle->Circle_Init();
			//player->playerRadSetter(sum);
		}
		player->playerSetVelocity(1.0f);
		gauge->randPointSet();
		
	}
	beforeSlowFlag = SlowFlag;
}

void SLOW::SlowMode_Draw(int Stage)
{
	////DrawFormatStringToHandle(x, y, GetColor(255, 255, 255), TitleFont, "SCORE :%d", point);
	
	if (SlowFlag)
	{
		DrawGraph(680, 600, SpaceImg, true);
		
		DrawExtendGraph(UIBASE_X, UIBASE_Y, UIBASE_X+UIBASE_SIZE_X, UIBASE_Y+UIBASE_SIZE_Y, UiImg[0], true);
		DrawExtendGraph(CLOCK_X, CLOCK_Y, CLOCK_X + Clock_SIZE_X, CLOCK_Y + Clock_SIZE_Y, CLOCKIMG[0], true);
		DrawFormatStringToHandle(CLOCK_X + Clock_SIZE_X + 20, CLOCK_Y + 20, GetColor(255, 255, 255), TitleFont, "%d", EndTime - time);
	}
	if (SlowFlag && !lastMissionFlag)
	{
		if (Stage%2==0)
		{

			gauge->Gauge_Draw();
			DrawGraph(600, 600, UiImg[1], true);
		}
		else
		{
			circle->Circle_Draw();
			DrawGraph(600, 600, UiImg[1], true);
		}
	}
	else if (SlowFlag &&   lastMissionFlag)
	{
		DrawRotaGraph(100,  700, 1, 0, UiImg[0], 1, 1, 1);

		DrawRotaGraph(680+350,600+100,1,0,UiImg[2],1);
		DrawRotaGraph(680+-500, 600+90, 1, 0, UiImg[2], 1,1,1);

	}
	//DrawFormatStringToHandle(800, 100, GetColor(255, 255, 255), TitleFont, "x:%d", x);
	//DrawFormatStringToHandle(800, 150, GetColor(255, 255, 255), TitleFont, "x:%d", y);
}

bool SLOW::returnSlowFlag()
{
	return SlowFlag;
}

void SLOW::Init()
{
	water->Init();
	lastMissionFlag = false;
	SlowFlag = false;
}
