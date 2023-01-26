#include "DxLib.h"
#include "SceneMgr.h"
#include"Fps.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	// �c�w���C�u��������������
	if (DxLib_Init() == -1)
	{
		return -1;	// �G���[���N�����璼���ɏI��
	}

	// ��ʃ��[�h�̃Z�b�g
	SetGraphMode(1280, 800, 16);
	// �E�B���h�E���[�h�\��
	ChangeWindowMode(true);
	// �`����ʂ𗠉�ʂɂ���
	SetDrawScreen(DX_SCREEN_BACK);

	SceneMgr* sceneMgr = new SceneMgr();
	Fps fps;
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0 && ClearDrawScreen() == 0)
	{
		fps.Update();

		sceneMgr->SceneMgr_Update();  //�X�V
		sceneMgr->SceneMgr_Draw();    //�`��
		/*fps.Draw();*/

		fps.Wait();
	}

	// �c�w���C�u�����̌�n��
	DxLib_End();
	// �\�t�g�̏I��
	return 0;

}