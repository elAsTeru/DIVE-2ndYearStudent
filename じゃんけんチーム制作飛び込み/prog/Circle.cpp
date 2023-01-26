#include "DxLib.h"
#include "Circle.h"

#define circleCenterPointX 640
#define circleCenterPointY 500
#define posnum 1000            

Circle::Circle()
{
	Cr          = GetColor(255, 255, 255);
	mpCr         = GetColor(255, 0, 0);
	cCr         = GetColor(0, 255, 0);
	CircleSize  = 20;
	nowCircle   = 0;
	maxCircle   = 150;
	minCircle   = 0;
	moveCircle  = 0;
	cPoint      = 0;
	// 0~200までの数字をランダムに入れる
	maxPoint    = GetRand(15) * 10;
	circleScale = TRUE;
	pushFlag = FALSE;
}
Circle::~Circle()
{
}
void Circle::Circle_Draw()
{
	DrawFormatString(100, 150, Cr, "最高点:%d", maxPoint);

	// 枠の表示
	DrawCircleAA(circleCenterPointX, circleCenterPointY, CircleSize, posnum, Cr, FALSE, 5.0f);
	// 円の表示（動く部分
	DrawCircle(circleCenterPointX, circleCenterPointY, moveCircle, cCr, TRUE);
	// 得点枠の表示
	DrawCircleAA(circleCenterPointX, circleCenterPointY, maxPoint, posnum, mpCr, FALSE, 5.0f);
}
void Circle::Circle_Calculation()
{
	// スペースキーが押されたらゲージ停止
	if(CheckHitKey(KEY_INPUT_SPACE))
	{
		moveCircle = CircleSize * nowCircle / maxCircle;
		pushFlag = TRUE;
	}
	else
	{
		if (pushFlag == FALSE)
		{
			moveCircle = CircleSize * nowCircle / maxCircle;

			// 円が最大値になるまで半径に加算、最大値になると最小値になるまで半径に減算
			if (circleScale == TRUE)
			{
				nowCircle++;

				// 円が最大値になるとフラグを下す
				if (nowCircle >= maxCircle)
				{
					circleScale = FALSE;
				}
			}
			if (circleScale == FALSE)
			{
				nowCircle--;
				// 円が最小値になるとフラグを立てる
				if (minCircle >= nowCircle)
				{
					circleScale = TRUE;
				}
			}
		}
	}
}
void Circle::Circle_Point()
{
	if (maxPoint > moveCircle && moveCircle > maxPoint - 50 ||
		maxPoint < moveCircle && moveCircle < maxPoint + 50)
	{
		cPoint = 10;
		if (maxPoint > moveCircle && moveCircle > maxPoint - 30 ||
			maxPoint < moveCircle && moveCircle < maxPoint + 30)
		{
			cPoint = cPoint + 20;
			if (maxPoint > moveCircle && moveCircle > maxPoint - 10 ||
				maxPoint < moveCircle && moveCircle < maxPoint + 10)
			{
				cPoint = cPoint + 30;
				if (maxPoint == moveCircle)
				{
					cPoint = cPoint * 2;
				}
			}
		}
	}
	DrawFormatString(100, 150, Cr, "得点:%d", cPoint);
}
void Circle::Circle_Init()
{
	Cr = GetColor(255, 255, 255);
	mpCr = GetColor(255, 0, 0);
	cCr = GetColor(0, 255, 0);
	CircleSize = 150;
	nowCircle = 0;
	maxCircle = 100;
	minCircle = 0;
	moveCircle = 0;
	cPoint = 0;
	// 0~200までの数字をランダムに入れる
	maxPoint = GetRand(15) * 10;
	circleScale = TRUE;
	pushFlag = FALSE;
}
