#pragma once
#ifndef _POINT_H_
#define _POINT_H_
#include"DxLib.h"
#include"iostream"
#include"vector"
#include"algorithm"

class pointMng
{
public:
	pointMng();
	~pointMng();
	void setPoint(int getpoint);
	int getRankPoint(int Rank);
	int LatestRankPoint();//最新のポイント取得
	int getVectorSize();
private:
	std::vector<int> PointV = {0};
	int LATESTPOINT;
	int Font;
};
#endif //_POINT_H_
