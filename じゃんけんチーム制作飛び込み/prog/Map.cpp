#include "DxLib.h"
#include "Map.h"



Map::Map()
{/*
//	x=25.0;
//	y=0;
//	z=-100.0;*/
	x = -400.0;
	y = 45;
	z = 0.0;
	TitleFont = CreateFontToHandle(NULL, 30, 10);
	float scalenum = 2.0f;
	VECTOR scale=VGet(1.0f* scalenum, 1.0f * scalenum, 1.0f * scalenum);
	VECTOR scaleD = VGet(1.0f * scalenum, 1.0f * scalenum, 1.0f * scalenum);
	// モデルハンドルにモデルを入れる
	//MapModelHandle = MV1LoadModel("data/Map/pool.pmx");
	// モデルハンドルにモデルを入れる
	//Map\pool_25m_v5
	MapModelHandle = MV1LoadModel("data/屋内プールv_0_8_2/屋内プール（短水路）v0_8_2.pmx");

	/*divingBoardModelHandle = MV1LoadModel("data/Map/プールa13/pool.x");*/
	MV1SetScale(MapModelHandle,scale );

	MV1SetRotationXYZ(MapModelHandle, VGet(0.0f * DX_PI_F/180.0f, 90.0f * DX_PI_F / 180.0f, 0.0f*DX_PI_F / 180.0f));

	divingBoardModelHandle = MV1LoadModel("data/Map/divingBoard.pmx");
	MV1SetScale(divingBoardModelHandle,scaleD );
	// 座標の指定
	MapPos = VGet(0, 0,0);
	// 座標の指定
	DbPos = VGet(x, y, z);
}
Map::~Map()
{
	// モデルの削除
	MV1DeleteModel(MapModelHandle);
	// モデルの削除
	MV1DeleteModel(divingBoardModelHandle);
	DeleteFontToHandle(TitleFont);
}
void Map::Map_Draw()
{
	
	/*if (CheckHitKey(KEY_INPUT_LEFT))
	{
		x++;
	}
	if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		x--;
	}
	if (CheckHitKey(KEY_INPUT_UP))
	{
		z++;
	}
	if (CheckHitKey(KEY_INPUT_DOWN))
	{
		z--;
	}*/
	DbPos = VGet(x, y, z);
	// モデルにポジションをセット
	MV1SetPosition(MapModelHandle, MapPos);
	// モデルにポジションをセット
	MV1SetPosition(divingBoardModelHandle, DbPos);
	// モデルの描画
	MV1DrawModel(MapModelHandle);
	// モデルの描画
	MV1DrawModel(divingBoardModelHandle);/*
	DrawFormatStringToHandle(0, 100, GetColor(255, 255, 255), TitleFont, " xの値は %.2f です", x);
	DrawFormatStringToHandle(0, 150, GetColor(255, 255, 255), TitleFont, " yの値は %.2f です", y);
	DrawFormatStringToHandle(0, 200, GetColor(255, 255, 255), TitleFont, " zの値は %.2f です", z);*/
}