#ifndef _FPS_H_
#define _FPS_H_



#include<math.h>
#include"DxLib.h"
class Fps
{
	int mStartTime;         //測定開始時刻
	int mCount;             //カウンタ
	float mFps;             //fps
	static const int N = 60;//平均を取るサンプル数
	static const int FPS = 60;	//設定したFPS
public:
	Fps();
	~Fps();
	bool Update();
	void Draw();
	void Wait();

private:

};

#endif // !_FPS_H_
