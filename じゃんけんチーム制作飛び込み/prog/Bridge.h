#pragma once

#ifndef _BRIDGE_H_
#define _BRIDGE_H_



#include "DxLib.h"
#include"Player.h"

class Bridge
{
public:
	Bridge();
	virtual ~Bridge();

	void Draw(const VECTOR player_x);
	void Update();

private:

	// 橋のポジション
	VECTOR pos;
	// ゲートのポジション
	VECTOR gPos;
	// スタートのポジション
	VECTOR sPos;
	VECTOR velocity;	//移動力	VECTOR velocity;	

	float move;	        //移動量
	int    bridgeModelHandle;
	int    gateModelHandle;    // ゴールゲート
	int    startModelHandle;   // スタート地点
	int background;
	int backPrintx;
}; 
#endif // !_BRIDGE_H_