#include"WaterIn.h"

WaterIn::WaterIn()
{
	right = LoadGraph("data/img/migi.png");
	left = LoadGraph("data/img/hidari.png");
}

WaterIn::~WaterIn()
{
	DeleteGraph(right);
	DeleteGraph(left);
}

int WaterIn::Update()
{
	if (CheckHitKey(KEY_INPUT_LEFT))
	{
		OpRad++;
	}
	if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		OpRad--;
	}
	return OpRad/10;
}

void WaterIn::Draw()
{
}
int WaterIn::getPointRad(int rad)
{
	int point = 0;
	if (rad >= 90 && rad <= 270)
	{
		point = 10;
		if (rad >= 140 && rad <= 230)
		{
			point *= 2;
			if (rad >= 170 && rad <= 190)
			{
				point *= 2;
			}
		}

	}
	return point;
}
void WaterIn::Init()
{
	OpRad=0;
}