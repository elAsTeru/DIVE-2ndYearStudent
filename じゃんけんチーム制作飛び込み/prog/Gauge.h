#pragma once

class Gauge
{
public:

    /*
    @fn �֐���      [Gauge()]
    @brief �v��     [�R���X�g���N�^]
    @param ����     []
    @return �Ԃ�l  []
    */
	Gauge();

    /*
    @fn �֐���      [Gauge()]
    @brief �v��     [�f�X�g���N�^]
    @param ����     []
    @return �Ԃ�l  []
    */
	~Gauge();

    /*
    @fn �֐���      [Gauge_Draw()]
    @brief �v��     [�Q�[�W�̕`��]
    @param ����     []
    @return �Ԃ�l  []
    */
    void Gauge_Draw();

    /*
    @fn �֐���      [Gauge_Calculation()]
    @brief �v��     [�Q�[�W�̓����̌v�Z]
    @param ����     []
    @return �Ԃ�l  []
    */
    void Gauge_Calculation();

    /*
    @fn �֐���      [Gauge_Point()]
    @brief �v��     [���_�̎Z�o]
    @param ����     []
    @return �Ԃ�l  []
    */
    void Gauge_Point();

    /*
    @fn �֐���      [Gauge_Init()]
    @brief �v��     [������]
    @param ����     []
    @return �Ԃ�l  []
    */
    void Gauge_Init();

    int Gauge_point_get() { return Point; };//�Ăяo�����Ɠ��_��������
    void randPointSet();
    bool GetputKey() { return pushFlag; };
private:

    /*
    @fn �֐���      [Cr]
    @brief �v��     [�Q�[�W�g�̐F]
    @param ����     []
    @return �Ԃ�l  []
    */
    unsigned int Cr;

    /*
    @fn �֐���      [gCr]
    @brief �v��     [�Q�[�W�̐F]
    @param ����     []
    @return �Ԃ�l  []
    */
    unsigned int gCr;


    /*
    @fn �֐���      [mpCr]
    @brief �v��     [�}�b�N�X�|�C���g�̐F]
    @param ����     []
    @return �Ԃ�l  []
    */
    unsigned int mpCr;


    /*
    @fn �֐���      [gaugeYoko]
    @brief �v��     [�Q�[�W�̉���]
    @param ����     []
    @return �Ԃ�l  []
    */
    int gaugeYoko = 400;

    /*
    @fn �֐���      [nowGauge]
    @brief �v��     [���݂̃Q�[�W]
    @param ����     []
    @return �Ԃ�l  []
    */
    int nowGauge = 100;

    /*
    @fn �֐���      [maxGauge]
    @brief �v��     [�Q�[�W�̍ő�l]
    @param ����     []
    @return �Ԃ�l  []
    */
    int maxGauge = 100;

    /*
    @fn �֐���      [minGauge]
    @brief �v��     [�Q�[�W�̍ŏ��l]
    @param ����     []
    @return �Ԃ�l  []
    */
    int minGauge = 0;

    /*
    @fn �֐���      [moveGauge]
    @brief �v��     [�Q�[�W]
    @param ����     []
    @return �Ԃ�l  []
    */
    int moveGauge = 0;


    /*
    @fn �֐���      [maxPoint]
    @brief �v��     [�ō����_�l]
    @param ����     []
    @return �Ԃ�l  []
    */
    int maxPoint;

    /*
    @fn �֐���      [Point]
    @brief �v��     [���_�l]
    @param ����     []
    @return �Ԃ�l  []
    */
    int Point;

    /*
    @fn �֐���      [gaugeUpDown]
    @brief �v��     [�Q�[�W�̏㉺�̂��߂̃t���O]
    @param ����     []
    @return �Ԃ�l  []
    */
    bool gaugeUpDown;

    /*
    @fn �֐���      [pushFlag]
    @brief �v��     [�L�[�̔���t���O]
    @param ����     []
    @return �Ԃ�l  []
    */
    bool pushFlag;

    const int Box_Start_X = 440;//��.x�n�_
    const int Box_End_X   = 0;  //��.x�I�_

    const int Box_Start_Y = 500;//��.y�n�_
    const int Box_End_Y   = 0;  //��.y�I�_

    const int Box_high    = 80;//���c
    const int Box_width   = 400;//����

    int speed;
};