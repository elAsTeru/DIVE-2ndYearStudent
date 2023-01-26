#include "DxLib.h"
#include "SceneMgr.h"
#include"Fps.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	// ＤＸライブラリ初期化処理
	if (DxLib_Init() == -1)
	{
		return -1;	// エラーが起きたら直ちに終了
	}

	// 画面モードのセット
	SetGraphMode(1280, 800, 16);
	// ウィンドウモード表示
	ChangeWindowMode(true);
	// 描画先画面を裏画面にする
	SetDrawScreen(DX_SCREEN_BACK);

	SceneMgr* sceneMgr = new SceneMgr();
	Fps fps;
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0 && ClearDrawScreen() == 0)
	{
		fps.Update();

		sceneMgr->SceneMgr_Update();  //更新
		sceneMgr->SceneMgr_Draw();    //描画
		/*fps.Draw();*/

		fps.Wait();
	}

	// ＤＸライブラリの後始末
	DxLib_End();
	// ソフトの終了
	return 0;

}