#include "DxLib.h"
#include "SceneMgr.h"

SceneMgr::SceneMgr()
    :SoundFlag(false)
{
    loadImgX = 600;
    loadImgY = 470;
    flameCounter = 0;
    game = new Game;
    title = new Title;
    result = new Result;
    point = new pointMng;
    tutorial = new Tutorial;
    //SpaceImg = LoadGraph("data/img/SPACEキー1.png");
    //loadImg[0] = LoadGraph("data/img/1.png");
    //loadImg[1] = LoadGraph("data/img/2.png");
    //loadImg[2] = LoadGraph("data/img/4.png");
    waitImg = LoadGraph("data/img/LOADING.png");


}
SceneMgr::~SceneMgr()
{
    delete(game);
    delete(title);
    delete(result);
    delete(point);
    DeleteGraph(waitImg);
}

//更新
void SceneMgr::SceneMgr_Update() 
{
    //前のSceneを保存
    BackScene = Scene;

    if (SoundFlag == false)
    {
        sound->SoundBGM(Scene);
        //音を鳴らしてフラグを立てる
        SoundFlag = true;
    }
    //シーンによって処理を分岐
    //現在の画面がメニューなら
    //メニュー画面の更新処理をする
    //以下略
    switch (Scene) {
    case eScene_Title:
        title->Rode();
        title->Update();
        title->Delete();
        break;

    case eScene_Tutorial:
        tutorial->Load();
        tutorial->Update();
        tutorial->Delete();
        break;


    case eScene_Game:
        game->Rode();
        game->Update(point);
        game->Delete();
        break;


    case eScene_GameClear:
        result->Rode();
        result->Update();
        result->Delete();
        break;
    }


    //入力を止めるために0.5秒時間を挟む
    if (BackScene!=Scene)
    {  
        SoundFlag = false;
        DrawGraph(0, 0, waitImg, false);
        ScreenFlip();
        WaitTimer(500);
        
    }
}

//描画
void SceneMgr::SceneMgr_Draw() {
    switch (Scene) {  
    case eScene_Title:
        title->Rode();
        title->Draw();
        title->Delete();
        break;        
    case eScene_Tutorial:
        tutorial->Load();
        tutorial->Draw();
        tutorial->Delete();
        break;
    case eScene_Game:
        game->Rode();
        game->Loop();
        game->Delete();
        break;
    case eScene_GameClear:
        result->Rode();
        result->Draw(point);
        result->Delete();
        break;
    }
}

void SceneMgr::LoadAnimation(const int x, const int y,const int animImg[], const int numFlame, int& flameCounter)
{
flameCounter++;
}

// 引数 nextScene にシーンを変更する
void SceneMgr_ChangeScene(eScene NextScene) {
    Scene = NextScene;
}