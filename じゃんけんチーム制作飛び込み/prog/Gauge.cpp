#include "DxLib.h"
#include "Gauge.h"


Gauge::Gauge()
{
	Cr = GetColor(255, 255, 255);
	gCr = GetColor(0, 255, 0);
	mpCr = GetColor(255, 0, 0);
	gaugeYoko = 200;
	nowGauge = 100;
	maxGauge = 100;
	moveGauge = 0;
	Point = 0;
	// 0~100までの数字をランダムに入れる
	
	gaugeUpDown = TRUE;
	pushFlag = FALSE;
}
Gauge::~Gauge()
{

}
void Gauge::Gauge_Draw()
{
	/*DrawFormatString(100, 200, Cr, "最高得点値：%d", maxPoint / 2);
	DrawString(380 +  maxPoint / 2, 200.0f, "↓", Cr);
	DrawBox(380.0f, 250.0f, 380 + moveGauge, 290.0f, gCr, true);
	DrawBoxAA(380.0f, 250.0f, 380 + 200.0f, 290.0f, Cr, FALSE);*/

	/*DrawFormatString(100, 200, Cr, "最高得点値：%d", maxPoint / 2);*/
	//DrawString(Box_Start_X + maxPoint, Box_Start_Y-50, "↓", Cr);

	DrawBox  (Box_Start_X, Box_Start_Y, Box_Start_X + moveGauge, Box_Start_Y + Box_high, gCr, true);
	DrawBoxAA(Box_Start_X, Box_Start_Y, Box_Start_X + maxPoint, Box_Start_Y + Box_high, mpCr, FALSE, 5);
	DrawBoxAA(Box_Start_X, Box_Start_Y, Box_Start_X + Box_width, Box_Start_Y + Box_high, Cr, FALSE, 5);
}
void Gauge::Gauge_Calculation()
{
	if(CheckHitKey(KEY_INPUT_SPACE))
	{
		moveGauge = Box_width * nowGauge / maxGauge;
		pushFlag = TRUE;
	}
	else
	{
		if (pushFlag == FALSE)
		{
			moveGauge = Box_width * nowGauge / maxGauge;

			if (gaugeUpDown == TRUE)
			{
				nowGauge+=speed;
				if (nowGauge >= maxGauge)
				{
					gaugeUpDown = FALSE;
				}
			}
			else
			{
				nowGauge-=speed;
				if (minGauge >= nowGauge)
				{
					gaugeUpDown = TRUE;
				}
			}
		}
	}
}
void Gauge::Gauge_Point()
{
	if (maxPoint > moveGauge && moveGauge > maxPoint - 50 ||
		maxPoint < moveGauge && moveGauge < maxPoint + 50)
	{
		Point = 10;
		if (maxPoint > moveGauge && moveGauge > maxPoint - 30 ||
			maxPoint < moveGauge && moveGauge < maxPoint + 30)
		{
			Point = Point + 20;
			if (maxPoint > moveGauge && moveGauge > maxPoint - 10 ||
				maxPoint < moveGauge && moveGauge < maxPoint + 10)
			{
				Point = Point + 30;
				if (maxPoint == moveGauge)
				{
					Point = Point * 2;
				}
			}
		}
	}
	DrawFormatString(100, 150, Cr, "得点:%d", Point);
}
void Gauge::Gauge_Init()
{
	pushFlag = FALSE;
}

void Gauge::randPointSet()
{
	maxPoint = GetRand(200);
	speed = GetRand(3)+1;
}
