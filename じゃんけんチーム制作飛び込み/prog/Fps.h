#ifndef _FPS_H_
#define _FPS_H_



#include<math.h>
#include"DxLib.h"
class Fps
{
	int mStartTime;         //����J�n����
	int mCount;             //�J�E���^
	float mFps;             //fps
	static const int N = 60;//���ς����T���v����
	static const int FPS = 60;	//�ݒ肵��FPS
public:
	Fps();
	~Fps();
	bool Update();
	void Draw();
	void Wait();

private:

};

#endif // !_FPS_H_
