#include "Fadeout_in.h"

Fade::Fade()
	:fadeoutNum(0)
	,fadeinNum(255)
	, changeScene(false)
	,fadeSpeed(4)
{
	WhiteImg = LoadGraph("data/img/whiteback.png");
	BlackImg = LoadGraph("data/img/blackback.png");
}

Fade::~Fade()
{
	DeleteGraph(WhiteImg);
	DeleteGraph(BlackImg);
}

bool Fade::GetFadeoutEndFlag()
{

	if (fadeoutNum>=EndNumMax)
	{
		return true;
	}
	return false;
}

void Fade::DrawFadeOut()
{
	OutChange();//フラグが入れば画面変化開始

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeoutNum);
	DrawGraph(0, 0, WhiteImg, true);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

bool Fade::GetFadeinEndFlag()
{
	
	if (fadeinNum <= EndNumMin)
	{
		
		return true;
	}
	return false;
}

void Fade::DrawFadein()
{
	InChange();//フラグが入れば画面変化開始
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeinNum);
	DrawGraph(0, 0, WhiteImg, true);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

void Fade::OutChange()
{
	if (changeScene)
	{
		fadeoutNum += fadeSpeed;

	}
}

void Fade::InChange()
{
	if (inScene)
	{
		fadeinNum -= fadeSpeed;

	}
}