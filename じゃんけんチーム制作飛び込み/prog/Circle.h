#pragma once

class Circle
{
public:

    /*
    @fn �֐���      [Circle()]
    @brief �v��     [�R���X�g���N�^]
    @param ����     []
    @return �Ԃ�l  []
    */
	Circle();

    /*
    @fn �֐���      [~Circle()]
    @brief �v��     [�f�X�g���N�^]
    @param ����     []
    @return �Ԃ�l  []
    */
	~Circle();

    /*
    @fn �֐���      [~Circle()]
    @brief �v��     [�f�X�g���N�^]
    @param ����     []
    @return �Ԃ�l  []
    */
    void Circle_Draw();


    /*
    @fn �֐���      [~Circle()]
    @brief �v��     [�f�X�g���N�^]
    @param ����     []
    @return �Ԃ�l  []
    */
    void Circle_Calculation();


    /*
    @fn �֐���      [~Circle()]
    @brief �v��     [�f�X�g���N�^]
    @param ����     []
    @return �Ԃ�l  []
    */
    void Circle_Point();


    /*
    @fn �֐���      [~Circle()]
    @brief �v��     [�f�X�g���N�^]
    @param ����     []
    @return �Ԃ�l  []
    */
    void Circle_Init();

    int Getpoint() { return cPoint; };
    bool GetputKey() {  return pushFlag;};
private:


    /*
    @fn �֐���      [Cr]
    @brief �v��     [�T�[�N���g�̐F]
    @param ����     []
    @return �Ԃ�l  []
    */
    unsigned int Cr;


    /*
    @fn �֐���      [mpCr]
    @brief �v��     [���_�̃T�[�N���̘g�̐F]
    @param ����     []
    @return �Ԃ�l  []
    */
    unsigned int mpCr;


    /*
    @fn �֐���      [cCr]
    @brief �v��     [�T�[�N���̐F]
    @param ����     []
    @return �Ԃ�l  []
    */
    unsigned int cCr;


    /*
    @fn �֐���      [CircleSize]
    @brief �v��     [�T�[�N���̑傫��]
    @param ����     []
    @return �Ԃ�l  []
    */
    int CircleSize;


    /*
    @fn �֐���      [nowCircle]
    @brief �v��     [���̃T�[�N��]
    @param ����     []
    @return �Ԃ�l  []
    */
    int nowCircle;


    /*
    @fn �֐���      [maxCircle]
    @brief �v��     [�T�[�N���̍ő�l]
    @param ����     []
    @return �Ԃ�l  []
    */
    int maxCircle;


    /*
    @fn �֐���      [minCircle]
    @brief �v��     [�T�[�N���̍ŏ��l]
    @param ����     []
    @return �Ԃ�l  []
    */
    int minCircle;


    /*
    @fn �֐���      [moveCircle]
    @brief �v��     [�����Ă���T�[�N��]
    @param ����     []
    @return �Ԃ�l  []
    */
    int moveCircle;


    /*
    @fn �֐���      [maxPoint]
    @brief �v��     [�ő哾�_�l]
    @param ����     []
    @return �Ԃ�l  []
    */
    int maxPoint;


    /*
    @fn �֐���      [cPoint]
    @brief �v��     [�l�����_�l]
    @param ����     []
    @return �Ԃ�l  []
    */
    int cPoint;


    /*
    @fn �֐���      [circleScale]
    @brief �v��     [�T�[�N���̊g��k���t���O]
    @param ����     []
    @return �Ԃ�l  []
    */
    bool circleScale;


    /*
    @fn �֐���      [pushFlag]
    @brief �v��     [�L�[�̔���t���O]
    @param ����     []
    @return �Ԃ�l  []
    */
    bool pushFlag;

};