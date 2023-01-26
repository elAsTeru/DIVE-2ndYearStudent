#include "bridge.h"
#include <math.h>


// コンストラクタ
Bridge::Bridge()
{
	// ポジションの初期化
	pos = VGet(-10.0f, 0.0f, 0.0f);
	gPos= VGet(10.0f, -300.0f, 0.0f);
	sPos = VGet(0.0f, 0.0f, 0.0f);
	//移動力の設定
	velocity = VGet(0, 0, 0);

	//移動量の設定
	move = 1.0f;




	bridgeModelHandle = MV1LoadModel("data/back/bridge.pmx");
	gateModelHandle = MV1LoadModel("data/back/bridge.pmx");
	/*startModelHandle = MV1LoadModel("data/ゴールゲート/中間ゲート.pmx");*/
	MV1SetPosition(bridgeModelHandle, pos);
	MV1SetPosition(gateModelHandle, gPos);
	MV1SetPosition(startModelHandle, sPos);

	background= LoadGraph("data/img/BackGround.png");

	backPrintx = 0;
}
// デストラクタ
Bridge::~Bridge()
{
	// モデルのアンロード.
	MV1DeleteModel(bridgeModelHandle);
	/*MV1DeleteModel(gateModelHandle);
	MV1DeleteModel(startModelHandle);*/

	DeleteGraph(background);
}

void Bridge::Update()
{
	// 加速処理.
	VECTOR accelVec = VGet(0, 0, 0);

	////pos.zをmoveで引き続ける
	//pos.x -= move;

	// ポジションを更新.
	pos = VAdd(pos, velocity);

	// ポジションを更新
	MV1SetPosition(bridgeModelHandle, pos);
}

void Bridge::Draw(const VECTOR player_x)
{
	if (backPrintx >= 1280)
	{
		backPrintx = 0;
	}
	backPrintx = (int)-player_x.x;
	// 3Ⅾモデルの回転

	MV1SetRotationXYZ(bridgeModelHandle, VGet(0.0f, 180.0f * DX_PI_F / 180.0f, -80.0f));
	DrawGraph(backPrintx,0, background, false);
	DrawGraph(backPrintx+1280, 0, background,false);
	MV1SetRotationXYZ(gateModelHandle, VGet(0.0f, 90.0f * DX_PI_F / 180.0f, 0.0f));
	//MV1SetRotationXYZ(startModelHandle, VGet(0.0f, 90.0f * DX_PI_F / 180.0f, 0.0f));*/

	
	// ３Dモデルのポジション設定
	MV1DrawModel(bridgeModelHandle);
	MV1DrawModel(gateModelHandle);

}