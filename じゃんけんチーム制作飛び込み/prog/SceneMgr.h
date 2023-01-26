#ifndef _SCENEMGR_H_
#define _SCENEMGR_H_
#include "Game.h"
#include "Title.h"
#include "result.h"
#include "pointMng.h"
#include "BGM_SE.h"
#include"Tutorial.h"
typedef enum {
    eScene_Title,    //設定画面
    
    eScene_Game,     //ゲーム画面
    eScene_GameClear,     //ゲーム画面
    eScene_Tutorial, //チュートリアル
} eScene;

static eScene Scene;    //シーン管理変数

void SceneMgr_ChangeScene(eScene nextScene);
/*
@fn SceneMgr_ChangeScene(eScene nextScene)
@brief 呼び出すことで次のシーンに遷移する
@param nextScene 移りたいシーンを指定できる
*/



class SceneMgr
{
public:
    SceneMgr();
    ~SceneMgr();

    //更新
    void SceneMgr_Update();

    //描画
    void SceneMgr_Draw();
private:
    class Game*  game;
    class Title* title;
    class Result* result;
    class pointMng* point;
    class Tutorial* tutorial;
    class Fade* fade=new Fade;
    class BGMSE* sound=new BGMSE;
    int loadAnim[4];   //ロード画面アニメーションの画像のハンドル
    int flameCounter;
    int BackScene;//ひとつまえのScene
    /// <summary>
    /// ローディングアニメ再生用　DxLib必要
    /// </summary>
    /// <param name="x">描画位置X</param>
    /// <param name="y">描画位置Y</param>
    /// <param name="animImg">画像配列</param>
    /// <param name="numFlame">配列数</param>
    /// <param name="flameCounter">現在のコマ数を記憶</param>
    void LoadAnimation(const int x, const int y, const int animImg[],const int numFlame, int& flameCounter);
    int loadImgX, loadImgY;
    int waitImg;

    bool SoundFlag;
};
#endif // !_SCENEMGR_H_
