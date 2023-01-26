#include "DxLib.h"
#include "Title.h"
#include "SceneMgr.h"



Title::Title()
{
    rodeFlag   = TRUE;
    deleteFlag = FALSE;
}
Title::~Title()
{
    DeleteGraph(SPACEImg);
    DeleteGraph(GAMESTARTimg);
    DeleteGraph(background);
    DeleteGraph(TitleImg);
}
void Title::Update()
{
    ExpansionRate += changeCode;
    if (ExpansionRate >= 3)
    {
        changeCode = -0.3f;
    }
    if (ExpansionRate < 0)
    {
        changeCode = 0.3f;
    }
    
    camera->TitleCamera_Update();
    camera->TitleCamera_Calculation();
    if (CheckHitKey(KEY_INPUT_SPACE))
    {
        fade->SetChangeScene();
        //if (fade->GetFadeoutEndFlag())//フェードアウトが終われば変化
        //{
        //    SceneMgr_ChangeScene(eScene_Game);
        //}
        
        /* flag*/
    }
    if (fade->GetFadeoutEndFlag())//フェードアウトが終われば変化
    {
        SceneMgr_ChangeScene(eScene_Tutorial);
        deleteFlag = true;
    }



}
void Title::Draw()
{

    /*DrawGraph(0, 0, background, false);*/
    camera->TitleCamera_Draw();
    map->Map_Draw();
    DrawExtendGraph(STARTX - (int)ExpansionRate, 500 - (int)ExpansionRate, STARTX + (SPACESIZE_X * imgSize) + (int)ExpansionRate, 500 + (SPACESIZE_Y * imgSize) + (int)ExpansionRate, SPACEImg, false);


    DrawExtendGraph(STARTX + 50 + (SPACESIZE_X * imgSize), 500, STARTX + 50 + (SPACESIZE_X * imgSize) + (STARTSIZE_X * imgSize), 500 + (STARTSIZE_Y * imgSize), GAMESTARTimg, true);
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)ExpansionRate * 30);
    DrawBox(STARTX + 50 + (SPACESIZE_X * imgSize), 500, STARTX + 50 + (SPACESIZE_X * imgSize) + (STARTSIZE_X * imgSize), 500 + (STARTSIZE_Y * imgSize), GetColor(255, 255, 0), true);
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
    DrawGraph(100, 200, TitleImg, true);

    fade->DrawFadeOut();//シーン遷移でフェードアウト
    fade->DrawFadein();
}
void Title::Rode()
{
    if (rodeFlag == TRUE)
    {
        ExpansionRate = 0;
        changeCode = 0.3f;
        SPACEImg = LoadGraph("data/img/SPACEキー1.png");
        GAMESTARTimg = LoadGraph("data/img/GAMESTART1.png");
        background = LoadGraph("data/img/ResultImg.png");
        TitleImg = LoadGraph("data/img/タイトル (1).png");
        imgSize = 1.5f;
        map = new Map;
        camera = new TitleCamera;
        fade = new Fade;
        rodeFlag = FALSE;
        fade->SetinScene();
    }
}
void Title::Delete()
{
    if (deleteFlag == TRUE)
    {
        delete(map);
        delete(camera);
        delete(fade);
        DeleteGraph(SPACEImg);
        DeleteGraph(GAMESTARTimg);
        DeleteGraph(background);
        DeleteGraph(TitleImg);
        rodeFlag   = TRUE;
        deleteFlag = FALSE;
    }
}