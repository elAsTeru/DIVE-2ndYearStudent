#pragma once

class Gauge
{
public:

    /*
    @fn 関数名      [Gauge()]
    @brief 要約     [コンストラクタ]
    @param 引数     []
    @return 返り値  []
    */
	Gauge();

    /*
    @fn 関数名      [Gauge()]
    @brief 要約     [デストラクタ]
    @param 引数     []
    @return 返り値  []
    */
	~Gauge();

    /*
    @fn 関数名      [Gauge_Draw()]
    @brief 要約     [ゲージの描画]
    @param 引数     []
    @return 返り値  []
    */
    void Gauge_Draw();

    /*
    @fn 関数名      [Gauge_Calculation()]
    @brief 要約     [ゲージの動きの計算]
    @param 引数     []
    @return 返り値  []
    */
    void Gauge_Calculation();

    /*
    @fn 関数名      [Gauge_Point()]
    @brief 要約     [得点の算出]
    @param 引数     []
    @return 返り値  []
    */
    void Gauge_Point();

    /*
    @fn 関数名      [Gauge_Init()]
    @brief 要約     [初期化]
    @param 引数     []
    @return 返り値  []
    */
    void Gauge_Init();

    int Gauge_point_get() { return Point; };//呼び出されると得点をかえす
    void randPointSet();
    bool GetputKey() { return pushFlag; };
private:

    /*
    @fn 関数名      [Cr]
    @brief 要約     [ゲージ枠の色]
    @param 引数     []
    @return 返り値  []
    */
    unsigned int Cr;

    /*
    @fn 関数名      [gCr]
    @brief 要約     [ゲージの色]
    @param 引数     []
    @return 返り値  []
    */
    unsigned int gCr;


    /*
    @fn 関数名      [mpCr]
    @brief 要約     [マックスポイントの色]
    @param 引数     []
    @return 返り値  []
    */
    unsigned int mpCr;


    /*
    @fn 関数名      [gaugeYoko]
    @brief 要約     [ゲージの横幅]
    @param 引数     []
    @return 返り値  []
    */
    int gaugeYoko = 400;

    /*
    @fn 関数名      [nowGauge]
    @brief 要約     [現在のゲージ]
    @param 引数     []
    @return 返り値  []
    */
    int nowGauge = 100;

    /*
    @fn 関数名      [maxGauge]
    @brief 要約     [ゲージの最大値]
    @param 引数     []
    @return 返り値  []
    */
    int maxGauge = 100;

    /*
    @fn 関数名      [minGauge]
    @brief 要約     [ゲージの最小値]
    @param 引数     []
    @return 返り値  []
    */
    int minGauge = 0;

    /*
    @fn 関数名      [moveGauge]
    @brief 要約     [ゲージ]
    @param 引数     []
    @return 返り値  []
    */
    int moveGauge = 0;


    /*
    @fn 関数名      [maxPoint]
    @brief 要約     [最高得点値]
    @param 引数     []
    @return 返り値  []
    */
    int maxPoint;

    /*
    @fn 関数名      [Point]
    @brief 要約     [得点値]
    @param 引数     []
    @return 返り値  []
    */
    int Point;

    /*
    @fn 関数名      [gaugeUpDown]
    @brief 要約     [ゲージの上下のためのフラグ]
    @param 引数     []
    @return 返り値  []
    */
    bool gaugeUpDown;

    /*
    @fn 関数名      [pushFlag]
    @brief 要約     [キーの判定フラグ]
    @param 引数     []
    @return 返り値  []
    */
    bool pushFlag;

    const int Box_Start_X = 440;//箱.x始点
    const int Box_End_X   = 0;  //箱.x終点

    const int Box_Start_Y = 500;//箱.y始点
    const int Box_End_Y   = 0;  //箱.y終点

    const int Box_high    = 80;//箱縦
    const int Box_width   = 400;//箱横

    int speed;
};