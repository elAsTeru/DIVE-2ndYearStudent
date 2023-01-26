#pragma once

class TitleCamera
{
public:


    /*
    @fn �֐���      [TitleCamera()]
    @brief �v��     [�R���X�g���N�^]
    @param ����     []
    @return �Ԃ�l  []
    */
	TitleCamera();


    /*
    @fn �֐���      [~TitleCamera()]
    @brief �v��     [�f�X�g���N�^]
    @param ����     []
    @return �Ԃ�l  []
    */
	~TitleCamera();


    /*
    @fn �֐���      [TitleCamera_Update()]
    @brief �v��     [�X�V]
    @param ����     []
    @return �Ԃ�l  []
    */
    void TitleCamera_Update();


    /*
    @fn �֐���      [TitleCamera_Calculation()]
    @brief �v��     [�v�Z]
    @param ����     []
    @return �Ԃ�l  []
    */
    void TitleCamera_Calculation();


    /*
    @fn �֐���      [TitleCamera_Draw()]
    @brief �v��     [�`��]
    @param ����     []
    @return �Ԃ�l  []
    */
    void TitleCamera_Draw();



private:


    /*
    @fn �֐���      [CameraPos]
    @brief �v��     [�J�����̃|�W�V����]
    @param ����     []
    @return �Ԃ�l  []
    */
	VECTOR CameraPos;


    /*
    @fn �֐���      [GazePoint]
    @brief �v��     [�����_�̍��W]
    @param ����     []
    @return �Ԃ�l  []
    */
    VECTOR GazePoint;


    /*
    @fn �֐���      [NumCamera]
    @brief �v��     [�J�����؂�ւ�]
    @param ����     []
    @return �Ԃ�l  []
    */
    enum
    {
        FirstCamera,
        SecondCamera,
        ThirdCamera,
    }NumCamera;


    /*
    @fn �֐���      [OnlyOnceFlag]
    @brief �v��     [��x�����ʂ邽�߂̃t���O]
    @param ����     []
    @return �Ԃ�l  []
    */
    bool OnlyOnceFlag;

};