#pragma once
#include"DxLib.h"
#include"Player.h"

#ifndef _WATERIN_H_
#define _WATERIN_H_

class WaterIn
{
public:
	WaterIn();
	~WaterIn();

	int Update();
	void Draw();
	int getPointRad(int rad);
	void Init();
private:
	int OpRad=0;
	int right;
	int left;
};

#endif // !_WATERIN_H_
