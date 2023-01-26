#pragma once

class Circle
{
public:

    /*
    @fn 関数名      [Circle()]
    @brief 要約     [コンストラクタ]
    @param 引数     []
    @return 返り値  []
    */
	Circle();

    /*
    @fn 関数名      [~Circle()]
    @brief 要約     [デストラクタ]
    @param 引数     []
    @return 返り値  []
    */
	~Circle();

    /*
    @fn 関数名      [~Circle()]
    @brief 要約     [デストラクタ]
    @param 引数     []
    @return 返り値  []
    */
    void Circle_Draw();


    /*
    @fn 関数名      [~Circle()]
    @brief 要約     [デストラクタ]
    @param 引数     []
    @return 返り値  []
    */
    void Circle_Calculation();


    /*
    @fn 関数名      [~Circle()]
    @brief 要約     [デストラクタ]
    @param 引数     []
    @return 返り値  []
    */
    void Circle_Point();


    /*
    @fn 関数名      [~Circle()]
    @brief 要約     [デストラクタ]
    @param 引数     []
    @return 返り値  []
    */
    void Circle_Init();

    int Getpoint() { return cPoint; };
    bool GetputKey() {  return pushFlag;};
private:


    /*
    @fn 関数名      [Cr]
    @brief 要約     [サークル枠の色]
    @param 引数     []
    @return 返り値  []
    */
    unsigned int Cr;


    /*
    @fn 関数名      [mpCr]
    @brief 要約     [得点のサークルの枠の色]
    @param 引数     []
    @return 返り値  []
    */
    unsigned int mpCr;


    /*
    @fn 関数名      [cCr]
    @brief 要約     [サークルの色]
    @param 引数     []
    @return 返り値  []
    */
    unsigned int cCr;


    /*
    @fn 関数名      [CircleSize]
    @brief 要約     [サークルの大きさ]
    @param 引数     []
    @return 返り値  []
    */
    int CircleSize;


    /*
    @fn 関数名      [nowCircle]
    @brief 要約     [今のサークル]
    @param 引数     []
    @return 返り値  []
    */
    int nowCircle;


    /*
    @fn 関数名      [maxCircle]
    @brief 要約     [サークルの最大値]
    @param 引数     []
    @return 返り値  []
    */
    int maxCircle;


    /*
    @fn 関数名      [minCircle]
    @brief 要約     [サークルの最小値]
    @param 引数     []
    @return 返り値  []
    */
    int minCircle;


    /*
    @fn 関数名      [moveCircle]
    @brief 要約     [動いているサークル]
    @param 引数     []
    @return 返り値  []
    */
    int moveCircle;


    /*
    @fn 関数名      [maxPoint]
    @brief 要約     [最大得点値]
    @param 引数     []
    @return 返り値  []
    */
    int maxPoint;


    /*
    @fn 関数名      [cPoint]
    @brief 要約     [獲得得点値]
    @param 引数     []
    @return 返り値  []
    */
    int cPoint;


    /*
    @fn 関数名      [circleScale]
    @brief 要約     [サークルの拡大縮小フラグ]
    @param 引数     []
    @return 返り値  []
    */
    bool circleScale;


    /*
    @fn 関数名      [pushFlag]
    @brief 要約     [キーの判定フラグ]
    @param 引数     []
    @return 返り値  []
    */
    bool pushFlag;

};