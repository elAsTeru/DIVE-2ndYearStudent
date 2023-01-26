#pragma once
#include "DxLib.h"


class Map
{
public:

    /*
    @fn �֐���      [Map()]
    @brief �v��     [�R���X�g���N�^]
    @param ����     []
    @return �Ԃ�l  []
    */
    Map();

    /*
    @fn �֐���      [~Map()]
    @brief �v��     [�f�X�g���N�^]
    @param ����     []
    @return �Ԃ�l  []
    */
    ~Map();

    /*
    @fn �֐���      [Map_Draw()]
    @brief �v��     [�`��]
    @param ����     []
    @return �Ԃ�l  []
    */
    void Map_Draw();

private:

    /*
    @fn �֐���      [MapModelHandle]
    @brief �v��     [�}�b�v�̃��f���ۑ��ϐ�]
    @param ����     []
    @return �Ԃ�l  []
    */
    int MapModelHandle;

    /*
    @fn �֐���      [divingBoardModelHandle]
    @brief �v��     [��э��ݑ�̃��f���ۑ��ϐ�]
    @param ����     []
    @return �Ԃ�l  []
    */
    int divingBoardModelHandle;

    /*
    @fn �֐���      [MapPos]
    @brief �v��     [�}�b�v�̍��W]
    @param ����     []
    @return �Ԃ�l  []
    */
    VECTOR MapPos;

    /*
    @fn �֐���      [Dbpos]
    @brief �v��     [��э��ݑ�̍��W]
    @param ����     []
    @return �Ԃ�l  []
    */
    VECTOR DbPos;

    float x;
    float y;
    float z;
    int  TitleFont;
};