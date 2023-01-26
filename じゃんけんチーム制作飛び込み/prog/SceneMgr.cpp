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
    //SpaceImg = LoadGraph("data/img/SPACE�L�[1.png");
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

//�X�V
void SceneMgr::SceneMgr_Update() 
{
    //�O��Scene��ۑ�
    BackScene = Scene;

    if (SoundFlag == false)
    {
        sound->SoundBGM(Scene);
        //����炵�ăt���O�𗧂Ă�
        SoundFlag = true;
    }
    //�V�[���ɂ���ď����𕪊�
    //���݂̉�ʂ����j���[�Ȃ�
    //���j���[��ʂ̍X�V����������
    //�ȉ���
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


    //���͂��~�߂邽�߂�0.5�b���Ԃ�����
    if (BackScene!=Scene)
    {  
        SoundFlag = false;
        DrawGraph(0, 0, waitImg, false);
        ScreenFlip();
        WaitTimer(500);
        
    }
}

//�`��
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

// ���� nextScene �ɃV�[����ύX����
void SceneMgr_ChangeScene(eScene NextScene) {
    Scene = NextScene;
}