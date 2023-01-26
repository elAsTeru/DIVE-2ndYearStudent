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
	// ���f���n���h���Ƀ��f��������
	//MapModelHandle = MV1LoadModel("data/Map/pool.pmx");
	// ���f���n���h���Ƀ��f��������
	//Map\pool_25m_v5
	MapModelHandle = MV1LoadModel("data/�����v�[��v_0_8_2/�����v�[���i�Z���H�jv0_8_2.pmx");

	/*divingBoardModelHandle = MV1LoadModel("data/Map/�v�[��a13/pool.x");*/
	MV1SetScale(MapModelHandle,scale );

	MV1SetRotationXYZ(MapModelHandle, VGet(0.0f * DX_PI_F/180.0f, 90.0f * DX_PI_F / 180.0f, 0.0f*DX_PI_F / 180.0f));

	divingBoardModelHandle = MV1LoadModel("data/Map/divingBoard.pmx");
	MV1SetScale(divingBoardModelHandle,scaleD );
	// ���W�̎w��
	MapPos = VGet(0, 0,0);
	// ���W�̎w��
	DbPos = VGet(x, y, z);
}
Map::~Map()
{
	// ���f���̍폜
	MV1DeleteModel(MapModelHandle);
	// ���f���̍폜
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
	// ���f���Ƀ|�W�V�������Z�b�g
	MV1SetPosition(MapModelHandle, MapPos);
	// ���f���Ƀ|�W�V�������Z�b�g
	MV1SetPosition(divingBoardModelHandle, DbPos);
	// ���f���̕`��
	MV1DrawModel(MapModelHandle);
	// ���f���̕`��
	MV1DrawModel(divingBoardModelHandle);/*
	DrawFormatStringToHandle(0, 100, GetColor(255, 255, 255), TitleFont, " x�̒l�� %.2f �ł�", x);
	DrawFormatStringToHandle(0, 150, GetColor(255, 255, 255), TitleFont, " y�̒l�� %.2f �ł�", y);
	DrawFormatStringToHandle(0, 200, GetColor(255, 255, 255), TitleFont, " z�̒l�� %.2f �ł�", z);*/
}