#pragma once

class TitleCamera
{
public:


    /*
    @fn 関数名      [TitleCamera()]
    @brief 要約     [コンストラクタ]
    @param 引数     []
    @return 返り値  []
    */
	TitleCamera();


    /*
    @fn 関数名      [~TitleCamera()]
    @brief 要約     [デストラクタ]
    @param 引数     []
    @return 返り値  []
    */
	~TitleCamera();


    /*
    @fn 関数名      [TitleCamera_Update()]
    @brief 要約     [更新]
    @param 引数     []
    @return 返り値  []
    */
    void TitleCamera_Update();


    /*
    @fn 関数名      [TitleCamera_Calculation()]
    @brief 要約     [計算]
    @param 引数     []
    @return 返り値  []
    */
    void TitleCamera_Calculation();


    /*
    @fn 関数名      [TitleCamera_Draw()]
    @brief 要約     [描画]
    @param 引数     []
    @return 返り値  []
    */
    void TitleCamera_Draw();



private:


    /*
    @fn 関数名      [CameraPos]
    @brief 要約     [カメラのポジション]
    @param 引数     []
    @return 返り値  []
    */
	VECTOR CameraPos;


    /*
    @fn 関数名      [GazePoint]
    @brief 要約     [注視点の座標]
    @param 引数     []
    @return 返り値  []
    */
    VECTOR GazePoint;


    /*
    @fn 関数名      [NumCamera]
    @brief 要約     [カメラ切り替え]
    @param 引数     []
    @return 返り値  []
    */
    enum
    {
        FirstCamera,
        SecondCamera,
        ThirdCamera,
    }NumCamera;


    /*
    @fn 関数名      [OnlyOnceFlag]
    @brief 要約     [一度だけ通るためのフラグ]
    @param 引数     []
    @return 返り値  []
    */
    bool OnlyOnceFlag;

};