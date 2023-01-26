#ifndef _SCENEMGR_H_
#define _SCENEMGR_H_
#include "Game.h"
#include "Title.h"
#include "result.h"
#include "pointMng.h"
#include "BGM_SE.h"
#include"Tutorial.h"
typedef enum {
    eScene_Title,    //�ݒ���
    
    eScene_Game,     //�Q�[�����
    eScene_GameClear,     //�Q�[�����
    eScene_Tutorial, //�`���[�g���A��
} eScene;

static eScene Scene;    //�V�[���Ǘ��ϐ�

void SceneMgr_ChangeScene(eScene nextScene);
/*
@fn SceneMgr_ChangeScene(eScene nextScene)
@brief �Ăяo�����ƂŎ��̃V�[���ɑJ�ڂ���
@param nextScene �ڂ肽���V�[�����w��ł���
*/



class SceneMgr
{
public:
    SceneMgr();
    ~SceneMgr();

    //�X�V
    void SceneMgr_Update();

    //�`��
    void SceneMgr_Draw();
private:
    class Game*  game;
    class Title* title;
    class Result* result;
    class pointMng* point;
    class Tutorial* tutorial;
    class Fade* fade=new Fade;
    class BGMSE* sound=new BGMSE;
    int loadAnim[4];   //���[�h��ʃA�j���[�V�����̉摜�̃n���h��
    int flameCounter;
    int BackScene;//�ЂƂ܂���Scene
    /// <summary>
    /// ���[�f�B���O�A�j���Đ��p�@DxLib�K�v
    /// </summary>
    /// <param name="x">�`��ʒuX</param>
    /// <param name="y">�`��ʒuY</param>
    /// <param name="animImg">�摜�z��</param>
    /// <param name="numFlame">�z��</param>
    /// <param name="flameCounter">���݂̃R�}�����L��</param>
    void LoadAnimation(const int x, const int y, const int animImg[],const int numFlame, int& flameCounter);
    int loadImgX, loadImgY;
    int waitImg;

    bool SoundFlag;
};
#endif // !_SCENEMGR_H_
