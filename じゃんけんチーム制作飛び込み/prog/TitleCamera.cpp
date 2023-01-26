#include "DxLib.h"
#include "TitleCamera.h"


#define FirstCameraPostion  VGet(0, 55, -85)
#define FirstGazePoint      VGet(-50, 100, 0)
#define SecondCameraPostion VGet(0, 55, 85)
#define SecondGazePoint     VGet(-50, 100, 0)
#define ThirdCameraPostion  VGet(-50, 200, 0)
#define ThirdGazePoint      VGet(-50, 0, 0)

#define CameraMoveX         1.0f
#define CameraMoveY         0.1f
#define CameraMoveZ         0.1f

#define MaxDistance         250.0f


TitleCamera::TitleCamera()
{
	SetCameraNearFar(3.0f, 1000.0f);
	CameraPos        = VGet(0, 0, 0);
	GazePoint        = VGet(0, 0, 0);
	OnlyOnceFlag     = TRUE;
	NumCamera        = FirstCamera;

}
TitleCamera::~TitleCamera()
{
}
void TitleCamera::TitleCamera_Update()
{
	switch (NumCamera) 
	{
	case FirstCamera:


		if (OnlyOnceFlag == TRUE)
		{
			CameraPos    = FirstCameraPostion;
			GazePoint    = FirstGazePoint;
			OnlyOnceFlag = FALSE;
		}
		if (CameraPos.x > MaxDistance)
		{
			OnlyOnceFlag = TRUE;
			NumCamera = SecondCamera;
		}


			break;
	case SecondCamera:


		if (OnlyOnceFlag == TRUE)
		{
			CameraPos    = SecondCameraPostion;
			GazePoint    = SecondGazePoint;
			OnlyOnceFlag = FALSE;
		}
		if (CameraPos.x > MaxDistance)
		{
			OnlyOnceFlag = TRUE;
			NumCamera    = ThirdCamera;
		}
		
			break;
	case ThirdCamera:
		if (OnlyOnceFlag == TRUE)
		{
			CameraPos    = ThirdCameraPostion;
			GazePoint    = ThirdGazePoint;
			OnlyOnceFlag = FALSE;
		}
		if (CameraPos.x > MaxDistance)
		{
			OnlyOnceFlag = TRUE;
			NumCamera    = FirstCamera;
		}
			break;
	}
}
void TitleCamera::TitleCamera_Calculation()
{
	switch (NumCamera)
	{
	case FirstCamera:

		CameraPos.x += CameraMoveX;
		CameraPos.y += CameraMoveY;
		CameraPos.z += CameraMoveZ;


		break;
	case SecondCamera:


		CameraPos.x += CameraMoveX;
		CameraPos.y += CameraMoveY;
		CameraPos.z += CameraMoveZ;


		break;
	case ThirdCamera:


		CameraPos.x += CameraMoveX;


		break;
	}
}
void TitleCamera::TitleCamera_Draw()
{
	SetCameraPositionAndTarget_UpVecY(CameraPos, GazePoint);
}