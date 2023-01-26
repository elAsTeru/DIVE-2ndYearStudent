#pragma once
#include "DxLib.h"


class Map
{
public:

    /*
    @fn 関数名      [Map()]
    @brief 要約     [コンストラクタ]
    @param 引数     []
    @return 返り値  []
    */
    Map();

    /*
    @fn 関数名      [~Map()]
    @brief 要約     [デストラクタ]
    @param 引数     []
    @return 返り値  []
    */
    ~Map();

    /*
    @fn 関数名      [Map_Draw()]
    @brief 要約     [描画]
    @param 引数     []
    @return 返り値  []
    */
    void Map_Draw();

private:

    /*
    @fn 関数名      [MapModelHandle]
    @brief 要約     [マップのモデル保存変数]
    @param 引数     []
    @return 返り値  []
    */
    int MapModelHandle;

    /*
    @fn 関数名      [divingBoardModelHandle]
    @brief 要約     [飛び込み台のモデル保存変数]
    @param 引数     []
    @return 返り値  []
    */
    int divingBoardModelHandle;

    /*
    @fn 関数名      [MapPos]
    @brief 要約     [マップの座標]
    @param 引数     []
    @return 返り値  []
    */
    VECTOR MapPos;

    /*
    @fn 関数名      [Dbpos]
    @brief 要約     [飛び込み台の座標]
    @param 引数     []
    @return 返り値  []
    */
    VECTOR DbPos;

    float x;
    float y;
    float z;
    int  TitleFont;
};