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
		//呼び出しが一度目の時
		if (firstCall == false)
		{
			//カウント開始
			startCount = GetNowCount();
			//呼び出しフラフを立てる
			firstCall = true;
			se->SoundSE(se->SE_CHEER);
		}
		//時間を秒に直す
		Time = (GetNowCount() - startCount) / 1000;
		
		//ゲーム中にカウントダウンをしないための処理
		if (3 - Time < 0 && !callend)
		{
			//ゲームオーバーのためのカウント開始
			startCount = GetNowCount();
			//今後呼び出さないためのフラグを立てる
			callend = true;
			se->StopSoundSE(se->SE_CHEER);
		}
	}
	

	// シーンがゲームかウインドウが閉じられるまでループ
	if (ProcessMessage() == 0 && (CheckHitKey(KEY_INPUT_ESCAPE) == 0 && Scene == 0) && callend == true)
	{


		// プレイヤー行動
		player->Update();
		//位置に差し掛かったらスロウフラグを立てる
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
		//位置に差し掛かったらスロウフラグを折る
		if (STAGE_POS_Y_END[NowStage] >= player->middlePos.y)
		{
			if (NowStage < 4)
			{

				slow->SlowSwitch_OFF();
				point += slow->returnPoint();

			}

			NowStage++;

		}

		if (55 >= player->middlePos.y)//クリア条件
		{
			ClearFlag = true;
		}

		if (ClearFlag)
		{
			if (oneceagain)//一度だけ
			{
				startCount = GetNowCount();
				se->SoundSE(se->SE_WATER);
				oneceagain = false;
				fade->SetChangeScene();
			}

			if (((GetNowCount() - startCount) / 1000) >= 1)//二秒待つ
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

		// カメラ位置
		camera->GetPos(*player, player->Getjumpflag());
		//// 橋の描画
		/*bridge->Draw(player->GetPos());*/
		map->Map_Draw();
		if (slow->returnSlowFlag())
		{

			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
			DrawGraph(0, 0, WhiteBack, true);
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
		}
		// プレイヤー描画.
		slow->SlowMode_Draw(NowStage);

		player->Draw();

		/// <summary>
		/// 変更点＜緒方＞点線
		/// </summary>
		if (player->middlePos.y < 60 && player->middlePos.y > 55)
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
			DrawGraph(0, -45, lastMiniGameModelHandel, TRUE);
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
		}

		



		//三秒カウントがおわっていないかつカウントダウンフラグが立っていない
		if (3 - Time >= 0 && callend == false)
		{

			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 170);
			DrawGraph(0, 0, BlackBack, true);
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
			if ((3 - Time) > 0)
			{
				//カウントダウン
				DrawFormatStringToHandle(590, 400, RedCode, TimeFont, "%d", 3 - Time);
			}
			else
			{
				//カウントダウン
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
		Description = LoadGraph("data/img/説明 (2).png");
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
		// エネミーの解放
		/*enemy->DestroyEnemys();*/
		// クラスの解放
		delete(player);
		/*delete(enemy);*/
		delete(camera);
		delete(map);
		delete(slow);
		delete(se);
		delete(fade);
		// 画像の削除
		DeleteGraph(Description);
		DeleteGraph(WhiteBack);
		DeleteGraph(BlackBack);
		// フォントの削除
		DeleteFontToHandle(TimeFont);
		DeleteFontToHandle(CountDownFont);
		// SE・BGMの削除



		rodeFlag = TRUE;
		deleteFlag = FALSE;
	}
}