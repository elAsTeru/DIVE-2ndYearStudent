#include "Game.h"
#include "Player.h"
#include "Camera.h"
#include "bridge.h"
#include "SceneMgr.h"

Game::Game()
{
	rodeFlag = TRUE;
	deleteFlag = FALSE;
	callend = false;
	firstCall = false;
	TitleFont = CreateFontToHandle(NULL, 50, 10, DX_FONTTYPE_EDGE, -1, 5, true);
}
Game::~Game()
{
}
void Game::Update(pointMng* pointM)
{
	
	if (fade->GetFadeinEndFlag())
	{
		//�Ăяo������x�ڂ̎�
		if (firstCall == false)
		{
			//�J�E���g�J�n
			startCount = GetNowCount();
			//�Ăяo���t���t�𗧂Ă�
			firstCall = true;
			se->SoundSE(se->SE_CHEER);
		}
		//���Ԃ�b�ɒ���
		Time = (GetNowCount() - startCount) / 1000;
		
		//�Q�[�����ɃJ�E���g�_�E�������Ȃ����߂̏���
		if (3 - Time < 0 && !callend)
		{
			//�Q�[���I�[�o�[�̂��߂̃J�E���g�J�n
			startCount = GetNowCount();
			//����Ăяo���Ȃ����߂̃t���O�𗧂Ă�
			callend = true;
			se->StopSoundSE(se->SE_CHEER);
		}
	}
	

	// �V�[�����Q�[�����E�C���h�E��������܂Ń��[�v
	if (ProcessMessage() == 0 && (CheckHitKey(KEY_INPUT_ESCAPE) == 0 && Scene == 0) && callend == true)
	{


		// �v���C���[�s��
		player->Update();
		//�ʒu�ɍ����|��������X���E�t���O�𗧂Ă�
		if (STAGE_POS_Y_START[NowStage] >= player->middlePos.y)
		{
			if (NowStage == 3)
			{
				slow->LAST_SlowSwitch_ON();
				/*player->middlePos.y=STAGE_POS_Y_START[NowStage];*/
			}
			if (NowStage < 4)
			{
				slow->SlowSwitch_ON();
			}
		}
		//�ʒu�ɍ����|��������X���E�t���O��܂�
		if (STAGE_POS_Y_END[NowStage] >= player->middlePos.y)
		{
			if (NowStage < 4)
			{

				slow->SlowSwitch_OFF();
				point += slow->returnPoint();

			}

			NowStage++;

		}

		if (55 >= player->middlePos.y)//�N���A����
		{
			ClearFlag = true;
		}

		if (ClearFlag)
		{
			if (oneceagain)//��x����
			{
				startCount = GetNowCount();
				se->SoundSE(se->SE_WATER);
				oneceagain = false;
				fade->SetChangeScene();
			}

			if (((GetNowCount() - startCount) / 1000) >= 1)//��b�҂�
			{



				if (fade->GetFadeoutEndFlag())
				{
					pointM->setPoint(point);
					SceneMgr_ChangeScene(eScene::eScene_GameClear);
					GameInit();
					deleteFlag = true;
				}
				
			}
		}
		slow->SlowMode_Update(player, NowStage);



	}
}
void Game::Loop()
{
	if (ProcessMessage() == 0 && (CheckHitKey(KEY_INPUT_ESCAPE) == 0 && Scene == 0))
	{

		// �J�����ʒu
		camera->GetPos(*player, player->Getjumpflag());
		//// ���̕`��
		/*bridge->Draw(player->GetPos());*/
		map->Map_Draw();
		if (slow->returnSlowFlag())
		{

			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
			DrawGraph(0, 0, WhiteBack, true);
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
		}
		// �v���C���[�`��.
		slow->SlowMode_Draw(NowStage);

		player->Draw();

		/// <summary>
		/// �ύX�_���������_��
		/// </summary>
		if (player->middlePos.y < 60 && player->middlePos.y > 55)
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
			DrawGraph(0, -45, lastMiniGameModelHandel, TRUE);
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
		}

		



		//�O�b�J�E���g��������Ă��Ȃ����J�E���g�_�E���t���O�������Ă��Ȃ�
		if (3 - Time >= 0 && callend == false)
		{

			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 170);
			DrawGraph(0, 0, BlackBack, true);
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
			if ((3 - Time) > 0)
			{
				//�J�E���g�_�E��
				DrawFormatStringToHandle(590, 400, RedCode, TimeFont, "%d", 3 - Time);
			}
			else
			{
				//�J�E���g�_�E��
				DrawFormatStringToHandle(490, 400, RedCode, TimeFont, "START");
			}

			DrawGraph(0, 600, Description, true);
		}
	}
	fade->DrawFadeOut();
	fade->DrawFadein();
}

void Game::GameInit()
{
	player->playerInit();
	slow->Init();
	callend = false;
	firstCall = false;
	point = 0;
	oneceagain = true;
	NowStage = 0;
	ClearFlag = false;
}

void Game::Rode()
{
	if (rodeFlag == TRUE)
	{
		player = new Player();
		/*enemy  = new EnemyManager();*/
		camera = new Camera();;
		map = new Map();
		slow = new SLOW;
		se = new BGMSE;
		fade = new Fade;
		/*enemy->CreateEnemys();*/
		TimeFont = CreateFontToHandle("Impact", 100, 10);
		CountDownFont = CreateFontToHandle("Impact", 32, 10);
		RedCode = GetColor(255, 0, 0);
		Description = LoadGraph("data/img/���� (2).png");
		WhiteBack = LoadGraph("data/img/whiteback.png");
		BlackBack = LoadGraph("data/img/blackback.png");
		lastMiniGameModelHandel = LoadGraph("data/img/lastMinigame.png");
		startCount = 0;
		NowStage = 0;
		rodeFlag = FALSE;
		


		fade->SetinScene();

	}
}
void Game::Delete()
{
	if (deleteFlag == TRUE)
	{
		// �G�l�~�[�̉��
		/*enemy->DestroyEnemys();*/
		// �N���X�̉��
		delete(player);
		/*delete(enemy);*/
		delete(camera);
		delete(map);
		delete(slow);
		delete(se);
		delete(fade);
		// �摜�̍폜
		DeleteGraph(Description);
		DeleteGraph(WhiteBack);
		DeleteGraph(BlackBack);
		// �t�H���g�̍폜
		DeleteFontToHandle(TimeFont);
		DeleteFontToHandle(CountDownFont);
		// SE�EBGM�̍폜



		rodeFlag = TRUE;
		deleteFlag = FALSE;
	}
}