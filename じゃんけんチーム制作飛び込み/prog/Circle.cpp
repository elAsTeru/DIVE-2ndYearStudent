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
	// 0~200�܂ł̐����������_���ɓ����
	maxPoint    = GetRand(15) * 10;
	circleScale = TRUE;
	pushFlag = FALSE;
}
Circle::~Circle()
{
}
void Circle::Circle_Draw()
{
	DrawFormatString(100, 150, Cr, "�ō��_:%d", maxPoint);

	// �g�̕\��
	DrawCircleAA(circleCenterPointX, circleCenterPointY, CircleSize, posnum, Cr, FALSE, 5.0f);
	// �~�̕\���i��������
	DrawCircle(circleCenterPointX, circleCenterPointY, moveCircle, cCr, TRUE);
	// ���_�g�̕\��
	DrawCircleAA(circleCenterPointX, circleCenterPointY, maxPoint, posnum, mpCr, FALSE, 5.0f);
}
void Circle::Circle_Calculation()
{
	// �X�y�[�X�L�[�������ꂽ��Q�[�W��~
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

			// �~���ő�l�ɂȂ�܂Ŕ��a�ɉ��Z�A�ő�l�ɂȂ�ƍŏ��l�ɂȂ�܂Ŕ��a�Ɍ��Z
			if (circleScale == TRUE)
			{
				nowCircle++;

				// �~���ő�l�ɂȂ�ƃt���O������
				if (nowCircle >= maxCircle)
				{
					circleScale = FALSE;
				}
			}
			if (circleScale == FALSE)
			{
				nowCircle--;
				// �~���ŏ��l�ɂȂ�ƃt���O�𗧂Ă�
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
	DrawFormatString(100, 150, Cr, "���_:%d", cPoint);
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
	// 0~200�܂ł̐����������_���ɓ����
	maxPoint = GetRand(15) * 10;
	circleScale = TRUE;
	pushFlag = FALSE;
}
