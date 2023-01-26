#include"pointMng.h"


pointMng::pointMng()
	:LATESTPOINT(0)
{
	for (int i = 0; i < 10; i++)
	{

		PointV.push_back(0);
	}
}

pointMng::~pointMng()
{
}

void pointMng::setPoint(int getpoint)
{
	LATESTPOINT = getpoint;
	PointV.push_back(getpoint);
	std::sort(PointV.begin(), PointV.end(), std::greater<int>{});
}
/// <summary>
/// 順位の取得
/// </summary>
/// <param name="Rank"></ランクに欲しい順位>
/// <returns></returns>
int  pointMng::getRankPoint(int Rank)
{
	return PointV[Rank];
}

int pointMng::LatestRankPoint()
{
	return LATESTPOINT;
}

int pointMng::getVectorSize()
{
	return PointV.size();
}

